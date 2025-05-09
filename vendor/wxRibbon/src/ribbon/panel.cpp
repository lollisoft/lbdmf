///////////////////////////////////////////////////////////////////////////////
// Name:        src/ribbon/panel.cpp
// Purpose:     Ribbon-style container for a group of related tools / controls
// Author:      Peter Cawley
// Modified by:
// Created:     2009-05-25
// RCS-ID:      $Id: panel.cpp,v 1.3.2.1 2025/04/05 16:16:41 lothar Exp $
// Copyright:   (C) Peter Cawley
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wx/ribbon/art.h"
#include "wx/ribbon/bar.h"
#include "wx/ribbon/panel.h"
#include "wx/dcbuffer.h"
#include "wx/display.h"

#if wxUSE_RIBBON

#ifndef WX_PRECOMP
#endif

#ifdef __WXMSW__
#include "wx/msw/private.h"
#endif

#include <wx/image.h>
#include <wx/frame.h>

IMPLEMENT_CLASS(wxRibbonPanel, wxRibbonControl)

BEGIN_EVENT_TABLE(wxRibbonPanel, wxRibbonControl)
    EVT_ENTER_WINDOW(wxRibbonPanel::OnMouseEnter)
    EVT_ERASE_BACKGROUND(wxRibbonPanel::OnEraseBackground)
    EVT_KILL_FOCUS(wxRibbonPanel::OnKillFocus)
    EVT_LEAVE_WINDOW(wxRibbonPanel::OnMouseLeave)
    EVT_LEFT_DOWN(wxRibbonPanel::OnMouseClick)
    EVT_PAINT(wxRibbonPanel::OnPaint)
    EVT_SIZE(wxRibbonPanel::OnSize)
END_EVENT_TABLE()

wxRibbonPanel::wxRibbonPanel()
{
}

wxRibbonPanel::wxRibbonPanel(wxWindow* parent,
                  wxWindowID id,
                  const wxString& label,
                  const wxBitmap& minimised_icon,
                  const wxPoint& pos,
                  const wxSize& size,
                  long style)
    : wxRibbonControl(parent, id, pos, size, wxBORDER_NONE)
{
    CommonInit(label, minimised_icon, style);
}

wxRibbonPanel::~wxRibbonPanel()
{
    if(m_expanded_panel)
    {
        m_expanded_panel->m_expanded_dummy = NULL;
        m_expanded_panel->GetParent()->Destroy();
    }
}

bool wxRibbonPanel::Create(wxWindow* parent,
                wxWindowID id,
                const wxString& label,
                const wxBitmap& icon,
                const wxPoint& pos,
                const wxSize& size,
                long style)
{
    if(!wxRibbonControl::Create(parent, id, pos, size, wxBORDER_NONE))
    {
        return false;
    }

    CommonInit(label, icon, style);

    return true;
}

void wxRibbonPanel::SetArtProvider(wxRibbonArtProvider* art)
{
    m_art = art;
    for ( wxWindowList::compatibility_iterator node = GetChildren().GetFirst();
          node;
          node = node->GetNext() )
    {
        wxWindow* child = node->GetData();
        wxRibbonControl* ribbon_child = wxDynamicCast(child, wxRibbonControl);
        if(ribbon_child)
        {
            ribbon_child->SetArtProvider(art);
        }
    }
    if(m_expanded_panel)
        m_expanded_panel->SetArtProvider(art);
}

void wxRibbonPanel::CommonInit(const wxString& label, const wxBitmap& icon, long style)
{
    SetName(label);
    SetLabel(label);

    m_minimised_size = wxDefaultSize; // Unknown / none
    m_smallest_unminimised_size = wxSize(INT_MAX, INT_MAX); // Unknown / none
    m_preferred_expand_direction = wxSOUTH;
    m_expanded_dummy = NULL;
    m_expanded_panel = NULL;
    m_flags = style;
    m_minimised_icon = icon;
    m_minimised = false;
    m_hovered = false;

    if(m_art == NULL)
    {
        wxRibbonControl* parent = wxDynamicCast(GetParent(), wxRibbonControl);
        if(parent != NULL)
        {
            m_art = parent->GetArtProvider();
        }
    }

    SetAutoLayout(true);
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    SetMinSize(wxSize(20, 20));
}

bool wxRibbonPanel::IsMinimised() const
{
    return m_minimised;
}

bool wxRibbonPanel::IsHovered() const
{
    return m_hovered;
}

void wxRibbonPanel::OnMouseEnter(wxMouseEvent& evt)
{
    TestPositionForHover(evt.GetPosition());
}

void wxRibbonPanel::OnMouseEnterChild(wxMouseEvent& evt)
{
    wxPoint pos = evt.GetPosition();
    wxWindow *child = wxDynamicCast(evt.GetEventObject(), wxWindow);
    if(child)
    {
        pos += child->GetPosition();
        TestPositionForHover(pos);
    }
    evt.Skip();
}

void wxRibbonPanel::OnMouseLeave(wxMouseEvent& evt)
{
    TestPositionForHover(evt.GetPosition());
}

void wxRibbonPanel::OnMouseLeaveChild(wxMouseEvent& evt)
{
    wxPoint pos = evt.GetPosition();
    wxWindow *child = wxDynamicCast(evt.GetEventObject(), wxWindow);
    if(child)
    {
        pos += child->GetPosition();
        TestPositionForHover(pos);
    }
    evt.Skip();
}

void wxRibbonPanel::TestPositionForHover(const wxPoint& pos)
{
    bool hovered = false;
    if(pos.x >= 0 && pos.y >= 0)
    {
        wxSize size = GetSize();
        if(pos.x < size.GetWidth() && pos.y < size.GetHeight())
        {
            hovered = true;
        }
    }
    if(hovered != m_hovered)
    {
        m_hovered = hovered;
        Refresh(false);
    }
}

void wxRibbonPanel::AddChild(wxWindowBase *child)
{
    wxRibbonControl::AddChild(child);

    // Window enter / leave events count for only the window in question, not
    // for children of the window. The panel wants to be in the hovered state
    // whenever the mouse cursor is within its boundary, so the events need to
    // be attached to children too.
    child->Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&wxRibbonPanel::OnMouseEnterChild, NULL, this);
    child->Connect(wxEVT_LEAVE_WINDOW, (wxObjectEventFunction)&wxRibbonPanel::OnMouseLeaveChild, NULL, this);
}

void wxRibbonPanel::RemoveChild(wxWindowBase *child)
{
    child->Disconnect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&wxRibbonPanel::OnMouseEnterChild, NULL, this);
    child->Disconnect(wxEVT_LEAVE_WINDOW, (wxObjectEventFunction)&wxRibbonPanel::OnMouseLeaveChild, NULL, this);

    wxRibbonControl::RemoveChild(child);
}

void wxRibbonPanel::OnSize(wxSizeEvent& evt)
{
    if(GetAutoLayout())
        Layout();

    evt.Skip();
}

void wxRibbonPanel::DoSetSize(int x, int y, int width, int height, int sizeFlags)
{
    // At least on MSW, changing the size of a window will cause GetSize() to
    // report the new size, but a size event may not be handled immediately.
    // If this minimised check was performed in the OnSize handler, then
    // GetSize() could return a size much larger than the minimised size while
    // IsMinimised() returns true. This would then affect layout, as the panel
    // will refuse to grow any larger while in limbo between minimised and non.

    bool minimised = (m_flags & wxRIBBON_PANEL_NO_AUTO_MINIMISE) == 0 &&
        IsMinimised(wxSize(width, height));
    if(minimised != m_minimised)
    {
        m_minimised = minimised;

        for (wxWindowList::compatibility_iterator node = GetChildren().GetFirst();
                  node;
                  node = node->GetNext())
        {
            node->GetData()->Show(!minimised);
        }

        Refresh();
    }
    
    wxRibbonControl::DoSetSize(x, y, width, height, sizeFlags);
}

bool wxRibbonPanel::IsMinimised(wxSize at_size) const
{
    if(!m_minimised_size.IsFullySpecified())
        return false;

    return (at_size.GetX() <= m_minimised_size.GetX() &&
        at_size.GetY() <= m_minimised_size.GetY()) || 
        at_size.GetX() < m_smallest_unminimised_size.GetX() ||
        at_size.GetY() < m_smallest_unminimised_size.GetY();
}

void wxRibbonPanel::OnEraseBackground(wxEraseEvent& WXUNUSED(evt))
{
    // All painting done in main paint handler to minimise flicker
}

void wxRibbonPanel::OnPaint(wxPaintEvent& WXUNUSED(evt))
{
    wxAutoBufferedPaintDC dc(this);

    if(m_art != NULL)
    {
        if(IsMinimised())
        {
            m_art->DrawMinimisedPanel(dc, this, GetSize(), m_minimised_icon_resized);
        }
        else
        {
            m_art->DrawPanelBackground(dc, this, GetSize());
        }
    }
}

bool wxRibbonPanel::IsSizingContinuous() const
{
    // A panel never sizes continuously, even if all of its children can,
    // as it would appear out of place along side non-continuous panels.
    return false;
}

wxSize wxRibbonPanel::DoGetNextSmallerSize(wxOrientation direction,
                                         wxSize relative_to) const
{
    if(m_expanded_panel != NULL)
    {
        // Next size depends upon children, who are currently in the
        // expanded panel
        return m_expanded_panel->DoGetNextSmallerSize(direction, relative_to);
    }

    // TODO: Check for, and delegate to, a sizer

    // Simple (and common) case of single ribbon child
    if(GetChildren().GetCount() == 1)
    {
        wxWindow* child = GetChildren().Item(0)->GetData();
        wxRibbonControl* ribbon_child = wxDynamicCast(child, wxRibbonControl);
        if(m_art != NULL && ribbon_child != NULL)
        {
            wxMemoryDC dc;
            wxSize child_relative = m_art->GetPanelClientSize(dc, this, relative_to, NULL);
            wxSize smaller = ribbon_child->GetNextSmallerSize(direction, child_relative);
            if(smaller == child_relative)
            {
                if(CanAutoMinimise())
                {
                    wxSize minimised = m_minimised_size;
                    switch(direction)
                    {
                    case wxHORIZONTAL:
                        minimised.SetHeight(relative_to.GetHeight());
                        break;
                    case wxVERTICAL:
                        minimised.SetWidth(relative_to.GetWidth());
                        break;
                    default:
                        break;
                    }
                    return minimised;
                }
                else
                {
                    return relative_to;
                }
            }
            else
            {
                return m_art->GetPanelSize(dc, this, smaller, NULL);
            }
        }
    }

    // Fallback: Decrease by 20% (or minimum size, whichever larger)
    wxSize current(relative_to);
    wxSize minimum(GetMinSize());
    if(direction & wxHORIZONTAL)
    {
        current.x = (current.x * 4) / 5;
        if(current.x < minimum.x)
        {
            current.x = minimum.x;
        }
    }
    if(direction & wxVERTICAL)
    {
        current.y = (current.y * 4) / 5;
        if(current.y < minimum.y)
        {
            current.y = minimum.y;
        }
    }
    return current;
}

wxSize wxRibbonPanel::DoGetNextLargerSize(wxOrientation direction,
                                        wxSize relative_to) const
{
    if(m_expanded_panel != NULL)
    {
        // Next size depends upon children, who are currently in the
        // expanded panel
        return m_expanded_panel->DoGetNextLargerSize(direction, relative_to);
    }

    if(IsMinimised(relative_to))
    {
        wxSize current = relative_to;
        wxSize min_size = GetMinNotMinimisedSize();
        switch(direction)
        {
        case wxHORIZONTAL:
            if(min_size.x > current.x && min_size.y == current.y)
                return min_size;
            break;
        case wxVERTICAL:
            if(min_size.x == current.x && min_size.y > current.y)
                return min_size;
            break;
        case wxBOTH:
            if(min_size.x > current.x && min_size.y > current.y)
                return min_size;
            break;
        default:
            break;
        }
    }

    // TODO: Check for, and delegate to, a sizer

    // Simple (and common) case of single ribbon child
    if(GetChildren().GetCount() == 1)
    {
        wxWindow* child = GetChildren().Item(0)->GetData();
        wxRibbonControl* ribbon_child = wxDynamicCast(child, wxRibbonControl);
        if(ribbon_child != NULL)
        {
            wxMemoryDC dc;
            wxSize child_relative = m_art->GetPanelClientSize(dc, this, relative_to, NULL);
            wxSize larger = ribbon_child->GetNextLargerSize(direction, child_relative);
            if(larger == child_relative)
            {
                return relative_to;
            }
            else
            {
                wxMemoryDC dc;
                return m_art->GetPanelSize(dc, this, larger, NULL);
            }
        }
    }

    // Fallback: Increase by 25% (equal to a prior or subsequent 20% decrease)
    // Note that due to rounding errors, this increase may not exactly equal a
    // matching decrease - an ideal solution would not have these errors, but
    // avoiding them is non-trivial unless an increase is by 100% rather than
    // a fractional amount. This would then be non-ideal as the resizes happen
    // at very large intervals.
    wxSize current(relative_to);
    if(direction & wxHORIZONTAL)
    {
        current.x = (current.x * 5 + 3) / 4;
    }
    if(direction & wxVERTICAL)
    {
        current.y = (current.y * 5 + 3) / 4;
    }
    return current;
}

bool wxRibbonPanel::CanAutoMinimise() const
{
    return (m_flags & wxRIBBON_PANEL_NO_AUTO_MINIMISE) == 0
        && m_minimised_size.IsFullySpecified();
}

wxSize wxRibbonPanel::GetMinSize() const
{
    if(m_expanded_panel != NULL)
    {
        // Minimum size depends upon children, who are currently in the
        // expanded panel
        return m_expanded_panel->GetMinSize();
    }

    if(CanAutoMinimise())
    {
        return m_minimised_size;
    }
    else
    {
        return GetMinNotMinimisedSize();
    }
}

wxSize wxRibbonPanel::GetMinNotMinimisedSize() const
{
    // TODO: Ask sizer

    // Common case of no sizer and single child taking up the entire panel
    if(GetChildren().GetCount() == 1)
    {
        wxWindow* child = GetChildren().Item(0)->GetData();
        wxMemoryDC dc;
        return m_art->GetPanelSize(dc, this, child->GetMinSize(), NULL);
    }

    return wxRibbonControl::GetMinSize();
}

wxSize wxRibbonPanel::DoGetBestSize() const
{
    // TODO: Ask sizer

    // Common case of no sizer and single child taking up the entire panel
    if(GetChildren().GetCount() == 1)
    {
        wxWindow* child = GetChildren().Item(0)->GetData();
        wxMemoryDC dc;
        return m_art->GetPanelSize(dc, this, child->GetBestSize(), NULL);
    }

    return wxRibbonControl::DoGetBestSize();
}

bool wxRibbonPanel::Realize()
{
    bool status = true;

    for (wxWindowList::compatibility_iterator node = GetChildren().GetFirst();
                  node;
                  node = node->GetNext())
    {
        wxRibbonControl* child = wxDynamicCast(node->GetData(), wxRibbonControl);
        if(child == NULL)
        {
            continue;
        }
        if(!child->Realize())
        {
            status = false;
        }
    }

    wxSize minimum_children_size(0, 0);
    // TODO: Ask sizer if there is one
    if(GetChildren().GetCount() == 1)
    {
        minimum_children_size = GetChildren().GetFirst()->GetData()->GetMinSize();
    }

    if(m_art != NULL)
    {
        wxMemoryDC temp_dc;

        m_smallest_unminimised_size =
            m_art->GetPanelSize(temp_dc, this, minimum_children_size, NULL);

        wxSize bitmap_size;
        wxSize panel_min_size = GetMinNotMinimisedSize();
        m_minimised_size = m_art->GetMinimisedPanelMinimumSize(temp_dc, this,
            &bitmap_size, &m_preferred_expand_direction);

		wxSize s = wxSize(m_minimised_icon.GetWidth(), m_minimised_icon.GetHeight());

		if(m_minimised_icon.IsOk() && s != bitmap_size)
        {
            wxImage img(m_minimised_icon.ConvertToImage());
            img.Rescale(bitmap_size.GetWidth(), bitmap_size.GetHeight(), wxIMAGE_QUALITY_HIGH);
            m_minimised_icon_resized = wxBitmap(img);
        }
        else
        {
            m_minimised_icon_resized = m_minimised_icon;
        }
        if(m_minimised_size.x > panel_min_size.x &&
            m_minimised_size.y > panel_min_size.y)
        {
            // No point in having a minimised size which is larger than the
            // minimum size which the children can go to.
            m_minimised_size = wxSize(-1, -1);
        }
        else
        {
            if(m_art->GetFlags() & wxRIBBON_BAR_FLOW_VERTICAL)
            {
                m_minimised_size.x = panel_min_size.x;
            }
            else
            {
                m_minimised_size.y = panel_min_size.y;
            }
        }
    }
    else
    {
        m_minimised_size = wxSize(-1, -1);
    }

    return Layout() && status;
}

bool wxRibbonPanel::Layout()
{
    if(IsMinimised())
    {
        // Children are all invisible when minimised
        return true;
    }

    // TODO: Delegate to a sizer

    // Common case of no sizer and single child taking up the entire panel
    if(GetChildren().GetCount() == 1)
    {
        wxWindow* child = GetChildren().Item(0)->GetData();
        wxPoint position;
        wxMemoryDC dc;
        wxSize size = m_art->GetPanelClientSize(dc, this, GetSize(), &position);
        child->SetSize(position.x, position.y, size.GetWidth(), size.GetHeight());
    }
    return true;
}

void wxRibbonPanel::OnMouseClick(wxMouseEvent& WXUNUSED(evt))
{
    if(IsMinimised())
    {
        if(m_expanded_panel != NULL)
        {
            HideExpanded();
        }
        else
        {
            ShowExpanded();
        }
    }
}

wxRibbonPanel* wxRibbonPanel::GetExpandedDummy()
{
    return m_expanded_dummy;
}

wxRibbonPanel* wxRibbonPanel::GetExpandedPanel()
{
    return m_expanded_panel;
}

bool wxRibbonPanel::ShowExpanded()
{
    if(!IsMinimised())
    {
        return false;
    }
    if(m_expanded_dummy != NULL || m_expanded_panel != NULL)
    {
        return false;
    }

    wxSize size = GetBestSize();
    wxPoint pos = GetExpandedPosition(wxRect(GetScreenPosition(), GetSize()),
        size, m_preferred_expand_direction).GetTopLeft();

    // Need a top-level frame to contain the expanded panel
    wxFrame *container = new wxFrame(NULL, wxID_ANY, GetLabel(),
        pos, size, wxFRAME_NO_TASKBAR | wxBORDER_NONE);

    m_expanded_panel = new wxRibbonPanel(container, wxID_ANY,
        GetLabel(), m_minimised_icon, wxPoint(0, 0), size, m_flags);

    m_expanded_panel->SetArtProvider(m_art);
    m_expanded_panel->m_expanded_dummy = this;

    // Move all children to the new panel.
    // Conceptually it might be simpler to reparent this entire panel to the
    // container and create a new panel to sit in its place while expanded.
    // This approach has a problem though - when the panel is reinserted into
    // its original parent, it'll be at a different position in the child list
    // and thus assume a new position.
    // NB: Children iterators not used as behaviour is not well defined
    // when iterating over a container which is being emptied
    while(!GetChildren().IsEmpty())
    {
        wxWindow *child = GetChildren().GetFirst()->GetData();
        child->Reparent(m_expanded_panel);
        child->Show();
    }

    // TODO: Move sizer to new panel

    m_expanded_panel->Realize();
    Refresh();
    container->Show();
    m_expanded_panel->SetFocus();

    return true;
}

bool wxRibbonPanel::ShouldSendEventToDummy(wxEvent& evt)
{
    // For an expanded panel, filter events between being sent up to the
    // floating top level window or to the dummy panel sitting in the ribbon
    // bar.

    // Child focus events should not be redirected, as the child would not be a
    // child of the window the event is redirected to. All other command events
    // seem to be suitable for redirecting.
    return evt.IsCommandEvent() && evt.GetEventType() != wxEVT_CHILD_FOCUS;
}

bool wxRibbonPanel::TryAfter(wxEvent& evt)
{
    if(m_expanded_dummy && ShouldSendEventToDummy(evt))
    {
        wxPropagateOnce propagateOnce(evt);
        return m_expanded_dummy->GetEventHandler()->ProcessEvent(evt);
    }
    else
    {
        return false; //wxRibbonControl::TryAfter(evt);
    }
}

static bool IsAncestorOf(wxWindow *ancestor, wxWindow *window)
{
    while(window != NULL)
    {
        wxWindow *parent = window->GetParent();
        if(parent == ancestor)
            return true;
        else
            window = parent;
    }
    return false;
}

void wxRibbonPanel::OnKillFocus(wxFocusEvent& evt)
{
    if(m_expanded_dummy)
    {
        wxWindow *receiver = evt.GetWindow();
        if(IsAncestorOf(this, receiver))
        {
            m_child_with_focus = receiver;
            receiver->Connect(wxEVT_KILL_FOCUS,
                wxFocusEventHandler(wxRibbonPanel::OnChildKillFocus),
                NULL, this);
        }
        else if(receiver == NULL || receiver != m_expanded_dummy)
        {
            HideExpanded();
        }
    }
}

void wxRibbonPanel::OnChildKillFocus(wxFocusEvent& evt)
{
    if(m_child_with_focus == NULL)
        return; // Should never happen, but a check can't hurt

    m_child_with_focus->Disconnect(wxEVT_KILL_FOCUS,
      wxFocusEventHandler(wxRibbonPanel::OnChildKillFocus), NULL, this);
    m_child_with_focus = NULL;

    wxWindow *receiver = evt.GetWindow();
    if(receiver == this || IsAncestorOf(this, receiver))
    {
        m_child_with_focus = receiver;
        receiver->Connect(wxEVT_KILL_FOCUS,
            wxFocusEventHandler(wxRibbonPanel::OnChildKillFocus), NULL, this);
        evt.Skip();
    }
    else if(receiver == NULL || receiver != m_expanded_dummy)
    {
        HideExpanded();
        // Do not skip event, as the panel has been de-expanded, causing the
        // child with focus to be reparented (and hidden). If the event
        // continues propogation then bad things happen.
    }
    else
    {
        evt.Skip();
    }
}

bool wxRibbonPanel::HideExpanded()
{
    if(m_expanded_dummy == NULL)
    {
        if(m_expanded_panel)
        {
            return m_expanded_panel->HideExpanded();
        }
        else
        {
            return false;
        }
    }

    // Move children back to original panel
    // NB: Children iterators not used as behaviour is not well defined
    // when iterating over a container which is being emptied
    while(!GetChildren().IsEmpty())
    {
        wxWindow *child = GetChildren().GetFirst()->GetData();
        child->Reparent(m_expanded_dummy);
        child->Hide();
    }

    // TODO: Move sizer back

    m_expanded_dummy->m_expanded_panel = NULL;
    m_expanded_dummy->Realize();
    m_expanded_dummy->Refresh();
    wxWindow *parent = GetParent();
    Destroy();
    parent->Destroy();

    return true;
}

wxRect wxRibbonPanel::GetExpandedPosition(wxRect panel,
                                          wxSize expanded_size,
                                          wxDirection direction)
{
    // Strategy:
    // 1) Determine primary position based on requested direction
    // 2) Move the position so that it sits entirely within a display
    //    (for single monitor systems, this moves it into the display region,
    //     but for multiple monitors, it does so without splitting it over
    //     more than one display)
    // 2.1) Move in the primary axis
    // 2.2) Move in the secondary axis

    wxPoint pos;
    bool primary_x = false;
    int secondary_x = 0;
    int secondary_y = 0;
    switch(direction)
    {
    case wxNORTH:
        pos.x = panel.GetX() + (panel.GetWidth() - expanded_size.GetWidth()) / 2;
        pos.y = panel.GetY() - expanded_size.GetHeight();
        primary_x = true;
        secondary_y = 1;
        break;
    case wxEAST:
        pos.x = panel.GetRight();
        pos.y = panel.GetY() + (panel.GetHeight() - expanded_size.GetHeight()) / 2;
        secondary_x = -1;
        break;
    case wxSOUTH:
        pos.x = panel.GetX() + (panel.GetWidth() - expanded_size.GetWidth()) / 2;
        pos.y = panel.GetBottom();
        primary_x = true;
        secondary_y = -1;
        break;
    case wxWEST:
    default:
        pos.x = panel.GetX() - expanded_size.GetWidth();
        pos.y = panel.GetY() + (panel.GetHeight() - expanded_size.GetHeight()) / 2;
        secondary_x = 1;
        break;
    }
    wxRect expanded(pos, expanded_size);

    wxRect best(expanded);
    int best_distance = INT_MAX;

    const unsigned display_n = wxDisplay::GetCount();
    unsigned display_i;
    for(display_i = 0; display_i < display_n; ++display_i)
    {
        wxRect display = wxDisplay(display_i).GetGeometry();

        if(display.Contains(expanded))
        {
            return expanded;
        }
        else if(display.Intersects(expanded))
        {
            wxRect new_rect(expanded);
            int distance = 0;

            if(primary_x)
            {
                if(expanded.GetRight() > display.GetRight())
                {
                    distance = expanded.GetRight() - display.GetRight();
                    new_rect.x -= distance;
                }
                else if(expanded.GetLeft() < display.GetLeft())
                {
                    distance = display.GetLeft() - expanded.GetLeft();
                    new_rect.x += distance;
                }
            }
            else
            {
                if(expanded.GetBottom() > display.GetBottom())
                {
                    distance = expanded.GetBottom() - display.GetBottom();
                    new_rect.y -= distance;
                }
                else if(expanded.GetTop() < display.GetTop())
                {
                    distance = display.GetTop() - expanded.GetTop();
                    new_rect.y += distance;
                }
            }
            if(!display.Contains(new_rect))
            {
                // Tried moving in primary axis, but failed.
                // Hence try moving in the secondary axis.
                int dx = secondary_x * (panel.GetWidth() + expanded_size.GetWidth());
                int dy = secondary_y * (panel.GetHeight() + expanded_size.GetHeight());
                new_rect.x += dx;
                new_rect.y += dy;

                // Squaring makes secondary moves more expensive (and also
                // prevents a negative cost)
                distance += dx * dx + dy * dy;
            }
            if(display.Contains(new_rect) && distance < best_distance)
            {
                best = new_rect;
                best_distance = distance;
            }
        }
    }

    return best;
}

#endif // wxUSE_RIBBON

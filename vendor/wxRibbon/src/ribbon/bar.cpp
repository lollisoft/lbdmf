///////////////////////////////////////////////////////////////////////////////
// Name:        src/ribbon/bar.cpp
// Purpose:     Top-level component of the ribbon-bar-style interface
// Author:      Peter Cawley
// Modified by:
// Created:     2009-05-23
// RCS-ID:      $Id: bar.cpp,v 1.2.2.1 2025/04/05 16:16:41 lothar Exp $
// Copyright:   (C) Peter Cawley
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wx/ribbon/bar.h"

#if wxUSE_RIBBON

#include "wx/ribbon/art.h"
#include "wx/dcbuffer.h"

#ifndef WX_PRECOMP
#endif

#ifdef __WXMSW__
#include "wx/msw/private.h"
#endif

#include "wx/arrimpl.cpp"

WX_DEFINE_USER_EXPORTED_OBJARRAY(wxRibbonPageTabInfoArray);


wxDEFINE_EVENT(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_PAGE_CHANGED, wxRibbonBarEvent);
wxDEFINE_EVENT(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_PAGE_CHANGING, wxRibbonBarEvent);
wxDEFINE_EVENT(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_TAB_MIDDLE_DOWN, wxRibbonBarEvent);
wxDEFINE_EVENT(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_TAB_MIDDLE_UP, wxRibbonBarEvent);
wxDEFINE_EVENT(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_TAB_RIGHT_DOWN, wxRibbonBarEvent);
wxDEFINE_EVENT(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBAR_TAB_RIGHT_UP, wxRibbonBarEvent);

IMPLEMENT_CLASS(wxRibbonBar, wxRibbonControl)
IMPLEMENT_DYNAMIC_CLASS(wxRibbonBarEvent, wxNotifyEvent)

BEGIN_EVENT_TABLE(wxRibbonBar, wxRibbonControl)
  EVT_ERASE_BACKGROUND(wxRibbonBar::OnEraseBackground)
  EVT_LEAVE_WINDOW(wxRibbonBar::OnMouseLeave)
  EVT_LEFT_DOWN(wxRibbonBar::OnMouseLeftDown)
  EVT_LEFT_UP(wxRibbonBar::OnMouseLeftUp)
  EVT_MIDDLE_DOWN(wxRibbonBar::OnMouseMiddleDown)
  EVT_MIDDLE_UP(wxRibbonBar::OnMouseMiddleUp)
  EVT_MOTION(wxRibbonBar::OnMouseMove)
  EVT_PAINT(wxRibbonBar::OnPaint)
  EVT_RIGHT_DOWN(wxRibbonBar::OnMouseRightDown)
  EVT_RIGHT_UP(wxRibbonBar::OnMouseRightUp)
  EVT_SIZE(wxRibbonBar::OnSize)
END_EVENT_TABLE()

void wxRibbonBar::AddPage(wxRibbonPage *page)
{
    wxRibbonPageTabInfo info;

    info.page = page;
    info.active = false;
    info.hovered = false;
    // info.rect not set (intentional)

    wxMemoryDC dcTemp;
    wxString label = wxEmptyString;
    if(m_flags & wxRIBBON_BAR_SHOW_PAGE_LABELS)
        label = page->GetLabel();
    wxBitmap icon = wxNullBitmap;
    if(m_flags & wxRIBBON_BAR_SHOW_PAGE_ICONS)
        icon = page->GetIcon();
    m_art->GetBarTabWidth(dcTemp, this, label, icon,
                          &info.ideal_width,
                          &info.small_begin_need_separator_width,
                          &info.small_must_have_separator_width,
                          &info.minimum_width);

    if(m_pages.IsEmpty())
    {
        m_tabs_total_width_ideal = info.ideal_width;
        m_tabs_total_width_minimum = info.minimum_width;
    }
    else
    {
        int sep = m_art->GetMetric(wxRIBBON_ART_TAB_SEPARATION_SIZE);
        m_tabs_total_width_ideal += sep + info.ideal_width;
        m_tabs_total_width_minimum += sep + info.minimum_width;
    }
    m_pages.Add(info);

    page->Hide(); // Most likely case is that this new page is not the active tab
    page->SetArtProvider(m_art);

    if(m_pages.GetCount() == 1)
    {
        SetActivePage((size_t)0);
    }
}

bool wxRibbonBar::DismissExpandedPanel()
{
    if(m_current_page == -1)
        return false;
    return m_pages.Item(m_current_page).page->DismissExpandedPanel();
}

void wxRibbonBar::SetWindowStyleFlag(long style)
{
    m_flags = style;
    if(m_art)
        m_art->SetFlags(style);
}

long wxRibbonBar::GetWindowStyleFlag() const
{
    return m_flags;
}

bool wxRibbonBar::Realize()
{
    bool status = true;

    wxMemoryDC dcTemp;
    int sep = m_art->GetMetric(wxRIBBON_ART_TAB_SEPARATION_SIZE);
    size_t numtabs = m_pages.GetCount();
    size_t i;
    for(i = 0; i < numtabs; ++i)
    {
        wxRibbonPageTabInfo& info = m_pages.Item(i);
        RepositionPage(info.page);
        if(!info.page->Realize())
        {
            status = false;
        }
        wxString label = wxEmptyString;
        if(m_flags & wxRIBBON_BAR_SHOW_PAGE_LABELS)
            label = info.page->GetLabel();
        wxBitmap icon = wxNullBitmap;
        if(m_flags & wxRIBBON_BAR_SHOW_PAGE_ICONS)
            icon = info.page->GetIcon();
        m_art->GetBarTabWidth(dcTemp, this, label, icon,
                              &info.ideal_width,
                              &info.small_begin_need_separator_width,
                              &info.small_must_have_separator_width,
                              &info.minimum_width);

        if(i == 0)
        {
            m_tabs_total_width_ideal = info.ideal_width;
            m_tabs_total_width_minimum = info.minimum_width;
        }
        else
        {
            m_tabs_total_width_ideal += sep + info.ideal_width;
            m_tabs_total_width_minimum += sep + info.minimum_width;
        }
    }
    m_tab_height = m_art->GetTabCtrlHeight(dcTemp, this, m_pages);

    RecalculateMinSize();
    RecalculateTabSizes();
    Refresh();

    return status;
}

void wxRibbonBar::OnMouseMove(wxMouseEvent& evt)
{
    int x = evt.GetX();
    int y = evt.GetY();
    int hovered_page = -1;
    bool refresh_tabs = false;
    if(y < m_tab_height)
    {
        // It is quite likely that the mouse moved a small amount and is still over the same tab
        if(m_current_hovered_page != -1 && m_pages.Item((size_t)m_current_hovered_page).rect.Contains(x, y))
        {
            hovered_page = m_current_hovered_page;
            // But be careful, if tabs can be scrolled, then parts of the tab rect may not be valid
            if(m_tab_scroll_buttons_shown)
            {
                if(x >= m_tab_scroll_right_button_rect.GetX() || x < m_tab_scroll_left_button_rect.GetRight())
                {
                    hovered_page = -1;
                }
            }
        }
        else
        {
            HitTestTabs(evt.GetPosition(), &hovered_page);
        }
    }
    if(hovered_page != m_current_hovered_page)
    {
        if(m_current_hovered_page != -1)
        {
            m_pages.Item((int)m_current_hovered_page).hovered = false;
        }
        m_current_hovered_page = hovered_page;
        if(m_current_hovered_page != -1)
        {
            m_pages.Item((int)m_current_hovered_page).hovered = true;
        }
        refresh_tabs = true;
    }
    if(m_tab_scroll_buttons_shown)
    {
#define SET_FLAG(variable, flag) \
    { if(((variable) & (flag)) != (flag)) variable |= (flag), refresh_tabs = true; }
#define UNSET_FLAG(variable, flag) \
    { if((variable) & (flag)) variable &= ~(flag), refresh_tabs = true; }

        if(m_tab_scroll_left_button_rect.Contains(x, y))
            SET_FLAG(m_tab_scroll_left_button_state, wxRIBBON_SCROLL_BTN_HOVERED)
        else
            UNSET_FLAG(m_tab_scroll_left_button_state, wxRIBBON_SCROLL_BTN_HOVERED)

        if(m_tab_scroll_right_button_rect.Contains(x, y))
            SET_FLAG(m_tab_scroll_right_button_state, wxRIBBON_SCROLL_BTN_HOVERED)
        else
            UNSET_FLAG(m_tab_scroll_right_button_state, wxRIBBON_SCROLL_BTN_HOVERED)
#undef SET_FLAG
#undef UNSET_FLAG
    }
    if(refresh_tabs)
    {
        RefreshTabBar();
    }
}

void wxRibbonBar::OnMouseLeave(wxMouseEvent& WXUNUSED(evt))
{
    // The ribbon bar is (usually) at the top of a window, and at least on MSW, the mouse
    // can leave the window quickly and leave a tab in the hovered state.
    bool refresh_tabs = false;
    if(m_current_hovered_page != -1)
    {
        m_pages.Item((int)m_current_hovered_page).hovered = false;
        m_current_hovered_page = -1;
        refresh_tabs = true;
    }
    if(m_tab_scroll_left_button_state & wxRIBBON_SCROLL_BTN_HOVERED)
    {
        m_tab_scroll_left_button_state &= ~wxRIBBON_SCROLL_BTN_HOVERED;
        refresh_tabs = true;
    }
    if(m_tab_scroll_right_button_state & wxRIBBON_SCROLL_BTN_HOVERED)
    {
        m_tab_scroll_right_button_state &= ~wxRIBBON_SCROLL_BTN_HOVERED;
        refresh_tabs = true;
    }
    if(refresh_tabs)
    {
        RefreshTabBar();
    }
}

wxRibbonPage* wxRibbonBar::GetPage(int n)
{
    if(n < 0 || (size_t)n >= m_pages.GetCount())
        return 0;
    return m_pages.Item(n).page;
}

bool wxRibbonBar::SetActivePage(size_t page)
{
    if(m_current_page == (int)page)
    {
        return true;
    }

    if(page >= m_pages.GetCount())
    {
        return false;
    }

    if(m_current_page != -1)
    {
        m_pages.Item((size_t)m_current_page).active = false;
        m_pages.Item((size_t)m_current_page).page->Hide();
    }
    m_current_page = (int)page;
    m_pages.Item(page).active = true;
    {
        wxRibbonPage* wnd = m_pages.Item(page).page;
        RepositionPage(wnd);
        wnd->Layout();
        wnd->Show();
    }
    Refresh();

    return true;
}

bool wxRibbonBar::SetActivePage(wxRibbonPage* page)
{
    size_t numpages = m_pages.GetCount();
    size_t i;
    for(i = 0; i < numpages; ++i)
    {
        if(m_pages.Item(i).page == page)
        {
            return SetActivePage(i);
        }
    }
    return false;
}

int wxRibbonBar::GetActivePage() const
{
    return m_current_page;
}

void wxRibbonBar::SetTabCtrlMargins(int left, int right)
{
    m_tab_margin_left = left;
    m_tab_margin_right = right;

    RecalculateTabSizes();
}

static int OrderPageTabInfoBySmallWidthAsc(wxRibbonPageTabInfo **first, wxRibbonPageTabInfo **second)
{
    return (**first).small_must_have_separator_width - (**second).small_must_have_separator_width;
}

void wxRibbonBar::RecalculateTabSizes()
{
    size_t numtabs = m_pages.GetCount();

    if(numtabs == 0)
        return;

    int width = GetSize().GetWidth() - m_tab_margin_left - m_tab_margin_right;
    int tabsep = m_art->GetMetric(wxRIBBON_ART_TAB_SEPARATION_SIZE);
    int x = m_tab_margin_left;
    const int y = 0;

    if(width >= m_tabs_total_width_ideal)
    {
        // Simple case: everything at ideal width
        size_t i;
        for(i = 0; i < numtabs; ++i)
        {
            wxRibbonPageTabInfo& info = m_pages.Item(i);
            info.rect.x = x;
            info.rect.y = y;
            info.rect.width = info.ideal_width;
            info.rect.height = m_tab_height;
            x += info.rect.width + tabsep;
        }
        m_tab_scroll_buttons_shown = false;
        m_tab_scroll_left_button_rect.SetWidth(0);
        m_tab_scroll_right_button_rect.SetWidth(0);
    }
    else if(width < m_tabs_total_width_minimum)
    {
        // Simple case: everything minimum with scrollbar
        size_t i;
        for(i = 0; i < numtabs; ++i)
        {
            wxRibbonPageTabInfo& info = m_pages.Item(i);
            info.rect.x = x;
            info.rect.y = y;
            info.rect.width = info.minimum_width;
            info.rect.height = m_tab_height;
            x += info.rect.width + tabsep;
        }
        if(!m_tab_scroll_buttons_shown)
        {
            m_tab_scroll_left_button_state = wxRIBBON_SCROLL_BTN_NORMAL;
            m_tab_scroll_right_button_state = wxRIBBON_SCROLL_BTN_NORMAL;
            m_tab_scroll_buttons_shown = true;
        }
        {
            wxMemoryDC temp_dc;
            m_tab_scroll_left_button_rect.SetWidth(m_art->GetScrollButtonMinimumSize(temp_dc, this, wxRIBBON_SCROLL_BTN_LEFT | wxRIBBON_SCROLL_BTN_NORMAL | wxRIBBON_SCROLL_BTN_FOR_TABS).GetWidth());
            m_tab_scroll_left_button_rect.SetHeight(m_tab_height);
            m_tab_scroll_left_button_rect.SetX(m_tab_margin_left);
            m_tab_scroll_left_button_rect.SetY(0);
            m_tab_scroll_right_button_rect.SetWidth(m_art->GetScrollButtonMinimumSize(temp_dc, this, wxRIBBON_SCROLL_BTN_RIGHT | wxRIBBON_SCROLL_BTN_NORMAL | wxRIBBON_SCROLL_BTN_FOR_TABS).GetWidth());
            m_tab_scroll_right_button_rect.SetHeight(m_tab_height);
            m_tab_scroll_right_button_rect.SetX(GetClientSize().GetWidth() - m_tab_margin_right - m_tab_scroll_right_button_rect.GetWidth());
            m_tab_scroll_right_button_rect.SetY(0);
        }
        if(m_tab_scroll_amount == 0)
        {
            m_tab_scroll_left_button_rect.SetWidth(0);
        }
        else if(m_tab_scroll_amount + width >= m_tabs_total_width_minimum)
        {
            m_tab_scroll_amount = m_tabs_total_width_minimum - width;
            m_tab_scroll_right_button_rect.SetX(m_tab_scroll_right_button_rect.GetX() + m_tab_scroll_right_button_rect.GetWidth());
            m_tab_scroll_right_button_rect.SetWidth(0);
        }
        for(i = 0; i < numtabs; ++i)
        {
            wxRibbonPageTabInfo& info = m_pages.Item(i);
            info.rect.x -= m_tab_scroll_amount;
        }
    }
    else
    {
        m_tab_scroll_buttons_shown = false;
        m_tab_scroll_left_button_rect.SetWidth(0);
        m_tab_scroll_right_button_rect.SetWidth(0);
        // Complex case: everything sized such that: minimum <= width < ideal
        /*
           Strategy:
             1) Uniformly reduce all tab widths from ideal to small_must_have_separator_width
             2) Reduce the largest tab by 1 pixel, repeating until all tabs are same width (or at minimum)
             3) Uniformly reduce all tabs down to their minimum width
        */
        int smallest_tab_width = INT_MAX;
        int total_small_width = tabsep * (numtabs - 1);
        size_t i;
        for(i = 0; i < numtabs; ++i)
        {
            wxRibbonPageTabInfo& info = m_pages.Item(i);
            if(info.small_must_have_separator_width < smallest_tab_width)
            {
                smallest_tab_width = info.small_must_have_separator_width;
            }
            total_small_width += info.small_must_have_separator_width;
        }
        if(width >= total_small_width)
        {
            // Do (1)
            int total_delta = m_tabs_total_width_ideal - total_small_width;
            total_small_width -= tabsep * (numtabs - 1);
            width -= tabsep * (numtabs - 1);
            for(i = 0; i < numtabs; ++i)
            {
                wxRibbonPageTabInfo& info = m_pages.Item(i);
                int delta = info.ideal_width - info.small_must_have_separator_width;
                info.rect.x = x;
                info.rect.y = y;
                info.rect.width = info.small_must_have_separator_width + delta * (width - total_small_width) / total_delta;
                info.rect.height = m_tab_height;

                x += info.rect.width + tabsep;
                total_delta -= delta;
                total_small_width -= info.small_must_have_separator_width;
                width -= info.rect.width;
            }
        }
        else
        {
            total_small_width = tabsep * (numtabs - 1);
            for(i = 0; i < numtabs; ++i)
            {
                wxRibbonPageTabInfo& info = m_pages.Item(i);
                if(info.minimum_width < smallest_tab_width)
                {
                    total_small_width += smallest_tab_width;
                }
                else
                {
                    total_small_width += info.minimum_width;
                }
            }
            if(width >= total_small_width)
            {
                // Do (2)
                wxRibbonPageTabInfoArray sorted_pages;
                for(i = 0; i < numtabs; ++i)
                {
                    // Sneaky obj array trickery to not copy the tab descriptors
                    sorted_pages.Add(&m_pages.Item(i));
                }
                sorted_pages.Sort(OrderPageTabInfoBySmallWidthAsc);
                width -= tabsep * (numtabs - 1);
                for(i = 0; i < numtabs; ++i)
                {
                    wxRibbonPageTabInfo& info = sorted_pages.Item(i);
                    if(info.small_must_have_separator_width * (int)(numtabs - i) <= width)
                    {
                        info.rect.width = info.small_must_have_separator_width;;
                    }
                    else
                    {
                        info.rect.width = width / (numtabs - i);
                    }
                    width -= info.rect.width;
                }
                for(i = 0; i < numtabs; ++i)
                {
                    wxRibbonPageTabInfo& info = m_pages.Item(i);
                    info.rect.x = x;
                    info.rect.y = y;
                    info.rect.height = m_tab_height;
                    x += info.rect.width + tabsep;
                    sorted_pages.Detach(numtabs - (i + 1));
                }
            }
            else
            {
                // Do (3)
                total_small_width = (smallest_tab_width + tabsep) * numtabs - tabsep;
                int total_delta = total_small_width - m_tabs_total_width_minimum;
                total_small_width = m_tabs_total_width_minimum - tabsep * (numtabs - 1);
                width -= tabsep * (numtabs - 1);
                for(i = 0; i < numtabs; ++i)
                {
                    wxRibbonPageTabInfo& info = m_pages.Item(i);
                    int delta = smallest_tab_width - info.minimum_width;
                    info.rect.x = x;
                    info.rect.y = y;
                    info.rect.width = info.minimum_width + delta * (width - total_small_width) / total_delta;
                    info.rect.height = m_tab_height;

                    x += info.rect.width + tabsep;
                    total_delta -= delta;
                    total_small_width -= info.minimum_width;
                    width -= info.rect.width;
                }
            }
        }
    }
}

wxRibbonBar::wxRibbonBar()
{
    m_flags = 0;
    m_tabs_total_width_ideal = 0;
    m_tabs_total_width_minimum = 0;
    m_tab_margin_left = 0;
    m_tab_margin_right = 0;
    m_tab_height = 0;
    m_tab_scroll_amount = 0;
    m_current_page = -1;
    m_current_hovered_page = -1;
    m_tab_scroll_left_button_state = wxRIBBON_SCROLL_BTN_NORMAL;
    m_tab_scroll_right_button_state = wxRIBBON_SCROLL_BTN_NORMAL;
    m_tab_scroll_buttons_shown = false;
}

wxRibbonBar::wxRibbonBar(wxWindow* parent,
                         wxWindowID id,
                         const wxPoint& pos,
                         const wxSize& size,
                         long style)
    : wxRibbonControl(parent, id, pos, size, wxBORDER_NONE)
{
    CommonInit(style);
}

wxRibbonBar::~wxRibbonBar()
{
    SetArtProvider(NULL);
}

bool wxRibbonBar::Create(wxWindow* parent,
                wxWindowID id,
                const wxPoint& pos,
                const wxSize& size,
                long style)
{
    if(!wxRibbonControl::Create(parent, id, pos, size, wxBORDER_NONE))
        return false;

    CommonInit(style);

    return true;
}

void wxRibbonBar::CommonInit(long style)
{
    SetName(wxT("wxRibbonBar"));

    m_flags = style;
    m_tabs_total_width_ideal = 0;
    m_tabs_total_width_minimum = 0;
    m_tab_margin_left = 50;
    m_tab_margin_right = 20;
    m_tab_height = 20; // initial guess
    m_tab_scroll_amount = 0;
    m_current_page = -1;
    m_current_hovered_page = -1;
    m_tab_scroll_left_button_state = wxRIBBON_SCROLL_BTN_NORMAL;
    m_tab_scroll_right_button_state = wxRIBBON_SCROLL_BTN_NORMAL;
    m_tab_scroll_buttons_shown = false;

    if(m_art == NULL)
    {
        SetArtProvider(new wxRibbonDefaultArtProvider);
    }
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

void wxRibbonBar::SetArtProvider(wxRibbonArtProvider* art)
{
    wxRibbonArtProvider *old = m_art;
    m_art = art;

    if(art)
    {
        art->SetFlags(m_flags);
    }
    size_t numpages = m_pages.GetCount();
    size_t i;
    for(i = 0; i < numpages; ++i)
    {
        wxRibbonPage *page = m_pages.Item(i).page;
        if(page->GetArtProvider() != art)
        {
            page->SetArtProvider(art);
        }
    }

    delete old;
}

void wxRibbonBar::OnPaint(wxPaintEvent& WXUNUSED(evt))
{
    wxAutoBufferedPaintDC dc(this);

    if(GetUpdateRegion().Contains(0, 0, GetClientSize().GetWidth(), m_tab_height) == wxOutRegion)
    {
        // Nothing to do in the tab area, and the page area is handled by the active page
        return;
    }

    DoEraseBackground(dc);

    size_t numtabs = m_pages.GetCount();
    double sep_visibility = 0.0;
    bool draw_sep = false;
    wxRect tabs_rect(m_tab_margin_left, 0, GetClientSize().GetWidth() - m_tab_margin_left - m_tab_margin_right, m_tab_height);
    if(m_tab_scroll_buttons_shown)
    {
        tabs_rect.x += m_tab_scroll_left_button_rect.GetWidth();
        tabs_rect.width -= m_tab_scroll_left_button_rect.GetWidth() + m_tab_scroll_right_button_rect.GetWidth();
    }
    size_t i;
    for(i = 0; i < numtabs; ++i)
    {
        wxRibbonPageTabInfo& info = m_pages.Item(i);

        dc.DestroyClippingRegion();
        if(m_tab_scroll_buttons_shown)
        {
            if(!tabs_rect.Intersects(info.rect))
                continue;
            dc.SetClippingRegion(tabs_rect);
        }
        dc.SetClippingRegion(info.rect);
        m_art->DrawTab(dc, this, info);

        if(info.rect.width < info.small_begin_need_separator_width)
        {
            draw_sep = true;
            if(info.rect.width < info.small_must_have_separator_width)
            {
                sep_visibility += 1.0;
            }
            else
            {
                sep_visibility += (double)(info.small_begin_need_separator_width - info.rect.width) / (double)(info.small_begin_need_separator_width - info.small_must_have_separator_width);
            }
        }
    }
    if(draw_sep)
    {
        wxRect rect = m_pages.Item(0).rect;
        rect.width = m_art->GetMetric(wxRIBBON_ART_TAB_SEPARATION_SIZE);
        sep_visibility /= (double)numtabs;
        for(i = 0; i < numtabs - 1; ++i)
        {
            wxRibbonPageTabInfo& info = m_pages.Item(i);
            rect.x = info.rect.x + info.rect.width;

            if(m_tab_scroll_buttons_shown && !tabs_rect.Intersects(rect))
            {
                continue;
            }

            dc.DestroyClippingRegion();
            dc.SetClippingRegion(rect);
            m_art->DrawTabSeparator(dc, this, rect, sep_visibility);
        }
    }
    if(m_tab_scroll_buttons_shown)
    {
        dc.DestroyClippingRegion();
        if(m_tab_scroll_left_button_rect.GetWidth() != 0)
        {
            m_art->DrawScrollButton(dc, this, m_tab_scroll_left_button_rect, wxRIBBON_SCROLL_BTN_LEFT | m_tab_scroll_left_button_state | wxRIBBON_SCROLL_BTN_FOR_TABS);
        }
        if(m_tab_scroll_right_button_rect.GetWidth() != 0)
        {
            m_art->DrawScrollButton(dc, this, m_tab_scroll_right_button_rect, wxRIBBON_SCROLL_BTN_RIGHT | m_tab_scroll_right_button_state | wxRIBBON_SCROLL_BTN_FOR_TABS);
        }
    }
}

void wxRibbonBar::OnEraseBackground(wxEraseEvent& WXUNUSED(evt))
{
    // Background painting done in main paint handler to reduce screen flicker
}

void wxRibbonBar::DoEraseBackground(wxDC& dc)
{
    wxRect tabs(GetSize());
    tabs.height = m_tab_height;
    m_art->DrawTabCtrlBackground(dc, this, tabs);
}

void wxRibbonBar::OnSize(wxSizeEvent& evt)
{
    RecalculateTabSizes();
    if(m_current_page != -1)
    {
        RepositionPage(m_pages.Item(m_current_page).page);
    }
    RefreshTabBar();

    evt.Skip();
}

void wxRibbonBar::RepositionPage(wxRibbonPage *page)
{
    int w, h;
    GetSize(&w, &h);
    page->SetSizeWithScrollButtonAdjustment(0, m_tab_height, w, h - m_tab_height);
}

wxRibbonPageTabInfo* wxRibbonBar::HitTestTabs(wxPoint position, int* index)
{
    wxRect tabs_rect(m_tab_margin_left, 0, GetClientSize().GetWidth() - m_tab_margin_left - m_tab_margin_right, m_tab_height);
    if(m_tab_scroll_buttons_shown)
    {
        tabs_rect.SetX(tabs_rect.GetX() + m_tab_scroll_left_button_rect.GetWidth());
        tabs_rect.SetWidth(tabs_rect.GetWidth() - m_tab_scroll_left_button_rect.GetWidth() - m_tab_scroll_right_button_rect.GetWidth());
    }
    if(tabs_rect.Contains(position))
    {
        size_t numtabs = m_pages.GetCount();
        size_t i;
        for(i = 0; i < numtabs; ++i)
        {
            wxRibbonPageTabInfo& info = m_pages.Item(i);
            if(info.rect.Contains(position))
            {
                if(index != NULL)
                {
                    *index = (int)i;
                }
                return &info;
            }
        }
    }
    if(index != NULL)
    {
        *index = -1;
    }
    return NULL;
}

#define ProcessWindowEvent(event) \
        m_eventHandler->ProcessEvent(event)


void wxRibbonBar::OnMouseLeftDown(wxMouseEvent& evt)
{
    wxRibbonPageTabInfo *tab = HitTestTabs(evt.GetPosition());
    if(tab && tab != &m_pages.Item(m_current_page))
    {
        wxRibbonBarEvent query(wxEVT_COMMAND_RIBBONBAR_PAGE_CHANGING, GetId(), tab->page);
        query.SetEventObject(this);
        ProcessWindowEvent(query);
        if(query.IsAllowed())
        {
            SetActivePage(query.GetPage());

            wxRibbonBarEvent notification(wxEVT_COMMAND_RIBBONBAR_PAGE_CHANGED, GetId(), m_pages.Item(m_current_page).page);
            notification.SetEventObject(this);
            ProcessWindowEvent(notification);
        }
    }
    else if(tab == NULL)
    {
        if(m_tab_scroll_left_button_rect.Contains(evt.GetPosition()))
        {
            m_tab_scroll_left_button_state |= wxRIBBON_SCROLL_BTN_ACTIVE | wxRIBBON_SCROLL_BTN_HOVERED;
            RefreshTabBar();
        }
        else if(m_tab_scroll_right_button_rect.Contains(evt.GetPosition()))
        {
            m_tab_scroll_right_button_state |= wxRIBBON_SCROLL_BTN_ACTIVE | wxRIBBON_SCROLL_BTN_HOVERED;
            RefreshTabBar();
        }
    }
}

void wxRibbonBar::OnMouseLeftUp(wxMouseEvent& WXUNUSED(evt))
{
    if(!m_tab_scroll_buttons_shown)
    {
        return;
    }

    int amount = 0;
    if(m_tab_scroll_left_button_state & wxRIBBON_SCROLL_BTN_ACTIVE)
    {
        amount = -1;
    }
    else if(m_tab_scroll_right_button_state & wxRIBBON_SCROLL_BTN_ACTIVE)
    {
        amount = 1;
    }
    if(amount != 0)
    {
        m_tab_scroll_left_button_state &= ~wxRIBBON_SCROLL_BTN_ACTIVE;
        m_tab_scroll_right_button_state &= ~wxRIBBON_SCROLL_BTN_ACTIVE;
        ScrollTabBar(amount * 8);
    }
}

void wxRibbonBar::ScrollTabBar(int amount)
{
    bool show_left = true;
    bool show_right = true;
    if(m_tab_scroll_amount + amount <= 0)
    {
        amount = -m_tab_scroll_amount;
        show_left = false;
    }
    else if(m_tab_scroll_amount + amount + (GetClientSize().GetWidth() - m_tab_margin_left - m_tab_margin_right) >= m_tabs_total_width_minimum)
    {
        amount = m_tabs_total_width_minimum - m_tab_scroll_amount - (GetClientSize().GetWidth() - m_tab_margin_left - m_tab_margin_right);
        show_right = false;
    }
    if(amount == 0)
    {
        return;
    }
    m_tab_scroll_amount += amount;
    size_t numtabs = m_pages.GetCount();
    size_t i;
    for(i = 0; i < numtabs; ++i)
    {
        wxRibbonPageTabInfo& info = m_pages.Item(i);
        info.rect.SetX(info.rect.GetX() - amount);
    }
    if(show_right != (m_tab_scroll_right_button_rect.GetWidth() != 0) ||
        show_left != (m_tab_scroll_left_button_rect.GetWidth() != 0))
    {
        wxMemoryDC temp_dc;
        if(show_left)
        {
            m_tab_scroll_left_button_rect.SetWidth(m_art->GetScrollButtonMinimumSize(temp_dc, this, wxRIBBON_SCROLL_BTN_LEFT | wxRIBBON_SCROLL_BTN_NORMAL | wxRIBBON_SCROLL_BTN_FOR_TABS).GetWidth());
        }
        else
        {
            m_tab_scroll_left_button_rect.SetWidth(0);
        }

        if(show_right)
        {
            if(m_tab_scroll_right_button_rect.GetWidth() == 0)
            {
                m_tab_scroll_right_button_rect.SetWidth(m_art->GetScrollButtonMinimumSize(temp_dc, this, wxRIBBON_SCROLL_BTN_RIGHT | wxRIBBON_SCROLL_BTN_NORMAL | wxRIBBON_SCROLL_BTN_FOR_TABS).GetWidth());
                m_tab_scroll_right_button_rect.SetX(m_tab_scroll_right_button_rect.GetX() - m_tab_scroll_right_button_rect.GetWidth());
            }
        }
        else
        {
            if(m_tab_scroll_right_button_rect.GetWidth() != 0)
            {
                m_tab_scroll_right_button_rect.SetX(m_tab_scroll_right_button_rect.GetX() + m_tab_scroll_right_button_rect.GetWidth());
                m_tab_scroll_right_button_rect.SetWidth(0);
            }
        }
    }

    RefreshTabBar();
}

void wxRibbonBar::RefreshTabBar()
{
    wxRect tab_rect(0, 0, GetClientSize().GetWidth(), m_tab_height);
    Refresh(false, &tab_rect);
}

void wxRibbonBar::OnMouseMiddleDown(wxMouseEvent& evt)
{
    DoMouseButtonCommon(evt, wxEVT_COMMAND_RIBBONBAR_TAB_MIDDLE_DOWN);
}

void wxRibbonBar::OnMouseMiddleUp(wxMouseEvent& evt)
{
    DoMouseButtonCommon(evt, wxEVT_COMMAND_RIBBONBAR_TAB_MIDDLE_UP);
}

void wxRibbonBar::OnMouseRightDown(wxMouseEvent& evt)
{
    DoMouseButtonCommon(evt, wxEVT_COMMAND_RIBBONBAR_TAB_RIGHT_DOWN);
}

void wxRibbonBar::OnMouseRightUp(wxMouseEvent& evt)
{
    DoMouseButtonCommon(evt, wxEVT_COMMAND_RIBBONBAR_TAB_RIGHT_UP);
}

void wxRibbonBar::DoMouseButtonCommon(wxMouseEvent& evt, wxEventType tab_event_type)
{
    wxRibbonPageTabInfo *tab = HitTestTabs(evt.GetPosition());
    if(tab)
    {
        wxRibbonBarEvent notification(tab_event_type, GetId(), tab->page);
        notification.SetEventObject(this);
        ProcessWindowEvent(notification);
    }
}

void wxRibbonBar::RecalculateMinSize()
{
    wxSize min_size(wxDefaultCoord, wxDefaultCoord);
    size_t numtabs = m_pages.GetCount();
    if(numtabs != 0)
    {
        min_size = m_pages.Item(0).page->GetMinSize();

        size_t i;
        for(i = 1; i < numtabs; ++i)
        {
            wxRibbonPageTabInfo& info = m_pages.Item(i);
            wxSize page_min = info.page->GetMinSize();

            min_size.x = wxMax(min_size.x, page_min.x);
            min_size.y = wxMax(min_size.y, page_min.y);
        }
    }
    if(min_size.y != wxDefaultCoord)
    {
        // TODO: Decide on best course of action when min height is unspecified
        // - should we specify it to the tab minimum, or leave it unspecified?
        min_size.IncBy(0, m_tab_height);
    }

    m_minWidth = min_size.GetWidth();
    m_minHeight = min_size.GetHeight();
}

wxSize wxRibbonBar::DoGetBestSize() const
{
    wxSize best(0, 0);
    if(m_current_page != -1)
    {
        best = m_pages.Item(m_current_page).page->GetBestSize();
    }
    if(best.GetHeight() == wxDefaultCoord)
    {
        best.SetHeight(m_tab_height);
    }
    else
    {
        best.IncBy(0, m_tab_height);
    }
    return best;
}

#endif // wxUSE_RIBBON

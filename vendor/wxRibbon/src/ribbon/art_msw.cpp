///////////////////////////////////////////////////////////////////////////////
// Name:        src/ribbon/art_msw.cpp
// Purpose:     MSW style art provider for ribbon interface
// Author:      Peter Cawley
// Modified by:
// Created:     2009-05-25
// RCS-ID:      $Id: art_msw.cpp,v 1.3.2.1 2025/04/05 16:16:41 lothar Exp $
// Copyright:   (C) Peter Cawley
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wx/ribbon/art.h"

#if wxUSE_RIBBON

#include "wx/ribbon/art_internal.h"
#include "wx/ribbon/bar.h"
#include "wx/ribbon/buttonbar.h"
#include "wx/ribbon/gallery.h"
#include "wx/ribbon/toolbar.h"

#ifndef WX_PRECOMP
#endif

#ifdef __WXMSW__
#include "wx/msw/private.h"
#endif // __WXMSW__

#ifdef __WXMAC__
#include "wx/dc.h"
#include "wx/dcmemory.h"
#endif // __WXMSW__

static const char* const gallery_up_xpm[] = {
  "5 5 2 1",
  "  c None",
  "x c #FF00FF",
  "     ",
  "  x  ",
  " xxx ",
  "xxxxx",
  "     "};

static const char* const gallery_down_xpm[] = {
  "5 5 2 1",
  "  c None",
  "x c #FF00FF",
  "     ",
  "xxxxx",
  " xxx ",
  "  x  ",
  "     "};

static const char* const gallery_left_xpm[] = {
  "5 5 2 1",
  "  c None",
  "x c #FF00FF",
  "   x ",
  "  xx ",
  " xxx ",
  "  xx ",
  "   x "};

static const char* const gallery_right_xpm[] = {
  "5 5 2 1",
  "  c None",
  "x c #FF00FF",
  " x   ",
  " xx  ",
  " xxx ",
  " xx  ",
  " x   "};

static const char* const gallery_extension_xpm[] = {
  "5 5 2 1",
  "  c None",
  "x c #FF00FF",
  "xxxxx",
  "     ",
  "xxxxx",
  " xxx ",
  "  x  "};

wxRibbonMSWArtProvider::wxRibbonMSWArtProvider(bool set_colour_scheme)
{
    m_flags = 0;
    m_tab_label_font = wxFont(8, wxDEFAULT, wxNORMAL, wxNORMAL, FALSE);
    m_button_bar_label_font = m_tab_label_font;
    m_panel_label_font = m_tab_label_font;

    if(set_colour_scheme)
    {
        SetColourScheme(
            wxColour(194, 216, 241),
            wxColour(255, 223, 114),
            wxColour(  0,   0,   0));
    }

    m_cached_tab_separator_visibility = -10.0; // valid visibilities are in range [0, 1]
    m_tab_separation_size = 3;
    m_page_border_left = 2;
    m_page_border_top = 1;
    m_page_border_right = 2;
    m_page_border_bottom = 3;
    m_panel_x_separation_size = 1;
    m_panel_y_separation_size = 1;
    m_tool_group_separation_size = 3;
    m_gallery_bitmap_padding_left_size = 4;
    m_gallery_bitmap_padding_right_size = 4;
    m_gallery_bitmap_padding_top_size = 4;
    m_gallery_bitmap_padding_bottom_size = 4;
}

wxRibbonMSWArtProvider::~wxRibbonMSWArtProvider()
{
}

void wxRibbonMSWArtProvider::GetColourScheme(
                         wxColour* primary,
                         wxColour* secondary,
                         wxColour* tertiary) const
{
    if(primary != NULL)
        *primary = m_primary_scheme_colour;
    if(secondary != NULL)
        *secondary = m_secondary_scheme_colour;
    if(tertiary != NULL)
        *tertiary = m_tertiary_scheme_colour;
}

void wxRibbonMSWArtProvider::SetColourScheme(
                         const wxColour& primary,
                         const wxColour& secondary,
                         const wxColour& tertiary)
{
    m_primary_scheme_colour = primary;
    m_secondary_scheme_colour = secondary;
    m_tertiary_scheme_colour = tertiary;

    wxRibbonHSLColour primary_hsl(primary);
    wxRibbonHSLColour secondary_hsl(secondary);
    // tertiary not used for anything

    // Map primary saturation from [0, 1] to [.25, .75]
    primary_hsl.saturation = cos(primary_hsl.saturation * M_PI) * -0.25 + 0.5;

    // Map primary luminance from [0, 1] to [.23, .83]
    primary_hsl.luminance = cos(primary_hsl.luminance * M_PI) * -0.3 + 0.53;

    // Map secondary saturation from [0, 1] to [0.16, 0.84]
    secondary_hsl.saturation = cos(secondary_hsl.saturation * M_PI) * -0.34 + 0.5;

    // Map secondary luminance from [0, 1] to [0.1, 0.9]
    secondary_hsl.luminance = cos(secondary_hsl.luminance * M_PI) * -0.4 + 0.5;

#define LikePrimary(h, s, l) \
    primary_hsl.ShiftHue(h ## f).Saturated(s ## f).Lighter(l ## f).ToRGB()
#define LikeSecondary(h, s, l) \
    secondary_hsl.ShiftHue(h ## f).Saturated(s ## f).Lighter(l ## f).ToRGB()

    m_page_border_pen = LikePrimary(1.4, 0.00, -0.08);

    m_page_background_top_colour = LikePrimary(-0.1, -0.03, 0.12);
    m_page_hover_background_top_colour = LikePrimary(-2.8, 0.27, 0.17);
    m_page_background_top_gradient_colour = LikePrimary(0.1, -0.10, 0.08);
    m_page_hover_background_top_gradient_colour = LikePrimary(3.2, 0.16, 0.13);
    m_page_background_colour = LikePrimary(0.4, -0.09, 0.05);
    m_page_hover_background_colour = LikePrimary(0.1, 0.19, 0.10);
    m_page_background_gradient_colour = LikePrimary(-3.2, 0.27, 0.10);
    m_page_hover_background_gradient_colour = LikePrimary(1.8, 0.01, 0.15);

    m_tab_active_background_colour = LikePrimary(-0.1, -0.31, 0.16);
    m_tab_active_background_gradient_colour = LikePrimary(-0.1, -0.03, 0.12);
    m_tab_separator_colour = LikePrimary(0.9, 0.24, 0.05);
    m_tab_ctrl_background_brush = LikePrimary(1.0, 0.39, 0.07);
    m_tab_hover_background_colour = LikePrimary(1.3, 0.15, 0.10);
    m_tab_hover_background_top_colour = LikePrimary(1.4, 0.36, 0.08);
    m_tab_border_pen = LikePrimary(1.4, 0.03, -0.05);  
    m_tab_separator_gradient_colour = LikePrimary(1.7, -0.15, -0.18);
    m_tab_hover_background_top_gradient_colour = LikePrimary(1.8, 0.34, 0.13);   
    m_tab_label_colour = LikePrimary(4.3, 0.13, -0.49);
    m_tab_hover_background_gradient_colour = LikeSecondary(-1.5, -0.34, 0.01);

    m_panel_minimised_border_gradient_pen = LikePrimary(-6.9, -0.17, -0.09);
    m_panel_minimised_border_pen = LikePrimary(-5.3, -0.24, -0.06);
    m_panel_border_gradient_pen	= LikePrimary(-5.2, -0.15, -0.06);
    m_panel_border_pen = LikePrimary(-2.8, -0.32, 0.02);
    m_panel_label_background_brush = LikePrimary(-1.5, 0.03, 0.05);
    m_panel_active_background_gradient_colour = LikePrimary(0.5, 0.34, 0.05);
    m_panel_hover_label_background_brush = LikePrimary(1.0, 0.30, 0.09);
    m_panel_active_background_top_gradient_colour = LikePrimary(1.4, -0.17, -0.13);
    m_panel_active_background_colour = LikePrimary(1.6, -0.18, -0.18);
    m_panel_active_background_top_colour = LikePrimary(1.7, -0.20, -0.03);
    m_panel_label_colour = LikePrimary(2.8, -0.14, -0.35);
    m_panel_hover_label_colour = m_panel_label_colour;
    m_panel_minimised_label_colour = m_tab_label_colour;

    m_gallery_button_disabled_background_colour = LikePrimary(-2.8, -0.46, 0.09);
    m_gallery_button_disabled_background_top_brush = LikePrimary(-2.8, -0.36, 0.15);    
    m_gallery_hover_background_brush = LikePrimary(-0.8, 0.05, 0.15);
    m_gallery_border_pen = LikePrimary(0.7, -0.02, 0.03);
    m_gallery_button_background_top_brush = LikePrimary(0.8, 0.34, 0.13);
    m_gallery_button_background_colour = LikePrimary(1.3, 0.10, 0.08);
    // SetColour used so that the relevant bitmaps are generated
    SetColour(wxRIBBON_ART_GALLERY_BUTTON_FACE_COLOUR, LikePrimary(1.4, -0.21, -0.23));
    SetColour(wxRIBBON_ART_GALLERY_BUTTON_HOVER_FACE_COLOUR, LikePrimary(1.5, -0.24, -0.29));
    SetColour(wxRIBBON_ART_GALLERY_BUTTON_ACTIVE_FACE_COLOUR, LikePrimary(1.5, -0.24, -0.29));
    SetColour(wxRIBBON_ART_GALLERY_BUTTON_DISABLED_FACE_COLOUR, LikePrimary(0.0, -1.0, 0.0));
    m_gallery_button_disabled_background_gradient_colour = LikePrimary(1.5, -0.43, 0.12);
    m_gallery_button_background_gradient_colour = LikePrimary(1.7, 0.11, 0.09);
    m_gallery_item_border_pen = LikeSecondary(-3.9, -0.16, -0.14);
    m_gallery_button_hover_background_colour = LikeSecondary(-0.9, 0.16, -0.07);
    m_gallery_button_hover_background_gradient_colour = LikeSecondary(0.1, 0.12, 0.03);
    m_gallery_button_hover_background_top_brush = LikeSecondary(4.3, 0.16, 0.17);

    m_gallery_button_active_background_colour = LikeSecondary(-9.9, 0.03, -0.22);
    m_gallery_button_active_background_gradient_colour = LikeSecondary(-9.5, 0.14, -0.11);
    m_gallery_button_active_background_top_brush = LikeSecondary(-9.0, 0.15, -0.08);
    
    m_button_bar_label_colour = m_tab_label_colour;
    m_button_bar_hover_border_pen = LikeSecondary(-6.2, -0.47, -0.14);
    m_button_bar_hover_background_gradient_colour = LikeSecondary(-0.6, 0.16, 0.04);
    m_button_bar_hover_background_colour = LikeSecondary(-0.2, 0.16, -0.10);
    m_button_bar_hover_background_top_gradient_colour = LikeSecondary(0.2, 0.16, 0.03);
    m_button_bar_hover_background_top_colour = LikeSecondary(8.8, 0.16, 0.17);
    m_button_bar_active_border_pen = LikeSecondary(-6.2, -0.47, -0.25);
    m_button_bar_active_background_top_colour = LikeSecondary(-8.4, 0.08, 0.06);
    m_button_bar_active_background_top_gradient_colour = LikeSecondary(-9.7, 0.13, -0.07);
    m_button_bar_active_background_colour = LikeSecondary(-9.9, 0.14, -0.14);
    m_button_bar_active_background_gradient_colour = LikeSecondary(-8.7, 0.17, -0.03);

    m_toolbar_border_pen = LikePrimary(1.4, -0.21, -0.16);
    SetColour(wxRIBBON_ART_TOOLBAR_FACE_COLOUR, LikePrimary(1.4, -0.17, -0.22));
    m_tool_background_top_colour = LikePrimary(-1.9, -0.07, 0.06);
    m_tool_background_top_gradient_colour = LikePrimary(1.4, 0.12, 0.08);
    m_tool_background_colour = LikePrimary(1.4, -0.09, 0.03);
    m_tool_background_gradient_colour = LikePrimary(1.9, 0.11, 0.09);
    m_tool_hover_background_top_colour = LikeSecondary(3.4, 0.11, 0.16);
    m_tool_hover_background_top_gradient_colour = LikeSecondary(-1.4, 0.04, 0.08);
    m_tool_hover_background_colour = LikeSecondary(-1.8, 0.16, -0.12);
    m_tool_hover_background_gradient_colour = LikeSecondary(-2.6, 0.16, 0.05);
    m_tool_active_background_top_colour = LikeSecondary(-9.9, -0.12, -0.09);
    m_tool_active_background_top_gradient_colour = LikeSecondary(-8.5, 0.16, -0.12);
    m_tool_active_background_colour = LikeSecondary(-7.9, 0.16, -0.20);
    m_tool_active_background_gradient_colour = LikeSecondary(-6.6, 0.16, -0.10);

#undef LikePrimary
#undef LikeSecondary

    // Invalidate cached tab separator
    m_cached_tab_separator_visibility = -1.0;
}

wxRibbonArtProvider* wxRibbonMSWArtProvider::Clone() const
{
    wxRibbonMSWArtProvider *copy = new wxRibbonMSWArtProvider;
    CloneTo(copy);
    return copy;
}

void wxRibbonMSWArtProvider::CloneTo(wxRibbonMSWArtProvider* copy) const
{
    for(int i = 0; i < 4; ++i)
    {
        copy->m_gallery_up_bitmap[i] = m_gallery_up_bitmap[i];
        copy->m_gallery_down_bitmap[i] = m_gallery_down_bitmap[i];
        copy->m_gallery_extension_bitmap[i] = m_gallery_extension_bitmap[i];
    }
    copy->m_toolbar_drop_bitmap = m_toolbar_drop_bitmap;

    copy->m_primary_scheme_colour = m_primary_scheme_colour;
    copy->m_secondary_scheme_colour = m_secondary_scheme_colour;
    copy->m_tertiary_scheme_colour = m_tertiary_scheme_colour;

    copy->m_button_bar_label_colour = m_button_bar_label_colour;
    copy->m_tab_label_colour = m_tab_label_colour;
    copy->m_tab_separator_colour = m_tab_separator_colour;
    copy->m_tab_separator_gradient_colour = m_tab_separator_gradient_colour;
    copy->m_tab_active_background_colour = m_tab_hover_background_colour;
    copy->m_tab_active_background_gradient_colour = m_tab_hover_background_gradient_colour;
    copy->m_tab_hover_background_colour = m_tab_hover_background_colour;
    copy->m_tab_hover_background_gradient_colour = m_tab_hover_background_gradient_colour;
    copy->m_tab_hover_background_top_colour = m_tab_hover_background_top_colour;
    copy->m_tab_hover_background_top_gradient_colour = m_tab_hover_background_top_gradient_colour;
    copy->m_panel_label_colour = m_panel_label_colour;
    copy->m_panel_hover_label_colour = m_panel_hover_label_colour;
    copy->m_panel_minimised_label_colour = m_panel_minimised_label_colour;
    copy->m_panel_active_background_colour = m_panel_active_background_colour;
    copy->m_panel_active_background_gradient_colour = m_panel_active_background_gradient_colour;
    copy->m_panel_active_background_top_colour = m_panel_active_background_top_colour;
    copy->m_panel_active_background_top_gradient_colour = m_panel_active_background_top_gradient_colour;
    copy->m_page_background_colour = m_page_background_colour;
    copy->m_page_background_gradient_colour = m_page_background_gradient_colour;
    copy->m_page_background_top_colour = m_page_background_top_colour;
    copy->m_page_background_top_gradient_colour = m_page_background_top_gradient_colour;
    copy->m_page_hover_background_colour = m_page_hover_background_colour;
    copy->m_page_hover_background_gradient_colour = m_page_hover_background_gradient_colour;
    copy->m_page_hover_background_top_colour = m_page_hover_background_top_colour;
    copy->m_page_hover_background_top_gradient_colour = m_page_hover_background_top_gradient_colour;
    copy->m_button_bar_hover_background_colour = m_button_bar_hover_background_colour;
    copy->m_button_bar_hover_background_gradient_colour = m_button_bar_hover_background_gradient_colour;
    copy->m_button_bar_hover_background_top_colour = m_button_bar_hover_background_top_colour;
    copy->m_button_bar_hover_background_top_gradient_colour = m_button_bar_hover_background_top_gradient_colour;
    copy->m_button_bar_active_background_colour = m_button_bar_active_background_colour;
    copy->m_button_bar_active_background_gradient_colour = m_button_bar_active_background_gradient_colour;
    copy->m_button_bar_active_background_top_colour = m_button_bar_active_background_top_colour;
    copy->m_button_bar_active_background_top_gradient_colour = m_button_bar_active_background_top_gradient_colour;
    copy->m_gallery_button_background_colour = m_gallery_button_background_colour;
    copy->m_gallery_button_background_gradient_colour = m_gallery_button_background_gradient_colour;    
    copy->m_gallery_button_hover_background_colour = m_gallery_button_hover_background_colour;
    copy->m_gallery_button_hover_background_gradient_colour = m_gallery_button_hover_background_gradient_colour;
    copy->m_gallery_button_active_background_colour = m_gallery_button_active_background_colour;
    copy->m_gallery_button_active_background_gradient_colour = m_gallery_button_active_background_gradient_colour;
    copy->m_gallery_button_disabled_background_colour = m_gallery_button_disabled_background_colour;
    copy->m_gallery_button_disabled_background_gradient_colour = m_gallery_button_disabled_background_gradient_colour;
    copy->m_gallery_button_face_colour = m_gallery_button_face_colour;
    copy->m_gallery_button_hover_face_colour = m_gallery_button_hover_face_colour;
    copy->m_gallery_button_active_face_colour = m_gallery_button_active_face_colour;
    copy->m_gallery_button_disabled_face_colour = m_gallery_button_disabled_face_colour;

    copy->m_tab_ctrl_background_brush = m_tab_ctrl_background_brush;
    copy->m_panel_label_background_brush = m_panel_label_background_brush;
    copy->m_panel_hover_label_background_brush = m_panel_hover_label_background_brush;
    copy->m_gallery_hover_background_brush = m_gallery_hover_background_brush;
    copy->m_gallery_button_background_top_brush = m_gallery_button_background_top_brush;
    copy->m_gallery_button_hover_background_top_brush = m_gallery_button_hover_background_top_brush;
    copy->m_gallery_button_active_background_top_brush = m_gallery_button_active_background_top_brush;
    copy->m_gallery_button_disabled_background_top_brush = m_gallery_button_disabled_background_top_brush;

    copy->m_tab_label_font = m_tab_label_font;
    copy->m_button_bar_label_font = m_button_bar_label_font;
    copy->m_panel_label_font = m_panel_label_font;

    copy->m_page_border_pen = m_page_border_pen;
    copy->m_panel_border_pen = m_panel_border_pen;
    copy->m_panel_border_gradient_pen = m_panel_border_gradient_pen;
    copy->m_panel_minimised_border_pen = m_panel_minimised_border_pen;
    copy->m_panel_minimised_border_gradient_pen = m_panel_minimised_border_gradient_pen;
    copy->m_tab_border_pen = m_tab_border_pen;
    copy->m_gallery_border_pen = m_gallery_border_pen;
    copy->m_button_bar_hover_border_pen = m_button_bar_hover_border_pen;
    copy->m_button_bar_active_border_pen = m_button_bar_active_border_pen;
    copy->m_gallery_item_border_pen = m_gallery_item_border_pen;
    copy->m_toolbar_border_pen = m_toolbar_border_pen;

    copy->m_flags = m_flags;
    copy->m_tab_separation_size = m_tab_separation_size;
    copy->m_page_border_left = m_page_border_left;
    copy->m_page_border_top = m_page_border_top;
    copy->m_page_border_right = m_page_border_right;
    copy->m_page_border_bottom = m_page_border_bottom;
    copy->m_panel_x_separation_size = m_panel_x_separation_size;
    copy->m_panel_y_separation_size = m_panel_y_separation_size;
    copy->m_gallery_bitmap_padding_left_size = m_gallery_bitmap_padding_left_size;
    copy->m_gallery_bitmap_padding_right_size = m_gallery_bitmap_padding_right_size;
    copy->m_gallery_bitmap_padding_top_size = m_gallery_bitmap_padding_top_size;
    copy->m_gallery_bitmap_padding_bottom_size = m_gallery_bitmap_padding_bottom_size;
}

long wxRibbonMSWArtProvider::GetFlags() const
{
    return m_flags;
}

void wxRibbonMSWArtProvider::SetFlags(long flags)
{
    if((flags ^ m_flags) & wxRIBBON_BAR_FLOW_VERTICAL)
    {
        if(flags & wxRIBBON_BAR_FLOW_VERTICAL)
        {
            m_page_border_left++;
            m_page_border_right++;
            m_page_border_top--;
            m_page_border_bottom--;
        }
        else
        {
            m_page_border_left--;
            m_page_border_right--;
            m_page_border_top++;
            m_page_border_bottom++;
        }
    }
    m_flags = flags;

    // Need to reload some bitmaps when flags change
#define Reload(setting) SetColour(setting, GetColour(setting))
    Reload(wxRIBBON_ART_GALLERY_BUTTON_FACE_COLOUR);
    Reload(wxRIBBON_ART_GALLERY_BUTTON_HOVER_FACE_COLOUR);
    Reload(wxRIBBON_ART_GALLERY_BUTTON_ACTIVE_FACE_COLOUR);
    Reload(wxRIBBON_ART_GALLERY_BUTTON_DISABLED_FACE_COLOUR);
#undef Reload
}

int wxRibbonMSWArtProvider::GetMetric(int id) const
{
    switch(id)
    {
        case wxRIBBON_ART_TAB_SEPARATION_SIZE:
            return m_tab_separation_size;
        case wxRIBBON_ART_PAGE_BORDER_LEFT_SIZE:
            return m_page_border_left;
        case wxRIBBON_ART_PAGE_BORDER_TOP_SIZE:
            return m_page_border_top;
        case wxRIBBON_ART_PAGE_BORDER_RIGHT_SIZE:
            return m_page_border_right;
        case wxRIBBON_ART_PAGE_BORDER_BOTTOM_SIZE:
            return m_page_border_bottom;
        case wxRIBBON_ART_PANEL_X_SEPARATION_SIZE:
            return m_panel_x_separation_size;
        case wxRIBBON_ART_PANEL_Y_SEPARATION_SIZE:
            return m_panel_y_separation_size;
        case wxRIBBON_ART_TOOL_GROUP_SEPARATION_SIZE:
            return m_tool_group_separation_size;
        case wxRIBBON_ART_GALLERY_BITMAP_PADDING_LEFT_SIZE:
            return m_gallery_bitmap_padding_left_size;
        case wxRIBBON_ART_GALLERY_BITMAP_PADDING_RIGHT_SIZE:
            return m_gallery_bitmap_padding_right_size;
        case wxRIBBON_ART_GALLERY_BITMAP_PADDING_TOP_SIZE:
            return m_gallery_bitmap_padding_top_size;
        case wxRIBBON_ART_GALLERY_BITMAP_PADDING_BOTTOM_SIZE:
            return m_gallery_bitmap_padding_bottom_size;
        default:
            wxFAIL_MSG(wxT("Invalid Metric Ordinal"));
            break;
    }

    return 0;
}

void wxRibbonMSWArtProvider::SetMetric(int id, int new_val)
{
    switch(id)
    {
        case wxRIBBON_ART_TAB_SEPARATION_SIZE:
            m_tab_separation_size = new_val;
            break;
        case wxRIBBON_ART_PAGE_BORDER_LEFT_SIZE:
            m_page_border_left = new_val;
            break;
        case wxRIBBON_ART_PAGE_BORDER_TOP_SIZE:
            m_page_border_top = new_val;
            break;
        case wxRIBBON_ART_PAGE_BORDER_RIGHT_SIZE:
            m_page_border_right = new_val;
            break;
        case wxRIBBON_ART_PAGE_BORDER_BOTTOM_SIZE:
            m_page_border_bottom = new_val;
            break;
        case wxRIBBON_ART_PANEL_X_SEPARATION_SIZE:
            m_panel_x_separation_size = new_val;
            break;
        case wxRIBBON_ART_PANEL_Y_SEPARATION_SIZE:
            m_panel_y_separation_size = new_val;
            break;
        case wxRIBBON_ART_TOOL_GROUP_SEPARATION_SIZE:
            m_tool_group_separation_size = new_val;
            break;
        case wxRIBBON_ART_GALLERY_BITMAP_PADDING_LEFT_SIZE:
            m_gallery_bitmap_padding_left_size = new_val;
            break;
        case wxRIBBON_ART_GALLERY_BITMAP_PADDING_RIGHT_SIZE:
            m_gallery_bitmap_padding_right_size = new_val;
            break;
        case wxRIBBON_ART_GALLERY_BITMAP_PADDING_TOP_SIZE:
            m_gallery_bitmap_padding_top_size = new_val;
            break;
        case wxRIBBON_ART_GALLERY_BITMAP_PADDING_BOTTOM_SIZE:
            m_gallery_bitmap_padding_bottom_size = new_val;
            break;
        default:
            wxFAIL_MSG(wxT("Invalid Metric Ordinal"));
            break;
    }
}

void wxRibbonMSWArtProvider::SetFont(int id, const wxFont& font)
{
    switch(id)
    {
        case wxRIBBON_ART_TAB_LABEL_FONT:
            m_tab_label_font = font;
            break;
        case wxRIBBON_ART_BUTTON_BAR_LABEL_FONT:
            m_button_bar_label_font = font;
            break;
        case wxRIBBON_ART_PANEL_LABEL_FONT:
            m_panel_label_font = font;
            break;
        default:
            wxFAIL_MSG(wxT("Invalid Metric Ordinal"));
            break;
    }
}

wxFont wxRibbonMSWArtProvider::GetFont(int id) const
{
    switch(id)
    {
        case wxRIBBON_ART_TAB_LABEL_FONT:
            return m_tab_label_font;
        case wxRIBBON_ART_BUTTON_BAR_LABEL_FONT:
            return m_button_bar_label_font;
        case wxRIBBON_ART_PANEL_LABEL_FONT:
            return m_panel_label_font;
        default:
            wxFAIL_MSG(wxT("Invalid Metric Ordinal"));
            break;
    }

    return wxNullFont;
}

wxColour wxRibbonMSWArtProvider::GetColour(int id) const
{
    switch(id)
    {
        case wxRIBBON_ART_BUTTON_BAR_LABEL_COLOUR:
            return m_button_bar_label_colour;
        case wxRIBBON_ART_BUTTON_BAR_HOVER_BORDER_COLOUR:
            return m_button_bar_hover_border_pen.GetColour();
        case wxRIBBON_ART_BUTTON_BAR_HOVER_BACKGROUND_TOP_COLOUR:
            return m_button_bar_hover_background_top_colour;
        case wxRIBBON_ART_BUTTON_BAR_HOVER_BACKGROUND_TOP_GRADIENT_COLOUR:
            return m_button_bar_hover_background_top_gradient_colour;
        case wxRIBBON_ART_BUTTON_BAR_HOVER_BACKGROUND_COLOUR:
            return m_button_bar_hover_background_colour;
        case wxRIBBON_ART_BUTTON_BAR_HOVER_BACKGROUND_GRADIENT_COLOUR:
            return m_button_bar_hover_background_gradient_colour;
        case wxRIBBON_ART_BUTTON_BAR_ACTIVE_BORDER_COLOUR:
            return m_button_bar_active_border_pen.GetColour();
        case wxRIBBON_ART_BUTTON_BAR_ACTIVE_BACKGROUND_TOP_COLOUR:
            return m_button_bar_active_background_top_colour;
        case wxRIBBON_ART_BUTTON_BAR_ACTIVE_BACKGROUND_TOP_GRADIENT_COLOUR:
            return m_button_bar_active_background_top_gradient_colour;
        case wxRIBBON_ART_BUTTON_BAR_ACTIVE_BACKGROUND_COLOUR:
            return m_button_bar_active_background_colour;
        case wxRIBBON_ART_BUTTON_BAR_ACTIVE_BACKGROUND_GRADIENT_COLOUR:
            return m_button_bar_active_background_gradient_colour;
        case wxRIBBON_ART_GALLERY_BORDER_COLOUR:
            return m_gallery_border_pen.GetColour();
        case wxRIBBON_ART_GALLERY_HOVER_BACKGROUND_COLOUR:
            return m_gallery_hover_background_brush.GetColour();
        case wxRIBBON_ART_GALLERY_BUTTON_BACKGROUND_COLOUR:
            return m_gallery_button_background_colour;
        case wxRIBBON_ART_GALLERY_BUTTON_BACKGROUND_GRADIENT_COLOUR:
            return m_gallery_button_background_gradient_colour;
        case wxRIBBON_ART_GALLERY_BUTTON_BACKGROUND_TOP_COLOUR:
            return m_gallery_button_background_top_brush.GetColour();
        case wxRIBBON_ART_GALLERY_BUTTON_FACE_COLOUR:
            return m_gallery_button_face_colour;
        case wxRIBBON_ART_GALLERY_BUTTON_HOVER_BACKGROUND_COLOUR:
            return m_gallery_button_hover_background_colour;
        case wxRIBBON_ART_GALLERY_BUTTON_HOVER_BACKGROUND_GRADIENT_COLOUR:
            return m_gallery_button_hover_background_gradient_colour;
        case wxRIBBON_ART_GALLERY_BUTTON_HOVER_BACKGROUND_TOP_COLOUR:
            return m_gallery_button_hover_background_top_brush.GetColour();
        case wxRIBBON_ART_GALLERY_BUTTON_HOVER_FACE_COLOUR:
            return m_gallery_button_face_colour;
        case wxRIBBON_ART_GALLERY_BUTTON_ACTIVE_BACKGROUND_COLOUR:
            return m_gallery_button_active_background_colour;
        case wxRIBBON_ART_GALLERY_BUTTON_ACTIVE_BACKGROUND_GRADIENT_COLOUR:
            return m_gallery_button_active_background_gradient_colour;
        case wxRIBBON_ART_GALLERY_BUTTON_ACTIVE_BACKGROUND_TOP_COLOUR:
            return m_gallery_button_background_top_brush.GetColour();
        case wxRIBBON_ART_GALLERY_BUTTON_ACTIVE_FACE_COLOUR:
            return m_gallery_button_active_face_colour;
        case wxRIBBON_ART_GALLERY_BUTTON_DISABLED_BACKGROUND_COLOUR:
            return m_gallery_button_disabled_background_colour;
        case wxRIBBON_ART_GALLERY_BUTTON_DISABLED_BACKGROUND_GRADIENT_COLOUR:
            return m_gallery_button_disabled_background_gradient_colour;
        case wxRIBBON_ART_GALLERY_BUTTON_DISABLED_BACKGROUND_TOP_COLOUR:
            return m_gallery_button_disabled_background_top_brush.GetColour();
        case wxRIBBON_ART_GALLERY_BUTTON_DISABLED_FACE_COLOUR:
            return m_gallery_button_disabled_face_colour;
        case wxRIBBON_ART_GALLERY_ITEM_BORDER_COLOUR:
            return m_gallery_item_border_pen.GetColour();
        case wxRIBBON_ART_TAB_CTRL_BACKGROUND_COLOUR:
        case wxRIBBON_ART_TAB_CTRL_BACKGROUND_GRADIENT_COLOUR:
            return m_tab_ctrl_background_brush.GetColour();
        case wxRIBBON_ART_TAB_LABEL_COLOUR:
            return m_tab_label_colour;
        case wxRIBBON_ART_TAB_SEPARATOR_COLOUR:
            return m_tab_separator_colour;
        case wxRIBBON_ART_TAB_SEPARATOR_GRADIENT_COLOUR:
            return m_tab_separator_gradient_colour;
        case wxRIBBON_ART_TAB_ACTIVE_BACKGROUND_TOP_COLOUR:
        case wxRIBBON_ART_TAB_ACTIVE_BACKGROUND_TOP_GRADIENT_COLOUR:
            return wxColour(0, 0, 0);
        case wxRIBBON_ART_TAB_ACTIVE_BACKGROUND_COLOUR:
            return m_tab_active_background_colour;
        case wxRIBBON_ART_TAB_ACTIVE_BACKGROUND_GRADIENT_COLOUR:
            return m_tab_active_background_gradient_colour;
        case wxRIBBON_ART_TAB_HOVER_BACKGROUND_TOP_COLOUR:
            return m_tab_hover_background_top_colour;
        case wxRIBBON_ART_TAB_HOVER_BACKGROUND_TOP_GRADIENT_COLOUR:
            return m_tab_hover_background_top_gradient_colour;
        case wxRIBBON_ART_TAB_HOVER_BACKGROUND_COLOUR:
            return m_tab_hover_background_colour;
        case wxRIBBON_ART_TAB_HOVER_BACKGROUND_GRADIENT_COLOUR:
            return m_tab_hover_background_gradient_colour;
        case wxRIBBON_ART_TAB_BORDER_COLOUR:
            return m_tab_border_pen.GetColour();
        case wxRIBBON_ART_PANEL_BORDER_COLOUR:
            return m_panel_border_pen.GetColour();
        case wxRIBBON_ART_PANEL_BORDER_GRADIENT_COLOUR:
            return m_panel_border_gradient_pen.GetColour();
        case wxRIBBON_ART_PANEL_MINIMISED_BORDER_COLOUR:
            return m_panel_minimised_border_pen.GetColour();
        case wxRIBBON_ART_PANEL_MINIMISED_BORDER_GRADIENT_COLOUR:
            return m_panel_minimised_border_gradient_pen.GetColour();
        case wxRIBBON_ART_PANEL_LABEL_BACKGROUND_COLOUR:
        case wxRIBBON_ART_PANEL_LABEL_BACKGROUND_GRADIENT_COLOUR:
            return m_panel_label_background_brush.GetColour();
        case wxRIBBON_ART_PANEL_LABEL_COLOUR:
            return m_panel_label_colour;
        case wxRIBBON_ART_PANEL_MINIMISED_LABEL_COLOUR:
            return m_panel_minimised_label_colour;
        case wxRIBBON_ART_PANEL_HOVER_LABEL_BACKGROUND_COLOUR:
        case wxRIBBON_ART_PANEL_HOVER_LABEL_BACKGROUND_GRADIENT_COLOUR:
            return m_panel_hover_label_background_brush.GetColour();
        case wxRIBBON_ART_PANEL_HOVER_LABEL_COLOUR:
            return m_panel_hover_label_colour;
        case wxRIBBON_ART_PANEL_ACTIVE_BACKGROUND_TOP_COLOUR:
            return m_panel_active_background_top_colour;
        case wxRIBBON_ART_PANEL_ACTIVE_BACKGROUND_TOP_GRADIENT_COLOUR:
            return m_panel_active_background_top_gradient_colour;
        case wxRIBBON_ART_PANEL_ACTIVE_BACKGROUND_COLOUR:
            return m_panel_active_background_colour;
        case wxRIBBON_ART_PANEL_ACTIVE_BACKGROUND_GRADIENT_COLOUR:
            return m_panel_active_background_gradient_colour;
        case wxRIBBON_ART_PAGE_BORDER_COLOUR:
            return m_page_border_pen.GetColour();
        case wxRIBBON_ART_PAGE_BACKGROUND_TOP_COLOUR:
            return m_page_background_top_colour;
        case wxRIBBON_ART_PAGE_BACKGROUND_TOP_GRADIENT_COLOUR:
            return m_page_background_top_gradient_colour;
        case wxRIBBON_ART_PAGE_BACKGROUND_COLOUR:
            return m_page_background_colour;
        case wxRIBBON_ART_PAGE_BACKGROUND_GRADIENT_COLOUR:
            return m_page_background_gradient_colour;
        case wxRIBBON_ART_PAGE_HOVER_BACKGROUND_TOP_COLOUR:
            return m_page_hover_background_top_colour;
        case wxRIBBON_ART_PAGE_HOVER_BACKGROUND_TOP_GRADIENT_COLOUR:
            return m_page_hover_background_top_gradient_colour;
        case wxRIBBON_ART_PAGE_HOVER_BACKGROUND_COLOUR:
            return m_page_hover_background_colour;
        case wxRIBBON_ART_PAGE_HOVER_BACKGROUND_GRADIENT_COLOUR:
            return m_page_hover_background_gradient_colour;
        case wxRIBBON_ART_TOOLBAR_BORDER_COLOUR:
        case wxRIBBON_ART_TOOLBAR_HOVER_BORDER_COLOUR:
            return m_toolbar_border_pen.GetColour();
        case wxRIBBON_ART_TOOLBAR_FACE_COLOUR:
            return m_tool_face_colour;
        default:
            wxFAIL_MSG(wxT("Invalid Metric Ordinal"));
            break;
    }

    return wxColour();
}

void wxRibbonMSWArtProvider::SetColour(int id, const wxColor& colour)
{
    switch(id)
    {
        case wxRIBBON_ART_BUTTON_BAR_LABEL_COLOUR:
            m_button_bar_label_colour = colour;
            break;
        case wxRIBBON_ART_BUTTON_BAR_HOVER_BORDER_COLOUR:
            m_button_bar_hover_border_pen.SetColour(colour);
            break;
        case wxRIBBON_ART_BUTTON_BAR_HOVER_BACKGROUND_TOP_COLOUR:
            m_button_bar_hover_background_top_colour = colour;
            break;
        case wxRIBBON_ART_BUTTON_BAR_HOVER_BACKGROUND_TOP_GRADIENT_COLOUR:
            m_button_bar_hover_background_top_gradient_colour = colour;
            break;
        case wxRIBBON_ART_BUTTON_BAR_HOVER_BACKGROUND_COLOUR:
            m_button_bar_hover_background_colour = colour;
            break;
        case wxRIBBON_ART_BUTTON_BAR_HOVER_BACKGROUND_GRADIENT_COLOUR:
            m_button_bar_hover_background_gradient_colour = colour;
            break;
        case wxRIBBON_ART_BUTTON_BAR_ACTIVE_BORDER_COLOUR:
            m_button_bar_active_border_pen.SetColour(colour);
            break;
        case wxRIBBON_ART_BUTTON_BAR_ACTIVE_BACKGROUND_TOP_COLOUR:
            m_button_bar_active_background_top_colour = colour;
            break;
        case wxRIBBON_ART_BUTTON_BAR_ACTIVE_BACKGROUND_TOP_GRADIENT_COLOUR:
            m_button_bar_active_background_top_gradient_colour = colour;
            break;
        case wxRIBBON_ART_BUTTON_BAR_ACTIVE_BACKGROUND_COLOUR:
            m_button_bar_active_background_colour = colour;
            break;
        case wxRIBBON_ART_BUTTON_BAR_ACTIVE_BACKGROUND_GRADIENT_COLOUR:
            m_button_bar_active_background_gradient_colour = colour;
            break;
        case wxRIBBON_ART_GALLERY_BORDER_COLOUR:
            m_gallery_border_pen.SetColour(colour);
            break;
        case wxRIBBON_ART_GALLERY_HOVER_BACKGROUND_COLOUR:
            m_gallery_hover_background_brush.SetColour(colour);
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_BACKGROUND_COLOUR:
            m_gallery_button_background_colour = colour;
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_BACKGROUND_GRADIENT_COLOUR:
            m_gallery_button_background_gradient_colour = colour;
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_BACKGROUND_TOP_COLOUR:
            m_gallery_button_background_top_brush.SetColour(colour);
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_FACE_COLOUR:
            m_gallery_button_face_colour = colour;
            if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
            {
                m_gallery_up_bitmap[0] = wxRibbonLoadPixmap(gallery_left_xpm, colour);
                m_gallery_down_bitmap[0] = wxRibbonLoadPixmap(gallery_right_xpm, colour);
            }
            else
            {
                m_gallery_up_bitmap[0] = wxRibbonLoadPixmap(gallery_up_xpm, colour);
                m_gallery_down_bitmap[0] = wxRibbonLoadPixmap(gallery_down_xpm, colour);
            }
            m_gallery_extension_bitmap[0] = wxRibbonLoadPixmap(gallery_extension_xpm, colour);
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_HOVER_BACKGROUND_COLOUR:
            m_gallery_button_hover_background_colour = colour;
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_HOVER_BACKGROUND_GRADIENT_COLOUR:
            m_gallery_button_hover_background_gradient_colour = colour;
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_HOVER_BACKGROUND_TOP_COLOUR:
            m_gallery_button_hover_background_top_brush.SetColour(colour);
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_HOVER_FACE_COLOUR:
            m_gallery_button_hover_face_colour = colour;
            if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
            {
                m_gallery_up_bitmap[1] = wxRibbonLoadPixmap(gallery_left_xpm, colour);
                m_gallery_down_bitmap[1] = wxRibbonLoadPixmap(gallery_right_xpm, colour);
            }
            else
            {
                m_gallery_up_bitmap[1] = wxRibbonLoadPixmap(gallery_up_xpm, colour);
                m_gallery_down_bitmap[1] = wxRibbonLoadPixmap(gallery_down_xpm, colour);
            }
            m_gallery_extension_bitmap[1] = wxRibbonLoadPixmap(gallery_extension_xpm, colour);
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_ACTIVE_BACKGROUND_COLOUR:
            m_gallery_button_active_background_colour = colour;
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_ACTIVE_BACKGROUND_GRADIENT_COLOUR:
            m_gallery_button_active_background_gradient_colour = colour;
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_ACTIVE_BACKGROUND_TOP_COLOUR:
            m_gallery_button_background_top_brush.SetColour(colour);
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_ACTIVE_FACE_COLOUR:
            m_gallery_button_active_face_colour = colour;
            if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
            {
                m_gallery_up_bitmap[2] = wxRibbonLoadPixmap(gallery_left_xpm, colour);
                m_gallery_down_bitmap[2] = wxRibbonLoadPixmap(gallery_right_xpm, colour);
            }
            else
            {
                m_gallery_up_bitmap[2] = wxRibbonLoadPixmap(gallery_up_xpm, colour);
                m_gallery_down_bitmap[2] = wxRibbonLoadPixmap(gallery_down_xpm, colour);
            }
            m_gallery_extension_bitmap[2] = wxRibbonLoadPixmap(gallery_extension_xpm, colour);
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_DISABLED_BACKGROUND_COLOUR:
            m_gallery_button_disabled_background_colour = colour;
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_DISABLED_BACKGROUND_GRADIENT_COLOUR:
            m_gallery_button_disabled_background_gradient_colour = colour;
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_DISABLED_BACKGROUND_TOP_COLOUR:
            m_gallery_button_disabled_background_top_brush.SetColour(colour);
            break;
        case wxRIBBON_ART_GALLERY_BUTTON_DISABLED_FACE_COLOUR:
            m_gallery_button_disabled_face_colour = colour;
            if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
            {
                m_gallery_up_bitmap[3] = wxRibbonLoadPixmap(gallery_left_xpm, colour);
                m_gallery_down_bitmap[3] = wxRibbonLoadPixmap(gallery_right_xpm, colour);
            }
            else
            {
                m_gallery_up_bitmap[3] = wxRibbonLoadPixmap(gallery_up_xpm, colour);
                m_gallery_down_bitmap[3] = wxRibbonLoadPixmap(gallery_down_xpm, colour);
            }
            m_gallery_extension_bitmap[3] = wxRibbonLoadPixmap(gallery_extension_xpm, colour);
            break;
        case wxRIBBON_ART_GALLERY_ITEM_BORDER_COLOUR:
            m_gallery_item_border_pen.SetColour(colour);
            break;
        case wxRIBBON_ART_TAB_CTRL_BACKGROUND_COLOUR:
        case wxRIBBON_ART_TAB_CTRL_BACKGROUND_GRADIENT_COLOUR:
            m_tab_ctrl_background_brush.SetColour(colour);
            m_cached_tab_separator_visibility = -1.0;
            break;
        case wxRIBBON_ART_TAB_LABEL_COLOUR:
            m_tab_label_colour = colour;
            break;
        case wxRIBBON_ART_TAB_SEPARATOR_COLOUR:
            m_tab_separator_colour = colour;
            m_cached_tab_separator_visibility = -1.0;
            break;
        case wxRIBBON_ART_TAB_SEPARATOR_GRADIENT_COLOUR:
            m_tab_separator_gradient_colour = colour;
            m_cached_tab_separator_visibility = -1.0;
            break;
        case wxRIBBON_ART_TAB_ACTIVE_BACKGROUND_TOP_COLOUR:
        case wxRIBBON_ART_TAB_ACTIVE_BACKGROUND_TOP_GRADIENT_COLOUR:
            break;
        case wxRIBBON_ART_TAB_ACTIVE_BACKGROUND_COLOUR:
            m_tab_active_background_colour = colour;
            break;
        case wxRIBBON_ART_TAB_ACTIVE_BACKGROUND_GRADIENT_COLOUR:
            m_tab_active_background_gradient_colour = colour;
            break;
        case wxRIBBON_ART_TAB_HOVER_BACKGROUND_TOP_COLOUR:
            m_tab_hover_background_top_colour = colour;
            break;
        case wxRIBBON_ART_TAB_HOVER_BACKGROUND_TOP_GRADIENT_COLOUR:
            m_tab_hover_background_top_gradient_colour = colour;
            break;
        case wxRIBBON_ART_TAB_HOVER_BACKGROUND_COLOUR:
            m_tab_hover_background_colour = colour;
            break;
        case wxRIBBON_ART_TAB_HOVER_BACKGROUND_GRADIENT_COLOUR:
            m_tab_hover_background_gradient_colour = colour;
            break;
        case wxRIBBON_ART_TAB_BORDER_COLOUR:
            m_tab_border_pen.SetColour(colour);
            break;
        case wxRIBBON_ART_PANEL_BORDER_COLOUR:
            m_panel_border_pen.SetColour(colour);
            break;
        case wxRIBBON_ART_PANEL_BORDER_GRADIENT_COLOUR:
            m_panel_border_gradient_pen.SetColour(colour);
            break;
        case wxRIBBON_ART_PANEL_MINIMISED_BORDER_COLOUR:
            m_panel_minimised_border_pen.SetColour(colour);
            break;
        case wxRIBBON_ART_PANEL_MINIMISED_BORDER_GRADIENT_COLOUR:
            m_panel_minimised_border_gradient_pen.SetColour(colour);
            break;
        case wxRIBBON_ART_PANEL_LABEL_BACKGROUND_COLOUR:
        case wxRIBBON_ART_PANEL_LABEL_BACKGROUND_GRADIENT_COLOUR:
            m_panel_label_background_brush.SetColour(colour);
            break;
        case wxRIBBON_ART_PANEL_LABEL_COLOUR:
            m_panel_label_colour = colour;
            break;
        case wxRIBBON_ART_PANEL_HOVER_LABEL_BACKGROUND_COLOUR:
        case wxRIBBON_ART_PANEL_HOVER_LABEL_BACKGROUND_GRADIENT_COLOUR:
            m_panel_hover_label_background_brush.SetColour(colour);
            break;
        case wxRIBBON_ART_PANEL_HOVER_LABEL_COLOUR:
            m_panel_hover_label_colour = colour;
            break;
        case wxRIBBON_ART_PANEL_MINIMISED_LABEL_COLOUR:
            m_panel_minimised_label_colour = colour;
            break;
        case wxRIBBON_ART_PANEL_ACTIVE_BACKGROUND_TOP_COLOUR:
            m_panel_active_background_top_colour = colour;
            break;
        case wxRIBBON_ART_PANEL_ACTIVE_BACKGROUND_TOP_GRADIENT_COLOUR:
            m_panel_active_background_top_gradient_colour = colour;
            break;
        case wxRIBBON_ART_PANEL_ACTIVE_BACKGROUND_COLOUR:
            m_panel_active_background_colour = colour;
            break;
        case wxRIBBON_ART_PANEL_ACTIVE_BACKGROUND_GRADIENT_COLOUR:
            m_panel_active_background_gradient_colour = colour;
            break;
        case wxRIBBON_ART_PAGE_BORDER_COLOUR:
            m_page_border_pen.SetColour(colour);
            break;
        case wxRIBBON_ART_PAGE_BACKGROUND_TOP_COLOUR:
            m_page_background_top_colour = colour;
            break;
        case wxRIBBON_ART_PAGE_BACKGROUND_TOP_GRADIENT_COLOUR:
            m_page_background_top_gradient_colour = colour;
            break;
        case wxRIBBON_ART_PAGE_BACKGROUND_COLOUR:
            m_page_background_colour = colour;
            break;
        case wxRIBBON_ART_PAGE_BACKGROUND_GRADIENT_COLOUR:
            m_page_background_gradient_colour = colour;
            break;
        case wxRIBBON_ART_PAGE_HOVER_BACKGROUND_TOP_COLOUR:
            m_page_hover_background_top_colour = colour;
            break;
        case wxRIBBON_ART_PAGE_HOVER_BACKGROUND_TOP_GRADIENT_COLOUR:
            m_page_hover_background_top_gradient_colour = colour;
            break;
        case wxRIBBON_ART_PAGE_HOVER_BACKGROUND_COLOUR:
            m_page_hover_background_colour = colour;
            break;
        case wxRIBBON_ART_PAGE_HOVER_BACKGROUND_GRADIENT_COLOUR:
            m_page_hover_background_gradient_colour = colour;
            break;
        case wxRIBBON_ART_TOOLBAR_BORDER_COLOUR:
        case wxRIBBON_ART_TOOLBAR_HOVER_BORDER_COLOUR:
            m_toolbar_border_pen.SetColour(colour);
            break;
        case wxRIBBON_ART_TOOLBAR_FACE_COLOUR:
            m_tool_face_colour = colour;
            m_toolbar_drop_bitmap = wxRibbonLoadPixmap(gallery_down_xpm, colour);
            break;
        default:
            wxFAIL_MSG(wxT("Invalid Metric Ordinal"));
            break;
    }
}

void wxRibbonMSWArtProvider::DrawTabCtrlBackground(
                        wxDC& dc,
                        wxWindow* WXUNUSED(wnd),
                        const wxRect& rect)
{
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(m_tab_ctrl_background_brush);
    dc.DrawRectangle(rect.x, rect.y, rect.width, rect.height);

    dc.SetPen(m_page_border_pen);
    if(rect.width > 6)
    {
        dc.DrawLine(rect.x + 3, rect.y + rect.height - 1, rect.x + rect.width - 3, rect.y + rect.height - 1);
    }
    else
    {
        dc.DrawLine(rect.x, rect.y + rect.height - 1, rect.x + rect.width, rect.y + rect.height - 1);
    }
}

void wxRibbonMSWArtProvider::DrawTab(
                 wxDC& dc,
                 wxWindow* WXUNUSED(wnd),
                 const wxRibbonPageTabInfo& tab)
{
    if(tab.rect.height <= 2)
        return;

    if(tab.active || tab.hovered)
    {
        if(tab.active)
        {
            wxRect background(tab.rect);

            background.x += 2;
            background.y += 2;
            background.width -= 4;
            background.height -= 2;

            dc.GradientFillLinear(background, m_tab_active_background_colour,
                m_tab_active_background_gradient_colour, wxSOUTH);

            // TODO: active and hovered
        }
        else if(tab.hovered)
        {
            wxRect background(tab.rect);

            background.x += 2;
            background.y += 2;
            background.width -= 4;
            background.height -= 3;
            int h = background.height;
            background.height /= 2;
            dc.GradientFillLinear(background,
                m_tab_hover_background_top_colour,
                m_tab_hover_background_top_gradient_colour, wxSOUTH);

            background.y += background.height;
            background.height = h - background.height;
            dc.GradientFillLinear(background, m_tab_hover_background_colour,
                m_tab_hover_background_gradient_colour, wxSOUTH);
        }

        wxPoint border_points[6];
        border_points[0] = wxPoint(1, tab.rect.height - 2);
        border_points[1] = wxPoint(1, 3);
        border_points[2] = wxPoint(3, 1);
        border_points[3] = wxPoint(tab.rect.width - 4, 1);
        border_points[4] = wxPoint(tab.rect.width - 2, 3);
        border_points[5] = wxPoint(tab.rect.width - 2, tab.rect.height - 1);

        dc.SetPen(m_tab_border_pen);
        dc.DrawLines(sizeof(border_points)/sizeof(wxPoint), border_points, tab.rect.x, tab.rect.y);

        if(tab.active)
        {
            // Give the tab a curved outward border at the bottom
            dc.DrawPoint(tab.rect.x, tab.rect.y + tab.rect.height - 2);
            dc.DrawPoint(tab.rect.x + tab.rect.width - 1, tab.rect.y + tab.rect.height - 2);

            wxPen p(m_tab_active_background_gradient_colour);
            dc.SetPen(p);

            // Technically the first two points are the wrong colour, but they're near enough
            dc.DrawPoint(tab.rect.x + 1, tab.rect.y + tab.rect.height - 2);
            dc.DrawPoint(tab.rect.x + tab.rect.width - 2, tab.rect.y + tab.rect.height - 2);
            dc.DrawPoint(tab.rect.x + 1, tab.rect.y + tab.rect.height - 1);
            dc.DrawPoint(tab.rect.x, tab.rect.y + tab.rect.height - 1);
            dc.DrawPoint(tab.rect.x + tab.rect.width - 2, tab.rect.y + tab.rect.height - 1);
            dc.DrawPoint(tab.rect.x + tab.rect.width - 1, tab.rect.y + tab.rect.height - 1);
        }
    }

    if(m_flags & wxRIBBON_BAR_SHOW_PAGE_ICONS)
    {
        wxBitmap icon = tab.page->GetIcon();
        int x = tab.rect.x + 4;
        if((m_flags & wxRIBBON_BAR_SHOW_PAGE_LABELS) == 0)
            x = tab.rect.x + (tab.rect.width - icon.GetWidth()) / 2;
        dc.DrawBitmap(icon, x, tab.rect.y + 1 + (tab.rect.height - 1 -
            icon.GetHeight()) / 2, true);
    }
    if(m_flags & wxRIBBON_BAR_SHOW_PAGE_LABELS)
    {
        wxString label = tab.page->GetLabel();
        if(!label.IsEmpty())
        {
            dc.SetFont(m_tab_label_font);
            dc.SetTextForeground(m_tab_label_colour);
            dc.SetBackgroundMode(wxTRANSPARENT);

            int text_height;
            int text_width;
            dc.GetTextExtent(label, &text_width, &text_height);
            int width = tab.rect.width - 5;
            int x = tab.rect.x + 3;
            if(m_flags & wxRIBBON_BAR_SHOW_PAGE_ICONS)
            {
                x += 3 + tab.page->GetIcon().GetWidth();
                width -= 3 + tab.page->GetIcon().GetWidth();
            }
            int y = tab.rect.y + (tab.rect.height - text_height) / 2;

            if(width <= text_width)
            {
                dc.SetClippingRegion(x, tab.rect.y, width, tab.rect.height);
                dc.DrawText(label, x, y);
            }
            else
            {
                dc.DrawText(label, x + (width - text_width) / 2 + 1, y);
            }
        }
    }
}

void wxRibbonMSWArtProvider::DrawTabSeparator(
                        wxDC& dc,
                        wxWindow* wnd,
                        const wxRect& rect,
                        double visibility)
{
    if(visibility <= 0.0)
    {
        return;
    }
    if(visibility > 1.0)
    {
        visibility = 1.0;
    }

    // The tab separator is relatively expensive to draw (for its size), and is
    // usually drawn multiple times sequentially (in different positions), so it
    // makes sense to draw it once and cache it.

	wxSize s = wxSize(m_cached_tab_separator.GetWidth(), m_cached_tab_separator.GetHeight());

    if(!m_cached_tab_separator.IsOk() || s != rect.GetSize() || visibility != m_cached_tab_separator_visibility)
    {
        wxRect size(rect.GetSize());
        ReallyDrawTabSeparator(wnd, size, visibility);
    }
    dc.DrawBitmap(m_cached_tab_separator, rect.x, rect.y, false);
}

void wxRibbonMSWArtProvider::ReallyDrawTabSeparator(wxWindow* wnd, const wxRect& rect, double visibility)
{
	wxSize s = wxSize(m_cached_tab_separator.GetWidth(), m_cached_tab_separator.GetHeight());
    if(!m_cached_tab_separator.IsOk() || s != rect.GetSize())
    {
        m_cached_tab_separator = wxBitmap(rect.GetWidth(), rect.GetHeight());
    }

    wxMemoryDC dc(m_cached_tab_separator);
    DrawTabCtrlBackground(dc, wnd, rect);

    wxCoord x = rect.x + rect.width / 2;
    double h = (double)(rect.height - 1);

    double r1 = m_tab_ctrl_background_brush.GetColour().Red() * (1.0 - visibility) + 0.5;
    double g1 = m_tab_ctrl_background_brush.GetColour().Green() * (1.0 - visibility) + 0.5;
    double b1 = m_tab_ctrl_background_brush.GetColour().Blue() * (1.0 - visibility) + 0.5;
    double r2 = m_tab_separator_colour.Red();
    double g2 = m_tab_separator_colour.Green();
    double b2 = m_tab_separator_colour.Blue();
    double r3 = m_tab_separator_gradient_colour.Red();
    double g3 = m_tab_separator_gradient_colour.Green();
    double b3 = m_tab_separator_gradient_colour.Blue();

    for(int i = 0; i < rect.height - 1; ++i)
    {
        double p = ((double)i)/h;

        double r = (p * r3 + (1.0 - p) * r2) * visibility + r1;
        double g = (p * g3 + (1.0 - p) * g2) * visibility + g1;
        double b = (p * b3 + (1.0 - p) * b2) * visibility + b1;

        wxPen P(wxColour((unsigned char)r, (unsigned char)g, (unsigned char)b));
        dc.SetPen(P);
        dc.DrawPoint(x, rect.y + i);
    }

    m_cached_tab_separator_visibility = visibility;
}

void wxRibbonMSWArtProvider::DrawPartialPageBackground(wxDC& dc,
        wxWindow* WXUNUSED(wnd), const wxRect& rect, wxRibbonPage* page,
        wxPoint offset, bool hovered)
{
    wxRect background(page->GetSize());
    page->AdjustRectToIncludeScrollButtons(&background);
    background.height -= 2;
    // Page background isn't dependant upon the width of the page
    // (at least not the part of it intended to be painted by this
    // function). Set to wider than the page itself for when externally
    // expanded panels need a background - the expanded panel can be wider
    // than the bar.
    background.x = 0;
    background.width = INT_MAX;

    // upper_rect, lower_rect, paint_rect are all in page co-ordinates
    wxRect upper_rect(background);
    upper_rect.height /= 5;

    wxRect lower_rect(background);
    lower_rect.y += upper_rect.height;
    lower_rect.height -= upper_rect.height;

    wxRect paint_rect(rect);
    paint_rect.x += offset.x;
    paint_rect.y += offset.y;

    wxColour bg_top, bg_top_grad, bg_btm, bg_btm_grad;
    if(hovered)
    {
        bg_top = m_page_hover_background_top_colour;
        bg_top_grad = m_page_hover_background_top_gradient_colour;
        bg_btm = m_page_hover_background_colour;
        bg_btm_grad = m_page_hover_background_gradient_colour;
    }
    else
    {
        bg_top = m_page_background_top_colour;
        bg_top_grad = m_page_background_top_gradient_colour;
        bg_btm = m_page_background_colour;
        bg_btm_grad = m_page_background_gradient_colour;
    }

    if(paint_rect.Intersects(upper_rect))
    {
        wxRect rect(upper_rect);
        rect.Intersect(paint_rect);
        rect.x -= offset.x;
        rect.y -= offset.y;
        wxColour starting_colour(wxRibbonInterpolateColour(bg_top, bg_top_grad,
            paint_rect.y, upper_rect.y, upper_rect.y + upper_rect.height));
        wxColour ending_colour(wxRibbonInterpolateColour(bg_top, bg_top_grad,
            paint_rect.y + paint_rect.height, upper_rect.y,
            upper_rect.y + upper_rect.height));
        dc.GradientFillLinear(rect, starting_colour, ending_colour, wxSOUTH);
    }

    if(paint_rect.Intersects(lower_rect))
    {
        wxRect rect(lower_rect);
        rect.Intersect(paint_rect);
        rect.x -= offset.x;
        rect.y -= offset.y;
        wxColour starting_colour(wxRibbonInterpolateColour(bg_btm, bg_btm_grad,
            paint_rect.y, lower_rect.y, lower_rect.y + lower_rect.height));
        wxColour ending_colour(wxRibbonInterpolateColour(bg_btm, bg_btm_grad,
            paint_rect.y + paint_rect.height,
            lower_rect.y, lower_rect.y + lower_rect.height));
        dc.GradientFillLinear(rect, starting_colour, ending_colour, wxSOUTH);
    }
}

void wxRibbonMSWArtProvider::DrawPageBackground(
                        wxDC& dc,
                        wxWindow* WXUNUSED(wnd),
                        const wxRect& rect)
{
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(m_tab_ctrl_background_brush);

    {
        wxRect edge(rect);

        edge.width = 2;
        dc.DrawRectangle(edge.x, edge.y, edge.width, edge.height);

        edge.x += rect.width - 2;
        dc.DrawRectangle(edge.x, edge.y, edge.width, edge.height);

        edge = rect;
        edge.height = 2;
        edge.y += (rect.height - edge.height);
        dc.DrawRectangle(edge.x, edge.y, edge.width, edge.height);
    }

    {
        wxRect background(rect);
        background.x += 2;
        background.width -= 4;
        background.height -= 2;

        background.height /= 5;
        dc.GradientFillLinear(background, m_page_background_top_colour,
            m_page_background_top_gradient_colour, wxSOUTH);

        background.y += background.height;
        background.height = rect.height - 2 - background.height;
        dc.GradientFillLinear(background, m_page_background_colour,
            m_page_background_gradient_colour, wxSOUTH);
    }

    {
        wxPoint border_points[8];
        border_points[0] = wxPoint(2, 0);
        border_points[1] = wxPoint(1, 1);
        border_points[2] = wxPoint(1, rect.height - 4);
        border_points[3] = wxPoint(3, rect.height - 2);
        border_points[4] = wxPoint(rect.width - 4, rect.height - 2);
        border_points[5] = wxPoint(rect.width - 2, rect.height - 4);
        border_points[6] = wxPoint(rect.width - 2, 1);
        border_points[7] = wxPoint(rect.width - 4, -1);

        dc.SetPen(m_page_border_pen);
        dc.DrawLines(sizeof(border_points)/sizeof(wxPoint), border_points, rect.x, rect.y);
    }
}

void wxRibbonMSWArtProvider::DrawScrollButton(
                        wxDC& dc,
                        wxWindow* WXUNUSED(wnd),
                        const wxRect& rect_,
                        long style)
{
    wxRect rect(rect_);

    if((style & wxRIBBON_SCROLL_BTN_FOR_MASK) == wxRIBBON_SCROLL_BTN_FOR_PAGE)
    {
        // Page scroll buttons do not have the luxury of rendering on top of anything
        // else, and their size includes some padding, hence the background painting
        // and size adjustment.
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.SetBrush(m_tab_ctrl_background_brush);
        dc.DrawRectangle(rect);
        dc.SetClippingRegion(rect);
        switch(style & wxRIBBON_SCROLL_BTN_DIRECTION_MASK)
        {
        case wxRIBBON_SCROLL_BTN_LEFT:
            rect.x++;
        case wxRIBBON_SCROLL_BTN_RIGHT:
            rect.y--;
            rect.width--;
            break;
        case wxRIBBON_SCROLL_BTN_UP:
            rect.x++;
            rect.y--;
            rect.width -= 2;
            rect.height++;
            break;
        case wxRIBBON_SCROLL_BTN_DOWN:
            rect.x++;
            rect.width -= 2;
            rect.height--;
            break;
        }
    }

    {
        wxRect background(rect);
        background.x++;
        background.y++;
        background.width -= 2;
        background.height -= 2;

        if(style & wxRIBBON_SCROLL_BTN_UP)
            background.height /= 2;
        else
            background.height /= 5;
        dc.GradientFillLinear(background, m_page_background_top_colour,
            m_page_background_top_gradient_colour, wxSOUTH);

        background.y += background.height;
        background.height = rect.height - 2 - background.height;
        dc.GradientFillLinear(background, m_page_background_colour,
            m_page_background_gradient_colour, wxSOUTH);
    }

    {
        wxPoint border_points[7];
        switch(style & wxRIBBON_SCROLL_BTN_DIRECTION_MASK)
        {
        case wxRIBBON_SCROLL_BTN_LEFT:
            border_points[0] = wxPoint(2, 0);
            border_points[1] = wxPoint(rect.width - 1, 0);
            border_points[2] = wxPoint(rect.width - 1, rect.height - 1);
            border_points[3] = wxPoint(2, rect.height - 1);
            border_points[4] = wxPoint(0, rect.height - 3);
            border_points[5] = wxPoint(0, 2);
            break;
        case wxRIBBON_SCROLL_BTN_RIGHT:
            border_points[0] = wxPoint(0, 0);
            border_points[1] = wxPoint(rect.width - 3, 0);
            border_points[2] = wxPoint(rect.width - 1, 2);
            border_points[3] = wxPoint(rect.width - 1, rect.height - 3);
            border_points[4] = wxPoint(rect.width - 3, rect.height - 1);
            border_points[5] = wxPoint(0, rect.height - 1);
            break;
        case wxRIBBON_SCROLL_BTN_UP:
            border_points[0] = wxPoint(2, 0);
            border_points[1] = wxPoint(rect.width - 3, 0);
            border_points[2] = wxPoint(rect.width - 1, 2);
            border_points[3] = wxPoint(rect.width - 1, rect.height - 1);
            border_points[4] = wxPoint(0, rect.height - 1);
            border_points[5] = wxPoint(0, 2);
            break;
        case wxRIBBON_SCROLL_BTN_DOWN:
            border_points[0] = wxPoint(0, 0);
            border_points[1] = wxPoint(rect.width - 1, 0);
            border_points[2] = wxPoint(rect.width - 1, rect.height - 3);
            border_points[3] = wxPoint(rect.width - 3, rect.height - 1);
            border_points[4] = wxPoint(2, rect.height - 1);
            border_points[5] = wxPoint(0, rect.height - 3);
            break;
        }
        border_points[6] = border_points[0];

        dc.SetPen(m_page_border_pen);
        dc.DrawLines(sizeof(border_points)/sizeof(wxPoint), border_points, rect.x, rect.y);
    }

    {
        // NB: Code for handling hovered/active state is temporary
        wxPoint arrow_points[3];
        switch(style & wxRIBBON_SCROLL_BTN_DIRECTION_MASK)
        {
        case wxRIBBON_SCROLL_BTN_LEFT:
            arrow_points[0] = wxPoint(rect.width / 2 - 2, rect.height / 2);
            if(style & wxRIBBON_SCROLL_BTN_ACTIVE)
                arrow_points[0].y += 1;
            arrow_points[1] = arrow_points[0] + wxPoint(3, -3);
            arrow_points[2] = arrow_points[0] + wxPoint(3,  3);
            break;
        case wxRIBBON_SCROLL_BTN_RIGHT:
            arrow_points[0] = wxPoint(rect.width / 2 + 2, rect.height / 2);
            if(style & wxRIBBON_SCROLL_BTN_ACTIVE)
                arrow_points[0].y += 1;
            arrow_points[1] = arrow_points[0] - wxPoint(3,  3);
            arrow_points[2] = arrow_points[0] - wxPoint(3, -3);
            break;
        case wxRIBBON_SCROLL_BTN_UP:
            arrow_points[0] = wxPoint(rect.width / 2, rect.height / 2 - 2);
            if(style & wxRIBBON_SCROLL_BTN_ACTIVE)
                arrow_points[0].y += 1;
            arrow_points[1] = arrow_points[0] + wxPoint( 3, 3);
            arrow_points[2] = arrow_points[0] + wxPoint(-3, 3);
            break;
        case wxRIBBON_SCROLL_BTN_DOWN:
            arrow_points[0] = wxPoint(rect.width / 2, rect.height / 2 + 2);
            if(style & wxRIBBON_SCROLL_BTN_ACTIVE)
                arrow_points[0].y += 1;
            arrow_points[1] = arrow_points[0] - wxPoint( 3, 3);
            arrow_points[2] = arrow_points[0] - wxPoint(-3, 3);
            break;
        }

        dc.SetPen(*wxTRANSPARENT_PEN);
        wxBrush B(style & wxRIBBON_SCROLL_BTN_HOVERED ? m_tab_active_background_colour : m_tab_label_colour);
        dc.SetBrush(B);
        dc.DrawPolygon(sizeof(arrow_points)/sizeof(wxPoint), arrow_points, rect.x, rect.y);
    }
}

void wxRibbonMSWArtProvider::DrawDropdownArrow(wxDC& dc, int x, int y, const wxColour& colour)
{
    wxPoint arrow_points[3];
    wxBrush brush(colour);
    arrow_points[0] = wxPoint(1, 2);
    arrow_points[1] = arrow_points[0] + wxPoint(-3, -3);
    arrow_points[2] = arrow_points[0] + wxPoint( 3, -3);
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(brush);
    dc.DrawPolygon(sizeof(arrow_points)/sizeof(wxPoint), arrow_points, x, y);
}

void wxRibbonMSWArtProvider::RemovePanelPadding(wxRect* rect)
{
    if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
    {
        rect->y += 1;
        rect->height -= 2;
    }
    else
    {
        rect->x += 1;
        rect->width -= 2;
    }
}

void wxRibbonMSWArtProvider::DrawPanelBackground(
                        wxDC& dc,
                        wxRibbonPanel* wnd,
                        const wxRect& rect)
{
    DrawPartialPageBackground(dc, wnd, rect, false);

    wxRect true_rect(rect);
    RemovePanelPadding(&true_rect);

    int label_height;
    {
        dc.SetFont(m_panel_label_font);
        dc.SetPen(*wxTRANSPARENT_PEN);
        if(wnd->IsHovered())
        {
            dc.SetBrush(m_panel_hover_label_background_brush);
            dc.SetTextForeground(m_panel_hover_label_colour);
        }
        else
        {
            dc.SetBrush(m_panel_label_background_brush);
            dc.SetTextForeground(m_panel_label_colour);
        }

        wxRect label_rect(true_rect);
        wxString label = wnd->GetLabel();
        bool clip_label = false;
        wxSize label_size(dc.GetTextExtent(label));

        label_rect.SetX(label_rect.GetX() + 1);
        label_rect.SetWidth(label_rect.GetWidth() - 2);
        label_rect.SetHeight(label_size.GetHeight() + 2);
        label_rect.SetY(true_rect.GetBottom() - label_rect.GetHeight());
        label_height = label_rect.GetHeight();

        if(label_size.GetWidth() > label_rect.GetWidth())
        {
            // Test if there is enough length for 3 letters and ...
            wxString new_label = label.Mid(0, 3) + wxT("...");
            label_size = dc.GetTextExtent(new_label);
            if(label_size.GetWidth() > label_rect.GetWidth())
            {
                // Not enough room for three characters and ...
                // Display the entire label and just crop it
                clip_label = true;
            }
            else
            {
                // Room for some characters and ...
                // Display as many characters as possible and append ...
                for(size_t len = label.Len() - 1; len >= 3; --len)
                {
                    new_label = label.Mid(0, len) + wxT("...");
                    label_size = dc.GetTextExtent(new_label);
                    if(label_size.GetWidth() <= label_rect.GetWidth())
                    {
                        label = new_label;
                        break;
                    }
                }
            }
        }

        dc.DrawRectangle(label_rect.GetX(), label_rect.GetY(), label_rect.GetWidth(), label_rect.GetHeight());
        if(clip_label)
        {
            wxDCClipper clip(dc, label_rect);
            dc.DrawText(label, label_rect.x, label_rect.y +
                (label_rect.GetHeight() - label_size.GetHeight()) / 2);
        }
        else
        {
            dc.DrawText(label, label_rect.x +
                (label_rect.GetWidth() - label_size.GetWidth()) / 2,
                label_rect.y +
                (label_rect.GetHeight() - label_size.GetHeight()) / 2);
        }
    }

    if(wnd->IsHovered())
    {
        wxRect client_rect(true_rect);
        client_rect.x++;
        client_rect.width -= 2;
        client_rect.y++;
        client_rect.height -= 2 + label_height;
        DrawPartialPageBackground(dc, wnd, client_rect, true);
    }

    DrawPanelBorder(dc, true_rect, m_panel_border_pen, m_panel_border_gradient_pen);
}

void wxRibbonMSWArtProvider::DrawGalleryBackground(
                        wxDC& dc,
                        wxRibbonGallery* wnd,
                        const wxRect& rect)
{
    DrawPartialPageBackground(dc, wnd, rect);

    if(wnd->IsHovered())
    {
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.SetBrush(m_gallery_hover_background_brush);
        if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
        {
            dc.DrawRectangle(rect.x + 1, rect.y + 1, rect.width - 2,
                rect.height - 16);
        }
        else
        {
            dc.DrawRectangle(rect.x + 1, rect.y + 1, rect.width - 16,
                rect.height - 2);
        }
    }

    dc.SetPen(m_gallery_border_pen);
    // Outline
    dc.DrawLine(rect.x + 1, rect.y, rect.x + rect.width - 1, rect.y);
    dc.DrawLine(rect.x, rect.y + 1, rect.x, rect.y + rect.height - 1);
    dc.DrawLine(rect.x + 1, rect.y + rect.height - 1, rect.x + rect.width - 1,
        rect.y + rect.height - 1);
    dc.DrawLine(rect.x + rect.width - 1, rect.y + 1, rect.x + rect.width - 1,
        rect.y + rect.height - 1);

    DrawGalleryBackgroundCommon(dc, wnd, rect);
}

void wxRibbonMSWArtProvider::DrawGalleryBackgroundCommon(wxDC& dc,
                        wxRibbonGallery* wnd,
                        const wxRect& rect)
{
    wxRect up_btn, down_btn, ext_btn;

    if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
    {
        // Divider between items and buttons
        dc.DrawLine(rect.x, rect.y + rect.height - 15, rect.x + rect.width,
            rect.y + rect.height - 15);

        up_btn = wxRect(rect.x, rect.y + rect.height - 15, rect.width / 3, 15);

        down_btn = wxRect(up_btn.GetRight() + 1, up_btn.GetTop(),
            up_btn.GetWidth(), up_btn.GetHeight());
        dc.DrawLine(down_btn.GetLeft(), down_btn.GetTop(), down_btn.GetLeft(),
            down_btn.GetBottom());

        ext_btn = wxRect(down_btn.GetRight() + 1, up_btn.GetTop(), rect.width -
            up_btn.GetWidth() - down_btn.GetWidth() - 1, up_btn.GetHeight());
        dc.DrawLine(ext_btn.GetLeft(), ext_btn.GetTop(), ext_btn.GetLeft(),
            ext_btn.GetBottom());
    }
    else
    {
        // Divider between items and buttons
        dc.DrawLine(rect.x + rect.width - 15, rect.y, rect.x + rect.width - 15,
            rect.y + rect.height);

        up_btn = wxRect(rect.x + rect.width - 15, rect.y, 15, rect.height / 3);

        down_btn = wxRect(up_btn.GetLeft(), up_btn.GetBottom() + 1,
            up_btn.GetWidth(), up_btn.GetHeight());
        dc.DrawLine(down_btn.GetLeft(), down_btn.GetTop(), down_btn.GetRight(),
            down_btn.GetTop());

        ext_btn = wxRect(up_btn.GetLeft(), down_btn.GetBottom() + 1, up_btn.GetWidth(),
            rect.height - up_btn.GetHeight() - down_btn.GetHeight() - 1);
        dc.DrawLine(ext_btn.GetLeft(), ext_btn.GetTop(), ext_btn.GetRight(),
            ext_btn.GetTop());
    }

    DrawGalleryButton(dc, up_btn, wnd->GetUpButtonState(),
        m_gallery_up_bitmap);
    DrawGalleryButton(dc, down_btn, wnd->GetDownButtonState(),
        m_gallery_down_bitmap);
    DrawGalleryButton(dc, ext_btn, wnd->GetExtensionButtonState(),
        m_gallery_extension_bitmap);
}

void wxRibbonMSWArtProvider::DrawGalleryButton(wxDC& dc,
                                            wxRect rect,
                                            wxRibbonGalleryButtonState state,
                                            wxBitmap* bitmaps)
{
    wxBitmap btn_bitmap;
    wxBrush btn_top_brush;
    wxColour btn_colour;
    wxColour btn_grad_colour;
    switch(state)
    {
    case wxRIBBON_GALLERY_BUTTON_NORMAL:
        btn_top_brush = m_gallery_button_background_top_brush;
        btn_colour = m_gallery_button_background_colour;
        btn_grad_colour = m_gallery_button_background_gradient_colour;
        btn_bitmap = bitmaps[0];
        break;
    case wxRIBBON_GALLERY_BUTTON_HOVERED:
        btn_top_brush = m_gallery_button_hover_background_top_brush;
        btn_colour = m_gallery_button_hover_background_colour;
        btn_grad_colour = m_gallery_button_hover_background_gradient_colour;
        btn_bitmap = bitmaps[1];
        break;
    case wxRIBBON_GALLERY_BUTTON_ACTIVE:
        btn_top_brush = m_gallery_button_active_background_top_brush;
        btn_colour = m_gallery_button_active_background_colour;
        btn_grad_colour = m_gallery_button_active_background_gradient_colour;
        btn_bitmap = bitmaps[2];
        break;
    case wxRIBBON_GALLERY_BUTTON_DISABLED:
        btn_top_brush = m_gallery_button_disabled_background_top_brush;
        btn_colour = m_gallery_button_disabled_background_colour;
        btn_grad_colour = m_gallery_button_disabled_background_gradient_colour;
        btn_bitmap = bitmaps[3];
        break;
    }

    rect.x++;
    rect.y++;
    if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
    {
        rect.width--;;
        rect.height -= 2;
    }
    else
    {
        rect.width -= 2;
        rect.height--;
    }

    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(btn_top_brush);
    dc.DrawRectangle(rect.x, rect.y, rect.width, rect.height / 2);

    wxRect lower(rect);
    lower.height = (lower.height + 1) / 2;
    lower.y += rect.height - lower.height;
    dc.GradientFillLinear(lower, btn_colour, btn_grad_colour, wxSOUTH);

    dc.DrawBitmap(btn_bitmap, rect.x + rect.width / 2 - 2, lower.y - 2, true);
}

void wxRibbonMSWArtProvider::DrawGalleryItemBackground(
                        wxDC& dc,
                        wxRibbonGallery* wnd,
                        const wxRect& rect,
                        wxRibbonGalleryItem* item)
{
    if(wnd->GetHoveredItem() != item && wnd->GetActiveItem() != item &&
        wnd->GetSelection() != item)
        return;

    dc.SetPen(m_gallery_item_border_pen);
    dc.DrawLine(rect.x + 1, rect.y, rect.x + rect.width - 1, rect.y);
    dc.DrawLine(rect.x, rect.y + 1, rect.x, rect.y + rect.height - 1);
    dc.DrawLine(rect.x + 1, rect.y + rect.height - 1, rect.x + rect.width - 1,
        rect.y + rect.height - 1);
    dc.DrawLine(rect.x + rect.width - 1, rect.y + 1, rect.x + rect.width - 1,
        rect.y + rect.height - 1);

    wxBrush top_brush;
    wxColour bg_colour;
    wxColour bg_gradient_colour;

    if(wnd->GetActiveItem() == item || wnd->GetSelection() == item)
    {
        top_brush = m_gallery_button_active_background_top_brush;
        bg_colour = m_gallery_button_active_background_colour;
        bg_gradient_colour = m_gallery_button_active_background_gradient_colour;
    }
    else
    {
        top_brush = m_gallery_button_hover_background_top_brush;
        bg_colour = m_gallery_button_hover_background_colour;
        bg_gradient_colour = m_gallery_button_hover_background_gradient_colour;
    }

    wxRect upper(rect);
    upper.x += 1;
    upper.width -= 2;
    upper.y += 1;
    upper.height /= 3;
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(top_brush);
    dc.DrawRectangle(upper.x, upper.y, upper.width, upper.height);

    wxRect lower(upper);
    lower.y += lower.height;
    lower.height = rect.height - 2 - lower.height;
    dc.GradientFillLinear(lower, bg_colour, bg_gradient_colour, wxSOUTH);
}

void wxRibbonMSWArtProvider::DrawPanelBorder(wxDC& dc, const wxRect& rect,
                                             wxPen& primary_colour,
                                             wxPen& secondary_colour)
{
    wxPoint border_points[9];
    border_points[0] = wxPoint(2, 0);
    border_points[1] = wxPoint(rect.width - 3, 0);
    border_points[2] = wxPoint(rect.width - 1, 2);
    border_points[3] = wxPoint(rect.width - 1, rect.height - 3);
    border_points[4] = wxPoint(rect.width - 3, rect.height - 1);
    border_points[5] = wxPoint(2, rect.height - 1);
    border_points[6] = wxPoint(0, rect.height - 3);
    border_points[7] = wxPoint(0, 2);

    if(primary_colour.GetColour() == secondary_colour.GetColour())
    {
        border_points[8] = border_points[0];
        dc.SetPen(primary_colour);
        dc.DrawLines(sizeof(border_points)/sizeof(wxPoint), border_points, rect.x, rect.y);
    }
    else
    {
        dc.SetPen(primary_colour);
        dc.DrawLines(3, border_points, rect.x, rect.y);

#define SingleLine(start, finish) \
        dc.DrawLine(start.x + rect.x, start.y + rect.y, finish.x + rect.x, finish.y + rect.y)

        SingleLine(border_points[0], border_points[7]);
        dc.SetPen(secondary_colour);
        dc.DrawLines(3, border_points + 4, rect.x, rect.y);
        SingleLine(border_points[4], border_points[3]);

#undef SingleLine

        border_points[6] = border_points[2];
        wxRibbonDrawParallelGradientLines(dc, 2, border_points + 6, 0, 1,
            border_points[3].y - border_points[2].y + 1, rect.x, rect.y,
            primary_colour.GetColour(), secondary_colour.GetColour());
    }
}

void wxRibbonMSWArtProvider::DrawMinimisedPanel(
                        wxDC& dc,
                        wxRibbonPanel* wnd,
                        const wxRect& rect,
                        wxBitmap& bitmap)
{
    DrawPartialPageBackground(dc, wnd, rect, false);

    wxRect true_rect(rect);
    RemovePanelPadding(&true_rect);

    if(wnd->GetExpandedPanel() != NULL)
    {
        wxRect client_rect(true_rect);
        client_rect.x++;
        client_rect.width -= 2;
        client_rect.y++;
        client_rect.height = (rect.y + rect.height / 5) - client_rect.x;
        dc.GradientFillLinear(client_rect, 
            m_panel_active_background_top_colour,
            m_panel_active_background_top_gradient_colour, wxSOUTH);

        client_rect.y += client_rect.height;
        client_rect.height = (true_rect.y + true_rect.height) - client_rect.y;
        dc.GradientFillLinear(client_rect, 
            m_panel_active_background_colour,
            m_panel_active_background_gradient_colour, wxSOUTH);
    }
    else if(wnd->IsHovered())
    {
        wxRect client_rect(true_rect);
        client_rect.x++;
        client_rect.width -= 2;
        client_rect.y++;
        client_rect.height -= 2;
        DrawPartialPageBackground(dc, wnd, client_rect, true);
    }

    wxRect preview;
    DrawMinimisedPanelCommon(dc, wnd, true_rect, &preview);

    dc.SetBrush(m_panel_hover_label_background_brush);
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(preview.x + 1, preview.y + preview.height - 8,
        preview.width - 2, 7);

    int mid_pos = rect.y + rect.height / 5 - preview.y;
    if(mid_pos < 0 || mid_pos >= preview.height)
    {
        wxRect full_rect(preview);
        full_rect.x += 1;
        full_rect.y += 1;
        full_rect.width -= 2;
        full_rect.height -= 9;
        if(mid_pos < 0)
        {
            dc.GradientFillLinear(full_rect,
                m_page_hover_background_colour,
                m_page_hover_background_gradient_colour, wxSOUTH);
        }
        else
        {
            dc.GradientFillLinear(full_rect,
                m_page_hover_background_top_colour,
                m_page_hover_background_top_gradient_colour, wxSOUTH);
        }
    }
    else
    {
        wxRect top_rect(preview);
        top_rect.x += 1;
        top_rect.y += 1;
        top_rect.width -= 2;
        top_rect.height = mid_pos;
        dc.GradientFillLinear(top_rect,
            m_page_hover_background_top_colour,
            m_page_hover_background_top_gradient_colour, wxSOUTH);

        wxRect btm_rect(top_rect);
        btm_rect.y = preview.y + mid_pos;
        btm_rect.height = preview.y + preview.height - 7 - btm_rect.y;
        dc.GradientFillLinear(btm_rect,
            m_page_hover_background_colour,
            m_page_hover_background_gradient_colour, wxSOUTH);
    }

    if(bitmap.IsOk())
    {
        dc.DrawBitmap(bitmap, preview.x + (preview.width - bitmap.GetWidth()) / 2,
            preview.y + (preview.height - 7 - bitmap.GetHeight()) / 2, true);
    }

    DrawPanelBorder(dc, preview, m_panel_border_pen, m_panel_border_gradient_pen);

    DrawPanelBorder(dc, true_rect, m_panel_minimised_border_pen,
        m_panel_minimised_border_gradient_pen);
}

void wxRibbonMSWArtProvider::DrawMinimisedPanelCommon(
                        wxDC& dc,
                        wxRibbonPanel* wnd,
                        const wxRect& true_rect,
                        wxRect* preview_rect)
{
    wxRect preview(0, 0, 32, 32);
    if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
    {
        preview.x = true_rect.x + 4;
        preview.y = true_rect.y + (true_rect.height - preview.height) / 2;
    }
    else
    {
        preview.x = true_rect.x + (true_rect.width - preview.width) / 2;
        preview.y = true_rect.y + 4;
    }
    if(preview_rect)
        *preview_rect = preview;

    wxCoord label_width, label_height;
    dc.SetFont(m_panel_label_font);
    dc.GetTextExtent(wnd->GetLabel(), &label_width, &label_height);

    int xpos = true_rect.x + (true_rect.width - label_width + 1) / 2;
    int ypos = preview.y + preview.height + 5;

    if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
    {
        xpos = preview.x + preview.width + 5;
        ypos = true_rect.y + (true_rect.height - label_height) / 2;
    }

    dc.SetTextForeground(m_panel_minimised_label_colour);
    dc.DrawText(wnd->GetLabel(), xpos, ypos);
    

    wxPoint arrow_points[3];
    if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
    {
        xpos += label_width;
        arrow_points[0] = wxPoint(xpos + 5, ypos + label_height / 2);
        arrow_points[1] = arrow_points[0] + wxPoint(-3,  3);
        arrow_points[2] = arrow_points[0] + wxPoint(-3, -3);
    }
    else
    {
        ypos += label_height;
        arrow_points[0] = wxPoint(true_rect.width / 2, ypos + 5);
        arrow_points[1] = arrow_points[0] + wxPoint(-3, -3);
        arrow_points[2] = arrow_points[0] + wxPoint( 3, -3);
    }

    dc.SetPen(*wxTRANSPARENT_PEN);
    wxBrush B(m_panel_minimised_label_colour);
    dc.SetBrush(B);
    dc.DrawPolygon(sizeof(arrow_points)/sizeof(wxPoint), arrow_points,
        true_rect.x, true_rect.y);
}

void wxRibbonMSWArtProvider::DrawButtonBarBackground(
                        wxDC& dc,
                        wxWindow* wnd,
                        const wxRect& rect)
{
    DrawPartialPageBackground(dc, wnd, rect, true);
}

void wxRibbonMSWArtProvider::DrawPartialPageBackground(
                        wxDC& dc,
                        wxWindow* wnd,
                        const wxRect& rect,
                        bool allow_hovered)
{
    // Assume the window is a child of a ribbon page, and also check for a
    // hovered panel somewhere between the window and the page, as it causes
    // the background to change.
    wxPoint offset(wnd->GetPosition());
    wxRibbonPage* page = NULL;
    wxWindow* parent = wnd->GetParent();
    wxRibbonPanel* panel = NULL;
    bool hovered = false;

    panel = wxDynamicCast(wnd, wxRibbonPanel);
    if(panel != NULL)
    {
        hovered = allow_hovered && panel->IsHovered();
        if(panel->GetExpandedDummy() != NULL)
        {
            offset = panel->GetExpandedDummy()->GetPosition();
            parent = panel->GetExpandedDummy()->GetParent();
        }
    }
    for(; parent; parent = parent->GetParent())
    {
        if(panel == NULL)
        {
            panel = wxDynamicCast(parent, wxRibbonPanel);
            if(panel != NULL)
            {
                hovered = allow_hovered && panel->IsHovered();
                if(panel->GetExpandedDummy() != NULL)
                {
                    parent = panel->GetExpandedDummy();
                }
            }
        }
        page = wxDynamicCast(parent, wxRibbonPage);
        if(page != NULL)
        {
            break;
        }
        offset += parent->GetPosition();
    }
    if(page != NULL)
    {
        DrawPartialPageBackground(dc, wnd, rect, page, offset, hovered);
        return;
    }

    // No page found - fallback to painting with a stock brush
    dc.SetBrush(*wxWHITE_BRUSH);
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(rect.x, rect.y, rect.width, rect.height);
}

void wxRibbonMSWArtProvider::DrawButtonBarButton(
                        wxDC& dc,
                        wxWindow* WXUNUSED(wnd),
                        const wxRect& rect,
                        wxRibbonButtonKind kind,
                        long state,
                        const wxString& label,
                        const wxBitmap& bitmap_large,
                        const wxBitmap& bitmap_small)
{
    if(state & (wxRIBBON_BUTTONBAR_BUTTON_HOVER_MASK |
        wxRIBBON_BUTTONBAR_BUTTON_ACTIVE_MASK))
    {
        if(state & wxRIBBON_BUTTONBAR_BUTTON_ACTIVE_MASK)
            dc.SetPen(m_button_bar_active_border_pen);
        else
            dc.SetPen(m_button_bar_hover_border_pen);

        wxRect bg_rect(rect);
        bg_rect.x++;
        bg_rect.y++;
        bg_rect.width -= 2;
        bg_rect.height -= 2;

        wxRect bg_rect_top(bg_rect);
        bg_rect_top.height /= 3;
        bg_rect.y += bg_rect_top.height;
        bg_rect.height -= bg_rect_top.height;

        if(kind == wxRIBBON_BUTTON_HYBRID)
        {
            switch(state & wxRIBBON_BUTTONBAR_BUTTON_SIZE_MASK)
            {
            case wxRIBBON_BUTTONBAR_BUTTON_LARGE:
                {
                    int iYBorder = rect.y + bitmap_large.GetHeight() + 4;
                    wxRect partial_bg(rect);
                    if(state & wxRIBBON_BUTTONBAR_BUTTON_NORMAL_HOVERED)
                    {
                        partial_bg.SetBottom(iYBorder - 1);
                    }
                    else
                    {
                        partial_bg.height -= (iYBorder - partial_bg.y + 1);
                        partial_bg.y = iYBorder + 1;
                    }
                    dc.DrawLine(rect.x, iYBorder, rect.x + rect.width, iYBorder);
                    bg_rect.Intersect(partial_bg);
                    bg_rect_top.Intersect(partial_bg);
                }
                break;
            case wxRIBBON_BUTTONBAR_BUTTON_MEDIUM:
                {
                    int iArrowWidth = 9;
                    if(state & wxRIBBON_BUTTONBAR_BUTTON_NORMAL_HOVERED)
                    {
                        bg_rect.width -= iArrowWidth;
                        bg_rect_top.width -= iArrowWidth;
                        dc.DrawLine(bg_rect_top.x + bg_rect_top.width,
                            rect.y, bg_rect_top.x + bg_rect_top.width,
                            rect.y + rect.height);
                    }
                    else
                    {
                        --iArrowWidth;
                        bg_rect.x += bg_rect.width - iArrowWidth;
                        bg_rect_top.x += bg_rect_top.width - iArrowWidth;
                        bg_rect.width = iArrowWidth;
                        bg_rect_top.width = iArrowWidth;
                        dc.DrawLine(bg_rect_top.x - 1, rect.y,
                            bg_rect_top.x - 1, rect.y + rect.height);
                    }
                }
                break;
            case wxRIBBON_BUTTONBAR_BUTTON_SMALL:
                break;
            }
        }

        if(state & wxRIBBON_BUTTONBAR_BUTTON_ACTIVE_MASK)
        {
            dc.GradientFillLinear(bg_rect_top,
                m_button_bar_active_background_top_colour,
                m_button_bar_active_background_top_gradient_colour, wxSOUTH);
            dc.GradientFillLinear(bg_rect,
                m_button_bar_active_background_colour,
                m_button_bar_active_background_gradient_colour, wxSOUTH);
        }
        else
        {
            dc.GradientFillLinear(bg_rect_top,
                m_button_bar_hover_background_top_colour,
                m_button_bar_hover_background_top_gradient_colour, wxSOUTH);
            dc.GradientFillLinear(bg_rect,
                m_button_bar_hover_background_colour,
                m_button_bar_hover_background_gradient_colour, wxSOUTH);
        }

        wxPoint border_points[9];
        border_points[0] = wxPoint(2, 0);
        border_points[1] = wxPoint(rect.width - 3, 0);
        border_points[2] = wxPoint(rect.width - 1, 2);
        border_points[3] = wxPoint(rect.width - 1, rect.height - 3);
        border_points[4] = wxPoint(rect.width - 3, rect.height - 1);
        border_points[5] = wxPoint(2, rect.height - 1);
        border_points[6] = wxPoint(0, rect.height - 3);
        border_points[7] = wxPoint(0, 2);
        border_points[8] = border_points[0];

        dc.DrawLines(sizeof(border_points)/sizeof(wxPoint), border_points,
            rect.x, rect.y);
    }

    dc.SetFont(m_button_bar_label_font);
    dc.SetTextForeground(m_button_bar_label_colour);
    DrawButtonBarButtonForeground(dc, rect, kind, state, label, bitmap_large,
        bitmap_small);
}

void wxRibbonMSWArtProvider::DrawButtonBarButtonForeground(
                        wxDC& dc,
                        const wxRect& rect,
                        wxRibbonButtonKind kind,
                        long state,
                        const wxString& label,
                        const wxBitmap& bitmap_large,
                        const wxBitmap& bitmap_small)
{
    switch(state & wxRIBBON_BUTTONBAR_BUTTON_SIZE_MASK)
    {
    case wxRIBBON_BUTTONBAR_BUTTON_LARGE:
        {
            const int padding = 2;
            dc.DrawBitmap(bitmap_large,
                rect.x + (rect.width - bitmap_large.GetWidth()) / 2,
                rect.y + padding, true);
            int ypos = rect.y + padding + bitmap_large.GetHeight() + padding;
            int arrow_width = kind == wxRIBBON_BUTTON_NORMAL ? 0 : 8;
            wxCoord label_w, label_h;
            dc.GetTextExtent(label, &label_w, &label_h);
            if(label_w + 2 * padding <= rect.width)
            {
                dc.DrawText(label, rect.x + (rect.width - label_w) / 2, ypos);
                if(arrow_width != 0)
                {
                    DrawDropdownArrow(dc, rect.x + rect.width / 2,
                        ypos + (label_h * 3) / 2,
                        m_button_bar_label_colour);
                }
            }
            else
            {
                size_t breaki = label.Len();
                do
                {
                    --breaki;
                    if(wxRibbonCanLabelBreakAtPosition(label, breaki))
                    {
                        wxString label_top = label.Mid(0, breaki);
                        dc.GetTextExtent(label_top, &label_w, &label_h);
                        if(label_w + 2 * padding <= rect.width)
                        {
                            dc.DrawText(label_top,
                                rect.x + (rect.width - label_w) / 2, ypos);
                            ypos += label_h;
                            wxString label_bottom = label.Mid(breaki + 1);
                            dc.GetTextExtent(label_bottom, &label_w, &label_h);
                            label_w += arrow_width;
                            int iX = rect.x + (rect.width - label_w) / 2;
                            dc.DrawText(label_bottom, iX, ypos);
                            if(arrow_width != 0)
                            {
                                DrawDropdownArrow(dc, 
                                    iX + 2 +label_w - arrow_width,
                                    ypos + label_h / 2 + 1,
                                    m_button_bar_label_colour);
                            }
                            break;
                        }
                    }
                } while(breaki > 0);
            }
        }
        break;
    case wxRIBBON_BUTTONBAR_BUTTON_MEDIUM:
        {
            int x_cursor = rect.x + 2;
            dc.DrawBitmap(bitmap_small, x_cursor,
                    rect.y + (rect.height - bitmap_small.GetHeight())/2, true);
            x_cursor += bitmap_small.GetWidth() + 2;
            wxCoord label_w, label_h;
            dc.GetTextExtent(label, &label_w, &label_h);
            dc.DrawText(label, x_cursor,
                rect.y + (rect.height - label_h) / 2);
            x_cursor += label_w + 3;
            if(kind != wxRIBBON_BUTTON_NORMAL)
            {
                DrawDropdownArrow(dc, x_cursor, rect.y + rect.height / 2,
                    m_button_bar_label_colour);
            }
            break;
        }
    default:
        // TODO
        break;
    }
}

void wxRibbonMSWArtProvider::DrawToolBarBackground(
                        wxDC& dc,
                        wxWindow* wnd,
                        const wxRect& rect)
{
    DrawPartialPageBackground(dc, wnd, rect);
}

void wxRibbonMSWArtProvider::DrawToolGroupBackground(
                        wxDC& dc,
                        wxWindow* WXUNUSED(wnd),
                        const wxRect& rect)
{
    dc.SetPen(m_toolbar_border_pen);
    wxPoint outline[9];
    outline[0] = wxPoint(2, 0);
    outline[1] = wxPoint(rect.width - 3, 0);
    outline[2] = wxPoint(rect.width - 1, 2);
    outline[3] = wxPoint(rect.width - 1, rect.height - 3);
    outline[4] = wxPoint(rect.width - 3, rect.height - 1);
    outline[5] = wxPoint(2, rect.height - 1);
    outline[6] = wxPoint(0, rect.height - 3);
    outline[7] = wxPoint(0, 2);
    outline[8] = outline[0];

    dc.DrawLines(sizeof(outline)/sizeof(wxPoint), outline, rect.x, rect.y);
}

void wxRibbonMSWArtProvider::DrawTool(
                wxDC& dc,
                wxWindow* WXUNUSED(wnd),
                const wxRect& rect,
                const wxBitmap& bitmap,
                wxRibbonButtonKind kind,
                long state)
{
    wxRect bg_rect(rect);
    bg_rect.Deflate(1);
    if((state & wxRIBBON_TOOLBAR_TOOL_LAST) == 0)
        bg_rect.width++;
    bool is_split_hybrid = (kind == wxRIBBON_BUTTON_HYBRID && (state &
        (wxRIBBON_TOOLBAR_TOOL_HOVER_MASK | wxRIBBON_TOOLBAR_TOOL_ACTIVE_MASK)));

    // Background
    wxRect bg_rect_top(bg_rect);
    bg_rect_top.height = (bg_rect_top.height * 2) / 5;
    wxRect bg_rect_btm(bg_rect);
    bg_rect_btm.y += bg_rect_top.height;
    bg_rect_btm.height -= bg_rect_top.height;
    wxColour bg_top_colour = m_tool_background_top_colour;
    wxColour bg_top_grad_colour = m_tool_background_top_gradient_colour;
    wxColour bg_colour = m_tool_background_colour;
    wxColour bg_grad_colour = m_tool_background_gradient_colour;
    if(state & wxRIBBON_TOOLBAR_TOOL_ACTIVE_MASK)
    {
        bg_top_colour = m_tool_active_background_top_colour;
        bg_top_grad_colour = m_tool_active_background_top_gradient_colour;
        bg_colour = m_tool_active_background_colour;
        bg_grad_colour = m_tool_active_background_gradient_colour;
    }
    else if(state & wxRIBBON_TOOLBAR_TOOL_HOVER_MASK)
    {
        bg_top_colour = m_tool_hover_background_top_colour;
        bg_top_grad_colour = m_tool_hover_background_top_gradient_colour;
        bg_colour = m_tool_hover_background_colour;
        bg_grad_colour = m_tool_hover_background_gradient_colour;
    }
    dc.GradientFillLinear(bg_rect_top, bg_top_colour, bg_top_grad_colour, wxSOUTH);
    dc.GradientFillLinear(bg_rect_btm, bg_colour, bg_grad_colour, wxSOUTH);
    if(is_split_hybrid)
    {
        wxRect nonrect(bg_rect);
        if(state & (wxRIBBON_TOOLBAR_TOOL_DROPDOWN_HOVERED |
            wxRIBBON_TOOLBAR_TOOL_DROPDOWN_ACTIVE))
        {
            nonrect.width -= 8;
        }
        else
        {
            nonrect.x += nonrect.width - 8;
            nonrect.width = 8;
        }
        wxBrush B(m_tool_hover_background_top_colour);
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.SetBrush(B);
        dc.DrawRectangle(nonrect.x, nonrect.y, nonrect.width, nonrect.height);
    }
    
    // Border
    dc.SetPen(m_toolbar_border_pen);
    if(state & wxRIBBON_TOOLBAR_TOOL_FIRST)
    {
        dc.DrawPoint(rect.x + 1, rect.y + 1);
        dc.DrawPoint(rect.x + 1, rect.y + rect.height - 2);
    }
    else
        dc.DrawLine(rect.x, rect.y + 1, rect.x, rect.y + rect.height - 1);   

    if(state & wxRIBBON_TOOLBAR_TOOL_LAST)
    {
        dc.DrawPoint(rect.x + rect.width - 2, rect.y + 1);
        dc.DrawPoint(rect.x + rect.width - 2, rect.y + rect.height - 2);
    }

    // Foreground
    int avail_width = bg_rect.GetWidth();
    if(kind != wxRIBBON_BUTTON_NORMAL)
    {
        avail_width -= 8;
        if(is_split_hybrid)
        {
            dc.DrawLine(rect.x + avail_width + 1, rect.y, 
                rect.x + avail_width + 1, rect.y + rect.height);
        }
        dc.DrawBitmap(m_toolbar_drop_bitmap, bg_rect.x + avail_width + 2,
            bg_rect.y + (bg_rect.height / 2) - 2, true);
    }
    dc.DrawBitmap(bitmap, bg_rect.x + (avail_width - bitmap.GetWidth()) / 2,
        bg_rect.y + (bg_rect.height - bitmap.GetHeight()) / 2, true);
}

void wxRibbonMSWArtProvider::GetBarTabWidth(
                        wxDC& dc,
                        wxWindow* WXUNUSED(wnd),
                        const wxString& label,
                        const wxBitmap& bitmap,
                        int* ideal,
                        int* small_begin_need_separator,
                        int* small_must_have_separator,
                        int* minimum)
{
    int width = 0;
    int min = 0;
    if((m_flags & wxRIBBON_BAR_SHOW_PAGE_LABELS) && !label.IsEmpty())
    {
        dc.SetFont(m_tab_label_font);
        width += dc.GetTextExtent(label).GetWidth();
        min += wxMin(25, width); // enough for a few chars
        if(bitmap.IsOk())
        {
            // gap between label and bitmap
            width += 4;
            min += 2;
        }
    }
    if((m_flags & wxRIBBON_BAR_SHOW_PAGE_ICONS) && bitmap.IsOk())
    {
        width += bitmap.GetWidth();
        min += bitmap.GetWidth();
    }

    if(ideal != NULL)
    {
        *ideal = width + 30;
    }
    if(small_begin_need_separator != NULL)
    {
        *small_begin_need_separator = width + 20;
    }
    if(small_must_have_separator != NULL)
    {
        *small_must_have_separator = width + 10;
    }
    if(minimum != NULL)
    {
        *minimum = min;
    }
}

int wxRibbonMSWArtProvider::GetTabCtrlHeight(
                        wxDC& dc,
                        wxWindow* WXUNUSED(wnd),
                        const wxRibbonPageTabInfoArray& pages)
{
    int text_height = 0;
    int icon_height = 0;

    if(pages.GetCount() <= 1 && (m_flags & wxRIBBON_BAR_ALWAYS_SHOW_TABS) == 0)
    {
        // To preserve space, a single tab need not be displayed. We still need
        // two pixels of border / padding though.
        return 2;
    }

    if(m_flags & wxRIBBON_BAR_SHOW_PAGE_LABELS)
    {
        dc.SetFont(m_tab_label_font);
        text_height = dc.GetTextExtent(wxT("ABCDEFXj")).GetHeight() + 10;
    }
    if(m_flags & wxRIBBON_BAR_SHOW_PAGE_ICONS)
    {
        size_t numpages = pages.GetCount();
        for(size_t i = 0; i < numpages; ++i)
        {
            const wxRibbonPageTabInfo& info = pages.Item(i);
            if(info.page->GetIcon().IsOk())
            {
                icon_height = wxMax(icon_height, info.page->GetIcon().GetHeight() + 4);
            }
        }
    }

    return wxMax(text_height, icon_height);
}

wxSize wxRibbonMSWArtProvider::GetScrollButtonMinimumSize(
                        wxDC& WXUNUSED(dc),
                        wxWindow* WXUNUSED(wnd),
                        long WXUNUSED(style))
{
    return wxSize(12, 12);
}

wxSize wxRibbonMSWArtProvider::GetPanelSize(
                        wxDC& dc,
                        const wxRibbonPanel* wnd,
                        wxSize client_size,
                        wxPoint* client_offset)
{
    dc.SetFont(m_panel_label_font);
    wxSize label_size = dc.GetTextExtent(wnd->GetLabel());

    client_size.IncBy(0, label_size.GetHeight());
    if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
        client_size.IncBy(4, 8);
    else
        client_size.IncBy(6, 6);

    if(client_offset != NULL)
    {
        if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
            *client_offset = wxPoint(2, 3);
        else
            *client_offset = wxPoint(3, 2);
    }

    return client_size;
}

wxSize wxRibbonMSWArtProvider::GetPanelClientSize(
                        wxDC& dc,
                        const wxRibbonPanel* wnd,
                        wxSize size,
                        wxPoint* client_offset)
{
    dc.SetFont(m_panel_label_font);
    wxSize label_size = dc.GetTextExtent(wnd->GetLabel());

    size.DecBy(0, label_size.GetHeight());
    if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
        size.DecBy(4, 8);
    else
        size.DecBy(6, 6);

    if(client_offset != NULL)
    {
        if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
            *client_offset = wxPoint(2, 3);
        else
            *client_offset = wxPoint(3, 2);
    }

    return size;
}

wxSize wxRibbonMSWArtProvider::GetGallerySize(
                        wxDC& WXUNUSED(dc),
                        const wxRibbonGallery* WXUNUSED(wnd),
                        wxSize client_size)
{
    client_size.IncBy( 2, 1); // Left / top padding
    if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
        client_size.IncBy(1, 16); // Right / bottom padding
    else
        client_size.IncBy(16, 1); // Right / bottom padding
    return client_size;
}

wxSize wxRibbonMSWArtProvider::GetGalleryClientSize(
                        wxDC& WXUNUSED(dc),
                        const wxRibbonGallery* WXUNUSED(wnd),
                        wxSize size,
                        wxPoint* client_offset,
                        wxRect* scroll_up_button,
                        wxRect* scroll_down_button,
                        wxRect* extension_button)
{
    wxRect scroll_up;
    wxRect scroll_down;
    wxRect extension;
    if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
    {
        // Flow is vertical - put buttons on bottom
        scroll_up.y = size.GetHeight() - 15;
        scroll_up.height = 15;
        scroll_up.x = 0;
        scroll_up.width = (size.GetWidth() + 2) / 3;
        scroll_down.y = scroll_up.y;
        scroll_down.height = scroll_up.height;
        scroll_down.x = scroll_up.x + scroll_up.width;
        scroll_down.width = scroll_up.width;        
        extension.y = scroll_down.y;
        extension.height = scroll_down.height;
        extension.x = scroll_down.x + scroll_down.width;
        extension.width = size.GetWidth() - scroll_up.width - scroll_down.width;
        size.DecBy(1, 16);
        size.DecBy( 2, 1);
    }
    else
    {
        // Flow is horizontal - put buttons on right
        scroll_up.x = size.GetWidth() - 15;
        scroll_up.width = 15;
        scroll_up.y = 0;
        scroll_up.height = (size.GetHeight() + 2) / 3;
        scroll_down.x = scroll_up.x;
        scroll_down.width = scroll_up.width;
        scroll_down.y = scroll_up.y + scroll_up.height;
        scroll_down.height = scroll_up.height;        
        extension.x = scroll_down.x;
        extension.width = scroll_down.width;
        extension.y = scroll_down.y + scroll_down.height;
        extension.height = size.GetHeight() - scroll_up.height - scroll_down.height;
        size.DecBy(16, 1);
        size.DecBy( 2, 1);
    }
    
    if(client_offset != NULL)
        *client_offset = wxPoint(2, 1);
    if(scroll_up_button != NULL)
        *scroll_up_button = scroll_up;
    if(scroll_down_button != NULL)
        *scroll_down_button = scroll_down;
    if(extension_button != NULL)
        *extension_button = extension;

    return size;
}

wxRect wxRibbonMSWArtProvider::GetPageBackgroundRedrawArea(
                        wxDC& WXUNUSED(dc),
                        const wxRibbonPage* WXUNUSED(wnd),
                        wxSize page_old_size,
                        wxSize page_new_size)
{
    wxRect new_rect, old_rect;

    if(page_new_size.GetWidth() != page_old_size.GetWidth())
    {
        if(page_new_size.GetHeight() != page_old_size.GetHeight())
        {
            // Width and height both changed - redraw everything
            return wxRect(page_new_size);
        }
        else
        {
            // Only width changed - redraw right hand side
            const int right_edge_width = 4;

            new_rect = wxRect(page_new_size.GetWidth() - right_edge_width, 0, right_edge_width, page_new_size.GetHeight());
            old_rect = wxRect(page_old_size.GetWidth() - right_edge_width, 0, right_edge_width, page_old_size.GetHeight());
        }
    }
    else
    {
        if(page_new_size.GetHeight() == page_old_size.GetHeight())
        {
            // Nothing changed (should never happen) - redraw nothing
            return wxRect(0, 0, 0, 0);
        }
        else
        {
            // Height changed - need to redraw everything (as the background
            // gradient is done vertically).
            return page_new_size;
        }
    }

    new_rect.Union(old_rect);
    new_rect.Intersect(wxRect(page_new_size));
    return new_rect;
}

bool wxRibbonMSWArtProvider::GetButtonBarButtonSize(
                        wxDC& dc,
                        wxWindow* wnd,
                        wxRibbonButtonKind kind,
                        wxRibbonButtonBarButtonState size,
                        const wxString& label,
                        wxSize bitmap_size_large,
                        wxSize bitmap_size_small,
                        wxSize* button_size,
                        wxRect* normal_region,
                        wxRect* dropdown_region)
{
    const int drop_button_width = 8;

    dc.SetFont(m_button_bar_label_font);
    switch(size & wxRIBBON_BUTTONBAR_BUTTON_SIZE_MASK)
    {
    case wxRIBBON_BUTTONBAR_BUTTON_SMALL:
        // Small bitmap, no label
        *button_size = bitmap_size_small + wxSize(6, 4);
        switch(kind)
        {
        case wxRIBBON_BUTTON_NORMAL:
            *normal_region = wxRect(*button_size);
            *dropdown_region = wxRect(0, 0, 0, 0);
            break;
        case wxRIBBON_BUTTON_DROPDOWN:
            *button_size += wxSize(drop_button_width, 0);
            *dropdown_region = wxRect(*button_size);
            *normal_region = wxRect(0, 0, 0, 0);
            break;
        case wxRIBBON_BUTTON_HYBRID:
            *normal_region = wxRect(*button_size);
            *dropdown_region = wxRect(button_size->GetWidth(), 0,
                drop_button_width, button_size->GetHeight());
            *button_size += wxSize(drop_button_width, 0);
            break;
        }
        break;
    case wxRIBBON_BUTTONBAR_BUTTON_MEDIUM:
        // Small bitmap, with label to the right
        {
            GetButtonBarButtonSize(dc, wnd, kind, wxRIBBON_BUTTONBAR_BUTTON_SMALL,
                label, bitmap_size_large, bitmap_size_small, button_size,
                normal_region, dropdown_region);
            int text_size = dc.GetTextExtent(label).GetWidth();
            button_size->SetWidth(button_size->GetWidth() + text_size);
            switch(kind)
            {
            case wxRIBBON_BUTTON_DROPDOWN:
                dropdown_region->SetWidth(dropdown_region->GetWidth() + text_size);
                break;
            case wxRIBBON_BUTTON_HYBRID:
                dropdown_region->SetX(dropdown_region->GetX() + text_size);
                // no break
            case wxRIBBON_BUTTON_NORMAL:
                normal_region->SetWidth(normal_region->GetWidth() + text_size);
                break;
            }
            break;
        }
    case wxRIBBON_BUTTONBAR_BUTTON_LARGE:
        // Large bitmap, with label below (possibly split over 2 lines)
        {
            wxSize icon_size(bitmap_size_large);
            icon_size += wxSize(4, 4);
            wxCoord label_height;
            wxCoord best_width;
            dc.GetTextExtent(label, &best_width, &label_height);
            int best_num_lines = 1;
            int last_line_extra_width = 0;
            if(kind != wxRIBBON_BUTTON_NORMAL)
            {
                last_line_extra_width += 8;
                best_num_lines = 2; // label on top line, button below
            }
            size_t i;
            for(i = 0; i < label.Len(); ++i)
            {
                if(wxRibbonCanLabelBreakAtPosition(label, i))
                {
                    int width = wxMax(
                        dc.GetTextExtent(label.Mid(0, i - 1)).GetWidth(),
                        dc.GetTextExtent(label.Mid(i + 1)).GetWidth() + last_line_extra_width);
                    if(width < best_width)
                    {
                        best_width = width;
                        best_num_lines = 2;
                    }
                }
            }
            label_height *= 2; // Assume two lines even when only one is used
                               // (to give all buttons a consistent height)
            icon_size.SetWidth(wxMax(icon_size.GetWidth(), best_width) + 6);
            icon_size.SetHeight(icon_size.GetHeight() + label_height);
            *button_size = icon_size;
            switch(kind)
            {
            case wxRIBBON_BUTTON_DROPDOWN:
                *dropdown_region = wxRect(icon_size);
                break;
            case wxRIBBON_BUTTON_HYBRID:
                *normal_region = wxRect(icon_size);
                normal_region->height -= 2 + label_height;
                dropdown_region->x = 0;
                dropdown_region->y = normal_region->height;
                dropdown_region->width = icon_size.GetWidth();
                dropdown_region->height = icon_size.GetHeight() - normal_region->height;
                break;
            case wxRIBBON_BUTTON_NORMAL:
                *normal_region = wxRect(icon_size);
                break;
            }
            break;
        }
    };
    return true;
}

wxSize wxRibbonMSWArtProvider::GetMinimisedPanelMinimumSize(
                        wxDC& dc,
                        const wxRibbonPanel* wnd,
                        wxSize* desired_bitmap_size,
                        wxDirection* expanded_panel_direction)
{
    if(desired_bitmap_size != NULL)
    {
        *desired_bitmap_size = wxSize(16, 16);
    }
    if(expanded_panel_direction != NULL)
    {
        if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
            *expanded_panel_direction = wxEAST;
        else
            *expanded_panel_direction = wxSOUTH;
    }
    wxSize base_size(42, 42);

    dc.SetFont(m_panel_label_font);
    wxSize label_size(dc.GetTextExtent(wnd->GetLabel()));
    label_size.IncBy(2, 2); // Allow for differences between this DC and a paint DC
    label_size.IncBy(6, 0); // Padding
    label_size.y *= 2; // Second line for dropdown button

    if(m_flags & wxRIBBON_BAR_FLOW_VERTICAL)
    {
        // Label alongside icon
        return wxSize(base_size.x + label_size.x,
            wxMax(base_size.y, label_size.y));
    }
    else
    {
        // Label beneath icon
        return wxSize(wxMax(base_size.x, label_size.x),
            base_size.y + label_size.y);
    }
}

wxSize wxRibbonMSWArtProvider::GetToolSize(
                        wxDC& WXUNUSED(dc),
                        wxWindow* WXUNUSED(wnd),
                        wxSize bitmap_size,
                        wxRibbonButtonKind kind,
                        bool WXUNUSED(is_first),
                        bool is_last,
                        wxRect* dropdown_region)
{
    wxSize size(bitmap_size);
    size.IncBy(7, 6);
    if(is_last)
        size.IncBy(1, 0);
    if(kind != wxRIBBON_BUTTON_NORMAL)
    {
        size.IncBy(8, 0);
        if(dropdown_region)
        {
            if(kind == wxRIBBON_BUTTON_DROPDOWN)
                *dropdown_region = size;
            else
                *dropdown_region = wxRect(size.GetWidth() - 8, 0, 8, size.GetHeight());
        }
    }
    else
    {
        if(dropdown_region)
            *dropdown_region = wxRect(0, 0, 0, 0);
    }
    return size;
}

#endif // wxUSE_RIBBON


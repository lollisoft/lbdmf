///////////////////////////////////////////////////////////////////////////////
// Name:        wx/ribbon/control.h
// Purpose:     Extension of wxControl with common ribbon methods
// Author:      Peter Cawley
// Modified by:
// Created:     2009-06-05
// RCS-ID:      $Id: control.h,v 1.2.2.1 2025/04/05 16:16:41 lothar Exp $
// Copyright:   (C) Peter Cawley
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_RIBBON_CONTROL_H_
#define _WX_RIBBON_CONTROL_H_

#include "wx/defs.h"

#if wxUSE_RIBBON

#include "wx/control.h"
#include "wx/dynarray.h"

class wxRibbonArtProvider;

class WXDLLIMPEXP_RIBBON wxRibbonControl : public wxControl
{
public:
    wxRibbonControl() { m_art = NULL; }

    wxRibbonControl(wxWindow *parent, wxWindowID id,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize, long style = 0,
                    const wxValidator& validator = wxDefaultValidator,
                    const wxString& name = wxControlNameStr);

    virtual void SetArtProvider(wxRibbonArtProvider* art);
    wxRibbonArtProvider* GetArtProvider() const {return m_art;}

    virtual bool IsSizingContinuous() const {return true;}
    wxSize GetNextSmallerSize(wxOrientation direction, wxSize relative_to) const;
    wxSize GetNextLargerSize(wxOrientation direction, wxSize relative_to) const;
    wxSize GetNextSmallerSize(wxOrientation direction) const;
    wxSize GetNextLargerSize(wxOrientation direction) const;

    virtual bool Realize();
    bool Realise() {return Realize();}

protected:
    wxRibbonArtProvider* m_art;

    virtual wxSize DoGetNextSmallerSize(wxOrientation direction,
                                        wxSize relative_to) const;
    virtual wxSize DoGetNextLargerSize(wxOrientation direction,
                                       wxSize relative_to) const;

#ifndef SWIG
    DECLARE_CLASS(wxRibbonControl)
#endif
};

WX_DEFINE_USER_EXPORTED_ARRAY(wxRibbonControl*, wxArrayRibbonControl, class WXDLLIMPEXP_RIBBON);

#endif // wxUSE_RIBBON

#endif // _WX_RIBBON_CONTROL_H_

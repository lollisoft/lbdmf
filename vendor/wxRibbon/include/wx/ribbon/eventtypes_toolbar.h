#ifndef _WX_RIBBON_TOOLBAR_EVENT_TYPES_H_
#define _WX_RIBBON_TOOLBAR_EVENT_TYPES_H_

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EXPORTED_EVENT_TYPE(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONTOOL_CLICKED, 10)
	DECLARE_EXPORTED_EVENT_TYPE(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONTOOL_DROPDOWN_CLICKED, 11)
END_DECLARE_EVENT_TYPES()

#define wxDECLARE_EXPORTED_EVENT( expdecl, name, type ) \
   extern expdecl const wxEventType name

#define wxDEFINE_EVENT( expdecl, name, type ) \
   expdecl const wxEventType name( wxNewEventType() )

typedef void (wxEvtHandler::*wxRibbonToolBarEventFunction)(wxRibbonToolBarEvent&);

#define wxRibbonToolBarEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxRibbonToolBarEventFunction, &func)

#define EVT_RIBBONTOOLBAR_CLICKED(winid, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_RIBBONTOOL_CLICKED, winid, wxRibbonToolBarEventHandler(fn))
#define EVT_RIBBONTOOLBAR_DROPDOWN_CLICKED(winid, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_RIBBONTOOL_DROPDOWN_CLICKED, winid, wxRibbonToolBarEventHandler(fn))

#endif // _WX_RIBBON_TOOLBAR_EVENT_TYPES_H_
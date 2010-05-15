#ifndef _WX_RIBBON_BUTTONBAR_EVENT_TYPES_H_
#define _WX_RIBBON_BUTTONBAR_EVENT_TYPES_H_


BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EXPORTED_EVENT_TYPE(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, 0)   
	DECLARE_EXPORTED_EVENT_TYPE(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, 1)
END_DECLARE_EVENT_TYPES()

typedef void (wxEvtHandler::*wxRibbonButtonBarEventFunction) (wxRibbonButtonBarEvent&);

#define wxRibbonButtonBarEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxRibbonButtonBarEventFunction, &func)

#define EVT_RIBBONBUTTONBAR_CLICKED(winid, fn) \
   wx__DECLARE_EVT1(wxEVT_COMMAND_RIBBONBUTTON_CLICKED, winid, wxRibbonButtonBarEventHandler(fn))
#define EVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED(winid, fn) \
   wx__DECLARE_EVT1(wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, winid, wxRibbonButtonBarEventHandler(fn))

#define wxDECLARE_EXPORTED_EVENT( expdecl, name, type ) \
   expdecl const wxEventType name

#define wxDEFINE_EVENT( expdecl, name, type ) \
   expdecl const wxEventType name( wxNewEventType() )

#endif // _WX_RIBBON_BUTTONBAR_EVENT_TYPES_H_
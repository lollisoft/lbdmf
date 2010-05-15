#ifndef _WX_RIBBON_GALLERY_EVENT_TYPES_H_
#define _WX_RIBBON_GALLERY_EVENT_TYPES_H_

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EXPORTED_EVENT_TYPE(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONGALLERY_HOVER_CHANGED, 8)
	DECLARE_EXPORTED_EVENT_TYPE(WXDLLIMPEXP_RIBBON, wxEVT_COMMAND_RIBBONGALLERY_SELECTED, 9)
END_DECLARE_EVENT_TYPES()

#define wxDECLARE_EXPORTED_EVENT( expdecl, name, type ) \
   extern expdecl const wxEventType name

#define wxDEFINE_EVENT( expdecl, name, type ) \
   expdecl const wxEventType name( wxNewEventType() )

typedef void (wxEvtHandler::*wxRibbonGalleryEventFunction)(wxRibbonGalleryEvent&);

#define wxRibbonGalleryEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxRibbonGalleryEventFunction, &func)

#define EVT_RIBBONGALLERY_HOVER_CHANGED(winid, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_RIBBONGALLERY_HOVER_CHANGED, winid, wxRibbonGalleryEventHandler(fn))
#define EVT_RIBBONGALLERY_SELECTED(winid, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_RIBBONGALLERY_SELECTED, winid, wxRibbonGalleryEventHandler(fn))


#endif // _WX_RIBBON_GALLERY_EVENT_TYPES_H_
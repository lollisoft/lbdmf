
/* Base class for fixed database formular
 *  lbDMFManager
 */

#ifdef WINDOWS
#include <windows.h>
#include <io.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


//#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#ifndef OSX
#include <malloc.h>
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#include <lbConfigHook.h>
#include <lbInterfaces.h>

#undef DLLEXPORT

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif
#ifdef LINUX 
#define DLLEXPORT
#endif

#ifdef __GNUG__
#pragma implementation "plugin.cpp"
#pragma interface "plugin.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/wizard.h>
#include <wx/image.h>
#include <wx/textdlg.h>
#include <wx/filename.h>


#include <wx/wxsf/wxShapeFramework.h>


// Include base class definition
#include <wxSFDesignerBase.h>

// Begin implementation code

wxSFDesignerBase::wxSFDesignerBase() 
{
	_CL_LOG << "wxSFDesignerBase::wxSFDesignerBase() called." LOG_
	untranslated_formName = NULL;
	base_formName = NULL;
	noDataAvailable = false;
	_created = false;
	
	ToolMode = 0;
	REQUEST(getModuleInstance(), lb_I_String, toolgroupname)
	*toolgroupname = "Designer";

	REQUEST(getModuleInstance(), lb_I_String, toolmenuname)
	*toolmenuname = _trans("&Designer");
	
	REQUEST(getModuleInstance(), lb_I_String, LayoutMenuBaseName)
}

wxSFDesignerBase::~wxSFDesignerBase() {
	_CL_LOG << "wxSFDesignerBase::~wxSFDesignerBase() called." LOG_

	free (formName);
	free (base_formName);
	free (untranslated_formName);
}

lb_I_Unknown* LB_STDCALL wxSFDesignerBase::getUnknown() {
	char eventName[100] = "";
	lb_I_Unknown* ukp;
	lb_I_EventHandler* evHandler = (lb_I_EventHandler*) this;
	
	sprintf(eventName, "%p , and this is %p.", evHandler, this);
	_LOG << "wxSFDesignerBase::getUnknown() called. Instance of lb_I_EventHandler* is " << eventName LOG_
	
	queryInterface("lb_I_Unknown", (void**) &ukp, __FILE__, __LINE__);
	return ukp;
}

void LB_STDCALL wxSFDesignerBase::windowIsClosing(lb_I_Window* w) {
	_LOG << "wxSFDesignerBase::windowIsClosing() called." LOG_
}

lbErrCodes LB_STDCALL wxSFDesignerBase::registerBaseEventHandler(lb_I_Dispatcher* dispatcher) {
	char eventName[100] = "";
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev)

	lb_I_EventHandler* evHandler = (lb_I_EventHandler*) this;
	
	int temp;
	
	
	metaapp->addMenuBar(toolmenuname->charrep());
	metaapp->addToolBar(toolgroupname->charrep());
	
	sprintf(eventName, "%pModeSelect", evHandler);
	ev->registerEvent(eventName, temp);
	metaapp->addMenuEntry(toolmenuname->charrep(), "Design", eventName, "");
	metaapp->addToolBarButton(toolgroupname->charrep(), "Design", eventName, "mouse_cursor.png");
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &wxSFDesignerBase::lbSetSelectMode, eventName);
	
	sprintf(eventName, "%pLoadModel", evHandler);
	ev->registerEvent(eventName, temp);
	metaapp->addMenuEntry("File", "Design laden", eventName, "");
	metaapp->addToolBarButton("Main Toolbar", "Design laden", eventName, "document-open.png");
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &wxSFDesignerBase::lbLoadModel, eventName);
	
	sprintf(eventName, "%pSaveModel", evHandler);
	ev->registerEvent(eventName, temp);
	metaapp->addMenuEntry("File", "Design speichern", eventName, "");
	metaapp->addToolBarButton("Main Toolbar", "Design speichern", eventName, "document-save.png");
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &wxSFDesignerBase::lbSaveModel, eventName);
	
	
	wxArrayString arrLayouts = m_AutoLayout.GetRegisteredAlgorithms();

	sprintf(eventName, "%pModeLayout", evHandler);
	*LayoutMenuBaseName = eventName;


	metaapp->addMenuBar("Layout");

	for( size_t i = 0; i < arrLayouts.GetCount(); ++i )
	{
		sprintf(eventName, "%pModeLayout%s", evHandler, arrLayouts[i].c_str());
		ev->registerEvent(eventName, temp);
		metaapp->addMenuEntry("Layout", arrLayouts[i].c_str(), eventName, "");
		dispatcher->addEventHandlerFn(this, (lbEvHandler) &wxSFDesignerBase::lbSetAutoLayout, eventName);
	}
}

lbErrCodes LB_STDCALL wxSFDesignerBase::lbLoadModel(lb_I_Unknown* uk) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL wxSFDesignerBase::lbSaveModel(lb_I_Unknown* uk) {
	return ERR_NONE;
}


lbErrCodes LB_STDCALL wxSFDesignerBase::lbSetAutoLayout(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, reversedEvent)
	UAP(lb_I_Integer, eventID)
	QI(uk, lb_I_Integer, eventID)
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	char* eventName = (char*) strdup(eman->reverseEvent(eventID->getData()));
	
	*reversedEvent = eventName;
	free (eventName);
	
	reversedEvent->replace(LayoutMenuBaseName->charrep(), "");
	
	m_AutoLayout.Layout( this, reversedEvent->charrep() );
	SaveCanvasState();
	return ERR_NONE;
}

lbErrCodes LB_STDCALL wxSFDesignerBase::lbSetSelectMode(lb_I_Unknown* uk) {
	ToolMode = 0;
	return ERR_NONE;
}

char*	   LB_STDCALL wxSFDesignerBase::getFormName() { 
	return formName; 
}
char*	   LB_STDCALL wxSFDesignerBase::getName() { 
	return formName; 
}


lbErrCodes LB_STDCALL wxSFDesignerBase::addButton(const char* buttonText, const char* evHandler, int x, int y, int w, int h) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL wxSFDesignerBase::addLabel(const char* text, int x, int y, int w, int h) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL wxSFDesignerBase::addTextField(const char* name, int x, int y, int w, int h) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL wxSFDesignerBase::addOwnerDrawn(const char* name, int x, int y, int w, int h) {
	return ERR_NONE;
}

wxSFShapeBase* LB_STDCALL wxSFDesignerBase::createModelElement(wxSFGridShape *&pGrid, wxMouseEvent& event, const char* Text, const char* iconName) {
    wxSFShapeBase *pShape = NULL;

	// Used for subclassing
	if (pGrid == NULL)
		pShape = GetDiagramManager()->AddShape(CLASSINFO(wxSFFlexGridShape), event.GetPosition(), sfDONT_SAVE_STATE);
	else 
		pShape = pGrid;
	
	if(pShape)
	{
		pGrid = (wxSFGridShape*)pShape;
		
		// set visual style
		pGrid->SetFill(*wxTRANSPARENT_BRUSH);
		pGrid->SetBorder(wxPen(*wxBLACK, 1, wxDOT));
		pGrid->SetDimensions(2, 2);
		pGrid->AcceptChild(wxT("All"));
		pGrid->AcceptConnection(wxT("All"));
		pGrid->AcceptSrcNeighbour(wxT("All"));
		pGrid->AcceptTrgNeighbour(wxT("All"));
		
		pShape = GetDiagramManager()->AddShape(CLASSINFO(wxSFBitmapShape), event.GetPosition(), sfDONT_SAVE_STATE);
		
		// create relative path
		wxFileName path( iconName );
		path.MakeRelativeTo( wxGetCwd() );
		
		// create image from BMP file
		((wxSFBitmapShape*)pShape)->CreateFromFile( path.GetFullPath(), wxBITMAP_TYPE_PNG );
		
		// set shape policy
		pShape->AcceptConnection(wxT("All"));
		pShape->AcceptSrcNeighbour(wxT("All"));
		pShape->AcceptTrgNeighbour(wxT("All"));
		
		pGrid->InsertToGrid(0, 0, pShape);
		
		pShape = NULL;
		
		pShape = GetDiagramManager()->AddShape(CLASSINFO(wxSFEditTextShape), event.GetPosition(), sfDONT_SAVE_STATE);
		
		if(pShape)
		{
			((wxSFTextShape*)pShape)->SetText(Text);
			
			// set alignment
			pShape->SetVAlign(wxSFShapeBase::valignTOP);
			pShape->SetHAlign(wxSFShapeBase::halignCENTER);
			pShape->SetVBorder(10);
			
			// set shapes policy
			pShape->AcceptConnection(wxT("All"));
			pShape->AcceptSrcNeighbour(wxT("All"));
			pShape->AcceptTrgNeighbour(wxT("wxSFTextShape"));
			pShape->AcceptTrgNeighbour(wxT("wxSFEditTextShape"));
			
			pGrid->InsertToGrid(1, 1, pShape);
		}
		pGrid->Update();
	}
	return pShape;
}

void wxSFDesignerBase::OnMouseWheel(wxMouseEvent& event)
{
	// do default actions
	wxSFShapeCanvas::OnMouseWheel(event);
	
	SetScale(double(GetScale() * 50)/50);
	Refresh(false);
}

void wxSFDesignerBase::OnMouseMove(wxMouseEvent& event) {
	wxSFShapeBase* pShape = GetShapeUnderCursor();

	if (pShape != NULL && pShape->IsKindOf(CLASSINFO(wxSFGridShape)))
		wxSFShapeCanvas::OnMouseMove(event);

	if (pShape == NULL)
		wxSFShapeCanvas::OnMouseMove(event);
}

void wxSFDesignerBase::OnLeftDown(wxMouseEvent& event)
{
    wxSFShapeBase *pShape = NULL;
	wxSFGridShape *pGrid = NULL;
	
	switch(ToolMode)
	{
		case 1:
		{
			pShape = createModelElement(pGrid, event, "Name der Anwendung", "toolbarimages/kthememgr.png");
		}
			break;
		case 2:
		{
			pShape = createModelElement(pGrid, event, "Name des Formulars", "toolbarimages/kpersonalizer.png");
		}
			break;
		case 3:
		{
			// do default actions
			wxSFShapeBase* pShape = GetShapeUnderCursor();
			
			if (pShape != NULL && pShape->IsKindOf(CLASSINFO(wxSFGridShape))) {
				if(GetMode() == modeREADY)
				{
					StartInteractiveConnection(CLASSINFO(wxSFLineShape), event.GetPosition());
					// interactive connection can be created also from existing object for example
					// if some connection properties should be modified before the connection creation
					// process is started:
					//StartInteractiveConnection(new wxSFLineShape(), event.GetPosition());
				}
				else
					wxSFShapeCanvas::OnLeftDown(event);
			}
		}
			break;
		default:
			// do default actions
			wxSFShapeBase* pShape = GetShapeUnderCursor();
			
			if (pShape != NULL && (pShape->IsKindOf(CLASSINFO(wxSFGridShape)) || pShape->IsKindOf(CLASSINFO(wxSFLineShape))))
				wxSFShapeCanvas::OnLeftDown(event);
			
			if (pShape == NULL)
				wxSFShapeCanvas::OnLeftDown(event);
	}
	
	if( pShape )
	{
	    SaveCanvasState();
		
        pShape->Refresh();
		pGrid->Refresh();
	}
}

void wxSFDesignerBase::OnDispatch(wxCommandEvent& event ) {
        switch (event.GetId()) {
        default:
                // Delegate all other events
                {
                	lbErrCodes err = ERR_NONE;
					lb_I_Module* m = getModuleInstance();
			
					UAP_REQUEST(m, lb_I_EventManager, eman)
		
					UAP_REQUEST(m, lb_I_Dispatcher, dispatcher)
					dispatcher->setEventManager(eman.getPtr());

					UAP_REQUEST(m, lb_I_Integer, param)
			
					param->setData(event.GetId());
			
					UAP(lb_I_Unknown, uk)
					QI(param, lb_I_Unknown, uk)
		
					UAP_REQUEST(m, lb_I_String, result)
					UAP(lb_I_Unknown, uk_result)
					QI(result, lb_I_Unknown, uk_result)
		
					if (formName != NULL) {
						_LOG << "wxSFDesignerBase::OnDispatch(" << event.GetId() << ") called ('" << formName << "')" LOG_
					} else {
						_LOG << "wxSFDesignerBase::OnDispatch(" << event.GetId() << ") called ('" << getClassName() << "')" LOG_
					}
					dispatcher->dispatch(event.GetId(), uk.getPtr(), &uk_result);
                }
                break;
        }
}

void LB_STDCALL wxSFDesignerBase::destroy()
{
	if (_created) {
		_LOG << "lbDatabasePanel::destroy() Destroying '" << base_formName << "'" LOG_
		Destroy();
	}
	_created = false;
}

void LB_STDCALL wxSFDesignerBase::create(int parentId) {
	wxWindow* w = FindWindowById(parentId);
	
	Create(w, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "panel");
	SetFocus();
	_created = true;
}

lbErrCodes LB_STDCALL wxSFDesignerBase::setName(char const * name, char const * appention) {
	if (formName) free(formName);
	if (untranslated_formName) free(untranslated_formName);

	char* transl = _trans((char*) name);
		
	char* temp = (char*) malloc(strlen(transl)+1);
	temp[0] = 0;
	strcpy(temp, transl);

	if (appention) {
		formName = (char*) malloc(1+strlen(temp)+strlen(appention));
		
		base_formName = (char*) malloc(1+strlen(name));
		untranslated_formName = (char*) malloc(1+strlen(name)+strlen(appention));
	} else {
		formName = (char*) malloc(1+strlen(temp));
		
		base_formName = (char*) malloc(1+strlen(name));
		untranslated_formName = (char*) malloc(1+strlen(name));
	}
	
	formName[0] = 0;
	strcat(formName, temp);
	if (appention) strcat(formName, appention);
	free(temp);
		
	untranslated_formName[0] = 0;
	strcat(untranslated_formName, name);
	if (appention) strcat(untranslated_formName, appention);
		
	base_formName[0] = 0;
	strcat(base_formName, name);
		
	return ERR_NONE;
}

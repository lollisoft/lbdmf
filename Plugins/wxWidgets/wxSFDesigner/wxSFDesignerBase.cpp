
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

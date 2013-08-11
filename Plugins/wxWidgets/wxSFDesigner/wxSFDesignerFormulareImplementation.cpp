
/* Implementation class for fixed database formular
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
#pragma implementation "wxSFDesignerAnwendungenImplementation.cpp"
#pragma interface "wxSFDesignerAnwendungenImplementation.cpp"
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
#include <wxSFDesignerFormulareImplementation.h> 

#include <lbDMFFormularShape.h>
#include <lbDMFFormularFieldShape.h>


BEGIN_IMPLEMENT_LB_UNKNOWN(Formulare)
	ADD_INTERFACE(lb_I_Window)
	ADD_INTERFACE(lb_I_Form)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfFormulare, Formulare)

lbErrCodes LB_STDCALL Formulare::setData(lb_I_Unknown* uk) {
		lbErrCodes err = ERR_NONE;
		
        _CL_VERBOSE << "Formulare::setData(...) not implemented yet" LOG_

		UAP(lb_I_Form, dbForm)
		QI(uk, lb_I_Form, dbForm)
		
        return ERR_NOT_IMPLEMENTED;
}

Formulare::Formulare() 
{
	_CL_LOG << "Formulare::Formulare() called." LOG_
	formName = strdup("Formulare");
}

Formulare::~Formulare() {
	_CL_LOG << "Formulare::~Formulare() called." LOG_
}

lbErrCodes LB_STDCALL Formulare::registerEventHandler(lb_I_Dispatcher* dispatcher) {

	char eventName[100] = "";
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev)

	dispatcher->setEventManager(ev.getPtr());

	registerBaseEventHandler(dispatcher);
	
	lb_I_EventHandler* evHandler = (lb_I_EventHandler*) this;

	int temp;

	metaapp->addToolBar(toolgroupname->charrep());
		
	sprintf(eventName, "%pModeFormularField", evHandler);
	ev->registerEvent(eventName, temp);
	metaapp->addMenuEntry(toolmenuname->charrep(), "Neues Feld", eventName, "");
	metaapp->addToolBarButton(toolgroupname->charrep(), "Neues Feld", eventName, "formular_field.png");
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &Formulare::lbSetFormularFieldMode, eventName);
	
	
	sprintf(eventName, "%pModeFieldConnect", evHandler);
	ev->registerEvent(eventName, temp);
	metaapp->addMenuEntry(toolmenuname->charrep(), "Verbinde Formularfeld mit Formular", eventName, "");
	metaapp->addToolBarButton(toolgroupname->charrep(), "Verbinde Formularfeld mit Formular", eventName, "formular_field_connect.png");
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &Formulare::lbSetFormularFieldConnectMode, eventName);
	
	return ERR_NONE;
}


lbErrCodes LB_STDCALL Formulare::lbSetFormularFieldMode(lb_I_Unknown* uk) {
	ToolMode = 4;
	return ERR_NONE;
}

lbErrCodes LB_STDCALL Formulare::lbSetFormularFieldConnectMode(lb_I_Unknown* uk) {
	ToolMode = 5;
	return ERR_NONE;
}

lbErrCodes LB_STDCALL Formulare::lbMouseDown(lb_I_Unknown* uk) {
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL Formulare::lbMouseUp(lb_I_Unknown* uk) {
	
	return ERR_NONE;
}


// Formular init routine



// Initialization of the form via source code

void LB_STDCALL Formulare::init() {
	lbErrCodes err = ERR_NONE;
	char prefix[100] = "";
	sprintf(prefix, "%p", this);

	_LOG << "Formulare::init() called." LOG_
	
	currentDiagramManager = new wxSFDiagramManager();
	SetDiagramManager(currentDiagramManager);	

	GetDiagramManager()->ClearAcceptedShapes();
	GetDiagramManager()->AcceptShape(wxT("All"));
	GetHistoryManager().SetMode(wxSFCanvasHistory::histUSE_SERIALIZATION);
	SaveCanvasState();
	
	
	AddStyle(sfsGRID_USE);
	AddStyle(sfsGRID_SHOW);
	// distances between grid lines can be modified via following function:
	SetGridLineMult(10);
	// grid line style can be set as follows:
	SetGridStyle(wxSHORT_DASH);
	
	AddStyle(sfsPROCESS_MOUSEWHEEL);
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	
	registerEventHandler(*&dispatcher);
	
	// Start generating diagram from model data
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	UAP(lb_I_Unknown, apps)
	UAP(lb_I_Applications, applications)
	UAP(lb_I_Formulars, forms)
	UAP(lb_I_Formular_Fields, formularfields)

	UAP(lb_I_SecurityProvider, securityManager)
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	AQUIRE_PLUGIN(lb_I_SecurityProvider, Default, securityManager, "No security provider found.")
	
	apps = securityManager->getApplicationModel();
	QI(apps, lb_I_Applications, applications)

	UAP_REQUEST(getModuleInstance(), lb_I_String, param)
	UAP_REQUEST(getModuleInstance(), lb_I_Container, model)
	
	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, activedocument)
	ukDoc = meta->getActiveDocument();
	QI(ukDoc, lb_I_Parameter, activedocument)

	*param = "ApplicationData";
	model->setCloning(false);
	activedocument->getUAPContainer(*&param, *&model);	
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	QI(name, lb_I_KeyBase, key)


	*name = "Formulars";
	uk = model->getElement(&key);
	QI(uk, lb_I_Formulars, forms)

	*name = "FormularFields";
	uk = model->getElement(&key);
	QI(uk, lb_I_Formular_Fields, formularfields)

	int x_distance = 50;
	int y_distance = 50;
	
	int x_offset = 0;
	int y_offset = 0;
	
	forms->finishIteration();
	while (forms->hasMoreElements()) {
		forms->setNextElement();
		
		wxSFShapeBase *pShape = NULL;
		pShape = GetDiagramManager()->AddShape(CLASSINFO(lbDMFFormularShape), wxPoint(x_distance+x_distance*x_offset, y_distance+y_distance*y_offset), sfDONT_SAVE_STATE);

		((lbDMFFormularShape*)pShape)->SetFormularName(wxString(forms->get_name()));
		
		pShape->Update();
		
		long FormID = forms->get_id();
		
		formularfields->finishIteration();
		while (formularfields->hasMoreElements()) {
			y_offset++;
			x_offset++;
		
			formularfields->setNextElement();
		
			if (FormID == formularfields->get_formularid()) {
				wxSFShapeBase *pFormFieldShape = NULL;
				pFormFieldShape = GetDiagramManager()->AddShape(CLASSINFO(lbDMFFormularFieldShape), wxPoint(x_distance+x_distance*x_offset, y_distance+y_distance*y_offset), sfDONT_SAVE_STATE);

				((lbDMFFormularFieldShape*)pFormFieldShape)->SetFormularFieldName(wxString(formularfields->get_name()));
			
				pFormFieldShape->Update();
			
				GetDiagramManager()->CreateConnection(pShape->GetId(), pFormFieldShape->GetId(), true);
			}
			
			x_offset--;
		}
	}
	
	m_AutoLayout.Layout( this, "Mesh" );
	m_AutoLayout.Layout( this, "HorizontalTree" );
	SaveCanvasState();

}

class lbPluginFormulare : public lb_I_PluginImpl {
public:
	lbPluginFormulare();
	
	virtual ~lbPluginFormulare();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace);

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukActions)
	UAP(lb_I_String, pluginNamespace)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormulare)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormulare, lbPluginFormulare)

lbErrCodes LB_STDCALL lbPluginFormulare::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormulare::setData(...) called.\n" LOG_

    return ERR_NOT_IMPLEMENTED;
}

lbPluginFormulare::lbPluginFormulare() {
	_CL_VERBOSE << "lbPluginFormulare::lbPluginFormulare() called.\n" LOG_
	REQUEST(getModuleInstance(), lb_I_String, pluginNamespace)
	*pluginNamespace = "Plugin namespace was not set.";
}

lbPluginFormulare::~lbPluginFormulare() {
	_CL_VERBOSE << "lbPluginFormulare::~lbPluginFormulare() called.\n" LOG_
}

void LB_STDCALL lbPluginFormulare::setNamespace(const char* _namespace) {
	*pluginNamespace = _namespace;
}

bool LB_STDCALL lbPluginFormulare::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormulare::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormulare::initialize() {
}
	
bool LB_STDCALL lbPluginFormulare::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormulare::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		Formulare* _Formulare = new Formulare();
	
		//_Formulare->setContextNamespace(pluginNamespace->charrep());

		QI(_Formulare, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE << "lbPluginFormulare::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormulare::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Formulare* _Formulare = new Formulare();
	
		//_Formulare->setContextNamespace(pluginNamespace->charrep());

		QI(_Formulare, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormulare::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}


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

#include <lbPropertyPanelHandler.h>

// Plugin module code

class lbPluginModulePropertyForm : public lb_I_PluginModule {
public:

	lbPluginModulePropertyForm();
	virtual ~lbPluginModulePropertyForm();

	DECLARE_LB_UNKNOWN()
	
	void LB_STDCALL initialize();
	void LB_STDCALL install();
	
	DECLARE_PLUGINS()
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModulePropertyForm)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModulePropertyForm)

BEGIN_PLUGINS(lbPluginModulePropertyForm)

	ADD_PLUGIN(lbPluginPropertyPanelHandler, PropertyPanel)

END_PLUGINS()

lbPluginModulePropertyForm::lbPluginModulePropertyForm() {
	_CL_VERBOSE << "lbPluginModulePropertyForm::lbPluginModulePropertyForm() called." LOG_
}

lbPluginModulePropertyForm::~lbPluginModulePropertyForm() {
	_CL_VERBOSE << "lbPluginModulePropertyForm::~lbPluginModulePropertyForm() called." LOG_
}

void LB_STDCALL lbPluginModulePropertyForm::install() {
}

void LB_STDCALL lbPluginModulePropertyForm::initialize() {
	lbErrCodes err = ERR_NONE;
	char ptr[20] = "";
	sprintf(ptr, "%p", this);

	enumPlugins();
}

lbErrCodes LB_STDCALL lbPluginModulePropertyForm::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginModulePropertyForm::setData(...) not implemented yet" LOG_

	if (uk != NULL) {
		_CL_VERBOSE << "Cloning object with " << uk->getRefCount() << " references." LOG_
	}
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/


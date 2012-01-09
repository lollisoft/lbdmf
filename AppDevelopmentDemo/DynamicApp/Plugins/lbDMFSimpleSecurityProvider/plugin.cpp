/*...sLicence:0:*/
/*


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
            Ginsterweg 4

            65760 Eschborn (germany)
*/
/*...e*/
/*...sincludes:0:*/
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

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
#ifndef DEBUG_MALLOC
#include <malloc.h>
#endif
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif


/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
/*...e*/

/*...e*/
/*...smisc and includes:0:*/
#ifdef __GNUG__
#pragma implementation "plugin.cpp"
#pragma interface "plugin.cpp"
#endif

/*...e*/

/*...sclass lbPluginModuleTest:0:*/
class lbPluginModule : public lb_I_PluginModule {
public:

	lbPluginModule();
	virtual ~lbPluginModule();

	DECLARE_LB_UNKNOWN()

	void LB_STDCALL initialize();
	void LB_STDCALL install();

	DECLARE_PLUGINS()
};
/*...e*/

/*...sclass lbPluginModuleTest implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModule)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModule)

BEGIN_PLUGINS(lbPluginModule)
	// Project manager
	ADD_PLUGIN(lbPluginDMFSSP, Default)
END_PLUGINS()

lbPluginModule::lbPluginModule() {
	
	_LOGVERBOSE << "lbPluginModule::lbPluginModule() lbPluginDMFSSP with namespace Default called." LOG_
}

lbPluginModule::~lbPluginModule() {
	_LOGVERBOSE << "lbPluginModule::~lbPluginModule() lbPluginDMFSSP with namespace Default called." LOG_
}

// The failure code is not late binding the columns, thus a primary key
// later on seems not to get handled proper when I try to set it readonly.
//#define FAILURE_CODE

// The query does not cause the stack corrupption either failure or not
//#define FAILURE_QUERY

void LB_STDCALL lbPluginModule::initialize() {
	lbErrCodes err = ERR_NONE;

	_LOGVERBOSE << "lbPluginModule::initialize() lbPluginDMFSSP called." LOG_
	enumPlugins();
}

void LB_STDCALL lbPluginModule::install() {
}

lbErrCodes LB_STDCALL lbPluginModule::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginModule::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

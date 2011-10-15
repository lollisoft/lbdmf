/*...sLicence:0:*/
/*
 DMF Distributed Multiplatform Framework (the initial goal of this library)
 This file is part of lbDMF.
 Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
 
 The author of this work will be reached by e-Mail or paper mail.
 e-Mail: lothar.behrens@lollisoft.de
 p-Mail: See my current address on http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=6
 
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
#include <malloc.h>
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

/*...sclass lbPluginModuleXSLTTransformer:0:*/
class lbPluginModuleXSLTTransformer : public lb_I_PluginModule {
public:
	
	lbPluginModuleXSLTTransformer();
	virtual ~lbPluginModuleXSLTTransformer();
	
	DECLARE_LB_UNKNOWN()
	
	void LB_STDCALL initialize();
	void LB_STDCALL install();
	
	DECLARE_PLUGINS()
};
/*...e*/

/*...sclass lbPluginModuleVisitors implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModuleXSLTTransformer)
ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModuleXSLTTransformer)

BEGIN_PLUGINS(lbPluginModuleXSLTTransformer)
ADD_PLUGIN(lbPluginXSLTTransformer,			XMLTransformer)
END_PLUGINS()



lbPluginModuleXSLTTransformer::lbPluginModuleXSLTTransformer() {
	
}

lbPluginModuleXSLTTransformer::~lbPluginModuleXSLTTransformer() {
	_CL_VERBOSE << "lbPluginModuleXSLTTransformer::~lbPluginModuleXSLTTransformer() called." LOG_
}

void LB_STDCALL lbPluginModuleXSLTTransformer::initialize() {
	_CL_VERBOSE << "lbPluginModuleXSLTTransformer::initialize() called." LOG_
	enumPlugins();
}

void LB_STDCALL lbPluginModuleXSLTTransformer::install() {

}

lbErrCodes LB_STDCALL lbPluginModuleXSLTTransformer::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbPluginModuleXSLTTransformer::setData(...) not implemented yet" LOG_
	
	if (uk != NULL) {
		_CL_LOG << "Cloning object with " << uk->getRefCount() << " references." LOG_
	}
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

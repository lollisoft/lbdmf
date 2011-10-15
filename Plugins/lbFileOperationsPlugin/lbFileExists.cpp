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

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <stdio.h>
#include <string.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#ifdef __WATCOMC__
#include <direct.h>
#endif

#ifdef __MINGW32__
#include <direct.h>
#endif

#include <lbFileExists.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(lbFileExists)
ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

lbFileExists::lbFileExists() {
	
}

lbFileExists::~lbFileExists() {
	
}

lb_I_Unknown* lbFileExists::getUnknown() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, uk)
	
	QI(this, lb_I_Unknown, uk)
	
	return uk.getPtr();
}

lbErrCodes LB_STDCALL lbFileExists::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_LOG << "lbFileExists::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbFileExists::registerEventHandler(lb_I_Dispatcher* disp) {
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	int temp;
	eman->registerEvent("fileExists", temp);

	disp->addEventHandlerFn(this, (lbEvHandler) &lbFileExists::fileExists, "fileExists");
	disp->addEventHandlerFn(this, (lbEvHandler) &lbFileExists::directoryExists, "directoryExists");
}

lbErrCodes LB_STDCALL lbFileExists::fileExists(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, filename) // Where to write to
	UAP_REQUEST(getModuleInstance(), lb_I_String, result) // Result for activity
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramName) // Parameter name
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramResult) // Parameter name
	
	lbErrCodes err = ERR_NONE;

	// Default is failure
	*paramName = "result";
	*paramResult = "result";
	*result = "0";

	UAP(lb_I_Parameter, params)
	
	if (uk == NULL) {
		_LOG << "lbFileExists::fileExists() Did not got an object." LOG_
		params->setUAPString(*&paramName, *&result);
		return ERR_PARAMETER_MISSING;
	}
	
	QI(uk, lb_I_Parameter, params)
	
	if (params == NULL) {
		_LOG << "lbFileExists::fileExists() Parameter is not of type lb_I_Parameter." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_ILLEGAL_PARAMETER;
	}
	
	*paramName = "filename";
	if ((err = params->getUAPString(*&paramName, *&filename)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbFileExists::fileExists() Parameter 'filename' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbFileExists::fileExists() Parameter 'filename' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	if (!FileExists(filename->charrep())) {
		*result = "0";
		params->setUAPString(*&paramResult, *&result);
		return ERR_NONE;
	}
	
	*result = "1";
	params->setUAPString(*&paramResult, *&result);
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbFileExists::directoryExists(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, directoryname) // Where to write to
	UAP_REQUEST(getModuleInstance(), lb_I_String, result) // Result for activity
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramName) // Parameter name
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramResult) // Parameter name
			
	lbErrCodes err = ERR_NONE;
			
	// Default is failure
	*paramName = "result";
	*paramResult = "result";
	*result = "0";
			
	UAP(lb_I_Parameter, params)
			
	if (uk == NULL) {
		_LOG << "lbFileExists::fileExists() Did not got an object." LOG_
		params->setUAPString(*&paramName, *&result);
		return ERR_PARAMETER_MISSING;
	}
			
	QI(uk, lb_I_Parameter, params)
			
	if (params == NULL) {
		_LOG << "lbFileExists::fileExists() Parameter is not of type lb_I_Parameter." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_ILLEGAL_PARAMETER;
	}
			
	*paramName = "directoryname";
	if ((err = params->getUAPString(*&paramName, *&directoryname)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbFileExists::fileExists() Parameter 'directoryname' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
			
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbFileExists::fileExists() Parameter 'directoryname' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
			
	if (!DirectoryExists(directoryname->charrep())) {
		*result = "0";
		params->setUAPString(*&paramResult, *&result);
		return ERR_NONE;
	}
				
	*result = "1";
	params->setUAPString(*&paramResult, *&result);
				
	return ERR_NONE;
}
				
				



class lbPluginFileExists : public lb_I_PluginImpl {
public:
	lbPluginFileExists();
	
	virtual ~lbPluginFileExists();
	
	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
	/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();
	
	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
	/*...e*/
	
	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukTransformer)
};



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFileExists)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFileExists, lbPluginFileExists)

/*...slbErrCodes LB_STDCALL lbPluginFileExists\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginFileExists::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPluginFileExists::setData(...) called.\n" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginFileExists::lbPluginFileExists() {
	_CL_VERBOSE << "lbPluginFileExists::lbPluginFileExists() called.\n" LOG_
	
}

lbPluginFileExists::~lbPluginFileExists() {
	_CL_VERBOSE << "lbPluginFileExists::~lbPluginFileExists() called.\n" LOG_
}

bool LB_STDCALL lbPluginFileExists::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL lbPluginFileExists::autorun() {
	lbErrCodes err = ERR_NONE;
	
	lbFileExists* XSLTTransformer = new lbFileExists();
		
	QI(XSLTTransformer, lb_I_Unknown, ukTransformer) 
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	
	XSLTTransformer->registerEventHandler(*&dispatcher);
	
	return err;
}

void LB_STDCALL lbPluginFileExists::initialize() {
}

bool LB_STDCALL lbPluginFileExists::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginFileExists\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginFileExists::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer == NULL) {
		lbFileExists* transformer = new lbFileExists();
		
		QI(transformer, lb_I_Unknown, ukTransformer)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukTransformer.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginFileExists\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginFileExists::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer == NULL) {
		
		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
		
		lbFileExists* transformer = new lbFileExists();
		
		
		QI(transformer, lb_I_Unknown, ukTransformer)
	}
	
	lb_I_Unknown* r = ukTransformer.getPtr();
	ukTransformer.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginFileExists::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer != NULL) {
		ukTransformer--;
		ukTransformer.resetPtr();
	}
}
/*...e*/
/*...e*/




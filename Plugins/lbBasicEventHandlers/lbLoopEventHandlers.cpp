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

#include <lbLoopEventHandlers.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(lbLoopEventHandlers)
ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

lbLoopEventHandlers::lbLoopEventHandlers() {
	
}

lbLoopEventHandlers::~lbLoopEventHandlers() {
	
}

lb_I_Unknown* lbLoopEventHandlers::getUnknown() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, uk)
	
	QI(this, lb_I_Unknown, uk)
	
	return uk.getPtr();
}

lbErrCodes LB_STDCALL lbLoopEventHandlers::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_LOG << "lbLoopEventHandlers::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbLoopEventHandlers::registerEventHandler(lb_I_Dispatcher* disp) {
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	int temp;
	eman->registerEvent("loopContainer", temp);
	eman->registerEvent("loopQueryResult", temp);

	disp->addEventHandlerFn(this, (lbEvHandler) &lbLoopEventHandlers::loopContainer, "loopContainer");
	disp->addEventHandlerFn(this, (lbEvHandler) &lbLoopEventHandlers::loopQueryResult, "loopQueryResult");
}

lbErrCodes LB_STDCALL lbLoopEventHandlers::loopContainer(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, containerName) // The name of the container in the parameteres to loop in. The container must have been created.
	UAP_REQUEST(getModuleInstance(), lb_I_String, resetLoopName) // The name of the variable to indicate reset the loop if that variable is 1 otherwise do not reset
	UAP_REQUEST(getModuleInstance(), lb_I_String, endLoopName) // The name of the variable to idicate loop end
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
		_LOG << "lbLoopEventHandlers::loopContainer() Did not got an object." LOG_
		params->setUAPString(*&paramName, *&result);
		return ERR_PARAMETER_MISSING;
	}
	
	QI(uk, lb_I_Parameter, params)
	
	if (params == NULL) {
		_LOG << "lbLoopEventHandlers::loopContainer() Parameter is not of type lb_I_Parameter." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_ILLEGAL_PARAMETER;
	}
	
	*paramName = "containerName";
	if ((err = params->getUAPString(*&paramName, *&containerName)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbLoopEventHandlers::loopContainer() Parameter 'containerName' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbLoopEventHandlers::loopContainer() Parameter 'containerName' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	*paramName = "resetLoopName";
	if ((err = params->getUAPString(*&paramName, *&resetLoopName)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbLoopEventHandlers::loopContainer() Parameter 'resetLoopName' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbLoopEventHandlers::loopContainer() Parameter 'resetLoopName' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	*paramName = "endLoopName";
	if ((err = params->getUAPString(*&paramName, *&endLoopName)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbLoopEventHandlers::loopContainer() Parameter 'endLoopName' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbLoopEventHandlers::loopContainer() Parameter 'endLoopName' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}

	//buffer->replace(toReplace->charrep(), with->charrep());

	//*paramName = "buffer";
	//params->setUAPString(*&paramName, *&buffer);
	
	*result = "1";
	params->setUAPString(*&paramResult, *&result);
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbLoopEventHandlers::loopQueryResult(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, queryInstanceName) // The name of the query instance to loop in. The query instance must have been created.
	UAP_REQUEST(getModuleInstance(), lb_I_String, resetLoopName) // The name of the variable to indicate reset the loop if that variable is 1 otherwise do not reset
	UAP_REQUEST(getModuleInstance(), lb_I_String, endLoopName) // The name of the variable to idicate loop end
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
		_LOG << "lbLoopEventHandlers::loopContainer() Did not got an object." LOG_
		params->setUAPString(*&paramName, *&result);
		return ERR_PARAMETER_MISSING;
	}
	
	QI(uk, lb_I_Parameter, params)
	
	if (params == NULL) {
		_LOG << "lbLoopEventHandlers::loopContainer() Parameter is not of type lb_I_Parameter." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_ILLEGAL_PARAMETER;
	}
	
	*paramName = "queryInstanceName";
	if ((err = params->getUAPString(*&paramName, *&queryInstanceName)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbLoopEventHandlers::loopContainer() Parameter 'queryInstanceName' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbLoopEventHandlers::loopContainer() Parameter 'queryInstanceName' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	*paramName = "resetLoopName";
	if ((err = params->getUAPString(*&paramName, *&resetLoopName)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbLoopEventHandlers::loopContainer() Parameter 'resetLoopName' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbLoopEventHandlers::loopContainer() Parameter 'resetLoopName' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}

	UAP_REQUEST(getModuleInstance(), lb_I_String, pre)
	
	//*pre = prepend->charrep();
	//*pre += buffer->charrep();
	//buffer = pre->charrep();

	//*paramName = "buffer";
	//params->setUAPString(*&paramName, *&buffer);
	
	*result = "1";
	params->setUAPString(*&paramResult, *&result);
	
	return ERR_NONE;
}


class lbPluginLoopEventHandlers : public lb_I_PluginImpl {
public:
	lbPluginLoopEventHandlers();
	
	virtual ~lbPluginLoopEventHandlers();
	
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



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginLoopEventHandlers)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginLoopEventHandlers, lbPluginLoopEventHandlers)

/*...slbErrCodes LB_STDCALL lbPluginLoopEventHandlers\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginLoopEventHandlers::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPluginLoopEventHandlers::setData(...) called.\n" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginLoopEventHandlers::lbPluginLoopEventHandlers() {
	_CL_VERBOSE << "lbPluginLoopEventHandlers::lbPluginLoopEventHandlers() called.\n" LOG_
	
}

lbPluginLoopEventHandlers::~lbPluginLoopEventHandlers() {
	_CL_VERBOSE << "lbPluginLoopEventHandlers::~lbPluginLoopEventHandlers() called.\n" LOG_
}

bool LB_STDCALL lbPluginLoopEventHandlers::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL lbPluginLoopEventHandlers::autorun() {
	lbErrCodes err = ERR_NONE;
	
	lbLoopEventHandlers* XSLTTransformer = new lbLoopEventHandlers();
		
	QI(XSLTTransformer, lb_I_Unknown, ukTransformer) 
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	
	XSLTTransformer->registerEventHandler(*&dispatcher);
	
	return err;
}

void LB_STDCALL lbPluginLoopEventHandlers::initialize() {
}

bool LB_STDCALL lbPluginLoopEventHandlers::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginLoopEventHandlers\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginLoopEventHandlers::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer == NULL) {
		lbLoopEventHandlers* transformer = new lbLoopEventHandlers();
		
		QI(transformer, lb_I_Unknown, ukTransformer)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukTransformer.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginLoopEventHandlers\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginLoopEventHandlers::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer == NULL) {
		
		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
		
		lbLoopEventHandlers* transformer = new lbLoopEventHandlers();
		
		
		QI(transformer, lb_I_Unknown, ukTransformer)
	}
	
	lb_I_Unknown* r = ukTransformer.getPtr();
	ukTransformer.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginLoopEventHandlers::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer != NULL) {
		ukTransformer--;
		ukTransformer.resetPtr();
	}
}
/*...e*/
/*...e*/




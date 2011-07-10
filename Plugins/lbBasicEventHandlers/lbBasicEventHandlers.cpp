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

#include <lbBasicEventHandlers.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(lbBasicEventHandlers)
ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

lbBasicEventHandlers::lbBasicEventHandlers() {
	ref = STARTREF;
}

lbBasicEventHandlers::~lbBasicEventHandlers() {
	
}

lb_I_Unknown* lbBasicEventHandlers::getUnknown() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, uk)
	
	QI(this, lb_I_Unknown, uk)
	
	return uk.getPtr();
}

lbErrCodes LB_STDCALL lbBasicEventHandlers::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_LOG << "lbBasicEventHandlers::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbBasicEventHandlers::registerEventHandler(lb_I_Dispatcher* disp) {
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	int temp;
	eman->registerEvent("replaceText", temp);
	eman->registerEvent("prependText", temp);
	eman->registerEvent("replaceText", temp);

	disp->addEventHandlerFn(this, (lbEvHandler) &lbBasicEventHandlers::replaceText, "replaceText");
	disp->addEventHandlerFn(this, (lbEvHandler) &lbBasicEventHandlers::prependText, "prependText");
	disp->addEventHandlerFn(this, (lbEvHandler) &lbBasicEventHandlers::appendText, "appendText");
}

lbErrCodes LB_STDCALL lbBasicEventHandlers::replaceText(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, buffer) // Replace in this
	UAP_REQUEST(getModuleInstance(), lb_I_String, toReplace) // What should be replaced
	UAP_REQUEST(getModuleInstance(), lb_I_String, with) // Replace to this text
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
		_LOG << "lbBasicEventHandlers::replaceText() Did not got an object." LOG_
		params->setUAPString(*&paramName, *&result);
		return ERR_PARAMETER_MISSING;
	}
	
	QI(uk, lb_I_Parameter, params)
	
	if (params == NULL) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter is not of type lb_I_Parameter." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_ILLEGAL_PARAMETER;
	}
	
	*paramName = "buffer";
	if ((err = params->getUAPString(*&paramName, *&buffer)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter 'buffer' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter 'buffer' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	*paramName = "toReplace";
	if ((err = params->getUAPString(*&paramName, *&toReplace)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter 'toReplace' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter 'toReplace' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	*paramName = "with";
	if ((err = params->getUAPString(*&paramName, *&with)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter 'with' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter 'with' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}

	buffer->replace(toReplace->charrep(), with->charrep());

	*paramName = "buffer";
	params->setUAPString(*&paramName, *&buffer);
	
	*result = "1";
	params->setUAPString(*&paramResult, *&result);
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbBasicEventHandlers::prependText(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, buffer) // Replace in this
	UAP_REQUEST(getModuleInstance(), lb_I_String, prepend) // What should be prepended
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
		_LOG << "lbBasicEventHandlers::replaceText() Did not got an object." LOG_
		params->setUAPString(*&paramName, *&result);
		return ERR_PARAMETER_MISSING;
	}
	
	QI(uk, lb_I_Parameter, params)
	
	if (params == NULL) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter is not of type lb_I_Parameter." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_ILLEGAL_PARAMETER;
	}
	
	*paramName = "buffer";
	if ((err = params->getUAPString(*&paramName, *&buffer)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter 'buffer' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter 'buffer' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	*paramName = "prepend";
	if ((err = params->getUAPString(*&paramName, *&prepend)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter 'prepend' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter 'prepend' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}

	UAP_REQUEST(getModuleInstance(), lb_I_String, pre)
	
	*pre = prepend->charrep();
	*pre += buffer->charrep();
	*buffer = pre->charrep();

	*paramName = "buffer";
	params->setUAPString(*&paramName, *&buffer);
	
	*result = "1";
	params->setUAPString(*&paramResult, *&result);
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbBasicEventHandlers::appendText(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, buffer) // Replace in this
	UAP_REQUEST(getModuleInstance(), lb_I_String, append) // What should be appended
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
		_LOG << "lbBasicEventHandlers::replaceText() Did not got an object." LOG_
		params->setUAPString(*&paramName, *&result);
		return ERR_PARAMETER_MISSING;
	}
	
	QI(uk, lb_I_Parameter, params)
	
	if (params == NULL) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter is not of type lb_I_Parameter." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_ILLEGAL_PARAMETER;
	}
	
	*paramName = "buffer";
	if ((err = params->getUAPString(*&paramName, *&buffer)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter 'buffer' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter 'buffer' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	*paramName = "append";
	if ((err = params->getUAPString(*&paramName, *&append)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter 'append' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbBasicEventHandlers::replaceText() Parameter 'append' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}

	*buffer += append->charrep();

	*paramName = "buffer";
	params->setUAPString(*&paramName, *&buffer);
	
	*result = "1";
	params->setUAPString(*&paramResult, *&result);
	
	return ERR_NONE;
}


class lbPluginBasicEventHandlers : public lb_I_PluginImpl {
public:
	lbPluginBasicEventHandlers();
	
	virtual ~lbPluginBasicEventHandlers();
	
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



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginBasicEventHandlers)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginBasicEventHandlers, lbPluginBasicEventHandlers)

/*...slbErrCodes LB_STDCALL lbPluginBasicEventHandlers\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginBasicEventHandlers::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPluginBasicEventHandlers::setData(...) called.\n" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginBasicEventHandlers::lbPluginBasicEventHandlers() {
	_CL_VERBOSE << "lbPluginBasicEventHandlers::lbPluginBasicEventHandlers() called.\n" LOG_
	ref = STARTREF;
}

lbPluginBasicEventHandlers::~lbPluginBasicEventHandlers() {
	_CL_VERBOSE << "lbPluginBasicEventHandlers::~lbPluginBasicEventHandlers() called.\n" LOG_
}

bool LB_STDCALL lbPluginBasicEventHandlers::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL lbPluginBasicEventHandlers::autorun() {
	lbErrCodes err = ERR_NONE;
	
	lbBasicEventHandlers* XSLTTransformer = new lbBasicEventHandlers();
	XSLTTransformer->setModuleManager(manager.getPtr(), __FILE__, __LINE__);	
	QI(XSLTTransformer, lb_I_Unknown, ukTransformer) 
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	
	XSLTTransformer->registerEventHandler(*&dispatcher);
	
	return err;
}

void LB_STDCALL lbPluginBasicEventHandlers::initialize() {
}

bool LB_STDCALL lbPluginBasicEventHandlers::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginBasicEventHandlers\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginBasicEventHandlers::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer == NULL) {
		lbBasicEventHandlers* transformer = new lbBasicEventHandlers();
		transformer->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		QI(transformer, lb_I_Unknown, ukTransformer)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukTransformer.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginBasicEventHandlers\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginBasicEventHandlers::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer == NULL) {
		
		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
		
		lbBasicEventHandlers* transformer = new lbBasicEventHandlers();
		transformer->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		
		QI(transformer, lb_I_Unknown, ukTransformer)
	}
	
	lb_I_Unknown* r = ukTransformer.getPtr();
	ukTransformer.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginBasicEventHandlers::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer != NULL) {
		ukTransformer--;
		ukTransformer.resetPtr();
	}
}
/*...e*/
/*...e*/




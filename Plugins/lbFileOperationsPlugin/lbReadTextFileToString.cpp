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

#include <lbReadTextFileToString.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(lbReadTextFileToString)
ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

lbReadTextFileToString::lbReadTextFileToString() {
	ref = STARTREF;
}

lbReadTextFileToString::~lbReadTextFileToString() {
	
}

lb_I_Unknown* lbReadTextFileToString::getUnknown() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, uk)
	
	QI(this, lb_I_Unknown, uk)
	
	return uk.getPtr();
}

lbErrCodes LB_STDCALL lbReadTextFileToString::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_LOG << "lbReadTextFileToString::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbReadTextFileToString::registerEventHandler(lb_I_Dispatcher* disp) {
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	int temp;
	eman->registerEvent("readFileToString", temp);
	
	disp->addEventHandlerFn(this, (lbEvHandler) &lbReadTextFileToString::readFileToString, "readFileToString");
}

lbErrCodes LB_STDCALL lbReadTextFileToString::readFileToString(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, filename) // What to transform
	UAP_REQUEST(getModuleInstance(), lb_I_String, target) // How to transform
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
		_LOG << "lbReadTextFileToString::readFileToString() Did not got an object." LOG_
		params->setUAPString(*&paramName, *&result);
		return ERR_PARAMETER_MISSING;
	}
	
	QI(uk, lb_I_Parameter, params)
	
	if (params == NULL) {
		_LOG << "lbReadTextFileToString::readFileToString() Parameter is not of type lb_I_Parameter." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_ILLEGAL_PARAMETER;
	}
	
	*paramName = "filename";
	if ((err = params->getUAPString(*&paramName, *&filename)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbReadTextFileToString::readFileToString() Parameter 'filename' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbReadTextFileToString::readFileToString() Parameter 'filename' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	*paramName = "target";
	if ((err = params->getUAPString(*&paramName, *&target)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbReadTextFileToString::readFileToString() Parameter 'target' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbReadTextFileToString::readFileToString() Parameter 'target' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	// Read the file into memory
	
	UAP_REQUEST(getModuleInstance(), lb_I_InputStream, iStream)
	
	iStream->setFileName(filename->charrep());
	
	if (!iStream->open()) {
		_LOG << "lbReadTextFileToString::readFileToString() Could not open the file to read." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_FILE_READ;
	}
	
	UAP(lb_I_String, value)
	
	value = iStream->getAsString();
	
	if (value == NULL) {
		_LOG << "lbReadTextFileToString::readFileToString() Could get file as string." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_FILE_READ;
	}
	
	*paramName = "target";
	params->setUAPString(*&paramName, *&value);
	
	*result = "1";
	params->setUAPString(*&paramResult, *&result);
	
	return ERR_NONE;
}





class lbPluginReadTextFileToString : public lb_I_PluginImpl {
public:
	lbPluginReadTextFileToString();
	
	virtual ~lbPluginReadTextFileToString();
	
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
	
	UAP(lb_I_Unknown, ukReadFileToString)
};



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReadTextFileToString)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReadTextFileToString, lbPluginReadTextFileToString)

/*...slbErrCodes LB_STDCALL lbPluginReadTextFileToString\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginReadTextFileToString::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPluginReadTextFileToString::setData(...) called.\n" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginReadTextFileToString::lbPluginReadTextFileToString() {
	_CL_VERBOSE << "lbPluginReadTextFileToString::lbPluginReadTextFileToString() called.\n" LOG_
	ref = STARTREF;
}

lbPluginReadTextFileToString::~lbPluginReadTextFileToString() {
	_CL_VERBOSE << "lbPluginReadTextFileToString::~lbPluginReadTextFileToString() called.\n" LOG_
}

bool LB_STDCALL lbPluginReadTextFileToString::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL lbPluginReadTextFileToString::autorun() {
	lbErrCodes err = ERR_NONE;
	
	lbReadTextFileToString* r = new lbReadTextFileToString();
	r->setModuleManager(manager.getPtr(), __FILE__, __LINE__);	
	QI(r, lb_I_Unknown, ukReadFileToString) 
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	
	r->registerEventHandler(*&dispatcher);
	
	return err;
}

void LB_STDCALL lbPluginReadTextFileToString::initialize() {
}

bool LB_STDCALL lbPluginReadTextFileToString::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginReadTextFileToString\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginReadTextFileToString::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukReadFileToString == NULL) {
		lbReadTextFileToString* r = new lbReadTextFileToString();
		r->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		QI(r, lb_I_Unknown, ukReadFileToString)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReadFileToString.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginReadTextFileToString\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginReadTextFileToString::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukReadFileToString == NULL) {
		
		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
		
		lbReadTextFileToString* r = new lbReadTextFileToString();
		r->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		
		QI(r, lb_I_Unknown, ukReadFileToString)
	}
	
	lb_I_Unknown* ukr = ukReadFileToString.getPtr();
	ukReadFileToString.resetPtr();
	return ukr;
}
/*...e*/
void LB_STDCALL lbPluginReadTextFileToString::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukReadFileToString != NULL) {
		ukReadFileToString--;
		ukReadFileToString.resetPtr();
	}
}
/*...e*/
/*...e*/




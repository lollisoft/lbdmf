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

#include <lbWriteStringToFile.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(lbWriteStringToFile)
ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

lbWriteStringToFile::lbWriteStringToFile() {
	ref = STARTREF;
}

lbWriteStringToFile::~lbWriteStringToFile() {
	
}

lb_I_Unknown* lbWriteStringToFile::getUnknown() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, uk)
	
	QI(this, lb_I_Unknown, uk)
	
	return uk.getPtr();
}

lbErrCodes LB_STDCALL lbWriteStringToFile::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_LOG << "lbWriteStringToFile::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbWriteStringToFile::registerEventHandler(lb_I_Dispatcher* disp) {
	disp->addEventHandlerFn(this, (lbEvHandler) &lbWriteStringToFile::writeStringToFile, "writeStringToFile");
}

lbErrCodes LB_STDCALL lbWriteStringToFile::writeStringToFile(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, source) // What to write
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
		_LOG << "lbWriteStringToFile::writeStringToFile() Did not got an object." LOG_
		params->setUAPString(*&paramName, *&result);
		return ERR_PARAMETER_MISSING;
	}
	
	QI(uk, lb_I_Parameter, params)
	
	if (params == NULL) {
		_LOG << "lbWriteStringToFile::writeStringToFile() Parameter is not of type lb_I_Parameter." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_ILLEGAL_PARAMETER;
	}
	
	*paramName = "source";
	if ((err = params->getUAPString(*&paramName, *&source)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbWriteStringToFile::writeStringToFile() Parameter 'source' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbWriteStringToFile::writeStringToFile() Parameter 'source' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	*paramName = "filename";
	if ((err = params->getUAPString(*&paramName, *&filename)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbWriteStringToFile::writeStringToFile() Parameter 'filename' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbWriteStringToFile::writeStringToFile() Parameter 'filename' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	
	UAP_REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)

	if (oStream == NULL) {
		_LOG << "lbWriteStringToFile::writeStringToFile() Error: Could not get instance of lb_I_OutputStream." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_MODULE_NOT_FOUND;
	}
	
	oStream->setFileName(filename->charrep());
	
	oStream->open();
	
	*oStream << source->charrep();
	
	oStream->close();
	
	*result = "1";
	params->setUAPString(*&paramResult, *&result);
	
	return ERR_NONE;
}





class lbPluginWriteStringToFile : public lb_I_PluginImpl {
public:
	lbPluginWriteStringToFile();
	
	virtual ~lbPluginWriteStringToFile();
	
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



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginWriteStringToFile)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginWriteStringToFile, lbPluginWriteStringToFile)

/*...slbErrCodes LB_STDCALL lbPluginWriteStringToFile\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginWriteStringToFile::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPluginWriteStringToFile::setData(...) called.\n" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginWriteStringToFile::lbPluginWriteStringToFile() {
	_CL_VERBOSE << "lbPluginWriteStringToFile::lbPluginWriteStringToFile() called.\n" LOG_
	ref = STARTREF;
}

lbPluginWriteStringToFile::~lbPluginWriteStringToFile() {
	_CL_VERBOSE << "lbPluginWriteStringToFile::~lbPluginWriteStringToFile() called.\n" LOG_
}

bool LB_STDCALL lbPluginWriteStringToFile::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL lbPluginWriteStringToFile::autorun() {
	lbErrCodes err = ERR_NONE;
	
	lbWriteStringToFile* XSLTTransformer = new lbWriteStringToFile();
	XSLTTransformer->setModuleManager(manager.getPtr(), __FILE__, __LINE__);	
	QI(XSLTTransformer, lb_I_Unknown, ukTransformer) 
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	
	XSLTTransformer->registerEventHandler(*&dispatcher);
	
	return err;
}

void LB_STDCALL lbPluginWriteStringToFile::initialize() {
}

bool LB_STDCALL lbPluginWriteStringToFile::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginWriteStringToFile\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginWriteStringToFile::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer == NULL) {
		lbWriteStringToFile* transformer = new lbWriteStringToFile();
		transformer->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		QI(transformer, lb_I_Unknown, ukTransformer)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukTransformer.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginWriteStringToFile\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginWriteStringToFile::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer == NULL) {
		
		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
		
		lbWriteStringToFile* transformer = new lbWriteStringToFile();
		transformer->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		
		QI(transformer, lb_I_Unknown, ukTransformer)
	}
	
	lb_I_Unknown* r = ukTransformer.getPtr();
	ukTransformer.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginWriteStringToFile::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer != NULL) {
		ukTransformer--;
		ukTransformer.resetPtr();
	}
}
/*...e*/
/*...e*/




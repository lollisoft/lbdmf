/*
 DMF Distributed Multiplatform Framework (the initial goal of this library)
 This file is part of lbDMF.
 Copyright (C) 2002-2015  Lothar Behrens (lothar.behrens@lollisoft.de)
 
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

#include <lbPluginAntlr3.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(lbAntlr3)
ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

lbAntlr3::lbAntlr3() {
	
}

lbAntlr3::~lbAntlr3() {
	
}

lb_I_Unknown* lbAntlr3::getUnknown() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, uk)
	
	QI(this, lb_I_Unknown, uk)
	
	return uk.getPtr();
}

lbErrCodes LB_STDCALL lbAntlr3::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_LOG << "lbAntlr3::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbAntlr3::registerEventHandler(lb_I_Dispatcher* disp) {
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	int temp;
	eman->registerEvent("parse", temp);

	disp->addEventHandlerFn(this, (lbEvHandler) &lbAntlr3::parse, "parse");
}

lbErrCodes LB_STDCALL lbAntlr3::parse(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, language) // Parse using this language
	UAP_REQUEST(getModuleInstance(), lb_I_String, sourcecode) // Parse source code
	UAP_REQUEST(getModuleInstance(), lb_I_String, result) // Result for parsing
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramName) // Parameter name
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramResult) // Parameter name
	
	lbErrCodes err = ERR_NONE;

	// Default is failure
	*paramName = "result";
	*paramResult = "result";
	*result = "0";

	UAP(lb_I_Parameter, params)
	
	if (uk == NULL) {
		_LOG << "lbAntlr3::parse() Did not got an object." LOG_
		params->setUAPString(*&paramName, *&result);
		return ERR_PARAMETER_MISSING;
	}
	
	QI(uk, lb_I_Parameter, params)
	
	if (params == NULL) {
		_LOG << "lbAntlr3::parse() Parameter is not of type lb_I_Parameter." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_ILLEGAL_PARAMETER;
	}
	
	*paramName = "language";
	if ((err = params->getUAPString(*&paramName, *&language)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbAntlr3::parse() Parameter 'language' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbAntlr3::parse() Parameter 'language' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	*paramName = "sourcecode";
	if ((err = params->getUAPString(*&paramName, *&sourcecode)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbAntlr3::parse() Parameter 'sourcecode' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbAntlr3::parse() Parameter 'sourcecode' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

	UAP(lb_I_ParserImplementation, languageImpl)

	AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_ParserImplementation, language->charrep(), languageImpl, "'language plugin'")

	if (languageImpl == NULL) {
		_LOG << "Error: Language " << language->charrep() << " not found" LOG_
		params->setUAPString(*&paramResult, *&language);
		return ERR_NONE;
	} else {
		UAP(lb_I_AbstractSyntaxTree, ast)
	
		languageImpl->init(sourcecode->charrep());
		
		ast = languageImpl->parse(NULL);
	}

	*result = "1";
	params->setUAPString(*&paramResult, *&result);
	
	return ERR_NONE;
}

class lbPluginAntlr3 : public lb_I_PluginImpl {
public:
	lbPluginAntlr3();
	
	virtual ~lbPluginAntlr3();
	
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
	
	UAP(lb_I_Unknown, uklbAntlr3)
};



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAntlr3)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAntlr3, lbPluginAntlr3)

/*...slbErrCodes LB_STDCALL lbPluginBasicEventHandlers\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginAntlr3::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPluginAntlr3::setData(...) called.\n" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginAntlr3::lbPluginAntlr3() {
	_CL_VERBOSE << "lbPluginAntlr3::lbPluginAntlr3() called.\n" LOG_
	
}

lbPluginAntlr3::~lbPluginAntlr3() {
	_CL_VERBOSE << "lbPluginAntlr3::~lbPluginAntlr3() called.\n" LOG_
}

bool LB_STDCALL lbPluginAntlr3::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL lbPluginAntlr3::autorun() {
	lbErrCodes err = ERR_NONE;

	lbAntlr3* antlr3 = new lbAntlr3();
		
	QI(antlr3, lb_I_Unknown, uklbAntlr3) 
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	
	antlr3->registerEventHandler(*&dispatcher);
	
	return err;
}

void LB_STDCALL lbPluginAntlr3::initialize() {
}

bool LB_STDCALL lbPluginAntlr3::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginBasicEventHandlers\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginAntlr3::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (uklbAntlr3 == NULL) {
		lbAntlr3* antlr3 = new lbAntlr3();
		
		QI(antlr3, lb_I_Unknown, uklbAntlr3)
	} else {
		_CL_VERBOSE << "lbPluginAntlr3::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return uklbAntlr3.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginBasicEventHandlers\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginAntlr3::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (uklbAntlr3 == NULL) {
		
		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
		
		lbAntlr3* antlr3 = new lbAntlr3();
		
		
		QI(antlr3, lb_I_Unknown, uklbAntlr3)
	}
	
	lb_I_Unknown* r = uklbAntlr3.getPtr();
	uklbAntlr3.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginAntlr3::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (uklbAntlr3 != NULL) {
		uklbAntlr3--;
		uklbAntlr3.resetPtr();
	}
}
/*...e*/
/*...e*/




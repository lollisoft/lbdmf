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

#include <lbPluginUIDsl.h>

#include <uiLexer.h>
#include <uiParser.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(lbUIDsl)
ADD_INTERFACE(lb_I_EventHandler)
ADD_INTERFACE(lb_I_ParserImplementation)
END_IMPLEMENT_LB_UNKNOWN()

lbUIDsl::lbUIDsl() {
	REQUEST(getModuleInstance(), lb_I_String, source)
}

lbUIDsl::~lbUIDsl() {
	
}

lb_I_Unknown* lbUIDsl::getUnknown() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, uk)
	
	QI(this, lb_I_Unknown, uk)
	
	return uk.getPtr();
}

lbErrCodes LB_STDCALL lbUIDsl::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_LOG << "lbUIDsl::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbUIDsl::registerEventHandler(lb_I_Dispatcher* disp) {
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	int temp;
	//eman->registerEvent("parse", temp);

	//disp->addEventHandlerFn(this, (lbEvHandler) &lbUIDsl::parse, "parse");
}

void LB_STDCALL lbUIDsl::init(const char* sourceCode) {
	printf("lbUIDsl::init() called.\n");
	if (sourceCode != NULL)	printf("Parser inits for %s\n", sourceCode);
	
	*source = sourceCode;
}

lb_I_AbstractSyntaxTree* LB_STDCALL lbUIDsl::parse(lb_I_ExecutionContext* parentContext) {
	printf("Parser parses...\n");
	
	pANTLR3_INPUT_STREAM           input;
    puiLexer		               lex;
    pANTLR3_COMMON_TOKEN_STREAM    tokens;
    puiParser		               parser;
 
 	pANTLR3_UINT8 input_string = (pANTLR3_UINT8)source->charrep();

	input  = antlr3StringStreamNew			   (input_string, ANTLR3_ENC_8BIT, strlen((const char*)input_string),(pANTLR3_UINT8)"ABCD");
    lex    = uiLexerNew			               (input);
    tokens = antlr3CommonTokenStreamSourceNew  (ANTLR3_SIZE_HINT, TOKENSOURCE(lex));
    parser = uiParserNew		               (tokens);
 
    uiParser_ui_return retval = parser  ->ui(parser);
 
	for (int i = 0; i < retval.tree->getChildCount(retval.tree); i++) {
        pANTLR3_BASE_TREE stat = (pANTLR3_BASE_TREE)retval.tree->getChild(retval.tree, i);

		
    }
	
    // Must manually clean up
    //
    parser ->free(parser);
    tokens ->free(tokens);
    lex    ->free(lex);
    input  ->close(input);
	
	
	return NULL;
}

class lbPluginUIDsl : public lb_I_PluginImpl {
public:
	lbPluginUIDsl();
	
	virtual ~lbPluginUIDsl();
	
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
	
	UAP(lb_I_Unknown, uklbUIDsl)
};



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginUIDsl)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginUIDsl, lbPluginUIDsl)

lbErrCodes LB_STDCALL lbPluginUIDsl::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPluginUIDsl::setData(...) called.\n" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbPluginUIDsl::lbPluginUIDsl() {
	_CL_VERBOSE << "lbPluginUIDsl::lbPluginUIDsl() called.\n" LOG_
	
}

lbPluginUIDsl::~lbPluginUIDsl() {
	_CL_VERBOSE << "lbPluginUIDsl::~lbPluginUIDsl() called.\n" LOG_
}

bool LB_STDCALL lbPluginUIDsl::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL lbPluginUIDsl::autorun() {
	lbErrCodes err = ERR_NONE;
	
	lbUIDsl* uidsl = new lbUIDsl();
		
	QI(uidsl, lb_I_Unknown, uklbUIDsl) 
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	
	uidsl->registerEventHandler(*&dispatcher);
	
	return err;
}

void LB_STDCALL lbPluginUIDsl::initialize() {
}

bool LB_STDCALL lbPluginUIDsl::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginUIDsl::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (uklbUIDsl == NULL) {
		lbUIDsl* uidsl = new lbUIDsl();
		
		QI(uidsl, lb_I_Unknown, uklbUIDsl)
	} else {
		_CL_VERBOSE << "lbPluginUIDsl::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return uklbUIDsl.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginUIDsl::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (uklbUIDsl == NULL) {
		
		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
		
		lbUIDsl* uidsl = new lbUIDsl();
		
		
		QI(uidsl, lb_I_Unknown, uklbUIDsl)
	}
	
	lb_I_Unknown* r = uklbUIDsl.getPtr();
	uklbUIDsl.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginUIDsl::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (uklbUIDsl != NULL) {
		uklbUIDsl--;
		uklbUIDsl.resetPtr();
	}
}
/*...e*/
/*...e*/




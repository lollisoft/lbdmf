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

#include <lbXSLTTransformer.h>

// Includes for the libxml / libxslt libraries

#include <libxml/xmlmemory.h>
#include <libxml/debugXML.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlIO.h>
#include <libxml/DOCBparser.h>
#include <libxml/xinclude.h>
#include <libxml/catalog.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include <libxslt/security.h>

#include <libexslt/exslt.h>

#ifndef __WATCOMC_
extern int xmlLoadExtDtdDefaultValue;
#endif
#ifdef __WATCOMC__
#define xsltSaveResultToString lb_xsltSaveResultToString
#define xsltParseStylesheetDoc lb_xsltParseStylesheetDoc
#define xsltApplyStylesheet lb_xsltApplyStylesheet
#define xsltFreeStylesheet lb_xsltFreeStylesheet
#define xmlSubstituteEntitiesDefault lb_xmlSubstituteEntitiesDefault
#define xmlFreeDoc lb_xmlFreeDoc
#define xsltCleanupGlobals lb_xsltCleanupGlobals
#define xmlCleanupParser lb_xmlCleanupParser
#define xmlReadMemory lb_xmlReadMemory
#define xmlInitMemory lb_xmlInitMemory
#define xsltNewSecurityPrefs lb_xsltNewSecurityPrefs
#define xsltSetDefaultSecurityPrefs lb_xsltSetDefaultSecurityPrefs
#define xsltSaveResultToFile lb_xsltSaveResultToFile
#define exsltRegisterAll lb_exsltRegisterAll
#endif


BEGIN_IMPLEMENT_LB_UNKNOWN(lbXSLTTransformer)
ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

lbXSLTTransformer::lbXSLTTransformer() {
	
}

lbXSLTTransformer::~lbXSLTTransformer() {
	
}

lb_I_Unknown* lbXSLTTransformer::getUnknown() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, uk)
	
	QI(this, lb_I_Unknown, uk)
	
	return uk.getPtr();
}

lbErrCodes LB_STDCALL lbXSLTTransformer::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_LOG << "lbXSLTTransformer::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbXSLTTransformer::registerEventHandler(lb_I_Dispatcher* disp) {
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	int temp;
	eman->registerEvent("transformXSLT", temp);
	
	disp->addEventHandlerFn(this, (lbEvHandler) &lbXSLTTransformer::transformXSLT, "transformXSLT");
}

lbErrCodes LB_STDCALL lbXSLTTransformer::transformXSLT(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, source) // What to transform
	UAP_REQUEST(getModuleInstance(), lb_I_String, stylesheet) // How to transform
	UAP_REQUEST(getModuleInstance(), lb_I_String, result) // Result for activity
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramName) // Parameter name
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramResult) // Parameter name
	
	lbErrCodes err = ERR_NONE;
	xsltStylesheetPtr cur = NULL;
	xmlDocPtr doc, res;
	xmlDocPtr stylesheetdoc;

	// Default is failure
	*paramName = "result";
	*paramResult = "result";
	*result = "0";

	UAP(lb_I_Parameter, params)
	
	if (uk == NULL) {
		_LOG << "lbXSLTTransformer::transformXSLT() Did not got an object." LOG_
		params->setUAPString(*&paramName, *&result);
		return ERR_PARAMETER_MISSING;
	}
	
	QI(uk, lb_I_Parameter, params)
	
	if (params == NULL) {
		_LOG << "lbXSLTTransformer::transformXSLT() Parameter is not of type lb_I_Parameter." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_ILLEGAL_PARAMETER;
	}
	
	*paramName = "source";
	if ((err = params->getUAPString(*&paramName, *&source)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbXSLTTransformer::transformXSLT() Parameter 'source' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbXSLTTransformer::transformXSLT() Parameter 'source' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	*paramName = "stylesheet";
	if ((err = params->getUAPString(*&paramName, *&stylesheet)) == ERR_PARAM_NOT_FOUND) {
		_LOG << "lbXSLTTransformer::transformXSLT() Parameter 'stylesheet' not found." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_NOT_FOUND;
	}
	
	if (err == ERR_PARAM_WRONG_TYPE) {
		_LOG << "lbXSLTTransformer::transformXSLT() Parameter 'stylesheet' is not of type lb_I_String." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_PARAM_WRONG_TYPE;
	}
	
	exsltRegisterAll();
	xsltSecurityPrefsPtr sec = NULL;
	xmlInitMemory();
	sec = xsltNewSecurityPrefs();
	xsltSetDefaultSecurityPrefs(sec);
	
	xmlSubstituteEntitiesDefault(1);
#ifndef __WATCOMC__
    xmlLoadExtDtdDefaultValue = 1;
#endif
#ifdef __WATCOMC__
    setxmlLoadExtDtdDefaultValue(1);
#endif
	
	xmlChar* URL = (xmlChar*) source->charrep();

	// Read the file into memory
	
	UAP_REQUEST(getModuleInstance(), lb_I_InputStream, iStream)
	
	iStream->setFileName(source->charrep());
	
	if (!iStream->open()) {
		_LOG << "lbXSLTTransformer::transformXSLT() Could not open the file to read." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_FILE_READ;
	}
	
	UAP(lb_I_String, value)
	
	value = iStream->getAsString();
	
	if (value == NULL) {
		_LOG << "lbXSLTTransformer::transformXSLT() Could get file as string." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_FILE_READ;
	}
	
	doc = xmlReadMemory((char const*) value->charrep(), strlen(value->charrep()), (char const*) URL, NULL, 0);

	if (doc == NULL) {
		_LOG << "lbXSLTTransformer::transformXSLT() Could not read XML document." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_DISPATCH_FAILS;
	}
	
	UAP(lb_I_String, styledoc)
	UAP_REQUEST(getModuleInstance(), lb_I_InputStream, input)
	input->setFileName(stylesheet->charrep());
	
	if (!input->open()) {
		_LOG << "lbXSLTTransformer::transformXSLT() Could not read stylesheet document." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_DISPATCH_FAILS;
	}
	
	styledoc = input->getAsString();
	URL = (xmlChar*) input->getFileName();
	stylesheetdoc = xmlReadMemory((char const*) styledoc->charrep(), strlen(styledoc->charrep()), (char const*) URL, NULL, 0);

	if (stylesheetdoc == NULL) {
		_LOG << "lbXSLTTransformer::transformXSLT() Could not read stylesheet document into memory." LOG_
		//chdir(oldcwd);
		
		params->setUAPString(*&paramResult, *&result);
		return ERR_DISPATCH_FAILS;
	}
	
	cur = xsltParseStylesheetDoc(stylesheetdoc);

	int len = 0;
	const char *p[16 + 1];
	
	p[0] = NULL;
	
	res = xsltApplyStylesheet(cur, doc, p);

	//xsltSaveResultToFile(stdout, res, cur);
	
	xmlChar *xmlbuff;
	int buffersize;
	
	//xmlDocDumpFormatMemory(res, &xmlbuff, &buffersize, 1);
	
	xsltSaveResultToString(&xmlbuff, &buffersize, res, cur);	
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, memorybuffer)
	
	*memorybuffer = (char*) xmlbuff;
	
	// Save the resulting content to a generic step output parameter.
	
	*paramName = "stepoutput";
	params->setUAPString(*&paramName, *&memorybuffer);
	
	xmlFree(xmlbuff);
	
	xsltFreeStylesheet(cur);
	xmlFreeDoc(res);

	xmlFreeDoc(doc);
	
	xsltCleanupGlobals();
	xmlCleanupParser();
	
	*result = "1";
	params->setUAPString(*&paramResult, *&result);
	
	return ERR_NONE;
}





class lbPluginXSLTTransformer : public lb_I_PluginImpl {
public:
	lbPluginXSLTTransformer();
	
	virtual ~lbPluginXSLTTransformer();
	
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



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginXSLTTransformer)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginXSLTTransformer, lbPluginXSLTTransformer)

/*...slbErrCodes LB_STDCALL lbPluginXSLTTransformer\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginXSLTTransformer::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPluginXSLTTransformer::setData(...) called.\n" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginXSLTTransformer::lbPluginXSLTTransformer() {
	_CL_VERBOSE << "lbPluginXSLTTransformer::lbPluginXSLTTransformer() called.\n" LOG_
	ref = STARTREF;
}

lbPluginXSLTTransformer::~lbPluginXSLTTransformer() {
	_CL_VERBOSE << "lbPluginXSLTTransformer::~lbPluginXSLTTransformer() called.\n" LOG_
}

bool LB_STDCALL lbPluginXSLTTransformer::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL lbPluginXSLTTransformer::autorun() {
	lbErrCodes err = ERR_NONE;
	
	lbXSLTTransformer* XSLTTransformer = new lbXSLTTransformer();
	XSLTTransformer->setModuleManager(manager.getPtr(), __FILE__, __LINE__);	
	QI(XSLTTransformer, lb_I_Unknown, ukTransformer) 
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	
	XSLTTransformer->registerEventHandler(*&dispatcher);
	
	return err;
}

void LB_STDCALL lbPluginXSLTTransformer::initialize() {
}

bool LB_STDCALL lbPluginXSLTTransformer::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginXSLTTransformer\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginXSLTTransformer::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer == NULL) {
		lbXSLTTransformer* transformer = new lbXSLTTransformer();
		transformer->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		QI(transformer, lb_I_Unknown, ukTransformer)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukTransformer.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginXSLTTransformer\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginXSLTTransformer::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer == NULL) {
		
		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
		
		lbXSLTTransformer* transformer = new lbXSLTTransformer();
		transformer->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		
		QI(transformer, lb_I_Unknown, ukTransformer)
	}
	
	lb_I_Unknown* r = ukTransformer.getPtr();
	ukTransformer.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginXSLTTransformer::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukTransformer != NULL) {
		ukTransformer--;
		ukTransformer.resetPtr();
	}
}
/*...e*/
/*...e*/





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
    p-Mail: Lothar Behrens
            Ginsterweg 4

            65760 Eschborn (germany)
*/
/*...e*/

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
#include <lbInterfaces-lbDMFManager.h>
#include <InternalFormatReader_Translations.h>

IMPLEMENT_FUNCTOR(instanceOfTranslationsInternalFormatReaderExtension, TranslationsInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(TranslationsInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

TranslationsInternalFormatReaderExtension::TranslationsInternalFormatReaderExtension() {
	_CL_VERBOSE << "TranslationsInternalFormatReaderExtension::TranslationsInternalFormatReaderExtension() called." LOG_
}

TranslationsInternalFormatReaderExtension::~TranslationsInternalFormatReaderExtension() {
	_CL_VERBOSE << "TranslationsInternalFormatReaderExtension::~TranslationsInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL TranslationsInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: TranslationsInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL TranslationsInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Translations, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: TranslationsInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_Translations." LOG_
		}
	} else {
		_LOG << "Error: TranslationsInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL TranslationsInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: TranslationsInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: TranslationsInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL TranslationsInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _translated = NULL;
		char* _text = NULL;
		char* _language = NULL;
	
		*iStream >> _ID;

		*iStream >> _translated;
		*iStream >> _text;
		*iStream >> _language;
		_LOG << "Read Translations entry from database: " << _translated << ", " << _text << ", " << _language << ", " <<  _ID LOG_
		owningObject->addTranslations(_translated, _text, _language,  _ID);

		// Leaky !
	}
}



class lbPluginTranslationsInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginTranslationsInternalFormatReaderExtension();
	
	virtual ~lbPluginTranslationsInternalFormatReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukTranslationsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginTranslationsInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginTranslationsInternalFormatReaderExtension, lbPluginTranslationsInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginTranslationsInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginTranslationsInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginTranslationsInternalFormatReaderExtension::lbPluginTranslationsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginTranslationsInternalFormatReaderExtension::lbPluginTranslationsInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginTranslationsInternalFormatReaderExtension::~lbPluginTranslationsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginTranslationsInternalFormatReaderExtension::~lbPluginTranslationsInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginTranslationsInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginTranslationsInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginTranslationsInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginTranslationsInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginTranslationsInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukTranslationsModelExtension == NULL) {
		TranslationsInternalFormatReaderExtension* TranslationsModelExtension = new TranslationsInternalFormatReaderExtension();
		
	
		QI(TranslationsModelExtension, lb_I_Unknown, ukTranslationsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukTranslationsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginTranslationsInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukTranslationsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		TranslationsInternalFormatReaderExtension* TranslationsModelExtension = new TranslationsInternalFormatReaderExtension();
		
	
		QI(TranslationsModelExtension, lb_I_Unknown, ukTranslationsModelExtension)
	}
	
	lb_I_Unknown* r = ukTranslationsModelExtension.getPtr();
	ukTranslationsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginTranslationsInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukTranslationsModelExtension != NULL) {
                ukTranslationsModelExtension--;
                ukTranslationsModelExtension.resetPtr();
        }
}

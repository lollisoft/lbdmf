
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
#include <XMLWriterExtension_Anwendungsparameter.h>

IMPLEMENT_FUNCTOR(instanceOfAnwendungsparameterXMLWriterExtension, AnwendungsparameterXMLWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(AnwendungsparameterXMLWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

AnwendungsparameterXMLWriterExtension::AnwendungsparameterXMLWriterExtension() {
	_CL_VERBOSE << "AnwendungsparameterXMLWriterExtension::AnwendungsparameterXMLWriterExtension() called." LOG_
}

AnwendungsparameterXMLWriterExtension::~AnwendungsparameterXMLWriterExtension() {
	_CL_VERBOSE << "AnwendungsparameterXMLWriterExtension::~AnwendungsparameterXMLWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL AnwendungsparameterXMLWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: AnwendungsparameterXMLWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL AnwendungsparameterXMLWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Anwendungsparameter, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: AnwendungsparameterXMLWriterExtension::setOwningObject() owning parameter is not a lb_I_Anwendungsparameter." LOG_
		}
	} else {
		_LOG << "Error: AnwendungsparameterXMLWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AnwendungsparameterXMLWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: AnwendungsparameterXMLWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: AnwendungsparameterXMLWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AnwendungsparameterXMLWriterExtension::execute() {
	*oStream << "<anwendungs_parameter>" << "\n";
	
	owningObject->finishAnwendungsparameterIteration();
	
	while (owningObject->hasMoreAnwendungsparameter()) {
		owningObject->setNextAnwendungsparameter();
		*oStream << 
		"<entry ID=\"" << owningObject->get_id() << 

		"\" parametervalue=\"" << owningObject->get_parametervalue() <<
		"\" parametername=\"" << owningObject->get_parametername() <<
		"\" anwendungid=\"" << owningObject->get_anwendungid() << "\"/>" << "\n";
	}
	*oStream << "</anwendungs_parameter>" << "\n";
}



class lbPluginAnwendungsparameterXMLWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginAnwendungsparameterXMLWriterExtension();
	
	virtual ~lbPluginAnwendungsparameterXMLWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAnwendungsparameterModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAnwendungsparameterXMLWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAnwendungsparameterXMLWriterExtension, lbPluginAnwendungsparameterXMLWriterExtension)

lbErrCodes LB_STDCALL lbPluginAnwendungsparameterXMLWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAnwendungsparameterXMLWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAnwendungsparameterXMLWriterExtension::lbPluginAnwendungsparameterXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginAnwendungsparameterXMLWriterExtension::lbPluginAnwendungsparameterXMLWriterExtension() called.\n" LOG_
}

lbPluginAnwendungsparameterXMLWriterExtension::~lbPluginAnwendungsparameterXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginAnwendungsparameterXMLWriterExtension::~lbPluginAnwendungsparameterXMLWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAnwendungsparameterXMLWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAnwendungsparameterXMLWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAnwendungsparameterXMLWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAnwendungsparameterXMLWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungsparameterXMLWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAnwendungsparameterModelExtension == NULL) {
		AnwendungsparameterXMLWriterExtension* AnwendungsparameterModelExtension = new AnwendungsparameterXMLWriterExtension();
		
	
		QI(AnwendungsparameterModelExtension, lb_I_Unknown, ukAnwendungsparameterModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAnwendungsparameterModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungsparameterXMLWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAnwendungsparameterModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		AnwendungsparameterXMLWriterExtension* AnwendungsparameterModelExtension = new AnwendungsparameterXMLWriterExtension();
		
	
		QI(AnwendungsparameterModelExtension, lb_I_Unknown, ukAnwendungsparameterModelExtension)
	}
	
	lb_I_Unknown* r = ukAnwendungsparameterModelExtension.getPtr();
	ukAnwendungsparameterModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAnwendungsparameterXMLWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAnwendungsparameterModelExtension != NULL) {
                ukAnwendungsparameterModelExtension--;
                ukAnwendungsparameterModelExtension.resetPtr();
        }
}

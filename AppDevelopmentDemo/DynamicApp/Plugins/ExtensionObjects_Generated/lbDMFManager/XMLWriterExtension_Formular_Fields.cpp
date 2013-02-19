
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
#include <XMLWriterExtension_Formular_Fields.h>

IMPLEMENT_FUNCTOR(instanceOfFormular_FieldsXMLWriterExtension, Formular_FieldsXMLWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Formular_FieldsXMLWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

Formular_FieldsXMLWriterExtension::Formular_FieldsXMLWriterExtension() {
	_CL_VERBOSE << "Formular_FieldsXMLWriterExtension::Formular_FieldsXMLWriterExtension() called." LOG_
}

Formular_FieldsXMLWriterExtension::~Formular_FieldsXMLWriterExtension() {
	_CL_VERBOSE << "Formular_FieldsXMLWriterExtension::~Formular_FieldsXMLWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL Formular_FieldsXMLWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Formular_FieldsXMLWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Formular_FieldsXMLWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Formular_Fields, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Formular_FieldsXMLWriterExtension::setOwningObject() owning parameter is not a lb_I_Formular_Fields." LOG_
		}
	} else {
		_LOG << "Error: Formular_FieldsXMLWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Formular_FieldsXMLWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: Formular_FieldsXMLWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: Formular_FieldsXMLWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Formular_FieldsXMLWriterExtension::execute() {
	*oStream << "<formular_fields>" << "\n";
	
	owningObject->finishIteration();
	
	while (owningObject->hasMoreElements()) {
		owningObject->setNextElement();
		*oStream << 
		"<entry ID=\"" << owningObject->get_id() << 

		"\" fkname=\"" << owningObject->get_fkname() <<
		"\" fktable=\"" << owningObject->get_fktable() <<
		"\" dbtype=\"" << owningObject->get_dbtype() <<
		"\" isforeignkey=\"" << owningObject->get_isforeignkey() <<
		"\" name=\"" << owningObject->get_name() <<
		"\" tablename=\"" << owningObject->get_tablename() <<
		"\" formularid=\"" << owningObject->get_formularid() << "\"/>" << "\n";
	}
	*oStream << "</formular_fields>" << "\n";
}



class lbPluginFormular_FieldsXMLWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginFormular_FieldsXMLWriterExtension();
	
	virtual ~lbPluginFormular_FieldsXMLWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormular_FieldsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormular_FieldsXMLWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormular_FieldsXMLWriterExtension, lbPluginFormular_FieldsXMLWriterExtension)

lbErrCodes LB_STDCALL lbPluginFormular_FieldsXMLWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormular_FieldsXMLWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormular_FieldsXMLWriterExtension::lbPluginFormular_FieldsXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginFormular_FieldsXMLWriterExtension::lbPluginFormular_FieldsXMLWriterExtension() called.\n" LOG_
}

lbPluginFormular_FieldsXMLWriterExtension::~lbPluginFormular_FieldsXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginFormular_FieldsXMLWriterExtension::~lbPluginFormular_FieldsXMLWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormular_FieldsXMLWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormular_FieldsXMLWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormular_FieldsXMLWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFormular_FieldsXMLWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_FieldsXMLWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_FieldsModelExtension == NULL) {
		Formular_FieldsXMLWriterExtension* Formular_FieldsModelExtension = new Formular_FieldsXMLWriterExtension();
		
	
		QI(Formular_FieldsModelExtension, lb_I_Unknown, ukFormular_FieldsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormular_FieldsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_FieldsXMLWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_FieldsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Formular_FieldsXMLWriterExtension* Formular_FieldsModelExtension = new Formular_FieldsXMLWriterExtension();
		
	
		QI(Formular_FieldsModelExtension, lb_I_Unknown, ukFormular_FieldsModelExtension)
	}
	
	lb_I_Unknown* r = ukFormular_FieldsModelExtension.getPtr();
	ukFormular_FieldsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormular_FieldsXMLWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormular_FieldsModelExtension != NULL) {
                ukFormular_FieldsModelExtension--;
                ukFormular_FieldsModelExtension.resetPtr();
        }
}

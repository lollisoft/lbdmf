
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
#include <XMLWriterExtension_Formulare.h>

IMPLEMENT_FUNCTOR(instanceOfFormulareXMLWriterExtension, FormulareXMLWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(FormulareXMLWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

FormulareXMLWriterExtension::FormulareXMLWriterExtension() {
	_CL_VERBOSE << "FormulareXMLWriterExtension::FormulareXMLWriterExtension() called." LOG_
}

FormulareXMLWriterExtension::~FormulareXMLWriterExtension() {
	_CL_VERBOSE << "FormulareXMLWriterExtension::~FormulareXMLWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL FormulareXMLWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: FormulareXMLWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL FormulareXMLWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Formulare, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: FormulareXMLWriterExtension::setOwningObject() owning parameter is not a lb_I_Formulare." LOG_
		}
	} else {
		_LOG << "Error: FormulareXMLWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormulareXMLWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: FormulareXMLWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: FormulareXMLWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormulareXMLWriterExtension::execute() {
	*oStream << "<formulare>" << "\n";
	
	owningObject->finishFormulareIteration();
	
	while (owningObject->hasMoreFormulare()) {
		owningObject->setNextFormulare();
		*oStream << 
		"<entry ID=\"" << owningObject->get_id() << 

		"\" name=\"" << owningObject->get_name() <<
		"\" menuname=\"" << owningObject->get_menuname() <<
		"\" menuhilfe=\"" << owningObject->get_menuhilfe() <<
		"\" eventname=\"" << owningObject->get_eventname() <<
		"\" toolbarimage=\"" << owningObject->get_toolbarimage() <<
		"\" anwendungid=\"" << owningObject->get_anwendungid() <<
		"\" typ=\"" << owningObject->get_typ() << "\"/>" << "\n";
	}
	*oStream << "</formulare>" << "\n";
}



class lbPluginFormulareXMLWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginFormulareXMLWriterExtension();
	
	virtual ~lbPluginFormulareXMLWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormulareModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormulareXMLWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormulareXMLWriterExtension, lbPluginFormulareXMLWriterExtension)

lbErrCodes LB_STDCALL lbPluginFormulareXMLWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormulareXMLWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormulareXMLWriterExtension::lbPluginFormulareXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginFormulareXMLWriterExtension::lbPluginFormulareXMLWriterExtension() called.\n" LOG_
}

lbPluginFormulareXMLWriterExtension::~lbPluginFormulareXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginFormulareXMLWriterExtension::~lbPluginFormulareXMLWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormulareXMLWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormulareXMLWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormulareXMLWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFormulareXMLWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormulareXMLWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormulareModelExtension == NULL) {
		FormulareXMLWriterExtension* FormulareModelExtension = new FormulareXMLWriterExtension();
		
	
		QI(FormulareModelExtension, lb_I_Unknown, ukFormulareModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormulareModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormulareXMLWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormulareModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FormulareXMLWriterExtension* FormulareModelExtension = new FormulareXMLWriterExtension();
		
	
		QI(FormulareModelExtension, lb_I_Unknown, ukFormulareModelExtension)
	}
	
	lb_I_Unknown* r = ukFormulareModelExtension.getPtr();
	ukFormulareModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormulareXMLWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormulareModelExtension != NULL) {
                ukFormulareModelExtension--;
                ukFormulareModelExtension.resetPtr();
        }
}

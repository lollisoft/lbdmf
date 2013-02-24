
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
#include <XMLWriterExtension_Applications_Formulars.h>

IMPLEMENT_FUNCTOR(instanceOfApplications_FormularsXMLWriterExtension, Applications_FormularsXMLWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Applications_FormularsXMLWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

Applications_FormularsXMLWriterExtension::Applications_FormularsXMLWriterExtension() {
	_CL_VERBOSE << "Applications_FormularsXMLWriterExtension::Applications_FormularsXMLWriterExtension() called." LOG_
}

Applications_FormularsXMLWriterExtension::~Applications_FormularsXMLWriterExtension() {
	_CL_VERBOSE << "Applications_FormularsXMLWriterExtension::~Applications_FormularsXMLWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL Applications_FormularsXMLWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Applications_FormularsXMLWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Applications_FormularsXMLWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Applications_Formulars, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Applications_FormularsXMLWriterExtension::setOwningObject() owning parameter is not a lb_I_Applications_Formulars." LOG_
		}
	} else {
		_LOG << "Error: Applications_FormularsXMLWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Applications_FormularsXMLWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: Applications_FormularsXMLWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: Applications_FormularsXMLWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Applications_FormularsXMLWriterExtension::execute() {
	*oStream << "<anwendungen_formulare>" << "\n";
	
	owningObject->finishIteration();
	
	while (owningObject->hasMoreElements()) {
		owningObject->setNextElement();
		*oStream << 
		"<applicationformular ID=\"" << owningObject->get_id() << 

		"\" anwendungid=\"" << owningObject->get_anwendungid() <<
		"\" formularid=\"" << owningObject->get_formularid() << "\"/>" << "\n";
	}
	*oStream << "</anwendungen_formulare>" << "\n";
}



class lbPluginApplications_FormularsXMLWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginApplications_FormularsXMLWriterExtension();
	
	virtual ~lbPluginApplications_FormularsXMLWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukApplications_FormularsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginApplications_FormularsXMLWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginApplications_FormularsXMLWriterExtension, lbPluginApplications_FormularsXMLWriterExtension)

lbErrCodes LB_STDCALL lbPluginApplications_FormularsXMLWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginApplications_FormularsXMLWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginApplications_FormularsXMLWriterExtension::lbPluginApplications_FormularsXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginApplications_FormularsXMLWriterExtension::lbPluginApplications_FormularsXMLWriterExtension() called.\n" LOG_
}

lbPluginApplications_FormularsXMLWriterExtension::~lbPluginApplications_FormularsXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginApplications_FormularsXMLWriterExtension::~lbPluginApplications_FormularsXMLWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginApplications_FormularsXMLWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginApplications_FormularsXMLWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginApplications_FormularsXMLWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginApplications_FormularsXMLWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginApplications_FormularsXMLWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplications_FormularsModelExtension == NULL) {
		Applications_FormularsXMLWriterExtension* Applications_FormularsModelExtension = new Applications_FormularsXMLWriterExtension();
		
	
		QI(Applications_FormularsModelExtension, lb_I_Unknown, ukApplications_FormularsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukApplications_FormularsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginApplications_FormularsXMLWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplications_FormularsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Applications_FormularsXMLWriterExtension* Applications_FormularsModelExtension = new Applications_FormularsXMLWriterExtension();
		
	
		QI(Applications_FormularsModelExtension, lb_I_Unknown, ukApplications_FormularsModelExtension)
	}
	
	lb_I_Unknown* r = ukApplications_FormularsModelExtension.getPtr();
	ukApplications_FormularsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginApplications_FormularsXMLWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukApplications_FormularsModelExtension != NULL) {
                ukApplications_FormularsModelExtension--;
                ukApplications_FormularsModelExtension.resetPtr();
        }
}

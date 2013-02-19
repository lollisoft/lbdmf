
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
#include <XMLWriterExtension_Actions.h>

IMPLEMENT_FUNCTOR(instanceOfActionsXMLWriterExtension, ActionsXMLWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ActionsXMLWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ActionsXMLWriterExtension::ActionsXMLWriterExtension() {
	_CL_VERBOSE << "ActionsXMLWriterExtension::ActionsXMLWriterExtension() called." LOG_
}

ActionsXMLWriterExtension::~ActionsXMLWriterExtension() {
	_CL_VERBOSE << "ActionsXMLWriterExtension::~ActionsXMLWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL ActionsXMLWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ActionsXMLWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ActionsXMLWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Actions, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ActionsXMLWriterExtension::setOwningObject() owning parameter is not a lb_I_Actions." LOG_
		}
	} else {
		_LOG << "Error: ActionsXMLWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ActionsXMLWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: ActionsXMLWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: ActionsXMLWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ActionsXMLWriterExtension::execute() {
	*oStream << "<actions>" << "\n";
	
	owningObject->finishIteration();
	
	while (owningObject->hasMoreElements()) {
		owningObject->setNextElement();
		*oStream << 
		"<entry ID=\"" << owningObject->get_id() << 

		"\" target=\"" << owningObject->get_target() <<
		"\" source=\"" << owningObject->get_source() <<
		"\" name=\"" << owningObject->get_name() <<
		"\" typ=\"" << owningObject->get_typ() << "\"/>" << "\n";
	}
	*oStream << "</actions>" << "\n";
}



class lbPluginActionsXMLWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginActionsXMLWriterExtension();
	
	virtual ~lbPluginActionsXMLWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukActionsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginActionsXMLWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginActionsXMLWriterExtension, lbPluginActionsXMLWriterExtension)

lbErrCodes LB_STDCALL lbPluginActionsXMLWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginActionsXMLWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginActionsXMLWriterExtension::lbPluginActionsXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginActionsXMLWriterExtension::lbPluginActionsXMLWriterExtension() called.\n" LOG_
}

lbPluginActionsXMLWriterExtension::~lbPluginActionsXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginActionsXMLWriterExtension::~lbPluginActionsXMLWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginActionsXMLWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginActionsXMLWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginActionsXMLWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginActionsXMLWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginActionsXMLWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionsModelExtension == NULL) {
		ActionsXMLWriterExtension* ActionsModelExtension = new ActionsXMLWriterExtension();
		
	
		QI(ActionsModelExtension, lb_I_Unknown, ukActionsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActionsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginActionsXMLWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ActionsXMLWriterExtension* ActionsModelExtension = new ActionsXMLWriterExtension();
		
	
		QI(ActionsModelExtension, lb_I_Unknown, ukActionsModelExtension)
	}
	
	lb_I_Unknown* r = ukActionsModelExtension.getPtr();
	ukActionsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginActionsXMLWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActionsModelExtension != NULL) {
                ukActionsModelExtension--;
                ukActionsModelExtension.resetPtr();
        }
}

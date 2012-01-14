
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
#include <XMLWriterExtension_Action_Steps.h>

IMPLEMENT_FUNCTOR(instanceOfAction_StepsXMLWriterExtension, Action_StepsXMLWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Action_StepsXMLWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

Action_StepsXMLWriterExtension::Action_StepsXMLWriterExtension() {
	_CL_VERBOSE << "Action_StepsXMLWriterExtension::Action_StepsXMLWriterExtension() called." LOG_
}

Action_StepsXMLWriterExtension::~Action_StepsXMLWriterExtension() {
	_CL_VERBOSE << "Action_StepsXMLWriterExtension::~Action_StepsXMLWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL Action_StepsXMLWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Action_StepsXMLWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Action_StepsXMLWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Action_Steps, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Action_StepsXMLWriterExtension::setOwningObject() owning parameter is not a lb_I_Action_Steps." LOG_
		}
	} else {
		_LOG << "Error: Action_StepsXMLWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Action_StepsXMLWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: Action_StepsXMLWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: Action_StepsXMLWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Action_StepsXMLWriterExtension::execute() {
	*oStream << "<action_steps>" << "\n";
	
	owningObject->finishAction_StepsIteration();
	
	while (owningObject->hasMoreAction_Steps()) {
		owningObject->setNextAction_Steps();
		*oStream << 
		"<entry ID=\"" << owningObject->get_id() << 

		"\" bezeichnung=\"" << owningObject->get_bezeichnung() <<
		"\" what=\"" << owningObject->get_what() <<
		"\" a_order_nr=\"" << owningObject->get_a_order_nr() <<
		"\" type=\"" << owningObject->get_type() <<
		"\" actionid=\"" << owningObject->get_actionid() << "\"/>" << "\n";
	}
	*oStream << "</action_steps>" << "\n";
}



class lbPluginAction_StepsXMLWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginAction_StepsXMLWriterExtension();
	
	virtual ~lbPluginAction_StepsXMLWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAction_StepsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAction_StepsXMLWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAction_StepsXMLWriterExtension, lbPluginAction_StepsXMLWriterExtension)

lbErrCodes LB_STDCALL lbPluginAction_StepsXMLWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAction_StepsXMLWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAction_StepsXMLWriterExtension::lbPluginAction_StepsXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginAction_StepsXMLWriterExtension::lbPluginAction_StepsXMLWriterExtension() called.\n" LOG_
}

lbPluginAction_StepsXMLWriterExtension::~lbPluginAction_StepsXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginAction_StepsXMLWriterExtension::~lbPluginAction_StepsXMLWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAction_StepsXMLWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAction_StepsXMLWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAction_StepsXMLWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAction_StepsXMLWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAction_StepsXMLWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_StepsModelExtension == NULL) {
		Action_StepsXMLWriterExtension* Action_StepsModelExtension = new Action_StepsXMLWriterExtension();
		
	
		QI(Action_StepsModelExtension, lb_I_Unknown, ukAction_StepsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAction_StepsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAction_StepsXMLWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_StepsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Action_StepsXMLWriterExtension* Action_StepsModelExtension = new Action_StepsXMLWriterExtension();
		
	
		QI(Action_StepsModelExtension, lb_I_Unknown, ukAction_StepsModelExtension)
	}
	
	lb_I_Unknown* r = ukAction_StepsModelExtension.getPtr();
	ukAction_StepsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAction_StepsXMLWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAction_StepsModelExtension != NULL) {
                ukAction_StepsModelExtension--;
                ukAction_StepsModelExtension.resetPtr();
        }
}

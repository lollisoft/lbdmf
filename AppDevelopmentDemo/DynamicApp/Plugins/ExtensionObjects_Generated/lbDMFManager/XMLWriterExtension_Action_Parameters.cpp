
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
#include <XMLWriterExtension_Action_Parameters.h>

IMPLEMENT_FUNCTOR(instanceOfAction_ParametersXMLWriterExtension, Action_ParametersXMLWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Action_ParametersXMLWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

Action_ParametersXMLWriterExtension::Action_ParametersXMLWriterExtension() {
	_CL_VERBOSE << "Action_ParametersXMLWriterExtension::Action_ParametersXMLWriterExtension() called." LOG_
}

Action_ParametersXMLWriterExtension::~Action_ParametersXMLWriterExtension() {
	_CL_VERBOSE << "Action_ParametersXMLWriterExtension::~Action_ParametersXMLWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL Action_ParametersXMLWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Action_ParametersXMLWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Action_ParametersXMLWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Action_Parameters, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Action_ParametersXMLWriterExtension::setOwningObject() owning parameter is not a lb_I_Action_Parameters." LOG_
		}
	} else {
		_LOG << "Error: Action_ParametersXMLWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Action_ParametersXMLWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: Action_ParametersXMLWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: Action_ParametersXMLWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Action_ParametersXMLWriterExtension::execute() {
	*oStream << "<action_parameters>" << "\n";
	
	owningObject->finishAction_ParametersIteration();
	
	while (owningObject->hasMoreAction_Parameters()) {
		owningObject->setNextAction_Parameters();
		*oStream << 
		"<entry ID=\"" << owningObject->get_id() << 

		"\" name=\"" << owningObject->get_name() <<
		"\" value=\"" << owningObject->get_value() <<
		"\" interface=\"" << owningObject->get_interface() <<
		"\" description=\"" << owningObject->get_description() <<
		"\" actionid=\"" << owningObject->get_actionid() << "\"/>" << "\n";
	}
	*oStream << "</action_parameters>" << "\n";
}



class lbPluginAction_ParametersXMLWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginAction_ParametersXMLWriterExtension();
	
	virtual ~lbPluginAction_ParametersXMLWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAction_ParametersModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAction_ParametersXMLWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAction_ParametersXMLWriterExtension, lbPluginAction_ParametersXMLWriterExtension)

lbErrCodes LB_STDCALL lbPluginAction_ParametersXMLWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAction_ParametersXMLWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAction_ParametersXMLWriterExtension::lbPluginAction_ParametersXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginAction_ParametersXMLWriterExtension::lbPluginAction_ParametersXMLWriterExtension() called.\n" LOG_
}

lbPluginAction_ParametersXMLWriterExtension::~lbPluginAction_ParametersXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginAction_ParametersXMLWriterExtension::~lbPluginAction_ParametersXMLWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAction_ParametersXMLWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAction_ParametersXMLWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAction_ParametersXMLWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAction_ParametersXMLWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAction_ParametersXMLWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_ParametersModelExtension == NULL) {
		Action_ParametersXMLWriterExtension* Action_ParametersModelExtension = new Action_ParametersXMLWriterExtension();
		
	
		QI(Action_ParametersModelExtension, lb_I_Unknown, ukAction_ParametersModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAction_ParametersModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAction_ParametersXMLWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_ParametersModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Action_ParametersXMLWriterExtension* Action_ParametersModelExtension = new Action_ParametersXMLWriterExtension();
		
	
		QI(Action_ParametersModelExtension, lb_I_Unknown, ukAction_ParametersModelExtension)
	}
	
	lb_I_Unknown* r = ukAction_ParametersModelExtension.getPtr();
	ukAction_ParametersModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAction_ParametersXMLWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAction_ParametersModelExtension != NULL) {
                ukAction_ParametersModelExtension--;
                ukAction_ParametersModelExtension.resetPtr();
        }
}

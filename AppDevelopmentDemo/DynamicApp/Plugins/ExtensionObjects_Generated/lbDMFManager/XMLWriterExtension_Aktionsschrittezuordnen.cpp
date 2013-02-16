
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
#include <XMLWriterExtension_Aktionsschrittezuordnen.h>

IMPLEMENT_FUNCTOR(instanceOfAktionsschrittezuordnenXMLWriterExtension, AktionsschrittezuordnenXMLWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(AktionsschrittezuordnenXMLWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

AktionsschrittezuordnenXMLWriterExtension::AktionsschrittezuordnenXMLWriterExtension() {
	_CL_VERBOSE << "AktionsschrittezuordnenXMLWriterExtension::AktionsschrittezuordnenXMLWriterExtension() called." LOG_
}

AktionsschrittezuordnenXMLWriterExtension::~AktionsschrittezuordnenXMLWriterExtension() {
	_CL_VERBOSE << "AktionsschrittezuordnenXMLWriterExtension::~AktionsschrittezuordnenXMLWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL AktionsschrittezuordnenXMLWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: AktionsschrittezuordnenXMLWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL AktionsschrittezuordnenXMLWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Aktionsschrittezuordnen, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: AktionsschrittezuordnenXMLWriterExtension::setOwningObject() owning parameter is not a lb_I_Aktionsschrittezuordnen." LOG_
		}
	} else {
		_LOG << "Error: AktionsschrittezuordnenXMLWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AktionsschrittezuordnenXMLWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: AktionsschrittezuordnenXMLWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: AktionsschrittezuordnenXMLWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AktionsschrittezuordnenXMLWriterExtension::execute() {
	*oStream << "<action_steps>" << "\n";
	
	owningObject->finishAktionsschrittezuordnenIteration();
	
	while (owningObject->hasMoreAktionsschrittezuordnen()) {
		owningObject->setNextAktionsschrittezuordnen();
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



class lbPluginAktionsschrittezuordnenXMLWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginAktionsschrittezuordnenXMLWriterExtension();
	
	virtual ~lbPluginAktionsschrittezuordnenXMLWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAktionsschrittezuordnenModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAktionsschrittezuordnenXMLWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAktionsschrittezuordnenXMLWriterExtension, lbPluginAktionsschrittezuordnenXMLWriterExtension)

lbErrCodes LB_STDCALL lbPluginAktionsschrittezuordnenXMLWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAktionsschrittezuordnenXMLWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAktionsschrittezuordnenXMLWriterExtension::lbPluginAktionsschrittezuordnenXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginAktionsschrittezuordnenXMLWriterExtension::lbPluginAktionsschrittezuordnenXMLWriterExtension() called.\n" LOG_
}

lbPluginAktionsschrittezuordnenXMLWriterExtension::~lbPluginAktionsschrittezuordnenXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginAktionsschrittezuordnenXMLWriterExtension::~lbPluginAktionsschrittezuordnenXMLWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAktionsschrittezuordnenXMLWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAktionsschrittezuordnenXMLWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAktionsschrittezuordnenXMLWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAktionsschrittezuordnenXMLWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAktionsschrittezuordnenXMLWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAktionsschrittezuordnenModelExtension == NULL) {
		AktionsschrittezuordnenXMLWriterExtension* AktionsschrittezuordnenModelExtension = new AktionsschrittezuordnenXMLWriterExtension();
		
	
		QI(AktionsschrittezuordnenModelExtension, lb_I_Unknown, ukAktionsschrittezuordnenModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAktionsschrittezuordnenModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAktionsschrittezuordnenXMLWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAktionsschrittezuordnenModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		AktionsschrittezuordnenXMLWriterExtension* AktionsschrittezuordnenModelExtension = new AktionsschrittezuordnenXMLWriterExtension();
		
	
		QI(AktionsschrittezuordnenModelExtension, lb_I_Unknown, ukAktionsschrittezuordnenModelExtension)
	}
	
	lb_I_Unknown* r = ukAktionsschrittezuordnenModelExtension.getPtr();
	ukAktionsschrittezuordnenModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAktionsschrittezuordnenXMLWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAktionsschrittezuordnenModelExtension != NULL) {
                ukAktionsschrittezuordnenModelExtension--;
                ukAktionsschrittezuordnenModelExtension.resetPtr();
        }
}

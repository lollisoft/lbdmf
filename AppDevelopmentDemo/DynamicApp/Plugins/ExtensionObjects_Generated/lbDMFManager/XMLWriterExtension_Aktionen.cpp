
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
#include <XMLWriterExtension_Aktionen.h>

IMPLEMENT_FUNCTOR(instanceOfAktionenXMLWriterExtension, AktionenXMLWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(AktionenXMLWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

AktionenXMLWriterExtension::AktionenXMLWriterExtension() {
	_CL_VERBOSE << "AktionenXMLWriterExtension::AktionenXMLWriterExtension() called." LOG_
}

AktionenXMLWriterExtension::~AktionenXMLWriterExtension() {
	_CL_VERBOSE << "AktionenXMLWriterExtension::~AktionenXMLWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL AktionenXMLWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: AktionenXMLWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL AktionenXMLWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Aktionen, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: AktionenXMLWriterExtension::setOwningObject() owning parameter is not a lb_I_Aktionen." LOG_
		}
	} else {
		_LOG << "Error: AktionenXMLWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AktionenXMLWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: AktionenXMLWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: AktionenXMLWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AktionenXMLWriterExtension::execute() {
	*oStream << "<actions>" << "\n";
	
	owningObject->finishAktionenIteration();
	
	while (owningObject->hasMoreAktionen()) {
		owningObject->setNextAktionen();
		*oStream << 
		"<entry ID=\"" << owningObject->get_id() << 

		"\" target=\"" << owningObject->get_target() <<
		"\" source=\"" << owningObject->get_source() <<
		"\" name=\"" << owningObject->get_name() <<
		"\" typ=\"" << owningObject->get_typ() << "\"/>" << "\n";
	}
	*oStream << "</actions>" << "\n";
}



class lbPluginAktionenXMLWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginAktionenXMLWriterExtension();
	
	virtual ~lbPluginAktionenXMLWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAktionenModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAktionenXMLWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAktionenXMLWriterExtension, lbPluginAktionenXMLWriterExtension)

lbErrCodes LB_STDCALL lbPluginAktionenXMLWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAktionenXMLWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAktionenXMLWriterExtension::lbPluginAktionenXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginAktionenXMLWriterExtension::lbPluginAktionenXMLWriterExtension() called.\n" LOG_
}

lbPluginAktionenXMLWriterExtension::~lbPluginAktionenXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginAktionenXMLWriterExtension::~lbPluginAktionenXMLWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAktionenXMLWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAktionenXMLWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAktionenXMLWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAktionenXMLWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAktionenXMLWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAktionenModelExtension == NULL) {
		AktionenXMLWriterExtension* AktionenModelExtension = new AktionenXMLWriterExtension();
		
	
		QI(AktionenModelExtension, lb_I_Unknown, ukAktionenModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAktionenModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAktionenXMLWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAktionenModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		AktionenXMLWriterExtension* AktionenModelExtension = new AktionenXMLWriterExtension();
		
	
		QI(AktionenModelExtension, lb_I_Unknown, ukAktionenModelExtension)
	}
	
	lb_I_Unknown* r = ukAktionenModelExtension.getPtr();
	ukAktionenModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAktionenXMLWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAktionenModelExtension != NULL) {
                ukAktionenModelExtension--;
                ukAktionenModelExtension.resetPtr();
        }
}

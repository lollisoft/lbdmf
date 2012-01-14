
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
#include <InternalFormatWriter_FKPK_Mapping.h>

IMPLEMENT_FUNCTOR(instanceOfFKPK_MappingInternalFormatWriterExtension, FKPK_MappingInternalFormatWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(FKPK_MappingInternalFormatWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

FKPK_MappingInternalFormatWriterExtension::FKPK_MappingInternalFormatWriterExtension() {
	_CL_VERBOSE << "FKPK_MappingInternalFormatWriterExtension::FKPK_MappingInternalFormatWriterExtension() called." LOG_
}

FKPK_MappingInternalFormatWriterExtension::~FKPK_MappingInternalFormatWriterExtension() {
	_CL_VERBOSE << "FKPK_MappingInternalFormatWriterExtension::~FKPK_MappingInternalFormatWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL FKPK_MappingInternalFormatWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: FKPK_MappingInternalFormatWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL FKPK_MappingInternalFormatWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_FKPK_Mapping, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: FKPK_MappingInternalFormatWriterExtension::setOwningObject() owning parameter is not a lb_I_FKPK_Mapping." LOG_
		}
	} else {
		_LOG << "Error: FKPK_MappingInternalFormatWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FKPK_MappingInternalFormatWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: FKPK_MappingInternalFormatWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: FKPK_MappingInternalFormatWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FKPK_MappingInternalFormatWriterExtension::execute() {
	int count;

	count = owningObject->getFKPK_MappingCount();
	*oStream << count;
	
	owningObject->finishFKPK_MappingIteration();
	
	while (owningObject->hasMoreFKPK_Mapping()) {
		owningObject->setNextFKPK_Mapping();
		
		*oStream << owningObject->get_id();
		// Copy values

		*oStream << owningObject->get_pktable();
		*oStream << owningObject->get_pkname();
		*oStream << owningObject->get_fktable();
		*oStream << owningObject->get_fkname();
		*oStream << owningObject->get_fkname();
	}
}



class lbPluginFKPK_MappingInternalFormatWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginFKPK_MappingInternalFormatWriterExtension();
	
	virtual ~lbPluginFKPK_MappingInternalFormatWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFKPK_MappingModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFKPK_MappingInternalFormatWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFKPK_MappingInternalFormatWriterExtension, lbPluginFKPK_MappingInternalFormatWriterExtension)

lbErrCodes LB_STDCALL lbPluginFKPK_MappingInternalFormatWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFKPK_MappingInternalFormatWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFKPK_MappingInternalFormatWriterExtension::lbPluginFKPK_MappingInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginFKPK_MappingInternalFormatWriterExtension::lbPluginFKPK_MappingInternalFormatWriterExtension() called.\n" LOG_
}

lbPluginFKPK_MappingInternalFormatWriterExtension::~lbPluginFKPK_MappingInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginFKPK_MappingInternalFormatWriterExtension::~lbPluginFKPK_MappingInternalFormatWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFKPK_MappingInternalFormatWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFKPK_MappingInternalFormatWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFKPK_MappingInternalFormatWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFKPK_MappingInternalFormatWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFKPK_MappingInternalFormatWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFKPK_MappingModelExtension == NULL) {
		FKPK_MappingInternalFormatWriterExtension* FKPK_MappingModelExtension = new FKPK_MappingInternalFormatWriterExtension();
		
	
		QI(FKPK_MappingModelExtension, lb_I_Unknown, ukFKPK_MappingModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFKPK_MappingModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFKPK_MappingInternalFormatWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFKPK_MappingModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FKPK_MappingInternalFormatWriterExtension* FKPK_MappingModelExtension = new FKPK_MappingInternalFormatWriterExtension();
		
	
		QI(FKPK_MappingModelExtension, lb_I_Unknown, ukFKPK_MappingModelExtension)
	}
	
	lb_I_Unknown* r = ukFKPK_MappingModelExtension.getPtr();
	ukFKPK_MappingModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFKPK_MappingInternalFormatWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFKPK_MappingModelExtension != NULL) {
                ukFKPK_MappingModelExtension--;
                ukFKPK_MappingModelExtension.resetPtr();
        }
}

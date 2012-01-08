
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
#include <XMLWriterExtension_FKPK_Mapping.h>

IMPLEMENT_FUNCTOR(instanceOfFKPK_MappingXMLWriterExtension, FKPK_MappingXMLWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(FKPK_MappingXMLWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

FKPK_MappingXMLWriterExtension::FKPK_MappingXMLWriterExtension() {
	_CL_VERBOSE << "FKPK_MappingXMLWriterExtension::FKPK_MappingXMLWriterExtension() called." LOG_
}

FKPK_MappingXMLWriterExtension::~FKPK_MappingXMLWriterExtension() {
	_CL_VERBOSE << "FKPK_MappingXMLWriterExtension::~FKPK_MappingXMLWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL FKPK_MappingXMLWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: FKPK_MappingXMLWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL FKPK_MappingXMLWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_FKPK_Mapping, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: FKPK_MappingXMLWriterExtension::setOwningObject() owning parameter is not a lb_I_FKPK_Mapping." LOG_
		}
	} else {
		_LOG << "Error: FKPK_MappingXMLWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FKPK_MappingXMLWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: FKPK_MappingXMLWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: FKPK_MappingXMLWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FKPK_MappingXMLWriterExtension::execute() {
	*oStream << "<foreignkey_visibledata_mapping>" << "\n";
	
	owningObject->finishFKPK_MappingIteration();
	
	while (owningObject->hasMoreFKPK_Mapping()) {
		owningObject->setNextFKPK_Mapping();
		*oStream << 
		"<entry ID=\"" << owningObject->get_id() << 

		"\" pktable=\"" << owningObject->get_pktable() <<
		"\" pkname=\"" << owningObject->get_pkname() <<
		"\" fktable=\"" << owningObject->get_fktable() <<
		"\" fkname=\"" << owningObject->get_fkname() << "\"/>" << "\n";
	}
	*oStream << "</foreignkey_visibledata_mapping>" << "\n";
}



class lbPluginFKPK_MappingXMLWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginFKPK_MappingXMLWriterExtension();
	
	virtual ~lbPluginFKPK_MappingXMLWriterExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFKPK_MappingXMLWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFKPK_MappingXMLWriterExtension, lbPluginFKPK_MappingXMLWriterExtension)

lbErrCodes LB_STDCALL lbPluginFKPK_MappingXMLWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFKPK_MappingXMLWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFKPK_MappingXMLWriterExtension::lbPluginFKPK_MappingXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginFKPK_MappingXMLWriterExtension::lbPluginFKPK_MappingXMLWriterExtension() called.\n" LOG_
}

lbPluginFKPK_MappingXMLWriterExtension::~lbPluginFKPK_MappingXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginFKPK_MappingXMLWriterExtension::~lbPluginFKPK_MappingXMLWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFKPK_MappingXMLWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFKPK_MappingXMLWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFKPK_MappingXMLWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFKPK_MappingXMLWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFKPK_MappingXMLWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFKPK_MappingModelExtension == NULL) {
		FKPK_MappingXMLWriterExtension* FKPK_MappingModelExtension = new FKPK_MappingXMLWriterExtension();
		
	
		QI(FKPK_MappingModelExtension, lb_I_Unknown, ukFKPK_MappingModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFKPK_MappingModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFKPK_MappingXMLWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFKPK_MappingModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FKPK_MappingXMLWriterExtension* FKPK_MappingModelExtension = new FKPK_MappingXMLWriterExtension();
		
	
		QI(FKPK_MappingModelExtension, lb_I_Unknown, ukFKPK_MappingModelExtension)
	}
	
	lb_I_Unknown* r = ukFKPK_MappingModelExtension.getPtr();
	ukFKPK_MappingModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFKPK_MappingXMLWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFKPK_MappingModelExtension != NULL) {
                ukFKPK_MappingModelExtension--;
                ukFKPK_MappingModelExtension.resetPtr();
        }
}

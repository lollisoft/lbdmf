
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
#include <XMLWriterExtension_DBPrimaryKeys.h>

IMPLEMENT_FUNCTOR(instanceOfDBPrimaryKeysXMLWriterExtension, DBPrimaryKeysXMLWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(DBPrimaryKeysXMLWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

DBPrimaryKeysXMLWriterExtension::DBPrimaryKeysXMLWriterExtension() {
	_CL_VERBOSE << "DBPrimaryKeysXMLWriterExtension::DBPrimaryKeysXMLWriterExtension() called." LOG_
}

DBPrimaryKeysXMLWriterExtension::~DBPrimaryKeysXMLWriterExtension() {
	_CL_VERBOSE << "DBPrimaryKeysXMLWriterExtension::~DBPrimaryKeysXMLWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL DBPrimaryKeysXMLWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: DBPrimaryKeysXMLWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL DBPrimaryKeysXMLWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_DBPrimaryKeys, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: DBPrimaryKeysXMLWriterExtension::setOwningObject() owning parameter is not a lb_I_DBPrimaryKeys." LOG_
		}
	} else {
		_LOG << "Error: DBPrimaryKeysXMLWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBPrimaryKeysXMLWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: DBPrimaryKeysXMLWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: DBPrimaryKeysXMLWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBPrimaryKeysXMLWriterExtension::execute() {
	*oStream << "<dbprimarykey>" << "\n";
	
	owningObject->finishIteration();
	
	while (owningObject->hasMoreElements()) {
		owningObject->setNextElement();
		*oStream << 
		"<entry ID=\"" << owningObject->get_id() << 

		"\" tablecatalog=\"" << owningObject->get_tablecatalog() <<
		"\" tableschema=\"" << owningObject->get_tableschema() <<
		"\" tablename=\"" << owningObject->get_tablename() <<
		"\" columnname=\"" << owningObject->get_columnname() <<
		"\" columnname2=\"" << owningObject->get_columnname2() <<
		"\" keysequence=\"" << owningObject->get_keysequence() <<
		"\" dbtableid=\"" << owningObject->get_dbtableid() << "\"/>" << "\n";
	}
	*oStream << "</dbprimarykey>" << "\n";
}



class lbPluginDBPrimaryKeysXMLWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginDBPrimaryKeysXMLWriterExtension();
	
	virtual ~lbPluginDBPrimaryKeysXMLWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukDBPrimaryKeysModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDBPrimaryKeysXMLWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDBPrimaryKeysXMLWriterExtension, lbPluginDBPrimaryKeysXMLWriterExtension)

lbErrCodes LB_STDCALL lbPluginDBPrimaryKeysXMLWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDBPrimaryKeysXMLWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginDBPrimaryKeysXMLWriterExtension::lbPluginDBPrimaryKeysXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginDBPrimaryKeysXMLWriterExtension::lbPluginDBPrimaryKeysXMLWriterExtension() called.\n" LOG_
}

lbPluginDBPrimaryKeysXMLWriterExtension::~lbPluginDBPrimaryKeysXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginDBPrimaryKeysXMLWriterExtension::~lbPluginDBPrimaryKeysXMLWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginDBPrimaryKeysXMLWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDBPrimaryKeysXMLWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDBPrimaryKeysXMLWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginDBPrimaryKeysXMLWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginDBPrimaryKeysXMLWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBPrimaryKeysModelExtension == NULL) {
		DBPrimaryKeysXMLWriterExtension* DBPrimaryKeysModelExtension = new DBPrimaryKeysXMLWriterExtension();
		
	
		QI(DBPrimaryKeysModelExtension, lb_I_Unknown, ukDBPrimaryKeysModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukDBPrimaryKeysModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginDBPrimaryKeysXMLWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBPrimaryKeysModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		DBPrimaryKeysXMLWriterExtension* DBPrimaryKeysModelExtension = new DBPrimaryKeysXMLWriterExtension();
		
	
		QI(DBPrimaryKeysModelExtension, lb_I_Unknown, ukDBPrimaryKeysModelExtension)
	}
	
	lb_I_Unknown* r = ukDBPrimaryKeysModelExtension.getPtr();
	ukDBPrimaryKeysModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginDBPrimaryKeysXMLWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukDBPrimaryKeysModelExtension != NULL) {
                ukDBPrimaryKeysModelExtension--;
                ukDBPrimaryKeysModelExtension.resetPtr();
        }
}


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
#include <DBReader_Formulare.h>

IMPLEMENT_FUNCTOR(instanceOfFormulareDBReaderExtension, FormulareDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(FormulareDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

FormulareDBReaderExtension::FormulareDBReaderExtension() {
	_CL_VERBOSE << "FormulareDBReaderExtension::FormulareDBReaderExtension() called." LOG_
}

FormulareDBReaderExtension::~FormulareDBReaderExtension() {
	_CL_VERBOSE << "FormulareDBReaderExtension::~FormulareDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL FormulareDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: FormulareDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL FormulareDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Formulare, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: FormulareDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Formulare." LOG_
		}
	} else {
		_LOG << "Error: FormulareDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormulareDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: FormulareDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: FormulareDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormulareDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "FormulareDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select name, menuname, menuhilfe, eventname, toolbarimage, anwendungid, typ,  id from formulare") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Formulare would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Formulare found. All Formulare may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qname)
		UAP(lb_I_String, qmenuname)
		UAP(lb_I_String, qmenuhilfe)
		UAP(lb_I_String, qeventname)
		UAP(lb_I_String, qtoolbarimage)
		UAP(lb_I_Long, qanwendungid)
		UAP(lb_I_Long, qtyp)

		// Copy values

		qname = q->getAsString(1);
		qmenuname = q->getAsString(2);
		qmenuhilfe = q->getAsString(3);
		qeventname = q->getAsString(4);
		qtoolbarimage = q->getAsString(5);
		qanwendungid = q->getAsLong(6);
		qtyp = q->getAsLong(7);
		qID = q->getAsLong(8);

		owningObject->addFormulare(qname->charrep(), qmenuname->charrep(), qmenuhilfe->charrep(), qeventname->charrep(), qtoolbarimage->charrep(), qanwendungid->getData(), qtyp->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qname = q->getAsString(1);
			qmenuname = q->getAsString(2);
			qmenuhilfe = q->getAsString(3);
			qeventname = q->getAsString(4);
			qtoolbarimage = q->getAsString(5);
			qanwendungid = q->getAsLong(6);
			qtyp = q->getAsLong(7);
			qID = q->getAsLong(8);

			owningObject->addFormulare(qname->charrep(), qmenuname->charrep(), qmenuhilfe->charrep(), qeventname->charrep(), qtoolbarimage->charrep(), qanwendungid->getData(), qtyp->getData(),  qID->getData());
		}
	}
}



class lbPluginFormulareDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginFormulareDBReaderExtension();
	
	virtual ~lbPluginFormulareDBReaderExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormulareDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormulareDBReaderExtension, lbPluginFormulareDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginFormulareDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormulareDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormulareDBReaderExtension::lbPluginFormulareDBReaderExtension() {
	_CL_VERBOSE << "lbPluginFormulareDBReaderExtension::lbPluginFormulareDBReaderExtension() called.\n" LOG_
}

lbPluginFormulareDBReaderExtension::~lbPluginFormulareDBReaderExtension() {
	_CL_VERBOSE << "lbPluginFormulareDBReaderExtension::~lbPluginFormulareDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormulareDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormulareDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormulareDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFormulareDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormulareDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormulareModelExtension == NULL) {
		FormulareDBReaderExtension* FormulareModelExtension = new FormulareDBReaderExtension();
		
	
		QI(FormulareModelExtension, lb_I_Unknown, ukFormulareModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormulareModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormulareDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormulareModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FormulareDBReaderExtension* FormulareModelExtension = new FormulareDBReaderExtension();
		
	
		QI(FormulareModelExtension, lb_I_Unknown, ukFormulareModelExtension)
	}
	
	lb_I_Unknown* r = ukFormulareModelExtension.getPtr();
	ukFormulareModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormulareDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormulareModelExtension != NULL) {
                ukFormulareModelExtension--;
                ukFormulareModelExtension.resetPtr();
        }
}

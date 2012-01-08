
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
#include <DBReader_Formulars.h>

IMPLEMENT_FUNCTOR(instanceOfFormularsDBReaderExtension, FormularsDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(FormularsDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

FormularsDBReaderExtension::FormularsDBReaderExtension() {
	_CL_VERBOSE << "FormularsDBReaderExtension::FormularsDBReaderExtension() called." LOG_
}

FormularsDBReaderExtension::~FormularsDBReaderExtension() {
	_CL_VERBOSE << "FormularsDBReaderExtension::~FormularsDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL FormularsDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: FormularsDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL FormularsDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Formulars, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: FormularsDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Formulars." LOG_
		}
	} else {
		_LOG << "Error: FormularsDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormularsDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: FormularsDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: FormularsDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormularsDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "FormularsDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select name, menuname, menuhilfe, eventname, toolbarimage, anwendungid, typ,  id from formulare") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Formulars would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Formulars found. All Formulars may be deleted accidantly." LOG_
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

		owningObject->addFormulars(qname->charrep(), qmenuname->charrep(), qmenuhilfe->charrep(), qeventname->charrep(), qtoolbarimage->charrep(), qanwendungid->getData(), qtyp->getData(),  qID->getData());

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

			owningObject->addFormulars(qname->charrep(), qmenuname->charrep(), qmenuhilfe->charrep(), qeventname->charrep(), qtoolbarimage->charrep(), qanwendungid->getData(), qtyp->getData(),  qID->getData());
		}
	}
}



class lbPluginFormularsDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginFormularsDBReaderExtension();
	
	virtual ~lbPluginFormularsDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormularsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormularsDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormularsDBReaderExtension, lbPluginFormularsDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginFormularsDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormularsDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormularsDBReaderExtension::lbPluginFormularsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginFormularsDBReaderExtension::lbPluginFormularsDBReaderExtension() called.\n" LOG_
}

lbPluginFormularsDBReaderExtension::~lbPluginFormularsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginFormularsDBReaderExtension::~lbPluginFormularsDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormularsDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormularsDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormularsDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFormularsDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormularsDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularsModelExtension == NULL) {
		FormularsDBReaderExtension* FormularsModelExtension = new FormularsDBReaderExtension();
		
	
		QI(FormularsModelExtension, lb_I_Unknown, ukFormularsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormularsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormularsDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FormularsDBReaderExtension* FormularsModelExtension = new FormularsDBReaderExtension();
		
	
		QI(FormularsModelExtension, lb_I_Unknown, ukFormularsModelExtension)
	}
	
	lb_I_Unknown* r = ukFormularsModelExtension.getPtr();
	ukFormularsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormularsDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormularsModelExtension != NULL) {
                ukFormularsModelExtension--;
                ukFormularsModelExtension.resetPtr();
        }
}

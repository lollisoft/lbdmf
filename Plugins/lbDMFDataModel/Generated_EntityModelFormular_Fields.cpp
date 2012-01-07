
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
#include <Generated_EntityModelFormular_Fields.h>

IMPLEMENT_FUNCTOR(instanceOflbFormular_FieldsModel, lbFormular_FieldsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbFormular_FieldsModel)
	ADD_INTERFACE(lb_I_Formular_Fields)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbFormular_FieldsModel)

void		LB_STDCALL lbFormular_FieldsModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbFormular_FieldsModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbFormular_FieldsModel::lbFormular_FieldsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Formular_Fields)

    REQUEST(getModuleInstance(), lb_I_String, currentfkname)
    REQUEST(getModuleInstance(), lb_I_String, currentfktable)
    REQUEST(getModuleInstance(), lb_I_String, currentdbtype)
    REQUEST(getModuleInstance(), lb_I_Boolean, currentisforeignkey)
    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_String, currenttablename)
    REQUEST(getModuleInstance(), lb_I_Long, currentformularid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentFormular_FieldsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbFormular_FieldsModel::lbFormular_FieldsModel() called." LOG_
}

lbFormular_FieldsModel::~lbFormular_FieldsModel() {
	_CL_VERBOSE << "lbFormular_FieldsModel::~lbFormular_FieldsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbFormular_FieldsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbFormular_FieldsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbFormular_FieldsModel::addFormular_Fields(const char* _fkname, const char* _fktable, const char* _dbtype, bool _isforeignkey, const char* _name, const char* _tablename, long _formularid,  long _Formular_FieldsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __fkname)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __fktable)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __dbtype)
    UAP_REQUEST(getModuleInstance(), lb_I_Boolean, __isforeignkey)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __tablename)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __formularid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __Formular_FieldsID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__fkname = _fkname;
    *__fktable = _fktable;
    *__dbtype = _dbtype;
    __isforeignkey->setData(_isforeignkey);
    *__name = _name;
    *__tablename = _tablename;
    __formularid->setData(_formularid);

	
	__Formular_FieldsID->setData(_Formular_FieldsID);

    *paramname = "fkname";
    param->setUAPString(*&paramname, *&__fkname);
    *paramname = "fktable";
    param->setUAPString(*&paramname, *&__fktable);
    *paramname = "dbtype";
    param->setUAPString(*&paramname, *&__dbtype);
    *paramname = "isforeignkey";
    param->setUAPBoolean(*&paramname, *&__isforeignkey);
    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);
    *paramname = "tablename";
    param->setUAPString(*&paramname, *&__tablename);
    *paramname = "formularid";
    param->setUAPLong(*&paramname, *&__formularid);


	*paramname = "Formular_FieldsID";
	param->setUAPLong(*&paramname, *&__Formular_FieldsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__Formular_FieldsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Formular_Fields->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbFormular_FieldsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Formular_Fields->finishIteration();
	while (hasMoreFormular_Fields()) {
		setNextFormular_Fields();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Formular_Fields->remove(&key);
			Formular_Fields->finishIteration();
		}
	}
}

void		LB_STDCALL lbFormular_FieldsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Formular_Fields->finishIteration();
	while (hasMoreFormular_Fields()) {
		setNextFormular_Fields();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Formular_Fields->remove(&key);
			Formular_Fields->finishIteration();
		}
	}
}

bool LB_STDCALL lbFormular_FieldsModel::selectFormular_Fields(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Formular_Fields->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "fkname";
    param->getUAPString(*&paramname, *&currentfkname);
    *paramname = "fktable";
    param->getUAPString(*&paramname, *&currentfktable);
    *paramname = "dbtype";
    param->getUAPString(*&paramname, *&currentdbtype);
    *paramname = "isforeignkey";
    param->getUAPBoolean(*&paramname, *&currentisforeignkey);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "tablename";
    param->getUAPString(*&paramname, *&currenttablename);
    *paramname = "formularid";
    param->getUAPLong(*&paramname, *&currentformularid);


		*paramname = "Formular_FieldsID";
		param->getUAPLong(*&paramname, *&currentFormular_FieldsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbFormular_FieldsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbFormular_FieldsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbFormular_FieldsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbFormular_FieldsModel::getFormular_FieldsCount() {
	return Formular_Fields->Count();
}

bool  LB_STDCALL lbFormular_FieldsModel::hasMoreFormular_Fields() {
	return (Formular_Fields->hasMoreElements() == 1);
}

void  LB_STDCALL lbFormular_FieldsModel::setNextFormular_Fields() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Formular_Fields->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "fkname";
    param->getUAPString(*&paramname, *&currentfkname);
    *paramname = "fktable";
    param->getUAPString(*&paramname, *&currentfktable);
    *paramname = "dbtype";
    param->getUAPString(*&paramname, *&currentdbtype);
    *paramname = "isforeignkey";
    param->getUAPBoolean(*&paramname, *&currentisforeignkey);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "tablename";
    param->getUAPString(*&paramname, *&currenttablename);
    *paramname = "formularid";
    param->getUAPLong(*&paramname, *&currentformularid);

	*paramname = "Formular_FieldsID";
	param->getUAPLong(*&paramname, *&currentFormular_FieldsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbFormular_FieldsModel::finishFormular_FieldsIteration() {
	Formular_Fields->finishIteration();
}

long LB_STDCALL lbFormular_FieldsModel::get_id() {
	return currentFormular_FieldsID->getData();
}


char* LB_STDCALL lbFormular_FieldsModel::get_fkname() {
	return currentfkname->charrep();
}

char* LB_STDCALL lbFormular_FieldsModel::get_fktable() {
	return currentfktable->charrep();
}

char* LB_STDCALL lbFormular_FieldsModel::get_dbtype() {
	return currentdbtype->charrep();
}

bool LB_STDCALL lbFormular_FieldsModel::get_isforeignkey() {
	return currentisforeignkey->getData();
}

char* LB_STDCALL lbFormular_FieldsModel::get_name() {
	return currentname->charrep();
}

char* LB_STDCALL lbFormular_FieldsModel::get_tablename() {
	return currenttablename->charrep();
}

long LB_STDCALL lbFormular_FieldsModel::get_formularid() {
	return currentformularid->getData();
}


class lbPluginFormular_FieldsModel : public lb_I_PluginImpl {
public:
	lbPluginFormular_FieldsModel();
	
	virtual ~lbPluginFormular_FieldsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormular_FieldsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormular_FieldsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormular_FieldsModel, lbPluginFormular_FieldsModel)

lbErrCodes LB_STDCALL lbPluginFormular_FieldsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormular_FieldsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormular_FieldsModel::lbPluginFormular_FieldsModel() {
	_CL_VERBOSE << "lbPluginFormular_FieldsModel::lbPluginFormular_FieldsModel() called.\n" LOG_
}

lbPluginFormular_FieldsModel::~lbPluginFormular_FieldsModel() {
	_CL_VERBOSE << "lbPluginFormular_FieldsModel::~lbPluginFormular_FieldsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormular_FieldsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormular_FieldsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormular_FieldsModel::initialize() {
}
	
bool LB_STDCALL lbPluginFormular_FieldsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_FieldsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_FieldsModel == NULL) {
		lbFormular_FieldsModel* Formular_FieldsModel = new lbFormular_FieldsModel();
		
	
		QI(Formular_FieldsModel, lb_I_Unknown, ukFormular_FieldsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormular_FieldsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_FieldsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_FieldsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbFormular_FieldsModel* Formular_FieldsModel = new lbFormular_FieldsModel();
		
	
		QI(Formular_FieldsModel, lb_I_Unknown, ukFormular_FieldsModel)
	}
	
	lb_I_Unknown* r = ukFormular_FieldsModel.getPtr();
	ukFormular_FieldsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormular_FieldsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormular_FieldsModel != NULL) {
                ukFormular_FieldsModel--;
                ukFormular_FieldsModel.resetPtr();
        }
}


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

IMPLEMENT_FUNCTOR(instanceOfFormular_FieldsModel, Formular_FieldsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(Formular_FieldsModel)
	ADD_INTERFACE(lb_I_Formular_Fields)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(Formular_FieldsModel)

Formular_FieldsModel::Formular_FieldsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Formular_Fields)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currentfkname)
    REQUEST(getModuleInstance(), lb_I_String, currentfktable)
    REQUEST(getModuleInstance(), lb_I_String, currentdbtype)
    REQUEST(getModuleInstance(), lb_I_Boolean, currentisforeignkey)
    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_String, currenttablename)
    REQUEST(getModuleInstance(), lb_I_Long, currentformularid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentFormular_FieldsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "Formular_FieldsModel::Formular_FieldsModel() called." LOG_
}

Formular_FieldsModel::~Formular_FieldsModel() {
	_CL_VERBOSE << "Formular_FieldsModel::~Formular_FieldsModel() called." LOG_
}

lbErrCodes LB_STDCALL Formular_FieldsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: Formular_FieldsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL Formular_FieldsModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Formular_Fields";
	
	UAP(lb_I_KeyBase, key)
	QI(CNS, lb_I_KeyBase, key)
	
	if (objectExtensions->exists(*&key)) {
		UAP(lb_I_ExtensionObject, ex)
		UAP(lb_I_KeyBase, key)
		
		uk = objectExtensions->getElement(*&key);
		QI(uk, lb_I_ExtensionObject, ex)
		ex++;
		return ex;
	}
		
	AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_ExtensionObject, dbbackend, extension, "'database plugin'")
	if (extension == NULL) {
		_LOG << "Error: Did not find extension object for given namespace " << CNS->charrep() LOG_
		return NULL;
	}
	extension++;
	return extension.getPtr();
}

lb_I_ExtensionObject* LB_STDCALL Formular_FieldsModel::getExtension(const char* contextnamespace) {
/*
	These extensions may be supported until yet. At least the following are required.

	Required
	
	ADD_PLUGIN(lbPluginInputStream,			InputStreamVisitor)
	ADD_PLUGIN(lbPluginDatabaseInputStream,	DatabaseInputStreamVisitor)
	ADD_PLUGIN(lbPluginOutputStream,		OutputStreamVisitor)
	ADD_PLUGIN(lbPluginXMLOutputStream,		XMLOutputStreamVisitor)

	May
	
	ADD_PLUGIN(lbPluginXMLInputStream,		XMLInputStreamVisitor)
	ADD_PLUGIN(lbPluginJSONOutputStream,	JSONOutputStreamVisitor)
	ADD_PLUGIN(lbPluginJSONInputStream,		JSONInputStreamVisitor)
*/
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	return getExtension(*&CNS);
}

	
lbErrCodes LB_STDCALL Formular_FieldsModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL Formular_FieldsModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL Formular_FieldsModel::addFormular_Fields(const char* _fkname, const char* _fktable, const char* _dbtype, bool _isforeignkey, const char* _name, const char* _tablename, long _formularid,  long _Formular_FieldsID) {
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

void		LB_STDCALL Formular_FieldsModel::deleteUnmarked() {
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

void		LB_STDCALL Formular_FieldsModel::deleteMarked() {
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

bool LB_STDCALL Formular_FieldsModel::selectFormular_Fields(long user_id) {
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

bool LB_STDCALL Formular_FieldsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL Formular_FieldsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL Formular_FieldsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL Formular_FieldsModel::getFormular_FieldsCount() {
	return Formular_Fields->Count();
}

bool  LB_STDCALL Formular_FieldsModel::hasMoreFormular_Fields() {
	return (Formular_Fields->hasMoreElements() == 1);
}

void  LB_STDCALL Formular_FieldsModel::setNextFormular_Fields() {
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

void  LB_STDCALL Formular_FieldsModel::finishFormular_FieldsIteration() {
	Formular_Fields->finishIteration();
}

long LB_STDCALL Formular_FieldsModel::get_id() {
	return currentFormular_FieldsID->getData();
}


char* LB_STDCALL Formular_FieldsModel::get_fkname() {
	return currentfkname->charrep();
}

char* LB_STDCALL Formular_FieldsModel::get_fktable() {
	return currentfktable->charrep();
}

char* LB_STDCALL Formular_FieldsModel::get_dbtype() {
	return currentdbtype->charrep();
}

bool LB_STDCALL Formular_FieldsModel::get_isforeignkey() {
	return currentisforeignkey->getData();
}

char* LB_STDCALL Formular_FieldsModel::get_name() {
	return currentname->charrep();
}

char* LB_STDCALL Formular_FieldsModel::get_tablename() {
	return currenttablename->charrep();
}

long LB_STDCALL Formular_FieldsModel::get_formularid() {
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
		Formular_FieldsModel* aFormular_FieldsModel = new Formular_FieldsModel();
		
	
		QI(aFormular_FieldsModel, lb_I_Unknown, ukFormular_FieldsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormular_FieldsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_FieldsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_FieldsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Formular_FieldsModel* aFormular_FieldsModel = new Formular_FieldsModel();
		
	
		QI(aFormular_FieldsModel, lb_I_Unknown, ukFormular_FieldsModel)
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

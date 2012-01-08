
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
#include <Generated_EntityModelColumn_Types.h>

IMPLEMENT_FUNCTOR(instanceOfColumn_TypesModel, Column_TypesModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(Column_TypesModel)
	ADD_INTERFACE(lb_I_Column_Types)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(Column_TypesModel)

Column_TypesModel::Column_TypesModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Column_Types)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_String, currenttablename)
    REQUEST(getModuleInstance(), lb_I_Boolean, currentro)
    REQUEST(getModuleInstance(), lb_I_Boolean, currentspecialcolumn)
    REQUEST(getModuleInstance(), lb_I_String, currentcontroltype)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentColumn_TypesID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "Column_TypesModel::Column_TypesModel() called." LOG_
}

Column_TypesModel::~Column_TypesModel() {
	_CL_VERBOSE << "Column_TypesModel::~Column_TypesModel() called." LOG_
}

lbErrCodes LB_STDCALL Column_TypesModel::setData(lb_I_Unknown*) {
	_LOG << "Error: Column_TypesModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL Column_TypesModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Column_Types";
	
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

lb_I_ExtensionObject* LB_STDCALL Column_TypesModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL Column_TypesModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL Column_TypesModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL Column_TypesModel::addColumn_Types(const char* _name, const char* _tablename, bool _ro, bool _specialcolumn, const char* _controltype,  long _Column_TypesID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __tablename)
    UAP_REQUEST(getModuleInstance(), lb_I_Boolean, __ro)
    UAP_REQUEST(getModuleInstance(), lb_I_Boolean, __specialcolumn)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __controltype)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __Column_TypesID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__name = _name;
    *__tablename = _tablename;
    __ro->setData(_ro);
    __specialcolumn->setData(_specialcolumn);
    *__controltype = _controltype;

	
	__Column_TypesID->setData(_Column_TypesID);

    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);
    *paramname = "tablename";
    param->setUAPString(*&paramname, *&__tablename);
    *paramname = "ro";
    param->setUAPBoolean(*&paramname, *&__ro);
    *paramname = "specialcolumn";
    param->setUAPBoolean(*&paramname, *&__specialcolumn);
    *paramname = "controltype";
    param->setUAPString(*&paramname, *&__controltype);


	*paramname = "Column_TypesID";
	param->setUAPLong(*&paramname, *&__Column_TypesID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__Column_TypesID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Column_Types->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL Column_TypesModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Column_Types->finishIteration();
	while (hasMoreColumn_Types()) {
		setNextColumn_Types();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Column_Types->remove(&key);
			Column_Types->finishIteration();
		}
	}
}

void		LB_STDCALL Column_TypesModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Column_Types->finishIteration();
	while (hasMoreColumn_Types()) {
		setNextColumn_Types();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Column_Types->remove(&key);
			Column_Types->finishIteration();
		}
	}
}

bool LB_STDCALL Column_TypesModel::selectColumn_Types(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Column_Types->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "tablename";
    param->getUAPString(*&paramname, *&currenttablename);
    *paramname = "ro";
    param->getUAPBoolean(*&paramname, *&currentro);
    *paramname = "specialcolumn";
    param->getUAPBoolean(*&paramname, *&currentspecialcolumn);
    *paramname = "controltype";
    param->getUAPString(*&paramname, *&currentcontroltype);


		*paramname = "Column_TypesID";
		param->getUAPLong(*&paramname, *&currentColumn_TypesID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL Column_TypesModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL Column_TypesModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL Column_TypesModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL Column_TypesModel::getColumn_TypesCount() {
	return Column_Types->Count();
}

bool  LB_STDCALL Column_TypesModel::hasMoreColumn_Types() {
	return (Column_Types->hasMoreElements() == 1);
}

void  LB_STDCALL Column_TypesModel::setNextColumn_Types() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Column_Types->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "tablename";
    param->getUAPString(*&paramname, *&currenttablename);
    *paramname = "ro";
    param->getUAPBoolean(*&paramname, *&currentro);
    *paramname = "specialcolumn";
    param->getUAPBoolean(*&paramname, *&currentspecialcolumn);
    *paramname = "controltype";
    param->getUAPString(*&paramname, *&currentcontroltype);

	*paramname = "Column_TypesID";
	param->getUAPLong(*&paramname, *&currentColumn_TypesID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL Column_TypesModel::finishColumn_TypesIteration() {
	Column_Types->finishIteration();
}

long LB_STDCALL Column_TypesModel::get_id() {
	return currentColumn_TypesID->getData();
}


char* LB_STDCALL Column_TypesModel::get_name() {
	return currentname->charrep();
}

char* LB_STDCALL Column_TypesModel::get_tablename() {
	return currenttablename->charrep();
}

bool LB_STDCALL Column_TypesModel::get_ro() {
	return currentro->getData();
}

bool LB_STDCALL Column_TypesModel::get_specialcolumn() {
	return currentspecialcolumn->getData();
}

char* LB_STDCALL Column_TypesModel::get_controltype() {
	return currentcontroltype->charrep();
}


class lbPluginColumn_TypesModel : public lb_I_PluginImpl {
public:
	lbPluginColumn_TypesModel();
	
	virtual ~lbPluginColumn_TypesModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukColumn_TypesModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginColumn_TypesModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginColumn_TypesModel, lbPluginColumn_TypesModel)

lbErrCodes LB_STDCALL lbPluginColumn_TypesModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginColumn_TypesModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginColumn_TypesModel::lbPluginColumn_TypesModel() {
	_CL_VERBOSE << "lbPluginColumn_TypesModel::lbPluginColumn_TypesModel() called.\n" LOG_
}

lbPluginColumn_TypesModel::~lbPluginColumn_TypesModel() {
	_CL_VERBOSE << "lbPluginColumn_TypesModel::~lbPluginColumn_TypesModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginColumn_TypesModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginColumn_TypesModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginColumn_TypesModel::initialize() {
}
	
bool LB_STDCALL lbPluginColumn_TypesModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginColumn_TypesModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukColumn_TypesModel == NULL) {
		Column_TypesModel* aColumn_TypesModel = new Column_TypesModel();
		
	
		QI(aColumn_TypesModel, lb_I_Unknown, ukColumn_TypesModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukColumn_TypesModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginColumn_TypesModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukColumn_TypesModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Column_TypesModel* aColumn_TypesModel = new Column_TypesModel();
		
	
		QI(aColumn_TypesModel, lb_I_Unknown, ukColumn_TypesModel)
	}
	
	lb_I_Unknown* r = ukColumn_TypesModel.getPtr();
	ukColumn_TypesModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginColumn_TypesModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukColumn_TypesModel != NULL) {
                ukColumn_TypesModel--;
                ukColumn_TypesModel.resetPtr();
        }
}

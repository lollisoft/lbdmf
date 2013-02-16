
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
#include <Generated_EntityModelFKPK_Mapping.h>

IMPLEMENT_FUNCTOR(instanceOfFKPK_MappingModel, FKPK_MappingModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(FKPK_MappingModel)
	ADD_INTERFACE(lb_I_FKPK_Mapping)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(FKPK_MappingModel)

FKPK_MappingModel::FKPK_MappingModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, FKPK_Mapping)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currentpktable)
    REQUEST(getModuleInstance(), lb_I_String, currentpkname)
    REQUEST(getModuleInstance(), lb_I_String, currentfktable)
    REQUEST(getModuleInstance(), lb_I_String, currentfkname)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentFKPK_MappingID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "FKPK_MappingModel::FKPK_MappingModel() called." LOG_
}

FKPK_MappingModel::~FKPK_MappingModel() {
	_CL_VERBOSE << "FKPK_MappingModel::~FKPK_MappingModel() called." LOG_
}

lbErrCodes LB_STDCALL FKPK_MappingModel::setData(lb_I_Unknown*) {
	_LOG << "Error: FKPK_MappingModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL FKPK_MappingModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_FKPK_Mapping";
	
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

lb_I_ExtensionObject* LB_STDCALL FKPK_MappingModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL FKPK_MappingModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL FKPK_MappingModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL FKPK_MappingModel::add(const char* _pktable, const char* _pkname, const char* _fktable, const char* _fkname,  long _FKPK_MappingID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __pktable)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __pkname)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __fktable)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __fkname)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __FKPK_MappingID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__pktable = _pktable;
    *__pkname = _pkname;
    *__fktable = _fktable;
    *__fkname = _fkname;

	
	__FKPK_MappingID->setData(_FKPK_MappingID);

    *paramname = "pktable";
    param->setUAPString(*&paramname, *&__pktable);
    *paramname = "pkname";
    param->setUAPString(*&paramname, *&__pkname);
    *paramname = "fktable";
    param->setUAPString(*&paramname, *&__fktable);
    *paramname = "fkname";
    param->setUAPString(*&paramname, *&__fkname);


	*paramname = "FKPK_MappingID";
	param->setUAPLong(*&paramname, *&__FKPK_MappingID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__FKPK_MappingID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	FKPK_Mapping->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL FKPK_MappingModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	FKPK_Mapping->finishIteration();
	while (hasMoreFKPK_Mapping()) {
		setNextFKPK_Mapping();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			FKPK_Mapping->remove(&key);
			FKPK_Mapping->finishIteration();
		}
	}
}

void		LB_STDCALL FKPK_MappingModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	FKPK_Mapping->finishIteration();
	while (hasMoreFKPK_Mapping()) {
		setNextFKPK_Mapping();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			FKPK_Mapping->remove(&key);
			FKPK_Mapping->finishIteration();
		}
	}
}

bool LB_STDCALL FKPK_MappingModel::selectById(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = FKPK_Mapping->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "pktable";
    param->getUAPString(*&paramname, *&currentpktable);
    *paramname = "pkname";
    param->getUAPString(*&paramname, *&currentpkname);
    *paramname = "fktable";
    param->getUAPString(*&paramname, *&currentfktable);
    *paramname = "fkname";
    param->getUAPString(*&paramname, *&currentfkname);


		*paramname = "FKPK_MappingID";
		param->getUAPLong(*&paramname, *&currentFKPK_MappingID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL FKPK_MappingModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL FKPK_MappingModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL FKPK_MappingModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL FKPK_MappingModel::Count() {
	return FKPK_Mapping->Count();
}

bool  LB_STDCALL FKPK_MappingModel::hasMoreElements() {
	return (FKPK_Mapping->hasMoreElements() == 1);
}

void  LB_STDCALL FKPK_MappingModel::setNextElement() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = FKPK_Mapping->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "pktable";
    param->getUAPString(*&paramname, *&currentpktable);
    *paramname = "pkname";
    param->getUAPString(*&paramname, *&currentpkname);
    *paramname = "fktable";
    param->getUAPString(*&paramname, *&currentfktable);
    *paramname = "fkname";
    param->getUAPString(*&paramname, *&currentfkname);

	*paramname = "FKPK_MappingID";
	param->getUAPLong(*&paramname, *&currentFKPK_MappingID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL FKPK_MappingModel::finishIteration() {
	FKPK_Mapping->finishIteration();
}

long LB_STDCALL FKPK_MappingModel::get_id() {
	return currentFKPK_MappingID->getData();
}


char* LB_STDCALL FKPK_MappingModel::get_pktable() {
	return currentpktable->charrep();
}

char* LB_STDCALL FKPK_MappingModel::get_pkname() {
	return currentpkname->charrep();
}

char* LB_STDCALL FKPK_MappingModel::get_fktable() {
	return currentfktable->charrep();
}

char* LB_STDCALL FKPK_MappingModel::get_fkname() {
	return currentfkname->charrep();
}


class lbPluginFKPK_MappingModel : public lb_I_PluginImpl {
public:
	lbPluginFKPK_MappingModel();
	
	virtual ~lbPluginFKPK_MappingModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFKPK_MappingModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFKPK_MappingModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFKPK_MappingModel, lbPluginFKPK_MappingModel)

lbErrCodes LB_STDCALL lbPluginFKPK_MappingModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFKPK_MappingModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFKPK_MappingModel::lbPluginFKPK_MappingModel() {
	_CL_VERBOSE << "lbPluginFKPK_MappingModel::lbPluginFKPK_MappingModel() called.\n" LOG_
}

lbPluginFKPK_MappingModel::~lbPluginFKPK_MappingModel() {
	_CL_VERBOSE << "lbPluginFKPK_MappingModel::~lbPluginFKPK_MappingModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginFKPK_MappingModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFKPK_MappingModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFKPK_MappingModel::initialize() {
}
	
bool LB_STDCALL lbPluginFKPK_MappingModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFKPK_MappingModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFKPK_MappingModel == NULL) {
		FKPK_MappingModel* aFKPK_MappingModel = new FKPK_MappingModel();
		
	
		QI(aFKPK_MappingModel, lb_I_Unknown, ukFKPK_MappingModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFKPK_MappingModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFKPK_MappingModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFKPK_MappingModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FKPK_MappingModel* aFKPK_MappingModel = new FKPK_MappingModel();
		
	
		QI(aFKPK_MappingModel, lb_I_Unknown, ukFKPK_MappingModel)
	}
	
	lb_I_Unknown* r = ukFKPK_MappingModel.getPtr();
	ukFKPK_MappingModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFKPK_MappingModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFKPK_MappingModel != NULL) {
                ukFKPK_MappingModel--;
                ukFKPK_MappingModel.resetPtr();
        }
}

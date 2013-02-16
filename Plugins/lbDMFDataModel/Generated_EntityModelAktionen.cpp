
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
#include <Generated_EntityModelAktionen.h>

IMPLEMENT_FUNCTOR(instanceOfAktionenModel, AktionenModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(AktionenModel)
	ADD_INTERFACE(lb_I_Aktionen)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(AktionenModel)

AktionenModel::AktionenModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Aktionen)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currenttarget)
    REQUEST(getModuleInstance(), lb_I_String, currentsource)
    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_Long, currenttyp)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentAktionenID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "AktionenModel::AktionenModel() called." LOG_
}

AktionenModel::~AktionenModel() {
	_CL_VERBOSE << "AktionenModel::~AktionenModel() called." LOG_
}

lbErrCodes LB_STDCALL AktionenModel::setData(lb_I_Unknown*) {
	_LOG << "Error: AktionenModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL AktionenModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Aktionen";
	
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

lb_I_ExtensionObject* LB_STDCALL AktionenModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL AktionenModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL AktionenModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL AktionenModel::addAktionen(const char* _target, const char* _source, const char* _name, long _typ,  long _AktionenID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __target)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __source)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __typ)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __AktionenID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__target = _target;
    *__source = _source;
    *__name = _name;
    __typ->setData(_typ);

	
	__AktionenID->setData(_AktionenID);

    *paramname = "target";
    param->setUAPString(*&paramname, *&__target);
    *paramname = "source";
    param->setUAPString(*&paramname, *&__source);
    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);
    *paramname = "typ";
    param->setUAPLong(*&paramname, *&__typ);


	*paramname = "AktionenID";
	param->setUAPLong(*&paramname, *&__AktionenID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__AktionenID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Aktionen->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL AktionenModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Aktionen->finishIteration();
	while (hasMoreAktionen()) {
		setNextAktionen();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Aktionen->remove(&key);
			Aktionen->finishIteration();
		}
	}
}

void		LB_STDCALL AktionenModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Aktionen->finishIteration();
	while (hasMoreAktionen()) {
		setNextAktionen();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Aktionen->remove(&key);
			Aktionen->finishIteration();
		}
	}
}

bool LB_STDCALL AktionenModel::selectAktionen(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Aktionen->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "target";
    param->getUAPString(*&paramname, *&currenttarget);
    *paramname = "source";
    param->getUAPString(*&paramname, *&currentsource);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "typ";
    param->getUAPLong(*&paramname, *&currenttyp);


		*paramname = "AktionenID";
		param->getUAPLong(*&paramname, *&currentAktionenID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL AktionenModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL AktionenModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL AktionenModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL AktionenModel::getAktionenCount() {
	return Aktionen->Count();
}

bool  LB_STDCALL AktionenModel::hasMoreAktionen() {
	return (Aktionen->hasMoreElements() == 1);
}

void  LB_STDCALL AktionenModel::setNextAktionen() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Aktionen->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "target";
    param->getUAPString(*&paramname, *&currenttarget);
    *paramname = "source";
    param->getUAPString(*&paramname, *&currentsource);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "typ";
    param->getUAPLong(*&paramname, *&currenttyp);

	*paramname = "AktionenID";
	param->getUAPLong(*&paramname, *&currentAktionenID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL AktionenModel::finishAktionenIteration() {
	Aktionen->finishIteration();
}

long LB_STDCALL AktionenModel::get_id() {
	return currentAktionenID->getData();
}


char* LB_STDCALL AktionenModel::get_target() {
	return currenttarget->charrep();
}

char* LB_STDCALL AktionenModel::get_source() {
	return currentsource->charrep();
}

char* LB_STDCALL AktionenModel::get_name() {
	return currentname->charrep();
}

long LB_STDCALL AktionenModel::get_typ() {
	return currenttyp->getData();
}


class lbPluginAktionenModel : public lb_I_PluginImpl {
public:
	lbPluginAktionenModel();
	
	virtual ~lbPluginAktionenModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAktionenModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAktionenModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAktionenModel, lbPluginAktionenModel)

lbErrCodes LB_STDCALL lbPluginAktionenModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAktionenModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAktionenModel::lbPluginAktionenModel() {
	_CL_VERBOSE << "lbPluginAktionenModel::lbPluginAktionenModel() called.\n" LOG_
}

lbPluginAktionenModel::~lbPluginAktionenModel() {
	_CL_VERBOSE << "lbPluginAktionenModel::~lbPluginAktionenModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginAktionenModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAktionenModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAktionenModel::initialize() {
}
	
bool LB_STDCALL lbPluginAktionenModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAktionenModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAktionenModel == NULL) {
		AktionenModel* aAktionenModel = new AktionenModel();
		
	
		QI(aAktionenModel, lb_I_Unknown, ukAktionenModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAktionenModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAktionenModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAktionenModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		AktionenModel* aAktionenModel = new AktionenModel();
		
	
		QI(aAktionenModel, lb_I_Unknown, ukAktionenModel)
	}
	
	lb_I_Unknown* r = ukAktionenModel.getPtr();
	ukAktionenModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAktionenModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAktionenModel != NULL) {
                ukAktionenModel--;
                ukAktionenModel.resetPtr();
        }
}

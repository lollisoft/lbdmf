
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
#include <Generated_EntityModelApplications_Formulars.h>

IMPLEMENT_FUNCTOR(instanceOfApplications_FormularsModel, Applications_FormularsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(Applications_FormularsModel)
	ADD_INTERFACE(lb_I_Applications_Formulars)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(Applications_FormularsModel)

Applications_FormularsModel::Applications_FormularsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Applications_Formulars)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_Long, currentanwendungid)
    REQUEST(getModuleInstance(), lb_I_Long, currentformularid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentApplications_FormularsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "Applications_FormularsModel::Applications_FormularsModel() called." LOG_
}

Applications_FormularsModel::~Applications_FormularsModel() {
	_CL_VERBOSE << "Applications_FormularsModel::~Applications_FormularsModel() called." LOG_
}

lbErrCodes LB_STDCALL Applications_FormularsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: Applications_FormularsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL Applications_FormularsModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Applications_Formulars";
	
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

lb_I_ExtensionObject* LB_STDCALL Applications_FormularsModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL Applications_FormularsModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL Applications_FormularsModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL Applications_FormularsModel::add(long _anwendungid, long _formularid,  long _Applications_FormularsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_Long, __anwendungid)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __formularid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __Applications_FormularsID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    __anwendungid->setData(_anwendungid);
    __formularid->setData(_formularid);

	
	__Applications_FormularsID->setData(_Applications_FormularsID);

    *paramname = "anwendungid";
    param->setUAPLong(*&paramname, *&__anwendungid);
    *paramname = "formularid";
    param->setUAPLong(*&paramname, *&__formularid);


	*paramname = "Applications_FormularsID";
	param->setUAPLong(*&paramname, *&__Applications_FormularsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__Applications_FormularsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Applications_Formulars->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL Applications_FormularsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Applications_Formulars->finishIteration();
	while (hasMoreApplications_Formulars()) {
		setNextApplications_Formulars();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Applications_Formulars->remove(&key);
			Applications_Formulars->finishIteration();
		}
	}
}

void		LB_STDCALL Applications_FormularsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Applications_Formulars->finishIteration();
	while (hasMoreApplications_Formulars()) {
		setNextApplications_Formulars();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Applications_Formulars->remove(&key);
			Applications_Formulars->finishIteration();
		}
	}
}

bool LB_STDCALL Applications_FormularsModel::selectById(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Applications_Formulars->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "anwendungid";
    param->getUAPLong(*&paramname, *&currentanwendungid);
    *paramname = "formularid";
    param->getUAPLong(*&paramname, *&currentformularid);


		*paramname = "Applications_FormularsID";
		param->getUAPLong(*&paramname, *&currentApplications_FormularsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL Applications_FormularsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL Applications_FormularsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL Applications_FormularsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL Applications_FormularsModel::Count() {
	return Applications_Formulars->Count();
}

bool  LB_STDCALL Applications_FormularsModel::hasMoreElements() {
	return (Applications_Formulars->hasMoreElements() == 1);
}

void  LB_STDCALL Applications_FormularsModel::setNextElement() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Applications_Formulars->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "anwendungid";
    param->getUAPLong(*&paramname, *&currentanwendungid);
    *paramname = "formularid";
    param->getUAPLong(*&paramname, *&currentformularid);

	*paramname = "Applications_FormularsID";
	param->getUAPLong(*&paramname, *&currentApplications_FormularsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL Applications_FormularsModel::finishIteration() {
	Applications_Formulars->finishIteration();
}

long LB_STDCALL Applications_FormularsModel::get_id() {
	return currentApplications_FormularsID->getData();
}


long LB_STDCALL Applications_FormularsModel::get_anwendungid() {
	return currentanwendungid->getData();
}

long LB_STDCALL Applications_FormularsModel::get_formularid() {
	return currentformularid->getData();
}


class lbPluginApplications_FormularsModel : public lb_I_PluginImpl {
public:
	lbPluginApplications_FormularsModel();
	
	virtual ~lbPluginApplications_FormularsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukApplications_FormularsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginApplications_FormularsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginApplications_FormularsModel, lbPluginApplications_FormularsModel)

lbErrCodes LB_STDCALL lbPluginApplications_FormularsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginApplications_FormularsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginApplications_FormularsModel::lbPluginApplications_FormularsModel() {
	_CL_VERBOSE << "lbPluginApplications_FormularsModel::lbPluginApplications_FormularsModel() called.\n" LOG_
}

lbPluginApplications_FormularsModel::~lbPluginApplications_FormularsModel() {
	_CL_VERBOSE << "lbPluginApplications_FormularsModel::~lbPluginApplications_FormularsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginApplications_FormularsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginApplications_FormularsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginApplications_FormularsModel::initialize() {
}
	
bool LB_STDCALL lbPluginApplications_FormularsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginApplications_FormularsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplications_FormularsModel == NULL) {
		Applications_FormularsModel* aApplications_FormularsModel = new Applications_FormularsModel();
		
	
		QI(aApplications_FormularsModel, lb_I_Unknown, ukApplications_FormularsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukApplications_FormularsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginApplications_FormularsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplications_FormularsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Applications_FormularsModel* aApplications_FormularsModel = new Applications_FormularsModel();
		
	
		QI(aApplications_FormularsModel, lb_I_Unknown, ukApplications_FormularsModel)
	}
	
	lb_I_Unknown* r = ukApplications_FormularsModel.getPtr();
	ukApplications_FormularsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginApplications_FormularsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukApplications_FormularsModel != NULL) {
                ukApplications_FormularsModel--;
                ukApplications_FormularsModel.resetPtr();
        }
}

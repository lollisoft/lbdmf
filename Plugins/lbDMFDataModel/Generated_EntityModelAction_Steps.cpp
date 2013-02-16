
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
#include <Generated_EntityModelAction_Steps.h>

IMPLEMENT_FUNCTOR(instanceOfAction_StepsModel, Action_StepsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(Action_StepsModel)
	ADD_INTERFACE(lb_I_Action_Steps)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(Action_StepsModel)

Action_StepsModel::Action_StepsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Action_Steps)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currentbezeichnung)
    REQUEST(getModuleInstance(), lb_I_String, currentwhat)
    REQUEST(getModuleInstance(), lb_I_Long, currenta_order_nr)
    REQUEST(getModuleInstance(), lb_I_Long, currenttype)
    REQUEST(getModuleInstance(), lb_I_Long, currentactionid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentAction_StepsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "Action_StepsModel::Action_StepsModel() called." LOG_
}

Action_StepsModel::~Action_StepsModel() {
	_CL_VERBOSE << "Action_StepsModel::~Action_StepsModel() called." LOG_
}

lbErrCodes LB_STDCALL Action_StepsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: Action_StepsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL Action_StepsModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Action_Steps";
	
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

lb_I_ExtensionObject* LB_STDCALL Action_StepsModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL Action_StepsModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL Action_StepsModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL Action_StepsModel::add(const char* _bezeichnung, const char* _what, long _a_order_nr, long _type, long _actionid,  long _Action_StepsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __bezeichnung)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __what)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __a_order_nr)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __type)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __actionid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __Action_StepsID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__bezeichnung = _bezeichnung;
    *__what = _what;
    __a_order_nr->setData(_a_order_nr);
    __type->setData(_type);
    __actionid->setData(_actionid);

	
	__Action_StepsID->setData(_Action_StepsID);

    *paramname = "bezeichnung";
    param->setUAPString(*&paramname, *&__bezeichnung);
    *paramname = "what";
    param->setUAPString(*&paramname, *&__what);
    *paramname = "a_order_nr";
    param->setUAPLong(*&paramname, *&__a_order_nr);
    *paramname = "type";
    param->setUAPLong(*&paramname, *&__type);
    *paramname = "actionid";
    param->setUAPLong(*&paramname, *&__actionid);


	*paramname = "Action_StepsID";
	param->setUAPLong(*&paramname, *&__Action_StepsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__Action_StepsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Action_Steps->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL Action_StepsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Action_Steps->finishIteration();
	while (hasMoreAction_Steps()) {
		setNextAction_Steps();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Action_Steps->remove(&key);
			Action_Steps->finishIteration();
		}
	}
}

void		LB_STDCALL Action_StepsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Action_Steps->finishIteration();
	while (hasMoreAction_Steps()) {
		setNextAction_Steps();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Action_Steps->remove(&key);
			Action_Steps->finishIteration();
		}
	}
}

bool LB_STDCALL Action_StepsModel::selectById(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Action_Steps->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "bezeichnung";
    param->getUAPString(*&paramname, *&currentbezeichnung);
    *paramname = "what";
    param->getUAPString(*&paramname, *&currentwhat);
    *paramname = "a_order_nr";
    param->getUAPLong(*&paramname, *&currenta_order_nr);
    *paramname = "type";
    param->getUAPLong(*&paramname, *&currenttype);
    *paramname = "actionid";
    param->getUAPLong(*&paramname, *&currentactionid);


		*paramname = "Action_StepsID";
		param->getUAPLong(*&paramname, *&currentAction_StepsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL Action_StepsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL Action_StepsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL Action_StepsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL Action_StepsModel::Count() {
	return Action_Steps->Count();
}

bool  LB_STDCALL Action_StepsModel::hasMoreElements() {
	return (Action_Steps->hasMoreElements() == 1);
}

void  LB_STDCALL Action_StepsModel::setNextElement() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Action_Steps->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "bezeichnung";
    param->getUAPString(*&paramname, *&currentbezeichnung);
    *paramname = "what";
    param->getUAPString(*&paramname, *&currentwhat);
    *paramname = "a_order_nr";
    param->getUAPLong(*&paramname, *&currenta_order_nr);
    *paramname = "type";
    param->getUAPLong(*&paramname, *&currenttype);
    *paramname = "actionid";
    param->getUAPLong(*&paramname, *&currentactionid);

	*paramname = "Action_StepsID";
	param->getUAPLong(*&paramname, *&currentAction_StepsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL Action_StepsModel::finishIteration() {
	Action_Steps->finishIteration();
}

long LB_STDCALL Action_StepsModel::get_id() {
	return currentAction_StepsID->getData();
}


char* LB_STDCALL Action_StepsModel::get_bezeichnung() {
	return currentbezeichnung->charrep();
}

char* LB_STDCALL Action_StepsModel::get_what() {
	return currentwhat->charrep();
}

long LB_STDCALL Action_StepsModel::get_a_order_nr() {
	return currenta_order_nr->getData();
}

long LB_STDCALL Action_StepsModel::get_type() {
	return currenttype->getData();
}

long LB_STDCALL Action_StepsModel::get_actionid() {
	return currentactionid->getData();
}


class lbPluginAction_StepsModel : public lb_I_PluginImpl {
public:
	lbPluginAction_StepsModel();
	
	virtual ~lbPluginAction_StepsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAction_StepsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAction_StepsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAction_StepsModel, lbPluginAction_StepsModel)

lbErrCodes LB_STDCALL lbPluginAction_StepsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAction_StepsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAction_StepsModel::lbPluginAction_StepsModel() {
	_CL_VERBOSE << "lbPluginAction_StepsModel::lbPluginAction_StepsModel() called.\n" LOG_
}

lbPluginAction_StepsModel::~lbPluginAction_StepsModel() {
	_CL_VERBOSE << "lbPluginAction_StepsModel::~lbPluginAction_StepsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginAction_StepsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAction_StepsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAction_StepsModel::initialize() {
}
	
bool LB_STDCALL lbPluginAction_StepsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAction_StepsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_StepsModel == NULL) {
		Action_StepsModel* aAction_StepsModel = new Action_StepsModel();
		
	
		QI(aAction_StepsModel, lb_I_Unknown, ukAction_StepsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAction_StepsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAction_StepsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_StepsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Action_StepsModel* aAction_StepsModel = new Action_StepsModel();
		
	
		QI(aAction_StepsModel, lb_I_Unknown, ukAction_StepsModel)
	}
	
	lb_I_Unknown* r = ukAction_StepsModel.getPtr();
	ukAction_StepsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAction_StepsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAction_StepsModel != NULL) {
                ukAction_StepsModel--;
                ukAction_StepsModel.resetPtr();
        }
}


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
#include <Generated_EntityModelAction_Types.h>

IMPLEMENT_FUNCTOR(instanceOfAction_TypesModel, Action_TypesModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(Action_TypesModel)
	ADD_INTERFACE(lb_I_Action_Types)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(Action_TypesModel)

Action_TypesModel::Action_TypesModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Action_Types)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currentbezeichnung)
    REQUEST(getModuleInstance(), lb_I_String, currentaction_handler)
    REQUEST(getModuleInstance(), lb_I_String, currentmodule)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentAction_TypesID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "Action_TypesModel::Action_TypesModel() called." LOG_
}

Action_TypesModel::~Action_TypesModel() {
	_CL_VERBOSE << "Action_TypesModel::~Action_TypesModel() called." LOG_
}

lbErrCodes LB_STDCALL Action_TypesModel::setData(lb_I_Unknown*) {
	_LOG << "Error: Action_TypesModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL Action_TypesModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Action_Types";
	
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

lb_I_ExtensionObject* LB_STDCALL Action_TypesModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL Action_TypesModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL Action_TypesModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL Action_TypesModel::add(const char* _bezeichnung, const char* _action_handler, const char* _module,  long _Action_TypesID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __bezeichnung)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __action_handler)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __module)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __Action_TypesID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__bezeichnung = _bezeichnung;
    *__action_handler = _action_handler;
    *__module = _module;

	
	__Action_TypesID->setData(_Action_TypesID);

    *paramname = "bezeichnung";
    param->setUAPString(*&paramname, *&__bezeichnung);
    *paramname = "action_handler";
    param->setUAPString(*&paramname, *&__action_handler);
    *paramname = "module";
    param->setUAPString(*&paramname, *&__module);


	*paramname = "Action_TypesID";
	param->setUAPLong(*&paramname, *&__Action_TypesID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__Action_TypesID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Action_Types->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL Action_TypesModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Action_Types->finishIteration();
	while (hasMoreElements()) {
		setNextElement();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Action_Types->remove(&key);
			Action_Types->finishIteration();
		}
	}
}

void		LB_STDCALL Action_TypesModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Action_Types->finishIteration();
	while (hasMoreElements()) {
		setNextElement();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Action_Types->remove(&key);
			Action_Types->finishIteration();
		}
	}
}

bool LB_STDCALL Action_TypesModel::selectById(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Action_Types->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "bezeichnung";
    param->getUAPString(*&paramname, *&currentbezeichnung);
    *paramname = "action_handler";
    param->getUAPString(*&paramname, *&currentaction_handler);
    *paramname = "module";
    param->getUAPString(*&paramname, *&currentmodule);


		*paramname = "Action_TypesID";
		param->getUAPLong(*&paramname, *&currentAction_TypesID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL Action_TypesModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL Action_TypesModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL Action_TypesModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL Action_TypesModel::Count() {
	return Action_Types->Count();
}

bool  LB_STDCALL Action_TypesModel::hasMoreElements() {
	return (Action_Types->hasMoreElements() == 1);
}

void  LB_STDCALL Action_TypesModel::setNextElement() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Action_Types->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "bezeichnung";
    param->getUAPString(*&paramname, *&currentbezeichnung);
    *paramname = "action_handler";
    param->getUAPString(*&paramname, *&currentaction_handler);
    *paramname = "module";
    param->getUAPString(*&paramname, *&currentmodule);

	*paramname = "Action_TypesID";
	param->getUAPLong(*&paramname, *&currentAction_TypesID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL Action_TypesModel::finishIteration() {
	Action_Types->finishIteration();
}

long LB_STDCALL Action_TypesModel::get_id() {
	return currentAction_TypesID->getData();
}


char* LB_STDCALL Action_TypesModel::get_bezeichnung() {
	return currentbezeichnung->charrep();
}

char* LB_STDCALL Action_TypesModel::get_action_handler() {
	return currentaction_handler->charrep();
}

char* LB_STDCALL Action_TypesModel::get_module() {
	return currentmodule->charrep();
}


class lbPluginAction_TypesModel : public lb_I_PluginImpl {
public:
	lbPluginAction_TypesModel();
	
	virtual ~lbPluginAction_TypesModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAction_TypesModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAction_TypesModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAction_TypesModel, lbPluginAction_TypesModel)

lbErrCodes LB_STDCALL lbPluginAction_TypesModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAction_TypesModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAction_TypesModel::lbPluginAction_TypesModel() {
	_CL_VERBOSE << "lbPluginAction_TypesModel::lbPluginAction_TypesModel() called.\n" LOG_
}

lbPluginAction_TypesModel::~lbPluginAction_TypesModel() {
	_CL_VERBOSE << "lbPluginAction_TypesModel::~lbPluginAction_TypesModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginAction_TypesModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAction_TypesModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAction_TypesModel::initialize() {
}
	
bool LB_STDCALL lbPluginAction_TypesModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAction_TypesModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_TypesModel == NULL) {
		Action_TypesModel* aAction_TypesModel = new Action_TypesModel();
		
	
		QI(aAction_TypesModel, lb_I_Unknown, ukAction_TypesModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAction_TypesModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAction_TypesModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_TypesModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Action_TypesModel* aAction_TypesModel = new Action_TypesModel();
		
	
		QI(aAction_TypesModel, lb_I_Unknown, ukAction_TypesModel)
	}
	
	lb_I_Unknown* r = ukAction_TypesModel.getPtr();
	ukAction_TypesModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAction_TypesModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAction_TypesModel != NULL) {
                ukAction_TypesModel--;
                ukAction_TypesModel.resetPtr();
        }
}

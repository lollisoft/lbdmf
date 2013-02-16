
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
#include <Generated_EntityModelAction_Step_Transitions.h>

IMPLEMENT_FUNCTOR(instanceOfAction_Step_TransitionsModel, Action_Step_TransitionsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(Action_Step_TransitionsModel)
	ADD_INTERFACE(lb_I_Action_Step_Transitions)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(Action_Step_TransitionsModel)

Action_Step_TransitionsModel::Action_Step_TransitionsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Action_Step_Transitions)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currentexpression)
    REQUEST(getModuleInstance(), lb_I_Long, currentsrc_actionid)
    REQUEST(getModuleInstance(), lb_I_Long, currentdst_actionid)
    REQUEST(getModuleInstance(), lb_I_String, currentdescription)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentAction_Step_TransitionsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "Action_Step_TransitionsModel::Action_Step_TransitionsModel() called." LOG_
}

Action_Step_TransitionsModel::~Action_Step_TransitionsModel() {
	_CL_VERBOSE << "Action_Step_TransitionsModel::~Action_Step_TransitionsModel() called." LOG_
}

lbErrCodes LB_STDCALL Action_Step_TransitionsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: Action_Step_TransitionsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL Action_Step_TransitionsModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Action_Step_Transitions";
	
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

lb_I_ExtensionObject* LB_STDCALL Action_Step_TransitionsModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL Action_Step_TransitionsModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL Action_Step_TransitionsModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL Action_Step_TransitionsModel::add(const char* _expression, long _src_actionid, long _dst_actionid, const char* _description,  long _Action_Step_TransitionsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __expression)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __src_actionid)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __dst_actionid)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __description)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __Action_Step_TransitionsID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__expression = _expression;
    __src_actionid->setData(_src_actionid);
    __dst_actionid->setData(_dst_actionid);
    *__description = _description;

	
	__Action_Step_TransitionsID->setData(_Action_Step_TransitionsID);

    *paramname = "expression";
    param->setUAPString(*&paramname, *&__expression);
    *paramname = "src_actionid";
    param->setUAPLong(*&paramname, *&__src_actionid);
    *paramname = "dst_actionid";
    param->setUAPLong(*&paramname, *&__dst_actionid);
    *paramname = "description";
    param->setUAPString(*&paramname, *&__description);


	*paramname = "Action_Step_TransitionsID";
	param->setUAPLong(*&paramname, *&__Action_Step_TransitionsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__Action_Step_TransitionsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Action_Step_Transitions->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL Action_Step_TransitionsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Action_Step_Transitions->finishIteration();
	while (hasMoreAction_Step_Transitions()) {
		setNextAction_Step_Transitions();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Action_Step_Transitions->remove(&key);
			Action_Step_Transitions->finishIteration();
		}
	}
}

void		LB_STDCALL Action_Step_TransitionsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Action_Step_Transitions->finishIteration();
	while (hasMoreAction_Step_Transitions()) {
		setNextAction_Step_Transitions();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Action_Step_Transitions->remove(&key);
			Action_Step_Transitions->finishIteration();
		}
	}
}

bool LB_STDCALL Action_Step_TransitionsModel::selectById(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Action_Step_Transitions->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "expression";
    param->getUAPString(*&paramname, *&currentexpression);
    *paramname = "src_actionid";
    param->getUAPLong(*&paramname, *&currentsrc_actionid);
    *paramname = "dst_actionid";
    param->getUAPLong(*&paramname, *&currentdst_actionid);
    *paramname = "description";
    param->getUAPString(*&paramname, *&currentdescription);


		*paramname = "Action_Step_TransitionsID";
		param->getUAPLong(*&paramname, *&currentAction_Step_TransitionsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL Action_Step_TransitionsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL Action_Step_TransitionsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL Action_Step_TransitionsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL Action_Step_TransitionsModel::Count() {
	return Action_Step_Transitions->Count();
}

bool  LB_STDCALL Action_Step_TransitionsModel::hasMoreElements() {
	return (Action_Step_Transitions->hasMoreElements() == 1);
}

void  LB_STDCALL Action_Step_TransitionsModel::setNextElement() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Action_Step_Transitions->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "expression";
    param->getUAPString(*&paramname, *&currentexpression);
    *paramname = "src_actionid";
    param->getUAPLong(*&paramname, *&currentsrc_actionid);
    *paramname = "dst_actionid";
    param->getUAPLong(*&paramname, *&currentdst_actionid);
    *paramname = "description";
    param->getUAPString(*&paramname, *&currentdescription);

	*paramname = "Action_Step_TransitionsID";
	param->getUAPLong(*&paramname, *&currentAction_Step_TransitionsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL Action_Step_TransitionsModel::finishIteration() {
	Action_Step_Transitions->finishIteration();
}

long LB_STDCALL Action_Step_TransitionsModel::get_id() {
	return currentAction_Step_TransitionsID->getData();
}


char* LB_STDCALL Action_Step_TransitionsModel::get_expression() {
	return currentexpression->charrep();
}

long LB_STDCALL Action_Step_TransitionsModel::get_src_actionid() {
	return currentsrc_actionid->getData();
}

long LB_STDCALL Action_Step_TransitionsModel::get_dst_actionid() {
	return currentdst_actionid->getData();
}

char* LB_STDCALL Action_Step_TransitionsModel::get_description() {
	return currentdescription->charrep();
}


class lbPluginAction_Step_TransitionsModel : public lb_I_PluginImpl {
public:
	lbPluginAction_Step_TransitionsModel();
	
	virtual ~lbPluginAction_Step_TransitionsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAction_Step_TransitionsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAction_Step_TransitionsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAction_Step_TransitionsModel, lbPluginAction_Step_TransitionsModel)

lbErrCodes LB_STDCALL lbPluginAction_Step_TransitionsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAction_Step_TransitionsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAction_Step_TransitionsModel::lbPluginAction_Step_TransitionsModel() {
	_CL_VERBOSE << "lbPluginAction_Step_TransitionsModel::lbPluginAction_Step_TransitionsModel() called.\n" LOG_
}

lbPluginAction_Step_TransitionsModel::~lbPluginAction_Step_TransitionsModel() {
	_CL_VERBOSE << "lbPluginAction_Step_TransitionsModel::~lbPluginAction_Step_TransitionsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginAction_Step_TransitionsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAction_Step_TransitionsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAction_Step_TransitionsModel::initialize() {
}
	
bool LB_STDCALL lbPluginAction_Step_TransitionsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAction_Step_TransitionsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_Step_TransitionsModel == NULL) {
		Action_Step_TransitionsModel* aAction_Step_TransitionsModel = new Action_Step_TransitionsModel();
		
	
		QI(aAction_Step_TransitionsModel, lb_I_Unknown, ukAction_Step_TransitionsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAction_Step_TransitionsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAction_Step_TransitionsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_Step_TransitionsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Action_Step_TransitionsModel* aAction_Step_TransitionsModel = new Action_Step_TransitionsModel();
		
	
		QI(aAction_Step_TransitionsModel, lb_I_Unknown, ukAction_Step_TransitionsModel)
	}
	
	lb_I_Unknown* r = ukAction_Step_TransitionsModel.getPtr();
	ukAction_Step_TransitionsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAction_Step_TransitionsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAction_Step_TransitionsModel != NULL) {
                ukAction_Step_TransitionsModel--;
                ukAction_Step_TransitionsModel.resetPtr();
        }
}

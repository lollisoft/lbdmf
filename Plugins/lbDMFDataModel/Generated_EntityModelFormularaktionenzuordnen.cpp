
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
#include <Generated_EntityModelFormularaktionenzuordnen.h>

IMPLEMENT_FUNCTOR(instanceOfFormularaktionenzuordnenModel, FormularaktionenzuordnenModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(FormularaktionenzuordnenModel)
	ADD_INTERFACE(lb_I_Formularaktionenzuordnen)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(FormularaktionenzuordnenModel)

FormularaktionenzuordnenModel::FormularaktionenzuordnenModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Formularaktionenzuordnen)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currentevent)
    REQUEST(getModuleInstance(), lb_I_Long, currentaction)
    REQUEST(getModuleInstance(), lb_I_Long, currentformular)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentFormularaktionenzuordnenID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "FormularaktionenzuordnenModel::FormularaktionenzuordnenModel() called." LOG_
}

FormularaktionenzuordnenModel::~FormularaktionenzuordnenModel() {
	_CL_VERBOSE << "FormularaktionenzuordnenModel::~FormularaktionenzuordnenModel() called." LOG_
}

lbErrCodes LB_STDCALL FormularaktionenzuordnenModel::setData(lb_I_Unknown*) {
	_LOG << "Error: FormularaktionenzuordnenModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL FormularaktionenzuordnenModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Formularaktionenzuordnen";
	
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

lb_I_ExtensionObject* LB_STDCALL FormularaktionenzuordnenModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL FormularaktionenzuordnenModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL FormularaktionenzuordnenModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL FormularaktionenzuordnenModel::addFormularaktionenzuordnen(const char* _event, long _action, long _formular,  long _FormularaktionenzuordnenID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __event)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __action)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __formular)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __FormularaktionenzuordnenID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__event = _event;
    __action->setData(_action);
    __formular->setData(_formular);

	
	__FormularaktionenzuordnenID->setData(_FormularaktionenzuordnenID);

    *paramname = "event";
    param->setUAPString(*&paramname, *&__event);
    *paramname = "action";
    param->setUAPLong(*&paramname, *&__action);
    *paramname = "formular";
    param->setUAPLong(*&paramname, *&__formular);


	*paramname = "FormularaktionenzuordnenID";
	param->setUAPLong(*&paramname, *&__FormularaktionenzuordnenID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__FormularaktionenzuordnenID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Formularaktionenzuordnen->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL FormularaktionenzuordnenModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Formularaktionenzuordnen->finishIteration();
	while (hasMoreFormularaktionenzuordnen()) {
		setNextFormularaktionenzuordnen();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Formularaktionenzuordnen->remove(&key);
			Formularaktionenzuordnen->finishIteration();
		}
	}
}

void		LB_STDCALL FormularaktionenzuordnenModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Formularaktionenzuordnen->finishIteration();
	while (hasMoreFormularaktionenzuordnen()) {
		setNextFormularaktionenzuordnen();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Formularaktionenzuordnen->remove(&key);
			Formularaktionenzuordnen->finishIteration();
		}
	}
}

bool LB_STDCALL FormularaktionenzuordnenModel::selectFormularaktionenzuordnen(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Formularaktionenzuordnen->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "event";
    param->getUAPString(*&paramname, *&currentevent);
    *paramname = "action";
    param->getUAPLong(*&paramname, *&currentaction);
    *paramname = "formular";
    param->getUAPLong(*&paramname, *&currentformular);


		*paramname = "FormularaktionenzuordnenID";
		param->getUAPLong(*&paramname, *&currentFormularaktionenzuordnenID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL FormularaktionenzuordnenModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL FormularaktionenzuordnenModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL FormularaktionenzuordnenModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL FormularaktionenzuordnenModel::getFormularaktionenzuordnenCount() {
	return Formularaktionenzuordnen->Count();
}

bool  LB_STDCALL FormularaktionenzuordnenModel::hasMoreFormularaktionenzuordnen() {
	return (Formularaktionenzuordnen->hasMoreElements() == 1);
}

void  LB_STDCALL FormularaktionenzuordnenModel::setNextFormularaktionenzuordnen() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Formularaktionenzuordnen->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "event";
    param->getUAPString(*&paramname, *&currentevent);
    *paramname = "action";
    param->getUAPLong(*&paramname, *&currentaction);
    *paramname = "formular";
    param->getUAPLong(*&paramname, *&currentformular);

	*paramname = "FormularaktionenzuordnenID";
	param->getUAPLong(*&paramname, *&currentFormularaktionenzuordnenID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL FormularaktionenzuordnenModel::finishFormularaktionenzuordnenIteration() {
	Formularaktionenzuordnen->finishIteration();
}

long LB_STDCALL FormularaktionenzuordnenModel::get_id() {
	return currentFormularaktionenzuordnenID->getData();
}


char* LB_STDCALL FormularaktionenzuordnenModel::get_event() {
	return currentevent->charrep();
}

long LB_STDCALL FormularaktionenzuordnenModel::get_action() {
	return currentaction->getData();
}

long LB_STDCALL FormularaktionenzuordnenModel::get_formular() {
	return currentformular->getData();
}


class lbPluginFormularaktionenzuordnenModel : public lb_I_PluginImpl {
public:
	lbPluginFormularaktionenzuordnenModel();
	
	virtual ~lbPluginFormularaktionenzuordnenModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormularaktionenzuordnenModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormularaktionenzuordnenModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormularaktionenzuordnenModel, lbPluginFormularaktionenzuordnenModel)

lbErrCodes LB_STDCALL lbPluginFormularaktionenzuordnenModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormularaktionenzuordnenModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormularaktionenzuordnenModel::lbPluginFormularaktionenzuordnenModel() {
	_CL_VERBOSE << "lbPluginFormularaktionenzuordnenModel::lbPluginFormularaktionenzuordnenModel() called.\n" LOG_
}

lbPluginFormularaktionenzuordnenModel::~lbPluginFormularaktionenzuordnenModel() {
	_CL_VERBOSE << "lbPluginFormularaktionenzuordnenModel::~lbPluginFormularaktionenzuordnenModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormularaktionenzuordnenModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormularaktionenzuordnenModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormularaktionenzuordnenModel::initialize() {
}
	
bool LB_STDCALL lbPluginFormularaktionenzuordnenModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormularaktionenzuordnenModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularaktionenzuordnenModel == NULL) {
		FormularaktionenzuordnenModel* aFormularaktionenzuordnenModel = new FormularaktionenzuordnenModel();
		
	
		QI(aFormularaktionenzuordnenModel, lb_I_Unknown, ukFormularaktionenzuordnenModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormularaktionenzuordnenModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormularaktionenzuordnenModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularaktionenzuordnenModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FormularaktionenzuordnenModel* aFormularaktionenzuordnenModel = new FormularaktionenzuordnenModel();
		
	
		QI(aFormularaktionenzuordnenModel, lb_I_Unknown, ukFormularaktionenzuordnenModel)
	}
	
	lb_I_Unknown* r = ukFormularaktionenzuordnenModel.getPtr();
	ukFormularaktionenzuordnenModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormularaktionenzuordnenModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormularaktionenzuordnenModel != NULL) {
                ukFormularaktionenzuordnenModel--;
                ukFormularaktionenzuordnenModel.resetPtr();
        }
}

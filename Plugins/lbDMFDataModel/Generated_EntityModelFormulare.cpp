
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
#include <Generated_EntityModelFormulare.h>

IMPLEMENT_FUNCTOR(instanceOfFormulareModel, FormulareModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(FormulareModel)
	ADD_INTERFACE(lb_I_Formulare)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(FormulareModel)

FormulareModel::FormulareModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Formulare)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_String, currentmenuname)
    REQUEST(getModuleInstance(), lb_I_String, currentmenuhilfe)
    REQUEST(getModuleInstance(), lb_I_String, currenteventname)
    REQUEST(getModuleInstance(), lb_I_String, currenttoolbarimage)
    REQUEST(getModuleInstance(), lb_I_Long, currentanwendungid)
    REQUEST(getModuleInstance(), lb_I_Long, currenttyp)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentFormulareID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "FormulareModel::FormulareModel() called." LOG_
}

FormulareModel::~FormulareModel() {
	_CL_VERBOSE << "FormulareModel::~FormulareModel() called." LOG_
}

lbErrCodes LB_STDCALL FormulareModel::setData(lb_I_Unknown*) {
	_LOG << "Error: FormulareModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL FormulareModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Formulare";
	
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

lb_I_ExtensionObject* LB_STDCALL FormulareModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL FormulareModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL FormulareModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL FormulareModel::addFormulare(const char* _name, const char* _menuname, const char* _menuhilfe, const char* _eventname, const char* _toolbarimage, long _anwendungid, long _typ,  long _FormulareID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __menuname)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __menuhilfe)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __eventname)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __toolbarimage)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __anwendungid)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __typ)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __FormulareID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__name = _name;
    *__menuname = _menuname;
    *__menuhilfe = _menuhilfe;
    *__eventname = _eventname;
    *__toolbarimage = _toolbarimage;
    __anwendungid->setData(_anwendungid);
    __typ->setData(_typ);

	
	__FormulareID->setData(_FormulareID);

    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);
    *paramname = "menuname";
    param->setUAPString(*&paramname, *&__menuname);
    *paramname = "menuhilfe";
    param->setUAPString(*&paramname, *&__menuhilfe);
    *paramname = "eventname";
    param->setUAPString(*&paramname, *&__eventname);
    *paramname = "toolbarimage";
    param->setUAPString(*&paramname, *&__toolbarimage);
    *paramname = "anwendungid";
    param->setUAPLong(*&paramname, *&__anwendungid);
    *paramname = "typ";
    param->setUAPLong(*&paramname, *&__typ);


	*paramname = "FormulareID";
	param->setUAPLong(*&paramname, *&__FormulareID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__FormulareID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Formulare->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL FormulareModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Formulare->finishIteration();
	while (hasMoreFormulare()) {
		setNextFormulare();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Formulare->remove(&key);
			Formulare->finishIteration();
		}
	}
}

void		LB_STDCALL FormulareModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Formulare->finishIteration();
	while (hasMoreFormulare()) {
		setNextFormulare();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Formulare->remove(&key);
			Formulare->finishIteration();
		}
	}
}

bool LB_STDCALL FormulareModel::selectFormulare(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Formulare->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "menuname";
    param->getUAPString(*&paramname, *&currentmenuname);
    *paramname = "menuhilfe";
    param->getUAPString(*&paramname, *&currentmenuhilfe);
    *paramname = "eventname";
    param->getUAPString(*&paramname, *&currenteventname);
    *paramname = "toolbarimage";
    param->getUAPString(*&paramname, *&currenttoolbarimage);
    *paramname = "anwendungid";
    param->getUAPLong(*&paramname, *&currentanwendungid);
    *paramname = "typ";
    param->getUAPLong(*&paramname, *&currenttyp);


		*paramname = "FormulareID";
		param->getUAPLong(*&paramname, *&currentFormulareID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL FormulareModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL FormulareModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL FormulareModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL FormulareModel::getFormulareCount() {
	return Formulare->Count();
}

bool  LB_STDCALL FormulareModel::hasMoreFormulare() {
	return (Formulare->hasMoreElements() == 1);
}

void  LB_STDCALL FormulareModel::setNextFormulare() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Formulare->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "menuname";
    param->getUAPString(*&paramname, *&currentmenuname);
    *paramname = "menuhilfe";
    param->getUAPString(*&paramname, *&currentmenuhilfe);
    *paramname = "eventname";
    param->getUAPString(*&paramname, *&currenteventname);
    *paramname = "toolbarimage";
    param->getUAPString(*&paramname, *&currenttoolbarimage);
    *paramname = "anwendungid";
    param->getUAPLong(*&paramname, *&currentanwendungid);
    *paramname = "typ";
    param->getUAPLong(*&paramname, *&currenttyp);

	*paramname = "FormulareID";
	param->getUAPLong(*&paramname, *&currentFormulareID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL FormulareModel::finishFormulareIteration() {
	Formulare->finishIteration();
}

long LB_STDCALL FormulareModel::get_id() {
	return currentFormulareID->getData();
}


char* LB_STDCALL FormulareModel::get_name() {
	return currentname->charrep();
}

char* LB_STDCALL FormulareModel::get_menuname() {
	return currentmenuname->charrep();
}

char* LB_STDCALL FormulareModel::get_menuhilfe() {
	return currentmenuhilfe->charrep();
}

char* LB_STDCALL FormulareModel::get_eventname() {
	return currenteventname->charrep();
}

char* LB_STDCALL FormulareModel::get_toolbarimage() {
	return currenttoolbarimage->charrep();
}

long LB_STDCALL FormulareModel::get_anwendungid() {
	return currentanwendungid->getData();
}

long LB_STDCALL FormulareModel::get_typ() {
	return currenttyp->getData();
}


class lbPluginFormulareModel : public lb_I_PluginImpl {
public:
	lbPluginFormulareModel();
	
	virtual ~lbPluginFormulareModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormulareModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormulareModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormulareModel, lbPluginFormulareModel)

lbErrCodes LB_STDCALL lbPluginFormulareModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormulareModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormulareModel::lbPluginFormulareModel() {
	_CL_VERBOSE << "lbPluginFormulareModel::lbPluginFormulareModel() called.\n" LOG_
}

lbPluginFormulareModel::~lbPluginFormulareModel() {
	_CL_VERBOSE << "lbPluginFormulareModel::~lbPluginFormulareModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormulareModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormulareModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormulareModel::initialize() {
}
	
bool LB_STDCALL lbPluginFormulareModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormulareModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormulareModel == NULL) {
		FormulareModel* aFormulareModel = new FormulareModel();
		
	
		QI(aFormulareModel, lb_I_Unknown, ukFormulareModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormulareModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormulareModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormulareModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FormulareModel* aFormulareModel = new FormulareModel();
		
	
		QI(aFormulareModel, lb_I_Unknown, ukFormulareModel)
	}
	
	lb_I_Unknown* r = ukFormulareModel.getPtr();
	ukFormulareModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormulareModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormulareModel != NULL) {
                ukFormulareModel--;
                ukFormulareModel.resetPtr();
        }
}

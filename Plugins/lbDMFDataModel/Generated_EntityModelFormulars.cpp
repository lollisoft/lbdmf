
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
#include <Generated_EntityModelFormulars.h>

IMPLEMENT_FUNCTOR(instanceOfFormularsModel, FormularsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(FormularsModel)
	ADD_INTERFACE(lb_I_Formulars)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(FormularsModel)

FormularsModel::FormularsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Formulars)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_String, currentmenuname)
    REQUEST(getModuleInstance(), lb_I_String, currentmenuhilfe)
    REQUEST(getModuleInstance(), lb_I_String, currenteventname)
    REQUEST(getModuleInstance(), lb_I_String, currenttoolbarimage)
    REQUEST(getModuleInstance(), lb_I_Long, currentanwendungid)
    REQUEST(getModuleInstance(), lb_I_Long, currenttyp)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentFormularsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "FormularsModel::FormularsModel() called." LOG_
}

FormularsModel::~FormularsModel() {
	_CL_VERBOSE << "FormularsModel::~FormularsModel() called." LOG_
}

lbErrCodes LB_STDCALL FormularsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: FormularsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL FormularsModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Formulars";
	
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

lb_I_ExtensionObject* LB_STDCALL FormularsModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL FormularsModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL FormularsModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL FormularsModel::add(const char* _name, const char* _menuname, const char* _menuhilfe, const char* _eventname, const char* _toolbarimage, long _anwendungid, long _typ,  long _FormularsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __menuname)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __menuhilfe)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __eventname)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __toolbarimage)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __anwendungid)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __typ)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __FormularsID)

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

	
	__FormularsID->setData(_FormularsID);

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


	*paramname = "FormularsID";
	param->setUAPLong(*&paramname, *&__FormularsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__FormularsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Formulars->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL FormularsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Formulars->finishIteration();
	while (hasMoreElements()) {
		setNextElement();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Formulars->remove(&key);
			Formulars->finishIteration();
		}
	}
}

void		LB_STDCALL FormularsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Formulars->finishIteration();
	while (hasMoreElements()) {
		setNextElement();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Formulars->remove(&key);
			Formulars->finishIteration();
		}
	}
}

bool LB_STDCALL FormularsModel::selectById(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Formulars->getElement(&key);

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


		*paramname = "FormularsID";
		param->getUAPLong(*&paramname, *&currentFormularsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL FormularsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL FormularsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL FormularsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL FormularsModel::Count() {
	return Formulars->Count();
}

bool  LB_STDCALL FormularsModel::hasMoreElements() {
	return (Formulars->hasMoreElements() == 1);
}

void  LB_STDCALL FormularsModel::setNextElement() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Formulars->nextElement();
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

	*paramname = "FormularsID";
	param->getUAPLong(*&paramname, *&currentFormularsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL FormularsModel::finishIteration() {
	Formulars->finishIteration();
}

long LB_STDCALL FormularsModel::get_id() {
	return currentFormularsID->getData();
}


char* LB_STDCALL FormularsModel::get_name() {
	return currentname->charrep();
}

char* LB_STDCALL FormularsModel::get_menuname() {
	return currentmenuname->charrep();
}

char* LB_STDCALL FormularsModel::get_menuhilfe() {
	return currentmenuhilfe->charrep();
}

char* LB_STDCALL FormularsModel::get_eventname() {
	return currenteventname->charrep();
}

char* LB_STDCALL FormularsModel::get_toolbarimage() {
	return currenttoolbarimage->charrep();
}

long LB_STDCALL FormularsModel::get_anwendungid() {
	return currentanwendungid->getData();
}

long LB_STDCALL FormularsModel::get_typ() {
	return currenttyp->getData();
}


class lbPluginFormularsModel : public lb_I_PluginImpl {
public:
	lbPluginFormularsModel();
	
	virtual ~lbPluginFormularsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormularsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormularsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormularsModel, lbPluginFormularsModel)

lbErrCodes LB_STDCALL lbPluginFormularsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormularsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormularsModel::lbPluginFormularsModel() {
	_CL_VERBOSE << "lbPluginFormularsModel::lbPluginFormularsModel() called.\n" LOG_
}

lbPluginFormularsModel::~lbPluginFormularsModel() {
	_CL_VERBOSE << "lbPluginFormularsModel::~lbPluginFormularsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormularsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormularsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormularsModel::initialize() {
}
	
bool LB_STDCALL lbPluginFormularsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormularsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularsModel == NULL) {
		FormularsModel* aFormularsModel = new FormularsModel();
		
	
		QI(aFormularsModel, lb_I_Unknown, ukFormularsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormularsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormularsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FormularsModel* aFormularsModel = new FormularsModel();
		
	
		QI(aFormularsModel, lb_I_Unknown, ukFormularsModel)
	}
	
	lb_I_Unknown* r = ukFormularsModel.getPtr();
	ukFormularsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormularsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormularsModel != NULL) {
                ukFormularsModel--;
                ukFormularsModel.resetPtr();
        }
}

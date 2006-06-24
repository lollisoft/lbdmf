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
            Rosmarinstr. 3
            
            40235 Duesseldorf (germany)
*/
/*...e*/
#define LB_DMFDATAMODEL_DLL

#ifdef _MSC_VER

//#pragma warning( disable: 4101 )

#endif

/*...sincludes:0:*/


#include <stdio.h>
#include <string.h>
//#include <lbInterfaces.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {      
#endif            

//#include <conio.h>

#ifdef __cplusplus
}      
#endif            

#endif

#include <lbConfigHook.h>
#include <lbdmfdatamodel-module.h>

#include <lbApplicationsModel.h>

IMPLEMENT_FUNCTOR(instanceOflbApplications, lbApplications)


BEGIN_IMPLEMENT_LB_UNKNOWN(lbApplications)
	ADD_INTERFACE(lb_I_Applications)
END_IMPLEMENT_LB_UNKNOWN()

lbApplications::lbApplications() {
	ref = STARTREF;
	_CL_LOG << "lbApplications::lbApplications() called." LOG_
	REQUEST(getModuleInstance(), lb_I_Container, Applications)
	REQUEST(getModuleInstance(), lb_I_String, currentApplication)
	REQUEST(getModuleInstance(), lb_I_String, currentTitel)
	REQUEST(getModuleInstance(), lb_I_String, currentFunctor)
	REQUEST(getModuleInstance(), lb_I_String, currentModuleName)
	REQUEST(getModuleInstance(), lb_I_String, currentInterface)
	REQUEST(getModuleInstance(), lb_I_Long, currentApplicationUID)
}

lbApplications::~lbApplications() {
	_CL_LOG << "lbApplications::~lbApplications() called." LOG_
}

lbErrCodes LB_STDCALL lbApplications::setData(lb_I_Unknown*) {
		_LOG << "Error: lbApplications::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}

long	LB_STDCALL lbApplications::addApplication(const char* application, const char* titel, const char* modulename, const char* functor, const char* _interface, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_Long, _ID)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Application)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Titel)
	UAP_REQUEST(manager.getPtr(), lb_I_String, ModuleName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Functor)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Interface)
	
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)

	_ID->setData(_id);
	*Application = application;
	*Titel = titel;
	*ModuleName = modulename;
	*Functor = functor;
	*Interface = _interface;

	_CL_VERBOSE << "lbApplications::addApplication('" << application << "', '" << titel << "', '" << modulename << "', '" << functor << "', '" << _interface << "', '" << _ID->getData() << "') called" LOG_

	*paramname = "ID";
	param->setUAPLong(*&paramname, *&_ID);
	*paramname = "Application";
	param->setUAPString(*&paramname, *&Application);
	*paramname = "Titel";
	param->setUAPString(*&paramname, *&Titel);
	*paramname = "ModuleName";
	param->setUAPString(*&paramname, *&ModuleName);
	*paramname = "Functor";
	param->setUAPString(*&paramname, *&Functor);
	*paramname = "Interface";
	param->setUAPString(*&paramname, *&Interface);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(_ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Applications->insert(&ukParam, &key);

	return false;
}

bool	LB_STDCALL lbApplications::selectApplication(const char* application) {

	while (hasMoreApplications()) {
		setNextApplication();
		
		if (strcmp(getApplicationName(), application) == 0) {
			finishApplicationIteration();
			return true;
		}
	}

	return false;
}

bool	LB_STDCALL lbApplications::selectApplication(long _id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Applications->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		*name = "ID";
		param->getUAPLong(*&name, *&currentApplicationUID);
		*name = "Application";
		param->getUAPString(*&name, *&currentApplication);
		*name = "Titel";
		param->getUAPString(*&name, *&currentTitel);
		*name = "Functor";
		param->getUAPString(*&name, *&currentFunctor);
		*name = "ModuleName";
		param->getUAPString(*&name, *&currentModuleName);
		*name = "Interface";
		param->getUAPString(*&name, *&currentInterface);

		_CL_VERBOSE << "lbApplications::selectApplication('" << _id << "') selects '" << 
		currentApplication->charrep() << "', '" << 
		currentTitel->charrep() << "', '" << 
		currentModuleName->charrep() << "', '" << 
		currentFunctor->charrep() << "', '" << 
		currentInterface->charrep() << "', '" << currentApplicationUID->getData() << "'" LOG_

	} else {
		_CL_LOG << "Error: No such application with ID = " << _id << "." LOG_
	}
}

int		LB_STDCALL lbApplications::getApplicationCount() {
	return Applications->Count();
}

bool	LB_STDCALL lbApplications::hasMoreApplications() {
	return (Applications->hasMoreElements() == 1);
}

void	LB_STDCALL lbApplications::setNextApplication() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = Applications->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "ID";
	param->getUAPLong(*&name, *&currentApplicationUID);
	*name = "Application";
	param->getUAPString(*&name, *&currentApplication);
	*name = "Titel";
	param->getUAPString(*&name, *&currentTitel);
	*name = "ModuleName";
	param->getUAPString(*&name, *&currentModuleName);
	*name = "Functor";
	param->getUAPString(*&name, *&currentFunctor);
	*name = "Interface";
	param->getUAPString(*&name, *&currentInterface);
}

void	LB_STDCALL lbApplications::finishApplicationIteration() {
	Applications->finishIteration();
}

char*	LB_STDCALL lbApplications::getApplicationName() {
	return currentApplication->charrep();
}

long	LB_STDCALL lbApplications::getApplicationID() {
	return currentApplicationUID->getData();
}

char*	LB_STDCALL lbApplications::getApplicationTitle() {
	return currentTitel->charrep();
}

char*	LB_STDCALL lbApplications::getApplicationFunctor() {
	return currentFunctor->charrep();
}

char*	LB_STDCALL lbApplications::getApplicationModule() {
	return currentModuleName->charrep();
}

char*	LB_STDCALL lbApplications::getApplicationInterface() {
	return currentInterface->charrep();
}

/*...sclass lbPluginApplications implementation:0:*/
/*...slbPluginApplications:0:*/
class lbPluginApplications : public virtual lb_I_PluginImpl {
public:
	lbPluginApplications();
	
	virtual ~lbPluginApplications();

/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukApplications)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginApplications)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginApplications, lbPluginApplications)

/*...slbErrCodes LB_STDCALL lbPluginApplications\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginApplications::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginApplications::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginApplications::lbPluginApplications() {
	_CL_VERBOSE << "lbPluginApplications::lbPluginApplications() called.\n" LOG_
	ref = STARTREF;
}

lbPluginApplications::~lbPluginApplications() {
	_CL_VERBOSE << "lbPluginApplications::~lbPluginApplications() called.\n" LOG_
}

void LB_STDCALL lbPluginApplications::initialize() {
}
	
bool LB_STDCALL lbPluginApplications::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginApplications\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginApplications::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplications == NULL) {
		lbApplications* Applications = new lbApplications();
		Applications->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(Applications, lb_I_Unknown, ukApplications)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukApplications.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginApplications\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginApplications::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplications == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbApplications* Applications = new lbApplications();
		Applications->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(Applications, lb_I_Unknown, ukApplications)
	}
	
	lb_I_Unknown* r = ukApplications.getPtr();
	ukApplications.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginApplications::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
}
/*...e*/
/*...e*/


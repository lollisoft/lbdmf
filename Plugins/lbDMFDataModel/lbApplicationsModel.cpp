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

/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#include <lbApplicationsModel.h>

IMPLEMENT_FUNCTOR(instanceOflbApplications, lbApplications)


BEGIN_IMPLEMENT_LB_UNKNOWN(lbApplications)
	ADD_INTERFACE(lb_I_Applications)
END_IMPLEMENT_LB_UNKNOWN()

/*...slbApplications\58\\58\lbApplications\40\\41\:0:*/
lbApplications::lbApplications() {
	ref = STARTREF;
	_CL_VERBOSE << "lbApplications::lbApplications() called." LOG_
	REQUEST(getModuleInstance(), lb_I_Container, Applications)
	REQUEST(getModuleInstance(), lb_I_String, currentApplication)
	REQUEST(getModuleInstance(), lb_I_String, currentTitel)
	REQUEST(getModuleInstance(), lb_I_String, currentFunctor)
	REQUEST(getModuleInstance(), lb_I_String, currentModuleName)
	REQUEST(getModuleInstance(), lb_I_String, currentInterface)
	REQUEST(getModuleInstance(), lb_I_Long, currentApplicationUID)
	
	REQUEST(getModuleInstance(), lb_I_Long, marked)
}
/*...e*/
/*...slbApplications\58\\58\\126\lbApplications\40\\41\:0:*/
lbApplications::~lbApplications() {
	_CL_VERBOSE << "lbApplications::~lbApplications() called." LOG_
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbApplications\58\\58\setData\40\lb_I_Unknown\42\\41\:0:*/
lbErrCodes LB_STDCALL lbApplications::setData(lb_I_Unknown*) {
	_LOG << "Error: lbApplications::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

void		LB_STDCALL lbApplications::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Applications->finishIteration();
	while (hasMoreApplications()) {
		setNextApplication();
		if (!ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getApplicationID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Applications->remove(&key);
			Applications->finishIteration();
		}
	}
}

void		LB_STDCALL lbApplications::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Applications->finishIteration();
	while (hasMoreApplications()) {
		setNextApplication();
		if (ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getApplicationID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Applications->remove(&key);
			Applications->finishIteration();
		}
	}
}


/*...slong    LB_STDCALL lbApplications\58\\58\addApplication\40\\46\\46\\46\\41\:0:*/
long	LB_STDCALL lbApplications::addApplication(const char* application, const char* titel, const char* modulename, const char* functor, const char* _interface, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_Long, _ID)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Application)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Titel)
	UAP_REQUEST(manager.getPtr(), lb_I_String, ModuleName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Functor)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Interface)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, marked)
	
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
	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(_ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Applications->insert(&ukParam, &key);

	return false;
}
/*...e*/
/*...sbool    LB_STDCALL lbApplications\58\\58\selectApplication\40\const char\42\ application\41\:0:*/
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
/*...e*/
/*...sbool    LB_STDCALL lbApplications\58\\58\selectApplication\40\long _id\41\:0:*/
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
		*name = "marked";
		param->getUAPLong(*&name, *&marked);

		_CL_VERBOSE << "lbApplications::selectApplication('" << _id << "') selects '" << 
		currentApplication->charrep() << "', '" << 
		currentTitel->charrep() << "', '" << 
		currentModuleName->charrep() << "', '" << 
		currentFunctor->charrep() << "', '" << 
		currentInterface->charrep() << "', '" << currentApplicationUID->getData() << "'" LOG_
		return true;
	} else {
		_LOG << "Error: No such application with ID = " << _id << " Generated ID = " << ID->charrep() << "." LOG_
		return false;
	}
}
/*...e*/

bool LB_STDCALL lbApplications::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbApplications::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbApplications::unmark() {
	marked->setData((long) 0);
}

/*...sint     LB_STDCALL lbApplications\58\\58\getApplicationCount\40\\41\:0:*/
int	LB_STDCALL lbApplications::getApplicationCount() {
	return Applications->Count();
}
/*...e*/
/*...sbool    LB_STDCALL lbApplications\58\\58\hasMoreApplications\40\\41\:0:*/
bool	LB_STDCALL lbApplications::hasMoreApplications() {
	return (Applications->hasMoreElements() == 1);
}
/*...e*/
/*...svoid    LB_STDCALL lbApplications\58\\58\setNextApplication\40\\41\:0:*/
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
	*name = "marked";
	param->getUAPLong(*&name, *&marked);
}
/*...e*/
/*...svoid    LB_STDCALL lbApplications\58\\58\finishApplicationIteration\40\\41\:0:*/
void	LB_STDCALL lbApplications::finishApplicationIteration() {
	Applications->finishIteration();
}
/*...e*/
/*...schar\42\   LB_STDCALL lbApplications\58\\58\getApplicationName\40\\41\:0:*/
char*	LB_STDCALL lbApplications::getApplicationName() {
	return currentApplication->charrep();
}
/*...e*/
/*...slong    LB_STDCALL lbApplications\58\\58\getApplicationID\40\\41\:0:*/
long	LB_STDCALL lbApplications::getApplicationID() {
	return currentApplicationUID->getData();
}
/*...e*/
/*...schar\42\   LB_STDCALL lbApplications\58\\58\getApplicationTitle\40\\41\:0:*/
char*	LB_STDCALL lbApplications::getApplicationTitle() {
	return currentTitel->charrep();
}
/*...e*/
/*...schar\42\   LB_STDCALL lbApplications\58\\58\getApplicationFunctor\40\\41\:0:*/
char*	LB_STDCALL lbApplications::getApplicationFunctor() {
	return currentFunctor->charrep();
}
/*...e*/
/*...schar\42\   LB_STDCALL lbApplications\58\\58\getApplicationModule\40\\41\:0:*/
char*	LB_STDCALL lbApplications::getApplicationModule() {
	return currentModuleName->charrep();
}
/*...e*/
/*...schar\42\   LB_STDCALL lbApplications\58\\58\getApplicationInterface\40\\41\:0:*/
char*	LB_STDCALL lbApplications::getApplicationInterface() {
	return currentInterface->charrep();
}
/*...e*/

/*...sclass lbPluginApplications implementation:0:*/
/*...slbPluginApplications:0:*/
class lbPluginApplications : public lb_I_PluginImpl {
public:
	lbPluginApplications();
	
	virtual ~lbPluginApplications();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
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
	data = NULL;
	further_lock = 1;
}

lbPluginApplications::~lbPluginApplications() {
	_CL_VERBOSE << "lbPluginApplications::~lbPluginApplications() called.\n" LOG_
}

bool LB_STDCALL lbPluginApplications::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginApplications::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
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

        if (ukApplications != NULL) {
                ukApplications--;
                ukApplications.resetPtr();
        }
}
/*...e*/
/*...e*/


/*...sLicence:0:*/
/*
	DMF Distributed Multiplatform Framework (the initial goal of this library)
	This file is part of lbDMF.
	Copyright (C) 2002 Lothar Behrens (lothar.behrens@lollisoft.de)

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

/*...sRevision history:0:*/
/**************************************************************
* $Locker:  $
* $Revision: 1.2 $
* $Name:  $
* $Id: lbDocumentVersion.cpp,v 1.2 2012/02/12 11:58:26 lollisoft Exp $
*
* $Log: lbDocumentVersion.cpp,v $
* Revision 1.2  2012/02/12 11:58:26  lollisoft
* Implemented detection of a file version that has no version information.
*
* Revision 1.1  2012/02/11 19:18:53  lollisoft
* Basic implementation of document versioning compiles.
*
**************************************************************/
/*...e*/

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_CLASSES_DLL scope:0:*/
#define LB_CLASSES_DLL
#include <lbclasses-module.h>
/*...e*/

/*...sIncludes:0:*/
#include <iostream>
#include <stdio.h>
#include <time.h>

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <lbthread.h>
#include <lb_misc.h>
#include <fstream>
/*...e*/

class lbDocumentVersion : public lb_I_DocumentVersion
{
public:
	lbDocumentVersion();
	virtual ~lbDocumentVersion();
	
	DECLARE_LB_UNKNOWN()

	void LB_STDCALL setInvalid();

	bool LB_STDCALL isValidVersion();

	void LB_STDCALL setData(lb_I_String* _Interface, lb_I_String* _Functor, lb_I_String* _Module, lb_I_String* _ModuleVersion, lb_I_String* _StoragePluginNamespace, lb_I_String* _StoragePluginVersion);

	void LB_STDCALL setData(const char* _Interface, const char* _Functor, const char* _Module, const char* _ModuleVersion, const char* _StoragePluginNamespace, const char* _StoragePluginVersion);
	
	lb_I_String* LB_STDCALL getInterface();

	lb_I_String* LB_STDCALL getFunctor();

	lb_I_String* LB_STDCALL getModule();

	lb_I_String* LB_STDCALL getModuleVersion();

	lb_I_String* LB_STDCALL getStoragePluginNamespace();

	lb_I_String* LB_STDCALL getStoragePluginVersion();
	
private:
	bool invalid;
	UAP(lb_I_String, __Interface)
	UAP(lb_I_String, Functor)
	UAP(lb_I_String, Module)
	UAP(lb_I_String, ModuleVersion)
	UAP(lb_I_String, StoragePluginNamespace)
	UAP(lb_I_String, StoragePluginVersion)
};

IMPLEMENT_FUNCTOR(instanceOflbDocumentVersion, lbDocumentVersion)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDocumentVersion)
ADD_INTERFACE(lb_I_DocumentVersion)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbDocumentVersion::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbDocumentVersion::setData(lb_I_Unknown* uk) not implemented." LOG_
	return err;
}

lbDocumentVersion::lbDocumentVersion() {
	REQUEST(getModuleInstance(), lb_I_String, __Interface)
	REQUEST(getModuleInstance(), lb_I_String, Functor)
	REQUEST(getModuleInstance(), lb_I_String, Module)
	REQUEST(getModuleInstance(), lb_I_String, ModuleVersion)
	REQUEST(getModuleInstance(), lb_I_String, StoragePluginNamespace)
	REQUEST(getModuleInstance(), lb_I_String, StoragePluginVersion)
	invalid = true;
}

lbDocumentVersion::~lbDocumentVersion() {

}

void LB_STDCALL lbDocumentVersion::setInvalid() {
	invalid = true;
}

bool LB_STDCALL lbDocumentVersion::isValidVersion() {
	return !invalid;
}

void LB_STDCALL lbDocumentVersion::setData(lb_I_String* _Interface, lb_I_String* _Functor, lb_I_String* _Module, lb_I_String* _ModuleVersion, lb_I_String* _StoragePluginNamespace, lb_I_String* _StoragePluginVersion) {
	__Interface = _Interface;
	Functor = _Functor;
	Module = _Module;
	ModuleVersion = _ModuleVersion;
	StoragePluginNamespace =_StoragePluginNamespace;
	StoragePluginVersion = _StoragePluginVersion;

	__Interface++;
	Functor++;
	Module++;
	ModuleVersion++;
	StoragePluginNamespace++;
	StoragePluginVersion++;
	invalid = false;
}

void LB_STDCALL lbDocumentVersion::setData(const char* _Interface, const char* _Functor, const char* _Module, const char* _ModuleVersion, const char* _StoragePluginNamespace, const char* _StoragePluginVersion) {
	*__Interface = _Interface;
	*Functor = _Functor;
	*Module = _Module;
	*ModuleVersion = _ModuleVersion;
	*StoragePluginNamespace =_StoragePluginNamespace;
	*StoragePluginVersion = _StoragePluginVersion;
	invalid = false;
}

lb_I_String* LB_STDCALL lbDocumentVersion::getInterface() {
	__Interface++;
	return *&__Interface;
}

lb_I_String* LB_STDCALL lbDocumentVersion::getFunctor() {
	Functor++;
	return *&Functor;
}

lb_I_String* LB_STDCALL lbDocumentVersion::getModule() {
	Module++;
	return *&Module;
}

lb_I_String* LB_STDCALL lbDocumentVersion::getModuleVersion() {
	ModuleVersion++;
	return *&ModuleVersion;
}

lb_I_String* LB_STDCALL lbDocumentVersion::getStoragePluginNamespace() {
	StoragePluginNamespace++;
	return *&StoragePluginNamespace;
}

lb_I_String* LB_STDCALL lbDocumentVersion::getStoragePluginVersion() {
	StoragePluginVersion++;
	return *&StoragePluginVersion;
}

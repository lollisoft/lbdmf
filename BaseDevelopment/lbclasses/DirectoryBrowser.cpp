/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2013  Lothar Behrens (lothar.behrens@lollisoft.de)

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

#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#ifdef LINUX
#include <string.h>
#endif
#ifdef WINDOWS
#include <string.h>
#include <io.h>
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#define LB_CLASSES_DLL
#include <lbclasses-module.h>

#include <DirectoryBrowser.h>

#ifdef LINUX 
#include <dirent.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

IMPLEMENT_FUNCTOR(instanceOfDirectoryBrowser, DirectoryBrowser)

#ifdef __cplusplus
}
#endif
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(DirectoryBrowser)
	ADD_INTERFACE(lb_I_DirectoryBrowser)
END_IMPLEMENT_LB_UNKNOWN()


lbErrCodes LB_STDCALL DirectoryBrowser::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	return ERR_NONE;
}

DirectoryBrowser::DirectoryBrowser() {
	
}

DirectoryBrowser::~DirectoryBrowser() {
	
}

lb_I_Container* LB_STDCALL DirectoryBrowser::getDirectories(const char* path) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, _path)
	*_path = path;
	
	return getDirectories(*&_path);
}

lb_I_Container* LB_STDCALL DirectoryBrowser::getDirectories(lb_I_String* path) {
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, entry)
	UAP(lb_I_KeyBase, keyEntry)
	int ent = 0;

	UAP_REQUEST(getModuleInstance(), lb_I_Container, directories)
	directories++;

	QI(entry, lb_I_KeyBase, keyEntry)
	
	char* pluginDir = path->charrep();
	
#ifdef WINDOWS
	_finddata_t find;
	const char* mask = "*.*";
	char* toFind = (char*) malloc(strlen(mask)+strlen(pluginDir)+2);
	toFind[0] = 0;
	
	strcat(toFind, pluginDir);
	strcat(toFind, "\\");
	strcat(toFind, mask);

	long handle = _findfirst(toFind, &find);

	if (handle != -1) {
		if (find.attrib & _A_SUBDIR) {
			UAP_REQUEST(getModuleInstance(), lb_I_DirLocation, dLoc)
			UAP(lb_I_Unknown, ukLoc)
				
			UAP_REQUEST(getModuleInstance(), lb_I_String, fullPath)
				
			*fullPath = path;
			*fullPath += "\\";
			*fullPath += find.name;
				
			dLoc->setData(fullPath->charrep());
			QI(dLoc, lb_I_Unknown, ukLoc)
				
			ent++;
			entry->setData(ent);
				
			directories->insert(&ukLoc, &keyEntry);
		}
		
		while (_findnext(handle, &find) == 0) {
			if (find.attrib & _A_SUBDIR) {
				UAP_REQUEST(getModuleInstance(), lb_I_DirLocation, dLoc)
				UAP(lb_I_Unknown, ukLoc)
					
				UAP_REQUEST(getModuleInstance(), lb_I_String, fullPath)
					
				*fullPath = path;
				*fullPath += "\\";
				*fullPath += find.name;
					
				dLoc->setData(fullPath->charrep());
				QI(dLoc, lb_I_Unknown, ukLoc)
					
				ent++;
				entry->setData(ent);
					
				directories->insert(&ukLoc, &keyEntry);
			}
		}
		
		_findclose(handle);
	}

	free(toFind);

#endif
	
#ifdef LINUX
#ifndef OSX
	DIR *dir;
	struct dirent *dir_info;
	if ((dir = opendir(pluginDir)) != NULL) {
	
		dir_info = readdir(dir);
		
		while (dir_info != NULL) {
			if (dir_info->d_type == DT_DIR && strcmp(dir_info->d_name, ".") != 0 && strcmp(dir_info->d_name, "..") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_DirLocation, dLoc)
				UAP(lb_I_Unknown, ukLoc)
				
				UAP_REQUEST(getModuleInstance(), lb_I_String, fullPath)
				
				*fullPath = path;
				*fullPath += "/";
				*fullPath += dir_info->d_name;
				
				dLoc->setData(fullPath->charrep());
				QI(dLoc, lb_I_Unknown, ukLoc)
				
				ent++;
				entry->setData(ent);
				
				directories->insert(&ukLoc, &keyEntry);
			}
			
			dir_info = readdir(dir);
		}
	}
#endif
#endif
	
#ifdef OSX
	DIR *dir;
	struct dirent *dir_info;
	if ((dir = opendir(pluginDir)) != NULL) {
	
		dir_info = readdir(dir);
		
		while (dir_info != NULL) {
			if (dir_info->d_type == DT_DIR && strcmp(dir_info->d_name, ".") != 0 && strcmp(dir_info->d_name, "..") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_DirLocation, dLoc)
				UAP(lb_I_Unknown, ukLoc)
				
				UAP_REQUEST(getModuleInstance(), lb_I_String, fullPath)
				
				*fullPath = path;
				*fullPath += "/";
				*fullPath += dir_info->d_name;
				
				dLoc->setData(fullPath->charrep());
				QI(dLoc, lb_I_Unknown, ukLoc)
				
				ent++;
				entry->setData(ent);
				
				directories->insert(&ukLoc, &keyEntry);
			}
			
			dir_info = readdir(dir);
		}
	}
#endif
	
	return *&directories;	
}

lb_I_Container* LB_STDCALL DirectoryBrowser::getFiles(const char* path) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, _path)
	*_path = path;
	
	return getFiles(*&_path);
}

lb_I_Container* LB_STDCALL DirectoryBrowser::getFiles(lb_I_String* path) {
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, entry)
	UAP(lb_I_KeyBase, keyEntry)
	int ent = 0;

	UAP_REQUEST(getModuleInstance(), lb_I_Container, directories)
	directories++;
	
	QI(entry, lb_I_KeyBase, keyEntry)
	
	char* pluginDir = path->charrep();
	
#ifdef WINDOWS
	_finddata_t find;
	const char* mask = "*.*";
	char* toFind = (char*) malloc(strlen(mask)+strlen(pluginDir)+2);
	toFind[0] = 0;
	
	strcat(toFind, pluginDir);
	strcat(toFind, "\\");
	strcat(toFind, mask);

	long handle = _findfirst(toFind, &find);

	if (handle != -1) {
		if (!(find.attrib & _A_SUBDIR) && strcmp(find.name, ".") != 0 && strcmp(find.name, "..") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, dLoc)
			UAP(lb_I_Unknown, ukLoc)
				
			UAP_REQUEST(getModuleInstance(), lb_I_String, fullPath)

			*fullPath = path;
			*fullPath += "\\";
			*fullPath += find.name;
				
			dLoc->setData(find.name);
			QI(dLoc, lb_I_Unknown, ukLoc)
				
			ent++;
			entry->setData(ent);
				
			directories->insert(&ukLoc, &keyEntry);
		}
		
		while (_findnext(handle, &find) == 0) {
			if (!(find.attrib & _A_SUBDIR)  && strcmp(find.name, ".") != 0 && strcmp(find.name, "..") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, dLoc)
				UAP(lb_I_Unknown, ukLoc)
					
				UAP_REQUEST(getModuleInstance(), lb_I_String, fullPath)
					
				*fullPath = path;
				*fullPath += "\\";
				*fullPath += find.name;
					
				dLoc->setData(find.name);
				QI(dLoc, lb_I_Unknown, ukLoc)
					
				ent++;
				entry->setData(ent);
					
				directories->insert(&ukLoc, &keyEntry);
			}
		}
		
		_findclose(handle);
	}

	free(toFind);
#endif
	
#ifdef LINUX
#ifndef OSX
	DIR *dir;
	struct dirent *dir_info;
	if ((dir = opendir(pluginDir)) != NULL) {
		
		dir_info = readdir(dir);
		
		while (dir_info != NULL) {
			if (dir_info->d_type != DT_DIR && strcmp(dir_info->d_name, ".") != 0 && strcmp(dir_info->d_name, "..") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, fLoc)
				UAP(lb_I_Unknown, ukLoc)
				
				fLoc->setData(dir_info->d_name);
				QI(fLoc, lb_I_Unknown, ukLoc)
				
				ent++;
				entry->setData(ent);
				
				directories->insert(&ukLoc, &keyEntry);
			}
			
			dir_info = readdir(dir);
		}
	}
#endif
#endif
	
#ifdef OSX
	DIR *dir;
	struct dirent *dir_info;
	if ((dir = opendir(pluginDir)) != NULL) {
		
		dir_info = readdir(dir);
		
		while (dir_info != NULL) {
			if (dir_info->d_type != DT_DIR && strcmp(dir_info->d_name, ".") != 0 && strcmp(dir_info->d_name, "..") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, fLoc)
				UAP(lb_I_Unknown, ukLoc)
				
				fLoc->setData(dir_info->d_name);
				QI(fLoc, lb_I_Unknown, ukLoc)
				
				ent++;
				entry->setData(ent);
				
				directories->insert(&ukLoc, &keyEntry);
			}
			
			dir_info = readdir(dir);
		}
	}
#endif
	
	return *&directories;
}

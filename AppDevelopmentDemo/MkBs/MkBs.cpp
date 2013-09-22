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

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include <conio.h>
	
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <iostream>
#ifndef OSX
#include <malloc.h>
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

lb_I_Container* ScanDirectory(const char* path, const char* containsFile) {
	UAP_REQUEST(getModuleInstance(), lb_I_DirectoryBrowser, browser)
	UAP(lb_I_Container, directories)
	UAP_REQUEST(getModuleInstance(), lb_I_Container, directories_containsFile)
	UAP(lb_I_Container, files)

	directories = browser->getDirectories(path);

	directories->finishIteration();
	while (directories->hasMoreElements() != 0) {
		UAP(lb_I_Unknown, ukDir)
		UAP(lb_I_DirLocation, Dir)
		ukDir = directories->nextElement();
		QI(ukDir, lb_I_DirLocation, Dir)

		UAP_REQUEST(getModuleInstance(), lb_I_Integer, item)
		UAP(lb_I_KeyBase, keyItem)
		QI(item, lb_I_KeyBase, keyItem)
		
		//COUT << (char*)Dir->getData() << ENDL;
		
		files = browser->getFiles(Dir->getData());
		
		int i = 0;
		
		files->finishIteration();
		while (files->hasMoreElements() != 0) {
			UAP(lb_I_Unknown, ukFile)
			UAP(lb_I_FileLocation, File)
			
			ukFile = files->nextElement();
			QI(ukFile, lb_I_FileLocation, File)
			
			if (strcmp((char*)File->getData(), containsFile) == 0) {
				i++;
				item->setData(i);
				directories_containsFile->insert(&ukDir, &keyItem);
			}
		}
	}
	
	directories_containsFile++;
	
	return *&directories_containsFile;
}

void writeTargetSpec() {
#ifdef OSX	
	COUT << "" << ENDL;
	COUT << "TARGETPLUGIN=soplugin" << ENDL;
	COUT << "TARGETDLL=sobundle" << ENDL;
	COUT << "TARGETEXE=elf" << ENDL;
	COUT << "TARGETWXEXE=bundle" << ENDL;
	COUT << "TARGETWXPLUGIN=wxsoplugin" << ENDL;
	COUT << "TARGETSOBUNDLE=sobundle" << ENDL;
	COUT << "TARGETWXSHARED=wxshared" << ENDL;
	COUT << "" << ENDL;
#endif	
}

int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	
	if (argc <= 2) {
		COUT << "MkBs - Makefile bootstrapping tool." << ENDL;
		COUT << "Scans a directory for the existence of makefile.module files and builds an outer makefile." << ENDL;
		COUT << ENDL << "Usage: " << argv[0] << " <path> <target type>" << ENDL;
		
		return 0;
	}
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, R)
	*R = argv[1];
#ifndef WINDOWS
	*R += "/";
#endif
#ifdef WINDOWS
	*R += "\\";
#endif
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, string)
	string->setData("# Makefile generated automatically. Do not change.");
	
	COUT << string->charrep() << ENDL;

	writeTargetSpec();
	
	UAP(lb_I_Container, directories)
	
	directories = ScanDirectory(argv[1], "makefile.module");
	
	COUT << "" << ENDL;
	COUT << "all_targets: \\" << ENDL;
	
	directories->finishIteration();
	while (directories->hasMoreElements() != 0) {
		UAP(lb_I_Unknown, ukDir)
		UAP(lb_I_DirLocation, Dir)
		
		ukDir = directories->nextElement();
		QI(ukDir, lb_I_DirLocation, Dir)
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, D)
		*D = (char*)Dir->getData();
		
		D->replace(R->charrep(), "");
		
		COUT << "" << (char*) D->charrep() << " \\" << ENDL;
	}

	COUT << "" << ENDL;
	COUT << "" << ENDL;
	COUT << "dummy:" << ENDL;
	COUT << "" << ENDL;
	COUT << "" << ENDL;

	directories->finishIteration();
	while (directories->hasMoreElements() != 0) {
		UAP(lb_I_Unknown, ukDir)
		UAP(lb_I_DirLocation, Dir)
		
		ukDir = directories->nextElement();
		QI(ukDir, lb_I_DirLocation, Dir)

		UAP_REQUEST(getModuleInstance(), lb_I_String, D)
		*D = (char*)Dir->getData();
		
		D->replace(R->charrep(), "");
		
		COUT << "" << (char*) D->charrep() << ": dummy" << ENDL;
		COUT << "\t$(MAKE) -s -C $@ -e MODULE=" << D->charrep() << " -e TARGET=$(" << argv[2] << ") -f $(MAKE_CONFIG_FILE)" << ENDL;
		COUT << "\t$(MAKE) -s -C $@" << ENDL;
		COUT << "" << ENDL;
	}
	
	COUT << "" << ENDL;
	
	
	return 0;
}

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
#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif

/*...sincludes:0:*/
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

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <stdio.h>
#include <iostream>
#ifndef OSX
#ifndef USE_MPATROL
#ifndef MEMTRACK
#include <malloc.h>
#endif
#endif
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif
/*...e*/

#define LOOP


// (trackObject == NULL) ? "" : trackObject int argc, char *argv[]
int main(int argc, char *argv[])
{
	{
        lbErrCodes err = ERR_NONE;
		
		UAP_REQUEST(getModuleInstance(), lb_I_InputStream, is)

		setLogActivated(true);
		
		if (argc != 2) 
		{
			_CL_LOG << "************************************" LOG_
			_CL_LOG << "No parameter given. Need a filename." LOG_
			_CL_LOG << "************************************" LOG_
			return 1;
		}
		
        is->setFileName(argv[1]);
		is->open();

        if (is == NULL) return err;

        UAP(lb_I_Query, sampleQuery)
        UAP(lb_I_Database, sqldb)

		char* dbbackend = "DatabaseLayerGateway";
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, sqldb, "'database plugin'")
			_LOG << "lbDynamicApplication::initialize(): Using plugin database backend ..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, sqldb)
			_LOG << "lbDynamicApplication::initialize(): Using built in database backend ..." LOG_
		}

		if (sqldb == NULL) {
			_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
			return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
		}
		sqldb->init();

        char* DBName = "lbDMF";
        char* DBPass = "-";
        char* DBUser = "-";
        
        if (sqldb->connect(DBName, DBName, DBUser, DBPass) == ERR_NONE) {
			UAP(lb_I_String, sql)
			UAP_REQUEST(getModuleInstance(), lb_I_String, sqlmod)
			sampleQuery = sqldb->getQuery(DBName, 0);
			is->open();
			sql = is->getAsString();
			*sqlmod = "--Skip rewrite\n";
			*sqlmod += sql->charrep();
			if (sampleQuery->query(sqlmod->charrep()) != ERR_NONE) {
				_CL_LOG << "SQL query failed." LOG_
				return err;
			}
        }
	}
	unHookAll();
	return 0;
}

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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/
#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {      
#endif            
#ifndef OSX
#include <conio.h>
#endif
#ifdef __cplusplus
}
#endif            

#include <stdio.h>
#include <iostream>
#ifndef OSX
#ifndef USE_MPATROL
#include <malloc.h>
#endif
#endif
//#include "testdll.h"

#include <lbConfigHook.h>

lb_I_Unknown* findPluginByInterfaceAndNamespace(char* _interface, char* _namespace) {
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Plugin, pl)
		
	pl = PM->getFirstMatchingPlugin(_interface, _namespace);
	
		
	if (pl != NULL) {
				_CL_LOG << "References to plugin wrapper instance: " << pl->getRefCount() LOG_
       	        uk = pl->getImplementation();
       	        uk++;
       	        return uk.getPtr();
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;

{
#ifdef WINDOWS
	TRMemOpen();
	TRMemSetModuleName(__FILE__);
#endif	
	
	mm = getModuleInstance();

	UAP_REQUEST(mm, lb_I_String, preload)
	
	//PM->initialize();
	
	{
		UAP_REQUEST(mm, lb_I_PluginManager, PM)
		//UAP_REQUEST(mm, lb_I_Database, preloaddb)
		UAP(lb_I_Unknown, ukDatabaseWrapper)
		UAP(lb_I_Database, DatabaseWrapper)
		
		UAP(lb_I_Unknown, ukDatabaseWrapper1)
		UAP(lb_I_Database, DatabaseWrapper1)
		
		
		ukDatabaseWrapper = findPluginByInterfaceAndNamespace("lb_I_Database", "DatabaseLayerGateway");
		
		if (ukDatabaseWrapper == NULL) {
			_CL_LOG << "Database regression tests failed. Database gateway plugin not found." LOG_
			//preloaddb.resetPtr();
			//preloaddb = NULL;
			PM->unload();
			unHookAll();
			return 0;
		} else {
			QI(ukDatabaseWrapper, lb_I_Database, DatabaseWrapper)
			if (DatabaseWrapper == NULL) {
				_CL_LOG << "Database regression tests failed. Database gateway plugin has not the expected interface." LOG_
				//preloaddb.resetPtr();
				PM->unload();
				unHookAll();
				return 0;
			}
		}
		
		ukDatabaseWrapper1 = findPluginByInterfaceAndNamespace("lb_I_Database", "DatabaseLayerGateway");
		
		if (ukDatabaseWrapper1 == NULL) {
			_CL_LOG << "Database regression tests failed. Database gateway plugin not found." LOG_
			return 0;
		} else {
			QI(ukDatabaseWrapper1, lb_I_Database, DatabaseWrapper1)
			if (DatabaseWrapper1 == NULL) {
				_CL_LOG << "Database regression tests failed. Database gateway plugin has not the expected interface." LOG_
				return 0;
			}
		}
		
		_CL_LOG << "Database regression tests..." LOG_
			
			DatabaseWrapper->init();
		
		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
		DatabaseWrapper->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
		
		UAP(lb_I_Query, query2)
		UAP(lb_I_Query, queryA)
		UAP(lb_I_Query, query)
		UAP(lb_I_Query, query1)
			
		query = DatabaseWrapper->getQuery("lbDMF", 0);
		
		
		query1 = DatabaseWrapper->getQuery("lbDMF", 0);
		query1->skipFKCollecting();
		query1->query("drop table regressiontest");
		query1->query("drop table test");
		
		
		_CL_LOG << "query has " << query->getRefCount() << " references." LOG_

		char* buf = "create table regressiontest ("
			"id INTEGER PRIMARY KEY,"
			"test char(100) DEFAULT 'Nothing',"
			"btest bool DEFAULT false, "
			"btest1 bool DEFAULT false)";
			
		query->skipFKCollecting();
		query->query(buf);
			
			
		buf = 
			"CREATE TABLE test ("
			"	id INTEGER PRIMARY KEY,"
			"	test char(100),"
			"	id_reg INTEGER,"
			"	constraint fk_reg foreign key (id_reg) references regressiontest (id)"
			")";
		
		// I have problems which collecting foreign key data, if no result sets are there.
		query->skipFKCollecting();
		query->query(buf);
		
		_CL_LOG << "query has " << query->getRefCount() << " references." LOG_
			
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 1', 1, 0)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 2', 0, 1)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 3', 1, 0)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 4', 0, 1)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 5', 1, 0)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 6', 0, 1)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 7', 1, 0)");

		query1->query("select id, test, btest, btest1 from regressiontest");
		
		query1->PrintData();
		query1->PrintData(true);
		
		DatabaseWrapper1->init();
		
		lbDMFPasswd = getenv("lbDMFPasswd");
		lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
		DatabaseWrapper1->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
		
		query2 = DatabaseWrapper1->getQuery("lbDMF", 0);
		query2->skipPeeking();
		query2->query("select id, test, btest, btest1 from regressiontest");
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, column)
		UAP_REQUEST(getModuleInstance(), lb_I_String, value)
		
		query2->last();
		*column = "test";
		*value = "Updated column";
		query2->setString(*&column, *&value);
		*column = "btest";
		*value = "0";
		query2->setString(*&column, *&value);
		query2->update();
		
		query2->add();
		*column = "test";
		*value = "Inserted column";
		query2->setString(*&column, *&value);
		*column = "btest";
		*value = "0";
		query2->setString(*&column, *&value);
		query2->update();
		
		query2->PrintData();
		
		query2->enableFKCollecting();
		query2->query("select * from test");
		int fkcolumns = query2->getFKColumns();
		
		_CL_LOG << "Have " << fkcolumns << " foreign keys in table." LOG_
		
		_CL_LOG << "Done testing DatabaseLayer wrapper." LOG_

		//preloaddb.resetPtr();
		PM->unload();
		unHookAll();
	}

}

        return 0;
}

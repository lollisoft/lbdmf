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
#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif
/*...sincludes:0:*/
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
#include <iostream.h>
#ifndef OSX
#include <malloc.h>
#endif
//#include "testdll.h"

#include <lbConfigHook.h>
/*...e*/

/*...sDocumentation:0:*/
/** \page Regressiontests1 Testing DMF environment - Test table creation, char's and bool's.
 *
 * \section Introduction
 *
 * This test is intented to show the proper function of usual queries like table creation, select's
 * and also getting back correct data.
 *
 * \code
int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;
	
	// Get the module manager
	
	mm = getModuleInstance();
	mm->setModuleManager(mm, __FILE__, __LINE__);

	_CL_LOG << "Database regression tests..." LOG_
	
	UAP_REQUEST(mm, lb_I_Database, database)

	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", lbDMFUser, lbDMFPasswd);

	UAP(lb_I_Query, query, __FILE__, __LINE__)
	UAP(lb_I_Query, query1, __FILE__, __LINE__)
	UAP(lb_I_Query, query2, __FILE__, __LINE__)
	UAP(lb_I_Query, query3, __FILE__, __LINE__)

	query = database->getQuery(0);

	char buf[] = "create table regressiontest ("
			"test char(100) DEFAULT 'Nothing',\n"
			"btest bool DEFAULT false);";

	query->query(buf);

	query1 = database->getQuery(0);
	query1->query("insert into regressiontest (test) values('Nix')");
	query1->query("insert into regressiontest (btest) values(true)");

	query2 = database->getQuery(0);
	query2->query("select btest, test from regressiontest");

	err = query2->first();

	while (err == ERR_NONE || err == WARN_DB_NODATA) {
		_CL_LOG << "Values are '" << 
			query2->getAsString(1)->charrep() << 
			"' and '" << 
			query2->getAsString(2)->charrep() << "'" LOG_	
		
		err = query2->next();
	}
	
	query3 = database->getQuery(0);
	
	query3->query("drop table regressiontest");

        return 0;
}
 * \endcode
 *
 * \section Details
 *
 */
/*...e*/

int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;
	
	mm = getModuleInstance();
	mm->setModuleManager(mm, __FILE__, __LINE__);

	_CL_LOG << "Database regression tests..." LOG_
	
	UAP_REQUEST(mm, lb_I_Database, database)

	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", lbDMFUser, lbDMFPasswd);

	UAP(lb_I_Query, query, __FILE__, __LINE__)
	UAP(lb_I_Query, query1, __FILE__, __LINE__)
	UAP(lb_I_Query, query2, __FILE__, __LINE__)
	UAP(lb_I_Query, query3, __FILE__, __LINE__)

	query = database->getQuery(0);

	char buf[] = "create table regressiontest ("
			"test char(100) DEFAULT 'Nothing',\n"
			"btest bool DEFAULT false);";

	query->query(buf);

	query1 = database->getQuery(0);
	query1->query("insert into regressiontest (test) values('Nix')");
	query1->query("insert into regressiontest (btest) values(true)");

	query2 = database->getQuery(0);
	query2->query("select btest, test from regressiontest");

	err = query2->first();

	while (err == ERR_NONE || err == WARN_DB_NODATA) {
		_CL_LOG << "Values are '" << 
			query2->getAsString(1)->charrep() << 
			"' and '" << 
			query2->getAsString(2)->charrep() << "'" LOG_	
		
		err = query2->next();
	}
	
	query3 = database->getQuery(0);
	
	query3->query("drop table regressiontest");

        return 0;
}

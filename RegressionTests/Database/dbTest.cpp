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
#include <iostream>
#ifndef OSX
#ifndef USE_MPATROL
#include <malloc.h>
#endif
#endif
//#include "testdll.h"

#include <lbConfigHook.h>
/*...e*/

/*...sDocumentation:0:*/
/** \page Databasetests Testing DMF environment - Test table creation, char's and bool's.
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
			"btest bool DEFAULT false, "
			"btest1 bool DEFAULT false"
			");";

	query->query(buf);

	query1 = database->getQuery(0);
	query1->query("insert into regressiontest (test) values('Nix')");
	query1->query("insert into regressiontest (btest) values(true)");
	query1->query("insert into regressiontest (btest1) values(true)");

	query2 = database->getQuery(0);
	query2->query("select test, btest, btest1 from regressiontest");

	query2->PrintData();
	
	query3 = database->getQuery(0);
	
	query3->query("drop table regressiontest");
	query3->query("select tablename, name, \"specialColumn\", \"controlType\", ro from column_types");
	query3->PrintData();


	lb_I_Query::lbDBColumnTypes coltype = query3->getColumnType(5);

	switch (coltype) {
		case lb_I_Query::lbDBColumnBit:
			_CL_LOG << "lb_I_Query::lbDBColumnBit" LOG_
			break;
					
		case lb_I_Query::lbDBColumnChar:
			_CL_LOG << "lb_I_Query::lbDBColumnChar" LOG_
			break;
					
		case lb_I_Query::lbDBColumnBinary:
			_CL_LOG << "lb_I_Query::lbDBColumn" LOG_
			break;

		case lb_I_Query::lbDBColumnInteger:
			_CL_LOG << "lb_I_Query::lbDBColumnInteger" LOG_
			break;
					
		case lb_I_Query::lbDBColumnUnknown:
			_CL_LOG << "lb_I_Query::lbDBColumnUnknown" LOG_
			break;
	}

	query3->first();

	UAP_REQUEST(mm, lb_I_String, col)
	UAP_REQUEST(mm, lb_I_String, val)
	
	col->setData("ro");
	val->setData("true");

	query3->setString(*&col, *&val);	
	
	_CL_LOG << "Try update:" LOG_
	
	query3->update();
	
	_CL_LOG << "Try move first" LOG_
	
	query3->first();

	_CL_LOG << "Print out changed data:" LOG_	
	query3->PrintData();

        return 0;
}
 * \endcode
 *
 * \section Details
 *
 * The test also checks the handling of default values.
 *
 */
/*...e*/

int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;

{
#ifdef WINDOWS
	TRMemOpen();
	TRMemSetModuleName(__FILE__);
#endif	
	
	mm = getModuleInstance();

	_CL_LOG << "Database regression tests..." LOG_

/*...sBlock:8:*/
	{
		UAP_REQUEST(mm, lb_I_String, preload)
	
		// Try preload lbClasses
	
		UAP_REQUEST(mm, lb_I_Database, database)

		database->init();

		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");

		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		database->connect("lbDMF", lbDMFUser, lbDMFPasswd);

		UAP(lb_I_Query, query2, __FILE__, __LINE__)
		UAP(lb_I_Query, queryA, __FILE__, __LINE__)
		UAP(lb_I_Query, query, __FILE__, __LINE__)
		UAP(lb_I_Query, query1, __FILE__, __LINE__)

		query = database->getQuery(0);


		query1 = database->getQuery(0);
		query1->skipFKCollecting();
		query1->query("drop table regressiontest");


		_CL_LOG << "query has " << query->getRefCount() << " references." LOG_
		char buf[] = "create table regressiontest ("
				"id serial,"
				"test char(100) DEFAULT 'Nothing',\n"
				"btest bool DEFAULT false, "
				"btest1 bool DEFAULT false"
				");";
	
		// I have problems which collecting foreign key data, if no result sets are there.
		query->skipFKCollecting();
		query->query(buf);

		_CL_LOG << "query has " << query->getRefCount() << " references." LOG_

		query1->query("insert into regressiontest (test) values('Nix 1')");
		query1->query("insert into regressiontest (btest) values(true)");
		query1->query("insert into regressiontest (btest1) values(true)");
		query1->query("insert into regressiontest (test) values('Nix 2')");
		query1->query("insert into regressiontest (btest) values(true)");
		query1->query("insert into regressiontest (btest1) values(true)");


		UAP_REQUEST(mm, lb_I_Database, database1)

		database1->init();

		lbDMFPasswd = getenv("lbDMFPasswd");
		lbDMFUser   = getenv("lbDMFUser");

		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		database1->connect("lbDMF", lbDMFUser, lbDMFPasswd);

		query2 = database1->getQuery(0);
		query2->skipPeeking();
		query2->query("select id, test, btest, btest1 from regressiontest order by id");

		query2->PrintData();

		query2->first();
		
		query2->next();
		query2->next();
		query2->next();
		query2->remove();
		//query2->previous();
		query2->PrintData();
		query2->PrintData(true);

	}
/*...e*/

	unHookAll();
		
	exit(0);

/*...sbla:0:*/
#ifdef bla

	UAP(lb_I_Query, query1, __FILE__, __LINE__)
	UAP(lb_I_Query, query2, __FILE__, __LINE__)
	UAP(lb_I_Query, query3, __FILE__, __LINE__)

	query1 = database->getQuery(0);
	query1->query("insert into regressiontest (test) values('Nix')");
	query1->query("insert into regressiontest (btest) values(true)");
	query1->query("insert into regressiontest (btest1) values(true)");

	query2 = database->getQuery(0);
	query2->query("select test, btest, btest1 from regressiontest");

//	query2->PrintData();
	
	
	query3->query("select tablename, name, 'specialColumn', 'controlType', ro from column_types");
//	query3->PrintData();

	_CL_LOG << "Test datatypes..." LOG_
	lb_I_Query::lbDBColumnTypes coltype = query3->getColumnType(5);

	switch (coltype) {
		case lb_I_Query::lbDBColumnBit:
			_CL_LOG << "lb_I_Query::lbDBColumnBit" LOG_
			break;
					
		case lb_I_Query::lbDBColumnChar:
			_CL_LOG << "lb_I_Query::lbDBColumnChar" LOG_
			break;
					
		case lb_I_Query::lbDBColumnBinary:
			_CL_LOG << "lb_I_Query::lbDBColumn" LOG_
			break;

		case lb_I_Query::lbDBColumnInteger:
			_CL_LOG << "lb_I_Query::lbDBColumnInteger" LOG_
			break;
					
		case lb_I_Query::lbDBColumnUnknown:
			_CL_LOG << "lb_I_Query::lbDBColumnUnknown" LOG_
			break;
	}
#ifdef TEST_SNORT
	database->connect("snort", "snort", "Muffin.345");
	
	UAP(lb_I_Query, query4, __FILE__, __LINE__)

	query4 = database->getQuery(0);

	char userQuery[1000] = "";
	
	COUT << "Please enter your SQL query: ";
	CIN.getline(userQuery, sizeof(userQuery));

//	query4->skipFKCollecting();	
	query4->query(userQuery);
	
	query4->PrintData();
#endif

#endif
/*...e*/
}

        return 0;
}

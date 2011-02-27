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

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

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

	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	UAP(lb_I_Query, query)
	UAP(lb_I_Query, query1)
	UAP(lb_I_Query, query2)
	UAP(lb_I_Query, query3)

	query = database->getQuery("lbDMF", 0);

	char buf[] = "create table regressiontest ("
			"test char(100) DEFAULT 'Nothing',\n"
			"btest bool DEFAULT false, "
			"btest1 bool DEFAULT false"
			");";

	query->query(buf);

	query1 = database->getQuery("lbDMF", 0);
	query1->query("insert into regressiontest (test) values('Nix')");
	query1->query("insert into regressiontest (btest) values(true)");
	query1->query("insert into regressiontest (btest1) values(true)");

	query2 = database->getQuery("lbDMF", 0);
	query2->query("select test, btest, btest1 from regressiontest");

	query2->PrintData();

	query3 = database->getQuery("lbDMF", 0);

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
	UAP_REQUEST(mm, lb_I_String, preload)

/*...sBlock:8:*/
	{

		// Try preload lbClasses

		UAP_REQUEST(mm, lb_I_Database, database)

		if (database->init() == ERR_DB_INIT) {
			_CL_LOG << "Error while database initializiation." LOG_
			unHookAll();
			return 0;
		}

		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");

		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		if (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE) {
			_CL_LOG << "Error: Could not login to the database!" LOG_
			unHookAll();
			return 0;
		}

		UAP(lb_I_Query, query2)
		UAP(lb_I_Query, queryA)
		UAP(lb_I_Query, query)
		UAP(lb_I_Query, query1)

		query = database->getQuery("lbDMF", 0);


		query1 = database->getQuery("lbDMF", 0);
		query1->skipFKCollecting();
		query1->query("drop table regressiontest");


		_CL_LOG << "query has " << query->getRefCount() << " references." LOG_
		char buf[] = "create table regressiontest ("
				"id serial,"
				"test char(100) DEFAULT 'Nothing',\n"
				"btest bool DEFAULT false, "
				"btest1 bool DEFAULT false,"
				"CONSTRAINT regressiontest_pkey PRIMARY KEY (id)"
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

		database1->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

		query2 = database1->getQuery("lbDMF", 0);
		query2->enableFKCollecting();
		query2->skipPeeking();
		query2->query("select id, test, btest, btest1 from regressiontest order by id");
#ifdef bla
		query2->query(
		"select * from Anwendungen inner join User_Anwendungen on "
		"Anwendungen.id = User_Anwendungen.anwendungenid "
		"inner join Users on User_Anwendungen.userid = Users.id where Users.userid = 'user'");
#endif
		query2->PrintData();

		query2->first();
		UAP_REQUEST(mm, lb_I_String, col)
		UAP_REQUEST(mm, lb_I_String, val)

		col->setData("btest");
		val->setData("true");

		query2->setString(*&col, *&val);
		query2->update();
		query2->next();
		query2->next();
		query2->next();
		query2->remove();
		query2->update();
		//query2->previous();

		query2->PrintData();
		query2->PrintData(true);


		UAP(lb_I_Query, query3)
		query3 = database1->getQuery("lbDMF", 0);

		query3->query("select 'userid', 'anwendungenid' from 'user_anwendungen' where userid = 2");

		query3->first();
		query3->add();

		*col = "userid";
		*val = "2";
		query3->setString(*&col, *&val);

		_CL_LOG << "Call query->update() on added row." LOG_
		query3->update();
		_CL_LOG << "Called query->update() on added row." LOG_

	}
/*...e*/

	unHookAll();
	exit(0);

/*...sbla:0:*/
#ifdef bla

	UAP(lb_I_Query, query1)
	UAP(lb_I_Query, query2)
	UAP(lb_I_Query, query3)

	query1 = database->getQuery("lbDMF", 0);
	query1->query("insert into regressiontest (test) values('Nix')");
	query1->query("insert into regressiontest (btest) values(true)");
	query1->query("insert into regressiontest (btest1) values(true)");

	query2 = database->getQuery("lbDMF", 0);
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
	database->connect("snort", "snort", "snort", "Muffin.345");

	UAP(lb_I_Query, query4)

	query4 = database->getQuery("snort", 0);

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

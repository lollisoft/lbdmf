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

	char brk[100] = "";
	
	cout << "Please enter TRMem breakpoint address: ";
	cin >> brk;

#ifdef WINDOWS
	
	TRMemOpen();
	TRMemSetModuleName(__FILE__);
	TRMemSetAdrBreakPoint(brk);

	// Tell other modules the same breakpoint.
	setTRMemTrackBreak(brk);
#endif	
	
	mm = getModuleInstance();
	mm->setModuleManager(mm, __FILE__, __LINE__);

	_CL_LOG << "Database regression tests..." LOG_

	UAP_REQUEST(mm, lb_I_String, preload)
	
	// Try preload lbClasses
	
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
	
#ifdef bla
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
#endif

//_CL_LOG << "Check cleanup of main.................................." LOG_
//	setVerbose(true);
}
//setVerbose(false);
//_CL_LOG << "Checked cleanup of main................................" LOG_


        return 0;
}

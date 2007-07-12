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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/
/*...e*/
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

#include <lbConfigHook.h>

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

	{
		UAP_REQUEST(mm, lb_I_String, preload)
		UAP_REQUEST(mm, lb_I_Database, database)

		database->init();

		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");

		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

		UAP_REQUEST(mm, lb_I_String, col)
		UAP_REQUEST(mm, lb_I_String, val)
		
		UAP(lb_I_Query, query)
		UAP(lb_I_Query, query1)
		UAP(lb_I_Query, query2)
		
		query = database->getQuery("lbDMF", 0);
		query1 = database->getQuery("lbDMF", 0);
		query2 = database->getQuery("lbDMF", 0);


		query1->skipFKCollecting();
		query1->query("delete from \"user_anwendungen\"");
		query1->query("insert user_anwendungen (userid,anwendungenid) values(1,1)");
		query1->query("insert user_anwendungen (userid,anwendungenid) values(1,2)");
		query1->query("insert user_anwendungen (userid,anwendungenid) values(1,3)");
		query1->query("insert user_anwendungen (userid,anwendungenid) values(1,4)");
		query1->query("insert user_anwendungen (userid,anwendungenid) values(1,5)");
		query1->enableFKCollecting();

		query->query("select \"userid\", \"anwendungenid\" from \"user_anwendungen\"");
		
		query->PrintData();
		
		query->first();
		query->update();
		query->next();
		query->update();
		query->next();
		query->update();
		query->next();
		query->update();
		query->next();
		query->update();
		query->add();
		*col = "userid";
		*val = "1";
		query->setString(*&col, *&val);
		*col = "anwendungenid";
		*val = "1";
		query->setString(*&col, *&val);
		_CL_LOG << "Call query->update() on added row with all fk values proper set." LOG_
		query->update();
		_CL_LOG << "Called query->update() on added row with all fk values proper set." LOG_

		query->add();

		// Assume some invalid data. Shouldn't make any problem, if columns are set to NULL. But it makes :-(

		*col = "userid";
		*val = "0";
		query->setString(*&col, *&val);
		*col = "anwendungenid";
		*val = "0";
		query->setString(*&col, *&val);
		
		if (query->isNullable("userid")) 
			query->setNull("userid");
		else
			_CL_LOG << "Column userid not set to NULL." LOG_

		if (query->isNullable("anwendungenid")) 
			query->setNull("anwendungenid");
		else
			_CL_LOG << "Column anwendungenid not set to NULL." LOG_

		if (!query->isNull("userid")) _CL_LOG << "Error: Expect column 'userid' to be NULL!" LOG_
		if (!query->isNull("anwendungenid")) _CL_LOG << "Error: Expect column 'anwendungenid' to be NULL!" LOG_
	
		_CL_LOG << "Call query->update() on added row with all fk values proper set to NULL." LOG_
		if (query->update() != ERR_NONE) {
			_CL_LOG << "Error adding wrong key values." LOG_
		}
		_CL_LOG << "Called query->update() on added row with all fk values proper set to NULL." LOG_

		query->add(); // Affect the next two calls.

		if (!query->isNull("userid")) _CL_LOG << "Error: Expect column 'userid' to be NULL!" LOG_
		if (!query->isNull("anwendungenid")) _CL_LOG << "Error: Expect column 'anwendungenid' to be NULL!" LOG_

		query2->query("select \"userid\", \"anwendungenid\" from \"user_anwendungen\" where userid = 2");
		query2->first();
		query2->add();
		_CL_LOG << "Call query->update() on added row with default values." LOG_
		query2->update();
		_CL_LOG << "Called query->update() on added row with default values." LOG_

	}

	unHookAll();
	exit(0);

}

        return 0;
}

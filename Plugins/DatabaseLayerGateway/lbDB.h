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

#ifndef __LB_DATABASELAYERWRAPPER__
#define __LB_DATABASELAYERWRAPPER__
/*...sRevision history:0:*/
/*...e*/

#include <iostream>

class DatabaseLayer;

class lbDatabase :
public lb_I_Database
{
private:

	DECLARE_LB_UNKNOWN()

public:
        lbDatabase();
        virtual ~lbDatabase();

	lbErrCodes	LB_STDCALL init();
	void	LB_STDCALL close();
	void	LB_STDCALL open(char* connectionname);
	
	bool		LB_STDCALL isConnected();
	
	/**
	 * Makes a connection to the specified database. For ODBC database drivers,
	 * the DSN is a simple name without a special driver postfix.
	 *
	 * Input:	DSN	database name (name[:driver][:host][:port])
	 *		user	database user
	 *		passwd	database password
	 */
	lbErrCodes	LB_STDCALL connect(char* connectionname, char* DSN, char* user, char* passwd);
	lb_I_Query*	LB_STDCALL getQuery(char* connectionname, int readonly = 1);

	lbErrCodes	LB_STDCALL connect(char* connectionname, char* pass);

	lbErrCodes	LB_STDCALL setUser(char* _user);
	lbErrCodes	LB_STDCALL setDB(char* _db);	
	
	lb_I_Container* LB_STDCALL getTables(char* connectionname);
	lb_I_Container* LB_STDCALL getColumns(char* connectionname);
	
	lb_I_Container* LB_STDCALL getForeignKeys(char* connectionname);
	lb_I_Container* LB_STDCALL getPrimaryKeys(char* connectionname);
	
private:
	RETCODE  retcode;
	HENV     henv;	
	HDBC     hdbc;
	char*	 user;
	char*	 db;
	bool	 connected;
	DatabaseLayer* dbl;

	UAP(lb_I_Container, connPooling)
};


/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

//lbErrCodes DLLEXPORT LB_STDCALL lb_releaseInstance(lb_I_Unknown * inst);
DECLARE_SINGLETON_FUNCTOR(instanceOfDatabase)
DECLARE_FUNCTOR(instanceOfConnection)
DECLARE_FUNCTOR(instanceOfDBInterfaceRepository)
DECLARE_FUNCTOR(instanceOfDatabaseForm)
/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
}
#endif

/*...e*/

#endif // __LB_DATABASELAYERWRAPPER__

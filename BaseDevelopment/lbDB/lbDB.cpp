/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    lbModule.h is part of DMF.
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
            Borsteler Bogen 4

            22453 Hamburg (germany)
*/

/*...sincludes:0:*/
#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <malloc.h>

#include <lbInterfaces.h>
#include <lbConfigHook.h>

/*...sLB_DATABASE_DLL scope:0:*/
#define LB_DB_DLL
#include <lbdb-module.h>
/*...e*/

#include <lbDB.h>
/*...e*/

extern "C" {
#include <sql.h>
#include <sqlext.h>
}
#define SZLEN 300
#define SZDATELEN 24

#ifndef WINDOWS
#define lstrcpy strcpy
#endif

void process(void);
void dbError( LPSTR lp, HENV henv,HDBC hdbc,HSTMT hstmt);


/*
class lbStatement :
public lb_I_SQLStatement
{
        lbStatement();
        virtual ~lbStatement();
private:

	DECLARE_LB_UNKNOWN()

public:
	lb_I_Column* getColumn(int pos);
};

class lbColumn;
class lbBoundColumn;

*/

class lbDatabase :
public lb_I_Database
{
private:

	DECLARE_LB_UNKNOWN()

public:
        lbDatabase();
        virtual ~lbDatabase();
	
	/**
	 * Makes a connection to the specified database. For ODBC database drivers,
	 * the DSN is a simple name without a special driver postfix.
	 *
	 * Input:	DSN	database name (name[:driver][:host][:port])
	 *		user	database user
	 *		passwd	database password
	 */
	virtual lbErrCodes LB_STDCALL connect(char* DSN, char* user, char* passwd);

};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabase)
	ADD_INTERFACE(lb_I_Database)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfDatabase, lbDatabase)

lbDatabase::lbDatabase() {
}

lbDatabase::~lbDatabase() {
}

lbErrCodes LB_STDCALL lbDatabase::setData(lb_I_Unknown* uk) {
	_CL_LOG << "lbInstanceReference::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbDatabase::connect(char* DSN, char* user, char* passwd) {
    process();
    return ERR_NONE;
}

void process(void)
{
SDWORD cbempno;
SDWORD cbename;
SDWORD cbobjecttyp;
SDWORD cbjob;
SDWORD cbmgr;
SDWORD cbhiredate;
SDWORD cbsal;
SDWORD cbcomm;
SDWORD cbdeptno;
SDWORD cbX;
SDWORD cbY;
SDWORD cbW;
SDWORD cbH;
double dblempno;
double dblmgr;
double dblsal;
double dblcomm;
double dbldeptno;
long X;
long Y;
long W;
long H;
char   szename[SZLEN+1];
char   szobjecttyp[SZLEN+1];
char   szjob[SZLEN+1];
char   szhiredate[SZDATELEN+1];
HSTMT      hstmt = 0;
//SQLRETURN  retcode;
RETCODE  retcode;
HENV       henv = 0;
HDBC       hdbc = 0;
char       szSql[256];
char       szout[256];
TIMESTAMP_STRUCT ts;

retcode = SQLAllocEnv(&henv);              /* Environment handle */

if (retcode != SQL_SUCCESS)
        {
        dbError( "SQLAllocEnv()",henv,hdbc,hstmt);
        return;
        }

retcode = SQLAllocConnect(henv, &hdbc); /* Connection handle */

if (retcode != SQL_SUCCESS)
        {
        dbError( "SQLAllocConnect()",henv,hdbc,hstmt);
        SQLFreeEnv(henv);
        return;
        }

SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 15); /* Set login timeout to 15 seconds. */
retcode = SQLConnect(hdbc, (unsigned char*) "trainres", SQL_NTS, (unsigned char*) "trainres", SQL_NTS, (unsigned char*) "", SQL_NTS); /* Connect to data source */

if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
        {
        dbError( "SQLConnect()",henv,hdbc,hstmt);
        SQLFreeEnv(henv);
        return;
        } else {
            SQLFreeEnv(henv);
            printf("Connection succeeded.\n");
//            getch();
//            return;
        }


retcode = SQLAllocStmt(hdbc, &hstmt); /* Statement handle */

if (retcode != SQL_SUCCESS)
        {
        dbError( "SQLAllocStmt()",henv,hdbc,hstmt);
        SQLFreeEnv(henv);
        return;
        }

//lstrcpy( szSql,"select empno,ename,job,mgr,hiredate,sal,nvl(comm,0),deptno from emp order by empno asc");
lstrcpy( szSql,"select ObjectTyp, X, Y, W, H from World order by X, Y");

retcode = SQLExecDirect(hstmt, (unsigned char*) szSql, SQL_NTS);

if (retcode != SQL_SUCCESS)
        {
        dbError( " SQLExecDirect()",henv,hdbc,hstmt);
        }

if (retcode == SQL_SUCCESS)
        {

        printf("%10s\tX\tY\tW\tH\n", "ObjectType");
        while (true)
                {
                retcode = SQLFetch(hstmt);

                if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
                        {
                        dbError( "SQLFetch()",henv,hdbc,hstmt);
                        }

                if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                        {
/*
                        SQLGetData(hstmt, 1,SQL_C_DOUBLE, &dblempno,    0,     &cbempno);
                        SQLGetData(hstmt, 2,SQL_C_CHAR,   szename,      SZLEN, &cbename);
                        SQLGetData(hstmt, 3,SQL_C_CHAR,   szjob,        SZLEN, &cbjob);
                        SQLGetData(hstmt, 4,SQL_C_DOUBLE, &dblmgr,      0,     &cbmgr);
                        SQLGetData(hstmt, 5,SQL_C_DATE,   &ts,   16, &cbhiredate);
                        SQLGetData(hstmt, 6,SQL_C_DOUBLE, &dblsal,      0,     &cbsal);
                        SQLGetData(hstmt, 7,SQL_C_DOUBLE, &dblcomm,     0,     &cbcomm);
                        SQLGetData(hstmt, 8,SQL_C_DOUBLE, &dbldeptno,   0,     &cbdeptno);
*/
                        SQLGetData(hstmt, 1,SQL_C_CHAR,   szobjecttyp,      SZLEN, &cbobjecttyp);
                        SQLGetData(hstmt, 2,SQL_C_LONG, &X,      0,     &cbX);
                        SQLGetData(hstmt, 3,SQL_C_LONG, &Y,      0,     &cbY);
                        SQLGetData(hstmt, 4,SQL_C_LONG, &W,      0,     &cbW);
                        SQLGetData(hstmt, 5,SQL_C_LONG, &H,      0,     &cbH);


//                        sprintf( szhiredate,"%d-%d-%d",ts.month,ts.day,ts.year);
//                        sprintf(szout,"%6.0f\t%s\t%s\t%6.0f\t%s\t%6.0f\t%6.0f\t%6.0f\n",dblempno,szename,szjob,dblmgr,szhiredate,dblsal,dblcomm,dbldeptno);
                        printf("%10s\t%d\t%d\t%d\t%d\n", szobjecttyp, X, Y, W, H);
//                        puts(szout);
                        }
                else
                        {
                        break;
                        }
                }
        }

SQLFreeStmt(hstmt, SQL_DROP);
SQLDisconnect(hdbc);
SQLFreeConnect(hdbc);
SQLFreeEnv(henv);
}
// ------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------
void dbError( LPSTR lp, HENV henv,HDBC hdbc,HSTMT hstmt)
{
unsigned char buf[250];
unsigned char sqlstate[15];

SQLError( henv, hdbc, hstmt, sqlstate, NULL,buf, sizeof(buf), NULL);
fprintf(stderr, "%s. %s, SQLSTATE=%s\n",lp, buf, sqlstate);
}
// -------------------------------------------------------------------------------------------------------------



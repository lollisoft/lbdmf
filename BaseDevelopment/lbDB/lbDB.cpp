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

/*...sclass lbDBView:0:*/
class lbDBView: public lb_I_MVC_View
{
public:
	lbDBView() {}
	virtual ~lbDBView() {}
	
	DECLARE_LB_UNKNOWN()
	
/*...svirtual lbErrCodes LB_STDCALL updateView\40\\41\\59\:8:*/
        /*------ MVC variant ------------*/
        /* Data is available, I can read it out ... */
        virtual lbErrCodes LB_STDCALL updateView();
/*...e*/
        
/*...svirtual lbErrCodes LB_STDCALL setViewSource\40\lb_I_Unknown\42\ q\41\\59\:8:*/
        /* The view source is the data, that should be displayed.
         * As this would be a database view, the function tries to get
         * a lb_I_Query source.
         */
        virtual lbErrCodes LB_STDCALL setViewSource(lb_I_Unknown* q);
/*...e*/
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDBView)
        ADD_INTERFACE(lb_I_MVC_View)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfDBView, lbDBView)


lbErrCodes LB_STDCALL lbDBView::setData(lb_I_Unknown* uk) {
	_CL_LOG << "lbDBView::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}


lbErrCodes LB_STDCALL lbDBView::updateView() {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDBView::setViewSource(lb_I_Unknown* q) {
	return ERR_NONE;
}
/*...e*/
/*...sclass lbQuery:0:*/
class lbQuery :
public lb_I_Query
{
public:
	lbQuery() { hdbc = 0; hstmt = 0; }
	virtual ~lbQuery() {}
	
	DECLARE_LB_UNKNOWN()

	/* Column binding mode */
        virtual lbErrCodes LB_STDCALL setView(lb_I_ColumnBinding* cb);

/*...svirtual lbErrCodes LB_STDCALL \40\un\41\registerView\40\lb_I_MVC_View\42\ view\41\\59\:8:*/
	/* MVC View mode */
	/*
	 * As a sample may be a graphical view for the result of the interpreted
	 * graphics and the textual view. The controller then might use one button
	 * for updating the model and the model then informs its views.
	 */
	virtual lbErrCodes LB_STDCALL registerView(lb_I_MVC_View* view);
	virtual lbErrCodes LB_STDCALL unregisterView(lb_I_MVC_View* view);
/*...e*/

        /* Set the SQL query */
        virtual lbErrCodes LB_STDCALL query(char* q);
        
        /* Navigation */
        virtual lbErrCodes LB_STDCALL first();
        virtual lbErrCodes LB_STDCALL next();
        virtual lbErrCodes LB_STDCALL previous();
        virtual lbErrCodes LB_STDCALL last();
	
	lbErrCodes LB_STDCALL init(HENV henv, HDBC _hdbc);

private:
	HENV    henv;
	HDBC    hdbc;
	HSTMT   hstmt;
	RETCODE retcode;
	char    szSql[256];
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbQuery)
        ADD_INTERFACE(lb_I_Query)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbQuery::setData(lb_I_Unknown * uk) {
	_LOG << "lbQuery::setData(...): Not implemented yet" LOG_
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbQuery::setView(lb_I_ColumnBinding* cb) {
	_LOG << "lbQuery::setView(...): Not implemented yet" LOG_
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbQuery::registerView(lb_I_MVC_View* view) {
	_LOG << "lbQuery::registerView(...): Not implemented yet" LOG_
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbQuery::unregisterView(lb_I_MVC_View* view) {
	_LOG << "lbQuery::unregisterView(...): Not implemented yet" LOG_
        return ERR_NONE;
}

lbErrCodes LB_STDCALL lbQuery::init(HENV henv, HDBC _hdbc) {
	hdbc = _hdbc;

	retcode = SQLAllocStmt(hdbc, &hstmt); /* Statement handle */

	if (retcode != SQL_SUCCESS)
	{
	        dbError( "SQLAllocStmt()",henv,hdbc,hstmt);
	        _LOG << "lbDatabase::getQuery() failed due to statement allocation." LOG_
	        SQLFreeEnv(henv);
        	return ERR_DB_ALLOCSTATEMENT;
	}
	
	//retcode = SQLSetStmtOption(hstmt, SQL_CURSOR_TYPE, SQL_CURSOR_STATIC);
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbQuery::query(char* q) {

	lstrcpy(szSql, q);

	retcode = SQLExecDirect(hstmt, (unsigned char*) szSql, SQL_NTS);

	if (retcode != SQL_SUCCESS)
        {
        	dbError( "SQLExecDirect()",henv,hdbc,hstmt);
		_LOG << "lbQuery::query(...) failed." LOG_
		return ERR_DB_QUERYFAILED;
        }

	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbQuery::first() {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbQuery::next() {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbQuery::previous() {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbQuery::last() {
	return ERR_NONE;
}
/*...e*/
/*...sclass lbDatabase:0:*/
class lbDatabase :
public lb_I_Database
{
private:

	DECLARE_LB_UNKNOWN()

public:
        lbDatabase();
        virtual ~lbDatabase();

	virtual lbErrCodes LB_STDCALL init();
	
	/**
	 * Makes a connection to the specified database. For ODBC database drivers,
	 * the DSN is a simple name without a special driver postfix.
	 *
	 * Input:	DSN	database name (name[:driver][:host][:port])
	 *		user	database user
	 *		passwd	database password
	 */
	virtual lbErrCodes LB_STDCALL connect(char* DSN, char* user, char* passwd);
	virtual lb_I_Query* LB_STDCALL getQuery();
	
	
	
private:
	RETCODE  retcode;
	HENV     henv;	
	HDBC     hdbc;
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabase)
	ADD_INTERFACE(lb_I_Database)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfDatabase, lbDatabase)

lbDatabase::lbDatabase() {
	henv = 0;
	hdbc = 0;
}

lbDatabase::~lbDatabase() {
}

/*...slbErrCodes LB_STDCALL lbDatabase\58\\58\init\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabase::init() {
	retcode = SQLAllocEnv(&henv);
	if (retcode != SQL_SUCCESS) {
        	dbError( "SQLAllocEnv()",henv,0,0);
        	_LOG << "Database initializion failed." LOG_
        	return ERR_DB_INIT;
        }
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabase\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabase::setData(lb_I_Unknown* uk) {
	_CL_LOG << "lbInstanceReference::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabase\58\\58\connect\40\char\42\ DSN\44\ char\42\ user\44\ char\42\ passwd\41\:0:*/
lbErrCodes LB_STDCALL lbDatabase::connect(char* DSN, char* user, char* passwd) {
	retcode = SQLAllocConnect(henv, &hdbc); /* Connection handle */

	if (retcode != SQL_SUCCESS)
        {
        	dbError( "SQLAllocConnect()",henv,hdbc,0);
        	SQLFreeEnv(henv);
        	return ERR_DB_CONNECT;
        }	
	
	SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 15); /* Set login timeout to 15 seconds. */

	retcode = SQLConnect(hdbc, (unsigned char*) DSN, SQL_NTS, 
				   (unsigned char*) user, SQL_NTS, 
				   (unsigned char*) passwd, SQL_NTS); /* Connect to data source */

	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
        {
        	dbError( "SQLConnect()",henv,hdbc,0);
		_LOG << "Connection to database failed." LOG_
        	SQLFreeEnv(henv);
        	return ERR_DB_CONNECT;
        } else {
		SQLFreeEnv(henv);
		printf("Connection succeeded.\n");
        }

	return ERR_NONE;
}
/*...e*/
lb_I_Query* LB_STDCALL lbDatabase::getQuery() {
	lbQuery* query = new lbQuery;

	if (query->init(henv, hdbc) != ERR_NONE) return NULL;

	query->setModuleManager(*&manager, __FILE__, __LINE__);
	lb_I_Query* q;
	
	query->queryInterface("lb_I_Query", (void**) &q, __FILE__, __LINE__);

	return q;
}
/*...e*/
/*...svoid process\40\void\41\:0:*/
void process(void)
{
/*...svars:0:*/
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
/*...e*/

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
retcode = SQLConnect(hdbc, (unsigned char*) "trainres", SQL_NTS, (unsigned char*) "dba", SQL_NTS, (unsigned char*) "trainres", SQL_NTS); /* Connect to data source */

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
                        SQLGetData(hstmt, 1,SQL_C_CHAR,   szobjecttyp,      SZLEN, &cbobjecttyp);
                        SQLGetData(hstmt, 2,SQL_C_LONG, &X,      0,     &cbX);
                        SQLGetData(hstmt, 3,SQL_C_LONG, &Y,      0,     &cbY);
                        SQLGetData(hstmt, 4,SQL_C_LONG, &W,      0,     &cbW);
                        SQLGetData(hstmt, 5,SQL_C_LONG, &H,      0,     &cbH);


                        printf("%10s\t%d\t%d\t%d\t%d\n", szobjecttyp, X, Y, W, H);
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
/*...e*/
/*...svoid dbError\40\ LPSTR lp\44\ HENV henv\44\HDBC hdbc\44\HSTMT hstmt\41\:0:*/
void dbError( LPSTR lp, HENV henv,HDBC hdbc,HSTMT hstmt)
{
unsigned char buf[250];
unsigned char sqlstate[15];

SQLError( henv, hdbc, hstmt, sqlstate, NULL,buf, sizeof(buf), NULL);
fprintf(stderr, "%s. %s, SQLSTATE=%s\n",lp, buf, sqlstate);
}
/*...e*/



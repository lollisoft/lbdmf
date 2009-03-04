/*
	Based on Dave's post at google, this version is as close as possible to the scenario
	on what the crashes will happen.

	The scenario is aimed to be similar to my GUI with navigation, add and delete buttons,
	except the peek testing to inform the GUI about no more data before that really happens.

	It asks for the target database and then creates a table regarding to the SQL syntax
	of the database. It fills 6 rows of data into the table and later it tries to delete
	row 2 + 3.

	After this has been done a second data output will be performed to show the changes in
	non reverse and reverse order.

	Google posting: VARCHAR, CHAR types changed ?
	http://groups.google.com/group/pgsql.interfaces.odbc/browse_frm/thread/df155225d9d4a291/e9903c90492969b2#e9903c90492969b2
  
	Test's:
	
	MSSQL:		Deletes the two rows, but no detection of them to be deleted.
				There would be no datachanges, except the value in the primary
				key (id = 0).
	  
				All 6 rows would be printed out.
		
	Sybase:			There is a hang. Don't know why ?
		  
	PostgreSQL:		The data would be deleted and with my modified version of the ODBC driver
				I detect bodus pointer values (Linux/Windows).
			
				Driver version 07.03.0200 without changes does crash.
				Driver version 07.03.0200 with changes does not crash, but detection of
				bodus pointers does not result in a comparable output as of MSSQL.
			  
				Google posting: QR_get_value_backend_row returns invalid pointers !
				http://groups.google.com/group/pgsql.interfaces.odbc/browse_frm/thread/5eab6fe60712e7b6/a15b55bedd0bb9a4#a15b55bedd0bb9a4
				
	MySQL:			Not tested.

  
	TODO:	Find out, what are the reason's for the different database vendors.

		Fix the undefined behaviour in PostgreSQL driver version 07.03.0200.

		Why is there a difference between using 

		SQL_ATTR_ODBC_CURSORS = SQL_CUR_USE_IF_NEEDED
	
		and

		SQL_ATTR_ODBC_CURSORS = SQL_CUR_USE_ODBC
*/
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

#ifdef WINDOWS
#include <windows.h>
#endif
#ifndef WINDOWS
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#endif

#include <sqlext.h>
#include <stdio.h>
#include <iostream.h>

#define _SQL_ROW_DELETED 1000

void dbError(char* lp, HSTMT hstmt);
void PrintFooter(int cols);
void PrintHeader(int cols, HSTMT hstmt);
void PrintCurrent(int cols, HSTMT hstmt);
void _dbError_DBC(char* lp, HDBC hdbc);

// Fixed bound columns
char id[10] = "";
char test[200] = "";
char btest[100] = "";
char btest1[100] = "";
HDBC        hdbc = NULL;                            // Connection handle

void trim(char* stringdata) {
	while (stringdata[strlen(stringdata)-1] == ' ')
		stringdata[strlen(stringdata)-1] = 0;
}

void refresh(HSTMT hstmt) {
	RETCODE retcode = SQLSetPos(hstmt, 1, SQL_REFRESH, SQL_LOCK_NO_CHANGE);
	
	if (retcode != SQL_SUCCESS)
	{
		printf("ERROR: Refreshing data failed.\n");
		dbError("SQLSetPos(SQL_REFRESH)", hstmt);
	}
}

void remove(HSTMT hstmt, char* id) {
	//RETCODE retcode = SQLSetPos(hstmt, 1, SQL_DELETE, SQL_LOCK_NO_CHANGE);
	RETCODE retcode;

	HSTMT hstmt_delete;
	char buf[1000] = "delete from regressiontest where id = %s";
	char* SQL = (char*) malloc(strlen(buf)+1);

	sprintf(SQL, buf, id);

	retcode = SQLAllocStmt(hdbc, &hstmt_delete);

	if (retcode != SQL_SUCCESS)
	{
		_dbError_DBC("SQLAllocStmt()", hdbc);
	}

	SQLExecDirect(hstmt_delete, (UCHAR*) SQL, SQL_NTS);

	if (retcode != SQL_SUCCESS)
	{
		dbError("SQLExecDirect()", hstmt);
	}

	retcode = SQLFreeStmt(hstmt_delete, SQL_DROP);

	if (retcode != SQL_SUCCESS)
	{
		printf("ERROR: Removing data failed.\n");
		dbError("SQLSetPos(SQL_DELETE)", hstmt);
	}
/*	
	retcode = SQLSetPos(hstmt, 1, SQL_REFRESH, SQL_LOCK_NO_CHANGE);
	
	if (retcode != SQL_SUCCESS)
	{
		printf("ERROR: Removing data failed.\n");
		dbError("SQLSetPos(SQL_REFRESH)", hstmt);
	}
*/	
}

void update(HSTMT hstmt) {
	RETCODE retcode = SQLSetPos(hstmt, 1, SQL_UPDATE, SQL_LOCK_NO_CHANGE);
	
	if (retcode != SQL_SUCCESS)
	{
		dbError("SQLSetPos(SQL_UPDATE)", hstmt);
	}
}

#define CHECK_ROWSTAT() \
	if (retcode == SQL_ROW_DELETED) { \
	        printf("ERROR: This row is deleted.\n"); \
	        return _SQL_ROW_DELETED; \
	} \
        if (RowStat[0] == SQL_ROW_DELETED) { \
                printf("ERROR: This row is deleted.\n"); \
                return _SQL_ROW_DELETED; \
        } \
        if (RowStat[0] == SQL_ROW_NOROW) { \
                printf("ERROR: This row is norow.\n"); \
                if (retcode == SQL_NO_DATA) { \
                        cout << "ERROR: There would also be SQL_NO_DATA." << endl; \
                } \
        } \
        if (RowStat[0] == SQL_ROW_ERROR) { \
                printf("ERROR: This row is error.\n"); \
                if (retcode == SQL_NO_DATA) { \
                        cout << "ERROR: There would also be SQL_NO_DATA." << endl; \
                } \
        }

RETCODE absolute(HSTMT hstmt, int pos) {
	UWORD   RowStat[20];
	UDWORD  RowsFetched = 0;
	
	RETCODE retcode = SQLExtendedFetch(hstmt, SQL_FETCH_ABSOLUTE, pos, &RowsFetched, &RowStat[0]);
	
	CHECK_ROWSTAT()

	if (retcode != SQL_SUCCESS) dbError("SQLExtendedFetch()", hstmt);
	
	return retcode;
}

RETCODE last(HSTMT hstmt) {
	UWORD   RowStat[20];
	UDWORD  RowsFetched = 0;
	
	RETCODE retcode = SQLExtendedFetch(hstmt, SQL_FETCH_LAST, 0, &RowsFetched, &RowStat[0]);
	
	CHECK_ROWSTAT()

	if (retcode != SQL_SUCCESS) dbError("SQLExtendedFetch()", hstmt);
	
	return retcode;
}

RETCODE first(HSTMT hstmt) {
	UWORD   RowStat[20];
	UDWORD  RowsFetched = 0;
	
	RETCODE retcode = SQLExtendedFetch(hstmt, SQL_FETCH_FIRST, 0, &RowsFetched, &RowStat[0]);
	
	CHECK_ROWSTAT()

	if (retcode != SQL_SUCCESS) dbError("SQLExtendedFetch()", hstmt);
	
	return retcode;
}

RETCODE next(HSTMT hstmt) {
	UWORD   RowStat[20];
	UDWORD  RowsFetched = 0;
	
	RETCODE retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, &RowStat[0]);
	
	CHECK_ROWSTAT()

	if (retcode != SQL_SUCCESS) dbError("SQLExtendedFetch()", hstmt);
	
	return retcode;
}

RETCODE previous(HSTMT hstmt) {
	UWORD   RowStat[20];
	UDWORD  RowsFetched = 0;
	
	RETCODE retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, &RowStat[0]);
	
	CHECK_ROWSTAT()

	if (retcode != SQL_SUCCESS) dbError("SQLExtendedFetch()", hstmt);
	
	return retcode;
}

char lbQuery_column_Name[1000] = "";

char* getColumnName(HSTMT hstmt, int col) {
	SQLSMALLINT     ColumnNumber = 0;
	SQLCHAR         ColumnName[1000] = "";
	SQLSMALLINT     BufferLength = 500;
	SQLSMALLINT     DataType = 0;
	SQLSMALLINT     NameLength = 0;
	
	SQLSMALLINT     DecimalDigits = 0;
	SQLSMALLINT     Nullable = 0;
	SQLUINTEGER     ColumnSize;
	
	SQLRETURN ret = SQLDescribeCol( hstmt, col, ColumnName,
		BufferLength, &NameLength, &DataType,
		&ColumnSize, &DecimalDigits, &Nullable);
	
	if (ret != SQL_SUCCESS) {
		if (ret == SQL_SUCCESS_WITH_INFO) {
			strcpy(lbQuery_column_Name, (char*) ColumnName);
		} else {
			dbError("SQLDescribeCol()", hstmt);
			strcpy(lbQuery_column_Name, "");
		}
		
		return lbQuery_column_Name;
	} else {
		strcpy(lbQuery_column_Name, (char*) ColumnName);
		return lbQuery_column_Name;
	}
}


void PrintData(HSTMT hstmt, int cols, bool reverse, bool position = true) {
	RETCODE retcode;
	PrintHeader(cols, hstmt);
	if (reverse == false) {
		if (position == true) {
			retcode = first(hstmt);
			while (retcode == _SQL_ROW_DELETED) retcode = next(hstmt);
		} else {
			retcode = SQL_SUCCESS;
		}
		
		if ((retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO)) {
			PrintCurrent(cols, hstmt);
			retcode = next(hstmt);
			while (retcode == _SQL_ROW_DELETED) retcode = next(hstmt);
			while ((retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO)) {
				PrintCurrent(cols, hstmt);
				retcode = next(hstmt);
				while (retcode == _SQL_ROW_DELETED) retcode = next(hstmt);
			}      
		}
	} else {
		if (position == true) {
			retcode = last(hstmt);
			while (retcode == _SQL_ROW_DELETED) retcode = previous(hstmt);
		} else {
			retcode = SQL_SUCCESS;
		}

		if ((retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO)) {
			PrintCurrent(cols, hstmt);
			retcode = previous(hstmt);
			while (retcode == _SQL_ROW_DELETED) retcode = previous(hstmt);
			while ((retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO)) {
				PrintCurrent(cols, hstmt);
				retcode = previous(hstmt);
				while (retcode == _SQL_ROW_DELETED) retcode = previous(hstmt);
			}      
		}
	}
	PrintFooter(cols);
}

void PrintFooter(int cols) {
	for (int i = 1; i < cols; i++) {
		printf("-------------------");
	}
	
	printf("-------------------\n");
}

void PrintHeader(int cols, HSTMT hstmt) {
	for (int i = 1; i < cols; i++) {
		printf("%19s", getColumnName(hstmt, i));
	}
	
	printf("%19s\n", getColumnName(hstmt, cols));
	
	PrintFooter(cols);
}

// Future version of a bound column version.
typedef struct _boundColumn {
	void* buffer;
	int   column_size;
	char* columnName;
	_boundColumn* next;
} boundColumn;

/** \brief Print current row.
*
* This function prints the current row based on a fixed SQL query.
*/
void PrintCurrent(int cols, HSTMT hstmt) {
	char* temp;
	temp = strdup(id);
	trim(temp);
	printf("%19s", temp);
	free(temp);
	
	temp = strdup(test);
	trim(temp);
	printf("%19s", temp);
	free(temp);
	
	temp = strdup(btest);
	trim(temp);
	printf("%19s", temp);
	free(temp);
	
	temp = strdup(btest1);
	trim(temp);
	printf("%19s\n", temp);
	free(temp);
}

void _dbError_DBC(char* lp, HDBC hdbc) {
	SQLCHAR  SqlState[6], Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER NativeError;
	SQLSMALLINT i, MsgLen;
	SQLRETURN  rc;
	
	i = 1;
	
	while ((rc = SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, i, SqlState, &NativeError,
		Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) {
		
		cout << "Error in lbQuery: (" << lp << ") " <<
			SqlState << ": " << (int) NativeError << " - " << Msg << endl;
		i++;
	}
}

void _dbError_ENV(char* lp, HENV henv) {
	SQLCHAR  SqlState[6], Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER NativeError;
	SQLSMALLINT i, MsgLen;
	SQLRETURN  rc;
	
	i = 1;
	
	while ((rc = SQLGetDiagRec(SQL_HANDLE_ENV, henv, i, SqlState, &NativeError,
		Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) {
		
		cout << "Error in lbQuery: (" << lp << ") " <<
			SqlState << ": " << (int) NativeError << " - " << Msg << endl;
		i++;
	}
}

void dbError(char* lp, HSTMT hstmt)
{
	SQLCHAR  SqlState[6], Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER NativeError;
	SQLSMALLINT i, MsgLen;
	SQLRETURN  rc;
	
	i = 1;
	
	printf("Any error happens in %s\n", lp);
	
	while ((rc = SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, i, SqlState, &NativeError,
		Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) {
		cout << "Error in lbQuery: (" << lp << ") " <<
			SqlState << ": " << (int) NativeError << " - " << Msg << endl;
		i++;
	}
}

// This statement crashes inside SQLExecDirect(...)
UCHAR buf5[] = "select id, test, btest, btest1 from regressiontest";
	

void setQuery(unsigned char* q, HSTMT &hstmt) {
	RETCODE retcode;
	long cbBufferLength = 0;

	if (hstmt != NULL) {
		retcode = SQLFreeStmt (hstmt, SQL_CLOSE);
	}

	retcode = SQLExecDirect(hstmt, q, SQL_NTS);
	
	if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);

	retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, id, sizeof(id), &cbBufferLength);
	if (retcode != SQL_SUCCESS) dbError("SQLBindCol()", hstmt);
	retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, test, sizeof(test), &cbBufferLength);
	if (retcode != SQL_SUCCESS) dbError("SQLBindCol()", hstmt);
	retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, btest, sizeof(btest), &cbBufferLength);
	if (retcode != SQL_SUCCESS) dbError("SQLBindCol()", hstmt);
	retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, btest1, sizeof(btest1), &cbBufferLength);
	if (retcode != SQL_SUCCESS) dbError("SQLBindCol()", hstmt);
}

int main(void)
{
	HENV        henv = NULL;                            // Env Handle from SQLAllocEnv()
	HSTMT       hstmt = NULL;                           // Statement handle
	HSTMT       hstmt_select = NULL;                    // Statement handle
	UCHAR       *DSN = (unsigned char*) "lbDMF";		// Data Source Name buffer
	UCHAR       user[64] = "dba";                       // UserID buffer 
	UCHAR       passwd[64] = "trainres";                // Password buffer
	
	
	char *buf1;
	
	cout << "Select 1 for Sybase\nSelect 2 for PostgreSQL\nSelect 3 for MS SQL: ";
	
	int select;
	
	cin >> select;
	
	cout << "You have selected " << select << endl;
	
	switch (select) {
	case 1:
		DSN = (unsigned char*) strdup("lbDMF-sybase");
		buf1 = strdup("create table regressiontest (\n"
			"id INTEGER NOT NULL DEFAULT AUTOINCREMENT,\n"
			"test char(100) DEFAULT 'Nothing',\n"
			"btest BIT DEFAULT 0,\n"
			"btest1 BIT DEFAULT 0,\n"
			"PRIMARY KEY (id)\n"
			")");
		break;
	case 2:
		buf1 = strdup("create table regressiontest ("
			"id serial,"
			"test char(100) DEFAULT 'Nothing',"
			"btest bool DEFAULT false,"
			"btest1 bool DEFAULT false,"
			"CONSTRAINT regressiontest_pkey PRIMARY KEY (id)"
			")");
		break;
	case 3:
		DSN = (unsigned char*) strdup("trainresMSSQL");
		buf1 = strdup("create table regressiontest ("
			"id INTEGER IDENTITY,"
			"test char(100) DEFAULT 'Nothing',"
			"btest BIT DEFAULT 0,"
			"btest1 BIT DEFAULT 0,"
			"CONSTRAINT regressiontest_pkey PRIMARY KEY (id)"
			")");
		break;
	}
	
	
	long cbBufferLength = 0;
	
	RETCODE retcode;
	
	retcode = SQLAllocEnv (&henv);
	
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, 0);
	if (retcode != SQL_SUCCESS) _dbError_ENV("SQLSetConnectAttr()", henv);
	
	retcode = SQLAllocConnect (henv, &hdbc);
	
	retcode = SQLSetConnectAttr(hdbc, SQL_ATTR_ODBC_CURSORS, SQL_CUR_USE_IF_NEEDED, 0); /*(void*)SQL_CUR_USE_ODBC*/
	//retcode = SQLSetConnectAttr(hdbc, SQL_ATTR_ODBC_CURSORS, (void*) SQL_CUR_USE_ODBC, 0); 
	if (retcode != SQL_SUCCESS) _dbError_DBC("SQLSetConnectAttr()", hdbc);
	
	retcode = SQLConnect(hdbc, DSN, SQL_NTS, user, SQL_NTS, passwd, SQL_NTS);
	
	if (retcode != SQL_SUCCESS) {
		printf("Error while connecting to database!\n");
		return 0;
	}
	
	retcode = SQLSetConnectOption(hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);

	retcode = SQLAllocStmt (hdbc, &hstmt);

	retcode = SQLAllocStmt (hdbc, &hstmt_select);
	
	printf("Set select statement options...\n");
	
	retcode = SQLSetStmtOption(hstmt_select, SQL_ATTR_CONCURRENCY, SQL_CONCUR_ROWVER);
	if (retcode != SQL_SUCCESS) dbError("SQLSetStmtOption()", hstmt_select);
	
	retcode = SQLSetStmtOption(hstmt_select, SQL_CURSOR_TYPE, SQL_CURSOR_KEYSET_DRIVEN);
	if (retcode != SQL_SUCCESS) dbError("SQLSetStmtOption()", hstmt_select);
	
	UCHAR buf6[] = "drop table regressiontest";
	
	retcode = SQLExecDirect(hstmt, buf6, sizeof(buf6));
	if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);
	
	
	UCHAR *buf2 = ((select == 3) || (select == 1)) ? (UCHAR*) "insert into regressiontest (test) values('Nix')" : (UCHAR*) "insert into regressiontest (test) values('Nix')";
	UCHAR *buf3 = ((select == 3) || (select == 1)) ? (UCHAR*) "insert into regressiontest (btest) values(1)" : (UCHAR*) "insert into regressiontest (btest) values(true)";
	UCHAR *buf4 = ((select == 3) || (select == 1)) ? (UCHAR*) "insert into regressiontest (btest1) values(1)" : (UCHAR*) "insert into regressiontest (btest1) values(true)";
	UCHAR *buf12 = ((select == 3) || (select == 1)) ? (UCHAR*) "insert into regressiontest (test) values('Nix')" : (UCHAR*) "insert into regressiontest (test) values('Nix')";
	UCHAR *buf13 = ((select == 3) || (select == 1)) ? (UCHAR*) "insert into regressiontest (btest) values(1)" : (UCHAR*) "insert into regressiontest (btest) values(true)";
	UCHAR *buf14 = ((select == 3) || (select == 1)) ? (UCHAR*) "insert into regressiontest (btest1) values(1)" : (UCHAR*) "insert into regressiontest (btest1) values(true)";
	
	
	//if ((select == 2) || (select == 3)) {
	retcode = SQLExecDirect(hstmt, (unsigned char*) buf1, SQL_NTS);
	if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);
	//}
	
	retcode = SQLExecDirect(hstmt, buf2, SQL_NTS);
	if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);
	retcode = SQLExecDirect(hstmt, buf3, SQL_NTS);
	if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);
	retcode = SQLExecDirect(hstmt, buf4, SQL_NTS);
	if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);
	
	retcode = SQLExecDirect(hstmt, buf12, SQL_NTS);
	if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);
	retcode = SQLExecDirect(hstmt, buf13, SQL_NTS);
	if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);
	retcode = SQLExecDirect(hstmt, buf14, SQL_NTS);
	if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);

	retcode = SQLFreeStmt (hstmt, SQL_DROP);

	setQuery(buf5, hstmt_select);

	SWORD count = 0;
	retcode = SQLNumResultCols(hstmt_select, &count);
	
	//if (count == 0) count = 4;
	
	if (retcode != SQL_SUCCESS) dbError("SQLNumResultCols()", hstmt_select);
	
	printf("Number of columns: %d.\n", count);
	
	// Force an error
	char* columnName = getColumnName(hstmt_select, 0);
	
	printf("Have got column name '%s' for column 0\n", columnName);
	
	PrintData(hstmt_select, count, false);
	
	first( hstmt_select);
	next(  hstmt_select);
	
	remove(hstmt_select, id);
	//update(hstmt_select);
	
	next(  hstmt_select);
	
	remove(hstmt_select, id);
	//update(hstmt_select);
	
	// Close Cursor
	setQuery(buf5, hstmt_select);
	
	//refresh(hstmt_select);
	
	absolute(hstmt_select, 1);
	
	PrintData(hstmt_select, count, false, false);
	
	first( hstmt_select);
	
	printf("Test changing data...\n");
	
	sprintf(btest, "%d", 1); 
	sprintf(btest1, "%d", 1); 
	update(hstmt_select);
	
	PrintData(hstmt_select, count, false);
	
	PrintData(hstmt_select, count, true);
	
	// Free the allocated statement handles
	retcode = SQLFreeStmt (hstmt_select, SQL_DROP);
	
	// Free the allocated connection handle
	retcode = SQLFreeConnect (hdbc);
	
	// Free the allocated ODBC environment handle
	retcode = SQLFreeEnv (henv);
	
	printf("Ready.\n");
	
	switch (select) {
	case 1:
	case 3:
		if (DSN != NULL) free(DSN);
	case 2:
		if (buf1 != NULL) free(buf1);
		break;
	}
	
	getchar();
	
	return 0;
}

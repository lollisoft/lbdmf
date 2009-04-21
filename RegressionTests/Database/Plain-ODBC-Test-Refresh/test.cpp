/*
	This test is aimed to check the SQL_REFRESH functionality of ODBC drivers in different versions.

  
	Test's: These tests currently are for the following databases.
	
	MSSQL:			Not yet adopted.
		
	Sybase:			Not yet adopted.
		  
	PostgreSQL:		Not yet adopted.
					
	MySQL:			Not yet adopted.
  
	TODO:			Adapt to the listed databases.
	
*/
/*
	DMF Distributed Multiplatform Framework (the initial goal of this library)
	This file is part of lbDMF.
	Copyright (C) 2007  Lothar Behrens (lothar.behrens@lollisoft.de)

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
#ifdef WINDOWS
#include <iostream.h>
#endif
#ifdef LINUX 
#include <iostream>
#endif

#include <lbConfigHook.h>

#define _SQL_ROW_DELETED 1000

void dbError(char* lp, HSTMT hstmt);
void PrintFooter(int cols);
void PrintHeader(int cols, HSTMT hstmt);
void PrintCurrent(int cols, HSTMT hstmt);
void _dbError_DBC(char* lp, HDBC hdbc);


void testBlobUpdate(int column, HDBC hdbc, HSTMT hstmt, void* buffer, long buffersize);
void testBlobRead(int column, HSTMT hstmt, void** buffer, long size);

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
		printf("SQLSetPos(SQL_UPDATE) failed.\n");
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
                        COUT << "ERROR: There would also be SQL_NO_DATA." << ENDL; \
                } \
        } \
        if (RowStat[0] == SQL_ROW_ERROR) { \
                printf("ERROR: This row is error.\n"); \
                if (retcode == SQL_NO_DATA) { \
                        COUT << "ERROR: There would also be SQL_NO_DATA." << ENDL; \
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
			printf("SQLDescribeCol() failed.\n");
			strcpy(lbQuery_column_Name, "unknown");
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
	char* temp = strdup(test);
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
		
		COUT << "Error in lbQuery: (" << lp << ") " <<
			SqlState << ": " << (int) NativeError << " - " << Msg << ENDL;
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
		
		COUT << "Error in lbQuery: (" << lp << ") " <<
			SqlState << ": " << (int) NativeError << " - " << Msg << ENDL;
		i++;
	}
}

void dbError(char* lp, HSTMT hstmt)
{
	SQLCHAR  SqlState[6], Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER NativeError;
	SQLSMALLINT i, MsgLen;
	SQLRETURN  rc;
	
#ifndef WINDOWS	
	printf("%s\n", lp);
	return;
#endif	
	i = 1;
	
	printf("Any error happens in %s\n", lp);
	
	while ((rc = SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, i, SqlState, &NativeError,
		Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) {
		COUT << "Error in lbQuery: (" << lp << ") " <<
			SqlState << ": " << (int) NativeError << " - " << Msg << ENDL;
		i++;
	}
}

// This statement crashes inside SQLExecDirect(...)
UCHAR buf5[] = "select test, btest, btest1 from regressiontest";

void bind(HSTMT hstmt) {
	RETCODE retcode;
	long cbBufferLength = 0;
	retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, test, sizeof(test), &cbBufferLength);
	if (retcode != SQL_SUCCESS) dbError("SQLBindCol()", hstmt);
	retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, btest, sizeof(btest), &cbBufferLength);
	if (retcode != SQL_SUCCESS) dbError("SQLBindCol()", hstmt);
	retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, btest1, sizeof(btest1), &cbBufferLength);
	if (retcode != SQL_SUCCESS) dbError("SQLBindCol()", hstmt);
}

void unbind(HSTMT hstmt) {
	RETCODE retcode;
	long cbBufferLength = 0;
	retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, NULL, sizeof(test), &cbBufferLength);
	if (retcode != SQL_SUCCESS) dbError("SQLBindCol()", hstmt);
	retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, NULL, sizeof(btest), &cbBufferLength);
	if (retcode != SQL_SUCCESS) dbError("SQLBindCol()", hstmt);
	retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, NULL, sizeof(btest1), &cbBufferLength);
	if (retcode != SQL_SUCCESS) dbError("SQLBindCol()", hstmt);
}

void setQuery(unsigned char* q, HSTMT &hstmt) {
	RETCODE retcode;
	long cbBufferLength = 0;

	if (hstmt != NULL) {
		retcode = SQLFreeStmt (hstmt, SQL_CLOSE);
	}

	retcode = SQLExecDirect(hstmt, q, SQL_NTS);
	
	if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);

	bind(hstmt);
}

#define BLOB_SIZE 100

int main(void)
{
	HENV        henv = NULL;                            // Env Handle from SQLAllocEnv()
	HSTMT       hstmt = NULL;                           // Statement handle
	HSTMT       hstmt_select = NULL;                    // Statement handle
	UCHAR       *DSN = (unsigned char*) "lbDMF";		// Data Source Name buffer
	UCHAR       user[64] = "dba";                       // UserID buffer 
	UCHAR       passwd[64] = "trainres";                // Password buffer
	
	int			TargetDatabase = 0;
	
	char *buf1;
	
	COUT << "Select 1 for Sybase\nSelect 2 for PostgreSQL\nSelect 3 for MS SQL: ";
	
	int select;
	
	CIN >> select;
	
	COUT << "You have selected " << select << ENDL;
	
	switch (select) {
	case 1:
		DSN = (unsigned char*) strdup("trainres");
		buf1 = strdup("create table regressiontest (\n"
			"id INTEGER NOT NULL DEFAULT AUTOINCREMENT,\n"
			"test char(100) DEFAULT 'Nothing',\n"
			"btest BIT DEFAULT 0,\n"
			"btest1 BIT DEFAULT 0,\n"
			"PRIMARY KEY (id)\n"
			")");
		TargetDatabase = 1;
		break;
	case 2:
		buf1 = strdup("create table regressiontest ("
			"id serial,"
			"test char(100) DEFAULT 'Nothing',"
			"btest bool DEFAULT false,"
			"btest1 bool DEFAULT false,"
			"blobdata bytea,"
			"CONSTRAINT regressiontest_pkey PRIMARY KEY (id)"
			")");
		TargetDatabase = 2;
		break;
	case 3:
		DSN = (unsigned char*) strdup("trainresMSSQL");
		buf1 = strdup("create table regressiontest ("
			"id INTEGER IDENTITY,"
			"test char(100) DEFAULT 'Nothing',"
			"btest BIT DEFAULT 0,"
			"btest1 BIT DEFAULT 0,"
			"blobdata text,"
			"CONSTRAINT regressiontest_pkey PRIMARY KEY (id)"
			")");
		TargetDatabase = 3;
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
	
	retcode = SQLSetConnectOption(hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);
	retcode = SQLAllocStmt (hdbc, &hstmt);
	retcode = SQLAllocStmt (hdbc, &hstmt_select);
	
	if (TargetDatabase != 1) {
        printf("Set select statement options...\n");
	
        retcode = SQLSetStmtOption(hstmt_select, SQL_ATTR_CONCURRENCY, SQL_CONCUR_ROWVER);
        if (retcode != SQL_SUCCESS) printf("SQLSetStmtOption()");
	
        retcode = SQLSetStmtOption(hstmt_select, SQL_CURSOR_TYPE, SQL_CURSOR_KEYSET_DRIVEN);
        if (retcode != SQL_SUCCESS) printf("SQLSetStmtOption()");
	}
	
	UCHAR buf6[] = "drop table regressiontest";
	
	retcode = SQLExecDirect(hstmt, buf6, sizeof(buf6));
	if (retcode != SQL_SUCCESS) printf("SQLExecDirect() failed.\n");
	
	
	UCHAR *buf2 = ((select == 3) || (select == 1)) ? (UCHAR*) "insert into regressiontest (test) values('Nix')" : (UCHAR*) "insert into regressiontest (test) values('Nix')";
	UCHAR *buf3 = ((select == 3) || (select == 1)) ? (UCHAR*) "insert into regressiontest (btest) values(1)" : (UCHAR*) "insert into regressiontest (btest) values(true)";
	UCHAR *buf4 = ((select == 3) || (select == 1)) ? (UCHAR*) "insert into regressiontest (btest1) values(1)" : (UCHAR*) "insert into regressiontest (btest1) values(true)";
	UCHAR *buf12 = ((select == 3) || (select == 1)) ? (UCHAR*) "insert into regressiontest (test) values('Nix')" : (UCHAR*) "insert into regressiontest (test) values('Nix')";
	UCHAR *buf13 = ((select == 3) || (select == 1)) ? (UCHAR*) "insert into regressiontest (btest) values(1)" : (UCHAR*) "insert into regressiontest (btest) values(true)";
	UCHAR *buf14 = ((select == 3) || (select == 1)) ? (UCHAR*) "insert into regressiontest (btest1) values(1)" : (UCHAR*) "insert into regressiontest (btest1) values(true)";
	
	
	//if ((select == 2) || (select == 3)) {
	retcode = SQLExecDirect(hstmt, (unsigned char*) buf1, SQL_NTS);
	if (retcode != SQL_SUCCESS) printf("SQLExecDirect() failed.\n");
	//}
	
	retcode = SQLExecDirect(hstmt, buf2, SQL_NTS);
	if (retcode != SQL_SUCCESS) printf("SQLExecDirect() failed.\n");
	retcode = SQLExecDirect(hstmt, buf3, SQL_NTS);
	if (retcode != SQL_SUCCESS) printf("SQLExecDirect() failed.\n");
	retcode = SQLExecDirect(hstmt, buf4, SQL_NTS);
	if (retcode != SQL_SUCCESS) printf("SQLExecDirect() failed.\n");
	
	retcode = SQLExecDirect(hstmt, buf12, SQL_NTS);
	if (retcode != SQL_SUCCESS) printf("SQLExecDirect() failed.\n");
	retcode = SQLExecDirect(hstmt, buf13, SQL_NTS);
	if (retcode != SQL_SUCCESS) printf("SQLExecDirect() failed.\n");
	retcode = SQLExecDirect(hstmt, buf14, SQL_NTS);
	if (retcode != SQL_SUCCESS) printf("SQLExecDirect() failed.\n");

	retcode = SQLFreeStmt (hstmt, SQL_DROP);

    printf("Set database query.\n");

	setQuery(buf5, hstmt_select);

	SWORD count = 0;
	retcode = SQLNumResultCols(hstmt_select, &count);

	if (count == 0) count = 3;
	
	if (retcode != SQL_SUCCESS) dbError("SQLNumResultCols()", hstmt_select);
	
	printf("Number of columns: %d.\n", count);
	
	// Force an error
	char* columnName = getColumnName(hstmt_select, 0);
	
	printf("Have got column name '%s' for column 0\n", columnName);
	
	PrintData(hstmt_select, count, false);
	
	first(hstmt_select);

	printf("Do a refresh.\n");
	unbind(hstmt_select);
	refresh(hstmt_select);
	bind(hstmt_select);
	first(hstmt_select);
	PrintData(hstmt_select, count, false);

	printf("Done a refresh.\n");

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

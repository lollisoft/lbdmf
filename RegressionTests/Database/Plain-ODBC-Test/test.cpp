#ifdef WINDOWS
#include <windows.h>
#endif

#include <sqlext.h>
#include <stdio.h>
#include <iostream.h>


void dbError(char* lp, HSTMT hstmt);
void PrintFooter(int cols);
void PrintHeader(int cols, HSTMT hstmt);
void PrintCurrent(int cols, HSTMT hstmt);

char id[10] = "";
char test[200] = "";
char btest[100] = "";
char btest1[100] = "";


void trim(char* stringdata) {
        while (stringdata[strlen(stringdata)-1] == ' ')
                stringdata[strlen(stringdata)-1] = 0;
}

void remove(HSTMT hstmt) {
        RETCODE retcode = SQLSetPos(hstmt, 1, SQL_DELETE, SQL_LOCK_NO_CHANGE);

        if (retcode != SQL_SUCCESS)
        {
                printf("ERROR: Removing data failed.\n");
                dbError("SQLSetPos(SQL_DELETE)", hstmt);
        }
}

void update(HSTMT hstmt) {
        RETCODE retcode = SQLSetPos(hstmt, 1, SQL_UPDATE, SQL_LOCK_NO_CHANGE);

        if (retcode != SQL_SUCCESS)
        {
                        dbError("SQLSetPos(SQL_UPDATE)", hstmt);
        }
}

RETCODE last(HSTMT hstmt) {
        UWORD   RowStat[20];
        UDWORD  RowsFetched = 0;

        RETCODE retcode = SQLExtendedFetch(hstmt, SQL_FETCH_LAST, 0, &RowsFetched, &RowStat[0]);

        if (retcode != SQL_SUCCESS) dbError("SQLExtendedFetch()", hstmt);

        return retcode;
}

RETCODE first(HSTMT hstmt) {
        UWORD   RowStat[20];
        UDWORD  RowsFetched = 0;

        RETCODE retcode = SQLExtendedFetch(hstmt, SQL_FETCH_FIRST, 0, &RowsFetched, &RowStat[0]);

        if (retcode != SQL_SUCCESS) dbError("SQLExtendedFetch()", hstmt);

        return retcode;
}

RETCODE next(HSTMT hstmt) {
        UWORD   RowStat[20];
        UDWORD  RowsFetched = 0;

        RETCODE retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, &RowStat[0]);

        if (retcode != SQL_SUCCESS) dbError("SQLExtendedFetch()", hstmt);

        return retcode;
}

RETCODE previous(HSTMT hstmt) {
        UWORD   RowStat[20];
        UDWORD  RowsFetched = 0;

        RETCODE retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, &RowStat[0]);

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
                dbError("SQLDescribeCol()", hstmt);
                return "";
        } else {
                strcpy(lbQuery_column_Name, (char*) ColumnName);
                return lbQuery_column_Name;
        }
}


void PrintData(HSTMT hstmt, int cols, bool reverse) {
        PrintHeader(cols, hstmt);
        
        if (reverse == false) {
                if (first(hstmt) == SQL_SUCCESS) {
                    PrintCurrent(cols, hstmt);
                    
                    while (next(hstmt) == SQL_SUCCESS) {
                            PrintCurrent(cols, hstmt);
                    }      
                }

        } else {
                if (last(hstmt) == SQL_SUCCESS) {
                    PrintCurrent(cols, hstmt);
                            
                    while (previous(hstmt) == SQL_SUCCESS) {
                            PrintCurrent(cols, hstmt);
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


void dbError(char* lp, HSTMT hstmt)
{
        SQLCHAR  SqlState[6], Msg[SQL_MAX_MESSAGE_LENGTH];
        SQLINTEGER NativeError;
        SQLSMALLINT i, MsgLen;
        SQLRETURN  rc;

        i = 1;

        while ((rc = SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, i, SqlState, &NativeError,
              Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) {

                                cout << "Error in lbQuery: (" << lp << ") " <<
                                        SqlState << ": " << (int) NativeError << " - " << Msg << endl;
                i++;
        }
}

int main(void)
{
        HENV        henv = NULL;                            // Env Handle from SQLAllocEnv()
        HDBC        hdbc = NULL;                            // Connection handle
        HSTMT       hstmt = NULL;                           // Statement handle
        HSTMT       hstmt_select = NULL;                           // Statement handle
        UCHAR       DSN[SQL_MAX_DSN_LENGTH] = "lbDMF";      // Data Source Name buffer
        UCHAR       user[64] = "dba";                       // UserID buffer 
        UCHAR       passwd[64] = "trainres";                // Password buffer


        long cbBufferLength = 0;
        
        RETCODE retcode;

        retcode = SQLAllocEnv (&henv);
        retcode = SQLAllocConnect (henv, &hdbc);
        retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, 0);
        retcode = SQLSetConnectAttr(hdbc, SQL_ATTR_ODBC_CURSORS, (void*)SQL_CUR_USE_ODBC/*SQL_CUR_USE_IF_NEEDED*/, 0);
        retcode = SQLConnect(hdbc, DSN, SQL_NTS, user, SQL_NTS, passwd, SQL_NTS);
        retcode = SQLSetConnectOption(hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);
        retcode = SQLAllocStmt (hdbc, &hstmt);
        retcode = SQLAllocStmt (hdbc, &hstmt_select);

        retcode = SQLSetStmtOption(hstmt_select, SQL_ATTR_CONCURRENCY, SQL_CONCUR_ROWVER);
        if (retcode != SQL_SUCCESS) dbError("SQLSetStmtOption()", hstmt);

        retcode = SQLSetStmtOption(hstmt_select, SQL_CURSOR_TYPE, SQL_CURSOR_KEYSET_DRIVEN);
        if (retcode != SQL_SUCCESS) dbError("SQLSetStmtOption()", hstmt);

        UCHAR buf6[] = "drop table regressiontest";
        retcode = SQLExecDirect(hstmt, buf6, sizeof(buf6));
        if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);

        UCHAR buf1[] = "create table regressiontest ("
                       "id serial,"
                       "test char(100) DEFAULT 'Nothing',\n"
                       "btest bool DEFAULT false, "
                       "btest1 bool DEFAULT false"
                       ")";

        UCHAR buf2[] = "insert into regressiontest (test) values('Nix')";
        UCHAR buf3[] = "insert into regressiontest (btest) values(true)";
        UCHAR buf4[] = "insert into regressiontest (btest1) values(true)";
        UCHAR buf12[] = "insert into regressiontest (test) values('Nix')";
        UCHAR buf13[] = "insert into regressiontest (btest) values(true)";
        UCHAR buf14[] = "insert into regressiontest (btest1) values(true)";


        retcode = SQLExecDirect(hstmt, buf1, sizeof(buf1));
        if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);

        retcode = SQLExecDirect(hstmt, buf2, sizeof(buf2));
        if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);
        retcode = SQLExecDirect(hstmt, buf3, sizeof(buf3));
        if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);
        retcode = SQLExecDirect(hstmt, buf4, sizeof(buf4));
        if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);

        retcode = SQLExecDirect(hstmt, buf12, sizeof(buf12));
        if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);
        retcode = SQLExecDirect(hstmt, buf13, sizeof(buf13));
        if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);
        retcode = SQLExecDirect(hstmt, buf14, sizeof(buf14));
        if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);

        // This statement crashes inside SQLExecDirect(...)
        UCHAR buf5[] = "select id, test, btest, btest1 from regressiontest";
        retcode = SQLExecDirect(hstmt_select, buf5, sizeof(buf5));

        if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt_select);

        retcode = SQLBindCol(hstmt_select, 1, SQL_C_CHAR, id, sizeof(id), &cbBufferLength);
        if (retcode != SQL_SUCCESS) dbError("SQLBindCol()", hstmt_select);
        retcode = SQLBindCol(hstmt_select, 2, SQL_C_CHAR, test, sizeof(test), &cbBufferLength);
        if (retcode != SQL_SUCCESS) dbError("SQLBindCol()", hstmt_select);
        retcode = SQLBindCol(hstmt_select, 3, SQL_C_CHAR, btest, sizeof(btest), &cbBufferLength);
        if (retcode != SQL_SUCCESS) dbError("SQLBindCol()", hstmt_select);
        retcode = SQLBindCol(hstmt_select, 4, SQL_C_CHAR, btest1, sizeof(btest1), &cbBufferLength);
        if (retcode != SQL_SUCCESS) dbError("SQLBindCol()", hstmt_select);

        SWORD count = 0;
        retcode = SQLNumResultCols(hstmt_select, &count);

        if (retcode != SQL_SUCCESS) dbError("SQLNumResultCols()", hstmt_select);

        printf("Number of columns: %d.\n", count);

        PrintData(hstmt_select, count, false);

        first( hstmt_select);
        next(  hstmt_select);
        remove(hstmt_select);
        update(hstmt_select);
        next(  hstmt_select);
        remove(hstmt_select);
        update(hstmt_select);
        first( hstmt_select);

        PrintData(hstmt_select, count, false);

        // Free the allocated statement handle
        retcode = SQLFreeStmt (hstmt, SQL_DROP);
        retcode = SQLFreeStmt (hstmt_select, SQL_DROP);

        // Free the allocated connection handle
        retcode = SQLFreeConnect (hdbc);

        // Free the allocated ODBC environment handle
        retcode = SQLFreeEnv (henv);

        printf("Ready.\n");
        getchar();

        return 0;
}

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
            
            40235 D�sseldorf (germany)
*/
/*...e*/

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



class lbQuery;

/*...sclass def lbDBView:0:*/
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
/*...e*/
/*...sclass def lbBoundColumns:0:*/
class lbBoundColumns: public lb_I_ColumnBinding {
public:	
	lbBoundColumns() { ArraySize = 1; }
	virtual ~lbBoundColumns() {}
	
	DECLARE_LB_UNKNOWN()

        lb_I_Container* LB_STDCALL getBoundColumns();
        lbErrCodes      LB_STDCALL setBoundColumns(lb_I_Container* bc);

        /**
         * Set a currently used query to bind their columns.
         */
        lbErrCodes      LB_STDCALL setQuery(lbQuery* q);

	int		LB_STDCALL getMode();

        
        /**
         * Convert the internal data to a char array and return the data.
         */
        lbErrCodes	LB_STDCALL getString(int column, lb_I_String* instance);
        lbErrCodes	LB_STDCALL getString(char* column, lb_I_String* instance);
        lbErrCodes      LB_STDCALL setString(char* column, lb_I_String* instance);

	int LB_STDCALL getArraySize() { return ArraySize; }

private:
	UAP(lb_I_Container, boundColumns, __FILE__, __LINE__)
	UAP(lb_I_Container, ColumnNameMapping, __FILE__, __LINE__)
	UAP(lb_I_Integer, integerKey, __FILE__, __LINE__)
	int ArraySize;
	lbQuery* query;
};
/*...e*/
/*...sclass def lbQuery:0:*/
class lbQuery :
public lb_I_Query
{
public:
	lbQuery(int readonly = 1) { 
		_readonly = readonly; 
		hdbc = 0; 
		hstmt = 0; 
		databound = 0; 
		count = 0; 
		firstfetched = 0;
	}
	
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

	virtual lbErrCodes LB_STDCALL add();
	int LB_STDCALL isAdding() { return mode; }

	/**
	 * Deletes the current entry.
	 */
	virtual lbErrCodes LB_STDCALL remove();
	
	/**
	 * Updates the modified data or stores new data (added via add())
	 */
	virtual lbErrCodes LB_STDCALL update();
        
        /* Navigation */
        virtual lbErrCodes	LB_STDCALL first();
        virtual lbErrCodes	LB_STDCALL next();
        virtual lbErrCodes	LB_STDCALL previous();
        virtual lbErrCodes	LB_STDCALL last();

#ifdef UNBOUND
        virtual char* 		LB_STDCALL getChar(int column);
#endif
#ifndef UNBOUND       
        virtual lb_I_String*	LB_STDCALL getAsString(int column);
	virtual lbErrCodes	LB_STDCALL setString(lb_I_String* columnName, lb_I_String* value);
#endif        
	
	lbErrCodes LB_STDCALL init(HENV henv, HDBC _hdbc, int readonly = 1);
	int LB_STDCALL getColCount();


	/**
	 * Get the statement for creation of bound columns in lb_I_ColumnBinding.
	 * This function is public in class level, not on interface level.
	 */
	HSTMT LB_STDCALL getCurrentStatement() {
		return hstmt;
	}

	int LB_STDCALL isReadonly() {
		return _readonly;
	}

#ifndef UNBOUND
	lb_I_ColumnBinding* getBoundColumns() {
		return boundColumns.getPtr();
	}
#endif

private:
	HENV    henv;
	HDBC    hdbc;
	HSTMT   hstmt;
	RETCODE retcode;
	char    szSql[256];
	int	databound;
	int     firstfetched;
	int	_readonly; // readonly = 1, else = 0
	int	mode;  // insert = 1, select = 0

#ifdef UNBOUND	
	UAP(lb_I_Container, boundColumns, __FILE__, __LINE__)
#endif
#ifndef UNBOUND
	UAP(lb_I_ColumnBinding, boundColumns, __FILE__, __LINE__)
#endif
	int count;
};
/*...e*/
/*...sclass def lbBoundColumn:0:*/
class lbBoundColumn: public lb_I_BoundColumn {
public:	
	lbBoundColumn() {
		bound = 0;
		buffer = NULL;
	}
	virtual ~lbBoundColumn() {
		if ((bound != 0) && (buffer != NULL)) {
			free(buffer);
			buffer = NULL;
		}
	}
	
	DECLARE_LB_UNKNOWN()


	virtual lb_I_Unknown* LB_STDCALL getData();
	virtual lbErrCodes LB_STDCALL getAsString(lb_I_String* result);
	virtual lbErrCodes LB_STDCALL setFromString(lb_I_String* set, int mode);

	lb_I_String* LB_STDCALL getColumnName();

	lbErrCodes LB_STDCALL bindColumn(lbQuery* q, int column);
	
protected:

	virtual lbErrCodes  LB_STDCALL setData(int b, SQLSMALLINT dt, void* bu) {
		bound = b;
		_DataType = dt;
		buffer = bu;
		return ERR_NONE;
	}

	// I call my self to leave my ownership
	virtual lbErrCodes LB_STDCALL leaveOwnership(lb_I_BoundColumn* oldOwner, lb_I_BoundColumn* newOwner);

	int		bound;
	SQLSMALLINT     _DataType;
	void*		buffer;
	int		buffersize;
	UAP(lb_I_String, colName, __FILE__, __LINE__)
};
/*...e*/



/*...sclass lbDBView:0:*/

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
/*...sclass lbBoundColumns:0:*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbBoundColumns)
        ADD_INTERFACE(lb_I_ColumnBinding)
END_IMPLEMENT_LB_UNKNOWN()

// lbBoundColumns does not need a functor, because lbQuery acts as a factory

lbErrCodes LB_STDCALL lbBoundColumns::setData(lb_I_Unknown* uk) {
        _CL_LOG << "lbBoundColumns::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

lb_I_Container* LB_STDCALL lbBoundColumns::getBoundColumns() {
	return NULL;
}

lbErrCodes      LB_STDCALL lbBoundColumns::setBoundColumns(lb_I_Container* bc) {
	return ERR_NONE;
}

/*...slbErrCodes      LB_STDCALL lbBoundColumns\58\\58\setQuery\40\lbQuery\42\ q\41\:0:*/
lbErrCodes      LB_STDCALL lbBoundColumns::setQuery(lbQuery* q) {
	HSTMT hstmt = q->getCurrentStatement();
	query = q;

	const int ArraySize = 1;
	SQLUSMALLINT RowStatusArray[ArraySize];

	// Set the array size to one.
	SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_ARRAY_SIZE, (SQLPOINTER) ArraySize, 0);
	
	// Why this construct ??
	SQLINTEGER csrType = SQL_CURSOR_KEYSET_DRIVEN;
	
	SQLSetStmtAttr(hstmt, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER) csrType, 0);
	SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_BIND_TYPE, SQL_BIND_BY_COLUMN, 0);
	SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_STATUS_PTR, RowStatusArray, 0);

	/*
	 * Get the number of columns for this query.
	 */
	SQLSMALLINT num = 0;	
	SQLRETURN sqlreturn = SQLNumResultCols(hstmt, &num);
	
/*...sdocs:0:*/
#ifdef bla

MSDN:

	Many applications, especially ones that only display data, only require the metadata returned by 
	SQLDescribeCol. 
	For these applications, it is faster to use SQLDescribeCol than SQLColAttribute because the information is 
	returned in a single call. 


Therefore I need an indicator, set by the user of this library to know, which one I should use.

#endif
/*...e*/

	// Request bound columns holder and key helper
	// Warning: This function should only called once yet.
	REQUEST(manager.getPtr(), lb_I_Container, boundColumns)
	REQUEST(manager.getPtr(), lb_I_Integer, integerKey)
	

	// For each column create a bound column instance.
	// The instance will bind the column.
	for (int i = 1; i <= num; i++) {

		// Create the instance ...
		
		lbBoundColumn* bc = new lbBoundColumn();
		
		bc->setModuleManager(*&manager, __FILE__, __LINE__);
		printf("Bind column %d.\n", i);
		bc->bindColumn(q, i);
		
		integerKey->setData(i);
		
		UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)

		bc->queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__);
		integerKey->queryInterface("lb_I_KeyBase", (void**) &key, __FILE__, __LINE__);		
		
		boundColumns->insert(&uk, &key);
		
/*...sGet the column name for this column and add an index to it\39\s column id\46\:16:*/

		if (ColumnNameMapping == NULL) {
			// Create the index mapping instnce
			
			REQUEST(manager.getPtr(), lb_I_Container, ColumnNameMapping)
		}
		
		UAP(lb_I_KeyBase, skey, __FILE__, __LINE__)
		UAP(lb_I_String, string, __FILE__, __LINE__)

		string = bc->getColumnName();
		string->queryInterface("lb_I_KeyBase", (void**) &skey, __FILE__, __LINE__);
		
		UAP(lb_I_Unknown, ivalue, __FILE__, __LINE__)
		
		integerKey->queryInterface("lb_I_Unknown", (void**) &ivalue, __FILE__, __LINE__);
		
		ColumnNameMapping->insert(&ivalue, &skey);
/*...e*/
		
	}

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes      LB_STDCALL lbBoundColumns\58\\58\getString\40\int column\44\ lb_I_String\42\ instance\41\:0:*/
lbErrCodes	LB_STDCALL lbBoundColumns::getString(int column, lb_I_String* instance) {
	lbErrCodes err = ERR_NONE;

	if (boundColumns != NULL) {
		integerKey->setData(column);
		
		UAP(lb_I_Unknown, ukdata, __FILE__, __LINE__)
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
		
		QI(integerKey, lb_I_KeyBase, key, __FILE__, __LINE__)
		ukdata = boundColumns->getElement(&key);

		if (ukdata == NULL) printf("NULL pointer!\n");

		UAP(lb_I_BoundColumn, bc, __FILE__, __LINE__)
		lbErrCodes err = ukdata->queryInterface("lb_I_BoundColumn", (void**) &bc, __FILE__, __LINE__);

		bc->getAsString(instance);
	}

	return ERR_NONE;
}
/*...e*/
lbErrCodes	LB_STDCALL lbBoundColumns::getString(char* column, lb_I_String* instance) {
	return ERR_NONE;
}
lbErrCodes      LB_STDCALL lbBoundColumns::setString(char* column, lb_I_String* instance) {
	lbErrCodes err = ERR_NONE;
printf("lbBoundColumns::setString(char* column, lb_I_String* instance) called\n");	
	UAP(lb_I_Unknown, ukdata, __FILE__, __LINE__)
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, Column)
	
	Column->setData(column);
	
	QI(Column, lb_I_KeyBase, key, __FILE__, __LINE__)
	ukdata = ColumnNameMapping->getElement(&key);

	UAP(lb_I_KeyBase, index, __FILE__, __LINE__)
	QI(ukdata, lb_I_KeyBase, index, __FILE__, __LINE__)

	UAP(lb_I_Unknown, uk_bc, __FILE__, __LINE__)
	uk_bc = boundColumns->getElement(&index);
	
	UAP(lb_I_BoundColumn, bc, __FILE__, __LINE__)
	QI(uk_bc, lb_I_BoundColumn, bc, __FILE__, __LINE__)

	// Adding or updating ? - Decided inside
	bc->setFromString(instance, getMode());

	return ERR_NONE;
}

int		LB_STDCALL lbBoundColumns::getMode() {
	return query->isAdding();
}
/*...e*/
/*...sclass lbQuery:0:*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbQuery)
        ADD_INTERFACE(lb_I_Query)
END_IMPLEMENT_LB_UNKNOWN()

UAP(lb_I_Integer, key, __FILE__, __LINE__)

/*...sto be implemented:0:*/
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
/*...e*/

/*...slbErrCodes LB_STDCALL lbQuery\58\\58\init\40\HENV henv\44\ HDBC _hdbc\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::init(HENV henv, HDBC _hdbc, int readonly) {
	hdbc = _hdbc;

	retcode = SQLAllocStmt(hdbc, &hstmt); /* Statement handle */

	if (retcode != SQL_SUCCESS)
	{
	        dbError( "SQLAllocStmt()",henv,hdbc,hstmt);
	        _LOG << "lbDatabase::getQuery() failed due to statement allocation." LOG_
	        SQLFreeEnv(henv);
        	return ERR_DB_ALLOCSTATEMENT;
	}


	if (readonly == 0) {
	// Compare values before updating
		retcode = SQLSetStmtOption(hstmt, SQL_ATTR_CONCURRENCY, SQL_CONCUR_ROWVER);
		_readonly = readonly;
	}

        if (retcode != SQL_SUCCESS)
        {
                dbError( "SQLSetStmtOption()",henv,hdbc,hstmt);
                _LOG << "lbDatabase::getQuery() failed due to setting concurrency settings." LOG_
                SQLFreeEnv(henv);
                return ERR_DB_ALLOCSTATEMENT;
        }

	retcode = SQLSetStmtOption(hstmt, SQL_CURSOR_TYPE, SQL_CURSOR_KEYSET_DRIVEN);

        if (retcode != SQL_SUCCESS)
        {
                dbError( "SQLSetStmtOption()",henv,hdbc,hstmt);
                _LOG << "lbDatabase::getQuery() failed due to setting cursor type." LOG_
                SQLFreeEnv(henv);
                return ERR_DB_ALLOCSTATEMENT;
        }
        
        int size = 1;

	retcode = SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_ARRAY_SIZE, (SQLPOINTER) size, 0);

        if (retcode != SQL_SUCCESS)
        {
                dbError( "SQLSetStmtAttr()",henv,hdbc,hstmt);
                _LOG << "lbDatabase::getQuery() failed due to setting row array size." LOG_
                SQLFreeEnv(henv);
                return ERR_DB_ALLOCSTATEMENT;
        }

// Unneccesary
//	retcode = SQLSetStmtAttr(hstmt, SQL_ATTR_CURSOR_SCROLLABLE, (SQLPOINTER) SQL_SCROLLABLE, 0);




	if (retcode != SQL_SUCCESS) {
		dbError( "SQLSetStmtAttr()",henv,hdbc,hstmt);
		_LOG << "lbDatabase::getQuery() failed due to set statement attributes." LOG_
		//SQLFreeEnv(henv);
		return ERR_DB_ALLOCSTATEMENT;
	}	
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\query\40\char\42\ q\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::query(char* q) {

	lstrcpy(szSql, q);

/*...sdoc:0:*/
#ifdef bla

Using SQLSetPos
	Before an application calls SQLSetPos, it must perform the following sequence of steps: 

	If the application will call SQLSetPos with Operation set to SQL_UPDATE, call SQLBindCol 
	(or SQLSetDescRec) for each column to specify its data type and bind buffers for the columns data and length.


	If the application will call SQLSetPos with Operation set to SQL_DELETE or SQL_UPDATE, 
	call SQLColAttribute to make sure that the columns to be deleted or updated are updatable.


	Call SQLExecDirect, SQLExecute, or a catalog function to create a result set.


	Call SQLFetch or SQLFetchScroll to retrieve the data.
	Note In ODBC 3.x, SQLSetPos can be called before SQLFetch or SQLFetchScroll. For more information, 
	see the Block Cursors, Scrollable Cursors, and Backward Compatibility section in Appendix G, 
	Driver Guidelines for Backward Compatibility.

#endif
/*...e*/

	retcode = SQLExecDirect(hstmt, (unsigned char*) szSql, SQL_NTS);

	if (retcode != SQL_SUCCESS)
        {
        	dbError( "SQLExecDirect()",henv,hdbc,hstmt);
		_LOG << "lbQuery::query(...) failed." LOG_
		return ERR_DB_QUERYFAILED;
        }

	SQLSMALLINT cols;
	
	retcode = SQLNumResultCols(hstmt, &cols);
	
	if (retcode != SQL_SUCCESS)
	{
	        dbError( "SQLNumResultCols()",henv,hdbc,hstmt);
	        _LOG << "lbQuery::query(...) failed." LOG_
	        return ERR_DB_QUERYFAILED;
	} else {
		printf("Have %d columns\n", cols);


		lbBoundColumns* boundcols = new lbBoundColumns();
		boundcols->setModuleManager(*&manager, __FILE__, __LINE__);
		
		boundcols->setQuery(this);
		
		boundColumns = boundcols;
		
		printf("Have %d columns bound\n", cols);
	}

	return ERR_NONE;
}
/*...e*/
/*...sint LB_STDCALL lbQuery\58\\58\getColCount\40\\41\:0:*/
int LB_STDCALL lbQuery::getColCount() {
	SWORD count;
	retcode = SQLNumResultCols(hstmt, &count);
	
	return count;
}
/*...e*/
/*...svirtual char\42\ LB_STDCALL lbQuery\58\\58\getChar\40\int column\41\:0:*/
#ifdef UNBOUND
char* LB_STDCALL lbQuery::getChar(int column) {
	SDWORD cbobjecttyp;
	char   szobjecttyp[SZLEN+100];
	lbErrCodes err = ERR_NONE;

	if (databound == 0) {
/*...sPrebind columns:16:*/
		// Prebound data from row
		
		if (boundColumns == NULL) {
			REQUEST(manager.getPtr(), lb_I_Container, boundColumns)
		} else {
			_LOG << "Delete bound collumns" LOG_
			boundColumns->deleteAll();
		}
		
		if (boundColumns == NULL) _LOG << "Error: Unable to prebind columns!" LOG_
		if (firstfetched != 1) {
			firstfetched = 1; 
			count = getColCount();
		}
			
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, key)
		UAP_REQUEST(manager.getPtr(), lb_I_String, string)
		
		for (int i = 1; i <= count; i++) {
			retcode = SQLGetData(hstmt, i, SQL_C_CHAR, szobjecttyp, SZLEN+50, &cbobjecttyp);

			if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
	        		dbError( "SQLGetData()",henv,hdbc,hstmt);
	        		_LOG << "lbQuery::getChar(): Error while get data" LOG_
			} else {
				// Strip trailing blanks
				while (szobjecttyp[strlen(szobjecttyp)-1] == ' ') szobjecttyp[strlen(szobjecttyp)-1] = 0;
				string->setData(szobjecttyp);
				UAP(lb_I_KeyBase, bkey, __FILE__, __LINE__)
				UAP(lb_I_Unknown, ustring, __FILE__, __LINE__)
				QI(key, lb_I_KeyBase, bkey, __FILE__, __LINE__)
				QI(string, lb_I_Unknown, ustring, __FILE__, __LINE__)
				
				key->setData(i);
				
				boundColumns->insert(&ustring, &bkey);
				boundColumns->getElement(&bkey);
			}
		}
		
		databound = 1;
/*...e*/
	}
	
	if (key == NULL) {
		REQUEST(manager.getPtr(), lb_I_Integer, key)
	}
	
	key->setData(column);
	UAP(lb_I_KeyBase, bkey, __FILE__, __LINE__)
	QI(key, lb_I_KeyBase, bkey, __FILE__, __LINE__)
	
	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)

	uk = boundColumns->getElement(&bkey);

	UAP(lb_I_String, string, __FILE__, __LINE__)
	QI(uk, lb_I_String, string, __FILE__, __LINE__)

	return string->getData();
}
#endif
#ifndef UNBOUND
lb_I_String* LB_STDCALL lbQuery::getAsString(int column) {
	UAP_REQUEST(manager.getPtr(), lb_I_String, string)
	
	// Caller get's an owner
	string++;
	boundColumns->getString(column, *&string);
	
	return string.getPtr();;
}
#endif
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\first\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::first() {
        UWORD   RowStat[20];
        UDWORD  RowsFetched = 0;
	
        // Indicate, that data must prebound to a buffer
        databound = 0;

        retcode = SQLExtendedFetch(hstmt, SQL_FETCH_FIRST, 0, &RowsFetched, RowStat);

        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
                _LOG << "lbQuery::first(): Error while fetching next row" LOG_
                printf("Error in lbQuery::first()\n");
                dbError( "SQLExtendedFetch()",henv,hdbc,hstmt);
                
                // Unsave !!
                if (retcode == SQL_SUCCESS_WITH_INFO) return ERR_NONE;
                
                return ERR_DB_FETCHFIRST;
        }
        
        if (RowsFetched == 0) return ERR_DB_FETCHFIRST;
        
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\next\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::next() {
	UWORD   RowStat[20];
	UDWORD  RowsFetched = 0;
	
	// Indicate, that data must prebound to a buffer
	databound = 0;

	retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, RowStat);

	if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
		_LOG << "lbQuery::next(): Error while fetching next row" LOG_
		printf("Error in lbQuery::next()\n");
		dbError( "SQLExtendedFetch()",henv,hdbc,hstmt);

		// Unsave !!
		if (retcode == SQL_SUCCESS_WITH_INFO) return ERR_NONE;
		
		return ERR_DB_NODATA;
        }

	if (RowsFetched == 0) return ERR_DB_NODATA;

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\previous\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::previous() {
        UWORD   RowStat[20];
        UDWORD  RowsFetched = 0;

        // Indicate, that data must prebound to a buffer
        databound = 0;

        retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, RowStat);

        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
                _LOG << "lbQuery::previous(): Error while fetching next row" LOG_
                printf("Error in lbQuery::previous()\n");
                dbError( "SQLExtendedFetch()",henv,hdbc,hstmt);

		// Unsave !!
		if (retcode == SQL_SUCCESS_WITH_INFO) return ERR_NONE;
		
                return ERR_DB_NODATA;
        }
        
	if (RowsFetched == 0) return ERR_DB_NODATA;
        
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\last\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::last() {
        UWORD   RowStat[20];
        UDWORD  RowsFetched = 0;

        // Indicate, that data must prebound to a buffer
        databound = 0;

        retcode = SQLExtendedFetch(hstmt, SQL_FETCH_LAST, 0, &RowsFetched, RowStat);

        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
                _LOG << "lbQuery::last(): Error while fetching next row" LOG_
                printf("Error in lbQuery::last()\n");

                dbError( "SQLExtendedFetch()",henv,hdbc,hstmt);

		// Unsave !!
		if (retcode == SQL_SUCCESS_WITH_INFO) return ERR_NONE;
		
                return ERR_DB_FETCHLAST;
        }
        
        if (RowsFetched == 0) return ERR_DB_FETCHLAST;
                      
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\setString\40\lb_I_String\42\ columnName\44\ lb_I_String\42\ value\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::setString(lb_I_String* columnName, lb_I_String* value) {

	if (_readonly == 1) return ERR_DB_READONLY;
printf("lbQuery::setString(lb_I_String* columnName, lb_I_String* value)\n");
	if (mode == 1) {
		// Not supported yet
		printf("lbQuery::setString(lb_I_String* columnName, lb_I_String* value) Error: Append data not supported yet\n");
	} else {
		printf("Call boundColumns->setString('%s', '%s')\n", columnName->charrep(), value->charrep());
		boundColumns->setString(columnName->charrep(), value);
	}

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\add\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::add() {

	if (_readonly == 1) return ERR_DB_READONLY;

	mode = 1;

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\remove\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::remove() {

	if (mode == 1) return ERR_DB_STILL_ADDING;

	SQLSetPos(hstmt, 1, SQL_DELETE, SQL_LOCK_NO_CHANGE);

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\update\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::update() {

	if (mode == 1) {
		// Insert the new record
		SQLSetPos(hstmt, 2, SQL_ADD, SQL_LOCK_NO_CHANGE);
	} else {
		// Update the existing record
		printf("Update the existing record\n");
		retcode = SQLSetPos(hstmt, 1, SQL_UPDATE, SQL_LOCK_NO_CHANGE);
		
		if (retcode != SQL_SUCCESS)
		{
		        dbError( "SQLSetPos()",henv,hdbc,hstmt);
		        _LOG << "lbQuery::update(...) failed." LOG_
		        return ERR_DB_UPDATEFAILED;
		}		
	}


	return ERR_NONE;
}
/*...e*/

#ifdef bla
/*...sbla:0:*/

#define POSITIONED_UPDATE 100
#define POSITIONED_DELETE 101

SQLUINTEGER  CustIDArray[10];
SQLCHAR	NameArray[10][51], 
	AddressArray[10][51],
	PhoneArray[10][11];

SQLINTEGER
	CustIDIndArray[10],
	NameLenOrIndArray[10],
	AddressLenOrIndArray[10],
	PhoneLenOrIndArray[10];

SQLUSMALLINT RowStatusArray[10], Action, RowNum;
SQLHSTMT   hstmtCust, hstmtUpdate, hstmtDelete;







// Set the SQL_ATTR_BIND_TYPE statement attribute to use column-wise binding. Declare
// the rowset size with the SQL_ATTR_ROW_ARRAY_SIZE statement attribute. Set the
// SQL_ATTR_ROW_STATUS_PTR statement attribute to point to the row status array.
SQLSetStmtAttr(hstmtCust, SQL_ATTR_ROW_BIND_TYPE, SQL_BIND_BY_COLUMN, 0);
SQLSetStmtAttr(hstmtCust, SQL_ATTR_ROW_ARRAY_SIZE, 10, 0);
SQLSetStmtAttr(hstmtCust, SQL_ATTR_ROW_STATUS_PTR, RowStatusArray, 0);










// Bind arrays to the CustID, Name, Address, and Phone columns.
SQLBindCol(hstmtCust, 1, SQL_C_ULONG, CustIDArray, 0, CustIDIndArray);
SQLBindCol(hstmtCust, 2, SQL_C_CHAR, NameArray, sizeof(NameArray[0]),
     NameLenOrIndArray);
SQLBindCol(hstmtCust, 3, SQL_C_CHAR, AddressArray, sizeof(AddressArray[0]),
     AddressLenOrIndArray);
SQLBindCol(hstmtCust, 4, SQL_C_CHAR, PhoneArray, sizeof(PhoneArray[0]),
     PhoneLenOrIndArray);




// Set the cursor name to Cust.
SQLSetCursorName(hstmtCust, "Cust", SQL_NTS);






// Prepare positioned update and delete statements.
SQLPrepare(hstmtUpdate,
 "UPDATE Customers SET Address = ?, Phone = ? WHERE CURRENT OF Cust",
 SQL_NTS);
SQLPrepare(hstmtDelete, "DELETE FROM Customers WHERE CURRENT OF Cust", SQL_NTS);







// Execute a statement to retrieve rows from the Customers table.
SQLExecDirect(hstmtCust,
 "SELECT CustID, Name, Address, Phone FROM Customers FOR UPDATE OF Address, Phone",
 SQL_NTS);







// Fetch and display the first 10 rows.
SQLFetchScroll(hstmtCust, SQL_FETCH_NEXT, 0);
DisplayData(CustIDArray, CustIDIndArray, NameArray, NameLenOrIndArray, AddressArray,
    AddressLenOrIndArray, PhoneArray, PhoneLenOrIndArray, RowStatusArray);






// Call GetAction to get an action and a row number from the user.
while (GetAction(&Action, &RowNum)) {
 switch (Action) {

  case SQL_FETCH_NEXT:
  case SQL_FETCH_PRIOR:
  case SQL_FETCH_FIRST:
  case SQL_FETCH_LAST:
  case SQL_FETCH_ABSOLUTE:
  case SQL_FETCH_RELATIVE:
   // Fetch and display the requested data.
   SQLFetchScroll(hstmtCust, Action, RowNum);
   DisplayData(CustIDArray, CustIDIndArray, NameArray, NameLenOrIndArray,
       AddressArray, AddressLenOrIndArray, PhoneArray,
       PhoneLenOrIndArray, RowStatusArray);
   break;

  case POSITIONED_UPDATE:
   // Get the new data and place it in the rowset buffers.
   GetNewData(AddressArray[RowNum - 1], &AddressLenOrIndArray[RowNum - 1],
        PhoneArray[RowNum - 1], &PhoneLenOrIndArray[RowNum - 1]);

   // Bind the elements of the arrays at position RowNum-1 to the parameters
   // of the positioned update statement.
   SQLBindParameter(hstmtUpdate, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,
          50, 0, AddressArray[RowNum - 1], sizeof(AddressArray[0]),
          &AddressLenOrIndArray[RowNum - 1]);
   SQLBindParameter(hstmtUpdate, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,
          10, 0, PhoneArray[RowNum - 1], sizeof(PhoneArray[0]),
          &PhoneLenOrIndArray[RowNum - 1]);

   // Position the rowset cursor. The rowset is 1-based.
   SQLSetPos(hstmtCust, RowNum, SQL_POSITION, SQL_LOCK_NO_CHANGE);

   // Execute the positioned update statement to update the row.
   SQLExecute(hstmtUpdate);
   break;

  case POSITIONED_DELETE:
   // Position the rowset cursor. The rowset is 1-based.
   SQLSetPos(hstmtCust, RowNum, SQL_POSITION, SQL_LOCK_NO_CHANGE);

   // Execute the positioned delete statement to delete the row.
   SQLExecute(hstmtDelete);
   break;
 }
}

// Close the cursor.
SQLCloseCursor(hstmtCust);



/*...e*/
#endif
/*...e*/
/*...sclass lbBoundColumn:0:*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbBoundColumn)
        ADD_INTERFACE(lb_I_BoundColumn)
END_IMPLEMENT_LB_UNKNOWN()

/*...slbErrCodes LB_STDCALL lbBoundColumn\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbBoundColumn::setData(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_NONE;
        
        UAP(lb_I_BoundColumn, column, __FILE__, __LINE__)
        
        QI(uk, lb_I_BoundColumn, column, __FILE__, __LINE__)
        
        /**
         * I cannot use normal use of setData, because the internal pointers would
         * be copied to others. The ODBC bound column instead uses the old pointer.
         *
         * There must be a way to carry the pointer from one instance to another,
         * then set the old pointer to NULL (NO FREE or DELETE).
         * If the pointer would be deleted due to instance cleanup, the ODBC driver
         * would write to an deleted pointer.
         */


	leaveOwnership(*&column, this);

        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbBoundColumn\58\\58\leaveOwnership\40\lb_I_BoundColumn\42\ oldOwner\44\ lb_I_BoundColumn\42\ newOwner\41\:0:*/
lbErrCodes LB_STDCALL lbBoundColumn::leaveOwnership(lb_I_BoundColumn* oldOwner, lb_I_BoundColumn* newOwner) {

	lbBoundColumn* oO = (lbBoundColumn*) oldOwner;
	lbBoundColumn* nO = (lbBoundColumn*) newOwner;

	nO->setData(oO->bound, oO->_DataType, oO->buffer);
	oO->bound = 0;
	oO->buffer = NULL;

	return ERR_NONE;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbBoundColumn\58\\58\getData\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbBoundColumn::getData() {
	_CL_LOG << "lbBoundColumn::getData(...) not implemented yet" LOG_
	return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbBoundColumn\58\\58\getAsString\40\lb_I_String\42\ result\41\:0:*/
lbErrCodes LB_STDCALL lbBoundColumn::getAsString(lb_I_String* result) {
	
	switch (_DataType) {
	        case SQL_CHAR:
	        case SQL_VARCHAR:
	        case SQL_LONGVARCHAR:
	        	result->setData((char*) buffer);
	        	break;
	        case SQL_INTEGER:
			{
	        		char charrep[100] = "";
	        		sprintf(charrep, "%d", *(long*) buffer);
	        		result->setData(charrep);
			}
	        	break;
	        default:
	        	_CL_LOG << "lbBoundColumn::bindColumn(...) failed: Unknown or not supported datatype" LOG_
	        	break;
	}
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbBoundColumn\58\\58\setFromString\40\lb_I_String\42\ set\44\ int mode\41\:0:*/
lbErrCodes LB_STDCALL lbBoundColumn::setFromString(lb_I_String* set, int mode) {
	_LOG << "lbBoundColumn::setFromString(...) not implemented yet" LOG_

	if (mode == 1) {
		// Not supported yet
		_LOG << "lbBoundColumn::setFromString(...) if (mode == 1) not implemented yet" LOG_
		printf("lbBoundColumn::setFromString(...) if (mode == 1) not implemented yet\n");
	} else {
		// This would overwrite the pointer, not the data !!!
		printf("Copy string '%s' to '%s' with size of %d\n", set->getData(), (char*) buffer, strlen(set->getData()));
		printf("Buffer pointer is at %p\n", buffer);
		char* b = strcpy((char*) buffer, set->getData());
		printf("Result is: '%s', returned is '%s', set is '%s'\n", (char*) buffer, b, set->getData());
	}

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDC
			}ALL lbBoundColumn\58\\58\bindColumn\40\lbQuery\42\ q\44\ int column\41\:0:*/
lbErrCodes LB_STDCALL lbBoundColumn::bindColumn(lbQuery* q, int column) {

	HSTMT hstmt = q->getCurrentStatement();

/*...svars:8:*/
	SQLSMALLINT     ColumnNumber = 0;
	SQLCHAR         ColumnName[1000] = "";
	SQLSMALLINT     BufferLength = 500;
	SQLSMALLINT     NameLength = 0;
	SQLSMALLINT     DataType = 0;
	SQLUINTEGER     ColumnSize = 0;
	SQLSMALLINT     DecimalDigits = 0;
	SQLSMALLINT     Nullable = 0;
/*...e*/

// Assume readonly for now ...

	SQLRETURN ret = SQLDescribeCol( hstmt, column, ColumnName,
	                                BufferLength, &NameLength, &DataType,
	                                &ColumnSize, &DecimalDigits, &Nullable);

	long cbBufferLength;


	if (colName == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, colName)
		
		colName->setData((char*) ColumnName);
	}

	int rows = 2;

	switch (DataType) {
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
/*...sbind a character array:24:*/
			//        100    <      ?
			if (BufferLength < ColumnSize) {
				_CL_LOG << 
				"Warning: BufferLength is smaller than ColumnSize. Data would be truncated." LOG_
			}
			
			buffersize = (ColumnSize == 0) ? (BufferLength+1)*rows : (ColumnSize+1)*rows;
			if (buffersize == 0) printf("Fatal: Calculated bufferzize is zero!!\n");
			
			buffer = malloc(buffersize);
			
			printf("Buffer pointer is at %p\n", buffer);
			
			
			_DataType = DataType;
			bound = 1;
			((char*) buffer)[0] = 0;
			
			ret = SQLBindCol(hstmt, column, DataType, buffer, (ColumnSize == 0) ? 
				(BufferLength+1) : (ColumnSize+1), &cbBufferLength);
			
			if (ret != SQL_SUCCESS) {
				printf("Error while binding a column!\n");
			}
/*...e*/
			break;
/*...slater:16:*/
/*			
		case SQL_WCHAR:
		case SQL_WVARCHAR:
		case SQL_WLONGVARCHAR:
			break;
*/			
/*...e*/
		case SQL_INTEGER:
/*...sbind an integer:24:*/
			//        100    <      ?
			if (BufferLength < ColumnSize) {
				_CL_LOG << "Warning: BufferLength is smaller than ColumnSize. Data would be truncated." LOG_
			}
			
			buffer = malloc((ColumnSize == 0) ? BufferLength+1 : ColumnSize+1);
			_DataType = DataType;
			bound = 1;
			memset(buffer, 0, sizeof(long));

			SQLBindCol(hstmt, column, DataType, buffer, (ColumnSize == 0) ? BufferLength+1 : ColumnSize+1, &cbBufferLength);
			
			if (ret != SQL_SUCCESS) {
			        printf("Error while binding a column!\n");
			}
			
/*...e*/
			break;
		default:
			_CL_LOG << "lbBoundColumn::bindColumn(...) failed: Unknown or not supported datatype" LOG_
			break;
	}
	

	return ERR_NONE;
}
/*...e*/
lb_I_String* LB_STDCALL lbBoundColumn::getColumnName() {
	return colName.getPtr();
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
	virtual lb_I_Query* LB_STDCALL getQuery(int readonly = 1);
	
	
	
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

	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, 0);

	if (retcode != SQL_SUCCESS) {
        	dbError( "SQLSetEnvAttr()",henv,0,0);
        	_LOG << "Database version initializion failed." LOG_
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
        
	retcode = SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 15); /* Set login timeout to 15 seconds. */

        if (retcode != SQL_SUCCESS)
        {
                dbError( "SQLSetConnectOption()",henv,hdbc,0);
                SQLFreeEnv(henv);
                return ERR_DB_CONNECT;
        }

	retcode = SQLSetConnectAttr(hdbc, SQL_ATTR_ODBC_CURSORS, SQL_CUR_USE_IF_NEEDED, 0);

        if (retcode != SQL_SUCCESS)
        {
                dbError( "SQLSetConnectAttr()",henv,hdbc,0);
                SQLFreeEnv(henv);
                return ERR_DB_CONNECT;
        }

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

        retcode = SQLSetConnectOption(hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);

	if (retcode != SQL_SUCCESS)
	{
	        dbError( "SQLSetConnectOption(SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON)",henv,hdbc,0);
	        SQLFreeEnv(henv);
	        return ERR_DB_CONNECT;
	}
        


	return ERR_NONE;
}
/*...e*/
lb_I_Query* LB_STDCALL lbDatabase::getQuery(int readonly) {
	lbQuery* query = new lbQuery;

	if (query->init(henv, hdbc, readonly) != ERR_NONE) return NULL;

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



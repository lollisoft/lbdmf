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

/*...sincludes:0:*/
#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <lbConfigHook.h>

#include <stdio.h>
#ifndef OSX
#ifndef USE_MPATROL
#ifndef MEMTRACK
#include <malloc.h>
#endif
#endif
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif


/*...sLB_DATABASE_DLL scope:0:*/
#define LB_DB_DLL
#include <lbdb-module.h>
/*...e*/

#include <lbDB.h>
/*...e*/

//#define USE_FETCH_SCROLL

extern "C" {
#include <sql.h>
#include <sqlext.h>
}
#define SZLEN 300
#define SZDATELEN 24

#ifndef WINDOWS
#define lstrcpy strcpy
#endif

/*...s\35\define CHECK_ROWSTAT\40\\41\:0:*/
#define CHECK_ROWSTAT() \
	if (RowStat[0] == SQL_ROW_DELETED) { \
		reopen(); \
		if (haveData == false) { \
			_dataFetched = false; \
			return ERR_DB_NODATA; \
		} \
	} \
	if (RowStat[0] == SQL_ROW_NOROW) { \
		if (retcode == SQL_NO_DATA) { \
			_CL_LOG << "ERROR: There would also be SQL_NO_DATA." LOG_ \
		} \
	} \
	if (RowStat[0] == SQL_ROW_ERROR) { \
		if (retcode == SQL_NO_DATA) { \
			_CL_LOG << "ERROR: There would also be SQL_NO_DATA." LOG_ \
		} \
	}

/*...e*/

// Glogal variable for lbQuery::getTableName()
// Would be deleted in lbQuery::~lbQuery()

char *lpszTable = NULL;
int lpszSize = 0;

void _dbError_STMT(char* lp, HSTMT hstmt);
void _dbError_ENV(char* lp, HENV henv);
void _dbError_DBC(char* lp, HDBC hdbc);

#define TAB_LEN 128+1
#define REM_LEN 254+1
#define COL_LEN 100


class lbQuery;
class lbBoundColumn;
/*...sclass def lbDBView:0:*/

class lbDBView: public lb_I_MVC_View
{
public:
	lbDBView() {}
	virtual ~lbDBView() {}
	
	DECLARE_LB_UNKNOWN()
	
        virtual lbErrCodes LB_STDCALL updateView();
        
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
	lbBoundColumns() { ref = STARTREF; ArraySize = 1; }
	virtual ~lbBoundColumns() {
		_CL_VERBOSE << "lbBoundColumns::~lbBoundColumns() called." LOG_
	}
	
	DECLARE_LB_UNKNOWN()

        lb_I_Container* LB_STDCALL getBoundColumns();
        lbErrCodes      LB_STDCALL setBoundColumns(lb_I_Container* bc);

	lb_I_BoundColumn* LB_STDCALL getBoundColumn(int column);
	int		  LB_STDCALL getColumnCount();

        /**
         * Set a currently used query to bind their columns.
         */
        lbErrCodes      LB_STDCALL setQuery(lb_I_Query* q, lb_I_Container* ReadonlyColumns);

	int		LB_STDCALL getMode();

        
        /**
         * Convert the internal data to a char array and return the data.
         */
        lbErrCodes	LB_STDCALL getString(int column, lb_I_String* instance);
        lbErrCodes	LB_STDCALL getLong(int column, lb_I_Long* instance);
        lbErrCodes	LB_STDCALL getString(const char* column, lb_I_String* instance);
        lbErrCodes      LB_STDCALL setString(char* column, lb_I_String* instance);

	void		LB_STDCALL unbindReadonlyColumns();
	void		LB_STDCALL rebindReadonlyColumns();

	void		LB_STDCALL indicateNullValues();
	bool		LB_STDCALL setNull(int pos, bool b);
	bool		LB_STDCALL setNull(char const * name, bool b);

	bool		LB_STDCALL isNullable(int pos);
	bool		LB_STDCALL isNullable(char const * name);
	bool		LB_STDCALL isNull(int pos);
	bool		LB_STDCALL isNull(char const * name);

	lb_I_Query::lbDBColumnTypes LB_STDCALL getColumnType(int pos);
	lb_I_Query::lbDBColumnTypes LB_STDCALL getColumnType(char* name);
	int 		LB_STDCALL getColumnIndex(const char* name);

	void		LB_STDCALL setReadonly(char* column, bool updateable);
	bool		LB_STDCALL getReadonly(char* column);

	void		LB_STDCALL rebind();
	
	void		LB_STDCALL add();
	void		LB_STDCALL finishadd();
	
	bool		LB_STDCALL hasValidData();
	void		LB_STDCALL invalidateData();
		
	int LB_STDCALL getArraySize() { return ArraySize; }

private:
	UAP(lb_I_Container, boundColumns)
	UAP(lb_I_Container, ColumnNameMapping)
	int ArraySize;
	lbQuery* query;
};
/*...e*/
/*...sclass def lbQuery:0:*/
/** \brief Implementation using ODBC backend.
 */
class lbQuery :
public lb_I_Query
{
public:
	lbQuery(int readonly = 1) { 
		peeking = true;
		ref = STARTREF;
		_readonly = readonly; 
		hdbc = 0; 
		hstmt = 0; 
		henv = 0;
		hupdatestmt = 0;
		databound = 0; 
		count = 0; 
		firstfetched = 0;
		cols = 0;
		cursor = 1;
		haveData = false;
		mode = 0;
		_dataFetched = false;
		_autoRefresh = false;
		szSql = NULL;
		preparingFKColumns = 0;
		
		fetchstatus = 0;
		
		if (ReadOnlyColumns == NULL) {
		        REQUEST(getModuleInstance(), lb_I_Container, ReadOnlyColumns)
		}
	}
	
	virtual ~lbQuery() {
		if (szSql != NULL) {
			_CL_VERBOSE << "lbQuery::~lbQuery() called. (" << szSql << "). Refcount of ReadOnlyColumns is: " << ReadOnlyColumns->getRefCount() LOG_
			free(szSql);
		}
		if ((ReadOnlyColumns != NULL) && (ReadOnlyColumns->getRefCount() > 1)) _CL_LOG << "Error: Object would not deleted (ReadOnlyColumns) !" LOG_
		if ((mapPKTable_PKColumns_To_FKName != NULL) && (mapPKTable_PKColumns_To_FKName->getRefCount() > 1)) _CL_LOG << "Error: Object would not deleted (mapPKTable_PKColumns_To_FKName) !" LOG_		
		
		// The global variable for getTableName() :-(
		if (lpszTable) {
			/// \todo Return a ministring object, that gets automatically deleted.
			free(lpszTable);
			lpszTable = NULL;
		}
	}
	
	DECLARE_LB_UNKNOWN()

	/* Column binding mode */
        virtual lbErrCodes LB_STDCALL setView(lb_I_ColumnBinding* cb);

/*...svirtual lbErrCodes LB_STDCALL \40\un\41\registerView\40\lb_I_MVC_View\42\ view\41\\59\:8:*/
	/* MVC View mode */
	/*
	 * As a sample may be a graphical view for the result of the interpreted
	 * graphics and the textual view. The controller then might use one button
	 * for updating the model and the model then informs its views.
	 *
	 * For the future porting of FRS I would have a graphical view of the reserved
	 * places. It will show reserved as red and free as green.
	 *
	 * The source code for that object will call - maybe - 
	 * getColor("Reserved-Status", me).
	 *
	 * The dialog to reserve a place will update the data and therefore the model
	 * will inform also the graphical view.
	 */
	virtual lbErrCodes LB_STDCALL registerView(lb_I_MVC_View* view);
	virtual lbErrCodes LB_STDCALL unregisterView(lb_I_MVC_View* view);
/*...e*/

	void LB_STDCALL skipFKCollecting();
	void LB_STDCALL enableFKCollecting();
	void LB_STDCALL prepareFKList();

	char* LB_STDCALL getTableName(char* columnName = NULL);

	void LB_STDCALL dbError(char* lp, HSTMT hstmt);

	void LB_STDCALL PrintData(bool reverse);
	void LB_STDCALL PrintCurrent();
	void LB_STDCALL PrintHeader();
	void LB_STDCALL PrintFooter();

	void LB_STDCALL skipPeeking() { peeking = false; }

	/* Set the SQL query */
	lbErrCodes LB_STDCALL query(char* q, bool bind);
        
	lbErrCodes LB_STDCALL bind();

	bool LB_STDCALL dataFetched();

	lbErrCodes LB_STDCALL add();
	int LB_STDCALL isAdding() { return mode; }

	/**
	 * Deletes the current entry.
	 */
	lbErrCodes LB_STDCALL remove();
	
	/**
	 * Updates the modified data or stores new data (added via add())
	 */
	lbErrCodes LB_STDCALL update();


	/*
	 * General information based on the given query.
	 */

	int			LB_STDCALL getColumns();
	bool			LB_STDCALL lbQuery::hasColumnName(char* name);

	char*			LB_STDCALL getColumnName(int col);

	int			LB_STDCALL hasFKColumn(char* FKName);
			
	int			LB_STDCALL getFKColumns();
	
	lb_I_String*    	LB_STDCALL getFKColumn(int pos);
	
	lb_I_String*		LB_STDCALL getFKColumn(char* table, char* primary);
	
	lb_I_String*		LB_STDCALL getPKTable(char const * FKName);
	lb_I_String*    	LB_STDCALL getPKColumn(char const * FKName);

	int 			LB_STDCALL getPKColumns();
	lb_I_String* 		LB_STDCALL getPKColumn(int pos);

	bool		LB_STDCALL isFirst();
	bool		LB_STDCALL isLast();

	bool		LB_STDCALL isNullable(int pos);
	bool		LB_STDCALL isNullable(char const * name);
	bool		LB_STDCALL isNull(int pos);
	bool		LB_STDCALL isNull(char const * name);
	bool		LB_STDCALL setNull(int pos, bool b = true);
	bool		LB_STDCALL setNull(char const * name, bool b = true);

	lb_I_Query::lbDBColumnTypes LB_STDCALL getColumnType(int pos);
	lb_I_Query::lbDBColumnTypes LB_STDCALL getColumnType(char* name);

	lbDBCaseSensity    LB_STDCALL getCaseSensity();

	void			LB_STDCALL setReadonly(char* column, bool updateable = true);
	bool			LB_STDCALL getReadonly(char* column);
        
        /* Navigation */
        
        int             LB_STDCALL getPosition() { return cursor; }
        lbErrCodes      LB_STDCALL absolute(int pos);
        
        lbErrCodes	LB_STDCALL first();
        lbErrCodes	LB_STDCALL next();
        lbErrCodes	LB_STDCALL previous();
	lbErrCodes	LB_STDCALL last();
	char* 		LB_STDCALL setWhereClause(const char* query, char* where);
	
	char* 		LB_STDCALL addWhereClause(const char* query, char* where);
		
	void		LB_STDCALL setAutoRefresh(bool b);

	void		LB_STDCALL reopen();

#ifdef UNBOUND
        virtual char* 		LB_STDCALL getChar(int column);
#endif
#ifndef UNBOUND       
        lb_I_String*	LB_STDCALL getAsString(int column);
        lb_I_String*	LB_STDCALL getAsString(const char* column);
		lb_I_Long*		LB_STDCALL getAsLong(int column);
		lbErrCodes		LB_STDCALL setString(lb_I_String* columnName, lb_I_String* value);
#endif        
	
		lbErrCodes LB_STDCALL init(HENV _henv, HDBC _hdbc, int readonly = 1);

		lbErrCodes LB_STDCALL executeDirect(char* SQL);

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
	int		cursor;

	/// If any function such as first or next has been successfully called.
	bool	_dataFetched;
	
	/// Indicates a look forward to indicate if any more data is available.
	bool 	peeking;
	
	bool	haveData;
	HENV    henv;
	HDBC    hdbc;
	HSTMT   hstmt;
	HSTMT   hupdatestmt;
	RETCODE retcode;
	char*   szSql;
	int		databound;
	int     firstfetched;
	int		_readonly; // readonly = 1, else = 0
	bool	_autoRefresh;
	int		mode;  // insert = 1, select = 0
//	char* lpszTable;

	static	int     skipFKCollections;
	int		preparingFKColumns;
	
	// Number of columns for the query
	SQLSMALLINT cols;

	UAP(lb_I_Container, primaryColumns)
	UAP(lb_I_Container, ForeignColumns)
	
	UAP(lb_I_Container, mapPKTable_PKColumns_To_FKName)

	UAP(lb_I_Container, ReadOnlyColumns)

#ifdef UNBOUND	
	UAP(lb_I_Container, boundColumns)
#endif
#ifndef UNBOUND
	UAP(lb_I_ColumnBinding, boundColumns)
#endif
	char buff[100];

	int count;
	
	/**
	 * The status of the last fetch.
	 *
	 * -1 means, that the first row was reached.
	 * 0 means, that the cursor is everywhere between first and last.
	 * 1  means, that the last row was reached.
	 */
	int fetchstatus;
};

int lbQuery::skipFKCollections = 0;

/*...e*/
/*...sclass def lbBoundColumn:0:*/
class lbBoundColumn: public lb_I_BoundColumn {
public:	
	lbBoundColumn() {
		ref = STARTREF;
		bound = 0;
		buffer = NULL;
		//colName = NULL;
		ColumnSize = 0;
		rows = 2;
		mode = 0;
		cbBufferLength = new long[rows];
		cbBufferLength[0] = 0;
		cbBufferLength[1] = 0;
		isReadonly = true;
		// Binding a column may allow this.
		_isNullable = false;
		_hasValidData = false;
		columnName = NULL;
	}
	
	virtual ~lbBoundColumn() {
		if (columnName != NULL) {
			_CL_VERBOSE << "~lbBoundColumn('" << columnName << "') called." LOG_
			free(columnName);
		} else {
			_CL_VERBOSE << "~lbBoundColumn(?) called." LOG_
		}
		
		switch (_DataType) {
			case SQL_CHAR:
			case SQL_VARCHAR:
			case SQL_LONGVARCHAR:
				break;
			case SQL_INTEGER:
				break;
			case SQL_BIT:
				break;
			default:
				_CL_VERBOSE << "lbBoundColumn::~lbBoundColumn() failed: Unknown or not supported datatype for column '" << columnName << "'" LOG_
				break;
		}
		
		if (cbBufferLength != NULL) delete[] cbBufferLength;
		
		if ((bound != 0) && (buffer != NULL)) {
			free(buffer);
			buffer = NULL;
		}
	}
	
	lbBoundColumn(const lbBoundColumn& _ref) {
		printf("lbBoundColumn(const lbBoundColumn& _ref) called\n");
	}

	void operator=(const lbBoundColumn& _ref) {
		printf("void operator=(const lbBoundColumn& _ref) called\n");
	}

	DECLARE_LB_UNKNOWN()



	virtual bool LB_STDCALL isNullable();
	virtual bool LB_STDCALL isNull();
	virtual bool LB_STDCALL setNull(bool b);
	virtual lb_I_Query::lbDBColumnTypes LB_STDCALL getType();
	virtual lb_I_Unknown* LB_STDCALL getData();
	virtual lbErrCodes LB_STDCALL getAsString(lb_I_String* result, int asParameter = 0);
	virtual lbErrCodes LB_STDCALL getAsLong(lb_I_Long* result, int asParameter = 0);
	virtual lbErrCodes LB_STDCALL setFromString(lb_I_String* set, int mode);
	virtual lbErrCodes LB_STDCALL setFromLong(lb_I_Long* set, int mode);

	void		LB_STDCALL checkReadonly(int column);
	void		LB_STDCALL setReadonly(bool updateable);
	bool		LB_STDCALL getReadonly() { return isReadonly; }

	lb_I_String*	LB_STDCALL getColumnName();

	lbErrCodes	LB_STDCALL prepareBoundColumn(lb_I_Query* q, int column);
	lbErrCodes	LB_STDCALL bindColumn(lb_I_Query* q, int column, bool ro);
	void		LB_STDCALL bindNullColumn();


	void		LB_STDCALL unbindReadonlyColumns();
	void		LB_STDCALL rebindReadonlyColumns();

	void		LB_STDCALL rebind();
	
	void		LB_STDCALL add();
	void		LB_STDCALL finishadd();
	
	bool	LB_STDCALL hasValidData();
	void	LB_STDCALL invalidateData();
	
protected:

	char* LB_STDCALL getColumnName_c_str() { return columnName; }

	virtual lbErrCodes  LB_STDCALL setData(int b, SQLSMALLINT dt, void* bu, char* name) {
		bound = b;
		_DataType = dt;
		buffer = bu;
		
		if (name == NULL) {
			_LOG << "ERROR: Cloning data with NULL pointer" LOG_
		}

		setColumn(name);

		return ERR_NONE;
	}

	// I call my self to leave my ownership
	virtual lbErrCodes LB_STDCALL leaveOwnership(lb_I_BoundColumn* oldOwner, lb_I_BoundColumn* newOwner);


	virtual void LB_STDCALL setColumn(char* col) {
		if (columnName != NULL) free(columnName);
		
		columnName = (char*) malloc(strlen(col)+1);
		columnName[0] = 0;
		strcpy(columnName, col);
	}

	char*		columnName;

	int			bound;
	int			mode;
	bool		isReadonly;
	bool		_isNullable;
	bool		_hasValidData;
	SQLSMALLINT     _DataType;
	int 		_column;
	void*		buffer;
	int		buffersize;
	lbQuery*	query;
	
	
	/** \brief SQL_NULL_DATA indicator.
	 *
	 * This normally contains the buffer length of the filled data. If there is NULL data,
	 * it will indicated by SQL_NULL_DATA.
	 */
	long*		cbBufferLength;
	SQLUINTEGER     ColumnSize; //new (long);
	int		rows;
	HSTMT 		hstmt;
};

/*...e*/



/*...sclass lbDBView:0:*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDBView)
        ADD_INTERFACE(lb_I_MVC_View)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfDBView, lbDBView)


lbErrCodes LB_STDCALL lbDBView::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbDBView::setData(...) not implemented yet" LOG_
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

/*...sunimplemented:0:*/
lbErrCodes LB_STDCALL lbBoundColumns::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbBoundColumns::setData(...) not implemented yet" LOG_
        
        return ERR_NOT_IMPLEMENTED;
}

lb_I_Container* LB_STDCALL lbBoundColumns::getBoundColumns() {
        _CL_VERBOSE << "lbBoundColumns::getBoundColumns() not implemented yet" LOG_
	return NULL;
}

lbErrCodes      LB_STDCALL lbBoundColumns::setBoundColumns(lb_I_Container* bc) {
        _CL_VERBOSE << "lbBoundColumns::setBoundColumns() not implemented yet" LOG_
	return ERR_NONE;
}
/*...e*/

bool LB_STDCALL lbBoundColumns::isNull(char const * name) {
	int pos = getColumnIndex(name);
	return isNull(pos);
}

bool LB_STDCALL lbBoundColumns::isNull(int pos) {
	lbErrCodes err = ERR_NONE;
	if ((boundColumns != NULL) && (pos > -1)) {
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerKey) 
		integerKey->setData(pos);
		UAP(lb_I_Unknown, ukdata)
		UAP(lb_I_KeyBase, key)
		
		QI(integerKey, lb_I_KeyBase, key)

		ukdata = boundColumns->getElement(&key);
		if (ukdata == NULL) printf("NULL pointer!\n");

		UAP(lb_I_BoundColumn, bc)
		lbErrCodes err = ukdata->queryInterface("lb_I_BoundColumn", (void**) &bc, __FILE__, __LINE__);

		return bc->isNull();
	}

	// What to answer here ??
	return false;
}

bool LB_STDCALL lbBoundColumns::isNullable(char const * name) {
	int pos = getColumnIndex(name);
	return isNullable(pos);
}

bool LB_STDCALL lbBoundColumns::isNullable(int pos) {
	lbErrCodes err = ERR_NONE;
	if ((boundColumns != NULL) && (pos > -1)) {
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerKey) 
		integerKey->setData(pos);
		UAP(lb_I_Unknown, ukdata)
		UAP(lb_I_KeyBase, key)
		
		QI(integerKey, lb_I_KeyBase, key)

		ukdata = boundColumns->getElement(&key);
		if (ukdata == NULL) printf("NULL pointer!\n");

		UAP(lb_I_BoundColumn, bc)
		lbErrCodes err = ukdata->queryInterface("lb_I_BoundColumn", (void**) &bc, __FILE__, __LINE__);

		return bc->isNullable();
	}

	// What to answer here ??
	return false;
}

/*...svoid LB_STDCALL lbBoundColumns\58\\58\rebind\40\\41\:0:*/
void LB_STDCALL lbBoundColumns::rebind() {
	lbErrCodes err = ERR_NONE;
	
	if (boundColumns != NULL) {
		while (boundColumns->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_BoundColumn, bc)
			
			uk = boundColumns->nextElement();
			
			QI(uk, lb_I_BoundColumn, bc)
			
			bc->rebind();
		}
	}
}
/*...e*/

void LB_STDCALL lbBoundColumns::add() {
	lbErrCodes err = ERR_NONE;
	
	if (boundColumns != NULL) {
		while (boundColumns->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_BoundColumn, bc)
			
			uk = boundColumns->nextElement();
			
			QI(uk, lb_I_BoundColumn, bc)
			
			bc->add();
		}
	}
}

void LB_STDCALL lbBoundColumns::finishadd() {
	lbErrCodes err = ERR_NONE;
	
	if (boundColumns != NULL) {
		while (boundColumns->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_BoundColumn, bc)
			
			uk = boundColumns->nextElement();
			
			QI(uk, lb_I_BoundColumn, bc)
			
			bc->finishadd();
		}
	}
}

void LB_STDCALL lbBoundColumns::indicateNullValues() {
	lbErrCodes err = ERR_NONE;
	
	if (boundColumns != NULL) {
		while (boundColumns->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_BoundColumn, bc)
			
			uk = boundColumns->nextElement();
			
			QI(uk, lb_I_BoundColumn, bc)
			
			if (bc->isNull()) {
				bc->bindNullColumn();
			}
		}
	}
}

void	LB_STDCALL lbBoundColumns::invalidateData() {
	lbErrCodes err = ERR_NONE;
	
	while ((boundColumns != NULL) && (boundColumns->hasMoreElements())) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_BoundColumn, bc)
		uk = boundColumns->nextElement();
		
		QI(uk, lb_I_BoundColumn, bc)
		
		if (bc != NULL) {
			bc->invalidateData();
		}
	}
}

bool	LB_STDCALL lbBoundColumns::hasValidData() {
	lbErrCodes err = ERR_NONE;
	
	while ((boundColumns != NULL) && (boundColumns->hasMoreElements())) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_BoundColumn, bc)
		uk = boundColumns->nextElement();
		
		QI(uk, lb_I_BoundColumn, bc)
		
		if (bc != NULL) {
			if (!bc->hasValidData()) return false;
		}
	}
	
	return true;
}


bool LB_STDCALL lbBoundColumns::setNull(char const * name, bool b) {
	lbErrCodes err = ERR_NONE;
	
	int pos = getColumnIndex(name);

	return setNull(pos, b);
}

bool LB_STDCALL lbBoundColumns::setNull(int pos, bool b) {
	lbErrCodes err = ERR_NONE;
	if ((boundColumns != NULL) && (pos > -1)) {
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerKey) 
		integerKey->setData(pos);
		UAP(lb_I_Unknown, ukdata)
		UAP(lb_I_KeyBase, key)
		
		QI(integerKey, lb_I_KeyBase, key)

		ukdata = boundColumns->getElement(&key);
		if (ukdata == NULL) printf("NULL pointer!\n");

		UAP(lb_I_BoundColumn, bc)
		lbErrCodes err = ukdata->queryInterface("lb_I_BoundColumn", (void**) &bc, __FILE__, __LINE__);

		bc->setNull(b);
	}
	return true;
}

/*...svoid LB_STDCALL lbBoundColumns\58\\58\unbindReadonlyColumns\40\\41\:0:*/
void LB_STDCALL lbBoundColumns::unbindReadonlyColumns() {
	lbErrCodes err = ERR_NONE;
	
	if (boundColumns != NULL) {
		while (boundColumns->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_BoundColumn, bc)
			
			uk = boundColumns->nextElement();
			
			QI(uk, lb_I_BoundColumn, bc)
			
			bc->unbindReadonlyColumns();
		}
	}
}
/*...e*/
/*...svoid LB_STDCALL lbBoundColumns\58\\58\rebindReadonlyColumns\40\\41\:0:*/
void LB_STDCALL lbBoundColumns::rebindReadonlyColumns() {
	lbErrCodes err = ERR_NONE;
	
	if (boundColumns != NULL) {
		while (boundColumns->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_BoundColumn, bc)
			
			uk = boundColumns->nextElement();
			
			QI(uk, lb_I_BoundColumn, bc)
			
			bc->rebindReadonlyColumns();
		}
	}
}
/*...e*/

/*...slb_I_Query\58\\58\lbDBColumnTypes LB_STDCALL lbBoundColumns\58\\58\getColumnType\40\int pos\41\:0:*/
lb_I_Query::lbDBColumnTypes LB_STDCALL lbBoundColumns::getColumnType(int pos) {

	lbErrCodes err = ERR_NONE;
	if (boundColumns != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerKey) 
		integerKey->setData(pos);
		UAP(lb_I_Unknown, ukdata)
		UAP(lb_I_KeyBase, key)
		
		QI(integerKey, lb_I_KeyBase, key)

		ukdata = boundColumns->getElement(&key);
		if (ukdata == NULL) printf("NULL pointer!\n");

		UAP(lb_I_BoundColumn, bc)
		lbErrCodes err = ukdata->queryInterface("lb_I_BoundColumn", (void**) &bc, __FILE__, __LINE__);

		return bc->getType();
	}

	_LOG << "lbBoundColumns::getColumnType(int pos) returns unknown type" LOG_

	return lb_I_Query::lbDBColumnUnknown;
}
/*...e*/
/*...sint LB_STDCALL lbBoundColumns\58\\58\getColumnIndex\40\char\42\ name\41\:0:*/
int LB_STDCALL lbBoundColumns::getColumnIndex(const char* name) {

	lbErrCodes err = ERR_NONE;
	if (boundColumns != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, stringKey) 
		stringKey->setData(name);
		UAP(lb_I_Unknown, ukdata)
		UAP(lb_I_KeyBase, key)
		
		QI(stringKey, lb_I_KeyBase, key)

		ukdata = ColumnNameMapping->getElement(&key);
		if (ukdata == NULL) {
			_LOG << "lbBoundColumns::getColumnIndex('" << name << "') returned no data !" LOG_
			
			return -1;
		}

		UAP(lb_I_Integer, pos)
		
		lbErrCodes err = ukdata->queryInterface("lb_I_Integer", (void**) &pos, __FILE__, __LINE__);
		
		return pos->getData();
	}

	return -1;
}
/*...e*/
/*...slb_I_Query\58\\58\lbDBColumnTypes LB_STDCALL lbBoundColumns\58\\58\getColumnType\40\char\42\ name\41\:0:*/
lb_I_Query::lbDBColumnTypes LB_STDCALL lbBoundColumns::getColumnType(char* name) {

	lbErrCodes err = ERR_NONE;
	if (boundColumns != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, stringKey) 
		stringKey->setData(name);
		UAP(lb_I_Unknown, ukdata)
		UAP(lb_I_KeyBase, key)
		
		QI(stringKey, lb_I_KeyBase, key)

		ukdata = ColumnNameMapping->getElement(&key);
		if (ukdata == NULL) {
			_LOG << "lbBoundColumns::getColumnType('" << name << "') returned no data !" LOG_
			
			return lb_I_Query::lbDBColumnUnknown;
		}

		UAP(lb_I_BoundColumn, bc)
		UAP(lb_I_Integer, pos)
		
		lbErrCodes err = ukdata->queryInterface("lb_I_Integer", (void**) &pos, __FILE__, __LINE__);
		
		return getColumnType(pos->getData());
	}

	return lb_I_Query::lbDBColumnUnknown;
}
/*...e*/
/*...svoid LB_STDCALL lbBoundColumns\58\\58\setReadonly\40\char\42\ column\44\ bool updateable\41\:0:*/
void LB_STDCALL lbBoundColumns::setReadonly(char* column, bool updateable) {

	lbErrCodes err = ERR_NONE;
	if (boundColumns != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, stringKey) 
		stringKey->setData(column);
		UAP(lb_I_Unknown, ukdata)
		UAP(lb_I_KeyBase, key)
		
		QI(stringKey, lb_I_KeyBase, key)

		ukdata = ColumnNameMapping->getElement(&key);
		if (ukdata == NULL) printf("NULL pointer!\n");

		UAP(lb_I_Integer, pos)
		
		lbErrCodes err = ukdata->queryInterface("lb_I_Integer", (void**) &pos, __FILE__, __LINE__);
		
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerKey) 
		integerKey->setData(pos.getPtr());
		UAP(lb_I_Unknown, ukdata1)
		UAP(lb_I_KeyBase, key1)
		
		QI(integerKey, lb_I_KeyBase, key1)

		ukdata1 = boundColumns->getElement(&key1);
		if (ukdata1 == NULL) printf("NULL pointer!\n");

		UAP(lb_I_BoundColumn, bc)
		err = ukdata1->queryInterface("lb_I_BoundColumn", (void**) &bc, __FILE__, __LINE__);

		bc->setReadonly(updateable);
	}
}
/*...e*/
/*...sbool LB_STDCALL lbBoundColumns\58\\58\getReadonly\40\char\42\ column\41\:0:*/
bool LB_STDCALL lbBoundColumns::getReadonly(char* column) {
	lbErrCodes err = ERR_NONE;
	if (boundColumns != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, stringKey) 
		stringKey->setData(column);
		UAP(lb_I_Unknown, ukdata)
		UAP(lb_I_KeyBase, key)
		
		QI(stringKey, lb_I_KeyBase, key)

		ukdata = ColumnNameMapping->getElement(&key);
		if (ukdata == NULL) printf("NULL pointer!\n");

		

		UAP(lb_I_Integer, pos)
		
		lbErrCodes err = ukdata->queryInterface("lb_I_Integer", (void**) &pos, __FILE__, __LINE__);
		
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerKey) 
		integerKey->setData(pos.getPtr());
		UAP(lb_I_Unknown, ukdata1)
		UAP(lb_I_KeyBase, key1)
		
		QI(integerKey, lb_I_KeyBase, key1)

		ukdata1 = boundColumns->getElement(&key1);
		if (ukdata1 == NULL) printf("NULL pointer!\n");

		UAP(lb_I_BoundColumn, bc)
		err = ukdata1->queryInterface("lb_I_BoundColumn", (void**) &bc, __FILE__, __LINE__);

		return bc->getReadonly();
	}
	return false;
}
/*...e*/
/*...slb_I_BoundColumn\42\ LB_STDCALL lbBoundColumns\58\\58\getBoundColumn\40\int column\41\:0:*/
lb_I_BoundColumn* LB_STDCALL lbBoundColumns::getBoundColumn(int column) {
	lbErrCodes err = ERR_NONE;
	if (boundColumns != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerKey) 
		integerKey->setData(column);
		UAP(lb_I_Unknown, ukdata)
		UAP(lb_I_KeyBase, key)
		
		QI(integerKey, lb_I_KeyBase, key)

		ukdata = boundColumns->getElement(&key);
		if (ukdata == NULL) printf("NULL pointer!\n");

		UAP(lb_I_BoundColumn, bc)
		lbErrCodes err = ukdata->queryInterface("lb_I_BoundColumn", (void**) &bc, __FILE__, __LINE__);

		bc++;
		
		return bc.getPtr();
	}
	return NULL;
}
/*...e*/

/*...sint             LB_STDCALL lbBoundColumns\58\\58\getColumnCount\40\\41\:0:*/
int               LB_STDCALL lbBoundColumns::getColumnCount() {
	return boundColumns->Count();
}
/*...e*/

/*...slbErrCodes      LB_STDCALL lbBoundColumns\58\\58\setQuery\40\lbQuery\42\ q\44\ lb_I_Container\42\ ReadonlyColumns\41\:0:*/
lbErrCodes      LB_STDCALL lbBoundColumns::setQuery(lb_I_Query* q, lb_I_Container* ReadonlyColumns) {
/*...spreparements:0:*/

	lbQuery* qq = (lbQuery*) q;

	HSTMT hstmt = qq->getCurrentStatement();
	query = qq;

// As Luf states, here it should not be.
//#ifdef bla
	const int ArraySize = 1;
	SQLUSMALLINT RowStatusArray[ArraySize];

	// Set the array size to one.
	SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_ARRAY_SIZE, (SQLPOINTER) ArraySize, 0);
	
	// Why this construct ??
	SQLINTEGER csrType = SQL_CURSOR_KEYSET_DRIVEN;
	
	SQLSetStmtAttr(hstmt, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER) csrType, 0);
	SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_BIND_TYPE, SQL_BIND_BY_COLUMN, 0);
	SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_STATUS_PTR, RowStatusArray, 0);
//#endif
	/*
	 * Get the number of columns for this query.
	 */
	SQLSMALLINT num = 0;	
	SQLRETURN sqlreturn = SQLNumResultCols(hstmt, &num);
/*...e*/
	
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

	if (boundColumns == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, boundColumns)
	} else {
		boundColumns->deleteAll();
	}

	// For each column create a bound column instance.
	// The instance will bind the column.
	for (int i = 1; i <= num; i++) {
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerKey)
		lbErrCodes err = ERR_NONE;

		// Create the instance ...
		
		lbBoundColumn* bc = new lbBoundColumn();

		lb_I_Module* m = getModuleManager();


		bc->setModuleManager(m, __FILE__, __LINE__);

		bc->prepareBoundColumn(q, i);

		integerKey->setData(i);

		UAP(lb_I_Unknown, uk)
		UAP(lb_I_KeyBase, key)

		bc->queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__);
		integerKey->queryInterface("lb_I_KeyBase", (void**) &key, __FILE__, __LINE__);		

		boundColumns->insert(&uk, &key);

		UAP(lb_I_BoundColumn, bc1)
		bc1 = getBoundColumn(i);

		UAP_REQUEST(manager.getPtr(), lb_I_String, colName)
		UAP(lb_I_KeyBase, key1)
		colName->setData(qq->getColumnName(i));
		QI(colName, lb_I_KeyBase, key1)

		bool Readonly = false;

		if (ReadonlyColumns->exists(&key1) == 1) Readonly = true;

		bc1->bindColumn(q, i, Readonly);

/*...sGet the column name for this column and add an index to it\39\s column id\46\:16:*/

		if (ColumnNameMapping == NULL) {
			// Create the index mapping instnce
			
			REQUEST(manager.getPtr(), lb_I_Container, ColumnNameMapping)
		}
		
		UAP(lb_I_KeyBase, skey)
		UAP(lb_I_String, string)

		string = bc1->getColumnName();

		string->queryInterface("lb_I_KeyBase", (void**) &skey, __FILE__, __LINE__);

		UAP(lb_I_Unknown, ivalue)

		integerKey->queryInterface("lb_I_Unknown", (void**) &ivalue, __FILE__, __LINE__);
		
		if (ColumnNameMapping.getPtr() == NULL) printf("Error: NULL pointer at ColumnNameMapping detected\n");
		if (ivalue.getPtr() == NULL) printf("Error: NULL pointer at ivalue detected\n");
		if (skey.getPtr() == NULL) printf("Error: NULL pointer at skey detected\n");

		ColumnNameMapping->insert(&ivalue, &skey);
/*...e*/

	}

	return ERR_NONE;
}
/*...e*/
lbErrCodes	LB_STDCALL lbBoundColumns::getLong(int column, lb_I_Long* instance) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_BoundColumn, bc)

	bc = getBoundColumn(column);
	bc->getAsLong(instance);

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes      LB_STDCALL lbBoundColumns\58\\58\getString\40\int column\44\ lb_I_String\42\ instance\41\:0:*/
lbErrCodes	LB_STDCALL lbBoundColumns::getString(int column, lb_I_String* instance) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_BoundColumn, bc)

	bc = getBoundColumn(column);
	// getBoundColumn(column); increases refcount
	//bc++;
	bc->getAsString(instance);

	return ERR_NONE;
}
/*...e*/
lbErrCodes	LB_STDCALL lbBoundColumns::getString(const char* column, lb_I_String* instance) {
	getString(getColumnIndex(column), instance);
	
	return ERR_NONE;
}
/*...slbErrCodes      LB_STDCALL lbBoundColumns\58\\58\setString\40\char\42\ column\44\ lb_I_String\42\ instance\41\:0:*/
lbErrCodes      LB_STDCALL lbBoundColumns::setString(char* column, lb_I_String* instance) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, ukdata)
	UAP(lb_I_KeyBase, key)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, Column)
	
	Column->setData(column);
	
	QI(Column, lb_I_KeyBase, key)
	ukdata = ColumnNameMapping->getElement(&key);

	UAP(lb_I_KeyBase, index)
	QI(ukdata, lb_I_KeyBase, index)

	UAP(lb_I_Unknown, uk_bc)
	uk_bc = boundColumns->getElement(&index);
	
	UAP(lb_I_BoundColumn, bc)
	QI(uk_bc, lb_I_BoundColumn, bc)

	// Adding or updating ? - Decided inside
	bc->setFromString(instance, getMode());

	return ERR_NONE;
}
/*...e*/

int		LB_STDCALL lbBoundColumns::getMode() {
	return query->isAdding();
}

/*...sclass lbQuery:0:*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbQuery)
        ADD_INTERFACE(lb_I_Query)
END_IMPLEMENT_LB_UNKNOWN()

UAP(lb_I_Integer, key)

/*...sto be implemented:0:*/
lbErrCodes LB_STDCALL lbQuery::setData(lb_I_Unknown * uk) {
	_CL_LOG << "lbQuery::setData(...): Not implemented yet" LOG_
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
/*...senable and skip FK collection:0:*/
void LB_STDCALL lbQuery::skipFKCollecting() {
	skipFKCollections = 1;
}

void LB_STDCALL lbQuery::enableFKCollecting() {
	skipFKCollections = 0;
}
/*...e*/
/*...svoid LB_STDCALL lbQuery\58\\58\PrintData\40\bool reverse\41\:0:*/
void LB_STDCALL lbQuery::PrintData(bool reverse) {
	lbErrCodes err = ERR_NONE;
	int cols = getColumns();

	PrintHeader();
	
	if (reverse == false) {
/*...sforward:8:*/
	err = first();
	while (err == ERR_DB_ROWDELETED) err = next();

	if (err == ERR_NONE) {
	    PrintCurrent();
	    
	    err = next();
	    
	    while (err == ERR_DB_ROWDELETED) err = next();
	    
	    while (err == ERR_NONE) {
			PrintCurrent();
			
			err = next();
			
			while (err == ERR_DB_ROWDELETED) err = next();
	    }
		
	    if (err == WARN_DB_NODATA) {
	    		PrintCurrent();
	    }	    
	}
/*...e*/
	} else {
/*...sreverse:8:*/
	err = last();
	while (err == ERR_DB_ROWDELETED) err = previous();
	if (err == ERR_NONE) {
	    PrintCurrent();
	    
	    err = previous();
	    
	    while (err == ERR_DB_ROWDELETED) err = previous();
	    
	    while (err == ERR_NONE) {
			PrintCurrent();
			
			err = previous();
			
			while (err == ERR_DB_ROWDELETED) err = previous();
	    }
		
	    if (err == WARN_DB_NODATA) {
	    		PrintCurrent();
	    }	    
	}
/*...e*/
	}
	
	PrintFooter();
}
/*...e*/
/*...svoid LB_STDCALL lbQuery\58\\58\PrintFooter\40\\41\:0:*/
void LB_STDCALL lbQuery::PrintFooter() {
	int cols = getColumns();
	
	for (int i = 1; i < cols; i++) {
		printf("-------------------");
	}
	
	printf("-------------------\n");
}
/*...e*/
/*...svoid LB_STDCALL lbQuery\58\\58\PrintHeader\40\\41\:0:*/
void LB_STDCALL lbQuery::PrintHeader() {
	int cols = getColumns();
	for (int i = 1; i < cols; i++) {
	        printf("%19s", getColumnName(i));
	}

	printf("%19s\n", getColumnName(cols));

	PrintFooter();
}
/*...e*/
/*...svoid LB_STDCALL lbQuery\58\\58\PrintCurrent\40\\41\:0:*/
void LB_STDCALL lbQuery::PrintCurrent() {
	UAP(lb_I_String, s)
	int cols = getColumns();
	
	for (int i = 1; i <= cols-1; i++) {
		UAP(lb_I_String, s)
	        s = getAsString(i);
	        s->trim();
	        printf("%19s", s->charrep());
	};

	s = getAsString(cols);
	s->trim();
	printf("%19s\n", s->charrep());
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\executeDirect\40\char\42\ SQL\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::executeDirect(char* SQL) {
	HSTMT hstmt;

	retcode = SQLAllocStmt(hdbc, &hstmt);

	if (retcode != SQL_SUCCESS)
	{
	        _dbError_DBC( "SQLAllocStmt()", hdbc);
	        _LOG << "lbDatabase::getQuery() failed due to statement allocation." LOG_
        	return ERR_DB_EXECDIRECT;
	}
/*
	if (readonly == 0) {
		retcode = SQLSetStmtOption(hstmt, SQL_ATTR_CONCURRENCY, 
		//SQL_CONCUR_LOCK
		//SQL_CONCUR_VALUES // To be tested
		SQL_CONCUR_ROWVER // Does not work
		);
	}

        if (retcode != SQL_SUCCESS)
        {
                dbError( "SQLSetStmtOption()", hstmt);
                _LOG << "lbDatabase::getQuery() failed due to setting concurrency settings." LOG_
                return ERR_DB_EXECDIRECT;
        }
*/
	retcode = SQLSetStmtOption(hstmt, SQL_CURSOR_TYPE, SQL_CURSOR_KEYSET_DRIVEN);


	if (retcode == SQL_SUCCESS_WITH_INFO) {
                dbError( "SQLSetStmtOption()", hstmt);
                _LOG << "lbDatabase::getQuery() failed due to setting cursor type." LOG_
	} else
        if (retcode != SQL_SUCCESS)
        {
                dbError( "SQLSetStmtOption()", hstmt);
                _LOG << "lbDatabase::getQuery() failed due to setting cursor type." LOG_
                return ERR_DB_EXECDIRECT;
        }

        SQLINTEGER size = 1;

	if (retcode != SQL_SUCCESS) {
		dbError( "SQLSetStmtAttr()", hstmt);
		_LOG << "lbDatabase::getQuery() failed due to set statement attributes." LOG_
		return ERR_DB_EXECDIRECT;
	}

	retcode = SQLExecDirect(hstmt, (unsigned char*) SQL, SQL_NTS);

	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO))
	{
	        dbError("SQLExecDirect()", hstmt);
	        _LOG << "lbQuery::query(...) failed. (" << szSql << ")" LOG_
	        return ERR_DB_QUERYFAILED;
	}

	retcode = SQLFreeStmt (hstmt, SQL_DROP);

	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO))
	{
	        dbError("SQLExecDirect()", hstmt);
	        _LOG << "lbQuery::query(...) failed. (" << szSql << ")" LOG_
	        return ERR_DB_QUERYFAILED;
	}

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\init\40\HENV _henv\44\ HDBC _hdbc\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::init(HENV _henv, HDBC _hdbc, int readonly) {
	hdbc = _hdbc;
	henv = _henv;
	hdbc = _hdbc;

	retcode = SQLAllocStmt(hdbc, &hstmt); /* Statement handle */

	if (retcode != SQL_SUCCESS)
	{
	        _dbError_DBC( "SQLAllocStmt()", hdbc);
	        _LOG << "lbDatabase::getQuery() failed due to statement allocation." LOG_
	        SQLFreeEnv(henv);
        	return ERR_DB_ALLOCSTATEMENT;
	}

	if (readonly == 0) {
	// Compare values before updating
		
		
		retcode = SQLSetStmtOption(hstmt, SQL_ATTR_CONCURRENCY, 

		//SQL_CONCUR_LOCK
		//SQL_CONCUR_VALUES // To be tested
		SQL_CONCUR_ROWVER // Does not work
		
		);
		
		
		_readonly = readonly;
	}

        if (retcode != SQL_SUCCESS)
        {
                _LOG << "lbDatabase::getQuery() failed due to setting concurrency settings." LOG_
                dbError( "SQLSetStmtOption()", hstmt);
                SQLFreeEnv(henv);
                return ERR_DB_ALLOCSTATEMENT;
        }

	retcode = SQLSetStmtOption(hstmt, SQL_CURSOR_TYPE, SQL_CURSOR_KEYSET_DRIVEN);


	if (retcode == SQL_SUCCESS_WITH_INFO) {
                dbError( "SQLSetStmtOption()", hstmt);
                _LOG << "lbDatabase::getQuery() failed due to setting cursor type." LOG_
	} else
        if (retcode != SQL_SUCCESS)
        {
                dbError( "SQLSetStmtOption()", hstmt);
                _LOG << "lbDatabase::getQuery() failed due to setting cursor type." LOG_
                SQLFreeEnv(henv);
                return ERR_DB_ALLOCSTATEMENT;
        }

        SQLINTEGER size = 1;

	if (retcode != SQL_SUCCESS) {
		dbError( "SQLSetStmtAttr()", hstmt);
		_LOG << "lbDatabase::getQuery() failed due to set statement attributes." LOG_
		//SQLFreeEnv(henv);
		return ERR_DB_ALLOCSTATEMENT;
	}	
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\bind\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::bind() {
	if (databound == 0) {
		
		_CL_VERBOSE << "lbQuery::bind() binds columns..." LOG_
		
		retcode = SQLNumResultCols(hstmt, &cols);
	
		if (retcode != SQL_SUCCESS)
		{
			_CL_LOG << "lbQuery::bind() SQLNumResultCols() failed." LOG_
		        dbError("SQLNumResultCols()", hstmt);
		        return ERR_DB_QUERYFAILED;
		} else {
			lbErrCodes err = ERR_NONE;
			lbBoundColumns* boundcols = NULL;
			
			if (boundColumns != NULL) {
				_CL_LOG << "Unbind columns of previous query." LOG_
				boundColumns--;
				boundColumns = NULL;
			}
			
			boundcols = new lbBoundColumns();
			boundcols->setModuleManager(*&manager, __FILE__, __LINE__);

			//boundColumns = boundcols;
		
			_CL_VERBOSE << "Bind columns with " << ReadOnlyColumns->Count() << " readonly elements" LOG_
		
			QI(boundcols, lb_I_ColumnBinding, boundColumns)
		
			boundColumns->setQuery(this, ReadOnlyColumns.getPtr());
			
			prepareFKList();
		}
		
		databound = 1;
	}
	
	return ERR_NONE;
}
/*...e*/
/*...schar\42\ LB_STDCALL lbQuery\58\\58\setWhereClause\40\const char\42\ query\44\ char\42\ where\41\:0:*/
/// \todo Add support for joined tables.
char* LB_STDCALL lbQuery::setWhereClause(const char* query, char* where) {
	char* temp = NULL;
	UAP_REQUEST(manager.getPtr(), lb_I_String, orginal)
	
	*orginal = query;
		
	if (where != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, order)
		char* orderClause = orginal->stristr(orginal->charrep(), "ORDER BY");
		
		if (orderClause != NULL) {
			char* t;
			orderClause[-1] = 0;
			t = strdup(orderClause);
			orderClause = t;
			t = strdup(orginal->charrep());
			*orginal = t;
			*orginal += " ";
			*orginal += where;
			*orginal += " ";
			*orginal += orderClause;
			free(t);
			free(orderClause);
		} else {
			*orginal += " ";
			*orginal += where;
		}
	}
	return strdup(orginal->charrep());
}
/*...e*/
/// \todo Implement adding where clauses to exsisting.
char* LB_STDCALL lbQuery::addWhereClause(const char* query, char* where) {
	return strdup("ERROR: Not implemented.");
}

bool LB_STDCALL lbQuery::dataFetched() {
	return _dataFetched;
}
lb_I_Query::lbDBCaseSensity    LB_STDCALL lbQuery::getCaseSensity() {
	SQLUINTEGER    fFuncs;
	
	retcode = SQLGetInfo(hdbc, SQL_IDENTIFIER_CASE, (SQLPOINTER)&fFuncs, sizeof(fFuncs), NULL);


	switch (fFuncs) {
		case SQL_IC_UPPER: return lb_I_Query::lbDBCaseUpper;
		case SQL_IC_LOWER: return lb_I_Query::lbDBCaseLower;
		case SQL_IC_SENSITIVE: return lb_I_Query::lbDBCaseSensibility;
		case SQL_IC_MIXED: return lb_I_Query::lbDBCaseMixed;
	}

	_LOG << "Warning: ODBC conformance error!" LOG_
	
	return lb_I_Query::lbDBCaseSensibility;
}

/*...slbErrCodes LB_STDCALL lbQuery\58\\58\query\40\char\42\ q\44\ bool bind\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::query(char* q, bool bind) {
	lbBoundColumns* boundcols = NULL;

	_dataFetched = false;

    if (q == NULL) {
		_LOG << "Error: Have got a NULL pointer for the query to execute!" LOG_
		return ERR_DB_QUERYFAILED;
	}
	
	if (szSql != NULL) free(szSql);
	
	szSql = strdup(q);

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
/*...sbla:0:*/
/*
	char cursorname[100] = "";
	
	sprintf(cursorname, "Cursor-%p", this);

	retcode = SQLSetCursorName(hstmt, cursorname, SQL_NTS);
*/	
/*...e*/
// Moved from lbBoundColumns::setQuery(...)
// As Luf states, here it should be.
#ifdef bla
	const int ArraySize = 1;
	SQLUSMALLINT RowStatusArray[ArraySize];

	// Set the array size to one.
	SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_ARRAY_SIZE, (SQLPOINTER) ArraySize, 0);
	
	// Why this construct ??
	SQLINTEGER csrType = SQL_CURSOR_KEYSET_DRIVEN;
	
	if ((retcode = SQLSetStmtAttr(hstmt, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER) csrType, 0)) != SQL_SUCCESS) {
		if (retcode != SQL_SUCCESS_WITH_INFO) 
			_CL_LOG << "lbQuery::query(...) Error: Failed to set cursor to keyset driven." LOG_
	}

	if ((retcode = SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_BIND_TYPE, SQL_BIND_BY_COLUMN, 0)) != SQL_SUCCESS) {
		if (retcode != SQL_SUCCESS_WITH_INFO) 
			_CL_LOG << "lbQuery::query(...) Error: Failed to set binding by column." LOG_
	}
	
	if ((retcode = SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_STATUS_PTR, RowStatusArray, 0)) != SQL_SUCCESS) {
		if (retcode != SQL_SUCCESS_WITH_INFO) 
			_CL_LOG << "lbQuery::query(...) Error: Failed to set rowstatus array." LOG_
	}
#endif
	retcode = SQLExecDirect(hstmt, (unsigned char*) szSql, SQL_NTS);

	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO))
        {
        	//dbError("SQLExecDirect()", hstmt);
		_LOG << "lbQuery::query(...) failed. (" << szSql << ")" LOG_
		return ERR_DB_QUERYFAILED;
        }

	if (bind == true) {
		retcode = SQLNumResultCols(hstmt, &cols);

		if (retcode != SQL_SUCCESS)
		{
		        dbError("SQLNumResultCols()", hstmt);
		        return ERR_DB_QUERYFAILED;
		} else {
			lbErrCodes err = ERR_NONE;
			
			if (boundColumns != NULL) {
				_CL_LOG << "Unbind columns of previous query." LOG_
				boundColumns--;
				boundColumns = NULL;
			}
			
			if (ReadOnlyColumns != NULL) {
				ReadOnlyColumns->deleteAll();
			}

			boundcols = new lbBoundColumns();
			boundcols->setModuleManager(*&manager, __FILE__, __LINE__);

			QI(boundcols, lb_I_ColumnBinding, boundColumns)
		
			boundColumns->setQuery(this, ReadOnlyColumns.getPtr());
			
			prepareFKList();
		}
		
		databound = 1;
	} else {
		_CL_LOG << "Do not prebind columns. You must call bind()." LOG_
	}

	return ERR_NONE;
}
/*...e*/
/*...svirtual char\42\ LB_STDCALL lbQuery\58\\58\getAsString\40\int column\41\:0:*/
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
				UAP(lb_I_KeyBase, bkey)
				UAP(lb_I_Unknown, ustring)
				QI(key, lb_I_KeyBase, bkey)
				QI(string, lb_I_Unknown, ustring)
				
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
	UAP(lb_I_KeyBase, bkey)
	QI(key, lb_I_KeyBase, bkey)
	
	UAP(lb_I_Unknown, uk)

	uk = boundColumns->getElement(&bkey);

	UAP(lb_I_String, string)
	QI(uk, lb_I_String, string)

	return string->getData();
}
#endif
#ifndef UNBOUND
lb_I_String* LB_STDCALL lbQuery::getAsString(int column) {
	UAP_REQUEST(manager.getPtr(), lb_I_String, string)
	
	// Caller get's an owner
	string++;
	
	boundColumns->getString(column, *&string);
	
	return string.getPtr();
}

lb_I_String* LB_STDCALL lbQuery::getAsString(const char* column) {
	UAP_REQUEST(manager.getPtr(), lb_I_String, string)
	
	// Caller get's an owner
	string++;
	
	boundColumns->getString(column, *&string);
	
	return string.getPtr();
}

lb_I_Long* LB_STDCALL lbQuery::getAsLong(int column) {
	UAP_REQUEST(manager.getPtr(), lb_I_Long, value)
	// Caller get's an owner
	value++;
	boundColumns->getLong(column, *&value);
	return value.getPtr();
}

#endif
/*...e*/
/*...sint LB_STDCALL lbQuery\58\\58\getColumns\40\\41\:0:*/
int LB_STDCALL lbQuery::getColumns() {
	SWORD count = 0;
	retcode = SQLNumResultCols(hstmt, &count);

	if (retcode == SQL_SUCCESS) return count;
	
	//dbError("lbQuery::getColumns()", hstmt);
	
	_LOG << "lbQuery::getColumns() failed!" LOG_
	
	return count;
}
/*...e*/
/*...sbool LB_STDCALL lbQuery\58\\58\hasColumnName\40\char\42\ name\41\:0:*/
bool LB_STDCALL lbQuery::hasColumnName(char* name) {
	if ((boundColumns != NULL) && (boundColumns->getColumnIndex(name) != -1)) return true; 
	return false;
}
/*...e*/

/*...sint LB_STDCALL lbQuery\58\\58\hasFKColumn\40\char\42\ FKName\41\:0:*/
int LB_STDCALL lbQuery::hasFKColumn(char* FKName) {
	lbErrCodes err = ERR_NONE;

	if ((FKName != NULL) && (strlen(FKName) > 0)) {

		if (skipFKCollections == 1) {
			_CL_VERBOSE << "Warning: Skipping for checking of foreign columns." LOG_
			return 0;
		}
	
		UAP(lb_I_KeyBase, key)
		UAP_REQUEST(manager.getPtr(), lb_I_String, s)
	
		s->setData(FKName);
		s->toLower();
		
		QI(s, lb_I_KeyBase, key)
	
		if (ForeignColumns->exists(&key) == 1) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_String, s)
			
			uk = ForeignColumns->getElement(&key);
			QI(uk, lb_I_String, s)
			
			// Check, if FKName does not point from other table to me
			if (strcmp(s->charrep(), getTableName(FKName)) != 0) return 1;
		}

	}

	return 0;
}
/*...e*/
/*...sint LB_STDCALL lbQuery\58\\58\getFKColumns\40\\41\:0:*/
int LB_STDCALL lbQuery::getFKColumns() {
	if (skipFKCollections == 1) return 0;

	return ForeignColumns->Count();
}
/*...e*/
/*...slb_I_String\42\ LB_STDCALL lbQuery\58\\58\getFKColumn\40\int pos\41\:0:*/
lb_I_String* LB_STDCALL lbQuery::getFKColumn(int pos) {
	lbErrCodes err = ERR_NONE;
	
	if (skipFKCollections == 1) return NULL;
	
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_String,  s)
	
	// getKeyAt returns it's reference.
	// Bugfix: increment reference here.
	// Implementation of lb_I_Element should be fixed.

	// It is fixed now.
	
	uk = ForeignColumns->getKeyAt(pos);
	
	QI(uk, lb_I_String, s)
	s++;
	
	return s.getPtr();
}
/*...e*/
/*...slb_I_String\42\ LB_STDCALL lbQuery\58\\58\getFKColumn\40\char\42\ table\44\ char\42\ primary\41\:0:*/
lb_I_String* LB_STDCALL lbQuery::getFKColumn(char* table, char* primary) {
	lbErrCodes err = ERR_NONE;

	_CL_LOG << "lbQuery::getFKColumn('" << table << "', '" << primary << "') called." LOG_
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, PKTable_PKName)
	UAP(lb_I_KeyBase, key_PKTable_PKName)
	
	*PKTable_PKName = table;
	*PKTable_PKName += primary;
	
	QI(PKTable_PKName, lb_I_KeyBase, key_PKTable_PKName)

	UAP(lb_I_Unknown, result)
	UAP(lb_I_String, FKName)

	if (mapPKTable_PKColumns_To_FKName == NULL) {
		_CL_LOG << "Error: There were no foreign keys collected. (" << table << ", " << primary << ")" LOG_
		return NULL;
	}

	result = mapPKTable_PKColumns_To_FKName->getElement(&key_PKTable_PKName);

	if (result == NULL) {
		while (mapPKTable_PKColumns_To_FKName->hasMoreElements() == 1) {
			UAP(lb_I_KeyBase, key)
			UAP(lb_I_Unknown, value)
			UAP(lb_I_String, s)
			
			value = mapPKTable_PKColumns_To_FKName->nextElement();
			key = mapPKTable_PKColumns_To_FKName->currentKey();
			QI(value, lb_I_String, s)
			
			_LOG << "Element in 'mapPKTable_PKColumns_To_FKName' : " << s->charrep() << "' with key '" << key->charrep() << "'" LOG_
		}
		
		return NULL;
	}

	QI(result, lb_I_String, FKName)

	FKName++;
	
	return FKName.getPtr();
}
/*...e*/
/*...slb_I_String\42\ LB_STDCALL lbQuery\58\\58\getPKTable\40\char const \42\ FKName\41\:0:*/
lb_I_String* LB_STDCALL lbQuery::getPKTable(char const * FKName) {
	lbErrCodes err = ERR_NONE;


	if (skipFKCollections == 1) {
		_CL_VERBOSE << "Warning: Skipping for checking of foreign columns." LOG_
		return NULL;
	}
	
	UAP(lb_I_KeyBase, key)
	UAP_REQUEST(manager.getPtr(), lb_I_String, s)
	
	s->setData(FKName);
	s->toLower();
	
	QI(s, lb_I_KeyBase, key)
	
	if (ForeignColumns->exists(&key) == 1) {
		UAP(lb_I_String, string)
		UAP(lb_I_Unknown, uk)
		
		uk = ForeignColumns->getElement(&key)->clone(__FILE__, __LINE__);
		
		QI(uk, lb_I_String, string)

		string++;
		
		return string.getPtr();
	}

	return NULL;
}
/*...e*/
/*...slb_I_String\42\ LB_STDCALL lbQuery\58\\58\getPKColumn\40\char const \42\ FKName\41\:0:*/
lb_I_String* LB_STDCALL lbQuery::getPKColumn(char const * FKName) {
	unsigned char*   szTable = NULL;     /* Table to display   */

	UCHAR   szPkTable[TAB_LEN];  /* Primary key table name */
	UCHAR   szFkTable[TAB_LEN];  /* Foreign key table name */
	UCHAR   szPkCol[COL_LEN];  /* Primary key column   */
	UCHAR   szFkCol[COL_LEN];  /* Foreign key column   */

	SQLHSTMT         hstmt;
	SQLINTEGER      cbPkTable, cbPkCol, cbFkTable, cbFkCol, cbKeySeq;
	SQLSMALLINT      iKeySeq;
	SQLRETURN         retcode;

/*...sOriginally for windows \40\foreign table\41\:8:*/
	retcode = SQLAllocStmt(hdbc, &hstmt); /* Statement handle */

	if (retcode != SQL_SUCCESS)
	{
		_dbError_DBC("SQLAllocStmt()", hdbc);
	}

/*...sBind columns:16:*/
	SQLBindCol(hstmt, 3, SQL_C_CHAR, szPkTable, TAB_LEN, &cbPkTable);
	SQLBindCol(hstmt, 4, SQL_C_CHAR, szPkCol, COL_LEN, &cbPkCol);
	SQLBindCol(hstmt, 5, SQL_C_CHAR, &iKeySeq, TAB_LEN, &cbKeySeq); //SSHORT
	SQLBindCol(hstmt, 7, SQL_C_CHAR, szFkTable, TAB_LEN, &cbFkTable);
	SQLBindCol(hstmt, 8, SQL_C_CHAR, szFkCol, COL_LEN, &cbFkCol);
/*...e*/

	char* temp = (char*) getTableName(getColumnName(1));
	szTable = (unsigned char*) malloc(strlen(temp)+1);
	szTable[0] = 0;
	strcpy((char*) szTable, temp);
	
	if (strlen((char* const) szTable) > 99) {
		_CL_VERBOSE << "ERROR: Possible buffer overflows!" LOG_
	}

	_CL_VERBOSE << "Try to get foreign keys with '" << temp << "' as foreign table" LOG_
	
	retcode = SQLForeignKeys(hstmt,
	         NULL, 0,      /* Primary catalog   */
	         NULL, 0,      /* Primary schema   */
	         NULL, 0,      /* Primary table   */
	         NULL, 0,      /* Foreign catalog   */
	         NULL, 0,      /* Foreign schema   */
	         szTable, SQL_NTS); /* Foreign table   */

	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)) {
		_CL_LOG << "SQLForeignKeys(...) failed!" LOG_
	}

	while ((retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO)) {

	/* Fetch and display the result set. This will be all of the */
	/* foreign keys in other tables that refer to the ORDERS */
	/* primary key.                 */

	   retcode = SQLFetch(hstmt);

	   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
	      lbErrCodes err = ERR_NONE;
	      UAP_REQUEST(manager.getPtr(), lb_I_String, comp)
	      UAP_REQUEST(manager.getPtr(), lb_I_String, comp1)
	      
	      /// \todo Think about case sensity.
	      
	      if (isVerbose()) printf("%-s ( %-s ) <-- %-s ( %-s ) compare foreign column with: %s\n", szPkTable, szPkCol, szFkTable, szFkCol, FKName);
	      
	      *comp = (char*) szFkCol;
	      comp->toLower();
	      
	      *comp1 = FKName;
	      comp1->toLower();
	      
	      if (strcmp(comp1->charrep(), comp->charrep()) == 0) {
	      	UAP_REQUEST(manager.getPtr(), lb_I_String, c)
	      	
	      	c->setData((char const*) szPkCol);
	      	c++;
	      	free(szTable);
	      	SQLFreeStmt(hstmt, SQL_DROP);
	      	return c.getPtr();
	      }
	   } else {
	   	dbError("SQLFetch(hstmt) in getPKColumn()", hstmt);
	   }
	}

	free(szTable);

	/* Close the cursor (the hstmt is still allocated). */

	SQLFreeStmt(hstmt, SQL_DROP);
	
	return NULL;
/*...e*/
}
/*...e*/

/*...svoid LB_STDCALL lbQuery\58\\58\prepareFKList\40\\41\:0:*/
void LB_STDCALL lbQuery::prepareFKList() {
	#define TAB_LEN 100
	#define COL_LEN 100
	
	void* that = this;

	if (this == NULL) {
		_CL_LOG << "Fatal: Called member function on invalid object (lbQuery::prepareFKList(), NULL) !" LOG_ 
	}

	if (!_TRMemValidate(this)) {
		lbBreak();
	}

	if (mapPKTable_PKColumns_To_FKName == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, mapPKTable_PKColumns_To_FKName)
	} else {
		mapPKTable_PKColumns_To_FKName->deleteAll();
	}


	if (ForeignColumns == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, ForeignColumns)
	} else {
		ForeignColumns->deleteAll();
	}

	if (skipFKCollections == 1) {
	    _CL_VERBOSE << "==========================================" LOG_
	    _CL_VERBOSE << "Do not collect foreign column information!" LOG_
	    _CL_VERBOSE << "==========================================" LOG_

	    return;
	}

/*...sOriginally for windows \40\primary table\41\:8:*/
/*...sVariables:16:*/
	unsigned char*   szTable = NULL;     /* Table to display   */

	UCHAR   szPkTable[TAB_LEN];  /* Primary key table name */
	UCHAR   szFkTable[TAB_LEN];  /* Foreign key table name */
	UCHAR   szPkCol[COL_LEN];  /* Primary key column   */
	UCHAR   szFkCol[COL_LEN];  /* Foreign key column   */

	char    buffer1[100] = "";
	SQLHSTMT         hstmt;
	char    buffer2[100] = "";

	SQLINTEGER      cbPkTable = TAB_LEN;
	SQLINTEGER 	cbPkCol = TAB_LEN;
	SQLINTEGER	cbFkTable = TAB_LEN;
	SQLINTEGER	cbFkCol = TAB_LEN;
	SQLINTEGER	cbKeySeq = TAB_LEN;
	SQLSMALLINT      iKeySeq;
	SQLRETURN         retcode;
/*...e*/

	retcode = SQLAllocStmt(hdbc, &hstmt); /* Statement handle */

	if (retcode != SQL_SUCCESS)
	{
	        _dbError_DBC("SQLAllocStmt()", hdbc);
	}

/*...sBind columns:16:*/
	SQLBindCol(hstmt, 3, SQL_C_CHAR, szPkTable, TAB_LEN, &cbPkTable);
	SQLBindCol(hstmt, 4, SQL_C_CHAR, szPkCol, COL_LEN, &cbPkCol);
	SQLBindCol(hstmt, 5, SQL_C_CHAR, &iKeySeq, TAB_LEN, &cbKeySeq); //SSHORT
	SQLBindCol(hstmt, 7, SQL_C_CHAR, szFkTable, TAB_LEN, &cbFkTable);
	SQLBindCol(hstmt, 8, SQL_C_CHAR, szFkCol, COL_LEN, &cbFkCol);
/*...e*/

	char* temp = (char*) getTableName(getColumnName(1));
	szTable = (unsigned char*) malloc(strlen(temp)+1);
	szTable[0] = 0;
	strcpy((char*) szTable, temp);
	
	if (strlen((char* const) szTable) > 99) {
		_LOG << "ERROR: Possible buffer overflows!" LOG_
	}

	_CL_VERBOSE << "Get foreign keys for '" << szTable << "'" LOG_

/*...e*/

/*...sOriginally for windows \40\foreign table\41\:8:*/
	_CL_VERBOSE << "Try to get foreign keys with '" << temp << "' as foreign table" LOG_
	
	retcode = SQLForeignKeys(hstmt,
	         NULL, 0,      /* Primary catalog   */
	         NULL, 0,      /* Primary schema   */
	         NULL, 0,      /* Primary table   */
	         NULL, 0,      /* Foreign catalog   */
	         NULL, 0,      /* Foreign schema   */
	         szTable, SQL_NTS); /* Foreign table   */

	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)) {
		_LOG << "SQLForeignKeys(...) failed!" LOG_
	}


	while ((retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO)) {

	/* Fetch and display the result set. This will be all of the */
	/* foreign keys in other tables that refer to the ORDERS */
	/* primary key.                 */

	   retcode = SQLFetch(hstmt);
	   
	   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
	      lbErrCodes err = ERR_NONE;

	      //if (isVerbose()) 
	      printf("%s ( %s ) <-- %s ( %s )\n", szPkTable, szPkCol, szFkTable, szFkCol);
	      
	      
	      UAP_REQUEST(manager.getPtr(), lb_I_String, FKName)
	      UAP_REQUEST(manager.getPtr(), lb_I_String, PKTable)
	      
	      UAP_REQUEST(manager.getPtr(), lb_I_String, PKTable_PKName)
	      
	      FKName->setData((char*) szFkCol);
	      PKTable->setData((char*) szPkTable);

	      FKName->toLower();
	      PKTable->toLower();
	      
	      UAP(lb_I_Unknown, uk_PKTable)
	      UAP(lb_I_KeyBase, key_FKName)
	      
	      UAP(lb_I_Unknown, uk_FKName)
	      UAP(lb_I_KeyBase, key_PKTable_PKName)
	      
	      QI(FKName, lb_I_KeyBase, key_FKName)
	      QI(PKTable, lb_I_Unknown, uk_PKTable)

	      ForeignColumns->insert(&uk_PKTable, &key_FKName);
	      
	      *PKTable_PKName = (char*) szPkTable;
	      *PKTable_PKName += (char*) szPkCol;
	      
	      PKTable_PKName->toLower();
	      
	      QI(PKTable_PKName, lb_I_KeyBase, key_PKTable_PKName)
	      QI(FKName, lb_I_Unknown, uk_FKName)

	      _CL_VERBOSE << "Insert map for '" << key_PKTable_PKName->charrep() << "' to '" << FKName->charrep() << "'" LOG_
	      
	      mapPKTable_PKColumns_To_FKName->insert(&uk_FKName, &key_PKTable_PKName);
	   }
	}

	if (this != that) {
		_CL_LOG << "Fatal: Short before bug (lbQuery::prepareFKList(), NULL) !" LOG_ 
	}

	/* Close the cursor (the hstmt is still allocated). */

	if (!_TRMemValidate(this)) {
		lbBreak();
	}
	

	SQLFreeStmt(hstmt, SQL_DROP);

	free(szTable);

/*...e*/


// MySQL does not yet support Foreign keys or my tests with type INNODB doesn't work
// Fallback to use manual queries. (Using MySQL-Max solved that)

	if (ForeignColumns->Count() == 0) {		
/*...sOriginally for Linux:8:*/
	lbErrCodes err = ERR_NONE;
	
	char buffer[1000] = "";
	
	/* For each column in the table for the current query try to select the PKTable and associate it to
	   the foreign column.
	 */

	_CL_VERBOSE << "lbQuery::prepareFKList() tries to read foreign column information from table" LOG_
	
	char* table = getTableName(getColumnName(1));
	
	lb_I_Module* m = getModuleManager();

        UAP_REQUEST(m, lb_I_Database, db)
        db->init();
	
        char* user = getenv("lbDMFUser");
        char* pass = getenv("lbDMFPasswd");
	
        if (!user) user = "dba";
        if (!pass) pass = "trainres";
	
        db->connect("lbDMF", "lbDMF", user, pass);

	
	for (int i = 1; i <= getColumns(); i++) { 
    	    UAP(lb_I_Query, q)

	    buffer[0] = 0;
	    
	    char* column = strdup(getColumnName(i));

	    sprintf(buffer, "select PKTable, PKName from ForeignKey_VisibleData_Mapping where FKTable = '%s' and FKName = '%s'", table, column);

	    _CL_LOG << "Query: " << buffer LOG_

	    q = db->getQuery("lbDMF", 0);

	    skipFKCollections = 1;
	    err = q->query(buffer);
	    skipFKCollections = 0;

	    if ((err != ERR_NONE) || (err != WARN_DB_NODATA)) {
				_CL_VERBOSE << "No foreign key to primary data mapping found." LOG_
		} else {
			err = q->first();

			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				UAP_REQUEST(manager.getPtr(), lb_I_String, FKName)
				UAP_REQUEST(manager.getPtr(), lb_I_String, PKTable)
				UAP_REQUEST(manager.getPtr(), lb_I_String, PKName)
				UAP_REQUEST(manager.getPtr(), lb_I_String, PKTable_PKName)
	
				UAP_REQUEST(manager.getPtr(), lb_I_String, PKColumn)
	
				PKTable = q->getAsString(1);
				PKName = q->getAsString(2);
		
				FKName->setData(column);
				FKName->toLower();
				PKTable->toLower();
		
		
				UAP(lb_I_Unknown, uk_PKTable)
				UAP(lb_I_KeyBase, key_FKName)

				UAP(lb_I_Unknown, uk_FKName)
				UAP(lb_I_KeyBase, key_PKTable_PKName)
	      
				QI(FKName, lb_I_KeyBase, key_FKName)
				QI(PKTable, lb_I_Unknown, uk_PKTable)


				//if (isVerbose())
					printf("%-s ( %-s ) <-- %-s ( %-s )\n", PKTable->charrep(), PKName->charrep(), table, FKName->charrep());

				ForeignColumns->insert(&uk_PKTable, &key_FKName);
	        
				*PKTable_PKName = PKTable->charrep();
				PKColumn = getPKColumn(FKName->charrep());
				*PKTable_PKName += PKColumn->charrep();

				QI(PKTable_PKName, lb_I_KeyBase, key_PKTable_PKName)
				QI(FKName, lb_I_Unknown, uk_FKName)

				PKTable_PKName->toLower();

				_CL_VERBOSE << "Insert map for '" << key_PKTable_PKName->charrep() << 
					"' to '" << FKName->charrep() << "'" LOG_

				mapPKTable_PKColumns_To_FKName->insert(&uk_FKName, &key_PKTable_PKName);
	        
			} else {
				_CL_VERBOSE << "No foreign key to primary data mapping found." LOG_
			}
		}	    
	    free(column);
	}
/*...e*/
	}
}
/*...e*/
/*...sint LB_STDCALL lbQuery\58\\58\getPKColumns\40\\41\:0:*/
int LB_STDCALL lbQuery::getPKColumns() {
	
	if (primaryColumns == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, primaryColumns)
        } else {
                primaryColumns->deleteAll();
        }

	unsigned char*   szTable = NULL;     /* Table to display   */

	UCHAR   szPkTable[TAB_LEN];  /* Primary key table name */
	UCHAR   szFkTable[TAB_LEN];  /* Foreign key table name */
	UCHAR   szPkCol[COL_LEN];  /* Primary key column   */
	UCHAR   szFkCol[COL_LEN];  /* Foreign key column   */

	SQLHSTMT         hstmt;
	SQLINTEGER      cbPkTable, cbPkCol, cbFkTable, cbFkCol, cbKeySeq;
	SQLSMALLINT      iKeySeq;
	SQLRETURN         retcode;

	retcode = SQLAllocStmt(hdbc, &hstmt); /* Statement handle */

	SQLBindCol(hstmt, 3, SQL_C_CHAR, szPkTable, TAB_LEN, &cbPkTable);
	if (retcode != SQL_SUCCESS)
	{
	        dbError("SQLAllocStmt()", hstmt);
	}

	SQLBindCol(hstmt, 4, SQL_C_CHAR, szPkCol, COL_LEN, &cbPkCol);
	if (retcode != SQL_SUCCESS)
	{
	        dbError("SQLAllocStmt()", hstmt);
	}

	SQLBindCol(hstmt, 5, SQL_C_SSHORT, &iKeySeq, TAB_LEN, &cbKeySeq);
	if (retcode != SQL_SUCCESS)
	{
	        dbError("SQLAllocStmt()", hstmt);
	}
	
	_CL_VERBOSE << "Call getTableName('" << getColumnName(1) << "')" LOG_

	char* temp = (char*) getTableName(getColumnName(1));
	szTable = (unsigned char*) malloc(strlen(temp)+1);
	szTable[0] = 0;
	strcpy((char*) szTable, temp);
	
	retcode = SQLPrimaryKeys(hstmt,
	         NULL, 0,      		/* Primary catalog   */
	         NULL, 0,      		/* Primary schema   */
	         szTable, SQL_NTS);	/* Primary table   */

	int columns = 0;

	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO))
	{
		_CL_LOG << "lbQuery::getPKColumns() SQLPrimaryKeys failed." LOG_
		
		dbError("SQLPrimaryKeys()", hstmt);
	}
	

	while ((retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO)) {

	/* Fetch and display the result set. This will be all of the */
	/* foreign keys in other tables that refer to the ORDERS */
	/* primary key.                 */

	   retcode = SQLFetch(hstmt);
	   
	   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		lbErrCodes err = ERR_NONE;

		printf("%s ( %s ) seq: %hd\n", szPkTable, szPkCol, iKeySeq);
	      
		columns++;
	      
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, KeyPosition)
		UAP_REQUEST(manager.getPtr(), lb_I_String, PKName)
	      
		KeyPosition->setData(columns);
		PKName->setData((char*) szPkCol);
	      
		UAP(lb_I_Unknown, uk_PKName)
		UAP(lb_I_KeyBase, key_Pos)
		
		QI(PKName, lb_I_Unknown, uk_PKName)
		QI(KeyPosition, lb_I_KeyBase, key_Pos)


		// Store the position as they appear
		primaryColumns->insert(&uk_PKName, &key_Pos);
	   }
	}

	free(szTable);

	/* Close the cursor (the hstmt is still allocated). */

	SQLFreeStmt(hstmt, SQL_DROP);
	
	return columns;
}
/*...e*/
/*...slb_I_String\42\ LB_STDCALL lbQuery\58\\58\getPKColumn\40\int pos\41\:0:*/
lb_I_String* LB_STDCALL lbQuery::getPKColumn(int pos) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, Position)

	UAP(lb_I_KeyBase, key_Position)
	QI(Position, lb_I_KeyBase, key_Position)

	Position->setData(pos);

	if (primaryColumns->exists(&key_Position) != 0) {
		UAP(lb_I_String, column)
		UAP(lb_I_Unknown, uk)
		
		uk = primaryColumns->getElement(&key_Position);
		QI(uk, lb_I_String, column)
		column++;
		
		return column.getPtr();
	
	}

	return NULL;
}
/*...e*/

bool LB_STDCALL lbQuery::isNullable(int pos) {
	return boundColumns->isNullable(pos);
}

bool	LB_STDCALL lbQuery::isNullable(char const * name) {
	return boundColumns->isNullable(name);
}

bool LB_STDCALL lbQuery::isNull(int pos) {
	return boundColumns->isNull(pos);
}

bool	LB_STDCALL lbQuery::isNull(char const * name) {
	return boundColumns->isNull(name);
}

bool	LB_STDCALL lbQuery::setNull(int pos, bool b) {
	return boundColumns->setNull(pos, b);
}

bool	LB_STDCALL lbQuery::setNull(char const * name, bool b) {
	return boundColumns->setNull(name, b);
}

/*...slb_I_Query\58\\58\lbDBColumnTypes LB_STDCALL lbQuery\58\\58\getColumnType\40\int pos\41\:0:*/
lb_I_Query::lbDBColumnTypes LB_STDCALL lbQuery::getColumnType(int pos) {
	return boundColumns->getColumnType(pos);
}
/*...e*/
/*...slb_I_Query\58\\58\lbDBColumnTypes LB_STDCALL lbQuery\58\\58\getColumnType\40\char\42\ name\41\:0:*/
lb_I_Query::lbDBColumnTypes LB_STDCALL lbQuery::getColumnType(char* name) {
	return boundColumns->getColumnType(name);
}
/*...e*/
/*...svoid LB_STDCALL lbQuery\58\\58\setReadonly\40\char\42\ column\44\ bool updateable\41\:0:*/
void LB_STDCALL lbQuery::setReadonly(char* column, bool updateable) {
	lbErrCodes err = ERR_NONE;

	if (updateable == true) 
		_CL_LOG << "lbQuery::setReadonly(" << column << ", TRUE)" LOG_
	else
		_CL_LOG << "lbQuery::setReadonly(" << column << ", FALSE)" LOG_
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, col)
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, uk)
	
	QI(col, lb_I_KeyBase, key)
	QI(col, lb_I_Unknown, uk)
	
	col->setData(column);

	if (ReadOnlyColumns == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, ReadOnlyColumns)
	}

	if (!ReadOnlyColumns->exists(&key) && updateable == true) {
		_CL_LOG << "lbQuery::setReadonly(...) calls ReadOnlyColumns->insert(...)." LOG_
		ReadOnlyColumns->insert(&uk, &key);
	}
	
	if (ReadOnlyColumns->exists(&key) && updateable == false) {
		_CL_LOG << "lbQuery::setReadonly(...) calls ReadOnlyColumns->remove(&key)." LOG_
		ReadOnlyColumns->remove(&key);
	}

	if (boundColumns.getPtr() != NULL) {
		_CL_LOG << "lbQuery::setReadonly(...) calls boundColumns->setReadonly(...)." LOG_
		boundColumns->setReadonly(column, updateable);
	}
	
	_CL_LOG << "lbQuery::setReadonly(...) returns." LOG_
}
/*...e*/
/*...sbool LB_STDCALL lbQuery\58\\58\getReadonly\40\char\42\ column\41\:0:*/
bool LB_STDCALL lbQuery::getReadonly(char* column) {
	return boundColumns->getReadonly(column);
}
/*...e*/
/*...schar\42\ LB_STDCALL lbQuery\58\\58\getTableName\40\char\42\ columnName\41\:0:*/
char* LB_STDCALL lbQuery::getTableName(char* columnName) {
		
		if (columnName == NULL) {
			_LOG << "Error: lbQuery::getTableName(char* columnName) called with a NULL pointer as parameter." LOG_
			return "";
		}
		
		if (strlen(columnName) == 0) {
			_LOG << "Error: lbQuery::getTableName(char* columnName) called with an empty string as parameter." LOG_
			return "";
		}
		
		SQLHSTMT	StatementHandle;
		SQLUSMALLINT	ColumnNumber;
		SQLUSMALLINT	FieldIdentifier;
		SQLPOINTER	CharacterAttributePtr;
		SQLSMALLINT	BufferLength;
		SQLSMALLINT	StringLengthPtr = 0;
		SQLPOINTER	NumericAttributePtr;
		
		SQLINTEGER	Int = 0;
		
		CharacterAttributePtr = (void*) malloc(101);
		memset(CharacterAttributePtr, 0, 101);

		NumericAttributePtr = &Int;
		
		SQLRETURN retcode;
		int index = boundColumns->getColumnIndex(columnName);

		SQLUINTEGER    fFuncs;
		
		retcode = SQLGetInfo(hdbc, SQL_IDENTIFIER_CASE, (SQLPOINTER)&fFuncs, sizeof(fFuncs), NULL);
	
		retcode = SQLColAttribute(
				  hstmt,
				  index, 
				  SQL_DESC_TABLE_NAME, 
				  // SQL_DESC_BASE_TABLE_NAME would make problems
				  // under Mac OS X and Linux
				  CharacterAttributePtr,
				  100,
				  &StringLengthPtr,
				  NumericAttributePtr);
			
		if ((retcode == SQL_ERROR) || (retcode == SQL_SUCCESS_WITH_INFO)) {
			_CL_LOG << "ERROR: SQLColAttribute(...) failed." LOG_
			dbError("SQLColAttribute()", hstmt);
		}
		
		if (lpszTable == NULL) {
			int _size = strlen((char*) CharacterAttributePtr)+1;
			lpszTable = (char*) malloc(_size);
			lpszTable[0] = 0;
			strcpy(lpszTable, (char*) CharacterAttributePtr);
			lpszSize = _size;
		} else {
			int _size = strlen((char*) CharacterAttributePtr)+1;
			if (lpszSize < _size) {
				free(lpszTable);
				lpszTable = (char*) malloc(_size);
				lpszSize = _size;
			}
		
			lpszTable[0] = 0;
			strcpy((char*) lpszTable, (char*) CharacterAttributePtr);
		}
		
		free(CharacterAttributePtr);
		
		
	if (strcmp(lpszTable, "") == 0) {
		// Quick hack

		char* buf = strdup(szSql);
		char* t = strtok(buf, " ,");
		
		while (t) {
			t = strtok(NULL, " ,");
			
			if (strcmp(t, "from") == 0) break;
		}

		t = strtok(NULL, " ,");

		printf("%s\n", t);
		
		strcpy((char*) lpszTable, t);
		free(buf);
	}
		
		
		
		return lpszTable;
	}
/*...e*/
/*...schar\42\ LB_STDCALL lbQuery\58\\58\getColumnName\40\int col\41\:0:*/
char lbQuery_column_Name[100] = "";

char* LB_STDCALL lbQuery::getColumnName(int col) {
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
		_CL_LOG << "Error: lbQuery::getColumnName('" << col << "') failed. (" << ColumnName << ")" LOG_
	}
	
	if (strchr((char const*) ColumnName, '.') != 0) {
		strcpy(lbQuery_column_Name, (char*) (strchr((char const*) ColumnName, '.') + 1));
	} else {
		strcpy(lbQuery_column_Name, (char*) ColumnName);
	}
	
	return lbQuery_column_Name;
}
/*...e*/

bool LB_STDCALL lbQuery::isFirst() {
	return fetchstatus == -1;
}

bool LB_STDCALL lbQuery::isLast() {
	return fetchstatus == 1;
}



/*...svoid LB_STDCALL lbQuery\58\\58\reopen\40\\41\:0:*/
void LB_STDCALL lbQuery::reopen() {
	RETCODE retcode;
	
	if (hstmt != NULL) {
	        retcode = SQLFreeStmt (hstmt, SQL_CLOSE);
	}

	retcode = SQLExecDirect(hstmt, (unsigned char*) szSql, SQL_NTS);

	if (retcode != SQL_SUCCESS) dbError("SQLExecDirect()", hstmt);

	boundColumns->rebind();
	if (cursor > 0 ) 
		if (absolute(cursor) == ERR_DB_NODATA) {
			haveData = false;
		} else {
			haveData = true;
		}
	else
		first();
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbQuery\58\\58\absolute\40\int pos\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::absolute(int pos) {
        UWORD   RowStat[20];
        UDWORD  RowsFetched = 0;

	cursor = 1;

	memset(&RowStat[0], sizeof(UWORD)*20, 0);

        // Indicate, that data must prebound to a buffer
        databound = 0;

	fetchstatus = -1;

#ifndef USE_FETCH_SCROLL
        retcode = SQLExtendedFetch(hstmt, SQL_FETCH_ABSOLUTE, pos, &RowsFetched, &RowStat[0]);

	CHECK_ROWSTAT()
	
	if (peeking == false) {
		if (retcode == SQL_SUCCESS) {
			cursor = pos;
		        return ERR_NONE;
		}
	        
	        if (retcode == SQL_NO_DATA) return last();
	}
#endif

#ifdef USE_FETCH_SCROLL
	retcode = SQLFetchScroll(hstmt, SQL_FETCH_FIRST, 0);
#endif
	if (retcode == SQL_NO_DATA) return ERR_DB_NODATA;
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
                _LOG << "lbQuery::first(): Error while fetching next row" LOG_
                dbError("SQLExtendedFetch()", hstmt);
                
                // Unsave !!
                if (retcode == SQL_SUCCESS_WITH_INFO) return ERR_NONE;
                
                return ERR_DB_FETCHFIRST;
        }
		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, &RowStat[0]);
		
		//CHECK_ROWSTAT()
		
		if (retcode == SQL_NO_DATA) {
			retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, &RowStat[0]);
			
			//CHECK_ROWSTAT()
			
			if (retcode == SQL_NO_DATA) {
				_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
				fetchstatus = 2;
				return ERR_DB_NODATA;
			}
			fetchstatus = 1;
			return WARN_DB_NODATA;
		} else {
			retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, &RowStat[0]);
			
			//CHECK_ROWSTAT()
			
			if (retcode == SQL_NO_DATA) {
				_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
				fetchstatus = 2;
				return ERR_DB_NODATA;
			}
			fetchstatus = 0;
			return ERR_NONE;
		}
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbQuery\58\\58\first\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::first() {
	UWORD   RowStat[20];
	UDWORD  RowsFetched = 0;
	
	cursor = 1;
	
	memset(&RowStat[0], 0, sizeof(UWORD)*20);
	
	// Indicate, that data must prebound to a buffer
	databound = 0;
	
	fetchstatus = -1;
	
#ifndef USE_FETCH_SCROLL
	retcode = SQLExtendedFetch(hstmt, SQL_FETCH_FIRST, 0, &RowsFetched, &RowStat[0]);
	
	CHECK_ROWSTAT()
		
	if (peeking == false) {
		if (retcode == SQL_NO_DATA) {
			_dataFetched = false;
			return ERR_DB_NODATA;
		} else {
			_dataFetched = true;
			return ERR_NONE;
		}
	}
#endif
	
#ifdef USE_FETCH_SCROLL
	retcode = SQLFetchScroll(hstmt, SQL_FETCH_FIRST, 0);
#endif
	if (retcode == SQL_NO_DATA) {
		_dataFetched = false;
		return ERR_DB_NODATA;
	}
	
	if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
		_LOG << "lbQuery::first(): Error while fetching next row" LOG_
		//dbError("SQLExtendedFetch()", hstmt);
		
		// Unsave !!
		if (retcode == SQL_SUCCESS_WITH_INFO) {
			_dataFetched = true;
			return ERR_NONE;
		}
		_dataFetched = false;
		return ERR_DB_FETCHFIRST;
	}
	retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, &RowStat[0]);
	
	if (retcode == SQL_NO_DATA) {
		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, &RowStat[0]);
		
		if (retcode == SQL_NO_DATA) {
			_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
			fetchstatus = 2;
			_dataFetched = false;
			return ERR_DB_NODATA;
		}
		fetchstatus = 1;
		_dataFetched = true;
		return WARN_DB_NODATA;
	} else {
		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, &RowStat[0]);
		
		if (retcode == SQL_NO_DATA) {
			_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
			fetchstatus = 2;
			_dataFetched = false;
			return ERR_DB_NODATA;
		}
		fetchstatus = 0;
		_dataFetched = true;
		return ERR_NONE;
	}
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\next\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::next() {
	UWORD   RowStat[20];
	UDWORD  RowsFetched = 0;
	databound = 0; // Indicate, that data must prebound to a buffer
	
	memset(&RowStat[0], 0, sizeof(UWORD)*20);
	
#ifndef USE_FETCH_SCROLL
	retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, &RowStat[0]);
	
	CHECK_ROWSTAT()
		
		if (peeking == false) {
			if (retcode == SQL_SUCCESS) cursor++;
			if (retcode == SQL_NO_DATA) {
				_dataFetched = false;
				return ERR_DB_NODATA;
			} else {
				_dataFetched = true;
				return ERR_NONE;
			}
		}
	
	if (retcode == SQL_NO_DATA) {
		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, &RowStat[0]);
		_dataFetched = false;		
		fetchstatus = 2; /// \todo Why was this 1 ?
		return ERR_DB_NODATA; // Really no data
	} else {
		if (retcode == SQL_SUCCESS) cursor++;
		
		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, &RowStat[0]);
		
		if (retcode == SQL_NO_DATA) {
			retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, &RowStat[0]);
			
			if (retcode == SQL_NO_DATA) {
				_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
				fetchstatus = 2;
				_dataFetched = false;
				return ERR_DB_NODATA; // ERROR: Go back to intented row failed after peek
			}
			fetchstatus = 1;
			_dataFetched = true;
			return WARN_DB_NODATA; // Warn for no more data
		} else {
			retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, &RowStat[0]);
			
			if (retcode == SQL_NO_DATA) {
				_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
				fetchstatus = 2;
				_dataFetched = false;
				return ERR_DB_NODATA;
			}
			fetchstatus = 0;
			_dataFetched = true;
			return ERR_NONE;
		}
	}
#endif
	
#ifdef USE_FETCH_SCROLL
	retcode = SQLFetchScroll(hstmt, SQL_FETCH_NEXT, 0);
#endif
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\previous\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::previous() {
	UWORD   RowStat[20];
	UDWORD  RowsFetched = 0;
	
	memset(&RowStat[0], 0, sizeof(UWORD)*20);
	
	// Indicate, that data must prebound to a buffer
	databound = 0;
	
#ifndef USE_FETCH_SCROLL
	retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, &RowStat[0]);
	
	CHECK_ROWSTAT()
		
		if (peeking == false) {
			if (retcode == SQL_SUCCESS) cursor--;
			if (retcode == SQL_NO_DATA) {
				_dataFetched = false;
				return ERR_DB_NODATA;
			} else {
				_dataFetched = true;
				return ERR_NONE;
			}
		}
	
	if (retcode == SQL_NO_DATA) {
		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, &RowStat[0]);
		_dataFetched = false;
		fetchstatus = -2; /// \todo Why was this -1 ?
		return ERR_DB_NODATA;
	} else {
		if (retcode == SQL_SUCCESS) cursor--;
		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, &RowStat[0]);
		
		if (retcode == SQL_NO_DATA) {
			retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, &RowStat[0]);
			
			if (retcode == SQL_NO_DATA) {
				_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
				fetchstatus = -2;
				_dataFetched = false;
				return ERR_DB_NODATA;
			}
			fetchstatus = -1;
			_dataFetched = true;
			return WARN_DB_NODATA;
		} else {
			retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, &RowStat[0]);
			
			if (retcode == SQL_NO_DATA) {
				_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
				fetchstatus = -2;
				_dataFetched = false;
				return ERR_DB_NODATA;
			}
			fetchstatus = 0;
			_dataFetched = true;
			return ERR_NONE;
		}
	}
#endif
	
#ifdef USE_FETCH_SCROLL
	retcode = SQLFetchScroll(hstmt, SQL_FETCH_PREV, 0);
#endif
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\last\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::last() {
	UWORD   RowStat[20];
	UDWORD  RowsFetched = 0;
	
	cursor = -1;
	
	memset(&RowStat[0], sizeof(UWORD)*20, 0);
	
	// Indicate, that data must prebound to a buffer
	databound = 0;
	
	fetchstatus = 1;
	
#ifndef USE_FETCH_SCROLL
	retcode = SQLExtendedFetch(hstmt, SQL_FETCH_LAST, 0, &RowsFetched, &RowStat[0]);
	
	CHECK_ROWSTAT()
		
		if (peeking == false) {
			if (retcode == SQL_NO_DATA) {
				_dataFetched = false;
				return ERR_DB_NODATA;
			} else {
				_dataFetched = true;
				return ERR_NONE;
			}
		}
	
#endif
#ifdef USE_FETCH_SCROLL
	retcode = SQLFetchScroll(hstmt, SQL_FETCH_LAST, 0);
#endif
	if (retcode == SQL_NO_DATA) {
		_dataFetched = false;
		return ERR_DB_NODATA;
	}
	if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
		_LOG << "lbQuery::last(): Error while fetching next row" LOG_
		dbError("SQLExtendedFetch()", hstmt);
		// Unsave !!
		if (retcode == SQL_SUCCESS_WITH_INFO) {
			_dataFetched = true;
			return ERR_NONE;
		}
		_dataFetched = false;
		return ERR_DB_FETCHLAST;
	}
	retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, &RowStat[0]);
	
	if (retcode == SQL_NO_DATA) {
		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, &RowStat[0]);
		
		if (retcode == SQL_NO_DATA) {
			_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
			fetchstatus = -2;
			_dataFetched = false;
			return ERR_DB_NODATA;
		}
		fetchstatus = -1;
		_dataFetched = true;
		return WARN_DB_NODATA;
	} else {
		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, &RowStat[0]);
		
		if (retcode == SQL_NO_DATA) {
			_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
			fetchstatus = -2;
			_dataFetched = false;
			return ERR_DB_NODATA;
		}
		fetchstatus = 0;
		_dataFetched = true;
		return ERR_NONE;
	}
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\setString\40\lb_I_String\42\ columnName\44\ lb_I_String\42\ value\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::setString(lb_I_String* columnName, lb_I_String* value) {

	if (_readonly == 1) return ERR_DB_READONLY;
	if (mode == 1) {
		boundColumns->setString(columnName->charrep(), value);
	} else {
		boundColumns->setString(columnName->charrep(), value);
	}

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\add\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::add() {

	if (_readonly == 1) return ERR_DB_READONLY;

	mode = 1;

	if (boundColumns != NULL) {
		boundColumns->invalidateData();
		boundColumns->add();
	}

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\remove\40\\41\:0:*/
//#define CREATE_DYNAMIC_STATEMENTS
lbErrCodes LB_STDCALL lbQuery::remove() {
UWORD   RowStat[20];
UDWORD  RowsFetched = 0;

/**
 * \todo Could not build delete statement without primary key included in SQL statement.
 *
 * It must be possible to avoid showing the primary key to the user, but it
 * is needed in the query to correctly build delete statements.
 *
 * Currently, CREATE_DYNAMIC_STATEMENTS is undefined and SQL_DELETE would be used.
 * It is a compromise between problems with PostgreSQL ODBC driver version 07.03.0200
 * and it's reread problem. 
 *
 * Reopen is used.
 * 
 */

	if (mode == 1) return ERR_DB_STILL_ADDING;

#ifdef CREATE_DYNAMIC_STATEMENTS
	/* As of still having problems with deleting rows with SQLSetPos
	   I try to build a delete statement dynamically. */

	UAP_REQUEST(manager.getPtr(), lb_I_String, SQL)
	UAP(lb_I_String, pk)

	int  PKCols = getPKColumns();

	pk = getPKColumn(PKCols);
	*SQL = "delete from ";
	*SQL += getTableName(pk->charrep()); // What is, if I have a joined query ?
	*SQL += " where ";

	for (int i = 1; i < PKCols; i++) {
		#define NAME_LEN 10
		
		SQLCHAR szName[NAME_LEN] = "";
		SQLINTEGER  cbName;
		
		UAP(lb_I_String, pk)
		UAP(lb_I_String, val)
		pk = getPKColumn(i);
		
		RETCODE retcode = SQLGetData(hstmt, i, SQL_C_CHAR, szName, NAME_LEN, &cbName);
		
		if (retcode != SQL_SUCCESS) {
			_CL_LOG << "ERROR: Column could not retrieved !" LOG_
		} else {
			*SQL += pk->charrep();
			*SQL += " = ";
			*SQL += (char*) szName;
			*SQL += " and ";
		}
	}
	
	UAP(lb_I_String, value)
	pk = getPKColumn(PKCols);
	value = getAsString(PKCols);
		
	*SQL += pk->charrep();
	*SQL += " = ";
	*SQL += value->charrep();

	_CL_LOG << "Created a delete statement as follows: '" << SQL->charrep() << "'" LOG_

	executeDirect(SQL->charrep());

	reopen();
	
	if (haveData == false) return ERR_DB_NODATA;
		
	return INFO_DB_REOPENED;
/*
	retcode = SQLSetPos(hstmt, 1, SQL_REFRESH, SQL_LOCK_NO_CHANGE);
	
	if (retcode != SQL_SUCCESS)
	{
	        dbError("SQLSetPos(SQL_DELETE)", hstmt);
	        _CL_LOG << "lbQuery::remove(...) deleting failed." LOG_
	        return ERR_NONE;
	}
*/
#endif

#ifndef CREATE_DYNAMIC_STATEMENTS
	retcode = SQLSetPos(hstmt, 1, SQL_DELETE, SQL_LOCK_NO_CHANGE);
	
	if (retcode != SQL_SUCCESS)
	{
	        //dbError("SQLSetPos(SQL_DELETE)", hstmt);
	        _CL_LOG << "lbQuery::remove(...) deleting failed." LOG_
	        return ERR_DB_ROWDELETED;
	}

	reopen();
	
	if (haveData == false) return ERR_DB_NODATA;

#endif
	return ERR_NONE;
}
/*...e*/
void LB_STDCALL lbQuery::setAutoRefresh(bool b) {
	_autoRefresh = b;
}
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\update\40\\41\:0:*/
//#define USE_CURRENT_OF
lbErrCodes LB_STDCALL lbQuery::update() {
	lbErrCodes err = ERR_NONE;
	#define cbMAXSQL    512
	char* CursorName = (char*) malloc(cbMAXSQL);
	CursorName[0] = 0;

	if (boundColumns != NULL) {
		boundColumns->indicateNullValues();
		boundColumns->unbindReadonlyColumns();
		
		if ((mode == 1) && (!boundColumns->hasValidData())) {
			_LOG << "Error: Query has not got valid data to be added." LOG_
			mode = 0;
			free(CursorName);
			return ERR_DB_UPDATEFAILED;
		}
	}
	
	if (mode == 1) {
	
		retcode = SQLSetPos(hstmt, 2, SQL_ADD, SQL_LOCK_NO_CHANGE);
		
		if (retcode != SQL_SUCCESS)
		{
		        //dbError("SQLSetPos()", hstmt);
		        _LOG << "lbQuery::update(...) adding failed." LOG_
		        
		        if (boundColumns != NULL) boundColumns->rebindReadonlyColumns();
				free(CursorName);
		        return ERR_DB_UPDATEFAILED;
		}

		mode = 0;
		boundColumns->finishadd();
	} else {
#ifdef USE_CURRENT_OF
/*...susing WHERE CURRENT OF \46\\46\\46\:0:*/
		// Update the existing record

		// Now I am able to begin the update statement
		
		char* buffer = (char*) malloc(2000);

		char* Update = "UPDATE ";
		char* Table  = getTableName();
		char* Set    = " SET ";
		
		
		int ci = 0;
		
		while (Table[ci] != ' ') ci++;
		
		Table[ci] = 0;
		
		SWORD    cb;
		
		
		SQLGetCursorName(hstmt, (unsigned char *) CursorName ,cbMAXSQL, &cb);
		
		
		printf("Update table '%s'\n", Table);

		/* Get the updateable columns, that I have bound.
		   That means, primary and foreign keys should not
		   updated here, because this is intented for the
		   simplest forms without dropdown boxes that may
		   handle it correctly.
		   And why should I change a primary key ?
		*/
		
		sprintf(buffer, "%s%s%s", Update, Table, Set);
		
		for (int i = 1; i <= boundColumns->getColumnCount()-1; i++) {
			UAP(lb_I_BoundColumn, bc)
			
			bc = boundColumns->getBoundColumn(i);


			if (bc == NULL) {
				_LOG << "ERROR: boundColumns->getBoundColumn(" << i << ") returns NULL pointer" LOG_
				printf("Nullpointer logged\n");
			}
			
			char* tempbuffer = strdup(buffer);
			
			UAP_REQUEST(manager.getPtr(), lb_I_String, s)
			if (s.getPtr() == NULL) printf("ERROR: s is NULL\n");
			bc->getAsString(s.getPtr(), 1);

			if (s == NULL) printf("ERROR: Null pointer in s\n");
			if (bc == NULL) printf("ERROR: Null pointer in bc\n");
			if (bc->getColumnName() == NULL) printf("ERROR: Null pointer in bc->getColumnName()\n");
			
			char* colName = bc->getColumnName()->getData();
			char* colValue = s->getData();
			sprintf(buffer, "%s%s=%s, ", tempbuffer, colName, colValue);
			free(tempbuffer);
		}
		
		{
			UAP(lb_I_BoundColumn, bc)
			bc = boundColumns->getBoundColumn(boundColumns->getColumnCount());
		
		//printf("Build set clause for %s\n", bc->getColumnName()->charrep());
			
			char* tempbuffer = strdup(buffer);
			
			UAP_REQUEST(manager.getPtr(), lb_I_String, s)
			bc->getAsString(s.getPtr(), 1);
			
//			sprintf(buffer, "%s%s=%s WHERE CURRENT OF %s", tempbuffer, bc->getColumnName()->getData(), s->getData(), CursorName);
			sprintf(buffer, "%s%s=%s", tempbuffer, bc->getColumnName()->getData(), s->getData());
			
			free(tempbuffer);
			
		}
		
printf("Query is: '%s'\n", buffer);

		retcode = SQLExecDirect(hupdatestmt, (unsigned char*) buffer, SQL_NTS);
//		             SQLExecute(hupdatestmt, (unsigned char *)buffer, SQL_NTS);
		if (retcode != SQL_SUCCESS)
		{
		        dbError("SQLExecDirect() for update", hupdatestmt);
		        _LOG << "lbQuery::update(...) failed." LOG_
				free(CursorName);
		        return ERR_DB_UPDATEFAILED;
		}

free(buffer);

/*...e*/
#endif
#ifndef USE_CURRENT_OF
		retcode = SQLSetPos(hstmt, 1, SQL_UPDATE, SQL_LOCK_NO_CHANGE);
		
		if (retcode == SQL_ERROR)
		{
		        //dbError("SQLSetPos()", hstmt);
		        _LOG << "lbQuery::update(...) updating failed." LOG_

				free(CursorName);
		        
		        if (boundColumns != NULL) boundColumns->rebindReadonlyColumns();
		        
		        return ERR_DB_UPDATEFAILED;
		}
#endif
	}

	if (boundColumns != NULL) boundColumns->rebindReadonlyColumns();

	free(CursorName);

	if (_autoRefresh) reopen();

	return ERR_NONE;
}
/*...e*/
/*...svoid LB_STDCALL lbQuery\58\\58\dbError\40\char\42\ lp\44\ HSTMT hstmt\41\:0:*/
void LB_STDCALL lbQuery::dbError(char* lp, HSTMT hstmt)
{
	SQLCHAR  SqlState[6], SQLStmt[100], Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER NativeError;
	SQLSMALLINT i, MsgLen;
	SQLRETURN  rc;

	i = 1;
	
	while ((rc = SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, i, SqlState, &NativeError,
	      Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) {
	
		_CL_LOG << "Error in lbQuery: (" << lp << ") " << 
			SqlState << ": " << (int) NativeError << " - " << Msg LOG_
		i++;
	}
}

/*...e*/
/*...e*/

/*...sclass lbBoundColumn:0:*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbBoundColumn)
        ADD_INTERFACE(lb_I_BoundColumn)
END_IMPLEMENT_LB_UNKNOWN()

void LB_STDCALL lbBoundColumn::add() {
	mode = 1;
}

void LB_STDCALL lbBoundColumn::finishadd() {
	mode = 0;
}

bool LB_STDCALL lbBoundColumn::isNull() {
	long i = 0;
	if (mode == 1) {
		i = cbBufferLength[1];
		if (i == SQL_NULL_DATA)
			return true;
		else
			return false;
	} else {
		i = cbBufferLength[0];
		if (i == SQL_NULL_DATA)
			return true;
		else
			return false;
	}
}

bool LB_STDCALL lbBoundColumn::isNullable() {
	return _isNullable;
}

bool LB_STDCALL lbBoundColumn::setNull(bool b) {
	if (b == true) {
		if (mode == 1) {
			cbBufferLength[1] = SQL_NULL_DATA;
		} else {
			cbBufferLength[0] = SQL_NULL_DATA;
		}
		_hasValidData = true;
	} else {
		if (mode == 1) {
			cbBufferLength[1] = 0;
		} else {
			cbBufferLength[0] = 0;
		}
		rebind();
		_hasValidData = false;		
	}
	
	return true;
}

/*...slb_I_Query\58\\58\lbDBColumnTypes LB_STDCALL lbBoundColumn\58\\58\getType\40\\41\:0:*/
lb_I_Query::lbDBColumnTypes LB_STDCALL lbBoundColumn::getType() {
	switch (_DataType) {
	
		case SQL_FLOAT:
			return lb_I_Query::lbDBColumnFloat;
			
		case SQL_BIT:
			return lb_I_Query::lbDBColumnBit;
			
		case SQL_DATE:
		case SQL_TYPE_DATE:
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR: 
		
			return lb_I_Query::lbDBColumnChar;
			
		case SQL_INTEGER: 
			return lb_I_Query::lbDBColumnInteger;

		case SQL_BIGINT: 
			return lb_I_Query::lbDBColumnBigInteger;
			
		case SQL_BINARY:
			return lb_I_Query::lbDBColumnBinary;
		
		default: return lb_I_Query::lbDBColumnUnknown;
	}

}
/*...e*/
/*...slbErrCodes LB_STDCALL lbBoundColumn\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbBoundColumn::setData(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_NONE;
        
        UAP(lb_I_BoundColumn, column)
        
        QI(uk, lb_I_BoundColumn, column)
	        
        /**
         * I cannot use normal use of setData, because the internal pointers would
         * be copied to others. The ODBC bound column instead uses the old pointer.
         *
         * There must be a way to carry the pointer from one instance to another,
         * then set the old pointer to NULL (NO FREE or DELETE).
         * If the pointer would be deleted due to instance cleanup, the ODBC driver
         * would write to an deleted pointer.
         */

		setColumn(column->getColumnName_c_str());
		leaveOwnership(*&column, this);

		_hasValidData = true;
		
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbBoundColumn\58\\58\leaveOwnership\40\lb_I_BoundColumn\42\ oldOwner\44\ lb_I_BoundColumn\42\ newOwner\41\:0:*/
lbErrCodes LB_STDCALL lbBoundColumn::leaveOwnership(lb_I_BoundColumn* oldOwner, lb_I_BoundColumn* newOwner) {

	lbBoundColumn* oO = (lbBoundColumn*) oldOwner;
	lbBoundColumn* nO = (lbBoundColumn*) newOwner;

	nO->setData(oO->bound, oO->_DataType, oO->buffer, oO->columnName);
	oO->bound = 0;
	nO->isReadonly = oO->isReadonly;
	
	nO->cbBufferLength = oO->cbBufferLength;
	oO->cbBufferLength = NULL;
	
	if (oO->buffer != NULL) oO->buffer = NULL;

	return ERR_NONE;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbBoundColumn\58\\58\getData\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbBoundColumn::getData() {
	_CL_VERBOSE << "lbBoundColumn::getData(...) not implemented yet" LOG_
	return NULL;
}
/*...e*/
lbErrCodes LB_STDCALL lbBoundColumn::getAsLong(lb_I_Long* result, int asParameter) {
	lbErrCodes err = ERR_NONE;
	
	switch (_DataType) {
		case SQL_INTEGER:
		{
			result->setData(*(long*) buffer);
			break;
		}

        default:
			_CL_VERBOSE << "lbBoundColumn::getAsLong(...) failed: Unknown or not supported datatype for column '" << columnName << "'"  LOG_
	       	break;
	}
	
	return err;
}

/*...slbErrCodes LB_STDCALL lbBoundColumn\58\\58\getAsString\40\lb_I_String\42\ result\44\ int asParameter\41\:0:*/
lbErrCodes LB_STDCALL lbBoundColumn::getAsString(lb_I_String* result, int asParameter) {
	
	switch (_DataType) {
		case SQL_FLOAT:
		case SQL_DATE:
		case SQL_TYPE_DATE:
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
#ifndef BIND_BOOL_DEFAULT
		case SQL_BIT:
		case SQL_TINYINT:
#endif
			if (asParameter == 1) {
				char* b = (char*) malloc(strlen((char const *) buffer)+3);
				b[0] = 0;
				sprintf(b, "'%s'", buffer);
				result->setData(b);
				free(b);
			} else {
				result->setData((char*) buffer);
				result->trim();
			}
			
			break;
		case SQL_BINARY:
			_CL_VERBOSE << "lbBoundColumn::getAsString(...) failed: Binary data not supported for column '" << columnName << "'" LOG_
			break;
		case SQL_BIGINT:
		{
			char charrep[100] = "";
#ifdef WINDOWS
#ifndef _MSC_VER
			lltoa(*(long long*) buffer, charrep, 10);
#endif
#ifdef _MSC_VER
			sprintf(charrep, "%I64d", *(__int64*) buffer);
#endif
#endif
#ifdef LINUX
			sprintf(charrep, "%I64d", *(long long*) buffer);
#endif
#ifdef OSX
			sprintf(charrep, "%I64d", *(long long*) buffer);
#endif
			//sprintf(charrep, "%Ld", *(long long*) buffer);
			result->setData(charrep);
		}
			break;
		case SQL_INTEGER:
		{
			char charrep[100] = "";
			sprintf(charrep, "%d", *(long*) buffer);
			result->setData(charrep);
		}
			break;
#ifdef BIND_BOOL_DEFAULT
		case SQL_BIT:
		case SQL_TINYINT:
		{
#ifdef OSX
			int bi = 0;
			bi = *(int*) buffer;
			
			if (bi != 0) {
#endif
#ifndef OSX
				bool b = *(bool*) buffer;
				if (b == true) {
#endif
					result->setData("true");
				}
				else {
					result->setData("false");
				}	
			}
			break;
#endif
	        default:
	        	_CL_VERBOSE << "lbBoundColumn::getAsString(...) failed: Unknown or not supported datatype for column '" << columnName << "'"  LOG_
	        	break;
		}
		/* Pointer doesn't get changed.
		char* buf = (char*) malloc(20);
		sprintf(buf, "(%p)", buffer);
		*result += buf;
		free(buf);
		*/
		return ERR_NONE;
}
/*...e*/
lbErrCodes LB_STDCALL lbBoundColumn::setFromLong(lb_I_Long* set, int mode) {
	lbErrCodes err = ERR_NONE;
	if (isReadonly) {
		_CL_LOG << "Warning: Updating a column '" << columnName << "' with readonly status skipped." LOG_
		return ERR_NONE;
	}
	if (mode == 1) {
		switch (_DataType) {
			case SQL_INTEGER:
			{
				long l = set->getData();
				
				long* pl = (long*) buffer;
				
				void* b = pl+1;
				
				memcpy(b, &l, sizeof(l));
			}
				break;
		}
	} else {
		switch (_DataType) {
			case SQL_INTEGER:
			{
				long l = set->getData();
				memcpy(buffer, &l, sizeof(l));
			}
		}
	}
	_hasValidData = true;
	return err;
}
/*...slbErrCodes LB_STDCALL lbBoundColumn\58\\58\setFromString\40\lb_I_String\42\ set\44\ int mode\41\:0:*/
lbErrCodes LB_STDCALL lbBoundColumn::setFromString(lb_I_String* set, int mode) {
		if (isReadonly) {
			_CL_LOG << "Warning: Updating a column '" << columnName << "' with readonly status skipped." LOG_
			return ERR_NONE;
		}
		
		if (mode == 1) {
			switch (_DataType) {
				case SQL_FLOAT:
				case SQL_DATE:
				case SQL_TYPE_DATE:
				case SQL_CHAR:
				case SQL_VARCHAR:
				case SQL_LONGVARCHAR:
#ifndef BIND_BOOL_DEFAULT
				case SQL_BIT:
				case SQL_TINYINT:
#endif
					
				{
					// Must set an offset for the insert buffer
					
					char* bb = (char*) buffer;
					
					char* b = strcpy(bb + ColumnSize + 1, set->getData());
					cbBufferLength[1] = strlen((char*) buffer);
				}
					break;
				case SQL_INTEGER:
				{
					long l = 0;
					l = atol(set->getData());
					
					long* pl = (long*) buffer;
					
					void* b = pl+1;
					
					memcpy(b, &l, sizeof(l));
				}
					break;
					
				case SQL_BIGINT:
				{
#ifndef _MSC_VER
					long long l = 0;
					l = atoll(set->getData());
					long long* pl = (long long*) buffer;
#endif					
#ifdef _MSC_VER
					__int64 l = 0;
					l = _atoi64(set->getData());
					__int64* pl = (__int64*) buffer;
#endif										
					void* b = pl+1;
					
					memcpy(b, &l, sizeof(l));
				}
					break;
				case SQL_BINARY:
					_CL_VERBOSE << "lbBoundColumn::setFromString(...) failed: Binary data not supported for column '" << columnName << "'"  LOG_
					break;
#ifdef BIND_BOOL_DEFAULT					
				case SQL_BIT:
				case SQL_TINYINT:
				{
#ifdef OSX				
					long l = 0;
					if (strcmp(set->charrep(), "true") == 0) {
						l = 1;
					}
					
					long* pl = (long*) buffer;
					
					void* b = pl+1;
					
					memcpy(b, &l, sizeof(l));
#endif
#ifndef OSX
					bool l = false;
					if (strcmp(set->charrep(), "true") == 0) {
						l = true;
					}
					
					bool* pl = (bool*) buffer;
					
					void* b = pl+1;
					
					memcpy(b, &l, sizeof(l));
#endif 
				}
				break;
#endif			
			}
		} else {
			switch (_DataType) {
				case SQL_FLOAT:
				case SQL_DATE:
				case SQL_TYPE_DATE:
				case SQL_CHAR:
				case SQL_VARCHAR:
				case SQL_LONGVARCHAR:
#ifndef BIND_BOOL_DEFAULT
				case SQL_BIT:
				case SQL_TINYINT:
#endif
					
				{
					char* b = strcpy((char*) buffer, set->getData());
					cbBufferLength[0] = strlen((char*) buffer);
				}
					break;
				case SQL_INTEGER:
				{
					long l = 0;
					l = atol(set->getData());
					memcpy(buffer, &l, sizeof(l));
				}
					break;
				case SQL_BINARY:
					_CL_VERBOSE << "lbBoundColumn::setFromString(...) failed: Binary data not supported for column '" << columnName << "'" LOG_
					break;
#ifdef BIND_BOOL_DEFAULT					
				case SQL_BIT:
				case SQL_TINYINT:
				{
#ifdef OSX
					long l = 0;
					if (strcmp(set->charrep(), "true") == 0) {
						l = -1;
					}

					*((long*) buffer) = l;
#endif
#ifndef OSX
					bool l = false;
					if (strcmp(set->charrep(), "true") == 0) {
						l = true;
					}
					
					*((bool*) buffer) = l;
#endif
					//memcpy(buffer, &l, sizeof(bool));
				}
				break;
#endif					
			}
			
		}
		_hasValidData = true;
		return ERR_NONE;
	}
/*...e*/
/*...slbErrCodes LB_STDCALL lbBoundColumn\58\\58\prepareBoundColumn\40\lb_I_Query\42\ q\44\ int column\41\:0:*/
lbErrCodes LB_STDCALL lbBoundColumn::prepareBoundColumn(lb_I_Query* q, int column) {
	lbErrCodes err = ERR_NONE;

	HSTMT hstmt = ((lbQuery*) q)->getCurrentStatement();

/*...svars:8:*/
	SQLSMALLINT     ColumnNumber = 0;
	SQLCHAR         ColumnName[1000] = "";
	SQLSMALLINT     BufferLength = 500;
	SQLSMALLINT     NameLength = 0;
	SQLSMALLINT     DataType = 0;
	
	SQLSMALLINT     DecimalDigits = 0;
	SQLSMALLINT     Nullable = 0;
/*...e*/

// Assume readonly for now ...

	SQLRETURN ret = SQLDescribeCol( hstmt, column, ColumnName,
	                                BufferLength, &NameLength, &DataType,
	                                &ColumnSize, &DecimalDigits, &Nullable);

	_DataType = DataType;

	//if (colName == NULL) {
	//	REQUEST(manager.getPtr(), lb_I_String, colName)
	//}
	
	//colName->setData((char*) ColumnName);

	if (columnName) free(columnName);
	columnName = (char*) malloc(strlen((char const*) ColumnName)+1);
	columnName[0] = 0;

	if (strchr((char const*) ColumnName, '.') != 0) {
	        strcpy(columnName, (char*) (strchr((char const*) ColumnName, '.') + 1));
        } else {
                strcpy(columnName, (char*) ColumnName);
        }

	return err;
}
/*...e*/
/*...svoid       LB_STDCALL lbBoundColumn\58\\58\checkReadonly\40\int column\41\:0:*/
void       LB_STDCALL lbBoundColumn::checkReadonly(int column)
	{// Check for any type of readonly column	
		SQLHSTMT	StatementHandle;
		SQLUSMALLINT	ColumnNumber;
		SQLUSMALLINT	FieldIdentifier;
		SQLPOINTER	CharacterAttributePtr;
		SQLSMALLINT	BufferLength;
		SQLSMALLINT	StringLengthPtr = 0;
		SQLPOINTER	NumericAttributePtr;
		
		SQLINTEGER	Int = 0;
		
		CharacterAttributePtr = (void*) malloc(101);
		memset(CharacterAttributePtr, 0, 101);
		
		SQLRETURN retcode;
		
		retcode = SQLColAttribute(
				  hstmt,
				  column, 
				  SQL_DESC_UPDATABLE,
				  CharacterAttributePtr,
				  100,
				  &StringLengthPtr,
				  &Int ); 
			
		if ((retcode == SQL_ERROR) || (retcode == SQL_SUCCESS_WITH_INFO)) {
			_CL_LOG << "ERROR: SQLColAttribute(...) failed." LOG_
		}
		
		setReadonly(false);
		
		if (Int == SQL_ATTR_READONLY) {
			setReadonly(true);
		}
		
		free(CharacterAttributePtr);
	}	
/*...e*/
void LB_STDCALL lbBoundColumn::bindNullColumn() {
/*...svars:8:*/
	SQLSMALLINT     ColumnNumber = 0;
	SQLCHAR         ColumnName[1000] = "";
	SQLSMALLINT     BufferLength = 500;
	SQLSMALLINT     DataType = 0;
	SQLSMALLINT     NameLength = 0;
	
	SQLSMALLINT     DecimalDigits = 0;
	SQLSMALLINT     Nullable = 0;
/*...e*/

// Assume readonly for now ...

	if (mode == 1)
		cbBufferLength[1] = SQL_NULL_DATA;
	else
		cbBufferLength[0] = SQL_NULL_DATA;

	SQLRETURN ret;

	ret = SQLDescribeCol( hstmt, _column, ColumnName,
	                                BufferLength, &NameLength, &DataType,
	                                &ColumnSize, &DecimalDigits, &Nullable);

	_isNullable = Nullable == 1;

	if (ret != SQL_SUCCESS) {
		printf("Error: Failed to get column description for column %d.\n", _column);
		query->dbError("SQLDescribeCol()", hstmt);
	}

	ret = SQLBindCol(hstmt, _column, DataType, buffer, 0, cbBufferLength);

	if (ret != SQL_SUCCESS) {
	        printf("Error while binding a NULL column!\n");
	        query->dbError("SQLBindCol()", hstmt);
	}
}

/*...slbErrCodes LB_STDCALL lbBoundColumn\58\\58\bindColumn\40\lb_I_Query\42\ q\44\ int column\44\ bool ro\41\:0:*/
lbErrCodes LB_STDCALL lbBoundColumn::bindColumn(lb_I_Query* q, int column, bool ro) {
	hstmt = ((lbQuery*) q)->getCurrentStatement();

	query = (lbQuery*) q;

	_column = column;

/*...svars:8:*/
	SQLSMALLINT     ColumnNumber = 0;
	SQLCHAR         ColumnName[1000] = "";
	SQLSMALLINT     BufferLength = 500;
	SQLSMALLINT     DataType = 0;
	SQLSMALLINT     NameLength = 0;
	
	SQLSMALLINT     DecimalDigits = 0;
	SQLSMALLINT     Nullable = 0;
/*...e*/

// Assume readonly for now ...

	if (mode == 1)
		cbBufferLength[1] = 0;
	else
		cbBufferLength[0] = 0;
		
	SQLRETURN ret;

	if (ro == true) {
		_CL_LOG << "Bind a column that is read only (" << columnName << ")" LOG_
		if (mode == 1)
			cbBufferLength[1] = SQL_COLUMN_IGNORE;
		else
			cbBufferLength[0] = SQL_COLUMN_IGNORE;
		
		isReadonly = true;
	} else {
		// Check, if there are aggregates to be readonly
		checkReadonly(column);
	}


	ret = SQLDescribeCol( hstmt, column, ColumnName,
	                                BufferLength, &NameLength, &DataType,
	                                &ColumnSize, &DecimalDigits, &Nullable);

	_isNullable = Nullable == 1;

	if (ret != SQL_SUCCESS) {
		printf("Error: Failed to get column description for column %d.\n", column);
		query->dbError("SQLDescribeCol()", hstmt);
	}

	if (columnName) free(columnName);
	columnName = (char*) malloc(strlen((char const*) ColumnName)+1);
	columnName[0] = 0;

	if (strchr((char const*) ColumnName, '.') != 0) {
	        strcpy(columnName, (char*) (strchr((char const*) ColumnName, '.') + 1));
        } else {
                strcpy(columnName, (char*) ColumnName);
        }

	switch (DataType) {
		case SQL_DATE:
/*...sbind a character array:24:*/
			buffer = malloc((ColumnSize+1)*rows+20);

			_DataType = DataType;
			bound = 1;			     // Try a spacer for bugfix
			memset(buffer, 0, (ColumnSize+1)*rows+20);

			ret = SQLBindCol(hstmt, column, SQL_C_CHAR, buffer, (ColumnSize+1), cbBufferLength);
			
			if (ret != SQL_SUCCESS) {
				printf("Error while binding a column!\n");
				query->dbError("SQLBindCol()", hstmt);
			}
/*...e*/
			break;
		case SQL_TYPE_DATE:
/*...sbind a character array:24:*/
			buffer = malloc((ColumnSize+1)*rows+20);

			_DataType = DataType;
			bound = 1;			     // Try a spacer for bugfix
			memset(buffer, 0, (ColumnSize+1)*rows+20);

			ret = SQLBindCol(hstmt, column, SQL_C_CHAR, buffer, (ColumnSize+1), cbBufferLength);
			
			if (ret != SQL_SUCCESS) {
				printf("Error while binding a column!\n");
				query->dbError("SQLBindCol()", hstmt);
			}
/*...e*/
			break;
		case SQL_FLOAT:
		case SQL_BIT:
		case SQL_TINYINT:
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
/*...sbind a character array:24:*/
			buffer = malloc((ColumnSize+1)*rows+20);

			_DataType = DataType;
			bound = 1;			     // Try a spacer for bugfix
			memset(buffer, 0, (ColumnSize+1)*rows+20);

			ret = SQLBindCol(hstmt, column, SQL_C_CHAR, buffer, (ColumnSize+1), cbBufferLength);
			
			if (ret != SQL_SUCCESS) {
				printf("Error while binding a column!\n");
				query->dbError("SQLBindCol()", hstmt);
			}
/*...e*/
			break;
		case SQL_BINARY:
/*...sbind a binary array:24:*/
			buffer = malloc((ColumnSize+1)*rows+20);

			_DataType = DataType;
			bound = 1;			     // Try a spacer for bugfix
			memset(buffer, 0, (ColumnSize+1)*rows+20);
			
			ret = SQLBindCol(hstmt, column, SQL_C_DEFAULT, buffer, (ColumnSize+1), cbBufferLength);
			
			if (ret != SQL_SUCCESS) {
				printf("Error while binding a column!\n");
				query->dbError("SQLBindCol()", hstmt);
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
			buffer = malloc((sizeof(long))*rows);
			_DataType = DataType;
			bound = 1;
			memset(buffer, 0, sizeof(long)*rows);
			SQLBindCol(hstmt, column, DataType, buffer, sizeof(long), cbBufferLength);
			if (ret != SQL_SUCCESS) {
			        printf("Error while binding a column!\n");
			        query->dbError("SQLBindCol()", hstmt);
			}
/*...e*/
			break;
		case SQL_BIGINT:
/*...sbind an big integer:24:*/
#ifndef _MSC_VER
			buffer = malloc((sizeof(long long))*rows);
#endif
#ifdef _MSC_VER
			buffer = malloc((sizeof(__int64))*rows);
#endif
			_DataType = DataType;
			bound = 1;
#ifndef _MSC_VER
			memset(buffer, 0, sizeof(long long)*rows);
			ret = SQLBindCol(hstmt, column, SQL_C_DEFAULT, buffer, sizeof(long long), cbBufferLength);
#endif
#ifdef _MSC_VER
			memset(buffer, 0, sizeof(__int64)*rows);
			ret = SQLBindCol(hstmt, column, SQL_C_DEFAULT, buffer, sizeof(__int64), cbBufferLength);
#endif
			if (ret != SQL_SUCCESS) {
			        printf("Error while binding a column!\n");
			        query->dbError("SQLBindCol()", hstmt);
			}
/*...e*/
			break;
// Having no problems updating, when bound to a char array...
#ifdef BIND_BOOL_DEFAULT		
		case SQL_BIT:
		case SQL_TINYINT:
#ifndef OSX		
			buffer = malloc((sizeof(bool))*rows);
			_DataType = DataType;
			bound = 1;
			memset(buffer, 0, sizeof(bool)*rows);
			ret = SQLBindCol(hstmt, column, SQL_BIT, buffer, sizeof(bool), cbBufferLength);
#endif
#ifdef OSX
			buffer = malloc((sizeof(long))*rows);
			_DataType = DataType;
			bound = 1;
			memset(buffer, 0, sizeof(long)*rows);
			ret = SQLBindCol(hstmt, column, SQL_BIT, buffer, sizeof(long), cbBufferLength);
#endif
			if (ret != SQL_SUCCESS) {
				_LOG << "Error: Binding column '" << columnName << "' failed!" LOG_
				
			        query->dbError("SQLBindCol()", hstmt);
			}
			break;
#endif
		default:
			_CL_LOG << "lbBoundColumn::bindColumn(...) failed: Unknown or not supported datatype for column '" << columnName << "': " << DataType LOG_
			break;
	}
	

	return ERR_NONE;
}
/*...sSample of dynamically allocated buffer:0:*/
#ifdef bla

// I cannot use that because I have a separate class of a bound column.
// And why should it impossible to allocate separate buffers for each
// column.


// This application allocates a buffer at run time. For each column, this buffer
// contains memory for the column's data and length/indicator. For example:
//
//  column 1    column 2 column 3 column 4
// <------------><---------------><-----><------------>
//  db1 li1  db2   li2 db3 li3  db4 li4
//   |   |    |   | | |  |   |
//  _____V_____V________V_______V___V___V______V_____V_
// |__________|__|_____________|__|___|__|__________|__|
//
// dbn = data buffer for column n
// lin = length/indicator buffer for column n

// Define a macro to increase the size of a buffer so it is a multiple of the alignment
// size. Thus, if a buffer starts on an alignment boundary, it will end just before the
// next alignment boundary. In this example, an alignment size of 4 is used because
// this is the size of the largest data type used in the application's buffer -- the
// size of an SDWORD and of the largest default C data type are both 4. If a larger
// data type (such as _int64) was used, it would be necessary to align for that size.
#define ALIGNSIZE 4
#define ALIGNBUF(Length) Length % ALIGNSIZE ? \
         Length + ALIGNSIZE - (Length % ALIGNSIZE) : Length

SQLCHAR   SelectStmt[100];
SQLSMALLINT NumCols, *CTypeArray, i;
SQLINTEGER  *ColLenArray, *OffsetArray, SQLType, *DataPtr;
SQLRETURN rc; 
SQLHSTMT  hstmt;

// Get a SELECT statement from the user and execute it.
GetSelectStmt(SelectStmt, 100);
SQLExecDirect(hstmt, SelectStmt, SQL_NTS);

// Determine the number of result set columns.  Allocate arrays to hold the C type,
// byte length, and buffer offset to the data.
SQLNumResultCols(hstmt, &NumCols);
CTypeArray = (SQLSMALLINT *) malloc(NumCols * sizeof(SQLSMALLINT));
ColLenArray = (SQLINTEGER *) malloc(NumCols * sizeof(SQLINTEGER));
OffsetArray = (SQLINTEGER *) malloc(NumCols * sizeof(SQLINTEGER));

OffsetArray[0] = 0;
for (i = 0; i < NumCols; i++) {
 // Determine the column's SQL type. GetDefaultCType contains a switch statement that
 // returns the default C type for each SQL type.
 SQLColAttribute(hstmt, ((SQLUSMALLINT) i) + 1, SQL_DESC_TYPE, NULL, 0, NULL, (SQLPOINTER) &SQLType);
 CTypeArray[i] = GetDefaultCType(SQLType);

 // Determine the column's byte length. Calculate the offset in the buffer to the
 // data as the offset to the previous column, plus the byte length of the previous
 // column, plus the byte length of the previous column's length/indicator buffer.
 // Note that the byte length of the column and the length/indicator buffer are
 // increased so that, assuming they start on an alignment boundary, they will end on
 // the byte before the next alignment boundary. Although this might leave some holes
 // in the buffer, it is a relatively inexpensive way to guarantee alignment.
 SQLColAttribute(hstmt, ((SQLUSMALLINT) i)+1, SQL_DESC_OCTET_LENGTH, NULL, 0, NULL, &ColLenArray[i]);
 ColLenArray[i] = ALIGNBUF(ColLenArray[i]);
 if (i)
  OffsetArray[i] = OffsetArray[i-1]+ColLenArray[i-1]+ALIGNBUF(sizeof(SQLINTEGER));
}

// Allocate the data buffer. The size of the buffer is equal to the offset to the data
// buffer for the final column, plus the byte length of the data buffer and
// length/indicator buffer for the last column.
void *DataPtr = malloc(OffsetArray[NumCols - 1] +
        ColLenArray[NumCols - 1] + ALIGNBUF(sizeof(SQLINTEGER)));

// For each column, bind the address in the buffer at the start of the memory allocated
// for that column's data and the address at the start of the memory allocated for that
// column's length/indicator buffer.
for (i = 0; i < NumCols; i++)
 SQLBindCol(hstmt,
      ((SQLUSMALLINT) i) + 1,
      CTypeArray[i],
      (SQLPOINTER)((SQLCHAR *)DataPtr + OffsetArray[i]),
      ColLenArray[i],
      (SQLINTEGER *)((SQLCHAR *)DataPtr + OffsetArray[i] + ColLenArray[i]));

// Retrieve and print each row. PrintData accepts a pointer to the data, its C type,
// and its byte length/indicator. It contains a switch statement that casts and prints
// the data according to its type. Code to check if rc equals SQL_ERROR or
// SQL_SUCCESS_WITH_INFO not shown.
while ((rc = SQLFetch(hstmt)) != SQL_NO_DATA) {
 for (i = 0; i < NumCols; i++) {
  PrintData((SQLCHAR *)DataPtr[OffsetArray[i]], CTypeArray[i],
      (SQLINTEGER *)((SQLCHAR *)DataPtr[OffsetArray[i] + ColLenArray[i]]));
 }
}

// Close the cursor.
SQLCloseCursor(hstmt);


#endif
/*...e*/
/*...e*/
/*...svoid LB_STDCALL lbBoundColumn\58\\58\unbindReadonlyColumns\40\\41\:0:*/
void LB_STDCALL lbBoundColumn::unbindReadonlyColumns() {
	SQLRETURN ret = SQL_SUCCESS;

	if (isReadonly) {
/*...sUnbind:16:*/
	switch (_DataType) {
		case SQL_DATE:
		case SQL_TYPE_DATE:
			_CL_VERBOSE << "Unbind date" LOG_
			bound = 0;

			ret = SQLBindCol(hstmt, _column, SQL_C_CHAR, NULL, (ColumnSize+1), cbBufferLength);
			break;
		case SQL_FLOAT:	
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
#ifndef BIND_BOOL_DEFAULT
		case SQL_BIT:
		case SQL_TINYINT:
#endif		
			_CL_VERBOSE << "Unbind char" LOG_
			bound = 0;

			ret = SQLBindCol(hstmt, _column, SQL_C_CHAR, NULL, (ColumnSize+1), cbBufferLength);
			break;
		case SQL_BINARY:
			_CL_VERBOSE << "Unbind binary" LOG_
			bound = 0;
			
			ret = SQLBindCol(hstmt, _column, SQL_C_DEFAULT, NULL, (ColumnSize+1), cbBufferLength);
			break;
		case SQL_INTEGER:
			_CL_VERBOSE << "Unbind integer" LOG_
			bound = 0;

			SQLBindCol(hstmt, _column, SQL_C_DEFAULT, NULL, sizeof(long), cbBufferLength);
			break;
		case SQL_BIGINT:
			_CL_VERBOSE << "Unbind big integer" LOG_
			bound = 0;
#ifndef _MSC_VER
			SQLBindCol(hstmt, _column, SQL_C_DEFAULT, NULL, sizeof(long long), cbBufferLength);
#endif
#ifdef _MSC_VER
			SQLBindCol(hstmt, _column, SQL_C_DEFAULT, NULL, sizeof(__int64), cbBufferLength);
#endif
			break;
#ifdef BIND_BOOL_DEFAULT
		case SQL_BIT:
		case SQL_TINYINT:
			_CL_VERBOSE << "Unbind bit" LOG_
			bound = 0;
#ifdef OSX
			SQLBindCol(hstmt, _column, SQL_BIT, NULL, sizeof(long), cbBufferLength);
#endif
#ifndef OSX
			SQLBindCol(hstmt, _column, SQL_BIT, NULL, sizeof(bool), cbBufferLength);
#endif			
			if (ret != SQL_SUCCESS) {
			        printf("Error while unbinding a column!\n");
			        query->dbError("SQLBindCol()", hstmt);
			}
			break;
#endif
		default:
			_CL_VERBOSE << "lbBoundColumn::unbindReadonlyColumns(...) failed: Unknown or not supported datatype for column '" << columnName << "': " << _DataType LOG_
			break;
	}
/*...e*/
	}

	if (ret != SQL_SUCCESS) {
		printf("Error while unbinding a column!\n");
		query->dbError("SQLBindCol()", hstmt);
	}
}
/*...e*/
/*...svoid LB_STDCALL lbBoundColumn\58\\58\rebindReadonlyColumns\40\\41\:0:*/
void LB_STDCALL lbBoundColumn::rebindReadonlyColumns() {
	SQLRETURN ret = SQL_SUCCESS;

	if (isReadonly) {
/*...sRebind:16:*/
	switch (_DataType) {
		case SQL_DATE:
		case SQL_TYPE_DATE:
			_CL_VERBOSE << "Rebind date" LOG_
			bound = 1;

			ret = SQLBindCol(hstmt, _column, SQL_C_CHAR, buffer, (ColumnSize+1), cbBufferLength);
			break;
		case SQL_FLOAT:
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
#ifndef BIND_BOOL_DEFAULT
		case SQL_BIT:
		case SQL_TINYINT:
#endif		
		
			_CL_VERBOSE << "Rebind char" LOG_
			bound = 1;

			ret = SQLBindCol(hstmt, _column, SQL_C_CHAR, buffer, (ColumnSize+1), cbBufferLength);
			break;
		case SQL_BINARY:
			_CL_VERBOSE << "Rebind binary" LOG_
			bound = 1;
			
			ret = SQLBindCol(hstmt, _column, SQL_C_DEFAULT, buffer, (ColumnSize+1), cbBufferLength);
			break;
		case SQL_INTEGER:
			_CL_VERBOSE << "Rebind integer" LOG_
			bound = 1;

			SQLBindCol(hstmt, _column, SQL_C_DEFAULT, buffer, sizeof(long), cbBufferLength);
			break;
		case SQL_BIGINT:
			_CL_VERBOSE << "Rebind big integer" LOG_
			bound = 1;
#ifndef _MSC_VER
			SQLBindCol(hstmt, _column, SQL_C_DEFAULT, buffer, sizeof(long long), cbBufferLength);
#endif
#ifdef _MSC_VER
			SQLBindCol(hstmt, _column, SQL_C_DEFAULT, buffer, sizeof(__int64), cbBufferLength);
#endif
			break;
#ifdef BIND_BOOL_DEFAULT
		case SQL_BIT:
		case SQL_TINYINT:
			_CL_VERBOSE << "Rebind bit" LOG_
			bound = 1;
#ifdef OSX
			SQLBindCol(hstmt, _column, SQL_BIT, buffer, sizeof(long), cbBufferLength);
#endif
#ifndef OSX
			SQLBindCol(hstmt, _column, SQL_BIT, buffer, sizeof(bool), cbBufferLength);
#endif
			if (ret != SQL_SUCCESS) {
			        printf("Error while binding a column!\n");
			        query->dbError("SQLBindCol()", hstmt);
			}
			break;
#endif
		default:
			_CL_VERBOSE << "lbBoundColumn::rebindReadonlyColumns(...) failed: Unknown or not supported datatype for column '" << columnName << "': " << _DataType LOG_
			break;
	}
/*...e*/
	}

	if (ret != SQL_SUCCESS) {
	        printf("Error while binding column %s!\n", columnName);
	        query->dbError("SQLBindCol()", hstmt);
	}
}
/*...e*/

void	LB_STDCALL lbBoundColumn::invalidateData() {
	// No extra function for adding mode.
	_hasValidData = false;
}

bool	LB_STDCALL lbBoundColumn::hasValidData() {
	if (!(_hasValidData || isReadonly)) {
		_LOG << "Bound column '" << columnName << "' has no valid data." LOG_
	}
	return _hasValidData || isReadonly || _isNullable;
}


/*...svoid LB_STDCALL lbBoundColumn\58\\58\rebind\40\\41\:0:*/
void LB_STDCALL lbBoundColumn::rebind() {
	SQLRETURN ret = SQL_SUCCESS;
	
	mode = 0;

/*...sRebind:8:*/
	switch (_DataType) {
		case SQL_DATE:
		case SQL_TYPE_DATE:
			_CL_VERBOSE << "Rebind date" LOG_
			bound = 1;

			ret = SQLBindCol(hstmt, _column, SQL_C_CHAR, buffer, (ColumnSize+1), cbBufferLength);
			break;
		case SQL_FLOAT:
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
#ifndef BIND_BOOL_DEFAULT
		case SQL_BIT:
		case SQL_TINYINT:
#endif		
		
			_CL_VERBOSE << "Rebind char" LOG_
			bound = 1;

			ret = SQLBindCol(hstmt, _column, SQL_C_CHAR, buffer, (ColumnSize+1), cbBufferLength);
			break;
		case SQL_BINARY:
			_CL_VERBOSE << "Rebind binary" LOG_
			bound = 1;
			
			ret = SQLBindCol(hstmt, _column, SQL_C_DEFAULT, buffer, (ColumnSize+1), cbBufferLength);
			break;
		case SQL_INTEGER:
			_CL_VERBOSE << "Rebind integer" LOG_
			bound = 1;

			SQLBindCol(hstmt, _column, SQL_C_DEFAULT, buffer, sizeof(long), cbBufferLength);
			break;
		case SQL_BIGINT:
			_CL_VERBOSE << "Rebind big integer" LOG_
			bound = 1;
#ifndef _MSC_VER
			SQLBindCol(hstmt, _column, SQL_C_DEFAULT, buffer, sizeof(long long), cbBufferLength);
#endif
#ifdef _MSC_VER
			SQLBindCol(hstmt, _column, SQL_C_DEFAULT, buffer, sizeof(__int64), cbBufferLength);
#endif
			break;
#ifdef BIND_BOOL_DEFAULT
		case SQL_BIT:
		case SQL_TINYINT:
			_CL_VERBOSE << "Rebind bit" LOG_
			bound = 1;
#ifdef OSX
			SQLBindCol(hstmt, _column, _DataType, buffer, sizeof(long), cbBufferLength);
#endif
#ifndef OSX
			SQLBindCol(hstmt, _column, _DataType, buffer, sizeof(bool), cbBufferLength);
#endif
			if (ret != SQL_SUCCESS) {
			        printf("Error while binding a column!\n");
			        query->dbError("SQLBindCol()", hstmt);
			}
			break;
#endif
		default:
			_CL_VERBOSE << "lbBoundColumn::rebindReadonlyColumns(...) failed: Unknown or not supported datatype for column '" << columnName << "': " << _DataType LOG_
			break;
	}
/*...e*/

	if (ret != SQL_SUCCESS) {
	        printf("Error while binding column %s!\n", columnName);
	        query->dbError("SQLBindCol()", hstmt);
	}
}
/*...e*/
/*...slb_I_String\42\ LB_STDCALL lbBoundColumn\58\\58\getColumnName\40\\41\:0:*/
lb_I_String* LB_STDCALL lbBoundColumn::getColumnName() {
	UAP_REQUEST(manager.getPtr(), lb_I_String, colName)
	colName->setData(columnName);
	colName++;
	
	return colName.getPtr();
}
/*...e*/
/*...svoid lbBoundColumn\58\\58\setReadonly\40\bool updateable\41\:0:*/
void lbBoundColumn::setReadonly(bool updateable) {
	isReadonly = updateable;
}
/*...e*/
/*...e*/
/*...sclass lbConnection:0:*/
class lbConnection : public lb_I_Connection
{
public:
        lbConnection()  {
	    ref = STARTREF;
	    _dbname = NULL;
	    _dbuser = NULL;
	}
        virtual ~lbConnection() {
        	_CL_VERBOSE << "lbConnection::~lbConnection() called" LOG_
		if (_dbname) free(_dbname);
		if (_dbuser) free(_dbuser);
	}

	DECLARE_LB_UNKNOWN()


	virtual char* LB_STDCALL getDBName() { return _dbname; }
	virtual char* LB_STDCALL getDBUser() { return _dbuser; }

//-- Private interface -----------------------------------------
	virtual void LB_STDCALL setDBName(char* name) {
	    if (_dbname) {
		free(_dbname);
		_dbname = NULL;
	    }
	    
	    _dbname = (char*) malloc(strlen(name)+1);
	    
	    if (name) strcpy(_dbname, name);
	}
	
	virtual void LB_STDCALL setDBUser(char* name) {
	    if (_dbuser) {
		free(_dbuser);
		_dbuser = NULL;
	    }
	    
	    _dbuser = (char*) malloc(strlen(name)+1);
	    
	    if (name) strcpy(_dbuser, name);
	}
	
	virtual void LB_STDCALL setConnection(HDBC _hdbc) {
	    hdbc = _hdbc;
	}
	
	virtual HDBC LB_STDCALL getConnection() { return hdbc; }
	
protected:

	char* _dbname;
	char* _dbuser;
	
	HDBC     hdbc;
};
/*...e*/

/*...sclass lbConnection implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbConnection)
	ADD_INTERFACE(lb_I_Connection)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfConnection, lbConnection)

lbErrCodes LB_STDCALL lbConnection::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	UAP(lb_I_Connection, con)
	QI(uk, lb_I_Connection, con)
	
	lbConnection* connection; 
	
	if (con.getPtr() != NULL) {
	    connection = (lbConnection*) con.getPtr();
	    
	    hdbc = connection->getConnection();
	}
	
	return ERR_NOT_IMPLEMENTED;
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

	lbErrCodes	LB_STDCALL init();
	
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
	
	lb_I_Container* LB_STDCALL getTables();
	lb_I_Container* LB_STDCALL getColumns();
	
	lb_I_Container* LB_STDCALL getForeignKeys();
	lb_I_Container* LB_STDCALL getPrimaryKeys();
	
private:
	RETCODE  retcode;
	HENV     henv;	
	HDBC     hdbc;
	char*	 user;
	char*	 db;
	bool	 connected;

	UAP(lb_I_Container, connPooling)
};

//lb_I_Container* lbDatabase::connPooling = NULL;

BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lbDatabase)
	ADD_INTERFACE(lb_I_Database)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfDatabase, lbDatabase)

lbDatabase::lbDatabase() {
	ref = STARTREF;
	henv = 0;
	hdbc = 0;
	user = NULL;
	db = NULL;
	connPooling = NULL;
	connected = false;
	_CL_VERBOSE << "lbDatabase::lbDatabase() called." LOG_
}

lbDatabase::~lbDatabase() {
	_CL_LOG << "lbDatabase::~lbDatabase() called." LOG_
}

/*...slbErrCodes LB_STDCALL lbDatabase\58\\58\init\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabase::init() {
	retcode = SQLAllocEnv(&henv);
	if (retcode != SQL_SUCCESS) {
        	_LOG << "lbDatabase::init(): Database initializion failed." LOG_
        	return ERR_DB_INIT;
        }

	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, 0);

	if (retcode != SQL_SUCCESS) {
        	_LOG << "lbDatabase::init(): Database version initializion failed." LOG_
        	return ERR_DB_INIT;
	}

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabase\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabase::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbInstanceReference::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbErrCodes LB_STDCALL lbDatabase::setUser(char* _user) {
	if (user != NULL) free(user);
	user = (char*) malloc(strlen(_user)+1);
	user[0] = 0;
	strcpy(user, _user);
	_CL_VERBOSE << "lbDatabase::setUser('" << user << "') called." LOG_
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDatabase::setDB(char* _db) {
	if (db != NULL) free(db);
	db = (char*) malloc(strlen(_db)+1);
	db[0] = 0;
	strcpy(db, _db);
	_CL_VERBOSE << "lbDatabase::setDB('" << db << "') called." LOG_
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDatabase::connect(char* connectionname, char* pass) {
	_CL_VERBOSE << "lbDatabase::connect(char* pass) called. DB:" << db << ", U:" << user << ", P:" << pass LOG_
	return connect(connectionname, db, user, pass);
}

bool LB_STDCALL lbDatabase::isConnected() {
	return connected;
}

/*...slbErrCodes LB_STDCALL lbDatabase\58\\58\connect\40\char\42\ DSN\44\ char\42\ user\44\ char\42\ passwd\41\:0:*/
lbErrCodes LB_STDCALL lbDatabase::connect(char* connectionname, char* DSN, char* user, char* passwd) {
	lbErrCodes err = ERR_NONE;

	// Put me to unconnected state, if anything goes wrong...
	connected = false;
	
	if (connPooling == NULL) {
	    UAP_REQUEST(manager.getPtr(), lb_I_Container, container)
	    container->queryInterface("lb_I_Container", (void**) &connPooling, __FILE__, __LINE__);
	}
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, ConnectionName)
	*ConnectionName = connectionname;
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, uk)
	
	QI(ConnectionName, lb_I_KeyBase, key)
	
	if (connPooling->exists(&key) != 1) {
	    _CL_VERBOSE << "SQLAllocConnect(henv, &hdbc);" LOG_

	    retcode = SQLAllocConnect(henv, &hdbc); /* Connection handle */

	    if (retcode != SQL_SUCCESS)
	    {
		_LOG << "SQLAllocConnect(henv, &hdbc) failed." LOG_
    		_dbError_ENV("SQLAllocConnect()", henv);
        	SQLFreeEnv(henv);
    		return ERR_DB_CONNECT;
    	    }	
        
	    lbConnection* c = new lbConnection();
	    
	    c->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
	    c->setConnection(hdbc);

	    QI(c, lb_I_Unknown, uk)
	    
	    _CL_VERBOSE << "SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 15);" LOG_
	    retcode = SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 15); /* Set login timeout to 15 seconds. */

            if (retcode != SQL_SUCCESS)
            {
				_LOG << "SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 15) failed." LOG_
                _dbError_DBC( "SQLSetConnectOption()", hdbc);
                SQLFreeEnv(henv);
                return ERR_DB_CONNECT;
            }

	    _CL_VERBOSE << "SQLSetConnectAttr(hdbc, SQL_ATTR_ODBC_CURSORS, SQL_CUR_USE_IF_NEEDED, 0);" LOG_

		// SQL_CUR_USE_IF_NEEDED does not work with psqlODBC 8.x.x
		// Use Cursor library.
	    //retcode = SQLSetConnectAttr(hdbc, SQL_ATTR_ODBC_CURSORS, (void*)SQL_CUR_USE_ODBC/*SQL_CUR_USE_IF_NEEDED*/, 0);
	    retcode = SQLSetConnectAttr(hdbc, SQL_ATTR_ODBC_CURSORS, SQL_CUR_USE_IF_NEEDED, 0);

		if (retcode != SQL_SUCCESS)
		{
			_LOG << "SQLSetConnectAttr(hdbc, SQL_ATTR_ODBC_CURSORS, SQL_CUR_USE_IF_NEEDED, 0) failed." LOG_
			_dbError_DBC( "SQLSetConnectAttr()", hdbc);
			SQLFreeEnv(henv);
			return ERR_DB_CONNECT;
	    }

	    retcode = SQLConnect(hdbc, (unsigned char*) DSN, SQL_NTS, 
				       (unsigned char*) user, SQL_NTS, 
				       (unsigned char*) passwd, SQL_NTS); /* Connect to data source */

	    if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			_dbError_DBC( "SQLConnect()", hdbc);
			_LOG << "Connection to database failed." LOG_
			SQLFreeEnv(henv);
			return ERR_DB_CONNECT;
		}
            
/* Does not help :-(
	    retcode = SQLSetConnectAttr(hdbc, SQL_TXN_ISOLATION, (void*) SQL_TXN_SERIALIZABLE, 0); //(void*) SQL_TXN_REPEATABLE_READ, 0);
	    
	    if (retcode != SQL_SUCCESS)
	    {
	        _dbError_DBC( "SQLSetConnectOption(SQL_TXN_ISOLATION, SQL_TXN_REPEATABLE_READ)", hdbc);
	        SQLFreeEnv(henv);
	        return ERR_DB_CONNECT;
	    }
*/
		retcode = SQLSetConnectOption(hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);

		if (retcode != SQL_SUCCESS)
		{
			_LOG << "SQLSetConnectOption(hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON) failed." LOG_
			_dbError_DBC( "SQLSetConnectOption(SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON)", hdbc);
			SQLFreeEnv(henv);
			return ERR_DB_CONNECT;
	    }
	    
	    connPooling->insert(&uk, &key);
		connected = true;
	}

	return ERR_NONE;
}
/*...e*/
lb_I_Query* LB_STDCALL lbDatabase::getQuery(char* connectionname, int readonly) {
	lbErrCodes err = ERR_NONE;
	lbQuery* query = new lbQuery;
	query->setModuleManager(*&manager, __FILE__, __LINE__);

	if (connectionname == NULL) {
		_LOG << "lbDatabase::getQuery() Error: Did not got a connection name." LOG_
		return NULL;
	}

	UAP_REQUEST(manager.getPtr(), lb_I_String, ConnectionName)
	*ConnectionName = connectionname;
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, uk)
	
	QI(ConnectionName, lb_I_KeyBase, key)
	
	if (connPooling->exists(&key) == 1) {
	    UAP(lb_I_Connection, con)
	    
	    uk = connPooling->getElement(&key);
	    
	    QI(uk, lb_I_Connection, con)
	    
	    if (con != NULL) {
			lbConnection* c = (lbConnection*) con.getPtr();
		
			hdbc = c->getConnection();
			connected = true;
		}
	}

	if (query->init(henv, hdbc, readonly) != ERR_NONE) {
		_LOG << "ERROR: Initializion of query has been failed!" LOG_
		
		//return NULL;
	}

	lb_I_Query* q = NULL;
	
	query->queryInterface("lb_I_Query", (void**) &q, __FILE__, __LINE__);

	return q;
}
/*...e*/

lb_I_Container* LB_STDCALL lbDatabase::getTables() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Container, tables)
	tables++;
	
	tables->setCloning(false);
	
	UCHAR			szTableCatalog[TAB_LEN];
	UCHAR			szTableSchema[TAB_LEN];
	UCHAR			szTableName[TAB_LEN];
	UCHAR			szTableType[TAB_LEN];
	UCHAR			szTableRemarks[REM_LEN];
	
	SQLHSTMT		hstmt;
	
	SQLINTEGER		cbTableCatalog = TAB_LEN;
	SQLINTEGER		cbTableSchema = TAB_LEN;
	SQLINTEGER		cbTableName = TAB_LEN;
	SQLINTEGER		cbTableType = TAB_LEN;
	SQLINTEGER		cbTableRemarks = REM_LEN;
	SQLRETURN		retcode;
	
	retcode = SQLAllocStmt(hdbc, &hstmt); /* Statement handle */
	
	if (retcode != SQL_SUCCESS)
	{
		_LOG << "Error: Failed to get statement handle from database connection!" LOG_
		return tables.getPtr();
	}
	
	SQLBindCol(hstmt, 1, SQL_C_CHAR, szTableCatalog, TAB_LEN, &cbTableCatalog);
	SQLBindCol(hstmt, 2, SQL_C_CHAR, szTableSchema, TAB_LEN, &cbTableSchema);
	SQLBindCol(hstmt, 3, SQL_C_CHAR, szTableName, TAB_LEN, &cbTableName);
	SQLBindCol(hstmt, 4, SQL_C_CHAR, szTableType, TAB_LEN, &cbTableType);
	SQLBindCol(hstmt, 5, SQL_C_CHAR, szTableRemarks, REM_LEN, &cbTableRemarks);
	
	retcode = SQLTables(hstmt, NULL, 0, NULL, 0, NULL, 0, NULL, 0);
		
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, index)
	UAP(lb_I_KeyBase, key)
	QI(index, lb_I_KeyBase, key)
	
	long i = 0;
	
	while(retcode == SQL_SUCCESS) {
		retcode = SQLFetch(hstmt);
		if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
			_LOG << "Error: Some error happened while fetching tables." LOG_
			tables->deleteAll();
			SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
			return tables.getPtr();
		}
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){
            ;   /* Process fetched data */
			
			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
			
			*value = (const char*) szTableCatalog;
			*name = "TableCatalog";
			param->setUAPString(*&name, *&value);
			*value = (const char*) szTableSchema;
			*name = "TableSchema";
			param->setUAPString(*&name, *&value);
			*value = (const char*) szTableName;
			*name = "TableName";
			param->setUAPString(*&name, *&value);
			*value = (const char*) szTableType;
			*name = "TableTyp";
			param->setUAPString(*&name, *&value);
			*value = (const char*) szTableRemarks;
			*name = "TableRemarks";
			param->setUAPString(*&name, *&value);

			index->setData(++i);

			UAP(lb_I_Unknown, uk)
			QI(param, lb_I_Unknown, uk)
				 
			tables->insert(&uk, &key);
		}
	}
	
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	
	return tables.getPtr();
}

lb_I_Container* LB_STDCALL lbDatabase::getColumns() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Container, columns)
	columns++;
	
	columns->setCloning(false);

	SQLCHAR       szCatalog[TAB_LEN], szSchema[TAB_LEN];
	SQLCHAR       szTableName[TAB_LEN], szColumnName[TAB_LEN];
	SQLCHAR       szTypeName[TAB_LEN], szRemarks[REM_LEN];
	SQLCHAR       szColumnDefault[TAB_LEN], szIsNullable[TAB_LEN];
	SQLINTEGER    ColumnSize, BufferLength, CharOctetLength, OrdinalPosition;
	SQLSMALLINT   DataType, DecimalDigits, NumPrecRadix, Nullable;
	SQLSMALLINT   SQLDataType, DatetimeSubtypeCode;
	SQLRETURN     retcode;
	SQLHSTMT      hstmt;
	
	/* Declare buffers for bytes available to return */
	
	SQLINTEGER cbCatalog, cbSchema, cbTableName, cbColumnName;
	SQLINTEGER cbDataType, cbTypeName, cbColumnSize, cbBufferLength;
	SQLINTEGER cbDecimalDigits, cbNumPrecRadix, cbNullable, cbRemarks;
	SQLINTEGER cbColumnDefault, cbSQLDataType, cbDatetimeSubtypeCode, cbCharOctetLength;
	SQLINTEGER cbOrdinalPosition, cbIsNullable;
	
	retcode = SQLAllocStmt(hdbc, &hstmt); /* Statement handle */
	
	if (retcode != SQL_SUCCESS)
	{
		_LOG << "Error: Failed to get statement handle from database connection!" LOG_
		return columns.getPtr();
	}

	
	retcode = SQLColumns(hstmt, NULL, 0, NULL, 0, NULL, 0, NULL, 0);     
	
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		 /* Bind columns in result set to buffers */
							 
		 SQLBindCol(hstmt, 1, SQL_C_CHAR, szCatalog, TAB_LEN,&cbCatalog);
		 SQLBindCol(hstmt, 2, SQL_C_CHAR, szSchema, TAB_LEN, &cbSchema);
		 SQLBindCol(hstmt, 3, SQL_C_CHAR, szTableName, TAB_LEN,&cbTableName);
		 SQLBindCol(hstmt, 4, SQL_C_CHAR, szColumnName, TAB_LEN, &cbColumnName);
		 SQLBindCol(hstmt, 5, SQL_C_SSHORT, &DataType, 0, &cbDataType);
		 SQLBindCol(hstmt, 6, SQL_C_CHAR, szTypeName, TAB_LEN, &cbTypeName);
		 SQLBindCol(hstmt, 7, SQL_C_SLONG, &ColumnSize, 0, &cbColumnSize);
		 SQLBindCol(hstmt, 8, SQL_C_SLONG, &BufferLength, 0, &cbBufferLength);
		 SQLBindCol(hstmt, 9, SQL_C_SSHORT, &DecimalDigits, 0, &cbDecimalDigits);
		 SQLBindCol(hstmt, 10, SQL_C_SSHORT, &NumPrecRadix, 0, &cbNumPrecRadix);
		 SQLBindCol(hstmt, 11, SQL_C_SSHORT, &Nullable, 0, &cbNullable);
		 SQLBindCol(hstmt, 12, SQL_C_CHAR, szRemarks, REM_LEN, &cbRemarks);
		 SQLBindCol(hstmt, 13, SQL_C_CHAR, szColumnDefault, TAB_LEN, &cbColumnDefault);
		 SQLBindCol(hstmt, 14, SQL_C_SSHORT, &SQLDataType, 0, &cbSQLDataType);
		 SQLBindCol(hstmt, 15, SQL_C_SSHORT, &DatetimeSubtypeCode, 0, &cbDatetimeSubtypeCode);
		 SQLBindCol(hstmt, 16, SQL_C_SLONG, &CharOctetLength, 0, &cbCharOctetLength);
		 SQLBindCol(hstmt, 17, SQL_C_SLONG, &OrdinalPosition, 0, &cbOrdinalPosition);
		 SQLBindCol(hstmt, 18, SQL_C_CHAR, szIsNullable, TAB_LEN, &cbIsNullable);
		 
		 
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP_REQUEST(getModuleInstance(), lb_I_String, value)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, number)

		UAP_REQUEST(getModuleInstance(), lb_I_Long, index)
		UAP(lb_I_KeyBase, key)
		QI(index, lb_I_KeyBase, key)
	
		long i = 0;
		
		_LOG << "lbDatabase::getColumns() short before fetching column informations." LOG_
		
		while(retcode == SQL_SUCCESS) {
			retcode = SQLFetch(hstmt);
			if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
				 _LOG << "Error: Some error happened while fetching tables." LOG_
				 columns->deleteAll();
				 SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
				 return columns.getPtr();
			 }
			 if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){
				 ;   /* Process fetched data */
				 
				 UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
					 
				 number->setData((long)DatetimeSubtypeCode);
				 *name = "DatetimeSubtypeCode";
				 param->setUAPLong(*&name, *&number);
				 
				 *value = (const char*) szCatalog;
				 *name = "TableCatalog";
				 param->setUAPString(*&name, *&value);
				 
				 *value = (const char*) szSchema;
				 *name = "TableSchema";
				 param->setUAPString(*&name, *&value);
				 
				 *value = (const char*) szTableName;
				 *name = "TableName";
				 param->setUAPString(*&name, *&value);
				 
				 *value = (const char*) szColumnName;
				 *name = "ColumnName";
				 param->setUAPString(*&name, *&value);
				 
				 number->setData((long)DataType);
				 *name = "DataType";
				 param->setUAPLong(*&name, *&number);
				 
				 *value = (const char*) szTypeName;
				 *name = "TypeName";
				 param->setUAPString(*&name, *&value);
				 
				 number->setData((long)BufferLength);
				 *name = "BufferLength";
				 param->setUAPLong(*&name, *&number);
				 
				 number->setData((long)DecimalDigits);
				 *name = "DecimalDigits";
				 param->setUAPLong(*&name, *&number);
				 
				 number->setData((long)NumPrecRadix);
				 *name = "NumPrecRadix";
				 param->setUAPLong(*&name, *&number);
				 
				 number->setData((long)Nullable);
				 *name = "Nullable";
				 param->setUAPLong(*&name, *&number);
				 
				 *value = (const char*) szRemarks;
				 *name = "Remarks";
				 param->setUAPString(*&name, *&value);
				 
				 *value = (const char*) szColumnDefault;
				 *name = "ColumnDefault";
				 param->setUAPString(*&name, *&value);
				 
				 number->setData((long)SQLDataType);
				 *name = "SQLDataType";
				 param->setUAPLong(*&name, *&number);
				 
				 number->setData((long)CharOctetLength);
				 *name = "CharOctetLength";
				 param->setUAPLong(*&name, *&number);
				 
				 number->setData((long)OrdinalPosition);
				 *name = "OrdinalPosition";
				 param->setUAPLong(*&name, *&number);
				 
				 *value = (const char*) szIsNullable;
				 *name = "IsNullable";
				 param->setUAPString(*&name, *&value);
				 
				 number->setData((long)ColumnSize);
				 *name = "ColumnSize";
				 param->setUAPLong(*&name, *&number);

				 index->setData(++i);
				 
				 UAP(lb_I_Unknown, uk)
				 QI(param, lb_I_Unknown, uk)
				 
				columns->insert(&uk, &key);
			 }
		 }
	}
	
	
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	
	return columns.getPtr();
}

lb_I_Container* LB_STDCALL lbDatabase::getPrimaryKeys() {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbDatabase::getPrimaryKeys() called." LOG_
#define TAB_LEN SQL_MAX_TABLE_NAME_LEN + 1
#define COL_LEN SQL_MAX_COLUMN_NAME_LEN + 1
	UAP_REQUEST(getModuleInstance(), lb_I_Container, PrimaryKeys)
	PrimaryKeys++;

	UCHAR TableCatalog[TAB_LEN];
	UCHAR TableSchema[TAB_LEN];
	UCHAR TableName[TAB_LEN];
	UCHAR ColumnName[COL_LEN];
	UCHAR ColumnName_V2[COL_LEN];
	
	SQLSMALLINT KeySequence;

	SQLINTEGER cbTableCatalog;
	SQLINTEGER cbTableSchema;
	SQLINTEGER cbTableName;
	SQLINTEGER cbColumnName;
	SQLINTEGER cbColumnName_V2;
	SQLINTEGER cbKeySequence;

	
	SQLHSTMT      hstmt;
	SQLRETURN     retcode;
	
		
	retcode = SQLAllocStmt(hdbc, &hstmt); /* Statement handle */
	
	if (retcode != SQL_SUCCESS)
	{
		_LOG << "Error: Failed to get statement handle from database connection!" LOG_
		return PrimaryKeys.getPtr();
	}

	UAP(lb_I_Container, tables)
	
	
	tables = getTables();
	
	
	while (tables->hasMoreElements() == 1) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Parameter, param)
		UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
		UAP_REQUEST(getModuleInstance(), lb_I_String, tablename)
		uk = tables->nextElement();
		QI(uk, lb_I_Parameter, param)
			
		*paramname = "TableName";
		param->getUAPString(*&paramname, *&tablename);
		
		retcode = SQLPrimaryKeys(hstmt, NULL, 0, NULL, 0, (SQLCHAR*) tablename->charrep(), SQL_NTS);
		
		UAP_REQUEST(getModuleInstance(), lb_I_Long, index)
		UAP(lb_I_KeyBase, key)
		QI(index, lb_I_KeyBase, key)
			
		long i = 0;
		
		if  ((retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO)) {
			SQLBindCol(hstmt, 1, SQL_C_CHAR, TableCatalog, TAB_LEN, &cbTableCatalog);
			SQLBindCol(hstmt, 2, SQL_C_CHAR, TableSchema, TAB_LEN, &cbTableSchema);
			SQLBindCol(hstmt, 3, SQL_C_CHAR, TableName, TAB_LEN, &cbTableName);
			SQLBindCol(hstmt, 4, SQL_C_CHAR, ColumnName, COL_LEN, &cbColumnName);
			SQLBindCol(hstmt, 5, SQL_C_SSHORT, &KeySequence, TAB_LEN, &cbKeySequence);
			SQLBindCol(hstmt, 6, SQL_C_CHAR, ColumnName_V2, COL_LEN, &cbColumnName_V2);
		} else {
			_LOG << "lbDatabase::getPrimaryKeys() failed with call to SQLPrimaryKeys!" LOG_
			
			_dbError_STMT("Error message from driver: ", hstmt);
		}
		
		while ((retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO)) {
			
			/* Fetch and display the result set. This will be a list of the */
			/* columns in the primary key of the ORDERS table. */
			
			retcode = SQLFetch(hstmt);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
				UAP_REQUEST(getModuleInstance(), lb_I_Long, number)
				UAP_REQUEST(getModuleInstance(), lb_I_String, name)
				UAP_REQUEST(getModuleInstance(), lb_I_String, value)
				
				*name = "TableCatalog";
				*value = (const char*) TableCatalog;
				param->setUAPString(*&name, *&value);
				*name = "TableSchema";
				*value = (const char*) TableSchema;
				param->setUAPString(*&name, *&value);
				*name = "TableName";
				*value = (const char*) TableName;
				param->setUAPString(*&name, *&value);
				*name = "ColumnName";
				*value = (const char*) ColumnName;
				param->setUAPString(*&name, *&value);
				*name = "ColumnName_V2";
				*value = (const char*) ColumnName_V2;
				param->setUAPString(*&name, *&value);
				
				*name = "KeySequence";
				number->setData(KeySequence);
				param->setUAPLong(*&name, *&number);
				
				index->setData(++i);
				
				UAP(lb_I_Unknown, uk)
					QI(param, lb_I_Unknown, uk)
#ifdef bla
					_LOG << "Insert a primary key entry: TableCatalog=" << (const char*) TableCatalog << 
					", TableSchema=" << (const char*) TableSchema << 
					", TableName=" << (const char*) TableName << 
					", ColumnName=" << (const char*) ColumnName << 
					", ColumnName_V2=" << (const char*) ColumnName_V2 LOG_
#endif			
					
					PrimaryKeys->insert(&uk, &key);
			}	
		}
		SQLFreeStmt(hstmt, SQL_CLOSE);
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	
	
	PrimaryKeys->finishIteration();
	return PrimaryKeys.getPtr();
}

lb_I_Container* LB_STDCALL lbDatabase::getForeignKeys() {
	lbErrCodes err = ERR_NONE;
#define TAB_LEN SQL_MAX_TABLE_NAME_LEN + 1
#define COL_LEN SQL_MAX_COLUMN_NAME_LEN + 1
	UAP_REQUEST(getModuleInstance(), lb_I_Container, ForeignKeys)
	ForeignKeys++;
	
	UCHAR PKTableCatalog[TAB_LEN];
	UCHAR PKTableSchema[TAB_LEN];
	UCHAR PKTableName[TAB_LEN];
	UCHAR PKTableColumnName[COL_LEN];

	UCHAR FKTableCatalog[TAB_LEN];
	UCHAR FKTableSchema[TAB_LEN];
	UCHAR FKTableName[TAB_LEN];
	UCHAR FKTableColumnName[COL_LEN];

	SQLSMALLINT KeySequence;
	SQLSMALLINT UpdateRule;
	SQLSMALLINT DeleteRule;

	SQLINTEGER cbKeySequence;
	SQLINTEGER cbUpdateRule;
	SQLINTEGER cbDeleteRule;


	SQLINTEGER cbPKTableCatalog;
	SQLINTEGER cbPKTableSchema;
	SQLINTEGER cbPKTableName;
	SQLINTEGER cbPKTableColumnName;

	SQLINTEGER cbFKTableCatalog;
	SQLINTEGER cbFKTableSchema;
	SQLINTEGER cbFKTableName;
	SQLINTEGER cbFKTableColumnName;

	SQLHSTMT		hstmt;

	retcode = SQLAllocStmt(hdbc, &hstmt); /* Statement handle */
	
	if (retcode != SQL_SUCCESS)
	{
		_LOG << "Error: Failed to get statement handle from database connection!" LOG_
		return ForeignKeys.getPtr();
	}

	
	SQLBindCol(hstmt, 1, SQL_C_CHAR, PKTableCatalog, TAB_LEN, &cbPKTableCatalog);
	SQLBindCol(hstmt, 2, SQL_C_CHAR, PKTableSchema, TAB_LEN, &cbPKTableSchema);
	SQLBindCol(hstmt, 3, SQL_C_CHAR, PKTableName, TAB_LEN, &cbPKTableName);
	SQLBindCol(hstmt, 4, SQL_C_CHAR, PKTableColumnName, COL_LEN, &cbPKTableColumnName);
	
	SQLBindCol(hstmt, 5, SQL_C_CHAR, FKTableCatalog, TAB_LEN, &cbFKTableCatalog);
	SQLBindCol(hstmt, 6, SQL_C_CHAR, FKTableSchema, TAB_LEN, &cbFKTableSchema);
	SQLBindCol(hstmt, 7, SQL_C_CHAR, FKTableName, TAB_LEN, &cbFKTableName);
	SQLBindCol(hstmt, 8, SQL_C_CHAR, FKTableColumnName, COL_LEN, &cbFKTableColumnName);
	
	
	SQLBindCol(hstmt, 9, SQL_C_SSHORT, &KeySequence, TAB_LEN, &cbKeySequence);
	SQLBindCol(hstmt, 10, SQL_C_SSHORT, &UpdateRule, TAB_LEN, &cbUpdateRule);
	SQLBindCol(hstmt, 11, SQL_C_SSHORT, &DeleteRule, TAB_LEN, &cbDeleteRule);
	
	
	UAP(lb_I_Container, tables)
	
	
	tables = getTables();
	
	
	while (tables->hasMoreElements() == 1) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Parameter, param)
		UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
		UAP_REQUEST(getModuleInstance(), lb_I_String, tablename)
		uk = tables->nextElement();
		QI(uk, lb_I_Parameter, param)
			
		*paramname = "TableName";
		param->getUAPString(*&paramname, *&tablename);
		
		retcode = SQLForeignKeys(hstmt, NULL, 0, NULL, 0, (SQLCHAR*) tablename->charrep(), SQL_NTS, NULL, 0, NULL, 0, NULL, 0);        
		
		UAP_REQUEST(getModuleInstance(), lb_I_Long, index)
			UAP(lb_I_KeyBase, key)
			QI(index, lb_I_KeyBase, key)
			
			long i = 0;
		
		while ((retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO)) {
			retcode = SQLFetch(hstmt);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
				UAP_REQUEST(getModuleInstance(), lb_I_Long, number)
				UAP_REQUEST(getModuleInstance(), lb_I_String, name)
				UAP_REQUEST(getModuleInstance(), lb_I_String, value)
				
				*name = "PKTableCatalog";
				*value = (const char*) PKTableCatalog;
				param->setUAPString(*&name, *&value);
				*name = "PKTableSchema";
				*value = (const char*) PKTableSchema;
				param->setUAPString(*&name, *&value);
				*name = "PKTableName";
				*value = (const char*) PKTableName;
				param->setUAPString(*&name, *&value);
				*name = "PKTableColumnName";
				*value = (const char*) PKTableColumnName;
				param->setUAPString(*&name, *&value);
				
				*name = "FKTableCatalog";
				*value = (const char*) FKTableCatalog;
				param->setUAPString(*&name, *&value);
				*name = "FKTableSchema";
				*value = (const char*) FKTableSchema;
				param->setUAPString(*&name, *&value);
				*name = "FKTableName";
				*value = (const char*) FKTableName;
				param->setUAPString(*&name, *&value);
				*name = "FKTableColumnName";
				*value = (const char*) FKTableColumnName;
				param->setUAPString(*&name, *&value);
				
				
				
				*name = "KeySequence";
				number->setData(KeySequence);
				param->setUAPLong(*&name, *&number);
				
				*name = "UpdateRule";
				number->setData(UpdateRule);
				param->setUAPLong(*&name, *&number);
				
				*name = "DeleteRule";
				number->setData(DeleteRule);
				param->setUAPLong(*&name, *&number);
				
				index->setData(++i);
				
				UAP(lb_I_Unknown, uk)
					QI(param, lb_I_Unknown, uk)
					
					ForeignKeys->insert(&uk, &key);
			}
		}
		SQLFreeStmt(hstmt, SQL_CLOSE);
	}
	
	SQLFreeStmt(hstmt, SQL_DROP);

	ForeignKeys->finishIteration();
	return ForeignKeys.getPtr();
}

/*...svoid _dbError_STMT\40\char\42\ lp\44\ HSTMT hstmt\41\:0:*/
void _dbError_STMT(char* lp, HSTMT hstmt) {
	SQLCHAR  SqlState[6], SQLStmt[100], Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER NativeError;
	SQLSMALLINT i, MsgLen;
	SQLRETURN  rc;

	i = 1;
	
	while ((rc = SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, i, SqlState, &NativeError,
	      Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) {
	
		_LOG << "Error in lbQuery: (" << lp << ") " << 
			(const char*) SqlState << ": " << (int) NativeError << " - " << (const char*) Msg LOG_
		i++;
	}
}
/*...e*/
/*...svoid _dbError_ENV\40\char\42\ lp\44\ HENV henv\41\:0:*/
void _dbError_ENV(char* lp, HENV henv) {
	SQLCHAR  SqlState[6], SQLStmt[100], Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER NativeError;
	SQLSMALLINT i, MsgLen;
	SQLRETURN  rc;

	i = 1;
	
	while ((rc = SQLGetDiagRec(SQL_HANDLE_ENV, henv, i, SqlState, &NativeError,
	      Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) {
	
		_CL_LOG << "Error in lbQuery: (" << lp << ") " << 
			SqlState << ": " << (int) NativeError << " - " << Msg LOG_
		i++;
	}
}
/*...e*/
/*...svoid _dbError_DBC\40\char\42\ lp\44\ HDBC hdbc\41\:0:*/
void _dbError_DBC(char* lp, HDBC hdbc) {
	SQLCHAR  SqlState[6], SQLStmt[100], Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER NativeError;
	SQLSMALLINT i, MsgLen;
	SQLRETURN  rc;

	i = 1;
	
	while ((rc = SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, i, SqlState, &NativeError,
	      Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) {
	
		_CL_LOG << "Error in lbQuery: (" << lp << ") " << 
			SqlState << ": " << (int) NativeError << " - " << Msg LOG_
		i++;
	}
}
/*...e*/

/*...sclass lbDBInterfaceRepository:0:*/
class lbDBInterfaceRepository : public lb_I_InterfaceRepository
{
public:
        lbDBInterfaceRepository();
        virtual ~lbDBInterfaceRepository();

        DECLARE_LB_UNKNOWN()

	void LB_STDCALL setCurrentSearchInterface(const char* iface);
	lb_I_FunctorEntity* LB_STDCALL getFirstEntity();

	void initIntefaceList();

	int errorsOccured;
	
	// Created once and contains all interface nodes
	unsigned int interfaces; // current interface index
	unsigned int len;
	
	/**
	 * Indicates the current search mode (currently only over interfaces).
	 */
	int CurrentSearchMode;
	char* searchArgument;
	
	/**
	 * Indicates an invalid search status like 
	 * 	noPrevious interface;
	 *	noNext     interface;
	 *
	 * Note:	Moving to first or last interface resets any invalid status.
	 */
	int invalidSearchStatus;
private:
        RETCODE  retcode;
        HENV     henv;
        HDBC     hdbc;
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDBInterfaceRepository)
        ADD_INTERFACE(lb_I_InterfaceRepository)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfDBInterfaceRepository, lbDBInterfaceRepository)

lbDBInterfaceRepository::lbDBInterfaceRepository() {	
	manager = NULL;
	ref = STARTREF;
	henv = 0;
	hdbc = 0;

#ifdef bla

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




	retcode = SQLAllocConnect(henv, &hdbc); /* Connection handle */

	if (retcode != SQL_SUCCESS)
        {
        	_dbError("SQLAllocConnect()", henv);
        	SQLFreeEnv(henv);
        	return ERR_DB_CONNECT;
        }	
        
	retcode = SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 15); /* Set login timeout to 15 seconds. */

        if (retcode != SQL_SUCCESS)
        {
                _dbError("SQLSetConnectOption()", hdbc);
                SQLFreeEnv(henv);
                return ERR_DB_CONNECT;
        }

	retcode = SQLSetConnectAttr(hdbc, SQL_ATTR_ODBC_CURSORS, SQL_CUR_USE_IF_NEEDED, 0);

        if (retcode != SQL_SUCCESS)
        {
                _dbError("SQLSetConnectAttr()", hdbc);
                SQLFreeEnv(henv);
                return ERR_DB_CONNECT;
        }

	retcode = SQLConnect(hdbc, (unsigned char*) "lbDMFConfig", SQL_NTS, 
				   (unsigned char*) "lbDMF", SQL_NTS, 
				   (unsigned char*) "lbDMF", SQL_NTS); /* Connect to data source */

	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
        {
        	_dbError( "SQLConnect()", hdbc);
		_LOG << "Connection to database failed." LOG_
        	SQLFreeEnv(henv);
        	return ERR_DB_CONNECT;
        } else {
//		SQLFreeEnv(henv);
		printf("Connection succeeded.\n");
        }

        retcode = SQLSetConnectOption(hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);

	if (retcode != SQL_SUCCESS)
	{
	        _dbError("SQLSetConnectOption(SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON)", hdbc);
	        SQLFreeEnv(henv);
	        return ERR_DB_CONNECT;
	}
        

#endif



}

lbDBInterfaceRepository::~lbDBInterfaceRepository() {
}

lbErrCodes lbDBInterfaceRepository::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbDBInterfaceRepository::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL lbDBInterfaceRepository::setCurrentSearchInterface(const char* iface) {
	searchArgument = strdup(iface);
	interfaces = 0;
	CurrentSearchMode = 1;
	
//	initIntefaceList();
}

/*...slb_I_FunctorEntity\42\ LB_STDCALL lbDBInterfaceRepository\58\\58\getFirstEntity\40\\41\:0:*/
lb_I_FunctorEntity* LB_STDCALL lbDBInterfaceRepository::getFirstEntity() {
	if (CurrentSearchMode == 0) {
		printf("SearchMode not set. Please call first lbDBInterfaceRepository::setCurrentSearchInterface(char* iface)\nOr any further other setCurrentSearch<Mode>(char* argument) function\n");
		return NULL;
	}
	
	if (CurrentSearchMode != 1) {
		printf("SearchMode currently not provided.\n");
		return NULL;
	}

#ifdef bla
	// Search for that node, containing specifed interface.
	for (interfaces; interfaces < len; interfaces++) {
/*...sOld DOM code:0:*/
#ifdef bla	
		DOM_Node node = DOMlist.item(interfaces);
		
		DOM_NamedNodeMap attributeMap = node.getAttributes();
		
		DOM_Node InterfaceName = attributeMap.getNamedItem(DOMString("Name"));
		
		if (InterfaceName.getNodeValue().equals(DOMString(searchArgument))) {
		
			DOMString nodename = node.getNodeName();
		
			char* module = NULL;
			char* functor = NULL;
		
			// Navidate to the Function node to get the functor name
			node = node.getParentNode().getParentNode();
			DOM_NodeList nodeList = node.getChildNodes();
		
/*...sfind function name value:24:*/
		// Find function name
		for (unsigned int index = 0; index < nodeList.getLength(); index++) {
			node = nodeList.item(index);
			if (node.getNodeName().equals(DOMString("FunctionName"))) break;
		}
				
		attributeMap = node.getAttributes();

		DOM_Node an_attr = attributeMap.getNamedItem(DOMString("Name"));

		if (an_attr == NULL) {
		        printf("Error: Attribute not found\n"); // LOG_

		        return NULL;
		        
		}
/*...e*/
			DOMString functorName = an_attr.getNodeValue();

			DOM_Node moduleNode = node.getParentNode().getParentNode().getParentNode();
			nodeList = moduleNode.getChildNodes();
			
/*...sfind module for that functor:24:*/

			DOM_Node moduleNameNode;

	                // Find module name
	                for (int i = 0; i < nodeList.getLength(); i++) {
	                        moduleNameNode = nodeList.item(i);
	                        if (moduleNameNode.getNodeName().equals(DOMString("ModuleName"))) break;
	                }			

			attributeMap = moduleNameNode.getAttributes();
			an_attr = attributeMap.getNamedItem(DOMString("Name"));
			
			if (an_attr == NULL) {
			        printf("Error: Attribute not found\n"); 
			        for (unsigned int l = 0; l < attributeMap.getLength(); l++) {
			        	DOM_Node n = attributeMap.item(l);
			        	printf("Debug of Node ");
			        	moduleNode.getNodeName().print();
			        	printf(" has Attribute ");
			        	n.getNodeName().println();
			        }

			        return NULL;

			}
			
/*...e*/

			DOMString moduleName = an_attr.getNodeValue();

			char* temp = functorName.transcode();
			functor = strdup(temp);
			functorName.deletetranscoded(temp);
			
			temp = moduleName.transcode();
			module = strdup(temp);
			moduleName.deletetranscoded(temp);
			
			
			lbFunctorEntity* fe = new lbFunctorEntity;
			fe->setModuleManager(this->getModuleManager(), __FILE__, __LINE__);
			lb_I_FunctorEntity* _fe = NULL;
			fe->queryInterface("lb_I_FunctorEntity", (void**) &_fe, __FILE__, __LINE__);
			
			_fe->setModule(module);
			_fe->setFunctor(functor);
			
			
			return _fe;
			
		}
/*...sRubbish:0:*/
#ifdef bla
		if (value == DOMString(iface)) {
/*...sget the nodes\44\ that contains the data:24:*/
			// Get the functor and module for creation of FunctorEntity
			DOM_Node module = node.getParentNode();
			module = module.getParentNode();
			module = module.getParentNode();
			module = module.getParentNode();
			
			DOM_Node functor = node.getParentNode();
			functor = functor.getParentNode();
/*...e*/

			DOM_NodeList DOMlist = module.getChildNodes();
			int count = DOMlist.getLength();
			
			DOM_Node child;
			char* modulename = NULL;
			char* functorname = NULL;
			
/*...sget module name:24:*/
			for (int ii = 0; ii < count; ii++) {
				child = DOMlist.item(ii);
				
				if (child.getNodeName() == DOMString("ModuleName")) {
					DOM_NamedNodeMap attributeMap = child.getAttributes();

					if (attributeMap == NULL) {
					        _CL_VERBOSE << "Error: This node is not of type ELEMENT" LOG_

					        return NULL;
					}

					DOM_Node an_attr = attributeMap.getNamedItem(DOMString("Name"));

					if (an_attr == NULL) {
					        _CL_VERBOSE << "Error: Attribute not found" LOG_

					        return NULL;
					}

					DOMString value = an_attr.getNodeValue();
					char* temp = value.transcode();
					
					// Bugfix in XML4C - do cleanup directly
					modulename = strdup(temp);
					value.deletetranscoded(temp);
					temp = NULL;
					break;
				}
			}
/*...e*/
			
			DOMlist = functor.getChildNodes();
			count = DOMlist.getLength();
			
/*...sget functor name:24:*/
			for (ii = 0; ii < count; ii++) {
				child = DOMlist.item(ii);
				
				if (child.getNodeName() == DOMString("FunctionName")) {
					DOM_NamedNodeMap attributeMap = child.getAttributes();

					if (attributeMap == NULL) {
					        _CL_VERBOSE << "Error: This node is not of type ELEMENT" LOG_

					        return NULL;
					}

					DOM_Node an_attr = attributeMap.getNamedItem(DOMString("Name"));

					if (an_attr == NULL) {
					        _CL_VERBOSE << "Error: Attribute not found" LOG_

					        return NULL;
					}

					DOMString value = an_attr.getNodeValue();
					char* temp = value.transcode();
					
					// Bugfix in XML4C - do cleanup directly
					functorname = strdup(temp);
					value.deletetranscoded(temp);
					temp = NULL;
				}
			}
/*...e*/

			printf("lbDBInterfaceRepository got functor %s in module %s for %s\n", functorname, modulename, iface);
			
			break;
		}
#endif
/*...e*/
#endif
/*...e*/
	}
#endif

	return NULL;
}
/*...e*/
#ifdef bla
/*...slbErrCodes LB_STDCALL lbDBInterfaceRepository\58\\58\parse\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDBInterfaceRepository::parse() {
	lbErrCodes err = ERR_NONE;
	char *filename = getenv("LBHOSTCFGFILE");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	COUT << "Parse file '" << filename << "'..." << ENDL;
#endif
/*...e*/

	if (filename != NULL) {

/*...sSetup objects:12:*/
	    // Begin parsing...
	    DOMParser parser;
	    parser.setDoValidation(true);

	    parser.setErrorHandler(errReporter);
		
/*...e*/


/*...stry parsing \40\no explicid allocation\41\:12:*/
	    // Parse the file and catch any exceptions that propogate out
	    try	
		{
		    errorsOccured = 0;
	            parser.parse(filename);
	
	            doc = parser.getDocument();
		}

		catch (const XMLException& )
	        {
			COUT << "Parse error\n" << ENDL;
			errorsOccured = 1;
			return ERR_XML_NOFILE;
		}
/*...e*/

	    // Clean up our parser and handler
	    //delete handler;

	} else return ERR_NO_ENVIRONMENT;
	return err;
}
/*...e*/
#endif
/*...svoid lbDBInterfaceRepository\58\\58\initIntefaceList\40\\41\:0:*/
void lbDBInterfaceRepository::initIntefaceList() {
	char* name = NULL;
	char* savename = NULL;
        savename = strdup("#document/dtdHostCfgDoc/Modules/Module/Functions/Function/Functor/InterfaceName");
        name = strrchr(savename, '/');
        if (name == NULL) name = savename;
//        DOMlist = doc.getElementsByTagName(((name[0] == '/') ? &name[1] : name));
//        len = DOMlist.getLength();
        // Cleanup
        delete [] savename;
}
/*...e*/
/*...e*/
#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";

        switch (reason) {
                case DLL_PROCESS_ATTACH:
                	TRMemOpen();

			if (isSetTRMemTrackBreak()) TRMemSetAdrBreakPoint(getTRMemTrackBreak(), 0);
			
                	TRMemSetModuleName(__FILE__);
                	
                	_CL_VERBOSE << "DLL lbDB loaded." LOG_
                	
                        if (situation) {
                                _CL_VERBOSE << "DLL statically loaded." LOG_
                        }
                        else {
                                _CL_VERBOSE << "DLL dynamically loaded.\n" LOG_
                        }
                        break;
                case DLL_THREAD_ATTACH:
                        _CL_VERBOSE << "New thread starting.\n" LOG_
                        break;
                case DLL_PROCESS_DETACH:                        
                       	_CL_VERBOSE << "DLL_PROCESS_DETACH for " << __FILE__ LOG_
                        if (situation)
                        {
                        	//if (lbDatabase::connPooling != NULL) lbDatabase::connPooling->release(__FILE__, __LINE__);

                                _CL_VERBOSE << "DLL released by system." LOG_
                        }
                        else
                        {
                        	// Cleanup the static container holding open connections.
                        	
                        	//if (lbDatabase::connPooling != NULL) lbDatabase::connPooling->release(__FILE__, __LINE__);
                                
                                _CL_VERBOSE << "DLL released by program.\n" LOG_
                        }
                        break;
                case DLL_THREAD_DETACH:
                        _CL_VERBOSE << "Thread terminating.\n" LOG_
                default:
                        return FALSE;
        }
        
        return TRUE;
}
/*...e*/
#endif

    

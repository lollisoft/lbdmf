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
#define USE_SQLITE

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


#define LB_DB_DLL
#include <lbdb-module.h>

//#define USE_FETCH_SCROLL

extern "C" {
// Here I may collide with the both sql.h versions (ODBC and Cody Pisto's version)
//#include <sqlitefk/src/sql.h>
#include <sql.h>
#include <sqlext.h>
}
#include "lbDB.h"

#define SZLEN 300
#define SZDATELEN 24

#ifndef WINDOWS
#define lstrcpy strcpy
#endif

#include "../include/DatabaseLayer.h"
#include "../include/DatabaseErrorCodes.h"
#include "../include/DatabaseLayerException.h"
#include "../include/ResultSetMetaData.h"

#ifdef USE_SQLITE
  #include "../include/SqliteDatabaseLayer.h"
#elif USE_FIREBIRD
  #include "../include/FirebirdDatabaseLayer.h"
#elif USE_POSTGRESQL
  #include "../include/PostgresDatabaseLayer.h"
#elif USE_MYSQL
  #include "../include/MysqlDatabaseLayer.h"
#elif USE_ORACLE
  #include "../include/OTLDatabaseLayer.h"
#elif USE_ODBC
  #include "../include/OdbcDatabaseLayer.h"
#elif USE_TDS
  #include "../include/TdsDatabaseLayer.h"
#endif


// Glogal variable for lbDatabaseLayerQuery::getTableName()
// Would be deleted in lbDatabaseLayerQuery::~lbDatabaseLayerQuery()

char *lpszTable = NULL;
int lpszSize = 0;

void _dbError_STMT(char* lp, HSTMT hstmt);
void _dbError_ENV(char* lp, HENV henv);
void _dbError_DBC(char* lp, HDBC hdbc);

#define TAB_LEN 128+1
#define REM_LEN 254+1
#define COL_LEN 100


class lbDatabaseLayerQuery;
class lbDatabaseLayerBoundColumn;

class lbDatabaseLayerBoundColumns: public lb_I_ColumnBinding {
public:	
	lbDatabaseLayerBoundColumns() { ref = STARTREF; ArraySize = 1; }
	virtual ~lbDatabaseLayerBoundColumns() {
		_CL_VERBOSE << "lbDatabaseLayerBoundColumns::~lbDatabaseLayerBoundColumns() called." LOG_
	}
	
	DECLARE_LB_UNKNOWN()

	lb_I_Container*		LB_STDCALL getBoundColumns();
	lbErrCodes			LB_STDCALL setBoundColumns(lb_I_Container* bc);

	lb_I_BoundColumn*	LB_STDCALL getBoundColumn(int column);
	int					LB_STDCALL getColumnCount();

	lbErrCodes			LB_STDCALL setQuery(lb_I_Query* q, lb_I_Container* ReadonlyColumns);

	int					LB_STDCALL getMode();

        
	lbErrCodes			LB_STDCALL getString(int column, lb_I_String* instance);
	lbErrCodes			LB_STDCALL getLong(int column, lb_I_Long* instance);
	lbErrCodes			LB_STDCALL getString(const char* column, lb_I_String* instance);
	lbErrCodes			LB_STDCALL setString(char* column, lb_I_String* instance);

	void				LB_STDCALL unbindReadonlyColumns();
	void				LB_STDCALL rebindReadonlyColumns();

	void				LB_STDCALL indicateNullValues();
	bool				LB_STDCALL setNull(int pos, bool b);
	bool				LB_STDCALL setNull(char const * name, bool b);

	bool				LB_STDCALL isNullable(int pos);
	bool				LB_STDCALL isNullable(char const * name);
	bool				LB_STDCALL isNull(int pos);
	bool				LB_STDCALL isNull(char const * name);

	bool				LB_STDCALL isBound(int pos);
	bool				LB_STDCALL isBound(char const * name);

	lb_I_Query::lbDBColumnTypes LB_STDCALL getColumnType(int pos);
	lb_I_Query::lbDBColumnTypes LB_STDCALL getColumnType(char* name);
	int					LB_STDCALL getColumnIndex(const char* name);

	void				LB_STDCALL setReadonly(char* column, bool updateable);
	bool				LB_STDCALL getReadonly(char* column);

	void				LB_STDCALL rebind();
	void				LB_STDCALL unbind();
	
	void				LB_STDCALL add();
	void				LB_STDCALL finishadd();
	
	bool				LB_STDCALL hasValidData();
	void				LB_STDCALL invalidateData();
		
	int					LB_STDCALL getArraySize() { return ArraySize; }

private:
	UAP(lb_I_Container, boundColumns)
	UAP(lb_I_Container, ColumnNameMapping)
	int ArraySize;
	lbDatabaseLayerQuery* query;
};

/** \brief Implementation using Databaselayer backend.
 */
class lbDatabaseLayerQuery :
public lb_I_Query
{
public:
	lbDatabaseLayerQuery(int readonly = 1) { 
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
		cursor = 0;
		haveData = false;
		mode = 0;
		_dataFetched = false;
		_autoRefresh = false;
		szSql = NULL;
		preparingFKColumns = 0;
		cursorname = NULL;
		fetchstatus = 0;
		theResult = NULL;
		dbName = NULL;
		cachedRowIndex = 1;
		skipAutoQuery = false;
		numPrimaryKeys = 0;
		max_in_cursor_default = max_in_cursor = 100;
		
		if (ReadOnlyColumns == NULL) {
			REQUEST(getModuleInstance(), lb_I_Container, ReadOnlyColumns)
		}
		if (binaryDataColumns == NULL) {
			REQUEST(getModuleInstance(), lb_I_Container, binaryDataColumns)
			binaryDataColumns->setCloning(false); // Don't clone these big data.
		}
		if (cachedDataColumns == NULL) {
			REQUEST(getModuleInstance(), lb_I_Container, cachedDataColumns)
		}
		if (cachedDataRows == NULL) {
			REQUEST(getModuleInstance(), lb_I_Container, cachedDataRows)
		}
		if (cachedColumnNames == NULL) {
			REQUEST(getModuleInstance(), lb_I_Container, cachedColumnNames)
		}
		if (cachedColumnTableNames == NULL) {
			REQUEST(getModuleInstance(), lb_I_Container, cachedColumnTableNames)
		}
		if (cachedColumnTypes == NULL) {
			REQUEST(getModuleInstance(), lb_I_Container, cachedColumnTypes)
		}
		if (cachedColumnPrimaryColumns == NULL) {
			REQUEST(getModuleInstance(), lb_I_Container, cachedColumnPrimaryColumns)
		}
		if (cachedColumnForeignColumnsToPrimaryColumns == NULL) {
			REQUEST(getModuleInstance(), lb_I_Container, cachedColumnForeignColumnsToPrimaryColumns)
		}
		
	}
	
	virtual ~lbDatabaseLayerQuery() {
		close();
		if (szSql != NULL) {
			_CL_VERBOSE << "lbDatabaseLayerQuery::~lbDatabaseLayerQuery() called. (" << szSql << "). Refcount of ReadOnlyColumns is: " << ReadOnlyColumns->getRefCount() LOG_
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
		if (cursorname != NULL) free (cursorname);
	}
	
	DECLARE_LB_UNKNOWN()
	
	virtual						lbErrCodes LB_STDCALL setView(lb_I_ColumnBinding* cb);
	
	virtual						lbErrCodes LB_STDCALL registerView(lb_I_MVC_View* view);
	virtual						lbErrCodes LB_STDCALL unregisterView(lb_I_MVC_View* view);
	
	void						LB_STDCALL skipFKCollecting();
	void						LB_STDCALL enableFKCollecting();
	void						LB_STDCALL prepareFKList();
	
	lb_I_String*				LB_STDCALL getTableName(char* columnName = NULL);
	
	void						LB_STDCALL dbError(char* lp, HSTMT hstmt);
	
	void						LB_STDCALL PrintData(bool reverse);
	void						LB_STDCALL PrintCurrent();
	void						LB_STDCALL PrintHeader();
	void						LB_STDCALL PrintFooter();
	
	void						LB_STDCALL skipPeeking() { peeking = false; }
	
	lbErrCodes					LB_STDCALL query(char* q, bool bind);
	
	lbErrCodes					LB_STDCALL bind();
	void						LB_STDCALL unbind();
	
	bool						LB_STDCALL dataFetched();
	
	lbErrCodes					LB_STDCALL add();
	int							LB_STDCALL isAdding() { return mode; }
	
	lbErrCodes					LB_STDCALL remove();
	
	lbErrCodes					LB_STDCALL update();
	
	int							LB_STDCALL getColumns();
	bool						LB_STDCALL hasColumnName(char* name);
	
	lb_I_String*				LB_STDCALL getColumnName(int col);
	
	int							LB_STDCALL hasFKColumn(char* FKName);
	
	int							LB_STDCALL getFKColumns();
	
	lb_I_String*				LB_STDCALL getFKColumn(int pos);
	
	lb_I_String*				LB_STDCALL getFKColumn(char* table, char* primary);
	
	lb_I_String*				LB_STDCALL getPKTable(char const * FKName);
	lb_I_String*				LB_STDCALL getPKColumn(char const * FKName);
	
	int							LB_STDCALL getPKColumns();
	lb_I_String*				LB_STDCALL getPKColumn(int pos);
	
	bool						LB_STDCALL isFirst();
	bool						LB_STDCALL isLast();
	
	bool						LB_STDCALL isNullable(int pos);
	bool						LB_STDCALL isNullable(char const * name);
	bool						LB_STDCALL isNull(int pos);
	bool						LB_STDCALL isNull(char const * name);
	bool						LB_STDCALL setNull(int pos, bool b = true);
	bool						LB_STDCALL setNull(char const * name, bool b = true);
	
	lb_I_Query::lbDBColumnTypes	LB_STDCALL getColumnType(int pos);
	lb_I_Query::lbDBColumnTypes	LB_STDCALL getColumnType(char* name);
	
	lbDBCaseSensity				LB_STDCALL getCaseSensity();
	
	void						LB_STDCALL setReadonly(char* column, bool updateable = true);
	bool						LB_STDCALL getReadonly(char* column);
	
	/* Navigation */
	
	int							LB_STDCALL getPosition() { return cursor; }
	lbErrCodes					LB_STDCALL absolute(int pos);
	
	lbErrCodes					LB_STDCALL first();
	lbErrCodes					LB_STDCALL next();
	lbErrCodes					LB_STDCALL previous();
	lbErrCodes					LB_STDCALL last();
	char*						LB_STDCALL setWhereClause(const char* query, char* where);
	
	char*						LB_STDCALL addWhereClause(const char* query, char* where);
	
	void						LB_STDCALL setAutoRefresh(bool b);
	
	lbErrCodes					LB_STDCALL reopen();
	void						LB_STDCALL close();
	lbErrCodes					LB_STDCALL open();
	
#ifdef UNBOUND
	virtual char*				LB_STDCALL getChar(int column);
#endif
#ifndef UNBOUND       
	lb_I_String*				LB_STDCALL getAsString(int column);
	lb_I_String*				LB_STDCALL getAsString(const char* column);
	lb_I_Long*					LB_STDCALL getAsLong(int column);
	lbErrCodes					LB_STDCALL setString(lb_I_String* columnName, lb_I_String* value);
	
	lb_I_BinaryData*			LB_STDCALL getBinaryData(int column);
	lb_I_BinaryData*			LB_STDCALL getBinaryData(const char* column);
	lbErrCodes					LB_STDCALL setBinaryData(int column, lb_I_BinaryData* value);
	lbErrCodes					LB_STDCALL setBinaryData(const char* column, lb_I_BinaryData* value);
#endif        
	
	lbErrCodes					LB_STDCALL init(DatabaseLayer* dbLayer, char* dbname, bool ro = false);
	
	lbErrCodes					LB_STDCALL executeDirect(char* SQL);
	
	/** \brief Build a cursor set.
	 * Generates a list of keys in a 'window' of the main resultset.
	 */
	lbErrCodes					LB_STDCALL nextCursorSet(long last_id);

	/** \brief Build a cursor set.
	 * Generates a list of keys in a 'window' of the main resultset.
	 */
	lbErrCodes					LB_STDCALL previousCursorSet(long first_id);
	
	/** \brief Selects the current row.
	 * This function is responsible to get a row by issuing a query with cursorWhere based on currentCursorview[cursor].
	 * If there would be an under or overflow, a new query will be issued to get a new list of currentCursorview ID's.
	 * Based on overflow and underflow the correct position will be stored into cursor.
	 */
	bool						LB_STDCALL selectCurrentRow();
	
	/** \brief Select the cached row at current cachedRowIndex.
	 * A cached row is one of several rows for a statement where no cursor feature is present. The cursor behaviour therefore
	 * is implemented on cached data.
	 */
	lbErrCodes					LB_STDCALL selectCachedRow();
	
	/** \brief Create meta information.
	 */
	void						LB_STDCALL createMetaInformation();
	
	/** \brief Destroy meta information.
	 */
	void						LB_STDCALL destroyMetaInformation();
	
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
	bool    skipAutoQuery;
	int		cachedRowIndex;
	bool	haveData;
	HENV    henv;
	HDBC    hdbc;
	HSTMT   hstmt;
	char*	cursorname;
	HSTMT   hupdatestmt;
	RETCODE retcode;
	char*   szSql;
	char*	dbName;
	int		numPrimaryKeys;
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
	
	UAP(lb_I_Container, binaryDataColumns)

	/* \brief When there is a JOIN in the query or more than one table in the select statement.
	 * This container is filled with all the data from the query. Each row contains a cachedDataColumns container.
	 */
	UAP(lb_I_Container, cachedDataRows)
	UAP(lb_I_Container, cachedDataColumns)
	

	
	/* \brief Caching some meta information of the current query.
	 *
	 */
	UAP(lb_I_Container, cachedColumnTableNames)
	UAP(lb_I_Container, cachedColumnNames)
	UAP(lb_I_Container, cachedColumnTypes)

	UAP(lb_I_Container, cachedColumnPrimaryColumns)
	// Maps foreign columns to their primary columns.
	UAP(lb_I_Container, cachedColumnForeignColumnsToPrimaryColumns)

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
	
	/// Holds values in a 'window' of the current resultset.
	wxArrayString currentCursorview;
	
	// Holds the min values per window of yet determined key values.
	wxArrayInt minWindowValues;
	// Holds the max values per window of yet determined key values. The numer of elements must correspond to minWindowValues to always get a pair.
	wxArrayInt maxWindowValues;
	
	// The primary key names to be used for cursorWhere creation.
	wxArrayString primarykeys;
	wxArrayString tables;
	bool cursorFeature;
	int max_in_cursor;
	int max_in_cursor_default;
	
	// The query in some parts
	wxString plainQuery;	// The columns including 'FROM'
	wxString joinClause;	// If there are JOIN rules
	wxString whereClause;	// If there are where clauses
	wxString orderRule;		// If there are order rules
	
	wxString cursorWhere;	// Actiual cursor position
	
	// Datamanipulation helpers
	
	wxArrayString nullColumns;
	wxArrayString nullValues;
	
	wxArrayString queryColumns;
	wxArrayString queryValues;
	
	DatabaseLayer* currentdbLayer;
	DatabaseResultSet* theResult;
};

int lbDatabaseLayerQuery::skipFKCollections = 0;

/*...e*/
/*...sclass def lbDatabaseLayerBoundColumn:0:*/
class lbDatabaseLayerBoundColumn: public lb_I_BoundColumn {
public:	
	lbDatabaseLayerBoundColumn() {
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
	
	virtual ~lbDatabaseLayerBoundColumn() {
		if (columnName != NULL) {
			_CL_VERBOSE << "~lbDatabaseLayerBoundColumn('" << columnName << "') called." LOG_
			free(columnName);
		} else {
			_CL_VERBOSE << "~lbDatabaseLayerBoundColumn(?) called." LOG_
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
				_CL_VERBOSE << "lbDatabaseLayerBoundColumn::~lbDatabaseLayerBoundColumn() failed: Unknown or not supported datatype for column '" << columnName << "'" LOG_
				break;
		}
		
		if (cbBufferLength != NULL) delete[] cbBufferLength;
		
		if ((bound != 0) && (buffer != NULL)) {
			free(buffer);
			buffer = NULL;
		}
	}
	
	lbDatabaseLayerBoundColumn(const lbDatabaseLayerBoundColumn& _ref) {
		printf("lbDatabaseLayerBoundColumn(const lbDatabaseLayerBoundColumn& _ref) called\n");
	}

	void operator=(const lbDatabaseLayerBoundColumn& _ref) {
		printf("void operator=(const lbDatabaseLayerBoundColumn& _ref) called\n");
	}

	DECLARE_LB_UNKNOWN()



	virtual bool LB_STDCALL isNullable();
	virtual bool LB_STDCALL isNull();
	virtual bool LB_STDCALL isBound();
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
	void		LB_STDCALL unbind();
	
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
	SQLSMALLINT	_DataType;
	int			_column;
	void*		buffer;
	int			buffersize;
	lbDatabaseLayerQuery*	query;
	
	
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

/*...sclass lbDatabaseLayerBoundColumns:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseLayerBoundColumns)
        ADD_INTERFACE(lb_I_ColumnBinding)
END_IMPLEMENT_LB_UNKNOWN()

// lbDatabaseLayerBoundColumns does not need a functor, because lbDatabaseLayerQuery acts as a factory

/*...sunimplemented:0:*/
lbErrCodes LB_STDCALL lbDatabaseLayerBoundColumns::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbDatabaseLayerBoundColumns::setData(...) not implemented yet" LOG_
        
	return ERR_NOT_IMPLEMENTED;
}

lb_I_Container* LB_STDCALL lbDatabaseLayerBoundColumns::getBoundColumns() {
	_CL_VERBOSE << "lbDatabaseLayerBoundColumns::getBoundColumns() not implemented yet" LOG_
	return NULL;
}

lbErrCodes      LB_STDCALL lbDatabaseLayerBoundColumns::setBoundColumns(lb_I_Container* bc) {
	_CL_VERBOSE << "lbDatabaseLayerBoundColumns::setBoundColumns() not implemented yet" LOG_
	return ERR_NONE;
}
/*...e*/

bool LB_STDCALL lbDatabaseLayerBoundColumns::isBound(int pos) {
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

		return bc->isBound();
	}

	// What to answer here ??
	return false;
}

bool LB_STDCALL lbDatabaseLayerBoundColumns::isBound(char const * name) {
	int pos = getColumnIndex(name);
	return isBound(pos);
}

bool LB_STDCALL lbDatabaseLayerBoundColumns::isNull(char const * name) {
	int pos = getColumnIndex(name);
	return isNull(pos);
}

bool LB_STDCALL lbDatabaseLayerBoundColumns::isNull(int pos) {
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

bool LB_STDCALL lbDatabaseLayerBoundColumns::isNullable(char const * name) {
	int pos = getColumnIndex(name);
	return isNullable(pos);
}

bool LB_STDCALL lbDatabaseLayerBoundColumns::isNullable(int pos) {
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

void LB_STDCALL lbDatabaseLayerBoundColumns::unbind() {
	lbErrCodes err = ERR_NONE;
	
	if (boundColumns != NULL) {
		while (boundColumns->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_BoundColumn, bc)
			
			uk = boundColumns->nextElement();
			
			QI(uk, lb_I_BoundColumn, bc)
			
			bc->unbind();
		}
	}
}

/*...svoid LB_STDCALL lbDatabaseLayerBoundColumns\58\\58\rebind\40\\41\:0:*/
void LB_STDCALL lbDatabaseLayerBoundColumns::rebind() {
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

void LB_STDCALL lbDatabaseLayerBoundColumns::add() {
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

void LB_STDCALL lbDatabaseLayerBoundColumns::finishadd() {
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

void LB_STDCALL lbDatabaseLayerBoundColumns::indicateNullValues() {
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

void	LB_STDCALL lbDatabaseLayerBoundColumns::invalidateData() {
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

bool	LB_STDCALL lbDatabaseLayerBoundColumns::hasValidData() {
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


bool LB_STDCALL lbDatabaseLayerBoundColumns::setNull(char const * name, bool b) {
	lbErrCodes err = ERR_NONE;
	
	int pos = getColumnIndex(name);

	return setNull(pos, b);
}

bool LB_STDCALL lbDatabaseLayerBoundColumns::setNull(int pos, bool b) {
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

void LB_STDCALL lbDatabaseLayerBoundColumns::unbindReadonlyColumns() {
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

void LB_STDCALL lbDatabaseLayerBoundColumns::rebindReadonlyColumns() {
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

lb_I_Query::lbDBColumnTypes LB_STDCALL lbDatabaseLayerBoundColumns::getColumnType(int pos) {

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

	_LOG << "lbDatabaseLayerBoundColumns::getColumnType(int pos) returns unknown type" LOG_

	return lb_I_Query::lbDBColumnUnknown;
}

int LB_STDCALL lbDatabaseLayerBoundColumns::getColumnIndex(const char* name) {

	lbErrCodes err = ERR_NONE;
	if (boundColumns != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, stringKey) 
		stringKey->setData(name);
		UAP(lb_I_Unknown, ukdata)
		UAP(lb_I_KeyBase, key)
		
		QI(stringKey, lb_I_KeyBase, key)

		ukdata = ColumnNameMapping->getElement(&key);
		if (ukdata == NULL) {
			_LOG << "lbDatabaseLayerBoundColumns::getColumnIndex('" << name << "') returned no data !" LOG_
			
			return -1;
		}

		UAP(lb_I_Integer, pos)
		
		lbErrCodes err = ukdata->queryInterface("lb_I_Integer", (void**) &pos, __FILE__, __LINE__);
		
		return pos->getData();
	}

	return -1;
}

lb_I_Query::lbDBColumnTypes LB_STDCALL lbDatabaseLayerBoundColumns::getColumnType(char* name) {

	lbErrCodes err = ERR_NONE;
	if (boundColumns != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, stringKey) 
		stringKey->setData(name);
		UAP(lb_I_Unknown, ukdata)
		UAP(lb_I_KeyBase, key)
		
		QI(stringKey, lb_I_KeyBase, key)

		ukdata = ColumnNameMapping->getElement(&key);
		if (ukdata == NULL) {
			_LOG << "lbDatabaseLayerBoundColumns::getColumnType('" << name << "') returned no data !" LOG_
			
			return lb_I_Query::lbDBColumnUnknown;
		}

		UAP(lb_I_BoundColumn, bc)
		UAP(lb_I_Integer, pos)
		
		lbErrCodes err = ukdata->queryInterface("lb_I_Integer", (void**) &pos, __FILE__, __LINE__);
		
		return getColumnType(pos->getData());
	}

	return lb_I_Query::lbDBColumnUnknown;
}

void LB_STDCALL lbDatabaseLayerBoundColumns::setReadonly(char* column, bool updateable) {

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

bool LB_STDCALL lbDatabaseLayerBoundColumns::getReadonly(char* column) {
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

lb_I_BoundColumn* LB_STDCALL lbDatabaseLayerBoundColumns::getBoundColumn(int column) {
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

int               LB_STDCALL lbDatabaseLayerBoundColumns::getColumnCount() {
	return boundColumns->Count();
}

lbErrCodes      LB_STDCALL lbDatabaseLayerBoundColumns::setQuery(lb_I_Query* q, lb_I_Container* ReadonlyColumns) {
	lbDatabaseLayerQuery* qq = (lbDatabaseLayerQuery*) q;

	HSTMT hstmt = qq->getCurrentStatement();
	query = qq;

	SQLSMALLINT num = 0;	
	///\todo Implement getting number of columns.
	SQLRETURN sqlreturn = 0;//SQLNumResultCols(hstmt, &num);
	
	if (boundColumns == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, boundColumns)
	} else {
		boundColumns->deleteAll();
	}

	for (int i = 1; i <= num; i++) {
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerKey)
		lbErrCodes err = ERR_NONE;

		// Create the instance ...
		
		lbDatabaseLayerBoundColumn* bc = new lbDatabaseLayerBoundColumn();

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

	}

	return ERR_NONE;
}

lbErrCodes	LB_STDCALL lbDatabaseLayerBoundColumns::getLong(int column, lb_I_Long* instance) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_BoundColumn, bc)

	bc = getBoundColumn(column);
	bc->getAsLong(instance);

	return ERR_NONE;
}

lbErrCodes	LB_STDCALL lbDatabaseLayerBoundColumns::getString(int column, lb_I_String* instance) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_BoundColumn, bc)

	bc = getBoundColumn(column);
	// getBoundColumn(column); increases refcount
	//bc++;
	bc->getAsString(instance);

	return ERR_NONE;
}

lbErrCodes	LB_STDCALL lbDatabaseLayerBoundColumns::getString(const char* column, lb_I_String* instance) {
	getString(getColumnIndex(column), instance);
	
	return ERR_NONE;
}

lbErrCodes      LB_STDCALL lbDatabaseLayerBoundColumns::setString(char* column, lb_I_String* instance) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, ukdata)
	UAP(lb_I_KeyBase, key)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, Column)
	
	Column->setData(column);
	
	QI(Column, lb_I_KeyBase, key)
	ukdata = ColumnNameMapping->getElement(&key);

	if (ukdata == NULL) {
		_LOG << "Error: Column '" << column << "' not found." LOG_
		return ERR_DB_COLUMN_NOT_FOUND;
	}

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


int		LB_STDCALL lbDatabaseLayerBoundColumns::getMode() {
	return query->isAdding();
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseLayerQuery)
        ADD_INTERFACE(lb_I_Query)
END_IMPLEMENT_LB_UNKNOWN()

UAP(lb_I_Integer, key)

void LB_STDCALL lbDatabaseLayerQuery::createMetaInformation() {
	lbErrCodes err = ERR_NONE;
	int count = 0;
	// Be sure
	destroyMetaInformation();
	
	if (szSql) {
		DatabaseResultSet* tempResult = currentdbLayer->RunQueryWithResults(szSql);
		
		if (tempResult != NULL) {
			ResultSetMetaData* metadata = tempResult->GetMetaData();
			count = metadata->GetColumnCount();
			
			for(int i=1;i<=count;i++) {
				UAP_REQUEST(getModuleManager(), lb_I_String, name)
				UAP_REQUEST(getModuleManager(), lb_I_String, tablename)
				UAP_REQUEST(getModuleManager(), lb_I_Integer, type)
				UAP_REQUEST(getModuleManager(), lb_I_Integer, columnIndex)
				UAP(lb_I_KeyBase, key)
				UAP(lb_I_Unknown, uk)
				UAP(lb_I_Unknown, ukT)
				UAP(lb_I_Unknown, ukTable)
				
				QI(columnIndex, lb_I_KeyBase, key)
				QI(name, lb_I_Unknown, uk)
				QI(type, lb_I_Unknown, ukT)
				QI(tablename, lb_I_Unknown, ukTable)

				columnIndex->setData(i);
				
				type->setData(metadata->GetColumnType(i));
				wxString column = metadata->GetColumnName(i);

				*name = column.c_str();

				cachedColumnNames->insert(&uk, &key);
				cachedColumnTypes->insert(&ukT, &key);
				
				// Store the number of primary keys for the table of the first column.
				/// \todo Joins and multible tables not supported yet.
				numPrimaryKeys = currentdbLayer->GetPrimaryKeys(metadata->GetTableForColumn(1));

				wxString table = metadata->GetTableForColumn(column);
				*tablename = table.c_str();
				
				// Store the table name per column
				cachedColumnTableNames->insert(&ukTable, &key);
				
				// Creating the mapping from foreign key to their primary column
				int fkcolumns = currentdbLayer->GetForeignKeys(table);
				
				for (int ifk = 0; ifk<fkcolumns;ifk++) {
					if (currentdbLayer->GetForeignKeyFKColumn(ifk) == column) {
						UAP(lb_I_Unknown, ukPK)
						UAP(lb_I_KeyBase, keyForeign)
						UAP_REQUEST(getModuleManager(), lb_I_String, pkColumn)
						*pkColumn = currentdbLayer->GetForeignKeyPKColumn(ifk).c_str();
						
						QI(name, lb_I_KeyBase, keyForeign)
						QI(pkColumn, lb_I_Unknown, ukPK)
						
						cachedColumnForeignColumnsToPrimaryColumns->insert(&ukPK, &keyForeign);
					}
				}
				
			}
		} else {
			_LOG << "Error: szSql resulted in no resultset!" LOG_
		}
		
		currentdbLayer->CloseResultSet(tempResult);
	} else {
			_LOG << "Error: szSql should have a value!" LOG_
	}
	
	if (getColumns() != count) {
		_LOG << "Error: Number of reported columns not equal to expected!" LOG_
	}
}

void LB_STDCALL lbDatabaseLayerQuery::destroyMetaInformation() {
	cachedColumnTableNames->deleteAll();
	cachedColumnNames->deleteAll();
	cachedColumnTypes->deleteAll();
	
	cachedColumnPrimaryColumns->deleteAll();
	cachedColumnForeignColumnsToPrimaryColumns->deleteAll();
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::setData(lb_I_Unknown * uk) {
	_CL_LOG << "lbDatabaseLayerQuery::setData(...): Not implemented yet" LOG_
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::setView(lb_I_ColumnBinding* cb) {
	_LOG << "lbDatabaseLayerQuery::setView(...): Not implemented yet" LOG_
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::registerView(lb_I_MVC_View* view) {
	_LOG << "lbDatabaseLayerQuery::registerView(...): Not implemented yet" LOG_
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::unregisterView(lb_I_MVC_View* view) {
	_LOG << "lbDatabaseLayerQuery::unregisterView(...): Not implemented yet" LOG_
        return ERR_NONE;
}

void LB_STDCALL lbDatabaseLayerQuery::skipFKCollecting() {
	skipFKCollections = 1;
}

void LB_STDCALL lbDatabaseLayerQuery::enableFKCollecting() {
	skipFKCollections = 0;
}

void LB_STDCALL lbDatabaseLayerQuery::PrintData(bool reverse) {
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

void LB_STDCALL lbDatabaseLayerQuery::PrintFooter() {
	int cols = getColumns();
	
	for (int i = 1; i < cols; i++) {
		printf("-------------------");
	}
	
	printf("-------------------\n");
}

void LB_STDCALL lbDatabaseLayerQuery::PrintHeader() {
	int cols = getColumns();
	UAP(lb_I_String, col)
	for (int i = 1; i < cols; i++) {
			col = getColumnName(i);
	        printf("%19s", col->charrep());
	}
	col = getColumnName(cols);
	printf("%19s\n", col->charrep());

	PrintFooter();
}

void LB_STDCALL lbDatabaseLayerQuery::PrintCurrent() {
	UAP(lb_I_String, s)
	UAP(lb_I_Long, l)
	int cols = getColumns();
	
	for (int i = 1; i <= cols-1; i++) {
		UAP(lb_I_String, s)
		UAP(lb_I_Long, l)
		switch (getColumnType(i)) {
			case lbDBColumnBit:
				s = getAsString(i);
				break;
			case lbDBColumnChar:
				s = getAsString(i);
				break;
			case lbDBColumnInteger:
			{
				REQUEST(getModuleManager(), lb_I_String, s)
				l = getAsLong(i);
				*s = l->charrep();
			}
				break;
			case lbDBColumnBigInteger:
			{
				REQUEST(getModuleManager(), lb_I_String, s)
				l = getAsLong(i);
				*s = l->charrep();
			}
				break;
			case lbDBColumnBinary:
			{
				REQUEST(getModuleManager(), lb_I_String, s)
				*s = "Binary column";
			}
				break;
			case lbDBColumnDate:
				s = getAsString(i);
				break;
			case lbDBColumnFloat:
				s = getAsString(i);
				break;
			default:
				REQUEST(getModuleManager(), lb_I_String, s)
				*s = "Unknown column";
		}
		s->trim();
        printf("%19s", s->charrep());
	}

	switch (getColumnType(cols)) {
		case lbDBColumnBit:
			s = getAsString(cols);
			break;
		case lbDBColumnChar:
			s = getAsString(cols);
			break;
		case lbDBColumnInteger:
		{
			REQUEST(getModuleManager(), lb_I_String, s)
			l = getAsLong(cols);
			*s = l->charrep();
		}
			break;
		case lbDBColumnBigInteger:
		{
			REQUEST(getModuleManager(), lb_I_String, s)
			l = getAsLong(cols);
			*s = l->charrep();
		}
			break;
		case lbDBColumnBinary:
		{
			REQUEST(getModuleManager(), lb_I_String, s)
			*s = "Binary column";
		}
			break;
		case lbDBColumnDate:
			s = getAsString(cols);
			break;
		case lbDBColumnFloat:
			s = getAsString(cols);
			break;
		default:
			REQUEST(getModuleManager(), lb_I_String, s)
			*s = "Unknown column";
	}
	s->trim();
	printf("%19s\n", s->charrep());
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::executeDirect(char* SQL) {
	if (currentdbLayer != NULL) {
		try {
			if (!currentdbLayer->RunQuery(SQL)) {
				_LOG << "lbDatabaseLayerQuery::executeDirect(): Error: Could not execute query. Query failed." LOG_
				return ERR_DB_QUERYFAILED;
			}
		}
		catch (...) {
			_LOG << "lbDatabaseLayerQuery::executeDirect(char* SQL) failed with query: " << SQL LOG_
			return ERR_DB_QUERYFAILED;
		}
		return ERR_NONE;
	} else {
		_LOG << "lbDatabaseLayerQuery::executeDirect(): Error: Could not execute query. Have no database layer instance." LOG_
	}
	return ERR_DB_INIT;
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::init(DatabaseLayer* dbLayer, char* dbname, bool ro) {
	_LOG << "lbDatabaseLayerQuery::init(...) called." LOG_
	currentdbLayer = dbLayer;
	if (dbName) free(dbName);
	dbName = NULL;
	if (dbname) dbName = strdup(dbname);
	
	if (currentdbLayer) {
		_LOG << "lbDatabaseLayerQuery::init(...) Instance of currentdbLayer available." LOG_
	} else {
		_LOG << "lbDatabaseLayerQuery::init(...) Instance of currentdbLayer not available." LOG_
	}
	
	if (!dbLayer || !dbLayer->IsOpen()) {
		_LOG << "Error: database not opened!" LOG_
		return ERR_DB_INIT;
	}
	
	if (ro) {
		_CL_LOG << "Set actual query to be readonly." LOG_
		_readonly = 1;
	} else _readonly = 0;
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::bind() {
    return ERR_NONE;
}
/*...e*/
/*...schar\42\ LB_STDCALL lbDatabaseLayerQuery\58\\58\setWhereClause\40\const char\42\ query\44\ char\42\ where\41\:0:*/
/// \todo Add support for joined tables.
char* LB_STDCALL lbDatabaseLayerQuery::setWhereClause(const char* query, char* where) {
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
char* LB_STDCALL lbDatabaseLayerQuery::addWhereClause(const char* query, char* where) {
	return strdup("ERROR: Not implemented.");
}

bool LB_STDCALL lbDatabaseLayerQuery::dataFetched() {
	return _dataFetched;
}
lb_I_Query::lbDBCaseSensity    LB_STDCALL lbDatabaseLayerQuery::getCaseSensity() {
	///\todo Implement
	return lb_I_Query::lbDBCaseSensibility;
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::query(char* q, bool bind) {
	lbErrCodes err = ERR_NONE;
	if (bind) {
		_LOG << "lbDatabaseLayerQuery::query('" << q << "', true) called." LOG_
	} else {
		_LOG << "lbDatabaseLayerQuery::query('" << q << "', false) called." LOG_
	}
	lbDatabaseLayerBoundColumns* boundcols = NULL;

	// Maybe cursor possible
	cursorFeature = true;
	_dataFetched = false;
	
    if (q == NULL) {
		_LOG << "Error: Have got a NULL pointer for the query to execute!" LOG_
		return ERR_DB_QUERYFAILED;
	}
	
	if (szSql != q) {
		if (szSql != NULL) free(szSql);
		szSql = strdup(q);
	}
	
	if (theResult != NULL) {
		///\todo Cleanup resultset.
	}
	
	if (strcmp(szSql, "COMMIT") == 0) {
		currentdbLayer->RunQuery(szSql);
		return ERR_NONE;
	}
	
	try {
		theResult = currentdbLayer->RunQueryWithResults(szSql);
		
		if (theResult != NULL) {
			_LOG << "Have got a resultset for '" << szSql << "'" LOG_
			_dataFetched = false;
			createMetaInformation();
			if (!theResult->Next()) {
				if (skipFKCollections == 0) prepareFKList();

				ResultSetMetaData* metadata = theResult->GetMetaData();
				
				// Get all tables once
				int count = metadata->GetColumnCount();
				for (int i = 1; i <= count; i++) {
					wxString table = metadata->GetTableForColumn(i);
					if (tables.Index(table) == wxNOT_FOUND) tables.Add(table);
				}

				_LOG << "lbDatabaseLayerQuery::query() Error: There is no data! Query was: " << q LOG_
				
				// As figured out by the translation function
				// Keep for meta data
				currentdbLayer->CloseResultSet(theResult);
				
				return ERR_DB_NODATA;
			} else {
				///\todo Read in all primary key values used as 'cursor'
				_dataFetched = true;
				if (skipFKCollections == 0) prepareFKList();
							

/*				
				if (theQuery.Upper().Contains("JOIN")) {
					joinClause = theQuery.SubString(theQuery.Find(wxString("JOIN")), theQuery.Length());
					
					if (joinClause.Upper().Contains("WHERE")) {
						whereClause = joinClause.SubString(theQuery.Find(wxString("WHERE")), joinClause.Length());
						joinClause = joinClause.SubString(0, theQuery.Find(wxString("WHERE")) -1);
					}
					
				} else if (theQuery.Upper().Contains("WHERE")) {
					whereClause = theQuery.SubString(theQuery.Find(wxString("WHERE")), theQuery.Length());
				}
*/				
				wxString theQuery = wxString(szSql);
			
				if (theQuery.Upper().Contains("INSERT")) {
					if (theResult) {
						currentdbLayer->CloseResultSet(theResult);
						theResult = NULL;
					}
					return ERR_NONE;
				}
				if (theQuery.Upper().Contains("UPDATE")) {
					if (theResult) {
						currentdbLayer->CloseResultSet(theResult);
						theResult = NULL;
					}
					return ERR_NONE;
				}
				if (theQuery.Upper().Contains("DROP")) {
					if (theResult) {
						currentdbLayer->CloseResultSet(theResult);
						theResult = NULL;
					}
					return ERR_NONE;
				}
				if (theQuery.Upper().Contains("CREATE")) {
					if (theResult) {
						currentdbLayer->CloseResultSet(theResult);
						theResult = NULL;
					}
					return ERR_NONE;
				}

				ResultSetMetaData* metadata = theResult->GetMetaData();
				
				// Get all tables once
				int count = metadata->GetColumnCount();
				for (int i = 1; i <= count; i++) {
					wxString table = metadata->GetTableForColumn(i);
					if (tables.Index(table) == wxNOT_FOUND) tables.Add(table);
				}
				
				if (tables.Count() > 1)
				// Maybe a join or more difficult query I not yet want to handle cursor for
					cursorFeature = false;
				
	// The query in some parts
	//wxString plainQuery;	// The columns including 'FROM'
	//wxString joinClause;	// If there are JOIN rules
	//wxString whereClause;	// If there are where clauses
	
	//wxString cursorWhere;	// Actiual cursor position

				
				if (theQuery.Upper().Contains("JOIN"))
					cursorFeature = false;
				
				if (theQuery.Upper().Contains(" WHERE ")) {
					//cursorFeature = false;
					whereClause = theQuery.SubString(theQuery.Upper().Find("WHERE"), theQuery.Length());
					plainQuery = theQuery.SubString(0, theQuery.Upper().Find("WHERE") - 1);

					// Strip off the order by clause
					if (whereClause.Upper().Contains(" ORDER ")) {
						whereClause = whereClause.SubString(0, whereClause.Upper().Find("ORDER") - 1);
					}
				} else {
					if (theQuery.Upper().Contains(" ORDER ")) {
						plainQuery = theQuery.SubString(0, theQuery.Upper().Find("ORDER") - 1);
					} else {
						plainQuery = theQuery;
					}
				}

				
				if (cursorFeature) {
					int pkeys = currentdbLayer->GetPrimaryKeys(tables[0]);
					
					if (pkeys >= 1) {
						wxString tempSQL = "SELECT ";
						tempSQL += currentdbLayer->GetPrimaryKeyColumn(0);
						tempSQL += " from ";
						tempSQL += tables[0];
						
						if (whereClause != "") {
							tempSQL += " ";
							tempSQL += whereClause;
							tempSQL += " ";
						}
						
						/* What about the order by clauses that are no based on primary keys ?
						 * It could be used the values of that ordering to be filled in the currentCursorview.
						 * To avoid the problem if there are, for sample 500 rows with the same 'ordering key',
						 * The primary key could be added at the end of the order list.
						 */ 
						tempSQL += " order by ";
						tempSQL += currentdbLayer->GetPrimaryKeyColumn(0);
						
						_LOG << "Created help query: " << tempSQL.c_str() LOG_
						
						DatabaseResultSet* tempResult;
						
						try {
							tempResult = currentdbLayer->RunQueryWithResults(tempSQL);
						} catch (DatabaseLayerException ex) {
							_LOG << "lbDatabaseLayerQuery() Error: Catched an exeption while issuing temporary query! Exception was: " << ex.GetErrorMessage().c_str() << ". Query was: " << tempSQL.c_str() LOG_
							return ERR_DB_QUERYFAILED;
						}
						
						int count = 0;
						if (tempResult && tempResult->Next()) {
							count++;
							wxString value = tempResult->GetResultString(1);
							//_LOG << "Fill ID list with item " << value.c_str() LOG_
							currentCursorview.Add(value);
							while (tempResult->Next()) {
								count++;
								value = tempResult->GetResultString(1);
								//_LOG << "Fill ID list with item " << value.c_str() LOG_
								currentCursorview.Add(value);
								if (count == max_in_cursor) break;
							}
						}
						cursor = 0;
						max_in_cursor = count;
						
						// Keep for meta data
						currentdbLayer->CloseResultSet(theResult);
						
						selectCurrentRow();
					} else {
						cursorFeature = false;
					}
				} else {					
					UAP(lb_I_KeyBase, rowKey)
					UAP_REQUEST(getModuleInstance(), lb_I_Integer, Row)
					QI(Row, lb_I_KeyBase, rowKey)
					ResultSetMetaData* metadata = theResult->GetMetaData();
					// Cache the data, because after a finish, no data will be given back.
					cachedDataColumns->deleteAll();
					
					int row = 1;
					Row->setData(row);
					
					for (int i_cache = 1; i_cache <= getColumns(); i_cache++) {
						UAP_REQUEST(getModuleInstance(), lb_I_Integer, I)
						UAP(lb_I_KeyBase, key)
						UAP(lb_I_Unknown, uk)
						I->setData(i_cache);
						QI(I, lb_I_KeyBase, key)
						
						switch (getColumnType(i_cache)) {
							case lbDBColumnBit:
							{
								UAP_REQUEST(getModuleInstance(), lb_I_String, string)
								*string = theResult->GetResultString(i_cache).c_str();
								if (*string == "1") {
									*string = "true";
								} else {
									*string = "false";
								}
								QI(string, lb_I_Unknown, uk)
							}
								break;
							case lbDBColumnChar:
							{
								UAP_REQUEST(getModuleInstance(), lb_I_String, string)
								*string = theResult->GetResultString(i_cache).c_str();
								QI(string, lb_I_Unknown, uk)
							}
								break;
							case lbDBColumnInteger:
							{
								UAP_REQUEST(manager.getPtr(), lb_I_Long, value)
								value->setData(theResult->GetResultLong(i_cache));
								QI(value, lb_I_Unknown, uk)
							}
								break;
							case lbDBColumnBigInteger:
							{
								UAP_REQUEST(manager.getPtr(), lb_I_Long, value)
								value->setData(theResult->GetResultLong(i_cache));
								QI(value, lb_I_Unknown, uk)
							}
								break;
							case lbDBColumnBinary:
							{
								UAP_REQUEST(getModuleInstance(), lb_I_BinaryData, binarydata)
								wxMemoryBuffer buffer;
								
								if (theResult) theResult->GetResultBlob(i_cache, buffer);
								
								binarydata->append(buffer.GetData(), buffer.GetBufSize());
								binarydata->append((void*) "", 1);
								QI(binarydata, lb_I_Unknown, uk)
							}
								break;
							case lbDBColumnDate:
							{
								UAP_REQUEST(getModuleInstance(), lb_I_String, string)
								*string = theResult->GetResultString(i_cache).c_str();
								QI(string, lb_I_Unknown, uk)
							}
								break;
							case lbDBColumnFloat:
							{
								UAP_REQUEST(getModuleInstance(), lb_I_String, string)
								*string = theResult->GetResultString(i_cache).c_str();
								QI(string, lb_I_Unknown, uk)
							}
								break;
							default:
							{
								UAP_REQUEST(getModuleInstance(), lb_I_String, string)
								*string = theResult->GetResultString(i_cache).c_str();
								_LOG << "Warning: Have got unknown column (value = " << string->charrep() << ")!" LOG_
								QI(string, lb_I_Unknown, uk)
							}
								break;
						}
						
						cachedDataColumns->insert(&uk, &key);
					}

					UAP(lb_I_Unknown, ukcachedDataColumns)
					QI(cachedDataColumns, lb_I_Unknown, ukcachedDataColumns)
					
					cachedDataRows->insert(&ukcachedDataColumns, &rowKey);
					
					// Cache the complete resultset and finish.
					while (theResult->Next()) {
						Row->setData(++row);
						cachedDataColumns->deleteAll();

						for (int i_cache = 1; i_cache <= getColumns(); i_cache++) {
							UAP_REQUEST(getModuleInstance(), lb_I_Integer, I)
							UAP(lb_I_KeyBase, key)
							UAP(lb_I_Unknown, uk)
							I->setData(i_cache);
							QI(I, lb_I_KeyBase, key)
							
							switch (getColumnType(i_cache)) {
								case lbDBColumnBit:
								{
									UAP_REQUEST(getModuleInstance(), lb_I_String, string)
									*string = theResult->GetResultString(i_cache).c_str();
									if (*string == "1") {
										*string = "true";
									} else {
										*string = "false";
									}
									QI(string, lb_I_Unknown, uk)
								}
									break;
								case lbDBColumnChar:
								{
									UAP_REQUEST(getModuleInstance(), lb_I_String, string)
									*string = theResult->GetResultString(i_cache).c_str();
									QI(string, lb_I_Unknown, uk)
								}
									break;
								case lbDBColumnInteger:
								{
									UAP_REQUEST(manager.getPtr(), lb_I_Long, value)
									value->setData(theResult->GetResultLong(i_cache));
									QI(value, lb_I_Unknown, uk)
								}
									break;
								case lbDBColumnBigInteger:
								{
									UAP_REQUEST(manager.getPtr(), lb_I_Long, value)
									value->setData(theResult->GetResultLong(i_cache));
									QI(value, lb_I_Unknown, uk)
								}
									break;
								case lbDBColumnBinary:
								{
									UAP_REQUEST(getModuleInstance(), lb_I_BinaryData, binarydata)
									wxMemoryBuffer buffer;
									
									if (theResult) theResult->GetResultBlob(i_cache, buffer);
									
									binarydata->append(buffer.GetData(), buffer.GetBufSize());
									binarydata->append((void*) "", 1);
									QI(binarydata, lb_I_Unknown, uk)
								}
									break;
								case lbDBColumnDate:
								{
									UAP_REQUEST(getModuleInstance(), lb_I_String, string)
									*string = theResult->GetResultString(i_cache).c_str();
									QI(string, lb_I_Unknown, uk)
								}
									break;
								case lbDBColumnFloat:
								{
									UAP_REQUEST(getModuleInstance(), lb_I_String, string)
									*string = theResult->GetResultString(i_cache).c_str();
									QI(string, lb_I_Unknown, uk)
								}
									break;
								default:
								{
									UAP_REQUEST(getModuleInstance(), lb_I_String, string)
									*string = theResult->GetResultString(i_cache).c_str();
									_LOG << "Warning: Have got unknown column (value = " << string->charrep() << ")!" LOG_
									QI(string, lb_I_Unknown, uk)
								}
									break;
							}
							
							cachedDataColumns->insert(&uk, &key);
						}
						cachedDataRows->insert(&ukcachedDataColumns, &rowKey);						
					}
					// Keep for meta data
					currentdbLayer->CloseResultSet(theResult);	
				}
			}
		} else {
			wxString theQuery = szSql;
			if (theQuery.Upper().Contains("INSERT")) {
				return ERR_NONE;
			}
			if (theQuery.Upper().Contains("UPDATE")) {
				return ERR_NONE;
			}
			if (theQuery.Upper().Contains("DROP")) {
				return ERR_NONE;
			}
			if (theQuery.Upper().Contains("CREATE")) {
				return ERR_NONE;
			}
			_LOG << "Error: Query '" << szSql << "' failed!" LOG_
			return ERR_DB_QUERYFAILED;
		}
		_dataFetched = true;
		return ERR_NONE;
	} catch (DatabaseLayerException ex) {
		_LOG << "lbDatabaseLayerQuery::query() Error: Catched an exeption! Exception was: " << ex.GetErrorMessage().c_str() << ". Query was: " << q LOG_
		return ERR_DB_QUERYFAILED;
	}
	
}
/*...e*/
/*...svirtual char\42\ LB_STDCALL lbDatabaseLayerQuery\58\\58\getAsString\40\int column\41\:0:*/
#ifdef UNBOUND
char* LB_STDCALL lbDatabaseLayerQuery::getChar(int column) {
}
#endif
#ifndef UNBOUND
lb_I_String* LB_STDCALL lbDatabaseLayerQuery::getAsString(int column) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_String, value)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, col)
	QI(col, lb_I_KeyBase, key)
	col->setData(column);
	
	if (cachedDataColumns->exists(&key) == 1) {
		uk = cachedDataColumns->getElement(&key);
		QI(uk, lb_I_String, value)
		if (value == NULL) {
			_LOG << "Error: Column is not of type lb_I_String!" LOG_
			REQUEST(getModuleInstance(), lb_I_String, value)
			*value = "";
		}
	} else {
		REQUEST(getModuleInstance(), lb_I_String, value)
		*value = "";
	}
	
	// Caller get's an owner
	value++;

	///\todo Implement this.

	return value.getPtr();
}

lb_I_String* LB_STDCALL lbDatabaseLayerQuery::getAsString(const char* column) {
	UAP_REQUEST(manager.getPtr(), lb_I_String, string)
	
	// Caller get's an owner
	string++;
	
	///\todo Implement this.
	
	return string.getPtr();
}

lb_I_Long* LB_STDCALL lbDatabaseLayerQuery::getAsLong(int column) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Long, value)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, col)
	QI(col, lb_I_KeyBase, key)
	col->setData(column);
	
	if (cachedDataColumns->exists(&key) == 1) {
		uk = cachedDataColumns->getElement(&key);
		QI(uk, lb_I_Long, value)
		if (value == NULL) {
			_LOG << "Error: Column is not of type lb_I_Long!" LOG_
			REQUEST(getModuleInstance(), lb_I_Long, value)
		}
	} else {
		REQUEST(getModuleInstance(), lb_I_Long, value)
	}
	
	// Caller get's an owner
	value++;
	
	///\todo Implement this.
	
	return value.getPtr();
}

lb_I_BinaryData* LB_STDCALL lbDatabaseLayerQuery::getBinaryData(int column) {
#ifdef bla
	UAP_REQUEST(getModuleInstance(), lb_I_BinaryData, binarydata)

	///\todo Implement this.
	wxMemoryBuffer buffer;

	if (theResult) theResult->GetResultBlob(column, buffer);
	
	binarydata->append(buffer.GetData(), buffer.GetBufSize());
	binarydata->append((void*) "", 1);

	binarydata++;
	return binarydata.getPtr();
#endif
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_BinaryData, value)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, col)
	QI(col, lb_I_KeyBase, key)
	col->setData(column);
	
	if (cachedDataColumns->exists(&key) == 1) {
		uk = cachedDataColumns->getElement(&key);
		QI(uk, lb_I_BinaryData, value)
		if (value == NULL) {
			_LOG << "Error: Column is not of type lb_I_Long!" LOG_
			REQUEST(getModuleInstance(), lb_I_BinaryData, value)
		}
	} else {
		REQUEST(getModuleInstance(), lb_I_BinaryData, value)
	}
	
	value->append((void*) "", 1);

	// Caller get's an owner
	value++;
	
	///\todo Implement this.
	
	return value.getPtr();
}

lb_I_BinaryData* LB_STDCALL lbDatabaseLayerQuery::getBinaryData(const char* column) {
	UAP_REQUEST(getModuleInstance(), lb_I_BinaryData, binarydata)

	///\todo Implement this.

	binarydata->append((void*) "", 1);

	binarydata++;
	return binarydata.getPtr();
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::setBinaryData(int column, lb_I_BinaryData* value) {
	///\todo Implement this.
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_String, name)
	name = getColumnName(column);
	
	UAP(lb_I_Unknown, ukValue)
	UAP(lb_I_KeyBase, key)
	
	QI(name, lb_I_KeyBase, key)
	QI(value, lb_I_Unknown, ukValue)
	
	if (binaryDataColumns->exists(&key)) binaryDataColumns->remove(&key);
	binaryDataColumns->insert(&ukValue, &key);
	
/*	
	wxString tempSQL = "UPDATE ";
	tempSQL += tables[0];
	tempSQL += " SET ";
	tempSQL += name->charrep();
	tempSQL += " = ? WHERE ";
	tempSQL += currentdbLayer->GetPrimaryKeyColumn(0);
	tempSQL += " = ";
	tempSQL += currentCursorview[cursor];
	
	PreparedStatement* pStatement = currentdbLayer->PrepareStatement(tempSQL);

	if (pStatement) {
		pStatement->SetParamBlob(1, value->getData(), value->getSize());
		pStatement->RunQuery();
	}
*/
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::setBinaryData(const char* column, lb_I_BinaryData* value) {
	///\todo Implement this.
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_Unknown, ukValue)
	UAP(lb_I_KeyBase, key)
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	
	*name = column;
	
	QI(name, lb_I_KeyBase, key)
	QI(value, lb_I_Unknown, ukValue)
	
	if (binaryDataColumns->exists(&key)) binaryDataColumns->remove(&key);
	binaryDataColumns->insert(&ukValue, &key);
	
/*	
	wxString tempSQL = "UPDATE ";
	tempSQL += tables[0];
	tempSQL += " SET ";
	tempSQL += column;
	tempSQL += " = ? WHERE ";
	tempSQL += currentdbLayer->GetPrimaryKeyColumn(0);
	tempSQL += " = ";
	tempSQL += currentCursorview[cursor];
	
	PreparedStatement* pStatement = currentdbLayer->PrepareStatement(tempSQL);
	
	for (int i = 1; i <= getColumns(); i++) {
		UAP(lb_I_String, name)
		name = getColumnName(i);
		
		if (strcmp(name->charrep(), column) == 0 && pStatement) {
			pStatement->SetParamBlob(1, value->getData(), value->getSize());
			pStatement->RunQuery();
		}
	}
*/
	return ERR_NONE;
}


#endif

int LB_STDCALL lbDatabaseLayerQuery::getColumns() {
	ResultSetMetaData* metadata;
	if (theResult == NULL) {
		_LOG << "Error: No resultset available." LOG_
		return 0;
	}

	int count = cachedColumnNames->Count();
	
	return count;
}

bool LB_STDCALL lbDatabaseLayerQuery::hasColumnName(char* name) {
	if ((boundColumns != NULL) && (boundColumns->getColumnIndex(name) != -1)) return true; 
	return false;
}

int LB_STDCALL lbDatabaseLayerQuery::hasFKColumn(char* FKName) {
	lbErrCodes err = ERR_NONE;

	if ((FKName != NULL) && (strlen(FKName) > 0)) {

		if (skipFKCollections == 1) {
			_CL_VERBOSE << "Warning: Skipping for checking of foreign columns." LOG_
			return 0;
		}
	
		UAP(lb_I_KeyBase, key)
		UAP_REQUEST(manager.getPtr(), lb_I_String, s)
	
		s->setData(FKName);
		//s->toLower();
		
		QI(s, lb_I_KeyBase, key)
	
		if (ForeignColumns != NULL) {
			if (ForeignColumns->exists(&key) == 1) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_String, s)
			UAP(lb_I_String, T)
			
			uk = ForeignColumns->getElement(&key);
			QI(uk, lb_I_String, s)
			
			// Check, if FKName does not point from other table to me
			T = getTableName(FKName);
			if (strcmp(s->charrep(), T->charrep()) != 0) return 1;
			}
		}
	}

	return 0;
}
/*...e*/
/*...sint LB_STDCALL lbDatabaseLayerQuery\58\\58\getFKColumns\40\\41\:0:*/
int LB_STDCALL lbDatabaseLayerQuery::getFKColumns() {
	if (skipFKCollections == 1) return 0;

	if (ForeignColumns == NULL) {
		_CL_LOG << "Error: List of foreign columns is not initialized!" LOG_
		return 0;
	}

	return ForeignColumns->Count();
}
/*...e*/
/*...slb_I_String\42\ LB_STDCALL lbDatabaseLayerQuery\58\\58\getFKColumn\40\int pos\41\:0:*/
lb_I_String* LB_STDCALL lbDatabaseLayerQuery::getFKColumn(int pos) {
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
/*...slb_I_String\42\ LB_STDCALL lbDatabaseLayerQuery\58\\58\getFKColumn\40\char\42\ table\44\ char\42\ primary\41\:0:*/
lb_I_String* LB_STDCALL lbDatabaseLayerQuery::getFKColumn(char* table, char* primary) {
	lbErrCodes err = ERR_NONE;

	_CL_LOG << "lbDatabaseLayerQuery::getFKColumn('" << table << "', '" << primary << "') called." LOG_
	
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
/*...slb_I_String\42\ LB_STDCALL lbDatabaseLayerQuery\58\\58\getPKTable\40\char const \42\ FKName\41\:0:*/
lb_I_String* LB_STDCALL lbDatabaseLayerQuery::getPKTable(char const * FKName) {
	lbErrCodes err = ERR_NONE;


	if (skipFKCollections == 1) {
		_CL_VERBOSE << "Warning: Skipping for checking of foreign columns." LOG_
		return NULL;
	}
	
	UAP(lb_I_KeyBase, key)
	UAP_REQUEST(manager.getPtr(), lb_I_String, s)
	
	s->setData(FKName);
	//s->toLower();
	
	QI(s, lb_I_KeyBase, key)
	
	if (ForeignColumns->exists(&key) == 1) {
		UAP(lb_I_String, string)
		UAP(lb_I_Unknown, uk)
		
		uk = ForeignColumns->getElement(&key)->clone(__FILE__, __LINE__);
		
		QI(uk, lb_I_String, string)

		string++;
		
		return string.getPtr();
	}
	
	_LOG << "Error: Didn't found primary table from foreign key name. (" << FKName << ")" LOG_
	
	return NULL;
}
/*...e*/
/*...slb_I_String\42\ LB_STDCALL lbDatabaseLayerQuery\58\\58\getPKColumn\40\char const \42\ FKName\41\:0:*/
lb_I_String* LB_STDCALL lbDatabaseLayerQuery::getPKColumn(char const * FKName) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, s)
	UAP_REQUEST(getModuleInstance(), lb_I_String, FK)
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, uk)
	
	if (theResult == NULL) {
		_LOG << "Error: No resultset available." LOG_
		*s = "";
		s++;
		return s.getPtr();
	}

	*FK = FKName;
	QI(FK, lb_I_KeyBase, key)
	
	if (cachedColumnForeignColumnsToPrimaryColumns->exists(&key) == 1) {
		uk = cachedColumnForeignColumnsToPrimaryColumns->getElement(&key);
		QI(uk, lb_I_String, s)
		s++;
		return s.getPtr();
	}
	*s = "";
	s++;
    return s.getPtr();
}
/*...e*/

/*...svoid LB_STDCALL lbDatabaseLayerQuery\58\\58\prepareFKList\40\\41\:0:*/
void LB_STDCALL lbDatabaseLayerQuery::prepareFKList() {
	#define TAB_LEN 100
	#define COL_LEN 100
	lbErrCodes err = ERR_NONE;
	void* that = this;

	if (this == NULL) {
		_CL_LOG << "Fatal: Called member function on invalid object (lbDatabaseLayerQuery::prepareFKList(), NULL) !" LOG_ 
	}

	if (!_TRMemValidate(this)) {
		lbBreak();
	}

	if (mapPKTable_PKColumns_To_FKName == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, mapPKTable_PKColumns_To_FKName)
	} else {
		mapPKTable_PKColumns_To_FKName->deleteAll();
	}


	if (ForeignColumns == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, ForeignColumns)
	} else {
		ForeignColumns->deleteAll();
	}

	if (ForeignColumns == NULL) {
		_CL_LOG << "FATAL: ForeignColumns could note be initialized!" LOG_
	}

	if (skipFKCollections == 1) {
	    _CL_VERBOSE << "==========================================" LOG_
	    _CL_VERBOSE << "Do not collect foreign column information!" LOG_
	    _CL_VERBOSE << "==========================================" LOG_

	    return;
	}

	UAP(lb_I_String, tbl)
	UAP(lb_I_String, col)
	
	col = getColumnName(1);
	tbl = getTableName(col->charrep());
	
    char* table = tbl->charrep();
	
    // Use fk code from Cody Pisto
	
	try {
		int count = currentdbLayer->GetForeignKeys(table);
		for (int i = 0; i < count; i++) {
			UAP_REQUEST(manager.getPtr(), lb_I_String, FKName)
			UAP_REQUEST(manager.getPtr(), lb_I_String, PKTable)
			UAP_REQUEST(manager.getPtr(), lb_I_String, PKName)
			UAP_REQUEST(manager.getPtr(), lb_I_String, PKTable_PKName)
			
			UAP_REQUEST(manager.getPtr(), lb_I_String, PKColumn)
			
			wxString fkEntry = currentdbLayer->GetForeignKeyFKColumn(i);
			wxString pkEntry = currentdbLayer->GetForeignKeyPKColumn(i);
			wxString pkTable = currentdbLayer->GetForeignKeyPKTable(i);
			
			*PKTable = pkTable.c_str();
			*PKName = pkEntry.c_str();		
			*FKName = fkEntry.c_str();
			
			UAP(lb_I_Unknown, uk_PKTable)
			UAP(lb_I_KeyBase, key_FKName)
				
			UAP(lb_I_Unknown, uk_FKName)
			UAP(lb_I_KeyBase, key_PKTable_PKName)
				
			QI(FKName, lb_I_KeyBase, key_FKName)
			QI(PKTable, lb_I_Unknown, uk_PKTable)
				
				
			if (isVerbose())
			printf("%-s ( %-s ) <-- %-s ( %-s )\n", PKTable->charrep(), PKName->charrep(), table, FKName->charrep());
			
			ForeignColumns->insert(&uk_PKTable, &key_FKName);
			
			*PKTable_PKName = PKTable->charrep();
			// Geht wahrscheinlich nicht.
			//PKColumn = getPKColumn(FKName->charrep());
			*PKTable_PKName += PKName->charrep();
			
			QI(PKTable_PKName, lb_I_KeyBase, key_PKTable_PKName)
			QI(FKName, lb_I_Unknown, uk_FKName)
				
			//PKTable_PKName->toLower();
				
			_CL_VERBOSE << "Insert map for '" << key_PKTable_PKName->charrep() << 
			"' to '" << FKName->charrep() << "'" LOG_
				
			mapPKTable_PKColumns_To_FKName->insert(&uk_FKName, &key_PKTable_PKName);
		}
	} catch (...) {
		_CL_LOG << "Exception caught!" LOG_
	}
}
/*...e*/
/*...sint LB_STDCALL lbDatabaseLayerQuery\58\\58\getPKColumns\40\\41\:0:*/
int LB_STDCALL lbDatabaseLayerQuery::getPKColumns() {
	SWORD count = 0;
	
	if (currentdbLayer == NULL) {
		_LOG << "Error: No connection opened." LOG_
		return 0;
	}
	
	if (theResult == NULL) {
		_LOG << "Error: No resultset available." LOG_
		if (szSql) {
			_LOG << "The last SQL query was " << szSql LOG_ 
		}
		return 0;
	}
	
	return numPrimaryKeys;
}
/*...e*/
/*...slb_I_String\42\ LB_STDCALL lbDatabaseLayerQuery\58\\58\getPKColumn\40\int pos\41\:0:*/
lb_I_String* LB_STDCALL lbDatabaseLayerQuery::getPKColumn(int pos) {
	if (currentdbLayer == NULL) {
		_LOG << "Error: No connection opened." LOG_
		return 0;
	}

	wxString col = currentdbLayer->GetPrimaryKeyColumn(pos-1);
	UAP_REQUEST(getModuleInstance(), lb_I_String, s)
	*s = col.c_str();
	s++;
	
	_LOG << "lbDatabaseLayerQuery::getPKColumn(" << pos-1 << ") returns " << s->charrep() LOG_
	
	return s.getPtr();
}
/*...e*/

bool LB_STDCALL lbDatabaseLayerQuery::isNullable(int pos) {
	if (currentdbLayer == NULL) {
		_LOG << "Error: No connection opened." LOG_
		return 0;
	}
	UAP(lb_I_String, columnName)
	UAP(lb_I_String, tableName)
	columnName = getColumnName(pos);
	tableName = getTableName(columnName->charrep());

	return currentdbLayer->GetColumnNullable(tableName->charrep(), columnName->charrep());
}

bool	LB_STDCALL lbDatabaseLayerQuery::isNullable(char const * name) {
	if (currentdbLayer == NULL) {
		_LOG << "Error: No connection opened." LOG_
		return 0;
	}
	UAP_REQUEST(getModuleInstance(), lb_I_String, columnName)
	UAP(lb_I_String, tableName)
	*columnName = name;
	tableName = getTableName(columnName->charrep());
	
	return currentdbLayer->GetColumnNullable(tableName->charrep(), columnName->charrep());
}

bool LB_STDCALL lbDatabaseLayerQuery::isNull(int pos) {
	if (theResult == NULL) {
		_LOG << "Error: No resultset available." LOG_
		return false;
	}
	UAP(lb_I_String, columnName)
	columnName = getColumnName(pos);
	
	return isNull(columnName->charrep());
}

bool	LB_STDCALL lbDatabaseLayerQuery::isNull(char const * name) {
	if (nullColumns.Index(wxString(name)) != wxNOT_FOUND) {
		if (nullValues[nullColumns.Index(wxString(name))] == "true") return true;
		else return false;
	} else {
		return false;
	}
}

bool	LB_STDCALL lbDatabaseLayerQuery::setNull(int pos, bool b) {
	if (theResult == NULL) {
		_LOG << "Error: No resultset available." LOG_
		return 0;
	}
	UAP(lb_I_String, columnName)
	columnName = getColumnName(pos);

	return setNull(columnName->charrep(), b);
}

bool	LB_STDCALL lbDatabaseLayerQuery::setNull(char const * name, bool b) {
	wxString nullFlag = "false";
	if (b) nullFlag = "true";
	
	if (nullColumns.Index(wxString(name)) != wxNOT_FOUND) {
		nullValues[nullColumns.Index(wxString(name))] = nullFlag;
	} else {
		nullColumns.Add(wxString(name));
		nullValues.Add(nullFlag);
	}

	return true; //boundColumns->setNull(name, b);
}

/*...slb_I_Query\58\\58\lbDBColumnTypes LB_STDCALL lbDatabaseLayerQuery\58\\58\getColumnType\40\int pos\41\:0:*/
lb_I_Query::lbDBColumnTypes LB_STDCALL lbDatabaseLayerQuery::getColumnType(int pos) {
	lbErrCodes err = ERR_NONE;
	if (theResult == NULL) {
		_LOG << "Error: No resultset available." LOG_
		return lbDBColumnUnknown;
	}

	UAP(lb_I_Integer, type)
	UAP_REQUEST(getModuleManager(), lb_I_Integer, index)
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, uk)
	
	index->setData(pos);
	QI(index, lb_I_KeyBase, key)
	
	if (cachedColumnTypes->exists(&key) == 1) {
		uk = cachedColumnTypes->getElement(&key);
		QI(uk, lb_I_Integer, type)

		int t = type->getData();
		
		switch (t) {
			case ResultSetMetaData::COLUMN_INTEGER: return lbDBColumnInteger;
			case ResultSetMetaData::COLUMN_STRING: return lbDBColumnChar;
			case ResultSetMetaData::COLUMN_DOUBLE: return lbDBColumnFloat;
			case ResultSetMetaData::COLUMN_BOOL: return lbDBColumnBit;
			case ResultSetMetaData::COLUMN_TEXT: return lbDBColumnBinary;
			case ResultSetMetaData::COLUMN_BLOB: return lbDBColumnBinary;
			case ResultSetMetaData::COLUMN_DATE: return lbDBColumnDate;
			default: 
			{
				_LOG << "Warning: Column type not known: " << t LOG_
				return lbDBColumnUnknown;
			}
		}
	}
	_LOG << "Error: Type for column not stored: " << pos LOG_
	return lbDBColumnUnknown;
}
/*...e*/
/*...slb_I_Query\58\\58\lbDBColumnTypes LB_STDCALL lbDatabaseLayerQuery\58\\58\getColumnType\40\char\42\ name\41\:0:*/
lb_I_Query::lbDBColumnTypes LB_STDCALL lbDatabaseLayerQuery::getColumnType(char* name) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleManager(), lb_I_String, Name)
	
	*Name = name;
	
	if (!theResult) {
		_LOG << "lbDatabaseLayerQuery::getColumnType('" << name << "') Error: No result set available for this operation!" LOG_
		return lbDBColumnUnknown;
	}
	
	if (theResult == NULL) {
		_LOG << "Error: No resultset available." LOG_
		return lbDBColumnUnknown;
	}
	
	cachedColumnNames->finishIteration();
	while (cachedColumnNames->hasMoreElements() == 1) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_String, column)
		UAP(lb_I_Integer, index)
		
		uk = cachedColumnNames->nextElement();
		QI(uk, lb_I_String, column)
		
		if (column->equals(*&Name)) {
			key = cachedColumnNames->currentKey();
			QI(key, lb_I_Integer, index)
			cachedColumnNames->finishIteration();
			return getColumnType(index->getData());
		}
	}

	return lbDBColumnUnknown;
}
/*...e*/
/*...svoid LB_STDCALL lbDatabaseLayerQuery\58\\58\setReadonly\40\char\42\ column\44\ bool updateable\41\:0:*/
void LB_STDCALL lbDatabaseLayerQuery::setReadonly(char* column, bool updateable) {
	lbErrCodes err = ERR_NONE;

	if (updateable == true) 
		_CL_LOG << "lbDatabaseLayerQuery::setReadonly(" << column << ", TRUE)" LOG_
	else
		_CL_LOG << "lbDatabaseLayerQuery::setReadonly(" << column << ", FALSE)" LOG_
	
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
		_CL_LOG << "lbDatabaseLayerQuery::setReadonly(...) calls ReadOnlyColumns->insert(...)." LOG_
		ReadOnlyColumns->insert(&uk, &key);
	}
	
	if (ReadOnlyColumns->exists(&key) && updateable == false) {
		_CL_LOG << "lbDatabaseLayerQuery::setReadonly(...) calls ReadOnlyColumns->remove(&key)." LOG_
		ReadOnlyColumns->remove(&key);
	}

	if (boundColumns.getPtr() != NULL) {
		_CL_LOG << "lbDatabaseLayerQuery::setReadonly(...) calls boundColumns->setReadonly(...)." LOG_
		boundColumns->setReadonly(column, updateable);
	}
	
	_CL_VERBOSE << "lbDatabaseLayerQuery::setReadonly(...) returns." LOG_
}
/*...e*/
/*...sbool LB_STDCALL lbDatabaseLayerQuery\58\\58\getReadonly\40\char\42\ column\41\:0:*/
bool LB_STDCALL lbDatabaseLayerQuery::getReadonly(char* column) {
	//return boundColumns->getReadonly(column);
	// \todo Implement.
	return false;
}
/*...e*/
/*...schar\42\ LB_STDCALL lbDatabaseLayerQuery\58\\58\getTableName\40\char\42\ columnName\41\:0:*/
lb_I_String* LB_STDCALL lbDatabaseLayerQuery::getTableName(char* columnName) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, table)
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	*name = columnName;
	if (theResult == NULL) {
		_LOG << "Error: No resultset available. Try reopen." LOG_
		if (reopen() != ERR_NONE) {
			_LOG << "Error: Reopen failed." LOG_
			*table = "";
			table++;
			return table.getPtr();
		} else {
			if (theResult == NULL) {
				_LOG << "Error: No resultset after reopen available." LOG_
				*table = "";
				table++;
				return table.getPtr();
			}
		}
	}
	
	cachedColumnNames->finishIteration();
	while (cachedColumnNames->hasMoreElements() == 1) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_String, column)
		UAP(lb_I_Integer, index)
		
		uk = cachedColumnNames->nextElement();
		QI(uk, lb_I_String, column)
		
		if (column->equals(*&name)) {
			key = cachedColumnNames->currentKey();
			QI(key, lb_I_Integer, index)
			cachedColumnNames->finishIteration();

			if (cachedColumnTableNames->exists(&key) == 1) {
				UAP(lb_I_Unknown, uk)
				UAP(lb_I_String, table)
				uk = cachedColumnTableNames->getElement(&key);
				QI(uk, lb_I_String, table)
				table++;
				return table.getPtr();
			}
		}
	}
	_LOG << "Error: Mapping of column name over index to table name not found." LOG_
	*table = "";
	table++;
	return table.getPtr();
}
/*...e*/
/*...schar\42\ LB_STDCALL lbDatabaseLayerQuery\58\\58\getColumnName\40\int col\41\:0:*/
char lbDatabaseLayerQuery_column_Name[100] = "";

lb_I_String* LB_STDCALL lbDatabaseLayerQuery::getColumnName(int col) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, t)
	///\todo Implement
	if (theResult == NULL) {
		_LOG << "Error: No resultset available." LOG_
		if (szSql) {
			_LOG << "The last SQL query was " << szSql LOG_ 
		}
		*t = "Error";
		t++;
		return t.getPtr(); 
	}
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_String, column)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, index)

	index->setData(col);
	QI(index, lb_I_KeyBase, key)
	
	if (cachedColumnNames->exists(&key) == 1) {
		UAP(lb_I_Unknown, uk)
		uk = cachedColumnNames->getElement(&key);
		QI(uk, lb_I_String, column)
		column++;
		return column.getPtr();
	}
	
	*t = "";
	t++;
	return t.getPtr();
}
/*...e*/

bool LB_STDCALL lbDatabaseLayerQuery::isFirst() {
	return fetchstatus == -1;
}

bool LB_STDCALL lbDatabaseLayerQuery::isLast() {
	return fetchstatus == 1;
}

void LB_STDCALL lbDatabaseLayerQuery::unbind() {
	if (boundColumns != NULL) boundColumns->unbind();
}

/*...svoid LB_STDCALL lbDatabaseLayerQuery\58\\58\reopen\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseLayerQuery::reopen() {
	///\todo Implement
	int backup_cursor = cursor;
	currentCursorview.Clear();
	lbErrCodes err = query(szSql, true);
	
	if ((err == ERR_DB_QUERYFAILED) || (err == ERR_DB_NODATA)) {
		_LOG << "Warning: Reopen of current statement failed." LOG_
		if ((err = open()) != ERR_NONE) {
			_LOG << "Error: Reopen connection propably failed too." LOG_
		}
		return err;
	}
	
	absolute(backup_cursor);
	if (theResult == NULL) {
			_LOG << "Error: Got no resultset after a reopen!" LOG_
		return ERR_DB_QUERYFAILED;
	}
	return ERR_NONE;
}

void LB_STDCALL lbDatabaseLayerQuery::close() {
	_CL_LOG << "lbDatabaseLayerQuery::close() called." LOG_

#ifdef bla
	if (currentdbLayer && currentdbLayer->IsOpen()) {
		bool closed = currentdbLayer->CloseResultSet(theResult);
		if (closed) {
			if (szSql) {
				_CL_LOG << "lbDatabaseLayerQuery::close() closed the resultset (" << szSql << ")." LOG_
			} else {
				_CL_LOG << "lbDatabaseLayerQuery::close() closed the resultset." LOG_
			}
		} else {
			if (szSql) {
				_CL_LOG << "lbDatabaseLayerQuery::close() don't closed the resultset (" << szSql << ")." LOG_
			} else {
				_CL_LOG << "lbDatabaseLayerQuery::close() don't closed the resultset." LOG_
			}
		}
		
		currentdbLayer = NULL;
	}
#endif
	
	if (theResult) {
		theResult = NULL;
	}
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::open() {
	_LOG << "lbDatabaseLayerQuery::open() called." LOG_
	lbErrCodes err = ERR_NONE;
	
	if (currentdbLayer == NULL) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Database, database)
		if (uk == NULL) {
			_CL_VERBOSE << "Warning: peekImplementation() has not been used prior." LOG_
			instanceOflbDatabaseLayerDatabase(&uk, manager.getPtr(), __FILE__, __LINE__);
		}
		uk->queryInterface("lb_I_Database", (void**) &database, __FILE__, __LINE__);
		currentdbLayer = ((lbDatabaseLayerDatabase*) database.getPtr())->getBackend(dbName); // Internally open is called, thus .db3 is appended.
	}
	
	if (!currentdbLayer->IsOpen()) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, connName)
		*connName = dbName;
		*connName += ".db3";
		currentdbLayer->Open(connName->charrep());
	}
	
	if (skipAutoQuery) return ERR_NONE;
	
	if ((err = query(szSql, true)) != ERR_NONE) {
		return err;
	}
	if (theResult == NULL) {
		_LOG << "Error: Got no resultset after a open!" LOG_
		return ERR_DB_QUERYFAILED;
	}
	return ERR_NONE;
}

bool LB_STDCALL lbDatabaseLayerQuery::selectCurrentRow() {
	lbErrCodes err = ERR_NONE;
	if (cursor < 0) {
		// Handle underflow
		// Try to read 100 more key values less than the first key in currentCursorview: currentCursorview[0]-1
		
		wxString tempSQL = "SELECT ";
		tempSQL += currentdbLayer->GetPrimaryKeyColumn(0);
		tempSQL += " FROM ";
		tempSQL += tables[0];

		if (whereClause != "") {
			tempSQL += " ";
			tempSQL += whereClause;
			tempSQL += " AND ";
		} else {
			tempSQL += " WHERE ";
		}
		
		tempSQL += currentdbLayer->GetPrimaryKeyColumn(0);
		tempSQL += " < ";
		tempSQL += currentCursorview[0];
		tempSQL += " ORDER BY ";
		tempSQL += currentdbLayer->GetPrimaryKeyColumn(0);
		tempSQL += " DESC "; // Reverse order to get the top most 100 key values, not the minimum 100 values. 
		
		_LOG << "Cursor is < 0. Rebuild currentCursorview with '" << tempSQL.c_str() << "'" LOG_
		
		DatabaseResultSet* tempResult = currentdbLayer->RunQueryWithResults(tempSQL);
		
		max_in_cursor = max_in_cursor_default;
		
		wxArrayString tempCursorview;

		currentCursorview.Clear();
		
		int count = 0;
		if ((tempResult != NULL) && tempResult->Next()) {
			count++;
			tempCursorview.Add(tempResult->GetResultString(1));
			while (tempResult->Next()) {
				count++;
				tempCursorview.Add(tempResult->GetResultString(1));
				if (count == max_in_cursor) break;
			}
		}
		
		for (int reverseid = count-1; reverseid >= 0; reverseid--) {
			currentCursorview.Add(tempCursorview[reverseid]);
		}
		
		// Overwrite in case of lesser elements in last cursor reading
		max_in_cursor = count;
		// Position the cursor at the end
		cursor = count-1;
		
		currentdbLayer->CloseResultSet(tempResult);
	} else if (cursor >= max_in_cursor) {
		// Handle overflow
		
		// Try to read 100 more key values from the last key in currentCursorview: currentCursorview[99]+1
		
		if (cursor > max_in_cursor) {
			// Jump to last
			wxString tempSQL = "SELECT ";
			tempSQL += currentdbLayer->GetPrimaryKeyColumn(0);
			tempSQL += " FROM ";
			tempSQL += tables[0];

			if (whereClause != "") {
				tempSQL += " ";
				tempSQL += whereClause;
			}
		
			tempSQL += " ORDER BY ";
			tempSQL += currentdbLayer->GetPrimaryKeyColumn(0);
			tempSQL += " DESC "; // Reverse order to get the top most 100 key values, not the minimum 100 values. 
			
			_LOG << "Cursor is >= max_in_cursor. Rebuild currentCursorview with '" << tempSQL.c_str() << "'" LOG_
			
			DatabaseResultSet* tempResult = currentdbLayer->RunQueryWithResults(tempSQL);
			
			max_in_cursor = max_in_cursor_default;
			
			wxArrayString tempCursorview;
			
			currentCursorview.Clear();
			
			int count = 0;
			if ((tempResult != NULL) && tempResult->Next()) {
				count++;
				wxString value = tempResult->GetResultString(1);
				//_LOG << "Fill ID list with item " << value.c_str() LOG_
				tempCursorview.Add(value);
				while (tempResult->Next()) {
					count++;
					value = tempResult->GetResultString(1);
					//_LOG << "Fill ID list with item " << value.c_str() LOG_
					tempCursorview.Add(value);
					if (count == max_in_cursor) break;
				}
			}
			
			for (int reverseid = count-1; reverseid >= 0; reverseid--) {
				currentCursorview.Add(tempCursorview[reverseid]);
			}
			
			// Overwrite in case of lesser elements in last cursor reading
			max_in_cursor = count;
			// Position the cursor at the end
			cursor = count-1;

			currentdbLayer->CloseResultSet(tempResult);
		} else {
			wxString tempSQL = "SELECT ";
			tempSQL += currentdbLayer->GetPrimaryKeyColumn(0);
			tempSQL += " FROM ";
			tempSQL += tables[0];
			
			if (currentCursorview.Count() > 0) {

				if (whereClause != "") {
					tempSQL += " ";
					tempSQL += whereClause;
					tempSQL += " AND ";
				} else {
					tempSQL += " WHERE ";
				}
		
				tempSQL += currentdbLayer->GetPrimaryKeyColumn(0);
				tempSQL += " > ";
			
				if (max_in_cursor-1 < 0) {
					tempSQL += currentCursorview[0];
				} else {
					tempSQL += currentCursorview[max_in_cursor-1];
				}
				
				tempSQL += " ORDER BY ";
				tempSQL += currentdbLayer->GetPrimaryKeyColumn(0);
			} else {
				// No cursor data, but also try add the where clause.
				if (whereClause != "") {
					tempSQL += " ";
					tempSQL += whereClause;
				}
			}
			
			_LOG << "Cursor is between 0 and max_in_cursor. Rebuild currentCursorview with '" << tempSQL.c_str() << "'" LOG_

			DatabaseResultSet* tempResult = currentdbLayer->RunQueryWithResults(tempSQL);
			
			max_in_cursor = max_in_cursor_default;
			
			currentCursorview.Clear();
			
			int count = 0;
			if (tempResult && tempResult->Next()) {
				count++;
				wxString value = tempResult->GetResultString(1);
				//_LOG << "Fill ID list with item " << value.c_str() LOG_
				currentCursorview.Add(value);
				while (tempResult->Next()) {
					count++;
					value = tempResult->GetResultString(1);
					//_LOG << "Fill ID list with item " << value.c_str() LOG_
					currentCursorview.Add(value);
					if (count == max_in_cursor) break;
				}
			}
			
			// Overwrite in case of lesser elements in last cursor reading
			max_in_cursor = count;
			
			cursor = 0;
			
			currentdbLayer->CloseResultSet(tempResult);
		}
	}

	wxString cursorWhere = " WHERE ";
	if (currentdbLayer == NULL) {
		_LOG << "Error: table has no open connection!" LOG_
		return false;
	}
	cursorWhere += currentdbLayer->GetPrimaryKeyColumn(0);
	cursorWhere += " = ";
	
	if (currentCursorview.Count() == 0) {
		_LOG << "Warning: No cursor data could be built up." LOG_
		return false;
	}
	
	cursorWhere += currentCursorview[cursor];

	wxString newQuery = plainQuery + joinClause + cursorWhere;

	theResult = currentdbLayer->RunQueryWithResults(newQuery);
	
	if (theResult && theResult->Next()) {
		ResultSetMetaData* metadata = theResult->GetMetaData();
		for (int i = 1; i <= metadata->GetColumnCount(); i++) {
			UAP(lb_I_String, name)
			name = getColumnName(i);
			_LOG << "Check field '" << name->charrep() << "'" LOG_
			if (theResult->IsFieldNull(i)) 
				setNull(i, true);
			else
				setNull(i, false);
		}

		// Cache the data, because after a finish, no data will be given back.
		
		cachedDataColumns->deleteAll();
		
		for (int i_cache = 1; i_cache <= getColumns(); i_cache++) {
			UAP_REQUEST(getModuleInstance(), lb_I_Integer, I)
			UAP(lb_I_KeyBase, key)
			UAP(lb_I_Unknown, uk)
			I->setData(i_cache);
			QI(I, lb_I_KeyBase, key)

			switch (getColumnType(i_cache)) {
				case lbDBColumnBit:
				{
					UAP_REQUEST(getModuleInstance(), lb_I_String, string)
					*string = theResult->GetResultString(i_cache).c_str();
					if (*string == "1") {
						*string = "true";
					} else {
						*string = "false";
					}
					QI(string, lb_I_Unknown, uk)
				}
					break;
				case lbDBColumnChar:
				{
					UAP_REQUEST(getModuleInstance(), lb_I_String, string)
					*string = theResult->GetResultString(i_cache).c_str();
					QI(string, lb_I_Unknown, uk)
				}
					break;
				case lbDBColumnInteger:
				{
					UAP_REQUEST(manager.getPtr(), lb_I_Long, value)
					value->setData(theResult->GetResultLong(i_cache));
					QI(value, lb_I_Unknown, uk)
				}
					break;
				case lbDBColumnBigInteger:
				{
					UAP_REQUEST(manager.getPtr(), lb_I_Long, value)
					value->setData(theResult->GetResultLong(i_cache));
					QI(value, lb_I_Unknown, uk)
				}
					break;
				case lbDBColumnBinary:
				{
					UAP_REQUEST(getModuleInstance(), lb_I_BinaryData, binarydata)
					wxMemoryBuffer buffer;
					
					if (theResult) theResult->GetResultBlob(i_cache, buffer);
					
					binarydata->append(buffer.GetData(), buffer.GetBufSize());
					binarydata->append((void*) "", 1);
					QI(binarydata, lb_I_Unknown, uk)
				}
					break;
				case lbDBColumnDate:
				{
					UAP_REQUEST(getModuleInstance(), lb_I_String, string)
					*string = theResult->GetResultString(i_cache).c_str();
					QI(string, lb_I_Unknown, uk)
				}
					break;
				case lbDBColumnFloat:
				{
					UAP_REQUEST(getModuleInstance(), lb_I_String, string)
					*string = theResult->GetResultString(i_cache).c_str();
					QI(string, lb_I_Unknown, uk)
				}
					break;
				default:
				{
					UAP_REQUEST(getModuleInstance(), lb_I_String, string)
					*string = theResult->GetResultString(i_cache).c_str();
					_LOG << "Warning: Have got unknown column (value = " << string->charrep() << ")!" LOG_
					QI(string, lb_I_Unknown, uk)
				}
					break;
			}
			
			cachedDataColumns->insert(&uk, &key);
		}
		
		
		
		// Force a finish with an error message when there was more than one row that is unexpected in this cursor algorithm.
		while (theResult->Next()) {
			_LOG << "lbDatabaseLayerQuery::selectCurrentRow() Warning: Simulated cursor gave back more than one row." LOG_
		}
		
		// Keep for meta data
		currentdbLayer->CloseResultSet(theResult);
		
		return true;
	} else {
		if (theResult) currentdbLayer->CloseResultSet(theResult);
	}
	_LOG << "lbDatabaseLayerQuery::selectCurrentRow() Query gave no data: " << newQuery.c_str() LOG_
	return false;
}

/// \todo Deeper check required.
lbErrCodes LB_STDCALL lbDatabaseLayerQuery::absolute(int pos) {
	///\todo Implement
	if (cursorFeature == false) return ERR_NONE;
	
	cursor = pos;
	if ((currentCursorview.Count() < max_in_cursor) || currentCursorview.Count() == 0) {
		cursor = 0;
		if (!selectCurrentRow()) return ERR_DB_NODATA;
		_dataFetched = true;
		return ERR_NONE;
	}
	if (max_in_cursor-1 < 0) {
		//currentCursorview[0] = "0";
		cursor = 0;
		if (!selectCurrentRow()) return ERR_DB_NODATA;
		_dataFetched = true;
		return ERR_NONE;
	}
	//currentCursorview[max_in_cursor-1] = "0";
	if (!selectCurrentRow()) return ERR_DB_NODATA;
	_dataFetched = true;
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::selectCachedRow() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, row)
	UAP(lb_I_KeyBase, key)
	QI(row, lb_I_KeyBase, key)
	
	row->setData(cachedRowIndex);
	
	if (cachedDataRows->exists(&key) == 1) {
		UAP(lb_I_Unknown, uk)
		
		uk = cachedDataRows->getElement(&key);
		cachedDataColumns--;
		cachedDataColumns.resetPtr();
		QI(uk, lb_I_Container, cachedDataColumns)
		
		if (cachedDataColumns == NULL) {
				_LOG << "Error: Stored element is not of type lb_I_Container (" << uk->getClassName() << ")!" LOG_
		}
		
		return ERR_NONE;	
	} else {
		return ERR_DB_NODATA;
	}
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::first() {
	///\todo Implement
	if (_dataFetched == false) return ERR_DB_NODATA;

	if (cursorFeature == false) {
		cachedRowIndex = 1;
		return selectCachedRow();
	}

	cursor = max_in_cursor;
	if ((currentCursorview.Count() < max_in_cursor) || currentCursorview.Count() == 0) {
		cursor = 0;
		if (!selectCurrentRow()) return ERR_DB_NODATA;
		_dataFetched = true;
		return ERR_NONE;
	}
	if (max_in_cursor-1 < 0) {
		currentCursorview[0] = "0";
		cursor = 0;
		if (!selectCurrentRow()) return ERR_DB_NODATA;
		_dataFetched = true;
		return ERR_NONE;
	}
	currentCursorview[max_in_cursor-1] = "0";
	if (!selectCurrentRow()) return ERR_DB_NODATA;
	_dataFetched = true;
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::next() {
	///\todo Implement
	if (_dataFetched == false) return ERR_DB_NODATA;

	if (cursorFeature == true) {
		cursor++;
		if (!selectCurrentRow()) return ERR_DB_NODATA;
		_dataFetched = true;
		return ERR_NONE;
	} else {
		cachedRowIndex++;
		return selectCachedRow();
	}
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::previous() {
	///\todo Implement
	if (_dataFetched == false) return ERR_DB_NODATA;

	if (cursorFeature == false) {
		cachedRowIndex--;
		return selectCachedRow();
	}

	if (cursorFeature == true) {
		cursor--;
		if (!selectCurrentRow()) return ERR_DB_NODATA;
	}
	_dataFetched = true;
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::last() {
	///\todo Implement
	if (_dataFetched == false) return ERR_DB_NODATA;

	if (cursorFeature == false) {
		cachedRowIndex = cachedDataRows->Count();
		return selectCachedRow();
	}
	if (cursorFeature == true) {
		cursor = max_in_cursor+1;
		if (!selectCurrentRow()) return ERR_DB_NODATA;
	}
	_dataFetched = true;
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::setString(lb_I_String* columnName, lb_I_String* value) {
	if (_readonly == 1) {
		_CL_LOG << "Error: Query is readonly." LOG_
		return ERR_DB_READONLY;
	}
	
	if (getColumnType(columnName->charrep()) == lbDBColumnBit) {
        if (*value == "true") {
            if (queryColumns.Index(columnName->charrep()) != wxNOT_FOUND) {
                queryValues[queryColumns.Index(columnName->charrep())] = "1";
            } else {
                queryColumns.Add(columnName->charrep());
                queryValues.Add("1");
            }        
        } else {
            if (queryColumns.Index(columnName->charrep()) != wxNOT_FOUND) {
                queryValues[queryColumns.Index(columnName->charrep())] = "0";
            } else {
                queryColumns.Add(columnName->charrep());
                queryValues.Add("0");
            }        
        }
	} else {
        if (queryColumns.Index(columnName->charrep()) != wxNOT_FOUND) {
            queryValues[queryColumns.Index(columnName->charrep())] = value->charrep();
        } else {
            queryColumns.Add(columnName->charrep());
            queryValues.Add(value->charrep());
        }
    }
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::add() {
	if (cursorFeature == false) return ERR_DB_READONLY;
	if (_readonly == 1) return ERR_DB_READONLY;

	mode = 1;
/*
	if (boundColumns != NULL) {
		boundColumns->invalidateData();
		boundColumns->add();
	} else {
		_LOG << "Error: Did not have bound columns. Could not really add data." LOG_
	}
*/
	return ERR_NONE;
}

//#define CREATE_DYNAMIC_STATEMENTS
lbErrCodes LB_STDCALL lbDatabaseLayerQuery::remove() {
	if (cursorFeature == false) return ERR_DB_READONLY;
	if (mode == 1) return ERR_DB_STILL_ADDING;

	wxString strSQL = _("DELETE FROM ");
	strSQL += tables[0];
	strSQL += " WHERE ";
	strSQL += currentdbLayer->GetPrimaryKeyColumn(0);
	strSQL += " = ";
	strSQL += currentCursorview[cursor];

	_LOG << "Update statement: " << strSQL.c_str() LOG_

	executeDirect((char*) strSQL.c_str());

	reopen();

	return ERR_NONE;
}

void LB_STDCALL lbDatabaseLayerQuery::setAutoRefresh(bool b) {
	_autoRefresh = b;
}

lbErrCodes LB_STDCALL lbDatabaseLayerQuery::update() {
	lbErrCodes err = ERR_NONE;
	if (cursorFeature == false) return ERR_DB_READONLY;

/// \todo Create a prepared statement for it.
	if (queryColumns.Count() == 0) {
		_LOG << "Warning: Noting to update." LOG_
		return ERR_NONE;
	}

	if (mode == 1) {
		// Add mode
		mode = 0;
		if (tables.Count() > 1) {
			_LOG << "Error: Could not yet handle insert statements on multiple tables." LOG_
			return ERR_DB_QUERYFAILED;
		}
		
		wxString strSQL = _("INSERT INTO ");
		strSQL += tables[0];
		strSQL += " ( ";
		for (int i = 0; i < queryColumns.Count(); i++) {
			if (i > 0) strSQL += ", ";
			strSQL += queryColumns[i];
		}
		
		if (binaryDataColumns->Count() > 0) {
			binaryDataColumns->finishIteration();
			
			while (binaryDataColumns->hasMoreElements()) {
				UAP(lb_I_Unknown, ukBinary)
				UAP(lb_I_BinaryData, binary)
				UAP(lb_I_String, name)
				UAP(lb_I_KeyBase, key)
				
				ukBinary = binaryDataColumns->nextElement();
				key = binaryDataColumns->currentKey();
				
				strSQL += ", ";
				strSQL += key->charrep();
			}
		}
		
		strSQL += " ) VALUES (";

		for (int i = 0; i < queryValues.Count(); i++) {
			if (i > 0) strSQL += ", ";
			if (isNull(i+1))
				strSQL += "NULL";
			else
				strSQL += "?";
		}

		if (binaryDataColumns->Count() > 0) {
			binaryDataColumns->finishIteration();
			
			while (binaryDataColumns->hasMoreElements()) {
				UAP(lb_I_Unknown, ukBinary)
				UAP(lb_I_BinaryData, binary)
				UAP(lb_I_String, name)
				UAP(lb_I_KeyBase, key)
				
				ukBinary = binaryDataColumns->nextElement();
				key = binaryDataColumns->currentKey();
				QI(ukBinary, lb_I_BinaryData, binary)
				
				if (binary->getData() == NULL) {
					strSQL += ", NULL";
				} else {
					strSQL += ", ?";
				}
			}
		}
		
		strSQL += " )";

		_LOG << "Insert statement: " << strSQL.c_str() LOG_

#define USE_IMMEDIALY_CLOSE
#ifdef USE_IMMEDIALY_CLOSE
			PreparedStatement* pStatement = ((SqliteDatabaseLayer*) currentdbLayer)->PrepareStatement(strSQL, false);
#endif
#ifndef USE_IMMEDIALY_CLOSE
			PreparedStatement* pStatement = currentdbLayer->PrepareStatement(strSQL);
#endif
			if (pStatement)
			{
				for (int i = 0; i < queryValues.Count(); i++) {
					pStatement->SetParamString(i+1, queryValues[i]);
				}
				
				int offset = queryValues.Count();
				
				if (binaryDataColumns->Count() > 0) {
					binaryDataColumns->finishIteration();
					
					while (binaryDataColumns->hasMoreElements()) {
						UAP(lb_I_Unknown, ukBinary)
						UAP(lb_I_BinaryData, binary)
						UAP(lb_I_String, name)
						UAP(lb_I_KeyBase, key)
						
						ukBinary = binaryDataColumns->nextElement();
						key = binaryDataColumns->currentKey();
						QI(ukBinary, lb_I_BinaryData, binary)
						
						if (binary->getData() == NULL) {
						} else {
							pStatement->SetParamBlob(++offset, binary->getData(), binary->getSize());
						}					
					}
				}
				
				try
				{
					pStatement->RunQuery();
					_LOG << "Added a new row." LOG_
#ifdef USE_IMMEDIALY_CLOSE
					pStatement->Close();
					delete pStatement;
					pStatement = NULL;
#endif
					/*				
					 char* sqlBackup = strdup(szSql);
					 skipFKCollecting();
					 query("pragma database_list;", false);
					 PrintData(false);
					 szSql = sqlBackup;
					 open();
					 enableFKCollecting();
					 */				
					//last();
				}
				catch (DatabaseLayerException& ex)
				{
					_LOG << "Error: Adding a row failed (Sql: " << strSQL.c_str() << ", Exception: " << ex.GetErrorMessage().c_str() << ")" LOG_
					
					try {
						pStatement->Close();
						delete pStatement;
						pStatement = NULL;
						theResult = NULL; // It will go invalid.
						currentdbLayer->Close();
                        skipAutoQuery = true;
						open();
						skipAutoQuery = false;

#define USE_IMMEDIALY_CLOSE
#ifdef USE_IMMEDIALY_CLOSE
						PreparedStatement* pStatement = ((SqliteDatabaseLayer*) currentdbLayer)->PrepareStatement(strSQL, false);
#endif
#ifndef USE_IMMEDIALY_CLOSE
						PreparedStatement* pStatement = currentdbLayer->PrepareStatement(strSQL);
#endif
						if (pStatement)
						{
							for (int i = 0; i < queryValues.Count(); i++) {
								pStatement->SetParamString(i+1, queryValues[i]);
							}
							
							int offset = queryValues.Count();
							
							if (binaryDataColumns->Count() > 0) {
								binaryDataColumns->finishIteration();
								
								while (binaryDataColumns->hasMoreElements()) {
									UAP(lb_I_Unknown, ukBinary)
									UAP(lb_I_BinaryData, binary)
									UAP(lb_I_String, name)
									UAP(lb_I_KeyBase, key)
									
									ukBinary = binaryDataColumns->nextElement();
									key = binaryDataColumns->currentKey();
									QI(ukBinary, lb_I_BinaryData, binary)
									
									if (binary->getData() == NULL) {
									} else {
										pStatement->SetParamBlob(++offset, binary->getData(), binary->getSize());
									}					
								}
							}

							pStatement->RunQuery();
							_LOG << "Added a new row." LOG_
#ifdef USE_IMMEDIALY_CLOSE
							pStatement->Close();
							delete pStatement;
							pStatement = NULL;
                            currentdbLayer->Close();
                            open();
#endif							
						}
					}
					catch (DatabaseLayerException& ex)
					{
						skipAutoQuery = false;
						if (pStatement) {
							pStatement->Close();
							delete pStatement;
							pStatement = NULL;
                            currentdbLayer->Close();
                            open();
						}
						_LOG << "Error: Retry adding a row failed (Sql: " << strSQL.c_str() << ", Exception: " << ex.GetErrorMessage().c_str() << ")" LOG_
					}
				}
			} else {
				_LOG << "Insert statement failed." LOG_
			}
	} else {
		if (tables.Count() > 1) {
			_LOG << "Error: Could not yet handle insert statements on multiple tables." LOG_
			return ERR_DB_QUERYFAILED;
		}
		
		if (currentCursorview.Count() == 0) {
            _LOG << "Error: Have no data loaded. Thus updating is impossible." LOG_
			return ERR_DB_NODATA;
		}
		
		wxString strSQL = _("UPDATE ");
		strSQL += tables[0];
		strSQL += " SET ";
		for (int i = 0; i < queryColumns.Count(); i++) {
			if (getColumnType((char*) queryColumns[i].c_str()) == lbDBColumnChar) {
				if (i > 0) strSQL += ", ";
				strSQL += queryColumns[i];
				if (isNull(i+1)) {
					strSQL += " = NULL";
				} else {
					strSQL += " = '";
					strSQL += queryValues[i];
					strSQL += "'";
				}
			} else {
				if (i > 0) strSQL += ", ";
				if (isNull(i+1) && queryValues[i] == "") {
					strSQL += queryColumns[i];
					strSQL += " = NULL";
				} else {
					strSQL += queryColumns[i];
					strSQL += " = ";
					if (queryValues[i].Trim() == "") {
						strSQL += "NULL";
					} else {
						strSQL += queryValues[i];
					}
				}
			}
		}
		
		if (binaryDataColumns->Count() > 0) {
			binaryDataColumns->finishIteration();
			
			while (binaryDataColumns->hasMoreElements()) {
				UAP(lb_I_Unknown, ukBinary)
				UAP(lb_I_BinaryData, binary)
				UAP(lb_I_KeyBase, key)
				
				ukBinary = binaryDataColumns->nextElement();
				key = binaryDataColumns->currentKey();
				QI(ukBinary, lb_I_BinaryData, binary)

				if (binary->getData() != NULL) {
					strSQL += ", ";
					strSQL += key->charrep();
					strSQL += " = ?";
				}
			}
		}
		
		strSQL += " WHERE ";
		strSQL += currentdbLayer->GetPrimaryKeyColumn(0);
		strSQL += " = ";
		strSQL += currentCursorview[cursor];

#define USE_IMMEDIALY_CLOSE
		PreparedStatement* pStatement = NULL;
		
		try {
#ifdef USE_IMMEDIALY_CLOSE
			pStatement = ((SqliteDatabaseLayer*) currentdbLayer)->PrepareStatement(strSQL, false);
#endif
#ifndef USE_IMMEDIALY_CLOSE
			pStatement = currentdbLayer->PrepareStatement(strSQL);
#endif
		} catch (...) {
			_LOG << "Update query failed: " << strSQL.c_str() LOG_
			return ERR_DB_UPDATEFAILED;
		}

		int paramNo = 0;
		if (binaryDataColumns->Count() > 0) {
			binaryDataColumns->finishIteration();
			
			while (binaryDataColumns->hasMoreElements()) {
				UAP(lb_I_Unknown, ukBinary)
				UAP(lb_I_BinaryData, binary)
				UAP(lb_I_String, name)
				
				ukBinary = binaryDataColumns->nextElement();
				QI(ukBinary, lb_I_BinaryData, binary)
				if (binary->getData() != NULL) {
					pStatement->SetParamBlob(++paramNo, binary->getData(), binary->getSize());
				}
			}
		}
		
		_LOG << "Update statement: " << strSQL.c_str() LOG_

		try {
			pStatement->RunQuery();
			
#ifdef USE_IMMEDIALY_CLOSE
			pStatement->Close();
			delete pStatement;
#endif
		}
		catch (DatabaseLayerException ex) {
			if (!currentdbLayer->IsOpen()) {
				_LOG << "Error: Update statement failed. Database is not open, retry update after opening the database." LOG_
				open();
				try {
					pStatement->RunQuery();
				}
				catch (...) {
					_LOG << "Error: Update statement after reoprning failed too." LOG_
				}
			} else {
				_LOG << "Error: Update statement failed. (" << ex.GetErrorMessage().c_str() << ")" LOG_
			}
		}
	}
	queryColumns.Clear();
	queryValues.Clear();

	reopen();

	if (currentCursorview.Count() == 0) {
		_LOG << "Error: Reopen failed." LOG_
	}
	
	if (binaryDataColumns->Count() > 0) {
		binaryDataColumns->deleteAll();
	}
	
	return ERR_NONE;
}

void LB_STDCALL lbDatabaseLayerQuery::dbError(char* lp, HSTMT hstmt)
{
///\todo Implement
}

/*...e*/
/*...e*/

/*...sclass lbDatabaseLayerBoundColumn:0:*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseLayerBoundColumn)
        ADD_INTERFACE(lb_I_BoundColumn)
END_IMPLEMENT_LB_UNKNOWN()

void LB_STDCALL lbDatabaseLayerBoundColumn::add() {
	mode = 1;
}

void LB_STDCALL lbDatabaseLayerBoundColumn::finishadd() {
	mode = 0;
}

bool LB_STDCALL lbDatabaseLayerBoundColumn::isBound() {
	return bound == 1;
}

bool LB_STDCALL lbDatabaseLayerBoundColumn::isNull() {
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

bool LB_STDCALL lbDatabaseLayerBoundColumn::isNullable() {
	return _isNullable;
}

bool LB_STDCALL lbDatabaseLayerBoundColumn::setNull(bool b) {
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

/*...slb_I_Query\58\\58\lbDBColumnTypes LB_STDCALL lbDatabaseLayerBoundColumn\58\\58\getType\40\\41\:0:*/
lb_I_Query::lbDBColumnTypes LB_STDCALL lbDatabaseLayerBoundColumn::getType() {
	switch (_DataType) {
	
		case SQL_FLOAT:
			return lb_I_Query::lbDBColumnFloat;
			
		case SQL_BIT:
			return lb_I_Query::lbDBColumnBit;
			
		case SQL_DATE:
		case SQL_TYPE_DATE:
			return lb_I_Query::lbDBColumnDate;

		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR: 
		
			return lb_I_Query::lbDBColumnChar;
			
		case SQL_INTEGER: 
			return lb_I_Query::lbDBColumnInteger;

		case SQL_BIGINT: 
			return lb_I_Query::lbDBColumnBigInteger;
			
		case SQL_LONGVARBINARY:
		case SQL_BINARY:
			return lb_I_Query::lbDBColumnBinary;
		
		default: return lb_I_Query::lbDBColumnUnknown;
	}

}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseLayerBoundColumn\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseLayerBoundColumn::setData(lb_I_Unknown* uk) {
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
/*...slbErrCodes LB_STDCALL lbDatabaseLayerBoundColumn\58\\58\leaveOwnership\40\lb_I_BoundColumn\42\ oldOwner\44\ lb_I_BoundColumn\42\ newOwner\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseLayerBoundColumn::leaveOwnership(lb_I_BoundColumn* oldOwner, lb_I_BoundColumn* newOwner) {

	lbDatabaseLayerBoundColumn* oO = (lbDatabaseLayerBoundColumn*) oldOwner;
	lbDatabaseLayerBoundColumn* nO = (lbDatabaseLayerBoundColumn*) newOwner;

	nO->setData(oO->bound, oO->_DataType, oO->buffer, oO->columnName);
	oO->bound = 0;
	nO->isReadonly = oO->isReadonly;
	
	nO->cbBufferLength = oO->cbBufferLength;
	oO->cbBufferLength = NULL;
	
	if (oO->buffer != NULL) oO->buffer = NULL;

	return ERR_NONE;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbDatabaseLayerBoundColumn\58\\58\getData\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbDatabaseLayerBoundColumn::getData() {
	_CL_VERBOSE << "lbDatabaseLayerBoundColumn::getData(...) not implemented yet" LOG_
	return NULL;
}
/*...e*/
lbErrCodes LB_STDCALL lbDatabaseLayerBoundColumn::getAsLong(lb_I_Long* result, int asParameter) {
	lbErrCodes err = ERR_NONE;
	
	switch (_DataType) {
		case SQL_INTEGER:
		{
			result->setData(*(long*) buffer);
			break;
		}

        default:
			_CL_VERBOSE << "lbDatabaseLayerBoundColumn::getAsLong(...) failed: Unknown or not supported datatype for column '" << columnName << "'"  LOG_
	       	break;
	}
	
	return err;
}

/*...slbErrCodes LB_STDCALL lbDatabaseLayerBoundColumn\58\\58\getAsString\40\lb_I_String\42\ result\44\ int asParameter\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseLayerBoundColumn::getAsString(lb_I_String* result, int asParameter) {
	
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
			_CL_VERBOSE << "lbDatabaseLayerBoundColumn::getAsString(...) failed: Binary data not supported for column '" << columnName << "'" LOG_
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
				result->setData("true");
			} else {
				result->setData("false");
			}	
#endif
#ifndef OSX
			bool b = *(bool*) buffer;
			if (b == true) {
				result->setData("true");
			} else {
				result->setData("false");
			}	
#endif
		}
			break;
#endif
		default:
			_CL_VERBOSE << "lbDatabaseLayerBoundColumn::getAsString(...) failed: Unknown or not supported datatype for column '" << columnName << "'"  LOG_
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
lbErrCodes LB_STDCALL lbDatabaseLayerBoundColumn::setFromLong(lb_I_Long* set, int mode) {
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
/*...slbErrCodes LB_STDCALL lbDatabaseLayerBoundColumn\58\\58\setFromString\40\lb_I_String\42\ set\44\ int mode\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseLayerBoundColumn::setFromString(lb_I_String* set, int mode) {
		if (isReadonly) {
			_CL_LOG << "Warning: Updating a column '" << columnName << "' with readonly status skipped." LOG_
			return ERR_NONE;
		}
		
		if (mode == 1) {
			switch (_DataType) {
				case SQL_DATE:
				case SQL_TYPE_DATE:
				{
					// Must set an offset for the insert buffer
					
					char* bb = (char*) buffer;
					
					char* b = strcpy(bb + ColumnSize + 1, set->getData());
					cbBufferLength[1] = strlen((char*) buffer);
					if (cbBufferLength[1] > ColumnSize+1) {
						_LOG << "Error: Set a date from string exceeds buffer size. Buffer size is " << (long) ColumnSize+1 << ", input is '" << set->charrep() << "'" LOG_
					}

				}
					break;
				case SQL_FLOAT:
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
					_CL_VERBOSE << "lbDatabaseLayerBoundColumn::setFromString(...) failed: Binary data not supported for column '" << columnName << "'"  LOG_
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
				case SQL_DATE:
				case SQL_TYPE_DATE:
				{
					char* b = strcpy((char*) buffer, set->getData());
					cbBufferLength[0] = strlen((char*) buffer);
					if (cbBufferLength[0] > ColumnSize+1) {
						_LOG << "Error: Set a date from string exceeds buffer size. Buffer size is " << (long) ColumnSize+1 << ", input is '" << set->charrep() << "'" LOG_
					}
				}
					break;
				case SQL_FLOAT:
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
					if (cbBufferLength[0] > ColumnSize+1) {
						_LOG << "Error: Set a string from string exceeds buffer size. Buffer size is " << (long) ColumnSize+1 << ", input is '" << set->charrep() << "'" LOG_
					}
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
					_CL_VERBOSE << "lbDatabaseLayerBoundColumn::setFromString(...) failed: Binary data not supported for column '" << columnName << "'" LOG_
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
/*...slbErrCodes LB_STDCALL lbDatabaseLayerBoundColumn\58\\58\prepareBoundColumn\40\lb_I_Query\42\ q\44\ int column\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseLayerBoundColumn::prepareBoundColumn(lb_I_Query* q, int column) {
///\todo Implement.
	return ERR_NONE;
}
/*...e*/
/*...svoid       LB_STDCALL lbDatabaseLayerBoundColumn\58\\58\checkReadonly\40\int column\41\:0:*/
void       LB_STDCALL lbDatabaseLayerBoundColumn::checkReadonly(int column) {
///\todo Implement.
}	
/*...e*/
void LB_STDCALL lbDatabaseLayerBoundColumn::bindNullColumn() {
///\todo Implement.
}

lbErrCodes LB_STDCALL lbDatabaseLayerBoundColumn::bindColumn(lb_I_Query* q, int column, bool ro) {
///\todo Implement.
	return ERR_NONE;
}

void LB_STDCALL lbDatabaseLayerBoundColumn::unbindReadonlyColumns() {
///\todo Implement.
}
/*...e*/
/*...svoid LB_STDCALL lbDatabaseLayerBoundColumn\58\\58\rebindReadonlyColumns\40\\41\:0:*/
void LB_STDCALL lbDatabaseLayerBoundColumn::rebindReadonlyColumns() {
///\todo Implement.
}
/*...e*/

void	LB_STDCALL lbDatabaseLayerBoundColumn::invalidateData() {
	// No extra function for adding mode.
	_hasValidData = false;
}

bool	LB_STDCALL lbDatabaseLayerBoundColumn::hasValidData() {
	if (!(_hasValidData || isReadonly)) {
		_LOG << "Bound column '" << columnName << "' has no valid data." LOG_
	}
	return _hasValidData || isReadonly || _isNullable;
}

void LB_STDCALL lbDatabaseLayerBoundColumn::unbind() {
///\todo Implement.
}


/*...svoid LB_STDCALL lbDatabaseLayerBoundColumn\58\\58\rebind\40\\41\:0:*/
void LB_STDCALL lbDatabaseLayerBoundColumn::rebind() {
///\todo Implement.
}
/*...e*/
/*...slb_I_String\42\ LB_STDCALL lbDatabaseLayerBoundColumn\58\\58\getColumnName\40\\41\:0:*/
lb_I_String* LB_STDCALL lbDatabaseLayerBoundColumn::getColumnName() {
	UAP_REQUEST(manager.getPtr(), lb_I_String, colName)
	colName->setData(columnName);
	colName++;
	
	return colName.getPtr();
}
/*...e*/
/*...svoid lbDatabaseLayerBoundColumn\58\\58\setReadonly\40\bool updateable\41\:0:*/
void lbDatabaseLayerBoundColumn::setReadonly(bool updateable) {
	isReadonly = updateable;
}
/*...e*/
/*...e*/
/*...sclass lbConnection:0:*/
class lbConnection : public lb_I_Connection
{
public:
    lbConnection();
	
    virtual ~lbConnection();
	
	DECLARE_LB_UNKNOWN()


	virtual char* LB_STDCALL getDBName();
	virtual char* LB_STDCALL getDBUser();

//-- Private interface -----------------------------------------
	virtual void LB_STDCALL setDBName(char* name);
	
	virtual void LB_STDCALL setDBUser(char* name);
	
	virtual void LB_STDCALL setConnection(DatabaseLayer* _dbl);
	
	virtual DatabaseLayer* LB_STDCALL getConnection();
	
protected:

	DatabaseLayer* dbl;
	char* _dbname;
	char* _dbuser;
};
/*...e*/

/*...sclass lbConnection implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbConnection)
	ADD_INTERFACE(lb_I_Connection)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfConnection, lbConnection)

lbConnection::lbConnection() {
	ref = STARTREF;
	_dbname = NULL;
	_dbuser = NULL;
	dbl = NULL;
}

lbConnection::~lbConnection() {
	_CL_LOG << "lbConnection::~lbConnection() called." LOG_
	if (dbl) {
		if (_dbname) {
			_CL_LOG << "lbConnection::~lbConnection() closes dbl connection. (Database: " << _dbname << ")" LOG_
		} else {
			_CL_LOG << "lbConnection::~lbConnection() closes dbl connection. (Database: -)" LOG_
		}
		try {
			dbl->Close();
		}
		catch (DatabaseLayerException& ex)
		{
			_LOG << "Error: closing database failed (Exception: " << ex.GetErrorMessage().c_str() << ")" LOG_
		}
	} else {
		if (_dbname) {
			_CL_LOG << "lbConnection::~lbConnection() Warning: No dbl connection was set (" << _dbname << ")" LOG_
		} else {
			_CL_LOG << "lbConnection::~lbConnection() Warning: No dbl connection was set." LOG_
		}
	}
	if (_dbname) free(_dbname);
	if (_dbuser) free(_dbuser);
}

char* LB_STDCALL lbConnection::getDBName() {
	return _dbname;
}

char* LB_STDCALL lbConnection::getDBUser() { 
	return _dbuser;
}

void LB_STDCALL lbConnection::setDBName(char* name) {
	if (_dbname) {
		free(_dbname);
		_dbname = NULL;
	}
	
	_dbname = (char*) malloc(strlen(name)+1);
	_dbname[0] = 0;
	
	if (name) strcpy(_dbname, name);
}

void LB_STDCALL lbConnection::setDBUser(char* name) {
	if (_dbuser) {
		free(_dbuser);
		_dbuser = NULL;
	}
	
	_dbuser = (char*) malloc(strlen(name)+1);
	_dbuser[0] = 0;

	if (name) strcpy(_dbuser, name);
}

void LB_STDCALL lbConnection::setConnection(DatabaseLayer* _dbl) {
	dbl = _dbl;
}

DatabaseLayer* LB_STDCALL lbConnection::getConnection() { 
	return dbl;
}

lbErrCodes LB_STDCALL lbConnection::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbConnection::setData() called." LOG_
	
	UAP(lb_I_Connection, con)
	QI(uk, lb_I_Connection, con)
	
	lbConnection* connection; 
	
	if (con.getPtr() != NULL) {
	    connection = (lbConnection*) con.getPtr();
		_LOG << "lbConnection::setData() called and copies the connection." LOG_

		dbl = connection->getConnection();
		if (dbl) {
			_LOG << "lbConnection::setData() the connection instance is available." LOG_
			if (dbl->IsOpen()) {
				_LOG << "lbConnection::setData() the connection instance is open." LOG_
			}
		}
		if (connection->getDBName()) _dbname = strdup(connection->getDBName());
	    if (connection->getDBUser()) _dbuser = strdup(connection->getDBUser());
		connection->setConnection(NULL); // Only one instance should have the database instance.
	}
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/



//lb_I_Container* lbDatabase::connPooling = NULL;

BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lbDatabaseLayerDatabase)
	ADD_INTERFACE(lb_I_Database)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_SINGLETON_FUNCTOR(instanceOflbDatabaseLayerDatabase, lbDatabaseLayerDatabase)

lbDatabaseLayerDatabase::lbDatabaseLayerDatabase() {
	ref = STARTREF;
	henv = 0;
	hdbc = 0;
	user = NULL;
	db = NULL;
	connPooling = NULL;
	connected = false;
	dbl = NULL;
	_LOG << "lbDatabaseLayerDatabase::lbDatabaseLayerDatabase() called." LOG_
}

lbDatabaseLayerDatabase::~lbDatabaseLayerDatabase() {
	_CL_LOG << "lbDatabaseLayerDatabase::~lbDatabaseLayerDatabase() called." LOG_
	close();
}

void	LB_STDCALL lbDatabaseLayerDatabase::close() {
	_CL_LOG << "lbDatabaseLayerDatabase::close() called." LOG_
	if (connPooling != NULL) {
		_CL_LOG << "lbDatabaseLayerDatabase::close() Info: Connection pool initialized." LOG_
		connPooling->deleteAll();
		connPooling--;
		connPooling.resetPtr();
		_CL_LOG << "lbDatabaseLayerDatabase::close() Info: Connection pool cleaned up." LOG_
	}
	try {
		if (dbl) dbl->Close();
	}
	catch (DatabaseLayerException ex) {
		_LOG << "lbDatabaseLayerDatabase::close() Error: Catched an exeption! Exception was: " << ex.GetErrorMessage().c_str() << "." LOG_
	}
	
	
	connected = false;
}

DatabaseLayer* LB_STDCALL lbDatabaseLayerDatabase::getBackend(char* connectionname) {
	open(connectionname);
	return dbl;
}

void	LB_STDCALL lbDatabaseLayerDatabase::open(char* connectionname) {
	lbErrCodes err = ERR_NONE;
	if (connectionname == NULL) {
		_LOG << "lbDatabaseLayerDatabase::getQuery() Error: Did not got a connection name." LOG_
		return;
	}

	UAP_REQUEST(getModuleInstance(), lb_I_String, connName)
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, uk)
	
	QI(connName, lb_I_KeyBase, key)

	*connName = connectionname;

	*connName += ".db3";
	
	if (connPooling == NULL) {
		_LOG << "lbDatabaseLayerDatabase::open() Initialize connection pooling." LOG_
		REQUEST(getModuleInstance(), lb_I_Container, connPooling)
	}


	if (connPooling->exists(&key) == 1) {
		uk = connPooling->getElement(&key);
		lbConnection* conn = (lbConnection*) uk.getPtr();
		
		dbl = conn->getConnection();
	} else {
		dbl = new SqliteDatabaseLayer();
		lbConnection* conn = new lbConnection();
		conn->setModuleManager(*&manager, __FILE__, __LINE__);
		conn->queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__);

		conn->setDBName(connName->charrep());
		conn->setConnection(dbl);

		if (connPooling->exists(&key) == 0) {
			connPooling->insert(&uk, &key);
		}
	}

	if (dbl == NULL) dbl = new SqliteDatabaseLayer();
	if (!dbl->IsOpen()) dbl->Open(connName->charrep());
	
	connected = true;
}

/*...slbErrCodes LB_STDCALL lbDatabaseLayerDatabase\58\\58\init\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseLayerDatabase::init() {
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseLayerDatabase\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseLayerDatabase::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbInstanceReference::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbErrCodes LB_STDCALL lbDatabaseLayerDatabase::setUser(char* _user) {
	if (user != NULL) free(user);
	user = (char*) malloc(strlen(_user)+1);
	user[0] = 0;
	strcpy(user, _user);
	_CL_VERBOSE << "lbDatabaseLayerDatabase::setUser('" << user << "') called." LOG_
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDatabaseLayerDatabase::setDB(char* _db) {
	if (db != NULL) free(db);
	db = (char*) malloc(strlen(_db)+1);
	db[0] = 0;
	strcpy(db, _db);
	_CL_VERBOSE << "lbDatabaseLayerDatabase::setDB('" << db << "') called." LOG_
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDatabaseLayerDatabase::connect(char* connectionname, char* pass) {
	_CL_VERBOSE << "lbDatabaseLayerDatabase::connect(char* pass) called. DB:" << db << ", U:" << user << ", P:" << pass LOG_
	return connect(connectionname, db, user, pass);
}

bool LB_STDCALL lbDatabaseLayerDatabase::isConnected() {
	return connected;
}

/*...slbErrCodes LB_STDCALL lbDatabaseLayerDatabase\58\\58\connect\40\char\42\ DSN\44\ char\42\ user\44\ char\42\ passwd\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseLayerDatabase::connect(char* connectionname, char* DSN, char* user, char* passwd) {
	_LOG << "lbDatabaseLayerDatabase::connect('" << connectionname << "') called." LOG_
	//connected = true;
    return ERR_NONE;
}
/*...e*/
lb_I_Query* LB_STDCALL lbDatabaseLayerDatabase::getQuery(char* connectionname, int readonly) {
	lbErrCodes err = ERR_NONE;
	lbDatabaseLayerQuery* query = new lbDatabaseLayerQuery;
	query->setModuleManager(*&manager, __FILE__, __LINE__);

	open(connectionname);
	
	if (query->init(dbl, connectionname) != ERR_NONE) {
		_LOG << "ERROR: Initializion of query has been failed!" LOG_
		
		//return NULL;
	}

	lb_I_Query* q = NULL;
	
	query->queryInterface("lb_I_Query", (void**) &q, __FILE__, __LINE__);

	return q;
}
/*...e*/

lb_I_Container* LB_STDCALL lbDatabaseLayerDatabase::getTables(char* connectionname) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Container, container)
///\todo Implement.

	DatabaseLayer* dbl = new SqliteDatabaseLayer();
	UAP_REQUEST(getModuleInstance(), lb_I_String, connName)
	*connName = connectionname;
	*connName += ".db3";
	dbl->Open(connName->charrep());
	
	wxArrayString tables = dbl->GetTables();
	UAP_REQUEST(getModuleInstance(), lb_I_String, table)
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	QI(table, lb_I_KeyBase, key)
	
	for (int i = 0; i < tables.Count(); i++) {
		*table = tables[i].c_str();
	
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
		QI(param, lb_I_Unknown, uk)
		
		*value = (const char*) "";
		*name = "TableCatalog";
		param->setUAPString(*&name, *&value);
		*value = (const char*) "";
		*name = "TableSchema";
		param->setUAPString(*&name, *&value);
		*value = (const char*) tables[i].c_str();
		*name = "TableName";
		param->setUAPString(*&name, *&value);
		*value = (const char*) "";
		*name = "TableTyp";
		param->setUAPString(*&name, *&value);
		*value = (const char*) "";
		*name = "TableRemarks";
		param->setUAPString(*&name, *&value);
		
		container->insert(&uk, &key);
	}

	container++;
	return container.getPtr();
}

lb_I_Container* LB_STDCALL lbDatabaseLayerDatabase::getColumns(char* connectionname) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Container, columns)
	columns++;
	
	DatabaseLayer* dbl = new SqliteDatabaseLayer();
	UAP_REQUEST(getModuleInstance(), lb_I_String, connName)
	*connName = connectionname;
	*connName += ".db3";
	dbl->Open(connName->charrep());
	
	DatabaseResultSet* pResult = NULL;
	ResultSetMetaData* pMetaData = NULL;
	
	long ind = 0;
	
	wxArrayString tables = dbl->GetTables();

	for (int i = 0; i < tables.Count(); i++) {
		wxString table = tables[i];
		
		wxString q = "select * from ";
		q += table;
		q += " LIMIT 0";
		
		pResult = dbl->ExecuteQuery(q);
		pResult->Next();
		pMetaData = pResult->GetMetaData();
		
		UAP_REQUEST(getModuleInstance(), lb_I_Long, index)
		UAP(lb_I_KeyBase, key)
		QI(index, lb_I_KeyBase, key)
		
		// 1-based
		for(long ii=1; ii<=pMetaData->GetColumnCount(); ii++)
		{
			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
			
			UAP_REQUEST(getModuleInstance(), lb_I_String, name)
			
			UAP_REQUEST(getModuleInstance(), lb_I_String, colName)
			UAP_REQUEST(getModuleInstance(), lb_I_String, TableName)
			UAP_REQUEST(getModuleInstance(), lb_I_String, typeName)
			UAP_REQUEST(getModuleInstance(), lb_I_Long, typeLong)
			
			UAP_REQUEST(getModuleInstance(), lb_I_String, dummyString)
			UAP_REQUEST(getModuleInstance(), lb_I_Long, dummyLong)
			
			dummyLong->setData((long)0);
			*name = "DatetimeSubtypeCode";
			param->setUAPLong(*&name, *&dummyLong);
			
			*dummyString = (const char*) "sqlite";
			*name = "TableCatalog";
			param->setUAPString(*&name, *&dummyString);
			
			*dummyString = (const char*) "lbDMF";
			*name = "TableSchema";
			param->setUAPString(*&name, *&dummyString);
			
			*TableName = (const char*) table.c_str();
			*name = "TableName";
			param->setUAPString(*&name, *&TableName);
			
			*colName = pMetaData->GetColumnName(ii).c_str();
			*name = "ColumnName";
			param->setUAPString(*&name, *&colName);
			
			long   colTypeLong = (long) pMetaData->GetColumnType(ii);
			typeLong->setData((long)colTypeLong);
			*name = "DataType";
			param->setUAPLong(*&name, *&typeLong);
			
			// Implement mapping to the same as of PostgreSQL typenames !!!
			/// \todo What is here the best type naming for all the different databases ?
			switch (colTypeLong)
			{
				case ResultSetMetaData::COLUMN_INTEGER:
					*typeName = "int4";
					break;
				case ResultSetMetaData::COLUMN_DOUBLE:
					*typeName = "Float";
					break;
				case ResultSetMetaData::COLUMN_STRING:
					*typeName = "bpchar";
					break;
				case ResultSetMetaData::COLUMN_BOOL:
					*typeName = "Bit";
					break;
				case ResultSetMetaData::COLUMN_BLOB:
					*typeName = "bytea";
					break;
				case ResultSetMetaData::COLUMN_TEXT:
					*typeName = "text";
					break;
				case ResultSetMetaData::COLUMN_NULL:
					*typeName = "COLUMN_NULL";
					break;
				default:
					*typeName = "COLUMN_UNKNOWN";
					break;
			};
			*name = "TypeName";
			param->setUAPString(*&name, *&typeName);
			
			dummyLong->setData((long)-1);
			*name = "BufferLength";
			param->setUAPLong(*&name, *&dummyLong);
			
			dummyLong->setData((long)-1);
			*name = "DecimalDigits";
			param->setUAPLong(*&name, *&dummyLong);
			
			dummyLong->setData((long)-1);
			*name = "NumPrecRadix";
			param->setUAPLong(*&name, *&dummyLong);
			
			dummyLong->setData((long)-1);
			*name = "Nullable";
			param->setUAPLong(*&name, *&dummyLong);
			
			*dummyString = (const char*) "";
			*name = "Remarks";
			param->setUAPString(*&name, *&dummyString);
			
			*dummyString = (const char*) "";
			*name = "ColumnDefault";
			param->setUAPString(*&name, *&dummyString);
			
			dummyLong->setData((long)-1);
			*name = "SQLDataType";
			param->setUAPLong(*&name, *&dummyLong);
			
			dummyLong->setData((long)-1);
			*name = "CharOctetLength";
			param->setUAPLong(*&name, *&dummyLong);
			
			dummyLong->setData((long)-1);
			*name = "OrdinalPosition";
			param->setUAPLong(*&name, *&dummyLong);
			
			*dummyString = (const char*) "";
			*name = "IsNullable";
			param->setUAPString(*&name, *&dummyString);
			
			dummyLong->setData((long)-1);
			*name = "ColumnSize";
			param->setUAPLong(*&name, *&dummyLong);
			
			UAP(lb_I_Unknown, uk)
			QI(param, lb_I_Unknown, uk)
				
			index->setData(++ind);
			columns->insert(&uk, &key);
		}
		
		if (pMetaData != NULL)
		{
			pResult->CloseMetaData(pMetaData);
			pMetaData = NULL;
		}
		
		if (pResult != NULL)
		{
			dbl->CloseResultSet(pResult);
			pResult = NULL;
		}

	}
	
	return columns.getPtr();
}

lb_I_Container* LB_STDCALL lbDatabaseLayerDatabase::getPrimaryKeys(char* connectionname) {
	lbErrCodes err = ERR_NONE;
	//UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	UAP_REQUEST(getModuleInstance(), lb_I_Container, columns)
	UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
	//meta->setStatusText("Info", "Get primary keys ...");

	columns++;
	
	UAP_REQUEST(getModuleInstance(), lb_I_Long, index)
	UAP(lb_I_KeyBase, key)
	QI(index, lb_I_KeyBase, key)
		
	long ind = 0;

	DatabaseLayer* dbl = new SqliteDatabaseLayer();
	UAP_REQUEST(getModuleInstance(), lb_I_String, connName)
	*connName = connectionname;
	*connName += ".db3";
	dbl->Open(connName->charrep());
	
	DatabaseResultSet* pResult = NULL;
	ResultSetMetaData* pMetaData = NULL;
	
	wxArrayString tables = dbl->GetTables();

	for (int i = 0; i < tables.Count(); i++) {
		int fks = dbl->GetPrimaryKeys(tables[i]);
		
		for (int ii = 0;ii < fks;ii++) {
			wxString pkcol = dbl->GetPrimaryKeyColumn(ii);
			wxString pkseq = dbl->GetPrimaryKeySequence(ii);

			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
			UAP_REQUEST(getModuleInstance(), lb_I_Long, number)
			UAP_REQUEST(getModuleInstance(), lb_I_String, name)
			UAP_REQUEST(getModuleInstance(), lb_I_String, value)
			
			*name = "TableCatalog";
			*value = (const char*) "";
			param->setUAPString(*&name, *&value);
			*name = "TableSchema";
			*value = (const char*) "";
			param->setUAPString(*&name, *&value);
			*name = "TableName";
			*value = (const char*) tables[i].c_str();
			param->setUAPString(*&name, *&value);
			*name = "ColumnName";
			*value = (const char*) pkcol.c_str();
			param->setUAPString(*&name, *&value);
			*name = "ColumnName_V2";
			*value = (const char*) "";
			param->setUAPString(*&name, *&value);
			
			*name = "KeySequence";
			value->setData(pkseq.c_str());
			param->setUAPString(*&name, *&value);
	
			UAP(lb_I_Unknown, uk)
			QI(param, lb_I_Unknown, uk)
			
			*msg = "Get primary column ";
			*msg += (const char*) pkcol.c_str();
			*msg += " of table ";
			*msg += (const char*) tables[i].c_str();
			*msg += " ...";

			index->setData(++ind);

			//meta->setStatusText("Info", msg->charrep());

			
			columns->insert(&uk, &key);
			}
	}

	return columns.getPtr();
}

lb_I_Container* LB_STDCALL lbDatabaseLayerDatabase::getForeignKeys(char* connectionname) {
	lbErrCodes err = ERR_NONE;
	//UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	UAP_REQUEST(getModuleInstance(), lb_I_Container, columns)
	UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
	//meta->setStatusText("Info", "Get foreign keys ...");

	columns++;
	
	UAP_REQUEST(getModuleInstance(), lb_I_Long, index)
	UAP(lb_I_KeyBase, key)
	QI(index, lb_I_KeyBase, key)
		
	long ind = 0;

	DatabaseLayer* dbl = new SqliteDatabaseLayer();
	UAP_REQUEST(getModuleInstance(), lb_I_String, connName)
	*connName = connectionname;
	*connName += ".db3";
	dbl->Open(connName->charrep());
	
	DatabaseResultSet* pResult = NULL;
	ResultSetMetaData* pMetaData = NULL;
	
	wxArrayString tables = dbl->GetTables();
	for (int i = 0; i < tables.Count(); i++) {
	    if (!tables[i].Upper().Contains("SQLITE_STAT1")) {
			//printf("Get foreign keys for table %s.\n", tables[i].c_str());
			int fks = dbl->GetForeignKeys(tables[i]);
			
			if (fks > 0) {
				for (int ii = 0;ii < fks;ii++) {
					wxString fkcol = dbl->GetForeignKeyFKColumn(ii);
					wxString pkcol = dbl->GetForeignKeyPKColumn(ii);
					wxString pktab = dbl->GetForeignKeyPKTable(ii);
					
					UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
					UAP_REQUEST(getModuleInstance(), lb_I_Long, number)
					UAP_REQUEST(getModuleInstance(), lb_I_String, name)
					UAP_REQUEST(getModuleInstance(), lb_I_String, value)
						
					*name = "PKTableCatalog";
					*value = (const char*) "";
					param->setUAPString(*&name, *&value);
					*name = "PKTableSchema";
					*value = (const char*) "";
					param->setUAPString(*&name, *&value);
					*name = "PKTableName";
					*value = (const char*) pktab;
					param->setUAPString(*&name, *&value);
					*name = "PKTableColumnName";
					*value = (const char*) pkcol;
					param->setUAPString(*&name, *&value);
					*name = "FKTableCatalog";
					*value = (const char*) "";
					param->setUAPString(*&name, *&value);
					*name = "FKTableSchema";
					*value = (const char*) "";
					param->setUAPString(*&name, *&value);
					*name = "FKTableName";
					*value = (const char*) tables[i].c_str();
					param->setUAPString(*&name, *&value);
					*name = "FKTableColumnName";
					*value = (const char*) fkcol;
					param->setUAPString(*&name, *&value);
					*name = "KeySequence";
					number->setData(-1);
					param->setUAPLong(*&name, *&number);
					*name = "UpdateRule";
					number->setData(-1);
					param->setUAPLong(*&name, *&number);
					*name = "DeleteRule";
					number->setData(-1);
					param->setUAPLong(*&name, *&number);
					
					index->setData(++ind);
					
					UAP(lb_I_Unknown, uk)
					QI(param, lb_I_Unknown, uk)
						
					*msg = "Get foreign column ";
					*msg += (const char*) fkcol.c_str();
					*msg += " of table ";
					*msg += (const char*) tables[i].c_str();
					*msg += " pointing to column ";
					*msg += (const char*) pkcol.c_str();
					*msg += " of table ";
					*msg += (const char*) pktab.c_str();
					*msg += " ...";
					
					//meta->setStatusText("Info", msg->charrep());
					columns->insert(&uk, &key);
				}
			}
		}
	}

	return columns.getPtr();
}

/*...svoid _dbError_STMT\40\char\42\ lp\44\ HSTMT hstmt\41\:0:*/
void _dbError_STMT(char* lp, HSTMT hstmt) {
}
/*...e*/
/*...svoid _dbError_ENV\40\char\42\ lp\44\ HENV henv\41\:0:*/
void _dbError_ENV(char* lp, HENV henv) {
}
/*...e*/
/*...svoid _dbError_DBC\40\char\42\ lp\44\ HDBC hdbc\41\:0:*/
void _dbError_DBC(char* lp, HDBC hdbc) {
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

    

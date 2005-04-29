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

#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#ifndef OSX
#include <malloc.h>
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif
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
void _dbError( LPSTR lp, HENV henv,HDBC hdbc,HSTMT hstmt);



class lbQuery;
class lbBoundColumn;
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
	lbBoundColumns() { ref = STARTREF; ArraySize = 1; }
	virtual ~lbBoundColumns() {
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
        lbErrCodes	LB_STDCALL getString(char* column, lb_I_String* instance);
        lbErrCodes      LB_STDCALL setString(char* column, lb_I_String* instance);

	void		LB_STDCALL unbindReadonlyColumns();
	void		LB_STDCALL rebindReadonlyColumns();

	bool		LB_STDCALL isNull(int pos);
	lb_I_Query::lbDBColumnTypes LB_STDCALL getColumnType(int pos);
	lb_I_Query::lbDBColumnTypes LB_STDCALL getColumnType(char* name);

	void		LB_STDCALL setUpdateable(char* column, bool updateable);
		
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
		ref = STARTREF;
		_readonly = readonly; 
		hdbc = 0; 
		hstmt = 0; 
		henv = 0;
		hupdatestmt = 0;
		databound = 0; 
		count = 0; 
		firstfetched = 0;
//		lpszTable = NULL;
		cols = 0;

		preparingFKColumns = 0;
		
		fetchstatus = 0;
		
		if (ReadOnlyColumns == NULL) {
		        REQUEST(getModuleInstance(), lb_I_Container, ReadOnlyColumns)
		}
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

	virtual void LB_STDCALL skipFKCollecting();
	virtual void LB_STDCALL enableFKCollecting();
	void LB_STDCALL prepareFKList();

	virtual char* LB_STDCALL getTableName();

	void LB_STDCALL dbError(char* lp);

	void LB_STDCALL PrintData();

        /* Set the SQL query */
        virtual lbErrCodes LB_STDCALL query(char* q, bool bind);
        
        lbErrCodes LB_STDCALL bind();

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


	/*
	 * General information based on the given query.
	 */

	virtual int		LB_STDCALL getColumns();

	virtual char*		LB_STDCALL getColumnName(int col);

	virtual int		LB_STDCALL hasFKColumn(char* FKName);
	virtual lb_I_String*	LB_STDCALL getPKTable(char const * FKName);

	virtual bool		LB_STDCALL isNull(int pos);

	virtual lb_I_Query::lbDBColumnTypes LB_STDCALL getColumnType(int pos);
	virtual lb_I_Query::lbDBColumnTypes LB_STDCALL getColumnType(char* name);

	void               LB_STDCALL setUpdateable(char* column, bool updateable = false);
        
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
	
	lbErrCodes LB_STDCALL init(HENV _henv, HDBC _hdbc, int readonly = 1);

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
	HSTMT   hupdatestmt;
	RETCODE retcode;
	char    szSql[1000];
	int	databound;
	int     firstfetched;
	int	_readonly; // readonly = 1, else = 0
	int	mode;  // insert = 1, select = 0
//	char* lpszTable;

	static int     skipFKCollections;
	int	preparingFKColumns;
	
	// Number of columns for the query
	SQLSMALLINT cols;

	UAP(lb_I_Container, ForeignColumns, __FILE__, __LINE__)

	UAP(lb_I_Container, ReadOnlyColumns, __FILE__, __LINE__)

#ifdef UNBOUND	
	UAP(lb_I_Container, boundColumns, __FILE__, __LINE__)
#endif
#ifndef UNBOUND
	UAP(lb_I_ColumnBinding, boundColumns, __FILE__, __LINE__)
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
		cbBufferLength = 0;
		buffer = NULL;
		colName = NULL;
		ColumnSize = 0;
		rows = 2;
		isUpdateable = true;
	}
	
	virtual ~lbBoundColumn() {

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
				_CL_LOG << "lbBoundColumn::~lbBoundColumn() failed: Unknown or not supported datatype for column '" << colName->charrep() << "'" LOG_
				break;
		}
		
		if ((bound != 0) && (buffer != NULL)) {
			printf("Free buffer in lbBoundColumn\n");
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



	virtual bool LB_STDCALL isNull();
	virtual lb_I_Query::lbDBColumnTypes LB_STDCALL getType();
	virtual lb_I_Unknown* LB_STDCALL getData();
	virtual lbErrCodes LB_STDCALL getAsString(lb_I_String* result, int asParameter = 0);
	virtual lbErrCodes LB_STDCALL setFromString(lb_I_String* set, int mode);

	void 		   LB_STDCALL setUpdateable(bool updateable);

	lb_I_String* LB_STDCALL getColumnName();

	lbErrCodes LB_STDCALL prepareBoundColumn(lb_I_Query* q, int column);
	lbErrCodes LB_STDCALL bindColumn(lb_I_Query* q, int column, bool ro);

	void	   LB_STDCALL unbindReadonlyColumns();
	void	   LB_STDCALL rebindReadonlyColumns();
	
protected:

	virtual lbErrCodes  LB_STDCALL setData(int b, SQLSMALLINT dt, void* bu, lb_I_String* name) {
		bound = b;
		_DataType = dt;
		buffer = bu;
		REQUEST(manager.getPtr(), lb_I_String, colName)

		if (name == NULL) {
			printf("ERROR: Cloning data with NULL pointer\n");
		}

		colName->setData(name->getData());
		return ERR_NONE;
	}

	// I call my self to leave my ownership
	virtual lbErrCodes LB_STDCALL leaveOwnership(lb_I_BoundColumn* oldOwner, lb_I_BoundColumn* newOwner);

	int		bound;
	bool		isUpdateable;
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
	long		cbBufferLength;
	SQLUINTEGER     ColumnSize; //new (long);
	int		rows;
	HSTMT 		hstmt;
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

/*...sunimplemented:0:*/
lbErrCodes LB_STDCALL lbBoundColumns::setData(lb_I_Unknown* uk) {
        _CL_LOG << "lbBoundColumns::setData(...) not implemented yet" LOG_
        
        return ERR_NOT_IMPLEMENTED;
}

lb_I_Container* LB_STDCALL lbBoundColumns::getBoundColumns() {
        _CL_LOG << "lbBoundColumns::getBoundColumns() not implemented yet" LOG_
	return NULL;
}

lbErrCodes      LB_STDCALL lbBoundColumns::setBoundColumns(lb_I_Container* bc) {
        _CL_LOG << "lbBoundColumns::setBoundColumns() not implemented yet" LOG_
	return ERR_NONE;
}
/*...e*/

/*...sbool LB_STDCALL lbBoundColumns\58\\58\isNull\40\int pos\41\:0:*/
bool LB_STDCALL lbBoundColumns::isNull(int pos) {

	lbErrCodes err = ERR_NONE;
	if (boundColumns != NULL) {
		REQUEST(manager.getPtr(), lb_I_Integer, integerKey) 
		integerKey->setData(pos);
		UAP(lb_I_Unknown, ukdata, __FILE__, __LINE__)
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
		
		QI(integerKey, lb_I_KeyBase, key, __FILE__, __LINE__)

		ukdata = boundColumns->getElement(&key);
		if (ukdata == NULL) printf("NULL pointer!\n");

		UAP(lb_I_BoundColumn, bc, __FILE__, __LINE__)
		lbErrCodes err = ukdata->queryInterface("lb_I_BoundColumn", (void**) &bc, __FILE__, __LINE__);

		return bc->isNull();
	}

	// What to answer here ??
	return false;
}
/*...e*/
/*...svoid LB_STDCALL lbBoundColumns\58\\58\unbindReadonlyColumns\40\\41\:0:*/
void LB_STDCALL lbBoundColumns::unbindReadonlyColumns() {
	lbErrCodes err = ERR_NONE;
	
	if (boundColumns != NULL) {
		while (boundColumns->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
			UAP(lb_I_BoundColumn, bc, __FILE__, __LINE__)
			
			uk = boundColumns->nextElement();
			
			QI(uk, lb_I_BoundColumn, bc, __FILE__, __LINE__)
			
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
			UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
			UAP(lb_I_BoundColumn, bc, __FILE__, __LINE__)
			
			uk = boundColumns->nextElement();
			
			QI(uk, lb_I_BoundColumn, bc, __FILE__, __LINE__)
			
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
		UAP(lb_I_Unknown, ukdata, __FILE__, __LINE__)
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
		
		QI(integerKey, lb_I_KeyBase, key, __FILE__, __LINE__)

		ukdata = boundColumns->getElement(&key);
		if (ukdata == NULL) printf("NULL pointer!\n");

		UAP(lb_I_BoundColumn, bc, __FILE__, __LINE__)
		lbErrCodes err = ukdata->queryInterface("lb_I_BoundColumn", (void**) &bc, __FILE__, __LINE__);

		return bc->getType();
	}

	return lb_I_Query::lbDBColumnUnknown;
}
/*...e*/
/*...slb_I_Query\58\\58\lbDBColumnTypes LB_STDCALL lbBoundColumns\58\\58\getColumnType\40\char\42\ name\41\:0:*/
lb_I_Query::lbDBColumnTypes LB_STDCALL lbBoundColumns::getColumnType(char* name) {

	lbErrCodes err = ERR_NONE;
	if (boundColumns != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, stringKey) 
		stringKey->setData(name);
		UAP(lb_I_Unknown, ukdata, __FILE__, __LINE__)
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
		
		QI(stringKey, lb_I_KeyBase, key, __FILE__, __LINE__)

		ukdata = ColumnNameMapping->getElement(&key);
		if (ukdata == NULL) printf("NULL pointer!\n");

		UAP(lb_I_BoundColumn, bc, __FILE__, __LINE__)
		UAP(lb_I_Integer, pos, __FILE__, __LINE__)
		
		lbErrCodes err = ukdata->queryInterface("lb_I_Integer", (void**) &pos, __FILE__, __LINE__);
		
		return getColumnType(pos->getData());
	}

	return lb_I_Query::lbDBColumnUnknown;
}
/*...e*/
/*...svoid LB_STDCALL lbBoundColumns\58\\58\setUpdateable\40\char\42\ column\44\ bool updateable\41\:0:*/
void LB_STDCALL lbBoundColumns::setUpdateable(char* column, bool updateable) {

	lbErrCodes err = ERR_NONE;
	if (boundColumns != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, stringKey) 
		stringKey->setData(column);
		UAP(lb_I_Unknown, ukdata, __FILE__, __LINE__)
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
		
		QI(stringKey, lb_I_KeyBase, key, __FILE__, __LINE__)

		ukdata = ColumnNameMapping->getElement(&key);
		if (ukdata == NULL) printf("NULL pointer!\n");

		UAP(lb_I_Integer, pos, __FILE__, __LINE__)
		
		lbErrCodes err = ukdata->queryInterface("lb_I_Integer", (void**) &pos, __FILE__, __LINE__);
		
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerKey) 
		integerKey->setData(pos.getPtr());
		UAP(lb_I_Unknown, ukdata1, __FILE__, __LINE__)
		UAP(lb_I_KeyBase, key1, __FILE__, __LINE__)
		
		QI(integerKey, lb_I_KeyBase, key1, __FILE__, __LINE__)

		ukdata1 = boundColumns->getElement(&key1);
		if (ukdata1 == NULL) printf("NULL pointer!\n");

		UAP(lb_I_BoundColumn, bc, __FILE__, __LINE__)
		err = ukdata1->queryInterface("lb_I_BoundColumn", (void**) &bc, __FILE__, __LINE__);

		bc->setUpdateable(updateable);
	}
}
/*...e*/
/*...slb_I_BoundColumn\42\ LB_STDCALL lbBoundColumns\58\\58\getBoundColumn\40\int column\41\:0:*/
lb_I_BoundColumn* LB_STDCALL lbBoundColumns::getBoundColumn(int column) {
	lbErrCodes err = ERR_NONE;
	if (boundColumns != NULL) {
		REQUEST(manager.getPtr(), lb_I_Integer, integerKey) 
		integerKey->setData(column);
		UAP(lb_I_Unknown, ukdata, __FILE__, __LINE__)
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
		
		QI(integerKey, lb_I_KeyBase, key, __FILE__, __LINE__)

		ukdata = boundColumns->getElement(&key);
		if (ukdata == NULL) printf("NULL pointer!\n");

		UAP(lb_I_BoundColumn, bc, __FILE__, __LINE__)
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

class lbQuery;

/*...slbErrCodes      LB_STDCALL lbBoundColumns\58\\58\setQuery\40\lbQuery\42\ q\44\ lb_I_Container\42\ ReadonlyColumns\41\:0:*/
lbErrCodes      LB_STDCALL lbBoundColumns::setQuery(lb_I_Query* q, lb_I_Container* ReadonlyColumns) {
/*...spreparements:0:*/

	lbQuery* qq = (lbQuery*) q;

	HSTMT hstmt = qq->getCurrentStatement();
	query = qq;

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
	REQUEST(manager.getPtr(), lb_I_Container, boundColumns)
	REQUEST(manager.getPtr(), lb_I_Integer, integerKey)

	// For each column create a bound column instance.
	// The instance will bind the column.
	for (int i = 1; i <= num; i++) {
		lbErrCodes err = ERR_NONE;

		// Create the instance ...
		
		lbBoundColumn* bc = new lbBoundColumn();

		lb_I_Module* m = getModuleManager();


		bc->setModuleManager(m, __FILE__, __LINE__);

		bc->prepareBoundColumn(q, i);

		integerKey->setData(i);

		UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)

		bc->queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__);
		integerKey->queryInterface("lb_I_KeyBase", (void**) &key, __FILE__, __LINE__);		

		boundColumns->insert(&uk, &key);

		UAP(lb_I_BoundColumn, bc1, __FILE__, __LINE__)
		bc1 = getBoundColumn(i);

		UAP_REQUEST(manager.getPtr(), lb_I_String, colName)
		UAP(lb_I_KeyBase, key1, __FILE__, __LINE__)
		colName->setData(qq->getColumnName(i));
		QI(colName, lb_I_KeyBase, key1, __FILE__, __LINE__)

		bool Readonly = false;

		if (ReadonlyColumns->exists(&key1) == 1) Readonly = true;

		bc1->bindColumn(q, i, Readonly);

/*...sGet the column name for this column and add an index to it\39\s column id\46\:16:*/

		if (ColumnNameMapping == NULL) {
			// Create the index mapping instnce
			
			REQUEST(manager.getPtr(), lb_I_Container, ColumnNameMapping)
		}
		
		UAP(lb_I_KeyBase, skey, __FILE__, __LINE__)
		UAP(lb_I_String, string, __FILE__, __LINE__)

		string = bc1->getColumnName();

		string->queryInterface("lb_I_KeyBase", (void**) &skey, __FILE__, __LINE__);

		UAP(lb_I_Unknown, ivalue, __FILE__, __LINE__)

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
/*...slbErrCodes      LB_STDCALL lbBoundColumns\58\\58\getString\40\int column\44\ lb_I_String\42\ instance\41\:0:*/
lbErrCodes	LB_STDCALL lbBoundColumns::getString(int column, lb_I_String* instance) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_BoundColumn, bc, __FILE__, __LINE__)

	bc = getBoundColumn(column);
	bc++;
	bc->getAsString(instance);

	return ERR_NONE;
}
/*...e*/
lbErrCodes	LB_STDCALL lbBoundColumns::getString(char* column, lb_I_String* instance) {
	return ERR_NONE;
}
/*...slbErrCodes      LB_STDCALL lbBoundColumns\58\\58\setString\40\char\42\ column\44\ lb_I_String\42\ instance\41\:0:*/
lbErrCodes      LB_STDCALL lbBoundColumns::setString(char* column, lb_I_String* instance) {
	lbErrCodes err = ERR_NONE;
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
/*...e*/

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

void LB_STDCALL lbQuery::skipFKCollecting() {
	skipFKCollections = 1;
}

void LB_STDCALL lbQuery::enableFKCollecting() {
	skipFKCollections = 0;
}

void LB_STDCALL lbQuery::PrintData() {
	lbErrCodes err = ERR_NONE;
	
	lb_I_Query* q = this;
	
	if (q->first() == ERR_NONE) {
		UAP(lb_I_String, s, __FILE__, __LINE__)
		s = q->getAsString(q->getColumns());
		s->trim();

	    for (int cols = 1; cols <= q->getColumns()-1; cols++) {
			UAP(lb_I_String, s1, __FILE__, __LINE__)
			s1 = q->getAsString(cols);
			s1->trim();
			printf("%s;", s1->charrep());
	    };
	    
	    printf("%s\n", s->charrep());
	    
	    while ((err = q->next()) == ERR_NONE) {
			for (int cols = 1; cols <= q->getColumns()-1; cols++) { 
				s = q->getAsString(cols);
				s->trim();
				printf("%s;", s->charrep());
			};
			s = q->getAsString(q->getColumns());
			s->trim();
			printf("%s\n", s->charrep());
	    };	    
		
	    if (err == WARN_DB_NODATA) {
			for (int cols = 1; cols <= q->getColumns()-1; cols++) { 
				s = q->getAsString(cols);
				s->trim();
				printf("%s;", s->charrep());
			};
			s = q->getAsString(q->getColumns());
			s->trim();
			printf("%s\n", s->charrep());
	    };	    
	}
}


/*...slbErrCodes LB_STDCALL lbQuery\58\\58\init\40\HENV _henv\44\ HDBC _hdbc\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::init(HENV _henv, HDBC _hdbc, int readonly) {
	hdbc = _hdbc;
	henv = _henv;

/*...sbla:0:*/
	hdbc = _hdbc;

	retcode = SQLAllocStmt(hdbc, &hstmt); /* Statement handle */

	if (retcode != SQL_SUCCESS)
	{
	        dbError( "SQLAllocStmt()");
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
                dbError( "SQLSetStmtOption()");
                _LOG << "lbDatabase::getQuery() failed due to setting concurrency settings." LOG_
                SQLFreeEnv(henv);
                return ERR_DB_ALLOCSTATEMENT;
        }

	retcode = SQLSetStmtOption(hstmt, SQL_CURSOR_TYPE, SQL_CURSOR_KEYSET_DRIVEN);


	if (retcode == SQL_SUCCESS_WITH_INFO) {
                dbError( "SQLSetStmtOption()");
                _LOG << "lbDatabase::getQuery() failed due to setting cursor type." LOG_
	} else
        if (retcode != SQL_SUCCESS)
        {
                dbError( "SQLSetStmtOption()");
                _LOG << "lbDatabase::getQuery() failed due to setting cursor type." LOG_
                SQLFreeEnv(henv);
                return ERR_DB_ALLOCSTATEMENT;
        }

        SQLINTEGER size = 1;
/*
	retcode = SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_ARRAY_SIZE, (SQLPOINTER) &size, 0);

        if (retcode != SQL_SUCCESS)
        {
		_dbError( "SQLSetStmtAttr()",henv,hdbc,hstmt);
                _LOG << "lbDatabase::getQuery() failed due to setting row array size." LOG_
                SQLFreeEnv(henv);
                return ERR_DB_ALLOCSTATEMENT;
        }
*/
// Unneccesary
//	retcode = SQLSetStmtAttr(hstmt, SQL_ATTR_CURSOR_SCROLLABLE, (SQLPOINTER) SQL_SCROLLABLE, 0);




	if (retcode != SQL_SUCCESS) {
		dbError( "SQLSetStmtAttr()");
		_LOG << "lbDatabase::getQuery() failed due to set statement attributes." LOG_
		//SQLFreeEnv(henv);
		return ERR_DB_ALLOCSTATEMENT;
	}	
/*...e*/
/*...sbla:0:*/
#ifdef bla
	hdbc = _hdbc;

	retcode = SQLAllocStmt(hdbc, &hupdatestmt); /* Statement handle */

	if (retcode != SQL_SUCCESS)
	{
	        _dbError( "SQLAllocStmt()",henv,hdbc,hupdatestmt);
	        _LOG << "lbDatabase::getQuery() failed due to statement allocation." LOG_
	        SQLFreeEnv(henv);
        	return ERR_DB_ALLOCSTATEMENT;
	}


	if (readonly == 0) {
	// Compare values before updating
		retcode = SQLSetStmtOption(hupdatestmt, SQL_ATTR_CONCURRENCY, SQL_CONCUR_ROWVER);
		_readonly = readonly;
	}

        if (retcode != SQL_SUCCESS)
        {
                _dbError( "SQLSetStmtOption()",henv,hdbc,hupdatestmt);
                _LOG << "lbDatabase::getQuery() failed due to setting concurrency settings." LOG_
                SQLFreeEnv(henv);
                return ERR_DB_ALLOCSTATEMENT;
        }

	retcode = SQLSetStmtOption(hupdatestmt, SQL_CURSOR_TYPE, SQL_CURSOR_KEYSET_DRIVEN);

        if (retcode != SQL_SUCCESS)
        {
                _dbError( "SQLSetStmtOption()",henv,hdbc,hupdatestmt);
                _LOG << "lbDatabase::getQuery() failed due to setting cursor type." LOG_
                SQLFreeEnv(henv);
                return ERR_DB_ALLOCSTATEMENT;
        }

	retcode = SQLSetStmtAttr(hupdatestmt, SQL_ATTR_ROW_ARRAY_SIZE, (SQLPOINTER) size, 0);

        if (retcode != SQL_SUCCESS)
        {
                _dbError( "SQLSetStmtAttr()",henv,hdbc,hupdatestmt);
                _LOG << "lbDatabase::getQuery() failed due to setting row array size." LOG_
                SQLFreeEnv(henv);
                return ERR_DB_ALLOCSTATEMENT;
        }

// Unneccesary
//	retcode = SQLSetStmtAttr(hstmt, SQL_ATTR_CURSOR_SCROLLABLE, (SQLPOINTER) SQL_SCROLLABLE, 0);




	if (retcode != SQL_SUCCESS) {
		_dbError( "SQLSetStmtAttr()",henv,hdbc,hupdatestmt);
		_LOG << "lbDatabase::getQuery() failed due to set statement attributes." LOG_
		//SQLFreeEnv(henv);
		return ERR_DB_ALLOCSTATEMENT;
	}
#endif	
/*...e*/
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\bind\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::bind() {
	if (databound == 0) {
		
		_CL_LOG << "lbQuery::bind() binds columns..." LOG_
		
		retcode = SQLNumResultCols(hstmt, &cols);
	
		if (retcode != SQL_SUCCESS)
		{
		        dbError( "SQLNumResultCols()");
		        return ERR_DB_QUERYFAILED;
		} else {
			lbBoundColumns* boundcols = NULL;
			
			boundcols = new lbBoundColumns();
			boundcols->setModuleManager(*&manager, __FILE__, __LINE__);
			boundColumns = boundcols;
		
			_CL_LOG << "Bind columns with " << ReadOnlyColumns->Count() << " readonly elements" LOG_
		
			boundColumns->setQuery(this, ReadOnlyColumns.getPtr());
			
			prepareFKList();
		}
		
		databound = 1;
	}
	
	return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbQuery\58\\58\query\40\char\42\ q\44\ bool bind\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::query(char* q, bool bind) {
	lbBoundColumns* boundcols = NULL;

	if (strlen(q) >= 1000) printf("WARNING: Bufferoverflow in %s at %d\n", __FILE__, __LINE__);

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
/*...sbla:0:*/
/*
	char cursorname[100] = "";
	
	sprintf(cursorname, "Cursor-%p", this);

	retcode = SQLSetCursorName(hstmt, cursorname, SQL_NTS);
*/	
/*...e*/

	retcode = SQLExecDirect(hstmt, (unsigned char*) szSql, SQL_NTS);

	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO))
        {
        	dbError( "SQLExecDirect()");
		_LOG << "lbQuery::query(...) failed. (" << szSql << ")" LOG_
		return ERR_DB_QUERYFAILED;
        }

	if (bind) {
		retcode = SQLNumResultCols(hstmt, &cols);
	
		if (retcode != SQL_SUCCESS)
		{
		        dbError( "SQLNumResultCols()");
		        return ERR_DB_QUERYFAILED;
		} else {

			boundcols = new lbBoundColumns();
			boundcols->setModuleManager(*&manager, __FILE__, __LINE__);
			boundColumns = boundcols;
		
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
	
	return string.getPtr();
}
#endif
/*...e*/
//#define USE_FETCH_SCROLL

int   LB_STDCALL lbQuery::getColumns() {
	SWORD count;
	retcode = SQLNumResultCols(hstmt, &count);
	
	return count;
}

/*...sint LB_STDCALL lbQuery\58\\58\hasFKColumn\40\char\42\ FKName\41\:0:*/
int LB_STDCALL lbQuery::hasFKColumn(char* FKName) {
	lbErrCodes err = ERR_NONE;


	if (skipFKCollections == 1) {
		_CL_VERBOSE << "Warning: Skipping for checking of foreign columns." LOG_
		return 0;
	}
	
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	UAP_REQUEST(manager.getPtr(), lb_I_String, s)
	
	s->setData(FKName);
	
	QI(s, lb_I_KeyBase, key, __FILE__, __LINE__)
	
	if (ForeignColumns->exists(&key) == 1) return 1;

	return 0;
}
/*...e*/

/*...slb_I_String\42\ LB_STDCALL lbQuery\58\\58\getPKTable\40\char const \42\ FKName\41\:0:*/
lb_I_String* LB_STDCALL lbQuery::getPKTable(char const * FKName) {
	lbErrCodes err = ERR_NONE;


	if (skipFKCollections == 1) {
		_CL_VERBOSE << "Warning: Skipping for checking of foreign columns." LOG_
		return NULL;
	}
	
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	UAP_REQUEST(manager.getPtr(), lb_I_String, s)
	
	s->setData(FKName);
	
	QI(s, lb_I_KeyBase, key, __FILE__, __LINE__)
	
	if (ForeignColumns->exists(&key) == 1) {
		UAP(lb_I_String, string, __FILE__, __LINE__)
		UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
		
		uk = ForeignColumns->getElement(&key)->clone(__FILE__, __LINE__);
		
		QI(uk, lb_I_String, string, __FILE__, __LINE__)

		string++;
		
		return string.getPtr();
	}

	return NULL;
}
/*...e*/

/*...svoid LB_STDCALL lbQuery\58\\58\prepareFKList\40\\41\:0:*/
void LB_STDCALL lbQuery::prepareFKList() {
	#define TAB_LEN 100
	#define COL_LEN 100

	REQUEST(manager.getPtr(), lb_I_Container, ForeignColumns)

	if (skipFKCollections == 1) {
	    _CL_VERBOSE << "==========================================" LOG_
	    _CL_VERBOSE << "Do not collect foreign column information!" LOG_
	    _CL_VERBOSE << "==========================================" LOG_

	    return;
	}

/*...sOriginally for windows:8:*/

	unsigned char*   szTable;     /* Table to display   */

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
	SQLBindCol(hstmt, 4, SQL_C_CHAR, szPkCol, COL_LEN, &cbPkCol);
	SQLBindCol(hstmt, 5, SQL_C_SSHORT, &iKeySeq, TAB_LEN, &cbKeySeq);
	SQLBindCol(hstmt, 7, SQL_C_CHAR, szFkTable, TAB_LEN, &cbFkTable);
	SQLBindCol(hstmt, 8, SQL_C_CHAR, szFkCol, COL_LEN, &cbFkCol);

	if (retcode != SQL_SUCCESS)
	{
	        _dbError( "SQLAllocStmt()",henv,hdbc,hstmt);
	}

	szTable = (unsigned char*) strdup(getTableName());
	
	if (strlen((char* const) szTable) > 99) {
		_CL_LOG << "ERROR: Possible buffer overflows!" LOG_
	}
	
	retcode = SQLForeignKeys(hstmt,
	         NULL, 0,      /* Primary catalog   */
	         NULL, 0,      /* Primary schema   */
	         NULL, 0,      /* Primary table   */
	         NULL, 0,      /* Foreign catalog   */
	         NULL, 0,      /* Foreign schema   */
	         szTable, SQL_NTS);      /* Foreign table   */


	while ((retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO)) {

	/* Fetch and display the result set. This will be all of the */
	/* foreign keys in other tables that refer to the ORDERS */
	/* primary key.                 */

	   retcode = SQLFetch(hstmt);
	   
	   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
	      lbErrCodes err = ERR_NONE;

	      printf("%-s ( %-s ) <-- %-s ( %-s )\n", szPkTable, szPkCol, szFkTable, szFkCol);
	      
	      
	      UAP_REQUEST(manager.getPtr(), lb_I_String, FKName)
	      UAP_REQUEST(manager.getPtr(), lb_I_String, PKTable)
	      
	      FKName->setData((char*) szFkCol);
	      PKTable->setData((char*) szPkTable);
	      
	      UAP(lb_I_Unknown, uk_PKTable, __FILE__, __LINE__)
	      UAP(lb_I_KeyBase, key_FKName, __FILE__, __LINE__)
	      
	      QI(FKName, lb_I_KeyBase, key_FKName, __FILE__, __LINE__)
	      QI(PKTable, lb_I_Unknown, uk_PKTable, __FILE__, __LINE__)

	      ForeignColumns->insert(&uk_PKTable, &key_FKName);
	      
	   }
	}

	/* Close the cursor (the hstmt is still allocated). */

	SQLFreeStmt(hstmt, SQL_DROP);
/*...e*/


// MySQL does not yet support Foreign keys or my tests with type INNODB doesn't work
// Fallback to use manual queries.

	if (ForeignColumns->Count() == 0) {		
/*...sOriginally for Linux:8:*/
	lbErrCodes err = ERR_NONE;
	
	char buffer[1000] = "";
	
	/* For each column in the table for the current query try to select the PKTable and associate it to
	   the foreign column.
	 */
	
	char* table = getTableName();
	
	lb_I_Module* m = getModuleManager();

	if (m != manager.getPtr()) {
	    _CL_LOG << "ERROR: Existing manager pointer is not the same as a fresh initialized one!" LOG_ 
	}
	
        UAP_REQUEST(m, lb_I_Database, db)
        db->init();
	
        char* user = getenv("lbDMFUser");
        char* pass = getenv("lbDMFPasswd");
	
        if (!user) user = "dba";
        if (!pass) pass = "trainres";
	
        db->connect("lbDMF", user, pass);

	
	for (int i = 1; i <= getColumns(); i++) { 
    	    lb_I_Query* q;

	    buffer[0] = 0;
	    
	    char* column = getColumnName(i);

	    sprintf(buffer, "select PKTable from ForeignKey_VisibleData_Mapping where FKTable = '%s' and FKName = '%s'", table, column);

	    q = db->getQuery(0);

	    skipFKCollections = 1;
	    err = q->query(buffer);
	    skipFKCollections = 0;
	    
	    err = q->first();

	    if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, FKName)
	        UAP_REQUEST(manager.getPtr(), lb_I_String, PKTable)
	
		PKTable = q->getAsString(1);
		
	        FKName->setData(column);
		
		UAP(lb_I_Unknown, uk_PKTable, __FILE__, __LINE__)
		UAP(lb_I_KeyBase, key_FKName, __FILE__, __LINE__)
	      
	        QI(FKName, lb_I_KeyBase, key_FKName, __FILE__, __LINE__)
	        QI(PKTable, lb_I_Unknown, uk_PKTable, __FILE__, __LINE__)

	        ForeignColumns->insert(&uk_PKTable, &key_FKName);
	    }
	}
/*...e*/
	}
}
/*...e*/

bool LB_STDCALL lbQuery::isNull(int pos) {
	return boundColumns->isNull(pos);
}

lb_I_Query::lbDBColumnTypes LB_STDCALL lbQuery::getColumnType(int pos) {
	return boundColumns->getColumnType(pos);
}

lb_I_Query::lbDBColumnTypes LB_STDCALL lbQuery::getColumnType(char* name) {
	return boundColumns->getColumnType(name);
}

void LB_STDCALL lbQuery::setUpdateable(char* column, bool updateable) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, col)
	
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	
	QI(col, lb_I_KeyBase, key, __FILE__, __LINE__)
	QI(col, lb_I_Unknown, uk, __FILE__, __LINE__)
	
	col->setData(column);

	if (ReadOnlyColumns == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, ReadOnlyColumns)
	}

	ReadOnlyColumns->insert(&uk, &key);

	if (boundColumns.getPtr() != NULL) boundColumns->setUpdateable(column, updateable);
}

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

	strcpy(lbQuery_column_Name, (char*) ColumnName);
	
	return lbQuery_column_Name;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\first\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::first() {
        UWORD   RowStat[20];
        UDWORD  RowsFetched = 0;
	
        // Indicate, that data must prebound to a buffer
        databound = 0;

	fetchstatus = -1;

#ifndef USE_FETCH_SCROLL
        retcode = SQLExtendedFetch(hstmt, SQL_FETCH_FIRST, 0, &RowsFetched, RowStat);
#endif

#ifdef USE_FETCH_SCROLL
	retcode = SQLFetchScroll(hstmt, SQL_FETCH_FIRST, 0);
#endif

        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
                _LOG << "lbQuery::first(): Error while fetching next row" LOG_
                printf("Error in lbQuery::first()\n");
                dbError( "SQLExtendedFetch()");
                
                // Unsave !!
                if (retcode == SQL_SUCCESS_WITH_INFO) return ERR_NONE;
                
                return ERR_DB_FETCHFIRST;
        }

// Try also fetch probe here

		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, RowStat);

char buf[100] = "";

		if (retcode == SQL_NO_DATA) {
			// Indicate for no data and go back

			retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, RowStat);
			
			if (retcode == SQL_NO_DATA) {
				_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
				
				fetchstatus = 2;
				
				return ERR_DB_NODATA;
			}
			
			fetchstatus = 1;
			
			return WARN_DB_NODATA;
		} else {

_LOG << "Fetch gave no error, so all would be good." LOG_

			retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, RowStat);
			
			if (retcode == SQL_NO_DATA) {
				_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
				
				fetchstatus = 2;
				
				return ERR_DB_NODATA;
			}
			
			fetchstatus = 0;
			
			return ERR_NONE;
		}



#ifndef USE_FETCH_SCROLL        
        if (RowsFetched == 0) return ERR_DB_FETCHFIRST;
#endif
        
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\next\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::next() {
	UWORD   RowStat[20];
	UDWORD  RowsFetched = 0;
	
	// Indicate, that data must prebound to a buffer
	databound = 0;

#ifndef USE_FETCH_SCROLL
	retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, RowStat);

	/* Check for having no data.
	 * This could only happen, if really no data is in the resultset.
	 */
	 
	if (retcode == SQL_NO_DATA) {

		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, RowStat);

		_LOG << "Return error" LOG_	

		fetchstatus = 1;
		
		return ERR_DB_NODATA;
	} else {
		// Check next row to indicate having still data or not

// These check and error output solved pSQLODBC driver bug
		
		if ((retcode == SQL_SUCCESS_WITH_INFO) || (retcode == SQL_ERROR)) {
			_LOG << "lbQuery::next() - SQLExtendedFetch failed" LOG_
			
			if (retcode == SQL_SUCCESS_WITH_INFO) dbError( "SQLExtendedFetch() failed with SQL_SUCCESS_WITH_INFO");
			if (retcode == SQL_ERROR) dbError( "SQLExtendedFetch() failed with SQL_ERROR");
		}
		

		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, RowStat);

		if (retcode == SQL_NO_DATA) {
			// Indicate for no data and go back

			retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, RowStat);
			
			if (retcode == SQL_NO_DATA) {
				_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
				
				fetchstatus = 2;
				
				return ERR_DB_NODATA;
			}
			
			fetchstatus = 1;
			
			return WARN_DB_NODATA;
		} else {

			retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, RowStat);
			
			if (retcode == SQL_NO_DATA) {
				_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
				
				fetchstatus = 2;
				
				return ERR_DB_NODATA;
			}
			
			fetchstatus = 0;
			
			return ERR_NONE;
		}
	}
	
#endif

#ifdef USE_FETCH_SCROLL
	retcode = SQLFetchScroll(hstmt, SQL_FETCH_NEXT, 0);
#endif

#ifdef bla
	if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
		_LOG << "lbQuery::next(): Error while fetching next row" LOG_
		printf("Error in lbQuery::next()\n");
		dbError( "SQLExtendedFetch()");

		// Unsave !!
		if (retcode == SQL_SUCCESS_WITH_INFO) {
			_LOG << "lbQuery::next() returns with SQL_SUCCESS_WITH_INFO" LOG_
			return ERR_NONE;
		}
		
		return ERR_DB_NODATA;
        }

#ifndef USE_FETCH_SCROLL
	if (RowsFetched == 0) {
		_LOG << "lbQuery::next() returns with ERR_DB_NODATA" LOG_
		return ERR_DB_NODATA;
	}
#endif

	return ERR_NONE;
#endif
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\previous\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::previous() {
        UWORD   RowStat[20];
        UDWORD  RowsFetched = 0;

        // Indicate, that data must prebound to a buffer
        databound = 0;
        
#ifndef USE_FETCH_SCROLL
        retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, RowStat);

	/* Check for having no data.
	 * This could only happen, if really no data is in the resultset.
	 */
	if (retcode == SQL_NO_DATA) {
		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, RowStat);
		
		fetchstatus = -1;
		
		return ERR_DB_NODATA;
	} else {
		// Check next row to indicate having still data or not
		
// These check and error output solved pSQLODBC driver bug
		
		if ((retcode == SQL_SUCCESS_WITH_INFO) || (retcode == SQL_ERROR)) {
			_LOG << "lbQuery::next() - SQLExtendedFetch failed" LOG_
			
			if (retcode == SQL_SUCCESS_WITH_INFO) dbError( "SQLExtendedFetch() failed with SQL_SUCCESS_WITH_INFO");
			if (retcode == SQL_ERROR) dbError( "SQLExtendedFetch() failed with SQL_ERROR");
		}
		
		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, RowStat);

//char buf[100] = "";
		
		if (retcode == SQL_NO_DATA) {
			// Indicate for no data and go back
			retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, RowStat);
			
			if (retcode == SQL_NO_DATA) {
				_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
				
				fetchstatus = -2;
				
				return ERR_DB_NODATA;
			}
			
			fetchstatus = -1;
			
			return WARN_DB_NODATA;
		} else {
			retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, RowStat);
			
			if (retcode == SQL_NO_DATA) {
				_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
				
				fetchstatus = -2;
				
				return ERR_DB_NODATA;
			}
			
			fetchstatus = 0;
			
			return ERR_NONE;
		}
	}
#endif

#ifdef USE_FETCH_SCROLL
	retcode = SQLFetchScroll(hstmt, SQL_FETCH_PREV, 0);
#endif

#ifdef bla

        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
                _LOG << "lbQuery::previous(): Error while fetching next row" LOG_
                printf("Error in lbQuery::previous()\n");
                dbError( "SQLExtendedFetch()");

		// Unsave !!
		if (retcode == SQL_SUCCESS_WITH_INFO) {
			
			_LOG << "lbQuery::previous() returns with SQL_SUCCESS_WITH_INFO" LOG_
			
			return ERR_NONE;
		}
		
                return ERR_DB_NODATA;
        }

#ifndef USE_FETCH_SCROLL        
	if (RowsFetched == 0) {
		_LOG << "lbQuery::previous() returns with ERR_DB_NODATA" LOG_
		return ERR_DB_NODATA;
	}
#endif
        
	return ERR_NONE;
#endif
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\last\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::last() {
        UWORD   RowStat[20];
        UDWORD  RowsFetched = 0;

        // Indicate, that data must prebound to a buffer
        databound = 0;

	fetchstatus = 1;
        
#ifndef USE_FETCH_SCROLL
        retcode = SQLExtendedFetch(hstmt, SQL_FETCH_LAST, 0, &RowsFetched, RowStat);
#endif

#ifdef USE_FETCH_SCROLL
	retcode = SQLFetchScroll(hstmt, SQL_FETCH_LAST, 0);
#endif

        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
                _LOG << "lbQuery::last(): Error while fetching next row" LOG_
                printf("Error in lbQuery::last()\n");

                dbError( "SQLExtendedFetch()");

		// Unsave !!
		if (retcode == SQL_SUCCESS_WITH_INFO) return ERR_NONE;
		
                return ERR_DB_FETCHLAST;
        }

// Try also here a fetch probe
		retcode = SQLExtendedFetch(hstmt, SQL_FETCH_PREV, 0, &RowsFetched, RowStat);

char buf[100] = "";
		
		if (retcode == SQL_NO_DATA) {
			// Indicate for no data and go back
			printf("No, we don't have more.\n");
			retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, RowStat);
			
			if (retcode == SQL_NO_DATA) {
				_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
				
				fetchstatus = -2;
				
				return ERR_DB_NODATA;
			}
			
			fetchstatus = -1;
			
			return WARN_DB_NODATA;
		} else {
			printf("Yes, we have.\n");
			retcode = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 0, &RowsFetched, RowStat);
			
			if (retcode == SQL_NO_DATA) {
				_LOG << "FATAL ERROR: Resultset indication for no data has been failed!" LOG_
				
				fetchstatus = -2;
				
				return ERR_DB_NODATA;
			}
			
			fetchstatus = 0;
			
			return ERR_NONE;
		}



#ifndef USE_FETCH_SCROLL        
        if (RowsFetched == 0) return ERR_DB_FETCHLAST;
#endif
                      
	return ERR_NONE;
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

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\remove\40\\41\:0:*/
lbErrCodes LB_STDCALL lbQuery::remove() {
UWORD   RowStat[20];
UDWORD  RowsFetched = 0;

	if (mode == 1) return ERR_DB_STILL_ADDING;

	SQLSetPos(hstmt, 1, SQL_DELETE, SQL_LOCK_NO_CHANGE);

/*
	SQLCHAR cursorname[100] = "";
	short l;
	
	SQLGetCursorName(hstmt, cursorname, 99, &l);


	SQLCHAR query[500] = "";
	
	sprintf((char*) query, "update %s set deleted = 1 where CURRENT OF '%s'", getTableName(), cursorname);

	printf("%s\n", query);

	retcode = SQLExecDirect(hstmt, query, SQL_NTS);

	
	if (retcode != SQL_SUCCESS)
	{
	        dbError( "SQLExecDirect()");
	        _LOG << "lbQuery::remove(...) deleting failed." LOG_
	        return ERR_NONE;
	}

	printf("SQLExecDirect() done\n");
*/
	SQLSetPos(hstmt, 1, SQL_REFRESH, SQL_LOCK_NO_CHANGE);
	

//	if (fetchstatus == 1) return previous();
//	return next();

/*
	if (fetchstatus == 0) {
		lbErrCodes err = ERR_NONE;
		err = next();
		if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
			return first();
		}
		return err;
	} else {		
		switch (fetchstatus) {
		
		case 1  : 
			return previous();
		case -1 :
			return next();
		default:
			break;
		}
	}
*/
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbQuery\58\\58\update\40\\41\:0:*/
//#define USE_CURRENT_OF
lbErrCodes LB_STDCALL lbQuery::update() {
	lbErrCodes err = ERR_NONE;
	#define cbMAXSQL    512
	char* CursorName = (char*) malloc(cbMAXSQL);
	CursorName[0] = 0;

	if (mode == 1) {
	
	
		if (ReadOnlyColumns->Count() > 0) {
			_CL_LOG << "Try to unbind readonly columns while adding a row." LOG_
			
			boundColumns->unbindReadonlyColumns();
			
		}
	
		retcode = SQLSetPos(hstmt, 2, SQL_ADD, SQL_LOCK_NO_CHANGE);
		
		if (retcode != SQL_SUCCESS)
		{
		        dbError( "SQLSetPos()");
		        _LOG << "lbQuery::update(...) adding failed." LOG_
		        return ERR_DB_UPDATEFAILED;
		}

		if (ReadOnlyColumns->Count() > 0) {
			_CL_LOG << "Try to rebind readonly columns after adding a row." LOG_
			
			boundColumns->rebindReadonlyColumns();
		}

		mode = 0;
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
			UAP(lb_I_BoundColumn, bc, __FILE__, __LINE__)
			
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
			UAP(lb_I_BoundColumn, bc, __FILE__, __LINE__)
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
		        _dbError( "SQLExecDirect() for update",henv,hdbc,hupdatestmt);
		        _LOG << "lbQuery::update(...) failed." LOG_
		        return ERR_DB_UPDATEFAILED;
		}

free(buffer);

/*...e*/
#endif
#ifndef USE_CURRENT_OF

		retcode = SQLSetPos(hstmt, 1, SQL_UPDATE, SQL_LOCK_NO_CHANGE);
		
		if (retcode != SQL_SUCCESS)
		{
		        dbError( "SQLSetPos()");
		        _LOG << "lbQuery::update(...) updating failed." LOG_
		        return ERR_DB_UPDATEFAILED;
		}
#endif
	}

	free(CursorName);

	return ERR_NONE;
}
/*...e*/
/*...schar\42\ LB_STDCALL lbQuery\58\\58\getTableName\40\\41\:0:*/
#define ISBLANK(x)      ((x) == ' ')
#define ISCOMMA(x)      ((x) == ',')
#define ISNUM(x)        (((x) >= '0') && ((x) <= '9'))
#define ISLPAREN(x)     ((x) == '(')
#define ISRPAREN(x)     ((x) == ')')
#define ISPERIOD(x)     ((x) == '.')
#define ISRETURN(x)     (((x) == '\n') || ((x) == '\r'))
#define ISTAB(x)        ((x) == '\t')
#define ISWHITE(x)      (ISBLANK(x) || ISTAB(x) || ISRETURN(x))


// This possibly causes a crash in wxWidgets sample application
char *lpszTable = NULL;

char* LB_STDCALL lbQuery::getTableName() {
   LPCSTR   lpsz;
   int      cp;
   int      cb;

    if (lpszTable == NULL) {
	lpszTable = (char*) malloc(1000);
    }
    
   lpszTable[0] = 0;

   cb = strlen("from");

   char        g_szQuoteChar[2];      // Identifier quote char

// Get identifier quote character
      SQLGetInfo(hdbc, SQL_IDENTIFIER_QUOTE_CHAR,
                                    g_szQuoteChar, sizeof(g_szQuoteChar), NULL);
         //*g_szQuoteChar = ' ';




   for (lpsz=szSql, cp=0; *lpsz; ) {

      while (*lpsz && ISWHITE(*lpsz)) lpsz++;

      if (!cp && !strncmp(lpsz, "from", cb) && ISWHITE(*(lpsz+cb)))
         break;

      if (ISLPAREN(*lpsz))
         cp++;
      else if (ISRPAREN(*lpsz))
         cp--;

      while (*lpsz && !ISWHITE(*lpsz)) lpsz++;
   }

   while (*lpsz && !ISWHITE(*lpsz)) lpsz++;
   while (*lpsz && ISWHITE(*lpsz))  lpsz++;

// There may be a bug in the last lines and here I have my table...

int i = 0;
while (lpsz[i] != 0 && lpsz[i] != ' ') i++;

if (strlen(lpsz) > 999) {
    lpszTable = (char*) realloc(lpszTable, strlen(lpsz)+1);
    lpszTable[0] = 0;
}

strcpy(lpszTable, lpsz);

char* pos = strstr(lpszTable, "where");

if (pos) pos[0] = 0;


pos = strstr(lpszTable, " order");

if (pos) pos[0] = 0;

pos = strstr(lpszTable, " inner");

if (pos) pos[0] = 0;

int a = 0;
int b = 0;

char* temp;

temp = new char[strlen((char const*) lpszTable)+1];

while (b <= strlen((char const*) lpszTable)) {
        if (lpszTable[b] != '\"') {
                temp[a] = lpszTable[b];
                a++;
                b++;
        } else {
                b++;
        }
}

lpszTable[0] = 0;
strcpy(lpszTable, temp);

delete[] temp;

return lpszTable; //!!!

#ifdef bla
   if (*lpsz == *g_szQuoteChar) {
      *lpszTable++ = *lpsz++; // Copy beginning quote
      while (*lpsz && *lpsz != *g_szQuoteChar) *lpszTable++ = *lpsz++;
      *lpszTable++ = *lpsz++; // Copy ending quote
   }
   else  // Not a quoted identifier
      while (*lpsz && !ISCOMMA(*lpsz) && !ISWHITE(*lpsz)) {
      	printf("%s\n", lpsz);
      	*lpszTable++ = *lpsz++;
      }

printf("Endscan at '%s'\n", lpszTable);

   //*lpszTable = '\0';

   return lpszTable;
#endif
}
/*...e*/

void LB_STDCALL lbQuery::dbError(char* lp)
{
	unsigned char buf[1000];
	unsigned char sqlstate[15];

	SQLError( henv, hdbc, hstmt, sqlstate, NULL, buf, sizeof(buf), NULL);
	fprintf(stderr, "%s. %s, SQLSTATE=%s\n",lp, buf, sqlstate);
}

/*...e*/
/*...sclass lbBoundColumn:0:*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbBoundColumn)
        ADD_INTERFACE(lb_I_BoundColumn)
END_IMPLEMENT_LB_UNKNOWN()

bool LB_STDCALL lbBoundColumn::isNull() {
	return (cbBufferLength == SQL_NULL_DATA);
}
/*...slb_I_Query\58\\58\lbDBColumnTypes LB_STDCALL lbBoundColumn\58\\58\getType\40\\41\:0:*/
lb_I_Query::lbDBColumnTypes LB_STDCALL lbBoundColumn::getType() {
	switch (_DataType) {
	
		case SQL_BIT:
			return lb_I_Query::lbDBColumnBit;
			
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR: 
			return lb_I_Query::lbDBColumnChar;
			
		case SQL_INTEGER: 
			return lb_I_Query::lbDBColumnInteger;
			
		case SQL_BINARY:
			return lb_I_Query::lbDBColumnBinary;
		
		default: return lb_I_Query::lbDBColumnUnknown;
	}

}
/*...e*/
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

	REQUEST(manager.getPtr(), lb_I_String, colName)

	if (column->getColumnName() != NULL) {
		colName->setData(column->getColumnName()->getData());
	}

	leaveOwnership(*&column, this);
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbBoundColumn\58\\58\leaveOwnership\40\lb_I_BoundColumn\42\ oldOwner\44\ lb_I_BoundColumn\42\ newOwner\41\:0:*/
lbErrCodes LB_STDCALL lbBoundColumn::leaveOwnership(lb_I_BoundColumn* oldOwner, lb_I_BoundColumn* newOwner) {

	lbBoundColumn* oO = (lbBoundColumn*) oldOwner;
	lbBoundColumn* nO = (lbBoundColumn*) newOwner;

//	printf("Leave ownership: Buffer pointer is at %p\n", oO->buffer);	

	nO->setData(oO->bound, oO->_DataType, oO->buffer, oO->colName.getPtr());
	oO->bound = 0;
	nO->isUpdateable = oO->isUpdateable;
	if (oO->buffer != NULL) oO->buffer = NULL;

	return ERR_NONE;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbBoundColumn\58\\58\getData\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbBoundColumn::getData() {
	_CL_LOG << "lbBoundColumn::getData(...) not implemented yet" LOG_
	return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbBoundColumn\58\\58\getAsString\40\lb_I_String\42\ result\44\ int asParameter\41\:0:*/
lbErrCodes LB_STDCALL lbBoundColumn::getAsString(lb_I_String* result, int asParameter) {
	
	switch (_DataType) {
	        case SQL_CHAR:
	        case SQL_VARCHAR:
	        case SQL_LONGVARCHAR:
	        	if (asParameter == 1) {
	        		char* b = (char*) malloc(strlen((char const *) buffer)+3);
	        		b[0] = 0;
	        		sprintf(b, "'%s'", buffer);
	        		result->setData(b);
	        		free(b);
	        	} else {
	        		result->setData((char*) buffer);
	        	}
	        	
	        	break;
	        case SQL_BINARY:
	        	_CL_LOG << "lbBoundColumn::getAsString(...) failed: Binary data not supported for column '" << colName->charrep() << "'" LOG_
	        	break;
	        case SQL_INTEGER:
			{
	        		char charrep[100] = "";
	        		sprintf(charrep, "%d", *(long*) buffer);
	        		result->setData(charrep);
			}
	        	break;
	        case SQL_BIT:
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
	        default:
	        	_CL_LOG << "lbBoundColumn::getAsString(...) failed: Unknown or not supported datatype for column '" << colName->charrep() << "'"  LOG_
	        	break;
	}
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbBoundColumn\58\\58\setFromString\40\lb_I_String\42\ set\44\ int mode\41\:0:*/
lbErrCodes LB_STDCALL lbBoundColumn::setFromString(lb_I_String* set, int mode) {

	if (!isUpdateable) {
		_CL_LOG << "Warning: Updating a column '" << colName->charrep() << "' with readonly status skipped." LOG_
		return ERR_NONE;
	}

	if (mode == 1) {
		switch (_DataType) {
			case SQL_CHAR:
			case SQL_VARCHAR:
			case SQL_LONGVARCHAR:
				{
					// Must set an offset for the insert buffer
					
					char* bb = (char*) buffer;
					
					char* b = strcpy(bb + ColumnSize + 1, set->getData());
					cbBufferLength = strlen((char*) buffer);
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
			case SQL_BINARY:
				_CL_LOG << "lbBoundColumn::setFromString(...) failed: Binary data not supported for column '" << colName->charrep() << "'"  LOG_
				break;
			case SQL_BIT:
				{
					bool l = false;
					if (strcmp(set->charrep(), "true") == 0) {
						l = true;
					}
			
					bool* pl = (bool*) buffer;
					
					void* b = pl+1;
					
					memcpy(b, &l, sizeof(l));
				}
				break;
		}

	} else {
		switch (_DataType) {
			case SQL_CHAR:
			case SQL_VARCHAR:
			case SQL_LONGVARCHAR:
				{
					char* b = strcpy((char*) buffer, set->getData());
					cbBufferLength = strlen((char*) buffer);
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
				_CL_LOG << "lbBoundColumn::setFromString(...) failed: Binary data not supported for column '" << colName->charrep() << "'" LOG_
				break;
			case SQL_BIT:
				{
					bool l = false;
					if (strcmp(set->charrep(), "true") == 0) {
						l = true;
					}

					memcpy(buffer, &l, sizeof(l));
				}
				break;
		}

	}

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

	REQUEST(manager.getPtr(), lb_I_String, colName)
	colName->setData((char*) ColumnName);

	return err;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbBoundColumn\58\\58\bindColumn\40\lbQuery\42\ q\44\ int column\44\ bool ro\41\:0:*/
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

	cbBufferLength = 0;
	SQLRETURN ret;

	if (ro) {
		_CL_LOG << "Bind a column that is read only !" LOG_
		cbBufferLength = SQL_COLUMN_IGNORE;
		isUpdateable = false;
	}


	ret = SQLDescribeCol( hstmt, column, ColumnName,
	                                BufferLength, &NameLength, &DataType,
	                                &ColumnSize, &DecimalDigits, &Nullable);

	if (ret != SQL_SUCCESS) {
		printf("Error: Failed to get column description for column %d.\n", column);
		q->dbError("SQLDescribeCol()");
	}

	REQUEST(manager.getPtr(), lb_I_String, colName)
	colName->setData((char*) ColumnName);
	

	switch (DataType) {
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
/*...sbind a character array:24:*/
			buffer = malloc((ColumnSize+1)*rows+20);

			_DataType = DataType;
			bound = 1;			     // Try a spacer for bugfix
			memset(buffer, 0, (ColumnSize+1)*rows+20);

			ret = SQLBindCol(hstmt, column, SQL_C_DEFAULT, buffer, (ColumnSize+1), &cbBufferLength);
			
			if (ret != SQL_SUCCESS) {
				printf("Error while binding a column!\n");
				q->dbError("SQLBindCol()");
			}
/*...e*/
			break;
		case SQL_BINARY:
/*...sbind a binary array:24:*/
			buffer = malloc((ColumnSize+1)*rows+20);

			_DataType = DataType;
			bound = 1;			     // Try a spacer for bugfix
			memset(buffer, 0, (ColumnSize+1)*rows+20);
			
			ret = SQLBindCol(hstmt, column, SQL_C_DEFAULT, buffer, (ColumnSize+1), &cbBufferLength);
			
			if (ret != SQL_SUCCESS) {
				printf("Error while binding a column!\n");
				q->dbError("SQLBindCol()");
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
			SQLBindCol(hstmt, column, DataType, buffer, sizeof(long), &cbBufferLength);
			if (ret != SQL_SUCCESS) {
			        printf("Error while binding a column!\n");
			        q->dbError("SQLBindCol()");
			}
/*...e*/
			break;
		case SQL_BIT:
			buffer = malloc((sizeof(bool))*rows);
			_DataType = DataType;
			bound = 1;
			memset(buffer, 0, sizeof(bool)*rows);
			SQLBindCol(hstmt, column, DataType, buffer, sizeof(bool), &cbBufferLength);
			if (ret != SQL_SUCCESS) {
			        printf("Error while binding a column!\n");
			        q->dbError("SQLBindCol()");
			}
			break;
		default:
			_CL_LOG << "lbBoundColumn::bindColumn(...) failed: Unknown or not supported datatype for column '" << colName->charrep() << "': " << DataType LOG_
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
	SQLRETURN ret;
	if (!isUpdateable) {
		_CL_LOG << "Really unbind column '" << colName->charrep() << "'" LOG_
/*...sUnbind:16:*/
	switch (_DataType) {
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
			_CL_LOG << "Unbind char" LOG_
/*...sbind a character array:40:*/
			bound = 0;

			ret = SQLBindCol(hstmt, _column, SQL_C_DEFAULT, NULL, (ColumnSize+1), &cbBufferLength);
			
			if (ret != SQL_SUCCESS) {
				printf("Error while binding a column!\n");
				query->dbError("SQLBindCol()");
			}
/*...e*/
			break;
		case SQL_BINARY:
			_CL_LOG << "Unbind binary" LOG_
/*...sbind a binary array:40:*/
			bound = 0;
			
			ret = SQLBindCol(hstmt, _column, SQL_C_DEFAULT, NULL, (ColumnSize+1), &cbBufferLength);
			
			if (ret != SQL_SUCCESS) {
				printf("Error while binding a column!\n");
				query->dbError("SQLBindCol()");
			}
/*...e*/
			break;
/*...slater:32:*/
/*			
		case SQL_WCHAR:
		case SQL_WVARCHAR:
		case SQL_WLONGVARCHAR:
			break;
*/			
/*...e*/
		case SQL_INTEGER:
			_CL_LOG << "Unbind integer" LOG_
/*...sbind an integer:40:*/
			bound = 0;

			SQLBindCol(hstmt, _column, _DataType, NULL, sizeof(long), &cbBufferLength);

			if (ret != SQL_SUCCESS) {
			        printf("Error while binding a column!\n");
			        query->dbError("SQLBindCol()");
			}
/*...e*/
			break;
		case SQL_BIT:
			_CL_LOG << "Unbind bit" LOG_
			bound = 0;

			SQLBindCol(hstmt, _column, _DataType, NULL, sizeof(bool), &cbBufferLength);

			if (ret != SQL_SUCCESS) {
			        printf("Error while binding a column!\n");
			        query->dbError("SQLBindCol()");
			}
			break;
		default:
			_CL_LOG << "lbBoundColumn::unbindReadonlyColumns(...) failed: Unknown or not supported datatype for column '" << colName->charrep() << "': " << _DataType LOG_
			break;
	}
/*...e*/
	}
}
/*...e*/
/*...svoid LB_STDCALL lbBoundColumn\58\\58\rebindReadonlyColumns\40\\41\:0:*/
void LB_STDCALL lbBoundColumn::rebindReadonlyColumns() {
	SQLRETURN ret;
	if (!isUpdateable) {
		_CL_LOG << "Really rebind column '" << colName->charrep() << "'" LOG_
/*...sRebind:16:*/
	switch (_DataType) {
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
			_CL_LOG << "Rebind char" LOG_
/*...sbind a character array:40:*/
			bound = 1;

			ret = SQLBindCol(hstmt, _column, SQL_C_DEFAULT, buffer, (ColumnSize+1), &cbBufferLength);
			
			if (ret != SQL_SUCCESS) {
				printf("Error while binding a column!\n");
				query->dbError("SQLBindCol()");
			}
/*...e*/
			break;
		case SQL_BINARY:
			_CL_LOG << "Rebind binary" LOG_
/*...sbind a binary array:40:*/
			bound = 1;
			
			ret = SQLBindCol(hstmt, _column, SQL_C_DEFAULT, buffer, (ColumnSize+1), &cbBufferLength);
			
			if (ret != SQL_SUCCESS) {
				printf("Error while binding a column!\n");
				query->dbError("SQLBindCol()");
			}
/*...e*/
			break;
/*...slater:32:*/
/*			
		case SQL_WCHAR:
		case SQL_WVARCHAR:
		case SQL_WLONGVARCHAR:
			break;
*/			
/*...e*/
		case SQL_INTEGER:
			_CL_LOG << "Rebind integer" LOG_
/*...sbind an integer:40:*/
			bound = 1;

			SQLBindCol(hstmt, _column, _DataType, buffer, sizeof(long), &cbBufferLength);

			if (ret != SQL_SUCCESS) {
			        printf("Error while binding a column!\n");
			        query->dbError("SQLBindCol()");
			}
/*...e*/
			break;
		case SQL_BIT:
			_CL_LOG << "Rebind bit" LOG_
			bound = 1;

			SQLBindCol(hstmt, _column, _DataType, buffer, sizeof(bool), &cbBufferLength);

			if (ret != SQL_SUCCESS) {
			        printf("Error while binding a column!\n");
			        query->dbError("SQLBindCol()");
			}
			break;
		default:
			_CL_LOG << "lbBoundColumn::rebindReadonlyColumns(...) failed: Unknown or not supported datatype for column '" << colName->charrep() << "': " << _DataType LOG_
			break;
	}
/*...e*/
	}
}
/*...e*/
/*...slb_I_String\42\ LB_STDCALL lbBoundColumn\58\\58\getColumnName\40\\41\:0:*/
lb_I_String* LB_STDCALL lbBoundColumn::getColumnName() {
	if (colName.getPtr() == NULL) printf("ERROR lbBoundColumn::getColumnName(): returning a null pointer\n");
	return colName.getPtr();
}
/*...e*/
/*...svoid lbBoundColumn\58\\58\setUpdateable\40\bool updateable\41\:0:*/
void lbBoundColumn::setUpdateable(bool updateable) {
	isUpdateable = updateable;
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
	    
	    if (name) _dbname = strdup(name);
	}
	
	virtual void LB_STDCALL setDBUser(char* name) {
	    if (_dbuser) {
		free(_dbuser);
		_dbuser = NULL;
	    }
	    
	    if (name) _dbuser = strdup(name);
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
	
	UAP(lb_I_Connection, con, __FILE__, __LINE__)
	QI(uk, lb_I_Connection, con, __FILE__, __LINE__)
	
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
	
	static lb_I_Container* connPooling;
};

lb_I_Container* lbDatabase::connPooling = NULL;

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabase)
	ADD_INTERFACE(lb_I_Database)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfDatabase, lbDatabase)

lbDatabase::lbDatabase() {
	ref = STARTREF;
	henv = 0;
	hdbc = 0;
}

lbDatabase::~lbDatabase() {
}

/*...slbErrCodes LB_STDCALL lbDatabase\58\\58\init\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabase::init() {
	retcode = SQLAllocEnv(&henv);
	if (retcode != SQL_SUCCESS) {
        	_dbError( "SQLAllocEnv()",henv,0,0);
        	_LOG << "Database initializion failed." LOG_
        	return ERR_DB_INIT;
        }

	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, 0);

	if (retcode != SQL_SUCCESS) {
        	_dbError( "SQLSetEnvAttr()",henv,0,0);
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
	lbErrCodes err = ERR_NONE;
	
	if (connPooling == NULL) {
	    UAP_REQUEST(manager.getPtr(), lb_I_Container, container)
	    container->queryInterface("lb_I_Container", (void**) &connPooling, __FILE__, __LINE__);
	}

	char* DSN_user = (char*) malloc(strlen(DSN)+1+strlen(user)+1);
	DSN_user[0] = 0;
	
	// Build the key for the connection
	
	strcat(DSN_user, DSN);	
	strcat(DSN_user, "-");
	strcat(DSN_user, user);
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, dsn_user)
	dsn_user->setData(DSN_user);
	
	free(DSN_user);
	
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	
	QI(dsn_user, lb_I_KeyBase, key, __FILE__, __LINE__)
	
	if (connPooling->exists(&key) == 1) {
	    UAP(lb_I_Connection, con, __FILE__, __LINE__)
	    
	    uk = connPooling->getElement(&key);
	    
	    QI(uk, lb_I_Connection, con, __FILE__, __LINE__)
	    
	    if (con != NULL) {
		lbConnection* c = (lbConnection*) con.getPtr();
		
		hdbc = c->getConnection();
	    }
	    	
	} else {
	

	    _CL_VERBOSE << "SQLAllocConnect(henv, &hdbc);" LOG_

	    retcode = SQLAllocConnect(henv, &hdbc); /* Connection handle */

		if (retcode != SQL_SUCCESS)
	        {
    		    _dbError( "SQLAllocConnect()",henv,hdbc,0);
        	    SQLFreeEnv(henv);
        	    return ERR_DB_CONNECT;
    		}	
        
	    lbConnection* c = new lbConnection();
	    
	    c->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
	    c->setConnection(hdbc);

	    QI(c, lb_I_Unknown, uk, __FILE__, __LINE__)
	    
	    connPooling->insert(&uk, &key);
	
	    _CL_VERBOSE << "SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 15);" LOG_
	    retcode = SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 15); /* Set login timeout to 15 seconds. */

            if (retcode != SQL_SUCCESS)
            {
                    _dbError( "SQLSetConnectOption()",henv,hdbc,0);
                    SQLFreeEnv(henv);
                    return ERR_DB_CONNECT;
            }

	    _CL_VERBOSE << "SQLSetConnectAttr(hdbc, SQL_ATTR_ODBC_CURSORS, SQL_CUR_USE_IF_NEEDED, 0);" LOG_

	    retcode = SQLSetConnectAttr(hdbc, SQL_ATTR_ODBC_CURSORS, SQL_CUR_USE_IF_NEEDED, 0);

            if (retcode != SQL_SUCCESS)
            {
	        _dbError( "SQLSetConnectAttr()",henv,hdbc,0);
                SQLFreeEnv(henv);
                return ERR_DB_CONNECT;
	    }

	    _CL_VERBOSE << "SQLConnect(hdbc, '" << DSN << "', '" << user << "');" LOG_

	    retcode = SQLConnect(hdbc, (unsigned char*) DSN, SQL_NTS, 
				       (unsigned char*) user, SQL_NTS, 
				       (unsigned char*) passwd, SQL_NTS); /* Connect to data source */

	    _CL_VERBOSE << "Called." LOG_

	    if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
            {
        	_dbError( "SQLConnect()",henv,hdbc,0);
		_LOG << "Connection to database failed." LOG_
        	SQLFreeEnv(henv);
        	return ERR_DB_CONNECT;
            }

            retcode = SQLSetConnectOption(hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);

	    if (retcode != SQL_SUCCESS)
	    {
	        _dbError( "SQLSetConnectOption(SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON)",henv,hdbc,0);
	        SQLFreeEnv(henv);
	        return ERR_DB_CONNECT;
	    }
        }

	return ERR_NONE;
}
/*...e*/
lb_I_Query* LB_STDCALL lbDatabase::getQuery(int readonly) {
	lbQuery* query = new lbQuery;
	query->setModuleManager(*&manager, __FILE__, __LINE__);

	if (query->init(henv, hdbc, readonly) != ERR_NONE) {
		_LOG << "ERROR: Initializion of query has been failed!" LOG_
		
		//return NULL;
	}

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
        _dbError( "SQLAllocEnv()",henv,hdbc,hstmt);
        return;
        }

retcode = SQLAllocConnect(henv, &hdbc); /* Connection handle */

if (retcode != SQL_SUCCESS)
        {
        _dbError( "SQLAllocConnect()",henv,hdbc,hstmt);
        SQLFreeEnv(henv);
        return;
        }

SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 15); /* Set login timeout to 15 seconds. */
retcode = SQLConnect(hdbc, (unsigned char*) "trainres", SQL_NTS, (unsigned char*) "dba", SQL_NTS, (unsigned char*) "trainres", SQL_NTS); /* Connect to data source */

if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
        {
        _dbError( "SQLConnect()",henv,hdbc,hstmt);
        SQLFreeEnv(henv);
        return;
        } else {
            SQLFreeEnv(henv);
        }


retcode = SQLAllocStmt(hdbc, &hstmt); /* Statement handle */

if (retcode != SQL_SUCCESS)
        {
        _dbError( "SQLAllocStmt()",henv,hdbc,hstmt);
        SQLFreeEnv(henv);
        return;
        }

//lstrcpy( szSql,"select empno,ename,job,mgr,hiredate,sal,nvl(comm,0),deptno from emp order by empno asc");
lstrcpy( szSql,"select ObjectTyp, X, Y, W, H from World order by X, Y");

retcode = SQLExecDirect(hstmt, (unsigned char*) szSql, SQL_NTS);

if (retcode != SQL_SUCCESS)
        {
        _dbError( " SQLExecDirect()",henv,hdbc,hstmt);
        }

if (retcode == SQL_SUCCESS)
        {

        printf("%10s\tX\tY\tW\tH\n", "ObjectType");
        while (true)
                {
                retcode = SQLFetch(hstmt);

                if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
                        {
                        _dbError( "SQLFetch()",henv,hdbc,hstmt);
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
/*...svoid _dbError\40\ LPSTR lp\44\ HENV henv\44\HDBC hdbc\44\HSTMT hstmt\41\:0:*/
void _dbError( LPSTR lp, HENV henv,HDBC hdbc,HSTMT hstmt)
{
unsigned char buf[1000];
unsigned char sqlstate[15];

SQLError( henv, hdbc, hstmt, sqlstate, NULL, buf, sizeof(buf), NULL);
fprintf(stderr, "%s. %s, SQLSTATE=%s\n",lp, buf, sqlstate);
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

	retcode = SQLConnect(hdbc, (unsigned char*) "lbDMFConfig", SQL_NTS, 
				   (unsigned char*) "lbDMF", SQL_NTS, 
				   (unsigned char*) "lbDMF", SQL_NTS); /* Connect to data source */

	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
        {
        	dbError( "SQLConnect()",henv,hdbc,0);
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
	        dbError( "SQLSetConnectOption(SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON)",henv,hdbc,0);
	        SQLFreeEnv(henv);
	        return ERR_DB_CONNECT;
	}
        

#endif



}

lbDBInterfaceRepository::~lbDBInterfaceRepository() {
}

lbErrCodes lbDBInterfaceRepository::setData(lb_I_Unknown* uk) {
        _CL_LOG << "lbDBInterfaceRepository::setData(...) not implemented yet" LOG_
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
					        _CL_LOG << "Error: This node is not of type ELEMENT" LOG_

					        return NULL;
					}

					DOM_Node an_attr = attributeMap.getNamedItem(DOMString("Name"));

					if (an_attr == NULL) {
					        _CL_LOG << "Error: Attribute not found" LOG_

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
					        _CL_LOG << "Error: This node is not of type ELEMENT" LOG_

					        return NULL;
					}

					DOM_Node an_attr = attributeMap.getNamedItem(DOMString("Name"));

					if (an_attr == NULL) {
					        _CL_LOG << "Error: Attribute not found" LOG_

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

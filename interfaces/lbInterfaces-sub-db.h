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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/
/*...e*/
#ifndef __LB_DATABASE__
#define __LB_DATABASE__

//class lb_I_Query;

class lb_I_ColumnBinding;
class lb_I_MVC_View;

/*...sclass lb_I_Query:0:*/
/**
 * \brief A SQL Query interface.
 *
 * This is a basic interface to issue SQL queries. It should provide cursor functionality,
 * because it has first, next, previous and last for navigation in the result of a query.
 */
class lb_I_Query : public lb_I_Unknown
{
protected:
	/**
	 * \deprecated Pure abstract class has no ctor/dtor's
	 */
        lb_I_Query() {}
	/**
	 * \deprecated Pure abstract class has no ctor/dtor's
	 */
        virtual ~lb_I_Query() {}
public:
	/**
	 * \brief Column binding mode.
	 * 
	 * Not clear how the view should get a bound columns instance.
	 */
        virtual lbErrCodes LB_STDCALL setView(lb_I_ColumnBinding* cb) = 0;

/*...svirtual lbErrCodes LB_STDCALL \40\un\41\registerView\40\lb_I_MVC_View\42\ view\41\ \61\ 0\59\:8:*/
	/* MVC View mode */
	/*
	 * As a sample may be a graphical view for the result of the interpreted
	 * graphics and the textual view. The controller then might use one button
	 * for updating the model and the model then informs its views.
	 */
	/**
	 * \brief Register a view to this query instance.
	 *
	 * It is an attempt to enable active updates issued to the views, if other
	 * views have made them.
	 */
	virtual lbErrCodes LB_STDCALL registerView(lb_I_MVC_View* view) = 0;
	
	/**
	 * \brief Unregister a view to this query instance.
	 *
	 * A view would be destroyed. Unregister it prior.
	 */
	virtual lbErrCodes LB_STDCALL unregisterView(lb_I_MVC_View* view) = 0;
/*...e*/

	/** \brief Print the resulting query data to the console. 
	 *
	 */
	virtual void LB_STDCALL PrintData(bool reverse = false) = 0;

	/** \brief Print the current row data to the console. 
	 *
	 */
	virtual void LB_STDCALL PrintCurrent() = 0;

	/** \brief Print out table header.
	 *
	 */
	virtual void LB_STDCALL PrintHeader() = 0;

	/** \brief Print out table footer.
	 *
	 */
	virtual void LB_STDCALL PrintFooter() = 0;

	/** \brief Skip look ahead if there are more rows.
	 *
	 * This deactivates extra look ahead if there are more rows in the
	 * cursor. The GUI sample need this to determine erly state for the
	 * navigation buttons.
	 */
	virtual void LB_STDCALL skipPeeking() = 0;

        /**
         * \brief Set the SQL query.
         *
         * Set the SQL query string to be used.
         */
        virtual lbErrCodes LB_STDCALL query(char* q, bool bind = true) = 0;

	/**
	 * \brief Bind columns, if not yet have bound.
	 *
	 * This function should be used, if query would explicitly called to not
	 * bind the columns. This enables setup some readonly columns, that must
	 * bound differently.
	 */
	virtual lbErrCodes LB_STDCALL bind() = 0;

	/**
	 * \brief Unbind all columns.
	 *
	 * There are some problems with the ODBC driver for PostgreSQL. (At least the 07.03.0200 version)
	 * To avoid crashes in SQLSetPos with SQL_REFRESH when logging is on, this function must be called.
	 */
	virtual void LB_STDCALL unbind() = 0;

	/* Manipulation */
	/**
	 * \brief Begin adding a row.
	 *
	 * Sets a flag, that the data should be positioned at the new row space.
	 * This also should set default values accordingly to the database in behind.
	 *
	 * All further data manipulation is done at this row.
	 *
	 * Any further navigation is skipped until the update function has been called.
	 */
	virtual lbErrCodes LB_STDCALL add() = 0;

	/** \brief Get adding mode.
	 *
	 * Returns 1 if adding is active or 0 if not.
	 */
	virtual int LB_STDCALL isAdding() = 0;
	
	/** \brief Is current row the first.
	 */
	virtual bool LB_STDCALL isFirst() = 0;
	
	/** \brief Is current row the last.
	 */
	virtual bool LB_STDCALL isLast() = 0;
	
	/**
	 * \brief Deletes the current entry.
	 */
	virtual lbErrCodes LB_STDCALL remove() = 0;
	
	/**
	 * \brief Updates the modified data or stores the new data added via add().
	 */
	virtual lbErrCodes LB_STDCALL update() = 0;

	/**
	 * \brief Get column count.
	 */
	virtual int        LB_STDCALL getColumns() = 0;
	
	/**
	 * \brief Check exsistence for column name.
	 *
	 * Returns false, if given column name is not in the query.
	 */
	virtual bool		LB_STDCALL hasColumnName(char* name) = 0;
	
	/**
	 * \brief Get the name of a column.
	 *
	 * The first column is 1. 
	 *
	 * \param col Integer index of the column.
	 */
	virtual lb_I_String*      LB_STDCALL getColumnName(int col) = 0;

	/**
	 * \brief Get the table name of the query.
	 *
	 * This is still buggy, if the query has joins.
	 */
	virtual lb_I_String* LB_STDCALL getTableName(char* columnName = NULL) = 0;

	/**
	 * \brief Skip foreign column informations.
	 *
	 * Disable the collection of foreign keys in an internal list.
	 */
	virtual void LB_STDCALL skipFKCollecting() = 0;

	/**
	 * \brief Enable foreign column informations.
	 *
	 * Enable the collection of foreign keys in an internal list.
	 */
	virtual void LB_STDCALL enableFKCollecting() = 0;



	/**
	 * \brief Determines occurence of foreign column.
	 *
	 * Returns 1 if true. 0 if false.
	 */
	virtual int	LB_STDCALL hasFKColumn(char* FKName) = 0;

	/**
	 * \brief Return number of foreign columns.
	 */
	virtual int	LB_STDCALL getFKColumns() = 0;
	
	/**
	 * \brief Return foreign column at pos.
	 */
	virtual lb_I_String* LB_STDCALL getFKColumn(int pos) = 0;

	/**
	 * \brief Get the foreign key based on given primary table and primary key name.
	 */
	virtual lb_I_String* LB_STDCALL getFKColumn(char* table, char* primary) = 0;

	/**
	 * \brief Get primary table name.
	 *
	 * Returns an lb_I_String instance of the primary table name from the given foreign column name.
	 * 
	 * Returns a NULL pointer, if no primary table name could be found.
	 */
	virtual lb_I_String*	LB_STDCALL getPKTable(char const * FKName) = 0;

	/** \brief Get primary column name.
	 *
	 * A foreign column points to another table's primary column.
	 */
	virtual lb_I_String* 	LB_STDCALL getPKColumn(char const * FKName) = 0;

	/**
	 * \brief Get the count of primary columns.
	 */
	virtual int		LB_STDCALL getPKColumns() = 0;

	/**
	 * \brief Get the primary column at given pos.
	 */
	virtual lb_I_String*	LB_STDCALL getPKColumn(int pos) = 0;

	/**
	 * \brief NULL indicator for pos column.
	 */
	virtual bool	LB_STDCALL isNull(int pos) = 0;

	/**
	 * \brief NULL indicator for named column.
	 */
	virtual bool	LB_STDCALL isNull(char const * name) = 0;

	/**
	 * \brief NULL indicator for pos column.
	 */
	virtual bool	LB_STDCALL isNullable(int pos) = 0;

	/**
	 * \brief NULL indicator for named column.
	 */
	virtual bool	LB_STDCALL isNullable(char const * name) = 0;

	/**
	 * \brief NULL indicator for pos column.
	 */
	virtual bool	LB_STDCALL setNull(int pos, bool b = true) = 0;

	/**
	 * \brief NULL indicator for named column.
	 */
	virtual bool	LB_STDCALL setNull(char const * name, bool b = true) = 0;
	
	/**
	 * \brief Returns false if query is not in any valid cursor position.
	 */	
	virtual bool	LB_STDCALL dataFetched() = 0;

	/**
	 * \brief Supported column types
	 */
	enum lbDBColumnTypes {
		lbDBColumnBit,
		lbDBColumnChar,
		lbDBColumnInteger,
		lbDBColumnBigInteger,
		lbDBColumnBinary,
		lbDBColumnDate,
		lbDBColumnFloat,
		lbDBColumnUnknown
	};

	/**
	 * \brief Gets the type of the column.
	 *
	 */
	virtual lbDBColumnTypes	   LB_STDCALL getColumnType(int pos) = 0;

	/**
	 * \brief Gets the type of the column.
	 *
	 */
	virtual lbDBColumnTypes	   LB_STDCALL getColumnType(char* name) = 0;


	enum lbDBCaseSensity {
		lbDBCaseLower,
		lbDBCaseUpper,
		lbDBCaseMixed,
		lbDBCaseSensibility
	};

	virtual lbDBCaseSensity    LB_STDCALL getCaseSensity() = 0;

	/** \brief Set updateability of column.
	 *
	 * Set the column 'column' to be updateable or not.
	 */
	virtual void		   LB_STDCALL setReadonly(char* column, bool updateable = true) = 0;

	/** \brief Get updateability of column.
	 *
	 * Get the updateability of column 'column'.
	 */
	virtual bool		   LB_STDCALL getReadonly(char* column) = 0;


        /* Navigation */

	/** \brief Get integer based position.
	 *
	 * The position is internally used to reposition the cursor to a prior
	 * position after the function reopen has recreated the statement.
	 *
	 * Currently remove makes use of reopen.
	 *
	 * First row starts with 1.
	 */
	virtual int		LB_STDCALL getPosition() = 0;

	/** \brief Position the cursor to an absolute position.
	 *
	 * First row starts with 1.
	 */
	virtual lbErrCodes	LB_STDCALL absolute(int pos) = 0;
        
	/**
	 * \brief Move to first row.
	 *
	 * Sets the cursor position to the first of the result set.
	 */        
        virtual lbErrCodes LB_STDCALL first() = 0;

	/**
	 * \brief Move to next row.
	 *
	 * Sets the cursor position to the next of the result set.
	 *
	 * Return:
	 *
	 *	WARN_DB_NODATA if only one more row will be present.
	 *	ERR_DB_NODATA if no more data is available.
	 */        
        virtual lbErrCodes LB_STDCALL next() = 0;

	/**
	 * \brief Move to previous row.
	 *
	 * Sets the cursor position to the previous of the result set.
	 */        
        virtual lbErrCodes LB_STDCALL previous() = 0;

	/**
	 * \brief Move to last row.
	 *
	 * Sets the cursor position to the last  of the result set.
	 */        
        virtual lbErrCodes LB_STDCALL last() = 0;

	/**
	 * \brief Enables refreshing resultset.
	 */
	virtual void	LB_STDCALL reopen() = 0;

	virtual void	LB_STDCALL close() = 0;
	virtual void	LB_STDCALL open() = 0;

	/** \brief Build new SQL query with where clause.
	 *
	 * This function copies the result into a new buffer. You have to free() it.
	 */
	virtual char* LB_STDCALL setWhereClause(const char* query, char* where) = 0;
	
	/** \brief Add to an existing where clause.
	 *
	 * This function copies the result into a new buffer. You have to free() it.
	 */
	 
	virtual char* LB_STDCALL addWhereClause(const char* query, char* where) = 0;
		
	/** \brief Set autorefresh on update.
	 *
	 */
	virtual void LB_STDCALL setAutoRefresh(bool b) = 0;
    /* Accessors */
#ifdef UNBOUND        
	/**
	 * \brief Get the column data as char*
	 */
        virtual char* LB_STDCALL getChar(int column) = 0;
#endif
#ifndef UNBOUND

	/**
	 * \brief Get the column data as lb_I_String* instance.
	 * 
	 * Builds a lb_I_String instance and fills in the data of the bound column.
	 */
        virtual lb_I_String*    LB_STDCALL getAsString(int column) = 0;

        virtual lb_I_String*    LB_STDCALL getAsString(const char* column) = 0;
        
        /**
         * \brief Set string to column.
         *
         * Modifies the column at the current row or sets the column for the new row data.
         *
         * \param columnName Name of the column.
         * \param value Value as a string.
         */
        virtual lbErrCodes	LB_STDCALL setString(lb_I_String* columnName, lb_I_String* value) = 0;
		
		/**
		 * \brief Get the column data as lb_I_Integer* instance.
		 * 
		 * Builds a lb_I_Integer instance and fills in the data of the bound column.
		 * The database column must be of valit integer type. 
		 */
		virtual lb_I_Long* LB_STDCALL getAsLong(int column) = 0;
		
		/** \brief Get BLOB data.
		 */
		virtual lb_I_BinaryData* LB_STDCALL getBinaryData(int column) = 0;
		
		/** \brief Get BLOB data.
		 */
		virtual lb_I_BinaryData* LB_STDCALL getBinaryData(const char* column) = 0;

		/** \brief Set BLOB data.
		 */
		virtual lbErrCodes LB_STDCALL setBinaryData(int column, lb_I_BinaryData* value) = 0;
		
		/** \brief Get BLOB data.
		 */
		virtual lbErrCodes LB_STDCALL setBinaryData(const char* column, lb_I_BinaryData* value) = 0;
#endif
};
/*...e*/
/*...sclass lb_I_BoundColumn:0:*/
/**
 * \brief A single bound column, such as a text field on a form
 *
 * A bounf column contains one entity of a database column.
 */
class lb_I_BoundColumn : public lb_I_Unknown
{
protected:
	/**
	 * \deprecated Pure abstract class has no ctor/dtor's
	 */
        lb_I_BoundColumn() {}

        /**
         * \deprecated Pure abstract class has no ctor/dtor's
         */
        virtual ~lb_I_BoundColumn() {}
public:

	/**
	 * \brief Indicates NULL data in the column.
	 */
	virtual bool LB_STDCALL isNullable() = 0;
	
	/**
	 * \brief Indicates NULL data in the column.
	 */
	virtual bool LB_STDCALL isNull() = 0;
	
	/**
	 * \brief Set NULL data in the column.
	 */
	virtual bool LB_STDCALL setNull(bool b) = 0;

	/**
	 * \brief A binary column is not bound.
	 */
	virtual bool LB_STDCALL isBound() = 0;
	
	/**
	 * \brief Type of the column.
	 */
	virtual lb_I_Query::lbDBColumnTypes LB_STDCALL getType() = 0;

	/**
	 * \brief Set the column updateability.
	 */
	virtual void		LB_STDCALL setReadonly(bool updateable) = 0;

	/**
	 * \brief Get the column updateability.
	 */
	virtual bool		LB_STDCALL getReadonly() = 0;

/*...sdoc:8:*/
	/**
	 * \brief Universal access to the column.
	 *
	 * This function creates an instance of an interface regarding to the
	 * underlying data type. For example:
	 * 
	 * DATETIME creates a lb_I_Datetime instance (to be implemented),
	 * CHAR(n)  creates a lb_I_String instance,
	 * VARCHAR  creates a lb_I_String instance
	 * and so on...
	 *
	 * The user of this class library knows about its datatypes for a query.
	 * Therefore he can expect that interfaces.
	 *
	 * If the application is an interacive query tool, then it should be the
	 * same. But it should additionally contain a general representation
	 * interface - like a lb_I_String.
	 *
	 * The setData is still defined in the base class - to be implemented here.
	 */
/*...e*/
	virtual lb_I_Unknown* LB_STDCALL getData() = 0;
	
	/**
	 * \brief Get the data formatted as string.
	 *
	 * \param result Result must be an instance of lb_I_String to be filled.
	 * \param asParameter Don't know why here a parameter should be possible.
	 */
	virtual lbErrCodes LB_STDCALL getAsString(lb_I_String* result, int asParameter = 0) = 0;
	
	/**
	 * \brief Get a long column.
	 *
	 * \param result Result must be an instance of lb_I_Long to be filled.
	 * \param asParameter Don't know why here a parameter should be possible.
	 */
	virtual lbErrCodes LB_STDCALL getAsLong(lb_I_Long* result, int asParameter = 0) = 0;
	
	/**
	 * \brief Set the data from a string.
	 *
	 * This sets the column value to the content of string set.
	 *
	 * \param set Set the value of this string into the column.
	 * \param mode ??
	 */	
	virtual lbErrCodes LB_STDCALL setFromString(lb_I_String* set, int mode) = 0;

	/**
	 * \brief Get the column name.
	 */
	virtual lb_I_String* LB_STDCALL getColumnName() = 0;

	virtual char* LB_STDCALL getColumnName_c_str() = 0;
	
	/**
	 * \brief Preparation for column binding.
	 *
	 * This should be protected and only visible to the lb_I_BoundColumns interface.
	 */
	virtual lbErrCodes   LB_STDCALL prepareBoundColumn(lb_I_Query* q, int column) = 0;
	
	/**
	 * \brief Finish binding of a column.
	 *
	 * Bind a column from the query to this instance.
	 *
	 * \param q The query.
	 * \param column The number of the column to bind.
	 */
	virtual lbErrCodes	LB_STDCALL bindColumn(lb_I_Query* q, int column, bool ro) = 0;

	virtual void		LB_STDCALL bindNullColumn() = 0;

	virtual void		LB_STDCALL unbindReadonlyColumns() = 0;	
	
	virtual void		LB_STDCALL rebindReadonlyColumns() = 0;	

	/**
	 * \brief Rebind column.
	 */
	virtual void LB_STDCALL rebind() = 0;
	virtual void LB_STDCALL unbind() = 0;

	virtual void LB_STDCALL add() = 0;
	virtual void LB_STDCALL finishadd() = 0;


	/** \brief Returns true when data has been provided or column is set to NULL.
	 */
	virtual bool LB_STDCALL hasValidData() = 0;

	/** \brief Invalidates all data.
	 * This function is used indirectly on lbQuery::add() to mark data as invalid.
	 * You have to either set a value or call setNull per column. 
	 */
	virtual void	LB_STDCALL invalidateData() = 0;

protected:
	/**
	 * This function will be used in setData to take the ownership of the internal
	 * data to the given instance.
	 *
	 * This is needed to store the instance in a container. Due to the container's
	 * call of clone, the new instance in the container must have the same data, not
	 * a copy. In this case a bound column has an allocated memory area, that must not
	 * be copied. Instead the clone must get ownership of the cloned instance data.
	 *
	 * This means, the cloned memory pointer must be set to NULL and must not be deleted.
	 * The clone get's the pointer to the memory area.
	 */
	virtual lbErrCodes LB_STDCALL leaveOwnership(lb_I_BoundColumn* oldOwner, lb_I_BoundColumn* newOwner) = 0;

/*...s:0:*/
#ifdef bla	
	virtual lbErrCodes LB_STDCALL bindColumn(
	SQLSMALLINT	stmt,
	SQLCHAR		column,
	SQLSMALLINT	name,
	SQLSMALLINT	length,
	SQLSMALLINT
	SQLUINTEGER
	SQLSMALLINT
	SQLSMALLINT

hstmt, 
i, 
ColumnName,
BufferLength, 
&NameLength, 
&DataType,
&ColumnSize, 
&DecimalDigits, 
&Nullable

#endif
/*...e*/


};
/*...e*/
/*...sclass lb_I_ColumnBinding:0:*/
/**
 * \brief Bound columns interface. It holds all bound columns.
 *
 * This interface is an attempt to providing column binding
 * informations for the query. As I saw, when the column binding is done
 * twice, the documentation says, that this is not possible with an
 * SQLExtendetFetch. The documentation also calls this rebinding.
 * For this, I can not use column binding to update more than one view.
 * 
 * It is then better to use a MVC View approach and let the view get its
 * data needed. 
 */
class lb_I_ColumnBinding : public lb_I_Unknown
{
protected:
	/**
	 * \deprecated Pure abstract class has no ctor/dtor's
	 */
        lb_I_ColumnBinding() {}
	/**
	 * \deprecated Pure abstract class has no ctor/dtor's
	 */
        virtual ~lb_I_ColumnBinding() {}
public:
        /* Get bound columns. If the ColumnBinding instance does not
         * bind all colums of a query, it would provide dummies.
         */
         
        /**
         * \brief Get a list of bound columns.
         *
         * This is not implemented yet.
         */ 
        virtual lb_I_Container* LB_STDCALL getBoundColumns() = 0;
        
        /**
         * \brief Set a list of bound columns.
         *
         * This is not implemented yet.
         */
        virtual lbErrCodes      LB_STDCALL setBoundColumns(lb_I_Container* bc) = 0;

	/**
	 * \brief Get the bound column.
	 *
	 * \param column Index of the column
	 */
	virtual lb_I_BoundColumn* LB_STDCALL getBoundColumn(int column) = 0;

	/**
	 * \brief Indicate those columns having NULL values.
	 */
	virtual void LB_STDCALL indicateNullValues() = 0;
	
	/**
	 * \brief Set a specific column to be NULL.
	 */
	virtual bool LB_STDCALL setNull(int pos, bool b) = 0;

	/**
	 * \brief NULL indicator for pos column.
	 */
	virtual bool LB_STDCALL isNullable(int pos) = 0;

	/**
	 * \brief NULL indicator for named column.
	 */
	virtual bool LB_STDCALL isNullable(char const * name) = 0;

	/**
	 * \brief NULL indicator for pos column.
	 */
	virtual bool LB_STDCALL isNull(int pos) = 0;

	/**
	 * \brief NULL indicator for named column.
	 */
	virtual bool LB_STDCALL isNull(char const * name) = 0;

	/**
	 * \brief NULL indicator for named column.
	 */
	virtual bool LB_STDCALL setNull(char const * name, bool b) = 0;

	/**
	 * \brief Unbind readonly columns.
	 */
	virtual void LB_STDCALL unbindReadonlyColumns() = 0;

	/**
	 * \brief Rebind readonly columns.
	 */
	virtual void LB_STDCALL rebindReadonlyColumns() = 0;

	/** 
	 * \brief Rebind all columns.
	 */
	virtual void LB_STDCALL rebind() = 0;
	virtual void LB_STDCALL unbind() = 0;

	virtual bool LB_STDCALL isBound(int pos) = 0;
	virtual bool LB_STDCALL isBound(char const * name) = 0;

	virtual void LB_STDCALL add() = 0;
	virtual void LB_STDCALL finishadd() = 0;

	/**
	 * \brief Get the type of a column.
	 */
	virtual lb_I_Query::lbDBColumnTypes  LB_STDCALL getColumnType(int pos) = 0;

	/**
	 * \brief Get the type of a column.
	 */
	virtual lb_I_Query::lbDBColumnTypes  LB_STDCALL getColumnType(char* name) = 0;

	/**
	 * \brief Get the index of the bound column.
	 */
	virtual int             LB_STDCALL getColumnIndex(const char* name) = 0;

	/**
	 * \brief Set the column updateability.
	 */
	virtual void		LB_STDCALL setReadonly(char* column, bool updateable) = 0;

	/**
	 * \brief Get the column updateability.
	 */
	virtual bool		LB_STDCALL getReadonly(char* column) = 0;
	
	/**
	 * \brief Get the amound of columns.
	 *
	 * This returns the currently bound columns based on the SQL query.
	 */
	virtual int               LB_STDCALL getColumnCount() = 0;

	/**
	 * \brief Get the column as string representation.
	 *
	 * Returns index column as a string.
	 *
	 * \param column Index of the column.
	 * \param instance String instance to be filled with the value.
	 */
        virtual lbErrCodes      LB_STDCALL getString(int column, lb_I_String* instance) = 0;
        
	/**
	 * \brief Get the column as string representation.
	 *
	 * Returns index column as a string.
	 *
	 * \param column Index of the column.
	 * \param instance String instance to be filled with the value.
	 */
        virtual lbErrCodes      LB_STDCALL getLong(int column, lb_I_Long* instance) = 0;
        
	/**
	 * \brief Get the column as string representation.
	 *
	 * Returns index column as a string.
	 *
	 * \param column Name of the column.
	 * \param instance String instance to be filled with the value.
	 */
        virtual lbErrCodes      LB_STDCALL getString(const char* column, lb_I_String* instance) = 0;
        
	/**
	 * \brief Set the column as string representation.
	 *
	 * Sets column as a string.
	 *
	 * \param column Name of the column.
	 * \param instance String instance with the value to be set.
	 */
	virtual lbErrCodes      LB_STDCALL setString(char* column, lb_I_String* instance) = 0;        

#ifdef bla
        /**
         * Set a currently used query to bind their columns.
         */
//        virtual lbErrCodes      LB_STDCALL setQuery(lb_I_Query* q) = 0;
#endif

	virtual lbErrCodes		LB_STDCALL setQuery(lb_I_Query* q, lb_I_Container* ReadonlyColumns) = 0;

	/**
	 * \brief Indicator, if the current column is an adding column.
	 *
	 * Returns 1 if adding mode is active. Otherwise it returns 0.
	 */
	virtual int		LB_STDCALL getMode() = 0;
	
	/** \brief Returns true if all columns have valid data.
	 */
	virtual bool	LB_STDCALL hasValidData() = 0;
	
	/** \brief Invalidates all data.
	 * This function is used on lbQuery::add() to mark data as invalid.
	 * You have to either set a value or call setNull per column. 
	 */
	virtual void	LB_STDCALL invalidateData() = 0;
};
/*...e*/
/*...sclass lb_I_MVC_View:0:*/
class lb_I_MVC_View : public lb_I_Unknown
{
protected:
	lb_I_MVC_View() {}
	virtual ~lb_I_MVC_View() {}
public:
/*...svirtual lbErrCodes LB_STDCALL updateView\40\\41\ \61\ 0\59\:8:*/
        /*------ MVC variant ------------*/
        /* Data is available, I can read it out ... */
        virtual lbErrCodes LB_STDCALL updateView() = 0;
/*...e*/
        
/*...svirtual lbErrCodes LB_STDCALL setViewSource\40\lb_I_Unknown\42\ q\41\ \61\ 0\59\:8:*/
        /* The view source is the data, that should be displayed.
         * As this would be a database view, the function tries to get
         * a lb_I_Query source.
         */
        virtual lbErrCodes LB_STDCALL setViewSource(lb_I_Unknown* q) = 0;
/*...e*/
};
/*...e*/

/*...sclass lb_I_Connection:0:*/
/**
 * \brief This is the storage for one connection per db name and user name.
 */
class lb_I_Connection : public lb_I_Unknown
{
public:

	/**
	 * \brief Get the name of the db connection.
	 */
	virtual char* LB_STDCALL getDBName() = 0;

	/**
	 * \brief Get the user of the db connection.
	 */
	virtual char* LB_STDCALL getDBUser() = 0;
};
/*...e*/

/*...sclass lb_I_Database:0:*/
/**
 * \brief The main class for operating with databases.
 *
 * This interface is used as the main access interface for operating with
 * databases.
 */
class lb_I_Database : public lb_I_Unknown
{
protected:
	/**
	 * \deprecated Pure abstract class has no ctor/dtor's
	 */
	lb_I_Database() {}
	/**
	 * \deprecated Pure abstract class has no ctor/dtor's
	 */
	virtual ~lb_I_Database() {}
public:
	/**
	 * \brief Initializion of the database backend.
	 */
	virtual lbErrCodes	LB_STDCALL init() = 0;
	virtual void	LB_STDCALL close() = 0;
	virtual void	LB_STDCALL open(char* connectionname) = 0;

	virtual lbErrCodes	LB_STDCALL setUser(char* _user) = 0;
	virtual lbErrCodes	LB_STDCALL setDB(char* _db) = 0;

	/** \brief Determine connection status.
	 *
	 */
	virtual bool		LB_STDCALL isConnected() = 0;

	/**
	 * \brief Connect to the database.
	 *
	 * This function connects to the database and in this first state of
	 * development makes the test against this database.
	 * For this test, you should have created an ODBC datasource to
	 * a postgreSQL database named trainres. User is dba, password is
	 * trainres and the table is as the following definition:
	 *
	 * \param DSN Data source name - usually the name in the ODBC configuration.
	 * \param user User to connect as.
	 * \param passwd The passord. 
	 */
	virtual lbErrCodes LB_STDCALL connect(char* connectionname, char* DSN, char* user, char* passwd) = 0;

	virtual lbErrCodes LB_STDCALL connect(char* connectionname, char* pass) = 0;

	/**
	 * \brief Get a query instance.
	 *
	 * Creates a query instance and returns it. You get the ownership and must destroy it
	 * if no longer in use.
	 *
	 * \param readonly Set 0 to have write access. Default is readonly.
	 */	
	virtual lb_I_Query* LB_STDCALL getQuery(char* connectionname, int readonly = 1) = 0;
	
	virtual lb_I_Container* LB_STDCALL getTables(char* connectionname) = 0;
	virtual lb_I_Container* LB_STDCALL getColumns(char* connectionname) = 0;

	virtual lb_I_Container* LB_STDCALL getForeignKeys(char* connectionname) = 0;
	virtual lb_I_Container* LB_STDCALL getPrimaryKeys(char* connectionname) = 0;
};
/*...e*/
/*...sclass lb_I_DatabaseForm:0:*/
class lb_I_MasterDetailFormDefinition;

/**
 * \brief An attempt for a database form interface.
 */
class lb_I_DatabaseForm : 
	public lb_I_Form
	{
public:
	/** \brief Set the query object.
	 *
	 * A database form needs a query object, from whom it should
	 * show the data.
	 */
	virtual void LB_STDCALL init(char* SQLString, char* DBName, char* DBUser, char* DBPass) = 0;

	/**
	 * \brief Get the used SQL query.
	 *
	 * This function is used to compare the in used query with the query, that should be used (from the database).
	 * Using this avoids additional usage of a container for it and enables recreation of a changed form at runtime.
	 */
	virtual char* LB_STDCALL getQuery() = 0;
	
	/** \brief Set a filter for the form.
	 *
	 * Setup a filter to be used in the form. The filter must specify a typical where clause or
	 * a part of it. To reset the filter, you need a call to this function without a parameter.
	 *
	 * Sample to show only data for one customer: kdnummer = 100001
	 */
	virtual void LB_STDCALL setFilter(char* filter = NULL) = 0;

	/** \brief Get the table name based on column name.
	 *
	 * Return the related table name, that contains the given column name.
	 */
	virtual lb_I_String* LB_STDCALL getTableName(char* columnName) = 0;

/*...sMaster Detail form interface part:8:*/
	/** \brief Get the number of master columns.
	 *
	 * Needed to access the column name.
	 */
	virtual int LB_STDCALL getPrimaryColumns() = 0;

	/** \brief Get the number of foreign columns related to given primary tables.
	 *
	 * Needed to access the column name.
	 */
	virtual int LB_STDCALL getForeignColumns(char* primaryTable = NULL) = 0;

	/** \brief Get the primary column at position pos.
	 *
	 * Warning: You must cleanup.
	 */
	virtual lb_I_String* LB_STDCALL getPrimaryColumn(int pos) = 0;

	/** \brief Get the foreign column at position pos.
	 *
	 * Warning: You must cleanup.
	 */
	virtual lb_I_String* LB_STDCALL getForeignColumn(int pos) = 0;

	/** \brief Return if the control is of type char.
	 *
	 */
	virtual bool LB_STDCALL isCharacterColumn(char* name) = 0;

	/** \brief Get the value of a control.
	 *
	 */
	virtual const char* LB_STDCALL getControlValue(char* name) = 0;

	/** \brief Get the value of a control.
	 *
	 */
	virtual const char* LB_STDCALL getControlValue(int pos) = 0;

	/** \brief Get the number of controls.
	 *
	 * Return the number of controls in the form. This includes all
	 * controls.
	 */
	virtual int LB_STDCALL getControls() = 0;

	/** \brief Set a master formular for this one.
	 *
	 * This let's you define a master form that, if the user select's another entry in the master form, the
	 * detail form -  eg. this one - would reopen the query based on the new master - detail relation ship.
	 * 
	 */
	virtual void LB_STDCALL setMasterForm(lb_I_DatabaseForm* master, lb_I_Parameter* params) = 0;

	virtual void LB_STDCALL setDetailForm(lb_I_DatabaseForm* detail, lb_I_Parameter* params) = 0;

	/** \brief Update the clientforms.
	 *
	 * This function would be called for all client forms, contained by a master form.
	 */
	virtual void LB_STDCALL updateFromMaster() = 0;

	virtual void LB_STDCALL updateFromDetail() = 0;

	/**
	 * \brief Do not include foreign keys into the layout.
	 */
	virtual void LB_STDCALL ignoreForeignKeys(char* toTable) = 0;

	virtual lb_I_String* LB_STDCALL getColumnName(int pos) = 0;
	
	/** \brief Reopen the form.
	 * Used in SQL actions to ensure valid data (after deletion of some data for sample).
	 */
	virtual void LB_STDCALL reopen() = 0;
/*...e*/
};
/*...e*/
/**
 * \brief An attempt for a fixed database form interface.
 */
class lb_I_FixedDatabaseForm : 
	public lb_I_Form
	{
public:
	/** \brief Initialize the form.
	 *
	 */
	virtual void LB_STDCALL init() = 0;

	/**
	 * \brief Get the used SQL query.
	 *
	 * This function is used to compare the in used query with the query, that should be used (from the database).
	 * Using this avoids additional usage of a container for it and enables recreation of a changed form at runtime.
	 */
	virtual char* LB_STDCALL getQuery() = 0;
	
	/** \brief Set a filter for the form.
	 *
	 * Setup a filter to be used in the form. The filter must specify a typical where clause or
	 * a part of it. To reset the filter, you need a call to this function without a parameter.
	 *
	 * Sample to show only data for one customer: kdnummer = 100001
	 */
	virtual void LB_STDCALL setFilter(char* filter = NULL) = 0;

	/** \brief Get the table name based on column name.
	 *
	 * Return the related table name, that contains the given column name.
	 */
	virtual lb_I_String* LB_STDCALL getTableName(char* columnName) = 0;

/*...sMaster Detail form interface part:8:*/
	/** \brief Get the number of master columns.
	 *
	 * Needed to access the column name.
	 */
	virtual int LB_STDCALL getPrimaryColumns() = 0;

	/** \brief Get the number of foreign columns related to given primary tables.
	 *
	 * Needed to access the column name.
	 */
	virtual int LB_STDCALL getForeignColumns(char* primaryTable = NULL) = 0;

	/** \brief Get the primary column at position pos.
	 *
	 * Warning: You must cleanup.
	 */
	virtual lb_I_String* LB_STDCALL getPrimaryColumn(int pos) = 0;

	/** \brief Get the foreign column at position pos.
	 *
	 * Warning: You must cleanup.
	 */
	virtual lb_I_String* LB_STDCALL getForeignColumn(int pos) = 0;

	/** \brief Return if the control is of type char.
	 *
	 */
	virtual bool LB_STDCALL isCharacterColumn(char* name) = 0;

	/** \brief Get the value of a control.
	 *
	 */
	virtual const lb_I_String* LB_STDCALL getControlValue(char* name) = 0;

	/** \brief Get the value of a control.
	 *
	 */
	virtual const lb_I_String* LB_STDCALL getControlValue(int pos) = 0;

	/** \brief Get the number of controls.
	 *
	 * Return the number of controls in the form. This includes all
	 * controls.
	 */
	virtual int LB_STDCALL getControls() = 0;

	virtual lb_I_String* LB_STDCALL getColumnName(int pos) = 0;
/*...e*/
};

class lb_I_DBReportTextblock : public lb_I_Unknown {
	virtual void LB_STDCALL getPosition(long& x, long& y, long& w, long& h) = 0;
	virtual void LB_STDCALL setPosition(long x, long y, long w, long h) = 0;

	virtual void LB_STDCALL addLine(long line, const char* text) = 0;
	virtual bool LB_STDCALL hasMoreLines() = 0;
	virtual lb_I_String* LB_STDCALL getNextLine() = 0;
};

class lb_I_DBReportProperties : public lb_I_Unknown {
	/** \brief Add a named parameter.
	 */
	virtual lbErrCodes LB_STDCALL addParameter(const char* name, const char* value) = 0;

	/** \brief Add a text block element.
	 */
	virtual lbErrCodes LB_STDCALL addTextBlock(lb_I_DBReportTextblock* tb) = 0;

	/** \brief Get the number of parameters.
	 */
	virtual long		LB_STDCALL getParameterCount() = 0;
	
	/** \brief Begin or indicate end of iteration.
	 */
	virtual bool		LB_STDCALL hasMoreParameters() = 0;

	/** \brief Iterate to next parameter.
	 */
	virtual void		LB_STDCALL setNextParameter() = 0;

	/** \brief Stop iteration.
	 */
	virtual void		LB_STDCALL finishParameterIteration() = 0;

	lb_I_String* getParameterByName(const char* name);
	lb_I_String* getParameterName();
	lb_I_String* getParameterValue();
};

/*...sclass lb_I_DatabaseReport:0:*/
/**
 * \brief An attempt for a report based on database queries.
 *
 * Based on the wxReportWriter project from http://www.daily.de/RepWrt/,
 * this is an adaption to my framework.
 */
class lb_I_DatabaseReport :
	public lb_I_Unknown
{
public:
	/** \brief Set the report data.
	 *
	 * A database report needs a query object, from whom it should
	 * report the data.
	 */
	virtual void LB_STDCALL init(char* SQLString, char* DBName, char* DBUser, char* DBPass) = 0;

	/** \brief Add a where clause and condition.
	 *
	 * This function is used to preset where clause conditions. The name/value pair
	 * would be added to a list of 'ANDed' condition rules. 
	 */
	virtual void LB_STDCALL addAndCondition(char* column, char* value) = 0;
	
	/** \brief Add a where clause or condition.
	 *
	 * This function is used to preset where clause conditions. The name/value pair
	 * would be added to a list of 'ORed' condition rules. 
	 */
	virtual void LB_STDCALL addOrCondition(char* column, char* value) = 0;
	
	/** \brief Begin a bracket condition block.
	 *
	 * Use this function to set a list of conditions in a bracket.
	 */
	virtual void LB_STDCALL beginBracket() = 0;
	
	/** \brief End a bracket condition block.
	 *
	 * Use this function to end a list of conditions in a bracket.
	 */
	virtual void LB_STDCALL endBracket() = 0;
	
	/** \brief Set the parent window for the report.
	 *
	 */
	virtual void LB_STDCALL setFrame(lb_I_Unknown* _frame) = 0;
	
	/** \brief Update the data for the report.
	 *
	 * The instance should reread the data from the data source.
	 *
	 * There may be different datasources. 
	 * 
	 * On the one hand, it would be a SQL query, given by the init function.
	 *
	 * On the other hand, it may be a row of a current result set. May be from
	 * a database form.
	 *
	 * Both may have sub reports, depending of it's configuration.
	 */
	virtual void LB_STDCALL update() = 0;

	/**
	 * \brief Show the preview of the report.
	 */	
	virtual void LB_STDCALL show() = 0;

	/**
	 * \brief Destroy the preview of the report.
	 */
	virtual void LB_STDCALL destroy() = 0;
	
	/**
	 * \brief Print the report.
	 */
	virtual void LB_STDCALL print() = 0;
	
	/**
	 * \brief Set the name for the report.
	 */
	virtual lbErrCodes LB_STDCALL setName(char const * name, char const * appention = NULL) = 0;
	
	/** \brief Add a replacer item.
	 * A replacer item is a name surrounding with brackets ({}). This enables text templates
	 * that could be customized by data from database.
	 */
	virtual lbErrCodes LB_STDCALL addReplacer(const char* name, const char* value) = 0;
};
/*...e*/

/*...sclass lb_I_MasterDetailFormDefinition:0:*/
/**
 * \brief Definition of a master to detail relation.
 */
class lb_I_MasterDetailFormDefinition :
	public lb_I_Unknown
	{
public:	

	/** \brief Set the master form.
	 *
	 * The master form will be needed to determine the primary key control that a master form should have in it's
	 * related tables, that are given in the 'SQLString' for the init function of the master form.
	 *
	 * This means, if the master has changed it's data in any way, it will inform it's detail forms about the change.
	 * In this case each detail form performs the following steps to update it's own data:
	 *
	 * 1)	Saves changed data.
	 * 2)	Get the data for each primary column, that stays in relation to the detail view.
	 * 3)	Rebuild the where clause.
	 * 4)	Unbinds all columns.
	 * 5)	Opens a new query.
	 */
	virtual void LB_STDCALL setMasterForm(lb_I_DatabaseForm* master) = 0;
	
	/** \brief Adds a new column as a master.
	 *
	 * This could be used multiple times. It depends on how many columns may relate to the detail.
	 */
	virtual void LB_STDCALL addMasterColumn(char* column) = 0;
	
	/** \brief Get the number of master columns.
	 *
	 * Needed to access the column name.
	 */
	virtual int LB_STDCALL getMasterColumns() = 0;

	/** \brief Get the column at position pos.
	 *
	 * Warning: You must cleanup.
	 */
	virtual lb_I_String* LB_STDCALL getMasterColumn(int pos) = 0;

	/** \brief Get the master form.
	 */
	virtual lb_I_DatabaseForm* LB_STDCALL getMasterForm() = 0;
	
	virtual void LB_STDCALL setCharacterColumn(int pos, bool is = true) = 0;
	
	virtual bool LB_STDCALL isCharacterColumn(int pos) = 0;
};
/*...e*/


#endif // __LB_DATABASE__

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

	/**
	 * \brief Error message printing.
	 */
	virtual void LB_STDCALL dbError(char* lp) = 0;

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
	 * \brief Get the name of a column.
	 *
	 * \param col Integer index of the column.
	 */
	virtual char*      LB_STDCALL getColumnName(int col) = 0;

	/**
	 * \brief Get the table name of the query.
	 *
	 * This is still buggy, if the query has joins.
	 */
	virtual char* LB_STDCALL getTableName() = 0;


	/**
	 * \brief Skip foreign column informations.
	 *
	 * This disables the collecting of foreign keys. There are some problems on
	 * my test system (Windows 2000 / german). My development system is english
	 * and works !
	 *
	 * The implementation under linux has problems, if SQLForeignColumns is used. There
	 * an alternative implementation is used.
	 *
	 * WARNING: The affecting variable is static and affects all instances of this class.
	 */

	virtual void LB_STDCALL skipFKCollecting() = 0;

	/**
	 * \brief Enable foreign column informations.
	 *
	 * This enables the collecting of foreign keys. There are some problems on
	 * my test system (Windows 2000 / german). My development system is english
	 * and works !
	 *
	 * The implementation under linux has problems, if SQLForeignColumns is used. There
	 * an alternative implementation is used.
	 *
	 * WARNING: The affecting variable is static and affects all instances of this class.
	 */

	virtual void LB_STDCALL enableFKCollecting() = 0;



	/**
	 * \brief Determines occurence of foreign column.
	 *
	 * Returns 1 if true. 0 if false.
	 */
	virtual int	LB_STDCALL hasFKColumn(char* FKName) = 0;

	/**
	 * \brief Get primary table name.
	 *
	 * Returns an lb_I_String instance of the primary table name from the given foreign column name.
	 * 
	 * Returns a NULL pointer, if no primary table name could be found.
	 */
	virtual lb_I_String*	LB_STDCALL getPKTable(char const * FKName) = 0;



	/**
	 * \brief NULL indicator for pos column.
	 */
	virtual bool	LB_STDCALL isNull(int pos) = 0;

	/**
	 * \brief Supported column types
	 */
	enum lbDBColumnTypes {
		lbDBColumnBit,
		lbDBColumnChar,
		lbDBColumnInteger,
		lbDBColumnBinary,
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


	/** \brief Set updateability of column.
	 *
	 * Set the column 'column' to be updateable or not.
	 */
	virtual void		   LB_STDCALL setUpdateable(char* column, bool updateable = false) = 0;

        /* Navigation */
        
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
        
        /**
         * \brief Set string to column.
         *
         * Modifies the column at the current row or sets the column for the new row data.
         *
         * \param columnName Name of the column.
         * \param value Value as a string.
         */
        virtual lbErrCodes	LB_STDCALL setString(lb_I_String* columnName, lb_I_String* value) = 0;
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
	virtual bool LB_STDCALL isNull() = 0;
	
	/**
	 * \brief Type of the column.
	 */
	virtual lb_I_Query::lbDBColumnTypes LB_STDCALL getType() = 0;

	/**
	 * \brief Set the column updateability.
	 */
	virtual void                        LB_STDCALL setUpdateable(bool updateable) = 0;

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
	virtual lbErrCodes   LB_STDCALL bindColumn(lb_I_Query* q, int column, bool ro) = 0;

	virtual void	     LB_STDCALL unbindReadonlyColumns() = 0;	
	
	virtual void	     LB_STDCALL rebindReadonlyColumns() = 0;	

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
	 * \brief NULL indicator for pos column.
	 */
	virtual bool LB_STDCALL isNull(int pos) = 0;

	/**
	 * \brief Unbind readonly columns.
	 */

	virtual void LB_STDCALL unbindReadonlyColumns() = 0;

	/**
	 * \brief Rebind readonly columns.
	 */

	virtual void LB_STDCALL rebindReadonlyColumns() = 0;

	/**
	 * \brief Get the type of a column.
	 */
	virtual lb_I_Query::lbDBColumnTypes  LB_STDCALL getColumnType(int pos) = 0;

	/**
	 * \brief Get the type of a column.
	 */
	virtual lb_I_Query::lbDBColumnTypes  LB_STDCALL getColumnType(char* name) = 0;

	/**
	 * \brief Set the column updateability.
	 */
	virtual void 			     LB_STDCALL setUpdateable(char* column, bool updateable) = 0;
	
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
	 * \param column Name of the column.
	 * \param instance String instance to be filled with the value.
	 */
        virtual lbErrCodes      LB_STDCALL getString(char* column, lb_I_String* instance) = 0;
        
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
	virtual lbErrCodes LB_STDCALL init() = 0;

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
	virtual lbErrCodes LB_STDCALL connect(char* DSN, char* user, char* passwd) = 0;

	/**
	 * \brief Get a query instance.
	 *
	 * Creates a query instance and returns it. You get the ownership and must destroy it
	 * if no longer in use.
	 *
	 * \param readonly Set 0 to have write access. Default is readonly.
	 */	
	virtual lb_I_Query* LB_STDCALL getQuery(int readonly = 1) = 0;
	
	
};
/*...e*/
/*...sclass lb_I_DatabaseForm:0:*/
/**
 * \brief An attempt for a database form interface.
 */
class lb_I_DatabaseForm : 
	public lb_I_Form
	{
public:
	/**
	 * \brief Set the query object.
	 *
	 * A database form needs a query object, from whom it should
	 * show the data.
	 */
	virtual void LB_STDCALL init(char* SQLString, char* DBName, char* DBUser, char* DBPass) = 0;
	
};
/*...e*/
#endif // __LB_DATABASE__

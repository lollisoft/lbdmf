#ifndef __LB_DATABASE__
#define __LB_DATABASE__

class lb_I_Query;

/*...sclass lb_I_BoundColumn:0:*/
/*
 * A single bound column, such as a text field on a form
 */
class lb_I_BoundColumn : public lb_I_Unknown
{
protected:
        lb_I_BoundColumn() {}
        virtual ~lb_I_BoundColumn() {}
public:

/*...sdoc:8:*/
	/**
	 * Universal access to the column.
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
	 * Generic string representatoin - regardless of data type.
	 *
	 * Warning: There may be a limit of string nength.
	 */
	virtual lbErrCodes LB_STDCALL getAsString(lb_I_String* result) = 0;
	virtual lbErrCodes LB_STDCALL setFromString(lb_I_String* set, int mode) = 0;

	virtual lb_I_String* LB_STDCALL getColumnName() = 0;
	

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
/*
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
        lb_I_ColumnBinding() {}
        virtual ~lb_I_ColumnBinding() {}
public:
        /* Get bound columns. If the ColumnBinding instance does not
         * bind all colums of a query, it would provide dummies.
         */
        virtual lb_I_Container* LB_STDCALL getBoundColumns() = 0;
        virtual lbErrCodes      LB_STDCALL setBoundColumns(lb_I_Container* bc) = 0;

        virtual lbErrCodes      LB_STDCALL getString(int column, lb_I_String* instance) = 0;
        virtual lbErrCodes      LB_STDCALL getString(char* column, lb_I_String* instance) = 0;
	virtual lbErrCodes      LB_STDCALL setString(char* column, lb_I_String* instance) = 0;        
        /**
         * Set a currently used query to bind their columns.
         */
//        virtual lbErrCodes      LB_STDCALL setQuery(lb_I_Query* q) = 0;


	/**
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
/*...sclass lb_I_Query:0:*/
class lb_I_Query : public lb_I_Unknown
{
protected:
        lb_I_Query() {}
        virtual ~lb_I_Query() {}
public:
	/* Column binding mode */
        virtual lbErrCodes LB_STDCALL setView(lb_I_ColumnBinding* cb) = 0;

/*...svirtual lbErrCodes LB_STDCALL \40\un\41\registerView\40\lb_I_MVC_View\42\ view\41\ \61\ 0\59\:8:*/
	/* MVC View mode */
	/*
	 * As a sample may be a graphical view for the result of the interpreted
	 * graphics and the textual view. The controller then might use one button
	 * for updating the model and the model then informs its views.
	 */
	virtual lbErrCodes LB_STDCALL registerView(lb_I_MVC_View* view) = 0;
	virtual lbErrCodes LB_STDCALL unregisterView(lb_I_MVC_View* view) = 0;
/*...e*/

        /* Set the SQL query */
        virtual lbErrCodes LB_STDCALL query(char* q) = 0;


	/* Manipulation */
	/**
	 * Sets a flag, that the data should be positioned at the new row space.
	 * This also should set default values accordingly to the database in behind.
	 *
	 * All further data manipulation is done at this row.
	 *
	 * Any further navigation is skipped until the update function has been called.
	 */
	virtual lbErrCodes LB_STDCALL add() = 0;
	
	/**
	 * Deletes the current entry.
	 */
	virtual lbErrCodes LB_STDCALL remove() = 0;
	
	/**
	 * Updates the modified data or stores the new data added via add().
	 */
	virtual lbErrCodes LB_STDCALL update() = 0;
        
        /* Navigation */
        virtual lbErrCodes LB_STDCALL first() = 0;
        virtual lbErrCodes LB_STDCALL next() = 0;
        virtual lbErrCodes LB_STDCALL previous() = 0;
        virtual lbErrCodes LB_STDCALL last() = 0;
        
        /* Accessors */
#ifdef UNBOUND        
        virtual char* LB_STDCALL getChar(int column) = 0;
#endif
#ifndef UNBOUND
        virtual lb_I_String*    LB_STDCALL getAsString(int column) = 0;
        
        /**
         * Modifies the column at the current row or sets the column for the new row data 
         */
        virtual lbErrCodes	LB_STDCALL setString(lb_I_String* columnName, lb_I_String* value) = 0;
#endif
};
/*...e*/
/*...sclass lb_I_Database:0:*/
class lb_I_Database : public lb_I_Unknown
{
protected:
	lb_I_Database() {}
	virtual ~lb_I_Database() {}
public:
	virtual lbErrCodes LB_STDCALL init() = 0;
	/**
	 * This function connects to the database and in this first state of
	 * development makes the test against this database.
	 * For this test, you should have created an ODBC datasource to
	 * a postgreSQL database named trainres. User is dba, password is
	 * trainres and the table is as the following definition:
	 */
	virtual lbErrCodes LB_STDCALL connect(char* DSN, char* user, char* passwd) = 0;

	/**
	 * Get a query instance to be used against the connection.
	 * The parameter readonly is per default set to 1 to indicate
	 * a readonly query. To change data in that query, you must
	 * call the function with a 0 value as parameter.
	 */	
	virtual lb_I_Query* LB_STDCALL getQuery(int readonly = 1) = 0;
	
	
};
/*...e*/
#endif // __LB_DATABASE__

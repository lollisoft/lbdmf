#ifndef __LB_DATABASE__
#define __LB_DATABASE__

class lb_I_Query;

/*
 * A single bound column, such as a text field on a form
 */
class lb_I_BoundColumn : public lb_I_Unknown
{
protected:
        lb_I_BoundColumn() {}
        virtual ~lb_I_BoundColumn() {}
public:
	virtual char* getDataType() = 0;
};

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
};

class lb_I_MVC_DBView : public lb_I_Unknown
{
protected:
	lb_I_MVC_DBView() {}
	virtual ~lb_I_MVC_DBView() {}
public:
        /*------ MVC variant ------------*/
        /* Data is available, I can read it out ... */
        virtual lbErrCodes LB_STDCALL dataAvailable() = 0;
        virtual lbErrCodes LB_STDCALL setQueryInstance(lb_I_Query* q) = 0;
};


class lb_I_Query : public lb_I_Unknown
{
protected:
        lb_I_Query() {}
        virtual ~lb_I_Query() {}
public:
	/* Column binding mode */
        virtual lbErrCodes LB_STDCALL setView(lb_I_ColumnBinding* cb) = 0;

	/* MVC View mode */
	/*
	 * As a sample may be a graphical view for the result of the interpreted
	 * graphics and the textual view. The controller then might use one button
	 * for updating the model and the model then informs its views.
	 */
	virtual lbErrCodes LB_STDCALL registerView(lb_I_MVC_DBView* view) = 0;
	virtual lbErrCodes LB_STDCALL unregisterView(lb_I_MVC_DBView* view) = 0;



        /* Set the SQL query */
        virtual lbErrCodes LB_STDCALL query(char* q) = 0;
        /* Navigation */
        virtual lbErrCodes LB_STDCALL first() = 0;
        virtual lbErrCodes LB_STDCALL next() = 0;
        virtual lbErrCodes LB_STDCALL previous() = 0;
        virtual lbErrCodes LB_STDCALL last() = 0;
};

class lb_I_Database : public lb_I_Unknown
{
protected:
	lb_I_Database() {}
	virtual ~lb_I_Database() {}
public:
	/**
	 * This function connects to the database and in this first state of
	 * development makes the test against this database.
	 * For this test, you should have created an ODBC datasource to
	 * a postgreSQL database named trainres. User is dba, password is
	 * trainres and the table is as the following definition:
	 */
	virtual lbErrCodes LB_STDCALL connect(char* DSN, char* user, char* passwd) = 0;
	
	virtual lb_I_Query* LB_STDCALL getQuery() = 0;
	
	
};
#endif // __LB_DATABASE__

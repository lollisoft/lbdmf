#ifndef __LB_DATABASE__
#define __LB_DATABASE__

class lb_I_Query : public lb_I_Unknown
{
	lb_I_Query() {}
	virtual ~lb_I_Query() {}
	
	virtual lbErrCodes LB_STDCALL query(char* q) = 0;
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
	
	virtual lb_I_Query LB_STDCALL getQuery() = 0;
	
	
};
#endif // __LB_DATABASE__

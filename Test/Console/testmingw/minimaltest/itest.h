// Description of test and sample output.
// 
// The code demonstrates a problem returning values of type enum.
// The problem appears when MINGW tries to use a Open Watcom DLL.
// The problem only appears when the DLL is loaded dynamically.
// 
// Q:\develop\Projects\CPP\Test\Console\testmingw\minimaltest>testow
// Hello from test DLL. Text is 'From text.exe'.
// Instance of Test created.
// Hello from test DLL. Text is 'From object out of test.exe'.
// Hello from test DLL. Text is 'p2'.
// Have true.
// Success: ITest->getInt() returns 1
// Test::release() called.
// Instance of Test deleted.
// Test MINGW DLL.
// Loading testdllmingw DLL dynamically from Open Watcom EXE:
// Instance of Test created.
// Success: ITest->getInt() returns 1
// Test if value is not NULL.
// Test if value is not NULL.
// Success: ITest->getInt() returns 1
// Test OW DLL.
// Loading testdllow DLL dynamically from Open Watcom EXE:
// Test instance from OW DLL created via gettestow.
// Test instance from OW DLL created via _gettestow.
// OW Instance of Test created.
// Success: ITest->getInt() returns 1
// Test if value is not NULL.
// Test if value is not NULL.
// Success: ITest->getInt() returns 1
//
// Q:\develop\Projects\CPP\Test\Console\testmingw\minimaltest>testmingw
// Hello from test DLL. Text is 'From text.exe'.
// Instance of Test created.
// Hello from test DLL. Text is 'From object out of test.exe'.
// Hello from test DLL. Text is 'p2'.
// Have true.
// Success: ITest->getInt() returns 1
// Test::release() called.
// Instance of Test deleted.
// Test MINGW DLL.
// Loading testdllmingw DLL dynamically from MINGW32 EXE:
// Instance of Test created.
// Success: ITest->getInt() returns 1
// Test if value is not NULL.
// Test if value is not NULL.
// Success: ITest->getInt() returns 1
// Test OW DLL.
// Loading testdllow DLL dynamically from MINGW32 EXE:
// Test instance from OW DLL created via gettestow.
// Test instance from OW DLL created via _gettestow.
// OW Instance of Test created.
// Error: ITest->getInt() doesn't return 1
// Test if value is not NULL.
// Test if value is not NULL.
// Success: ITest->getInt() returns 1

#define API __stdcall
//#define API __cdecl

enum lbErrCodes {
	ERR_NONE = 0,
	ERR_FAIL = 1,
	ERR_SOWISO = 2,
	ERR_LAST = 0x7FFFFFFF
};

class lb_I_Unknown;
class ITest;

// Test the registration of a member function callback
typedef lbErrCodes (API ITest::*lbEvHandler)(lb_I_Unknown* uk);

class lb_I_Unknown {
public:
	virtual lbErrCodes	API		queryInterface(char const* name, void** unknown) = 0;
	virtual int			API		getBase() = 0;
	virtual int			API		getBase1() = 0;
private:
	lb_I_Unknown* operator=(const lb_I_Unknown* rhs);
};

class ITest : public lb_I_Unknown {
public:
	virtual lbErrCodes	API		getInt(char* _int, bool showmsg) = 0;
	virtual int			API		IntegerSize() = 0;
	virtual bool		API		getbool() = 0;
	virtual void		API		test(char* text, char* p2) = 0;
	virtual void		API		release() = 0;
	virtual lbErrCodes	API		registerHandler(ITest* instance, lbEvHandler handler, char* name) = 0;
	virtual lbErrCodes	API		registerHandler(ITest* instance, lbEvHandler handler, int number) = 0;
	virtual lbErrCodes	API		Foo(int param1, int param2, int param3) = 0;
};

#include "../MiniCppUnit/MiniCppUnit.hxx"

//#define NO_CONSOLE_LOG

#include <lbConfigHook.h>

#ifdef bla
/*...sCleanup helper:0:*/
#ifdef WINDOWS
class cleanUp {
public:
	cleanUp() {
	}
	
	virtual ~cleanUp() {
		unHookAll();
	}
	
};

cleanUp clean_up;
#endif
#ifdef OSX
class cleanUp {
public:
	cleanUp() {
	}
	
	virtual ~cleanUp() {
		_CL_LOG << "Call unHookAll()..." LOG_
		//lbBreak();
		unHookAll();
		_CL_LOG << "Called unHookAll()." LOG_
	}
	
};

cleanUp clean_up;
#endif
/*...e*/
#endif

int main()
{
	int result = 0;
	{
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

		PM->initialize();

		result = theInstance().runTests() ? 0 : -1;

        theInstance().unregisterTests();

		PM->unload();
	}

	unHookAll();

	return result;
}

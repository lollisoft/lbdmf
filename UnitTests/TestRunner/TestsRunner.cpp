#include "../MiniCppUnit/MiniCppUnit.hxx"

#define NO_CONSOLE_LOG

#include <lbConfigHook.h>

int main()
{
	int result = 0;
	
	{
		lb_I_Module* m = getModuleInstance();
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		
		PM->initialize();
		
		result = TestFixtureFactory::theInstance().runTests() ? 0 : -1;
		
		PM->unload();
		
	}
	
	unHookAll();
	
	return result;
}	

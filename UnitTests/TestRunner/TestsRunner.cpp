#include "../MiniCppUnit/MiniCppUnit.hxx"

//#define NO_CONSOLE_LOG

#include <lbConfigHook.h>

int main()
{
	int result = 0;
	{
		lb_I_Module* m = getModuleInstance();
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		
		PM->initialize();
		
		result = theInstance().runTests() ? 0 : -1;

		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		
		meta->uninitialize();
		
		lbUnloadModule("DatabaseLayerGateway.so");
		lbUnloadModule("DatabaseLayerGateway.so");
		
		PM->unload();
	}

	unHookAll();
	
	return result;
}	

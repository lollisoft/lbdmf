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

        printf("Unregister meta application.\n");
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		meta->uninitialize();

        printf("Unregister unit tests.\n");
        theInstance().unregisterTests();

        printf("Unload plugins.\n");
		PM->unload();
	}


    setVerbose(true);
	unHookAll();
    setVerbose(false);


	return result;
}

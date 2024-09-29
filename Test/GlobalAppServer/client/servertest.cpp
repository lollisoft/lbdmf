#include <lbConfigHook.h>
//#include <lbinclude.h>
#include <conio.h>
#include <signal.h>

#include <IApplicationBus.h>
//#include <ApplicationBus/ApplicationBusProxy.h>

void handler(int sig) {
	COUT << "Oops..." << ENDL;
	exit(0);
}

/*...smain:0:*/
int main(int argc, char** argv) {
	int count = 0;
	

	/**
	 * This let the app not crashing. But the handler simply
	 * does exit(0), no cleanup yet ???
	 */
	signal(SIGINT, handler);

	signal(SIGILL, handler);

		char* LOGGING = getenv("LOGGING");

		// Default
		setLogActivated(false);
		if (LOGGING != NULL) {
			if ((strcmp(LOGGING, "no") != 0) && (strcmp(LOGGING, "NO") != 0) && (strcmp(LOGGING, "No") != 0) && (strcmp(LOGGING, "nO") != 0)) 
			// Activate
				setLogActivated(true);
			else
				setLogActivated(false);
		}

		if (argc > 1 && strcmp(argv[1], "-log") == 0) {
			setLogActivated(true);
		}
	
	UAP_REQUEST(getModuleInstance(), lb_I_ApplicationBus, client)
	
	if (client != NULL) {
		char buf[100] = "";
		
		_CL_LOG << "Application bus instantiated." LOG_
		
		while (count++ < 1) {
			UAP(lb_I_String, backend)
			char* text = "Hallo Server, dies ist eine Echo - Message";
			client->Echo(text);
			
			_CL_LOG << "Echo result is: " << text LOG_
			
			
			backend = client->findBackend("lbDMFManager");
			
			
			_CL_LOG << "Backend is " << backend->charrep() LOG_
			
		}
	} else {
		_CL_LOG << "Error: Can't find application bus." LOG_
	}
	
	_CL_LOG << "Ending server test thread" LOG_
	exit(0);
	return 0;
}
/*...e*/

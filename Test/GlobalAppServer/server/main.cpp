#include <lbConfigHook.h>

#include <lbinclude.h>
#include <conio.h>
#include <signal.h>

void handler(int sig) {
	COUT << "Oops..." << ENDL;
	exit(0);
}

/*...smain:0:*/
int main(int argc, char** argv) {
	UAP_REQUEST(getModuleInstance(), lb_I_ApplicationServer, appServer)
	setLogActivated(true);
	_CL_LOG << "Global application server is starting..." LOG_
	setLogActivated(false);

	/**
	 * This let the app not crashing. But the handler simply
	 * does exit(0), no cleanup yet ???
	 */
	//signal(SIGINT, handler);

	//signal(SIGILL, handler);

 	if (appServer != NULL) {
		appServer->run();
	} else {
		printf("Global application server not found...\n");
	}
	printf("Global application server is ending...\n");
	return 0;
}
/*...e*/

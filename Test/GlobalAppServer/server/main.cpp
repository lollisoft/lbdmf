#include <lbConfigHook.h>

#include <lbinclude.h>
#include <conio.h>
#include <signal.h>

void handler(int sig) {
	cout << "Oops..." << endl;
	exit(0);
}

/*...smain:0:*/
int main(int argc, char** argv) {
	printf("Global application server is starting...\n");

	/**
	 * This let the app not crashing. But the handler simply
	 * does exit(0), no cleanup yet ???
	 */
	signal(SIGINT, handler);

	signal(SIGILL, handler);

	UAP_REQUEST(getModuleInstance(), lb_I_ApplicationServer, appServer)
 	if (appServer != NULL) {
		appServer->run();
	} else {
		printf("Global application server not found...\n");
	}
	printf("Global application server is ending...\n");
	getch();
	return 0;
}
/*...e*/

#include <lbConfigHook.h>
#include <lbinclude.h>
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
	//setLogActivated(true);

	/**
	 * This let the app not crashing. But the handler simply
	 * does exit(0), no cleanup yet ???
	 */
	signal(SIGINT, handler);

	signal(SIGILL, handler);

	UAP_REQUEST(getModuleInstance(), lb_I_ApplicationBus, client)
	if (client != NULL) {
		char buf[100] = "";
		_LOG << "Application bus instantiated." LOG_
		while (count++ < 1) {
			char* text = "Hallo, dies ist eine Echo - Message";
			client->Echo(text);
		}
	} else {
		_CL_LOG << "Error: Can't find application bus." LOG_
	}
	
	_CL_LOG << "Ending server test thread" LOG_
	exit(0);
	return 0;
}
/*...e*/

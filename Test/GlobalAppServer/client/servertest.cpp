#include <lbinclude.h>
#include <conio.h>
#include <signal.h>

void handler(int sig) {
	cout << "Oops..." << endl;
	exit(0);
}

/*...smain:0:*/
void main(int argc, char** argv) {
LOGPREFIX("ServerTest: ");
	int count = 0;

	/**
	 * This let the app not crashing. But the handler simply
	 * does exit(0), no cleanup yet ???
	 */
	signal(SIGINT, handler);


	LOG("-------------- Testing Server---------------");
	lbAppBusClient client;
	LOG("------- Must be connected to Server --------");
	
	//cout << "Begin tesing Anounce user in 1 sec..." << endl;
	//lb_sleep(1000);


	char buf[100] = "";
	
	while (count++ < 3) {
	LOG("--------------- Anounce user ---------------");
		client.Echo("Hallo, dies ist eine Echo - Message");
	LOG("--------------- User anounced --------------");
	}
	
	cout << "Ending server test thread" << endl;
	getch();
	exit(0);
}
/*...e*/

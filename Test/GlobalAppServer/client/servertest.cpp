#include <lbinclude.h>
#include <conio.h>

/*...smain:0:*/
void main(int argc, char** argv) {
LOGPREFIX("ServerTest: ");
	int count = 0;
	LOG("-------------- Testing Server---------------");
	lbAppBusClient client;
	LOG("------- Must be connected to Server --------");
	cout << "Begin tesing Anounce user in 1 sec..." << endl;
	lb_sleep(1000);


	char buf[100] = "";
	
	while (count++ < 3) {
	LOG("--------------- Anounce user ---------------");
		client.Echo("Hallo, dies ist eine Echo - Message");
	LOG("--------------- User anounced --------------");
	}
	
	cout << "Ending server test thread" << endl;
	getch();
}
/*...e*/

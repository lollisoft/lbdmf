#include <lbinclude.h>
#include <conio.h>
#include <signal.h>

#ifdef bla
/*...sclass GlobalAppServer:0:*/

/**
 * Per request invoked
 */
/*...sGlobalAppServer\58\\58\_request\40\char \42\servicetyp\44\ request\44\ result\41\:0:*/
int GlobalAppServer::_request(char *servicetyp, 
                              lb_Transfer_Data request, 
                              lb_Transfer_Data & result) {
LOGENABLE("GlobalAppServer::_request()");
LOG("GlobalAppServer::_request(): Handle a request");
	// Handle the request
	int count = request.getPacketCount();

	char buf[100];
/*...sVERBOSE:0:*/
#ifdef NOVERBOSE
	sprintf(buf, "GlobalAppServer::_request(): Packetcount = %d", count);
	printf("%s\n", buf);
	LOG(buf);
#endif		
/*...e*/

	request.resetPositionCount();
		
	while (count--) {
		LB_PACKET_TYPE type;
		int i = 0;
		char *buffer;
		char msg[100];
		request.getPacketType(type);

		switch (type) {
			case LB_CHAR:
				request.get(buffer);

/*...sVERBOSE:32:*/
				#ifdef NOVERBOSE
				printf("Char value = %s\n", buffer); 
				sprintf(msg, "Char value = %s", buffer); 
				LOG(msg);
				#endif
/*...e*/
				
				if (strcmp(buffer, "login") == 0) {
					int res = login(request, result);
					
					if (res == 1) 
						isLoggedIn = TRUE;
					else
						isLoggedIn = FALSE;
						
					return res;
				}
				
				if (strcmp(buffer, "logout") == 0) {
					int res = logout(request, result);
					
					isLoggedIn = FALSE;
					
					return res;
				}
				
				if (isLoggedIn == TRUE) 
					return handleAuthRequest(request, result);

				break;
				
			default:
				printf("Unknown packet type!\n"); 
				LOG("Unknown packet type!"); 
				break;
		}
			
		request.incrementPosition();
	}
	LOG("GlobalAppServer::_request(): Request handled");
	return 1;                              
}
/*...e*/

/**
 * Per run invoked
 */
/*...sGlobalAppServer\58\\58\_service\40\\41\:0:*/
int GlobalAppServer::_service() {
	LOG("GlobalAppServer::_service() called");

	int exit = 0;
	
	while (exit <= 1) {
		LOG("GlobalAppServer::_service(): Waiting for a request");
		printf("GlobalAppServer::_service(): Waiting for a request\n");
		
		lb_Transfer_Data request;
		lb_Transfer_Data result;
		
		waitForRequest(request);
/*...sVERBOSE:0:*/
#ifdef NOVERBOSE
LOG("GlobalAppServer::_service(): Got a request, handle it");
#endif
/*...e*/
		// Check request for service type
		handleRequest("GlobalAppServer", request, result);

		answerRequest(result);

		exit++;
		printf("GlobalAppServer::_service(): Got a request\n");
/*...sVERBOSE:0:*/
#ifdef NOVERBOSE
		LOG("GlobalAppServer::_service(): Got a request");
#endif
/*...e*/
	}	
	
	return 0;
}
/*...e*/
/*...e*/
#endif

/*...sclass GASThread:0:*/
class GASThread : public lbThread {
public:
	GASThread();
	
	virtual ~GASThread();
	
protected:
	void* Entry();
};

/*...sGASThread\58\\58\GASThread\40\\41\:0:*/
GASThread::GASThread() {
}
/*...e*/

/*...sGASThread\58\\58\\126\GASThread\40\\41\:0:*/
GASThread::~GASThread() {
}
/*...e*/

/*...svoid\42\ GASThread\58\\58\Entry\40\\41\:0:*/
void* GASThread::Entry() {

	for (int i=0; i<5; i++) {
		printf("GASThread::Entry - Loop at %d\n", i);
		Beep(200, 50);
		lb_sleep(1000);
	}

	int count = 0;
	LOG("-------------- Testing Server---------------");
	lbAppBusClient client;
	LOG("------- Must be connected to Server --------");
	cout << "Begin tesing Anounce user in 1 sec..." << endl;
	lb_sleep(1000);
	while (count++ < 100) {
	LOG("--------------- Anounce user ---------------");
		client.AnounceUser("lothar", "wuff");
	LOG("--------------- User anounced --------------");
	}
	
	cout << "Ending server test thread" << endl;
	getch();
	return NULL;
}
/*...e*/
/*...e*/

void handler(int sig) {
	cout << "Oops..." << endl;
	exit(0);
}

/*...smain:0:*/
void main(int argc, char** argv) {
LOGPREFIX("GlobalAppServer: ");

	printf("Global application server is starting...\n");

	/**
	 * This let the app not crashing. But the handler simply
	 * does exit(0), no cleanup yet ???
	 */
	signal(SIGINT, handler);

/*
	if (TRUE) {	
		GASThread *thread = new GASThread;
		
		thread->create();
		thread->run();
	}
*/
	lbAppBusServer server;
 	server.run();
	printf("Global application server is ending...\n");
	getch();
}
/*...e*/

#include <lbinclude.h>
#include <conio.h>

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
#ifdef VERBOSE
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
				#ifdef VERBOSE
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
#ifdef VERBOSE
LOG("GlobalAppServer::_service(): Got a request, handle it");
#endif
/*...e*/
		// Check request for service type
		handleRequest("GlobalAppServer", request, result);

		answerRequest(result);

		exit++;
		printf("GlobalAppServer::_service(): Got a request\n");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
		LOG("GlobalAppServer::_service(): Got a request");
#endif
/*...e*/
	}	
	
	return 0;
}
/*...e*/
/*...e*/

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
	GlobalAppServer server;
	
	server.run();

	for (int i=0; i<5; i++) {
		printf("GASThread::Entry - Loop at %d\n", i);
		Beep(200, 50);
		lb_sleep(1000);
	}
	return NULL;
}
/*...e*/
/*...e*/
#endif
/*...smain:0:*/
void main(int argc, char** argv) {
LOGPREFIX("GlobalAppServer");
	printf("Global application server is starting...\n");

/*...sBla:0:*/
#ifdef bla
	GASThread *thread;
	thread = new GASThread();
	
	lbThreadError err = thread->create();
	//lb_sleep(1000);
/*...sCheck and print errors:8:*/
	switch (err) {
		case LB_THREAD_NO_ERROR:
			printf("Thread is created...\n");
			break;
		case LB_THREAD_ERROR:
			printf("Thread run returns some error\n");
			break;
		default:
			printf("Thread run returns unknown error\n");
	}
/*...e*/
	err = thread->run();
	lb_sleep(10);
/*...sOutput of main:8:*/
	int i = 0;
	while (1) {
		i++;
		lb_sleep(1000);
/*		
		if (i == 100) {
		  thread = new myThread();
		  lbThreadError err = thread->create();
		  err = thread->run();
		}
*/		
		printf("Main is at %d\n", i);
	}
/*...e*/
	lb_sleep(1000);	
/*...sCheck and print errors:8:*/
	switch (err) {
		case LB_THREAD_NO_ERROR:
			printf("Thread is running...\n");
			break;
		case LB_THREAD_ERROR:
			printf("Thread run returns some error\n");
			break;
		default:
			printf("Thread run returns unknown error\n");
	}
/*...e*/
	printf("Global application server is ending...\n");
	lb_sleep(1000);
	getch();
#endif
/*...e*/

	lbAppBusServer server;
	
	server.run();

}
/*...e*/

#include <lbinclude.h>
#include <conio.h>

/*...sclass GlobalAppServer:0:*/
class GlobalAppServer : public lbAppBusServer {
public:
	GlobalAppServer() 
	{
		LOG("GlobalAppServer::GlobalAppServer() called");
	};

	virtual ~GlobalAppServer() 
	{
	};
	
	int _service();
	
	int _request(char * servertype,
                     lb_Transfer_Data request,
                     lb_Transfer_Data & result);
};

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
	sprintf(buf, "GlobalAppServer::_request(): Packetcount = %d", count);
	printf("%s\n", buf);
	
	LOG(buf);
		
	request.resetPositionCount();
		
	while (count--) {
	LOG("GlobalAppServer::_request(): Handle a packet");
		LB_PACKET_TYPE type;
		int i = 0;
		char *buffer;
		request.getPacketType(type);

		switch (type) {
			case LB_CHAR:
				request.get(buffer);
				printf("Char value = %s\n", buffer); 
				break;
			case LB_INT: 
				request.get(i);
				printf("Integer value = %d\n", i);
				break;
				
			default:
				printf("Unknown packet type!\n"); 
				break;
		}
			
		request.incrementPosition();
	LOG("GlobalAppServer::_request(): Packet handled");
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
LOG("GlobalAppServer::_service(): Got a request, handle it");
		// Check request for service type
		handleRequest("GlobalAppServer", request, result);

		answerRequest(result);

		exit++;
		printf("GlobalAppServer::_service(): Got a request\n");
		LOG("GlobalAppServer::_service(): Got a request");
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
	LOG("myThread::myThread() called");
}
/*...e*/

/*...sGASThread\58\\58\\126\GASThread\40\\41\:0:*/
GASThread::~GASThread() {
	LOG("myThread::~myThread() called");
}
/*...e*/

/*...svoid\42\ GASThread\58\\58\Entry\40\\41\:0:*/
void* GASThread::Entry() {
	LOG("GASThread::Entry() called");

	GlobalAppServer server;
	
	LOG("GASThread::Entry(): Start server");
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

/*...smain:0:*/
void main(int argc, char** argv) {
LOGPREFIX("GlobalAppServer");
LOGENABLE("main(...)");
	printf("Global application server is starting...\n");
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
}
/*...e*/

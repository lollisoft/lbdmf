#include <lbinclude.h>
#include <conio.h>

class myThread : public lbThread {
public:
	myThread();
	
	virtual ~myThread();
	
protected:
	void* Entry();
};

myThread::myThread() {
	LOG("myThread::myThread() called");
}

myThread::~myThread() {
	LOG("myThread::~myThread() called\n");
}

class GlobalAppServer : public lbAppServer {
public:
	GlobalAppServer() 
	{
		LOG("GlobalAppServer::GlobalAppServer() called");
	};
	virtual ~GlobalAppServer() {};
	
	int _service();
};


int GlobalAppServer::_service() {
	LOG("GlobalAppServer::_service() called");
	
	int exit = 0;
	RemoteAppReq req;
	RemoteAppRes res;
	
	while (exit == 0) {
		LOG("GlobalAppServer::_service(): Waiting for a request");
		recv(req);
		LOG("GlobalAppServer::_service(): Got a request");
	}	
	
	return 0;
}

void* myThread::Entry() {
	LOG("myThread::Entry() called");

	GlobalAppServer server;
	
	LOG("myThread::Entry(): Start server");
	server.run();


	for (int i=0; i<5; i++) {
		printf("myThread::Entry - Loop at %d\n", i);
		Beep(200, 50);
		lb_sleep(1000);
	}
	return NULL;
}

void main(int argc, char** argv) {
LOGENABLE("main(...)");
	printf("Global application server is starting...\n");
	myThread *thread;
	thread = new myThread();
	
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
	for (int i=0;i<1000;i++) {
		lb_sleep(100);
		
		if (i == 100) {
		  thread = new myThread();
		  lbThreadError err = thread->create();
		  err = thread->run();
		}
		
		printf("Main is at %d\n", i);
		getch();
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

#ifndef LB_APPBUS
#define LB_APPBUS

#undef DLLEXPORT

/*...s\35\ifdef APPCS_DLL:0:*/
#ifdef APPCS_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif
/*...e*/

/*...s\35\ifndef APPCS_DLL:0:*/
#ifndef APPCS_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif
/*...e*/

/*...sbla:0:*/
#ifdef bla
// Here are some statis defined to enable communication on the app bus
enum {
	LB_ABBBUS_ERR
} lbAppBusStatus;
#endif
/*...e*/
/*...slbAppBus:0:*/
class DLLEXPORT lbTransfer;

class DLLEXPORT lbAppBus {

public:
	lbAppBus();
	virtual ~lbAppBus();

	lbTransfer* getServerConnection(const char* server);

protected:

	char* bus_master_adr;
	u_short bus_master_port;
};
/*...e*/

/*...slbAppBusClient:0:*/

class lbAppBusClient : public lbAppBus {
public:
	lbAppBusClient();
	virtual ~lbAppBusClient();

	void AnounceClient();
};
/*...e*/

/*...slbAppBusServer:0:*/
class lbAppBusServer : public lbAppBus {
public:
	lbAppBusServer();
	virtual ~lbAppBusServer();

	
};
/*...e*/
#endif

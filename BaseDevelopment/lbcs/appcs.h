#ifndef LB_APPCS
#define LB_APPCS

/*...sdefine DLLEXPORT:0:*/
#undef DLLEXPORT

#ifdef APPCS_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef APPCS_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif
/*...e*/



/**
 * Base class for communication 
 */

class DLLEXPORT RemoteAppCS {
};

/*...sclass RemoteAppReq:0:*/
class DLLEXPORT RemoteAppReq {
public:
	RemoteAppReq();
	virtual ~RemoteAppReq();

	void setIssue(char* what);
	void setValue(const char* param);
	
	char* getIssue();
	char* getValue();

private:
	char* issue;
	char* parameter;
};
/*...e*/

/**
 * RemoteAppRes represents a list with one or more results. The list ha a name, wich can be get
 * with getResultName. A result number indicates the request number.
 */

/*...sclass RemoteAppRes:0:*/
class DLLEXPORT RemoteAppRes {
public:
        RemoteAppRes();
		virtual ~RemoteAppRes();

        int isError();
        void reportError();

		char* getResultName();

        int getEntries();
        char* getEntryName(int i);
};
/*...e*/

class DLLEXPORT lbAppServer {
public:
	lbAppServer();
	virtual ~lbAppServer();

//	int run();
	
	/**
	 * This function must be implemented by the specific 
	 * server implementation.
	 */
	
	virtual int _service() = 0;

protected:

#ifdef bla
	// Server sends a result
	void send (const RemoteAppRes& res);

	// Server gets a request
	void recv (RemoteAppReq& req);
#endif

};

class DLLEXPORT lbAppClient {
public:
        lbAppClient();
        virtual ~lbAppClient();

		/**
		 * Establish a connection to an application server. The Server knows of the application
		 * name and from who the connection request comes from. The dataflow of this function
		 * is like this:
		 *
		 * All the data should be encrypted!
		 *
		 * Client		->		"Begin Connect" 						->		Server (or a proxy)
		 * Client		<-		"Ack: convID"							<-		Server (convID is the conversation id known by the server now)
		 * Client		->		"Connect as <Appname> <convID>"			->		Server
		 *
		 * Client		<-		"Ack: Application not known"			<-		Server (Server don't know any of this application)
		 * Client returns with error
		 * or
		 * Client		<-		"Ack: Need password"					<-		Server
		 * Client		->		"Password: <pw>"						->		Server
		 * Client		<-		"Ack" or "Fail"							<-		Server
		 *
		 */
        void Connect(const char* application);
        void Disconnect();

        RemoteAppRes& requestObject(const char* name);
#ifdef bla
        RemoteAppRes& subObject(const RemoteAppRes& res, const char* name);
#endif
};

#endif //LB_APPCS

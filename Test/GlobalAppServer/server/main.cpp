#include <lbConfigHook.h>

//#include <lbinclude.h>
#include <conio.h>
#include <signal.h>


void handler(int sig) {
	COUT << "Oops..." << ENDL;
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	PM->unload();
	unHookAll();
	
	exit(0);
}

#ifdef WINDOWS
bool CtrlHandler( DWORD fdwCtrlType ) 
{ 
  switch( fdwCtrlType ) 
  { 
    // Handle the CTRL-C signal. 
    case CTRL_C_EVENT: 
	{
      printf( "Ctrl-C event\n\n" );
      //Beep( 750, 300 ); 
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		PM->unload();
		unHookAll();
	
		exit(0);
      return( TRUE );
	}
#ifdef bla
    // CTRL-CLOSE: confirm that the user wants to exit. 
    case CTRL_CLOSE_EVENT: 
      Beep( 600, 200 ); 
      printf( "Ctrl-Close event\n\n" );
      return( TRUE ); 
 
    // Pass other signals to the next handler. 
    case CTRL_BREAK_EVENT: 
      Beep( 900, 200 ); 
      printf( "Ctrl-Break event\n\n" );
      return FALSE; 
 
    case CTRL_LOGOFF_EVENT: 
      Beep( 1000, 200 ); 
      printf( "Ctrl-Logoff event\n\n" );
      return FALSE; 
 
    case CTRL_SHUTDOWN_EVENT: 
      Beep( 750, 500 ); 
      printf( "Ctrl-Shutdown event\n\n" );
      return FALSE; 
#endif
    default: 
      return FALSE; 
  } 
} 
#endif



/*...smain:0:*/
int main(int argc, char** argv) {
	{
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		UAP_REQUEST(getModuleInstance(), lb_I_ApplicationServer, appServer)

		char* LOGGING = getenv("LOGGING");

		// Default
		setLogActivated(false);
		if (LOGGING != NULL) {
			if ((strcmp(LOGGING, "no") != 0) && (strcmp(LOGGING, "NO") != 0) && (strcmp(LOGGING, "No") != 0) && (strcmp(LOGGING, "nO") != 0)) 
			// Activate
				setLogActivated(true);
			else
				setLogActivated(false);
		}

		if (argc > 1 && strcmp(argv[1], "-log") == 0) {
			setLogActivated(true);
		}

		PM->initialize();
		
		_CL_LOG << "Global application server is starting..." LOG_
		
	
		/**
		* This let the app not crashing. But the handler simply
		* does exit(0), no cleanup yet ???
		*/
#ifndef WINDOWS
		signal(SIGINT, handler);
		signal(SIGTERM, handler);
#endif

#ifdef WINDOWS
		// As of http://msdn.microsoft.com/en-us/library/ms685049%28v=vs.85%29.aspx
		SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE );
#endif
	
		if (appServer != NULL) {
			appServer->run();
			PM->unload();
		} else {
			printf("Global application server not found...\n");
		}
		printf("Global application server is ending...\n");
		unHookAll();
	}
	return 0;
}
/*...e*/

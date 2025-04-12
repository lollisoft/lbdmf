/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2000-2025  Lothar Behrens (lothar.behrens@lollisoft.de)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
            Odenwaldstra�e 14

            63150 Heusenstamm (germany)
*/
#include <lbConfigHook.h>
//#include <lbinclude.h>
#include <conio.h>
#include <signal.h>

#include <IApplicationBus.h>
//#include <ApplicationBus/ApplicationBusProxy.h>

void handler(int sig) {
        COUT << "Oops..." << ENDL;
        exit(0);
}

void runTest(const char* servername, const char* servicename)
{
        int count = 0;

        UAP_REQUEST(getModuleInstance(), lb_I_ApplicationBus, client)
        
        if (client != NULL) {
                char buf[100] = "";
                
                _CL_LOG << "Application bus instantiated." LOG_

                if (servername != NULL && servicename != NULL) {
                    _CL_LOG << "Initialize custom host and service..." LOG_
                    client->setServerName(servername, servicename);
                }
                
                while (count++ < 1) {
                        UAP(lb_I_String, echo)
                        UAP(lb_I_String, backend)

                        //client->AnounceUser("lothar", "test");

                        char* text = "Hallo Server, dies ist eine Echo - Message";
                        echo = client->Echo(text);
                        
                        _CL_LOG << "Echo result is: " << echo->charrep() LOG_
                        
                        
                        backend = client->findBackend("lbDMFManager");
                        
                        
                        if (backend != NULL) _CL_LOG << "Backend is " << backend->charrep() LOG_
                }
        } else {
                _CL_LOG << "Error: Can't find application bus." LOG_
        }       
}

/*...smain:0:*/
int main(int argc, char** argv) {
        /**
         * This let the app not crashing. But the handler simply
         * does exit(0), no cleanup yet ???
         */
        signal(SIGINT, handler);

        signal(SIGILL, handler);

        char* LOGGING = getenv("LOGGING");

        // Default
        setLogActivated(false);
        if (LOGGING != NULL) {
                if ((strcmp(LOGGING, "no") != 0) && 
                        (strcmp(LOGGING, "NO") != 0) && 
                        (strcmp(LOGGING, "No") != 0) && 
                        (strcmp(LOGGING, "nO") != 0)) 
                        // Activate
                        setLogActivated(true);
                else
                        setLogActivated(false);
        }

        if (argc > 1 && strcmp(argv[1], "-log") == 0) {
                setLogActivated(true);
        }

        char* server = NULL; //"LAPTOP-02RLMPT3";
        char* service = NULL; //"busmaster";

        if (argc > 5 &&
                strcmp(argv[1], "-server") == 0 &&
                strcmp(argv[2], "-log") != 0 &&
                strcmp(argv[3], "-service") == 0 &&
                strcmp(argv[4], "-log") != 0 &&
                strcmp(argv[5], "-log") == 0) {
                setLogActivated(true);
                _CL_LOG << "Got server parameter..." LOG_
                server = strdup(argv[2]);
                service = strdup(argv[4]);
                _CL_LOG << "Server = " << server << "/" << service LOG_
        } else
        if (argc > 4 &&
                strcmp(argv[1], "-server") == 0 &&
                strcmp(argv[2], "-log") != 0 &&
                strcmp(argv[3], "-service") == 0 &&
                strcmp(argv[4], "-log") != 0) {
                server = strdup(argv[2]);
                service = strdup(argv[4]);
        } else
        if (argc > 1 && strcmp(argv[1], "-log") != 0)
        {
                _CL_LOG << "Call application like " << argv[0] << " [-log]" LOG_
                _CL_LOG << "Call application like " << argv[0] << " -server server -service service [-log]" LOG_
        }
        
        runTest(server, service);
        
        getchar();

        _CL_LOG << "Ending server test thread" LOG_
        exit(0);
        return 0;
}
/*...e*/

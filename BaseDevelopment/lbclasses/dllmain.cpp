/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    lbModule.h is part of DMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

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
            Borsteler Bogen 4

            22453 Hamburg (germany)
*/

#ifdef WINDOWS
#include <windows.h>
#include <lbInterfaces.h>
#include <lbConfigHook.h>


#ifdef LB_CLASSES_DLL
lb_I_Log *log;
int isInitializing;
#endif


/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";
        
        switch (reason) {
                case DLL_PROCESS_ATTACH:
                        if (situation) {
                                _LOG << "DLL statically loaded." LOG_
                        }
                        else {
                                _LOG << "DLL dynamically loaded." LOG_
                        }
                        break;
                case DLL_THREAD_ATTACH:
                        _LOG << "New thread starting." LOG_
                        break;
                case DLL_PROCESS_DETACH:                        
                        if (situation)
                        {
                                _LOG << "DLL released by system." LOG_
                        }
                        else
                        {
                                _LOG << "DLL released by program." LOG_
                        }
                        break;
                case DLL_THREAD_DETACH:
                        _LOG << "Thread terminating." LOG_
                derault:
                        return FALSE;
        }
        
        return TRUE;
}
/*...e*/
#endif

#ifdef WINDOWS
#include <windows.h>
#include <lbInterfaces.h>
#include <lbConfigHook.h>
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

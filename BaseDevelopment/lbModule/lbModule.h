#ifndef __LB_MODULE__
#define __LB_MODULE__

#include <iostream.h>

/*...sDLLEXPORT:0:*/
#undef DLLEXPORT

#ifdef LB_MODULE_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef LB_MODULE_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif
/*...e*/

/*...sclass lbModule:0:*/
class lbModule : 
                public lb_I_Module
{
public:
        lbModule() {
                ref = STARTREF;
        }
        
        virtual ~lbModule() {
                if (ref != STARTREF) cout << "Error: Reference count mismatch" << endl;
        }
        
        virtual lbErrCodes release();
        virtual lbErrCodes queryInterface(char* name, void** unknown);
        
        virtual lbErrCodes initialize();
        virtual lbErrCodes request(const char* request, lb_I_Unknown*& result);
        virtual lbErrCodes uninitialize();
        
        
//        void operator delete(void * del) { delete del; }
        
        virtual lbErrCodes load(char* name);
        virtual lbErrCodes getObjectInstance(char* name, lb_I_Container*& inst);
        
protected:
        int ref;
};
/*...e*/

/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

lbErrCodes DLLEXPORT __cdecl getlb_ModuleInstance(lb_I_Module*& inst);
lbErrCodes DLLEXPORT __cdecl lb_releaseInstance(lb_I_Unknown * inst);

/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#endif // __LB_MODULE__

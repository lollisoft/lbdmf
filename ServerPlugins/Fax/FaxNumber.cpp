
/*
        Automatically created file. Do not modify.
 */

#include <lbConfigHook.h>
#include <IFaxNumber.h>

#undef DLLEXPORT

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif
#ifdef LINUX 
#define DLLEXPORT
#endif

#include <FaxNumber.h>

      

IMPLEMENT_FUNCTOR(instanceOfFaxNumber, FaxNumber)

BEGIN_IMPLEMENT_LB_UNKNOWN(FaxNumber)
        ADD_INTERFACE(lb_I_ProtocolTarget)
        ADD_INTERFACE(lb_I_FaxNumber_ProtocolTarget)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL FaxNumber::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "FaxNumber::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}


FaxNumber::FaxNumber() {
        
        UAP_REQUEST(getModuleInstance(), lb_I_Container, connections)
        REQUEST(getModuleInstance(), lb_I_String, ServerInstance)
}

FaxNumber::~FaxNumber() {

}

const char* FaxNumber::getServiceName() {
        return "localhost/FaxNumber";
}

lbErrCodes LB_STDCALL FaxNumber::registerProtocols(lb_I_ProtocolManager* protoMgr, const char* serverInstance) {

                UAP_REQUEST(getModuleInstance(), lb_I_String, protocolScope)
                
                *ServerInstance = serverInstance;
                
                *protocolScope = serverInstance;
                *protocolScope += ".";
                *protocolScope += getClassName();
                *protocolScope += ".";
                *protocolScope += "AskForFaxNumber";
        protoMgr->addProtocolHandler(protocolScope->charrep(), this, (lbProtocolCallback) &FaxNumber::_AskForFaxNumber);

        return ERR_NONE;
}


void LB_STDCALL FaxNumber::AskForFaxNumber(lb_I_String* faxnumber) {

}
lbErrCodes LB_STDCALL FaxNumber::_AskForFaxNumber(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result) {
        LB_PACKET_TYPE type;
    lbErrCodes err = ERR_NONE;


        unsigned long pid = 0;
        unsigned long tid = 0;

        UAP_REQUEST(getModuleInstance(), lb_I_String, faxnumber)
            

/*...sEcho proto:0:*/
/*
        add("Echo")
        add("Your echo message");
*/
/*...e*/

        AskForFaxNumber(*&faxnumber);


        result->add("faxnumber");
        result->add(faxnumber->charrep());

    return err;
}
      

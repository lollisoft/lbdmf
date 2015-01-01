/*...sincludes:0:*/
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#include <io.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#ifndef OSX
#include <malloc.h>
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
/*...e*/

#include <wx/datetime.h>

/*...e*/

/*...slbTimerEventInterceptor:0:*/
class lbTimerEventInterceptor :
        public lb_I_DispatchInterceptor {
        public:
                lbTimerEventInterceptor();
                virtual ~lbTimerEventInterceptor();
                
                lb_I_String* LB_STDCALL getVendorName();
                
                lb_I_String* LB_STDCALL getDescription();
                lbErrCodes LB_STDCALL initialize();
                
                lbErrCodes LB_STDCALL addInterceptedInstance(lb_I_Unknown* intercepted);
                lbErrCodes LB_STDCALL removeInterceptedInstance(lb_I_Unknown* interceptedInstance);
                
                lbErrCodes LB_STDCALL OnBeforeTimerEvent(lb_I_Unknown* uk_unused);
                lbErrCodes LB_STDCALL OnAfterTimerEvent(lb_I_Unknown* uk);

                DECLARE_LB_UNKNOWN()
                
private:
                // Actually looks up the matching intercepted instance.
                lb_I_Unknown* LB_STDCALL lookupIntercepted(lb_I_Unknown* uk);
                
                UAP(lb_I_Container, interceptedHandlers)
};


BEGIN_IMPLEMENT_LB_UNKNOWN(lbTimerEventInterceptor)
        ADD_INTERFACE(lb_I_DispatchInterceptor)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbTimerEventInterceptor, lbTimerEventInterceptor)


/*...slbErrCodes LB_STDCALL lbTest\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbTimerEventInterceptor::setData(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_NONE;
    _CL_LOG << "lbTimerEventInterceptor::setData(...) not implemented yet" LOG_
    return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbTest\58\\58\lbTest\40\\41\:0:*/
lbTimerEventInterceptor::lbTimerEventInterceptor() 
{
	_LOG << "lbTimerEventInterceptor::lbTimerEventInterceptor() called." LOG_
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)

	initialize(); // Initialize the interceptors.
}
/*...e*/
/*...slbTest\58\\58\\126\lbTest\40\\41\:0:*/
lbTimerEventInterceptor::~lbTimerEventInterceptor() {
        _LOG << "lbTimerEventInterceptor::~lbTimerEventInterceptor() called." LOG_
        
        // This plugin sould only get instances of database forms that are deleted by the wxWidgets system. Thus detach and avoid crashing.
        if (interceptedHandlers != NULL) interceptedHandlers->detachAll();
}
/*...e*/

lb_I_String* lbTimerEventInterceptor::getDescription() {
        UAP_REQUEST(getModuleInstance(), lb_I_String, info)
        *info = "TimerEventInterceptor will hook into the timer event provided by the hosting application.";
        info++;
        return info.getPtr();
}

lb_I_String* lbTimerEventInterceptor::getVendorName() {
        UAP_REQUEST(getModuleInstance(), lb_I_String, info)
        *info = "lollisoft Softwareentwicklung Lothar Behrens";
        info++;
        return info.getPtr();
}

lbErrCodes lbTimerEventInterceptor::initialize() {
        lbErrCodes err = ERR_NONE;
        UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
        UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
        dispatcher->setEventManager(eman.getPtr());

        REQUEST(getModuleInstance(), lb_I_Container, interceptedHandlers)
        
        interceptedHandlers->setCloning(false); // Don't clone the event handlers!
        
        _LOG << "lbTimerEventInterceptor::initialize() called.\n" LOG_
        
        dispatcher->setInterceptor(this, (lbInterceptor) &lbTimerEventInterceptor::OnBeforeTimerEvent, (lbInterceptor) &lbTimerEventInterceptor::OnAfterTimerEvent, "timerEvent");

        // Need to get called by a timer event to enable polling of new external events
        // Idea to the schema:
        // A timer handler has a name. Each handler is added at the end so it will enforce an ordered sequence (or chain) if several handlers are registered with the same name.
        // But then the typical registration is not enough as it will replace existing handlers.
}

lbErrCodes LB_STDCALL lbTimerEventInterceptor::removeInterceptedInstance(lb_I_Unknown* interceptedInstance) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbTimerEventInterceptor::addInterceptedInstance(lb_I_Unknown* intercepted) {
	lbErrCodes err = ERR_NONE;
	char ptr[20] = "";
	bool validInstance = false;
	UAP(lb_I_DatabaseForm, metaIntercepted)
	
	QI(intercepted, lb_I_MetaApplication, metaIntercepted)
	
	// Tricky conversion due to inheritance design (no diamond / lb_I_EventHandler has no base class)
	lb_I_EventHandler* evH;
	
	if (metaIntercepted != NULL) {
		validInstance = true;
		evH = (lb_I_EventHandler*) metaIntercepted.getPtr();
	}
	
	if (!validInstance) {
		_LOG << "Error: This interceptor only accepts instances of the following types: lb_I_MetaApplication." LOG_
		return ERR_INVALID_INTERCEPTED_INSTANCE;
	}
	
	sprintf(ptr, "%p", evH);
	UAP_REQUEST(getModuleInstance(), lb_I_String, I)
	UAP(lb_I_KeyBase, key)
	*I = ptr;
	
	QI(I, lb_I_KeyBase, key)
	
	if (interceptedHandlers->exists(&key) != 1) {
		_LOG << "lbTimerEventInterceptor::addInterceptedInstance() Insert intercepted instance into interceptedHandlers." LOG_
		UAP(lb_I_Unknown, uk)
		QI(intercepted, lb_I_Unknown, uk)
		interceptedHandlers->insert(&uk, &key);
	}
	return ERR_NONE;
}

lb_I_Unknown* LB_STDCALL lbTimerEventInterceptor::lookupIntercepted(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_NONE;
        UAP(lb_I_Integer, id)
        
        if (uk == NULL) {
                _LOG << "lbTimerEventInterceptor::lookupIntercepted() Error: Expected an object." LOG_
                return NULL;
        }

        QI(uk, lb_I_Integer, id)
        

        if (id != NULL) {
                UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
                UAP_REQUEST(getModuleInstance(), lb_I_String, event)
                *event = eman->reverseEvent(id->getData());
                
                interceptedHandlers->finishIteration();
                while(interceptedHandlers->hasMoreElements() != 0) {
                        UAP(lb_I_Unknown, uk)
                        UAP(lb_I_KeyBase, key)
                        uk = interceptedHandlers->nextElement();
                        key = interceptedHandlers->currentKey();
                        _LOG << "lbTimerEventInterceptor::lookupIntercepted() Compare event '" << event->charrep() << "' with key '" << key->charrep() << "'." LOG_
                        if (event->strpos(key->charrep()) >= 0) {
                                uk++;
                                return uk.getPtr();
                        }
                }
        } else {
                _LOG << "lbTimerEventInterceptor::lookupIntercepted() Error: Expected an lb_I_Integer object, but found '" << uk->getClassName() << "'" LOG_
        }
        
        return NULL;
}

lbErrCodes LB_STDCALL lbTimerEventInterceptor::OnBeforeTimerEvent(lb_I_Unknown* uk_unused) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbTimerEventInterceptor::OnBeforeTimerEvent() called." LOG_

	
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

	UAP(lb_I_Parameter, UpdateSettings)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, LastCheckWeek)

	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	*name = "LastCheckWeek";
	
	bool doCheck = false;
	
	UpdateSettings = meta->getPropertySet("UpdateSettings");
	UpdateSettings->getUAPInteger(*&name, *&LastCheckWeek);

	wxDateTime dt;
	
	if (LastCheckWeek->getData() == 0) {
		wxDateTime::wxDateTime_t week = dt.GetWeekOfYear();
		
		LastCheckWeek->setData(week + 1);

		UpdateSettings->setUAPInteger(*&name, *&LastCheckWeek);
		
		meta->addPropertySet(*&UpdateSettings, "UpdateSettings");
		
		doCheck = true;
	} else {
		wxDateTime::wxDateTime_t week = dt.GetWeekOfYear();
		
		if (week > LastCheckWeek->getData()) {
			doCheck = true;
		
			LastCheckWeek->setData(week + 1);
			
			UpdateSettings->setUAPInteger(*&name, *&LastCheckWeek);
		}
	}
	
	if (!doCheck) return ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)
	
	parameter->setData("msg");
	value->setData("lbTimerEventInterceptor::OnBeforeTimerEvent");
	param->setUAPString(*&parameter, *&value);
	parameter->setData("title");
	value->setData("Interceptor triggered");
	param->setUAPString(*&parameter, *&value);
	
	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)
	
	int event = 0;
	
	eman->resolveEvent("RunUpdateCheck", event);
	
	dispatcher->dispatch("RunUpdateCheck", uk.getPtr(), &uk_result);

	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbTimerEventInterceptor::OnAfterTimerEvent(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbTimerEventInterceptor::OnAfterTimerEvent() called." LOG_
        
	return ERR_NONE;
}

/*...e*/

#include "../MiniCppUnit/MiniCppUnit.hxx"

#include <lbConfigHook.h>
#include <signal.h>

#define DONT_USE_LBDMF_EXCEPTIONS

#ifdef WINDOWS
#define LOGFILE "\\myLog.log"
#endif

#ifdef LINUX
#define LOGFILE "/myLog.log"
#endif

#include <UIWrapper.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(UIWrapper)
	ADD_INTERFACE(lb_I_Application)
	ADD_INTERFACE(lb_I_SimulatedApplication)
END_IMPLEMENT_LB_UNKNOWN()

//IMPLEMENT_FUNCTOR(instanceOfApplication, UIWrapper)

UIWrapper::UIWrapper() {
	
	gui = NULL;
	REQUEST(getModuleInstance(), lb_I_Container, answerList)
	REQUEST(getModuleInstance(), lb_I_String, fileanswer)
	
	numberOfAnswers = 0;
	
	printf("Instance of lb_I_Application created\n");
	_LOG << "Instance of lb_I_Application created" LOG_
}

UIWrapper::~UIWrapper() {
	_LOG << "Instance of lb_I_Application destroyed" LOG_
	
	lb_I_EventHandler* evHandler = (lb_I_EventHandler*) this;
	
	dispatcher->detachInstance(evHandler);
}

void LB_STDCALL UIWrapper::setFileAnswer(char* what) {
	*fileanswer = what;
}

void LB_STDCALL UIWrapper::addAnswer(char* what, bool last) {
	numberOfAnswers++;
	
	UAP(lb_I_Unknown, uk);
	UAP(lb_I_KeyBase, keyAnswerNumber)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, AnswerNumber)
	UAP_REQUEST(getModuleInstance(), lb_I_String, answer)
	
	QI(AnswerNumber, lb_I_KeyBase, keyAnswerNumber)
	QI(answer, lb_I_Unknown, uk)
	
	*answer = what;
	AnswerNumber->setData(numberOfAnswers);

	answerList->insert(&uk, &keyAnswerNumber);

	if (last == true)
		numberOfAnswers = 0;
}

lbErrCodes LB_STDCALL UIWrapper::askOpenFileReadStream(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, filepath)
	UAP_REQUEST(getModuleInstance(), lb_I_String, defaultdir)
	UAP_REQUEST(getModuleInstance(), lb_I_String, after)

	UAP(lb_I_Parameter, param)

	QI(uk, lb_I_Parameter, param)

	parameter->setData("extension");
	param->getUAPString(*&parameter, *&name);

	//"BMP and GIF files (*.bmp;*.gif)|*.bmp;*.gif|PNG files (*.png)|*.png"

	printf("Choose a file. Default directory: %s, Name: %s\n", defaultdir->charrep(), name->charrep());

	parameter->setData("result");
	filepath->setData(fileanswer->charrep());
	param->setUAPString(*&parameter, *&filepath);

	return err;
}

lbErrCodes LB_STDCALL UIWrapper::setStatusText(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_DISPATCH_PARAMETER_WRONG;
        UAP(lb_I_Parameter, params)

        QI(uk, lb_I_Parameter, params)

        if (params != NULL) {
                UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
                UAP_REQUEST(getModuleInstance(), lb_I_String, name)
				UAP_REQUEST(getModuleInstance(), lb_I_String, value)
				UAP_REQUEST(getModuleInstance(), lb_I_String, CallYield)

                *parameter = "Name";
                params->getUAPString(*&parameter, *&name);
                *parameter = "Value";
                params->getUAPString(*&parameter, *&value);
				*parameter = "CallYield";
				params->getUAPString(*&parameter, *&CallYield);

				printf("Status: %s\n", value->charrep());

                err = ERR_NONE;
        }

        return err;
}

lbErrCodes LB_STDCALL UIWrapper::showMsgBox(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_NONE;

        UAP(lb_I_Parameter, param)
        UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
        UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
        UAP_REQUEST(getModuleInstance(), lb_I_String, title)
        QI(uk, lb_I_Parameter, param)

        parameter->setData("msg");
        param->getUAPString(*&parameter, *&msg);
        parameter->setData("title");
        param->getUAPString(*&parameter, *&title);

        printf("Message title: %s\nMessage: %s\n", title->charrep(), msg->charrep());

        return err;
}

lbErrCodes LB_STDCALL UIWrapper::askYesNo(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
	UAP_REQUEST(getModuleInstance(), lb_I_String, answer)
	UAP_REQUEST(getModuleInstance(), lb_I_String, result)

	UAP(lb_I_Parameter, param)
	QI(uk, lb_I_Parameter, param)

	UAP(lb_I_KeyBase, keyAnswerNumber)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, AnswerNumber)
	QI(AnswerNumber, lb_I_KeyBase, keyAnswerNumber)
	numberOfAnswers++;
	AnswerNumber->setData(numberOfAnswers);

	UAP(lb_I_Unknown, ukAnswer)
	ukAnswer = answerList->getElement(&keyAnswerNumber);
	QI(ukAnswer, lb_I_String, answer)
	
	parameter->setData("msg");
	param->getUAPString(*&parameter, *&msg);

	printf("Question: %s\n", msg->charrep());
	printf("Answer: %s\n", answer->charrep());

    parameter->setData("result");
    result->setData(answer->charrep());
    param->setUAPString(*&parameter, *&result);

    COUT << ENDL;

	return err;
}

lbErrCodes LB_STDCALL UIWrapper::registerEventHandler(lb_I_Dispatcher* disp) {
	lb_I_EventHandler* eh = (lb_I_EventHandler*) this;

	disp->addEventHandlerFn(eh, (lbEvHandler) &UIWrapper::showMsgBox, "showMsgBox");
	disp->addEventHandlerFn(eh, (lbEvHandler) &UIWrapper::askYesNo, "askYesNo");
	disp->addEventHandlerFn(eh, (lbEvHandler) &UIWrapper::setStatusText, "setStatusText");
	disp->addEventHandlerFn(eh, (lbEvHandler) &UIWrapper::askOpenFileReadStream, "askOpenFileReadStream");


	return ERR_NONE;
}

lb_I_Unknown* LB_STDCALL UIWrapper::getUnknown() {
	UAP(lb_I_Unknown, uk)
	queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__);
	uk++;
	return uk.getPtr();
}

/*...slbErrCodes LB_STDCALL lbApplication\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL UIWrapper::setData(lb_I_Unknown* uk) {
	_LOG << "lbApplication::setData() has not been implemented" LOG_

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\setGUI\40\lb_I_GUI\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL UIWrapper::setGUI(lb_I_GUI* _gui) {
	gui = _gui;
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\getGUI\40\lb_I_GUI\42\\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL UIWrapper::getGUI(lb_I_GUI** _gui) {
	*_gui = gui;
	return ERR_NONE;
}
/*...e*/
/*...slb_I_EventManager\42\ LB_STDCALL lbApplication\58\\58\getEVManager\40\ void \41\:0:*/
lb_I_EventManager* LB_STDCALL UIWrapper::getEVManager( void ) {
	return NULL;
}
/*...e*/

lbErrCodes LB_STDCALL UIWrapper::save() {
    return ERR_NONE;
}

lbErrCodes LB_STDCALL UIWrapper::load() {
    return ERR_NONE;
}


lbErrCodes LB_STDCALL UIWrapper::uninitialize() {
	return ERR_NONE;
}
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\initialize\40\char\42\ user \61\ NULL\44\ char\42\ app \61\ NULL\41\:0:*/
lbErrCodes LB_STDCALL UIWrapper::initialize(const char* user, const char* app) {

	// To be implemented in a separate application module

	int askYesNo;
	int showMsgBox;
	int setStatusText;
	int askOpenFileReadStream;

	// Get the event manager

	REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)

	eman->registerEvent("askYesNo", askYesNo);
	printf("Registered event ID=%d for askYesNo.\n", askYesNo);
	eman->registerEvent("showMsgBox", showMsgBox);
	printf("Registered event ID=%d for showMsgBox.\n", showMsgBox);
	eman->registerEvent("setStatusText", setStatusText);
	printf("Registered event ID=%d for setStatusText.\n", setStatusText);
	eman->registerEvent("askOpenFileReadStream", askOpenFileReadStream);
	printf("Registered event ID=%d for askOpenFileReadStream.\n", askOpenFileReadStream);

	dispatcher->setEventManager(eman.getPtr());
	registerEventHandler(dispatcher.getPtr());
	return ERR_NONE;
}
/*...e*/
lbErrCodes LB_STDCALL UIWrapper::getUserName(lb_I_String** user) {
	(*user)->setData(LogonUser->charrep());
	return ERR_NONE;
}

lbErrCodes LB_STDCALL UIWrapper::getApplicationName(lb_I_String** app) {
	(*app)->setData(LogonApplication->charrep());
	return ERR_NONE;
}
lbErrCodes LB_STDCALL UIWrapper::setUserName(const char* user) {
	if (LogonUser == NULL) {
        	REQUEST(getModuleInstance(), lb_I_String, LogonUser)
	}

       	LogonUser->setData(user);
	return ERR_NONE;
}

lbErrCodes LB_STDCALL UIWrapper::setApplicationName(const char* app) {
	if (LogonApplication == NULL) {
        	REQUEST(getModuleInstance(), lb_I_String, LogonApplication)
	}

       	LogonApplication->setData(app);
	return ERR_NONE;
}


lbErrCodes LB_STDCALL UIWrapper::run() {
#ifdef bla
	lb_I_Unknown* result;

	dispatcher->dispatch("AddMenu", NULL, &result);
#endif
	return ERR_NONE;
}


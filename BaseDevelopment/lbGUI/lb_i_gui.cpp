#define LB_I_GUI_DLL

/*...sInclude:0:*/
/*
#include <appcs.h>

#include <string.h>
#include <lbObject.h>
#include <lbKey.h>

#include <lbContainer.h>
*/

#include <lbInclude.h>

#include <lb_I_GUI.h>
#include <lb_misc.h>
/*...e*/


/*...sprivate class definitions:0:*/
/*...sclass DLLEXPORT lb_I_GUIMenuEntry:0:*/
class DLLEXPORT lb_I_GUIMenuEntry: public lb_I_GUIComponent {
public:
    lb_I_GUIMenuEntry();
    virtual ~lb_I_GUIMenuEntry();
        
    int getId();
    char* getTxt();
    char* getHlp();
 
    /**
     * This is no longer used, because setParameters
     */   
    void setMenu(int id, char* txt, char* hlp);
protected:
    void setType();

    
    lb_Transfer_Data* getParameterInfo();
    int setParameters(lb_Transfer_Data* data);

//    lb_I_GUIComponent* createChildInstance(); // here ever NULL

    char* MenuTxt;
    char* MenuHlp;
    int MenuId;
};
/*...e*/

/*...sclass DLLEXPORT lb_I_GUIMenu:0:*/
class DLLEXPORT lb_I_GUIMenu: public lb_I_GUIComponent {
public:
    lb_I_GUIMenu();
    virtual ~lb_I_GUIMenu();

        
    GUITypes getType();
    
    /**
     * The name is also the scope of the object
     */
    char* getName();
    void setName(char* n);

protected:
    void setType();

    lb_Transfer_Data* getParameterInfo();
    int setParameters(lb_Transfer_Data* data);

//    lb_I_GUIComponent* createChildInstance();
    
    lbComponentDictionary* menuEntries;
    char* name;
};
/*...e*/

/*...sclass DLLEXPORT lb_I_GUIMenuBar:0:*/
class DLLEXPORT lb_I_GUIMenuBar: public lb_I_GUIComponent {
public:
    /**
     * This constructor is used to get the menubar for the
     * given application name. The initializion may be done
     * by network requests.
     */
    lb_I_GUIMenuBar();
    virtual ~lb_I_GUIMenuBar();

    int hasMoreElements();

    lb_I_GUIComponent* nextElement();


protected:
    void setType();

//    lb_I_GUIComponent* createChildInstance();

    lb_Transfer_Data* getParameterInfo();
    int setParameters(lb_Transfer_Data* data);
    
    // A list of menus (File, View, Help...)
    lbComponentDictionary* Menus;

    // The name of the application (used to get menu setup from remote server
};
/*...e*/
/*...e*/


// Class, that holds a GUI component. An object of this class could be stored
// in lbComponentDictionary
/*...slb_GUIComponent:0:*/
class lb_GUIComponent: public lbObject {
public:
        lb_GUIComponent() {
        }

	virtual ~lb_GUIComponent() {
        }

	/**
	 * Implement the abstract functions
	 */
	void setType() { OTyp = LB_GUIOBJECT; }
	lbObject* clone() const {
		lb_GUIComponent *c = new lb_GUIComponent();
		c->setObject(theObject);
		return c;
	}
                
        void setObject(lb_I_GUIComponent* o) {
            theObject = o;
        }

        lb_I_GUIComponent* getObject() {
            return theObject;
        }

        lb_I_GUIComponent* theObject;    
};
/*...e*/

/*...slb_I_GUIComponent:0:*/
lb_I_GUIApplication* lb_I_GUIComponent::GUIApplication = NULL;

lb_I_GUIComponent::lb_I_GUIComponent() {
}

lb_I_GUIComponent::~lb_I_GUIComponent() {
}

lb_I_GUIComponent* lb_I_GUIComponent::factory(const char* typeName) {
	return NULL;
}

int lb_I_GUIComponent::eventHandler(lb_Transfer_Data& request, lb_Transfer_Data& result) {
	return 0;
}

char* lb_I_GUIComponent::getRefId() {
	return NULL;
}

lbKey lb_I_GUIComponent::getKey() {
	return key;
}

GUITypes lb_I_GUIComponent::getType() {
    return typ;
}

int lb_I_GUIComponent::setParent(lb_I_GUIComponent* const _parent) {
	GUIApplication->setParent(this, _parent);
	return 1;
}

lb_I_GUIComponent* lb_I_GUIComponent::getParent() {
	return GUIApplication->getParent(this);
}

lbComponentDictionary* lb_I_GUIComponent::getChildren() {
	return GUIApplication->getChildrens(this);
}
/*...e*/

/*...slb_I_GUIMenuBar:0:*/
lb_I_GUIMenuBar::lb_I_GUIMenuBar() {
}

lb_I_GUIMenuBar::~lb_I_GUIMenuBar() {
}
#ifdef bla
lb_I_GUIComponent* lb_I_GUIMenuBar::createChildInstance() {
	return (lb_I_GUIComponent*) new lb_I_GUIMenu();
}
#endif
/*...sMarshalling interface:0:*/
lb_Transfer_Data* lb_I_GUIMenuBar::getParameterInfo() {
	return NULL;
}

int lb_I_GUIMenuBar::setParameters(lb_Transfer_Data* data) {
	return 1;
}

/*...e*/


#ifdef bla
/*...slbStringList\42\ lb_I_GUIMenuBar\58\\58\getChildScopes\40\\41\:0:*/
lbStringList* lb_I_GUIMenuBar::getChildScopes() {

    lbAppClient* client = getClientConnection();

    lbObject* temp;
    lbStringList* subitems = NULL;

    temp = client->requestObject("LB_MENUBAR", "subitems");
    if ((temp != NULL) && (temp->getType() == lbObject::LB_STRINGLIST))
      subitems = (lbStringList*) temp;

    delete client;
    
    return subitems;
}
/*...e*/
#endif
/*...slb_I_GUIMenuBar\58\\58\hasMoreElements\40\\41\:0:*/
int lb_I_GUIMenuBar::hasMoreElements() {
    return Menus->hasMoreElements();
}
/*...e*/
/*...slb_I_GUIMenuBar\58\\58\nextElement\40\\41\:0:*/
lb_I_GUIComponent* lb_I_GUIMenuBar::nextElement() {
        lb_GUIComponent *component;
        try {
                component = (lb_GUIComponent*) Menus->nextElement();
				if (component == NULL) LOG("Component in lb_I_GUIMenuBar is NULL");
        } catch (...) {
                LOG("In lb_I_GUI.cpp: Failed to get next menu element");
        }
        
        return component->getObject();
}
/*...e*/
/*...slb_I_GUIMenuBar\58\\58\setType\40\\41\:0:*/
void lb_I_GUIMenuBar::setType() {
    typ = LB_MENUBAR;
}
/*...e*/
/*...e*/

/*...slb_I_GUIMenu:0:*/
lb_I_GUIMenu::lb_I_GUIMenu() {
        name = NULL;
}

lb_I_GUIMenu::~lb_I_GUIMenu() {
}

/*...sMarshalling interface:0:*/
lb_Transfer_Data* lb_I_GUIMenu::getParameterInfo() {
	return NULL;
}

int lb_I_GUIMenu::setParameters(lb_Transfer_Data* data) {
	return 1;
}

/*...e*/


void lb_I_GUIMenu::setType() {
    typ = LB_MENU;
}
#ifdef bla
lb_I_GUIComponent* lb_I_GUIMenu::createChildInstance() {
	return (lb_I_GUIComponent*) new lb_I_GUIMenuEntry();
}
#endif
/*...slbStringList\42\ lb_I_GUIMenu\58\\58\getChildScopes\40\\41\:0:*/
#ifdef bla
lbStringList* lb_I_GUIMenu::getChildScopes() {

    lbAppClient* client = getClientConnection();

    lbObject* temp;
    lbStringList* subitems = NULL;

    temp = client->requestObject("LB_MENU", "subitems");
    if ((temp != NULL) && (temp->getType() == lbObject::LB_STRINGLIST))
      subitems = (lbStringList*) temp;

    delete client;
    
    return subitems;
}
#endif
/*...e*/
        
GUITypes lb_I_GUIMenu::getType() {
        return LB_MENU;
}

char* lb_I_GUIMenu::getName() {
        return name;
}

void lb_I_GUIMenu::setName(char* n) {
        if (name != NULL) delete name;
        name = strdup(n);
}
/*...e*/

/*...slb_I_GUIMenuEntry:0:*/
lb_I_GUIMenuEntry::lb_I_GUIMenuEntry() {
}

lb_I_GUIMenuEntry::~lb_I_GUIMenuEntry() {
}

/*...sMarshalling interface:0:*/
lb_Transfer_Data* lb_I_GUIMenuEntry::getParameterInfo() {
	return NULL;
}

int lb_I_GUIMenuEntry::setParameters(lb_Transfer_Data* data) {
	return 1;
}

/*...e*/

int lb_I_GUIMenuEntry::getId() {
    return MenuId;
}

char* lb_I_GUIMenuEntry::getTxt() {
    return MenuTxt;
}


char* lb_I_GUIMenuEntry::getHlp() {
    return MenuHlp;
}

void lb_I_GUIMenuEntry::setMenu(int id, char* txt, char* hlp) {
    MenuId = id;
    MenuTxt = strdup(txt);
    MenuHlp = strdup(hlp);
}


void lb_I_GUIMenuEntry::setType() {
    typ = LB_MENUENTRY;
}
#ifdef bla
/*...slbStringList\42\ lb_I_GUIMenuEntry\58\\58\getChildScopes\40\\41\:0:*/
lbStringList* lb_I_GUIMenuEntry::getChildScopes() {
    return NULL;
}
/*...e*/
#endif
#ifdef bla
lb_I_GUIComponent* lb_I_GUIMenuEntry::createChildInstance() {
        return NULL;
}
#endif
/*...e*/

/*...slb_I_Event:0:*/
lb_I_Event::lb_I_Event() {
}

lb_I_Event::~lb_I_Event() {
}

void lb_I_Event::setType() {
	OTyp = LB_EVENT;
}

lbObject* lb_I_Event::clone() const {
	LOG("lb_I_Event::clone(): Not yet implemented!");
	return NULL;
}
/*...e*/

/*...slb_I_Application:0:*/
lb_I_Application::lb_I_Application() {
	wrapped = NULL;
	wrapper = this;
}

lb_I_Application::~lb_I_Application() {
	// Nothing to do yet
}

int lb_I_Application::callback(lb_Transfer_Data& request, lb_Transfer_Data& result) {
	if ((wrapper != NULL) && 
	    (wrapped != NULL) &&
	    (this == wrapped)
	   ) {
	   	return _callback(request, result);
	   } else {
	   	LOG("lb_I_Application::callback(...): Failed to issue a callback");
	   }
	return 0;
}

/*...e*/

/*...slb_I_GUIApplication:0:*/
lbAppBusClient* lb_I_GUIApplication::AppBusClient = NULL;

/*...slb_I_GUIApplication\58\\58\lb_I_GUIApplication\40\\41\:0:*/
lb_I_GUIApplication::lb_I_GUIApplication() {
	wrapped = this;
}
/*...e*/

/*...slb_I_GUIApplication\58\\58\\126\lb_I_GUIApplication\40\\41\:0:*/
lb_I_GUIApplication::~lb_I_GUIApplication() {
	if (AppBusClient != NULL) delete AppBusClient;
}
/*...e*/

/*...slb_I_GUIApplication\58\\58\AnounceUser\40\char\42\ _user\44\ char\42\ _passwd\41\:0:*/
int lb_I_GUIApplication::AnounceUser(char* _user, char* _passwd) {
	if (AppBusClient == NULL) {
		LOG("lb_I_GUIApplication::AnounceUser(): Error, Load was not called prior this call.");
		return 0;
	}
	
	lb_Transfer_Data request;
	lb_Transfer_Data result;

	return 0;
}
/*...e*/

/*...sevent handling:0:*/
int lb_I_GUIApplication::setWrapperEventDispatcher(lb_I_EventDispatcher* evDisp) {
	return 0;
}
/*...e*/

/*...scallback:0:*/
/**
 * Must implement my _callback routine, so a GUI element may issue an event 
 * to my in order to update the data model. 
 * 
 */
int lb_I_GUIApplication::_callback(lb_Transfer_Data&, lb_Transfer_Data&) {
	LOG("lb_I_GUIApplication::_callback(...): Error, have no instance for a wrapped object");
	return 0;
}
/*...e*/

/*...sLoad components:0:*/
int lb_I_GUIApplication::loadComponent(lb_I_GUIComponent* parent) {
	// Get an object type to be created. It's a string
	if (client == NULL) {
		LOG("lb_I_GUIApplication::loadComponent(): Error, client connection not created");
		return 0;
	}

	lbStringList* elements;
	
	if (parent == NULL)
		elements = (lbStringList*) client->requestObject("GUI", "list components");
	else 
	/**
	 * parent is currently an instance everywhere and so having 
	 * a reverenceId. This is, because, the object still can be changed
	 * since it has been created.
	 *
	 */
		elements = (lbStringList*) client->requestObject("children", parent->getRefId());

	while (elements->hasMoreElements()) {
		lbString* componentName = elements->nextElement();
		lbString* typeName = (lbString*) client->requestObject("Componenttype", componentName->getData());
		
		// Create the object with help of the factory pattern
		lb_I_GUIComponent* component = lb_I_GUIComponent::factory(typeName->getData());

		setParent(component, parent);
	
		// Put the object in the container
		
		lb_GUIComponent c;
		
		c.setObject(component);
		
		LoadedComponents->insert(c, component->getKey());
		
		loadComponent(component);
		
		//delete component;
	}
	delete elements;
	
	return 0;
}
/*...e*/

/*...sLoad the application:0:*/
int lb_I_GUIApplication::Load() {
	char *user = NULL;
	char *passwd = NULL;
	// Reading the config file here for lb_I_GUIApplication
	
	// In turn of not having a config file and a tool for reading
	// it, define it hardcoded.
	
	lbString ApplicationName;
	ApplicationName.setData("Test");
	
	// Create the application bus if no object is created yet.
	// Behind, this object may encapsulate it self and using a singleton
	
	if (AppBusClient == NULL) AppBusClient = new lbAppBusClient();
	
/*...slogin:8:*/
	// Try three logins
	int count = 0;
        do {
		// Prepare callback
		
		lb_Transfer_Data needLoginData;
		lb_Transfer_Data result;
		
		// Set the data...
		
		
		// Retrieve user name and password
		callback(needLoginData, result);
		
	}
	while ((AnounceUser(user, passwd) == 0) &&
	       (count++ < 3));
/*...e*/

	// Get the needed application server
	
	// Create an instance of a client.
	//client = AppBusClient->factory("AppClient", ApplicationName);
	
	client = AppBusClient->getClientInstance(ApplicationName.getData());

	// Loop

	int result = loadComponent(NULL);
	
	AppBusClient->release(client);
	
	return 0;
}
/*...e*/

/*...slb_I_GUIApplication\58\\58\isFirstStart\40\\41\:0:*/
int lb_I_GUIApplication::isFirstStart() {
    return 0;
}
/*...e*/

/*...sComponent handling:0:*/
/*...slb_I_GUIApplication\58\\58\setParent\40\lb_I_GUIComponent\42\ const _this\44\ lb_I_GUIComponent\42\ const _parent\41\:0:*/
int lb_I_GUIApplication::setParent(lb_I_GUIComponent* const _this, lb_I_GUIComponent* const _parent) {
	return 1;
}
/*...e*/

/*...slb_I_GUIComponent\42\ lb_I_GUIApplication\58\\58\getParent\40\lb_I_GUIComponent\42\ from\41\:0:*/
lb_I_GUIComponent* lb_I_GUIApplication::getParent(lb_I_GUIComponent* from) {
	return NULL;
}
/*...e*/
    
/*...slbComponentDictionary\42\ lb_I_GUIApplication\58\\58\getChildrens\40\lb_I_GUIComponent\42\ from\41\:0:*/
lbComponentDictionary* lb_I_GUIApplication::getChildrens(lb_I_GUIComponent* from) {
	return NULL;
}
/*...e*/

/*...slbComponentDictionary\42\ lb_I_GUIApplication\58\\58\getChildrens\40\lb_I_GUIComponent\42\ from\44\ GUITypes type\41\:0:*/
lbComponentDictionary* lb_I_GUIApplication::getChildrens(lb_I_GUIComponent* from, GUITypes type) {
	return NULL;
}
/*...e*/

/*...sint lb_I_GUIApplication\58\\58\hasMoreComponents\40\\41\:0:*/
int lb_I_GUIApplication::hasMoreComponents() {
	return 0;
}
/*...e*/

/*...slb_I_GUIComponent\42\ lb_I_GUIApplication\58\\58\nextComponent\40\\41\:0:*/
lb_I_GUIComponent* lb_I_GUIApplication::nextComponent() {
	return NULL;
}
/*...e*/
/*...e*/
/*...e*/



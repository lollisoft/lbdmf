/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.2 $
 * $Name:  $
 * $Id: lb_i_gui.h,v 1.2 2000/04/27 01:36:05 lolli Exp $
 *
 * $Log: lb_i_gui.h,v $
 * Revision 1.2  2000/04/27 01:36:05  lolli
 * Commit in order of data GAU
 *
 * Revision 1.1  2000/03/05 17:14:13  lolli
 * Moved to AppDevelopment/GUI/wxGUI
 *
 * Revision 1.2  2000/01/18 21:14:14  lolli
 * Current version
 *
 * Revision 1.1  1999/11/25 21:00:00  lothar
 * Initial version
 *
 **************************************************************/
/*...e*/

#ifndef LB_I_GUIAPPLICATION
#define LB_I_GUIAPPLICATION

/*...sDLLEXPORT:0:*/
#undef DLLEXPORT

#ifdef LB_I_GUI_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef LB_I_GUI_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif
/*...e*/

#ifdef bla
/*...sComponentTypes:0:*/
enum ComponentTypes {
	GUI,		// 
	EVENTHANDLER,	// A GUI component can recieve events
	EVENTRAISER,	// This is an active component
};
/*...e*/

/*...sGUITypes:0:*/
enum GUITypes { 
	LB_MENUBAR, 
	LB_MENU, 
	LB_MENUENTRY, 
	LB_APP_TITLE
};
/*...e*/
#endif

class lbComponentDictionary;
class RemoteAppRes;
class lbAppBusClient;
class lb_I_wxGUIApplication;
class lb_I_GUIApplication;
class lb_I_GUIComponent;
class lb_Transfer_Data;


/*...sclass DLLEXPORT lb_I_GUIComponent:0:*/
class DLLEXPORT lb_I_GUIComponent {
public:
        lb_I_GUIComponent();
	virtual ~lb_I_GUIComponent();

	/**
	 * This function creates an instance of an object from this family.
	 * (Factory pattern)
	 */
	static lb_I_GUIComponent* factory(const char* typeName);

	lbKey getKey();
	
	/**
	 * An Id to the instance (anywhere)
	 */
	char* getRefId();

        GUITypes getType();

	int eventHandler(lb_Transfer_Data& request, lb_Transfer_Data& result);

protected:
        virtual void setType() = 0;
        GUITypes typ;

/*...sMarshalling:8:*/
	/**
	 * A component may have various parameters not known by
	 * an application. This parameters must be asked by the
	 * application. Implement a function that returns a list
	 * of parameters. This may be done with lb_Transfer_Data.
	 */
	 
	/**
	 * This can be used to create user interfaces for the data.
	 */ 
	virtual lb_Transfer_Data* getParameterInfo() = 0;
	
	/**
	 * Load the data.
	 */
	virtual int setParameters(lb_Transfer_Data* data) = 0; 
/*...e*/

/*...sParent and child handling:8:*/
	/**
	 * A Child is mostly created later than a parent. Then only
	 * this function is needed.
	 */
	 
	int setParent(lb_I_GUIComponent* const _parent); 

	/**
	 * A component can have a parent. Like a window, this is a basic
	 * functionality, needed by the real GUI interface implementation.
	 */
	lb_I_GUIComponent* getParent();
	
	/**
	 * This is also necesary for a normal GUI interface.
	 */
	lbComponentDictionary* getChildren();
/*...e*/

	/**
	 * Every component can create childs of a specific type.
	 * Implement with this prototype.
	 */
//	virtual lb_I_GUIComponent* createChildInstance() = 0;

//	void setName(lbString _name);
	
/*...sbla:0:*/
#ifdef bla
	/**
	 * This should not longer be here
	 */
	void setAppBusConnector(lbAppBusClient* client);

	/**
	 * A GUI component may have a parent component. If not, the component
	 * is owned by the wxGUIApplication.
	 */
	lb_I_GUIComponent* parent;

	lbComponentDictionary* childrens;
#endif
/*...e*/
        /**
         * Every component has a pointer to the main lb_I_wxGUIApplication 
         * instance. So every component can get the instance of the application
         * bus.
         */
         
        static lb_I_GUIApplication* GUIApplication;
        
        friend class lb_I_GUIApplication;
        
        
protected:
	lbString name;
	lbKey key;
};
/*...e*/

typedef int (lb_I_GUIComponent::*T_p_eventHandler)(lb_Transfer_Data& request, lb_Transfer_Data& result);


typedef struct __eventTableEntry {
	T_p_eventHandler eventFn(lb_Transfer_Data& request, lb_Transfer_Data& result);
} eventTableEntry, *peventTableEntry;

class lb_I_EventDispatcher;

/*...sclass lb_I_Event \58\ public lbObject:0:*/
class lb_I_Event : public lbObject {
	lb_I_Event();
	virtual ~lb_I_Event();

	virtual void setType();
	virtual lbObject* clone() const;

	int invoke(lb_Transfer_Data& request, lb_Transfer_Data& result);

protected:
	void set(lbKey& k, eventTableEntry& _ev);


	// Contains the pointer to the eventHandler function
	eventTableEntry ev;
	// The id generated from dispatcher
	lbKey* eventId;
	
	friend class lb_I_EventDispatcher;
};
/*...e*/

/*...sclass DLLEXPORT lb_I_EventDispatcher:0:*/
class DLLEXPORT lb_I_EventDispatcher {
	lb_I_EventDispatcher();
	virtual ~lb_I_EventDispatcher();
	
	int add(T_p_eventHandler eventFn);
	
	lbComponentDictionary eventTable;
	
};
/*...e*/

/*...sclass DLLEXPORT lb_I_Application:0:*/

class DLLEXPORT lb_I_Application {
public:
	lb_I_Application();
	virtual ~lb_I_Application();

	/**
	 * This cunction is called and will check, if the pointers are set
	 * correctly and if the calling instance's this pointer is stored
	 * in wrapped. Then it will be a correct call to a wrapper.
	 */
	int callback(lb_Transfer_Data& request, lb_Transfer_Data& result);

protected:
	virtual int _callback(lb_Transfer_Data&, lb_Transfer_Data&) = 0;

	lb_I_Application *wrapper;
	lb_I_Application *wrapped;
};
/*...e*/

/*...sclass DLLEXPORT lb_I_GUIApplication:0:*/
/**
 * The only class, who knows about component interactions. A component did
 * not know of any other components.
 */


class DLLEXPORT lb_I_GUIApplication : public lb_I_Application {
public:
    lb_I_GUIApplication();

    virtual ~lb_I_GUIApplication();

    int _callback(lb_Transfer_Data&, lb_Transfer_Data&);

    int isFirstStart();

    void InstallClient();

    /**
     * The main loader for an application. This function reads the 
     * configuration and then calls loadApplication()
     */
    int Load();
    
    /**
     * The name of the application.
     */
    char* getName();

    /**
     * setWrapperEventDispatcher tells this instance the event dispatcher
     * of the wrapper class. So this class can issue events to the wrapper.
     * Maybe there is a view, having changed a data item. Then it sets
     * the the changed flag in lb_I_EventDispatcher for its event.
     * The lb_I_EventDispatcher is the Observable class, knowing all objects
     * like to be informed of any change or some else event.
     */

    int setWrapperEventDispatcher(lb_I_EventDispatcher* evDisp);

/*...sComponent handling:0:*/
    lb_I_GUIComponent* getParent(lb_I_GUIComponent* from);
    
    /**
     * Get all childrens.
     */
    lbComponentDictionary* getChildrens(lb_I_GUIComponent* from);

    /**
     * Get all childs from this type
     */

    lbComponentDictionary* getChildrens(lb_I_GUIComponent* from, GUITypes type);

    /**
     * An application may have several components, wich it self may have subcomponents.
     * For an example, an application has a menu (a visual component).
     */
    int hasMoreComponents();
    lb_I_GUIComponent* nextComponent();

/*...e*/
/*...sComponent dependency handling:0:*/
    int setParent(lb_I_GUIComponent* const _this, lb_I_GUIComponent* const _parent);
/*...e*/

protected:

    int AnounceUser(char* _user, char* _passwd);
/*...sLoading and mapping:0:*/
    /**
     * This function makes the main work for loading the components for
     * this application. It needs a bootstrapping information to know
     * what to load. This must be configured anywhere.
     *
     * In the real GUI interface, you must call this function first.
     * Then you can create your instances of mapped GUI interface components.
     */

    int loadComponent(lb_I_GUIComponent* component);
    /**
     * This function enables a lookup of the object for the real GUI
     * interface. This is the only assotiazion of the pair of GUI
     * components.
     */
    int getMapId(lb_I_GUIComponent* from);
    /**
     * Use this function after loading with loadApplication() to map
     * each of your GUI component to the corresponding lb_I_GUIComponent
     */
    int setMapId(lb_I_GUIComponent* from, int Id);
/*...e*/

/*...sVars:0:*/
    char* title;
    int componentCount;

    static lbAppBusClient* AppBusClient;
    lbAppClient* client;

    /**
     * In this dictionary are the instantiated components stored. All
     * components can be loaded from the server (their data), but one
     * must be bootstrapped from the application.
     */
    lbComponentDictionary* LoadedComponents;


    /**
     * A wrapper like lb_I_wxGUIApplication holds its own dispatcher.
     * He must be known here.
     */
    lb_I_EventDispatcher* wrapper;
/*...e*/
};
/*...e*/

#endif // LB_I_GUIAPPLICATION


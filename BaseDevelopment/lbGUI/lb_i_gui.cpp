#define LB_I_GUI_DLL

/*...sInclude:0:*/
#include <appcs.h>

#include <string.h>
#include <lbObject.h>
#include <lbKey.h>

#include <lbContainer.h>

#include <lb_I_GUI.h>
#include <lb_misc.h>
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


lb_I_GUIComponent::lb_I_GUIComponent() {
}

lb_I_GUIComponent::~lb_I_GUIComponent() {
}

lb_I_GUIComponent::GUITypes lb_I_GUIComponent::getType() {
    return typ;
}

void lb_I_GUIComponent::setApplicationName(char *name) {
    forApplication = strdup(name);
}
/*...e*/

/*...slb_I_GUIMenuBar:0:*/
lb_I_GUIMenuBar::lb_I_GUIMenuBar() {
}

lb_I_GUIMenuBar::~lb_I_GUIMenuBar() {
}

void lb_I_GUIMenuBar::Setup(char* applicationName) {
LOGENABLE("lb_I_GUIMenuBar::Setup(char* applicationName)");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lb_I_GUIMenuBar::Setup(char* applicationName): Create instance lb_GUIComponent component;");
#endif
/*...e*/
	lb_GUIComponent component;

/*...sDoc:0:*/
	// For an application name exists one menubar

	// What did I really need here ?
	// I need an application server, that serve for several GUI components
	// Must I differ several component types ?
/*...e*/
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lb_I_GUIMenuBar::Setup(char* applicationName): Create instance lbAppClient AppClient;");
#endif
/*...e*/
	lbAppClient AppClient;

	// The application server need to know, for which application the connection is needed.
	AppClient.Connect(applicationName);

    // Is beginLoad really good?
    //TaskId tid = RemoteApp.beginLoad(); // IP stuff or other machine info is built by the local dispatcher

    // I am interested in getting a main menu. Here the result may be represented by a stringlist
	RemoteAppRes res = AppClient.requestObject("LB_MENUBAR");

    if (res.isError()) {
		LOG("There was an error");
        res.reportError();
    } else {
        // Here I got what I want. The MenuBar here should have &File and &Help

		// Is the resultname requested here (different menubars)?

		char *name = strdup(res.getResultName());
		delete[] name; // Savely yet

        for (int i = 1; i <= res.getEntries(); i++) { // Load the two menus
            /* An application contains a set of menus. All menus are pop up menus
             * so this code should work anyway.
             */

            lb_I_GUIMenu *menu = new lb_I_GUIMenu();
            menu->setName(res.getEntryName(i));
			LOG("lb_I_GUIMenu has now this name:");
			LOG(menu->getName());
			/**
			 * Now the menu should be loaded from the server (we have a name)
			 * Also we have a base request, on wich we rely.
			 * The base request given above, let us know which subsequent data
			 * is needed (here for the main menu the sub data for a single
			 * menu by name).
			 */
			//RemoteAppRes r_menuentry = AppClient.subObject(res, menu->getName());
			
			component.setObject(menu);
			Menus.insert(component, lbKey(i));
        }
    }
	AppClient.Disconnect();
	LOG("Disconnected from application server");
}

int lb_I_GUIMenuBar::hasMoreElements() {
    return Menus.hasMoreElements();
}

lb_I_GUIComponent* lb_I_GUIMenuBar::nextElement() {
        lb_GUIComponent *component;
        try {
                component = (lb_GUIComponent*) Menus.nextElement();
				if (component == NULL) LOG("Component in lb_I_GUIMenuBar is NULL");
        } catch (...) {
                LOG("In lb_I_GUI.cpp: Failed to get next menu element");
        }
        
        return component->getObject();
}

void lb_I_GUIMenuBar::setType() {
    typ = LB_MENUBAR;
}
/*...e*/

/*...slb_I_GUIMenu:0:*/
lb_I_GUIMenu::lb_I_GUIMenu() {
        name = NULL;
}

lb_I_GUIMenu::~lb_I_GUIMenu() {
}

void lb_I_GUIMenu::setType() {
    typ = LB_MENU;
}
        
lb_I_GUIMenu::GUITypes lb_I_GUIMenu::getType() {
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
/*...e*/

/*...slb_I_GUIApplication:0:*/
lb_I_GUIApplication::lb_I_GUIApplication() {
}

lb_I_GUIApplication::~lb_I_GUIApplication() {
}

int lb_I_GUIApplication::isFirstStart() {
    return 0;
}
/*...e*/



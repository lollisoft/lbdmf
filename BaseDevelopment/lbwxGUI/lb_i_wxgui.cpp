#define LB_I_WXGUI_DLL

/*...sInclude:0:*/
#include <string.h>
#include <stdlib.h>

#include <lb_misc.h>

#include <lbObject.h>
#include <lbKey.h>
#include <lbelement.h>
#include <lbContainer.h>

// Include base lb GUI interface
#include <lb_I_GUI.h>

// Include interface for wx library
#include <lb_I_wxGUI.h>
/*...e*/

/*...slb_wxComponent:0:*/
// Class, that holds a GUI component. An object of this class could be stored
// in lbComponentDictionary
class lb_wxComponent: public lbObject {
public:
        lb_wxComponent() {
			setType();
        }

		virtual ~lb_wxComponent() {
        }

		/**
		 * Implement the abstract functions
		 */
		void setType() { OTyp = LB_WXGUIOBJECT; }
		lbObject* clone() const {
			lb_wxComponent *c = new lb_wxComponent();
			c->setObject(theObject);
			return c;
		}

        void setObject(lb_I_wxGUIComponent* o) {
            theObject = o;
        }

        lb_I_wxGUIComponent* getObject() {
            return theObject;
        }

        lb_I_wxGUIComponent* theObject;    
};


lb_I_wxGUIComponent::lb_I_wxGUIComponent() {
}

lb_I_wxGUIComponent::~lb_I_wxGUIComponent() {
}

lb_I_wxGUIComponent::GUITypes lb_I_wxGUIComponent::getType() {
    return typ;
}

void lb_I_wxGUIComponent::setApplicationName(wxString name) {
    forApplication = name;
}
/*...e*/

/*...slb_I_wxMenuEntry:0:*/
lb_I_wxGUIMenuEntry::lb_I_wxGUIMenuEntry() {
    MenuId  = -1;
    MenuTxt = "";
    MenuHlp = "";
}

lb_I_wxGUIMenuEntry::~lb_I_wxGUIMenuEntry() {
}

void lb_I_wxGUIMenuEntry::setType() {
    typ = LB_MENUENTRY;
}

int lb_I_wxGUIMenuEntry::getId() {
    return MenuId;
}

wxString lb_I_wxGUIMenuEntry::getTxt() {
    return MenuTxt;
}

wxString lb_I_wxGUIMenuEntry::getHlp() {
    return MenuHlp;
}
/*...e*/

/*...slb_I_wxGUIMenu:0:*/
lb_I_wxGUIMenu::lb_I_wxGUIMenu(/*lb_I_GUIMenu& menu*/) {
	setType();
}

lb_I_wxGUIMenu::~lb_I_wxGUIMenu() {
}

void lb_I_wxGUIMenu::setType() {
    typ = LB_MENU;
}

wxMenu* lb_I_wxGUIMenu::getMenu(wxEvtHandler* evtHandle, wxObjectEventFunction func) {
    wxMenu* menu = new wxMenu("");

/*    

    evtHandle->Connect(1, -1, wxEVT_COMMAND_MENU_SELECTED,
                       (wxObjectEventFunction)
                       (wxEventFunction)
                       (wxCommandEventFunction) func );
    menuFile->Append(1, "E&xit", "Quit this program");
    menuBar->Append(menuFile, "&File");



    evtHandle->Connect(2, -1, wxEVT_COMMAND_MENU_SELECTED,
                       (wxObjectEventFunction)
                       (wxEventFunction)
                       (wxCommandEventFunction) func );

    menuHelp->Append(2, "&About...", "Show about dialog");

    evtHandle->Connect(3, -1, wxEVT_COMMAND_MENU_SELECTED,
                       (wxObjectEventFunction)
                       (wxEventFunction)
                       (wxCommandEventFunction) func );

    menuHelp->Append(3, "&Contents...", "Help Contents");

    menuBar->Append(menuHelp, "&Help");
*/


    //menu->Append(MenuId, MenuTxt, MenuHlp);

    return menu;
}

wxString lb_I_wxGUIMenu::getName() {
    return name;
}

void lb_I_wxGUIMenu::setName(wxString n) {
    name = n;
}
/*...e*/

/*...slb_I_wxGUIMenuBar:0:*/
/*...slb_I_wxGUIMenuBar\58\\58\lb_I_wxGUIMenuBar\40\wxString \38\applicationName\41\:0:*/
lb_I_wxGUIMenuBar::lb_I_wxGUIMenuBar(wxString &applicationName) {

    setType();
        
    lb_wxComponent aGUIElement;

    Menus = new lbComponentDictionary();

    //appName = applicationName;

    /**
     * The constructor loads automatically the menu.
     * This is done by invoking the lb_I_GUIMenubar.
     *
     * The GUIMenuBar then holds information of sub-
     * menus.
     */

    char* an = strdup(applicationName.GetData());

    lb_I_GUIMenuBar GUIMenuBar;

    char buf[100];

    sprintf(buf, "Setup GUIMenuBar for %s", an);
    LOG(buf);
    GUIMenuBar.Setup(an);
    LOG("GUIMenuBar setup complete");

    while (GUIMenuBar.hasMoreElements() == 1) {
        /**
         * A lb_I_GUIMenu holds the parent (menubar), a menu name and a list of menu entries.
         * 
         */
		lb_I_GUIMenu* menu = (lb_I_GUIMenu*) GUIMenuBar.nextElement();
/*...sVERBOSE:0:*/
#ifdef VERBOSE
		LOG("lb_I_GUIMenu in lb_I_wxGUIMenuBar::lb_I_wxGUIMenuBar has now this name:");
		LOG(menu->getName());
#endif
/*...e*/
        /**
         * Construct a wxGUI object from a GUI object.
         * This means mapping to a specific framework.
         */
		lb_I_wxGUIMenu* wx_menu = new lb_I_wxGUIMenu(/*menu*/);

		wx_menu->setName(wxString(menu->getName()));

        /**
         * Put this "submenu" to the list (lbComponentDictionary)
         */
        aGUIElement.setObject(wx_menu);

		/**
		 * We use here lb_wxComponent as a wrapper, that contains the real object
		 */

        char* cp = strdup(wx_menu->getName().GetData());

        lbStringKey key = lbStringKey(cp);

        Menus->insert(aGUIElement, key);

		lbObject *o = Menus->getElement(key);
    }
}
/*...e*/

lb_I_wxGUIMenuBar::~lb_I_wxGUIMenuBar() {
}

void lb_I_wxGUIMenuBar::setType() {
    typ = LB_MENUBAR;
}

wxMenuBar* lb_I_wxGUIMenuBar::getMenuBar(wxEvtHandler* evtHandle, wxObjectEventFunction func) {
    wxMenuBar *menuBar = new wxMenuBar;

    /**
     * In the constructor I fill the Menus list. Here I get out this
     * elements. This is done to be able to cache information on local
     * the machine. Later I can check a timestamp for the menubar and load
     * the local information instead (done in constructor).
     */
    while (Menus->hasMoreElements()) {
        lb_wxComponent* Element = (lb_wxComponent*) Menus->nextElement();

	if(Element == NULL) 
	{
	  LOG("lb_I_wxGUIMenuBar::getMenuBar(...) Element is NULL! Where a non NULL was excepted.");
	  break;
        }
               
        lb_I_wxGUIComponent* comp = Element->getObject();
                
        wxMenu* menu;

        if (comp->getType() == lb_I_wxGUIComponent::LB_MENU)
        {
		wxString menuName = ((lb_I_wxGUIMenu*) comp)->getName();
		wxString msg = wxString("lb_I_wxGUIMenuBar::getMenuBar(...) Add a menu to the menubar(") + menuName + wxString(")");
			
		LOG(msg.GetData());

/*...sOld code:0:*/
/*
    evtHandle->Connect(1, -1, wxEVT_COMMAND_MENU_SELECTED,
                       (wxObjectEventFunction)
                       (wxEventFunction)
                       (wxCommandEventFunction) func );
    menuFile->Append(1, "E&xit", "Quit this program");
    menuBar->Append(menuFile, "&File");

*/
/*...e*/
		menu = ((lb_I_wxGUIMenu*) comp)->getMenu(evtHandle, func);
		menuBar->Append(menu, menuName);
        }
        else
        {
            LOG("Error while creating the menu. Submenu type is not LB_MENU");
        }
    }
    return menuBar;
}
/*...e*/

/*...slb_I_wxGUIApplication:0:*/
lb_I_wxGUIApplication::lb_I_wxGUIApplication() {
    title = strdup("Generic wxGUIApp by Lothar Behrens");
    componentCount = 1;
}

lb_I_wxGUIApplication::~lb_I_wxGUIApplication() {
}

int lb_I_wxGUIApplication::isFirstStart() {
    return 0;
}

void lb_I_wxGUIApplication::InstallClient() {
}

char* lb_I_wxGUIApplication::getAppTitle() {
    return title;
}

/*
lb_I_wxGUIApplication::GUITypes lb_I_wxGUIApplication::getNext() {
    return GUITypes(LB_APP_TITLE);
}
*/

int lb_I_wxGUIApplication::hasMoreComponents() {
    return componentCount > 0;
}

lb_I_wxGUIComponent* lb_I_wxGUIApplication::nextComponent() {
    componentCount--;
    char* appname = strdup("Minimal");
/*...sNOT YET VERBOSE:0:*/
LOGENABLE("lb_I_wxGUIApplication::nextComponent()");
LOG("Create new lb_I_wxGUIMenuBar(wxString(appname));");
//LOGDISABLE("lb_I_wxGUIApplication::nextComponent()");
/*...e*/
    lb_I_wxGUIMenuBar *mb = new lb_I_wxGUIMenuBar(wxString(appname));
/*...sNOT YET VERBOSE:0:*/
LOG("Created");
/*...e*/

    /**
     * Construct a menubar as a sample. The name here should be from any
     * config file, loaded by the lb_I_GUIApplication. The menubar then
     * should be generated from remote information through the given name.
     */
    return mb;
}


wxMenu* lb_I_wxGUIApplication::loadMenu() {
    return NULL;
}
/*...e*/

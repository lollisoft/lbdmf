#define LB_I_WXGUI_DLL

/*...sInclude:0:*/
#include <string.h>
#include <stdlib.h>

#include <lbInclude.h>
#include <lbContainer.h>

// Include base lb GUI interface
#include <lb_I_GUI.h>

// Include interface for wx library
#include <lb_I_wxGUI.h>
/*...e*/

/*...sprivate classes:0:*/

/*...sclass DLLEXPORT lb_I_wxGUIMenuBar\58\ public lb_I_wxGUIComponent:0:*/
class DLLEXPORT lb_I_wxGUIMenuBar: public lb_I_wxGUIComponent {
public:
    lb_I_wxGUIMenuBar();
    virtual ~lb_I_wxGUIMenuBar();

// MenuBar specific
    wxMenuBar* getMenuBar(wxEvtHandler* evtHandle, wxObjectEventFunction func);

protected:
    void setType();

/*...sMarshalling:4:*/
	lb_Transfer_Data* getParameterInfo();
	int setParameters(lb_Transfer_Data* data);
/*...e*/
    

    // A list of  (File, View, Help...)
    lbComponentDictionary* Menus;
};
/*...e*/

/*...sclass DLLEXPORT lb_I_wxGUIMenu\58\ public lb_I_wxGUIComponent:0:*/
class DLLEXPORT lb_I_wxGUIMenu: public lb_I_wxGUIComponent {
public:
    lb_I_wxGUIMenu();
    virtual ~lb_I_wxGUIMenu();
        
    wxMenu* getMenu(wxEvtHandler* evtHandle, wxObjectEventFunction func);

    wxString getName();
    void setName(wxString n);

protected:
    void setType();

/*...sMarshalling:8:*/
	lb_Transfer_Data* getParameterInfo();
	int setParameters(lb_Transfer_Data* data);
/*...e*/

//    lbComponentDictionary* menuEntries;
    wxString name;
};
/*...e*/

/*...sclass DLLEXPORT lb_I_wxGUIMenuEntry\58\ public lb_I_wxGUIComponent:0:*/
class DLLEXPORT lb_I_wxGUIMenuEntry: public lb_I_wxGUIComponent {
public:
    lb_I_wxGUIMenuEntry();
    virtual ~lb_I_wxGUIMenuEntry();
        
    int getId();
    wxString getTxt();
    wxString getHlp();
    
    void setMenu(int id, wxString txt, wxString hlp);
protected:
    void setType();

/*...sMarshalling:8:*/
	lb_Transfer_Data* getParameterInfo();
	int setParameters(lb_Transfer_Data* data);
/*...e*/

    wxString MenuTxt;
    wxString MenuHlp;
    int MenuId;
};
/*...e*/
/*...e*/


lb_I_wxGUIApplication* wxAppBus;

/*...slb_wxComponent:0:*/
// Class, that holds a GUI component. An object of this class could be stored
// in lbComponentDictionary
/*...sclass lb_wxComponent\58\ public lbObject:0:*/
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
/*...e*/
/*...e*/

/*...slb_I_wxGUIComponent:0:*/
lb_I_wxGUIComponent::lb_I_wxGUIComponent() {
}

lb_I_wxGUIComponent::~lb_I_wxGUIComponent() {
}

static lb_I_wxGUIComponent* factory(const char* typeName) {
	LOGENABLE("lb_I_wxGUIComponent* factory(const char* typeName)");
	LOG("lb_I_wxGUIComponent* factory(const char* typeName): Error, not yet implemented");
	return NULL;
}

GUITypes lb_I_wxGUIComponent::getType() {
    return typ;
}
/*...e*/

/*...slb_I_wxMenuEntry:0:*/
lb_I_wxGUIMenuEntry::lb_I_wxGUIMenuEntry() {
}

lb_I_wxGUIMenuEntry::~lb_I_wxGUIMenuEntry() {
}

/*...sMarshalling:0:*/
lb_Transfer_Data* lb_I_wxGUIMenuEntry::getParameterInfo() {
	return NULL;
}
	
int lb_I_wxGUIMenuEntry::setParameters(lb_Transfer_Data* data) {
	return 1;
}
/*...e*/


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

/*...sMarshalling:0:*/
lb_Transfer_Data* lb_I_wxGUIMenu::getParameterInfo() {
	return NULL;
}
	
int lb_I_wxGUIMenu::setParameters(lb_Transfer_Data* data) {
	return 1;
}
/*...e*/


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
/*...slb_I_wxGUIMenuBar\58\\58\lb_I_wxGUIMenuBar\40\\41\:0:*/
lb_I_wxGUIMenuBar::lb_I_wxGUIMenuBar() {
/*...sBla:0:*/
#ifdef bla
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
#ifdef NOVERBOSE
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
#endif
/*...e*/
}
/*...e*/

lb_I_wxGUIMenuBar::~lb_I_wxGUIMenuBar() {
}

/*...sMarshalling:0:*/
lb_Transfer_Data* lb_I_wxGUIMenuBar::getParameterInfo() {
	return NULL;
}
	
int lb_I_wxGUIMenuBar::setParameters(lb_Transfer_Data* data) {
	return 1;
}
/*...e*/

void lb_I_wxGUIMenuBar::setType() {
    typ = LB_MENUBAR;
}

wxMenuBar* lb_I_wxGUIMenuBar::getMenuBar(wxEvtHandler* evtHandle, wxObjectEventFunction func) {
    wxMenuBar *menuBar = new wxMenuBar;

    return menuBar;
}
/*...e*/

/*...slb_I_wxGUIApplication:0:*/
lb_I_wxGUIApplication::lb_I_wxGUIApplication() {
    LOGENABLE("lb_I_wxGUIApplication::lb_I_wxGUIApplication()");



    componentCount = 1;
    components = new lbComponentDictionary();

    GUIApplication = new lb_I_GUIApplication();
}

lb_I_wxGUIApplication::~lb_I_wxGUIApplication() {
    if (components != NULL) components->deleteAll();
    if (GUIApplication != NULL) delete GUIApplication;
}

int lb_I_wxGUIApplication::_callback(lb_Transfer_Data&, lb_Transfer_Data&) {
	LOG("lb_I_wxGUIApplication::_callback(...): Error, have no instance for a wrapper");
	return 0;
}


/*...sComponent handling:0:*/
lb_I_wxGUIComponent* lb_I_wxGUIApplication::getParent(lb_I_wxGUIComponent* from) {
	return NULL;
}
    
lbComponentDictionary* lb_I_wxGUIApplication::getChildrens(lb_I_wxGUIComponent* from) {
	return NULL;
}

lbComponentDictionary* lb_I_wxGUIApplication::getChildrens(lb_I_wxGUIComponent* from, GUITypes type) {
	return NULL;
}

int lb_I_wxGUIApplication::hasMoreComponents() {
    return 0;
}

lb_I_wxGUIComponent* lb_I_wxGUIApplication::nextComponent() {
    return NULL;
}
/*...e*/
/*...sComponent dependency handling:0:*/
    int setParent(lb_I_wxGUIComponent* const _this, lb_I_wxGUIComponent* const _parent);
/*...e*/

int lb_I_wxGUIApplication::setDynEvHandler(wxEvtHandler* evtHandler, wxObjectEventFunction func) {
	/**
	 * Store the instance evtHandler and func in a set.
	 * Then I am able to add and remove event Id's during runtime.
	 */
	return 1;
}

const int lb_I_wxGUIApplication::getEvId(char* evName) const {
	return -1;
}

int lb_I_wxGUIApplication::Load() {
LOG("lb_I_wxGUIApplication::Load() called");

    /**
     * Normally the apptitle depends on a configuration file. If this
     * File does not exsist, the GUI can display a list of possible
     * applications, that are allowed to run on this host.
     */
    title = strdup("Generic wxGUIApp by Lothar Behrens");

	if (GUIApplication->Load() == 0) {
		LOG("lb_I_wxGUIApplication::Load(): Call to GUIApplication->Load() failed");
	}

	return 1;
}

int lb_I_wxGUIApplication::isFirstStart() {
    return 0;
}

void lb_I_wxGUIApplication::InstallClient() {
}

wxMenu* lb_I_wxGUIApplication::loadMenu() {
    return NULL;
}
/*...e*/

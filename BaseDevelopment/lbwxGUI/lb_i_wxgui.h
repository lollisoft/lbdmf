/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
            Rosmarinstr. 3
            
            40235 Duesseldorf (germany)
*/
/*...e*/
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.5 $
 * $Name:  $
 * $Id: lb_i_wxgui.h,v 1.5 2005/03/31 09:04:48 lollisoft Exp $
 *
 * $Log: lb_i_wxgui.h,v $
 * Revision 1.5  2005/03/31 09:04:48  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.4  2003/12/13 10:56:26  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.3  2000/06/24 21:32:12  lolli
 * Socket bugfix
 *
 * Revision 1.2  2000/04/27 01:36:06  lolli
 * Commit in order of data GAU
 *
 * Revision 1.1  2000/03/05 17:14:14  lolli
 * Moved to AppDevelopment/GUI/wxGUI
 *
 * Revision 1.3  2000/01/23 15:15:47  lolli
 * Corrected revision conflict
 *
 * Revision 1.1  1999/11/25 21:00:00  lothar
 * Initial version
 *
 **************************************************************/
/*...e*/


#ifndef LB_I_WXGUIAPPLICATION
#define LB_I_WXGUIAPPLICATION

#include <lb_I_GUI.h>

/*...sDLLEXPORT:0:*/
#undef DLLEXPORT

#ifdef LB_I_WXGUI_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef LB_I_WXGUI_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif
/*...e*/

/*...swxWindows stuff:0:*/
// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
#ifdef __GNUG__
    #pragma implementation "minimal.cpp"
    #pragma interface "minimal.cpp"
#endif


// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// ressources
// ----------------------------------------------------------------------------
// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "mondrian.xpm"
#endif
/*...e*/



class wxMenu;
class wxMenuBar;
class wxEvtHandler;
class lb_I_GUIApplication;
class lb_I_wxGUIApplication;
class lb_Transfer_Data;

/*...sclass DLLEXPORT lb_I_wxGUIComponent:0:*/
class DLLEXPORT lb_I_wxGUIComponent : public lb_I_GUIComponent {
public:
        lb_I_wxGUIComponent();
	virtual ~lb_I_wxGUIComponent();

        GUITypes getType();

	static lb_I_wxGUIComponent* factory(const char* typeName);
	
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
	 
	int setParent(lb_I_wxGUIComponent* const _parent); 

	/**
	 * A component can have a parent. Like a window, this is a basic
	 * functionality, needed by the real GUI interface implementation.
	 */
	lb_I_wxGUIComponent* getParent();
	
	/**
	 * This is also necesary for a normal GUI interface.
	 */
	lbComponentDictionary* getChildren();
/*...e*/

        /**
         * Every component has a pointer to the main lb_I_wxGUIApplication 
         * instance. So every component can get the instance of the application
         * bus.
         */


	/**
	 * All the parent and child handling is mapped over wxGUIApplication
	 */         
        static lb_I_wxGUIApplication* wxGUIApplication;
        
        friend class lb_I_wxGUIApplication;
};
/*...e*/
#ifdef bla
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
#endif
/*...sclass DLLEXPORT lb_I_wxGUIApplication:0:*/
class DLLEXPORT lb_I_wxGUIApplication : public lb_I_Application {
public:
    lb_I_wxGUIApplication();
    virtual ~lb_I_wxGUIApplication();


    int isFirstStart();

    void InstallClient();

    /**
     * The main loader for an application
     */
    int Load();

    /**
     * Set the handler to a member for handling the callback
     */
    int setDynEvHandler(wxEvtHandler* evtHandler, wxObjectEventFunction func);

    const int getEvId(char* evName) const;

    /**
     * Callback for lb_I_GUIApplication
     */
    
    wxMenu* loadMenu();

/*...sComponent handling:0:*/
    lb_I_wxGUIComponent* getParent(lb_I_wxGUIComponent* from);
    
    /**
     * Get all childrens.
     */
    lbComponentDictionary* getChildrens(lb_I_wxGUIComponent* from);

    /**
     * Get all childs from this type
     */

    lbComponentDictionary* getChildrens(lb_I_wxGUIComponent* from, GUITypes type);

    /**
     * An application may have several components, wich it self may have subcomponents.
     * For an example, an application has a menu (a visual component).
     */
    int hasMoreComponents();
    lb_I_wxGUIComponent* nextComponent();

/*...e*/
/*...sComponent dependency handling:0:*/
    int setParent(lb_I_wxGUIComponent* const _this, lb_I_wxGUIComponent* const _parent);
/*...e*/


protected:    

    int _callback(lb_Transfer_Data&, lb_Transfer_Data&);

/*...svars:0:*/
    char* title;
    int componentCount;
    
    /**
     * In this container I store the wxGUI components with an associated
     * Id as the key.
     */
    lbComponentDictionary* components;

    lb_I_GUIApplication* GUIApplication;
    
    /**
     * Handler for all callback events.
     */
    wxObjectEventFunction m_fn;
/*...e*/
};
/*...e*/

#endif // LB_I_WXGUIAPPLICATION

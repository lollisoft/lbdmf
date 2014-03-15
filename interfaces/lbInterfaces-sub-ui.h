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

#ifndef __LB_INTERFACES_SUB_UI__
#define __LB_INTERFACES_SUB_UI__

/** \brief Base class for all windows and controls.
 *
 * This is an attempt to have an universal base interface for all windows like it
 * is in wxWidgets and other frameworks.
 */
class lb_I_Window : public lb_I_Unknown
{
public:	
	virtual void LB_STDCALL create(int parentId) = 0;
	virtual int  LB_STDCALL getId() = 0;
	virtual void LB_STDCALL windowIsClosing(lb_I_Window* w) = 0;
};

/*...sclass lb_I_Form:0:*/
/**
 * \brief Base for formulars.
 *
 * This class enables you to create formulars with any layout caractaristics.
 */
class lb_I_Form : 
	public lb_I_Window, 
	public lb_I_EventHandler {
public:
	/** \brief Initialize the form.
	 *
	 */
	virtual void LB_STDCALL init() = 0;
		
	
	/** \brief Set the name of the form
	 *
	 */
	virtual lbErrCodes LB_STDCALL setName(const char* name, const char* appention = NULL) = 0;

		
	/** \brief Get the original name.
	 * The original name is that name, that was used in name of setName.
	 */
	virtual char* LB_STDCALL getName() = 0;
		
	/** \brief Add a button
	 *
	 * Add a new button at the given position and size.
	 */
	virtual lbErrCodes LB_STDCALL addButton(const char* buttonText, const char* evHandler, int x, int y, int w, int h) = 0;
	
	/** \brief Add a label
	 *
	 * Add a new label at the given position and size.
	 */
	virtual lbErrCodes LB_STDCALL addLabel(const char* text, int x, int y, int w, int h) = 0;
	
	/** \brief Add a text field
	 *
	 * Add a new text field at the given position and size.
	 */
	virtual lbErrCodes LB_STDCALL addTextField(const char* name, int x, int y, int w, int h) = 0;
	
	/** \brief Add an ownerdrawn control
	 *
	 * Add a new ownerdrawn control at the given position and size.
	 *
	 * This aims to draw various symbols or drawings based on an interpreted language.
	 */
	virtual lbErrCodes LB_STDCALL addOwnerDrawn(const char* name, int x, int y, int w, int h) = 0;

	virtual void LB_STDCALL show() = 0;
	virtual void LB_STDCALL destroy() = 0;
	
	virtual char* LB_STDCALL getFormName() = 0;
};
/*...e*/
class lb_I_GUIApp {

};
/*...sclass lb_I_GUI:0:*/
/**
 * It seems, that this is the factory class for any GUI elements. It also knows about any instance.
 */
class lb_I_GUI :
public lb_I_Unknown
{
public:
	
/*...sCreation functions:8:*/
	/*
	 * Creation functions
	 */
	 
	/**
	 * Let the GUI implementation create a frame.
	 */ 
	virtual lb_I_Unknown* LB_STDCALL createFrame() = 0;
	
	/**
	 * Let the GUI implementation create a menu.
	 */
	virtual lb_I_Unknown* LB_STDCALL createMenu() = 0;
	
	/**
	 * Let the GUI implementation create a menu bar.
	 */
	virtual lb_I_Unknown* LB_STDCALL createMenuBar() = 0;
	
	/**
	 * Let the GUI implementation create a menu entry.
	 */
	virtual lb_I_Unknown* LB_STDCALL createMenuEntry() = 0;

	
	/**
	 * This function creates a database dialog for the given query.
	 *
	 * \param formName Is the name for the form.
	 * \param queryString Is the SQL query whose data should be displayed for modification.
	 */
	virtual lb_I_DatabaseForm* LB_STDCALL createDBForm(const char* formName, const char* queryString, const char* DBName, const char* DBUser, const char* DBPass) = 0;

	/** \brief Register a form.
	 *
	 * This function must be used to register a database form, that has not been created
	 * by an instance of this interface.
	 *
	 * It will be used in the master detail form implementations. 
	 */
	virtual void LB_STDCALL registerDBForm(const char* formName, lb_I_DatabaseForm* form) = 0;

	virtual lb_I_Form* LB_STDCALL createLoginForm() = 0;
/*...e*/
/*...sGetter functions:8:*/
	/**
	 * Returns the main frame for the GUI application.
	 */
	 
	virtual lb_I_Unknown* LB_STDCALL getFrame() = 0; 
/*...e*/
/*...sMenu manipulation:8:*/
	/**
	 * Disable a menuentry at the current position.
	 * The position is reached by using gotoMenuEntry.
	 */
	virtual lbErrCodes LB_STDCALL deactivateMenuEntry() = 0;
	
	/**
	 * Enable a menuentry at the current position.
	 * The position is reached by using gotoMenuEntry.
	 */
	virtual lbErrCodes LB_STDCALL activateMenuEntry() = 0;

	/**
	 * This enables the manipulation of any manin menu entries and the addition of
	 * main menus.
	 */	
	virtual lbErrCodes LB_STDCALL gotoMenuRoot() = 0;
	
	/**
	 * Go to any menu entry, to manipulate at this position.
	 */
	virtual lbErrCodes LB_STDCALL gotoMenuEntry(const char* entry) = 0;
	
	/**
	 * Insert a menu instance after the current position.
	 */
	virtual lbErrCodes LB_STDCALL insertMenuEntry(lb_I_Unknown* entry) = 0;
	
	/**
	 * Add an entry at the current position (insert before)
	 */
	virtual lbErrCodes LB_STDCALL addMenuEntry(lb_I_Unknown* entry) = 0; 
/*...e*/



/*...sDocs:0:*/
/*
 * This will fasten up the current sample. It is not really needed to use
 * parameter based dispatching, if the target GUI interface provides the desired
 * functionality.
 *
 * So here, the GUI interface should provide some primitives handling code in its
 * interface.
 * 
 * These are buttons, labels, textfields, menus and so on.
 *
 * The handling code should include creation, removement, hiding and so on.
 */
/*...e*/

/*...sfunctions that had been implemented in metaapplication:0:*/

	/* The menubar is still present in the demo. At the
	   first time, a new menubar should not be used.
	*/

	/**
	 * Add a menu bar to the main menu with the given name.
	 */
	virtual lbErrCodes LB_STDCALL addMenuBar(const char* name) = 0;

	/**
	 * Add a menu behind the last.
	 */
	virtual lbErrCodes LB_STDCALL addMenu(const char* name) = 0;
	
	/**
	 * Add a menu entry in the named menu after given entry,
	 * if provided. The handler must be registered.
	 * 
	 * 
	 * \param  in_menu Which menu to add to (File/Edit/Help/...)
	 * \param  entry The text for that entry
	 * \param  evHandler The name of a registered event handler, that handle this
	 * \param  afterentry Insert the entry after an exsisting entry
	 */
	virtual lbErrCodes LB_STDCALL addMenuEntry(const char* in_menu, const char* entry, const char* evHandler, const char* afterentry = NULL) = 0;
/*...e*/



	
	/**
	 * Let the GUI server show a dialog box.
	 * This would be the simplest way to show informations to the user.
	 */
	virtual lbErrCodes LB_STDCALL msgBox(const char* windowTitle, const char* msg) = 0;

	/**
	 * We do not implement a dispatcher here, but we need one.
	 */
	virtual lbErrCodes LB_STDCALL setDispatcher(lb_I_Dispatcher* disp) = 0;	
	
	/**
	 * \brief Find any dynamic database window.
	 *
	 * This function finds any dynamic database window by their name.
	 */
	virtual lb_I_DatabaseForm* LB_STDCALL findDBForm(const char* name) = 0;
	
	/**
	 * \brief Find any custom database window.
	 *
	 * This function finds any custom database window by their name.
	 */
	virtual lb_I_FixedDatabaseForm* LB_STDCALL findCustomDBForm(const char* name) = 0;
	
	/**
	 * \brief Show form with given name.
	 */
	virtual void LB_STDCALL showForm(const char* name) = 0;
	
	/** \brief Set the app's icon.
	 */
	virtual void LB_STDCALL setIcon(const char* name) = 0;
	
	/** \brief Add an existing instance of a formular.
	 * Expected is a panel based formular, that could be placed into a notebook like
	 * control or in a dialog based control.
	 */
	virtual lb_I_Form* LB_STDCALL addCustomForm(lb_I_Form* form, const char* formName) = 0;
	
	virtual void LB_STDCALL closeCurrentPage() = 0;
	
	/** \brief To get informed, when the splash closes.
	 */
	virtual void LB_STDCALL splashDestroyed() = 0;
	
	/** \brief A splash is shown.
	 */
	virtual void LB_STDCALL splashCreated() = 0;

	virtual void LB_STDCALL showPendingMessages() = 0;
	
	virtual void LB_STDCALL refreshAll() = 0;

	virtual lbErrCodes LB_STDCALL openWebPage(const char* pagename, const char* url) = 0;
};
/*...e*/
/*...sclass lb_I_wxGUI:0:*/
class lb_I_wxGUI : public lb_I_GUI {
public:
};
/*...e*/

/** \brief Base class for a control.
 *
 */
class lb_I_Control : public lb_I_Window
{
public:
	/** \brief Initialize the control.
	 *
	 * The control must know its parent window.
	 */
	virtual void LB_STDCALL init(lb_I_Window* parent) = 0;
};

class lb_I_LogonPage {

};

class lb_I_AppSelectPage {

};

class lb_I_LogonHandler {

};

#endif // __LB_INTERFACES_SUB_WXWRAPPER__

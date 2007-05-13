// used for documentation

#ifdef LB_I_EXTENTIONS
#undef LB_I_EXTENTIONS
#define LB_I_EXTENTIONS
#endif

/*...sCopyright notice:0:*/
// Orginal version:
/////////////////////////////////////////////////////////////////////////////
// Name:        dynamic.cpp
// Purpose:     Dynamic events wxWindows sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: dynamic.cpp,v 1.135 2007/05/13 20:30:54 lollisoft Exp $
// Copyright:   (c) Julian Smart and Markus Holzem
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

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
/*...e*/
/*...sHistory:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.135 $
 * $Name:  $
 * $Id: dynamic.cpp,v 1.135 2007/05/13 20:30:54 lollisoft Exp $
 *
 * $Log: dynamic.cpp,v $
 * Revision 1.135  2007/05/13 20:30:54  lollisoft
 * First (partly) working XML export.
 *
 * Revision 1.134  2007/05/11 21:21:02  lollisoft
 * Linux compiler is more restrictive with const char*
 *
 * Revision 1.133  2007/05/01 16:07:41  lollisoft
 * Added code to show left property bar.
 *
 * Revision 1.132  2007/04/22 13:55:43  lollisoft
 * Mainlz added a spash screen.
 *
 * Revision 1.131  2007/02/28 19:24:30  lollisoft
 * New plugin compiles under Mac OS X.
 *
 * Revision 1.130  2007/02/09 21:35:51  lollisoft
 * Implemented remaining stuff for basic toolbar support.
 * But these seems not to show the bitmap on Mac OS X.
 *
 * Revision 1.129  2007/01/29 20:12:59  lollisoft
 * Checkin for Linux.
 *
 * Revision 1.128  2006/12/31 11:24:25  lollisoft
 * Bugfix in the order of meta application initialisation.
 *
 * Revision 1.127  2006/12/23 15:42:43  lollisoft
 * Many changes to get a more stable release. Still having problems with database updates on foreign keys.
 *
 * Revision 1.126  2006/12/10 17:05:24  lollisoft
 * Other changes under Mac OS X.
 *
 * Revision 1.125  2006/10/22 18:34:36  lollisoft
 * Many memory leaks resolved, but they were caused by small errors :-(
 * This is also a sync.
 *
 * Revision 1.124  2006/07/02 13:39:16  lollisoft
 * Minor change (PM).
 *
 * Revision 1.123  2006/06/10 09:54:49  lollisoft
 * Removed outside saving structure code for meta application.
 * This is now done by the new save method.
 *
 * Revision 1.122  2006/06/03 06:16:58  lollisoft
 * Changes against new Datamodel classes.
 * These are used instead spread SQL commands.
 *
 * Currently, the SQL commands are for fallback issues,
 * if there is no data in the config files.
 *
 * Later the planned fallback SQL commands are replaced by
 * a controlled visitor operation.
 *
 * Work is in process.
 *
 * Revision 1.121  2006/05/07 07:06:54  lollisoft
 * Return an empty string on file dialog canceling.
 *
 * Revision 1.120  2006/03/28 11:38:58  lollisoft
 * Renamed Initialize to initialize and call unloadApplication in OnExit() for better unloading of the application.
 *
 * Revision 1.119  2006/03/24 17:14:21  lollisoft
 * Added GUI state for maximized or not.
 *
 * Revision 1.118  2006/03/09 08:59:41  lollisoft
 * Catch plugin failures while saving application data.
 *
 * Revision 1.117  2006/02/21 21:02:16  lollisoft
 * Wrong menu check handling.
 *
 * Revision 1.116  2006/02/21 19:35:51  lollisoft
 * Implemented autoload mechanism of last loaded application.
 * It demonstrates the new capabilities operating with files.
 *
 * Revision 1.115  2006/02/16 16:14:38  lollisoft
 * Small changes to let wxAUI based layout compile under Windows.
 *
 * Revision 1.114  2006/02/06 14:49:41  lollisoft
 * Try to implement left panel using wxPropertyGrid
 *
 * Revision 1.113  2006/02/04 18:14:58  lollisoft
 * Adaptions to Linux
 *
 * Revision 1.112  2006/02/04 11:15:55  lollisoft
 * Changed wxFrame class structure and added support for splitter windows.
 *
 * Revision 1.111  2006/01/30 15:54:15  lollisoft
 * Removed the __FILE__ and __LINE__ parameter usage in UAP and QI.
 * This was an unnessesary thing and makes programming easier.
 *
 * Revision 1.110  2006/01/30 06:24:59  lollisoft
 * Added preparation for splitter windows and renamed neutral handler names.
 *
 * Revision 1.109  2006/01/26 14:09:10  lollisoft
 * Added event en/disable and toggle event handlers. Also added askYesNo handler.
 *
 * Revision 1.108  2006/01/22 17:26:18  lollisoft
 * Several changes as of new types and tests of them.
 *
 * Revision 1.107  2005/12/09 15:57:58  lollisoft
 * Things work more properly under Mac OS X.
 *
 * Added stristr member function in lb_I_String.
 * Added setWhereClause/addWhereClause in lb_I_Query.
 *
 * All that needed to fix a bug in master / detail forms on
 * SQL queries with order by clauses.
 *
 * Revision 1.106  2005/12/07 23:43:08  lollisoft
 * Small changes that let also not crash the app at exit under
 * Mac OS X. But there is still a problem with creating first
 * data entries in a table.
 *
 * Revision 1.105  2005/12/07 11:41:23  lollisoft
 * Linux handles unloading modules correctly - for now.
 *
 * Handling this behaviour without positioning the loading of the modules
 * is still a TODO, if it ever is possible.
 *
 * Revision 1.104  2005/12/06 15:54:56  lollisoft
 * Changes let the GUI work properly in debug mode. But there is a NULL
 * pointer exeption in release mode near opening a database form.
 *
 * Testing on Mac OS X and Linux.
 *
 * Revision 1.103  2005/11/26 18:59:11  lollisoft
 * Minor changes to compile and run under Linux
 *
 * Revision 1.102  2005/11/18 23:41:32  lollisoft
 * More memory leaks have been fixed. There are currently less than 200
 * chunks unfreed, wich may be located in the plugin mechanism.
 *
 * Revision 1.101  2005/11/11 22:51:30  lollisoft
 * Memory leaks removed. There are currently only 4 chunks leaky.
 * These may be false positives, because one of them is an allocated
 * wxMenu instance, I have not to delete after adding it to a wxMenuBar.
 * wxMenuBar gets an owner (see wxWidgets documentation).
 *
 * Revision 1.100  2005/11/06 19:47:22  lollisoft
 * There was a problem with other UAP based instances in the main application.\nMoved the unhookAll() call to a destructor in a static instance in the main application file.
 *
 * Revision 1.99  2005/11/06 19:25:34  lollisoft
 * All bugs of unloading shared libraries removed.\nUsing dlopen more than once per shared library leads into unability to unload that library.\nMac OS X seems to not properly handle the reference counting, thus unloading of twice loaded shared libs fails.\n\nI have implemented a workaround to handle this properly.\n\nThere is one exeption: lbModule.so is needed by UAP macros, thus this shared library is left loaded and the system can unload it for me.
 *
 * Revision 1.98  2005/10/31 19:37:55  lollisoft
 * This version compiles and ends without a crash at exit. I have added a simple
 * string class to store places of queryInterface calls and setModuleManager calls.
 * This may change the layout to let the application not crash at exit.
 *
 * Revision 1.97  2005/10/31 15:13:32  lollisoft
 * Using unload function. But the cleanup doesn't work yet. There is a crash in
 * some system functions after unloading lbDB DLL. Not used now.
 *
 * Revision 1.96  2005/10/26 06:07:19  lollisoft
 * Commit due to checks of crashes on OS X and Linux.
 *
 * Revision 1.95  2005/10/05 11:04:39  lollisoft
 * Report login failures due to missing database or correct ODBC configuration
 * of it.
 *
 * Revision 1.94  2005/10/02 17:10:09  lollisoft
 * Removed console output under Windows.
 *
 * Revision 1.93  2005/10/02 16:51:48  lollisoft
 * New wxNotebook layout completed. Not yet changeable at runtime, but it works.
 *
 * Revision 1.92  2005/10/01 10:12:12  lollisoft
 * Added functions for layout modes.
 *
 * Revision 1.91  2005/09/11 19:07:48  lollisoft
 * Missing registerDBForm when compiled without wxWrapperDLL.
 *
 * Revision 1.90  2005/09/11 06:27:29  lollisoft
 * Precomp problems.
 *
 * Revision 1.89  2005/09/07 20:46:34  lollisoft
 * Minor changes due to wxWidgets 2.6.1 usage under Windows.
 *
 * Revision 1.88  2005/08/28 11:01:55  lollisoft
 * Changed the lb_I_GUI implementation not to show the created form.
 * Form will be returned now.
 *
 * Revision 1.87  2005/08/22 16:35:10  lollisoft
 * Wrong conditional compiling.
 *
 * Revision 1.86  2005/08/21 23:23:53  lollisoft
 * Moving code to wxWrapper DLL/so module.
 *
 * Revision 1.85  2005/08/12 15:44:08  lollisoft
 * Removed log messages.
 *
 * Revision 1.84  2005/08/05 19:54:59  lollisoft
 * Removed verbosity.
 *
 * Revision 1.83  2005/06/30 07:28:55  lollisoft
 * Added a static text to the application selector.
 *
 * Revision 1.82  2005/06/28 15:50:07  lollisoft
 * Better layout of application selector.
 *
 * Revision 1.81  2005/06/25 12:44:16  lollisoft
 * Changed wxComboBox to wxChoice.
 *
 * Revision 1.80  2005/06/24 23:09:51  lollisoft
 * Changes to build with new wxWidgets version 2.6.1.
 * Added fallback to hardcoded settings, if no environment
 * variables are found. Logging changed to reside in a
 * $(HOME)/log directory.
 *
 * GUI application build process enhanced to also make the
 * bundle. App runs from clicking on the desktop icon.
 *
 * Revision 1.79  2005/06/21 14:36:33  lollisoft
 * Missed event table declaration for page changing event.
 *
 * Revision 1.78  2005/06/20 11:21:42  lollisoft
 * Added feature for skipping login wizard. Added findDBForm to get master
 * form instances.
 *
 * Revision 1.77  2005/06/09 07:27:47  lollisoft
 * Allow reopen the form if SQL query has been changed.
 *
 * Revision 1.76  2005/06/01 11:03:06  lollisoft
 * Program exit works now.
 *
 * Revision 1.75  2005/05/26 08:30:12  lollisoft
 * Removed usage of DEBUG_UAP and added some more log messages
 * due to crashes under Windows (at exit).
 *
 * Revision 1.74  2005/05/17 22:59:19  lollisoft
 * Bugfix in reference counting.
 *
 * Storing windows in a selfdeleting (UAP) container would
 * crash. This has been overcome since the bugfix for the
 * containers self has been taken.
 *
 * The wxWidgets controls or windows are not reference
 * counted, or have its own one. So they should not be stored
 * simply in a container of my framework.
 *
 * Special reference increment is done for the specific dialogs.
 *
 * Revision 1.73  2005/05/15 19:27:03  lollisoft
 * Catch a bug. If an event could not resolved, it could not
 * added as an menu entry.
 *
 * Revision 1.72  2005/05/11 13:19:40  lollisoft
 * Bugfix for reference count error and changed back any _CL_LOG messages to be _CL_VERBOSE only
 *
 * Revision 1.71  2005/05/01 21:34:12  lollisoft
 * Added informative filename to show when printing memory leaks.
 * Deactivated FreeConsole for memory tests.
 *
 * Thanks to the trmem code from Open Watcom.
 *
 * Revision 1.70  2005/04/28 10:20:19  lollisoft
 * Made password field hide characters.
 *
 * Revision 1.69  2005/04/28 09:46:30  lollisoft
 * Some changes under Linux to built correctly
 *
 * Revision 1.68  2005/04/28 07:25:56  lollisoft
 * Freeing console problem solved.
 *
 * Revision 1.67  2005/04/18 19:01:59  lollisoft
 * Changes due to interface changings in lb_I_Form and lb_I_DatabaseForm.
 *
 * Revision 1.66  2005/04/03 22:10:08  lollisoft
 * Form gets destroyed and - so - self deleted. UAP is not really needed.
 *
 * Revision 1.65  2005/04/02 12:49:56  lollisoft
 * More translations
 *
 * Revision 1.64  2005/04/02 09:45:06  lollisoft
 * Removed log messages and little code changes.
 *
 * Revision 1.63  2005/03/31 15:21:00  lollisoft
 * Reporting name of menu to append after
 *
 * Revision 1.62  2005/03/31 14:42:51  lollisoft
 * Changes to get menubar appending to work
 *
 * Revision 1.61  2005/03/31 09:22:03  lollisoft
 * Copyright text problems under linux.
 * Bugfix while calling _trans in function parameter twice.
 *
 * Revision 1.60  2005/03/19 16:44:05  lollisoft
 * Implemented i18n. Removed unused code.
 *
 * Revision 1.59  2005/03/15 22:26:50  lollisoft
 * More changes on OSX to compile plugins
 *
 * Revision 1.58  2005/03/15 20:52:29  lollisoft
 * Removed from now on unused code.
 *
 * Revision 1.57  2005/03/15 14:43:52  lollisoft
 * Changes for linux to build and let GUI running with plugins
 *
 * Revision 1.56  2005/03/14 18:59:03  lollisoft
 * Various changes and additions to make plugins also work with database forms
 *
 * Revision 1.55  2005/03/10 09:02:34  lollisoft
 * Plugin code complete until real loading.
 *
 * Revision 1.54  2005/03/07 20:27:25  lollisoft
 * Minor compile problem fixed due to Linux changes
 *
 * Revision 1.53  2005/03/07 20:09:34  lollisoft
 * Minor changes to compile under Linux
 *
 * Revision 1.52  2005/03/07 19:30:22  lollisoft
 * Changes to again build correctly under linux
 *
 * Revision 1.51  2005/03/05 23:13:33  lollisoft
 * More changes to build source tree under Mac OS X
 *
 * Revision 1.50  2005/03/03 08:42:21  lollisoft
 * Added loading of plugins.
 *
 * Revision 1.49  2005/03/02 20:02:47  lollisoft
 * Now using DLL version of wxWidgets library
 *
 * Revision 1.48  2005/02/20 18:01:23  lollisoft
 * Bugfix due to buffer overflow affecting GUI sample under Linux
 *
 * Revision 1.47  2005/02/20 09:38:44  lollisoft
 * Removed unneeded menu entries.
 *
 * Revision 1.46  2005/02/14 16:37:14  lollisoft
 * Much tries to get foreign key handling work under linux. But there might be some magic bugs, that don't let them use
 *
 * Revision 1.45  2005/02/12 15:56:27  lollisoft
 * Changed SQL queries and enabled user and password settings via
 * environment.
 *
 * Revision 1.44  2005/02/10 19:16:23  lollisoft
 * Begun with new database types, removed messages
 *
 * Revision 1.43  2005/02/02 13:30:30  lollisoft
 * Latest changes for version 0.4.1
 *
 * Revision 1.42  2005/01/27 12:59:11  lollisoft
 * Changed logging messages and SQL query to not use " in it
 *
 * Revision 1.41  2005/01/25 12:52:56  lollisoft
 * Be only on linux verbose
 *
 * Revision 1.40  2005/01/25 12:28:35  lollisoft
 * Changes for linux due to several reasons. The GUI sample has still problems with database access. Crash in lbDB.cpp while creating bound columns. Console works
 *
 * Revision 1.39  2005/01/24 22:21:24  lollisoft
 * Changes on Linux to get database access running. Login and selecting / loading an application works. But the application would not load
 *
 * Revision 1.38  2005/01/23 17:30:56  lollisoft
 * Some problems under Linux
 *
 * Revision 1.37  2005/01/23 11:35:00  lollisoft
 * Now the code compiles under SuSE Linux 9.1 except wx. It has link problems
 *
 * Revision 1.36  2005/01/22 11:54:57  lollisoft
 * Removed log messages
 *
 * Revision 1.35  2005/01/05 13:40:02  lollisoft
 * New dynamic application implementation works
 *
 * Revision 1.34  2004/12/14 19:25:01  lollisoft
 * Change due to temporary variable differences in cleanup
 *
 * Revision 1.33  2004/12/14 16:13:17  lollisoft
 * Implemented a login wizard with application selection from database configuration.
 *
 * Revision 1.32  2004/11/16 19:49:57  lollisoft
 * Added much code to implement a login wizard
 *
 * Revision 1.31  2004/10/05 22:19:54  lollisoft
 * Corrected a bug in enabling/disabling the right buttons in the RIGHT windows.
 * Attention: There is a documented bugfix.
 *
 * Revision 1.30  2004/08/16 05:11:29  lollisoft
 * Better handling of database navigation.
 *
 * Revision 1.29  2004/08/10 18:23:45  lollisoft
 * Lesser logging messages and a try to disable database navigation buttons
 * if they are not needed.
 *
 * Revision 1.28  2004/08/03 22:01:10  lollisoft
 * Implemented adding of new data.
 *
 * Revision 1.27  2004/08/01 21:34:03  lollisoft
 * More documentation
 *
 * Revision 1.26  2004/07/31 15:51:38  lollisoft
 * Added doxygen formatted documentation.
 *
 * Revision 1.25  2004/07/28 20:45:51  lollisoft
 * Added add and delete handlers, but doesn't work due to incomplete lbDB
 * implementation.
 *
 * Revision 1.24  2004/07/26 22:00:40  lollisoft
 * Better layout and resizeable database form
 *
 * Revision 1.23  2004/07/22 23:36:38  lollisoft
 * Different database forms now working. Cleanup handled correctly and
 * the app always quits correctly.
 *
 * Revision 1.22  2004/07/21 22:21:10  lollisoft
 * Hang on exit solved by providing lb_wxGUI instance to lb_wxFrame. The
 * frame then can cleanup on exit.
 *
 * Revision 1.21  2004/07/18 07:28:26  lollisoft
 * Now the database sample works also under linux. Some bugs solved and minor changes
 *
 * Revision 1.20  2004/07/17 22:25:37  lollisoft
 * GUI demo now works for one database form. I have still one problem: where
 * to cleanup the instances. The app stays running. You will see it at the cmd
 * promt. It doesn't reappear. Press CTRL+C.
 *
 **************************************************************/
/*...e*/
/*...smisc and includes:0:*/
#ifdef __GNUG__
#pragma implementation "dynamic.cpp"
#pragma interface "dynamic.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".

#ifdef WX_PRECOMP
#include <wx/wxprec.h>
#endif

/*...swx ifdef\39\s:0:*/
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifdef LB_I_EXTENTIONS
//#include <lbInterfaces.h>
#include <lbConfigHook.h>
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#if defined(__WXGTK__) || defined(__WXMOTIF__)
#include "mondrian.xpm"
#endif
/*...e*/

#include "wx/wizard.h"
#include "wx/splitter.h"
#include "wx/treectrl.h"
#include <wx/splash.h>
#include <wx/image.h>
/*...e*/

// ID for the menu commands
#define DYNAMIC_QUIT		1000
#define DYNAMIC_TEXT		1001
#define DYNAMIC_ABOUT		1002
#define DYNAMIC_BUILDMENU	1003
#define DYNAMIC_TEST1		1004
#define DYNAMIC_TEST2           1005
#define DYNAMIC_VERBOSE		1006

#ifdef USE_WXWRAPPER_DLL
#include "wx/propgrid/propgrid.h"
#include <wxWrapperDLL.h>
#endif
#ifdef OSX
    #include <dlfcn.h>
#endif

#ifndef USE_WXWRAPPER_DLL

class lb_wxGUI;

#ifdef LB_I_EXTENTIONS
/*...sclass lb_wxFrame:0:*/
/**
 * \brief This is the main frame implementation.
 *
 * It implements the main event handling interface via OnDispatch.
 */
class lb_wxFrame : 
		public wxFrame,
                public lb_I_wxFrame
{ 
public:
/*...sctors\47\dtors:8:*/
	/**
	 * Initialize a default application layout.
	 */
        lb_wxFrame():
        	wxFrame(NULL, -1, _trans("Dynamic sample"), wxPoint(50, 50), wxSize(450, 340))
        {
        	menu_bar = NULL; 
        	gui = NULL;
        	guiCleanedUp = 0;
        }
        
        virtual ~lb_wxFrame();
/*...e*/
public:
        lb_wxFrame(wxFrame *frame, char *title, int x, int y, int w, int h);

        DECLARE_LB_UNKNOWN()

	/**
	 * Set the GUI wrapper instance.
	 */
	void setGUI(lb_wxGUI* _gui) { gui = _gui; }

	/**
	 * Intented to typecast to derived class. Not sure, if this is really stupid.
	 * Where is it used ?
	 */
        virtual lb_wxFrame* getPeer() { return this; } 

public:
        void OnQuit(wxCommandEvent& event);
        void OnVerbose(wxCommandEvent& event);
        
        /**
         * Displays the about form of the application.
         */
        void OnAbout(wxCommandEvent& event);

	/**
	 * Displays the logon wizard dialog.
	 */
	void OnRunLogonWizard(wxCommandEvent& WXUNUSED(event));


        /**
         * This dispatcher converts all events to lb_I_Dispatcher events
         * and forwards them to such a dispatcher.
         * 
         * wx Handlers are forwarded directly.
         */
        void OnDispatch(wxCommandEvent& event);

	/**
	 * Build the minimal standard menu of the application.
	 */
	void OnBuildMenu(wxCommandEvent& event);
	
	/**
	 * \deprecated This was only a menu instance pointer check - debug.
	 */
	void OnCheck(wxCommandEvent& event);

	/**
	 * Return the frames menubar. Internal use only.
	 */
	wxMenuBar* LB_STDCALL getMenuBar() {
		return menu_bar;
	}


    
public:
        /**
         * Mixin the interface code, so the base of wxFrame can be used.
         * Simple a dummy code yet.
         */
        virtual lb_I_EventCallback LB_STDCALL getEventFunction(char* name) { return NULL; }
        virtual lbErrCodes LB_STDCALL Connect(char* evName, lb_I_EventCallback evFn) { return ERR_NONE; }
        virtual lbErrCodes LB_STDCALL getSinkEventList(lb_I_Container* c) { return ERR_NONE; }

        virtual lbErrCodes LB_STDCALL registerEvents(lb_I_EventConnector* object);
        
        virtual lbErrCodes LB_STDCALL createEventsource(lb_I_EventConnector* object);
        virtual lb_I_Unknown* LB_STDCALL getEventsource(lb_I_EventConnector* object) { return NULL; }
        
        wxMenuBar* menu_bar;
        
        lb_wxGUI* gui;
        int guiCleanedUp;
        
        UAP(lb_I_EventManager, eman)
        UAP(lb_I_Dispatcher, dispatcher)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lb_wxFrame)
//        ADD_INTERFACE(lb_I_EventSink)
        ADD_INTERFACE(lb_I_wxFrame)
END_IMPLEMENT_LB_UNKNOWN()

/*...slbErrCodes lb_wxFrame\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::setData(lb_I_Unknown* uk) {
        _LOG << "lb_wxFrame::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...slbErrCodes lb_wxFrame\58\\58\registerEvents\40\lb_I_EventConnector\42\ object\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::registerEvents(lb_I_EventConnector* object) {
        lb_wxFrame* peer = getPeer();


        
        ((wxFrame*) peer)->Connect( DYNAMIC_QUIT,  -1, wxEVT_COMMAND_MENU_SELECTED,
                  (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                  &lb_wxFrame::OnDispatch );

        ((wxFrame*) peer)->Connect( DYNAMIC_ABOUT, -1, wxEVT_COMMAND_MENU_SELECTED,
                  (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                  &lb_wxFrame::OnDispatch );

	((wxFrame*) peer)->Connect( DYNAMIC_BUILDMENU, -1, wxEVT_COMMAND_MENU_SELECTED,
	          (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                  &lb_wxFrame::OnDispatch );

	((wxFrame*) peer)->Connect( DYNAMIC_VERBOSE, -1, wxEVT_COMMAND_MENU_SELECTED,
	          (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                  &lb_wxFrame::OnVerbose );


        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lb_wxFrame\58\\58\createEventsource\40\lb_I_EventConnector\42\ object\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::createEventsource(lb_I_EventConnector* object) {

/*...screate a menu:0:*/
  // Make a menubar
  wxMenu *file_menu = new wxMenu;
  
  file_menu->Append(DYNAMIC_ABOUT, _trans("&About\tCtrl-A"));
  file_menu->Append(DYNAMIC_VERBOSE, _trans("&Verbose\tCtrl-V"));
  file_menu->Append(DYNAMIC_QUIT, _trans("E&xit\tCtrl-x"));

  menu_bar = new wxMenuBar;
  menu_bar->Append(file_menu, _trans("&File"));
  
/*...e*/

/*...sset the created menubar:0:*/

  SetMenuBar(menu_bar);

/*...e*/
        return ERR_NONE;
}
/*...e*/
/*...e*/
#endif

/*...swxAppSelectPage:0:*/
class wxAppSelectPage :
public lb_I_Unknown,
public lb_I_EventHandler, 
public wxWizardPageSimple
{
public:

	wxAppSelectPage() {
		app = wxString("");
	}
	
	virtual ~wxAppSelectPage() {
	    _CL_VERBOSE << "wxAppSelectPage::~wxAppSelectPage() called" LOG_
	}


	DECLARE_LB_UNKNOWN()

/*...swxAppSelectPage\40\wxWizard \42\parent\41\:8:*/
	wxAppSelectPage(wxWizard *parent) : wxWizardPageSimple(parent)
	{
			//m_bitmap = wxBITMAP(wiztest2);

			sizerMain  = new wxBoxSizer(wxVERTICAL);

			wxStaticText* text = new wxStaticText(this, -1, _trans("Application:"));
			box = new wxChoice(this, -1);
	        
			sizerMain->Add(text, 0, wxEXPAND | wxALL, 5);
			sizerMain->Add(box, 0, wxEXPAND | wxALL, 5);
	        
			SetSizer(sizerMain);
	        
			sizerMain->SetSizeHints(this);
			sizerMain->Fit(this);
	        
			box->SetFocusFromKbd();
			
			Centre();
	}

/*...e*/
	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* dispatcher);

	wxString LB_STDCALL getSelectedApp() { return app; }

/*...svoid setLoggedOnUser\40\char\42\ user\41\:8:*/
	void setLoggedOnUser(char* user) {
		userid = strdup(user);
		 
		REQUEST(manager.getPtr(), lb_I_Database, database)

		database->init();

		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		database->connect("lbDMF", lbDMFUser, lbDMFPasswd);

		sampleQuery = database->getQuery(0);

		char buffer[800] = "";

		sprintf(buffer, 
			"select Anwendungen.name from Anwendungen inner join User_Anwendungen on "
			"Anwendungen.id = User_Anwendungen.anwendungenid "
			"inner join Users on User_Anwendungen.userid = Users.id where "
			"Users.userid = '%s'"
				, userid);


		sampleQuery->skipFKCollecting();
		sampleQuery->query(buffer);
		sampleQuery->enableFKCollecting();

		// Clear the box, if it was previously filled due to navigation.
		
		box->Clear();
		
		// Fill up the available applications for that user.

		lbErrCodes err = sampleQuery->first();

		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {

			UAP_REQUEST(manager.getPtr(), lb_I_String, s1)	

			s1 = sampleQuery->getAsString(1);

			box->Append(wxString(s1->charrep()));

			while (err == ERR_NONE) {
				lbErrCodes err = sampleQuery->next();
				
				if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
					s1 = sampleQuery->getAsString(1);
					
					box->Append(wxString(s1->charrep()));
					
					if (err == WARN_DB_NODATA) {
						break;
					}
				}
			}
			box->SetSelection(0);
		}

		sizerMain->Fit(this);
		//Fit();

		return;
	}
/*...e*/

/*...svirtual bool TransferDataFromWindow\40\\41\:8:*/
	virtual bool TransferDataFromWindow()
	{
	        return TRUE;
	}
/*...e*/

	void OnWizardPageChanging(wxWizardEvent& event) {
		if (event.GetDirection()) {
			int sel = box->GetSelection();
			app = box->GetString(sel);

			if (!app.IsEmpty()) {
				UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		
				char* _app = strdup(app.c_str());
			
				meta->loadApplication(userid, _app);
			
				free(_app);
			}
		}
	}

private:
	wxCheckBox *m_checkbox;
	char* userid;
	wxChoice* box;
	wxString app;
	wxBoxSizer* sizerMain;

	UAP(lb_I_Database, database)
	UAP(lb_I_Query, sampleQuery)

	DECLARE_EVENT_TABLE()	
	
	
	// l gets overwritten, while assigning a lb_I_Query* pointer to sampleQuery !!
	// l and buf are therefore as a bugfix.
	long l;
	char buf[100];
};

BEGIN_EVENT_TABLE(wxAppSelectPage, wxWizardPageSimple)
    EVT_WIZARD_PAGE_CHANGING(-1, wxAppSelectPage::OnWizardPageChanging)
END_EVENT_TABLE()

BEGIN_IMPLEMENT_LB_UNKNOWN(wxAppSelectPage)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL wxAppSelectPage::setData(lb_I_Unknown* uk) {
        _LOG << "wxAppSelectPage::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

/*...slbErrCodes LB_STDCALL wxAppSelectPage\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ dispatcher\41\:0:*/
lbErrCodes LB_STDCALL wxAppSelectPage::registerEventHandler(lb_I_Dispatcher* dispatcher) {

	return ERR_NONE;
}
/*...e*/
/*...e*/

/*...swxLogonPage:0:*/
class wxLogonPage :
public lb_I_Unknown,
public lb_I_EventHandler,
public wxWizardPageSimple
{
public:


DECLARE_LB_UNKNOWN()

	wxLogonPage() {
	
	}
	
	virtual ~wxLogonPage() {
	}

	wxLogonPage(wxWizard *parent) : wxWizardPageSimple(parent)
	{
	        //m_bitmap = wxBITMAP(wiztest2);
	}

	char const * LB_STDCALL getTextValue(char* _name);

	void setAppSelectPage(wxAppSelectPage* p) {
		appselect = p;
	}

	// wizard event handlers
	void OnWizardCancel(wxWizardEvent& event)
	{
	        if ( wxMessageBox(_T("Do you really want to cancel?"), _T("Question"),
	                          wxICON_QUESTION | wxYES_NO, this) != wxYES )
	        {
	            // not confirmed
	            event.Veto();
	        }
	}

	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* dispatcher);

/*...slbErrCodes LB_STDCALL createPasswdCtrl\40\char\42\ _name\41\:8:*/
	lbErrCodes LB_STDCALL createPasswdCtrl(char* _name) {
		char* name = NULL;

		name = strdup(_name);

		wxTextCtrl *text = new wxTextCtrl(this, -1, "", wxPoint(), wxDefaultSize, wxTE_PASSWORD);

		text->SetName(name);

		sizerRight->Add(text, 1, wxEXPAND | wxALL, 5);

		char* tLabel = new char[strlen(name) + 1];

		tLabel[0] = 0;

		tLabel = strcat(tLabel, name);

		wxStaticText *label = new wxStaticText(this, -1, tLabel, wxPoint());
		sizerLeft->Add(label, 1, wxEXPAND | wxALL, 5);
	
		free(name);

		return ERR_NONE;
	}
/*...e*/
/*...slbErrCodes LB_STDCALL createTextCtrl\40\char\42\ _name\41\:8:*/
	lbErrCodes LB_STDCALL createTextCtrl(char* _name) {
		char* name = NULL;

		name = strdup(_name);

		wxTextCtrl *text = new wxTextCtrl(this, -1, "", wxPoint());

		text->SetName(name);

		sizerRight->Add(text, 1, wxEXPAND | wxALL, 5);

		char* tLabel = new char[strlen(name) + 1];

		tLabel[0] = 0;

		tLabel = strcat(tLabel, name);

		wxStaticText *label = new wxStaticText(this, -1, tLabel, wxPoint());
		sizerLeft->Add(label, 1, wxEXPAND | wxALL, 5);
	
		free(name);

		return ERR_NONE;
	}
/*...e*/
/*...svirtual bool TransferDataFromWindow\40\\41\:8:*/
	virtual bool TransferDataFromWindow()
	{
		lbErrCodes err = ERR_NONE;
		
		REQUEST(manager.getPtr(), lb_I_Database, database)

		database->init();

		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		err = database->connect("lbDMF", lbDMFUser, lbDMFPasswd);

		if (err != ERR_NONE) {
			char* buf = strdup(_trans("Login to database failed.\n\nYou could not use the dynamic features of the\napplication without a proper configured database."));
			char* buf1 = strdup(_trans("Error"));
			wxMessageDialog dialog(NULL, buf, buf1, wxOK);

			dialog.ShowModal();

			free(buf);
			free(buf1);		
		}

		sampleQuery = database->getQuery(0);

		char buffer[800] = "";

		char* pass = strdup(getTextValue("Passwort:"));
		char* user = strdup(getTextValue("Benutzer:"));


		sampleQuery->skipFKCollecting();

		sprintf(buffer, "select userid, passwort from Users where userid = '%s' and passwort = '%s'",
                	user, pass);

_CL_VERBOSE << "Query for user " << user LOG_

		if (sampleQuery->query(buffer) != ERR_NONE) {
		    printf("Query for user and password failed\n");
		    sampleQuery->enableFKCollecting();
		    return FALSE;
		}
		
		sampleQuery->enableFKCollecting();

		err = sampleQuery->first();

		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			appselect->setLoggedOnUser(user);

			if (pass) free(pass);
			if (user) free(user);

			return TRUE;
		} else {
		        printf("User authentication failed\n");

			if (pass) free(pass);
			if (user) free(user);

			return FALSE;
		}
	}
/*...e*/
/*...svoid init\40\wxWindow\42\ parent\41\:8:*/
	void init(wxWindow* parent)
	{
		char prefix[100] = "";
		sprintf(prefix, "%p", this);

		SetTitle("Login");

		sizerMain  = new wxBoxSizer(wxVERTICAL);
		sizerHor   = new wxBoxSizer(wxHORIZONTAL);
		sizerAddRem = new wxBoxSizer(wxHORIZONTAL);
		sizerLeft  = new wxBoxSizer(wxVERTICAL);	
		sizerRight = new wxBoxSizer(wxVERTICAL);

		int LoginOk;
		int LoginCancel;
	
		UAP_REQUEST(manager.getPtr(), lb_I_EventManager, eman)
		UAP_REQUEST(manager.getPtr(), lb_I_Dispatcher, dispatcher)

		char eventName[100] = "";
		
		dispatcher->setEventManager(eman.getPtr());

		registerEventHandler(dispatcher.getPtr());

		sizerHor->Add(sizerLeft, 1, wxEXPAND | wxALL, 5);
		sizerHor->Add(sizerRight, 1, wxEXPAND | wxALL, 5);
	
		createTextCtrl("Benutzer:");
		createPasswdCtrl("Passwort:");

		//#define CONNECTOR ((wxFrame*) frame)
		#define CONNECTOR this
	
		SetAutoLayout(TRUE);
		
		sizerMain->Add(sizerHor, 0, wxEXPAND | wxALL, 5);
		sizerMain->Add(sizerAddRem, 0, wxEXPAND | wxALL, 5);
		
		SetSizer(sizerMain);
	
		sizerMain->SetSizeHints(this);
		sizerMain->Fit(this);
		
		//Centre();
	}
/*...e*/

    
	UAP(lb_I_Database, database)
	UAP(lb_I_Query, sampleQuery)


	// l gets overwritten, while assigning a lb_I_Query* pointer to sampleQuery !!
	// l and buf are therefore as a bugfix.
	long l;
	char buf[100];

	wxWindow* OkButton;
	wxWindow* CancelButton;
	
	wxString textValue;

	wxBoxSizer* sizerMain;
	wxBoxSizer* sizerHor;
	wxBoxSizer* sizerAddRem;
	wxBoxSizer* sizerLeft;
	wxBoxSizer* sizerRight;

	wxAppSelectPage* appselect;
};


BEGIN_IMPLEMENT_LB_UNKNOWN(wxLogonPage)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL wxLogonPage::setData(lb_I_Unknown* uk) {
        _LOG << "wxLogonPage::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}


/*...slbErrCodes LB_STDCALL wxLogonPage\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ dispatcher\41\:0:*/
lbErrCodes LB_STDCALL wxLogonPage::registerEventHandler(lb_I_Dispatcher* dispatcher) {

	return ERR_NONE;
}
/*...e*/

/*...schar const \42\ LB_STDCALL wxLogonPage\58\\58\getTextValue\40\char\42\ _name\41\:0:*/
char const * LB_STDCALL wxLogonPage::getTextValue(char* _name) {
	
	wxWindow* w = FindWindowByName(wxString(_name));

	if (w != NULL) {
        	wxTextCtrl* tx = (wxTextCtrl*) w;

	        textValue = tx->GetValue();

		return textValue.c_str();
	}

	return "";
}
/*...e*/
/*...e*/
#endif

#ifndef USE_WXWRAPPER_DLL
/*...sclass lb_wxGUI:0:*/
#ifdef LB_I_EXTENTIONS

/*...sclass lb_wxGUI:0:*/
class lb_wxGUI
: public lb_I_wxGUI,
  public lb_I_EventHandler

{
public:
/*...sctor\47\dtor:8:*/
        lb_wxGUI() {
		#ifdef VERBOSE        	
                _LOG << "lb_I_wxGUI object will be created and initialized" LOG_
		#endif                
                
                eventCount = 0;
                sampleQuery = NULL;
                handlersInitialized = FALSE;
                frame = NULL;
		dialog = NULL;
        }

	virtual ~lb_wxGUI() { 
		#ifdef VERBOSE
	        _LOG << "lb_wxGUI::~lb_wxGUI() called.\n" LOG_
	        #endif
	}
/*...e*/

        DECLARE_LB_UNKNOWN()

/*...sGUI element creation functions:8:*/
        virtual lb_I_Unknown* LB_STDCALL createFrame();
        virtual lb_I_Unknown* LB_STDCALL createMenu();
        virtual lb_I_Unknown* LB_STDCALL createMenuBar();
        virtual lb_I_Unknown* LB_STDCALL createMenuEntry();

	lb_I_DatabaseForm* LB_STDCALL createDBForm(char* formName, char* queryString, char* DBName, char* DBUser, char* DBPass);

	void LB_STDCALL registerDBForm(char* formName, lb_I_DatabaseForm* form);

	lb_I_Form* LB_STDCALL createLoginForm();
/*...e*/

/*...sGUI element getter functions:8:*/
        virtual lb_I_Frame* LB_STDCALL getFrame();
/*...e*/
        
/*...sEvent related stuff:8:*/
        /**
         * Event related code.
         *
         * Register an event handler by the event registry.
         * This is from interface lb_I_EventManager
         */
        virtual lbErrCodes LB_STDCALL registerEvent(char* EvName, int & EvNr);
        
        /**
         * This is from lb_I_EventHandler. A event handler must provide
         * this function, to be able to call it from the dispatcher.
         */
        virtual lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);
        
        /**
         * To be able to recieve any events, it is neccesary to provide the dispatcher.
         * An other way may be registrering a direct callback, without dispatching it.
         */
        virtual lbErrCodes LB_STDCALL addDispatcher(lb_I_Dispatcher* disp);
        virtual lbErrCodes LB_STDCALL dispatchEvent(int EvNr, lb_I_Unknown* EvData);

        lbErrCodes LB_STDCALL setDiapatcher(lb_I_Dispatcher* disp);
        lb_I_Dispatcher* LB_STDCALL getDispatcher();

        /**
         * Provide a function to interact with event names instead if their ID's.
         * If the event is not known, it returns ERR_EVENT_UNKNOWN and leaves
         * the provided EvData untouched.
         *
         * As a sample, you may create a new menu in the GUI. This menu is the
         * new help menu, for that you want provide a basic application about
         * dialog.
         *
         * To be able, creating a simple about dialog, it is neccesary to have
         * a pointer to the frame, in with the dialog should be displayed.
         * So first you must query for a frame reference.
         */

        virtual lbErrCodes LB_STDCALL queryEvent(char* EvName, lb_I_Unknown* EvData);
/*...e*/
        
/*...sMenu related manipulation and navigation:8:*/
        /**
         * Menu manipulation based on current position. The members
         * deleates this calls to the lb_I_GUI instance.
         */
         
        virtual lbErrCodes LB_STDCALL deactivateMenuEntry();
        virtual lbErrCodes LB_STDCALL activateMenuEntry();
        
        virtual lbErrCodes LB_STDCALL gotoMenuRoot();
        virtual lbErrCodes LB_STDCALL gotoMenuEntry(char* entry);
        
        virtual lbErrCodes LB_STDCALL addMenuEntry(lb_I_Unknown* entry);
        virtual lbErrCodes LB_STDCALL insertMenuEntry(lb_I_Unknown* entry);

/*...e*/
        
        virtual lbErrCodes LB_STDCALL msgBox(char* windowTitle, char* msg);
        
        virtual lbErrCodes LB_STDCALL setDispatcher(lb_I_Dispatcher* disp);

/*...sTypical GUI handler\44\ that do not need to be dispatched:8:*/
	/* The menubar is still present in the demo. At the
	   first time, a new menubar should not be used.
	*/
	virtual lbErrCodes LB_STDCALL addMenuBar(char* name) { return ERR_NONE; };

	/**
	 * Add a menu behind the last.
	 */
	virtual lbErrCodes LB_STDCALL addMenu(char* name) { return ERR_NONE; };
	
	/**
	 * Add a menu entry in the named menu after given entry,
	 * if provided. The handler must be registered prior.
	 * 
	 * Input:
	 *	char* in_menu:		Which menu to add to (File/Edit/Help/...)
	 *	char* entry:		The text for that entry
	 *	char* evHandler:	The name of a registered event handler, that handle this
	 *	char* afterentry:	Insert the entry after an exsisting entry
	 */
	virtual lbErrCodes LB_STDCALL addMenuEntry(char* in_menu, char* entry, char* evHandler, char* afterentry = NULL) { return ERR_NONE; };

	/**
	 * Add a button at a given position.
	 *
	 * Input:
	 *	char* buttonText	The text for that button
	 *	char* evHandler		The name of a registered event handler, that handle this
	 *	int x 			X coordinade
	 *	int y			Y coordinade
	 *	int w			W coordinade
	 *	int h			H coordinade
	 */
	virtual lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) { return ERR_NONE; };


	virtual lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h) { return ERR_NONE; };


	virtual lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h) { return ERR_NONE; };
/*...e*/
        

	lb_I_DatabaseForm* LB_STDCALL findDBForm(char* name);

	/*
	 * Cleanup. This will destroy all possible (hidden) dialogs.
	 * These dialogs are like the database form sample dialog, wich woild
	 * be created only once and then reused by ShowModal().
	 */

	lbErrCodes LB_STDCALL cleanup();

	/**
	 * \brief Set presentation mode.
	 *
	 * This function set's wether the application uses wxNotebooks to show
	 * database forms inside (lb_Database_Panel) or uses dialog based forms.
	 */
	void	LB_STDCALL setNotebookMode(bool mode = TRUE);
	
	/**
	 * \brief Get presentation mode.
	 *
	 * Returns true, if the mode is notebook and false if it is dialog mode.
	 */
	bool	LB_STDCALL isNotebookMode();
	
	bool _NotebookMode;

        int eventCount;
        
        lb_I_Unknown* _main_frame;
        lb_I_Dispatcher* myDispatcher;
        
        lb_I_Query* sampleQuery;
        
        bool handlersInitialized;
        
        lb_I_DatabaseForm* dialog;

        // The frame has the main dispatcher and is a wxEventHandler subclass
        lb_wxFrame* frame;
	
	UAP(lb_I_Container, forms)
	char buffer[100];
};
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lb_wxGUI)
        ADD_INTERFACE(lb_I_wxGUI)
END_IMPLEMENT_LB_UNKNOWN()

/*...sUnimplemented code:0:*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\setDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::setDispatcher(lb_I_Dispatcher* disp) {
       _LOG << "lb_wxGUI::setDispatcher() not implemented yet" LOG_
        
        return ERR_NONE;
}
/*...e*/


/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\registerEvent\40\char\42\ EvName\44\ int \38\ EvNr\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::registerEvent(char* EvName, int & EvNr) {
       _LOG << "Registering an event" LOG_;
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\addDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::addDispatcher(lb_I_Dispatcher* disp) {
       _LOG << "Add a sub dispatcher" LOG_;
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\dispatchEvent\40\int EvNr\44\ lb_I_Unknown\42\ EvData\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::dispatchEvent(int EvNr, lb_I_Unknown* EvData) {
       _LOG << "Dispatch an event" LOG_;
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\queryEvent\40\char\42\ EvName\44\ lb_I_Unknown\42\ EvData\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::queryEvent(char* EvName, lb_I_Unknown* EvData) {
       _LOG << "Query an event" LOG_;
        return ERR_NONE;
}
/*...e*/

/*...slbErrCodes lb_wxGUI\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::setData(lb_I_Unknown* uk) {
        _LOG << "lb_wxGUI::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\createMenu\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::createMenu() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return NULL;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\createMenuBar\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::createMenuBar() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return NULL;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\createMenuEntry\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::createMenuEntry() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\deactivateMenuEntry\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::deactivateMenuEntry() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\activateMenuEntry\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::activateMenuEntry() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\gotoMenuRoot\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::gotoMenuRoot() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\addMenuEntry\40\lb_I_Unknown\42\ entry\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::addMenuEntry(lb_I_Unknown* entry) {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\insertMenuEntry\40\lb_I_Unknown\42\ entry\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::insertMenuEntry(lb_I_Unknown* entry) {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...e*/

/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::registerEventHandler(lb_I_Dispatcher* disp) {

// Cleanup is no event handler.        
//        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxGUI::cleanup, "wxGUI_Cleanup"); 
         
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\cleanup\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::cleanup() {
	
	/* Destroy all still created forms that are hidden.
	 * If this would not be taken, the application will hang,
	 * because these windows are still there.
	 *
	 * But the container must be deleted and there seems to be
	 * a double delete. So I need a removeAll function for the container. 
	 */

	if (forms == NULL) {
		_CL_LOG << "lb_wxGUI::cleanup() has nothing to clean up." LOG_
		return ERR_NONE;
	} 

	while (forms->hasMoreElements()) {
		lbErrCodes err = ERR_NONE;
				
		lb_I_Unknown* form = forms->nextElement();

		if (!form) continue;

		UAP(lb_I_DatabaseForm, d)		
		QI(form, lb_I_DatabaseForm, d)
		
		/* Really needed here !
		 * The wxWidgets system doesn't have a or at least has it's own reference counting system.
		 *
		 * So here I must ensure, that the object it self doesn't get deleted in the container.
		 * wxWidgets should call the destructor of the form.
		 */
		 
		 
		_CL_LOG << "Destroy a form with " << d->getRefCount() << " references ..." LOG_
		 
		d++;
		
		d->destroy();
		
		_CL_LOG << "Destroyed the form." LOG_
	}
	
	forms->detachAll();

        return ERR_NONE;
}
/*...e*/
/*...slb_I_Form\42\ LB_STDCALL lb_wxGUI\58\\58\createLoginForm\40\\41\:0:*/
lb_I_Form* LB_STDCALL lb_wxGUI::createLoginForm() {
	wxWizard *wizard = new wxWizard(NULL, -1, _T("Anmeldung"));

	wxWizardPageSimple *page1 = new wxWizardPageSimple(wizard);

	wxStaticText *text = new wxStaticText(page1, -1, _T("Melden Sie sich nun an.\n"));

	wxSize size = text->GetBestSize();

	wxLogonPage *page2 = new wxLogonPage(wizard);
	
	page2->setModuleManager(getModuleManager(), __FILE__, __LINE__);

	page2->init(frame);

	wxAppSelectPage *page3 = new wxAppSelectPage(wizard);
	page3->setModuleManager(getModuleManager(), __FILE__, __LINE__);

	page2->setAppSelectPage(page3);


	page1->SetNext(page2);
	page2->SetPrev(page1);
	page2->SetNext(page3);
	page3->SetPrev(page2);
	

	wizard->SetPageSize(size);

	if ( ! wizard->RunWizard(page1) )
	{
	    wxMessageBox(_T("Anmeldung fehlgeschlagen"), _T("That's all"),
            wxICON_INFORMATION | wxOK);
        }

//	wxString app = page3->getSelectedApp();

	wizard->Destroy();


#ifdef bla
/*...s:0:*/

	lbErrCodes err = ERR_NONE;

	// Locate the form instance in the container
	
	lbLoginDialog* _dialog = NULL;
	
	if (forms == NULL) {
		REQUEST(getModuleManager(), lb_I_Container, forms)
	}	

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	UAP_REQUEST(getModuleManager(), lb_I_String, fName)
	fName->setData("LoginForm");
	
	QI(fName, lb_I_KeyBase, key)
	
	uk = forms->getElement(&key);	
	
	if (uk != NULL) {
		_dialog = (lbLoginDialog*) *&uk;
	}

	if (_dialog) {
		_dialog->Show(TRUE);
	} else {
		_dialog = new lbLoginDialog();
		_dialog->setModuleManager(getModuleManager(), __FILE__, __LINE__);
		
		QI(_dialog, lb_I_Unknown, uk)
		
		forms->insert(&uk, &key);
		
		delete _dialog;
		_dialog = NULL;
		
		uk = forms->getElement(&key);
		
		if (uk != NULL) {
		        _dialog = (lbLoginDialog*) *&uk;
		}
		
		_dialog->init(frame);
		_dialog->Show();
	}
/*...e*/
#endif
	return NULL;
}
/*...e*/
/*...slb_I_DatabaseForm\42\ LB_STDCALL lb_wxGUI\58\\58\createDBForm\40\char\42\ formName\44\ char\42\ queryString\44\ char\42\ DBName\44\ char\42\ DBUser\44\ char\42\ DBPass\41\:0:*/
lb_I_DatabaseForm* LB_STDCALL lb_wxGUI::createDBForm(char* formName, char* queryString, char* DBName, char* DBUser, char* DBPass) {
	lbErrCodes err = ERR_NONE;

	// Locate the form instance in the container
	
	UAP(lb_I_DatabaseForm, _dialog)
	
	if (forms == NULL) {
		REQUEST(getModuleManager(), lb_I_Container, forms)
	}	

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	UAP_REQUEST(getModuleManager(), lb_I_String, fName)
	fName->setData(formName);
	
	QI(fName, lb_I_KeyBase, key)
	
	uk = forms->getElement(&key);	
	
	if (uk != NULL) {
		QI(uk, lb_I_DatabaseForm, _dialog)
	}

	if ((_dialog.getPtr() != NULL) && (strcmp(queryString, _dialog->getQuery()) != 0)) {
	
		// SQL query from database has been changed. Recreate the dialog from scratch. 
	
		// Don't delete any forms inside the container
		forms->detachAll();
	
		forms->remove(&key);
		
		_dialog->destroy();
	
		_dialog.resetPtr();
	}

	if (_dialog.getPtr() == NULL) {
		/*
		 * Try to find a database form plugin, having the interface lb_I_DatabaseForm.
		 *
		 * This interface contains one and only one member function to initialize the
		 * form with a given SQL query, the required database name, login and password.
		 *
		 * This demonstrates the extensibleability of the GUI wrapper with the new plugin
		 * framework.
		 */

		UAP_REQUEST(manager.getPtr(), lb_I_PluginManager, PM)
		UAP(lb_I_Plugin, pl)
		
		pl = PM->getFirstMatchingPlugin("lb_I_DatabaseForm");

		if (pl == NULL) {
			char* msg = (char*) malloc(200);
			msg[0] = 0;
			strcpy(msg, _trans("Database form plugin not found or not installed.\n\nDatabase forms are not available."));
			msgBox(_trans("Error"), msg);
			free(msg);
			return NULL;
		}

		uk = pl->getImplementation();
		
		forms->insert(&uk, &key);
		
		//-------------------------------------------------------
		// The form has been cloned. Destroy the unused instance.
		// This avoids application hang at exit.
		
		UAP(lb_I_DatabaseForm, form)
		QI(uk, lb_I_DatabaseForm, form)
		
		form->destroy();
		form = NULL;
		//-------------------------------------------------------
		
		uk = forms->getElement(&key);
		
		if (uk != NULL) {
		        QI(uk, lb_I_DatabaseForm, _dialog)
		}
		
		_dialog->setName(formName);
		
		_dialog->init(queryString, DBName, DBUser, DBPass);
		
	}

	//_dialog->show();
	_dialog++;
	
	return _dialog.getPtr();
}
/*...e*/

void LB_STDCALL lb_wxGUI::registerDBForm(char* formName, lb_I_DatabaseForm* form) {

}

/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\createFrame\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::createFrame() {
        frame = new lb_wxFrame();
        
        frame->setModuleManager(getModuleManager(), __FILE__, __LINE__);
        frame->queryInterface("lb_I_Unknown", (void**) &_main_frame, __FILE__, __LINE__);

	frame->setGUI(this);

	#ifdef VERBOSE
	char ptr[20] = "";
	sprintf(ptr, "%p", frame);
	
	_LOG << "Created a lb_wxFrame object at " << ptr LOG_
        #endif
        
        return frame;
}
/*...e*/
/*...slb_I_Frame\42\ LB_STDCALL lb_wxGUI\58\\58\getFrame\40\\41\:0:*/
lb_I_Frame* LB_STDCALL lb_wxGUI::getFrame() {
        lb_I_Frame* f = NULL;
        
        _main_frame->queryInterface("lb_I_Frame", (void**) &f, __FILE__, __LINE__);
        
        return f;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\gotoMenuEntry\40\char\42\ entry\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::gotoMenuEntry(char* entry) {
        lbErrCodes err = ERR_NONE;
        UAP(lb_I_Frame, frame)
        
        QI(_main_frame, lb_I_Frame, frame)


        /**
         * Create the dispatch request
         */


        UAP_REQUEST(manager.getPtr(), lb_I_DispatchRequest, d_req)
        
        /**
         * We get a dispatch responce
         */
         
        UAP(lb_I_DispatchResponse, d_res)

        if (d_req.getPtr()) {
                // d_req must resolve the symbolic request name to its Id.
                // So it must have an instance from lb_I_EventManager
                d_req->setRequestName("hasMenuEntry");

                d_res = myDispatcher->dispatch(*&d_req);

                if ((d_res.getPtr()) && (d_res->isOk())) {
                } else {
                }
        } 

/*        id (frame->hasMenuEntry(entry)) {
                if (currentMenuEntry) free(currentMenuEntry);
                currentMenuEntry = strdup(entry);
        }
*/
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\msgBox\40\char\42\ windowTitle\44\ char\42\ msg\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::msgBox(char* windowTitle, char* msg) {
        wxMessageDialog dialog(NULL, msg, windowTitle, wxOK);

        dialog.ShowModal();

        return ERR_NONE;
}
/*...e*/
lb_I_DatabaseForm* LB_STDCALL lb_wxGUI::findDBForm(char* name) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleManager(), lb_I_String, fName)
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, uk)
	
	fName->setData(name);
	
	QI(fName, lb_I_KeyBase, key)
	
	uk = forms->getElement(&key);
	
	UAP(lb_I_DatabaseForm, w)
	QI(uk, lb_I_DatabaseForm, w)
	// Not really needed, because my dialogs are forced to not be smart.
	w++;
	return w.getPtr();
}
#endif
/*...e*/
#endif
#ifndef LB_I_EXTENTIONS
class MyFrame;
#endif

/*...sclass MyApp:0:*/
// Define a new application type

/**
 * \brief Sample application. The main of a wxWidgets application.
 *
 * It is used to demonstrate a GUI sample application.
 */
class MyApp:
#ifdef LB_I_EXTENTIONS
public lb_I_Unknown
, public lb_I_GUIApp
, public lb_I_EventConnector
, public lb_I_EventHandler ,
#endif
public wxApp
{ public:
	/**
	 * Initialisation.
	 */
	MyApp() {
#ifdef LB_I_EXTENTIONS	
	  wxGUI = NULL;
	  metaApp = NULL;
#endif
	 panel = NULL;
	}

	/**
	 * Deletes the lb_I_GUI instance used for independent GUI component handlers.
	 */
	virtual ~MyApp() { 
/*
 * It seems, that frame was deleted prior !!
 */

		if (wxGUI) delete wxGUI;

		printf("MyApp::~MyApp() called.\n");
		
	}

	/**
	 * Main initialisation member. It shows the integration of my framework into a wxWidgets application.
	 */
    bool OnInit(void);
    
    int  OnExit();

#ifdef LB_I_EXTENTIONS
/*...ssome docs:0:*/
    /*
     * This instance knows of some events, have to be interconnected.
     * The source are menus and the target is the frame, that handles
     * it.
     * As in general, the application must define the events it needs
     * for the proper work. We see, that the OnInit method defines some
     * events, here exit and about. The application needs to be able for
     * exiting and may provide an about dialog. As an interpreter here, the
     * application will be in a module later and the interpreter loads the app.
     *
     * The application in the module is the real application. This object simply
     * delegates the functionality to it.
     */
/*...e*/

        virtual lbErrCodes LB_STDCALL getConnectorEventList(lb_I_Container* c) { return ERR_NONE; }
        virtual lbErrCodes LB_STDCALL createEventsource(lb_I_EventConnector* object) { return ERR_NONE; }

	/**
	 * Create event handler, that this application would provide to the lbDMF user.
	 */
        virtual lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);

	// I provide some eventhandlers
	
	/**
	 * Event handler to add a menu in the main application. It is not implemented because
	 * the sample application creates it directly to have a menu if no other modules are
	 * found. At leasd an exit handling is created.
	 */
	lbErrCodes LB_STDCALL addMenu(lb_I_Unknown* uk);
	
	/** \brief Handler to ask for a filename.
	 *
	 */
	lbErrCodes LB_STDCALL askOpenFileReadStream(lb_I_Unknown* uk);

	/** \brief Handler to ask for YES or NO.
	 *
	 */
	lbErrCodes LB_STDCALL askYesNo(lb_I_Unknown* uk);

	/** \brief Handler to add a menubar.
	 * Event handler to add a menu bar on the main menu. This is used in my lb_I_MetaApplication and
	 * also used in the demo app module.
	 */
	lbErrCodes LB_STDCALL addMenuBar(lb_I_Unknown* uk);
	
	/**
	 * Event handler to add a menu entry in a given menu bar name.
	 * \note These handlers should not called by the user of lbDMF. The programmer would use lb_I_MetaApplication to abstract from the real GUI implementation.
	 */
	lbErrCodes LB_STDCALL addMenuEntry(lb_I_Unknown* uk);	
	
	/** \brief Enable an event.
	 *
	 * Enable all event sources, that are associated with this event name.
	 */
	lbErrCodes LB_STDCALL enableEvent(lb_I_Unknown* uk);

	/** \brief Disable an event.
	 *
	 * Disable all event sources, that are associated with this event name.
	 */
	lbErrCodes LB_STDCALL disableEvent(lb_I_Unknown* uk);

	/** \brief Toggle an event.
	 *
	 * Enable or disable all event sources, that are associated with this event name.
	 */
	lbErrCodes LB_STDCALL toggleEvent(lb_I_Unknown* uk);
	
	// These event handlers are canditates for an API replacement

	/**
	 * Add a button to the main frame.
	 */	
	lbErrCodes LB_STDCALL addButton(lb_I_Unknown* uk);
	
	/**
	 * Add a label to the main frame.
	 */
	lbErrCodes LB_STDCALL addLabel(lb_I_Unknown* uk);
	
	/**
	 * Add a text control to the main frame.
	 */
	lbErrCodes LB_STDCALL addTextField(lb_I_Unknown* uk);

	/**
	 * Unused ?
	 */
        lbErrCodes LB_STDCALL HandleGetFrame(lb_I_Unknown* uk); // Thread parameter as output
        
        /**
         * Unused ?
         */
        lbErrCodes LB_STDCALL HandleAddMenu(lb_I_Unknown* uk);  // Thread parameter as input
    
        DECLARE_LB_UNKNOWN()
    
protected:
/*...ssome docs:0:*/
        /**
         * This instance will be known in the meta application. So all events from the
         * application logic will be forwarded to this instance.
         *
         * Every event from the meta app or any registered components would be mapped to
         * wxWindows events, so that the wxWindows objects could be manipulated.
         */
/*...e*/
        lb_wxGUI* wxGUI;

        //UAP(lb_I_EventHandler, frame)

	// Storage for event ID's generated on the fly
        
        int AddMenu;
        int AddMenuBar;
        int AddMenuEntry;
        int AddLabel;
        int AddTextField;
        int AddButton;
        int _enableEvent;
        int _disableEvent;
        int _toggleEvent;
        int _askYesNo;
	int AskOpenFileReadStream;
		
        
        
/*...sevent manager:8:*/
        /*
         * I need an instance of the event manager. The event manager is used to give me id's for my
         * symbolic event names. First I do not handle a scope.
         */
        
        UAP(lb_I_EventManager, ev_manager)
/*...e*/
/*...smeta application:8:*/
        /*
         * I also need an instance of the meta application, that is loaded as the application wrapper.
         */
         
        UAP(lb_I_MetaApplication, metaApp) 
/*...e*/
/*...sframe:8:*/
	lb_wxFrame *frame;
/*...e*/

	char buffer[100];
#endif

        #ifndef LB_I_EXTENTIONS
        MyFrame *frame;
        #endif
        wxPanel *panel;
};
/*...e*/

#ifndef LB_I_EXTENTIONS
/*...sclass MyFrame:0:*/
// Define a new frame type
class MyFrame: public wxFrame
{ public:
    MyFrame(wxFrame *frame, char *title, int x, int y, int w, int h);

 public:
    void OnVerbose(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
/*...e*/
#endif



#ifdef LB_I_EXTENTIONS
BEGIN_IMPLEMENT_LB_UNKNOWN(MyApp)
//        ADD_INTERFACE(lb_I_EventConnector)
//        ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()
#endif 


// Create a new application object
#ifdef OSX
IMPLEMENT_APP  (MyApp)
#endif
#ifdef LINUX
#ifndef OSX
IMPLEMENT_APP  (MyApp)
#endif
#endif

/*...sint MyApp\58\\58\OnExit\40\\41\:0:*/
int MyApp::OnExit() {
	lbErrCodes err = ERR_NONE;
	
	if (metaApp == NULL) {
		REQUEST(getModuleInstance(), lb_I_MetaApplication, metaApp)
	}
	

	UAP_REQUEST(manager.getPtr(), lb_I_PluginManager, PM)
	
	metaApp->unloadApplication();
	
	metaApp->save();
	
	PM->unload();
	
	_CL_LOG << "Unloaded plugins." LOG_
		
	return 0;
}
/*...e*/
/*...sMyApp\58\\58\OnInit\40\void\41\:0:*/
// `Main program' equivalent, creating windows and returning main app frame
bool MyApp::OnInit(void)
{
    char b[100] = "";
    wxStopWatch sw;


    UAP(lb_I_Module, mm)
    mm = getModuleInstance();

    wxImage::AddHandler(new wxPNGHandler);

    wxSplashScreen* splash;
    wxBitmap bitmap;
    if (bitmap.LoadFile("splash.png", wxBITMAP_TYPE_PNG))
    {
          splash = new wxSplashScreen(bitmap,
          wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
          6000, NULL, -1, wxDefaultPosition, wxDefaultSize,
          wxSIMPLE_BORDER); //|wxSTAY_ON_TOP);
    }
    wxYield();

    if (mm == NULL) {
	wxMessageDialog dialog(NULL, "Module manager not found. could not run application.", "Error", wxOK);

	dialog.ShowModal();  
	return FALSE;
    } 

    mm->setModuleManager(mm.getPtr(), __FILE__, __LINE__);
    setModuleManager(mm.getPtr(), __FILE__, __LINE__);


    
    UAP_REQUEST(mm.getPtr(), lb_I_Dispatcher, disp)
	REQUEST(mm.getPtr(), lb_I_EventManager, ev_manager)        

    UAP_REQUEST(mm.getPtr(), lb_I_String, string)
    UAP_REQUEST(mm.getPtr(), lb_I_Database, tempDB) // Preload this module
    UAP_REQUEST(mm.getPtr(), lb_I_PluginManager, PM)
    UAP_REQUEST(mm.getPtr(), lb_I_MetaApplication, metaApp)


    PM->initialize();

    /// \todo Find leak.
    metaApp++;

    lbErrCodes err = ERR_NONE;

    disp->setEventManager(ev_manager.getPtr());
		
    if (disp == NULL) _LOG << "Fatal: Have not got a dispatcher!" LOG_

    if (wxGUI == NULL) {
        wxGUI = new lb_wxGUI();
        wxGUI->setModuleManager(mm.getPtr(), __FILE__, __LINE__);

		// Register Events, that I provide

		ev_manager->registerEvent("AddMenu", AddMenu);
		ev_manager->registerEvent("AddMenuBar", AddMenuBar);
		ev_manager->registerEvent("AddButton", AddButton);	

		ev_manager->registerEvent("showLeft", AddButton);	
	
		ev_manager->registerEvent("AddMenuEntry", AddMenuEntry);
		ev_manager->registerEvent("AddLabel", AddLabel);
		ev_manager->registerEvent("AddTextField", AddTextField);
		ev_manager->registerEvent("askOpenFileReadStream", AskOpenFileReadStream);
		ev_manager->registerEvent("askYesNo", _askYesNo);
		ev_manager->registerEvent("enableEvent", _enableEvent);
		ev_manager->registerEvent("disableEvent", _disableEvent);
		ev_manager->registerEvent("toggleEvent", _toggleEvent);

        registerEventHandler(*&disp);
    }

    if (metaApp != NULL) {
        metaApp->setGUI(wxGUI);
	}
	
    UAP(lb_I_Unknown, uk)
    uk = wxGUI->createFrame();
    uk++;
    uk++;

    frame = (lb_wxFrame*) uk.getPtr();

    frame->registerEventHandler(*&disp);

    // Fake. Parameter not used yet.
    wxGUI->setIcon("mondrian");

    //err = frame->createEventsource(this);

    wxGUI->registerEventHandler(*&disp);

    if (err != ERR_NONE) _LOG << "Have some problems to set up menu event sources" LOG_
  
    frame->Centre();

    SetTopWindow(frame);

    if (metaApp != NULL) {
        metaApp->initialize();

	if (metaApp->isPropertyPaneLayoutLeft()) metaApp->showPropertyPanel();
	if (metaApp->isPropertyPaneLayoutFloating()) metaApp->showPropertyPanel();
	if (metaApp->getGUIMaximized()) frame->Maximize();
    } 

    if (PM->beginEnumPlugins()) {
		
    while (TRUE) {
        UAP(lb_I_Plugin, pl)
        pl = PM->nextPlugin();
        if (pl == NULL) break;
            pl->autorun();
        }
    }
	
    frame->Show(TRUE);
    
#ifdef LINUX
    if (splash != NULL) splash->Raise();
#endif

    if (metaApp != NULL) metaApp->run();

    return TRUE;
}
/*...e*/
#ifdef LB_I_EXTENTIONS
/*...sMyApp\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL MyApp::setData(lb_I_Unknown* uk) {
        _LOG << "MyApp::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

/*...e*/

/*...sMyApp\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL MyApp::registerEventHandler(lb_I_Dispatcher* disp) {
	// We provide some menu manipulation
	
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addMenu, "AddMenu");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addMenuBar, "AddMenuBar");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addMenuEntry, "AddMenuEntry");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addButton, "AddButton");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addLabel, "AddLabel");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addTextField, "AddTextField");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::askOpenFileReadStream, "askOpenFileReadStream");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::askYesNo, "askYesNo");

	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::enableEvent, "enableEvent");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::disableEvent, "disableEvent");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::toggleEvent, "toggleEvent");

	return ERR_NONE;
}
/*...e*/
/*...sevent handler:0:*/
/*...sHandleGetFrame\9\\9\Handler:0:*/
lbErrCodes LB_STDCALL MyApp::HandleGetFrame(lb_I_Unknown* uk) {
        if(frame != NULL) {
                lb_I_Unknown* _uk;
                UAP(lb_I_Reference, ref)
                frame->queryInterface("lb_I_Unknown", (void**) &_uk, __FILE__, __LINE__);
                
                uk->queryInterface("lb_I_Reference", (void**) &ref, __FILE__, __LINE__);
                
                ref->set(_uk);
        }
        return ERR_NONE;
}
/*...e*/
/*...sHandleAddMenu\9\\9\Handler:0:*/
lbErrCodes LB_STDCALL MyApp::HandleAddMenu(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_String, string)
	if (uk == NULL) _LOG << "Have got a null pointer" LOG_;
	QI(uk, lb_I_String, string)
	
	wxMenu *menu = new wxMenu;

	menu->Append(DYNAMIC_TEST1, "&About");
	menu->Append(DYNAMIC_TEST2, "E&xit");
	    
	wxMenuBar* mBar = frame->getMenuBar();
	mBar->Append(menu, "&Edit");

        return ERR_NONE;
}
/*...e*/
/*...saskOpenFileReadStream\9\Handler:0:*/
lbErrCodes LB_STDCALL MyApp::askOpenFileReadStream(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP_REQUEST(manager.getPtr(), lb_I_String, filepath)
	UAP_REQUEST(manager.getPtr(), lb_I_String, defaultdir)
	UAP_REQUEST(manager.getPtr(), lb_I_String, after)

	UAP(lb_I_Parameter, param)
	
	QI(uk, lb_I_Parameter, param)
	
	parameter->setData("extention");
	param->getUAPString(*&parameter, *&name);

	//"BMP and GIF files (*.bmp;*.gif)|*.bmp;*.gif|PNG files (*.png)|*.png"
	
	wxFileDialog fileDialog(NULL, _trans("Choose a file"), defaultdir->charrep(), "", name->charrep(), wxOPEN);

	_CL_LOG << "Show up a file dialog." LOG_

	if (fileDialog.ShowModal() == wxID_OK) {
		parameter->setData("result");
		filepath->setData(fileDialog.GetPath().c_str());
		param->setUAPString(*&parameter, *&filepath);
	} else {
		parameter->setData("result");
		filepath->setData("");
		param->setUAPString(*&parameter, *&filepath);
	}
	
	return err;
}
/*...e*/
/*...saskYesNo\9\\9\\9\Handler:0:*/
lbErrCodes LB_STDCALL MyApp::askYesNo(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, msg)
	UAP_REQUEST(manager.getPtr(), lb_I_String, result)

	UAP(lb_I_Parameter, param)
	
	QI(uk, lb_I_Parameter, param)
	
	parameter->setData("msg");
	param->getUAPString(*&parameter, *&msg);
	
	wxMessageDialog msgDialog(NULL, msg->charrep(), _trans("Frage..."), wxYES_NO);

	if (msgDialog.ShowModal() == wxID_YES) {
		parameter->setData("result");
		result->setData("yes");
		param->setUAPString(*&parameter, *&result);
	} else {
		parameter->setData("result");
		result->setData("no");
		param->setUAPString(*&parameter, *&result);
	}
	
	return err;
}
/*...e*/

/*...saddMenuBar\9\\9\\9\Handler:0:*/
lbErrCodes LB_STDCALL MyApp::addMenuBar(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP_REQUEST(manager.getPtr(), lb_I_String, after)

	UAP(lb_I_Parameter, param)
	
	QI(uk, lb_I_Parameter, param)
	
	parameter->setData("name");
	param->getUAPString(*&parameter, *&name);

	if (param->Count() > 1) {
		parameter->setData("after");
		param->getUAPString(*&parameter, *&after);
		
		wxMenu *menu = new wxMenu;
		
		wxMenuBar* mbar = frame->getMenuBar();
		
		int pos = 0;
		
		if (mbar) {
			wxString m = wxString(after->getData());
			pos = mbar->FindMenu(m);
			mbar->Insert(pos+1, menu, name->getData());
		}
	} else {
		wxMenu *menu = new wxMenu;

		wxMenuBar* mbar = frame->getMenuBar();
		if (mbar) mbar->Append(menu, name->getData());
	}
	
	return err;
}
/*...e*/
/*...saddMenuEntry\9\\9\Handler:0:*/
/**
 * Add a menu entry to a specific menubar.
 *
 * Params:
 *	menubar:	Name of menubar
 *	menuname:	Name of menu entry
 *	handlername:	Name of handler
 */
lbErrCodes LB_STDCALL MyApp::addMenuEntry(lb_I_Unknown* uk) {
/*...scode:0:*/
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, menubar)
	UAP_REQUEST(manager.getPtr(), lb_I_String, menuname)
	UAP_REQUEST(manager.getPtr(), lb_I_String, handlername)
	UAP_REQUEST(manager.getPtr(), lb_I_String, checkable)
	
	
	UAP(lb_I_Parameter, param)

	QI(uk, lb_I_Parameter, param)

	parameter->setData("menubar");
	param->getUAPString(*&parameter, *&menubar);
	parameter->setData("menuname");
	param->getUAPString(*&parameter, *&menuname);
	parameter->setData("handlername");
	param->getUAPString(*&parameter, *&handlername);

	if (param->Count() > 3) {
		parameter->setData("checkable");
		param->getUAPString(*&parameter, *&checkable);
	}
	
	int EvNr = 0;
	
	if (ev_manager->resolveEvent(handlername->getData(), EvNr) == ERR_EVENT_NOTREGISTERED) {
		_CL_LOG << "ERROR: Could not register a menu entry with an unregistered handler!" LOG_
		
		return ERR_EVENT_NOTREGISTERED;
	}

	wxMenuBar* mbar = frame->getMenuBar();
	
	wxMenu* menu = mbar->GetMenu(mbar->FindMenu(wxString(menubar->getData())));


	if ((param->Count() > 3) && (strcmp(checkable->charrep(), "yes") == 0))
		menu->AppendCheckItem(EvNr, menuname->getData());
	else
		menu->Append(EvNr, menuname->getData());



	((wxFrame*) frame)->Connect( EvNr,  -1, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
          &lb_wxFrame::OnDispatch );

	return ERR_NONE;
/*...e*/
}
/*...e*/
/*...stoggleEvent\9\\9\\9\Handler:0:*/
lbErrCodes LB_STDCALL MyApp::toggleEvent(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, handlername)
	
	UAP(lb_I_Parameter, param)
	QI(uk, lb_I_Parameter, param)

	parameter->setData("handlername");
	param->getUAPString(*&parameter, *&handlername);

	int EvNr = 0;
	
	if (ev_manager->resolveEvent(handlername->getData(), EvNr) == ERR_EVENT_NOTREGISTERED) {
		_CL_LOG << "ERROR: Could not register a menu entry with an unregistered handler!" LOG_
		
		return ERR_EVENT_NOTREGISTERED;
	}

	wxMenuBar* mbar = frame->getMenuBar();

	mbar->Check(EvNr, !mbar->IsChecked(EvNr));

	return err;
}
/*...e*/
/*...sdisableEvent\9\\9\Handler:0:*/
lbErrCodes LB_STDCALL MyApp::disableEvent(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, handlername)
	
	UAP(lb_I_Parameter, param)
	QI(uk, lb_I_Parameter, param)

	parameter->setData("handlername");
	param->getUAPString(*&parameter, *&handlername);

	int EvNr = 0;
	
	if (ev_manager->resolveEvent(handlername->getData(), EvNr) == ERR_EVENT_NOTREGISTERED) {
		_CL_LOG << "ERROR: Could not register a menu entry with an unregistered handler!" LOG_
		
		return ERR_EVENT_NOTREGISTERED;
	}

	wxMenuBar* mbar = frame->getMenuBar();

	mbar->Enable(EvNr, false);

	return err;
}
/*...e*/
/*...senableEvent\9\\9\\9\Handler:0:*/
lbErrCodes LB_STDCALL MyApp::enableEvent(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, handlername)
	
	UAP(lb_I_Parameter, param)
	QI(uk, lb_I_Parameter, param)

	parameter->setData("handlername");
	param->getUAPString(*&parameter, *&handlername);

	int EvNr = 0;
	
	if (ev_manager->resolveEvent(handlername->getData(), EvNr) == ERR_EVENT_NOTREGISTERED) {
		_CL_LOG << "ERROR: Could not register a menu entry with an unregistered handler!" LOG_
		
		return ERR_EVENT_NOTREGISTERED;
	}

	wxMenuBar* mbar = frame->getMenuBar();

	mbar->Enable(EvNr, true);

	return err;
}
/*...e*/
/*...saddButton \9\\9\\9\Handler:0:*/
/**
 * Add a button to the active window.
 *
 * Params:
 *      buttontext:     Text of the button
 *      handlername:    Name of handler
 */
lbErrCodes LB_STDCALL MyApp::addButton(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, buttontext)
	UAP_REQUEST(manager.getPtr(), lb_I_String, handlername)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, x)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, y)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, w)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, h)	
	
	UAP(lb_I_Parameter, param)

	QI(uk, lb_I_Parameter, param)

	parameter->setData("buttontext");
	param->getUAPString(*&parameter, *&buttontext);
	parameter->setData("handlername");
	param->getUAPString(*&parameter, *&handlername);
	parameter->setData("x");
	param->getUAPInteger(*&parameter, *&x);	
	parameter->setData("y");
	param->getUAPInteger(*&parameter, *&y);	
	parameter->setData("w");
	param->getUAPInteger(*&parameter, *&w);	
	parameter->setData("h");
	param->getUAPInteger(*&parameter, *&h);	
	
	int EvNr = 0;
	ev_manager->resolveEvent(handlername->getData(), EvNr);

	wxButton *button = new wxButton(panel, EvNr, buttontext->getData(), 
					wxPoint(x->getData(),y->getData()), 
					wxSize((int) w->getData(),(int) h->getData() ));

	frame->Connect( EvNr,  -1, wxEVT_COMMAND_BUTTON_CLICKED,
	  (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
	    &lb_wxFrame::OnDispatch );

	return ERR_NONE;
}
/*...e*/
/*...saddLabel\9\\9\\9\Handler:0:*/
lbErrCodes LB_STDCALL MyApp::addLabel(lb_I_Unknown* uk) {
	_LOG << "MyApp::addLabel called" LOG_
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, buttontext)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, x)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, y)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, w)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, h)	
	
	UAP(lb_I_Parameter, param)

	QI(uk, lb_I_Parameter, param)

	parameter->setData("labeltext");
	param->getUAPString(*&parameter, *&buttontext);
	parameter->setData("x");
	param->getUAPInteger(*&parameter, *&x);	
	parameter->setData("y");
	param->getUAPInteger(*&parameter, *&y);	
	parameter->setData("w");
	param->getUAPInteger(*&parameter, *&w);	
	parameter->setData("h");
	param->getUAPInteger(*&parameter, *&h);	
	
	wxStaticText *text = new wxStaticText(panel, -1, buttontext->getData(), wxPoint(x->getData(),y->getData()),
					wxSize((int) w->getData(),(int) h->getData() ));

	return ERR_NONE;
}
/*...e*/
/*...saddTextField\9\\9\Handler:0:*/
lbErrCodes LB_STDCALL MyApp::addTextField(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, buttontext)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, x)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, y)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, w)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, h)	
	
	UAP(lb_I_Parameter, param)

	QI(uk, lb_I_Parameter, param)

	parameter->setData("text");
	param->getUAPString(*&parameter, *&buttontext);
	parameter->setData("x");
	param->getUAPInteger(*&parameter, *&x);	
	parameter->setData("y");
	param->getUAPInteger(*&parameter, *&y);	
	parameter->setData("w");
	param->getUAPInteger(*&parameter, *&w);	
	parameter->setData("h");
	param->getUAPInteger(*&parameter, *&h);	
	
	wxTextCtrl *text = new 
	
	wxTextCtrl(panel, -1, buttontext->getData(), wxPoint(x->getData(),y->getData()),
					wxSize((int) w->getData(),(int) h->getData() ));

	return ERR_NONE;
}
/*...e*/
lbErrCodes LB_STDCALL MyApp::addMenu(lb_I_Unknown* uk) {
	return ERR_NONE;
}
/*...e*/
#endif
#ifndef LB_I_EXTENTIONS
/*...sMyFrame:0:*/
// My frame constructor
MyFrame::MyFrame(wxFrame *frame, char *title, int x, int y, int w, int h):
  wxFrame(frame, -1, title, wxPoint(x, y), wxSize(w, h))
{}

void MyFrame::OnVerbose(wxCommandEvent& WXUNUSED(event) )
{
  setVerbose(!isVerbose());
}

/*...sMyFrame\58\\58\OnQuit\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event) )
{
  Close(TRUE);
}
/*...e*/
void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event) )
{
  wxMessageDialog dialog(this, "This demonstrates dynamic event handling",
    "About Dynamic", wxYES_NO|wxCANCEL);

  dialog.ShowModal();
}
/*...e*/
#endif

#ifndef USE_WXWRAPPER_DLL

#ifdef LB_I_EXTENTIONS
/*...slb_wxFrame:0:*/
// My frame constructor
lb_wxFrame::lb_wxFrame(wxFrame *frame, char *title, int x, int y, int w, int h):
  wxFrame(frame, -1, title, wxPoint(x, y), wxSize(w, h))
{
	menu_bar = NULL;
	guiCleanedUp = 0;
}

lb_wxFrame::~lb_wxFrame() {
        _CL_LOG << "lb_wxFrame::~lb_wxFrame() called." LOG_

        if (guiCleanedUp == 0) {
        	_CL_LOG << "lb_wxFrame::~lb_wxFrame() cleans up GUI" LOG_
                if (gui) gui->cleanup();
                _CL_LOG << "lb_wxFrame::~lb_wxFrame() cleaned up GUI" LOG_
                guiCleanedUp = 1;
        } else {
        	_CL_LOG << "lb_wxFrame::~lb_wxFrame() GUI has been cleaned up prior." LOG_
        	_CL_LOG << "********************************************************" LOG_
        }
}

void lb_wxFrame::OnRunLogonWizard(wxCommandEvent& WXUNUSED(event)) {
    wxWizard *wizard = new wxWizard(this, -1, _T("Anmeldung"));

    wxWizardPageSimple *page1 = new wxWizardPageSimple(wizard);

    wxStaticText *text = new wxStaticText(page1, -1, _T("Melden Sie sich nun an.\n"));

    wxSize size = text->GetBestSize();

    wxLogonPage *page2 = new wxLogonPage(wizard);
    wxAppSelectPage *page3 = new wxAppSelectPage(wizard);
    
    wxWizardPageSimple::Chain(page2, page3);
    
    wizard->SetPageSize(size);

    if ( wizard->RunWizard(page1) )
    {
        wxMessageBox(_T("The wizard successfully completed"), _T("That's all"),
                     wxICON_INFORMATION | wxOK);
    }

    wizard->Destroy();
                                             

}
/*...slb_wxFrame\58\\58\OnQuit\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void lb_wxFrame::OnQuit(wxCommandEvent& WXUNUSED(event) )
{
  	/*
  	 * Let the lb_wxGUI class cleanup it's created  and hidden forms.
  	 * The database form sample is a modal form and may be making the
  	 * problem, if it is not destroyed here.
  	 */

  	 
	if (guiCleanedUp == 0) {
		_CL_LOG << "lb_wxFrame::OnQuit(...) cleans up GUI" LOG_
        	if (gui) gui->cleanup();
        	_CL_LOG << "lb_wxFrame::OnQuit(...) cleaned up GUI" LOG_
        	guiCleanedUp = 1;
	}

	UAP_REQUEST(mm.getPtr(), lb_I_PluginManager, PM)
	
	PM->unload();

	Close(TRUE);
}

void lb_wxFrame::OnVerbose(wxCommandEvent& WXUNUSED(event) ) {
    setVerbose(!isVerbose());
}

/*...e*/
/*...slb_wxFrame\58\\58\OnAbout\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void lb_wxFrame::OnAbout(wxCommandEvent& WXUNUSED(event) )
{
  char* buf = strdup(_trans("This is the wxWindows GUI wrapper.\nA interface to any application."));
  char* buf1 = strdup(_trans("About wxWidgets GUI wrapper"));
  wxMessageDialog dialog(NULL, buf, buf1, wxOK);

  dialog.ShowModal();

  free(buf);
  free(buf1);
}
/*...e*/
/*...slb_wxFrame\58\\58\OnCheck\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void lb_wxFrame::OnCheck(wxCommandEvent& WXUNUSED(event) ) {
	char ptr[200] = "";
	sprintf(ptr, "%p for instance %p", menu_bar, this);
	
	_LOG << "Have this instance now: " << ptr LOG_
}
/*...e*/
/*...slb_wxFrame\58\\58\OnBuildMenu\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void lb_wxFrame::OnBuildMenu(wxCommandEvent& WXUNUSED(event) ) {
	wxMenu *menu = new wxMenu;
	wxMenuBar* mbar = NULL;
	
	menu->Append(DYNAMIC_ABOUT, "&About");
	menu->Append(DYNAMIC_QUIT, "E&xit");

	char ptr[200] = "";
	sprintf(ptr, "%p for instance %p", menu_bar, this);
	_LOG << "Request for a menu pointer: " << ptr LOG_
	
	mbar = getMenuBar();
	if (menu_bar) menu_bar->Append(menu, "T&est");

}
/*...e*/
/*...slb_wxFrame\58\\58\OnDispatch\40\wxCommandEvent\38\ event \41\:0:*/
void lb_wxFrame::OnDispatch(wxCommandEvent& event ) {
        switch (event.GetId()) {
        case DYNAMIC_QUIT:
                OnQuit(event);
                break;
        case DYNAMIC_ABOUT:
                OnAbout(event);
                break;
	case DYNAMIC_VERBOSE:
		OnVerbose(event);
		break;
        case DYNAMIC_BUILDMENU:
        	{
        		OnBuildMenu(event);
        	}
        	break;
        default:
                // Delegate all other events
                {
                	lbErrCodes err = ERR_NONE;
			lb_I_Module* m = getModuleInstance();
			
			//if (eman == NULL) {
				REQUEST(m, lb_I_EventManager, eman)
			//}
		
			//if (dispatcher == NULL) {
				REQUEST(m, lb_I_Dispatcher, dispatcher)
				dispatcher->setEventManager(eman.getPtr());
			//}				

			UAP_REQUEST(m, lb_I_Integer, param)
			
			param->setData(event.GetId());
			
			UAP(lb_I_Unknown, uk)
			QI(param, lb_I_Unknown, uk)
		
			UAP_REQUEST(m, lb_I_String, result)
			UAP(lb_I_Unknown, uk_result)
			QI(result, lb_I_Unknown, uk_result)
		
			dispatcher->dispatch(event.GetId(), uk.getPtr(), &uk_result);
                }
                break;
        }
}
/*...e*/

/*
void lb_wxFrame::OnPluginTest(wxCommandEvent& WXUNUSED(event) ) {

	UAP_REQUEST(manager.getPtr(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)

	pl = PM->getFirstMatchingPlugin("lb_I_DatabaseReport");

}
*/
/*...e*/
#endif
#endif

/*...sCleanup helper:0:*/
#ifdef WINDOWS
class cleanUp {
public:
	cleanUp() {
	}
	
	virtual ~cleanUp() {
		unHookAll();
	}
	
};

cleanUp clean_up;
#endif
#ifdef OSX
class cleanUp {
public:
	cleanUp() {
	}
	
	virtual ~cleanUp() {
		_CL_LOG << "Call unHookAll()..." LOG_
		//lbBreak();
		unHookAll();
		_CL_LOG << "Called unHookAll()." LOG_		
	}
	
};

cleanUp clean_up;
#endif
/*...e*/

/*...sWindows based WinMain implementation:0:*/
#ifndef OSX
#ifndef LINUX
wxAppConsole *wxCreateApp()
    {
        wxApp::CheckBuildOptions(wxBuildOptions());
        return new MyApp;
    }

//wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction) &wxCreateApp);
MyApp& wxGetApp() { return *(MyApp *)wxTheApp; }

wxApp* _app = NULL;

int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	//wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction) wxCreateApp);

	char* CONSOLE_DETACH = getenv("CONSOLE_DETACH");

	if (CONSOLE_DETACH == NULL) FreeConsole();
	if ((CONSOLE_DETACH != NULL) && 
	    (strcmp(CONSOLE_DETACH, "no") != 0) &&
	    (strcmp(CONSOLE_DETACH, "NO") != 0) &&
	    (strcmp(CONSOLE_DETACH, "No") != 0) &&
	    (strcmp(CONSOLE_DETACH, "nO") != 0)) FreeConsole();

	TRMemOpen();
	TRMemSetModuleName(__FILE__);
    
	MyApp::SetInitializerFunction(wxCreateApp);
    
	return wxEntry((WXHINSTANCE) hInstance, (WXHINSTANCE) hPrevInstance, lpCmdLine, nCmdShow);
}
#endif
#endif
/*...e*/

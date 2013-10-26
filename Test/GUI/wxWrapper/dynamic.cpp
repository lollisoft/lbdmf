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
// RCS-ID:      $Id: dynamic.cpp,v 1.174.2.8 2013/10/26 04:39:11 lollisoft Exp $
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
            Ginsterweg 4

            65760 Eschborn (germany)
*/
/*...e*/
/*...e*/
/*...sHistory:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.174.2.8 $
 * $Name:  $
 * $Id: dynamic.cpp,v 1.174.2.8 2013/10/26 04:39:11 lollisoft Exp $
 *
 * $Log: dynamic.cpp,v $
 * Revision 1.174.2.8  2013/10/26 04:39:11  lollisoft
 * Fixes on Linux related to socket and transfer classes.
 *
 * Revision 1.174.2.7  2013/01/31 06:46:47  lollisoft
 * Fixed application reload bug. After a reload on Mac OS X images could no more get loaded from application bundle.
 *
 * Revision 1.174.2.6  2012/11/19 07:38:57  lollisoft
 * Fixed remaining reload issues.
 *
 * Revision 1.174.2.5  2012/11/18 08:38:19  lollisoft
 * Many changes that help improving unit tests. They mainly include application
 * reload capabilities, but that didn't yet work in GUI. Some menu entries are
 * doubled, data isn't valid (NULL pointer).
 *
 * Revision 1.174.2.4  2012/10/09 05:39:48  lollisoft
 * Removed old code from the very beginning.
 *
 * Revision 1.174.2.3  2012/09/16 07:16:15  lollisoft
 * Moved call to plugin installers after creation of the splash screen.
 *
 * Revision 1.174.2.2  2012/06/07 17:29:55  lollisoft
 * Fixed application exit issues. The dispatcher and event manager was
 * instantiated earlyer than a string or any other class from lbclasses.
 * The error was hidden a long time when logging was active. This also
 * instantiated a class (logger) within lbclasses that 'fixed' the order of
 * module dependencies.
 *
 * Revision 1.174.2.1  2012/06/05 11:54:43  lollisoft
 * Got a working application initialization and unload. Also autologin works
 * when loading application model from file.
 *
 * Revision 1.174  2011/10/16 08:40:57  lollisoft
 * Refactoring produced again some uninitialized variables that havs been fixed now. The app seems to start and esit without errors.
 *
 * Revision 1.173  2011/10/15 21:47:13  lollisoft
 * Removed all code that is obsolete. Current code compiles but still does not run.
 *
 * Revision 1.172  2011/09/20 06:58:29  lollisoft
 * Added optional logging control via environment variable.
 *
 * Revision 1.171  2011/02/27 10:34:00  lollisoft
 * Changed all copyright entries addresses to match my current postal address.
 *
 * Revision 1.170  2010/01/14 17:31:25  lollisoft
 * More changes for interceptor functionality, but crashes on Mac OS X (PPC).
 *
 * Revision 1.169  2009/12/06 19:21:21  lollisoft
 * Modified build process to use precompiled files.
 * Corrected the long build time problem. It is located in the _LOG macro.
 * Updated wxPropgrid to 1.4.9.1 and updated building against wxMSW 2.8.10.
 *
 * Build works, but running the application fails with not properly initialized error.
 * (0xc0000005)
 *
 * Also updated the iss files for the new planned release.
 *
 * Revision 1.168  2009/11/25 21:45:54  lollisoft
 * Fixed copy & paste bug.
 *
 * Revision 1.167  2009/11/08 11:49:32  lollisoft
 * Implemented 'unit test' like capabilities. The TestPlugin in the Plugins directory demonstrates the usage. Yet missing is a real test listener and stuff to display results. But it shows a working unit test mechanism using plugins.
 *
 * Corrected mkmk to find also include files in <> brackets.
 *
 * Corrected make system to work correctly with the new mkmk version. There may be a performance problem when compiling tvision code, thus that target is deactivated.
 *
 * Fixed some warnings.
 *
 * Revision 1.166  2009/09/03 17:32:43  lollisoft
 * Corrected exit behaviour when clicking on window close button.
 *
 * Revision 1.165  2009/07/19 22:42:12  lollisoft
 * Using the new plugin install method per plugin module.
 *
 * Revision 1.164  2009/07/12 10:46:54  lollisoft
 * Added frame to fix hang at exit if splash is still shown.
 *
 * Revision 1.163  2009/07/11 19:44:15  lollisoft
 * Added NO_SPLASH option in environment.
 *
 * Revision 1.162  2009/07/05 00:57:31  lollisoft
 * Added new tableview dialog class and enabled switching
 * between table view and form view. This does not interfer
 * with panel and dialog view - as these are different flags.
 *
 * Revision 1.161  2009/06/29 10:24:09  lollisoft
 * Renamed a dispatch parameter.
 *
 * Revision 1.160  2009/06/10 11:46:55  lollisoft
 * Added code to pass the application name and removed hardcoded application name.
 *
 * Revision 1.159  2009/06/02 20:37:31  lollisoft
 * Using always wxSTAY_ON_TOP from now on and deactivated calling Raise.
 *
 * Revision 1.158  2009/06/02 19:33:10  lollisoft
 * Added some debug messages to determine a crash in installation.
 *
 * Revision 1.157  2009/03/19 17:11:00  lollisoft
 * Added a flag to avoid multiple calls to load the XRC resource.
 *
 * Revision 1.156  2009/03/12 19:03:16  lollisoft
 * Added optional check for splash screen inside of bundle.
 *
 * Revision 1.155  2008/08/08 11:30:30  lollisoft
 * Tries on Linux
 *
 * Revision 1.154  2008/05/24 23:15:51  lollisoft
 * Removed a hardcoded breakpoint :-)
 *
 * Revision 1.153  2008/05/21 22:25:10  lollisoft
 * Some improvements for working with Sqlite database.
 *
 * Revision 1.152  2008/05/19 06:42:31  lollisoft
 * Added code to check for availability of any database. Corrected splash screen and modal dialog problems.
 *
 * Revision 1.151  2008/05/14 18:36:16  lollisoft
 * Save moved into the frame destructor.
 *
 * Revision 1.150  2008/02/18 19:57:19  lollisoft
 * Added function to get a directory from the user.
 *
 * Revision 1.149  2008/02/09 23:18:20  lollisoft
 * Reactivated splash screen 'always on top' for Mac.
 *
 * Revision 1.148  2007/11/22 16:11:35  lollisoft
 * Added some logging messages.
 *
 * Revision 1.147  2007/11/18 19:40:41  lollisoft
 * Added handler to load xrc file.
 *
 * Revision 1.146  2007/11/16 20:53:19  lollisoft
 * Initial DatabaseLayer based lb_I_Query and lb_I_Database classes. Rudimentary readonly queries are working.
 *
 * But also full cursor functionality emulation works.
 *
 * More than simple queries are not tested.
 * (No order, where, join and subqueries)
 *
 * See DatabaseLayerWrapperTest.
 *
 * Revision 1.145  2007/10/11 13:38:40  lollisoft
 * Propably completed offline capability from system database.
 *
 * Revision 1.144  2007/09/30 14:24:37  lollisoft
 * Check for exsisting splash screen to avoid error messages.
 *
 * Revision 1.143  2007/09/18 12:29:33  lollisoft
 * Added code to find splash screen on fallback location.
 *
 * Revision 1.142  2007/08/29 10:15:18  lollisoft
 * Deactivated code to show property panel.
 *
 * Revision 1.141  2007/08/28 14:54:21  lollisoft
 * Solved layout issues with properties. If it is opened, no new window would be created. If it was closed the hidden
 * property grid window will be reused.
 *
 * Revision 1.140  2007/08/06 19:10:29  lollisoft
 * Improved installation process on Windows.
 *
 * Revision 1.139  2007/07/13 12:28:37  lollisoft
 * Remaining code changes done and fixed database login bug.
 *
 * Revision 1.138  2007/07/07 18:12:40  lollisoft
 * Some type conflicts resolved.
 *
 * Revision 1.137  2007/06/16 10:26:54  lollisoft
 * This changes let the application successfully run under Solaris. Also a bug is fixed that caused a crash at application exit.
 *
 * Revision 1.136  2007/06/06 21:33:24  lollisoft
 * Made bugfixes and enhancements that were required.
 *
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

#include <lbDMF_wxPrec.h>

/*...swx ifdef\39\s:0:*/
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef LBDMF_PREC
#ifdef LB_I_EXTENTIONS
#include <lbConfigHook.h>
#endif
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
#include <wx/notebook.h>
#include <wx/file.h>
#include <wx/fs_zip.h>
#include <wx/xrc/xmlres.h>
/*...e*/

// ID for the menu commands
#define DYNAMIC_QUIT		1000
#define DYNAMIC_TEXT		1001
#define DYNAMIC_ABOUT		1002
#define DYNAMIC_BUILDMENU	1003
#define DYNAMIC_TEST1		1004
#define DYNAMIC_TEST2       1005
#define DYNAMIC_VERBOSE		1006

#ifdef USE_WXWRAPPER_DLL
#include "wx/propgrid/propgrid.h"
#include <wxWrapperDLL.h>
#endif
#ifdef OSX
    #include <dlfcn.h>
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
		frame = NULL;
	}

	/**
	 * Deletes the lb_I_GUI instance used for independent GUI component handlers.
	 */
	virtual ~MyApp() {
		_LOG << "wxApp::~MyApp() called." LOG_
/*
 * It seems, that frame was deleted prior !!
 */

		if (wxGUI) delete wxGUI;
	}

	/**
	 * Main initialisation member. It shows the integration of my framework into a wxWidgets application.
	 */
    bool OnInit(void);

	void FlushMenubarQueue();
	void FlushMenuentryQueue();

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
	lb_I_Unknown* LB_STDCALL getUnknown();

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

	lbErrCodes LB_STDCALL removeMenuBar(lb_I_Unknown* uk);
	
	/**
	 * Event handler to add a menu entry in a given menu bar name.
	 * \note These handlers should not called by the user of lbDMF. The programmer would use lb_I_MetaApplication to abstract from the real GUI implementation.
	 */
	lbErrCodes LB_STDCALL addMenuEntry(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL removeMenuEntry(lb_I_Unknown* uk);

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

		lbErrCodes LB_STDCALL setXRCFile(lb_I_Unknown* uk);

		lbErrCodes LB_STDCALL askForDirectory(lb_I_Unknown* uk);

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
		int RemoveMenuBar;
        int AddMenuEntry;
        int RemoveMenuEntry;
        int AddLabel;
        int AddTextField;
        int AddButton;
        int _enableEvent;
        int _disableEvent;
        int _toggleEvent;
        int _askYesNo;
		int _setXRCFile;
		int _askForDirectory;
	int AskOpenFileReadStream;

	bool _XRCFileSet;


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

	// If the frame is not yet created, queue any menu creation events.
	UAP(lb_I_Container, menubarQueue)
	UAP(lb_I_Container, menuentryQueue)

};
/*...e*/

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
	_LOG << "MyApp::OnExit() called." LOG_
	lbErrCodes err = ERR_NONE;

	if (metaApp == NULL) {
		REQUEST(getModuleInstance(), lb_I_MetaApplication, metaApp)
	}


	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

	_CL_LOG << "Unload application ..." LOG_

	metaApp->disableStatusbar();

	metaApp->unloadApplication();
	metaApp->uninitialize();

	_CL_LOG << "Unloaded application." LOG_

	//metaApp->save();

	PM->unload();

	_CL_LOG << "Unloaded plugins." LOG_

	return 0;
}
/*...e*/

void MyApp::FlushMenubarQueue() {
	if (menubarQueue != NULL) {
		menubarQueue->finishIteration();
		while (menubarQueue->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			uk = menubarQueue->nextElement();
			addMenuBar(*&uk);
		}
		menubarQueue--;
		menubarQueue = NULL;
	}
}

void MyApp::FlushMenuentryQueue() {
	_LOG << "MyApp::FlushMenuentryQueue() called." LOG_
	if (menuentryQueue != NULL) {
		menuentryQueue->finishIteration();
		while (menuentryQueue->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			uk = menuentryQueue->nextElement();
			addMenuEntry(*&uk);
		}
		menuentryQueue--;
		menuentryQueue = NULL;
	}
}


/*...sMyApp\58\\58\OnInit\40\void\41\:0:*/
// `Main program' equivalent, creating windows and returning main app frame
bool MyApp::OnInit(void)
{
    char b[100] = "";
    wxStopWatch sw;

    UAP(lb_I_Module, mm)
    mm = getModuleInstance();
	_XRCFileSet = false;

    if (mm == NULL) {
	wxMessageDialog dialog(NULL, "Module manager not found. could not run application.", "Error", wxOK);

	dialog.ShowModal();
	return FALSE;
    }

	wxString appname = GetAppName();
	_LOGALWAYS << "Application " << appname.c_str() << " starts up." LOG_


    UAP_REQUEST(getModuleInstance(), lb_I_String, string)
    UAP_REQUEST(getModuleInstance(), lb_I_Database, tempDB) // Preload this module
    UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
    UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaApp)
    UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
	REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)

    if (disp == NULL) {
		_LOG << "Fatal: Have not got a dispatcher!" LOG_
    }

	disp->setEventManager(ev_manager.getPtr());

	// Register Events, that I provide

	ev_manager->registerEvent("AddMenu", AddMenu);
	ev_manager->registerEvent("AddMenuBar", AddMenuBar);
	ev_manager->registerEvent("RemoveMenuBar", RemoveMenuBar);
	ev_manager->registerEvent("AddButton", AddButton);

	ev_manager->registerEvent("showLeft", AddButton);

	ev_manager->registerEvent("AddMenuEntry", AddMenuEntry);
	ev_manager->registerEvent("RemoveMenuEntry", RemoveMenuEntry);
	ev_manager->registerEvent("AddLabel", AddLabel);
	ev_manager->registerEvent("AddTextField", AddTextField);
	ev_manager->registerEvent("askOpenFileReadStream", AskOpenFileReadStream);
	ev_manager->registerEvent("askYesNo", _askYesNo);
	ev_manager->registerEvent("enableEvent", _enableEvent);
	ev_manager->registerEvent("disableEvent", _disableEvent);
	ev_manager->registerEvent("toggleEvent", _toggleEvent);
	ev_manager->registerEvent("setXRCFile", _setXRCFile);
	ev_manager->registerEvent("askForDirectory", _askForDirectory);

	/* Initialize early menu creation queues in case the frame has not been created yet.
	 * The menu handlers only works after registered handler functions as of call to
	 * registerEventHandler(*&disp);
	 *
	 * But ensure that before.
	 */
	if (menubarQueue == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, menubarQueue)
	}

	if (menuentryQueue == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, menuentryQueue)
	}

	registerEventHandler(*&disp);

    /// \todo Find leak.
    metaApp++;

    lbErrCodes err = ERR_NONE;

    if (wxGUI == NULL) {
        wxGUI = new lb_wxGUI();
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

	// Preload to enable flag modifications in plugins. Such as loading from database instead file
    if (metaApp->load() != ERR_NONE) {
	// If there are no files yet, then this is a wrong interpretation
	//PM->unload();
	//return false;
    }

    SetTopWindow(frame);

    PM->initialize();

	/* If a plugin module needs to install something, it happens here.
	 * Do not move this after the splash screen as it may block when any
	 * installer asks the user something.
	 */
	//PM->runInstallers();

    wxImage::AddHandler(new wxPNGHandler);

    bool no_splash = false;
   	char* NO_SPLASH = getenv("NO_SPLASH");

    if (NO_SPLASH != NULL &&
        (
         (strcmp(NO_SPLASH, "Yes") == 0) ||
         (strcmp(NO_SPLASH, "YES") == 0) ||
         (strcmp(NO_SPLASH, "yes") == 0))
        ) no_splash = true;

    lbSplashScreen* splash = NULL;
    wxBitmap bitmap;
    if (!no_splash && wxFile::Exists("splash.png") && bitmap.LoadFile("splash.png", wxBITMAP_TYPE_PNG))
    {
		splash = new lbSplashScreen(wxGUI, bitmap,
		wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
		6000, frame, -1, ::wxGetMousePosition(), wxDefaultSize,
#ifndef OSX
		wxSIMPLE_BORDER|wxSTAY_ON_TOP); //|wxSTAY_ON_TOP);
#endif
#ifdef OSX
		wxSIMPLE_BORDER|wxSTAY_ON_TOP);
#endif
		wxGUI->splashCreated();
    } else if (wxFile::Exists("/usr/share/lbdmf/splash.png") && bitmap.LoadFile("/usr/share/lbdmf/splash.png", wxBITMAP_TYPE_PNG)) {
		splash = new lbSplashScreen(wxGUI, bitmap,
									wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
									6000, frame, -1, wxDefaultPosition, wxDefaultSize,
#ifndef OSX
									wxSIMPLE_BORDER|wxSTAY_ON_TOP); //|wxSTAY_ON_TOP);
#endif
#ifdef OSX
		wxSIMPLE_BORDER|wxSTAY_ON_TOP);
#endif
		wxGUI->splashCreated();
	}
#ifdef OSX
	else if (wxFile::Exists("./" + appname + ".app/Contents/Resources/splash.png") && bitmap.LoadFile("./" + appname + ".app/Contents/Resources/splash.png", wxBITMAP_TYPE_PNG)) {
		splash = new lbSplashScreen(wxGUI, bitmap,
								wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
								6000, frame, -1, wxDefaultPosition, wxDefaultSize,
								wxSIMPLE_BORDER|wxSTAY_ON_TOP);
		wxGUI->splashCreated();
	}
#endif

	PM->runInstallers();

	wxYield();

    if (metaApp != NULL) {
		metaApp->setProcessName(appname.c_str());
        metaApp->initialize();

		//if (metaApp->isPropertyPaneLayoutLeft()) metaApp->showPropertyPanel();
		//if (metaApp->isPropertyPaneLayoutFloating()) metaApp->showPropertyPanel();
		if (metaApp->getGUIMaximized()) frame->Maximize();
    }

    _LOG << "Start enumerating plugins to call their autorun function." LOG_

    if (PM->beginEnumPlugins()) {

    while (TRUE) {
        UAP(lb_I_Plugin, pl)
        pl = PM->nextPlugin();
        if (pl == NULL) break;
            pl->autorun();
        }
    }

	FlushMenubarQueue();
	FlushMenuentryQueue();

    frame->Show(TRUE);
	
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

lb_I_Unknown* LB_STDCALL MyApp::getUnknown() {
	UAP(lb_I_Unknown, uk)
	queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__); 
	uk++;
	return uk.getPtr();
}

/*...sMyApp\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL MyApp::registerEventHandler(lb_I_Dispatcher* disp) {
	// We provide some menu manipulation

	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addMenu, "AddMenu");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addMenuBar, "AddMenuBar");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addMenuEntry, "AddMenuEntry");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::removeMenuBar, "RemoveMenuBar");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::removeMenuEntry, "RemoveMenuEntry");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addButton, "AddButton");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addLabel, "AddLabel");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addTextField, "AddTextField");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::askOpenFileReadStream, "askOpenFileReadStream");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::askYesNo, "askYesNo");

	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::enableEvent, "enableEvent");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::disableEvent, "disableEvent");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::toggleEvent, "toggleEvent");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::setXRCFile, "setXRCFile");

	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::askForDirectory, "askForDirectory");


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
lbErrCodes LB_STDCALL MyApp::askForDirectory(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, filepath)
	UAP_REQUEST(getModuleInstance(), lb_I_String, defaultdir)
	UAP_REQUEST(getModuleInstance(), lb_I_String, after)

	UAP(lb_I_Parameter, param)

	QI(uk, lb_I_Parameter, param)

	wxDirDialog dirDialog(NULL, _trans("Choose a directory"));

	if (dirDialog.ShowModal() == wxID_OK) {
		parameter->setData("result");
		filepath->setData(dirDialog.GetPath().c_str());
		param->setUAPString(*&parameter, *&filepath);
	} else {
		parameter->setData("result");
		filepath->setData("");
		param->setUAPString(*&parameter, *&filepath);
	}

	return err;
}


lbErrCodes LB_STDCALL MyApp::setXRCFile(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	if (_XRCFileSet) return ERR_NONE;

	_XRCFileSet = true;

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, filename)

	UAP(lb_I_Parameter, param)

	QI(uk, lb_I_Parameter, param)

	parameter->setData("xrcfilename");
	param->getUAPString(*&parameter, *&filename);

    wxXmlResource::Get()->InitAllHandlers();
    wxFileSystem::AddHandler(new wxZipFSHandler);
    wxXmlResource::Get()->Load(filename->charrep());


	return ERR_NONE;
}

/*...saskYesNo\9\\9\\9\Handler:0:*/
lbErrCodes LB_STDCALL MyApp::askYesNo(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
	UAP_REQUEST(getModuleInstance(), lb_I_String, result)

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

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, after)

	UAP(lb_I_Parameter, param)

	QI(uk, lb_I_Parameter, param)

	if (frame == NULL) {
		UAP(lb_I_KeyBase, mbarkey)

		parameter->setData("name");
		param->getUAPString(*&parameter, *&name);
		QI(name, lb_I_KeyBase, mbarkey)

		if (menubarQueue->exists(&mbarkey) != 0) {
			menubarQueue->remove(&mbarkey);
		}

		menubarQueue->insert(&uk, &mbarkey);
	} else {
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

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, menubar)
	UAP_REQUEST(getModuleInstance(), lb_I_String, menuname)
	UAP_REQUEST(getModuleInstance(), lb_I_String, handlername)
	UAP_REQUEST(getModuleInstance(), lb_I_String, checkable)


	UAP(lb_I_Parameter, param)

	QI(uk, lb_I_Parameter, param)

	if (frame == NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, key)
		UAP(lb_I_KeyBase, menuentrykey)

		parameter->setData("menubar");
		param->getUAPString(*&parameter, *&menubar);
		parameter->setData("menuname");
		param->getUAPString(*&parameter, *&menuname);
		parameter->setData("handlername");
		param->getUAPString(*&parameter, *&handlername);

		*key = *&menubar;
		*key += *&menuname;
		*key += *&handlername;

		QI(key, lb_I_KeyBase, menuentrykey)

		if (menuentryQueue->exists(&menuentrykey) != 0) {
			menuentryQueue->remove(&menuentrykey);
		}
		_LOG << "Frame not yet up. Put new menu entry into the queue. '" << menuentrykey->charrep() << "'" LOG_
		menuentryQueue->insert(&uk, &menuentrykey);
	} else {
		parameter->setData("menubar");
		param->getUAPString(*&parameter, *&menubar);
		parameter->setData("menuname");
		param->getUAPString(*&parameter, *&menuname);
		parameter->setData("handlername");
		param->getUAPString(*&parameter, *&handlername);

		if ((menubar->charrep() == NULL) || (menuname->charrep() == NULL) || (handlername->charrep() == NULL)) {
			_LOG << "Error: There are some parameters with NULL pointers!" LOG_
			if ((menubar->charrep() == NULL)) {
				*menubar = "Unknown menubar";
			}
			if ((menuname->charrep() == NULL)) {
				*menuname = "Unknown menuname";
			}
			if ((handlername->charrep() == NULL)) {
				*handlername = "Unknown handlername";
			}
		}

		_LOGERROR << "Add a menu entry at '" << menubar->charrep() << "' with '" << menuname->charrep() << "' that handles '" << handlername->charrep() << "'" LOG_


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

		int index;

		index = mbar->FindMenu(wxString(menubar->getData()));

		if (index == wxNOT_FOUND) {
			_CL_LOG << "ERROR: Programming error. Forgotten to create the required menu. Do it here." LOG_
			wxMenu *menu = new wxMenu;
			mbar->Append(menu, menubar->getData());
			index = mbar->FindMenu(wxString(menubar->getData()));
		}

		wxMenu* menu = mbar->GetMenu(index);


		if ((param->Count() > 3) && (strcmp(checkable->charrep(), "yes") == 0))
			menu->AppendCheckItem(EvNr, menuname->getData());
		else
			menu->Append(EvNr, menuname->getData());

		((wxFrame*) frame)->Connect( EvNr,  -1, wxEVT_COMMAND_MENU_SELECTED,
									(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
									&lb_wxFrame::OnDispatch );
	}


	return ERR_NONE;
/*...e*/
}
/*...e*/
/*...sremoveMenuBar\9\\9\\9\Handler:0:*/
lbErrCodes LB_STDCALL MyApp::removeMenuBar(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)

	UAP(lb_I_Parameter, param)

	QI(uk, lb_I_Parameter, param)

	if (frame == NULL) {
		_LOGERROR << "MyApp::removeMenuBar(): Illegal function call. The frame is NULL." LOG_
	} else {
		parameter->setData("name");
		param->getUAPString(*&parameter, *&name);

		wxMenuBar* mbar = frame->getMenuBar();

		int pos = 0;

		if (mbar) {
			wxString m = wxString(name->getData());
			pos = mbar->FindMenu(m);
			
			if (pos != wxNOT_FOUND)
			{
				wxMenu* menu = mbar->Remove(pos);
				delete menu;
			}
		}
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
lbErrCodes LB_STDCALL MyApp::removeMenuEntry(lb_I_Unknown* uk) {
/*...scode:0:*/
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, menubar)
	UAP_REQUEST(getModuleInstance(), lb_I_String, menuname)


	UAP(lb_I_Parameter, param)

	QI(uk, lb_I_Parameter, param)

	if (frame == NULL) {
		_LOGERROR << "MyApp::removeMenuBar(): Illegal function call. The frame is NULL." LOG_
	} else {
		parameter->setData("menubar");
		param->getUAPString(*&parameter, *&menubar);
		parameter->setData("menuname");
		param->getUAPString(*&parameter, *&menuname);

		if ((menubar->charrep() == NULL) || (menuname->charrep() == NULL)) {
			_LOG << "Error: There are some parameters with NULL pointers!" LOG_
			return err;
		}

		_LOG << "Remove a menu entry at '" << menubar->charrep() << "' with '" << menuname->charrep() << "'" LOG_

		wxMenuBar* mbar = frame->getMenuBar();

		int index;

		index = mbar->FindMenu(wxString(menubar->getData()));

		if (index == wxNOT_FOUND) {
			_LOGERROR << "ERROR: Programming error. Forgotten to create the required menu. Do it here." LOG_
			return err;
		}

		wxMenu* menu = mbar->GetMenu(index);

		int mid = menu->FindItem(menuname->charrep());
		
		if (mid != wxNOT_FOUND)
		{
			menu->Destroy(mid);
		}
	}

	return ERR_NONE;
/*...e*/
}
/*...e*/
/*...stoggleEvent\9\\9\\9\Handler:0:*/
lbErrCodes LB_STDCALL MyApp::toggleEvent(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, handlername)

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

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, handlername)

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

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, handlername)

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

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, buttontext)
	UAP_REQUEST(getModuleInstance(), lb_I_String, handlername)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, x)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, y)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, w)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, h)

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

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, buttontext)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, x)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, y)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, w)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, h)

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

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, buttontext)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, x)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, y)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, w)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, h)

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

/*...sCleanup helper:0:*/
#ifdef WINDOWS
class cleanUp {
public:
	cleanUp() {
	}

	virtual ~cleanUp() {
		_CL_LOG << "cleanUp::~cleanUp() unloads all modules." LOG_
		unHookAll();
		_CL_LOG << "cleanUp::~cleanUp() unloaded all modules." LOG_
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
		_CL_LOG << "cleanUp::~cleanUp() unloads all modules." LOG_
		unHookAll();
		_CL_LOG << "cleanUp::~cleanUp() unloaded all modules." LOG_
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
        //wxApp::CheckBuildOptions(wxBuildOptions());
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
	char* LOGGING = getenv("LOGGING");

	// Default
	setLogActivated(false);
	if (LOGGING != NULL) {
		if ((strcmp(LOGGING, "no") != 0) && (strcmp(LOGGING, "NO") != 0) && (strcmp(LOGGING, "No") != 0) && (strcmp(LOGGING, "nO") != 0)) 
		// Activate
			setLogActivated(true);
		else
			setLogActivated(false);
	}
	
	if (CONSOLE_DETACH == NULL) FreeConsole();
	if ((CONSOLE_DETACH != NULL) &&
	    (strcmp(CONSOLE_DETACH, "no") != 0) &&
	    (strcmp(CONSOLE_DETACH, "NO") != 0) &&
	    (strcmp(CONSOLE_DETACH, "No") != 0) &&
	    (strcmp(CONSOLE_DETACH, "nO") != 0)) FreeConsole();

	TRMemOpen();
	TRMemSetModuleName(__FILE__);

	MyApp::SetInitializerFunction(wxCreateApp);

	return wxEntry((HINSTANCE) hInstance, (HINSTANCE) hPrevInstance, lpCmdLine, nCmdShow);
}
#endif
#endif
/*...e*/

# Global makefile to build all sub modules
# **************************************************************
# * $Locker:  $
# * $Revision: 1.139 $
# * $Name:  $
# * $Id: Makefile,v 1.139 2007/10/13 18:32:24 lollisoft Exp $
# *
# * $Log: Makefile,v $
# * Revision 1.139  2007/10/13 18:32:24  lollisoft
# * Try to add xsl, xmi and UML sample files.
# *
# * Revision 1.138  2007/09/28 18:26:34  lollisoft
# * Some bugfixes on Windows regarding xslt processing.
# *
# * Revision 1.137  2007/09/18 12:22:42  lollisoft
# * Added splash screen image to the correct install location.
# *
# * Revision 1.136  2007/09/18 09:02:53  lollisoft
# * Try again from SuSE specification. (http://forgeftp.novell.com//library/SUSE%20Package%20Conventions/spc.pdf)
# *
# * Revision 1.135  2007/09/18 06:49:26  lollisoft
# * Added desktop file to /share/applications.
# *
# * Revision 1.134  2007/09/17 11:07:56  lollisoft
# * Added desktop symbol to Linux installation. Small correction.
# *
# * Revision 1.133  2007/09/17 11:06:24  lollisoft
# * Added desktop symbol to Linux installation.
# *
# * Revision 1.132  2007/09/16 23:02:50  lollisoft
# * Corrected toolbar image path creation.
# *
# * Revision 1.131  2007/09/16 21:40:02  lollisoft
# * Other place for toolbar images.
# *
# * Revision 1.130  2007/09/16 16:18:47  lollisoft
# * Using copy script without creating it. (Added to repo)
# *
# * Revision 1.129  2007/09/16 13:51:51  lollisoft
# * Try to echo into o script.
# *
# * Revision 1.128  2007/09/16 12:25:35  lollisoft
# * Trouble with special characters.
# *
# * Revision 1.127  2007/09/16 09:44:05  lollisoft
# * Try to use tested ldd command to include required wxWidgets libraries.
# *
# * Revision 1.126  2007/09/12 08:11:11  lollisoft
# * Deacivated copying wx library.
# *
# * Revision 1.125  2007/08/06 19:10:29  lollisoft
# * Improved installation process on Windows.
# *
# * Revision 1.124  2007/07/08 16:50:27  lollisoft
# * Removed some targets. Last removal failed ??
# *
# * Revision 1.123  2007/07/08 16:30:29  lollisoft
# * Removed some targets in rpmbuild verion.
# *
# * Revision 1.122  2007/07/07 16:37:32  lollisoft
# * Changes to let xslt code work.
# *
# * Revision 1.121  2007/06/16 10:26:51  lollisoft
# * This changes let the application successfully run under Solaris. Also a bug is fixed that caused a crash at application exit.
# *
# * Revision 1.120  2007/05/14 19:19:14  lollisoft
# * Unfinished changes. Go to Linux.
# *
# * Revision 1.119  2007/04/22 14:05:20  lollisoft
# * Many changes due to client/server redesign.
# *
# * Revision 1.118  2007/02/28 19:24:29  lollisoft
# * New plugin compiles under Mac OS X.
# *
# * Revision 1.117  2007/02/27 21:40:34  lollisoft
# * Added new plugin
# *
# * Revision 1.116  2006/12/10 17:05:24  lollisoft
# * Other changes under Mac OS X.
# *
# * Revision 1.115  2006/10/22 18:34:36  lollisoft
# * Many memory leaks resolved, but they were caused by small errors :-(
# * This is also a sync.
# *
# * Revision 1.114  2006/07/17 17:37:45  lollisoft
# * Changes dueto bugfix in plugin manager. Repeadable iterator problem.
# * Not correctly finished the iteration, thus plugins in the same DLL wouldn't
# * be found any more after first query.
# *
# * Code works well with improved trmem library, but there is still a crash in
# * database classes (pgODBC library).
# *
# * Revision 1.113  2006/04/20 12:20:31  lollisoft
# * Changed make order to catch up all targets before propably non existing directories.
# *
# * Revision 1.112  2006/04/20 11:40:32  lollisoft
# * Added creation rules for ~/bin ~/lib and ~/plugins into the Mac OS X target list.
# *
# * Revision 1.111  2006/04/16 12:01:19  lollisoft
# * Missed addition of propgrid target.
# *
# * Revision 1.110  2006/04/16 10:10:43  lollisoft
# * Added wxPropgrid framework rule.
# *
# * Revision 1.109  2006/04/11 13:40:05  lollisoft
# * Added making propgrid module.
# *
# * Revision 1.108  2006/03/15 07:24:14  lollisoft
# * Moved Windows module make ordering.
# *
# * Revision 1.107  2006/03/09 09:03:10  lollisoft
# * Missing ALLDIRS.
# *
# * Revision 1.106  2006/03/07 09:40:28  lollisoft
# * Removed some targets in rpm build
# *
# * Revision 1.105  2006/03/06 13:10:31  lollisoft
# * Use local libdir for pulling wx library
# *
# * Revision 1.104  2006/03/06 09:17:18  lollisoft
# * Again wrong name
# *
# * Revision 1.103  2006/03/06 08:58:45  lollisoft
# * Wrong module name in installation
# *
# * Revision 1.102  2006/03/05 10:09:57  lollisoft
# * Wrong wx library name
# *
# * Revision 1.101  2006/03/04 22:18:17  lollisoft
# * Corrected library dependencies and build names
# *
# * Revision 1.100  2006/03/04 17:18:55  lollisoft
# * Bugfix
# *
# * Revision 1.99  2006/03/04 17:03:17  lollisoft
# * Symlinks do not simply appear in rpm's
# *
# * Revision 1.98  2006/03/04 16:41:23  lollisoft
# * Bugfix
# *
# * Revision 1.97  2006/03/04 16:24:20  lollisoft
# * Added creation of symlinks while installation.
# *
# * Revision 1.96  2006/03/04 12:18:18  lollisoft
# * Try to include wx libraries
# *
# * Revision 1.95  2006/03/03 16:16:40  lollisoft
# * Changes in shared library naming and linking against.
# *
# * Revision 1.94  2006/03/02 20:32:28  lollisoft
# * Minor changes under Windows
# *
# * Revision 1.93  2006/03/02 16:39:29  lollisoft
# * Use prefix for libraries.
# *
# * Revision 1.92  2006/03/02 13:10:40  lollisoft
# * Missing -p
# *
# * Revision 1.91  2006/03/02 13:06:58  lollisoft
# * Corrected creation of target directories
# *
# * Revision 1.90  2006/03/02 13:01:18  lollisoft
# * Added creation of target directories
# *
# * Revision 1.89  2006/03/02 12:35:22  lollisoft
# * Modified existing clean target and added install-strip target
# *
# * Revision 1.88  2006/03/01 11:34:46  lollisoft
# * Activated RPMBUILD section
# *
# * Revision 1.87  2006/03/01 11:30:51  lollisoft
# * Test RPMBUILD failure
# *
# * Revision 1.86  2006/02/28 23:11:59  lollisoft
# * Try -k
# *
# * Revision 1.85  2006/02/28 20:23:04  lollisoft
# * Test existence of ../AppDevelopment
# *
# * Revision 1.84  2006/02/28 19:40:04  lollisoft
# * Removed unused vendor targets
# *
# * Revision 1.83  2006/02/28 11:26:58  lollisoft
# * Set TARGETFRAMEWORK to so for Linux
# *
# * Revision 1.82  2006/02/26 23:46:18  lollisoft
# * Changed build method for shared libraries under Mac OS X
# * to be frameworks. These would be embedable into the
# * application bundle - thus enables better install method.
# *
# * Revision 1.81  2006/02/24 14:25:23  lollisoft
# * Fix wrong path
# *
# * Revision 1.80  2006/02/21 19:35:50  lollisoft
# * Implemented autoload mechanism of last loaded application.
# * It demonstrates the new capabilities operating with files.
# *
# * Revision 1.79  2006/02/16 22:48:38  lollisoft
# * Tested last wxAUI layout changes under Linux. It builds and runs.
# *
# * Revision 1.78  2006/02/15 12:47:12  lollisoft
# * Added wxAUI target.
# *
# * Revision 1.77  2006/01/29 09:36:33  lollisoft
# * Don't build TVision. It should completely be in my private makefile.
# *
# * Revision 1.76  2006/01/20 00:58:24  lollisoft
# * Changed order to enable building AppDevelopment tree.
# * This is a hook for users of lbDMF framework.
# *
# * Revision 1.75  2006/01/10 23:37:42  lollisoft
# * Added Goldparser for usability testing.
# *
# * Revision 1.74  2005/12/06 17:04:25  lollisoft
# * Last make problems under Linux
# *
# * Revision 1.73  2005/12/06 15:54:56  lollisoft
# * Changes let the GUI work properly in debug mode. But there is a NULL
# * pointer exeption in release mode near opening a database form.
# *
# * Testing on Mac OS X and Linux.
# *
# * Revision 1.72  2005/11/11 22:51:30  lollisoft
# * Memory leaks removed. There are currently only 4 chunks leaky.
# * These may be false positives, because one of them is an allocated
# * wxMenu instance, I have not to delete after adding it to a wxMenuBar.
# * wxMenuBar gets an owner (see wxWidgets documentation).
# *
# * Revision 1.71  2005/11/07 10:08:54  lollisoft
# * Windows was missing the new TARGETSHARED definition.
# *
# * Revision 1.70  2005/11/06 19:25:32  lollisoft
# * All bugs of unloading shared libraries removed.\nUsing dlopen more than once per shared library leads into unability to unload that library.\nMac OS X seems to not properly handle the reference counting, thus unloading of twice loaded shared libs fails.\n\nI have implemented a workaround to handle this properly.\n\nThere is one exeption: lbModule.so is needed by UAP macros, thus this shared library is left loaded and the system can unload it for me.
# *
# * Revision 1.69  2005/10/28 17:28:42  lollisoft
# * Fixed memory leaks in database classes. Using it in console is tested.
# * There now are only three objects leaked.
# *
# * Revision 1.68  2005/10/05 10:02:50  lollisoft
# * Creating help files was sensitive for errors and stops further making.
# *
# * Revision 1.67  2005/10/03 17:15:14  lollisoft
# * Latest changes for release 0.5.1 under Linux
# *
# * Revision 1.66  2005/09/24 21:41:32  lollisoft
# * Deactivated building tvision stuff. Not yet part of an usable sample.
# *
# * Revision 1.65  2005/09/11 06:33:11  lollisoft
# * Using stdandard make for wx sample app. Added wxWrapperDLL target.
# *
# * Revision 1.64  2005/09/09 18:06:18  lollisoft
# * Commented out libxml2.
# *
# * Revision 1.63  2005/09/07 20:49:46  lollisoft
# * Minor changes due to wxWidgets 2.6.1 usage under Windows.
# *
# * Revision 1.62  2005/08/22 16:33:03  lollisoft
# * Added wxWrapperDLL target for OSX.
# *
# * Revision 1.61  2005/08/21 23:25:50  lollisoft
# * Moving code to wxWrapper DLL/so module.
# *
# * Revision 1.60  2005/08/08 19:18:44  lollisoft
# * Minor changes.
# *
# * Revision 1.59  2005/07/14 19:36:50  lollisoft
# * Compiling SET's version of my tvision test application.
# *
# * Revision 1.58  2005/07/13 20:12:54  lollisoft
# * Changed wxWidgets built to bundle type.
# *
# * Revision 1.57  2005/06/30 07:30:33  lollisoft
# * Added building of login wizard plugin under Mac OS X.
# *
# * Revision 1.56  2005/06/24 23:09:47  lollisoft
# * Changes to build with new wxWidgets version 2.6.1.
# * Added fallback to hardcoded settings, if no environment
# * variables are found. Logging changed to reside in a
# * $(HOME)/log directory.
# *
# * GUI application build process enhanced to also make the
# * bundle. App runs from clicking on the desktop icon.
# *
# * Revision 1.55  2005/06/21 15:15:00  lollisoft
# * Added login wizard plugin under Linux
# *
# * Revision 1.54  2005/06/03 12:34:43  lollisoft
# * Compile tvision-set instead of my version. Better to work together.
# *
# * Revision 1.53  2005/05/15 19:24:40  lollisoft
# * Added new target under osx.
# *
# * Revision 1.52  2005/05/11 08:58:27  lollisoft
# * Little changes to get compiled tvision sample. Compiler switch changes.
# *
# * Revision 1.51  2005/05/10 22:37:47  lollisoft
# * Removed unused code.
# *
# * Revision 1.50  2005/05/10 15:03:23  lollisoft
# * Made Linux make more silent
# *
# * Revision 1.49  2005/05/09 22:20:34  lollisoft
# * Changes to also compile C source code.
# *
# * Revision 1.48  2005/05/03 21:07:18  lollisoft
# * More dependency to doxygen
# *
# * Revision 1.47  2005/04/29 20:49:41  lollisoft
# * Added more files in dependency to help generation
# *
# * Revision 1.46  2005/04/24 19:26:42  lollisoft
# * Moved making of help files to the end of make process
# *
# * Revision 1.45  2005/04/24 18:46:31  lollisoft
# * New modules
# *
# * Revision 1.44  2005/04/23 10:52:07  lollisoft
# * Try to add tvision target
# *
# * Revision 1.43  2005/04/13 21:32:37  lollisoft
# * Restructuring making of subdirectories.
# *
# * Revision 1.42  2005/03/16 23:38:07  lollisoft
# * Missing define to build wx so plugins
# *
# * Revision 1.41  2005/03/16 23:01:25  lollisoft
# * Automatically creating target directories for plugins
# *
# * Revision 1.40  2005/03/16 22:01:57  lollisoft
# * Added creating dll/libs dir under windows
# *
# * Revision 1.39  2005/03/16 20:31:55  lollisoft
# * DEVROOT / DEVROOT_MAKE and DEVROOT_MAKE_INTERNAL clashes
# * and cleanup.
# *
# * Revision 1.38  2005/03/16 00:27:36  lollisoft
# * Last changes to full automatic compiling under OSX.
# *
# * Revision 1.37  2005/03/15 22:26:39  lollisoft
# * More changes on OSX to compile plugins
# *
# * Revision 1.36  2005/03/15 22:17:52  lollisoft
# * mkmk and make process under linux improoved
# *
# * Revision 1.35  2005/03/15 14:43:51  lollisoft
# * Changes for linux to build and let GUI running with plugins
# *
# * Revision 1.34  2005/03/06 12:02:45  lollisoft
# * Added touching lbkey.h in include directory to avoid build failures (osx)
# *
# * Revision 1.33  2005/03/06 11:53:46  lollisoft
# * Changes to automatically make dosdir
# *
# * Revision 1.32  2005/03/06 00:43:56  lollisoft
# * Minor changes to auto compile mkmk as bootstrap
# *
# * Revision 1.31  2005/03/05 23:28:05  lollisoft
# * Initial wx plugin attempt
# *
# * Revision 1.30  2005/03/05 23:13:33  lollisoft
# * More changes to build source tree under Mac OS X
# *
# * Revision 1.29  2005/03/03 08:33:56  lollisoft
# * Added plugins to compile
# *
# * Revision 1.28  2005/03/02 20:05:57  lollisoft
# * Added new module lbLoginWizard and bugfixes
# *
# * Revision 1.27  2005/02/10 19:14:11  lollisoft
# * Why ?
# *
# * Revision 1.26  2005/02/10 16:59:05  lollisoft
# * Changes for Mac OS X
# *
# * Revision 1.25  2005/02/10 12:48:25  lollisoft
# * Changes for Mac OS X
# *
# * Revision 1.24  2005/02/03 19:56:41  lollisoft
# * Samples and more dependencies in documentation
# *
# * Revision 1.23  2005/02/02 13:30:15  lollisoft
# * Latest changes for version 0.4.1
# *
# * Revision 1.22  2005/01/27 12:47:21  lollisoft
# * Minor bugfixes
# *
# * Revision 1.21  2005/01/25 14:05:50  lollisoft
# * Minor changes
# *
# * Revision 1.20  2005/01/25 12:28:34  lollisoft
# * Changes for linux due to several reasons. The GUI sample has still problems with database access. Crash in lbDB.cpp while creating bound columns. Console works
# *
# * Revision 1.19  2005/01/24 22:21:01  lollisoft
# * Changes on Linux to get database access running. Login and selecting / loading an application works. But the application would not load
# *
# * Revision 1.18  2005/01/23 15:23:43  lollisoft
# * Last changes before release 0.4.0
# *
# * Revision 1.17  2005/01/22 15:01:25  lollisoft
# * Commented out lbhook
# *
# * Revision 1.16  2005/01/22 11:59:42  lollisoft
# * Restructuring
# *
# * Revision 1.15  2005/01/05 13:41:36  lollisoft
# * New dynamic application implementation works
# *
# * Revision 1.14  2004/12/14 16:15:06  lollisoft
# * Also make wxWrapper with mkmk and the like.
# *
# * Revision 1.13  2004/10/16 11:59:30  lollisoft
# * Adopted new make system to linux
# *
# * Revision 1.12  2004/10/16 10:10:38  lollisoft
# * Added the doxygen rule depending on lbInterfaces.h
# *
# * Revision 1.11  2004/10/16 09:47:37  lollisoft
# * New make system works nearly perfect. It does not longer build unnessesary.
# *
# * Revision 1.10  2004/10/09 18:01:27  lollisoft
# * Added distclean feature
# *
# * Revision 1.9  2004/10/09 17:22:51  lollisoft
# * Changed make process for wx based apps
# *
# * Revision 1.8  2004/10/09 16:52:46  lollisoft
# * Enhancements for cleaning up
# *
# * Revision 1.7  2004/08/17 20:04:02  lollisoft
# * Deactivated parts, that do not compile under Linux and added demo app module including sample apps
# *
# * Revision 1.6  2004/07/18 07:28:25  lollisoft
# * Now the database sample works also under linux. Some bugs solved and minor changes
# *
# * Revision 1.5  2004/06/06 12:55:58  lollisoft
# * Added new module lbPluginManager
# *
# * Revision 1.4  2003/05/24 02:09:44  lollisoft
# * Added lbDB module
# *
# * Revision 1.3  2003/02/17 21:34:33  lollisoft
# * Much problems with compilation solved, bu wy came this ??
# *
# * Revision 1.2  2002/11/29 19:50:26  lothar
# * Compiles again under linux, but some problems at runtime with DOMString
# *
# * Revision 1.1  2001/10/14 10:25:56  lothar
# * Initial
# *
# **************************************************************

#
# False targets
#
#.PHONY: dummy

ifeq ($(OSTYPE), solaris)
DEVROOT_MAKE=$(DEVROOT)

ifndef prefix
prefix=$(HOME)
endif

endif

ifeq ($(OSTYPE), linux)
DEVROOT_MAKE=$(DEVROOT)

ifndef prefix
prefix=$(HOME)
endif

endif

ifeq ($(OSTYPE), osx)
DEVROOT_MAKE=$(DEVROOT)

ifndef prefix
prefix=$(HOME)
endif

endif

ifeq ($(OSTYPE), Windows_NT)
DEVROOT_MAKE=$(DEVLW)/$(BASE_MAKE)
endif

Path=$(PATH)


#
# The BASEDIRECTORIES is intended to hook in other projects into the directory structure.
# This means, that these directories are for general intent. I would create some modules,
# plugins or even different applications.
#
# To enable one build process, these directories are predefined or checked for it's existence.

MAKE_CONFIG_FILE=$(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure

ifndef RPMBUILD 
ifeq ($(OSTYPE), solaris)
BASEDIRECTORIES= \
	../Plugins \
	../Modules \
	../RegressionTests \
	../AppDevelopmentDemo/DynamicApp/Plugins \
	../AppDevelopment
endif

ifeq ($(OSTYPE), linux)
BASEDIRECTORIES= \
	../Plugins \
	../AppDevelopmentDemo/DynamicApp/Plugins \
	../Modules \
	../RegressionTests \
	../AppDevelopment \
	../ServerPlugins \
	../ClientPlugins
	

#	../vendor/tvision-set \
#	../vendor/tvision-set/examples/lbDMF
#	../../open-watcom
endif
endif

ifdef RPMBUILD 
ifeq ($(OSTYPE), solaris)
BASEDIRECTORIES= \
	../Plugins \
	../Modules
endif
ifeq ($(OSTYPE), linux)
BASEDIRECTORIES= \
	../Plugins \
	../AppDevelopmentDemo/DynamicApp/Plugins \
	../Modules
endif
endif


ifeq ($(OSTYPE), Windows_NT)
BASEDIRECTORIES= \
	../Plugins \
	../AppDevelopmentDemo/DynamicApp/Plugins \
	../Modules \
	../RegressionTests \
	../vendor/wxaui-0.9.1/sample \
	../AppDevelopment

# Don't compile these every time.
#	../vendor/propgrid \
#	../vendor/tvision-set \
#	../vendor/tvision-set/examples/lbDMF \
#	../vendor/wxReportWriter \

endif


ifeq ($(OSTYPE), osx)

BASEDIRECTORIES= \
	../Plugins \
	../AppDevelopmentDemo/DynamicApp/Plugins \
	../Modules \
	../RegressionTests \
	../vendor/wxaui-0.9.1/sample \
	../AppDevelopment \
	../ServerPlugins \
	../ClientPlugins \
	../vendor/tvision/examples/lbDMF

TARGETDLL=sobundle
TARGETSHARED=so
TARGETEXE=elf
TARGETWXEXE=bundle
TARGET_TV_DLL=tvision_dll
TARGET_TV_EXE=tvision_elf
TARGETPLUGIN=soplugin
TARGETSOBUNDLE=sobundle
TARGETWXSO=wxso
TARGETWXSHARED=wxshared
TARGETWXPLUGIN=wxsoplugin
TARGETFRAMEWORK=framework
TARGETWXFRAMEWORK=wxframework

ALLTARGETS = \
	$(prefix)/bin \
	$(prefix)/lib \
	$(prefix)/plugins \
	../include/lbkey.h \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbModule \
	lbMetaApplication \
	lbclasses \
	lbDB \
	lbPluginManager \
	../vendor/propgrid \
	../vendor/wxaui-0.9.1/src \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Test/GUI/wxWrapper \
	../Test/Console/XML \
	$(BASEDIRECTORIES)

ALLDIRS = \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbMetaApplication \
	lbPluginManager \
	../vendor/propgrid \
	../vendor/wxaui-0.9.1/src \
	../vendor/wxaui-0.9.1/sample \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	$(BASEDIRECTORIES)


endif

ifeq ($(OSTYPE), solaris)

TARGETDLL=so
TARGETFRAMEWORK=so
TARGETEXE=elf
TARGETSHARED=so
TARGETWXEXE=elf
TARGETWXSO=wxso
TARGET_TV_DLL=tvision_dll
TARGET_TV_EXE=tvision_elf
TARGETPLUGIN=soplugin
TARGETWXPLUGIN=wxsoplugin

ifdef RPMBUILD
ALLDIRS = \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbMetaApplication \
	lbPluginManager \
	../vendor/propgrid \
	../vendor/wxaui-0.9.1/src \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	$(BASEDIRECTORIES)
endif

ifndef RPMBUILD
ALLDIRS = \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbMetaApplication \
	lbPluginManager \
	../vendor/propgrid \
	../vendor/wxaui-0.9.1/src \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	$(BASEDIRECTORIES)
endif

ALLTARGETS = \
	$(prefix)/bin \
	$(prefix)/lib \
	$(prefix)/plugins \
	../include/lbkey.h \
	$(ALLDIRS)

endif

ifeq ($(OSTYPE), linux)

TARGETDLL=so
TARGETFRAMEWORK=so
TARGETEXE=elf
TARGETSHARED=so
TARGETWXEXE=elf
TARGETWXSO=wxso
TARGET_TV_DLL=tvision_dll
TARGET_TV_EXE=tvision_elf
TARGETPLUGIN=soplugin
TARGETWXPLUGIN=wxsoplugin

ifdef RPMBUILD
ALLDIRS = \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbMetaApplication \
	lbPluginManager \
	../vendor/propgrid \
	../vendor/wxaui-0.9.1/src \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	$(BASEDIRECTORIES)
endif

ifndef RPMBUILD
ALLDIRS = \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbMetaApplication \
	lbPluginManager \
	../vendor/propgrid \
	../vendor/wxaui-0.9.1/src \
	../vendor/wxaui-0.9.1/sample \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	$(BASEDIRECTORIES)
endif

ALLTARGETS = \
	$(prefix)/bin \
	$(prefix)/lib \
	$(prefix)/plugins \
	../include/lbkey.h \
	$(ALLDIRS)

endif

ifeq ($(OSTYPE), Windows_NT)

TARGETDLL=dll
TARGETXSLTDLL=xsltdll
TARGETFRAMEWORK=dll
TARGETSHARED=dll
TARGETEXE=exe
TARGETPLUGIN=plugin
TARGETWXPLUGIN=wxplugin
TARGET_TV_DLL=tvision_dll
TARGET_TV_EXE=tvision_exe

bla = \
	../../open-watcom

ALLTARGETS = \
	../../lib \
	../../dll/libs \
	../../plugins/libs \
	lbHook \
	lbtransfer \
	lbcs \
	lbDB \
	lbModule \
	lbclasses \
	lbMetaApplication \
	lbPluginManager \
	../vendor/propgrid \
	../vendor/wxaui-0.9.1/src \
	../vendor/libxml2-2.6.29/bakefile \
	../vendor/libxslt-1.1.21/libxslt \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Samples/HelloWorld \
	../Doc/html \
	$(BASEDIRECTORIES)

ALLDIRS = \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbMetaApplication \
	lbPluginManager \
	../vendor/propgrid \
	../vendor/wxaui-0.9.1/src \
	../vendor/wxaui-0.9.1/sample \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	$(BASEDIRECTORIES)


#$(DEVROOT_MAKE)/wxwin/wx/samples/report \
#tvision: ../vendor/tvision
#	Q:/develop/wxwin/wx/contrib/wxCode/components/wxxml2/thirdparty/libxml2 \

endif


all_targets: $(ALLTARGETS)


install:
	for sub_target in $(ALLDIRS); do \
		$(MAKE) -C $$sub_target install; \
	done

ifndef RPMBUILD

install-strip:
	for sub_target in $(ALLDIRS); do \
		$(MAKE) -C $$sub_target install-strip; \
	done
	echo mkdir -p $(prefix)/lib
	mkdir -p $(prefix)/share
	mkdir -p $(prefix)/share/lbdmf
	mkdir -p $(prefix)/share/lbdmf/toolbarimages
	cp $(DEVROOT_MAKE)/Projects/CPP/Test/GUI/wxWrapper/toolbarimages/*.png $(prefix)/share/lbdmf/toolbarimages
	cp $(DEVROOT_MAKE)/Projects/CPP/Test/GUI/wxWrapper/toolbarimages/*.xpm $(prefix)/share/lbdmf/toolbarimages

endif

ifdef RPMBUILD

install-strip:
	for sub_target in $(ALLDIRS); do \
		$(MAKE) -C $$sub_target install-strip; \
	done
	echo mkdir -p $(prefix)/lib
	mkdir -p $(prefix)/share
	mkdir -p $(prefix)/share/lbdmf
	mkdir -p $(prefix)/share/lbdmf/toolbarimages
	mkdir -p $(prefix)/share/lbdmf/BoUML
	mkdir -p $(prefix)/share/lbdmf/XMIToDMF
	cp $(DEVROOT_MAKE)/Projects/CPP/Test/GUI/wxWrapper/toolbarimages/*.png $(prefix)/share/lbdmf/toolbarimages
	cp $(DEVROOT_MAKE)/Projects/CPP/Test/GUI/wxWrapper/toolbarimages/*.xpm $(prefix)/share/lbdmf/toolbarimages
	cp $(DEVROOT_MAKE)/Projects/CPP/Test/GUI/wxWrapper/splash.png $(prefix)/share/lbdmf
	cp $(DEVROOT_MAKE)/Projects/CPP/Test/GUI/wxWrapper/lbdmf.png $(prefix)/share/lbdmf
	cp $(DEVROOT_MAKE)/Projects/CPP/Test/GUI/wxWrapper/wxWrapper.desktop $(prefix)/share/lbdmf 
	cp $(DEVROOT_MAKE)/Projects/CPP/AppDevelopmentDemo/DynamicApp/XMIToDMF/*.xmi $(prefix)/share/lbdmf/XMIToDMF
	cp $(DEVROOT_MAKE)/Projects/CPP/AppDevelopmentDemo/DynamicApp/XMIToDMF/*.xsl $(prefix)/share/lbdmf/XMIToDMF
	cp $(DEVROOT_MAKE)/Projects/CPP/AppDevelopmentDemo/DynamicApp/BoUML/* $(prefix)/share/lbdmf/BoUML
	./copy-wxGTK-libs.sh $(prefix)

endif

test-ldd:
	./copy-wxGTK-libs.sh $(prefix)

../../lib:
	-mkdir ../../lib

../../dll/libs:
	-mkdir ../../dll/libs

../../plugins:
	-mkdir ../../plugins

../../plugins/libs: ../../plugins
	-mkdir ../../plugins/libs

$(prefix)/bin:
	-mkdir -p $@

$(prefix)/lib:
	-mkdir -p $@

$(prefix)/plugins:
	-mkdir -p $@

clean:
	@for d in $(ALLDIRS); do \
	  $(MAKE) -C $$d clean; \
	done

distclean:
	@for d in $(ALLDIRS); do \
	    echo $$d ; \
	    cp $$d/makefile $$d/makefile.clean; \
	    $(MAKE) -C $$d distclean -f makefile.clean || exit $? ; \
	    rm $$d/makefile.clean; \
	done

mkrelease:
	@for d in $(ALLDIRS); do \
	    $(MAKE) -C $$d clean || exit $? ; \
	done
	cd ../..; tar cvzf lbDMF-0.3.2.3.tgz CPP; cd CPP/BaseDevelopment

#	Doesn't compile yet under linux
#	lbPluginManager \
#	Doesn't compile if XML dependend module XML4C (alphaworks) is not installed
#	lbXMLConfig/lbDOMConfig \

dummy:

../vendor/c-goldparser: dummy
	$(MAKE) -s -C $@ -e MODULE=gold -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/libxml2-2.6.29/bakefile: dummy
	$(MAKE) -s -C $@ -f makefile.lbDMF

../vendor/libxslt-1.1.21/libxslt: dummy
	$(MAKE) -s -C $@ -e MODULE=lbxslt -e TARGET=$(TARGETXSLTDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/tvision: dummy
	$(MAKE) -s -C $@ -e MODULE=librhtv -e TARGET=$(TARGET_TV_DLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/tvision-set: dummy
	$(MAKE) -s -C $@ -e MODULE=librhtv -e TARGET=$(TARGET_TV_DLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/tvision-set/examples/lbDMF: dummy
	$(MAKE) -s -C $@ -e MODULE=demo -e TARGET=$(TARGET_TV_EXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/wxReportWriter: dummy
	$(MAKE) -s -C $@

../Test/Console/XML: dummy
	$(MAKE) -s -C $@ -e MODULE=console-test -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../include/lbkey.h: dummy
	touch ../include/lbkey.h

ifeq ($(OSTYPE), solaris)
../vendor/dosdir: dummy
	$@/make.sh $@
	cd ../BaseDevelopment

../vendor/mkmk: dummy
	$@/make.sh $@
	cp $@/mkmk $(HOME)/bin
	cd ../BaseDevelopment
endif

ifeq ($(OSTYPE), linux)
../vendor/dosdir: dummy
	$@/make.sh $@
	cd ../BaseDevelopment

../vendor/mkmk: dummy
	$@/make.sh $@
	cp $@/mkmk $(HOME)/bin
	cd ../BaseDevelopment
endif

ifeq ($(OSTYPE), osx)
../vendor/dosdir: dummy
	$@/make-osx.sh $@
	cd ../BaseDevelopment

../vendor/mkmk: dummy
	$@/make-osx.sh $@
	cp $@/mkmk $(HOME)/bin
	cd ../BaseDevelopment

../vendor/propgrid: dummy
	$(MAKE) -s -C $@ -e MODULE=wxPropgrid -e TARGET=$(TARGETWXFRAMEWORK) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../Test/GUI/wxPlugins/lbLoginWizard: dummy
	$(MAKE) -s -C $@ -e MODULE=lbLoginWizard -e TARGET=$(TARGETWXPLUGIN) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/wxaui-0.9.1/src: dummy
	$(MAKE) -s -C $@ -e MODULE=wxAUI -e TARGET=$(TARGETWXFRAMEWORK) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/wxaui-0.9.1/sample: dummy
	$(MAKE) -s -C $@ -e MODULE=wxAUISample -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../Test/GUI/wxWrapper: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapper -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	cp ../Test/GUI/wxWrapper/wxWrapper $(HOME)/bin

../Test/GUI/wxWrapperDLL: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapperDLL -e TARGET=$(TARGETWXFRAMEWORK) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
endif

ifeq ($(OSTYPE), solaris)
../vendor/wxaui-0.9.1/src: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxAUI -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../vendor/propgrid: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxPropgrid -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../vendor/wxaui-0.9.1/sample: dummy
	$(MAKE) -s -C $@ -e MODULE=wxAUISample -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../Test/GUI/wxWrapperDLL: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxWrapperDLL -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../Test/GUI/wxWrapper: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapper -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	cp ../Test/GUI/wxWrapper/wxWrapper $(HOME)/bin

#../Test/GUI/wxWrapper: dummy
#	$(MAKE) -s -C $@ -f makefile.wx-sample

../Test/GUI/wxPlugins/lbLoginWizard: dummy
	$(MAKE) -s -C $@ -e MODULE=lbLoginWizard -e TARGET=$(TARGETWXPLUGIN) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
endif

ifeq ($(OSTYPE), linux)
../vendor/wxaui-0.9.1/src: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxAUI -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../vendor/propgrid: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxPropgrid -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../vendor/wxaui-0.9.1/sample: dummy
	$(MAKE) -s -C $@ -e MODULE=wxAUISample -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../Test/GUI/wxWrapperDLL: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxWrapperDLL -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../Test/GUI/wxWrapper: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapper -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	cp ../Test/GUI/wxWrapper/wxWrapper $(HOME)/bin

#../Test/GUI/wxWrapper: dummy
#	$(MAKE) -s -C $@ -f makefile.wx-sample

../Test/GUI/wxPlugins/lbLoginWizard: dummy
	$(MAKE) -s -C $@ -e MODULE=lbLoginWizard -e TARGET=$(TARGETWXPLUGIN) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
endif

ifeq ($(OSTYPE), Windows_NT)
../Test/GUI/wxWrapper: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapper -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

$(DEVROOT_MAKE)/wxwin/wx/samples/report: dummy
	$(MAKE) -s -C $@ -e MODULE=report -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/propgrid: dummy
	$(MAKE) -s -C $@ -e MODULE=wxPropgrid -e TARGET=$(TARGETSHARED) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/wxaui-0.9.1/src: dummy
	$(MAKE) -s -C $@ -e MODULE=wxAUI -e TARGET=$(TARGETSHARED) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/wxaui-0.9.1/sample: dummy
	$(MAKE) -s -C $@ -e MODULE=wxAUISample -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../Test/GUI/wxWrapperDLL: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapperDLL -e TARGET=$(TARGETSHARED) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../Test/GUI/wxPlugins/lbLoginWizard: dummy
	$(MAKE) -s -C $@ -e MODULE=lbLoginWizard -e TARGET=$(TARGETWXPLUGIN) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
endif

../../open-watcom: dummy
	$(MAKE) -C $@

../AppDevelopment: dummy
	$(MAKE) -k -s -C $@

../Plugins: dummy
	$(MAKE) -s -C $@

../ServerPlugins: dummy
	$(MAKE) -s -C $@

../ClientPlugins: dummy
	$(MAKE) -s -C $@

../AppDevelopmentDemo/DynamicApp/Plugins: dummy
	$(MAKE) -s -C $@

../Modules: dummy
	$(MAKE) -s -C $@

../AppDevelopmentDemo: dummy
	$(MAKE) -s -C $@

../RegressionTests: dummy
	$(MAKE) -s -C $@

../AppDevelopmentDemo/App: dummy
	$(MAKE) -s -C $@ -e MODULE=Application -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../AppDevelopmentDemo/DynamicApp/App: dummy
	$(MAKE) -s -C $@ -e MODULE=lbDynApp -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

#../Plugins/DatabaseForm: dummy
#	$(MAKE) -s -C $@ -e MODULE=lbDatabaseForm -e TARGET=$(TARGETWXPLUGIN) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
#	$(MAKE) -s -C $@

lbHook: dummy
	@echo prefix='$(prefix)'
ifeq ($(OSTYPE), linux)
	$(MAKE) -s -C $@ -e MODULE=lib$@ -e TARGET=$(TARGETFRAMEWORK) -f $(MAKE_CONFIG_FILE)
else
ifeq ($(OSTYPE), solaris)
	$(MAKE) -s -C $@ -e MODULE=lib$@ -e TARGET=$(TARGETFRAMEWORK) -f $(MAKE_CONFIG_FILE)
else
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETFRAMEWORK) -f $(MAKE_CONFIG_FILE)
endif
endif
	$(MAKE) -s -C $@
ifeq ($(OSTYPE), solaris)
	$(MAKE) -s -C $@ install-strip
endif
ifeq ($(OSTYPE), linux)
	$(MAKE) -s -C $@ install-strip
endif

lbDB: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

lbPluginManager: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

lbModule: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

lbclasses: dummy
	$(MAKE) -s -C lbclasses -e MODULE=lbClasses -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C lbclasses

lbMetaApplication: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

lbtransfer: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

lbcs: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

lbXMLConfig/lbDOMConfig: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

#Q:/develop/wxwin/wx/contrib/wxCode/components/wxxml2/thirdparty/libxml2: dummy
#	$(MAKE) -s -C $@ -e MODULE=libxml2 -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
#	$(MAKE) -s -C $@

../Doc/html: ../doxygen.conf \
	../interfaces/lbInterfaces.h \
	../include/lbConfigHook.h \
	../Samples/HelloWorld/helloworld.cpp \
	../RegressionTests/Basetypes/Basetypes.cpp \
	../RegressionTests/Memory/memTest.cpp
	-@doxygen ../doxygen.conf
	
	

#	../RegressionTests/Database/dbTest.cpp \

../Samples/HelloWorld: dummy
	$(MAKE) -s -C $@ -e MODULE=HelloWorld -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

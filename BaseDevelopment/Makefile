# Global makefile to build all sub modules
# **************************************************************
# * $Locker:  $
# * $Revision: 1.57 $
# * $Name:  $
# * $Id: Makefile,v 1.57 2005/06/30 07:30:33 lollisoft Exp $
# *
# * $Log: Makefile,v $
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

ifeq ($(OSTYPE), linux)
DEVROOT_MAKE=$(DEVROOT)
endif

ifeq ($(OSTYPE), osx)
DEVROOT_MAKE=$(DEVROOT)
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


ifeq ($(OSTYPE), linux)
BASEDIRECTORIES= \
	../Plugins \
	../Modules \
	../RegressionTests \
	../vendor/tvision/examples/lbDMF \
	../AppDevelopment 

#	../../open-watcom
endif

ifeq ($(OSTYPE), Windows_NT)
BASEDIRECTORIES= \
	../Plugins \
	../Modules \
	../RegressionTests \
	../vendor/tvision-set \
	../vendor/tvision/examples/lbDMF \
	../AppDevelopment 
endif


MAKESUBDIR= \
	@( \
	cd $@; \
	./makefile.sh; \
	make; \
	)

MAKEWXSAMPLE= \
	@( \
	cd $@; \
	cp makefile.wx-sample makefile; \
	make; \
	)

ifeq ($(OSTYPE), osx)

BASEDIRECTORIES= \
	../Plugins \
	../Modules \
	../RegressionTests \
	../vendor/tvision/examples/lbDMF \
	../AppDevelopment 

TARGETDLL=so
TARGETEXE=elf
TARGETWXEXE=elf
TARGET_TV_DLL=tvision_dll
TARGET_TV_EXE=tvision_elf
TARGETPLUGIN=soplugin
TARGETWXPLUGIN=wxsoplugin

ALLTARGETS = \
	../include/lbkey.h \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbModule \
	lbMetaApplication \
	lbclasses \
	lbDB \
	lbPluginManager \
	../Plugins/DatabaseForm \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Test/Console/XML \
	$(BASEDIRECTORIES)

endif

ifeq ($(OSTYPE), linux)

TARGETDLL=so
TARGETEXE=elf
TARGET_TV_DLL=tvision_dll
TARGET_TV_EXE=tvision_elf
TARGETPLUGIN=soplugin
TARGETWXPLUGIN=wxsoplugin


ALLTARGETS = \
	../include/lbkey.h \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbMetaApplication \
	lbPluginManager \
	../Plugins/DatabaseForm \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	$(BASEDIRECTORIES)
endif

ifeq ($(OSTYPE), Windows_NT)

TARGETDLL=dll
TARGETEXE=exe
TARGETPLUGIN=plugin
TARGETWXPLUGIN=wxplugin
TARGET_TV_DLL=tvision_dll
TARGET_TV_EXE=tvision_exe

bla = \
	../../open-watcom

ALLTARGETS = \
	../../dll/libs \
	../../plugins/libs \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbMetaApplication \
	lbPluginManager \
	../Plugins/DatabaseForm \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Samples/HelloWorld \
	../Doc/html \
	$(BASEDIRECTORIES)

#tvision: ../vendor/tvision

endif


all_targets: $(ALLTARGETS)


../../dll/libs:
	mkdir ../../dll/libs

../../plugins/libs:
	mkdir ../../plugins
	mkdir ../../plugins/libs

clean:
	@for d in $(ALLTARGETS); do \
	    $(MAKE) -C $$d clean || exit $? ; \
	done

distclean:
	@for d in $(ALLTARGETS); do \
	    echo $$d ; \
	    cp $$d/makefile $$d/makefile.clean; \
	    $(MAKE) -C $$d distclean -f makefile.clean || exit $? ; \
	    rm $$d/makefile.clean; \
	done

mkrelease:
	@for d in $(ALLTARGETS); do \
	    $(MAKE) -C $$d clean || exit $? ; \
	done
	cd ../..; tar cvzf lbDMF-0.3.2.3.tgz CPP; cd CPP/BaseDevelopment

#	Doesn't compile yet under linux
#	lbPluginManager \
#	Doesn't compile if XML dependend module XML4C (alphaworks) is not installed
#	lbXMLConfig/lbDOMConfig \

dummy:

../vendor/tvision: dummy
	$(MAKE) -s -C $@ -e MODULE=tvision -e TARGET=$(TARGET_TV_DLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/tvision-set: dummy
	$(MAKE) -s -C $@ -e MODULE=tvision -e TARGET=$(TARGET_TV_DLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/tvision/examples/lbDMF: dummy
	$(MAKE) -s -C $@ -e MODULE=demo -e TARGET=$(TARGET_TV_EXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../Test/Console/XML: dummy
	$(MAKE) -s -C $@ -e MODULE=console-test -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../include/lbkey.h: dummy
	touch ../include/lbkey.h

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

../Test/GUI/wxPlugins/lbLoginWizard: dummy
	$(MAKE) -s -C $@ -e MODULE=lbLoginWizard -e TARGET=$(TARGETWXPLUGIN) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../Test/GUI/wxWrapper: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapper -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	cp ../Test/GUI/wxWrapper/wxWrapper $(HOME)/bin
endif

ifeq ($(OSTYPE), linux)
../Test/GUI/wxWrapper: dummy
	$(MAKE) -s -C $@ -f makefile.wx-sample

../Test/GUI/wxPlugins/lbLoginWizard: dummy
	$(MAKE) -s -C $@ -e MODULE=lbLoginWizard -e TARGET=$(TARGETWXPLUGIN) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
endif

ifeq ($(OSTYPE), Windows_NT)
../Test/GUI/wxWrapper: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapper -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../Test/GUI/wxPlugins/lbLoginWizard: dummy
	$(MAKE) -s -C $@ -e MODULE=lbLoginWizard -e TARGET=$(TARGETWXPLUGIN) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
endif

../../open-watcom: dummy
	$(MAKE) -C $@

../AppDevelopment: dummy
	$(MAKE) -s -C $@

../Plugins: dummy
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
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

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

lbXMLConfig/lbDOMConfig: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../Doc/html: ../doxygen.conf \
	../interfaces/lbInterfaces.h \
	../include/lbConfigHook.h \
	../Samples/HelloWorld/helloworld.cpp \
	../RegressionTests/Database/dbTest.cpp \
	../RegressionTests/Basetypes/Basetypes.cpp \
	../RegressionTests/Memory/memTest.cpp
	@doxygen ../doxygen.conf

../Samples/HelloWorld: dummy
	$(MAKE) -s -C $@ -e MODULE=HelloWorld -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

# Global makefile to build all sub modules
# **************************************************************
# * $Locker:  $
# * $Revision: 1.27 $
# * $Name:  $
# * $Id: Makefile,v 1.27 2005/02/10 19:14:11 lollisoft Exp $
# *
# * $Log: Makefile,v $
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
DEVROOT_MAKE=$(DEVROOT)
endif

Path=$(PATH)

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

TARGETDLL=so
TARGETEXE=elf

ALLTARGETS = lbHook \
	lbModule \
	lbMetaApplication \
	lbclasses
#	lbDB \
#	lbModule \
#	lbclasses \
#	lbMetaApplication \
#	../AppDevelopmentDemo/App \
#	../AppDevelopmentDemo/DynamicApp/App \
#	../Test/Console/XML \
#	../Test/GUI/wxWrapper \
#	../Doc/html
endif

ifeq ($(OSTYPE), linux)

TARGETDLL=so
TARGETEXE=elf

ALLTARGETS = lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbMetaApplication \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapper \
	../Doc/html
endif

ifeq ($(OSTYPE), Windows_NT)

TARGETDLL=dll
TARGETEXE=exe

ALLTARGETS = \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbMetaApplication \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapper \
	../AppDevelopment \
	../Doc/html \
	../Samples/HelloWorld
endif


all_targets: $(ALLTARGETS)


../../dll/libs:
	mkdir ../../dll/libs
	#chmod 0777 ../../dll/libs
	#echo "clean: dummy" > Makefile

clean:
	@for d in $(ALLTARGETS); do \
	    $(MAKE) -C $$d clean || exit $? ; \
	done

distclean:
	@for d in $(ALLTARGETS); do \
	    $(MAKE) -C $$d distclean || exit $? ; \
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

../Test/Console/XML: dummy
	$(MAKE) -C $@ -e MODULE=Test -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

ifeq ($(OSTYPE), linux)
../Test/GUI/wxWrapper: dummy
	$(MAKE) -C $@ -f makefile.wx-sample
endif
ifeq ($(OSTYPE), Windows_NT)
../Test/GUI/wxWrapper: dummy
	$(MAKE) -C $@ -e MODULE=wxWrapper -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@
endif

../AppDevelopment: dummy
	$(MAKE) -C $@

../AppDevelopmentDemo/App: dummy
	$(MAKE) -C $@ -e MODULE=Application -e TARGET=$(TARGETDLL) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

../AppDevelopmentDemo/DynamicApp/App: dummy
	$(MAKE) -C $@ -e MODULE=lbDynApp -e TARGET=$(TARGETDLL) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

lbHook: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

lbDB: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

lbPluginManager: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

lbModule: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

lbclasses: dummy
	$(MAKE) -C lbclasses -e MODULE=lbClasses -e TARGET=$(TARGETDLL) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C lbclasses

lbMetaApplication: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

lbXMLConfig/lbDOMConfig: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

../Doc/html: ../doxygen.conf \
	../interfaces/lbInterfaces.h \
	../Samples/HelloWorld/helloworld.cpp
	@doxygen ../doxygen.conf

../Samples/HelloWorld: dummy
	$(MAKE) -C $@ -e MODULE=HelloWorld -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

# Global makefile to build all sub modules
# **************************************************************
# *
# **************************************************************

#
# False targets
#
#.PHONY: dummy

ifeq ($(OSTYPE), solaris)
ifeq ($(CRUISECRONTROL), yes)
RELPATH=
else
RELPATH=/Projects/CPP
endif
DEVROOT_MAKE=$(DEVROOT)
endif

ifeq ($(OSTYPE), linux)
ifeq ($(CRUISECONTROL), yes)
RELPATH=
else
RELPATH=/Projects/CPP
endif
DEVROOT_MAKE=$(DEVROOT)
endif

ifeq ($(OSTYPE), osx)
ifeq ($(CRUISECONTROL), yes)
RELPATH=
else
RELPATH=/Projects/CPP
endif
DEVROOT_MAKE=$(DEVROOT)

OSVERSION_=$(OSVERSION)
OSPLATFORM_=$(OSPLATFORM)

#OSVERSION=9.0.0
#OSPLATFORM=ppc

OSNAME=Panther

ifeq ($(OSVERSION_), 9.0.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 9.1.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 9.6.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 9.8.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 10.0.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 10.2.0)
OSNAME=Leopard
endif


endif

ifeq ($(OSTYPE), Windows_NT)
ifeq ($(CRUISECONTROL), yes)
RELPATH=
else
RELPATH=\\Projects\\CPP
endif
endif

Path=$(PATH)

ifeq ($(OSTYPE), solaris)

TARGETDLL=so
TARGETEXE=elf
TARGETPLUGIN=soplugin
TARGETFRAMEWORK=so

ALLTARGETS = \
	MiniCppUnit \
	BaseDevelopment \
	TestRunner

endif
ifeq ($(OSTYPE), linux)

TARGETDLL=so
TARGETEXE=elf
TARGETPLUGIN=soplugin
TARGETFRAMEWORK=so

ALLTARGETS = \
	MiniCppUnit \
	BaseDevelopment \
	TestRunner

endif


ifeq ($(OSTYPE), osx)

TARGETDLL=so
TARGETEXE=elf
TARGETPLUGIN=soplugin
TARGETFRAMEWORK=framework

ALLTARGETS = \
	MiniCppUnit \
	BaseDevelopment \
	TestRunner

endif

ifeq ($(OSTYPE), Windows_NT)

TARGETDLL=dll
TARGETEXE=exe
TARGETPLUGIN=dll_target_mingw
TARGETFRAMEWORK=dll
TARGETDLLMINGW=dll_target_mingw

ALLTARGETS = \
	MiniCppUnit \
	BaseDevelopment \
	TestRunner

endif


all_targets: $(ALLTARGETS)



distclean:
	@for d in $(ALLTARGETS); do \
	    $(MAKE) -C $$d distclean || exit $? ; \
	done

mkrelease:
	@for d in $(ALLTARGETS); do \
	    $(MAKE) -C $$d clean || exit $? ; \
	done
	cd ../..; tar cvzf lbDMF-0.3.2.3.tgz CPP; cd CPP/BaseDevelopment

dummy:

ifeq ($(OSTYPE), Windows_NT)

MiniCppUnit: dummy
	$(MAKE) -C $@ -e MODULE=MiniCppUnit -e TARGET=$(TARGETDLLMINGW) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

endif

ifeq ($(OSTYPE), osx)

MiniCppUnit: dummy
	$(MAKE) -C $@ -e MODULE=MiniCppUnit -e TARGET=$(TARGETFRAMEWORK) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

endif

BaseDevelopment: dummy
	$(MAKE) -C $@ -e MODULE=testsBaseDevelopment -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

TestRunner: dummy
	$(MAKE) -C $@ -e MODULE=lbDMFUnitTests -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

clean:
	for sub_target in $(ALLTARGETS); do $(MAKE) -C $$sub_target clean; done 

install:
	for sub_target in $(ALLTARGETS); do $(MAKE) -C $$sub_target install; done 

install-strip:
	for sub_target in $(ALLTARGETS); do $(MAKE) -C $$sub_target install-strip; done


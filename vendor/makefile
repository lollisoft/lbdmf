# Global makefile to build all sub modules
# **************************************************************
# *
# **************************************************************

#
# False targets
#
#.PHONY: dummy

ifeq ($(CRUISECONTROL), yes)
RELPATH=
endif

ifneq ($(CRUISECONTROL), yes)
RELPATH=/Projects/CPP
endif

ifeq ($(OSTYPE), solaris)
DEVROOT_MAKE=$(DEVROOT)
endif

ifeq ($(OSTYPE), linux)
DEVROOT_MAKE=$(DEVROOT)
endif

ifeq ($(OSTYPE), linux-debian-ppc)
DEVROOT_MAKE=$(DEVROOT)
endif

ifeq ($(OSTYPE), osx)
DEVROOT_MAKE=$(DEVROOT)
endif

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

ifeq ($(OSVERSION_), 10.4.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 10.5.0)
OSNAME=Leopard
endif

Path=$(PATH)

ifeq ($(OSTYPE), solaris)

TARGETDLL=so
TARGETWXDLL=so
TARGETEXE=elf
TARGETWXEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
	wxRibbon \
	wxRibbon_Samples
endif

ifeq ($(OSTYPE), linux-debian-ppc)

TARGETDLL=so
TARGETWXDLL=so
TARGETEXE=elf
TARGETWXEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
	wxRibbon \
	wxRibbon_Samples
endif

ifeq ($(OSTYPE), linux)

TARGETDLL=so
TARGETWXDLL=so
TARGETEXE=elf
TARGETWXEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
	wxRibbon \
	wxRibbon_Samples
endif

ifeq ($(OSTYPE), osx)

TARGETDLL=so
TARGETWXDLL=wxframework
TARGETEXE=elf
TARGETWXEXE=bundle
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin
TARGETWXFRAMEWORK=wxframework

ALLTARGETS = \
	wxRibbon \
	wxRibbon_Samples
endif

ifeq ($(OSTYPE), Windows_NT)

TARGETDLL=dll
TARGETWXDLL=dll
TARGETEXE=exe
TARGETWXEXE=exe
TARGETWXPLUGIN=wxplugin
TARGETPLUGIN=plugin

ALLTARGETS = \
	wxRibbon \
	wxRibbon_Samples
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

wxRibbon: dummy
	$(MAKE) -C $@/src/ribbon -e MODULE=wxRibbon -e CUSTOM_DEP=,..\..\include\wx\ribbon -e TARGET=$(TARGETWXDLL) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@/src/ribbon

wxRibbon_Samples: dummy
	$(MAKE) -C wxRibbon/samples/ribbon -e MODULE=wxRibbonSample -e TARGET=$(TARGETWXEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C wxRibbon/samples/ribbon

clean:
	for sub_target in $(ALLTARGETS); do \
		$(MAKE) -C $$sub_target clean; \
	done

install:
	for sub_target in $(ALLTARGETS); do \
	$(MAKE) -C $$sub_target install; \
	done

install-strip:
	for sub_target in $(ALLTARGETS); do \
		$(MAKE) -C $$sub_target install-strip; \
	done 



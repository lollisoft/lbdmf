


# Global makefile to build all sub modules
# **************************************************************
# *
# **************************************************************

#
# False targets
#
#.PHONY: dummy

ifeq ($(OSTYPE), linux)
ifeq ($(CRUISECONTROL), yes)
RELPATH=
else
RELPATH=/Projects/lbdmf
RELPATH_MAKE=/Projects/lbdmf
endif
DEVROOT_MAKE=$(DEVROOT)
endif

ifeq ($(OSTYPE), osx)
ifeq ($(CRUISECONTROL), yes)
RELPATH=
else
RELPATH=/Projects/lbdmf
RELPATH_MAKE=/Projects/lbdmf
endif
DEVROOT_MAKE=$(DEVROOT)
endif

ifeq ($(OSTYPE), Windows_NT)
ifeq ($(CRUISECONTROL), yes)
RELPATH=
RELPATH_MAKE=
else
RELPATH=\Projects\lbdmf
RELPATH_MAKE=/Projects/lbdmf
endif
endif

ifeq ($(OSTYPE), solaris)
ifeq ($(CRUISECONTROL), yes)
RELPATH=
else
RELPATH=/Projects/lbdmf
RELPATH_MAKE=/Projects/lbdmf
endif
endif

Path=$(PATH)

ifeq ($(OSTYPE), linux)

TARGETDLL=so
TARGETEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
ApplicationBus \
Fax \



endif

ifeq ($(OSTYPE), osx)

TARGETDLL=so
TARGETEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
ApplicationBus \
Fax \


endif

ifeq ($(OSTYPE), Windows_NT)

TARGET_SELECTOR=_target_mingw
#TARGET_SELECTOR=

TARGETEXE=exe$(TARGET_SELECTOR)
TARGETDLL=dll$(TARGET_SELECTOR)
TARGETWXPLUGIN=wxplugin$(TARGET_SELECTOR)
TARGETPLUGIN=plugin$(TARGET_SELECTOR)

ALLTARGETS = \
ApplicationBus \
Fax \


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

ApplicationBus: dummy
	$(MAKE) -C $@ -e MODULE=ApplicationBusServer -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH_MAKE)/make/makefile.configure
	$(MAKE) -C $@ -e DEVROOT_MAKE_APPLICATIONS=$(DEVLW)/$(BASE_MAKE)

Fax: dummy
	$(MAKE) -C $@ -e MODULE=FaxServer -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH_MAKE)/make/makefile.configure
	$(MAKE) -C $@ -e DEVROOT_MAKE_APPLICATIONS=$(DEVLW)/$(BASE_MAKE)



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

    

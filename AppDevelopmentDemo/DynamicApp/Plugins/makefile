# Global makefile to build all sub modules
# **************************************************************
# *
# **************************************************************

#
# False targets
#
#.PHONY: dummy

ifeq ($(OSTYPE), solaris)
ifeq ($(CRUISECONTROL), yes)
RELPATH=
else
RELPATH=/Projects/$(REPO_NAME)
endif
DEVROOT_MAKE=$(DEVROOT)
endif

ifeq ($(OSTYPE), linux-debian-ppc)
ifeq ($(CRUISECONTROL), yes)
RELPATH=
else
RELPATH=/Projects/$(REPO_NAME)
endif
DEVROOT_MAKE=$(DEVROOT)
endif

ifeq ($(OSTYPE), linux)
ifeq ($(CRUISECONTROL), yes)
RELPATH=/Projects/$(REPO_NAME)
else
RELPATH=/Projects/$(REPO_NAME)
endif
DEVROOT_MAKE=$(DEVROOT)
endif

ifeq ($(OSTYPE), osx)
ifeq ($(CRUISECONTROL), yes)
RELPATH=/Projects/$(REPO_NAME)
else
RELPATH=/Projects/$(REPO_NAME)
endif
DEVROOT_MAKE=$(DEVROOT)
endif

ifeq ($(OSTYPE), Windows_NT)
ifeq ($(CRUISECONTROL), yes)
RELPATH=/Projects/$(REPO_NAME)
else
RELPATH=/Projects/$(REPO_NAME)
endif
endif

Path=$(PATH)

ifeq ($(OSTYPE), solaris)

TARGETDLL=so
TARGETEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
	lbDMFXslt \
	lbDMFBasicActionSteps \
	lbDynamicAppStorage
endif

ifeq ($(OSTYPE), linux-debian-ppc)

TARGETDLL=so
TARGETEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
	lbDMFXslt \
	lbDMFBasicActionSteps \
	lbDynamicAppStorage
endif

ifeq ($(OSTYPE), linux)

TARGETDLL=so
TARGETEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
	lbDMFXslt \
	lbDMFBasicActionSteps \
	lbDynamicAppStorage
endif

ifeq ($(OSTYPE), osx)

TARGETDLL=so
TARGETEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
	lbDMFXslt \
	lbDMFBasicActionSteps \
	lbDynamicAppStorage
endif

ifeq ($(OSTYPE), Windows_NT)

TARGET_SELECTOR=_target_mingw
#TARGET_SELECTOR=

TARGETDLL=dll$(TARGET_SELECTOR)
TARGETPLUGIN=plugin$(TARGET_SELECTOR)

TARGETEXE=exe
TARGETWXPLUGIN=wxplugin

ALLTARGETS = \
	lbDMFXslt \
	lbDMFBasicActionSteps \
	lbDynamicAppStorage
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
	cd ../..; tar cvzf lbDMF-0.3.2.3.tgz $(REPO_NAME); cd $(REPO_NAME)/BaseDevelopment

dummy:

lbDynamicAppStorage: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

lbDMFXslt: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

lbDMFBasicActionSteps: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@


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



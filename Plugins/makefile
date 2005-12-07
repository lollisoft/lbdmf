# Global makefile to build all sub modules
# **************************************************************
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


Path=$(PATH)

ifeq ($(OSTYPE), linux)

TARGETDLL=so
TARGETEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
	TestPlugin \
	DatabaseForm \
	DatabaseReport
endif

ifeq ($(OSTYPE), osx)

TARGETDLL=so
TARGETEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
	TestPlugin \
	DatabaseForm \
	DatabaseReport
endif

ifeq ($(OSTYPE), Windows_NT)

TARGETDLL=dll
TARGETEXE=exe
TARGETWXPLUGIN=wxplugin
TARGETPLUGIN=plugin

ALLTARGETS = \
	TestPlugin \
	DatabaseForm \
	DatabaseReport
endif


all_targets: $(ALLTARGETS)



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

dummy:

TestPlugin: dummy
	$(MAKE) -C $@ -e MODULE=TestPlugin -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

DatabaseForm: dummy
	$(MAKE) -C $@ -e MODULE=lbDatabaseForm -e TARGET=$(TARGETWXPLUGIN) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@
	
DatabaseReport: dummy
	$(MAKE) -C $@ -e MODULE=lbDatabaseReport -e TARGET=$(TARGETWXPLUGIN) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@
	

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


Path=$(PATH)

ifeq ($(OSTYPE), linux)

TARGETDLL=so
TARGETEXE=elf

ALLTARGETS = \
	DatabaseForm
endif

ifeq ($(OSTYPE), Windows_NT)

TARGETDLL=dll
TARGETEXE=exe

ALLTARGETS = \
	DatabaseForm
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

DatabaseForm: dummy
	$(MAKE) -C $@ -e MODULE=lbDatabaseForm -e TARGET=$(TARGETDLL) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@
	

# Global makefile to build all sub modules
# **************************************************************
# *
# **************************************************************

#
# False targets
#
#.PHONY: dummy

ifeq ($(OSTYPE), solaris)
DEVROOT_MAKE=$(DEVROOT)
endif

ifeq ($(OSTYPE), linux)
DEVROOT_MAKE=$(DEVROOT)
endif

ifeq ($(OSTYPE), osx)
DEVROOT_MAKE=$(DEVROOT)
endif


Path=$(PATH)

ifeq ($(OSTYPE), solaris)

TARGETDLL=so
TARGETEXE=elf

ALLTARGETS = \
	Database/Plain-ODBC-Test \
	Database \
	Basetypes \
	Memory \
	MetaApplication \
	Events \
	Translation \
	PluginTest

endif
ifeq ($(OSTYPE), linux)

TARGETDLL=so
TARGETEXE=elf

ALLTARGETS = \
	Database/Plain-ODBC-Test \
	Database \
	Basetypes \
	Memory \
	MetaApplication \
	Events \
	Translation \
	PluginTest

endif


ifeq ($(OSTYPE), osx)

TARGETDLL=so
TARGETEXE=elf

ALLTARGETS = \
	Database/FKTest \
	Database/Plain-ODBC-Test \
	Database/Plain-ODBC-Test-Blob \
	Database \
	Basetypes \
	Memory \
	MetaApplication \
	Events \
	Translation \
	PluginTest

endif

ifeq ($(OSTYPE), Windows_NT)

TARGETDLL=dll
TARGETEXE=exe

ALLTARGETS = \
	Database/Plain-ODBC-Test-Blob \
	Database/Plain-ODBC-Test \
	Database/FKTest \
	Database \
	Basetypes \
	Memory \
	MetaApplication \
	Events \
	Translation \
	PluginByInterfaceAndNamespace \
	Parameter \
	PluginTranslationsModel \
	PluginTest

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

Database/FKTest: dummy
	$(MAKE) -C $@ -e MODULE=fkTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

Database/Plain-ODBC-Test: dummy
	$(MAKE) -C $@ -e MODULE=plainTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

Database/Plain-ODBC-Test-Blob: dummy
	$(MAKE) -C $@ -e MODULE=plainTestBlob -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

Database: dummy
	$(MAKE) -C $@ -e MODULE=dbTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

Memory: dummy
	$(MAKE) -C $@ -e MODULE=memTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

Basetypes: dummy
	$(MAKE) -C $@ -e MODULE=Basetypes -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

MetaApplication: dummy
	$(MAKE) -C $@ -e MODULE=test$@ -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

Events: dummy
	$(MAKE) -C $@ -e MODULE=test$@ -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

Translation: dummy
	$(MAKE) -C $@ -e MODULE=test$@ -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

PluginTest: dummy
	$(MAKE) -C $@ -e MODULE=PluginTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

Parameter: dummy
	$(MAKE) -C $@ -e MODULE=ParameterTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

PluginTranslationsModel: dummy
	$(MAKE) -C $@ -e MODULE=test$@ -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

PluginByInterfaceAndNamespace: dummy
	$(MAKE) -C $@ -e MODULE=PluginTestInterface -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

clean:
	for sub_target in $(ALLTARGETS); do $(MAKE) -C $$sub_target clean; done 

install:
	for sub_target in $(ALLTARGETS); do $(MAKE) -C $$sub_target install; done 

install-strip:
	for sub_target in $(ALLTARGETS); do $(MAKE) -C $$sub_target install-strip; done


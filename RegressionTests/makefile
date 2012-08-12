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

ALLTARGETS = \
	Database/Plain-ODBC-Test \
	Database/Plain-ODBC-Test-Blob \
	Database/Plain-ODBC-Test-Refresh \
	Database \
	ContainerTest \
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
	Database/DatabaseLayerWrapperTest \
	Database/Plain-ODBC-Test \
	Database/Plain-ODBC-Test-Blob \
	Database/Plain-ODBC-Test-Refresh \
	Database \
	ContainerTest \
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
	UAPLeakTest \
	Database/FKTest \
	Database/DatabaseLayerWrapperTest \
	Database/Plain-ODBC-Test \
	Database/Plain-ODBC-Test-Blob \
	Database/Plain-ODBC-Test-Refresh \
	Database \
	TestUMLImport \
	ContainerTest \
	Basetypes \
	Memory \
	MetaApplication \
	Events \
	Translation \
	PluginTest

endif

ifeq ($(OSTYPE), Windows_NT)

TARGET_SELECTOR=_target_mingw
#TARGET_SELECTOR=

TARGETEXE=exe$(TARGET_SELECTOR)
TARGETWXEXE=exe$(TARGET_SELECTOR)
TARGETDLL=dll$(TARGET_SELECTOR)
TARGETFRAMEWORK=dll$(TARGET_SELECTOR)
TARGETSHARED=dll$(TARGET_SELECTOR)
TARGETWXSHARED=dll$(TARGET_SELECTOR)
TARGETXSLTDLL=xsltdll$(TARGET_SELECTOR)
TARGETPLUGIN=plugin$(TARGET_SELECTOR)
TARGETWXPLUGIN=wxplugin$(TARGET_SELECTOR)

ALLTARGETS = \
	Database/DatabaseLayerWrapperTest \
	Database/Plain-ODBC-Test \
	Database/Plain-ODBC-Test-Blob \
	Database/Plain-ODBC-Test-Refresh \
	Database/FKTest \
	Database \
	TestUMLImport \
	ContainerTest \
	Basetypes \
	Memory \
	MetaApplication \
	Events \
	Translation \
	PluginByInterfaceAndNamespace \
	Parameter \
	PluginTranslationsModel \
	PluginTest \
	TestGDB

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
	$(MAKE) -C $@ -e MODULE=fkTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

Database/DatabaseLayerWrapperTest: dummy
	$(MAKE) -C $@ -e MODULE=DatabaseLayerWrapperTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@


Database/Plain-ODBC-Test: dummy
	echo CRUISECONTROL: $(CRUISECONTROL)
	echo DEVROOT_MAKE: $(DEVROOT_MAKE)
	echo RELPATH: $(RELPATH)
	echo $(MAKE) -C $@ -e MODULE=plainODBCTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@ -e MODULE=plainODBCTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

Database/Plain-ODBC-Test-Blob: dummy
	$(MAKE) -C $@ -e MODULE=plainODBCTestBlob -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

Database/Plain-ODBC-Test-Refresh: dummy
	$(MAKE) -C $@ -e MODULE=plainODBCTestRefresh -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

ContainerTest: dummy
	$(MAKE) -C $@ -e MODULE=ContainerTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

TestUMLImport: dummy
	$(MAKE) -C $@ -e MODULE=testUMLImport -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

Database: dummy
	$(MAKE) -C $@ -e MODULE=dbTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

Memory: dummy
	$(MAKE) -C $@ -e MODULE=memTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

UAPLeakTest: dummy
	$(MAKE) -C $@ -e MODULE=UAPLeakTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

TestGDB: dummy
	$(MAKE) -C $@ -e MODULE=TestGDB -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

Basetypes: dummy
	$(MAKE) -C $@ -e MODULE=Basetypes -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

MetaApplication: dummy
	$(MAKE) -C $@ -e MODULE=test$@ -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

Events: dummy
	$(MAKE) -C $@ -e MODULE=test$@ -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

Translation: dummy
	$(MAKE) -C $@ -e MODULE=test$@ -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

PluginTest: dummy
	$(MAKE) -C $@ -e MODULE=PluginTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

Parameter: dummy
	$(MAKE) -C $@ -e MODULE=ParameterTest -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

PluginTranslationsModel: dummy
	$(MAKE) -C $@ -e MODULE=test$@ -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

PluginByInterfaceAndNamespace: dummy
	$(MAKE) -C $@ -e MODULE=PluginTestInterface -e TARGET=$(TARGETEXE) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

clean:
	for sub_target in $(ALLTARGETS); do $(MAKE) -C $$sub_target clean; done

install:
	for sub_target in $(ALLTARGETS); do $(MAKE) -C $$sub_target install; done

install-strip:
	for sub_target in $(ALLTARGETS); do $(MAKE) -C $$sub_target install-strip; done


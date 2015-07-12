# Global makefile to build all sub modules
# **************************************************************
# *
# **************************************************************

#
# False targets
#
#.PHONY: dummy

ifeq ($(CRUISECONTROL), yes)
RELPATH=/Projects/CPP
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


Path=$(PATH)

ifeq ($(OSTYPE), solaris)

TARGETDLL=so
TARGETEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
	lbANTLR3 \
	DomainLanguages/lbUILanguage \
	wxWidgets/wxPropertyForm \
	wxWidgets/wxUpdateChecker \
	wxWidgets/wxSFDesigner \
	UserFeedback \
	TestPlugin \
	VisitorOperations \
	DatabaseLayerGateway \
	DatabaseForm \
	lbDMFDataModel \
	lbXSLTTransformer \
	lbFileOperationsPlugin \
	lbBasicEventHandlers \
	DatabaseReport
endif

ifeq ($(OSTYPE), linux-debian-ppc)

TARGETDLL=so
TARGETEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
	lbANTLR3 \
	DomainLanguages/lbUILanguage \
	wxWidgets/wxPropertyForm \
	wxWidgets/wxUpdateChecker \
	wxWidgets/wxSFDesigner \
	UserFeedback \
	TestPlugin \
	DatabaseLayerGateway \
	VisitorOperations \
	DatabaseForm \
	lbDMFDataModel \
	lbXSLTTransformer \
	lbFileOperationsPlugin \
	lbBasicEventHandlers \
	DatabaseReport
endif

ifeq ($(OSTYPE), linux)

TARGETDLL=so
TARGETEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
	lbANTLR3 \
	DomainLanguages/lbUILanguage \
	wxWidgets/wxPropertyForm \
	wxWidgets/wxUpdateChecker \
	wxWidgets/wxSFDesigner \
	UserFeedback \
	TestPlugin \
	DatabaseLayerGateway \
	VisitorOperations \
	DatabaseForm \
	lbDMFDataModel \
	lbXSLTTransformer \
	lbFileOperationsPlugin \
	lbBasicEventHandlers \
	DatabaseReport
endif

ifeq ($(OSTYPE), osx)

TARGETDLL=so
TARGETEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

ALLTARGETS = \
	lbANTLR3 \
	DomainLanguages/lbUILanguage \
	wxWidgets/wxPropertyForm \
	wxWidgets/wxUpdateChecker \
	wxWidgets/wxSFDesigner \
	UserFeedback \
	TestPlugin \
	DatabaseLayerGateway \
	VisitorOperations \
	DatabaseForm \
	lbDMFDataModel \
	lbXSLTTransformer \
	lbFileOperationsPlugin \
	lbBasicEventHandlers \
	DatabaseReport
endif

ifeq ($(OSTYPE), Windows_NT)


TARGET_SELECTOR=_target_mingw
#TARGET_SELECTOR=

TARGETDLL=dll$(TARGET_SELECTOR)
TARGETEXE=exe$(TARGET_SELECTOR)
TARGETWXPLUGIN=wxplugin$(TARGET_SELECTOR)
TARGETPLUGIN=plugin$(TARGET_SELECTOR)

ALLTARGETS = \
	lbANTLR3 \
	DomainLanguages/lbUILanguage \
	wxWidgets/wxPropertyForm \
	wxWidgets/wxUpdateChecker \
	wxWidgets/wxSFDesigner \
	UserFeedback \
	VisitorOperations \
	DatabaseForm \
	lbDMFDataModel \
	TestPlugin \
	DatabaseLayerGateway \
	lbXSLTTransformer \
	lbFileOperationsPlugin \
	lbBasicEventHandlers \
	DatabaseReport
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

wxWidgets/wxPropertyForm: dummy
	$(MAKE) -C $@ -e MODULE=lbwxPropertyForm -e TARGET=$(TARGETWXPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

wxWidgets/wxUpdateChecker: dummy
	$(MAKE) -C $@ -e MODULE=lbwxUpdateChecker -e TARGET=$(TARGETWXPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

wxWidgets/wxSFDesigner: dummy
	$(MAKE) -C $@ -e MODULE=lbwxSFDesigner -e TARGET=$(TARGETWXPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

UserFeedback: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

lbBasicEventHandlers: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

lbFileOperationsPlugin: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

lbXSLTTransformer: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

lbANTLR3: dummy
	$(MAKE) -C $@ -e MODULE=lbANTLR3 -e TARGET=$(TARGETPLUGIN) -e CUSTOM_FILES='*.c' -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

DomainLanguages/lbUILanguage: dummy
	$(MAKE) -C $@ -e MODULE=lbUILanguage -e TARGET=$(TARGETPLUGIN) -e CUSTOM_FILES='output/*.c' -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

TestPlugin: dummy
	$(MAKE) -C $@ -e MODULE=TestPlugin -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

DatabaseForm: dummy
	$(MAKE) -C $@ -e MODULE=lbDatabaseForm -e TARGET=$(TARGETWXPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@
	
DatabaseLayerGateway: dummy
	$(MAKE) -C $@ -e MODULE=DatabaseLayerGateway -e TARGET=$(TARGETWXPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@
	
lbDMFDataModel: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@
	
DatabaseReport: dummy
	$(MAKE) -C $@ -e MODULE=lbDatabaseReport -e TARGET=$(TARGETWXPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@
	
VisitorOperations: dummy
	$(MAKE) -C $@ -e MODULE=lbVisitorOperations -e TARGET=$(TARGETPLUGIN) -e CUSTOM_FILES='*.c' -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
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



# Global makefile to build all sub modules
# **************************************************************
# *
# **************************************************************

#
# False targets
#
#.PHONY: dummy

ifeq ($(CRUISECONTROL), yes)
RELPATH=/Projects/$(REPO_NAME)
endif

ifneq ($(CRUISECONTROL), yes)
RELPATH=/Projects/$(REPO_NAME)
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

LBWXVERSION_CC_DEFAULT=old

ifeq ($(OSPLATFORM), arm)
LBWXVERSION_CC_DEFAULT=current
endif


Path=$(PATH)

ifeq ($(OSTYPE), solaris)

TARGETDLL=so
TARGETEXE=elf
TARGETWXPLUGIN=wxsoplugin
TARGETPLUGIN=soplugin

#Not yet activated.
#	../vendor/boost_1_59_0 \
#	../vendor/log4cplus-1.2.0-rc5 \
#	../vendor/gelf4cplus-master \
#	lbGraylogAdapter \

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

#Not yet activated.
#	../vendor/boost_1_59_0 \
#	../vendor/log4cplus-1.2.0-rc5 \
#	../vendor/gelf4cplus-master \
#	lbGraylogAdapter \

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

#Not yet activated.
#	../vendor/boost_1_59_0 \
#	../vendor/log4cplus-1.2.0-rc5 \
#	../vendor/gelf4cplus-master \
#	lbGraylogAdapter \

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

#Not yet activated.
#	../vendor/boost_1_59_0 \
#	../vendor/log4cplus-1.2.0-rc5 \
#	../vendor/gelf4cplus-master \
#	lbGraylogAdapter \

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

#Not yet activated.
#	../vendor/boost_1_59_0 \
#	../vendor/log4cplus-1.2.0-rc5 \
#	../vendor/gelf4cplus-master \
#	lbGraylogAdapter \

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
ifeq ($(CRUISECONTROL), yes)
	$(MAKE) -s -C $@ -e LBWXVERSION=$(LBWXVERSION_CC_DEFAULT)
else
	$(MAKE) -s -C $@ -e LBWXVERSION=current
endif

wxWidgets/wxUpdateChecker: dummy
	$(MAKE) -C $@ -e MODULE=lbwxUpdateChecker -e TARGET=$(TARGETWXPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
ifeq ($(CRUISECONTROL), yes)
	$(MAKE) -s -C $@ -e LBWXVERSION=$(LBWXVERSION_CC_DEFAULT)
else
	$(MAKE) -s -C $@ -e LBWXVERSION=current
endif

wxWidgets/wxSFDesigner: dummy
	$(MAKE) -C $@ -e MODULE=lbwxSFDesigner -e TARGET=$(TARGETWXPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
ifeq ($(CRUISECONTROL), yes)
	$(MAKE) -s -C $@ -e LBWXVERSION=$(LBWXVERSION_CC_DEFAULT)
else
	$(MAKE) -s -C $@ -e LBWXVERSION=current
endif

UserFeedback: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@

ifeq ($(OSTYPE), linux)

../vendor/boost_1_59_0: dummy
	tar xvzf ../vendor/boost_1_59_0.tar.gz -C ../vendor
	cd ../vendor/boost_1_59_0; pwd;	ls; chmod +x ./bootstrap.sh; \
	export NO_BZIP2=1; \
	./bootstrap.sh --prefix=$HOME/pool --libdir=$HOME/pool/lib --with-libraries=signals,thread,python; \
	./bjam address-model=32_64 architecture=x86 variant=release link=shared --with-iostreams install

endif

ifeq ($(OSTYPE), osx)

../vendor/boost_1_59_0: dummy
	tar xvzf ../vendor/boost_1_59_0.tar.gz -C ../vendor
	cd ../vendor/boost_1_59_0; pwd;	ls; chmod +x ./bootstrap.sh; \
	export NO_BZIP2=1; \
	./bootstrap.sh --prefix=$HOME/pool --libdir=$HOME/pool/lib --with-libraries=signals,thread,python; \
	./bjam address-model=32_64 architecture=x86 variant=release link=shared --with-iostreams install

endif

ifeq ($(OSTYPE), Windows_NT)

../vendor/boost_1_59_0.7z: dummy
	7z -y -r x ..\\vendor\\boost_1_59_0.7z -o..\\vendor

../vendor/boost_1_59_0: ../vendor/boost_1_59_0.7z dummy
	export NO_BZIP2=1; cd $(DEVROOT_MAKE)$(RELPATH)/vendor/boost_1_59_0;\
	./bootstrap.bat gcc --prefix=$HOME/pool --libdir=$HOME/pool/lib --with-libraries=signals,thread,python; \
	./b2 toolset=gcc --build-type=minimal stage --with-iostreams

endif

ifeq ($(OSTYPE), linux)

../vendor/log4cplus-1.2.0-rc5: dummy
	tar xvzf ../vendor/log4cplus-1.2.0-rc5.tar.gz -C ../vendor
	cd ../vendor/log4cplus-1.2.0-rc5; \
	./configure --enable-threads=no --prefix=$(HOME); \
	$(MAKE); \
	$(MAKE) install

endif

ifeq ($(OSTYPE), osx)

../vendor/log4cplus-1.2.0-rc5: dummy
	tar xvzf ../vendor/log4cplus-1.2.0-rc5.tar.gz -C ../vendor
	cd ../vendor/log4cplus-1.2.0-rc5; \
	./configure CXXFLAGS=$(LOG4CPLUSARCH) --enable-threads=no --prefix=$(HOME); \
	$(MAKE); \
	$(MAKE) install

endif

ifeq ($(OSTYPE), Windows_NT)

../vendor/log4cplus-1.2.0-rc5.tar.gz:
	tar xvzf ../vendor/log4cplus-1.2.0-rc5.tar.gz -C ../vendor

../vendor/log4cplus-1.2.0-rc5: ../vendor/log4cplus-1.2.0-rc5.tar.gz
	cd ..\\vendor\\log4cplus-1.2.0-rc5; \
	./configure --enable-threads=no; \
	$(MAKE); \
	$(MAKE) install

endif

../vendor/gelf4cplus-master: ../vendor/boost_1_59_0 ../vendor/log4cplus-1.2.0-rc5 dummy
	

lbGraylogAdapter: ../vendor/gelf4cplus-master dummy
	@echo You probably need to download the prerequisites from https://github.com/Gelber/gelf4cplus. I am using a snapshot...
	-$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	-$(MAKE) -C $@

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
ifeq ($(CRUISECONTROL), yes)
	$(MAKE) -s -C $@ -e LBWXVERSION=$(LBWXVERSION_CC_DEFAULT)
else
	$(MAKE) -s -C $@ -e LBWXVERSION=current
endif
	
DatabaseLayerGateway: dummy
	$(MAKE) -C $@ -e MODULE=DatabaseLayerGateway -e TARGET=$(TARGETWXPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
ifeq ($(CRUISECONTROL), yes)
	$(MAKE) -s -C $@ -e LBWXVERSION=$(LBWXVERSION_CC_DEFAULT)
else
	$(MAKE) -s -C $@ -e LBWXVERSION=current
endif
	
lbDMFDataModel: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET=$(TARGETPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
	$(MAKE) -C $@
	
DatabaseReport: dummy
	-$(MAKE) -C $@ -e MODULE=lbDatabaseReport -e TARGET=$(TARGETWXPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
ifeq ($(CRUISECONTROL), yes)
	-$(MAKE) -s -C $@ -e LBWXVERSION=$(LBWXVERSION_CC_DEFAULT)
else
	-$(MAKE) -s -C $@ -e LBWXVERSION=current
endif
	
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



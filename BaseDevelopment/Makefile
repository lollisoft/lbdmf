# Global makefile to build all sub modules
# **************************************************************
# * $Locker:  $
# * $Revision: 1.11 $
# * $Name:  $
# * $Id: Makefile,v 1.11 2004/10/16 09:47:37 lollisoft Exp $
# *
# * $Log: Makefile,v $
# * Revision 1.11  2004/10/16 09:47:37  lollisoft
# * New make system works nearly perfect. It does not longer build unnessesary.
# *
# * Revision 1.10  2004/10/09 18:01:27  lollisoft
# * Added distclean feature
# *
# * Revision 1.9  2004/10/09 17:22:51  lollisoft
# * Changed make process for wx based apps
# *
# * Revision 1.8  2004/10/09 16:52:46  lollisoft
# * Enhancements for cleaning up
# *
# * Revision 1.7  2004/08/17 20:04:02  lollisoft
# * Deactivated parts, that do not compile under Linux and added demo app module including sample apps
# *
# * Revision 1.6  2004/07/18 07:28:25  lollisoft
# * Now the database sample works also under linux. Some bugs solved and minor changes
# *
# * Revision 1.5  2004/06/06 12:55:58  lollisoft
# * Added new module lbPluginManager
# *
# * Revision 1.4  2003/05/24 02:09:44  lollisoft
# * Added lbDB module
# *
# * Revision 1.3  2003/02/17 21:34:33  lollisoft
# * Much problems with compilation solved, bu wy came this ??
# *
# * Revision 1.2  2002/11/29 19:50:26  lothar
# * Compiles again under linux, but some problems at runtime with DOMString
# *
# * Revision 1.1  2001/10/14 10:25:56  lothar
# * Initial
# *
# **************************************************************

#
# False targets
#
#.PHONY: dummy

Path=$(PATH)

MAKESUBDIR= \
	@( \
	cd $@; \
	./makefile.sh; \
	make; \
	)

MAKEWXSAMPLE= \
	@( \
	cd $@; \
	cp makefile.wx-sample makefile; \
	make; \
	)

ALLTARGETS = lbhook \
	lbDB \
	lbModule \
	lbclasses \
	lbMetaApplication \
	../AppDevelopmentDemo/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapper


all_targets: $(ALLTARGETS)



clean:
	@for d in $(ALLTARGETS); do \
	    $(MAKE) -C $$d clean || exit $? ; \
	done

distclean:
	@for d in $(ALLTARGETS); do \
	    $(MAKE) -C $$d distclean || exit $? ; \
	done


#	Doesn't compile yet under linux
#	lbPluginManager \
#	Doesn't compile if XML dependend module XML4C (alphaworks) is not installed
#	lbXMLConfig/lbDOMConfig \

dummy:

../Test/Console/XML: dummy
	$(MAKE) -C $@ -e MODULE=Test -e TARGET="exe" -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

../Test/GUI/wxWrapper: dummy
	$(MAKEWXSAMPLE)

#$(MAKEWXSAMPLE)

../AppDevelopmentDemo/App: dummy
	$(MAKE) -C $@ -e MODULE=Application -e TARGET="dll" -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

lbhook: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET="dll" -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

lbDB: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET="dll" -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

lbPluginManager: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET="dll" -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

lbModule: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET="dll" -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

lbclasses: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET="dll" -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

lbMetaApplication: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET="dll" -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

lbXMLConfig/lbDOMConfig: dummy
	$(MAKE) -C $@ -e MODULE=$@ -e TARGET="dll" -f $(DEVROOT_MAKE)/Projects/CPP/make/makefile.configure
	$(MAKE) -C $@

# Global makefile to build all sub modules
# **************************************************************
# * $Locker:  $
# * $Revision: 1.4 $
# * $Name:  $
# * $Id: Makefile,v 1.4 2003/05/24 02:09:44 lollisoft Exp $
# *
# * $Log: Makefile,v $
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

MAKESUBDIR= \
	@( \
	cd $@; \
	pwd; \
	./makefile.sh; \
	make; \
	cd ..; \
	)

all_targets: lbHook lbDB lbModule lbclasses lbMetaApplication lbXMLConfig/lbDOMConfig

dummy:

lbHook: dummy
	echo "Make with Makefile"
	$(MAKESUBDIR)

lbDB: dummy
	$(MAKESUBDIR)

lbModule: dummy
	$(MAKESUBDIR)

lbclasses: dummy
	$(MAKESUBDIR)

lbMetaApplication: dummy
	$(MAKESUBDIR)

lbXMLConfig/lbDOMConfig:dummy
	$(MAKESUBDIR)

# Global makefile to build all sub modules
# **************************************************************
# * $Locker:  $
# * $Revision: 1.2 $
# * $Name:  $
# * $Id: Makefile,v 1.2 2002/11/29 19:50:26 lothar Exp $
# *
# * $Log: Makefile,v $
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

all_targets: lbHook lbModule lbclasses lbMetaApplication lbXMLConfig/lbDOMConfig

dummy:

lbHook: dummy
	$(MAKESUBDIR)

lbModule: dummy
	$(MAKESUBDIR)

lbclasses: dummy
	$(MAKESUBDIR)

lbMetaApplication: dummy
	$(MAKESUBDIR)

lbXMLConfig/lbDOMConfig:dummy
	$(MAKESUBDIR)

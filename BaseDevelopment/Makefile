# Global makefile to build all sub modules
# **************************************************************
# * $Locker:  $
# * $Revision: 1.1 $
# * $Name:  $
# * $Id: Makefile,v 1.1 2001/10/14 10:25:56 lothar Exp $
# *
# * $Log: Makefile,v $
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
	./make.sh; \
	cd ..; \
	)

all_targets: lbHook lbModule

dummy:

lbHook: dummy
	$(MAKESUBDIR)

lbModule: dummy
	$(MAKESUBDIR)


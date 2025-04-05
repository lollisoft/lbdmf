
all: subs

include ../MakeVars

DIRS=naming events property-daemon relship stream-bench trader

subs:
	for i in $(DIRS); do $(MAKE) -C $$i || exit 1; done

clean:
	for i in $(DIRS); do $(MAKE) -C $$i clean || exit 1; done
	rm -f *.o core *~ .depend

install:
	$(IDIRCMD) $(INSTDIR)/doc/mico/examples/services
	$(ISRCCMD) Makefile $(INSTDIR)/doc/mico/examples/services
	$(ISRCCMD) README $(INSTDIR)/doc/mico/examples/services
	for i in $(DIRS) stream-sound; do $(MAKE) -C $$i install || exit 1; done


all: .depend client server

DIR_PREFIX=../
include ../../MakeVars

INSTALL_DIR     = poa/account-1
INSTALL_SRCS    = Makefile client.cc server.cc account.idl
INSTALL_SCRIPTS = account

server: account.h account.o server.o $(DEPS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) account.o server.o $(LDLIBS) -o server

client: account.h account.o client.o $(DEPS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) account.o client.o $(LDLIBS) -o client 


account.h account.cc : account.idl $(IDLGEN)
	$(IDL) --poa --no-boa account.idl

clean:
	rm -f account.cc account.h Bank.ref *.o core client server *~ .depend

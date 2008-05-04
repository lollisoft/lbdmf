YACC   = bison
LEX    = flex
CC     = gcc
CCOPTS = -g -Wall -O2 -DOSX

.PHONY: clean
all: fk

COMMON = \
lex.yy.c \
gram.tab.c \
mempool.c \
list.c

lex.yy.c: scan.l
	$(LEX) -i $<

gram.tab.c: gram.y
	$(YACC) -d -v gram.y

fk: fk.c $(COMMON)
	$(CC) $(CCOPTS) -o $@ fk.c $(COMMON)

clean:
	rm -f gram.tab.c gram.tab.h gram.output
	rm -f lex.yy.c
	rm -f fk

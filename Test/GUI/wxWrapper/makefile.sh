#/bin/sh

# This script creates a makefile based on templates

cat $DEVROOT/Projects/CPP/make/makefile.template > makefile
cat makefile.module >> makefile
echo all: Test >> makefile
echo >> makefile

mkmk elf Test ../dosdir,../include,../interfaces test.cpp >> makefile

#/bin/sh

# This script creates a makefile based on templates

cat $DEVROOT/Projects/CPP/make/makefile.template > makefile
cat makefile.module >> makefile
echo all: wxWrapper >> makefile
echo >> makefile

mkmk elf wxWrapper ../dosdir,../include,../interfaces dynamic.cpp >> makefile

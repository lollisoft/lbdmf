#/bin/sh

# This script creates a makefile based on templates

cat makefile.template > makefile
cat makefile.module >> makefile
echo all: mkmk >> makefile
echo >> makefile

mkmk - mkmk ../dosdir,../include,../interfaces *.cpp >> makefile

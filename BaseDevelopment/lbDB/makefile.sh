#/bin/sh

# This script creates a makefile based on templates

cat ../../make/makefile.template > makefile
cat makefile.module >> makefile
echo all: lbDB >> makefile
echo >> makefile

mkmk SO lbDB ../dosdir,../include,../interfaces *.cpp >> makefile

#/bin/sh

# This script creates a makefile based on templates

cat ../../make/makefile.template > makefile
cat makefile.module >> makefile
echo all: lbclasses >> makefile
echo >> makefile

mkmk SO lbclasses ../include,../interfaces *.cpp >> makefile

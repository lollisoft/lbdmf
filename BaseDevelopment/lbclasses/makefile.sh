#/bin/sh

# This script creates a makefile based on templates

cat ../../make/makefile.template > makefile
cat makefile.module >> makefile
echo all: lbClasses >> makefile
echo >> makefile

mkmk SO lbClasses ../include,../interfaces *.cpp >> makefile

#/bin/sh

# This script creates a makefile based on templates

cat ../../make/makefile.template > makefile
cat makefile.module >> makefile
echo all: lbModule >> makefile
echo >> makefile

mkmk SO lbModule ../dosdir,../include,../interfaces *.cpp >> makefile

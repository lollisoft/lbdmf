#/bin/sh

# This script creates a makefile based on templates

cat ../../../make/makefile.template > makefile
cat makefile.module >> makefile
echo all: lbDOMConfig >> makefile
echo >> makefile

mkmk SO lbDOMConfig ../../include,../../interfaces *.cpp >> makefile

#/bin/sh

# This script creates a makefile based on templates

cat ../../make/makefile.template > makefile
cat makefile.module >> makefile
echo all: lbMetaApp >> makefile
echo >> makefile

mkmk SO lbMetaApp ../include,../interfaces *.cpp >> makefile

#/bin/sh


# This script creates a makefile based on templates

cat ../../make/makefile.template > makefile
cat makefile.module >> makefile
echo all: lbMetaApplication >> makefile
echo >> makefile

mkmk SO lbMetaApplication ../include,../interfaces *.cpp >> makefile

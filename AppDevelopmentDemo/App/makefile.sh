#/bin/sh

# This script creates a makefile based on templates

cat ../../make/makefile.template > makefile
cat makefile.module >> makefile
echo all: Application >> makefile
echo >> makefile

mkmk SO Application ../dosdir,../include,../interfaces *.cpp >> makefile

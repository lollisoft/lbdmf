#/bin/sh

# This script creates a makefile based on templates

cat ../../make/makefile.template > makefile
cat makefile.module >> makefile
echo all: lbPluginManager >> makefile
echo >> makefile

mkmk SO lbPluginManager ../dosdir,../include,../interfaces *.cpp >> makefile

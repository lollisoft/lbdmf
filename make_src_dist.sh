#!/bin/sh
export DEVROOT=dist/Develop/Projects/CPP

if [ -e "dist" ]; then
	rm -R dist;
fi

mkdir dist
cd dist
cvs -d:ext:lollisoft@cvs.sourceforge.net:/cvsroot/lbdmf export -r HEAD CPP
cp ../Plugins/DatabaseReport/repwrt.cpp CPP/Plugins/DatabaseReport/repwrt.cpp
cp ../Plugins/DatabaseReport/repwrt.h CPP/Plugins/DatabaseReport/repwrt.h

# Remove some vendor packages, I do not use yet.

rm -R CPP/vendor/c-goldparser

ARCH=`arch`

if [ "$ARCH" == "ppc" ]; then
	exit;
fi

echo Do Linux stuff
mkdir lbdmf-$1
mv CPP lbdmf-$1
cp lbdmf-$1/CPP/configure lbdmf-$1
tar cvzf lbDMF-Source-$1.tgz lbdmf-$1/
cp lbDMF-Source-$1.tgz /usr/src/packages/SOURCES
cd ..
#rpmbuild -ba lbDMF.spec

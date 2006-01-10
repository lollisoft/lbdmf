#!/bin/sh
export DEVROOT=dist/Develop/Projects/CPP

if [ -e "dist" ]; then
	rm -R dist;
fi

mkdir dist
cd dist
#cvs -d:pserver:anonymous@cvs.sourceforge.net:/cvsroot/lbdmf login
cvs -d:ext:lollisoft@cvs.sourceforge.net:/cvsroot/lbdmf export -r HEAD CPP
cp ../Plugins/DatabaseReport/repwrt.cpp CPP/Plugins/DatabaseReport/repwrt.cpp
cp ../Plugins/DatabaseReport/repwrt.h CPP/Plugins/DatabaseReport/repwrt.h
tar cvzf lbDMF-Source-$1.tgz CPP/
cp lbDMF-Source-$1.tgz /usr/src/packages/SOURCES
cd ..
rpmbuild -ba lbDMF.spec
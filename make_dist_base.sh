#!/bin/sh

echo cp -r $1 $DEVROOT/$1
cp -r $1 $DEVROOT/$1
cd $DEVROOT/$1


if [ -e CVS ]; then
    rm -R CVS
fi

#rm *.bsc
#rm *.sbr
#rm *.exe
#rm *.obj

if [ -e *.bak ]; then
    rm *.bak
fi

if [ -e .#* ]; then
    rm .#*
fi

#rm *.ilk
#rm *.pch
#rm *.pdb
#rm *.lib
#rm *.dll
#rm *.mak
#rm *.opt
#rm *.lnk
#rm *.lb1
#rm *.lk1
#rm *.mk1
#rm *.sym
#rm *.map
#rm *.exp
#rm *.idb
#rm *.$$$
#rm null
if [ -e *.o ]; then
    rm *.o
fi
if [ -e *.so* ]; then
    rm *.so*
fi
cd ~/develop/Projects/CPP

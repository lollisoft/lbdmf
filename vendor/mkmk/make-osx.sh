#!/bin/sh
echo Make MKMK for OSX
cd $1
c++ mkmk.cpp -c -DUNIX -DOSX \
    -I /usr/include \
    -I ../dosdir

c++ contain.cpp -c -DUNIX -DOSX \
    -I /usr/include \
    -I ../dosdir

c++ -o mkmk contain.o mkmk.o ../dosdir/match.o ../dosdir/dosdir.o

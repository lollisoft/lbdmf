#!/bin/sh

echo Make MKMK for Linux

cd $1

g++-4.1 mkmk.cpp -c -DUNIX \
    -I /usr/include \
    -I ../dosdir

g++-4.1 contain.cpp -c -DUNIX \
    -I /usr/include \
    -I ../dosdir

g++-4.1 -o mkmk contain.o mkmk.o ../dosdir/match.o ../dosdir/dosdir.o

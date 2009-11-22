#!/bin/sh


cd $1

if [ $OSTYPE = solaris ]; then
echo Make MKMK for Solaris
CPP=g++
fi

if [ $OSTYPE = linux-debian-ppc ]; then
echo Make MKMK for Debian PPC
CPP=g++-4.1
fi

if [ $OSTYPE = linux ]; then
echo Make MKMK for Linux
CPP=g++
fi

if [ $OSTYPE = osx ]; then
echo Make MKMK for Mac OS X
CPP=g++

OSNAME=Panther

if [ $OSVERSION = 9.0.0 ]; then
OSNAME=Leopard
fi

if [ $OSVERSION = 9.1.0 ]; then
OSNAME=Leopard
fi

if [ $OSVERSION = 9.6.0 ]; then
OSNAME=Leopard
fi

if [ $OSVERSION = 9.8.0 ]; then
OSNAME=Leopard
fi

if [ $OSVERSION = 10.0.0 ]; then
OSNAME=Leopard
fi

fi

echo $OSNAME

$CPP mkmk.cpp -c -DOSX -DOSNAME_$OSNAME \
    -I /usr/include \
    -I ../dosdir

$CPP contain.cpp -c -DOSX \
    -I /usr/include \
    -I ../dosdir

$CPP -o mkmk contain.o mkmk.o ../dosdir/match.o ../dosdir/dosdir.o

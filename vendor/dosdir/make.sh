#!/bin/sh

cd $1

if [ $OSTYPE = solaris ]; then
	gcc dosdir.c -fPIC -g -c -DUNIX \
	    -I /usr/include \
	    -I .
	gcc match.c -fPIC -g -c -DUNIX \
	    -I /usr/include \
	    -I .
fi

if [ $OSTYPE = linux ]; then
	cc dosdir.c -fPIC -g -c -DUNIX \
	    -I /usr/include \
	    -I .
	cc match.c -fPIC -g -c -DUNIX \
	    -I /usr/include \
	    -I .
fi    

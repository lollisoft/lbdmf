#!/bin/sh

cd $1

cc dosdir.c -fPIC -g -c -DUNIX \
    -I /usr/include \
    -I .
cc match.c -fPIC -g -c -DUNIX \
    -I /usr/include \
    -I .
    

#!/bin/sh
cc dosdir.c -fPIC -g -c -DUNIX \
    -I /usr/include \
    -I .
cc match.c -fPIC -g -c -DUNIX \
    -I /usr/include \
    -I .
    
#!/bin/sh
c++ lbHook.cpp -fPIC -g -c -DLINUX \
    -I linuxCode \
    -I ../../interfaces \
    -I ../../include

cc linuxCode/conio.c -fPIC -g -c -DLINUX \
    -I linuxCode \
    -I ../../interfaces \
    -I ../../include

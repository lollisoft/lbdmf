#!/bin/sh
#cc linuxCode/conio.c -fPIC -g -c -DLINUX \
#    -I linuxCode \
#    -I ../../interfaces \
#    -I ../../include

c++ lbHook.cpp -fPIC -g -c -DLINUX \
    -I linuxCode \
    -I ../../interfaces \
    -I ../../include

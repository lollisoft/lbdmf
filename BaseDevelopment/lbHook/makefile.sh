#!/bin/sh
# This script creates a makefile based on templates

cat $DEVROOT/Projects/CPP/make/makefile.template > makefile
cat makefile.module >> makefile
echo all: lbhook >> makefile

mkmk so lbhook . linuxCode/conio.c *.cpp >> makefile

#!/bin/sh

MODULELIB=lbModule.so
export MODULELIB
LBXMLFUNCTOR=getlbDOMConfigInstance
export LBXMLFUNCTOR
LBMODULEFUNCTOR=getlb_ModuleInstance
export LBMODULEFUNCTOR
DEVROOT=~/develop
export DEVROOT
LD_LIBRARY_PATH=~/lib:/usr/local/lib:
export LD_LIBRARY_PATH
OSTYPE=linux-debian-ppc
export OSTYPE
PATH=$PATH:~/bin
export PATH

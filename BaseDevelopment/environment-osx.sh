#!/bin/bash

CVS_RSH=ssh
MODULELIB=lbModule.so
LBXMLFUNCTOR=getlbDOMConfigInstance
LBMODULEFUNCTOR=getlb_ModuleInstance
DEVROOT=~/develop
LD_LIBRARY_PATH=~/lib:
OSTYPE=osx
PATH="/sw/bin:/sw/sbin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/X11R6/bin:~/bin:/usr/local/bin"

export CVS_RSH
export MODULELIB
export LBXMLFUNCTOR
export LBMODULEFUNCTOR
export DEVROOT
export LD_LIBRARY_PATH
export OSTYPE
export PATH

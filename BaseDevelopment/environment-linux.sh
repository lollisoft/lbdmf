#!/bin

CVS_RSH=ssh
MODULELIB=lbModule.so
LBXMLFUNCTOR=getlbDOMConfigInstance
LBMODULEFUNCTOR=getlb_ModuleInstance
DEVROOT=~/develop
LD_LIBRARY_PATH=~/lib:
PLUGIN_DIR=~/plugins
OSTYPE=linux
PATH="/usr/local/bin:/sw/bin:/sw/sbin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/X11R6/bin:~/bin:$HOME/bin:/usr/local/bin:/usr/brlcad/bin:/opt/local/bin"

# On older OSX
# #DEVELOPER_TOOLS_PATH=/Developer/Tools
# #export DEVELOPER_TOOLS_PATH
# # On newer OSX

OSVERSION=`uname -r`
export OSVERSION
OSPLATFORM=`uname -p`
export OSPLATFORM

export CVS_RSH
export MODULELIB
export LBXMLFUNCTOR
export LBMODULEFUNCTOR
export DEVROOT
export LD_LIBRARY_PATH
export OSTYPE
export PATH
export PLUGIN_DIR
REPO_NAME=lbdmf
export REPO_NAME

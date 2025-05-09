#!/bin/sh

export REPO_NAME=lbdmf
prefix=`pwd`
export prefix

echo Hudson build started at: `pwd`
echo all: BaseDevelopment > Projects/$REPO_NAME/makefile
echo \# >> Projects/$REPO_NAME/makefile

#echo Updating full source tree to be save
#cvs update -d

echo export DEVROOT=`pwd` >> Projects/$REPO_NAME/makefile
echo export prefix=`pwd` >> Projects/$REPO_NAME/makefile
echo export PATH=`pwd`/bin:/usr/bin:/usr/local/bin:$PATH >> Projects/$REPO_NAME/makefile
echo export MODULELIB=lbModule.so >> Projects/$REPO_NAME/makefile
echo export LBXMLFUNCTOR=getlbDOMConfigInstance >> Projects/$REPO_NAME/makefile
echo export LBMODULEFUNCTOR=getlb_ModuleInstance >> Projects/$REPO_NAME/makefile
echo export LD_LIBRARY_PATH=`pwd`/lib: >> Projects/$REPO_NAME/makefile
echo export OSTYPE=osx >> Projects/$REPO_NAME/makefile
echo export OSVERSION=`uname -r` >> Projects/$REPO_NAME/makefile
echo export OSPLATFORM=`uname -p` >> Projects/$REPO_NAME/makefile
echo export DEVELOPER_TOOLS_PATH=/Developer/Tools >> Projects/$REPO_NAME/makefile

i=0
while [ $# -gt 0 ]
do
  case $1 in
  "--prefix"*) 
	echo all: BaseDevelopment > Projects/$REPO_NAME/makefile
	echo \# >> Projects/$REPO_NAME/makefile
	echo DEVROOT=`pwd` >> Projects/$REPO_NAME/makefile
	echo export prefix=`echo $1 | awk -F = '{ print $2; }'` >> Projects/$REPO_NAME/makefile;;
  esac
  shift
done

echo dummy: >> Projects/$REPO_NAME/makefile
echo \ >> Projects/$REPO_NAME/makefile
echo BaseDevelopment: dummy >> Projects/$REPO_NAME/makefile
echo \	\$\(MAKE\) -s -C \$\@ -e LBWXVERSION=old -e DEVROOT=\$\(DEVROOT\) -e prefix=$\(prefix\) >> Projects/$REPO_NAME/makefile

echo \ >> Projects/$REPO_NAME/makefile
echo install: dummy >> Projects/$REPO_NAME/makefile
echo \	\$\(MAKE\) -s -C BaseDevelopment -e LBWXVERSION=old -e DEVROOT=\$\(DEVROOT\) -e prefix=$\(prefix\) install >> Projects/$REPO_NAME/makefile

DEVROOT=`pwd`
export DEVROOT
OSTYPE=osx
export OSTYPE
OSVERSION=`uname -r`
export OSVERSION
OSPLATFORM=`uname -p`
export OSPLATFORM
CRUISECONTROL=yes
export CRUISECONTROL
DEVELOPER_TOOLS_PATH=/Developer/Tools
export DEVELOPER_TOOLS_PATH
make -C Projects/$REPO_NAME -e LBWXVERSION=old -e DEVROOT=$DEVROOT -e prefix=$prefix -f makefile
make -C Projects/$REPO_NAME -e LBWXVERSION=old -e DEVROOT=$DEVROOT -e prefix=$prefix -f makefile install



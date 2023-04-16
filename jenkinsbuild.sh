#!/bin/sh

export REPO_NAME=lbdmf

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
echo export OSTYPE=linux >> Projects/$REPO_NAME/makefile

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
echo \	\$\(MAKE\) -s -C \$\@ -e DEVROOT=\$\(DEVROOT\) >> Projects/$REPO_NAME/makefile

echo \ >> Projects/$REPO_NAME/makefile
echo install: dummy >> Projects/$REPO_NAME/makefile
echo \	\$\(MAKE\) -s -C BaseDevelopment -e DEVROOT=\$\(DEVROOT\) install >> Projects/$REPO_NAME/makefile
OSTYPE=linux
export OSTYPE
CRUISECONTROL=yes
export CRUISECONTROL
make -C Projects/$REPO_NAME -f makefile

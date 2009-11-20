#!/bin/sh
echo Hudson build started at: `pwd`
echo all: BaseDevelopment > makefile
echo \# >> makefile

#echo Updating full source tree to be save
#cvs update -d

echo export DEVROOT=`pwd` >> makefile
echo export prefix=`pwd` >> makefile
echo export PATH=`pwd`/bin:/usr/local/bin:$PATH >> makefile
echo export MODULELIB=lbModule.so >> makefile
echo export LBXMLFUNCTOR=getlbDOMConfigInstance >> makefile
echo export LBMODULEFUNCTOR=getlb_ModuleInstance >> makefile
echo export LD_LIBRARY_PATH=`pwd`/lib: >> makefile
echo export OSTYPE=linux >> makefile

i=0
while [ $# -gt 0 ]
do
  case $1 in
  "--prefix"*) 
	echo all: BaseDevelopment > makefile
	echo \# >> makefile
	echo DEVROOT=`pwd` >> makefile
	echo export prefix=`echo $1 | awk -F = '{ print $2; }'` >> makefile;;
  esac
  shift
done

echo dummy: >> makefile
echo \ >> makefile
echo BaseDevelopment: dummy >> makefile
echo \	\$\(MAKE\) -s -C \$\@ -e DEVROOT=\$\(DEVROOT\) >> makefile
CRUISECONTROL=yes
export CRUISECONTROL
make

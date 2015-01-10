#!/bin/sh

echo Hudson build started at: `pwd`
echo all: BaseDevelopment > Projects/CPP/makefile
echo \# >> Projects/CPP/makefile

#echo Updating full source tree to be save
#cvs update -d

echo export DEVROOT=`pwd` >> Projects/CPP/makefile
echo export prefix=`pwd` >> Projects/CPP/makefile
echo export PATH=`pwd`/bin:/usr/bin:/usr/local/bin:$PATH >> Projects/CPP/makefile
echo export MODULELIB=lbModule.so >> Projects/CPP/makefile
echo export LBXMLFUNCTOR=getlbDOMConfigInstance >> Projects/CPP/makefile
echo export LBMODULEFUNCTOR=getlb_ModuleInstance >> Projects/CPP/makefile
echo export LD_LIBRARY_PATH=`pwd`/lib: >> Projects/CPP/makefile
echo export OSTYPE=osx >> Projects/CPP/makefile
echo export OSVERSION=`uname -r` >> Projects/CPP/makefile
echo export OSPLATFORM=`uname -p` >> Projects/CPP/makefile

i=0
while [ $# -gt 0 ]
do
  case $1 in
  "--prefix"*) 
	echo all: BaseDevelopment > Projects/CPP/makefile
	echo \# >> Projects/CPP/makefile
	echo DEVROOT=`pwd` >> Projects/CPP/makefile
	echo export prefix=`echo $1 | awk -F = '{ print $2; }'` >> Projects/CPP/makefile;;
  esac
  shift
done

echo dummy: >> Projects/CPP/makefile
echo \ >> Projects/CPP/makefile
echo BaseDevelopment: dummy >> Projects/CPP/makefile
echo \	\$\(MAKE\) -s -C \$\@ -e DEVROOT=\$\(DEVROOT\) >> Projects/CPP/makefile

echo \ >> Projects/CPP/makefile
echo install: dummy >> Projects/CPP/makefile
echo \	\$\(MAKE\) -s -C BaseDevelopment -e DEVROOT=\$\(DEVROOT\) install >> Projects/CPP/makefile

echo \ >> Projects/CPP/makefile
echo clean: dummy >> Projects/CPP/makefile
echo \	\$\(MAKE\) -s -C BaseDevelopment -e DEVROOT=\$\(DEVROOT\) clean >> Projects/CPP/makefile

echo \ >> Projects/CPP/makefile
echo wxWrapper: dummy >> Projects/CPP/makefile
echo \	\$\(MAKE\) -s -C Test/GUI/wxWrapper -e DEVROOT=\$\(DEVROOT\) clean >> Projects/CPP/makefile
echo \	\$\(MAKE\) -s -C Test/GUI/wxWrapper -e DEVROOT=\$\(DEVROOT\) >> Projects/CPP/makefile
OSTYPE=osx
export OSTYPE
OSVERSION=`uname -r`
export OSVERSION
OSPLATFORM=`uname -p`
export OSPLATFORM
CRUISECONTROL=yes
export CRUISECONTROL
make -C Projects/CPP -f makefile clean
make -C Projects/CPP -f makefile
make -C Projects/CPP -f makefile install
make -C Projects/CPP -f makefile wxWrapper 

#!/bin/sh
echo Cruise Control build started at: `pwd`
echo all: BaseDevelopment > makefile
echo \# >> makefile

echo Updating full source tree to be save
cvs update -d

echo DEVROOT=`pwd` >> makefile

i=0
while [ $# -gt 0 ]
do
  case $1 in
  "--prefix"*) echo export prefix=`echo $1 | awk -F = '{ print $2; }'` >> makefile;;
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

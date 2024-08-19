#!/bin/sh

export VERSION=1.3.4
export SERVER=http://ci-master.behrens.de:8080
export XP=lbDMF-Release_1_0_4_stable_rc1_branch_XPVM_Release/ws/Projects/lbdmf/Output
export LINUX=lbDMF-Release_1_0_4_stable_rc1_branch_Linux_Release/ws/Projects/lbdmf/dist
export OSX=lbDMF-Release_1_0_4_stable_rc1_branch_OSX_Release/ws/Projects/lbdmf/Test/GUI/wxWrapper
export PPC=lbDMF-Release_1_0_4_stable_rc1_branch_PPC_Release/ws/Projects/lbdmf/Test/GUI/wxWrapper
export OSXArm=lbDMF-Release_1_0_4_stable_rc1_branch_OSXArm_Release/ws/Projects/lbdmf/Test/GUI/wxWrapper

wget $SERVER/job/$XP/lbDMF-BinbuildTools-$VERSION-vc.exe
wget $SERVER/job/$XP/lbDMF-BinSamples-$VERSION.exe
wget $SERVER/job/$XP/lbDMF-Docs-$VERSION.exe
wget $SERVER/job/$XP/lbDMF-Source-$VERSION.exe

wget $SERVER/job/$LINUX/SRPMS/lbdmf-$VERSION-1.src.rpm
wget $SERVER/job/$LINUX/RPMS/i586/lbdmf-$VERSION-1.i586.rpm
wget $SERVER/job/$LINUX/SOURCES/lbdmf-$VERSION.tgz

wget $SERVER/job/$OSX/lbDMF-$VERSION-i386-dist.dmg.zip

wget $SERVER/job/$PPC/lbDMF-$VERSION-powerpc-dist.dmg.zip
wget $SERVER/job/$OSXArm/lbDMF-$VERSION-arm-dist.dmg.zip

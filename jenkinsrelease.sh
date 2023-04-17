#!/bin/sh

echo Jenkins release started at: `pwd`

OSTYPE=linux
export OSTYPE
CRUISECONTROL=yes
export CRUISECONTROL
cd Projects/lbdmf
./make_src_dist.sh 1.3.2 jenkins

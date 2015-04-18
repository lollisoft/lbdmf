#!/bin/sh

echo Jenkins release started at: `pwd`

OSTYPE=linux
export OSTYPE
CRUISECONTROL=yes
export CRUISECONTROL
cd Projects/CPP
./make_src_dist.sh 1.1.0 jenkins

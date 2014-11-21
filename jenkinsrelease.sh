#!/bin/sh

echo Jenkins release started at: `pwd`

OSTYPE=linux
export OSTYPE
CRUISECONTROL=yes
export CRUISECONTROL
./make_src_dist.sh 1.0.4.3_final

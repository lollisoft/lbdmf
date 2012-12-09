#!/bin/sh

CRUISECONTROL=
export CRUISECONTROL
make -e prefix=`pwd`/.. install
LD_LIBRARY_PATH=$(pwd)/lib
export LD_LIBRARY_PATH
PLUGIN_DIR=$(pwd)/plugins
export PLUGIN_DIR
$(pwd)/bin/lbDMFUnitTests

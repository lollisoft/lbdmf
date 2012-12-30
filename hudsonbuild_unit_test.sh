#!/bin/sh

CRUISECONTROL=yes
export CRUISECONTROL

LD_LIBRARY_PATH=$(pwd)/lib
export LD_LIBRARY_PATH
PLUGIN_DIR=$(pwd)/plugins
export PLUGIN_DIR

make install

# Remove all wxWidgets based plugins that are not installed in a console based application.
# wxWidgets based stuff does not make sense here as I did not use wsWidgets outside of GUI.

rm $(pwd)/plugins/lbCryptoStream.*
rm $(pwd)/plugins/lbDatabaseForm.*
rm $(pwd)/plugins/lbDatabaseReport.*
rm $(pwd)/plugins/lbDMFProject.*
rm $(pwd)/plugins/lbLoginWizard.*
rm $(pwd)/plugins/lbwxSFDesigner.*
rm $(pwd)/plugins/UserFeedback.*

# Prepare local application directory

rm -rf $(HOME)/.lbDMF
mkdir $(HOME)/.lbDMF
cp Database/* $(HOME)/.lbDMF


$(pwd)/bin/lbDMFUnitTests

#!/bin/bash

cd lbHook
#./make.sh
makefile.sh
make

cd ..

cd lbModule
makefile.sh
make
cd ..

cd lbclasses
makefile.sh
make
cd ..

cd lbXMLConfig/lbDOMConfig
makefile.sh
make
cd ../..

cd ../AppDevelopment/Console/XML
makefile.sh
make
cd ../../../BaseDevelopment

#!/bin/bash

cd lbHook
./make.sh

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


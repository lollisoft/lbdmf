#!/bin/sh
export DEVROOT=dist/Develop/Projects/CPP

if [ -e "dist" ]; then
	rm -R dist;
fi

if [ ! -e "dist" ]; then
	mkdir dist;
fi

if [ ! -e "dist/Develop" ]; then
	mkdir dist/Develop;
fi

if [ ! -e "dist/Develop/Projects" ]; then
	mkdir dist/Develop/Projects;
fi

if [ ! -e "dist/Develop/Projects/CPP" ]; then
	mkdir dist/Develop/Projects/CPP;
fi

if [ ! -e "dist/Develop/Projects/CPP/BaseDevelopment" ]; then
	mkdir dist/Develop/Projects/CPP/BaseDevelopment;
fi

if [ ! -e "dist/Develop/Projects/CPP/BaseDevelopment/lbXMLConfig" ]; then
	mkdir dist/Develop/Projects/CPP/BaseDevelopment/lbXMLConfig;
fi

if [ ! -e "dist/Develop/Projects/CPP/AppDevelopmentDemo" ]; then
	mkdir dist/Develop/Projects/CPP/AppDevelopmentDemo;
fi


./make_dist_base.sh AppDevelopmentDemo/App
./make_dist_base.sh BaseDevelopment/lbHook 
./make_dist_base.sh BaseDevelopment/lbclasses 
./make_dist_base.sh BaseDevelopment/lbDB 
./make_dist_base.sh BaseDevelopment/lbPluginManager
./make_dist_base.sh BaseDevelopment/lbMetaApplication 
./make_dist_base.sh BaseDevelopment/lbModule 
./make_dist_base.sh BaseDevelopment/lbXMLConfig/lbDOMConfig 
./make_dist_base.sh Plugins/DatabaseForm
./make_dist_base.sh vendor/mkmk 
./make_dist_base.sh vendor/dosdir 
./make_dist_base.sh include 
./make_dist_base.sh interfaces 
./make_dist_base.sh make
./make_dist_base.sh Test/GUI/wxWrapper
./make_dist_base.sh Test/Console/XML
./make_dist_base.sh Compilers

cp README $DEVROOT
cp COPYING $DEVROOT
cp BaseDevelopment/Makefile $DEVROOT/BaseDevelopment
rm *.idb


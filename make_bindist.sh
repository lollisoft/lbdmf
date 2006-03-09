#!/bin/sh

# Create Mac OS X binary package of wxWrapper.

export DEVROOT=dist/Develop/Projects/CPP

if [ -e "bindist" ]; then
	rm -R bindist;
fi

mkdir bindist
cd bindist


mkdir Install_resources
mkdir Package_contents
mkdir Package_contents/usr
mkdir Package_contents/usr/local
mkdir Package_contents/usr/local/lib
mkdir ./lbDMF

cp -R ~/lib ./lbDMF
cp -R ~/plugins ./lbDMF

rm ./lbDMF/lib/lbDMFProjectApp.*
rm ./lbDMF/plugins/lbCSharpAppWriter.*
rm ./lbDMF/plugins/lbDMFAppWriter.*
rm ./lbDMF/plugins/lbDMFProject.*

cp /usr/local/lib/libwx_mac_Lollisoft*-2.6.0.2.0.dylib ./Package_contents/usr/local/lib
cd ./Package_contents/usr/local/lib
ln -s libwx_mac_Lollisoft-2.6.0.2.0.dylib libwx_mac_Lollisoft-2.6.0.dylib
ln -s libwx_mac_Lollisoft-2.6.0.dylib libwx_mac_Lollisoft-2.6.dylib
ln -s libwx_mac_Lollisoft_propgrid-2.6.0.2.0.dylib libwx_mac_Lollisoft_propgrid-2.6.0.dylib
ln -s libwx_mac_Lollisoft_propgrid-2.6.0.dylib libwx_mac_Lollisoft_propgrid-2.6.dylib
cd ../../../..

cp -R ~/develop/Projects/CPP/Test/GUI/wxWrapper/wxWrapper.app ./lbDMF

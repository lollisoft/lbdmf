#!/bin/sh
# Copies together files for the Mac OS X application bundle and created a disk image

cp ../../../Database/*.sql wxWrapper.app/Contents/Resources
cp splash.png wxWrapper.app/Contents/Resources
mkdir wxWrapper.app/Contents/Resources/toolbarimages
cp -R $HOME/lib wxWrapper.app/Contents
cp -R $HOME/plugins wxWrapper.app/Contents/Resources
# How to access them?
cp toolbarimages/*.xpm wxWrapper.app/Contents/Resources/toolbarimages
cp toolbarimages/*.png wxWrapper.app/Contents/Resources/toolbarimages
cp -R `wx-config --prefix`/lib/lib`wx-config --basename`-`wx-config --release`.0.6.0.dylib wxWrapper.app/Contents/lib
cp -R `wx-config --prefix`/lib/lib`wx-config --basename`-`wx-config --release`.0.dylib wxWrapper.app/Contents/lib
cp -R `wx-config --prefix`/lib/lib`wx-config --basename`-`wx-config --release`.dylib wxWrapper.app/Contents/lib

# Creating a new diskimage

hdiutil create -ov -size 80m -volname lbDMF-1.0.1 lbDMF-1.0.1-`uname -p`.dmg -fs HFS+

sleep 5

hdiutil attach lbDMF-1.0.1-`uname -p`.dmg

# Copy stuff

#mkdir /Volumes/lbDMF-1.0.1/`uname -p`

#cp -R wxWrapper.app /Volumes/lbDMF-1.0.1/`uname -p`
cp -R wxWrapper.app /Volumes/lbDMF-1.0.1
mkdir /Volumes/lbDMF-1.0.1/toolbarimages
cp toolbarimages/*.xpm /Volumes/lbDMF-1.0.1/toolbarimages
cp toolbarimages/*.png /Volumes/lbDMF-1.0.1/toolbarimages
cp -R ../../../AppDevelopmentDemo/DynamicApp/UMLSamples /Volumes/lbDMF-1.0.1
cp ../../../COPYING /Volumes/lbDMF-1.0.1
cp ../../../license-bindist.txt /Volumes/lbDMF-1.0.1
mkdir /Volumes/lbDMF-1.0.1/XSLT
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/include            /Volumes/lbDMF-1.0.1/XSLT/include
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/DMFToXMI           /Volumes/lbDMF-1.0.1/XSLT/DMFToXMI
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/XMIToDMF           /Volumes/lbDMF-1.0.1/XSLT/XMIToDMF
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/lbDMFDataViewModel /Volumes/lbDMF-1.0.1/XSLT/lbDMFDataViewModel
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/lbDMFFixedFormular /Volumes/lbDMF-1.0.1/XSLT/lbDMFFixedFormular
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/TurboVision        /Volumes/lbDMF-1.0.1/XSLT/TurboVision
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/wxActiveRecords    /Volumes/lbDMF-1.0.1/XSLT/wxActiveRecords
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/wxLua              /Volumes/lbDMF-1.0.1/XSLT/wxLua
cp ../../../AppDevelopmentDemo/DynamicApp/Doc/ApplicationprototypingDokumentation.pdf /Volumes/lbDMF-1.0.1/

cat <<EOF >> /Volumes/lbDMF-1.0.1/Readme.txt
Dear Mac user!

If you start designing your database applications on one platform (either Intel or PPC) and switch over to a later time, please copy the *.db3 *.mad and *.daf files in the application bundle to the other bundle at the same place (in Resources).

This is due to the fact I not yet support an universal application and the design data storage is in the Resources directory in the application bundle to ease moving them around.

Otherwise you could use the PostgreSQL database on a different server.

Thanks

Lothar Behrens
EOF

rm -rf `find /Volumes/lbDMF-1.0.1 -name CVS -print`

hdiutil detach /Volumes/lbDMF-1.0.1

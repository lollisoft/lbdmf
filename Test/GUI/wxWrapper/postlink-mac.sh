#!/bin/sh
# Copies together files for the Mac OS X application bundle and created a disk image

export VERSION=1.0.4.3_final

cp ../../../Database/*.sql wxWrapper.app/Contents/Resources
cp splash.png wxWrapper.app/Contents/Resources

mkdir wxWrapper.app/Contents/Resources/XSLT
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/include            wxWrapper.app/Contents/Resources/XSLT/include
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/DMFToXMI           wxWrapper.app/Contents/Resources/XSLT/DMFToXMI
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/XMIToDMF           wxWrapper.app/Contents/Resources/XSLT/XMIToDMF
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/lbDMFDataViewModel wxWrapper.app/Contents/Resources/XSLT/lbDMFDataViewModel
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/lbDMFFixedFormular wxWrapper.app/Contents/Resources/XSLT/lbDMFFixedFormular
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/TurboVision        wxWrapper.app/Contents/Resources/XSLT/TurboVision
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/wxActiveRecords    wxWrapper.app/Contents/Resources/XSLT/wxActiveRecords
cp -R ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/wxLua              wxWrapper.app/Contents/Resources/XSLT/wxLua

cp ../../../AppDevelopmentDemo/DynamicApp/XSLT_Templates/include/XMISettingsTemplate.xsl wxWrapper.app/Contents/Resources/XSLT/XMIToDMF/XMISettings.xsl
cp -R ../../../AppDevelopmentDemo/DynamicApp/UMLSamples wxWrapper.app/Contents/Resources

# Copying templates to an accessable place

cp -R wxWrapper.app/Contents/Resources/XSLT XSLT
cp -R wxWrapper.app/Contents/Resources/UMLSamples UMLSamples

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

hdiutil create -ov -size 200m -volname lbDMF-$VERSION lbDMF-$VERSION-`uname -p`.dmg -fs HFS+

sleep 5

hdiutil attach lbDMF-$VERSION-`uname -p`.dmg

# Copy stuff

#mkdir /Volumes/lbDMF-$VERSION/`uname -p`

#cp -R wxWrapper.app /Volumes/lbDMF-$VERSION/`uname -p`
cp -R wxWrapper.app /Volumes/lbDMF-$VERSION
mkdir /Volumes/lbDMF-$VERSION/toolbarimages
cp toolbarimages/*.xpm /Volumes/lbDMF-$VERSION/toolbarimages
cp toolbarimages/*.png /Volumes/lbDMF-$VERSION/toolbarimages

cp ../../../COPYING /Volumes/lbDMF-$VERSION
cp ../../../license-bindist.txt /Volumes/lbDMF-$VERSION

cp ../../../AppDevelopmentDemo/DynamicApp/Doc/ApplicationprototypingDokumentation.pdf /Volumes/lbDMF-$VERSION/

cat <<EOF >> /Volumes/lbDMF-$VERSION/Readme.txt
Dear Mac user!

If you start designing your database applications on one platform (either Intel or PPC) and switch over to a later time, then set the switch to prefer database. This let you update the locally cached files.
If you use a Sqlite database with more than the lbDMF Manager application in it, please copy the db3 file from the package (/Contents/Resources/lbDMF.db3) and put it into the bundle of the other mac.

This is due to the fact I not yet support an universal application and the design data storage is in the Resources directory in the application bundle to ease moving them around.

Otherwise you could use the PostgreSQL database on a different server.

Thanks

Lothar Behrens
EOF

rm -rf `find /Volumes/lbDMF-$VERSION -name CVS -print`

hdiutil detach /Volumes/lbDMF-$VERSION
rm lbDMF-$VERSION lbDMF-$VERSION-`uname -p`.dmg.zip
zip lbDMF.dmg.zip lbDMF-$VERSION lbDMF-$VERSION-`uname -p`.dmg
mv lbDMF.dmg.zip lbDMF-$VERSION-`uname -p`.dmg.zip

#!/bin/sh
# Copies together files for the Mac OS X application bundle and created a disk image

export prefix=$1

export VERSION=1.3.4

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

mkdir wxWrapper.app/Contents/Resources/toolbarimages
# UGLY! Using environment that also is properly defined while jenkins build is better
cp -R $prefix/lib wxWrapper.app/Contents
cp -R $prefix/plugins wxWrapper.app/Contents
mv wxWrapper.app/Contents/plugins wxWrapper.app/Contents/PlugIns

# How to access them?
cp toolbarimages/*.xpm wxWrapper.app/Contents/Resources/toolbarimages
cp toolbarimages/*.png wxWrapper.app/Contents/Resources/toolbarimages
cp -R `wx-config --prefix`/lib/lib`wx-config --basename`-`wx-config --release`.*.dylib wxWrapper.app/Contents/lib
cp -R `wx-config --prefix`/lib/lib`wx-config --basename`-`wx-config --release`.dylib wxWrapper.app/Contents/lib

cp Info.plist wxWrapper.app/Contents

./notarize_application.sh

# ****************
# Create dmg image
# ****************

hdiutil create -ov -size 200m -volname lbDMF-$VERSION lbDMF-$VERSION-`uname -p`.dmg -fs HFS+ & sleep 60
hdiutil attach lbDMF-$VERSION-`uname -p`.dmg & sleep 60

export DMGPATH=/Volumes/lbDMF-$VERSION

ditto wxWrapper.app $DMGPATH/wxWrapper.app
# Copy stuff
mkdir $DMGPATH/toolbarimages
cp toolbarimages/*.xpm $DMGPATH/toolbarimages
cp toolbarimages/*.png $DMGPATH/toolbarimages
cp ../../../COPYING $DMGPATH
cp ../../../license-bindist.txt $DMGPATH
cp ../../../AppDevelopmentDemo/DynamicApp/Doc/ApplicationprototypingDokumentation.pdf $DMGPATH
# Copying templates to an accessable place
cp -R wxWrapper.app/Contents/Resources/XSLT $DMGPATH
cp -R wxWrapper.app/Contents/Resources/UMLSamples $DMGPATH
mkdir $DMGPATH/.lbDMF
cp -R wxWrapper.app/Contents/Resources/*.sql $DMGPATH/.lbDMF

cat <<EOF >> $DMGPATH/Readme.txt
Dear Mac user!

If you start designing your database applications on one platform (either Intel or PPC) and switch over to a later time, then set the switch to prefer database. This let you update the locally cached files.
If you use a Sqlite database with more than the lbDMF Manager application in it, please copy the db3 file from the package (/Contents/Resources/lbDMF.db3) and put it into the bundle of the other mac.

This is due to the fact I not yet support an universal application and the design data storage is in the Resources directory in the application bundle to ease moving them around.

Otherwise you could use the PostgreSQL database on a different server.

Thanks

Lothar Behrens
EOF

rm -rf `find $DMGPATH -name CVS -print`

echo sleep 60
sleep 60

hdiutil detach /Volumes/lbDMF-$VERSION

echo sleep 60
sleep 60
echo sleep over

./notarize_dmg.sh

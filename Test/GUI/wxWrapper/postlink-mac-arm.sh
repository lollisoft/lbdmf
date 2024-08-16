#!/bin/sh
# Copies together files for the Mac OS X application bundle and created a disk image

#https://federicoterzi.com/blog/automatic-code-signing-and-notarization-for-macos-apps-using-github-actions/
# wxWrapper *********** Team ID 3MPMMGXYRY
# xcrun notarytool store-credentials "wxWrapper" --apple-id "********" --team-id "3MPMMGXYRY" --password "**********"
#

# ditto -c -k --keepParent "wxWrapper.app" "notarization.zip"
# xcrun notarytool submit "notarization.zip" --keychain-profile wxWrapper --wait
# xcrun stapler staple wxWrapper.app
#
# xcrun notarytool log f8ec56ec-2884-4582-ac9a-0931f896b2ea --keychain-profile "wxWrapper"



export DEVELOPERIDAPP=Developer\ ID\ Application:\ Lothar\ Behrens\ \(3MPMMGXYRY\)

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
#cp -R $prefix/plugins wxWrapper.app/Contents/Resources
cp -R $prefix/plugins wxWrapper.app/Contents
mv wxWrapper.app/Contents/plugins wxWrapper.app/Contents/PlugIns

# How to access them?
cp toolbarimages/*.xpm wxWrapper.app/Contents/Resources/toolbarimages
cp toolbarimages/*.png wxWrapper.app/Contents/Resources/toolbarimages
#cp -R `wx-config --prefix`/lib/lib`wx-config --basename`-`wx-config --release`.0.6.0.dylib wxWrapper.app/Contents/lib
#cp -R `wx-config --prefix`/lib/lib`wx-config --basename`-`wx-config --release`.0.dylib wxWrapper.app/Contents/lib
cp -R `wx-config --prefix`/lib/lib`wx-config --basename`-`wx-config --release`.*.dylib wxWrapper.app/Contents/lib
cp -R `wx-config --prefix`/lib/lib`wx-config --basename`-`wx-config --release`.dylib wxWrapper.app/Contents/lib

cp Info.plist wxWrapper.app/Contents


#export RUNTIMEOPTIONS=
#export ENTITLEMENTS=
export RUNTIMEOPTIONS=--options=runtime
export ENTITLEMENTS=--entitlements\ Entitlements.plist

rm -rf `find wxWrapper.app -name CVS -print`

mkdir dmgdist
cp -R wxWrapper.app dmgdist
cp Entitlements.plist dmgdist
# Copy stuff
mkdir dmgdist/toolbarimages
cp toolbarimages/*.xpm dmgdist/toolbarimages
cp toolbarimages/*.png dmgdist/toolbarimages
cp ../../../COPYING dmgdist
cp ../../../license-bindist.txt dmgdist
cp ../../../AppDevelopmentDemo/DynamicApp/Doc/ApplicationprototypingDokumentation.pdf dmgdist
# Copying templates to an accessable place
cp -R wxWrapper.app/Contents/Resources/XSLT dmgdist
cp -R wxWrapper.app/Contents/Resources/UMLSamples dmgdist
mkdir dmgdist/.lbDMF
cp -R wxWrapper.app/Contents/Resources/*.sql dmgdist/.lbDMF

cat <<EOF >> dmgdist/Readme.txt
Dear Mac user!

If you start designing your database applications on one platform (either Intel or PPC) and switch over to a later time, then set the switch to prefer database. This let you update the locally cached files.
If you use a Sqlite database with more than the lbDMF Manager application in it, please copy the db3 file from the package (/Contents/Resources/lbDMF.db3) and put it into the bundle of the other mac.

This is due to the fact I not yet support an universal application and the design data storage is in the Resources directory in the application bundle to ease moving them around.

Otherwise you could use the PostgreSQL database on a different server.

Thanks

Lothar Behrens
EOF

rm -rf `find dmgdist -name CVS -print`

cd dmgdist

codesign -f -v -s "$DEVELOPERIDAPP" $ENTITLEMENTS $RUNTIMEOPTIONS wxWrapper.app/Contents/Frameworks/lbHook.framework/Versions/A/lbHook
codesign -f -v -s "$DEVELOPERIDAPP" $ENTITLEMENTS $RUNTIMEOPTIONS wxWrapper.app/Contents/Frameworks/wxJson.framework/Versions/A/wxJson
codesign -f -v -s "$DEVELOPERIDAPP" $ENTITLEMENTS $RUNTIMEOPTIONS wxWrapper.app/Contents/Frameworks/wxWrapperDLL.framework/Versions/A/wxWrapperDLL
codesign -f -v -s "$DEVELOPERIDAPP" $ENTITLEMENTS $RUNTIMEOPTIONS wxWrapper.app/Contents/lib/*.so
codesign -f -v -s "$DEVELOPERIDAPP" $ENTITLEMENTS $RUNTIMEOPTIONS wxWrapper.app/Contents/lib/*.dylib
codesign -f -v -s "$DEVELOPERIDAPP" $ENTITLEMENTS $RUNTIMEOPTIONS wxWrapper.app/Contents/PlugIns/*.so
xattr -cr wxWrapper.app
codesign -f -v -s "$DEVELOPERIDAPP" $ENTITLEMENTS $RUNTIMEOPTIONS wxWrapper.app/Contents/MacOS/wxWrapper
#codesign -dvv wxWrapper.app
codesign -f -v -s "$DEVELOPERIDAPP" $ENTITLEMENTS $RUNTIMEOPTIONS wxWrapper.app
#spctl -a -t exec -vvvv wxWrapper.app
#codesign -dvv wxWrapper.app
#codesign -vv --deep-verify "$ENTITLEMENTS" $RUNTIMEOPTIONS wxWrapper.app 

# Starting the notarization step
ditto -c -k --keepParent "wxWrapper.app" "notarization.zip"

xcrun notarytool submit "notarization.zip" --keychain-profile wxWrapper --wait

xcrun stapler staple wxWrapper.app & sleep 5

cd ..

rm dmgdist/Entitlements.plist
rm dmgdist/notarization.zip

hdiutil create lbDMF-$VERSION-`uname -p`.dmg -ov -volname lbDMF-$VERSION -fs HFS+ -srcfolder "`pwd`/dmgdist/" & sleep 5

codesign -f -v -s "$DEVELOPERIDAPP" -i de.lollisoft.wxWrapper.app lbDMF-$VERSION-`uname -p`.dmg

hdiutil convert lbDMF-$VERSION-`uname -p`.dmg -format UDZO -o lbDMF-$VERSION-`uname -p`-dist.dmg

xcrun notarytool submit lbDMF-$VERSION-`uname -p`-dist.dmg --keychain-profile wxWrapper --wait

xcrun stapler staple lbDMF-$VERSION lbDMF-$VERSION-`uname -p`-dist.dmg

rm lbDMF-$VERSION lbDMF-$VERSION-`uname -p`.dmg.zip
zip lbDMF.dmg.zip lbDMF-$VERSION lbDMF-$VERSION-`uname -p`.dmg
mv lbDMF.dmg.zip lbDMF-$VERSION-`uname -p`.dmg.zip

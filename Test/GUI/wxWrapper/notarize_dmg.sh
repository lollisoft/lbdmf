#!/bin/sh

export ARCH_CODESIGNING=`uname -p`

if [ $ARCH_CODESIGNING = ppc ]; then
    echo Notarizing dmg not supported on $ARCH_CODESIGNING
    exit
fi
if [ $ARCH_CODESIGNING = i386 ]; then
    echo Notarizing dmg not supported on $ARCH_CODESIGNING
    exit
fi

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

codesign -f -v -s "$DEVELOPERIDAPP" -i de.lollisoft.wxWrapper.app lbDMF-$VERSION-`uname -p`.dmg

rm lbDMF-$VERSION-`uname -p`-dist.dmg

hdiutil convert lbDMF-$VERSION-`uname -p`.dmg -format UDZO -o lbDMF-$VERSION-`uname -p`-dist.dmg

xcrun notarytool submit lbDMF-$VERSION-`uname -p`-dist.dmg --keychain-profile wxWrapper --wait

xcrun stapler staple lbDMF-$VERSION lbDMF-$VERSION-`uname -p`-dist.dmg

rm lbDMF-$VERSION-`uname -p`.dmg.zip
zip lbDMF.dmg.zip lbDMF-$VERSION-`uname -p`-dist.dmg
mv lbDMF.dmg.zip lbDMF-$VERSION-`uname -p`-dist.dmg.zip


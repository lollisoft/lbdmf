#!/bin/sh

export ARCH_CODESIGNING=`uname -p`

if [ $ARCH_CODESIGNING = ppc ]; then
    echo Notarizing application not supported on $ARCH_CODESIGNING
    exit
fi
if [ $ARCH_CODESIGNING = i386 ]; then
    echo Notarizing application not supported on $ARCH_CODESIGNING
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

#export RUNTIMEOPTIONS=
#export ENTITLEMENTS=
export RUNTIMEOPTIONS=--options=runtime
export ENTITLEMENTS=--entitlements\ Entitlements.plist

rm -rf `find wxWrapper.app -name CVS -print`

# **************************
# Codesign built application
# **************************

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

# **************************
# Notarize built application
# **************************

# Starting the notarization step
ditto -c -k --keepParent "wxWrapper.app" "notarization.zip"

xcrun notarytool submit "notarization.zip" --keychain-profile wxWrapper --wait

xcrun stapler staple wxWrapper.app & sleep 5

rm notarization.zip

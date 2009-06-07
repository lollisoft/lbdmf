#!/bin/sh

cp ../../../Database/*.sql wxWrapper.app/Contents/Resources
cp splash.png wxWrapper.app/Contents/Resources
mkdir wxWrapper.app/Contents/Resources/toolbarimages
cp -R $HOME/lib wxWrapper.app/Contents
cp -R $HOME/plugins wxWrapper.app/Contents/Resources
# How to access them?
#cp toolbarimages/*.xpm wxWrapper.app/Contents/Resources/toolbarimages
#cp toolbarimages/*.png wxWrapper.app/Contents/Resources/toolbarimages
cp -R `wx-config --prefix`/lib/lib`wx-config --basename`* wxWrapper.app/Contents/lib
#!/bin/sh

export MAJOR=0
export MINOR=0
export MICRO=1


export PROGRAM=lbModule


cp /libdev/lib/$PROGRAM.so.$MAJOR.$MINOR.$MICRO /usr/lib
ln -sf /usr/lib/$PROGRAM.so.$MAJOR.$MINOR.$MICRO /usr/lib/$PROGRAM.so.$MAJOR
ln -sf /usr/lib/$PROGRAM.so.$MAJOR /usr/lib/$PROGRAM.so                          
 
export PROGRAM=lbclasses
cp /libdev/lib/$PROGRAM.so.$MAJOR.$MINOR.$MICRO /usr/lib
ln -sf /usr/lib/$PROGRAM.so.$MAJOR.$MINOR.$MICRO /usr/lib/$PROGRAM.so.$MAJOR
ln -sf /usr/lib/$PROGRAM.so.$MAJOR /usr/lib/$PROGRAM.so                          
 
export PROGRAM=lbclasses
cp /libdev/lib/$PROGRAM.so.$MAJOR.$MINOR.$MICRO /usr/lib
ln -sf /usr/lib/$PROGRAM.so.$MAJOR.$MINOR.$MICRO /usr/lib/$PROGRAM.so.$MAJOR
ln -sf /usr/lib/$PROGRAM.so.$MAJOR /usr/lib/lbClasses.so                          
 
export PROGRAM=lbhook
cp /libdev/lib/$PROGRAM.so.$MAJOR.$MINOR.$MICRO /usr/lib
ln -sf /usr/lib/$PROGRAM.so.$MAJOR.$MINOR.$MICRO /usr/lib/$PROGRAM.so.$MAJOR
ln -sf /usr/lib/$PROGRAM.so.$MAJOR /usr/lib/$PROGRAM.so                          
 
export PROGRAM=lbMetaApplication
cp /libdev/lib/$PROGRAM.so.$MAJOR.$MINOR.$MICRO /usr/lib
ln -sf /usr/lib/$PROGRAM.so.$MAJOR.$MINOR.$MICRO /usr/lib/$PROGRAM.so.$MAJOR
ln -sf /usr/lib/$PROGRAM.so.$MAJOR /usr/lib/$PROGRAM.so                          
 
export PROGRAM=lbDOMConfig
cp /libdev/lib/$PROGRAM.so.$MAJOR.$MINOR.$MICRO /usr/lib
ln -sf /usr/lib/$PROGRAM.so.$MAJOR.$MINOR.$MICRO /usr/lib/$PROGRAM.so.$MAJOR
ln -sf /usr/lib/$PROGRAM.so.$MAJOR /usr/lib/$PROGRAM.so                          
 

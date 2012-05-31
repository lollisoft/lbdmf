#!/bin/sh
#
# Script to generate a changelog file based on the old changelog created prior.
# The relevant directories are included in the parameters. There may be a changelog entry
# that was the last entry from the prior changelog. This is due to the missing seconds not reported in the changelog.
#
# (c) 2009 Lothar Behrens
# License; LGPL as the project it self.

# Get files only from the base directory. These files where not reported until now.
MISCFILES=`cat CVS/Entries | grep -Ev "^D" | awk -- 'BEGIN { FS="\/"; }{ print $2; }'`

LASTDATE=`awk -f printRecentChangedate.awk < ChangeLog-basic.txt`
export LASTDATE
cvs log -d \>"$LASTDATE" -rRelease_1_0_4_stable_rc1_branch $MISCFILES AppDevelopmentDemo BaseDevelopment Compilers Concepts Database Doc include interfaces make Plugins RegressionTests Samples Test UnitTests vendor/mkmk > ChangeLog

./vendor/cvs2cl/cvs2cl.pl --fsf --header /dev/null -f ChangeLog-basic.txt --stdin < ChangeLog

#!/bin/sh
#===============================================================================
#
#         FILE: cvs_root_replacer.sh
#        USAGE: ./cvs_root_replacer.sh
#  DESCRIPTION:
#               This program is used to replace the cvs ip address recursively.
#      OPTIONS: n/a
# REQUIREMENTS: cvs
#         BUGS: n/a
#        NOTES: ---
#       AUTHOR: (sridhar.M), <sridhar_dct3@yahoo.co.in>
#      COMPANY: 
#      VERSION: 1.0
#      CREATED: 02/25/08 16:24:22 IST
#     REVISION: ---
#===============================================================================
#set -x;
START_PATH='.';

# Checking whether the IP Address was passed as argument .
if [[ -z $1 ]] ; then
    echo "Usage : $0 NEW_CVSSERVER_IP";
    exit 1;
fi;

# This will replace the ip address to '$1' domain name.
echo "=============================================================================================================";
printf "=                                              \033[01;33mPROCESSING\033[0;0m                                                   =\n";
echo "=============================================================================================================";
# This will find all the files which has name 'Root' and check Root is under CVS Directory.
find $START_PATH -iname Root | grep "CVS\/Root" > cvslist.txt;
#This will replace all the 'space' into '|' - because the dirname can contain space as part of the filename.
LIST_OF_ROOT_FILES=`cat cvslist.txt | tr ' ' '\|'`;

# $LIST_OF_ROOT_FILES will contain all the filepath needs to be replaced.
for i in $LIST_OF_ROOT_FILES; 
do 
    # Here again replacing the '|' character of filename into space.
    i=`echo $i |sed 's/|/ /g'`;
    # Creating a copy of Root file .
    /bin/cp "$i" "$i.safe"; 
    # Here extracting all the string and replcing ip address with nameserver address.
    PRINT_MSG=`sed "s/^\(.*@\).*\(:.*\)$/\1$1\2/w $i" "$i".safe`; 
    printf "%-80s => :$PRINT_MSG: \n" "$i";
done;

echo "=============================================================================================================";
printf "=                                               \033[01;33mSTATUS\033[0;0m                                                      =\n";
echo "=============================================================================================================";

# This following for loop will just shows the status of the file . Whether it is successfully replaced.
for i in $LIST_OF_ROOT_FILES; 
do 
    i=`echo $i |sed 's/|/ /g'`;
    # Displaying Root file content and checking whether it was replaced successfully.
    /bin/cat "$i" | grep "$1" > /dev/null && printf "%-100s == [\033[01;32mOK\033[0;0m]\n" "$i"; 
    if [[ $? != 0 ]]; then
	echo Recreate file $i
	echo :passwd:lothar@jedi:/home/cvsroot > "$i"
        printf "%-100s == [\033[01;38mFAILED\033[0;0m]\n" "$i";
    else
        # Create a template: Activate this.
	#echo :pserver:lothar@jedi:/home/cvsroot > "$i"
        # Removing the safe file .
        rm -fr "$i".safe;
    fi;
done;
echo "=============================================================================================================";
# Removing the Root list file.
/bin/rm -fr cvslist.txt;

#CONFLICT
# This will not work when '|' characted is a part of the filename.
# This will empty 'cvslist.txt' if it is already exist in this directory.

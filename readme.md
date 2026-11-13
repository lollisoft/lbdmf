# DMF - Distributed Multiplatform Framework

Copyright (C)  Lothar Behrens 2000-2026

This readme replaces the original readme file and is intended for Github. It should be
as short as possible.

# Installation in a nutshell

# Installing on Windows
On windows, you should use the source code installer. Download that from sourceforge and follow
the instructions. If you never have installed it, and you need a painless compiling experience,
then tick the checkmark for either:

Get MinGW, wxWidgets (and ACE when flagged) and build it with debug or
Get MinGW64, wxWidgets (and ACE when flagged) and build it with debug

# Installing on Linux
You either can clone the code from Github, or install any prepared rpm. Actually openSuSE Tumbleweed
is tested by a local Podman instance on my Windows 10 machine by the batch files within Podman.
You could therefore always help in testing and reporting bugs this way with a dropable Podman image. 
Podman is required with a standard installation and it assumes, you have a drive D: to place the images to.
The batch files take care to move the omage to a specific location on drive D:.

Test-lbdmf-Tumbleweed.bat will create a minimal Tumbleweed image and install the rpm for testing. If installed,
just test by starting wxWrapper.

To cleanup, use DropSetup.bat and it will remove the specific folder on drive D:. Also a minimal setup is available
for a naked machine. That is InitialSetup.bat and DropSetup.bat drops thet as well.

# Installing on Mac OS X
The Mac OS X build works the same than that in Linux. Basically only difference would be the shell variables within
the environment.

Within the /etc/.profile I have made my settings as follows:

# System-wide .profile for sh(1)

if [ -x /usr/libexec/path_helper ]; then
        eval `/usr/libexec/path_helper -s`
fi

if [ "${BASH-no}" != "no" ]; then
        [ -r /etc/bashrc ] && . /etc/bashrc
fi

CVS_RSH=ssh
MODULELIB=lbModule.so
LBXMLFUNCTOR=getlbDOMConfigInstance
LBMODULEFUNCTOR=getlb_ModuleInstance
DEVROOT=~/develop
LD_LIBRARY_PATH=~/lib:
PLUGIN_DIR=~/plugins
OSTYPE=osx
PATH="/usr/local/bin:/sw/bin:/sw/sbin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/X11R6/bin:~/bin:/usr/local/bin:/usr/brlcad/bin:/opt/local/bin"

##On older OSX
#DEVELOPER_TOOLS_PATH=/Developer/Tools
#export DEVELOPER_TOOLS_PATH
# On newer OSX
DEVELOPER_TOOLS_PATH=/Library/Developer/CommandLineTools/usr/bin
export DEVELOPER_TOOLS_PATH

OSVERSION=`uname -r`
export OSVERSION
OSPLATFORM=`uname -p`
export OSPLATFORM

export CVS_RSH
export MODULELIB
export LBXMLFUNCTOR
export LBMODULEFUNCTOR
export DEVROOT
export LD_LIBRARY_PATH
export OSTYPE
export PATH
export PLUGIN_DIR
REPO_NAME=lbdmf
export REPO_NAME

So you may make a similar setup but not systemwide.
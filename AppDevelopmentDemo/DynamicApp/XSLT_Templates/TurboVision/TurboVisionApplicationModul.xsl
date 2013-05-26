<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002-2009  Lothar Behrens (lothar.behrens@lollisoft.de)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
			Ginsterweg 4

			65760 Eschborn (germany)
-->
<!-- Helper to create multible files. -->
<xsl:import href="../include/exsl.xsl"/>

<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>

<xsl:variable name="OrginalApplicationName" select="//lbDMF/applications/application[@ID=$ApplicationID]/@name"/>
<xsl:variable name="ApplicationName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$OrginalApplicationName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>

<xsl:template name="createCPPPreample">
</xsl:template>

<xsl:template name="createMakeFileModule_FormularModul">
<exsl:document href="{$basedir}/{$pluginsdir}/{$ApplicationName}/makefile.module" method="text">
# Define your module based settings

#    DMF Distributed Multiplatform Framework (the initial goal of this library)
#    This file is part of lbDMF.
#    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)
#
#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation; either
#    version 2.1 of the License, or (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this library; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#
#    The author of this work will be reached by e-Mail or paper mail.
#    e-Mail: lothar.behrens@lollisoft.de
#    p-Mail: Lothar Behrens
#			 Ginsterweg 4
#
#			 65760 Eschborn (germany)

ifeq ($(OSTYPE), Windows_NT)
MOD_INCL=$(STD_INCL)
MOD_INCL_CPP=$(STD_INCL_CPP)
OBJDEP=
SLASH=/
WATCOMLIBS=$(DEVROOT_MAKE)$(SLASH)Tools$(SLASH)watcom$(SLASH)lib386$(SLASH)nt
wxBase=$(DEVROOT_MAKE)$(SLASH)wxwin$(SLASH)wx$(SLASH)lib
LIBS = $(BASE_LIBS) $(DEVROOT_MAKE)$(SLASH)projects$(SLASH)dll$(SLASH)libs$(SLASH)lbhook.lib, \
	$(DEVROOT_MAKE)$(SLASH)projects$(SLASH)dll$(SLASH)libs$(SLASH)wxWrapperDLL.lib, \
	$(wxBase)$(SLASH)wat_dll$(SLASH)wxmsw$(WX_VERSION)$(WX_DEBUG).lib
	
LIBRS =	libr $(WATCOMLIBS)$(SLASH)kernel32.lib \
	libr $(WATCOMLIBS)$(SLASH)user32.lib \
	libr $(WATCOMLIBS)$(SLASH)gdi32.lib \
	libr $(WATCOMLIBS)$(SLASH)comdlg32.lib \
	libr $(WATCOMLIBS)$(SLASH)comctl32.lib \
	libr $(WATCOMLIBS)$(SLASH)advapi32.lib \
	libr $(WATCOMLIBS)$(SLASH)shell32.lib \
	libr $(WATCOMLIBS)$(SLASH)ole32.lib \
	libr $(WATCOMLIBS)$(SLASH)oleaut32.lib \
	libr $(WATCOMLIBS)$(SLASH)uuid.lib \
	libr $(WATCOMLIBS)$(SLASH)rpcrt4.lib \
	libr $(WATCOMLIBS)$(SLASH)wsock32.lib \
	libr $(WATCOMLIBS)$(SLASH)winmm.lib


# use global setup
#COMPILER=MICROSOFT
ifeq ($(COMPILER), MICROSOFT)
MOD_INCL = $(STD_INCL_MICROSOFT) /I $(DEVROOT_MAKE)/wxwin/wx/include
MOD_INCL += $(foreach s, $(INCLS), /I "$s")
CC=Cl
C_DLLOPS= $(C_DLLOPS_MICROSOFT$(MODE))
C_EXEOPS= $(C_EXEOPS_MICROSOFT$(MODE)) /D__WIN32__ /DWINVER=0x0400 /D__WINDOWS95__ /D__WINDOWS__ /D__WXMSW__ /DLB_I_EXTENTIONS /D__WXDEBUG__
C_LIBOPS= $(C_LIBOPS_MICROSOFT$(MODE))
LINK=  $(LINK_MICROSOFT)
LNKDLLOPS = $(L_DLLOPS_MICROSOFT) /NODEFAULT:MSVCRTD
MODULE=wxwrapper
APPVER=3.50 # 4.0
CPU=i386
LINKFLAGS = $(L_EXEOPS_MICROSOFT) $(LIBS) $(OBJS) \
/pdb:"$(OUTDIR)\$(MODULE).pdb" \
/out:"$(OUTDIR)\$(MODULE).exe" \
/INCREMENTAL:NO /DEBUG /NOLOGO -machine:$(CPU) -subsystem:windows,$(APPVER)
endif
ifeq ($(COMPILER), WATCOM)
MOD_INCL = $(STD_INCL) -i=$(DEVROOT_MAKE)\\wxwin\\wx\\include
MOD_INCL_CPP=$(STD_INCL_CPP) -i=$(DEVROOT_MAKE)/wxwin/wx/include

C_EXEOPS= $(C_EXEOPS_WATCOM$(MODE)) /D__WIN32__ /DWINVER=0x0400 /D__WINDOWS95__ \
		/D__WINDOWS__ /D__WXMSW__ /DLB_I_EXTENTIONS
		
C_DLLOPS= $(C_DLLOPS_WATCOM$(MODE)) /D__WIN32__ /DWINVER=0x0400 /D__WINDOWS95__ \
		/D__WINDOWS__ /D__WXMSW__ /DLB_I_EXTENTIONS /D_WINDLL /DWXUSINGDLL

CPP_EXEOPS= $(CPP_EXEOPS_WATCOM$(MODE)) /D__WIN32__ /DWINVER=0x0400 /D__WINDOWS95__ \
		/D__WINDOWS__ /D__WXMSW__ /DLB_I_EXTENTIONS
		
CPP_DLLOPS= $(CPP_DLLOPS_WATCOM$(MODE)) /D__WIN32__ /DWINVER=0x0400 /D__WINDOWS95__ \
		/D__WINDOWS__ /D__WXMSW__ /DLB_I_EXTENTIONS /D_WINDLL /DWXUSINGDLL

ifeq ($(MODE), _DEBUG)
C_EXEOPS+= /D__WXDEBUG__
C_DLLOPS+= /D__WXDEBUG__
CPP_EXEOPS+= /D__WXDEBUG__
CPP_DLLOPS+= /D__WXDEBUG__
endif
		
LINKFLAGS = $(L_EXEOPS)
endif

endif

ifeq ($(OSTYPE), solaris)
MOD_INCL=$(STD_INCL)
OBJDEP=
C_SOOPS_WX = -DLB_I_EXTENTIONS `wx-config --cxxflags`
C_SOOPS+= $(DEBUG_CXX_FLAGS) $(C_SOOPS_WX)
VENDORLIBS=-L$(prefix)/lib -llbHook 
L_OPS=$(L_SOOPS) `wx-config --inplace --libs` 
endif    


ifeq ($(OSTYPE), linux)
MOD_INCL=$(STD_INCL)
OBJDEP=
C_SOOPS_WX = -DUNIX -DLINUX -DLB_I_EXTENTIONS `wx-config --cxxflags`
C_SOOPS= $(C_SOOPS_WX)
VENDORLIBS=-L$(prefix)/lib -llbHook 
L_OPS=$(L_SOOPS) `wx-config --inplace --libs` 
endif    

ifeq ($(LB_USE_FRAMEWORKS), yes)

ifeq ($(OSTYPE), osx)
MOD_INCL=$(STD_INCL)
OBJDEP=
C_SOOPS_WX = -g -DOSX -DUNIX -DLINUX -DLB_I_EXTENTIONS `wx-config --inplace --cxxflags` 
C_SOOPS= $(C_SOOPS_WX)
VENDORLIBS=-lc /usr/lib/libgcc_s.1.dylib -lc /usr/lib/libstdc++.6.dylib
L_OPS=$(L_SOOPS) -F$(HOME)/lib -framework lbHook `wx-config --inplace --libs` 
endif    

endif

ifeq ($(LB_USE_FRAMEWORKS), no)

ifeq ($(OSTYPE), osx)
MOD_INCL=$(STD_INCL)
OBJDEP=
C_SOOPS_WX = -g -DOSX -DUNIX -DLINUX -DLB_I_EXTENTIONS `wx-config --inplace --cxxflags` 
C_SOOPS= $(C_SOOPS_WX)
VENDORLIBS=$(HOME)/lib/lbHook.so 
L_OPS=$(L_SOOPS) `wx-config --inplace --libs`
endif    

endif
</exsl:document>
</xsl:template>

<xsl:template name="createMakeFileModule_ApplicationModule">

<exsl:document href="{$basedir}/{$appmoduledir}/{$ApplicationName}_AppModule/makefile.module" method="text">
# Define your module based settings

#    DMF Distributed Multiplatform Framework (the initial goal of this library)
#    This file is part of lbDMF.
#    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)
#
#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation; either
#    version 2.1 of the License, or (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this library; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#
#    The author of this work will be reached by e-Mail or paper mail.
#    e-Mail: lothar.behrens@lollisoft.de
#    p-Mail: Lothar Behrens
#            Ginsterweg 4
#
#            65760 Eschborn (germany)


ifeq ($(OSTYPE), Windows_NT)
MOD_INCL=$(STD_INCL) -I=$(DEVROOT)\\Projects\\CPP\\AppDevelopment\\Interfaces
MOD_INCL_CPP=$(STD_INCL_CPP) -I=$(DEVROOT_MAKE)/Projects/CPP/AppDevelopment/Interfaces
SLASH=/
wxBase=$(DEVROOT_MAKE)$(SLASH)wxwin$(SLASH)wx$(SLASH)lib
LIBS = $(BASE_LIBS) $(DEVROOT_MAKE)/projects/dll/libs/lbhook.lib, $(DEVROOT_MAKE)$(SLASH)projects$(SLASH)dll$(SLASH)libs$(SLASH)wxWrapperDLL.lib, \
	$(wxBase)$(SLASH)wat_dll$(SLASH)wxmsw$(WX_VERSION)$(WX_DEBUG).lib


# use global setup
#COMPILER=MICROSOFT
ifeq ($(COMPILER), MICROSOFT)
MOD_INCL = $(STD_INCL_MICROSOFT)
MOD_INCL += $(foreach s, $(INCLS), /I "$s")
LIBS = Q:/develop/Tools/msc/VC98/Lib/odbc32.lib
CC=Cl
C_DLLOPS= $(C_DLLOPS_MICROSOFT$(MODE))
C_EXEOPS= $(C_EXEOPS_MICROSOFT$(MODE))
C_LIBOPS= $(C_LIBOPS_MICROSOFT$(MODE))
LINK=  $(LINK_MICROSOFT)
L_DLLOPS= $(L_DLLOPS_MICROSOFT)
LNKDLLOPS = $(L_DLLOPS_MICROSOFT)
endif

#OBJDEP=../lbHook/lbHook.o
# ../lbHook/conio.o
endif

ifeq ($(OSTYPE), solaris)
MOD_INCL=$(STD_INCL)
C_SOOPS= $(C_OPS)
OBJDEP=
VENDORLIBS=-L$(prefix)/lib -llbHook /usr/local/lib/libodbc.so
endif    

ifeq ($(OSTYPE), linux)
MOD_INCL=$(STD_INCL)
C_SOOPS= $(C_OPS)
OBJDEP=
VENDORLIBS=-L$(prefix)/lib -llbHook /usr/lib/libodbc.so
endif    

ifeq ($(LB_USE_FRAMEWORKS), yes)

ifeq ($(OSTYPE), osx)
MOD_INCL=$(STD_INCL) -I $(DEVROOT)/Projects/CPP/AppDevelopment/Interfaces
MOD_INCL_CPP=$(STD_INCL_CPP) -I $(DEVROOT)/Projects/CPP/AppDevelopment/Interfaces
VENDORLIBS=
LIBS=$(L_SOOPS) -F$(HOME)/lib -framework lbHook
endif    

endif

ifeq ($(LB_USE_FRAMEWORKS), no)

ifeq ($(OSTYPE), osx)
MOD_INCL=$(STD_INCL)
OBJDEP=
VENDORLIBS=$(HOME)/lib/lbHook.so
endif    

endif
</exsl:document>
</xsl:template>

<xsl:template name="createApplicationHeader">
		<xsl:param name="ApplicationID"/>

<exsl:document href="{$basedir}/{$appmoduledir}/{$ApplicationName}_AppModule/{$ApplicationName}.h" method="text">
/* This file is autogenerated. Please do not modify. It would be overwritten.
 */

#ifndef _TV_APP_
#define _TV_APP_

class TStatusLine;
class TMenuBar;
class TEvent;
class TPalette;
class THeapView;
class TClockView;
class fpstream;
class TApplication;

class T<xsl:value-of select="$ApplicationName"/> : public TApplication 
{

public:

    T<xsl:value-of select="$ApplicationName"/>( int argc, char **argv );
    static TStatusLine *initStatusLine( TRect r );
    static TMenuBar *initMenuBar( TRect r );
    virtual void handleEvent(TEvent&amp; Event);
    virtual void getEvent(TEvent&amp; event);
    virtual TPalette&amp; getPalette() const;
    virtual void idle();              // Updates heap and clock views

private:

    THeapView *heap;                  // Heap view
    TClockView *clock;                // Clock view

    void aboutDlgBox();               // "About" box
    void puzzle();                    // Puzzle
    void calendar();                  // Calendar
    void asciiTable();                // Ascii table
    void calculator();                // Calculator
    void openFile( char *fileSpec );  // File Viewer
    void changeDir();                 // Change directory
    void shell();                     // DOS shell
    void tile();                      // Tile windows
    void cascade();                   // Cascade windows
    void mouse();                     // Mouse control dialog box
    void colors();                    // Color control dialog box
    void outOfMemory();               // For validView() function
    void loadDesktop(fpstream&amp; s);    // Load and restore the
    void retrieveDesktop();           //  previously saved desktop
    void storeDesktop(fpstream&amp; s);   // Store the current desktop
    void saveDesktop();               //  in a resource file
    void testInputBox();              // SET: Just a test to show inputBox use

    //void OnDispatch(lb_I_Unknown* uk);

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>
    void show<xsl:value-of select="$FormularName"/>();
</xsl:for-each>


    // In original demo that's a CP 437 specific code. I left it but I use
    // it to show how to solve this using the new code page features of
    // this port of TV.
    static uchar systemMenuIcon[];    // Menu name for the "system menu"
                                      // encoded in current code page
    static uchar osystemMenuIcon[];   // Same encoded in CP 437, used as
                                      // reference.
public:
                                      // Previous callback in the code page chain
    static TVCodePageCallBack oldCPCallBack;
    static void cpCallBack(unsigned short  *map); // That's our callback
    
    
   	UAP(lb_I_EventManager, eman)
	UAP(lb_I_Dispatcher, dispatcher)

};

enum {
    cmBase = 200,
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>
    cm<xsl:value-of select="$FormularName"/>,
</xsl:for-each>
    cmAboutCmd,
    cmCalendarCmd,
    cmAsciiCmd,
    cmCalcCmd,
    cmPuzzleCmd,
    cmOpenCmd,
    cmChDirCmd,
    cmMouseCmd,
    cmColorCmd,
    cmSaveCmd,
    cmRestoreCmd,
    cmTestInputBox
};


enum {
    hcBase = 200,
    hcFirst,
    hcPrevious,
    hcNext,
    hcLast,
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>
  hc<xsl:value-of select="$FormularName"/>,
</xsl:for-each>
  hcEnd
};

#endif //_TV_APP_
</exsl:document>
</xsl:template>

<xsl:template name="createApplicationModule">
		<xsl:param name="ApplicationID"/>
		
<exsl:document href="{$basedir}/{$appmoduledir}/{$ApplicationName}_AppModule/{$ApplicationName}.cc" method="text">
/* This file is autogenerated. Please do not modify. It would be overwritten.
 */
#include &lt;stdio.h&gt;
#define Uses_string

#define Uses_TVCodePage
#define Uses_TView
#define Uses_TRect
#define Uses_TStatusLine
#define Uses_TStatusDef
#define Uses_TStatusItem
#define Uses_TKeys
#define Uses_MsgBox
#define Uses_fpstream
#define Uses_TEvent
#define Uses_TDeskTop
#define Uses_TDialog
#define Uses_TStaticText
#define Uses_TLabel
#define Uses_TButton
#define Uses_TCalculator
#define Uses_TColorGroup
#define Uses_TColorItem
#define Uses_TColorDialog
#define Uses_TChDirDialog
#define Uses_TFileDialog
#define Uses_TApplication
#define Uses_TPalette
#define Uses_TWindow
#define Uses_TSubMenu
#define Uses_TMenuBar
#define Uses_TInputLine
#define Uses_TEventQueue
#define Uses_TDeskTop
#define Uses_TMouseDialog
#define Uses_TScreen
#define Uses_IOS_BIN
#define Uses_THelpWindow
// Needed to remap the "system" menu character
#define Uses_TVCodePage
#define Uses_TStringCollection
#define Uses_TStreamableClass
#define Uses_TCheckBoxes
#define Uses_TComboBox
#define Uses_TStaticInputLine
//#define Uses_

#include &lt;tv.h&gt;

#include "tvdemo.h"
#include "gadgets.h"
#include "fileview.h"
#include "puzzle.h"
#include "ascii.h"
#include "calendar.h"
#include "demohelp.h"
#include "mousedlg.h"

#include "tcombobx.h"
#include "tsinputl.h"

#include &lt;lbConfigHook.h&gt;

UsingNamespaceStd

/* SS: changed */

//#ifdef __DPMI32__
#define HELP_FILENAME "demohelp.h32"
//#else
//#define HELP_FILENAME "DEMOHELP.H16"
//#endif

__link(RCalculator);
__link(RCalcDisplay);

#include "<xsl:value-of select="$ApplicationName"/>.h"

int main(int argc, char **argv, char **envir)
{
    UAP_REQUEST(getModuleInstance(), lb_I_String, firstInstanceRequired)


    // The following is optional, but helps some low level drivers.
    // Don't do it if you experiment any side effect in the arguments or you
    // use these variables in a not so common way.
    // Note that the Linux console driver will alter argv to be able to change
    // what ps reports, you'll get the setWindowTitle argument.
    TDisplay::setArgv(argc,argv,envir);
    
    // Uncommenting the next line the cursor won't be hided.
    // This is a test to get an application a little bit friendly for Braille
    // Terminals.
    //TDisplay::setShowCursorEver(True);
    
    // We have non-ASCII symbols that depends on the code page. We must
    // recode them to the screen code page, here is how we hook the code page
    // change chain.

    T<xsl:value-of select="$ApplicationName"/>::oldCPCallBack=TVCodePage::SetCallBack(T<xsl:value-of select="$ApplicationName"/>::cpCallBack);
    
    T<xsl:value-of select="$ApplicationName"/> *<xsl:value-of select="$ApplicationName"/> = new T<xsl:value-of select="$ApplicationName"/>(argc,argv);

    // This is new in our port of TV:
    const char *title=TScreen::getWindowTitle();
    TScreen::setWindowTitle("Turbo Vision <xsl:value-of select="$ApplicationName"/> Program");
    <xsl:value-of select="$ApplicationName"/>->run();

    TObject::CLY_destroy( <xsl:value-of select="$ApplicationName"/> );
    if( title )
        {
        TScreen::setWindowTitle(title);
        delete[] title;
        }

    return 0;
}

T<xsl:value-of select="$ApplicationName"/>::T<xsl:value-of select="$ApplicationName"/>( int argc, char **argv ) :
    TProgInit( &amp;T<xsl:value-of select="$ApplicationName"/>::initStatusLine,
               &amp;T<xsl:value-of select="$ApplicationName"/>::initMenuBar,
               &amp;T<xsl:value-of select="$ApplicationName"/>::initDeskTop )
{
    TView *w;
    char fileSpec[128];
    int len;

    TRect r = getExtent();                      // Create the clock view.
    r.a.x = r.b.x - 9;      r.b.y = r.a.y + 1;
    clock = new TClockView( r );
    insert(clock);

    r = getExtent();                            // Create the heap view.
    r.a.x = r.b.x - 13;     r.a.y = r.b.y - 1;
    heap = new THeapView( r );
    insert(heap);

    while (--argc > 0)                              // Display files specified
        {                                           //  on command line.
        strcpy( fileSpec, *++argv );
        len = strlen( fileSpec );

        /* SS: changed */

        if( fileSpec[len-1] == '/' )
            strcat( fileSpec, "*" );
        if( strchr( fileSpec, '*' ) || strchr( fileSpec, '?' ) )
            openFile( fileSpec );
        else
            {
            w = validView( new TFileWindow( fileSpec ) );
            if( w != 0 )
                deskTop->insert(w);
            }
        }

}

void T<xsl:value-of select="$ApplicationName"/>::getEvent(TEvent &amp;event)
{
    TWindow *w;
    THelpFile *hFile;
    fpstream *helpStrm;
    static Boolean helpInUse = False;

    TApplication::getEvent(event);
    switch (event.what)
        {
        case evCommand:
            if ((event.message.command == cmHelp) &amp;&amp; ( helpInUse == False)) 
                {
                helpInUse = True;
                helpStrm = new fpstream(HELP_FILENAME, CLY_IOSIn|CLY_IOSBin);
                hFile = new THelpFile(*helpStrm);
                if (!helpStrm)
                    {
                    messageBox("Could not open help file", mfError | mfOKButton);
                    delete hFile;
                    }
                else
                    {
                    w = new THelpWindow(hFile, getHelpCtx());
                    if (validView(w) != 0)
                        {
                        execView(w);
                        CLY_destroy(w);
                        }
                    clearEvent(event);
                    }
                helpInUse = False;
                }
            break;
        case evMouseDown:
            if (event.mouse.buttons != 1)
                event.what = evNothing;
            break;
        }

}  

//
// Create statusline.
//

TStatusLine *T<xsl:value-of select="$ApplicationName"/>::initStatusLine( TRect r )
{
    r.a.y = r.b.y - 1;

    return (new TStatusLine( r,
      *new TStatusDef( 0, 50 ) +
        *new TStatusItem( "~F1~ Help", kbF1, cmHelp ) +
        *new TStatusItem( "~Alt-X~ Exit", kbAltX, cmQuit ) +
        *new TStatusItem( 0, kbAltF3, cmClose ) +
        *new TStatusItem( 0, kbF10, cmMenu ) +
        *new TStatusItem( 0, kbF5, cmZoom ) +
        *new TStatusItem( 0, kbCtrlF5, cmResize ) +
      *new TStatusDef( 50, 0xffff ) +
        *new TStatusItem( "Howdy", kbF1, cmHelp )
        )
    );
}


//
// Puzzle function
//

void T<xsl:value-of select="$ApplicationName"/>::puzzle()
{
    TPuzzleWindow *puzz = (TPuzzleWindow *) validView(new TPuzzleWindow);

    if(puzz != 0)
        {
        puzz->helpCtx = hcPuzzle;
        deskTop->insert(puzz);
	}
}


//
// retrieveDesktop() function ( restores the previously stored Desktop )
//

// SET: Mike modified it to lowercase, is less annoying on POSIX systems
static const char *TVDemoFile="T<xsl:value-of select="$ApplicationName"/>.dst";

void T<xsl:value-of select="$ApplicationName"/>::retrieveDesktop()
{
	/* SS: changed */

//    struct ffblk ffblk;

//    if (findfirst("T<xsl:value-of select="$ApplicationName"/>.DST", &amp;ffblk, 0))
	FILE *fp;
	if ((fp = fopen(TVDemoFile, "r")) == NULL)
        messageBox("Could not find desktop file", mfOKButton | mfError);
        else
        {
	fclose(fp);
        fpstream *f = new fpstream(TVDemoFile, CLY_IOSIn|CLY_IOSBin);
        if( !f )
            messageBox("Could not open desktop file", mfOKButton | mfError);
        else
           {
           T<xsl:value-of select="$ApplicationName"/>::loadDesktop(*f);
           if( !f )
               messageBox("Error reading desktop file", mfOKButton | mfError);
           }
        delete f;
        }
}

//
// saveDesktop() function ( saves the DeskTop by calling storeDesktop function )
//

void T<xsl:value-of select="$ApplicationName"/>::saveDesktop()
{
    fpstream *f = new fpstream(TVDemoFile, CLY_IOSOut | CLY_IOSBin);

    if( f )
        {
        T<xsl:value-of select="$ApplicationName"/>::storeDesktop(*f);
        if( !f )
            {
            messageBox("Could not create T<xsl:value-of select="$ApplicationName"/>.dst.", mfOKButton | mfError);
            delete f;
            ::remove(TVDemoFile);
            return;
            }
        }
    delete f;
}

//
// writeView() function ( writes a view object to a resource file )
//

static void writeView(TView *p, void *strm)
{
   fpstream *s = (fpstream *) strm;
   if (p != TProgram::deskTop->last)
      *s &lt;&lt; p;
}

//
// storeDesktop() function ( stores the Desktop in a resource file )
//

void T<xsl:value-of select="$ApplicationName"/>::storeDesktop(fpstream&amp; s)
{
  deskTop->forEach(::writeView, &amp;s);
  s &lt;&lt; 0;
}

//
// Tile function
//

void T<xsl:value-of select="$ApplicationName"/>::tile()
{
    deskTop->tile( deskTop->getExtent() );
}

void T<xsl:value-of select="$ApplicationName"/>::shell()
{
	/* SS: this simulates a Ctrl-Z */
	/*raise(SIGTSTP);*/		/* stop the process */
    suspend();
    TScreen::System(CLY_GetShellName());
    resume();
    redraw();
}

void T<xsl:value-of select="$ApplicationName"/>::testInputBox()
{
    char buffer[20];
    strcpy(buffer,"Initial value");
    if (inputBox("Test for the inputBox","Enter a number",buffer,20)!=cmCancel)
    {
        messageBox(mfInformation | mfOKButton,"Value entered: %s",buffer);
    }
    else
    {
        messageBox("\x3""Input canceled", mfInformation | mfOKButton);
    }
}

//
// DemoApp::handleEvent()
//  Event loop to distribute the work.
//

void T<xsl:value-of select="$ApplicationName"/>::handleEvent(TEvent &amp;event)
{
    TApplication::handleEvent(event);

    if (event.what == evCommand)
    {
            lbErrCodes err = ERR_NONE;
			lb_I_Module* m = getModuleInstance();
			
			if (eman == NULL) {
				REQUEST(m, lb_I_EventManager, eman)
			}
		
			if (dispatcher == NULL) {
				REQUEST(m, lb_I_Dispatcher, dispatcher)
				dispatcher->setEventManager(eman.getPtr());
			}				

        switch (event.message.command)
            {
            case cmAboutCmd:            //  About Dialog Box
                aboutDlgBox();
                break;

            case cmCalendarCmd:         //  Calendar Window
                calendar();
                break;

            case cmAsciiCmd:            //  Ascii Table
                asciiTable();
                break;

            case cmCalcCmd:             //  Calculator
                calculator();
                break;

            case cmPuzzleCmd:           //  Puzzle
                puzzle();
                break;

            case cmOpenCmd:             //  View a file
                // SET: Even DOS port needs it.
                openFile("*");
                break;

            case cmChDirCmd:            //  Change directory
                changeDir();
                break;

            case cmCallShell:             //  DOS shell
                shell();
                break;

            case cmTile:             //  Tile current file windows
                tile();
                break;

            case cmCascade:          //  Cascade current file windows
                cascade();
                break;

            case cmMouseCmd:            //  Mouse control dialog box
                mouse();
                break;

            case cmColorCmd:            //  Color control dialog box
                colors();
                break;

        case cmSaveCmd:             //  Save current desktop
                saveDesktop();
                break;
 
        case cmRestoreCmd:          //  Restore saved desktop
                retrieveDesktop();
                break;

        case cmTestInputBox:
                testInputBox();
                break;

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>
        case cm<xsl:value-of select="$FormularName"/>:
                show<xsl:value-of select="$FormularName"/>();
                break;
</xsl:for-each>


            default:                    //  Unknown command
                            // Delegate all other events
                {

			UAP_REQUEST(m, lb_I_Integer, param)
			
			param->setData(event.message.command);
			
			UAP(lb_I_Unknown, uk)
			QI(param, lb_I_Unknown, uk)
		
			UAP_REQUEST(m, lb_I_String, result)
			UAP(lb_I_Unknown, uk_result)
			QI(result, lb_I_Unknown, uk_result)
		
			dispatcher->dispatch(event.message.command, uk.getPtr(), &amp;uk_result);
                }

                return;

            }
        clearEvent (event);
        }
}


unsigned short  executeDialog( TDialog* pD, void* data=0 )
{
    unsigned short  c=cmCancel;

    if (TProgram::application->validView(pD))
        {
        if (data)
        pD->setData(data);
        c = TProgram::deskTop->execView(pD);
        if ((c != cmCancel) &amp;&amp; (data))
            pD->getData(data);
        CLY_destroy(pD);
        }

    return c;
}

//
// About Box function()
//

void T<xsl:value-of select="$ApplicationName"/>::aboutDlgBox()
{
    TDialog *aboutBox = new TDialog(TRect(0, 0, 39, 13), "About");

    aboutBox->insert(
      new TStaticText(TRect(9, 2, 30, 9),
        "\003Turbo Vision Demo\n\n"       // These strings will be
        "\003C++ Version\n\n"             // concatenated by the compiler.
        "\003Copyright (c) 1994\n\n"      // The \003 centers the line.
        "\003Borland International"
        )
      );

    aboutBox->insert(
      new TButton(TRect(14, 10, 26, 12), " OK", cmOK, bfDefault)
      );

    aboutBox->options |= ofCentered;

    executeDialog(aboutBox);

}


//
// Ascii Chart function
//

void T<xsl:value-of select="$ApplicationName"/>::asciiTable()
{
    TAsciiChart *chart = (TAsciiChart *) validView(new TAsciiChart);

    if(chart != 0)
    {
        chart->helpCtx = hcAsciiTable;
        deskTop->insert(chart);
    }
}


//
// Calendar function()
//

void T<xsl:value-of select="$ApplicationName"/>::calendar()
{
    TCalendarWindow *cal = (TCalendarWindow *) validView(new TCalendarWindow);

    if(cal != 0)
    {
        cal->helpCtx = hcCalendar;
        deskTop->insert( cal );
    }
}


//
// Calculator function
//

void T<xsl:value-of select="$ApplicationName"/>::calculator()
{
    TCalculator *calc = (TCalculator *) validView(new TCalculator);

    if(calc != 0)
    {
        calc->helpCtx = hcCalculator;
        deskTop->insert(calc);
    }
}

//
// Cascade function
//

void T<xsl:value-of select="$ApplicationName"/>::cascade()
{
    deskTop->cascade( deskTop->getExtent() );
}


//
// Change Directory function
//

void T<xsl:value-of select="$ApplicationName"/>::changeDir()
{
    TView *d = validView( new TChDirDialog( 0, cmChangeDir ) );

    if( d != 0 )
        {
        d->helpCtx = hcFCChDirDBox;
        deskTop->execView( d );
        CLY_destroy(d);
    }
}


//
// Color Control Dialog Box function
//

void T<xsl:value-of select="$ApplicationName"/>::colors()
{
    TColorGroup &amp;group1 =
        *new TColorGroup("Desktop") +
            *new TColorItem("Color",             1)+

        *new TColorGroup("Menus") +
            *new TColorItem("Normal",            2)+
            *new TColorItem("Disabled",          3)+
            *new TColorItem("Shortcut",          4)+
            *new TColorItem("Selected",          5)+
            *new TColorItem("Selected disabled", 6)+
            *new TColorItem("Shortcut selected", 7
        );

    TColorGroup &amp;group2 =
        *new TColorGroup("Dialogs/Calc") +
            *new TColorItem("Frame/background",  33)+
            *new TColorItem("Frame icons",       34)+
            *new TColorItem("Scroll bar page",   35)+
            *new TColorItem("Scroll bar icons",  36)+
            *new TColorItem("Static text",       37)+

            *new TColorItem("Label normal",      38)+
            *new TColorItem("Label selected",    39)+
            *new TColorItem("Label shortcut",    40
        );

    TColorItem &amp;item_coll1 =
        *new TColorItem("Button normal",     41)+
        *new TColorItem("Button default",    42)+
        *new TColorItem("Button selected",   43)+
        *new TColorItem("Button disabled",   44)+
        *new TColorItem("Button shortcut",   45)+
        *new TColorItem("Button shadow",     46)+
        *new TColorItem("Cluster normal",    47)+
        *new TColorItem("Cluster selected",  48)+
        *new TColorItem("Cluster shortcut",  49
        );

    TColorItem &amp;item_coll2 =
        *new TColorItem("Input normal",      50)+
        *new TColorItem("Input selected",    51)+
        *new TColorItem("Input arrow",       52)+

        *new TColorItem("History button",    53)+
        *new TColorItem("History sides",     54)+
        *new TColorItem("History bar page",  55)+
        *new TColorItem("History bar icons", 56)+

        *new TColorItem("List normal",       57)+
        *new TColorItem("List focused",      58)+
        *new TColorItem("List selected",     59)+
        *new TColorItem("List divider",      60)+

        *new TColorItem("Information pane",  61
        );

     group2 = group2 + item_coll1 + item_coll2;

     TColorGroup &amp;group3 =
         *new TColorGroup("Viewer") +
             *new TColorItem("Frame passive",      8)+
             *new TColorItem("Frame active",       9)+
             *new TColorItem("Frame icons",       10)+
             *new TColorItem("Scroll bar page",   11)+
             *new TColorItem("Scroll bar icons",  12)+
             *new TColorItem("Text",              13)+
         *new TColorGroup("Puzzle")+
             *new TColorItem("Frame passive",      8)+
             *new TColorItem("Frame active",       9)+
             *new TColorItem("Frame icons",       10)+
             *new TColorItem("Scroll bar page",   11)+
             *new TColorItem("Scroll bar icons",  12)+
             *new TColorItem("Normal text",       13)+
             *new TColorItem("Highlighted text",  14
         );


     TColorGroup &amp;group4 =
         *new TColorGroup("Calendar") +
             *new TColorItem("Frame passive",     16)+
             *new TColorItem("Frame active",      17)+
             *new TColorItem("Frame icons",       18)+
             *new TColorItem("Scroll bar page",   19)+
             *new TColorItem("Scroll bar icons",  20)+
             *new TColorItem("Normal text",       21)+
             *new TColorItem("Current day",       22)+

         *new TColorGroup("Ascii table") +
             *new TColorItem("Frame passive",     24)+
             *new TColorItem("Frame active",      25)+
             *new TColorItem("Frame icons",       26)+
             *new TColorItem("Scroll bar page",   27)+
             *new TColorItem("Scroll bar icons",  28)+
             *new TColorItem("Text",              29
         );


    TColorGroup &amp;group5 = group1 + group2 + group3 + group4;

    TPalette *temp_pal=new TPalette(getPalette());
    TColorDialog *c = new TColorDialog(temp_pal, &amp;group5 );

    if( validView( c ) != 0 )
    {
        c->helpCtx = hcOCColorsDBox;  // set context help constant
        c->setData(&amp;getPalette());
        if( deskTop->execView( c ) != cmCancel )
            {
            getPalette() = *(c->pal);
            setScreenMode(TScreen::screenMode);
            }
        CLY_destroy(c);
    }
    delete temp_pal;
}

uchar T<xsl:value-of select="$ApplicationName"/>::systemMenuIcon[]="~\360~";
uchar T<xsl:value-of select="$ApplicationName"/>::osystemMenuIcon[]="~\360~";
TVCodePageCallBack T<xsl:value-of select="$ApplicationName"/>::oldCPCallBack=NULL;



void T<xsl:value-of select="$ApplicationName"/>::mouse()
{
    TMouseDialog *mouseCage = (TMouseDialog *) validView( new TMouseDialog() );

    if (mouseCage != 0)
        {
        mouseCage->helpCtx = hcOMMouseDBox;
        mouseCage->setData(&amp;(TEventQueue::mouseReverse));
        if (deskTop->execView(mouseCage) != cmCancel)
            mouseCage->getData(&amp;(TEventQueue::mouseReverse));
        }
    CLY_destroy(mouseCage);
   
}


//
// File Viewer function
//

void T<xsl:value-of select="$ApplicationName"/>::openFile( char *fileSpec )
{
    TFileDialog *d= (TFileDialog *)validView(
    new TFileDialog(fileSpec, "Open a File", "~N~ame", fdOpenButton, 100 ));

    if( d != 0 &amp;&amp; deskTop->execView( d ) != cmCancel )
        {
        char fileName[PATH_MAX];
        d->getFileName( fileName );
        d->helpCtx = hcFOFileOpenDBox;
        TView *w= validView( new TFileWindow( fileName ) );
        if( w != 0 )
            deskTop->insert(w);
    }
    CLY_destroy(d);
}


//
// "Out of Memory" function ( called by validView() )
//

void T<xsl:value-of select="$ApplicationName"/>::outOfMemory()
{
    messageBox( "Not enough memory available to complete operation.",
      mfError | mfOKButton );
}

//
// getPalette() function ( returns application's palette )
//
#define cpAppColor \
       "\x71\x70\x78\x74\x20\x28\x24\x17\x1F\x1A\x31\x31\x1E\x71\x1F" \
    "\x37\x3F\x3A\x13\x13\x3E\x21\x3F\x70\x7F\x7A\x13\x13\x70\x7F\x7E" \
    "\x70\x7F\x7A\x13\x13\x70\x70\x7F\x7E\x20\x2B\x2F\x78\x2E\x70\x30" \
    "\x3F\x3E\x1F\x2F\x1A\x20\x72\x31\x31\x30\x2F\x3E\x31\x13\x38\x00" \
    "\x17\x1F\x1A\x71\x71\x1E\x17\x1F\x1E\x20\x2B\x2F\x78\x2E\x10\x30" \
    "\x3F\x3E\x70\x2F\x7A\x20\x12\x31\x31\x30\x2F\x3E\x31\x13\x38\x00" \
    "\x37\x3F\x3A\x13\x13\x3E\x30\x3F\x3E\x20\x2B\x2F\x78\x2E\x30\x70" \
    "\x7F\x7E\x1F\x2F\x1A\x20\x32\x31\x71\x70\x2F\x7E\x71\x13\x78\x00" \
    "\x37\x3F\x3A\x13\x13\x30\x3E\x1E"    // help colors

#define cpAppBlackWhite \
       "\x70\x70\x78\x7F\x07\x07\x0F\x07\x0F\x07\x70\x70\x07\x70\x0F" \
    "\x07\x0F\x07\x70\x70\x07\x70\x0F\x70\x7F\x7F\x70\x07\x70\x07\x0F" \
    "\x70\x7F\x7F\x70\x07\x70\x70\x7F\x7F\x07\x0F\x0F\x78\x0F\x78\x07" \
    "\x0F\x0F\x0F\x70\x0F\x07\x70\x70\x70\x07\x70\x0F\x07\x07\x08\x00" \
    "\x07\x0F\x0F\x07\x70\x07\x07\x0F\x0F\x70\x78\x7F\x08\x7F\x08\x70" \
    "\x7F\x7F\x7F\x0F\x70\x70\x07\x70\x70\x70\x07\x7F\x70\x07\x78\x00" \
    "\x70\x7F\x7F\x70\x07\x70\x70\x7F\x7F\x07\x0F\x0F\x78\x0F\x78\x07" \
    "\x0F\x0F\x0F\x70\x0F\x07\x70\x70\x70\x07\x70\x0F\x07\x07\x08\x00" \
    "\x07\x0F\x07\x70\x70\x07\x0F\x70"    // help colors

#define cpAppMonochrome \
       "\x70\x07\x07\x0F\x70\x70\x70\x07\x0F\x07\x70\x70\x07\x70\x00" \
    "\x07\x0F\x07\x70\x70\x07\x70\x00\x70\x70\x70\x07\x07\x70\x07\x00" \
    "\x70\x70\x70\x07\x07\x70\x70\x70\x0F\x07\x07\x0F\x70\x0F\x70\x07" \
    "\x0F\x0F\x07\x70\x07\x07\x70\x07\x07\x07\x70\x0F\x07\x07\x70\x00" \
    "\x70\x70\x70\x07\x07\x70\x70\x70\x0F\x07\x07\x0F\x70\x0F\x70\x07" \
    "\x0F\x0F\x07\x70\x07\x07\x70\x07\x07\x07\x70\x0F\x07\x07\x01\x00" \
    "\x70\x70\x70\x07\x07\x70\x70\x70\x0F\x07\x07\x0F\x70\x0F\x70\x07" \
    "\x0F\x0F\x07\x70\x07\x07\x70\x07\x07\x07\x70\x0F\x07\x07\x01\x00" \
    "\x07\x0F\x07\x70\x70\x07\x0F\x70"    // help colors

TPalette&amp; T<xsl:value-of select="$ApplicationName"/>::getPalette() const
{
    static TPalette newcolor ( cpAppColor , sizeof( cpAppColor )-1 );
    static TPalette newblackwhite( cpAppBlackWhite , sizeof( cpAppBlackWhite )-1 );
    static TPalette newmonochrome( cpAppMonochrome , sizeof( cpAppMonochrome )-1 );
    static TPalette *palettes[] =
        {
        &amp;newcolor,
        &amp;newblackwhite,
        &amp;newmonochrome
        };
    return *(palettes[appPalette]);

}


//
// isTileable() function ( checks a view on desktop is tileable or not )
//

static Boolean isTileable(TView *p, void * )
{
   if( (p->options &amp; ofTileable) != 0)
       return True;
   else
       return False;
}

//
// idle() function ( updates heap and clock views for this program. )
//

void T<xsl:value-of select="$ApplicationName"/>::idle()
{
    TProgram::idle();
    clock->update();
    heap->update();
    if (deskTop->firstThat(isTileable, 0) != 0 )
        {
        enableCommand(cmTile);
        enableCommand(cmCascade);
        }
    else 
        {
        disableCommand(cmTile);
        disableCommand(cmCascade);
        }
}

//
// closeView() function
//

static void closeView(TView *p, void *p1)
{
    message(p, evCommand, cmClose, p1);
}

//
// loadDesktop() function 
//

void T<xsl:value-of select="$ApplicationName"/>::loadDesktop(fpstream &amp;s)
{
    TView  *p;

    if (deskTop->valid(cmClose))
        { 
        deskTop->forEach(::closeView, 0);  // Clear the desktop
        do {
           s &gt;&gt; p;
           deskTop->insertBefore(validView(p), deskTop->last);
           }
           while (p != 0);
        }
}

//
// Menubar initialization.
//

TMenuBar *T<xsl:value-of select="$ApplicationName"/>::initMenuBar(TRect r)
{
    TSubMenu&amp; sub1 =
      *new TSubMenu( (char *)systemMenuIcon, 0, hcSystem ) +
        *new TMenuItem( "~A~bout...", cmAboutCmd, kbNoKey, hcSAbout ) +
         newLine() +
        *new TMenuItem( "~P~uzzle", cmPuzzleCmd, kbNoKey, hcSPuzzle ) +
        *new TMenuItem( "Ca~l~endar", cmCalendarCmd, kbNoKey, hcSCalendar ) +
        *new TMenuItem( "Ascii ~T~able", cmAsciiCmd, kbNoKey, hcSAsciiTable ) +
        *new TMenuItem( "~C~alculator", cmCalcCmd, kbNoKey, hcCalculator );

    TSubMenu&amp; sub2 =
      *new TSubMenu( "~F~ile", 0, hcFile ) +
        *new TMenuItem( "~O~pen...", cmOpenCmd, kbF3, hcFOpen, "F3" ) +
        *new TMenuItem( "~C~hange Dir...", cmChDirCmd, kbNoKey, hcFChangeDir ) +
         newLine() +
        *new TMenuItem( "S~h~ell", cmCallShell, kbNoKey, hcFDosShell ) +
        *new TMenuItem( "E~x~it", cmQuit, kbAltX, hcFExit, "Alt-X" );

    TSubMenu&amp; subForms =
      *new TSubMenu( "~A~pplication <xsl:value-of select="$ApplicationName"/>", 0, hcWindows ) +
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>
        *new TMenuItem( "<xsl:value-of select="$FormularName"/>", cm<xsl:value-of select="$FormularName"/>, kbNoKey, hc<xsl:value-of select="$FormularName"/>, "Ctrl-F5" ) <xsl:if test="position()!=last()">+</xsl:if><xsl:if test="position()=last()">;</xsl:if>
</xsl:for-each>

    TSubMenu&amp;sub3 =
      *new TSubMenu( "~W~indows", 0, hcWindows ) +
        *new TMenuItem( "~R~esize/move", cmResize, kbCtrlF5, hcWSizeMove, "Ctrl-F5" ) +
        *new TMenuItem( "~Z~oom", cmZoom, kbF5, hcWZoom, "F5" ) +
        *new TMenuItem( "~N~ext", cmNext, kbF6, hcWNext, "F6" ) +
        *new TMenuItem( "~C~lose", cmClose, kbAltF3, hcWClose, "Alt-F3" ) +
        *new TMenuItem( "~T~ile", cmTile, kbNoKey, hcWTile ) +
        *new TMenuItem( "C~a~scade", cmCascade, kbNoKey, hcWCascade );

    TSubMenu&amp; sub4 =
      *new TSubMenu( "~O~ptions", 0, hcOptions ) +
        *new TMenuItem( "~M~ouse...", cmMouseCmd, kbNoKey, hcOMouse ) +
        *new TMenuItem( "~C~olors...", cmColorCmd, kbNoKey, hcOColors ) +
        *new TMenuItem( "~S~ave desktop", cmSaveCmd, kbNoKey, hcOSaveDesktop ) +
        *new TMenuItem( "~R~etrieve desktop", cmRestoreCmd, kbNoKey, hcORestoreDesktop ) +
        *new TMenuItem( "~T~est inputbox", cmTestInputBox, kbNoKey, hcORestoreDesktop );



    r.b.y =  r.a.y + 1;
    return (new TMenuBar( r, sub1 + sub2 + subForms + sub3 + sub4 ) );
}

// Called each time the code page changes. In this example we only have
// potential code page changes at start-up.
void T<xsl:value-of select="$ApplicationName"/>::cpCallBack(unsigned short  *map)
{
 TVCodePage::RemapString(systemMenuIcon,osystemMenuIcon,map);
 TCalendarView::upArrowChar=TVCodePage::RemapChar(TCalendarView::oupArrowChar,map);
 TCalendarView::downArrowChar=TVCodePage::RemapChar(TCalendarView::odownArrowChar,map);
 // If the chain was already used call it
 if (oldCPCallBack)
    oldCPCallBack(map);
}



<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="FormularID" select="@ID"/>
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>

class T<xsl:value-of select="$FormularName"/>Dialog :
public lb_I_Window,
public lb_I_EventHandler {
public:
    T<xsl:value-of select="$FormularName"/>Dialog();
    virtual ~T<xsl:value-of select="$FormularName"/>Dialog();
    
    DECLARE_LB_UNKNOWN()

	void LB_STDCALL create(int parentId) {}
	int  LB_STDCALL getId() { return -1; }
	void LB_STDCALL windowIsClosing(lb_I_Window* w) { }

    lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);

    TDialog* buildDialog<xsl:value-of select="$FormularName"/>(lb_I_EventManager* eman, lb_I_Dispatcher* disp);

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID][@isfk='1']">
	void fillComboBox_<xsl:value-of select="@name"/>(TStringCollection* choice);
</xsl:for-each>

protected:

    lbErrCodes LB_STDCALL DBUpdate();
    lbErrCodes LB_STDCALL DBRead();
    lbErrCodes LB_STDCALL DBFirst(lb_I_Unknown* uk);
    lbErrCodes LB_STDCALL DBPrevious(lb_I_Unknown* uk);
    lbErrCodes LB_STDCALL DBNext(lb_I_Unknown* uk);
    lbErrCodes LB_STDCALL DBLast(lb_I_Unknown* uk);

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
   TComboBox* cmb<xsl:value-of select="@name"/>;
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
   TCheckBoxes* cb<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
   TInputLine* txt<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
   TInputLine* txt<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:when test="@dbtype='String'">
   TInputLine* txt<xsl:value-of select="@name"/>;
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

    UAP(lb_I_String, _DBName)
    UAP(lb_I_String, _DBUser)
    UAP(lb_I_String, _DBPass)

    UAP(lb_I_Database, database)	
    UAP(lb_I_Query, sampleQuery)
    UAP(lb_I_String, SQLString)
	
	UAP(lb_I_Container, ComboboxMapperList)

};

BEGIN_IMPLEMENT_LB_UNKNOWN(T<xsl:value-of select="$FormularName"/>Dialog)
END_IMPLEMENT_LB_UNKNOWN()

T<xsl:value-of select="$FormularName"/>Dialog::T<xsl:value-of select="$FormularName"/>Dialog() {
	REQUEST(getModuleInstance(), lb_I_Container, ComboboxMapperList)
}

T<xsl:value-of select="$FormularName"/>Dialog::~T<xsl:value-of select="$FormularName"/>Dialog() {

}

lbErrCodes LB_STDCALL T<xsl:value-of select="$FormularName"/>Dialog::setData(lb_I_Unknown* uk) {
    return ERR_NONE;
}

lbErrCodes LB_STDCALL T<xsl:value-of select="$FormularName"/>Dialog::registerEventHandler(lb_I_Dispatcher* disp) {
    char eventName[100] = "";
    
    sprintf(eventName, "%pDBFirst", this);
	disp->addEventHandlerFn(this, (lbEvHandler) &amp;T<xsl:value-of select="$FormularName"/>Dialog::DBFirst, eventName);
    sprintf(eventName, "%pDBPrevious", this);
	disp->addEventHandlerFn(this, (lbEvHandler) &amp;T<xsl:value-of select="$FormularName"/>Dialog::DBPrevious, eventName);
    sprintf(eventName, "%pDBNext", this);
	disp->addEventHandlerFn(this, (lbEvHandler) &amp;T<xsl:value-of select="$FormularName"/>Dialog::DBNext, eventName);
    sprintf(eventName, "%pDBLast", this);
	disp->addEventHandlerFn(this, (lbEvHandler) &amp;T<xsl:value-of select="$FormularName"/>Dialog::DBLast, eventName);
    return ERR_NONE;
}

lbErrCodes LB_STDCALL T<xsl:value-of select="$FormularName"/>Dialog::DBRead() {
	UAP_REQUEST(getModuleInstance(), lb_I_String, col)
	UAP_REQUEST(getModuleInstance(), lb_I_String, val)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	
	_LOG &lt;&lt; "lbErrCodes LB_STDCALL T<xsl:value-of select="$FormularName"/>Dialog::DBRead() called." LOG_
	
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
#ifdef bla
	wxChoice* cbox_<xsl:value-of select="@name"/> = (wxChoice*) w;
				
	int pos_<xsl:value-of select="@name"/> = cbox_<xsl:value-of select="@name"/>->GetSelection();
				
	if (pos_<xsl:value-of select="@name"/> != -1) {
		lbErrCodes err = ERR_NONE;

		UAP_REQUEST(manager.getPtr(), lb_I_Integer, key)
		UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)
					
		cbName-&gt;setData("<xsl:value-of select="@name"/>");
					
		UAP(lb_I_KeyBase, key_cbName)
		UAP(lb_I_Unknown, uk_cbMapper)
		UAP(lb_I_Container, cbMapper)
					
		QI(cbName, lb_I_KeyBase, key_cbName)
			
		uk_cbMapper = ComboboxMapperList-&gt;getElement(&amp;key_cbName);
					
		QI(uk_cbMapper, lb_I_Container, cbMapper)
					
		key-&gt;setData(pos_<xsl:value-of select="@name"/>);

		UAP(lb_I_KeyBase, key_pos)
		QI(key, lb_I_KeyBase, key_pos)
		UAP(lb_I_Unknown, uk_mapping)
		uk_mapping = cbMapper-&gt;getElement(&amp;key_pos);

		if (uk_mapping == NULL)  { 
			if (!sampleQuery-&gt;isNullable("<xsl:value-of select="@name"/>")) {
				if (!meta-&gt;askYesNo(_trans("Failed to save data. Not all fields are filled."))) return ERR_UPDATE_FAILED;
			}
		} else {
			UAP(lb_I_Long, FK_id)
					
			QI(uk_mapping, lb_I_Long, FK_id)
			
			long p = FK_id-&gt;getData();
					
			char pp[20] = "";
						
			sprintf(pp, "%dl", p);
					
			col-&gt;setData("<xsl:value-of select="@name"/>");
			val-&gt;setData(pp);
				
			sampleQuery-&gt;setNull("<xsl:value-of select="@name"/>", false);
			sampleQuery-&gt;setString(*&amp;col, *&amp;val);
		}
	} else {
		if (!sampleQuery-&gt;isNullable("<xsl:value-of select="@name"/>")) {
			if (!meta-&gt;askYesNo(_trans("Failed to save data. Not all fields are filled."))) return ERR_UPDATE_FAILED;
		}
	}
#endif //bla	
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
	// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
	if (!sampleQuery->getReadonly("<xsl:value-of select="@name"/>")) {
		col->setData("<xsl:value-of select="@name"/>");
		val = sampleQuery->getString(*&amp;col, *&amp;val);

		if (cb<xsl:value-of select="@name"/>->mark(0) == TRUE) {
			if (*val == "false") {
                cb<xsl:value-of select="@name"/>->press(0);
			}
		} else {
			if (*val == "true") {
                cb<xsl:value-of select="@name"/>->press(0);
			}
		}
	}
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
        UAP(lb_I_String, s_<xsl:value-of select="@name"/>)
        s_<xsl:value-of select="@name"/> = sampleQuery->getAsString("<xsl:value-of select="@name"/>");
        txt<xsl:value-of select="@name"/>->maxLen = strlen(s_<xsl:value-of select="@name"/>->charrep());
        if (txt<xsl:value-of select="@name"/>->data) delete[] txt<xsl:value-of select="@name"/>->data;
        txt<xsl:value-of select="@name"/>->data = new char[txt<xsl:value-of select="@name"/>->maxLen+1];
        txt<xsl:value-of select="@name"/>->setData(s_<xsl:value-of select="@name"/>->charrep());
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
        UAP(lb_I_String, s_<xsl:value-of select="@name"/>)
        s_<xsl:value-of select="@name"/> = sampleQuery->getAsString("<xsl:value-of select="@name"/>");
        txt<xsl:value-of select="@name"/>->maxLen = strlen(s_<xsl:value-of select="@name"/>->charrep());
        if (txt<xsl:value-of select="@name"/>->data) delete[] txt<xsl:value-of select="@name"/>->data;
        txt<xsl:value-of select="@name"/>->data = new char[txt<xsl:value-of select="@name"/>->maxLen+1];
        txt<xsl:value-of select="@name"/>->setData(s_<xsl:value-of select="@name"/>->charrep());
			</xsl:when>
			<xsl:when test="@dbtype='String'">
        UAP(lb_I_String, s_<xsl:value-of select="@name"/>)
        s_<xsl:value-of select="@name"/> = sampleQuery->getAsString("<xsl:value-of select="@name"/>");
        txt<xsl:value-of select="@name"/>->maxLen = strlen(s_<xsl:value-of select="@name"/>->charrep())+50;
        if (txt<xsl:value-of select="@name"/>->data) delete[] txt<xsl:value-of select="@name"/>->data;
        txt<xsl:value-of select="@name"/>->data = new char[txt<xsl:value-of select="@name"/>->maxLen+1+50];
        txt<xsl:value-of select="@name"/>->setData(s_<xsl:value-of select="@name"/>->charrep());
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

	return ERR_NONE;
}

lbErrCodes LB_STDCALL T<xsl:value-of select="$FormularName"/>Dialog::DBUpdate() {
	UAP_REQUEST(getModuleInstance(), lb_I_String, col)
	UAP_REQUEST(getModuleInstance(), lb_I_String, val)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
#ifdef bla
	wxChoice* cbox_<xsl:value-of select="@name"/> = (wxChoice*) w;
				
	int pos_<xsl:value-of select="@name"/> = cbox_<xsl:value-of select="@name"/>->GetSelection();
				
	if (pos_<xsl:value-of select="@name"/> != -1) {
		lbErrCodes err = ERR_NONE;

		UAP_REQUEST(manager.getPtr(), lb_I_Integer, key)
		UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)
					
		cbName-&gt;setData("<xsl:value-of select="@name"/>");
					
		UAP(lb_I_KeyBase, key_cbName)
		UAP(lb_I_Unknown, uk_cbMapper)
		UAP(lb_I_Container, cbMapper)
					
		QI(cbName, lb_I_KeyBase, key_cbName)
			
		uk_cbMapper = ComboboxMapperList-&gt;getElement(&amp;key_cbName);
					
		QI(uk_cbMapper, lb_I_Container, cbMapper)
					
		key-&gt;setData(pos_<xsl:value-of select="@name"/>);

		UAP(lb_I_KeyBase, key_pos)
		QI(key, lb_I_KeyBase, key_pos)
		UAP(lb_I_Unknown, uk_mapping)
		uk_mapping = cbMapper-&gt;getElement(&amp;key_pos);

		if (uk_mapping == NULL)  { 
			if (!sampleQuery-&gt;isNullable("<xsl:value-of select="@name"/>")) {
				if (!meta-&gt;askYesNo(_trans("Failed to save data. Not all fields are filled."))) return ERR_UPDATE_FAILED;
			}
		} else {
			UAP(lb_I_Long, FK_id)
					
			QI(uk_mapping, lb_I_Long, FK_id)
			
			long p = FK_id-&gt;getData();
					
			char pp[20] = "";
						
			sprintf(pp, "%dl", p);
					
			col-&gt;setData("<xsl:value-of select="@name"/>");
			val-&gt;setData(pp);
				
			sampleQuery-&gt;setNull("<xsl:value-of select="@name"/>", false);
			sampleQuery-&gt;setString(*&amp;col, *&amp;val);
		}
	} else {
		if (!sampleQuery-&gt;isNullable("<xsl:value-of select="@name"/>")) {
			if (!meta-&gt;askYesNo(_trans("Failed to save data. Not all fields are filled."))) return ERR_UPDATE_FAILED;
		}
	}
#endif //bla	
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
	// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
	if (!sampleQuery->getReadonly("<xsl:value-of select="@name"/>")) {
		wxCheckBox *check = (wxCheckBox*) w;
		if (cb<xsl:value-of select="@name"/>->mark(0) == TRUE) {
			col->setData("<xsl:value-of select="@name"/>");
			val->setData("true");
	
			sampleQuery->setString(*&amp;col, *&amp;val);
		} else {
			col->setData("<xsl:value-of select="@name"/>");
			val->setData("false");
		
			sampleQuery->setString(*&amp;col, *&amp;val);
		}
	}
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
	if (!sampleQuery->getReadonly("<xsl:value-of select="@name"/>")) {
		col->setData("<xsl:value-of select="@name"/>");
		val->setData(txt<xsl:value-of select="@name"/>->data);

		sampleQuery->setString(*&amp;col, *&amp;val);
	}
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
	if (!sampleQuery->getReadonly("<xsl:value-of select="@name"/>")) {
		col->setData("<xsl:value-of select="@name"/>");
		val->setData(txt<xsl:value-of select="@name"/>->data);

		sampleQuery->setString(*&amp;col, *&amp;val);
	}
			</xsl:when>
			<xsl:when test="@dbtype='String'">
	if (!sampleQuery->getReadonly("<xsl:value-of select="@name"/>")) {
		col->setData("<xsl:value-of select="@name"/>");
		val->setData(txt<xsl:value-of select="@name"/>->data);

		sampleQuery->setString(*&amp;col, *&amp;val);
	}
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

	if (sampleQuery->update() != ERR_NONE) {
/*
		UAP_REQUEST(manager.getPtr(), lb_I_String, newTitle)

		newTitle->setData(formName);
		
		*newTitle += ": Update failed !";

		SetName(newTitle->charrep());
*/
		if (meta->askYesNo("Error while updating data. Would you re - read the current data and retry ?")) {
			DBRead();
		}
		
		_LOG &lt;&lt; "Update a database record in form '<xsl:value-of select="$FormularName"/>' failed." LOG_

		return ERR_UPDATE_FAILED;
	}


	return ERR_NONE;
}


lbErrCodes LB_STDCALL T<xsl:value-of select="$FormularName"/>Dialog::DBFirst(lb_I_Unknown* uk) {
    _LOG &lt;&lt; "T<xsl:value-of select="$FormularName"/>Dialog::DBFirst(lb_I_Unknown* uk) called" LOG_

    DBUpdate();
    sampleQuery->first();
    DBRead();

    return ERR_NONE;
}

lbErrCodes LB_STDCALL T<xsl:value-of select="$FormularName"/>Dialog::DBPrevious(lb_I_Unknown* uk) {
    _LOG &lt;&lt; "T<xsl:value-of select="$FormularName"/>Dialog::DBPrevious(lb_I_Unknown* uk) called" LOG_

    DBUpdate();
    sampleQuery->previous();
    DBRead();

    return ERR_NONE;
}

lbErrCodes LB_STDCALL T<xsl:value-of select="$FormularName"/>Dialog::DBNext(lb_I_Unknown* uk) {
    _LOG &lt;&lt; "T<xsl:value-of select="$FormularName"/>Dialog::DBNext(lb_I_Unknown* uk) called" LOG_

    DBUpdate();
    sampleQuery->next();
    DBRead();

    return ERR_NONE;
}

lbErrCodes LB_STDCALL T<xsl:value-of select="$FormularName"/>Dialog::DBLast(lb_I_Unknown* uk) {
    _LOG &lt;&lt; "T<xsl:value-of select="$FormularName"/>Dialog::DBLast(lb_I_Unknown* uk) called" LOG_

    DBUpdate();
    sampleQuery->last();
    DBRead();

    return ERR_NONE;
}


</xsl:for-each>



<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="FormularID" select="@ID"/>
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID][@isfk='1']">
void T<xsl:value-of select="$FormularName"/>Dialog::fillComboBox_<xsl:value-of select="@name"/>(TStringCollection* choice) {
	// The position in the combo box will be mapped to the key in the ukComboboxMapper_<xsl:value-of select="@name"/> mapping instance.
	int cbox_pos = 0;
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Container, ComboboxMapper_<xsl:value-of select="@name"/>)
	<xsl:variable name="pktable" select="@fktable"/>
	<xsl:variable name="pkey" select="//lbDMF/primarykeys/primarykey[@pktable=$pktable]/@pkcolumn"/>
	char* buffer = "select <xsl:value-of select="@fkname"/>, <xsl:value-of select="$pkey"/> from <xsl:value-of select="@fktable"/> order by <xsl:value-of select="$pkey"/>";

	if (database == NULL) {
		REQUEST(manager.getPtr(), lb_I_Database, database)

		database->init();
		if (database->connect("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 
							  "<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", "<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBUser'][@applicationid=$ApplicationID]/@value"/>", "<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBPass'][@applicationid=$ApplicationID]/@value"/>") != ERR_NONE) {
			_LOG &lt;&lt; "Error: Could not connect to given database: '" &lt;&lt; _DBName->charrep() &lt;&lt; "'" LOG_

			return;
		}
	}
	
	UAP(lb_I_Query, q)
	
	q = database-&gt;getQuery("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 0);

	if (q-&gt;query(buffer) == ERR_NONE) {
		int cb_pos = 0;
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, IKey)
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_String, data)
		UAP(lb_I_String, SKey)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Long, possibleKey)


		// key instance for the integer combobox position
		QI(IKey, lb_I_KeyBase, key)

		choice-&gt;removeAll();
	
		err = q-&gt;first();
	
		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			data = q-&gt;getAsString(1);

			if (data->charrep() == NULL) *data = "&lt;empty&gt;";
			if (*data == "") *data = "&lt;empty&gt;";

			possibleKey = q-&gt;getAsLong(2);
			// uk instance for the foreign key value
			QI(possibleKey, lb_I_Unknown, uk)

			IKey-&gt;setData(cb_pos);
			ComboboxMapper_<xsl:value-of select="@name"/>-&gt;insert(&amp;uk, &amp;key);
			cb_pos++;
			
			choice-&gt;insert(newStr(data->charrep()));

			err = q-&gt;next();

			while (err == ERR_NONE) {
				data = q-&gt;getAsString(1);

				if (data->charrep() == NULL) *data = "&lt;empty&gt;";
				if (*data == "") *data = "&lt;empty&gt;";

				possibleKey = q-&gt;getAsLong(2);
				// uk instance for the foreign key value
				QI(possibleKey, lb_I_Unknown, uk)
				
				IKey->setData(cb_pos);
				ComboboxMapper_<xsl:value-of select="@name"/>-&gt;insert(&amp;uk, &amp;key);
				cb_pos++;
				
				choice-&gt;insert(newStr(data->charrep()));
				err = q-&gt;next();
			}

			if (err == WARN_DB_NODATA) {
				data = q-&gt;getAsString(1);

				if (data->charrep() == NULL) *data = "&lt;empty&gt;";
				if (*data == "") *data = "&lt;empty&gt;";

				possibleKey = q-&gt;getAsLong(2);
				// uk instance for the foreign key value
				QI(possibleKey, lb_I_Unknown, uk)
				
				IKey->setData(cb_pos);
				ComboboxMapper_<xsl:value-of select="@name"/>-&gt;insert(&amp;uk, &amp;key);
				cb_pos++;
				
				choice-&gt;insert(newStr(data->charrep()));
			}
		} 
	}
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, mapperName)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	QI(mapperName, lb_I_KeyBase, key)
	QI(ComboboxMapper_<xsl:value-of select="@name"/>, lb_I_Unknown, uk)
	
	*mapperName = "<xsl:value-of select="@name"/>";
	
	if (ComboboxMapperList->exists(&amp;key) == 1) {
		ComboboxMapperList->remove(&amp;key);
	}
	
	ComboboxMapperList->insert(&amp;uk, &amp;key);
}
</xsl:for-each>


TDialog * T<xsl:value-of select="$FormularName"/>Dialog::buildDialog<xsl:value-of select="$FormularName"/>(lb_I_EventManager* eman, lb_I_Dispatcher* disp)
{
   //TScrollBar * sb1, * sb2;
   int dialogheight = 5 <xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">+ 2 </xsl:for-each>;
   int line = 2;
   int width = 20;
   int offsetlabel = 2;
   int offsetcontrol = 22;

    UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

   if (database == NULL) {
       REQUEST(getModuleInstance(), lb_I_Database, database)
   }

	if (_DBName == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, _DBName)
		_DBName->setData("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>");
	}
	if (_DBUser == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, _DBUser)
		_DBUser->setData("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBUser'][@applicationid=$ApplicationID]/@value"/>");
	}
	if (_DBPass == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, _DBPass)
		_DBPass->setData("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBPass'][@applicationid=$ApplicationID]/@value"/>");
	}

	database->init();

	if (database->connect("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 
						"<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 
	"<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBUser'][@applicationid=$ApplicationID]/@value"/>", "<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBPass'][@applicationid=$ApplicationID]/@value"/>") != ERR_NONE) {
		_LOG &lt;&lt; "Error: Could not connect to given database: '" &lt;&lt; _DBName->charrep() &lt;&lt; "'" LOG_

		return NULL;
	}

	sampleQuery = database->getQuery("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 0);
	sampleQuery-&gt;enableFKCollecting();

	sampleQuery-&gt;setAutoRefresh(meta->getAutorefreshData());

	if (SQLString == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SQLString)
		
<xsl:variable name="tempQuery" select="//lbDMF/formularparameter/parameter[@formularid=$FormularID][@name='query']/@value"/>
<xsl:variable name="Query">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempQuery"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'&quot;'"/>
		<xsl:with-param name="substringOut" select="'\&quot;'"/>
	</xsl:call-template>
</xsl:variable>
		
		SQLString->setData("<xsl:value-of select="$Query"/>");
	}

	sampleQuery->query(SQLString->charrep(), false);

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:for-each select="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@readonly='1']">
	sampleQuery->setReadonly("<xsl:value-of select="@name"/>"); // <xsl:value-of select="@tablename"/>
</xsl:for-each>
</xsl:for-each>

	sampleQuery-&gt;bind();

	sampleQuery-&gt;first();


   TDialog * d = new TDialog( TRect( 0, 0, offsetlabel+width+offsetcontrol+2, dialogheight ), "<xsl:value-of select="$FormularName"/>" );


<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
   TInputLine *tv<xsl:value-of select="@name"/>;
   TStringCollection *list<xsl:value-of select="@name"/>;
   list<xsl:value-of select="@name"/> = new TStringCollection(5,2);

   fillComboBox_<xsl:value-of select="@name"/>(list<xsl:value-of select="@name"/>);

   tv<xsl:value-of select="@name"/> = new TStaticInputLine(TRect(offsetcontrol, line, offsetcontrol+width, line+1), 128, list<xsl:value-of select="@name"/>);
   d->insert(tv<xsl:value-of select="@name"/>);
   TView* input<xsl:value-of select="@name"/> = new TComboBox(TRect(offsetcontrol+width, line, offsetcontrol+width+1, line+1), tv<xsl:value-of select="@name"/>, list<xsl:value-of select="@name"/>);
   d->insert(input<xsl:value-of select="@name"/>);
   d->insert(new TLabel( TRect(offsetlabel, line, offsetlabel+width, line+1), "<xsl:value-of select="@name"/>", input<xsl:value-of select="@name"/> ));


	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
   TView* input<xsl:value-of select="@name"/> = cb<xsl:value-of select="@name"/> = new TCheckBoxes( TRect(offsetlabel, line, offsetcontrol+width, line+1),
            new TSItem( "<xsl:value-of select="@name"/>", 0));
   d->insert( input<xsl:value-of select="@name"/> );
   //d->insert( new TLabel( TRect(offsetlabel, line, offsetlabel+width, line+1), "<xsl:value-of select="@name"/>", b ));
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
   TView* input<xsl:value-of select="@name"/>;
   txt<xsl:value-of select="@name"/> = new TInputLine( TRect(offsetcontrol, line, offsetcontrol+width, line+1 ), 20 );
   input<xsl:value-of select="@name"/> = (TView*) txt<xsl:value-of select="@name"/>;
   d->insert( input<xsl:value-of select="@name"/> );
   d->insert( new TLabel( TRect(offsetlabel, line, offsetlabel+width, line+1), "<xsl:value-of select="@name"/>", input<xsl:value-of select="@name"/> ));
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
   TView* input<xsl:value-of select="@name"/>;
   txt<xsl:value-of select="@name"/> = new TInputLine( TRect(offsetcontrol, line, offsetcontrol+width, line+1 ), 20 );
   input<xsl:value-of select="@name"/> = (TView*) txt<xsl:value-of select="@name"/>;
   d->insert( input<xsl:value-of select="@name"/> );
   d->insert( new TLabel( TRect(offsetlabel, line, offsetlabel+width, line+1), "<xsl:value-of select="@name"/>", input<xsl:value-of select="@name"/> ));
			</xsl:when>
			<xsl:when test="@dbtype='String'">
   TView* input<xsl:value-of select="@name"/>;
   txt<xsl:value-of select="@name"/> = new TInputLine( TRect(offsetcontrol, line, offsetcontrol+width, line+1 ), 50 );
   input<xsl:value-of select="@name"/> = (TView*) txt<xsl:value-of select="@name"/>;
   d->insert( input<xsl:value-of select="@name"/> );
   d->insert( new TLabel( TRect(offsetlabel, line, offsetlabel+width, line+1), "<xsl:value-of select="@name"/>", input<xsl:value-of select="@name"/> ));
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
   line += 2;
</xsl:for-each>

    char eventName[100] = "";
    int _DBFirst;
    int _DBPrevious;
    int _DBNext;
    int _DBLast;

    sprintf(eventName, "%pDBFirst", this);
	eman->registerEvent(eventName, _DBFirst);
	
    sprintf(eventName, "%pDBPrevious", this);
	eman->registerEvent(eventName, _DBPrevious);
	
    sprintf(eventName, "%pDBNext", this);
	eman->registerEvent(eventName, _DBNext);
	
    sprintf(eventName, "%pDBLast", this);
	eman->registerEvent(eventName, _DBLast);

    registerEventHandler(disp);


   d->insert( new TButton( TRect( offsetlabel, line, offsetlabel+10, line+2 ), "~F~irst", _DBFirst, bfNormal ) );
   offsetlabel+=10;
   d->insert( new TButton( TRect( offsetlabel, line, offsetlabel+10, line+2 ), "~P~rev", _DBPrevious, bfNormal ) );
   offsetlabel+=10;
   d->insert( new TButton( TRect( offsetlabel, line, offsetlabel+10, line+2 ), "~N~ext", _DBNext, bfNormal ) );
   offsetlabel+=10;
   d->insert( new TButton( TRect( offsetlabel, line, offsetlabel+10, line+2 ), "~L~ast", _DBLast, bfNormal ) );

   d->selectNext(True);
   
   	if (sampleQuery-&gt;dataFetched()) {
		sampleQuery-&gt;first();
		DBRead();
	} else {
		//nextButton-&gt;Disable();
		//lastButton-&gt;Disable();
		//deleteButton-&gt;Disable();
	}

   return d;
}

void T<xsl:value-of select="$ApplicationName"/>::show<xsl:value-of select="$FormularName"/>() {
    T<xsl:value-of select="$FormularName"/>Dialog* dlg = new T<xsl:value-of select="$FormularName"/>Dialog();
    dlg->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
    TDialog* dlg<xsl:value-of select="$FormularName"/> = dlg->buildDialog<xsl:value-of select="$FormularName"/>(*&amp;eman, *&amp;dispatcher);

    if(dlg<xsl:value-of select="$FormularName"/> != NULL)
    {
        dlg<xsl:value-of select="$FormularName"/>->helpCtx = hc<xsl:value-of select="$FormularName"/>;
        deskTop->insert( dlg<xsl:value-of select="$FormularName"/> );
    }
}

</xsl:for-each>

</exsl:document>
</xsl:template>
</xsl:stylesheet>

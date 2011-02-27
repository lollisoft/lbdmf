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
#ifdef WINDOWS
#include &lt;windows.h&gt;
#include &lt;io.h&gt;
#endif

#ifdef __cplusplus
extern "C" {
#endif


//#include &lt;conio.h&gt;

#ifdef __WATCOMC__
#include &lt;ctype.h&gt;
#endif
#ifdef __cplusplus
}
#endif

#include &lt;stdio.h&gt;
#ifndef OSX
#include &lt;malloc.h&gt;
#endif
#ifdef OSX
#include &lt;sys/malloc.h&gt;
#endif

#include &lt;lbConfigHook.h&gt;
#include &lt;lbInterfaces.h&gt;

#undef DLLEXPORT

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif
#ifdef LINUX 
#define DLLEXPORT
#endif
</xsl:template>

<xsl:template name="createMakeFileModule_DataViewModelApplicationModul">
<exsl:document href="{$basedir}/{$pluginsdir}/{$ApplicationName}/makefile.module" method="text">
# Define your module based settings

#    DMF Distributed Multiplatform Framework (the initial goal of this DataViewModellibrary)
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
MOD_INCL=$(STD_INCL) -I $(DEVROOT)$(RELPATH)/vendor/wxaui-0.9.1/include
OBJDEP=
C_SOOPS_WX = -DUNIX -DLINUX -DLB_I_EXTENTIONS `wx-config --cxxflags`
C_SOOPS= $(C_SOOPS_WX)
VENDORLIBS=-L$(prefix)/lib -llbHook 
L_OPS=$(L_SOOPS) `wx-config --inplace --libs` 
endif    

ifeq ($(OSTYPE), linux-debian-ppc)
MOD_INCL=$(STD_INCL) -I $(DEVROOT)$(RELPATH)/vendor/wxaui-0.9.1/include
OBJDEP=
C_SOOPS_WX = -DUNIX -DLINUX -DLB_I_EXTENTIONS `wx-config --cxxflags`
C_SOOPS= $(C_SOOPS_WX)
VENDORLIBS=-L$(prefix)/lib -llbHook -lwxAUI
L_OPS=$(L_SOOPS) `wx-config --inplace --libs` 
endif    

ifeq ($(LB_USE_FRAMEWORKS), yes)

ifeq ($(OSTYPE), osx)
MOD_INCL=$(STD_INCL)
OBJDEP=
C_SOOPS_WX = -g -DOSX -DUNIX -DLINUX -DLB_I_EXTENTIONS `wx-config --inplace --cxxflags` 
C_SOOPS= $(C_SOOPS_WX)
VENDORLIBS=-lc /usr/lib/libgcc_s.1.dylib -lc /usr/lib/libstdc++.6.dylib
L_OPS=$(L_SOOPS) -F$(prefix)/Library/Frameworks -framework lbHook `wx-config --inplace --libs` 
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

<xsl:template name="createMakeFileModule_DataViewModelModul">

<exsl:document href="{$basedir}/{$appexecutedir}/{$ApplicationName}_AppExecutable/makefile.module" method="text">
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

ifeq ($(OSTYPE), linux-debian-ppc)
MOD_INCL=$(STD_INCL) -I $(DEVROOT)$(RELPATH)/vendor/propgrid/include -I ../wxWrapperDLL -I $(DEVROOT)$(RELPATH)/vendor/wxaui-0.9.1/include
OBJDEP=

C_ELFOPS += `wx-config --inplace --cxxflags` -DUSE_WXWRAPPER_DLL -DUNIX -DLINUX -DLB_I_EXTENTIONS
L_OPS = `wx-config --inplace --libs` -o

VENDORLIBS=-L$(prefix)/lib -llbHook -lwxAUI
endif    

ifeq ($(LB_USE_FRAMEWORKS), yes)

ifeq ($(OSTYPE), osx)
MOD_INCL=$(STD_INCL) -I $(DEVROOT)$(RELPATH)/vendor/propgrid/include -I ../wxWrapperDLL
OBJDEP=
C_ELFOPS += `wx-config --inplace --cxxflags` -DWXUSINGDLL -DUSE_WXWRAPPER_DLL -DOSX -DUNIX -DLINUX -DLB_I_EXTENTIONS

ifeq ($(OSNAME), Panther)
AUIFRAMEWORK=-framework wxAUI
else
AUIFRAMEWORK=
endif

ifeq ($(DEBUG), yes)
C_ELFOPS +=  -D__WXDEBUG__
L_OPS = -L. -F$(prefix)/Library/Frameworks -framework lbHook `wx-config --inplace --libs`  -lc /usr/lib/libgcc_s.1.dylib -lc /usr/lib/libstdc++.6.dylib -bind_at_load -o
endif

ifeq ($(DEBUG), no)
L_OPS = -L. -F$(prefix)/Library/Frameworks -framework lbHook `wx-config --inplace --libs`  -lc /usr/lib/libgcc_s.1.dylib -lc /usr/lib/libstdc++.6.dylib -o
endif
VENDORLIBS=
endif

endif

ifeq ($(LB_USE_FRAMEWORKS), no)

ifeq ($(OSTYPE), osx)
MOD_INCL=$(STD_INCL) -I ../wxWrapperDLL
OBJDEP=
C_ELFOPS += -L. `wx-config --inplace --cxxflags` -DUSE_WXWRAPPER_DLL -DOSX -DUNIX -DLINUX -DLB_I_EXTENTIONS

ifeq ($(DEBUG), yes)
C_ELFOPS +=  -D__WXDEBUG__
endif

L_OPS = -lstdc++ -L. `wx-config --inplace --libs` -o
VENDORLIBS=$(HOME)/lib/lbHook.so $(HOME)/lib/wxWrapperDLL.so $(HOME)/lib/wxAUI.so 
endif

endif
</exsl:document>
</xsl:template>

<xsl:template name="createApplicationHeader">
		<xsl:param name="ApplicationID"/>

<exsl:document href="{$basedir}/{$appexecutedir}/{$ApplicationName}_AppExecutable/{$ApplicationName}.h" method="text">
/* This file is autogenerated. Please do not modify. It would be overwritten.
 */

#ifndef _LB_APP_
#define _LB_APP_

#include &lt;stdio.h&gt;
#include &lt;lbInterfaces.h&gt;

//WX_DECLARE_LIST(wxDateTime,wxArrayDate);


#endif //_LB_APP_
</exsl:document>
</xsl:template>

<xsl:template name="createApplicationModule">
		<xsl:param name="ApplicationID"/>
		
<exsl:document href="{$basedir}/{$appexecutedir}/{$ApplicationName}_AppExecutable/{$ApplicationName}.cpp" method="text">
/* This file is autogenerated. Please do not modify. It would be overwritten.
 */

#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#ifndef UNIX
#include &lt;windows.h&gt;
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {      
#endif            

#include &lt;conio.h&gt;

#ifdef __cplusplus
}      
#endif            

#endif
#include &lt;lbConfigHook.h&gt;

#define LB_DYNAPP_DLL
#include &lt;lbdynapp-module.h&gt;

#include &lt;<xsl:value-of select="$ApplicationName"/>.h&gt;

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include &lt;wx/dataview.h&gt;

//#include &lt;wx/listimpl.cpp&gt;
//WX_DEFINE_LIST(wxArrayDate)

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
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
#include &lt;<xsl:value-of select="$ApplicationName"/><xsl:value-of select="$FormularName"/>Implementation.h&gt;
</xsl:for-each>

#include &lt;wx/notebook.h&gt;

#ifndef OSX
#define wxAuiPaneInfo wxPaneInfo
#define wxAuiManager wxFrameManager
#include &lt;manager.h&gt;
#endif

#ifdef OSX
 #ifdef USE_WXAUI
  #ifdef OSVERSION_Panther
   #define wxAuiPaneInfo wxPaneInfo
   #define wxAuiManager wxFrameManager
   #include &lt;manager.h&gt;
  #else
   #include &lt;wx/aui/aui.h&gt;
  #endif
 #endif
#endif


// -------------------------------------
// MyApp
// -------------------------------------

class MyApp: public wxApp
{
public:
    bool OnInit(void);
    int  OnExit(void);
};


enum my_events
{
    ID_APPEND_ROW_LEFT = 1000,
    ID_PREPEND_ROW_LEFT,
    ID_INSERT_ROW_LEFT,
    ID_DELETE_ROW_LEFT,
    ID_EDIT_ROW_LEFT,
    
    ID_SELECT,
    ID_UNSELECT_ALL,

    ID_APPEND_ROW_RIGHT,
    ID_PREPEND_ROW_RIGHT,
    ID_INSERT_ROW_RIGHT,
    ID_DELETE_ROW_RIGHT,
    ID_EDIT_ROW_RIGHT,
    
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
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
    ID_<xsl:value-of select="$FormularName"/>,
</xsl:for-each>


    ID_DATABASE_BACKEND,
    ID_SORTED,
    ID_UNSORTED,
    ID_ACTIVATED,
    DYNAMIC_ABOUT,
    DYNAMIC_QUIT

    
};

class MyFrame: public wxFrame
{
public:
    MyFrame(wxFrame *frame, wxChar *title, int x, int y, int w, int h);
    virtual ~MyFrame();


public:
    void OnQuit(wxCommandEvent&amp; event);
    void OnAbout(wxCommandEvent&amp; event);
    void OnSize(wxSizeEvent&amp; event);

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
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
	/**
	 * \brief Create a formular for <xsl:value-of select="$FormularName"/> data model
	 */
	void OnShow<xsl:value-of select="$FormularName"/>(wxCommandEvent&amp; event);
</xsl:for-each>
	void OnToggleDatabaseBackend(wxCommandEvent&amp; event);

private:

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
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
	/**
	 * \brief Create a formular for <xsl:value-of select="$FormularName"/> data model
	 */
	<xsl:value-of select="$FormularName"/>* my<xsl:value-of select="$FormularName"/>;
	wxDataViewCtrl* dataview_<xsl:value-of select="$FormularName"/>;
</xsl:for-each>

	DECLARE_EVENT_TABLE()

    wxBoxSizer *sizerMain;
    bool _backend_plugin;
    wxNotebook* notebook;

    wxAuiManager m_mgr;
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_SIZE(MyFrame::OnSize)
END_EVENT_TABLE()


MyFrame::~MyFrame() {
        // deinitialize the frame manager
        m_mgr.UnInit();
}

MyFrame::MyFrame(wxFrame *frame, wxChar *title, int x, int y, int w, int h):
  wxFrame(frame, wxID_ANY, title, wxPoint(x, y), wxSize(w, h))
{
    //SetIcon(wxICON(sample));
    _backend_plugin = false;
    notebook = NULL;

    wxMenu *file_menu = new wxMenu;

    m_mgr.SetFrame(this);

    SetMinSize(wxSize(w, h));

    file_menu->Append(DYNAMIC_ABOUT, _T("&amp;About"));
    file_menu->Append(DYNAMIC_QUIT, _T("E&amp;xit"));
    file_menu->Append(ID_DATABASE_BACKEND, _T("Database backend"));
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
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
    file_menu->Append(ID_<xsl:value-of select="$FormularName"/>, _T("open <xsl:value-of select="$FormularName"/>"));
</xsl:for-each>

    wxMenuBar *menu_bar = new wxMenuBar;
    menu_bar->Append(file_menu, _T("&amp;File"));
    SetMenuBar(menu_bar);

    // You used to have to do some casting for param 4, but now there are type-safe handlers
    Connect( DYNAMIC_QUIT,  wxID_ANY,
                    wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnQuit) );
    Connect( DYNAMIC_ABOUT, wxID_ANY,
                    wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnAbout) );
    Connect( ID_DATABASE_BACKEND, wxID_ANY,
                    wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnToggleDatabaseBackend) );



<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
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
    Connect( ID_<xsl:value-of select="$FormularName"/>,  wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnShow<xsl:value-of select="$FormularName"/>) );
</xsl:for-each>


    UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
    PM->initialize();


    CreateStatusBar();

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
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
    dataview_<xsl:value-of select="$FormularName"/> = NULL;
</xsl:for-each>
}

void MyFrame::OnToggleDatabaseBackend(wxCommandEvent&amp; event) {
	_backend_plugin = !_backend_plugin;
}


void MyFrame::OnQuit(wxCommandEvent&amp; WXUNUSED(event) )
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent&amp; WXUNUSED(event) )
{
    wxMessageDialog dialog(this, _T("This is the generated application of <xsl:value-of select="$ApplicationName"/>"),
        _T("About <xsl:value-of select="$ApplicationName"/>"), wxOK);

    dialog.ShowModal();
}

void MyFrame::OnSize(wxSizeEvent&amp; event)
{
    // The event seemsnot to be triggered.
    SetMinSize(event.GetSize());

#ifdef SOLARIS
#ifdef bla
        if (skipfirstResizeEvent == false) {
                m_mgr.Update();
                event.Skip();
        }
        skipfirstResizeEvent = false;
#endif
#endif
#ifndef SOLARIS
        m_mgr.Update();
        event.Skip();
#endif

}


<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
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
<xsl:variable name="tempEventName" select="@eventname"/>
<xsl:variable name="EventName">
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
void MyFrame::OnShow<xsl:value-of select="$FormularName"/>(wxCommandEvent&amp; event) {
    if (!notebook) {
        notebook = new wxNotebook(this, -1);
        sizerMain = new wxBoxSizer(wxVERTICAL);

        SetAutoLayout(TRUE);
        notebook->SetAutoLayout(TRUE);

        sizerMain->Add(notebook, 1, wxEXPAND | wxALL, 0);

        SetSizer(sizerMain);
        m_mgr.AddPane(notebook,   wxCENTER, wxT("Workplace"));
        m_mgr.Update();
    }

    if (dataview_<xsl:value-of select="$FormularName"/>) {
        int num = notebook->GetPageCount();
        for (int i = 0; i &lt; num; i++) {
            if (strncmp(notebook-&gt;GetPageText(i).c_str(), "<xsl:value-of select="$FormularName"/>", strlen("<xsl:value-of select="$FormularName"/>")) == 0) {
                notebook-&gt;DeletePage(i);
                break; // Bug: The num variable is not updated and will produce an index out of range error.
            }
        }
    }	

    // Left wxDataViewCtrl
    dataview_<xsl:value-of select="$FormularName"/> = new wxDataViewCtrl( notebook, wxID_ANY );

    <xsl:value-of select="$FormularName"/> *model = new <xsl:value-of select="$FormularName"/>;
    model->SetBackend(_backend_plugin);
    model->InitModel();
    dataview_<xsl:value-of select="$FormularName"/>-&gt;AssociateModel( model );

    int column = 0;
	<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
	<xsl:variable name="FieldName" select="@name"/> 
	<xsl:variable name="TableName" select="@tablename"/>
	<xsl:choose>
	<xsl:when test="@isfk='1'">
    wxDataViewTextRenderer *text_renderer<xsl:value-of select="@name"/> = new wxDataViewTextRenderer( wxT("string"), wxDATAVIEW_CELL_EDITABLE );
    wxDataViewColumn *thecolumn<xsl:value-of select="@name"/> = new wxDataViewColumn( wxT("<xsl:value-of select="@name"/>"), text_renderer<xsl:value-of select="@name"/>, column );
    dataview_<xsl:value-of select="$FormularName"/>-&gt;AppendColumn( thecolumn<xsl:value-of select="@name"/> );
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
    wxDataViewTextRenderer *text_renderer<xsl:value-of select="@name"/> = new wxDataViewTextRenderer( wxT("string"), wxDATAVIEW_CELL_EDITABLE );
    wxDataViewColumn *thecolumn<xsl:value-of select="@name"/> = new wxDataViewColumn( wxT("<xsl:value-of select="@name"/>"), text_renderer<xsl:value-of select="@name"/>, column );
    dataview_<xsl:value-of select="$FormularName"/>-&gt;AppendColumn( thecolumn<xsl:value-of select="@name"/> );
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
    dataview_<xsl:value-of select="$FormularName"/>-&gt;AppendToggleColumn( wxT("<xsl:value-of select="@name"/>"), column );
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
    wxDataViewTextRenderer *text_renderer<xsl:value-of select="@name"/> = new wxDataViewTextRenderer( wxT("string"), wxDATAVIEW_CELL_EDITABLE );
    wxDataViewColumn *thecolumn<xsl:value-of select="@name"/> = new wxDataViewColumn( wxT("<xsl:value-of select="@name"/>"), text_renderer<xsl:value-of select="@name"/>, column );
    dataview_left-&gt;AppendColumn( thecolumn<xsl:value-of select="@name"/> );
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
    wxDataViewTextRenderer *text_renderer<xsl:value-of select="@name"/> = new wxDataViewTextRenderer( wxT("long"), wxDATAVIEW_CELL_EDITABLE );
    wxDataViewColumn *thecolumn<xsl:value-of select="@name"/> = new wxDataViewColumn( wxT("<xsl:value-of select="@name"/>"), text_renderer<xsl:value-of select="@name"/>, column );
    dataview_<xsl:value-of select="$FormularName"/>-&gt;AppendColumn( thecolumn<xsl:value-of select="@name"/> );
			</xsl:when>
			<xsl:when test="@dbtype='String'">
    wxDataViewTextRenderer *text_renderer<xsl:value-of select="@name"/> = new wxDataViewTextRenderer( wxT("string"), wxDATAVIEW_CELL_EDITABLE );
    wxDataViewColumn *thecolumn<xsl:value-of select="@name"/> = new wxDataViewColumn( wxT("<xsl:value-of select="@name"/>"), text_renderer<xsl:value-of select="@name"/>, column );
    dataview_<xsl:value-of select="$FormularName"/>-&gt;AppendColumn( thecolumn<xsl:value-of select="@name"/> );
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
	</xsl:choose>
	column++;
	</xsl:for-each>



    // layout dataview controls.

    notebook->AddPage(dataview_<xsl:value-of select="$FormularName"/>, "<xsl:value-of select="$FormularName"/>", true);

    m_mgr.Update();

    Fit();
}
</xsl:for-each>

IMPLEMENT_APP  (MyApp)

bool MyApp::OnInit(void)
{
    MyFrame *frame = new MyFrame(NULL, wxT("<xsl:value-of select="$ApplicationName"/>"), 10, 10, 800, 340);
    frame->Show(true);

    SetTopWindow(frame);
    
    return true;
}

int MyApp::OnExit(void) {
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	PM->unload();
	unHookAll();
}

</exsl:document>
</xsl:template>
</xsl:stylesheet>

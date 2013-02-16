<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" xmlns:lbDMF="http:///schemas/lbDMF/1"  xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
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
<xsl:import href="../include/exsl.xsl"/>
<xsl:output method="text" indent="no"/>

<xsl:variable name="ApplicationID" select="//lbDMF/@applicationid"/>
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

<!-- here is the template that does the replacement -->
<xsl:template name="SubstringReplace">
	<xsl:param name="stringIn"/>
	<xsl:param name="substringIn"/>
	<xsl:param name="substringOut"/>
	<xsl:choose>
		<xsl:when test="contains($stringIn,$substringIn)">
			<xsl:value-of select="concat(substring-before($stringIn,$substringIn),$substringOut)"/>
			<xsl:call-template name="SubstringReplace">
				<xsl:with-param name="stringIn" select="substring-after($stringIn,$substringIn)"/>
				<xsl:with-param name="substringIn" select="$substringIn"/>
				<xsl:with-param name="substringOut" select="$substringOut"/>
			</xsl:call-template>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="$stringIn"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<!-- This template creates a pair of files per formular name -->
<xsl:template name="ProxyMakefileModule">
	<xsl:param name="ApplicationName"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/># Define your module based settings

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
MOD_INCL_MINGW=$(STD_INCL_MINGW) \
	-I$(DEVROOT_MAKE)/Projects/CPP/AppDevelopment/Interfaces \
	-I$(DEVROOT_MAKE)/Projects/CPP/AppDevelopment/DynamicApp/Code/Targets/lbDMF/Interfaces \
	-I$(DEVROOT_MAKE)/Projects/CPP/AppDevelopment/DynamicApp/Code/Targets/lbDMF/Interfaces/<xsl:value-of select="$ApplicationName"/> \
	-I$(DEVROOT_MAKE)$(RELPATH_MAKE)/BaseDevelopment/lbcs
MOD_INCL_MINGW_CPP=$(STD_INCL_MINGW_CPP) \
	-I$(DEVROOT_MAKE)/Projects/CPP/AppDevelopment/Interfaces \
	-I$(DEVROOT_MAKE)/Projects/CPP/AppDevelopment/DynamicApp/Code/Targets/lbDMF/Interfaces \
	-I$(DEVROOT_MAKE)/Projects/CPP/AppDevelopment/DynamicApp/Code/Targets/lbDMF/Interfaces/<xsl:value-of select="$ApplicationName"/> \
	-I$(DEVROOT_MAKE)$(RELPATH_MAKE)/BaseDevelopment/lbcs

OBJDEP=
SLASH=/
WATCOMLIBS=$(DEVROOT_MAKE)$(SLASH)Tools$(SLASH)watcom$(SLASH)lib386$(SLASH)nt
wxBase=$(DEVROOT_MAKE)$(SLASH)wxwin$(SLASH)wx$(SLASH)lib
LIBS = $(BASE_LIBS) $(DEVROOT_MAKE)$(SLASH)projects$(SLASH)dll$(SLASH)libs$(SLASH)lbhook.lib
#	$(wxBase)$(SLASH)wat_dll$(SLASH)wxmsw26$(WX_DEBUG).lib
	
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
MOD_INCL=$(STD_INCL) -i=$(DEVROOT_MAKE)\\wxwin\\wx\\include -i=$(DEVROOT_MAKE)\\Projects\\CPP\\BaseDevelopment\\lbcs -i=$(DEVROOT_MAKE)\\Projects\\CPP\\ServerPlugins\\ApplicationBus -I=$(DEVROOT)\\Projects\\CPP\\AppDevelopment\\Interfaces
MOD_INCL_CPP=$(STD_INCL_CPP) -i=$(DEVROOT_MAKE)/wxwin/wx/include -i=$(DEVROOT_MAKE)$(RELPATH)/BaseDevelopment/lbcs -i=$(DEVROOT_MAKE)$(RELPATH)/ServerPlugins/ApplicationBus -I=$(DEVROOT_MAKE)$(RELPATH)/AppDevelopment/Interfaces

C_EXEOPS= $(C_EXEOPS_WATCOM$(MODE)) /D__WIN32__ /DWINVER=0x0400 /D__WINDOWS95__ \
		/D__WINDOWS__ /D__WXMSW__ /DLB_I_EXTENTIONS
		
C_DLLOPS= $(C_DLLOPS_WATCOM$(MODE)) /D__WIN32__ /DWINVER=0x0400 /D__WINDOWS95__ \
		/D__WINDOWS__ /D__WXMSW__ /DLB_I_EXTENTIONS /D_WINDLL /DWXUSINGDLL

CPP_EXEOPS= $(CPP_EXEOPS_WATCOM$(MODE)) /D__WIN32__ /DWINVER=0x0400 /D__WINDOWS95__ \
		/D__WINDOWS__ /D__WXMSW__ /DLB_I_EXTENTIONS
		
CPP_DLLOPS= $(CPP_DLLOPS_WATCOM$(MODE)) /D__WIN32__ /DWINVER=0x0400 /D__WINDOWS95__ \
		/D__WINDOWS__ /D__WXMSW__ /DLB_I_EXTENTIONS /D_WINDLL /DWXUSINGDLL

ifeq ($MODE), _DEBUG)
C_EXEOPS+= /D__WXDEBUG__
C_DLLOPS+= /D__WXDEBUG__
CPP_EXEOPS+= /D__WXDEBUG__
CPP_DLLOPS+= /D__WXDEBUG__
endif
		
LINKFLAGS = $(L_EXEOPS)
endif

endif

ifeq ($(OSTYPE), linux)
MOD_INCL=$(STD_INCL) -I $(DEVROOT)$(RELPATH)/AppDevelopment/Interfaces -I $(DEVROOT)$(RELPATH)/BaseDevelopment/lbcs
OBJDEP=
C_SOOPS_WX = -DUNIX -DLINUX -DLB_I_EXTENTIONS `wx-config --cxxflags`
C_SOOPS= $(C_SOOPS_WX)
VENDORLIBS=-L$(prefix)/lib -llbHook 
L_OPS=$(L_SOOPS) `wx-config --inplace --libs` 
endif

ifeq ($(LB_USE_FRAMEWORKS), yes)

ifeq ($(OSTYPE), osx)
MOD_INCL=$(STD_INCL) \
        -I $(DEVROOT)$(RELPATH)/AppDevelopment/Interfaces \
        -I $(DEVROOT)$(RELPATH)/AppDevelopment/DynamicApp/Code/Targets/lbDMF/Interfaces \
        -I $(DEVROOT)$(RELPATH)/AppDevelopment/DynamicApp/Code/Targets/lbDMF/Interfaces/<xsl:value-of select="$ApplicationName"/> \
        -I $(DEVROOT)$(RELPATH)/BaseDevelopment/lbcs

OBJDEP=
C_SOOPS_WX = -DOSX -DUNIX -DLINUX -DLB_I_EXTENTIONS `wx-config --inplace --cxxflags` 
C_SOOPS= $(C_SOOPS_WX)
VENDORLIBS=
LIBS=-F$(prefix)/Library/Frameworks -framework lbHook
endif    

endif

ifeq ($(LB_USE_FRAMEWORKS), no)

ifeq ($(OSTYPE), osx)
MOD_INCL=$(STD_INCL)
OBJDEP=
C_SOOPS_WX = -DOSX -DUNIX -DLINUX -DLB_I_EXTENTIONS `wx-config --inplace --cxxflags` 
C_SOOPS= $(C_SOOPS_WX)
VENDORLIBS=$(HOME)/lib/lbHook.so 
L_OPS=$(L_SOOPS) `wx-config --inplace --libs`
endif    

endif
</xsl:template>
</xsl:stylesheet>

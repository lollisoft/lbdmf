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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
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
#            Rosmarinstr. 3
#
#            40235 Duesseldorf (germany)

ifeq ($(OSTYPE), Windows_NT)
MOD_INCL=$(STD_INCL)
MOD_INCL_CPP=$(STD_INCL_CPP)
OBJDEP=
SLASH=/
WATCOMLIBS=$(DEVROOT_MAKE)$(SLASH)Tools$(SLASH)watcom$(SLASH)lib386$(SLASH)nt
wxBase=$(DEVROOT_MAKE)$(SLASH)wxwin$(SLASH)wx$(SLASH)lib
LIBS = $(BASE_LIBS) $(DEVROOT_MAKE)$(SLASH)projects$(SLASH)dll$(SLASH)libs$(SLASH)lbhook.lib, \
	$(DEVROOT_MAKE)$(SLASH)projects$(SLASH)dll$(SLASH)libs$(SLASH)wxWrapperDLL.lib, \
	$(wxBase)$(SLASH)wat_dll$(SLASH)wxmsw26$(WX_DEBUG).lib
	
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
#            Heinrich-Scheufelen-Platz 2
#
#            73252 Lenningen (germany)


ifeq ($(OSTYPE), Windows_NT)
MOD_INCL=$(STD_INCL) -I=$(DEVROOT)\\Projects\\CPP\\AppDevelopment\\Interfaces
MOD_INCL_CPP=$(STD_INCL_CPP) -I=$(DEVROOT_MAKE)/Projects/CPP/AppDevelopment/Interfaces
LIBS = $(BASE_LIBS) $(DEVROOT_MAKE)/projects/dll/libs/lbhook.lib,../../../../tools/watcom/lib386/nt/odbc32.lib

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
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/

#ifndef _LB_APP_
#define _LB_APP_

#include &lt;stdio.h&gt;
#include &lt;lbInterfaces.h&gt;

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_FUNCTOR(instanceOfApplication)

#ifdef __cplusplus
}
#endif

#endif //_LB_APP_
</exsl:document>
</xsl:template>

<xsl:template name="createApplicationModule">
		<xsl:param name="ApplicationID"/>
		
<exsl:document href="{$basedir}/{$appmoduledir}/{$ApplicationName}_AppModule/{$ApplicationName}.cpp" method="text">
/* This file is autogenerated. Please do not modify. It would be overwritten.
 */
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
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


class lbDynamicApplication : 
public lb_I_Application,
public lb_I_EventHandler
{
public:
	lbDynamicApplication();
	virtual ~lbDynamicApplication();

	DECLARE_LB_UNKNOWN()

	virtual lbErrCodes LB_STDCALL setGUI(lb_I_GUI* _gui);
	
	/**
	 * Let the implementation register it's symbolic events.
	 * For each event, it gets an numeric identifer so it may
	 * be able to dispatch that events.
	 */
	lbErrCodes LB_STDCALL initialize(char* user = NULL, char* app = NULL);
	lbErrCodes LB_STDCALL uninitialize();
	lbErrCodes LB_STDCALL run();
	lbErrCodes LB_STDCALL getGUI(lb_I_GUI** _gui);
	lbErrCodes LB_STDCALL getUserName(lb_I_String** user);
	lbErrCodes LB_STDCALL getApplicationName(lb_I_String** app);
	lbErrCodes LB_STDCALL setUserName(char* user);
	lbErrCodes LB_STDCALL setApplicationName(char* app);
	
	lb_I_EventManager* LB_STDCALL getEVManager( void );

	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);	

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
	 * \brief Create fixed database formular for <xsl:value-of select="$FormularName"/>
	 */
	lbErrCodes LB_STDCALL getFixedDBForm_<xsl:value-of select="$FormularName"/>(lb_I_Unknown* uk);
</xsl:for-each>
	
	/** \brief Print a report over menu/toolbar entry.
	 * A report may be based on a form, thus it's query is the data source.
	 * 
	 * On the other hand, it may be special reports not shown as forms. In that
	 * way, a separate configuration is needed.
	 */
	lbErrCodes LB_STDCALL printReport(lb_I_Unknown* uk);

	/** \brief Edit global properties when lbDMF Manager is running.
	 */
	lbErrCodes LB_STDCALL editProperties(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL OnPropertiesDataChange(lb_I_Unknown* uk);

protected:

	/** \brief Load the database forms.
	 */
	void LB_STDCALL activateDBForms(char* user, char* app);

	bool haveLoadedDBModel;

	lb_I_GUI* gui;
	UAP(lb_I_EventManager, eman)
	UAP(lb_I_Dispatcher, dispatcher)
	UAP(lb_I_Database, database)
	
	UAP(lb_I_String, LogonUser)
	UAP(lb_I_String, LogonApplication)
	UAP(lb_I_MetaApplication, metaapp)


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
	UAP(lb_I_FixedDatabaseForm, FixedDBForm<xsl:value-of select="$FormularName"/>)
</xsl:for-each>

	UAP(lb_I_String, UMLImportTargetDBName)
	UAP(lb_I_String, UMLImportTargetDBUser)
	UAP(lb_I_String, UMLImportTargetDBPass)


	char hdsihd[100];
};

lbDynamicApplication::lbDynamicApplication() {
	ref = STARTREF;
	gui = NULL;
	haveLoadedDBModel = false;
	_CL_LOG &lt;&lt; "lbDynamicApplication::lbDynamicApplication() called." LOG_
	
	REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBName)
	REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBUser)
	REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBPass)
}

lbDynamicApplication::~lbDynamicApplication() {
	_CL_LOG &lt;&lt; "lbDynamicApplication::~lbDynamicApplication() called." LOG_

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
	if (FixedDBForm<xsl:value-of select="$FormularName"/> != NULL) {
		FixedDBForm<xsl:value-of select="$FormularName"/>.resetPtr();
	}
</xsl:for-each>

}
/*...e*/

/*...sregister event handlers:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::registerEventHandler(lb_I_Dispatcher* disp) {
	// Register a dynamic formular creator

	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lbDynamicApplication::editProperties(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, appname)
		
	metaapp->getApplicationName(&amp;appname);
	
	// Guard, if this function is called accidently, but unintented.
	if (*appname == "lbDMF Manager") {
		// Build up a preferences object and pass it to the property view
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
		
		// General parameters for this application
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramGeneral)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterGeneral)
		UAP_REQUEST(manager.getPtr(), lb_I_String, valueGeneral)
		
		// Project manager parameters
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramProject)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterProject)
		UAP_REQUEST(manager.getPtr(), lb_I_String, valueProject)
		UAP_REQUEST(manager.getPtr(), lb_I_Boolean, boolProject)
		
		
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
		UAP_REQUEST(manager.getPtr(), lb_I_String, value)
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)
		
		parameter->setData("lbDMF Manager Import Definitions");
		//--------------------------------------------------------
		/*
		 parameterProject->setData("Autoopen last project");
		 boolProject->setData(true);
		 paramProject->setUAPBoolean(*&amp;parameterProject, *&amp;boolProject);
		 */
		
		parameterProject->setData("DB Name");
		valueProject->setData("CRM");
		paramProject->setUAPString(*&amp;parameterProject, *&amp;valueProject);
		
		parameterProject->setData("DB User");
		valueProject->setData("dba");
		paramProject->setUAPString(*&amp;parameterProject, *&amp;valueProject);
		
		parameterProject->setData("DB Password");
		valueProject->setData("trainres");
		paramProject->setUAPString(*&amp;parameterProject, *&amp;valueProject);
		
		metaapp->registerPropertyChangeEventGroup(	parameter->charrep(), *&amp;paramProject, 
													this, (lbEvHandler) &amp;lbDynamicApplication::OnPropertiesDataChange);
		
		param->setUAPParameter(*&amp;parameter, *&amp;paramProject);
		
		metaapp->showPropertyPanel(*&amp;param);
	}
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::OnPropertiesDataChange(lb_I_Unknown* uk) {
	_CL_LOG &lt;&lt; "lbDynamicApplication::OnProjectDataChange() called." LOG_
	
	lbErrCodes err = ERR_NONE;
	
	UAP(lb_I_Parameter, param)
	QI(uk, lb_I_Parameter, param)
	
	if (param != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, name)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterName)
		UAP_REQUEST(manager.getPtr(), lb_I_String, value)
		
		UAP(lb_I_KeyBase, key)
		
		name->setData("name");
		param->getUAPString(*&amp;name, *&amp;parameterName);
		
		name->setData("value");
		param->getUAPString(*&amp;name, *&amp;value);
		
		QI(parameterName, lb_I_KeyBase, key)
		
		if (strcmp(key->charrep(), "lbDMF Manager Import DefinitionsDB Name") == 0) {
					*UMLImportTargetDBName = value->charrep();
		}
		
		if (strcmp(key->charrep(), "lbDMF Manager Import DefinitionsDB User") == 0) {
					*UMLImportTargetDBUser = value->charrep();
		}
		
		if (strcmp(key->charrep(), "lbDMF Manager Import DefinitionsDB Password") == 0) {
					*UMLImportTargetDBPass = value->charrep();
		}
	} else {
		_LOG &lt;&lt; "ERROR: Could not decode parameter structure!" LOG_
	}
	
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)
	ukDoc = metaapp->getActiveDocument();
	QI(ukDoc, lb_I_Parameter, document)
								
	if (document != NULL) {
		*paramname = "UMLImportDBName";
		document->setUAPString(*&amp;paramname, *&amp;UMLImportTargetDBName);
		*paramname = "UMLImportDBUser";
		document->setUAPString(*&amp;paramname, *&amp;UMLImportTargetDBUser);
		*paramname = "UMLImportDBPass";
		document->setUAPString(*&amp;paramname, *&amp;UMLImportTargetDBPass);
	}
	
	return ERR_NONE;
}


BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicApplication)
	ADD_INTERFACE(lb_I_Application)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfApplication, lbDynamicApplication)

lbErrCodes LB_STDCALL lbDynamicApplication::setData(lb_I_Unknown* uk) {
	_LOG &lt;&lt; "lbDynamicApplication::setData() has not been implemented" LOG_
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::setGUI(lb_I_GUI* _gui) {
	gui = _gui;
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::getGUI(lb_I_GUI** _gui) {
	*_gui = gui;
	return ERR_NONE;
}

lb_I_EventManager* LB_STDCALL lbDynamicApplication::getEVManager( void ) {
	return NULL;
}

lbErrCodes LB_STDCALL lbDynamicApplication::uninitialize() {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::initialize(char* user, char* app) {
	_CL_LOG &lt;&lt; "lbDynamicApplication::initialize(...) called." LOG_	
	// To be implemented in a separate application module
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)

	// Get the event manager
	
	lb_I_Module* m = *&amp;manager;
	
	REQUEST(m, lb_I_EventManager, eman)
		
	REQUEST(m, lb_I_Dispatcher, dispatcher)
	dispatcher->setEventManager(eman.getPtr());
	
	if (metaapp == NULL) {
		REQUEST(manager.getPtr(), lb_I_MetaApplication, metaapp)
	}
	
	// Save user and app internally
	
	if (user == NULL) {
        _CL_LOG &lt;&lt; "lb_MetaApplication::Initialize() user is NULL" LOG_
	} else
		if (LogonUser == NULL) {
			REQUEST(manager.getPtr(), lb_I_String, LogonUser)
		}
	LogonUser->setData(user);
	
	if (app == NULL) {
        _CL_LOG &lt;&lt; "lb_MetaApplication::Initialize() app is NULL" LOG_
	} else
		if (LogonApplication == NULL) {
			REQUEST(manager.getPtr(), lb_I_String, LogonApplication)
		}

	_LOG &lt;&lt; "lbDynamicApplication::initialize('" &lt;&lt; user &lt;&lt; "', '" &lt;&lt; app &lt;&lt; "') called." LOG_
	LogonApplication->setData(app);
	
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)
	
	_CL_LOG &lt;&lt; "Begin setup menu ..." LOG_
		
	/*
	 Select all events, that are configured and register it.
	 */
	
	activateDBForms(user, app);
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, editMenu)
	UAP_REQUEST(getModuleInstance(), lb_I_String, menuEntry)
	
	return ERR_NONE;
}

void LB_STDCALL lbDynamicApplication::activateDBForms(char* user, char* app) {
	int unused;
	bool toolbaradded = false;
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
	eman->registerEvent("<xsl:value-of select="$EventName"/>", unused);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &amp;lbDynamicApplication::getFixedDBForm_<xsl:value-of select="$FormularName"/>, "<xsl:value-of select="$EventName"/>");
	metaapp->addMenuEntry(_trans(app), "<xsl:value-of select="@menuname"/>", "<xsl:value-of select="$EventName"/>", "");
	
	<xsl:if test="@toolbarimage!=''">
	if (toolbaradded == false) {
		metaapp->addToolBar(app);
		toolbaradded = true;
	}
						
	metaapp->addToolBarButton(app, "<xsl:value-of select="@menuname"/>", "<xsl:value-of select="$EventName"/>", "<xsl:value-of select="@toolbarimage"/>");
	</xsl:if>
</xsl:for-each>
}

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
lbErrCodes lbDynamicApplication::getFixedDBForm_<xsl:value-of select="$FormularName"/>(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)
	
	if (FixedDBForm<xsl:value-of select="$FormularName"/> == NULL) {
		pl = PM->getFirstMatchingPlugin("lb_I_FixedDatabaseForm", "FixedDBForm_<xsl:value-of select="$FormularName"/>");
	
		if (pl == NULL) {
			return ERR_NONE;
		}
	
		if (pl != NULL) {
			ukPl = pl->getImplementation();
			UAP(lb_I_FixedDatabaseForm, dbForm)
			QI(ukPl, lb_I_FixedDatabaseForm, dbForm)
				
			dbForm = gui->addCustomDBForm(dbForm.getPtr(), "<xsl:value-of select="$tempFormularName"/>");
			
			if (dbForm != NULL) {
				FixedDBForm<xsl:value-of select="$FormularName"/> = dbForm.getPtr();
				dbForm->show();
				metaapp->setStatusText("Info", "Database form created. Ready.");
			} else {
				metaapp->setStatusText("Info", "Error: Database form was not loaded by the GUI !");
			}
		}
	} else {
		FixedDBForm<xsl:value-of select="$FormularName"/>->show();
	}
	return ERR_NONE;
}
</xsl:for-each>


lbErrCodes LB_STDCALL lbDynamicApplication::getUserName(lb_I_String** user) {
	if (LogonUser == NULL) (*user)->setData("");
	else (*user)->setData(LogonUser->charrep());
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::getApplicationName(lb_I_String** app) {
	if (LogonApplication == NULL) (*app)->setData("");
	else (*app)->setData(LogonApplication->charrep());
	return ERR_NONE;
}
lbErrCodes LB_STDCALL lbDynamicApplication::setUserName(char* user) {
	if (LogonUser == NULL) {
        	REQUEST(manager.getPtr(), lb_I_String, LogonUser)
	}

       	LogonUser->setData(user);
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::setApplicationName(char* app) {
	if (LogonApplication == NULL) {
        	REQUEST(manager.getPtr(), lb_I_String, LogonApplication)
	}

       	LogonApplication->setData(app);
	return ERR_NONE;
}


// This starts the main application

/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\run\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::run() {
#ifdef bla
	lb_I_Unknown* result;

	dispatcher->dispatch("AddMenu", NULL, &amp;result);	
#endif
	return ERR_NONE;
}
/*...e*/

/*...e*/

#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";

        switch (reason) {
                case DLL_PROCESS_ATTACH:
                	TRMemOpen();
                	TRMemSetModuleName(__FILE__);

			if (isSetTRMemTrackBreak()) TRMemSetAdrBreakPoint(getTRMemTrackBreak(), 0);
                	
                        if (situation) {
                                _CL_VERBOSE &lt;&lt; "DLL statically loaded." LOG_
                        }
                        else {
                                _CL_VERBOSE &lt;&lt; "DLL dynamically loaded.\n" LOG_
                        }
                        break;
                case DLL_THREAD_ATTACH:
                        _CL_VERBOSE &lt;&lt; "New thread starting.\n" LOG_
                        break;
                case DLL_PROCESS_DETACH:                        
                	_CL_VERBOSE &lt;&lt; "DLL_PROCESS_DETACH for " &lt;&lt; __FILE__ LOG_
                        if (situation)
                        {
                                _CL_VERBOSE &lt;&lt; "DLL released by system." LOG_
                        }
                        else
                        {
                                _CL_VERBOSE &lt;&lt; "DLL released by program.\n" LOG_
                        }
                        break;
                case DLL_THREAD_DETACH:
                        _CL_VERBOSE &lt;&lt; "Thread terminating.\n" LOG_
                default:
                        return FALSE;
        }
        
        return TRUE;
}
/*...e*/
#endif

</exsl:document>
</xsl:template>
</xsl:stylesheet>
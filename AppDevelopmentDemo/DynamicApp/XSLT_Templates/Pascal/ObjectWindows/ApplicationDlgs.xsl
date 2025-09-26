<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2024-  Lothar Behrens (lothar.behrens@lollisoft.de)

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
<xsl:import href="../../include/exsl.xsl"/>

<xsl:import href="../../include/lbDMFBaseTemplates.xsl"/>

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

<xsl:template name="createApplicationMenu">

<exsl:document href="{$basedir}/{$pas_appmoduledir}/{$ApplicationName}/MainApp.rc" method="text">#include "owindows.inc"
#include "ostddlgs.inc"
#include "rcdefs.pas"

men_Main MENU
BEGIN
	POPUP "&amp;File"
	BEGIN
		MENUITEM "&amp;New", cm_FileNew
		MENUITEM "&amp;Open...", cm_FileOpen
		MENUITEM SEPARATOR
		MENUITEM "&amp;Save", cm_FileSave, GRAYED
		MENUITEM "Save &amp;as...", cm_FileSaveAs, GRAYED
		MENUITEM SEPARATOR
		MENUITEM "&amp;Print...", cm_Print, GRAYED
		MENUITEM SEPARATOR
		MENUITEM "E&amp;xit", cm_Exit
	END
	
	POPUP "&amp;Formulars"
	BEGIN
	<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularId" select="@ID"/>
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
		MENUITEM "<xsl:value-of select="$FormularName"/>", cm_<xsl:value-of select="$FormularName"/></xsl:for-each>
	END
END
</exsl:document>
</xsl:template>

<xsl:template name="createApplicationRcDefines">
<exsl:document href="{$basedir}/{$pas_appmoduledir}/{$ApplicationName}/rcdefs.pas" method="text">Unit RcDefs;

Interface

const 
    men_Main  = 100;
	cm_Print  = 105;
	cm_About  = 106;
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularId" select="@ID"/>
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
	cm_<xsl:value-of select="$FormularName"/> = cm_About + <xsl:value-of select="$FormularId"/>;</xsl:for-each>

Implementation
End.
</exsl:document>
</xsl:template>


<xsl:template name="createApplication">

<exsl:document href="{$basedir}/{$pas_appmoduledir}/{$ApplicationName}/MainApp.pas" method="text">Program <xsl:value-of select="$ApplicationName"/>;

Uses AppUnit;

{ Declare a variable of type T<xsl:value-of select="$ApplicationName"/>App }
var
  <xsl:value-of select="$ApplicationName"/>App: T<xsl:value-of select="$ApplicationName"/>App;

Begin  
  <xsl:value-of select="$ApplicationName"/>App.Init('<xsl:value-of select="$ApplicationName"/>App');
  <xsl:value-of select="$ApplicationName"/>App.Run;
  <xsl:value-of select="$ApplicationName"/>App.Done;
End.
</exsl:document>
</xsl:template>

<xsl:template name="createApplicationUnit">
		<xsl:param name="ApplicationID"/>

<exsl:document href="{$basedir}/{$pas_appmoduledir}/{$ApplicationName}/AppUnit.pas" method="text">Unit AppUnit;

Interface

Uses WinTypes, WinProcs, OWindows, RcDefs;

{ Command IDs }

{$R MAINAPP.RES}

Type
  PMainWindow = ^TMainWindow;
  TMainWindow = object(TWindow)
    Constructor Init(AParent: PWindowsObject; ATitle: PChar);
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
    Procedure show<xsl:value-of select="$FormularName"/>;</xsl:for-each>
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
    Procedure CM<xsl:value-of select="$FormularName"/>(var Msg: TMessage); Virtual cm_First + cm_<xsl:value-of select="$FormularName"/>;</xsl:for-each>
  End;
	
Type

  { Define a TApplication descendant }
  T<xsl:value-of select="$ApplicationName"/>App = object(TApplication)
    procedure InitMainWindow; virtual;
  end;

Implementation  

Constructor TMainWindow.Init(AParent: PWindowsObject; ATitle: PChar);
Begin
  Inherited Init(AParent, ATitle);
  Attr.Menu := LoadMenu(HInstance, MakeIntResource(100));
End;

{ Construct the T<xsl:value-of select="$ApplicationName"/>App's MainWindow object }
procedure T<xsl:value-of select="$ApplicationName"/>App.InitMainWindow;
begin
  MainWindow := New(PMainWindow, Init(nil, 'Hello, Borland Object Pascal World for <xsl:value-of select="$ApplicationName"/>'));
end;

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
Procedure TMainWindow.show<xsl:value-of select="$FormularName"/>;
Begin
  MessageBox(HWindow, '<xsl:value-of select="$FormularName"/>', '<xsl:value-of select="$ApplicationName"/>', mb_Ok);
End;
</xsl:for-each>

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
Procedure TMainWindow.CM<xsl:value-of select="$FormularName"/>(var Msg: TMessage);
Begin
  show<xsl:value-of select="$FormularName"/>;
End;
</xsl:for-each>

Begin

End.
</exsl:document>
</xsl:template>

</xsl:stylesheet>

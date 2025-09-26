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

<xsl:template name="createApplicationResource">

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
DIALOG_<xsl:value-of select="$FormularName"/> DIALOG 203, 48, 250, 180
STYLE DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "<xsl:value-of select="$FormularName"/>"
BEGIN
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularId]">
	<xsl:variable name="FieldName" select="@name"/>
	<xsl:variable name="TableName" select="@tablename"/>
	LTEXT "<xsl:value-of select="$FieldName"/>", -1, 10, <xsl:value-of select="10+20*(position()-1)"/>, 50, 8, WS_CHILD | WS_VISIBLE
	EDITTEXT 105+<xsl:value-of select="@ID"/>, 60, <xsl:value-of select="8+20*(position()-1)"/>, 120, 12
</xsl:for-each>
	CONTROL "Ok", 100, "BorBtn", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 190, 10, 32, 12
	CONTROL "Cancel", 101, "BorBtn", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 190, 50, 32, 12
END
</xsl:for-each>

DIALOG_Template DIALOG 203, 48, 250, 170
STYLE DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "Anwendungen"
BEGIN
	LTEXT "Name", -1, 10, 27, 22, 8, WS_CHILD | WS_VISIBLE
	EDITTEXT 100, 41, 25, 63, 12
	CONTROL "Id", -1, "STATIC", SS_LEFT | WS_CHILD | WS_VISIBLE, 10, 11, 22, 8
	EDITTEXT 101, 41, 9, 63, 12, ES_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP
	CONTROL "Ok", 102, "BorBtn", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 165, 146, 32, 20
	CONTROL "Cancel", 103, "BorBtn", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 211, 146, 32, 20
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

Uses WinTypes, WinProcs, OWindows, RcDefs, DataDlgs;

{ Command IDs }

{$R MAINAPP.RES}

Type
  { Define a TApplication descendant }
  T<xsl:value-of select="$ApplicationName"/>App = object(TApplication)
    procedure InitMainWindow; virtual;
  end;

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

Implementation  

{ Construct the T<xsl:value-of select="$ApplicationName"/>App's MainWindow object }
procedure T<xsl:value-of select="$ApplicationName"/>App.InitMainWindow;
begin
  MainWindow := New(PMainWindow, Init(nil, 'Hello, Borland Object Pascal World for <xsl:value-of select="$ApplicationName"/>'));
end;

Constructor TMainWindow.Init(AParent: PWindowsObject; ATitle: PChar);
Begin
  Inherited Init(AParent, ATitle);
  Attr.Menu := LoadMenu(HInstance, MakeIntResource(100));
End;

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
Var ADialog : P<xsl:value-of select="$FormularName"/>Dialog;
Var ReturnValue : Integer;
Begin
  {
  MessageBox(HWindow, '<xsl:value-of select="$FormularName"/>', '<xsl:value-of select="$ApplicationName"/>', mb_Ok);
  ADialog := New(P<xsl:value-of select="$FormularName"/>Dialog, Init(@Self, 'DIALOG_<xsl:value-of select="$FormularName"/>'));
  ADialog := New(P<xsl:value-of select="$FormularName"/>Dialog, Init);
  }
  ADialog := New(P<xsl:value-of select="$FormularName"/>Dialog, Init(@Self));
  ReturnValue := Application^.ExecDialog(ADialog);
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

<xsl:template name="createDataDialogUnit">

<exsl:document href="{$basedir}/{$pas_appmoduledir}/{$ApplicationName}/DataDlgs.pas" method="text">Unit DataDlgs;

Interface

Uses WinTypes, WinProcs, OWindows, ODialogs, RcDefs, BWCC;

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
Type
  P<xsl:value-of select="$FormularName"/>Dialog = ^T<xsl:value-of select="$FormularName"/>Dialog;
  T<xsl:value-of select="$FormularName"/>Dialog = object(TDialog)
    constructor Init(AParent: PWindowsObject);  
  End;
</xsl:for-each>

Implementation

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
constructor T<xsl:value-of select="$FormularName"/>Dialog.Init(AParent: PWindowsObject);
begin
  {inherited Init(@self, 'DIALOG_<xsl:value-of select="$FormularName"/>');}
  inherited Init(AParent, 'DIALOG_<xsl:value-of select="$FormularName"/>');
end;

</xsl:for-each>

Begin

End.
</exsl:document>

</xsl:template>

</xsl:stylesheet>

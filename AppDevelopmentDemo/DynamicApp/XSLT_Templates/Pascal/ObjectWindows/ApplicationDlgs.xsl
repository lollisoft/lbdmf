<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2000-2025  Lothar Behrens (lothar.behrens@lollisoft.de)

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
            Odenwaldstr. 14

            63150 Heusenstamm (germany)
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

<xsl:template name="createDataDialogUnit">

<exsl:document href="{$basedir}/{$pas_appmoduledir}/{$ApplicationName}/DataDlgs.pas" method="text">Unit DataDlgs;

Interface

Uses WinTypes, WinProcs, OWindows, ODialogs, RcDefs, Engine, Idapi, DbiTypes, DbiErrs, BWCC;

const
  file_Handles = 40;
  WM_DISPLAY = 2200;

Type
  PBaseDataDialog = ^TBaseDataDialog;
  TBaseDataDialog = object(TDialog)
	hCur: hDBICur;
    constructor Init(AParent: PWindowsObject; name: PChar);
    procedure idFirstRec(var Msg: TMessage);
       virtual id_First + id_FirstRec;
    procedure idLastRec(var Msg: TMessage);
       virtual id_First + id_LastRec;
    procedure idNextRec(var Msg: TMessage);
       virtual id_First + id_NextRec;
    procedure idPrevRec(var Msg: TMessage);
       virtual id_First + id_PrevRec;
  
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
Type
  P<xsl:value-of select="$FormularName"/>Dialog = ^T<xsl:value-of select="$FormularName"/>Dialog;
  T<xsl:value-of select="$FormularName"/>Dialog = object(TDialog)
    constructor Init(AParent: PWindowsObject);  
  End;
</xsl:for-each>

Implementation

{ TBaseDataDialog }
constructor TBaseDataDialog.Init(AParent: PWindowsObject; name: PChar);
begin
  inherited Init(AParent, name);
  if SetHandleCount(file_Handles) &lt;&gt; file_Handles then
  begin
    BWCCMessageBox(0, 'Not Enough File handles available', 'ERROR', mb_Ok);
    PostQuitMessage(0);
  end;
  SetPrivateDir;
end;

procedure TBaseDataDialog.idFirstRec(var Msg: TMessage);
begin
  GoTop(hCur, True);
  PostMessage(hWindow, wm_Display, 0, 0);
end;

procedure TBaseDataDialog.idLastRec(var Msg: TMessage);
begin
  GoBottom(hCur, True);
  PostMessage(hWindow, wm_Display, 0, 0);
end;

procedure TBaseDataDialog.idNextRec(var Msg: TMessage);
begin
  if not AtEOF(HCur) then
  begin
   GetNextRec(hCur);
   PostMessage(hWindow, wm_Display, 0, 0);
  end;
end;

procedure TBaseDataDialog.idPrevRec(var Msg: TMessage);
begin
  if not AtBOF(HCur) then
  begin
    GetPrevRec(HCur);
    PostMessage(hWindow, wm_Display, 0, 0);
  end;
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
constructor T<xsl:value-of select="$FormularName"/>Dialog.Init(AParent: PWindowsObject);
begin
  inherited Init(AParent, 'DIALOG_<xsl:value-of select="$FormularName"/>');
end;

</xsl:for-each>

Begin

End.
</exsl:document>

</xsl:template>

</xsl:stylesheet>

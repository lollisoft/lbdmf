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

<xsl:template name="createEngineUnits">

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
<exsl:document href="{$basedir}/{$pas_appmoduledir}/{$ApplicationName}/Eng{$FormularId}.pas" method="text">{$A+,B-,D+,F+,G+,I-,K+,L+,N+,P-,Q-,R-,S-,T-,V+,W+,X+,Y+}
{$M 25000,8192}
{************************************************}
{
    Base functions for data dialog for
	<xsl:value-of select="$FormularName"/>
}
{************************************************}
unit Eng<xsl:value-of select="$FormularId"/>;

interface
uses WinTypes, WinProcs, strings, Idapi, DbiTypes, DbiErrs, BWCC, WinDos;

const
  <xsl:value-of select="$FormularName"/>Index   = 1;
  <xsl:value-of select="$FormularName"/>IDIndex  = 2;

const
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularId]">
	<xsl:variable name="FieldName" select="@name"/>
	<xsl:variable name="TableName" select="@tablename"/>
	
{ FieldNums }
  F<xsl:value-of select="$TableName"/>_<xsl:value-of select="$FieldName"/>Num      = <xsl:value-of select="position()"/>;
  <xsl:value-of select="$TableName"/>_<xsl:value-of select="$FieldName"/>_len      = 32;
<xsl:if test="position()=last()">
  F<xsl:value-of select="$TableName"/>_IDNum      = <xsl:value-of select="last()+1"/>;
{ Name of table to be created }
  <xsl:value-of select="$TableName"/>TblName = '<xsl:value-of select="$TableName"/>';
{ Type of Table }
  <xsl:value-of select="$TableName"/>TblType = szDBase;
{ Number of fields to be created when the table is created. }
  <xsl:value-of select="$TableName"/>NumFields = <xsl:value-of select="position()"/>;
{ Number of indexes to be created when the table is created }
  <xsl:value-of select="$TableName"/>NumIndexes = 3;

type
  P<xsl:value-of select="$TableName"/>XIDXDesc = ^T<xsl:value-of select="$TableName"/>IDXDesc;
  T<xsl:value-of select="$TableName"/>IDXDesc = array[1..<xsl:value-of select="$TableName"/>NumIndexes] of IDXDesc;
  P<xsl:value-of select="$TableName"/>TempFldDesc = ^<xsl:value-of select="$TableName"/>TempFldDesc;
  <xsl:value-of select="$TableName"/>TempFldDesc = array[1..<xsl:value-of select="$TableName"/>NumFields] of FldDesc;
</xsl:if>  
</xsl:for-each>

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularId]">
	<xsl:variable name="FieldName" select="@name"/>
	<xsl:variable name="TableName" select="@tablename"/>
<xsl:if test="position()=1">
const
  X<xsl:value-of select="$TableName"/>FLDDesc: array[1..<xsl:value-of select="$TableName"/>NumFields] of FldDesc = (
</xsl:if>	
    { // Field 1 - <xsl:value-of select="$FieldName"/> }
    ( iFldNum:  F<xsl:value-of select="$TableName"/>_<xsl:value-of select="$FieldName"/>Num;        { Field Number }
      szName:   '<xsl:value-of select="$FieldName"/>';     { Field Name }
      iFldType: fldZSTRING;      { Field Type }
      iSubType: fldUNKNOWN;      { Field Subtype }
      iUnits1:  <xsl:value-of select="$TableName"/>_<xsl:value-of select="$FieldName"/>_Len;         { Field Size 1 or 0, except  BLOb or CHAR field }
      iUnits2:  0;               { Decimal places ( 0 )  computed }
      iOffset:  0;               { Offset in record ( 0 ) }
      iLen:     0;               { Length in Bytes  ( 0 ) }
      iNullOffset: 0;            { For Null Bits    ( 0 ) }
      efldvVchk: fldvNOCHECKS;   { Validiy checks   ( 0 ) }
      efldrRights: fldrREADWRITE { Rights }
    )<xsl:if test="position()!=last()">,</xsl:if>
</xsl:for-each>
     );

	 
	 
{ Index Descriptor - describes the Indexes associated with the
  table. This index is going to be added to the table when the
  table is created. }
	 
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularId]">
	<xsl:variable name="FieldName" select="@name"/>
	<xsl:variable name="TableName" select="@tablename"/>
<xsl:if test="position()=1">	

X<xsl:value-of select="$TableName"/>IDXDesc: array[1..<xsl:value-of select="$TableName"/>NumIndexes] of IDXDesc = (
  ( { Index #1 - LASTNAME }
    szName: '';                      { Index name }
    iIndexId: 1;                     { Index number }
    szTagName: 'NAME'#0;             { Tag name (for dBASE) }
    szFormat: #0;                    { Optional format(BTREE, HASH etc) }
    bPrimary: false;                 { True, if primary index }
    bUnique: false;                  { True, if unique keys }
    bDescending: false;              { True, for descending }
    bMaintained: true;               { True, if maintained }
    bSubset: false;                  { If subset index }
    bExpIdx: true;                   { If expression index }
    iCost: 0;                        { (For QBE only) }
    iFldsInKey: 2;                   { Fields in the key  }
    iKeyLen: 1;                      { Phy Key length in bytes (Key only) }
    bOutofDate: false;               { Index out of date }
    iKeyExpType: 0;                  { Key type of Expression }
    aiKeyFld: (2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
                                     { Array of field numbers in key }
    szKeyExp: 'TRIM(LASTNAME) + ", " + TRIM(FIRSTNAME)'#0;  { Key expression }
    szKeyCond: #0;                   { Subset condition }
    bCaseInsensitive: false;         { Case insensitive index }
    iBlockSize: 0;                   { Block size in bytes }
    iRestrNum: 0                     { Restructure number }
  ),
  ( { Index #2 - Single-Field }
    szName: '';                      { Index name }
    iIndexId: 2;                     { Index number }
    szTagName: 'EMPLOYEEID'#0;       { Tag name (for dBASE) }
    szFormat: #0;                    { Optional format(BTREE, HASH etc) }
    bPrimary: false;                 { True, if primary index }
    bUnique: false;                  { True, if unique keys }
    bDescending: false;              { True, for descending }
    bMaintained: true;               { True, if maintained }
    bSubset: false;                  { If subset index }
    bExpIdx: false;                  { If expression index }
    iCost: 0;                        { (For QBE only) }
    iFldsInKey: 1;                   { Fields in the key (1 for Exp) }
    iKeyLen: 1;                      { Phy Key length in bytes (Key only) }
    bOutofDate: false;               { Index out of date }
    iKeyExpType: 0;                  { Key type of Expression }
    aiKeyFld: (10,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0);{ Array of field numbers in key }
    szKeyExp: #0;  { Key expression }
    szKeyCond: #0;                   { Subset condition }
    bCaseInsensitive: false;         { Case insensitive index }
    iBlockSize: 0;                   { Block size in bytes }
    iRestrNum: 0                     { Restructure number }
  ),
 (   { Index #3 - Single-Field }
    szName: '';          { Index name }
    iIndexId: 3;                     { Index number }
    szTagName: 'DEPARTMENT'#0;       { Tag name (for dBASE) }
    szFormat: #0;                    { Optional format(BTREE, HASH etc) }
    bPrimary: false;                 { True, if primary index }
    bUnique: false;                  { True, if unique keys }
    bDescending: false;              { True, for descending }
    bMaintained: true;               { True, if maintained }
    bSubset: false;                  { If subset index }
    bExpIdx: false;                  { If expression index }
    iCost: 0;                        { (For QBE only) }
    iFldsInKey: 1;                   { Fields in the key (1 for Exp) }
    iKeyLen: 1;                      { Phy Key length in bytes (Key only) }
    bOutofDate: false;               { Index out of date }
    iKeyExpType: 0;                  { Key type of Expression }
    aiKeyFld: (13,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0);{ Array of field numbers in key }
    szKeyExp: #0;  { Key expression }
    szKeyCond: #0;                   { Subset condition }
    bCaseInsensitive: false;         { Case insensitive index }
    iBlockSize: 0;                   { Block size in bytes }
    iRestrNum: 0                     { Restructure number }
 ));

<xsl:value-of select="$TableName"/>IDXDescriptions: array[1..<xsl:value-of select="$TableName"/>NumIndexes] of PChar = (
  'Indexed on Employee''s last name',
  'Indexed on Employee''s identification number',
  'Indexed on Employee''s department number');

type

  P<xsl:value-of select="$TableName"/>RecordType = ^T<xsl:value-of select="$TableName"/>RecordType;
  T<xsl:value-of select="$TableName"/>RecordType = record
</xsl:if>  
    <xsl:value-of select="$FieldName"/>Field: array[0..<xsl:value-of select="$TableName"/>_<xsl:value-of select="$FieldName"/>_len] of char;
<xsl:if test="position()=last()">	
    IdField: double;
  end;
</xsl:if>  
</xsl:for-each>

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
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularId]">
	<xsl:variable name="FieldName" select="@name"/>
	<xsl:variable name="TableName" select="@tablename"/>
<xsl:if test="position()=1">

function <xsl:value-of select="$TableName"/>CreateTable: DBIResult;
function <xsl:value-of select="$TableName"/>AddRecord(hCur: hDBICur; PRec: P<xsl:value-of select="$TableName"/>RecordType; Add: BOOL): DBIResult;
function <xsl:value-of select="$TableName"/>GetData(hCur: hDBICur; pRecord: P<xsl:value-of select="$TableName"/>RecordType): DBIResult;
</xsl:if>
</xsl:for-each>
</xsl:for-each>

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
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularId]">
	<xsl:variable name="FieldName" select="@name"/>
	<xsl:variable name="TableName" select="@tablename"/>
<xsl:if test="position()=1">
function <xsl:value-of select="$TableName"/>AddRecord(hCur: hDBICur; PRec: P<xsl:value-of select="$TableName"/>RecordType; Add: BOOL): DBIResult;
function <xsl:value-of select="$TableName"/>GetData(hCur: hDBICur; pRecord: P<xsl:value-of select="$TableName"/>RecordType): DBIResult;
function <xsl:value-of select="$TableName"/>SetupIndex (hCur: hdbICur; IndexNum: word; FirstRec: BOOL): DBIResult;
function <xsl:value-of select="$TableName"/>SetIndex (hCur: hDBICur; uNum: word; FirstRec: BOOL): DBIResult;
function <xsl:value-of select="$TableName"/>GetIndexNum (hCur: hDBICur): word;
</xsl:if>
</xsl:for-each>
</xsl:for-each>

Implementation
{Uses Engine;}


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
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularId]">
	<xsl:variable name="FieldName" select="@name"/>
	<xsl:variable name="TableName" select="@tablename"/>
<xsl:if test="position()=1">
{=============================================================================
/  Name:   <xsl:value-of select="$TableName"/>CreateTable
/  Desc:   This function opens a database and creates a table.
=============================================================================}
function <xsl:value-of select="$TableName"/>CreateTable: DBIResult;
var
  crTblDsc: CRTblDesc;           { Table Descriptor }
  bOverWrite: BOOL;              { Overwrite, yes/no flag }
  TableDir: PChar;
  hdb: hdbIDb;

begin
  GetMem(TableDir, dbiMAXPATHLEN + 1);
  bOverWrite := TRUE;
  { Set the directory for the database handle }
  DbiError(DbiOpenDatabase(nil, nil, dbiREADWRITE, dbiOPENSHARED,
                           nil, 0, nil, nil, hdb));


  FindTablesDir(TableDir, 3);

  DbiError(DbiSetDirectory(hdb, TableDir));

  fillchar(crTblDsc, sizeof(CRTblDesc), #0);  { Clear the buffer. }

  { Set the name and the type of the table }
  strcopy(crTblDsc.szTblName, <xsl:value-of select="$TableName"/>TblName); { name of the table }
  strcopy(crTblDsc.szTblType, <xsl:value-of select="$TableName"/>TblType); { Type of table }

  { Set the field information for the table }

  crTblDsc.iFldCount := <xsl:value-of select="$TableName"/>NumFields;   { number of fields }
  crTblDsc.pfldDesc  := @X<xsl:value-of select="$TableName"/>FldDesc;   { Field descriptor }

  { Set the index information for the table }

  crTblDsc.iIdxCount := <xsl:value-of select="$TableName"/>NumIndexes;   { Number of indexes }
  crTblDsc.pidxDesc  := @X<xsl:value-of select="$TableName"/>IDXDesc;    { Index descriptor }

  { Create the table using information supplied in the Table
  { Descrpitor above }
  DbiError(DbiCreateTable(hdb, bOverWrite, crTblDsc));

  if(GlobalDBIErr &lt;&gt; DBIERR_NONE) then
  begin
    <xsl:value-of select="$TableName"/>CreateTable :=  GlobalDBIErr;
    DbiError(DbiCloseDatabase(hDb));
    FreeMem(TableDir, dbiMAXPATHLEN + 1);
    exit;
  end;

  {CloseDatabase}
  DbiError(DbiCloseDatabase(hDb));


  if(GlobalDBIErr &lt;&gt; DBIERR_NONE) then
     <xsl:value-of select="$TableName"/>CreateTable := GlobalDBIErr
  else
    <xsl:value-of select="$TableName"/>CreateTable := DBIERR_NONE;
  FreeMem(TableDir, dbiMAXPATHLEN + 1);
end;


{=============================================================================
/  Name:   <xsl:value-of select="$TableName"/>AddRecord
/  Desc:   This function adds a record to the table pointed at by the cursor.
=============================================================================}
function <xsl:value-of select="$TableName"/>AddRecord(hCur: hDBICur; PRec: P<xsl:value-of select="$TableName"/>RecordType; Add: BOOL): DBIResult;
var
  PRecBuf: pByte;         { Record buffer }
  TblProps: CURProps;     { Table Properties }
  j: integer;             { Field loop counter }
  Date1, Date2: Longint;
  RetVal: DBIResult;

begin
  j := 1;
  pRecBuf := nil;
  DbiError(DbiGetCursorProps(hCur, TblProps));

  getmem(PRecBuf, sizeof(T<xsl:value-of select="$TableName"/>RecordType));
  {  Make sure we're starting with a clean record buffer }
  DbiError(DbiInitRecord(hCur, pRecBuf));

  { Fill each field with the structure's data }
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularId]">
	<xsl:variable name="FFieldName" select="@name"/>
	<xsl:variable name="FTableName" select="@tablename"/>
  DbiError(DbiPutField(hCur, F<xsl:value-of select="$FTableName"/>_<xsl:value-of select="$FFieldName"/>Num, pRecBuf, @PRec^.<xsl:value-of select="$FieldName"/>Field));
<xsl:if test="position()=last()">
  DbiError(DbiPutField(hCur, F<xsl:value-of select="$FTableName"/>_IDNum, pRecBuf, @PRec^.IdField));
</xsl:if>
</xsl:for-each>
{ We do not yet have dates here ... }
{  RetVal := SetDate(Date1, PRec^.StartDate); }
{
  if RetVal = DBIERR_NONE then
  begin
    DbiError(DbiPutField(hCur, StartDateNum, pRecBuf, @Date1));

    if (strcomp(PRec^.EndDate, '') &lt;&gt; 0) then
    begin
      SetDate(Date2, PRec^.EndDate);
      DbiError(DbiPutField(hCur, EndDateNum, pRecBuf, @Date2));
    end
    else DbiError(DbiPutField(hCur, EndDateNum, pRecBuf, nil)); } { XXX AddRec}

{
    DbiError(DbiOpenBlob(hCur, pRecBuf, CommentsNum, dbiREADWRITE));
    DbiError(DbiPutBlob(hCur, pRecBuf, CommentsNum, 0, strlen(PRec^.Comments)+1, @PRec^.Comments));
}

    if(Add) then
    begin
        { Insert the record }
        DbiError(DbiInsertRecord(hCur, dbiWRITELOCK, pRecBuf));
        { Release the record lock }
        DbiError(DbiRelRecordLock(hCur, false));
    end
    else
    begin
        { Overwrite the record }
        { Get WriteLock rights to this record to modify it. }
        DeleteRec(hCur);
        DbiError(DbiInsertRecord(hCur, dbiWRITELOCK, pRecBuf));
        DbiError(DbiRelRecordLock(hCur, FALSE));
    end;

    { NOW YOU MUST FREE the blob. }
{	
    DbiError(DbiFreeBlob(hCur, pRecBuf, CommentsNum));
}
    freemem(PRecBuf, sizeof(T<xsl:value-of select="$TableName"/>RecordType));
    RetVal := GlobalDBIErr;
{
  end;
}
  <xsl:value-of select="$TableName"/>AddRecord := RetVal;
end; { <xsl:value-of select="$TableName"/>AddRecord }

{=============================================================================
/  Name:   <xsl:value-of select="$TableName"/>FillRec
/  Desc:   This function adds a record to the table pointed at by the cursor.
=============================================================================}
function <xsl:value-of select="$TableName"/>FillRec (hCur: hDBICur; pRecBuf: pByte; PRec: P<xsl:value-of select="$TableName"/>RecordType): DBIResult;
var
  DateInt: longint;
  DayInt:  word;      { Day part of the date }
  MonthInt:  word;    { Month part of the date }
  YearInt:  integer;      { Year part of the date }
  Actual:  longint;      { Total amount read from blob }
  BlobSize:  longint;    { Size of blob }
  FieldEmpty:  BOOL;    { Is field empty variable }
  TempStr:  array[0..MaxFieldSize] of char; { Temporary variable for reading data }
  Code: integer;
  DtRec: DateRec;
  Date1, Date2: longint;
begin
    { Put each field into the data structure }
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularId]">
	<xsl:variable name="FFieldName" select="@name"/>
	<xsl:variable name="FTableName" select="@tablename"/>
  DbiError(DbiGetField(hCur, F<xsl:value-of select="$FTableName"/>_<xsl:value-of select="$FFieldName"/>Num, pRecBuf, @PRec^.<xsl:value-of select="$FieldName"/>Field, FieldEmpty));
<xsl:if test="position()=last()">
  DbiError(DbiGetField(hCur, F<xsl:value-of select="$FTableName"/>_IDNum, pRecBuf, @PRec^.IdField, FieldEmpty));
</xsl:if>
</xsl:for-each>
{
  DbiError(DbiGetField(hCur, StartDateNum, pRecBuf, @Date1, FieldEmpty));
  DbiError(DbiDateDecode(Date1, MonthInt, Dayint, YearInt));
  DtRec.Month := MonthInt;
  DtRec.Day := DayInt;
  DtRec.Year := YearInt;
}
  { Format the date to MM\DD\YYYY format }
{
  wvsprintf(PRec^.StartDate, '%02u-%02u-%02u', DtRec);
}  
                                                              { XXX FillRec }
{
  DbiError(DbiGetField(hCur, EndDateNum, pRecBuf, nil, FieldEmpty));
  if FieldEmpty = false then
  begin
    DbiError(DbiGetField(hCur, EndDateNum, pRecBuf, @Date2, FieldEmpty));
    DbiError(DbiDateDecode(Date2, MonthInt, Dayint, YearInt));
    DtRec.Month := MonthInt;
    DtRec.Day := DayInt;
    DtRec.Year := YearInt;
}
    { Format the date to MM\DD\YYYY format }
{
    wvsprintf(PRec^.EndDate, '%02u-%02u-%02u', DtRec)
  end
  else strcopy(PRec^.EndDate, '');
}

{
  DbiError(DbiOpenBlob(hCur, pRecBuf, CommentsNum, dbiREADWRITE));
}
  { Now get the size of the blob so that you can allocate the
  / correct amount of memory.  The BlobSize variable is a UINT32. }
{
  DbiError(DbiGetBlobSize(hCur, pRecBuf, CommentsNum, BlobSize));
  DbiError(DbiGetBlob(hCur, pRecBuf, CommentsNum, 0, BlobSize,
                      @PRec^.Comments, Actual));
  PRec^.Comments[BlobSize] := #0;
  DbiError(DbiFreeBlob(hCur, pRecBuf, CommentsNum));
}
  <xsl:value-of select="$TableName"/>FillRec := DBIERR_NONE;
end;

{=============================================================================
/  Name:   <xsl:value-of select="$TableName"/>GetData
/  Desc:   This function gets the data pointed to by hCur and puts it
/          into the record structure.
=============================================================================}
function <xsl:value-of select="$TableName"/>GetData (hCur: hDBICur; pRecord: P<xsl:value-of select="$TableName"/>RecordType): DBIResult;
var
  TblProps: CURProps;
  PRecBuf: pByte;
  Rslt: DBIResult;
begin
  PRecBuf := nil;
  { Get the proporties of the table so that we can create the correct
  / buffer size for the record.  We will read the record into the buffer
  / and then we will pull the field from the buffer.
  }
  DbiError(DbiGetCursorProps(hCur, TblProps));

  { Create the record buffer.  The size comes from the proporty recsize. }

  getmem(PRecBuf, sizeof(T<xsl:value-of select="$TableName"/>RecordType));

  { Initialize the record buffer. }
  DbiError(DbiInitRecord(hCur, PRecBuf));

  { Get the current reocord with a READLOCK. }
  Rslt := DbiGetRecord(hCur, dbiREADLOCK, pRecBuf, nil);

  if(Rslt = DBIERR_NONE) then
  begin
    { Fill the structure with the present record pointed to by hCur. }
    DbiError(<xsl:value-of select="$TableName"/>FillRec(hCur, pRecBuf, pRecord));
    { Now free the record lock on this record ONLY. }
    DbiError(DbiRelRecordLock(hCur, false));
  end;
  freemem(pRecBuf, sizeof(T<xsl:value-of select="$TableName"/>RecordType));
  <xsl:value-of select="$TableName"/>GetData := DBIERR_NONE;
end; { <xsl:value-of select="$TableName"/>GetData }

{=============================================================================
/  Name:   SetupIndex
/  Desc:   This function switches to an index based upon the index array that
/          is used to create the table, and the IndexNum that is passed into
/          the function.  The IndexNum corresponds to an element in the array.
=============================================================================}
function <xsl:value-of select="$TableName"/>SetupIndex (hCur: hdbICur; IndexNum: word; FirstRec: BOOL): DBIResult;
var
  MyDesc: P<xsl:value-of select="$TableName"/>IDXDesc;       { Index Descriptor }
begin
  MyDesc := nil;
  GetMem(MyDesc, sizeof(IdxDesc));

  { Get any index descriptor, because ALL the tags have the same index name,
  / but they have different tag names.
  }

  DbiError(DbiGetIndexDesc(hCur, 1, MyDesc^));

  { Switch to the index based upon the IndexNum which reflects the element
  / number of the idxDesc array.  the idxDesc array is the array of indexes
  / used to create the table.
  }

  DbiError(DbiSwitchToIndex(hCur, MyDesc^.szName, X<xsl:value-of select="$TableName"/>IDXDesc[IndexNum].szTagName,
                            IndexNum, FirstRec));

  freeMem(MyDesc, sizeof(IdxDesc));
  <xsl:value-of select="$TableName"/>SetupIndex := DBIERR_NONE;
end;

{=============================================================================
/  Name:   <xsl:value-of select="$TableName"/>SetIndex
/  Desc:   This function runs SetupIndex and moves the new cursor to the
/          first record in the table.
=============================================================================}
function <xsl:value-of select="$TableName"/>SetIndex (hCur: hDBICur; uNum: word; FirstRec: BOOL): DBIResult;
begin
  { Move to the top of the table do not move forward one record past the crack. }
  GoTop(hCur, FirstRec);
  <xsl:value-of select="$TableName"/>SetupIndex(hCur, uNum, FirstRec);
  GoTop(hCur, FirstRec);
  <xsl:value-of select="$TableName"/>SetIndex := DBIERR_NONE;
end;
{=============================================================================
/  Name:   <xsl:value-of select="$TableName"/>GetIndexNum
/  Desc:   This function returns the index number that corresponds to
/          the index found in the index array (idxDesc).
=============================================================================}

function <xsl:value-of select="$TableName"/>GetIndexNum (hCur: hDBICur): word;
var
  i: word;
  Num: integer;          { set it to a value it can never reach. }
  MyDesc: p<xsl:value-of select="$TableName"/>IDXDesc;    { Index Descriptor. }
begin
  i := 1;
  Num := 300;

  GetMem(MyDesc, sizeof(IdxDesc));

  if (MyDesc = nil) then
  begin
      DbiExit;
      <xsl:value-of select="$TableName"/>GetIndexNum := DBIERR_NOMEMORY;
  end;

  { Get information about the indexes }
  DbiError(DbiGetIndexDesc(hCur, 0, MyDesc^));

  { Loop until you found a match or until the maximum number of indexes
   that are open on this table. }
  while (i &lt; NumIndexes) and (Num &lt;&gt; 0) do
  begin
      { compare the current tagname with the names we know.  If it matches
      / then return that element number of the index array. }
     Num := strcomp(MyDesc^.szTagName, XIDXDesc[i].szTagName);
      inc(i);
  end;
  FreeMem(MyDesc, sizeof(idxDesc));
  { return the current index number. }
  <xsl:value-of select="$TableName"/>GetIndexNum :=  i-1;
end; { <xsl:value-of select="$TableName"/>GetIndexNum }

</xsl:if>
</xsl:for-each>
</xsl:for-each>




Begin

End.</exsl:document>

</xsl:for-each>

<exsl:document href="{$basedir}/{$pas_appmoduledir}/{$ApplicationName}/Engine.pas" method="text">{$A+,B-,D+,F+,G+,I-,K+,L+,N+,P-,Q-,R-,S-,T-,V+,W+,X+,Y+}
{$M 25000,8192}
{************************************************}
{                                                }
{   Base functions for each data dialog          }
{                                                }
{                                                }
{************************************************}
unit Engine;

interface
uses WinTypes, WinProcs, strings, Idapi, DbiTypes, DbiErrs, BWCC, WinDos;
const
  AppName = '<xsl:value-of select="$ApplicationName"/>';
  { Field Lengths }
  MaxFieldSize    = 60; { Must be larger then any other field size below except
                        / blob fields. }

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



  

</xsl:for-each>
Type
  DateRec = record
    Month, Day, Year: word
  end;

  PMoveArray = ^TMoveArray;
  TMoveArray = array[1..10000] of byte; { Used on procedure MoveFromOffset }

{
const
  DefaultRecord1: TRecordType = (FName: 'Jack'; LName: 'Dolittle';
                          Address1: '2734 Seabright Av.';
                          Address2: '108 Santas Village Wy.';
                          City: 'Nowheresville';
                          State: 'CA';
                          Zip: '95837';
                          HPhone: '(408)555-1213';
                          WPhone: '(408)555-1214';
                          EmpId: 2293;
                          StartDate: '12-24-90';
                          EndDate: '01-20-91';
                          Department: 'Marketing';
                          Comments: 'Poor worker, fired promptly.');

  DefaultRecord2: TRecordType = (FName: 'Frank'; LName: 'Zipple';
                          Address1: '11432 1st Av.';
                          Address2: '38322 Branch Av.';
                          City: 'Walla Walla';
                          State: 'AZ';
                          Zip: '93947';
                          HPhone: '(408)555-1220';
                          WPhone: '(408)555-1221';
                          EmpId: 2291;
                          StartDate: '04-01-88';
                          EndDate: '06-24-93';
                          Department: 'Sales';
                          Comments: 'Good worker.  Excellent experience.');

  DefaultRecord3: TRecordType = (FName: 'Stan'; LName: 'Franich';
                          Address1: '1102 Bell St.';
                          Address2: '993 Worthington Wy.';
                          City: 'Soquel';
                          State: 'CA';
                          Zip: '38487';
                          HPhone: '(408)555-1230';
                          WPhone: '(408)555-1231';
                          EmpId: 2093;
                          StartDate: '04-01-80';
                          EndDate: '04-25-94';
                          Department: 'Research';
                          Comments: 'Excellent worker, quit for unknown reasons.');

  DefaultRecord4: TRecordType = (FName: 'Brandy'; LName: 'Giberson';
                          Address1: '1234 845th St.';
                          Address2: '94832 Pacific Wy.';
                          City: 'Portland';
                          State: 'ME';
                          Zip: '28356';
                          HPhone: '(408)555-1240';
                          WPhone: '(408)555-1241';
                          EmpId: 374;
                          StartDate: '10-20-84';
                          EndDate: '04-09-92';
                          Department: 'QA';
                          Comments: 'Great worker.');
}
var
  GlobalDBIErr: DBIResult;

{ Functions }

procedure SetPrivateDir;
procedure AddInitialRecords(hCur: HDBICur);

function FindTablesDir(var Dir: PChar; DirsBack: Byte): Boolean;
function DbInit: DBIResult;
function DbiError(RetVal: DBIResult): DBIResult;
function GetTable(var hDb: hDBIdb; var TblName: PChar; var TblType: PChar; var hCur: hDBICur) : DBIResult;
function CloseDb(hdb: hdbIDb; hCur: hDBICur): DBIResult;
function DeleteRec(hCur: hDBICur): DBIResult;
function GoTop(hCur: hDBICur; MoveRec: BOOL): DBIResult;
function GoBottom(hCur: hDBICur; MoveRec: BOOL): DBIResult;
function GetNextRec(hCur: hDBICur): DBIResult;
function GetPrevRec(hCur: hDBICur): DBIResult;
function AtEOF( hCur: hDBICur): BOOL;
function AtBOF( hCur: hDBICur): BOOL;
function Search(hCur: HDBICur; uCond: DBISearchCond; cKey: pBYTE): DBIResult;
function GetRecordCount(hCur: HDBICur): longint;


implementation

Uses <xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
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
</xsl:variable>	Eng<xsl:value-of select="$FormularId"/><xsl:if test="position()!=last()">,</xsl:if> {<xsl:value-of select="$FormularName"/>}
</xsl:for-each>;

procedure SetPrivateDir;
var
  PrivDir: String;
  PPrivDir: PChar;
  PTmp: PChar;
  Rec: TSearchRec;
  Error: array[0..200] of char;
  IniFile: Boolean;

begin
  GetMem(PPrivDir, 255);
  {Get private directory from .ini file if it exists.}
  GetPrivateProfileString(AppName, 'PrivateDir', '.', PPrivDir, 255, 'BDE.INI');
  {If it does not exist...}
  if PPrivDir[0] = '.' then
  begin
    IniFile := False;
    {Derive directory from executable directory.}
    PrivDir := ParamStr(0);
    StrPCopy(PPrivDir, PrivDir);
    PTmp := StrRScan(PPRivDir, '\');
    PTmp^ := #0;
    DBISetPrivateDir(PPrivDir);
  end
  else
    IniFile := True;
  {Make sure the directory exists.}
  FindFirst(PPrivDir, faDirectory, Rec);
  if DosError &lt;&gt; 0 then
  begin
    StrCopy(Error, 'Error setting private directory to ');
    StrCat(Error, PPrivDir);
    StrCat(Error, '.  Using current directory.');
    if IniFile = True then
      StrCat (Error, '  Check BDE.INI file for private directory setting.');
    MessageBox(0, Error, 'Warning', mb_Ok or mb_IconInformation);
    {By default, the private directory is set to current drectory if DBISetPrivateDir
     is not used or an error has occured setting private directory.}
  end;
  FreeMem(PPrivDir, 255);
end;


function FindTablesDir(var Dir: PChar; DirsBack: Byte): Boolean;
var
  TblDir: String[dbiMAXPATHLEN + 1];
  PTblDir: PChar;
  B: Byte;
  Rec: TSearchRec;
  Error: array[0..200] of char;
  IniFile: Boolean;

begin
  {Get private directory from .ini file if it exists.}
  GetPrivateProfileString(AppName, 'TblDir', '.', Dir, 255, 'BDE.INI');
  {If it does not exist...}
  if Dir[0] = '.' then
  begin
    IniFile := False;
    {Derive table directory from executable directory.}
    TblDir := ParamStr(0);
    StrPCopy(Dir, TblDir);
    for B := 1 to DirsBack do
    begin
      PTblDir := Dir;
      PTblDir := StrRScan(PTblDir, '\');
      if PTblDir = nil then
      begin
        BWCCMessageBox(0, 'An error occured finding tables directory!',
                       'ERROR', mb_OK or mb_IconExclamation);
        {Use relative path since a absolute path could not be found.}
        StrCopy(Dir, '..\..\TABLES');
        FindTablesDir := False;
        Break;
      end
      else
        PTblDir^ := #0;
    end;
    if Dir[0] &lt;&gt; '.' then
    begin
      {Directory extraction worked.}
      StrCat(Dir, '\TABLES');
      FindTablesDir := True;
    end;
  end
  else
    IniFile := True;
  {Make sure the directory exists.}
  FindFirst(Dir, faDirectory, Rec);
  if DosError &lt;&gt; 0 then
  begin
    StrCopy(Error, 'Error setting tables directory to ');
    StrCat(Error, Dir);
    StrCat(Error, '.  Using relative path ..\..\TABLES.');
    if IniFile = True then
      StrCat (Error, '  Check BDE.INI file for table directory setting.');

    MessageBox(0, Error, 'Warning', mb_Ok or mb_IconInformation);
    StrCopy(Dir, '..\..\TABLES');
  end;
end;

procedure AddInitialRecords(hCur: hDBICur);
begin
{
  if AddRecord(hCur, @DefaultRecord1, true) &lt;&gt; DBIERR_NONE then
     BWCCMessageBox(0, 'Error Adding Record', 'Error!', mb_ok);
  if AddRecord(hCur, @DefaultRecord2, true) &lt;&gt; DBIERR_NONE then
     BWCCMessageBox(0, 'Error Adding Record', 'Error!', mb_ok);
  if AddRecord(hCur, @DefaultRecord3, true) &lt;&gt; DBIERR_NONE then
     BWCCMessageBox(0, 'Error Adding Record', 'Error!', mb_ok);
  if AddRecord(hCur, @DefaultRecord4, true) &lt;&gt; DBIERR_NONE then
     BWCCMessageBox(0, 'Error Adding Record', 'Error!', mb_ok);
}
end;

procedure MoveFromOffset(var Source: TMoveArray; var Dest; FromOffset, Size: word);
var
  L: LongInt;

begin
  L := (FromOffset - 1) * Size + 1;
  move(Source[L], Dest, Size);
end;

function GetHexWord(w: Word): String;
const
  hexChars: array [0..$F] of Char =
    '0123456789ABCDEF';
begin
  GetHexWord := hexChars[Hi(w) shr 4] +
        hexChars[Hi(w) and $F] +
        hexChars[Lo(w) shr 4] +
        hexChars[Lo(w) and $F];
end;
{=============================================================================
/  Name:   DbiError
/  Description: This is function displays that is a message box about the
/  error that occured.
=============================================================================}

function DbiError(RetVal: DBIResult): DBIResult;
var
  DbiErrString: array[0..128] of char;
  ResStr: array[0..20] of char;
  S: String;
begin
  S := GetHexWord(RetVal);
  StrPCopy(ResStr, S);

  if (retVal = DBIERR_NONE) then
    GlobalDBIErr := DBIERR_NONE
  else
  begin
     GlobalDBIErr := RetVal;
     DbiGetErrorString(retVal, DbiErrString); { Get the error message }
     BWCCMessageBox(0, DbiErrString, ResStr, mb_ok);
  end;
  DbiError := retVal;
end;

{=============================================================================
/  Name:   SetDate
/  Desc:   This function puts the date that is in the PChar into the
/          Date variable.
=============================================================================}

function SetDate(var Dt: Longint; DateString: PChar): DBIResult;
var
    MonthInt: word;
    DayInt: word;
    YearInt: word;
    MonthAry: array[0..2] of char;
    DayAry: array[0..2] of char;
    YearAry: array[0..4] of char;
    Code: integer;
    RetVal: DBIResult;
begin
    { Get the first two month's numbers (the first two numbers). }
    strLCopy(MonthAry, DateString, 2);
    strLCopy(DayAry, @DateString[3], 2);
    strLCopy(YearAry, @DateString[6], 4);
    val(MonthAry, MonthInt, Code);
    val(DayAry, DayInt, Code);
    val(YearAry, YearInt, Code);

    RetVal := DbiDateEncode(MonthInt, DayInt, YearInt, Dt);
    if RetVal &lt;&gt; DBIERR_NONE then
       BWCCMessageBox(0, 'Invalid Date Format', 'Error', mb_OK);
    SetDate := RetVal;
end;

{=============================================================================
/  Name:   DbInit
/  Desc:   This function starts up the engine.
=============================================================================}
function DbInit: DBIResult;
var
  PEnv: PDbiEnv;
  rslt: DBIResult;
begin
  PEnv := nil;
  rslt := DbiError(DbiInit(PEnv));
  if (rslt &lt;&gt; DBIERR_NONE) then
  begin
       Dbinit := rslt;
       exit;
  end;

  DbiDebugLayerOptions(11, 'EMPLOYEE.INF');

  DbInit := rslt;

end;

{=============================================================================
/  Name:   GetTable
/  Desc:   This function opens a database and a table.
=============================================================================}
function GetTable(var hDb: hDBIdb; var TblName: PChar; var TblType: PChar; var hCur: hDBICur) : DBIResult;
var
  S: array[0..100] of Char;
  TableDir: PChar;
begin
    GetMem(TableDir, dbiMAXPATHLEN + 1);
    FindTablesDir(TableDir, 3);
    { Open a standard database handle }
    DbiError(DbiOpenDatabase(nil, nil, dbiREADWRITE, dbiOPENSHARED,
                             nil, 0, nil, nil, hdb));
    if (GlobalDBIErr &lt;&gt; DBIERR_NONE) then
    begin
      GetTable := GlobalDBIErr;
      Exit;
    end;
    { Set the directory for the table handle }
    DbiError(DbiSetDirectory(hdb, TableDir));

    { Now open the table to acquire a cursor on the table. }
    DbiError(DbiOpenTable(hdb, TblName, TblType, nil, nil, 0,
             dbiREADWRITE, dbiOPENSHARED,
             xltFIELD, FALSE, nil, hCur));
    if (GlobalDBIErr &lt;&gt; DBIERR_NONE) then
      GetTable := GlobalDBIErr
    else
      GetTable := DBIERR_NONE;
    FreeMem(TableDir, dbiMAXPATHLEN + 1);
end;


{=============================================================================
/  Name:   DeleteRec
/  Desc:   This function deletes the record that is pointed to by the
/          cursor.
=============================================================================}

function DeleteRec (hCur: hDBICur): DBIResult;
begin
    DbiError(DbiGetRecord(hCur, dbiWRITELOCK, nil, nil));
    DbiError(DbiDeleteRecord(hCur, nil));
    DeleteRec := GlobalDBIErr;
end; { DeleteRec }


{=============================================================================
/  Name:   GetPrevRec
/  Desc:   This function moves one record backwards.
=============================================================================}
function GetPrevRec(hCur: hDBICur): DBIResult;
begin
    DbiError(DbiGetPriorRecord(hCur, dbiNOLOCK, nil, nil));
    GetPrevRec := GlobalDBIErr;
end;

{=============================================================================
/  Name:   GoBottom
/  Desc:   This function moves to the bottom of the table, and moves one
/          record back if MoveRec (BOOL) is TRUE.
=============================================================================}
function GoBottom (hCur: hDBICur; MoveRec: BOOL): DBIResult;
begin
    DbiError(DbiSetToEnd(hCur));
    if(MoveRec) then
        GetPrevRec(hCur);
    GoBottom := GlobalDBIErr;
end;

{=============================================================================
/  Name:   GetNextRec
/  Desc:   This function moves one record forward.
=============================================================================}
function GetNextRec (hCur: hDBICur): DBIResult;
begin
  DbiError(DbiGetNextRecord(hCur, dbiNOLOCK, nil, nil));
  GetNextRec := GlobalDBIErr;
end;

{=============================================================================
/  Name:   GoTop
/  Desc:   This function moves to the top of the table, and moves one
/          record forward if MoveRec (BOOL) is TRUE.
=============================================================================}
function GoTop (hCur: hDBICur; MoveRec: BOOL): DBIResult;
begin
  DbiError(DbiSetToBegin(hCur));
  if(MoveRec) then
    GetNextRec(hCur);
  GoTop := GlobalDBIErr;
end;

{=============================================================================
/  Name:   AtEOF
/  Desc:   This function moves one record forward to test if the cursor
/          is at the EOF, and then moves back to put the cursor at the
/          place it was before jumping to the function.
=============================================================================}
function AtEOF ( hCur: hDBICur): BOOL;
var
  rslt: DBIResult;
  RetVal: BOOL;
begin
  { Check if we are at the end of the table. }

  rslt := DbiGetNextRecord(hCur, dbiNOLOCK, nil, nil);
  if(rslt = DBIERR_NONE) then
  begin
    RetVal := false
  end
  else
  begin
    RetVal := true;
  end;
  { Now put the cursor back to where it was before entering this function. }
  DbiGetPriorRecord(hCur, dbiNOLOCK, nil, nil);
  AtEOF := RetVal;
end;

{=============================================================================
/  Name:   AtBOF
/  Desc:   This function moves one record backwards to test if the cursor
/          is at the BOF.  Then it moves the cursor one record forward to
/          put it back to where it was originally.
=============================================================================}
function AtBOF (hCur: hDBICur): BOOL;
var
  rslt: DBIResult;
  RetVal: BOOL;
begin
  { Check if we are at the end of the table. }
  rslt := DbiGetPriorRecord(hCur, dbiNOLOCK, nil, nil);
  if(rslt = DBIERR_NONE) then
    RetVal := false
  else
    RetVal := true;
  { Now put the cursor back to where it was before entering this function. }
  DbiGetNextRecord(hCur, dbiNOLOCK, nil, nil);
  AtBOf := RetVal;
end;

{=============================================================================
/  Name:   CloseDb
/  Desc:   This function closes the table based upon the table pointer
/          that was passed into the function.
=============================================================================}
function CloseDb (hdb: hdbIDb; hCur: hDBICur): DBIResult;
begin
  if DbiCloseCursor(hCur) &lt;&gt; dbierr_None then
    BWCCMessageBox(0, 'Error closing cursor', 'ERROR', mb_Ok);

  if DbiCloseDatabase(hdb) &lt;&gt; dbierr_None then
      BWCCMessageBox(0, 'Error closing database', 'ERROR in wmClose', mb_Ok);
  CloseDb := DbiExit;
end;

{=============================================================================
/  Name:   Search()
/  Desc:   This function searches for a string based upon the index that
/          is presently active on the table.
=============================================================================}
function Search (hCur: HDBICur; uCond: DBISearchCond; cKey: pBYTE): DBIResult;
var
  Result: DBIResult;
  STblProps: CURProps;
  SIdxDesc: IDXDesc;
  SFldDesc: FLDDesc;
  FldDescAry: PMoveArray;
  FldNum: Integer;
  TempDoub: double;
  TempInt: integer;
  RecBuf: pBYTE;
  code: integer;
  RetVal: DBIResult;
begin
  { Get information about the current index }
  DBIError(DbiGetIndexDesc(hCur, 0, SidxDesc));

  if SidxDesc.bExpIdx = True then
  begin
    Result := DbiSetToKey(hCur, uCond, True, 0, 0, cKey);
    { Display an error message if an error other than Record not Found
    / is detected.}
    if ((Result &lt;&gt; DBIERR_NONE) and ( Result &lt;&gt; DBIERR_RECNOTFOUND)) then
      DBIError(Result);

    Search := Result;
    exit;
  end;

  { Determine the first field of the Index }
  FldNum := SidxDesc.aiKeyFld[0];

  { Get information about the cursor - needed to determine the number
  / of fields in the table. }
  DBIError(DbiGetCursorProps(hCur, STblProps));

  { Allocate a Field descriptior large enough to contain information about
  / all fields in the table. }
  getmem(FldDescAry, sizeof(FldDesc)*STblProps.iFields);

  { Get the field descriptors - needed to determine the type of the
  / first field of the index.}
  DBIError(DbiGetFieldDescs(hCur, PFldDesc(FldDescAry)));
{  procedure MoveFromOffset(var Source: TMoveArray; var Dest; FromOffset, Size: word);}
  MoveFromOffset(FldDescAry^, SFldDesc, FldNum, sizeof(FldDesc));

  getmem(RecBuf, sizeof(STblProps.iRecBufSize));

  { Initialize the record buffer }
  DBIError(DbiInitRecord(hCur, RecBuf));
  { Write the data to the record buffer. }
  case SFldDesc.iFldType of
    fldINT16:
      begin
        val(PChar(cKey), TempInt, code);
        DBIError(DbiPutField(hCur, FldNum, RecBuf, @TempInt));
      end;
    fldFLOAT:
      begin
        val(PChar(cKey), TempDoub, code);
        DBIError(DbiPutField(hCur, FldNum, RecBuf, @TempDoub));
      end;
    fldZSTRING:
      begin
        DBIError(DbiPutField(hCur, FldNum, RecBuf, cKey));
      end;
  else
    begin
      BWCCMessageBox(0, 'Cannot Search Expression Indexes', 'Message',
                     MB_ICONHAND or MB_OK);
      freemem(FldDescAry, sizeof(FldDesc)*STblProps.iFields);
      freemem(RecBuf, sizeof(STblProps.iRecBufSize));
      RetVal := DBIERR_NOTSUPPORTED;
      exit;
    end;
  end; { case }

  { Perform the actual search on the table. }
  Result := DbiSetToKey(hCur, uCond, FALSE, 0, 0, RecBuf);

  { Display an error message if an error other than Record not Found
  / is detected.}
  if ((Result &lt;&gt; DBIERR_NONE) and ( Result &lt;&gt; DBIERR_RECNOTFOUND)) then
    DBIError(Result);

  freemem(FldDescAry, sizeof(FldDesc)*STblProps.iFields);
  freemem(RecBuf, sizeof(STblProps.iRecBufSize));
  Search := Result;
end;


function GetRecordCount(hCur: HDBICur): longint;
var
  TblProps: CURProps;     { Table Properties }
  PBookMark: Pointer;
  RecCount: longint;
  rslt: DBIResult;
begin
  { Return 0 if the table is empty }
  rslt := DbiGetNextRecord(hCur, dbiNOLOCK, nil, nil);
  if (rslt &lt;&gt; DBIERR_NONE) then
  begin
    rslt := DbiGetPriorRecord(hCur, dbiNOLOCK, nil, nil);
    if (rslt &lt;&gt; DBIERR_NONE) then
    begin
      GetRecordCount := 0;
      exit;
    end;
    { Reset the current location if no error }
    DbiGetNextRecord(hCur, dbiNOLOCK, nil, nil);
  end
  else begin
    { Reset the current location if no error }
    DbiGetPriorRecord(hCur, dbiNOLOCK, nil, nil);
  end;

  { Count the number of records }

  RecCount := 0;
  DbiError(DbiGetCursorProps(hCur, TblProps));
  GetMem(PBookMark, TblProps.iBookMarkSize);
  DbiError(DbiGetBookMark(hCur, PBookMark));
  DbiSetToBegin(hCur);
  while DbiGetNextRecord(hCur, dbiNOLOCK, nil, nil) = DBIERR_NONE do
  begin
    inc(RecCount);
  end;
  DbiError(DbiSetToBookMark(hCur, PBookMark));
  FreeMem(PBookMark, TblProps.iBookMarkSize);
  GetRecordCount := RecCount;
end;

begin
end.
</exsl:document>


</xsl:template>

</xsl:stylesheet>

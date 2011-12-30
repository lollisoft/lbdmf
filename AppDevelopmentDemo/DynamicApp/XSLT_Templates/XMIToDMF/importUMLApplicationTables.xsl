<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" xmlns:lbDMF="lbDMF">
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
<xsl:output method="text"/>

<xsl:template name="importApplicationTablePrimaryKeys">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- Generate application tables <xsl:value-of select="@name"/> for <xsl:value-of select="$ApplicationName"/> primary keys. Tagtet database: '<xsl:value-of select="$TargetDatabaseType"/>'

<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
		<xsl:call-template name="createPrimaryKeys">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
		<xsl:call-template name="createPrimaryKeys">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
-- Skipped, due to creation in template 'importApplicationTable'
<!--
		<xsl:call-template name="createPrimaryKeys">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
-->
	</xsl:when>
</xsl:choose>
</xsl:template>

<xsl:template name="importApplicationTable">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- Generate application table <xsl:value-of select="@name"/> for <xsl:value-of select="$ApplicationName"/>. Tagtet database: '<xsl:value-of select="$TargetDatabaseType"/>'

<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
		<xsl:call-template name="createPostgreSQLTable">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
		<xsl:call-template name="createMSSQLTable">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
		<xsl:call-template name="createSqliteTable">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
</xsl:choose>
</xsl:template>

<xsl:template name="dropApplicationTable">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- Generate application table <xsl:value-of select="@name"/> for <xsl:value-of select="$ApplicationName"/>. Tagtet database: '<xsl:value-of select="$TargetDatabaseType"/>'

<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
		<xsl:call-template name="dropPostgreSQLTable">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
		<xsl:call-template name="dropMSSQLTable">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
		<xsl:call-template name="dropSqliteTable">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
</xsl:choose>
</xsl:template>

<!-- Initial import for classes that have no stereotype attached. -->
<xsl:template name="importApplicationTableAutoID">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- Generate application table <xsl:value-of select="@name"/> for <xsl:value-of select="$ApplicationName"/>

<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
		<xsl:call-template name="createPostgreSQLTableAutoID">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
		<xsl:call-template name="createMSSQLTableAutoID">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
		<xsl:call-template name="createSqliteTableAutoID">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
</xsl:choose>
</xsl:template>

<xsl:template name="importApplicationTableRelation">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>

<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
-- Generate PostgreSQL application relations for table <xsl:value-of select="@name"/> for <xsl:value-of select="$ApplicationName"/>
		<xsl:call-template name="createPostgreSQLTableRelation">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
-- Generate MSSQL application relations for table <xsl:value-of select="@name"/> for <xsl:value-of select="$ApplicationName"/>
		<xsl:call-template name="createMSSQLTableRelation">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
-- Generate Sqlite application relations for table <xsl:value-of select="@name"/> for <xsl:value-of select="$ApplicationName"/>
		<xsl:call-template name="createSqliteTableRelation">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
</xsl:choose>
</xsl:template>

<xsl:template name="importApplicationTableRelationAutoID">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- Generate application table <xsl:value-of select="@name"/> for <xsl:value-of select="$ApplicationName"/>

<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
		<xsl:call-template name="createPostgreSQLTableRelationAutoID">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
		<xsl:call-template name="createMSSQLTableRelationAutoID">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
		<xsl:call-template name="createSqliteTableRelationAutoID">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
</xsl:choose>
</xsl:template>

<xsl:template name="importApplicationDropTableRelation">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- Drop application table <xsl:value-of select="@name"/> for <xsl:value-of select="$ApplicationName"/>

<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
		<xsl:call-template name="dropPostgreSQLTableRelation">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
		<xsl:call-template name="dropMSSQLTableRelation">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
		<xsl:call-template name="dropSqliteTableRelation">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
</xsl:choose>
</xsl:template>


<xsl:template name="dropSqliteTable">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- DROP TABLE <xsl:value-of select="$TableName"/>
DROP TABLE IF EXISTS "<xsl:value-of select="$TableName"/>";
</xsl:template>

<xsl:template name="dropMSSQLTable">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- DROP TABLE <xsl:value-of select="$TableName"/>
exec lbDMF_dropTable '<xsl:value-of select="$TableName"/>';
</xsl:template>

<xsl:template name="dropPostgreSQLTable">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
select "dropTable"('<xsl:value-of select="$TableName"/>');
</xsl:template>





<xsl:template name="createSqliteTable">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- CREATE Sqlite TABLE <xsl:value-of select="$TableName"/>
CREATE TABLE "<xsl:value-of select="$TableName"/>" (<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']"><xsl:variable name="Aggregation" select="@aggregation"/><xsl:choose>
	<xsl:when test="$Aggregation='none'">
		<xsl:if test="@name!=''">
		<xsl:if test="./lowerValue/@value='1'">
		<xsl:if test="./upperValue/@value='1'">
			<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
			<xsl:variable name="datatype" select="//packagedElement[@xmi.id=$datatypeid]/@name"/><xsl:if test="position()!=1">,
	</xsl:if>
	<xsl:call-template name="createDBTypeForeignKeyColumn"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template>	
		</xsl:if>
		</xsl:if>
		</xsl:if>
	</xsl:when>
	<xsl:otherwise>
		<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
		<xsl:variable name="datatype" select="//packagedElement[@xmi.id=$datatypeid]/@name"/>
		<xsl:choose>
			<xsl:when test="$datatype='bigstring'"></xsl:when>
			<xsl:when test="$datatype='image'"></xsl:when>
<xsl:otherwise><xsl:if test="position()!=1">,</xsl:if>
	"<xsl:value-of select="@name"/>" <xsl:call-template name="createDBType"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template></xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
);
</xsl:template>

<xsl:template name="createMSSQLTable">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- CREATE TABLE <xsl:value-of select="$TableName"/>
CREATE TABLE "<xsl:value-of select="$TableName"/>" (
	<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']"><xsl:if test="position()!=1">,</xsl:if>
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:choose>
	<xsl:when test="$Aggregation='none'">
--</xsl:when>
	<xsl:otherwise>
		<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
		<xsl:variable name="datatype" select="//packagedElement[@xmi.id=$datatypeid]/@name"/>
		<xsl:choose>
			<xsl:when test="$datatype='bigstring'"></xsl:when>
			<xsl:when test="$datatype='image'"></xsl:when>
<xsl:otherwise>
	"<xsl:value-of select="@name"/>" <xsl:call-template name="createDBType"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template></xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
);
</xsl:template>

<xsl:template name="createPostgreSQLTable">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>

-- CREATE TABLE <xsl:value-of select="$TableName"/>
CREATE TABLE "<xsl:value-of select="$TableName"/>" (<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']"><xsl:variable name="Aggregation" select="@aggregation"/><xsl:choose>
	<xsl:when test="$Aggregation='none'"><!--
		<xsl:if test="./lowerValue/@value='1'">
		<xsl:if test="./upperValue/@value='1'">
			<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
			<xsl:variable name="datatype" select="//packagedElement[@xmi.id=$datatypeid]/@name"/><xsl:if test="position()!=1">,
	</xsl:if>
	<xsl:call-template name="createDBTypeForeignKeyColumn"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template>	
		</xsl:if>
		</xsl:if>-->
	</xsl:when>
	<xsl:otherwise>
		<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
		<xsl:variable name="datatype" select="//packagedElement[@xmi.id=$datatypeid]/@name"/>
		<xsl:choose>
			<xsl:when test="$datatype='bigstring'"></xsl:when>
			<xsl:when test="$datatype='image'"></xsl:when>
<xsl:otherwise><xsl:if test="position()!=1">,</xsl:if>
	"<xsl:value-of select="@name"/>" <xsl:call-template name="createDBType"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template></xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
) WITH OIDS;
</xsl:template>

<!-- ** Tables with autoID creation ** -->

<xsl:template name="createSqliteTableAutoID">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- CREATE TABLE <xsl:value-of select="$TableName"/> with auto id
CREATE TABLE "<xsl:value-of select="$TableName"/>" (
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:choose>
	<xsl:when test="$Aggregation='shared'">
		<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
		<xsl:variable name="datatype" select="//packagedElement[@xmi:id=$datatypeid]/@name"/>
		<xsl:choose>
			<xsl:when test="$datatype='bigstring'"></xsl:when>
			<xsl:when test="$datatype='image'"></xsl:when>
			<xsl:otherwise>
			<xsl:if test="@name=''">--</xsl:if><xsl:if test="@name!=''"><xsl:if test="contains(@name,'anonymous_role')"><xsl:if test="position()!=1">,
</xsl:if>	"<xsl:value-of select="$datatype"/>" INTEGER</xsl:if></xsl:if>
			<xsl:if test="@name!=''"><xsl:if test="contains(@name,'anonymous_role') != '1'"><xsl:if test="position()!=1">,
</xsl:if>	"<xsl:value-of select="@name"/>" INTEGER
					</xsl:if>
				</xsl:if>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:when>
	<xsl:when test="$Aggregation='none'">
	</xsl:when>
	<xsl:when test="$Aggregation=''">
	</xsl:when>
	<xsl:otherwise>
		<xsl:variable name="datatypeid" select="./type/@xmi:idref"/>
		<xsl:variable name="datatype" select="//packagedElement[@xmi:id=$datatypeid]/@name"/><xsl:if test="position()!=1">,</xsl:if>
	"<xsl:value-of select="@name"/>" <xsl:call-template name="createDBType"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template></xsl:otherwise>
</xsl:choose>
</xsl:for-each>,

	"ID" INTEGER PRIMARY KEY
);
</xsl:template>

<xsl:template name="createMSSQLTableAutoID">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- CREATE TABLE <xsl:value-of select="$TableName"/>
CREATE TABLE "<xsl:value-of select="$TableName"/>" (
	"ID" INTEGER IDENTITY (1, 1) NOT NULL,
	CONSTRAINT "<xsl:value-of select="$TableName"/>_pkey" PRIMARY KEY ("ID"),
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']"><xsl:if test="position()!=1">,</xsl:if>
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:choose>
	<xsl:when test="$Aggregation='none'">
--</xsl:when>
	<xsl:otherwise>
		<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
		<xsl:variable name="datatype" select="//packagedElement[@xmi.id=$datatypeid]/@name"/>
		<xsl:choose>
			<xsl:when test="$datatype='bigstring'"></xsl:when>
			<xsl:when test="$datatype='image'"></xsl:when>
<xsl:otherwise>
	"<xsl:value-of select="@name"/>" <xsl:call-template name="createDBType"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template></xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
);
</xsl:template>

<xsl:template name="createPostgreSQLTableAutoID">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- CREATE TABLE <xsl:value-of select="$TableName"/>
CREATE TABLE "<xsl:value-of select="$TableName"/>" (
	"ID" SERIAL,
	CONSTRAINT "<xsl:value-of select="$TableName"/>_pkey" PRIMARY KEY ("ID"),
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']"><xsl:if test="position()!=1">,</xsl:if>
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:choose>
	<xsl:when test="$Aggregation='none'">
--</xsl:when>
	<xsl:otherwise>
		<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
		<xsl:variable name="datatype" select="//packagedElement[@xmi.id=$datatypeid]/@name"/>
		<xsl:choose>
			<xsl:when test="$datatype='bigstring'"></xsl:when>
			<xsl:when test="$datatype='image'"></xsl:when>
<xsl:otherwise>
	"<xsl:value-of select="@name"/>" <xsl:call-template name="createDBType"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template></xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
) WITH OIDS;
</xsl:template>


<!-- ****************************************** -->


<xsl:template name="createPostgreSQLTableRelation">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:if test="./xmi:Extension/stereotype/@name='lbDMF:fk'">
ALTER TABLE "<xsl:value-of select="../@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/>_<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/>" ( "<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>" );
</xsl:if>
</xsl:for-each>
</xsl:template>

<!-- New version of generating foreign key rules based on attribute tagged values -->
<xsl:template name="createSqliteTableRelation">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- Create table relations for <xsl:value-of select="$TableName"/>
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:if test="./xmi:Extension/stereotype/@name='lbDMF:fk'">
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "<xsl:value-of select="../@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="../@name"/>_<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/>_<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/>" ( "<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_ins" BEFORE INSERT ON <xsl:value-of select="../@name"/> FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.<xsl:value-of select="@name"/> IS NOT NULL) AND ((SELECT <xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/> FROM <xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/> WHERE <xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/> = new.<xsl:value-of select="@name"/>) IS NULL))
                 THEN RAISE(ABORT, '<xsl:value-of select="@name"/> violates foreign key <xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/>(<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>)')
    END;
END;
CREATE TRIGGER "fk_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_upd" BEFORE UPDATE ON <xsl:value-of select="../@name"/> FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.<xsl:value-of select="@name"/> IS NOT NULL) AND ((SELECT <xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/> FROM <xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/> WHERE <xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/> = new.<xsl:value-of select="@name"/>) IS NULL))
                 THEN RAISE(ABORT, '<xsl:value-of select="@name"/> violates foreign key <xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/>(<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>)')
    END;
END;
CREATE TRIGGER "fk_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_del" BEFORE DELETE ON <xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/> FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT <xsl:value-of select="@name"/> FROM <xsl:value-of select="../@name"/> WHERE <xsl:value-of select="@name"/> = old.<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key <xsl:value-of select="../@name"/>(<xsl:value-of select="@name"/>)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/>', '<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>', '<xsl:value-of select="../@name"/>', '<xsl:value-of select="@name"/>');
 

</xsl:if>

<xsl:if test="./xmi:Extension/stereotype/@name='lbDMF:relationship'">
<xsl:if test="./lowerValue/@value='1'">
<xsl:if test="./upperValue/@value='1'">

<xsl:variable name="PrimaryTableId" select="./type/@xmi:idref"/>

<xsl:variable name="PrimaryTable" select="//packagedElement[@xmi:id=$PrimaryTableId]/@name"/>
<xsl:variable name="PrimaryTableSourceColumn" select="//packagedElement[@xmi:id=$PrimaryTableId]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>
--ALTER TABLE "<xsl:value-of select="../@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="../@name"/>_<xsl:value-of select="$PrimaryTable"/>_<xsl:value-of select="$PrimaryTableSourceColumn"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="$PrimaryTable"/>" ( "<xsl:value-of select="$PrimaryTableSourceColumn"/>" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "<xsl:value-of select="../@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="../@name"/>_<xsl:value-of select="$PrimaryTable"/>_<xsl:value-of select="$PrimaryTableSourceColumn"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="$PrimaryTable"/>" ( "<xsl:value-of select="$PrimaryTableSourceColumn"/>" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_ins" BEFORE INSERT ON <xsl:value-of select="../@name"/> FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.<xsl:value-of select="@name"/> IS NOT NULL) AND ((SELECT <xsl:value-of select="$PrimaryTableSourceColumn"/> FROM <xsl:value-of select="$PrimaryTable"/> WHERE <xsl:value-of select="$PrimaryTableSourceColumn"/> = new.<xsl:value-of select="@name"/>) IS NULL))
                 THEN RAISE(ABORT, '<xsl:value-of select="@name"/> violates foreign key <xsl:value-of select="$PrimaryTable"/>(<xsl:value-of select="$PrimaryTableSourceColumn"/>)')
    END;
END;
CREATE TRIGGER "fk_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_upd" BEFORE UPDATE ON <xsl:value-of select="../@name"/> FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.<xsl:value-of select="@name"/> IS NOT NULL) AND ((SELECT <xsl:value-of select="$PrimaryTableSourceColumn"/> FROM <xsl:value-of select="$PrimaryTable"/> WHERE <xsl:value-of select="$PrimaryTableSourceColumn"/> = new.<xsl:value-of select="@name"/>) IS NULL))
                 THEN RAISE(ABORT, '<xsl:value-of select="@name"/> violates foreign key <xsl:value-of select="$PrimaryTable"/>(<xsl:value-of select="$PrimaryTableSourceColumn"/>)')
    END;
END;
CREATE TRIGGER "fk_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_del" BEFORE DELETE ON <xsl:value-of select="$PrimaryTable"/> FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT <xsl:value-of select="@name"/> FROM <xsl:value-of select="../@name"/> WHERE <xsl:value-of select="@name"/> = old.<xsl:value-of select="$PrimaryTableSourceColumn"/>) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key <xsl:value-of select="../@name"/>(<xsl:value-of select="@name"/>)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('<xsl:value-of select="$PrimaryTable"/>', '<xsl:value-of select="$PrimaryTableSourceColumn"/>', '<xsl:value-of select="../@name"/>', '<xsl:value-of select="@name"/>');
 
</xsl:if>
</xsl:if>
</xsl:if>

</xsl:for-each>
</xsl:template>

<xsl:template name="createMSSQLTableRelation">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']"><xsl:variable name="Aggregation" select="@aggregation"/><xsl:if test="$Aggregation='none'">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/><!--<xsl:if test="position()=1">,</xsl:if>-->
	<xsl:call-template name="createDBType"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template></xsl:if>
</xsl:for-each>
</xsl:template>

<!-- ****************************************** -->

<xsl:template name="dropPostgreSQLTableRelation">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:if test="./xmi:Extension/stereotype/@name='lbDMF:fk'">
<!--
ALTER TABLE "<xsl:value-of select="../@name"/>" DROP CONSTRAINT "cst_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/>_<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>";
-->
select "dropConstraint"('<xsl:value-of select="../@name"/>', 'cst_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/>_<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>');
</xsl:if>
</xsl:for-each>
</xsl:template>

<xsl:template name="dropSqliteTableRelation">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:if test="./xmi:Extension/stereotype/@name='lbDMF:fk'">
--ALTER TABLE "<xsl:value-of select="../@name"/>" DROP CONSTRAINT "cst_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/>_<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/>" ( "<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>" );

DROP TRIGGER IF EXISTS 'fk_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_ins';
DROP TRIGGER IF EXISTS 'fk_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_upd';
DROP TRIGGER IF EXISTS 'fk_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_del';

<!--
DROP TRIGGER 'fk_nullable_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_ins';
DROP TRIGGER 'fk_nullable_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_upd';
DROP TRIGGER 'fk_nullable_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_del';
-->

DELETE FROM "lbDMF_ForeignKeys" where FKTable = '<xsl:value-of select="../@name"/>' AND FKColumn = '<xsl:value-of select="@name"/>';

</xsl:if>
</xsl:for-each>
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
				<xsl:if test="$lowerValue='1'"><xsl:if test="$upperValue='1'"><!--<xsl:if test="position()!=1">,</xsl:if>-->
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>
<xsl:variable name="primaryKey"><xsl:if test="//packagedElement[@xmi:id=$primaryTableID]/@xmi:type='uml:DataType'"><!-- A foreign key over a type other than int, I think. -->
<xsl:value-of select="./@name"/>
</xsl:if><xsl:if test="//packagedElement[@xmi:id=$primaryTableID]/@xmi:type='uml:Class'"><!-- A real foreign key -->
<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>
</xsl:if></xsl:variable>
<xsl:variable name="AssocID" select="./@association"/>
<xsl:variable name="AttributeID" select="./@xmi:id"/>
<xsl:variable name="foreignKey" select="//ownedAttribute[@association=$AssocID][@xmi:id!=$AttributeID]/@name"/>
<xsl:variable name="primaryTableID1" select="//ownedAttribute[@association=$AssocID][@xmi:id!=$AttributeID]/../@name"/>	

DROP TRIGGER IF EXISTS 'fk_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_ins';
DROP TRIGGER IF EXISTS 'fk_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_upd';
DROP TRIGGER IF EXISTS 'fk_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_del';

DELETE FROM "lbDMF_ForeignKeys" where FKTable = '<xsl:value-of select="../@name"/>' AND FKColumn = '<xsl:value-of select="@name"/>';
</xsl:if>
			</xsl:if>
</xsl:for-each>
</xsl:template>

<xsl:template name="dropMSSQLTableRelation">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']"><xsl:variable name="Aggregation" select="@aggregation"/><xsl:if test="$Aggregation='none'">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/><!--<xsl:if test="position()=1">,</xsl:if>-->
	<xsl:call-template name="dropDBType"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template></xsl:if>
</xsl:for-each>
</xsl:template>

<!-- ****************************************** -->


<xsl:template name="createPostgreSQLTableRelationAutoID">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']"><xsl:variable name="Aggregation" select="@aggregation"/><xsl:if test="$Aggregation='none'">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/><!--<xsl:if test="position()=1">,</xsl:if>-->
	<xsl:call-template name="createDBTypeAutoID"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template></xsl:if>
</xsl:for-each>
</xsl:template>

<xsl:template name="createSqliteTableRelationAutoID">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- Create table relations for <xsl:value-of select="$TableName"/> with auto id
	
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']"><xsl:variable name="Aggregation" select="@aggregation"/><xsl:if test="$Aggregation='none'">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/><!--<xsl:if test="position()=1">,</xsl:if>-->
	<xsl:call-template name="createDBTypeAutoID"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template></xsl:if>
</xsl:for-each>
</xsl:template>

<xsl:template name="createMSSQLTableRelationAutoID">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']"><xsl:variable name="Aggregation" select="@aggregation"/><xsl:if test="$Aggregation='none'">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/><!--<xsl:if test="position()=1">,</xsl:if>-->
	<xsl:call-template name="createDBTypeAutoID"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template></xsl:if>
</xsl:for-each>
</xsl:template>



<xsl:template name="createPostgreSQLColumn">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="ColumnName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>

	"<xsl:value-of select="$TableName"/>" <xsl:call-template name="createDBType"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template>

</xsl:template>


  <xsl:template name="genQueryForeignKeyColumns">
    <xsl:param name="id"/>
    <xsl:param name="package"/>
	<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property'][@association='none']">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/>"<xsl:value-of select="//packagedElement[@xmi:type='uml:Class'][@xmi:id='otherClassID']/@name"/>"</xsl:for-each>
  </xsl:template>




<xsl:template name="createDBTypeAutoID">
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
<xsl:variable name="DatatypeID" select="./type/@xmi:idref"/>
<xsl:variable name="backendType" select="//packagedElement[@xmi:id=$DatatypeID]/@name"/>
<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
		<xsl:choose>
			<xsl:when test="$backendType='boolean'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='float'">NUMERIC</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">SERIAL</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose>
			</xsl:when>
			<xsl:when test="$backendType='string'">CHAR(255)</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='text'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BYTEA</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>

<xsl:variable name="primaryKey" select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>

ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="@xmi:id"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ( "<xsl:value-of select="$primaryKey"/>" );
			</xsl:otherwise>
		</xsl:choose>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
		<xsl:choose>
			<xsl:when test="$backendType='boolean'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='float'">NUMERIC</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">SERIAL</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose>
			</xsl:when>
			<xsl:when test="$backendType='string'">CHAR(255)</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='text'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BLOB</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>

<xsl:variable name="primaryKey" select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>

ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="@xmi:id"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ( "<xsl:value-of select="$primaryKey"/>" );
			</xsl:otherwise>
		</xsl:choose>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
		<xsl:choose>
			<xsl:when test="$backendType='bool'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='boolean'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='float'">NUMERIC</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">INTEGER</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose>
			</xsl:when>
			<xsl:when test="$backendType='string'">BPCHAR</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='text'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BYTEA</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>

<xsl:variable name="primaryKey" select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>
<xsl:if test="@name=''">
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>_<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>_<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" FOREIGN KEY ( "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ) REFERENCES "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ( "ID" );
</xsl:if>
<xsl:if test="@name!=''"><xsl:if test="contains(@name, 'anonymous_role') != 1">
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" 
ADD CONSTRAINT "cst_<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>_<xsl:value-of select="@name"/>_<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" 
FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ( "ID" );
</xsl:if></xsl:if>
<xsl:if test="@name!=''"><xsl:if test="contains(@name, 'anonymous_role') = 1">
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>_<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>_<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" FOREIGN KEY ( "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ) REFERENCES "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ( "ID" );
</xsl:if></xsl:if>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:when>
</xsl:choose>
</xsl:template>

<xsl:template name="createDBType">
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>

<!--
<xsl:variable name="DatatypeID" select="./type/@xmi:idref"/>
<xsl:variable name="backendType" select="//packagedElement[@xmi:id=$DatatypeID]/@name"/>
-->
<!--
<xsl:if test="./type/@xmi:type=''"><xsl:variable name="backendType" select="//packagedElement[@xmi:id=$DatatypeID]/@name"/></xsl:if>
-->
<xsl:variable name="DatatypeID">
	<xsl:value-of select="./type/@xmi:idref"/>
</xsl:variable>

<xsl:variable name="backendType">
<xsl:if test="./type/@xmi:idref!=''">
<xsl:if test="//packagedElement[@xmi:id=$DatatypeID]/@xmi:type='uml:DataType'">
<xsl:value-of select="//packagedElement[@xmi:id=$DatatypeID]/@name"/>
</xsl:if>
</xsl:if>
<xsl:if test="./type/@xmi:type='uml:PrimitiveType'">
	<xsl:choose>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#Boolean'">boolean</xsl:when>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#String'">string</xsl:when>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#Integer'">int</xsl:when>
		<xsl:otherwise>-- Unknown: <xsl:value-of select="./type/@href"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:if>
</xsl:variable>
<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
		<xsl:choose>
			<xsl:when test="$backendType='boolean'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='float'">NUMERIC</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">SERIAL</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose>
			</xsl:when>
			<xsl:when test="$backendType='string'">CHAR(255)</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='text'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BYTEA</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
				<xsl:if test="$lowerValue='*'"><xsl:if test="$upperValue='*'"><!--<xsl:if test="position()!=1">,</xsl:if>-->
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>


<xsl:variable name="primaryKey"><xsl:if test="//packagedElement[@xmi:id=$primaryTableID]/@xmi:type='uml:DataType'"><!-- A foreign key over a type other than int, I think. -->
<xsl:value-of select="./@name"/>
</xsl:if><xsl:if test="//packagedElement[@xmi:id=$primaryTableID]/@xmi:type='uml:Class'"><!-- A real foreign key -->
<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>
</xsl:if></xsl:variable>


--ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ADD CONSTRAINT "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>_pkey" PRIMARY KEY ("<xsl:value-of select="$primaryKey"/>");
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="@xmi:id"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ( "<xsl:value-of select="$primaryKey"/>" );</xsl:if>
			</xsl:if>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
		<xsl:choose>
			<xsl:when test="$backendType='boolean'">BIT</xsl:when>
			<xsl:when test="$backendType='float'">float</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">INTEGER IDENTITY (1, 1) NOT NULL</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose></xsl:when>
			<xsl:when test="$backendType='string'">char(255)</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BLOG</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
				<xsl:if test="$lowerValue='*'"><xsl:if test="$upperValue='*'"><!--<xsl:if test="position()!=1">,</xsl:if>-->
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>

<xsl:variable name="primaryKey" select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>
<!--
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ADD CONSTRAINT "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>_pkey" PRIMARY KEY ("<xsl:value-of select="$primaryKey"/>");
-->
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="@xmi:id"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ( "<xsl:value-of select="$primaryKey"/>" );</xsl:if>
			</xsl:if>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
<!-- Create Sqlite database type for backendType = '<xsl:value-of select="$backendType"/>' as of DatatypeID = '<xsl:value-of select="$DatatypeID"/>'
-->		<xsl:choose>
			<xsl:when test="$backendType='bool'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='boolean'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='float'">NUMERIC</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">INTEGER PRIMARY KEY</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose>
			</xsl:when>
			<xsl:when test="$backendType='string'">BPCHAR</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='text'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BYTEA</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
				<xsl:if test="$lowerValue='*'"><xsl:if test="$upperValue='*'"><!--<xsl:if test="position()!=1">,</xsl:if>-->
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>

<!--<xsl:variable name="primaryKey" select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>-->

<!--
Due to the case that a foreign key also could point to a field with an unique constraint, I have to enable this here. 
The sqlite translation to triggers seems also not be a showstopper.
So use the properties name that is also visually the correct information.
 -->
<xsl:variable name="thisAssocID" select="./@xmi:id"/>
<xsl:variable name="thisAssoc" select="./@association"/>
<!-- <xsl:variable name="otherSide" select="//packagedElement[@xmi:id=$thisAssoc]/memberEnd[@xmi:idref!=$thisAssocID]/@xmi:id"/>-->
<xsl:variable name="otherSide" select="//packagedElement[@xmi:id=$thisAssoc]/memberEnd[@xmi:idref!=$thisAssocID]/@xmi:idref"/>
-- otherSide = '<xsl:value-of select="$otherSide"/>'
<xsl:variable name="primaryKey"><xsl:value-of select="//ownedAttribute[@xmi:id=$otherSide]/@name"/></xsl:variable>
<!--
<xsl:variable name="primaryKey"><xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/></xsl:variable>
-->
<!--
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ADD CONSTRAINT "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>_pkey" PRIMARY KEY ("<xsl:value-of select="$primaryKey"/>");
-->
<xsl:if test="@name=''">
</xsl:if>
<xsl:if test="@name!=''">
<xsl:if test="$primaryKey!=''">
-- Org Primary key set
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="@xmi:id"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ( "<xsl:value-of select="$primaryKey"/>" );
</xsl:if>
<xsl:if test="$primaryKey=''">
<xsl:variable name="foreignkeyname" select="./@name"/>
<xsl:variable name="RealPrimaryKey">
<xsl:for-each select="//packagedElement[@xmi:id=$foreignTableID]/ownedAttribute">
<!-- contains(<xsl:value-of select="@name"/>, <xsl:value-of select="$foreignkeyname"/>) = <xsl:value-of select="contains(@name, $foreignkeyname)"/>-->
<xsl:if test="contains(@name, $foreignkeyname)"><xsl:if test="@name!=$foreignkeyname"><xsl:value-of select="@name"/></xsl:if></xsl:if>
<xsl:if test="@name=$foreignkeyname"><xsl:value-of select="@name"/></xsl:if>
</xsl:for-each>
</xsl:variable>
-- Org Primary key not set
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="@xmi:id"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ( "<xsl:value-of select="$RealPrimaryKey"/>" );</xsl:if>
</xsl:if>
</xsl:if>
			</xsl:if>
			</xsl:otherwise>
<!--			<xsl:if test="./@association!=''"><xsl:if test="./@aggregation='none'">INTEGER</xsl:if></xsl:if>
-->
		</xsl:choose>
	</xsl:when>
</xsl:choose>
</xsl:template>

<xsl:template name="createDBTypeForeignKeyColumn">
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>

<xsl:variable name="DatatypeID">
	<xsl:value-of select="./type/@xmi:idref"/>
</xsl:variable>

<xsl:variable name="backendType">
<xsl:if test="./type/@xmi:idref!=''">
<xsl:if test="//packagedElement[@xmi:id=$DatatypeID]/@xmi:type='uml:DataType'">
<xsl:value-of select="//packagedElement[@xmi:id=$DatatypeID]/@name"/>
</xsl:if>
</xsl:if>
<xsl:if test="./type/@xmi:type='uml:PrimitiveType'">
	<xsl:choose>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#Boolean'">boolean</xsl:when>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#String'">string</xsl:when>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#Integer'">int</xsl:when>
		<xsl:otherwise>-- Unknown: <xsl:value-of select="./type/@href"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:if>
</xsl:variable>
<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
		<xsl:choose>
			<xsl:when test="$backendType='boolean'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='float'">NUMERIC</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">SERIAL</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose>
			</xsl:when>
			<xsl:when test="$backendType='string'">CHAR(255)</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='text'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BYTEA</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
				<xsl:if test="$lowerValue='1'"><xsl:if test="$upperValue='1'"><!--<xsl:if test="position()!=1">,</xsl:if>-->
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>
<xsl:variable name="primaryKey"><xsl:if test="//packagedElement[@xmi:id=$primaryTableID]/@xmi:type='uml:DataType'"><!-- A foreign key over a type other than int, I think. -->
<xsl:value-of select="./@name"/>
</xsl:if><xsl:if test="//packagedElement[@xmi:id=$primaryTableID]/@xmi:type='uml:Class'"><!-- A real foreign key -->
<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>
</xsl:if></xsl:variable>
<xsl:variable name="AssocID" select="./@association"/>
<xsl:variable name="AttributeID" select="./@xmi:id"/>
<xsl:variable name="foreignKey" select="//ownedAttribute[@association=$AssocID][@xmi:id!=$AttributeID]/@name"/>"<xsl:value-of select="@name"/>" INTEGER</xsl:if>
			</xsl:if>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
		<xsl:choose>
			<xsl:when test="$backendType='boolean'">BIT</xsl:when>
			<xsl:when test="$backendType='float'">float</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">INTEGER IDENTITY (1, 1) NOT NULL</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose></xsl:when>
			<xsl:when test="$backendType='string'">char(255)</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BLOG</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
				<xsl:if test="$lowerValue='1'"><xsl:if test="$upperValue='1'"><!--<xsl:if test="position()!=1">,</xsl:if>-->
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>
<xsl:variable name="primaryKey"><xsl:if test="//packagedElement[@xmi:id=$primaryTableID]/@xmi:type='uml:DataType'"><!-- A foreign key over a type other than int, I think. -->
<xsl:value-of select="./@name"/>
</xsl:if><xsl:if test="//packagedElement[@xmi:id=$primaryTableID]/@xmi:type='uml:Class'"><!-- A real foreign key -->
<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>
</xsl:if></xsl:variable>
<xsl:variable name="AssocID" select="./@association"/>
<xsl:variable name="AttributeID" select="./@xmi:id"/>
<xsl:variable name="foreignKey" select="//ownedAttribute[@association=$AssocID][@xmi:id!=$AttributeID]/@name"/>"<xsl:value-of select="@name"/>" INTEGER</xsl:if>
</xsl:if>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
<!-- Create Sqlite database type for backendType = '<xsl:value-of select="$backendType"/>' as of DatatypeID = '<xsl:value-of select="$DatatypeID"/>'
-->		<xsl:choose>
			<xsl:when test="$backendType='bool'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='boolean'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='float'">NUMERIC</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">INTEGER PRIMARY KEY</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose>
			</xsl:when>
			<xsl:when test="$backendType='string'">BPCHAR</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='text'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BYTEA</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
				<xsl:if test="$lowerValue='1'"><xsl:if test="$upperValue='1'"><!--<xsl:if test="position()!=1">,</xsl:if>-->
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>
<xsl:variable name="primaryKey"><xsl:if test="//packagedElement[@xmi:id=$primaryTableID]/@xmi:type='uml:DataType'"><!-- A foreign key over a type other than int, I think. -->
<xsl:value-of select="./@name"/>
</xsl:if><xsl:if test="//packagedElement[@xmi:id=$primaryTableID]/@xmi:type='uml:Class'"><!-- A real foreign key -->
<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>
</xsl:if></xsl:variable>
<xsl:variable name="AssocID" select="./@association"/>
<xsl:variable name="AttributeID" select="./@xmi:id"/>
<xsl:variable name="foreignKey" select="//ownedAttribute[@association=$AssocID][@xmi:id!=$AttributeID]/@name"/>"<xsl:value-of select="@name"/>" INTEGER</xsl:if>
</xsl:if>
</xsl:otherwise>
<!--			<xsl:if test="./@association!=''"><xsl:if test="./@aggregation='none'">INTEGER</xsl:if></xsl:if>
-->
		</xsl:choose>
	</xsl:when>
</xsl:choose>
</xsl:template>


<xsl:template name="dropDBType">
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
<xsl:variable name="DatatypeID" select="./type/@xmi:idref"/>
<xsl:variable name="backendType" select="//packagedElement[@xmi:id=$DatatypeID]/@name"/>

<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
		<xsl:choose>
			<xsl:when test="$backendType='boolean'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='float'">NUMERIC</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">SERIAL</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose>
			</xsl:when>
			<xsl:when test="$backendType='string'">CHAR(255)</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='text'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BYTEA</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
				<xsl:if test="$lowerValue='*'"><xsl:if test="$upperValue='*'"><!--<xsl:if test="position()!=1">,</xsl:if>-->
<!--"<xsl:value-of select="@name"/>" INT4,-->

<!-- New variables to help getting values from new profile based settings -->

<xsl:variable name="propertyID" select="@xmi:id"/>
<xsl:variable name="associationID" select="@association"/>

<xsl:variable name="assocCounterpart" select="//packagedElement[@xmi:type='uml:Association'][@xmi:id=$associationID]/memberEnd[@xmi:idref!=$propertyID]/@xmi:idref"/>

<xsl:variable name="primaryTableName" select="//ownedAttribute[@xmi:id=$assocCounterpart]/xmi:Extension/taggedValue[@tag='lbDMF:relationship:table']/@value"/>	

<!-- From old template version -->
<xsl:variable name="foreignTableID" select="../@xmi:id"/>
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	





<xsl:variable name="foreignTableName" select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>

<xsl:variable name="primaryKey_old" select="./xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>
<xsl:variable name="primaryKey" select="//ownedAttribute[@xmi:id=$assocCounterpart]/../ownedAttribute/xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>
<xsl:variable name="foreignKey" select="//ownedAttribute[@xmi:id=$assocCounterpart]/../ownedAttribute/xmi:Extension/taggedValue[@tag='lbDMF:table'][@value=$primaryTableName]/../../@name"/>

-- ...
-- ALTER TABLE DROP this ID <xsl:value-of select="@xmi:id"/> counterpart <xsl:value-of select="$assocCounterpart"/> <xsl:value-of select="$primaryKey"/>: <xsl:value-of select="$primaryTableName"/>
-- cst_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>_<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:table']/@value"/>_<xsl:value-of select="xmi:Extension/taggedValue[@tag='lbDMF:sourcecolumn']/@value"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>

ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" DROP CONSTRAINT "cst_<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>_<xsl:value-of select="@name"/>_<xsl:value-of select="$foreignTableName"/>_<xsl:value-of select="$primaryKey"/>";</xsl:if>
			</xsl:if>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
		<xsl:choose>
			<xsl:when test="$backendType='boolean'">BIT</xsl:when>
			<xsl:when test="$backendType='float'">float</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">INTEGER NOT NULL</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose></xsl:when>
			<xsl:when test="$backendType='string'">char(255)</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BLOG</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
				<xsl:if test="$lowerValue='*'"><xsl:if test="$upperValue='*'"><!--<xsl:if test="position()!=1">,</xsl:if>-->
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>

<xsl:variable name="primaryKey" select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>
<!--
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ADD CONSTRAINT "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>_pkey" PRIMARY KEY ("<xsl:value-of select="$primaryKey"/>");
-->
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" DROP CONSTRAINT "cst_<xsl:value-of select="@xmi:id"/>";</xsl:if>
			</xsl:if>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
		<xsl:choose>
			<xsl:when test="$backendType='bool'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='boolean'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='float'">NUMERIC</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">INTEGER PRIMARY KEY</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose>
			</xsl:when>
			<xsl:when test="$backendType='string'">BPCHAR</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='text'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BYTEA</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
				<xsl:if test="$lowerValue='*'"><xsl:if test="$upperValue='*'"><!--<xsl:if test="position()!=1">,</xsl:if>-->
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>

<xsl:variable name="primaryKey" select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>
-- Quick and dirty ignore it. This is an unsave method due to internally populated tables wouldn't cleaned up well.
--ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" DROP CONSTRAINT "cst_<xsl:value-of select="@xmi:id"/>";</xsl:if>
			</xsl:if>
			</xsl:otherwise>
<!--			<xsl:if test="./@association!=''"><xsl:if test="./@aggregation='none'">INTEGER</xsl:if></xsl:if>
-->
		</xsl:choose>
	</xsl:when>
</xsl:choose>
</xsl:template>

<xsl:template name="createPrimaryKeys">
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
<xsl:variable name="DatatypeID" select="./type/@xmi:idref"/>
<xsl:variable name="backendType" select="//packagedElement[@xmi:id=$DatatypeID]/@name"/>


<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="Aggregation" select="@aggregation"/>
<!--<xsl:if test="$Aggregation='none'">-->
	<xsl:variable name="otherClassID" select="./type/@xmi:idref"/><!--<xsl:if test="position()=1">,</xsl:if>-->
	<!--<xsl:call-template name="createPrimaryKeys_"><xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/></xsl:call-template>-->
	<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
	<xsl:variable name="foreignTableID" select="../@xmi:id"/>

	<xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>
		<xsl:if test="$primaryKey!=''">
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ADD CONSTRAINT "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>_pkey" PRIMARY KEY ("<xsl:value-of select="$primaryKey"/>");
		</xsl:if>
	<!--</xsl:if>-->
</xsl:for-each>
</xsl:template>



<xsl:template name="createPrimaryKeys_">
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
<xsl:variable name="DatatypeID" select="./type/@xmi:idref"/>
<xsl:variable name="backendType" select="//packagedElement[@xmi:id=$DatatypeID]/@name"/>
<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
			<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
			<xsl:variable name="upperValue" select="./upperValue/@value"/>
			<xsl:if test="$lowerValue='1'"><xsl:if test="$upperValue='1'">
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>
<xsl:variable name="primaryKey" select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='lbDMF:pk']/../../@name"/>
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ADD CONSTRAINT "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>_pkey" PRIMARY KEY ("<xsl:value-of select="$primaryKey"/>");
				</xsl:if>
			</xsl:if>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
		<xsl:choose>
			<xsl:when test="$backendType='boolean'">
			</xsl:when>
			<xsl:when test="$backendType='float'">
			</xsl:when>
			<xsl:when test="$backendType='int'">
			</xsl:when>
			<xsl:when test="$backendType='string'">
			</xsl:when>
			<xsl:when test="$backendType='bigstring'">
			</xsl:when>
			<xsl:when test="$backendType='image'">
			</xsl:when>
		</xsl:choose>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
		<xsl:choose>
			<xsl:when test="$backendType='boolean'">
			</xsl:when>
			<xsl:when test="$backendType='float'">
			</xsl:when>
			<xsl:when test="$backendType='int'">
			</xsl:when>
			<xsl:when test="$backendType='string'">
			</xsl:when>
			<xsl:when test="$backendType='bigstring'">
			</xsl:when>
			<xsl:when test="$backendType='image'">
			</xsl:when>
		</xsl:choose>
	</xsl:when>
</xsl:choose>
</xsl:template>


	<!--<xsl:template match="XMI.content">
	    <xsl:apply-templates/>
	</xsl:template>-->
</xsl:stylesheet>

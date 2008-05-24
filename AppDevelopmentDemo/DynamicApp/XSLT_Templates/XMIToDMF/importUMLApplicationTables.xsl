<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1">
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
-- Generate application table <xsl:value-of select="@name"/> for <xsl:value-of select="$ApplicationName"/>

<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
		<xsl:call-template name="createPostgreSQLTableRelation">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
		<xsl:call-template name="createMSSQLTableRelation">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDatabaseType"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TableName" select="@name"/>
		</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
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

<xsl:template name="createSqliteTable">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
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

<xsl:template name="createMSSQLTable">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- CREATE TABLE <xsl:value-of select="$TableName"/>
CREATE TABLE "<xsl:value-of select="$TableName"/>" (

);
</xsl:template>

<xsl:template name="createPostgreSQLTable">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- CREATE TABLE <xsl:value-of select="$TableName"/>
CREATE TABLE "<xsl:value-of select="$TableName"/>" (
	<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']"><xsl:if test="position()!=1">,</xsl:if>
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:choose>
	<xsl:when test="$Aggregation='none'">
--,</xsl:when>
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

<!-- ** Tables with autoID creation ** -->

<xsl:template name="createSqliteTableAutoID">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
-- CREATE TABLE <xsl:value-of select="$TableName"/>
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
);
</xsl:template>


<!-- ****************************************** -->


<xsl:template name="createPostgreSQLTableRelation">
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

<xsl:template name="createSqliteTableRelation">
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
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='key']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">SERIAL</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose>
			</xsl:when>
			<xsl:when test="$backendType='string'">BPCHAR</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BYTEA</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>

<xsl:variable name="primaryKey" select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='key']/../../@name"/>

ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="@xmi:id"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ( "<xsl:value-of select="$primaryKey"/>" );
			</xsl:otherwise>
		</xsl:choose>
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
			<xsl:when test="$backendType='bool'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='boolean'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='float'">NUMERIC</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='key']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">INTEGER</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose>
			</xsl:when>
			<xsl:when test="$backendType='string'">BPCHAR</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BYTEA</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>

<xsl:variable name="primaryKey" select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='key']/../../@name"/>
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
<xsl:variable name="DatatypeID" select="./type/@xmi:idref"/>
<xsl:variable name="backendType" select="//packagedElement[@xmi:id=$DatatypeID]/@name"/>
<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
		<xsl:choose>
			<xsl:when test="$backendType='boolean'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='float'">NUMERIC</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='key']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">SERIAL</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose>
			</xsl:when>
			<xsl:when test="$backendType='string'">BPCHAR</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BYTEA</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
				<xsl:if test="$lowerValue='*'"><xsl:if test="$upperValue='*'"><!--<xsl:if test="position()!=1">,</xsl:if>-->
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>

<xsl:variable name="primaryKey" select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='key']/../../@name"/>

--ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ADD CONSTRAINT "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>_pkey" PRIMARY KEY ("<xsl:value-of select="$primaryKey"/>");
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="@xmi:id"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ( "<xsl:value-of select="$primaryKey"/>" );</xsl:if>
			</xsl:if>
			</xsl:otherwise>
		</xsl:choose>
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
			<xsl:when test="$backendType='bool'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='boolean'">BOOLEAN</xsl:when>
			<xsl:when test="$backendType='float'">NUMERIC</xsl:when>
			<xsl:when test="$backendType='int'"><xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='key']/../../@name"/><xsl:choose>
<xsl:when test="$primaryKey!=''">INTEGER PRIMARY KEY</xsl:when><xsl:otherwise>INTEGER</xsl:otherwise></xsl:choose>
			</xsl:when>
			<xsl:when test="$backendType='string'">BPCHAR</xsl:when>
			<xsl:when test="$backendType='bigstring'">TEXT</xsl:when>
			<xsl:when test="$backendType='image'">BYTEA</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="lowerValue" select="./lowerValue/@value"/>
				<xsl:variable name="upperValue" select="./upperValue/@value"/>
				<xsl:if test="$lowerValue='*'"><xsl:if test="$upperValue='*'"><!--<xsl:if test="position()!=1">,</xsl:if>-->
<!--"<xsl:value-of select="@name"/>" INT4,-->
<xsl:variable name="primaryTableID" select="./type/@xmi:idref"/>	
<xsl:variable name="foreignTableID" select="../@xmi:id"/>

<xsl:variable name="primaryKey" select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='key']/../../@name"/>
<!--
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ADD CONSTRAINT "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>_pkey" PRIMARY KEY ("<xsl:value-of select="$primaryKey"/>");
-->
ALTER TABLE "<xsl:value-of select="//packagedElement[@xmi:id=$primaryTableID]/@name"/>" ADD CONSTRAINT "cst_<xsl:value-of select="@xmi:id"/>" FOREIGN KEY ( "<xsl:value-of select="@name"/>" ) REFERENCES "<xsl:value-of select="//packagedElement[@xmi:id=$foreignTableID]/@name"/>" ( "<xsl:value-of select="$primaryKey"/>" );</xsl:if>
			</xsl:if>
			</xsl:otherwise>
			<xsl:if test="./@association!=''"><xsl:if test="./@aggregation='none'">INTEGER</xsl:if></xsl:if>
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

	<xsl:variable name="primaryKey" select="./xmi:Extension/stereotype[@name='key']/../../@name"/>
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
<xsl:variable name="primaryKey" select="//packagedElement[@xmi:id=$primaryTableID]/ownedAttribute/xmi:Extension/stereotype[@name='key']/../../@name"/>
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

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" xmlns:UML="org.omg.xmi.namespace.UML" exclude-result-prefixes="UML">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002-2013  Lothar Behrens (lothar.behrens@lollisoft.de)

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
<xsl:import href="XMISysImport.CreateFormularDefinition.Sqlite.xsl"/>
<!--
<xsl:import href="XMISysImport.FillSchemaTables.PostgreSQL.xsl"/>
<xsl:import href="XMISysImport.FillSchemaTables.SqlServer.xsl"/>
-->
<xsl:output method="text"/>

<xsl:template name="XMISysImport.CreateFormularDefinition">
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="ApplicationName"/>
    <xsl:param name="FieldName"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="DataType"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="ClassId"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="ClassName"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="TableName"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="TargetDBType"/><!-- What database the SQL script should be created for -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
<xsl:choose>
<xsl:when test="$TargetDBType='Sqlite'">
<xsl:call-template name="XMISysImport.CreateFormularDefinition.Sqlite">
	<xsl:with-param name="FieldName" select="$FieldName"/>
	<xsl:with-param name="DataType" select="$DataType"/>
	<xsl:with-param name="ClassId" select="$ClassId"/>
	<xsl:with-param name="ClassName" select="$ClassName"/>
	<xsl:with-param name="TableName" select="$TableName"/>
	<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</xsl:when>	
</xsl:choose>
</xsl:template>

<xsl:template name="XMISysImport.CreateFormularDefinitionAssociation">
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="AssociationId"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TargetDBType"/><!-- What database the SQL script should be created for -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
<xsl:choose>
<xsl:when test="$TargetDBType='Sqlite'">
<xsl:call-template name="XMISysImport.CreateFormularDefinitionAssociation.Sqlite">
	<xsl:with-param name="AssociationId" select="$AssociationId"/>
	<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</xsl:when>	
</xsl:choose>
</xsl:template>

</xsl:stylesheet>

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
<xsl:import href="XMIImport.CreateDBSchema.Sqlite.xsl"/>
<xsl:import href="XMIImport.CreateDBSchema.PostgreSQL.xsl"/>
<xsl:import href="XMIImport.CreateDBSchema.SqlServer.xsl"/>

<xsl:import href="XMIImport.Helper.xsl"/>

<xsl:output method="text"/>

<xsl:template name="Translate.DropRules">
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="TargetDBType"/><!-- What database the SQL script should be created for -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
<xsl:choose>
<xsl:when test="$TargetDBType='Sqlite'">
<xsl:call-template name="Translate.DropRules.Sqlite">
</xsl:call-template>
</xsl:when>	
</xsl:choose>
</xsl:template>

<xsl:template name="Translate.StoredProcRules">
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="TargetDBType"/><!-- What database the SQL script should be created for -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
<xsl:choose>
<xsl:when test="$TargetDBType='Sqlite'">
<xsl:call-template name="Translate.StoredProcRules.Sqlite">
</xsl:call-template>
</xsl:when>	
</xsl:choose>
</xsl:template>

<xsl:template name="Translate.Association">
    <xsl:param name="ClassID"/>
    <xsl:param name="ReferencingClassID"/><!--  -->
    <xsl:param name="ReferencedClassID"/><!--  -->
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="TargetDBType"/><!-- What database the SQL script should be created for -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
<xsl:choose>
<xsl:when test="$TargetDBType='Sqlite'">
<xsl:call-template name="Translate.Association.Sqlite">
<xsl:with-param name="ReferencingClassID" select="$ReferencingClassID"/>
<xsl:with-param name="ReferencedClassID" select="$ReferencedClassID"/></xsl:call-template>
</xsl:when>	
</xsl:choose>
</xsl:template>

<xsl:template name="Translate.BuildForeignColumns">
    <xsl:param name="ID"/><!--  -->
    <xsl:param name="ClassID"/><!--  -->
    <xsl:param name="TargetDBType"/><!-- What database the SQL script should be created for -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
<xsl:variable name="AssocuationID">
<xsl:variable name="AssociationId" select="//UML:AssociationEnd.participant/UML:Class[@xmi.idref=$ClassID]/../../../../@xmi.id"/>
<xsl:variable name="OtherClassId" select="//UML:Association[@xmi.id=$AssociationId]/UML:Association.connection/UML:AssociationEnd/UML:AssociationEnd.participant/UML:Class[@xmi.idref!=$ClassID]/@xmi.idref"/>
<xsl:value-of select="$OtherClassId"/>
<!--
<xsl:call-template name="Helper.Lookup.Association">
<xsl:with-param name="ClassID" select="$ClassID"/>
<xsl:with-param name="Aggregate" select="'none'"/>
</xsl:call-template>
-->
</xsl:variable>
	
<xsl:choose>
<xsl:when test="$TargetDBType='Sqlite'">
<xsl:call-template name="Translate.BuildForeignColumns.Sqlite">
<xsl:with-param name="ClassID" select="$ClassID"/>
<xsl:with-param name="AssocuationID" select="$AssocuationID"/>
</xsl:call-template>
</xsl:when>	
</xsl:choose>

</xsl:template>

<xsl:template name="Translate.CreateTable">
    <xsl:param name="TargetDBType"/><!-- What database the SQL script should be created for -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
    <xsl:param name="ClassID"/><!--  -->
    <xsl:param name="ClassName"/><!--  -->
    <xsl:param name="Stereotype"/><!--  -->
<xsl:choose>
<xsl:when test="$TargetDBType='Sqlite'">
<xsl:call-template name="Translate.CreateTable.Sqlite">
<xsl:with-param name="ClassID" select="$ClassID"/>
<xsl:with-param name="ClassName" select="$ClassName"/>
<xsl:with-param name="Stereotype" select="$Stereotype"/>
</xsl:call-template>
</xsl:when>	
</xsl:choose>
</xsl:template>

</xsl:stylesheet>

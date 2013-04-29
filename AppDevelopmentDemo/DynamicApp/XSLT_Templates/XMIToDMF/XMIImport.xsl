<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:UML="org.omg.xmi.namespace.UML" exclude-result-prefixes="UML">
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
<!-- This is a generic import template that tries to detect exporter and be most generic and refactored -->

<!-- This file must be generated before this template could be applied. -->
<xsl:import href="XMISettings.xsl"/>

<xsl:import href="XMIImport.CreateDBSchema.xsl"/>

<xsl:output method="text" indent="no"/>

<!-- Stylesheet parameters that will overwrite those given from the XMISettings.xsl file. -->
<xsl:param name="XSLDatabaseBackendSystem"/>
<xsl:param name="XSLDatabaseBackendApplication"/>
<xsl:param name="overwriteDatabase"/>
<xsl:variable name="targetdatabase">
<xsl:if test="$XSLDatabaseBackendApplication=''"><xsl:value-of select="$settingsfile_targetdatabase"/></xsl:if>
<xsl:if test="$XSLDatabaseBackendApplication!=''"><xsl:value-of select="$XSLDatabaseBackendApplication"/></xsl:if>
</xsl:variable>
<xsl:variable name="execute_droprules">
<xsl:if test="$overwriteDatabase=''"><xsl:value-of select="$settingsfile_execute_droprules"/></xsl:if>
<xsl:if test="$overwriteDatabase!=''"><xsl:value-of select="$overwriteDatabase"/></xsl:if>
</xsl:variable>

<xsl:variable name="DefaultDatabaseSystem" select="'PostgreSQL'"/>

<xsl:variable name="TargetDBType">
	<xsl:if test="$targetdatabase = 'DatabaseLayerGateway'">Sqlite</xsl:if>
	<xsl:if test="$targetdatabase = 'PostgreSQL'">PostgreSQL</xsl:if>
	<xsl:if test="$targetdatabase = 'MSSQL'">MSSQL</xsl:if>
	<xsl:if test="$targetdatabase = 'Sqlite'">Sqlite</xsl:if>
	<xsl:if test="$targetdatabase = ' '"><xsl:value-of select="$DefaultDatabaseSystem"/></xsl:if>
	<xsl:if test="$targetdatabase = ''"><xsl:value-of select="$DefaultDatabaseSystem"/></xsl:if>
</xsl:variable>
<xsl:variable name="TargetDBVersion">
	<xsl:if test="$targetdatabase = 'DatabaseLayerGateway'">1.2.3</xsl:if>
	<xsl:if test="$targetdatabase = ' '">7.4</xsl:if>
	<xsl:if test="$targetdatabase = ''">7.4</xsl:if>
</xsl:variable>


<xsl:template match="XMI[@xmi.version='1.2']">
   <xsl:apply-templates select="XMI.content/UML:Model"/>
</xsl:template>

<xsl:template match="UML:Namespace.ownedElement/UML:Class">
-- Class '<xsl:value-of select="@name"/>' in model (xmi.id <xsl:value-of select="@xmi.id"/>).
   <xsl:apply-templates select="UML:Classifier.feature/UML:Attribute"/>
<xsl:variable name="ClassId" select="@xmi.id"/>
	<!-- Takes all, but I want one -->
	<!--<xsl:apply-templates select="//UML:Association.connection/UML:AssociationEnd"/>-->
	<!-- Does not work -->
	<!--<xsl:apply-templates select="//UML:Association.connection/UML:AssociationEnd[@aggregation='none']/UML:AssociationEnd.participant/UML:Class[@xmi.idref=$ClassId]"/>-->

	<!-- The only known solution to me yet is using for-each and filter -->
	<xsl:call-template name="Translate.BuildForeignColumns">
	<xsl:with-param name="ClassID" select="$ClassId"/>
	<xsl:with-param name="TargetDBType" select="$TargetDBType"/>
	</xsl:call-template>
</xsl:template>

<xsl:template match="UML:Namespace.ownedElement/UML:Association">
-- Association '<xsl:value-of select="@name"/>' in model (xmi.id <xsl:value-of select="@xmi.id"/>).
<xsl:variable name="referenced_class"><xsl:apply-templates select="UML:Association.connection/UML:AssociationEnd[@aggregation='none']"/></xsl:variable>
<xsl:variable name="referencing_class"><xsl:apply-templates select="UML:Association.connection/UML:AssociationEnd[@aggregation!='none']"/></xsl:variable>

<xsl:call-template name="Translate.Association">
<xsl:with-param name="ReferencingClassID" select="$referencing_class"/>
<xsl:with-param name="ReferencedClassID" select="$referenced_class"/>
<xsl:with-param name="TargetDBType" select="$TargetDBType"/>
</xsl:call-template>

</xsl:template>

<xsl:template match="UML:Association.connection/UML:AssociationEnd">

<!-- Lookup the foreign class as to be the link without a diamond -->

<xsl:if test="@xmi.id!= ''"><!--'<xsl:value-of select="@xmi.id"/>' ('<xsl:value-of select="@aggregation"/>') in model.-->
   <xsl:apply-templates select="UML:AssociationEnd.participant"/>
</xsl:if>
<xsl:if test="@type!= ''"><!--'<xsl:value-of select="@type"/>' ('<xsl:value-of select="@aggregation"/>') in model.-->
   <xsl:apply-templates select="UML:AssociationEnd.participant"/>
</xsl:if>

</xsl:template>

<xsl:template match="UML:Classifier.feature/UML:Attribute">
-- Attribute '<xsl:value-of select="@name"/>' in model.
</xsl:template>

<xsl:template match="UML:AssociationEnd/UML:AssociationEnd.participant">
<xsl:value-of select="UML:Class/@xmi.idref"/>
</xsl:template>

</xsl:stylesheet>

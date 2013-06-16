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

<xsl:import href="XMIImport.Variables.xsl"/>
<xsl:import href="XMIImport.CreateDBSchema.xsl"/>

<xsl:output method="text" indent="no"/>


<xsl:template match="XMI[@xmi.version='1.2']">
	<xsl:call-template name="Translate.DropRules">
	<xsl:with-param name="overwriteDatabase" select="$overwriteDatabase"/>
	<xsl:with-param name="TargetDBType" select="$TargetDBType"/>
	</xsl:call-template>
	<xsl:call-template name="Translate.StoredProcRules">
	<xsl:with-param name="TargetDBType" select="$TargetDBType"/>
	</xsl:call-template>
    <xsl:apply-templates select="XMI.content/UML:Model"/>
	<xsl:for-each select="//UML:Class">
<xsl:call-template name="Translate.Association">
<xsl:with-param name="ReferencingClassID" select="@xmi.id"/>
<xsl:with-param name="TargetDBType" select="$TargetDBType"/>
</xsl:call-template>
	</xsl:for-each>
</xsl:template>

<xsl:template match="UML:Namespace.ownedElement/UML:Class">
<xsl:variable name="ClassId" select="@xmi.id"/>
	<xsl:call-template name="Translate.CreateTable">
	<xsl:with-param name="ClassID" select="@xmi.id"/>
	<xsl:with-param name="ClassName" select="@name"/>
	<xsl:with-param name="TargetDBType" select="$TargetDBType"/>
	</xsl:call-template>
</xsl:template>

<!--
<xsl:template match="UML:Namespace.ownedElement/UML:Association">
<xsl:variable name="referenced_class"><xsl:apply-templates select="UML:Association.connection/UML:AssociationEnd[@aggregation='none']"/></xsl:variable>
<xsl:variable name="referencing_class"><xsl:apply-templates select="UML:Association.connection/UML:AssociationEnd[@aggregation!='none']"/></xsl:variable>

<xsl:call-template name="Translate.Association">
<xsl:with-param name="ReferencingClassID" select="$referencing_class"/>
<xsl:with-param name="ReferencedClassID" select="$referenced_class"/>
<xsl:with-param name="TargetDBType" select="$TargetDBType"/>
</xsl:call-template>

</xsl:template>

<xsl:template match="UML:Association.connection/UML:AssociationEnd">
<xsl:if test="@xmi.id!= ''">
   <xsl:apply-templates select="UML:AssociationEnd.participant"/>
</xsl:if>
<xsl:if test="@type!= ''">
   <xsl:apply-templates select="UML:AssociationEnd.participant"/>
</xsl:if>

</xsl:template>

<xsl:template match="UML:AssociationEnd/UML:AssociationEnd.participant">
<xsl:value-of select="UML:Class/@xmi.idref"/>
</xsl:template>
-->

</xsl:stylesheet>

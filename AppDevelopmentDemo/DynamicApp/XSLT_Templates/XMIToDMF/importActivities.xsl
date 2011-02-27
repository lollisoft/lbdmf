<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1">
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

	<xsl:template match="text()|@*">
		<xsl:value-of select="."/>
	</xsl:template>
	<xsl:template match="text()|@*"/>

<xsl:template match="packagedElement"> 
<xsl:value-of select="$activity"/></xsl:template>


	<xsl:template match="/">
	
	

    <xsl:for-each select="//ownedOperation"><xsl:variable name="function" select="@name"/>
-- Operation for class <xsl:value-of select="../@name"/> in package <xsl:value-of select="../../@name"/> is <xsl:value-of select="@name"/>.
<xsl:variable name="activity" select="../../packagedElement[@xmi:type = 'uml:Activity'][@name = $function]/@name"/>
<xsl:variable name="activityID" select="../../packagedElement[@xmi:type = 'uml:Activity'][@name = $function]/@xmi:id"/>
<!--<xsl:apply-templates select="../../packagedElement[@xmi:type = 'uml:Activity'][@name = $function]"/>-->

<xsl:if test="$activity=''">-- Activity not found.</xsl:if>
<xsl:if test="$activity!=''">-- Activity '<xsl:value-of select="$activity"/>' found.
<xsl:call-template name="convertActivityTolbDMFActivity"><xsl:with-param name="ID" select="$activityID"/><xsl:with-param name="Name" select="$activity"/></xsl:call-template>
</xsl:if>

</xsl:for-each>
-- Script ready.
</xsl:template>

<xsl:template name="convertActivityTolbDMFActivity">
    <xsl:param name="ID"/>
    <xsl:param name="Name"/>
-- Generate statemachine for <xsl:value-of select="$ID"/>
-- select "CreateActivityOnMissing"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>');

<xsl:for-each select="//packagedElement[@xmi:id=$ID]/node">
	<xsl:variable name="nodetype" select="@xmi:type"/>
		<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$nodetype='uml:InitialNode'">
-- Node <xsl:value-of select="$nodetype"/>.
select "CreateInitialNode"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>');
		</xsl:when>
		<xsl:when test="$nodetype='uml:DecisionNode'">
-- Node <xsl:value-of select="$nodetype"/>.
select "CreateDecisionNode"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>');
		</xsl:when>
		<xsl:when test="$nodetype='uml:OpaqueAction'">
-- Node <xsl:value-of select="$nodetype"/>.
select "CreateOpaqueAction"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>', '<xsl:value-of select="./body"/>'); 
		</xsl:when>
		<xsl:when test="$nodetype='uml:FinalNode'">
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$nodetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>
<xsl:for-each select="//packagedElement[@xmi:id=$ID]/edge">
	<xsl:variable name="edgetype" select="@xmi:type"/>
	<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$edgetype='uml:ControlFlow'">
			<xsl:variable name="expression" select="./guard[@xmi:type='uml:OpaqueExpression']/body"/>
--     CreateControlFlow(activityID, ActivityName, controlflowID, source, target, name, body);	

select "CreateControlFlow"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>', '<xsl:value-of select="./@source"/>', '<xsl:value-of select="./@target"/>', '<xsl:value-of select="$expression"/>');
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$edgetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>

<xsl:for-each select="//packagedElement[@xmi:id=$ID]/node">
	<xsl:variable name="nodetype" select="@xmi:type"/>
		<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$nodetype='uml:DecisionNode'">
			<xsl:variable name="decision" select="./@xmi:id"/>
			<xsl:variable name="incoming" select="./incoming/@xmi:idref"/>
			<xsl:for-each select="./outgoing">
-- Node <xsl:value-of select="$nodetype"/>.
select "CreateDecisionPath"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="$decision"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>', '<xsl:value-of select="$incoming"/>', '<xsl:value-of select="./@xmi:idref"/>');
			</xsl:for-each>
		</xsl:when>
		<xsl:when test="$nodetype='uml:OpaqueAction'">
		</xsl:when>
		<xsl:when test="$nodetype='uml:FinalNode'">
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$nodetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>

</xsl:template>


	<!--<xsl:template match="XMI.content">
	    <xsl:apply-templates/>
	</xsl:template>-->
</xsl:stylesheet>

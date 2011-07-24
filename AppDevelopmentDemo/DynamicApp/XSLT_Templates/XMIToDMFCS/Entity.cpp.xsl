<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" xmlns:lbDMF="http:///schemas/lbDMF/1"  xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
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
<xsl:import href="../include/exsl.xsl"/>
<xsl:import href="TypeMapping.xsl"/>
<xsl:output method="text" indent="no"/>

<!-- here is the template that does the replacement -->
<xsl:template name="SubstringReplace">
	<xsl:param name="stringIn"/>
	<xsl:param name="substringIn"/>
	<xsl:param name="substringOut"/>
	<xsl:choose>
		<xsl:when test="contains($stringIn,$substringIn)">
			<xsl:value-of select="concat(substring-before($stringIn,$substringIn),$substringOut)"/>
			<xsl:call-template name="SubstringReplace">
				<xsl:with-param name="stringIn" select="substring-after($stringIn,$substringIn)"/>
				<xsl:with-param name="substringIn" select="$substringIn"/>
				<xsl:with-param name="substringOut" select="$substringOut"/>
			</xsl:call-template>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="$stringIn"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<!-- This template creates a pair of files per formular name -->
<xsl:template name="Entity.cpp">
	<xsl:param name="ApplicationName"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>
/*
	Automatically created file. Do not modify.
 */
 
#include &lt;lbConfigHook.h&gt;
#include &lt;lbInterfaces-sub-Project.h&gt;

#undef DLLEXPORT

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif
#ifdef LINUX 
#define DLLEXPORT
#endif

#include &lt;I<xsl:value-of select="$FormName"/>.h&gt;
#include &lt;<xsl:value-of select="$FormName"/>Entity.h&gt;

IMPLEMENT_FUNCTOR(instanceOf<xsl:value-of select="$FormName"/>Entity, <xsl:value-of select="$FormName"/>Entity)

BEGIN_IMPLEMENT_LB_UNKNOWN(<xsl:value-of select="$FormName"/>Entity)
        ADD_INTERFACE(lb_I_<xsl:value-of select="$FormName"/>)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL <xsl:value-of select="$FormName"/>Entity::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE &lt;&lt; "<xsl:value-of select="$FormName"/>Entity::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

<xsl:value-of select="$FormName"/>Entity::<xsl:value-of select="$FormName"/>Entity() {
	ref = STARTREF;
	_CL_LOG &lt;&lt; "Init <xsl:value-of select="$FormName"/>Entity" LOG_
	m_id_Null = true;
<xsl:for-each select="//packagedElement[@xmi:id=$FormularID]/ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="backendType"><xsl:call-template name="MapType"/></xsl:variable>
<xsl:if test="$backendType!='lb_I_Collection'">
<xsl:if test="@name!=''">
	m_<xsl:value-of select="@name"/>_Null = true;
</xsl:if>
</xsl:if>

</xsl:for-each>

}

<xsl:value-of select="$FormName"/>Entity::~<xsl:value-of select="$FormName"/>Entity() {

}
	
lb_I_Integer* <xsl:value-of select="$FormName"/>Entity::get_id() {
	m_id++;
	return m_id.getPtr();
}

lbErrCodes <xsl:value-of select="$FormName"/>Entity::set_id(lb_I_Integer* value) {
	m_id_Null = false;
	m_id = value;
	m_id++;
}

bool <xsl:value-of select="$FormName"/>Entity::is_id_Null() {
	return m_id_Null;
}

lbErrCodes <xsl:value-of select="$FormName"/>Entity::set_id_Null() {
	m_id_Null = true;
	return ERR_NONE;
}

<xsl:for-each select="//packagedElement[@xmi:id=$FormularID]/ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="backendType"><xsl:call-template name="MapType"/></xsl:variable>
<xsl:if test="$backendType!='lb_I_Collection'">
<xsl:if test="@name!=''">
<xsl:value-of select="$backendType"/>* <xsl:value-of select="$FormName"/>Entity::get_<xsl:value-of select="@name"/>() {
	m_<xsl:value-of select="@name"/>++;
	return m_<xsl:value-of select="@name"/>.getPtr();
}

lbErrCodes <xsl:value-of select="$FormName"/>Entity::set_<xsl:value-of select="@name"/>(<xsl:value-of select="$backendType"/>* value) {
	m_<xsl:value-of select="@name"/>_Null = false;
	m_<xsl:value-of select="@name"/> = value;
	m_<xsl:value-of select="@name"/>++;
	return ERR_NONE;
}

bool <xsl:value-of select="$FormName"/>Entity::is_<xsl:value-of select="@name"/>_Null() {
	return m_<xsl:value-of select="@name"/>_Null;
}

lbErrCodes <xsl:value-of select="$FormName"/>Entity::set_<xsl:value-of select="@name"/>_Null() {
	m_<xsl:value-of select="@name"/>_Null = true;
	return ERR_NONE;
}

</xsl:if>
</xsl:if>

</xsl:for-each>
</xsl:template>
</xsl:stylesheet>
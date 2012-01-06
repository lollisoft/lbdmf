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
<xsl:output method="text" indent="no"/>

<xsl:variable name="ApplicationID" select="//lbDMF/@applicationid"/>
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

<xsl:template name="MapTypeObject">
<xsl:variable name="DatatypeID">
	<xsl:value-of select="./type/@xmi:idref"/>
</xsl:variable>
<xsl:if test="./type/@xmi:idref!=''">
<xsl:if test="//packagedElement[@xmi:id=$DatatypeID]/@xmi:type='uml:DataType'">
<xsl:if test="//packagedElement[@xmi:id=$DatatypeID]/@name!='ForeignKey'">
<xsl:value-of select="//packagedElement[@xmi:id=$DatatypeID]/@name"/>
</xsl:if>
</xsl:if>
</xsl:if>
<xsl:if test="//packagedElement[@xmi:id=$DatatypeID]/@name='ForeignKey'">
<xsl:if test="./type/@xmi:type='uml:Class'">lb_I_Integer</xsl:if>
</xsl:if>
<xsl:if test="//packagedElement[@xmi:id=$DatatypeID]/@name!='ForeignKey'">
<xsl:if test="./type/@xmi:type='uml:Class'">lb_I_Container</xsl:if>
</xsl:if>
<xsl:if test="./type/@xmi:type='uml:PrimitiveType'">
	<xsl:choose>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#Boolean'">lb_I_Boolean</xsl:when>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#String'">lb_I_String</xsl:when>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#Integer'">lb_I_Integer</xsl:when>
		<xsl:otherwise>-- Unknown: <xsl:value-of select="./type/@href"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:if>
</xsl:template>

<xsl:template name="Model.h">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>
/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

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
*/
/*...e*/

/** \brief class <xsl:value-of select="$FormName"/>.
 * Documentation for <xsl:value-of select="$FormName"/>
 */
class lb<xsl:value-of select="$FormName"/>Model : public lb_I_<xsl:value-of select="$FormName"/> {
public:
	lb<xsl:value-of select="$FormName"/>Model();
	virtual ~lb<xsl:value-of select="$FormName"/>Model();

	long		LB_STDCALL add<xsl:value-of select="$FormName"/>(<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/><xsl:variable name="TableName" select="@tablename"/><xsl:choose>
<xsl:when test="@isfk='1'">long _<xsl:value-of select="$FieldName"/>, </xsl:when>
<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']"> /* Special column _<xsl:value-of select="@name"/> */</xsl:when>
	<xsl:otherwise><xsl:choose>
	<xsl:when test="@dbtype='Bit'">bool _<xsl:value-of select="$FieldName"/>, </xsl:when>
	<xsl:when test="@dbtype='Float'">float _<xsl:value-of select="$FieldName"/>, </xsl:when>
	<xsl:when test="@dbtype='Integer'">int _<xsl:value-of select="$FieldName"/>, </xsl:when>
	<xsl:when test="@dbtype='String'">const char* _<xsl:value-of select="$FieldName"/>, </xsl:when></xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each> long _<xsl:value-of select="$FormName"/>ID = -1);

	bool		LB_STDCALL select<xsl:value-of select="$FormName"/>(long _id);
	int			LB_STDCALL get<xsl:value-of select="$FormName"/>Count();
	bool		LB_STDCALL hasMore<xsl:value-of select="$FormName"/>();
	void		LB_STDCALL setNext<xsl:value-of select="$FormName"/>();
	void		LB_STDCALL finish<xsl:value-of select="$FormName"/>Iteration();

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>

<xsl:choose>
	<xsl:when test="@isfk='1'">
	long		LB_STDCALL get_<xsl:value-of select="$FieldName"/>();
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
	bool		LB_STDCALL get_<xsl:value-of select="$FieldName"/>();</xsl:when>
			<xsl:when test="@dbtype='Float'">
	float		LB_STDCALL get_<xsl:value-of select="$FieldName"/>();</xsl:when>
			<xsl:when test="@dbtype='Integer'">
	int			LB_STDCALL get_<xsl:value-of select="$FieldName"/>();</xsl:when>
			<xsl:when test="@dbtype='String'">
	char*		LB_STDCALL get_<xsl:value-of select="$FieldName"/>();</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>

	long		LB_STDCALL get_id();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	void		LB_STDCALL setOperator(lb_I_Unknown* db);
	lbErrCodes	LB_STDCALL ExecuteOperation(const char* operationName);

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()
	
	UAP(lb_I_Container, <xsl:value-of select="$FormName"/>)
	
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>

<xsl:choose>
	<xsl:when test="@isfk='1'">
	UAP(lb_I_Long, current<xsl:value-of select="$FieldName"/>)
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
	UAP(lb_I_Boolean, current<xsl:value-of select="$FieldName"/>)
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
	UAP(lb_I_Float, current<xsl:value-of select="$FieldName"/>)
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
	UAP(lb_I_Integer, current<xsl:value-of select="$FieldName"/>)
			</xsl:when>
			<xsl:when test="@dbtype='String'">
	UAP(lb_I_String, current<xsl:value-of select="$FieldName"/>)
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>

	
	UAP(lb_I_Long, current<xsl:value-of select="$FormName"/>ID)

	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflb<xsl:value-of select="$FormName"/>Model)
</xsl:template>
</xsl:stylesheet>

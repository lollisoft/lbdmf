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

<xsl:template name="lookupEntityName">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="FormularID"/>
	<xsl:choose>
		<xsl:when test="./xmi:Extension/stereotype/@name='form'">
		<xsl:for-each select="//packagedElement[@xmi:type='uml:Dependency'][@client=$FormularID]">
			<xsl:variable name="SupplyerClassID" select="@supplier"/>
			<xsl:variable name="SupplierClassStereoType" select="//packagedElement[@xmi:id=$SupplyerClassID]/xmi:Extension/stereotype/@name"/>
			<xsl:if test="$SupplierClassStereoType='entity'">
				<xsl:variable name="DependencyToEntity" select="//packagedElement[@xmi:id=$SupplyerClassID]/@name"/>
				<xsl:value-of select="$DependencyToEntity"/>
			</xsl:if>
		</xsl:for-each>

		</xsl:when>
		<xsl:otherwise><xsl:value-of select="//packagedElement[@xmi:type='uml:Class'][@xmi:id=$FormularID]/@name"/></xsl:otherwise>
</xsl:choose>

	</xsl:template>

<xsl:template name="ApplicationCompositeModel.h">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>/*...sLicence:0:*/
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

/** \brief Storage implementation for XML.
 *
 * This class is used to export the internal representation of an application model. Thus, with this
 * file, you will be able to do what ever you want.
 *
 * Currently there is only implemented the save function.
 */
class lbDynamicAppXMLStorage :
    public lb_I_StandaloneStreamable {
public:
	lbDynamicAppXMLStorage();
	virtual ~lbDynamicAppXMLStorage();

	DECLARE_LB_UNKNOWN()

	lbErrCodes LB_STDCALL setOperator(lb_I_Unknown* _op) { op = _op; op++; return ERR_NONE; }
	lbErrCodes	LB_STDCALL load(lb_I_InputStream* iStream);
	lbErrCodes	LB_STDCALL save(lb_I_OutputStream* oStream);

	lbErrCodes	LB_STDCALL load(lb_I_Database* iDB);
	lbErrCodes	LB_STDCALL save(lb_I_Database* oDB);
	
	UAP(lb_I_Unknown, op)
};

/** \brief Storage implementation for internal fileformat.
 */
class lbDynamicAppInternalStorage :
    public lb_I_StandaloneStreamable {
public:
	lbDynamicAppInternalStorage();
	virtual ~lbDynamicAppInternalStorage();

	DECLARE_LB_UNKNOWN()

	lbErrCodes LB_STDCALL setOperator(lb_I_Unknown* _op) { op = _op; op++; return ERR_NONE; }
	lbErrCodes	LB_STDCALL load(lb_I_InputStream* iStream);
	lbErrCodes	LB_STDCALL save(lb_I_OutputStream* oStream);

	lbErrCodes	LB_STDCALL load(lb_I_Database* iDB);
	lbErrCodes	LB_STDCALL save(lb_I_Database* oDB);
	
	UAP(lb_I_Unknown, op)
};

/** \brief Storage implementation for importing an application model from UML (BoUML via XMI).
 */
class lbDynamicAppBoUMLImportExport :
    public lb_I_StandaloneStreamable {
public:
	lbDynamicAppBoUMLImportExport();
	virtual ~lbDynamicAppBoUMLImportExport();

	DECLARE_LB_UNKNOWN()

	lbErrCodes LB_STDCALL setOperator(lb_I_Unknown* _op) { op = _op; op++; return ERR_NONE; }
	lbErrCodes	LB_STDCALL load(lb_I_InputStream* iStream);
	lbErrCodes	LB_STDCALL save(lb_I_OutputStream* oStream);

	lbErrCodes	LB_STDCALL load(lb_I_Database* iDB);
	lbErrCodes	LB_STDCALL save(lb_I_Database* oDB);
	
	UAP(lb_I_Unknown, op)
};

DECLARE_FUNCTOR(instanceOflbDynamicAppBoUMLImportExport)
DECLARE_FUNCTOR(instanceOflbDynamicAppInternalStorage)
DECLARE_FUNCTOR(instanceOflbDynamicAppXMLStorage)
</xsl:template>
</xsl:stylesheet>

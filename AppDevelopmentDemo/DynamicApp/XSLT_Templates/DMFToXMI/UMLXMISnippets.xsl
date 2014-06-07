<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
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

<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>

<xsl:template name="getXMLEntityName">
	<xsl:param name="FormularID"/>
	<xsl:value-of select="//lbDMF/formularparameter/parameter[@formularid=$FormularID][@name='XMLEntityName']/@value"/>
</xsl:template>

<xsl:template name="WriteXMIClass">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>
	
<xsl:variable name="tempFormularName" select="$FormName"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
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
		&lt;packagedElement xmi:type="uml:Class" name="<xsl:value-of select="$FormularName"/>" xmi:id="<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>" visibility="package" isAbstract="false"&gt;
						&lt;xmi:Extension extender="Bouml"&gt;
							&lt;stereotype name="form"/&gt;
							&lt;taggedValue tag="lbDMF:toolbarimagefile" value="<xsl:value-of select="./@toolbarimage"/>"/&gt;
							&lt;taggedValue tag="lbDMF:xmlentityname" value="<xsl:call-template name="getXMLEntityName"><xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param></xsl:call-template>"/&gt;
						&lt;/xmi:Extension&gt;

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="$FormName"/>

<xsl:variable name="IsSpecialType" select="//columntypes/columntype[@tablename=$TableName][@name=$FieldName]/@specialcolumn"/>
<xsl:variable name="SpecialType" select="//columntypes/columntype[@tablename=$TableName][@name=$FieldName]/@controltype"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_ForeignKey"/&gt;
			&lt;/ownedAttribute&gt;
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Bit"/&gt;
				&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Float"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@dbtype='richtext'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Richtext"/&gt;
				&lt;xmi:Extension extender="Bouml"&gt;&lt;stereotype name="lbDMF:custombinaryfield"/&gt;&lt;/xmi:Extension&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@dbtype='String'">
<xsl:choose>
			<xsl:when test="$IsSpecialType='1' and $SpecialType='toolbarimagefile'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_String"/&gt;
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="lbDMF:toolbarimagefile"/&gt;
				&lt;/xmi:Extension&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="$IsSpecialType='true' and $SpecialType='toolbarimagefile'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_String"/&gt;
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="lbDMF:toolbarimagefile"/&gt;
				&lt;/xmi:Extension&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
	<xsl:otherwise>
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_String"/&gt;
			&lt;/ownedAttribute&gt;
	</xsl:otherwise>
</xsl:choose>

			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

<!-- Generate the unidirectional association properties for this class -->
<xsl:for-each select="//formularactions/action[@formularid=$FormularID]">
	<xsl:variable name="ActionID" select="@actionid"/>
	<xsl:choose>
		<xsl:when test="//actions/action[@ID=$ActionID]/@typ='1'">
		<!-- A Button press action -->
			<xsl:for-each select="//actionsteps/action[@actionid=$ActionID]">
				<xsl:variable name="ActionTypeID" select="@steptyp"/>
				<xsl:variable name="handler" select="//actiontypes/type[@ID=$ActionTypeID]/@handler"/>
				<xsl:choose>
					<xsl:when test="$handler='instanceOflbSQLQueryAction'">
					<!-- A Button press action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbSQLQueryAction'">
					<!-- A SQL query action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbFormAction'">
					<!-- A open form action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbDetailFormAction'">
					<!-- A open detail form action -->
<xsl:variable name="tempFormularName1" select="//formulare/formular[@ID = $FormularID]/@name"/>
<xsl:variable name="TFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName1"/>
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

<xsl:variable name="targetForm" select="@what"/>

<xsl:variable name="tempTargetFormularName" select="@what"/>
<xsl:variable name="TTargetFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempTargetFormularName"/>
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

<xsl:variable name="targetFormID" select="//lbDMF/formulare/formular[@applicationid=$ApplicationID][@name=$targetForm]/@ID"/>

			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$TTargetFormularName"/>" xmi:id="Prop_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" visibility="protected" association="Assoc_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" aggregation="none"&gt;
				&lt;type xmi:idref="<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>"/&gt;
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="lbDMF:masterdetail_action"/&gt;
			<!--	&lt;taggedValue tag="lbDMF:sourcecolumn" value="<xsl:value-of select="$ActionSource"/>"/&gt;	-->
				&lt;/xmi:Extension&gt;
			&lt;/ownedAttribute&gt;
					</xsl:when>
					<xsl:when test="$handler='instanceOflbMasterFormAction'">
					<!-- A open detail form action -->
<xsl:variable name="tempFormularName1" select="//formulare/formular[@ID = $FormularID]/@name"/>
<xsl:variable name="TFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName1"/>
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

<xsl:variable name="targetForm" select="@what"/>

<xsl:variable name="tempTargetFormularName" select="@what"/>
<xsl:variable name="TTargetFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempTargetFormularName"/>
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

<xsl:variable name="targetFormID" select="//lbDMF/formulare/formular[@applicationid=$ApplicationID][@name=$targetForm]/@ID"/>

			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$TTargetFormularName"/>" xmi:id="Prop_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" visibility="protected" association="Assoc_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" aggregation="none"&gt;
				&lt;type xmi:idref="<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>"/&gt;
			&lt;/ownedAttribute&gt;
					</xsl:when>
					<xsl:when test="$handler='instanceOflbDMFXslt'">
					<!-- Perform a code generation -->
<xsl:variable name="tempOperationName" select="//actions/action[@ID=$ActionID]/@name"/>
<xsl:variable name="OperationName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempOperationName"/>
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
						&lt;ownedOperation xmi:type="uml:Operation" name="<xsl:value-of select="$OperationName"/>" xmi:id="Action_<xsl:value-of select="$OperationName"/><xsl:value-of select="@ID"/>" visibility="public" isAbstract="false"&gt;
							&lt;xmi:Extension extender="Bouml"&gt;
								&lt;stereotype name="lbDMF:codegeneration"/&gt;
							&lt;/xmi:Extension&gt;
							&lt;ownedParameter xmi:type="uml:Parameter" name="<xsl:value-of select="//actions/action[@ID=$ActionID]/@source"/>" xmi:id="Param_<xsl:value-of select="$OperationName"/>_param_<xsl:value-of select="@ID"/>" direction="in"&gt;
								&lt;type xmi:type="uml:PrimitiveType" href="http://schema.omg.org/spec/UML/2.1/uml.xml#String"/&gt;
							&lt;/ownedParameter&gt;
						&lt;/ownedOperation&gt;
					</xsl:when>
				</xsl:choose>
			</xsl:for-each>
		</xsl:when>
	</xsl:choose>
</xsl:for-each>

		&lt;/packagedElement&gt;
		
<xsl:for-each select="//formularactions/action[@formularid=$FormularID]">
	<xsl:variable name="ActionID" select="@actionid"/>
	<xsl:variable name="ActionSource" select="//actions/action[@ID=$ActionID]/@source"/>
	<xsl:choose>
		<xsl:when test="//actions/action[@ID=$ActionID]/@typ='1'">
		<!-- A Button press action -->
			<xsl:for-each select="//actionsteps/action[@actionid=$ActionID]">
				<xsl:variable name="ActionTypeID" select="@steptyp"/>
				<xsl:variable name="handler" select="//actiontypes/type[@ID=$ActionTypeID]/@handler"/>
				<xsl:choose>
					<xsl:when test="$handler='instanceOflbSQLQueryAction'">
					<!-- A Button press action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbSQLQueryAction'">
					<!-- A SQL query action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbFormAction'">
					<!-- A open form action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbDetailFormAction'">
					<!-- A open detail form action -->
<xsl:variable name="tempFormularName2" select="//formulare/formular[@ID = $FormularID]/@name"/>
<xsl:variable name="TFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName2"/>
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

<xsl:variable name="targetForm" select="@what"/>

<xsl:variable name="tempTargetFormularName" select="@what"/>
<xsl:variable name="TTargetFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempTargetFormularName"/>
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

<xsl:variable name="targetFormID" select="//lbDMF/formulare/formular[@applicationid=$ApplicationID][@name=$targetForm]/@ID"/>
			&lt;packagedElement xmi:type="uml:Association" xmi:id="Assoc_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" name="<xsl:value-of select="$TTargetFormularName"/>" visibility="package"&gt;
				&lt;memberEnd xmi:idref="Prop_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>"/&gt;
				&lt;ownedEnd xmi:type="uml:Property" xmi:id="Reverse_<xsl:value-of select="@ID"/>" 
						association="Assoc_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" 
						visibility="private" type="<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>" aggregation="none" isNavigable="false"/&gt;
				&lt;memberEnd  xmi:idref="Reverse_<xsl:value-of select="@ID"/>"/&gt;
<!--
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="lbDMF:masterdetail_action"/&gt;
					&lt;taggedValue tag="lbDMF:sourcecolumn" value="<xsl:value-of select="$ActionSource"/>"/&gt;
				&lt;/xmi:Extension&gt;
-->
			&lt;/packagedElement&gt;
					</xsl:when>
					<xsl:when test="$handler='instanceOflbMasterFormAction'">
					<!-- A open master form action -->
<xsl:variable name="tempFormularName2" select="//formulare/formular[@ID = $FormularID]/@name"/>
<xsl:variable name="TFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName2"/>
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

<xsl:variable name="targetForm" select="@what"/>

<xsl:variable name="tempTargetFormularName" select="@what"/>
<xsl:variable name="TTargetFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempTargetFormularName"/>
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

<xsl:variable name="targetFormID" select="//lbDMF/formulare/formular[@applicationid=$ApplicationID][@name=$targetForm]/@ID"/>
			&lt;packagedElement xmi:type="uml:Association" xmi:id="Assoc_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" name="<xsl:value-of select="$TTargetFormularName"/>" visibility="package"&gt;
				&lt;memberEnd xmi:idref="Prop_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>"/&gt;
				&lt;ownedEnd xmi:type="uml:Property" xmi:id="Reverse_<xsl:value-of select="@ID"/>" 
						association="Assoc_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" 
						visibility="private" type="<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>" aggregation="none" isNavigable="false"/&gt;
				&lt;memberEnd  xmi:idref="Reverse_<xsl:value-of select="@ID"/>"/&gt;
<!--
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="lbDMF:detailmaster_action"/&gt;
					&lt;taggedValue tag="lbDMF:sourcecolumn" value="<xsl:value-of select="$ActionSource"/>"/&gt;
				&lt;/xmi:Extension&gt;
-->
			&lt;/packagedElement&gt;
					</xsl:when>
				</xsl:choose>
			</xsl:for-each>
		</xsl:when>
	</xsl:choose>
</xsl:for-each>

</xsl:template>

<xsl:template name="WriteXMIClass_Bootstrap">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>
	
<xsl:variable name="tempFormularName" select="$FormName"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
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
		&lt;packagedElement xmi:type="uml:Class" name="<xsl:value-of select="$FormularName"/>" xmi:id="Bootstrap_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>" visibility="package" isAbstract="false"&gt;
&lt;ownedComment xmi:type="uml:Comment" xmi:id="COMMENT__Bootstrap_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>" body="<xsl:value-of select="@remarks"/>"/&gt;
						&lt;xmi:Extension extender="Bouml"&gt;
							&lt;stereotype name="form"/&gt;
							&lt;taggedValue tag="lbDMF:toolbarimagefile" value=""/&gt;
							&lt;taggedValue tag="lbDMF:xmlentityname" value="<xsl:call-template name="getXMLEntityName"><xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param></xsl:call-template>"/&gt;
						&lt;/xmi:Extension&gt;

<xsl:for-each select="//lbDMF/dbcolumns/column[@tablename=$FormName]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="$FormName"/>

		<xsl:choose>
			<xsl:when test="@typ='bit'">
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Bit"/&gt;
				&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='bool'">
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Bit"/&gt;
				&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='BOOLEAN'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Bit"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='richtext'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Richtext"/&gt;
				&lt;xmi:Extension extender="Bouml"&gt;&lt;stereotype name="lbDMF:custombinaryfield"/&gt;&lt;/xmi:Extension&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='numeric'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Float"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='integer'">
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
				&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='int'">
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
				&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='bigint'">
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
				&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='tinyint'">
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
				&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='int4'">
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
				&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='int8'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='text'">
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_String"/&gt;
				&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='blob'">
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_String"/&gt;
				&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='bpchar'">
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_String"/&gt;
				&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='varchar'">
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_String"/&gt;
				&lt;/ownedAttribute&gt;
			</xsl:when>
		</xsl:choose>
</xsl:for-each>

<!-- Generate the unidirectional association properties for this class -->
<xsl:for-each select="//formularactions/action[@formularid=$FormularID]">
	<xsl:variable name="ActionID" select="@actionid"/>
	<xsl:choose>
		<xsl:when test="//actions/action[@ID=$ActionID]/@typ='1'">
		<!-- A Button press action -->
			<xsl:for-each select="//actionsteps/action[@actionid=$ActionID]">
				<xsl:variable name="ActionTypeID" select="@steptyp"/>
				<xsl:variable name="handler" select="//actiontypes/type[@ID=$ActionTypeID]/@handler"/>
				<xsl:choose>
					<xsl:when test="$handler='instanceOflbSQLQueryAction'">
					<!-- A Button press action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbSQLQueryAction'">
					<!-- A SQL query action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbFormAction'">
					<!-- A open form action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbDetailFormAction'">
					<!-- A open detail form action -->
<xsl:variable name="tempFormularName1" select="//formulare/formular[@ID = $FormularID]/@name"/>
<xsl:variable name="TFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName1"/>
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

<xsl:variable name="targetForm" select="@what"/>

<xsl:variable name="tempTargetFormularName" select="@what"/>
<xsl:variable name="TTargetFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempTargetFormularName"/>
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

<xsl:variable name="targetFormID" select="//lbDMF/formulare/formular[@applicationid=$ApplicationID][@name=$targetForm]/@ID"/>

			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$TTargetFormularName"/>" xmi:id="Prop_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" visibility="protected" association="Assoc_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" aggregation="none"&gt;
				&lt;type xmi:idref="<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>"/&gt;
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="lbDMF:masterdetail_action"/&gt;
			<!--	&lt;taggedValue tag="lbDMF:sourcecolumn" value="<xsl:value-of select="$ActionSource"/>"/&gt;	-->
				&lt;/xmi:Extension&gt;
			&lt;/ownedAttribute&gt;
					</xsl:when>
					<xsl:when test="$handler='instanceOflbMasterFormAction'">
					<!-- A open detail form action -->
<xsl:variable name="tempFormularName1" select="//formulare/formular[@ID = $FormularID]/@name"/>
<xsl:variable name="TFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName1"/>
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

<xsl:variable name="targetForm" select="@what"/>

<xsl:variable name="tempTargetFormularName" select="@what"/>
<xsl:variable name="TTargetFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempTargetFormularName"/>
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

<xsl:variable name="targetFormID" select="//lbDMF/formulare/formular[@applicationid=$ApplicationID][@name=$targetForm]/@ID"/>

			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$TTargetFormularName"/>" xmi:id="Prop_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" visibility="protected" association="Assoc_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" aggregation="none"&gt;
				&lt;type xmi:idref="<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>"/&gt;
			&lt;/ownedAttribute&gt;
					</xsl:when>
					<xsl:when test="$handler='instanceOflbDMFXslt'">
					<!-- Perform a code generation -->
<xsl:variable name="tempOperationName" select="//actions/action[@ID=$ActionID]/@name"/>
<xsl:variable name="OperationName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempOperationName"/>
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
						&lt;ownedOperation xmi:type="uml:Operation" name="<xsl:value-of select="$OperationName"/>" xmi:id="Action_<xsl:value-of select="$OperationName"/><xsl:value-of select="@ID"/>" visibility="public" isAbstract="false"&gt;
							&lt;xmi:Extension extender="Bouml"&gt;
								&lt;stereotype name="lbDMF:codegeneration"/&gt;
							&lt;/xmi:Extension&gt;
							&lt;ownedParameter xmi:type="uml:Parameter" name="<xsl:value-of select="//actions/action[@ID=$ActionID]/@source"/>" xmi:id="Param_<xsl:value-of select="$OperationName"/>_param_<xsl:value-of select="@ID"/>" direction="in"&gt;
								&lt;type xmi:type="uml:PrimitiveType" href="http://schema.omg.org/spec/UML/2.1/uml.xml#String"/&gt;
							&lt;/ownedParameter&gt;
						&lt;/ownedOperation&gt;
					</xsl:when>
				</xsl:choose>
			</xsl:for-each>
		</xsl:when>
	</xsl:choose>
</xsl:for-each>

		&lt;/packagedElement&gt;
		
<xsl:for-each select="//formularactions/action[@formularid=$FormularID]">
	<xsl:variable name="ActionID" select="@actionid"/>
	<xsl:variable name="ActionSource" select="//actions/action[@ID=$ActionID]/@source"/>
	<xsl:choose>
		<xsl:when test="//actions/action[@ID=$ActionID]/@typ='1'">
		<!-- A Button press action -->
			<xsl:for-each select="//actionsteps/action[@actionid=$ActionID]">
				<xsl:variable name="ActionTypeID" select="@steptyp"/>
				<xsl:variable name="handler" select="//actiontypes/type[@ID=$ActionTypeID]/@handler"/>
				<xsl:choose>
					<xsl:when test="$handler='instanceOflbSQLQueryAction'">
					<!-- A Button press action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbSQLQueryAction'">
					<!-- A SQL query action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbFormAction'">
					<!-- A open form action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbDetailFormAction'">
					<!-- A open detail form action -->
<xsl:variable name="tempFormularName2" select="//formulare/formular[@ID = $FormularID]/@name"/>
<xsl:variable name="TFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName2"/>
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

<xsl:variable name="targetForm" select="@what"/>

<xsl:variable name="tempTargetFormularName" select="@what"/>
<xsl:variable name="TTargetFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempTargetFormularName"/>
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

<xsl:variable name="targetFormID" select="//lbDMF/formulare/formular[@applicationid=$ApplicationID][@name=$targetForm]/@ID"/>
			&lt;packagedElement xmi:type="uml:Association" xmi:id="Assoc_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" name="<xsl:value-of select="$TTargetFormularName"/>" visibility="package"&gt;
				&lt;memberEnd xmi:idref="Prop_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>"/&gt;
				&lt;ownedEnd xmi:type="uml:Property" xmi:id="Reverse_<xsl:value-of select="@ID"/>" 
						association="Assoc_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" 
						visibility="private" type="<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>" aggregation="none" isNavigable="false"/&gt;
				&lt;memberEnd  xmi:idref="Reverse_<xsl:value-of select="@ID"/>"/&gt;
<!--
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="lbDMF:masterdetail_action"/&gt;
					&lt;taggedValue tag="lbDMF:sourcecolumn" value="<xsl:value-of select="$ActionSource"/>"/&gt;
				&lt;/xmi:Extension&gt;
-->
			&lt;/packagedElement&gt;
					</xsl:when>
					<xsl:when test="$handler='instanceOflbMasterFormAction'">
					<!-- A open master form action -->
<xsl:variable name="tempFormularName2" select="//formulare/formular[@ID = $FormularID]/@name"/>
<xsl:variable name="TFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName2"/>
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

<xsl:variable name="targetForm" select="@what"/>

<xsl:variable name="tempTargetFormularName" select="@what"/>
<xsl:variable name="TTargetFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempTargetFormularName"/>
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

<xsl:variable name="targetFormID" select="//lbDMF/formulare/formular[@applicationid=$ApplicationID][@name=$targetForm]/@ID"/>
			&lt;packagedElement xmi:type="uml:Association" xmi:id="Assoc_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" name="<xsl:value-of select="$TTargetFormularName"/>" visibility="package"&gt;
				&lt;memberEnd xmi:idref="Prop_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>"/&gt;
				&lt;ownedEnd xmi:type="uml:Property" xmi:id="Reverse_<xsl:value-of select="@ID"/>" 
						association="Assoc_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" 
						visibility="private" type="<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>" aggregation="none" isNavigable="false"/&gt;
				&lt;memberEnd  xmi:idref="Reverse_<xsl:value-of select="@ID"/>"/&gt;
<!--
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="lbDMF:detailmaster_action"/&gt;
					&lt;taggedValue tag="lbDMF:sourcecolumn" value="<xsl:value-of select="$ActionSource"/>"/&gt;
				&lt;/xmi:Extension&gt;
-->
			&lt;/packagedElement&gt;
					</xsl:when>
				</xsl:choose>
			</xsl:for-each>
		</xsl:when>
	</xsl:choose>
</xsl:for-each>

</xsl:template>

<xsl:template name="WriteXMIClassRelationalActionStereotype">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>

<!-- Generate the unidirectional association properties for this class -->
<xsl:for-each select="//formularactions/action[@formularid=$FormularID]">
	<xsl:variable name="ActionID" select="@actionid"/>
	<xsl:variable name="ActionSource" select="//actions/action[@ID=$ActionID]/@source"/>
	<xsl:choose>
		<xsl:when test="//actions/action[@ID=$ActionID]/@typ='1'">
		<!-- A Button press action -->
			<xsl:for-each select="//actionsteps/action[@actionid=$ActionID]">
				<xsl:variable name="ActionTypeID" select="@steptyp"/>
				<xsl:variable name="handler" select="//actiontypes/type[@ID=$ActionTypeID]/@handler"/>
				<xsl:choose>
					<xsl:when test="$handler='instanceOflbSQLQueryAction'">
					<!-- A Button press action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbSQLQueryAction'">
					<!-- A SQL query action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbFormAction'">
					<!-- A open form action -->
					</xsl:when>
					<xsl:when test="$handler='instanceOflbDetailFormAction'">
					<!-- A open detail form action -->
<xsl:variable name="tempFormularName" select="//formulare/formular[@ID = $FormularID]/@name"/>
<xsl:variable name="TFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
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

<xsl:variable name="targetForm" select="@what"/>

<xsl:variable name="tempTargetFormularName" select="@what"/>
<xsl:variable name="TTargetFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempTargetFormularName"/>
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

<xsl:variable name="tempFormularName3" select="$FormName"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName3"/>
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

<xsl:variable name="targetFormID" select="//lbDMF/formulare/formular[@applicationid=$ApplicationID][@name=$targetForm]/@ID"/>
			&lt;lbDMF:masterdetail_action xmi:id="STELT_Prop_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" 
			sourcecolumn="<xsl:value-of select="$ActionSource"/>"
			base_Element="Prop_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>"/&gt;
					</xsl:when>
					<xsl:when test="$handler='instanceOflbMasterFormAction'">
					<!-- A open master form action -->
<xsl:variable name="tempFormularName" select="//formulare/formular[@ID = $FormularID]/@name"/>
<xsl:variable name="TFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
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

<xsl:variable name="targetForm" select="@what"/>

<xsl:variable name="tempTargetFormularName" select="@what"/>
<xsl:variable name="TTargetFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempTargetFormularName"/>
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

<xsl:variable name="tempFormularName3" select="$FormName"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName3"/>
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

<xsl:variable name="targetFormID" select="//lbDMF/formulare/formular[@applicationid=$ApplicationID][@name=$targetForm]/@ID"/>
			&lt;lbDMF:detailmaster_action xmi:id="STELT_Prop_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>" 
			sourcecolumn="<xsl:value-of select="$ActionSource"/>"
			base_Element="Prop_<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>"/&gt;
					</xsl:when>
				</xsl:choose>
			</xsl:for-each>
		</xsl:when>
	</xsl:choose>
</xsl:for-each>
</xsl:template>

<xsl:template name="WriteXMIEntityRelationStereotype">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="EntityID"/>
	<xsl:param name="EntityName"/>

<xsl:for-each select="//dbcolumns/column[@tablename=$EntityName]">
<xsl:variable name="FieldName" select="@name"/>
<xsl:variable name="TableName" select="@tablename"/>
<xsl:for-each select="//foreignkeys/foreignkey[@pktable=$EntityName][@pkcolumn=$FieldName]">
<!--
			&lt;lbDMF:relationship xmi:id="STELT_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@ID"/>" base_Element="<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@ID"/>"/&gt;
-->
</xsl:for-each>
<xsl:for-each select="//foreignkeys/foreignkey[@fktable=$EntityName][@fkcolumn=$FieldName]">
			&lt;lbDMF:relationship xmi:id="STELT_<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@ID"/>" 
			sourcecolumn="<xsl:value-of select="@pkcolumn"/>" table="<xsl:value-of select="@pktable"/>" order="<xsl:value-of select="@keysequence"/>"
			base_Element="<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@ID"/>"/&gt;
</xsl:for-each>
</xsl:for-each>
</xsl:template>


<xsl:template name="WriteXMIClassRelationalActions">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>
	
<xsl:variable name="tempFormularName" select="$FormName"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
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
		&lt;packagedElement xmi:type="uml:Class" name="<xsl:value-of select="$FormularName"/>" xmi:id="<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>" visibility="package" isAbstract="false"&gt;
						&lt;xmi:Extension extender="Bouml"&gt;
							&lt;stereotype name="form"/&gt;
						&lt;/xmi:Extension&gt;

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_ForeignKey"/&gt;
			&lt;/ownedAttribute&gt;
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Bit"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Float"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@dbtype='String'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_String"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
		&lt;/packagedElement&gt;
</xsl:template>

<xsl:template name="WriteXMIEntity">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="TableID"/>
	<xsl:param name="TableName"/>
	
<xsl:variable name="tempTableName" select="$TableName"/>
<xsl:variable name="TName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempTableName"/>
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
		&lt;packagedElement xmi:type="uml:Class" name="<xsl:value-of select="$TName"/>" xmi:id="ID_<xsl:value-of select="$TName"/>" visibility="package" isAbstract="false"&gt;
			&lt;xmi:Extension extender="Bouml"&gt;
				&lt;stereotype name="entity"/&gt;
			&lt;/xmi:Extension&gt;

<xsl:for-each select="//dbcolumns/column[@tablename=$TName]">
<xsl:variable name="FieldName" select="@name"/>
<xsl:variable name="TableName" select="@tablename"/>

<xsl:variable name="isForeignKey">
<xsl:for-each select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]"><xsl:if test="position()=0"><xsl:value-of select="$FieldName"/></xsl:if></xsl:for-each>
</xsl:variable>


<xsl:for-each select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]"><xsl:if test="position()=0">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_ForeignKey"/&gt;
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;taggedValue tag="lbDMF:sourcecolumn" value="<xsl:value-of select="@pkcolumn"/>"/&gt;
					&lt;taggedValue tag="lbDMF:table" value="<xsl:value-of select="@pktable"/>"/&gt;
					&lt;taggedValue tag="lbDMF:order" value="<xsl:value-of select="@keysequence"/>"/&gt;
				&lt;/xmi:Extension&gt;
			&lt;/ownedAttribute&gt;
</xsl:if>
</xsl:for-each>
<xsl:if test="$isForeignKey!=$FieldName">
	<xsl:choose>
			<xsl:when test="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]">
			</xsl:when>
			<xsl:when test="@typ='bit'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
			&lt;type xmi:idref="BOUML_datatype_Bit"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='Bit'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
			&lt;type xmi:idref="BOUML_datatype_Bit"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='bool'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Bit"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='BOOLEAN'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Bit"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='richtext'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Richtext"/&gt;
				&lt;xmi:Extension extender="Bouml"&gt;&lt;stereotype name="lbDMF:custombinaryfield"/&gt;&lt;/xmi:Extension&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='datetime'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Datetime"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='decimal'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Float"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='Float'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Float"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='tinyint'">
			<xsl:when test="@typ='tinyint'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
			&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
			<xsl:if test="//primarykeys/primarykey[@pktable=$TName][@pkcolumn=$FieldName]">
				&lt;xmi:Extension extender="Bouml"&gt;
				&lt;stereotype name="lbDMF:pk"/&gt;
				&lt;/xmi:Extension&gt;
			</xsl:if>
			<xsl:if test="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]">
				&lt;xmi:Extension extender="Bouml"&gt;
				&lt;stereotype name="lbDMF:fk"/&gt;
				&lt;taggedValue tag="lbDMF:sourcecolumn" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@pkcolumn"/>"/&gt;
				&lt;taggedValue tag="lbDMF:table" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@pktable"/>"/&gt;
				&lt;taggedValue tag="lbDMF:order" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@keysequence"/>"/&gt;
				&lt;/xmi:Extension&gt;
			</xsl:if>
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='integer'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
			&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
			<xsl:if test="//primarykeys/primarykey[@pktable=$TName][@pkcolumn=$FieldName]">
				&lt;xmi:Extension extender="Bouml"&gt;
				&lt;stereotype name="lbDMF:pk"/&gt;
				&lt;/xmi:Extension&gt;
			</xsl:if>
			<xsl:if test="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]">
				&lt;xmi:Extension extender="Bouml"&gt;
				&lt;stereotype name="lbDMF:fk"/&gt;
				&lt;taggedValue tag="lbDMF:sourcecolumn" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@pkcolumn"/>"/&gt;
				&lt;taggedValue tag="lbDMF:table" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@pktable"/>"/&gt;
				&lt;taggedValue tag="lbDMF:order" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@keysequence"/>"/&gt;
				&lt;/xmi:Extension&gt;
			</xsl:if>
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='bigint'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
			&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
			<xsl:if test="//primarykeys/primarykey[@pktable=$TName][@pkcolumn=$FieldName]">
				&lt;xmi:Extension extender="Bouml"&gt;
				&lt;stereotype name="lbDMF:pk"/&gt;
				&lt;/xmi:Extension&gt;
			</xsl:if>
			<xsl:if test="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]">
				&lt;xmi:Extension extender="Bouml"&gt;
				&lt;stereotype name="lbDMF:fk"/&gt;
				&lt;taggedValue tag="lbDMF:sourcecolumn" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@pkcolumn"/>"/&gt;
				&lt;taggedValue tag="lbDMF:table" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@pktable"/>"/&gt;
				&lt;taggedValue tag="lbDMF:order" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@keysequence"/>"/&gt;
				&lt;/xmi:Extension&gt;
			</xsl:if>
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='int'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
				<xsl:if test="//primarykeys/primarykey[@pktable=$TName][@pkcolumn=$FieldName]">
					&lt;xmi:Extension extender="Bouml"&gt;
						&lt;stereotype name="lbDMF:pk"/&gt;
					&lt;/xmi:Extension&gt;
				</xsl:if>
				<xsl:if test="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]">
					&lt;xmi:Extension extender="Bouml"&gt;
						&lt;stereotype name="lbDMF:fk"/&gt;
						&lt;taggedValue tag="lbDMF:sourcecolumn" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@pkcolumn"/>"/&gt;
						&lt;taggedValue tag="lbDMF:table" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@pktable"/>"/&gt;
						&lt;taggedValue tag="lbDMF:order" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@keysequence"/>"/&gt;
					&lt;/xmi:Extension&gt;
				</xsl:if>
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='int4'">

			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
				<xsl:if test="//primarykeys/primarykey[@pktable=$TName][@pkcolumn=$FieldName]">
					&lt;xmi:Extension extender="Bouml"&gt;
						&lt;stereotype name="lbDMF:pk"/&gt;
					&lt;/xmi:Extension&gt;
				</xsl:if>
				<xsl:if test="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]">
					&lt;xmi:Extension extender="Bouml"&gt;
						&lt;stereotype name="lbDMF:fk"/&gt;
						&lt;taggedValue tag="lbDMF:sourcecolumn" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@pkcolumn"/>"/&gt;
						&lt;taggedValue tag="lbDMF:table" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@pktable"/>"/&gt;
						&lt;taggedValue tag="lbDMF:order" value="<xsl:value-of select="//foreignkeys/foreignkey[@fkcolumn=$FieldName][@fktable=$TableName]/@keysequence"/>"/&gt;
					&lt;/xmi:Extension&gt;
				</xsl:if>
			&lt;/ownedAttribute&gt;

			</xsl:when>
			<xsl:when test="@typ='varchar'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
			&lt;type xmi:idref="BOUML_datatype_String"/&gt;
			<xsl:if test="//formularfields/formular[@fktable=$TName][@fkname=$FieldName]/@isfk=1">
				&lt;xmi:Extension extender="Bouml"&gt;
				&lt;stereotype name="visible"/&gt;
				&lt;/xmi:Extension&gt;
			</xsl:if>
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='bpchar'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_String"/&gt;
<xsl:if test="//formularfields/formular[@fktable=$TName][@fkname=$FieldName]/@isfk=1">
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="visible"/&gt;
				&lt;/xmi:Extension&gt;
</xsl:if>
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='blob'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
			&lt;type xmi:idref="BOUML_datatype_String"/&gt;
			<xsl:if test="//formularfields/formular[@fktable=$TName][@fkname=$FieldName]/@isfk=1">
				&lt;xmi:Extension extender="Bouml"&gt;
				&lt;stereotype name="visible"/&gt;
				&lt;/xmi:Extension&gt;
			</xsl:if>
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='text'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Text"/&gt;
<xsl:if test="//formularfields/formular[@fktable=$TName][@fkname=$FieldName]/@isfk=1">
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="visible"/&gt;
				&lt;/xmi:Extension&gt;
</xsl:if>
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='varchar'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Text"/&gt;
<xsl:if test="//formularfields/formular[@fktable=$TName][@fkname=$FieldName]/@isfk=1">
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="visible"/&gt;
				&lt;/xmi:Extension&gt;
</xsl:if>
			&lt;/ownedAttribute&gt;
			</xsl:when>
		</xsl:choose>
</xsl:if>

<xsl:for-each select="//foreignkeys/foreignkey[@fktable=$TName][@fkcolumn=$FieldName]">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="@fkcolumn"/>" xmi:id="<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@ID"/>"	visibility="protected" association="ASSOC_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@ID"/>" aggregation="none"&gt;
				&lt;type xmi:type="uml:Class" xmi:idref="ID_<xsl:value-of select="@pktable"/>"/&gt;
				&lt;lowerValue xmi:type="uml:LiteralString" xmi:id="MULTIPLICITY_LOWER_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@fktable"/>" value="1"/&gt;
				&lt;upperValue xmi:type="uml:LiteralString" xmi:id="MULTIPLICITY_UPPER_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@fktable"/>" value="1"/&gt;
			&lt;/ownedAttribute&gt;
</xsl:for-each>
<xsl:for-each select="//foreignkeys/foreignkey[@pktable=$TName][@pkcolumn=$FieldName]">
			&lt;ownedAttribute xmi:type="uml:Property" name="" xmi:id="<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@ID"/>" visibility="protected" association="ASSOC_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@ID"/>" aggregation="none"&gt;
				&lt;type  xmi:type="uml:Class" xmi:idref="ID_<xsl:value-of select="@fktable"/>"/&gt;
				&lt;lowerValue xmi:type="uml:LiteralString" xmi:id="MULTIPLICITY_LOWER_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@fktable"/>" value="*"/&gt;
				&lt;upperValue xmi:type="uml:LiteralString" xmi:id="MULTIPLICITY_UPPER_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@fktable"/>" value="*"/&gt;
			&lt;/ownedAttribute&gt;
</xsl:for-each>
</xsl:for-each>
		&lt;/packagedElement&gt;

<!-- Write the uml:Association elements for each table relation -->
<xsl:for-each select="//foreignkeys/foreignkey[@pktable=$TName]">
			&lt;packagedElement xmi:type="uml:Association" xmi:id="ASSOC_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;memberEnd xmi:idref="<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@ID"/>"/&gt;
				&lt;memberEnd xmi:idref="<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@ID"/>"/&gt;
			&lt;/packagedElement&gt;
</xsl:for-each>

<xsl:for-each select="//formularfields/formular[@tablename=$TableName]">
		<xsl:if test="position()=1">
			<xsl:variable name="FormID" select="@formularid"/>

<xsl:variable name="tempFormularName" select="//formulare/formular[@ID = $FormID]/@name"/>
<xsl:variable name="TFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
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

			&lt;packagedElement xmi:type="uml:Dependency" xmi:id="FormID_<xsl:value-of select="@ID"/>" client="<xsl:value-of select="$TFormularName"/>_<xsl:value-of select="@formularid"/>" supplier="ID_<xsl:value-of select="//dbtables/table[@name=$TableName]/@name"/>"&gt;
			&lt;/packagedElement&gt;
		</xsl:if>
</xsl:for-each>		
		
</xsl:template>

</xsl:stylesheet>

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

<xsl:template name="Model.cpp">
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

#ifdef LBDMF_PREC
#include &lt;lbConfigHook.h&gt;
#endif

#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#ifndef UNIX
#include &lt;windows.h&gt;
#endif
#ifdef UNIX
#endif

#ifndef LBDMF_PREC
#include &lt;lbConfigHook.h&gt;
#endif

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include &lt;lbdmfdatamodel-module.h&gt;
/*...e*/
#include &lt;lbInterfaces-<xsl:value-of select="$ApplicationName"/>.h&gt;
#include &lt;lb<xsl:value-of select="$FormName"/>Model.h&gt;

IMPLEMENT_FUNCTOR(instanceOflb<xsl:value-of select="$FormName"/>Model, lb<xsl:value-of select="$FormName"/>Model)

BEGIN_IMPLEMENT_LB_UNKNOWN(lb<xsl:value-of select="$FormName"/>Model)
	ADD_INTERFACE(lb_I_<xsl:value-of select="$FormName"/>)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lb<xsl:value-of select="$FormName"/>Model)

void		LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lb<xsl:value-of select="$FormName"/>Model::lb<xsl:value-of select="$FormName"/>Model() {
	
	REQUEST(getModuleInstance(), lb_I_Container, <xsl:value-of select="$FormName"/>)

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/> <xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'"><xsl:value-of select="'    '"/>REQUEST(getModuleInstance(), lb_I_Long, current<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">// Special column <xsl:value-of select="@name"/>
</xsl:when>
<xsl:otherwise>
<xsl:choose><xsl:when test="@dbtype='Bit'"><xsl:value-of select="'    '"/>REQUEST(getModuleInstance(), lb_I_Boolean, current<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="@dbtype='Float'"><xsl:value-of select="'    '"/>REQUEST(getModuleInstance(), lb_I_Float, current<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="@dbtype='Integer'"><xsl:value-of select="'    '"/>REQUEST(getModuleInstance(), lb_I_Integer, current<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="@dbtype='String'"><xsl:value-of select="'    '"/>REQUEST(getModuleInstance(), lb_I_String, current<xsl:value-of select="@name"/>)
</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>
	
	REQUEST(getModuleInstance(), lb_I_Long, current<xsl:value-of select="$FormName"/>ID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE &lt;&lt; "lb<xsl:value-of select="$FormName"/>Model::lb<xsl:value-of select="$FormName"/>Model() called." LOG_
}

lb<xsl:value-of select="$FormName"/>Model::~lb<xsl:value-of select="$FormName"/>Model() {
	_CL_VERBOSE &lt;&lt; "lb<xsl:value-of select="$FormName"/>Model::~lb<xsl:value-of select="$FormName"/>Model() called." LOG_
}

lbErrCodes LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::setData(lb_I_Unknown*) {
	_LOG &lt;&lt; "Error: lb<xsl:value-of select="$FormName"/>Model::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::add<xsl:value-of select="$FormName"/>(<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/><xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">long <xsl:value-of select="$FieldName"/>, </xsl:when>
<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">/* Special column <xsl:value-of select="@name"/> */</xsl:when>
<xsl:otherwise><xsl:choose>
<xsl:when test="@dbtype='Bit'">bool <xsl:value-of select="$FieldName"/>, </xsl:when>
<xsl:when test="@dbtype='Float'">float <xsl:value-of select="$FieldName"/>, </xsl:when>
<xsl:when test="@dbtype='Integer'">int <xsl:value-of select="$FieldName"/>, </xsl:when>
<xsl:when test="@dbtype='String'">char* <xsl:value-of select="$FieldName"/>, </xsl:when>
</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each> long <xsl:value-of select="$FormName"/>ID) {
	lbErrCodes err = ERR_NONE;

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/> <xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'"><xsl:value-of select="'    '"/>UAP_REQUEST(getModuleInstance(), lb_I_Long, _<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">// Special column <xsl:value-of select="@name"/>
</xsl:when>
<xsl:otherwise>
<xsl:choose><xsl:when test="@dbtype='Bit'"><xsl:value-of select="'    '"/>UAP_REQUEST(getModuleInstance(), lb_I_Boolean, _<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="@dbtype='Float'"><xsl:value-of select="'    '"/>UAP_REQUEST(getModuleInstance(), lb_I_Float, _<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="@dbtype='Integer'"><xsl:value-of select="'    '"/>UAP_REQUEST(getModuleInstance(), lb_I_Integer, _<xsl:value-of select="@name"/>)
</xsl:when><xsl:when test="@dbtype='String'"><xsl:value-of select="'    '"/>UAP_REQUEST(getModuleInstance(), lb_I_String, _<xsl:value-of select="@name"/>)
</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>

	UAP_REQUEST(getModuleInstance(), lb_I_Long, _<xsl:value-of select="$FormName"/>ID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/> <xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'"><xsl:value-of select="'    '"/>_<xsl:value-of select="@name"/>-&gt;setData(<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">// Special column <xsl:value-of select="@name"/>
</xsl:when>
<xsl:otherwise>
<xsl:choose><xsl:when test="@dbtype='Bit'"><xsl:value-of select="'    '"/>_<xsl:value-of select="@name"/>-&gt;setData(<xsl:value-of select="@name"/>));
</xsl:when><xsl:when test="@dbtype='Float'"><xsl:value-of select="'    '"/>_<xsl:value-of select="@name"/>-&gt;setData(<xsl:value-of select="@name"/>));
</xsl:when><xsl:when test="@dbtype='Integer'"><xsl:value-of select="'    '"/>_<xsl:value-of select="@name"/>-&gt;setData(<xsl:value-of select="@name"/>));
</xsl:when><xsl:when test="@dbtype='String'"><xsl:value-of select="'    '"/>*_<xsl:value-of select="@name"/> = <xsl:value-of select="@name"/>;
</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>
	
	_<xsl:value-of select="$FormName"/>ID-&gt;setData(<xsl:value-of select="$FormName"/>ID);

	_LOG &lt;&lt; "lb<xsl:value-of select="$FormName"/>Model::add<xsl:value-of select="$FormName"/>('" &lt;&lt; name &lt;&lt; "', '" &lt;&lt; menuname &lt;&lt; "'...) called." LOG_
	
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/> <xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;setUAPLong(*&amp;paramname, *&amp;_<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
// Special column <xsl:value-of select="@name"/>
</xsl:when>
<xsl:otherwise>
<xsl:choose><xsl:when test="@dbtype='Bit'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;setUAPBoolean(*&amp;paramname, *&amp;_<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='Float'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;setUAPFloat(*&amp;paramname, *&amp;_<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='Integer'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;setUAPInteger(*&amp;paramname, *&amp;_<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='String'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;setUAPString(*&amp;paramname, *&amp;_<xsl:value-of select="@name"/>);
</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>

	*paramname = "<xsl:value-of select="$FormName"/>ID";
	param-&gt;setUAPLong(*&amp;paramname, *&amp;<xsl:value-of select="$FormName"/>ID);

	*paramname = "marked";
	param-&gt;setUAPLong(*&amp;paramname, *&amp;marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(<xsl:value-of select="$FormName"/>ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	<xsl:value-of select="$FormName"/>-&gt;insert(&amp;ukParam, &amp;key);

	return -1;
}

void		LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	<xsl:value-of select="$FormName"/>-&gt;finishIteration();
	while (hasMore<xsl:value-of select="$FormName"/>()) {
		setNext<xsl:value-of select="$FormName"/>();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID-&gt;setData(getID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			<xsl:value-of select="$FormName"/>-&gt;remove(&amp;key);
			<xsl:value-of select="$FormName"/>-&gt;finishIteration();
		}
	}
}

void		LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	<xsl:value-of select="$FormName"/>-&gt;finishIteration();
	while (hasMore<xsl:value-of select="$FormName"/>()) {
		setNext<xsl:value-of select="$FormName"/>();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID-&gt;setData(getID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			<xsl:value-of select="$FormName"/>-&gt;remove(&amp;key);
			<xsl:value-of select="$FormName"/>-&gt;finishIteration();
		}
	}
}

bool LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::select<xsl:value-of select="$FormName"/>(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID-&gt;setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = <xsl:value-of select="$FormName"/>-&gt;getElement(&amp;key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/> <xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPLong(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
// Special column <xsl:value-of select="@name"/>
</xsl:when>
<xsl:otherwise>
<xsl:choose><xsl:when test="@dbtype='Bit'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPBoolean(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='Float'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPFloat(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='Integer'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPInteger(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='String'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPString(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>

		*paramname = "<xsl:value-of select="$FormName"/>ID";
		param-&gt;getUAPLong(*&amp;paramname, *&amp;current<xsl:value-of select="$FormName"/>ID);

		*paramname = "marked";
		param-&gt;getUAPLong(*&amp;paramname, *&amp;marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::ismarked() {
	if (marked-&gt;getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::mark() {
	marked-&gt;setData((long) 1);
}

void LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::unmark() {
	marked-&gt;setData((long) 0);
}

int  LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::get<xsl:value-of select="$FormName"/>Count() {
	return <xsl:value-of select="$FormName"/>-&gt;Count();
}

bool  LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::hasMore<xsl:value-of select="$FormName"/>() {
	return (<xsl:value-of select="$FormName"/>-&gt;hasMoreElements() == 1);
}

void  LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::setNext<xsl:value-of select="$FormName"/>() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = <xsl:value-of select="$FormName"/>-&gt;nextElement();
	QI(uk, lb_I_Parameter, param)

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/> <xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPLong(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
// Special column <xsl:value-of select="@name"/>
</xsl:when>
<xsl:otherwise>
<xsl:choose><xsl:when test="@dbtype='Bit'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPBoolean(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='Float'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPFloat(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='Integer'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPInteger(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when><xsl:when test="@dbtype='String'">
<xsl:value-of select="'    '"/>*paramname = "<xsl:value-of select="@name"/>";
<xsl:value-of select="'    '"/>param-&gt;getUAPString(*&amp;paramname, *&amp;current<xsl:value-of select="@name"/>);
</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>
	*paramname = "<xsl:value-of select="$FormName"/>ID";
	param-&gt;getUAPLong(*&amp;paramname, *&amp;current<xsl:value-of select="$FormName"/>ID);

	*paramname = "marked";
	param-&gt;getUAPLong(*&amp;paramname, *&amp;marked);
	
}

void  LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::finish<xsl:value-of select="$FormName"/>Iteration() {
	<xsl:value-of select="$FormName"/>-&gt;finishIteration();
}

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/> <xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">
long LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::get_<xsl:value-of select="@name"/>() {
	return current<xsl:value-of select="@name"/>-&gt;getData();
}
</xsl:when><xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
// Special column <xsl:value-of select="@name"/>
</xsl:when>
<xsl:otherwise>
<xsl:choose><xsl:when test="@dbtype='Bit'">
boolean LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::get_<xsl:value-of select="@name"/>() {
	return current<xsl:value-of select="@name"/>-&gt;getData();
}
</xsl:when><xsl:when test="@dbtype='Float'">
float LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::get_<xsl:value-of select="@name"/>() {
	return current<xsl:value-of select="@name"/>-&gt;getData();
}
</xsl:when><xsl:when test="@dbtype='Integer'">
int LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::get_<xsl:value-of select="@name"/>() {
	return current<xsl:value-of select="@name"/>-&gt;getData();
}
</xsl:when><xsl:when test="@dbtype='String'">
char* LB_STDCALL lb<xsl:value-of select="$FormName"/>Model::get_<xsl:value-of select="@name"/>() {
	return current<xsl:value-of select="@name"/>-&gt;charrep();
}
</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>

class lbPlugin<xsl:value-of select="$FormName"/>Model : public lb_I_PluginImpl {
public:
	lbPlugin<xsl:value-of select="$FormName"/>Model();
	
	virtual ~lbPlugin<xsl:value-of select="$FormName"/>Model();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, uk<xsl:value-of select="$FormName"/>Model)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPlugin<xsl:value-of select="$FormName"/>Model)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPlugin<xsl:value-of select="$FormName"/>Model, lbPlugin<xsl:value-of select="$FormName"/>Model)

lbErrCodes LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$FormName"/>Model::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPlugin<xsl:value-of select="$FormName"/>Model::lbPlugin<xsl:value-of select="$FormName"/>Model() {
	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$FormName"/>Model::lbPlugin<xsl:value-of select="$FormName"/>Model() called.\n" LOG_
}

lbPlugin<xsl:value-of select="$FormName"/>Model::~lbPlugin<xsl:value-of select="$FormName"/>Model() {
	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$FormName"/>Model::~lbPlugin<xsl:value-of select="$FormName"/>Model() called.\n" LOG_
}

bool LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::initialize() {
}
	
bool LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (uk<xsl:value-of select="$FormName"/>Model == NULL) {
		lb<xsl:value-of select="$FormName"/>Model* <xsl:value-of select="$FormName"/>Model = new lb<xsl:value-of select="$FormName"/>Model();
		
	
		QI(<xsl:value-of select="$FormName"/>Model, lb_I_Unknown, uk<xsl:value-of select="$FormName"/>Model)
	} else {
		_CL_VERBOSE &lt;&lt; "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return uk<xsl:value-of select="$FormName"/>Model.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (uk<xsl:value-of select="$FormName"/>Model == NULL) {

		_CL_VERBOSE &lt;&lt; "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lb<xsl:value-of select="$FormName"/>Model* <xsl:value-of select="$FormName"/>Model = new lb<xsl:value-of select="$FormName"/>Model();
		
	
		QI(<xsl:value-of select="$FormName"/>Model, lb_I_Unknown, uk<xsl:value-of select="$FormName"/>Model)
	}
	
	lb_I_Unknown* r = uk<xsl:value-of select="$FormName"/>Model.getPtr();
	uk<xsl:value-of select="$FormName"/>Model.resetPtr();
	return r;
}

void LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>Model::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (uk<xsl:value-of select="$FormName"/>Model != NULL) {
                uk<xsl:value-of select="$FormName"/>Model--;
                uk<xsl:value-of select="$FormName"/>Model.resetPtr();
        }
}
</xsl:template>
</xsl:stylesheet>
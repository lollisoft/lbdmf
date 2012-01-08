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
<xsl:if test="./type/@xmi:type='uml:Class'">lb_I_Long</xsl:if>
</xsl:if>
<xsl:if test="//packagedElement[@xmi:id=$DatatypeID]/@name!='ForeignKey'">
<xsl:if test="./type/@xmi:type='uml:Class'">lb_I_Container</xsl:if>
</xsl:if>
<xsl:if test="./type/@xmi:type='uml:PrimitiveType'">
	<xsl:choose>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#Boolean'">lb_I_Boolean</xsl:when>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#String'">lb_I_String</xsl:when>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#Integer'">lb_I_Long</xsl:when>
		<xsl:otherwise>-- Unknown: <xsl:value-of select="./type/@href"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:if>
</xsl:template>

<xsl:template name="DBReaderExtension.cpp">
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
#include &lt;lbInterfaces-lbDMFManager.h&gt;
#include &lt;DBReader_<xsl:value-of select="$FormName"/>.h&gt;

IMPLEMENT_FUNCTOR(instanceOf<xsl:value-of select="$FormName"/>DBReaderExtension, <xsl:value-of select="$FormName"/>DBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(<xsl:value-of select="$FormName"/>DBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

<xsl:value-of select="$FormName"/>DBReaderExtension::<xsl:value-of select="$FormName"/>DBReaderExtension() {
	_CL_VERBOSE &lt;&lt; "<xsl:value-of select="$FormName"/>DBReaderExtension::<xsl:value-of select="$FormName"/>DBReaderExtension() called." LOG_
}

<xsl:value-of select="$FormName"/>DBReaderExtension::~<xsl:value-of select="$FormName"/>DBReaderExtension() {
	_CL_VERBOSE &lt;&lt; "<xsl:value-of select="$FormName"/>DBReaderExtension::~<xsl:value-of select="$FormName"/>DBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL <xsl:value-of select="$FormName"/>DBReaderExtension::setData(lb_I_Unknown*) {
	_LOG &lt;&lt; "Error: <xsl:value-of select="$FormName"/>DBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL <xsl:value-of select="$FormName"/>DBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_<xsl:value-of select="$FormName"/>, owningObject)
		if (owningObject == NULL) {
			_LOG &lt;&lt; "Error: <xsl:value-of select="$FormName"/>DBReaderExtension::setOwningObject() owning parameter is not a lb_I_<xsl:value-of select="$FormName"/>." LOG_
		}
	} else {
		_LOG &lt;&lt; "Error: <xsl:value-of select="$FormName"/>DBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL <xsl:value-of select="$FormName"/>DBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG &lt;&lt; "Error: <xsl:value-of select="$FormName"/>DBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp-&gt;getDatabase();
	} else {
		_LOG &lt;&lt; "Error: <xsl:value-of select="$FormName"/>DBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL <xsl:value-of select="$FormName"/>DBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG &lt;&lt; "<xsl:value-of select="$FormName"/>DBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db-&gt;getQuery("lbDMF", 0);

	q-&gt;skipFKCollecting();

	if (q-&gt;query("select <xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/><xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'"><xsl:value-of select="$FieldName"/>, </xsl:when>
<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']"></xsl:when>
<xsl:otherwise><xsl:choose>
<xsl:when test="@dbtype='Bit'"><xsl:value-of select="$FieldName"/>, </xsl:when>
<xsl:when test="@dbtype='Float'"><xsl:value-of select="$FieldName"/>, </xsl:when>
<xsl:when test="@dbtype='Integer'"><xsl:value-of select="$FieldName"/>, </xsl:when>
<xsl:when test="@dbtype='String'"><xsl:value-of select="$FieldName"/>, </xsl:when>
</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each> id from <xsl:value-of select="//lbDMF/formularfields/formular[@formularid=$FormularID]/@tablename"/>") != ERR_NONE) {
		_LOG &lt;&lt; "Error: Access to application table failed. Read <xsl:value-of select="$FormName"/> would be skipped." LOG_
		return;
	}

	err = q-&gt;first();

	if ((err != ERR_NONE) &amp;&amp; (err != WARN_DB_NODATA)) {
		_LOG &lt;&lt; "Error: No <xsl:value-of select="$FormName"/> found. All <xsl:value-of select="$FormName"/> may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/><xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">
		UAP(lb_I_Long, q<xsl:value-of select="$FieldName"/>)</xsl:when>
<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']"></xsl:when>
<xsl:otherwise><xsl:choose>
<xsl:when test="@dbtype='Bit'">
		UAP(lb_I_Boolean, q<xsl:value-of select="$FieldName"/>)</xsl:when>
<xsl:when test="@dbtype='Float'">
		UAP(lb_I_Float, q<xsl:value-of select="$FieldName"/>)</xsl:when>
<xsl:when test="@dbtype='Integer'">
		UAP(lb_I_Long, q<xsl:value-of select="$FieldName"/>)</xsl:when>
<xsl:when test="@dbtype='String'">
		UAP(lb_I_String, q<xsl:value-of select="$FieldName"/>)</xsl:when>
</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

		// Copy values
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/><xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">
		q<xsl:value-of select="$FieldName"/> = q-&gt;getAsLong(<xsl:value-of select="position()"/>);</xsl:when>
<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']"></xsl:when>
<xsl:otherwise><xsl:choose>
<xsl:when test="@dbtype='Bit'">
		UAP(lb_I_String, b<xsl:value-of select="$FieldName"/>)
		b<xsl:value-of select="$FieldName"/> = q-&gt;getAsString(<xsl:value-of select="position()"/>);
		if (*b<xsl:value-of select="$FieldName"/> == "true")
			q<xsl:value-of select="$FieldName"/>-&gt;setData(true);
		else
			q<xsl:value-of select="$FieldName"/>-&gt;setData(false);</xsl:when>
<xsl:when test="@dbtype='Float'">
		q<xsl:value-of select="$FieldName"/> = q-&gt;getAsString(<xsl:value-of select="position()"/>);</xsl:when>
<xsl:when test="@dbtype='Integer'">
		q<xsl:value-of select="$FieldName"/> = q-&gt;getAsLong(<xsl:value-of select="position()"/>);</xsl:when>
<xsl:when test="@dbtype='String'">
		q<xsl:value-of select="$FieldName"/> = q-&gt;getAsString(<xsl:value-of select="position()"/>);</xsl:when>
</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
<xsl:if test="position()=last()">
		qID = q-&gt;getAsLong(<xsl:value-of select="position()+1"/></xsl:if>
</xsl:for-each>);

		owningObject-&gt;add<xsl:value-of select="$FormName"/>(<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/><xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">q<xsl:value-of select="$FieldName"/>-&gt;getData(), </xsl:when>
<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']"></xsl:when>
<xsl:otherwise><xsl:choose>
<xsl:when test="@dbtype='Bit'">q<xsl:value-of select="$FieldName"/>-&gt;getData(), </xsl:when>
<xsl:when test="@dbtype='Float'">q<xsl:value-of select="$FieldName"/>-&gt;getData(), </xsl:when>
<xsl:when test="@dbtype='Integer'">q<xsl:value-of select="$FieldName"/>-&gt;getData(), </xsl:when>
<xsl:when test="@dbtype='String'">q<xsl:value-of select="$FieldName"/>-&gt;charrep(), </xsl:when>
</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each> qID-&gt;getData());

		while (((err = q-&gt;next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/><xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">
			q<xsl:value-of select="$FieldName"/> = q-&gt;getAsLong(<xsl:value-of select="position()"/>);</xsl:when>
<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']"></xsl:when>
<xsl:otherwise><xsl:choose>
<xsl:when test="@dbtype='Bit'">
			UAP(lb_I_String, b<xsl:value-of select="$FieldName"/>)
			b<xsl:value-of select="$FieldName"/> = q-&gt;getAsString(<xsl:value-of select="position()"/>);
			if (*b<xsl:value-of select="$FieldName"/> == "true")
				q<xsl:value-of select="$FieldName"/>-&gt;setData(true);
			else
				q<xsl:value-of select="$FieldName"/>-&gt;setData(false);</xsl:when>
<xsl:when test="@dbtype='Float'">
			q<xsl:value-of select="$FieldName"/> = q-&gt;getAsString(<xsl:value-of select="position()"/>);</xsl:when>
<xsl:when test="@dbtype='Integer'">
			q<xsl:value-of select="$FieldName"/> = q-&gt;getAsLong(<xsl:value-of select="position()"/>);</xsl:when>
<xsl:when test="@dbtype='String'">
			q<xsl:value-of select="$FieldName"/> = q-&gt;getAsString(<xsl:value-of select="position()"/>);</xsl:when>
</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
<xsl:if test="position()=last()">
			qID = q-&gt;getAsLong(<xsl:value-of select="position()+1"/>
</xsl:if>
</xsl:for-each>);

			owningObject-&gt;add<xsl:value-of select="$FormName"/>(<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]"><xsl:variable name="FieldName" select="@name"/><xsl:variable name="TableName" select="@tablename"/>
<xsl:choose><xsl:when test="@isfk='1'">q<xsl:value-of select="$FieldName"/>-&gt;getData(), </xsl:when>
<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']"></xsl:when>
<xsl:otherwise><xsl:choose>
<xsl:when test="@dbtype='Bit'">q<xsl:value-of select="$FieldName"/>-&gt;charrep(), </xsl:when>
<xsl:when test="@dbtype='Float'">q<xsl:value-of select="$FieldName"/>-&gt;charrep(), </xsl:when>
<xsl:when test="@dbtype='Integer'">q<xsl:value-of select="$FieldName"/>-&gt;getData(), </xsl:when>
<xsl:when test="@dbtype='String'">q<xsl:value-of select="$FieldName"/>-&gt;charrep(), </xsl:when>
</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each> qID-&gt;getData());
		}
	}
}



class lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension : public lb_I_PluginImpl {
public:
	lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension();
	
	virtual ~lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, uk<xsl:value-of select="$FormName"/>ModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension, lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension)

lbErrCodes LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension::lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension() {
	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension::lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension() called.\n" LOG_
}

lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension::~lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension() {
	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension::~lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (uk<xsl:value-of select="$FormName"/>ModelExtension == NULL) {
		<xsl:value-of select="$FormName"/>DBReaderExtension* <xsl:value-of select="$FormName"/>ModelExtension = new <xsl:value-of select="$FormName"/>DBReaderExtension();
		
	
		QI(<xsl:value-of select="$FormName"/>ModelExtension, lb_I_Unknown, uk<xsl:value-of select="$FormName"/>ModelExtension)
	} else {
		_CL_VERBOSE &lt;&lt; "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return uk<xsl:value-of select="$FormName"/>ModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (uk<xsl:value-of select="$FormName"/>ModelExtension == NULL) {

		_CL_VERBOSE &lt;&lt; "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		<xsl:value-of select="$FormName"/>DBReaderExtension* <xsl:value-of select="$FormName"/>ModelExtension = new <xsl:value-of select="$FormName"/>DBReaderExtension();
		
	
		QI(<xsl:value-of select="$FormName"/>ModelExtension, lb_I_Unknown, uk<xsl:value-of select="$FormName"/>ModelExtension)
	}
	
	lb_I_Unknown* r = uk<xsl:value-of select="$FormName"/>ModelExtension.getPtr();
	uk<xsl:value-of select="$FormName"/>ModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPlugin<xsl:value-of select="$FormName"/>DBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (uk<xsl:value-of select="$FormName"/>ModelExtension != NULL) {
                uk<xsl:value-of select="$FormName"/>ModelExtension--;
                uk<xsl:value-of select="$FormName"/>ModelExtension.resetPtr();
        }
}
</xsl:template>
</xsl:stylesheet>

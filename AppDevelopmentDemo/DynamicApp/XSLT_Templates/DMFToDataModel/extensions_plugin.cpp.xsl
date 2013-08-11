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

<xsl:template name="extensions_plugin.cpp">
	<xsl:param name="ApplicationID"/>
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
/*...sincludes:0:*/
#ifdef LBDMF_PREC
#include &lt;lbConfigHook.h&gt;
#endif

#ifdef WINDOWS
#include &lt;windows.h&gt;
#include &lt;io.h&gt;
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#include &lt;conio.h&gt;

#ifdef __WATCOMC__
#include &lt;ctype.h&gt;
#endif
#ifdef __cplusplus
}
#endif

#include &lt;stdio.h&gt;
#ifndef OSX
#include &lt;malloc.h&gt;
#endif
#ifdef OSX
#include &lt;sys/malloc.h&gt;
#endif

#ifndef LBDMF_PREC
#include &lt;lbConfigHook.h&gt;
#endif

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include &lt;lbdmfdatamodel-module.h&gt;
/*...e*/

/*...e*/

/*...sclass lbPluginModulelbDMFDataModelExtensions:0:*/
class lbPluginModulelbDMFDataModelExtensions : public lb_I_PluginModule {
public:

	lbPluginModulelbDMFDataModelExtensions();
	virtual ~lbPluginModulelbDMFDataModelExtensions();

	DECLARE_LB_UNKNOWN()
	
	void LB_STDCALL initialize();
	void LB_STDCALL install();
	
	DECLARE_PLUGINS()
};
/*...e*/

/*...sclass lbPluginModulelbDMFDataModelExtensions implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModulelbDMFDataModelExtensions)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModulelbDMFDataModelExtensions)

BEGIN_PLUGINS(lbPluginModulelbDMFDataModelExtensions)
// Generated plugin definitions<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularName" select="@name"/>
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
	ADD_PLUGIN(lbPlugin<xsl:value-of select="$FormularName"/>InternalFormatReaderExtension, InputStreamVisitor_<xsl:value-of select="$FormularName"/>Model)
	ADD_PLUGIN(lbPlugin<xsl:value-of select="$FormularName"/>DBReaderExtension, DatabaseInputStreamVisitor_<xsl:value-of select="$FormularName"/>Model)
	ADD_PLUGIN(lbPlugin<xsl:value-of select="$FormularName"/>InternalFormatWriterExtension, OutputStreamVisitor_<xsl:value-of select="$FormularName"/>Model)
	ADD_PLUGIN(lbPlugin<xsl:value-of select="$FormularName"/>XMLWriterExtension, XMLOutputStreamVisitor_<xsl:value-of select="$FormularName"/>Model)
</xsl:for-each>	
END_PLUGINS()

lbPluginModulelbDMFDataModelExtensions::lbPluginModulelbDMFDataModelExtensions() {
	_CL_VERBOSE &lt;&lt; "lbPluginModulelbDMFDataModelExtensions::lbPluginModulelbDMFDataModelExtensions() called." LOG_
}

lbPluginModulelbDMFDataModelExtensions::~lbPluginModulelbDMFDataModelExtensions() {
	_CL_VERBOSE &lt;&lt; "lbPluginModulelbDMFDataModelExtensions::~lbPluginModulelbDMFDataModelExtensions() called." LOG_
}

void LB_STDCALL lbPluginModulelbDMFDataModelExtensions::initialize() {
	char ptr[20] = "";
	sprintf(ptr, "%p", this);
	
	enumPlugins();
}

void LB_STDCALL lbPluginModulelbDMFDataModelExtensions::install() {

}

lbErrCodes LB_STDCALL lbPluginModulelbDMFDataModelExtensions::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE &lt;&lt; "lbPluginModulelbDMFDataModelExtensions::setData(...) not implemented yet" LOG_

	if (uk != NULL) {
		_CL_VERBOSE &lt;&lt; "Cloning object with " &lt;&lt; uk-&gt;getRefCount() &lt;&lt; " references." LOG_
	}
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
</xsl:template>
</xsl:stylesheet>
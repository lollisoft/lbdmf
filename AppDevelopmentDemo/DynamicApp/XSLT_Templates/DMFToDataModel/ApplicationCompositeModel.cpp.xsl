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

<xsl:template name="ApplicationCompositeModel.cpp">
	<xsl:param name="ApplicationID"/>/*...sLicence:0:*/
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

#include &lt;lbInterfaces-sub-security.h&gt;
#include &lt;lbInterfaces-lbDMFManager.h&gt;
#include &lt;ApplicationCompositeModel.h&gt;

// Includes for the libxml / libxslt libraries

#include &lt;libxml/xmlmemory.h&gt;
#include &lt;libxml/debugXML.h&gt;
#include &lt;libxml/HTMLtree.h&gt;
#include &lt;libxml/xmlIO.h&gt;
#include &lt;libxml/DOCBparser.h&gt;
#include &lt;libxml/xinclude.h&gt;
#include &lt;libxml/catalog.h&gt;
#include &lt;libxslt/xslt.h&gt;
#include &lt;libxslt/xsltInternals.h&gt;
#include &lt;libxslt/transform.h&gt;
#include &lt;libxslt/xsltutils.h&gt;

#ifndef __WATCOMC_ 
extern int xmlLoadExtDtdDefaultValue;
#endif
#ifdef __WATCOMC__

// Map the orginal API functions to my versions as exported under Windows

#define xsltSaveResultToString lb_xsltSaveResultToString
#define xsltParseStylesheetDoc lb_xsltParseStylesheetDoc
#define xsltApplyStylesheet lb_xsltApplyStylesheet
#define xsltFreeStylesheet lb_xsltFreeStylesheet
#define xmlSubstituteEntitiesDefault lb_xmlSubstituteEntitiesDefault
#define xmlFreeDoc lb_xmlFreeDoc
#define xsltCleanupGlobals lb_xsltCleanupGlobals
#define xmlCleanupParser lb_xmlCleanupParser
#define xmlReadMemory lb_xmlReadMemory
#endif


IMPLEMENT_FUNCTOR(instanceOflbDynamicAppXMLStorage, lbDynamicAppXMLStorage)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicAppXMLStorage)
	ADD_INTERFACE(lb_I_StandaloneStreamable)
END_IMPLEMENT_LB_UNKNOWN()


lbDynamicAppXMLStorage::lbDynamicAppXMLStorage() {
	

	_CL_LOG &lt;&lt; "lbDynamicAppStorage::lbDynamicAppStorage() called." LOG_
}

lbDynamicAppXMLStorage::~lbDynamicAppXMLStorage() {
	_CL_LOG &lt;&lt; "lbDynamicAppStorage::~lbDynamicAppStorage() called." LOG_
}

lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::setData(lb_I_Unknown*) {
		_CL_VERBOSE &lt;&lt; "Error: lbDynamicAppStorage::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}


lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::load(lb_I_InputStream* iStream) {
	lbErrCodes err = ERR_NONE;


	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::save(lb_I_OutputStream* oStream) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_Aspect, aspect)
	QI(op, lb_I_Aspect, aspect)

	UAP(lb_I_Unknown, uk)

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM" select="@name"/>
<xsl:variable name="FormularNameACM">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM"/>
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
	UAP(lb_I_<xsl:value-of select="$FormularNameACM"/>, <xsl:value-of select="$FormularNameACM"/>)
</xsl:for-each>

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	UAP_REQUEST(getModuleInstance(), lb_I_String, param)
	UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
	UAP(lb_I_Unknown, ukParams)
	
	UAP(lb_I_Parameter, params)

	ukParams = meta-&gt;getActiveDocument();
	QI(ukParams, lb_I_Parameter, params)

	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, activedocument)
	ukDoc = meta-&gt;getActiveDocument();
	QI(ukDoc, lb_I_Parameter, activedocument)
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBPass)

	UAP_REQUEST(getModuleInstance(), lb_I_String, overwrite)
	UAP_REQUEST(getModuleInstance(), lb_I_String, writeXMISettings)

	
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileExportSettings)

	if (activedocument != NULL) {
		*param = "XSLFileExportSettings";
		activedocument-&gt;getUAPFileLocation(*&amp;param, *&amp;XSLFileExportSettings);
/*
		*param = "XSLFileSystemDatabase";
		activedocument-&gt;getUAPFileLocation(*&amp;param, *&amp;XSLFileSystemDatabase);
		*param = "XSLFileApplicationDatabase";
		activedocument-&gt;getUAPFileLocation(*&amp;param, *&amp;XSLFileApplicationDatabase);
 
		_LOG &lt;&lt; "Have got the following files: " &lt;&lt; XSLFileSystemDatabase-&gt;charrep() &lt;&lt; " and " &lt;&lt; XSLFileApplicationDatabase-&gt;charrep() LOG_		
 */
		*param = "UMLImportDBName";
		activedocument-&gt;getUAPString(*&amp;param, *&amp;DBName);
		*param = "UMLImportDBUser";
		activedocument-&gt;getUAPString(*&amp;param, *&amp;DBUser);
		*param = "UMLImportDBPass";
		activedocument-&gt;getUAPString(*&amp;param, *&amp;DBPass);

		*param = "overwriteDatabase";
		activedocument-&gt;getUAPString(*&amp;param, *&amp;overwrite);
		if (overwrite-&gt;charrep() == NULL) {
			_LOG &lt;&lt; "Warning: The overwriteDatabase parameter was not passed. Set it to no." LOG_
			*overwrite = "no";
		}
		
		*param = "writeXMISettings";
		activedocument-&gt;getUAPString(*&amp;param, *&amp;writeXMISettings);
		if (writeXMISettings-&gt;charrep() == NULL) {
			_LOG &lt;&lt; "Warning: The writeXMISettings parameter was not passed. Set it to no." LOG_
			*writeXMISettings = "no";
		}
	}
	
	// Write the settings file for the application database here ...
	// If I import to a MS SQL server, then I need other settings. Always writing the 'wrong' default settings is not correct.
	if (*writeXMISettings == "yes") {
		if (XSLFileExportSettings-&gt;charrep() != NULL) {
			if (strcmp(XSLFileExportSettings-&gt;charrep(), "&lt;settings&gt;") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)
				
				oStream-&gt;setFileName(XSLFileExportSettings-&gt;charrep());
				if (oStream-&gt;open()) {
					oStream-&gt;setBinary();
					*oStream &lt;&lt; "&lt;xsl:stylesheet version=\"1.1\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\" xmlns:exsl=\"http://exslt.org/common\" extension-element-prefixes=\"exsl\"&gt;\n";
					*oStream &lt;&lt; "&lt;!--&lt;xsl:variable name=\"targetdatabase\" select=\"' '\"/&gt;--&gt;&lt;!-- Mapped to DefaultDatabaseSystem as in XSLT document defined. --&gt;\n";
					*oStream &lt;&lt; "&lt;!--&lt;xsl:variable name=\"targetdatabase\" select=\"'DatabaseLayerGateway'\"/&gt;--&gt;&lt;!-- Mapped to Sqlite (in XSLT document) --&gt;\n";
					*oStream &lt;&lt; "&lt;!--&lt;xsl:variable name=\"targetdatabase\" select=\"'MSSQL'\"/&gt;--&gt;\n";
					*oStream &lt;&lt; "&lt;!--&lt;xsl:variable name=\"targetdatabase\" select=\"'PostgreSQL'\"/&gt;--&gt;\n";
					*oStream &lt;&lt; "&lt;xsl:variable name=\"targetdatabase\" select=\"'" &lt;&lt; meta-&gt;getApplicationDatabaseBackend() &lt;&lt; "'\"/&gt;&lt;!-- Mapped from Application Database backend in the properties window group General --&gt;\n";
					*oStream &lt;&lt; "&lt;xsl:variable name=\"execute_droprules\" select=\"'" &lt;&lt; overwrite-&gt;charrep() &lt;&lt; "'\"/&gt;\n";
					*oStream &lt;&lt; "&lt;xsl:variable name=\"stream_output\" select=\"'no'\"/&gt;\n"; // Writing out to uml would overwrite this here, because first this output must be created.
					
					DBName-&gt;replace("&gt;", "&amp;gt;");
					DBName-&gt;replace("&lt;", "&amp;lt;");
					DBUser-&gt;replace("&gt;", "&amp;gt;");
					DBUser-&gt;replace("&lt;", "&amp;lt;");
					DBPass-&gt;replace("&gt;", "&amp;gt;");
					DBPass-&gt;replace("&lt;", "&amp;lt;");
					
					*oStream &lt;&lt; "&lt;xsl:variable name=\"database_name\" select=\"'" &lt;&lt; DBName-&gt;charrep() &lt;&lt; "'\"/&gt;\n";
					*oStream &lt;&lt; "&lt;xsl:variable name=\"database_user\" select=\"'" &lt;&lt; DBUser-&gt;charrep() &lt;&lt; "'\"/&gt;\n";
					*oStream &lt;&lt; "&lt;xsl:variable name=\"database_pass\" select=\"'" &lt;&lt; DBPass-&gt;charrep() &lt;&lt; "'\"/&gt;\n";
					
					/// \todo Write additional XMI settings here.				
					
					
					*oStream &lt;&lt; "&lt;/xsl:stylesheet&gt;\n";
					oStream-&gt;close();
				}
			}
		}
	}
	
	*param = "ApplicationData";
	document-&gt;setCloning(false);
	params-&gt;getUAPContainer(*&amp;param, *&amp;document);	

	// Get the application ID, that would be stored inside the XML document
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, AppID)
	*param = "SaveApplicationID";
	params-&gt;getUAPInteger(*&amp;param, *&amp;AppID);
	
	_LOG &lt;&lt; "Application ID, that would be stored inside the XML document: " &lt;&lt; AppID-&gt;charrep() LOG_

	UAP_REQUEST(getModuleInstance(), lb_I_String, name)

	UAP(lb_I_KeyBase, key)
	QI(name, lb_I_KeyBase, key)

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM1" select="@name"/>
<xsl:variable name="FormularNameACM1">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM1"/>
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
	*name = "<xsl:value-of select="$FormularNameACM1"/>";
	uk = document-&gt;getElement(&amp;key);
	QI(uk, lb_I_<xsl:value-of select="$FormularNameACM1"/>, <xsl:value-of select="$FormularNameACM1"/>)
</xsl:for-each>

	// Mark that data sets, that are related to this application
	UAP(lb_I_SecurityProvider, securityManager)
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	AQUIRE_PLUGIN(lb_I_SecurityProvider, Default, securityManager, "No security provider found.")
	UAP(lb_I_Unknown, apps)
	apps = securityManager-&gt;getApplicationModel();
	QI(apps, lb_I_Applications, Applications)
	
	meta-&gt;setStatusText("Info", "Write XML document ...");
	
	Applications-&gt;selectById(AppID-&gt;getData());
	Applications-&gt;mark();

	if (
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM2" select="@name"/>
<xsl:variable name="FormularNameACM2">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM2"/>
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
		(<xsl:value-of select="$FormularNameACM2"/> != NULL) &amp;&amp;
</xsl:for-each>
	    true) {

	
		*oStream &lt;&lt; "&lt;lbDMF applicationid=\"";

		// Save currently used database backend information. It could be used to determine what to to in the XSLT templates.
		// If exported, the information may be changed.
		
		char* dbbackend = meta-&gt;getSystemDatabaseBackend();

		*oStream &lt;&lt; AppID-&gt;charrep() &lt;&lt; "\" backend=\"" &lt;&lt; dbbackend &lt;&lt; 
#ifdef OSX		
		"\" platform=\"osx\"&gt;\n";
#else
#ifdef LINUX		
		"\" platform=\"linux\"&gt;\n";
#else		
#ifdef WINDOWS		
		"\" platform=\"windows\"&gt;\n";
#else		
#ifdef SOLARIS		
		"\" platform=\"solaris\"&gt;\n";
#endif		
#endif		
#endif		
#endif

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM3" select="@name"/>
<xsl:variable name="FormularNameACM3">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM3"/>
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
		meta-&gt;setStatusText("Info", "Write XML document (<xsl:value-of select="$FormularNameACM3"/>) ...");
		<xsl:value-of select="$FormularNameACM3"/>-&gt;accept(*&amp;aspect);
</xsl:for-each>

		*oStream &lt;&lt; "&lt;/lbDMF&gt;\n";
	}
	_LOG &lt;&lt; "lbDynamicAppXMLStorage::save(lb_I_OutputStream* oStream) returns" LOG_

	meta-&gt;setStatusText("Info", "Done writing XML document ...");
	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::load(lb_I_Database* iDB) {
	lbErrCodes err = ERR_NONE;

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::save(lb_I_Database* oDB) {
	lbErrCodes err = ERR_NONE;

	return err;
}

IMPLEMENT_FUNCTOR(instanceOflbDynamicAppInternalStorage, lbDynamicAppInternalStorage)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicAppInternalStorage)
	ADD_INTERFACE(lb_I_StandaloneStreamable)
END_IMPLEMENT_LB_UNKNOWN()


lbDynamicAppInternalStorage::lbDynamicAppInternalStorage() {
	

	_CL_LOG &lt;&lt; "lbDynamicAppInternalStorage::lbDynamicAppInternalStorage() called." LOG_
}

lbDynamicAppInternalStorage::~lbDynamicAppInternalStorage() {
	_CL_LOG &lt;&lt; "lbDynamicAppInternalStorage::~lbDynamicAppInternalStorage() called." LOG_
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::setData(lb_I_Unknown*) {
		_CL_VERBOSE &lt;&lt; "Error: lbDynamicAppInternalStorage::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}


lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::load(lb_I_InputStream* iStream) {
	lbErrCodes err = ERR_NONE;
	_LOG &lt;&lt; "lbDynamicAppInternalStorage::load(lb_I_InputStream*) called." LOG_
	UAP(lb_I_Aspect, aspect)
	QI(op, lb_I_Aspect, aspect)
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

	if (aspect == NULL) {
	    _LOG &lt;&lt; "Error: aspect instance not available." LOG_
	}

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM4" select="@name"/>
<xsl:variable name="FormularNameACM4">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM4"/>
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
	UAP(lb_I_<xsl:value-of select="$FormularNameACM4"/>, <xsl:value-of select="$FormularNameACM4"/>)
</xsl:for-each>

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM5" select="@name"/>
<xsl:variable name="FormularNameACM5">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM5"/>
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
	AQUIRE_PLUGIN(lb_I_<xsl:value-of select="$FormularNameACM5"/>, Model, <xsl:value-of select="$FormularNameACM5"/>, "'<xsl:value-of select="$FormularNameACM5"/>'")
</xsl:for-each>

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM6" select="@name"/>
<xsl:variable name="FormularNameACM6">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM6"/>
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
	<xsl:value-of select="$FormularNameACM6"/>-&gt;accept(*&amp;aspect);
</xsl:for-each>

	// Read out application settings
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBPass)

	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XMIFileUMLProject)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XMIFileUMLProjectExport)

	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileImportSettings)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileExportSettings)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileUMLExport)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileSystemDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileApplicationDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DatabaseSettingNamespace)
	UAP_REQUEST(getModuleInstance(), lb_I_String, GeneralDBSchemaname)

	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, UsePlugin)
	//UAP_REQUEST(getModuleInstance(), lb_I_Boolean, UseOtherXSLFile)

	UMLImportTargetDBName-&gt;accept(*&amp;aspect);
	UMLImportTargetDBUser-&gt;accept(*&amp;aspect);
	UMLImportTargetDBPass-&gt;accept(*&amp;aspect);

	DatabaseSettingNamespace-&gt;accept(*&amp;aspect);
	UsePlugin-&gt;accept(*&amp;aspect);	
	XSLFileSystemDatabase-&gt;accept(*&amp;aspect);
	XSLFileApplicationDatabase-&gt;accept(*&amp;aspect);
	//UseOtherXSLFile-&gt;accept(*&amp;aspect);
	XMIFileUMLProject-&gt;accept(*&amp;aspect);
	XMIFileUMLProjectExport-&gt;accept(*&amp;aspect);

	GeneralDBSchemaname-&gt;accept(*&amp;aspect);
	XSLFileUMLExport-&gt;accept(*&amp;aspect);
	XSLFileImportSettings-&gt;accept(*&amp;aspect);
	XSLFileExportSettings-&gt;accept(*&amp;aspect);
	
	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_KeyBase, key)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)
	UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	QI(name, lb_I_KeyBase, key)

	param-&gt;setCloning(false);
	document-&gt;setCloning(false);

	if (
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM7" select="@name"/>
<xsl:variable name="FormularNameACM7">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM7"/>
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
		(<xsl:value-of select="$FormularNameACM7"/> != NULL) &amp;&amp; 
</xsl:for-each>
		true) {
		
		UAP(lb_I_Unknown, uk)
		
		metaapp-&gt;setStatusText("Info", "Load internal file format ...");
		
		_LOG &lt;&lt; "Get active document" LOG_
		

		UAP(lb_I_Unknown, ukParams)
		UAP(lb_I_Parameter, params)

		ukParams = metaapp-&gt;getActiveDocument();
		QI(ukParams, lb_I_Parameter, params)
		
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM8" select="@name"/>
<xsl:variable name="FormularNameACM8">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM8"/>
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
		*name = "<xsl:value-of select="$FormularNameACM8"/>";
		QI(<xsl:value-of select="$FormularNameACM8"/>, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);
</xsl:for-each>

		*name = "UMLImportTargetDBName";
		QI(UMLImportTargetDBName, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);
		
		*name = "UMLImportTargetDBUser";
		QI(UMLImportTargetDBUser, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);
		
		*name = "UMLImportTargetDBPass";
		QI(UMLImportTargetDBPass, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);
		
		*name = "DatabaseSettingNamespace";
		QI(DatabaseSettingNamespace, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);
		
		*name = "UsePlugin";
		QI(UsePlugin, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);
		
		*name = "XSLFileSystemDatabase";
		QI(XSLFileSystemDatabase, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);
		
		*name = "XSLFileApplicationDatabase";
		QI(XSLFileApplicationDatabase, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);
		
		*name = "XMIFileUMLProject";
		QI(XMIFileUMLProject, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);
		
		*name = "XMIFileUMLProjectExport";
		QI(XMIFileUMLProjectExport, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);

		*name = "GeneralDBSchemaname";
		QI(GeneralDBSchemaname, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);
		
		*name = "XSLFileUMLExport";
		QI(XSLFileUMLExport, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);
		
		*name = "XSLFileImportSettings";
		QI(XSLFileImportSettings, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);
		
		*name = "XSLFileExportSettings";
		QI(XSLFileExportSettings, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);
	}		
	
	*name = "ApplicationData";
	param-&gt;setUAPContainer(*&amp;name, *&amp;document);
	
	param++;
	metaapp-&gt;setActiveDocument(*&amp;param);
	
	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::save(lb_I_OutputStream* oStream) {
	lbErrCodes err = ERR_NONE;

	_LOG &lt;&lt; "lbDynamicAppInternalStorage::save(lb_I_OutputStream*) called." LOG_

	UAP(lb_I_Aspect, aspect)
	QI(op, lb_I_Aspect, aspect)

	UAP(lb_I_Unknown, uk)

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM9" select="@name"/>
<xsl:variable name="FormularNameACM9">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM9"/>
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
	UAP(lb_I_<xsl:value-of select="$FormularNameACM9"/>, <xsl:value-of select="$FormularNameACM9"/>)
</xsl:for-each>

	// Save application settings
	UAP(lb_I_String, UMLImportTargetDBName)
	UAP(lb_I_String, UMLImportTargetDBUser)
	UAP(lb_I_String, UMLImportTargetDBPass)
	UAP(lb_I_String, GeneralDBSchemaname)

	UAP(lb_I_FileLocation, XMIFileUMLProject)
	UAP(lb_I_FileLocation, XMIFileUMLProjectExport)
	UAP(lb_I_FileLocation, XSLFileImportSettings)
	UAP(lb_I_FileLocation, XSLFileExportSettings)
	UAP(lb_I_FileLocation, XSLFileUMLExport)
	UAP(lb_I_FileLocation, XSLFileSystemDatabase)
	UAP(lb_I_FileLocation, XSLFileApplicationDatabase)
	UAP(lb_I_String, DatabaseSettingNamespace)

	UAP(lb_I_Boolean, UsePlugin)
	//UAP(lb_I_Boolean, UseOtherXSLFile)


	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	UAP_REQUEST(getModuleInstance(), lb_I_String, param)
	
	meta-&gt;setStatusText("Info", "Store internal file format ...");
	
	_LOG &lt;&lt; "Get active document" LOG_
	
	UAP(lb_I_Unknown, ukDoc)
	UAP_REQUEST(getModuleInstance(), lb_I_Container, document)

	UAP(lb_I_Unknown, ukParams)
	UAP(lb_I_Parameter, params)

	ukParams = meta-&gt;getActiveDocument();
	QI(ukParams, lb_I_Parameter, params)

	_LOG &lt;&lt; "Retrieve document container with name 'ApplicationData'" LOG_

	*param = "ApplicationData";
	document-&gt;setCloning(false);
	params-&gt;getUAPContainer(*&amp;param, *&amp;document);	

	UAP_REQUEST(getModuleInstance(), lb_I_String, name)

	UAP(lb_I_KeyBase, key)
	QI(name, lb_I_KeyBase, key)
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM10" select="@name"/>
<xsl:variable name="FormularNameACM10">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM10"/>
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
	*name = "<xsl:value-of select="$FormularNameACM10"/>";
	uk = document-&gt;getElement(&amp;key);
	if (uk != NULL) {
		QI(uk, lb_I_<xsl:value-of select="$FormularNameACM10"/>, <xsl:value-of select="$FormularNameACM10"/>)
	} else {
		AQUIRE_PLUGIN(lb_I_<xsl:value-of select="$FormularNameACM10"/>, Model, <xsl:value-of select="$FormularNameACM10"/>, "'<xsl:value-of select="$FormularNameACM10"/>'")
	}
</xsl:for-each>

	// Store the settings from dynamic application
	*name = "UMLImportTargetDBName";
	uk = document-&gt;getElement(&amp;key);
	QI(uk, lb_I_String, UMLImportTargetDBName)
			
	*name = "UMLImportTargetDBUser";
	uk = document-&gt;getElement(&amp;key);
	QI(uk, lb_I_String, UMLImportTargetDBUser)
			
	*name = "UMLImportTargetDBPass";
	uk = document-&gt;getElement(&amp;key);
	QI(uk, lb_I_String, UMLImportTargetDBPass)
			
	*name = "XSLFileSystemDatabase";
	uk = document-&gt;getElement(&amp;key);
	QI(uk, lb_I_FileLocation, XSLFileSystemDatabase)
			
	*name = "XSLFileApplicationDatabase";
	uk = document-&gt;getElement(&amp;key);
	QI(uk, lb_I_FileLocation, XSLFileApplicationDatabase)
			
	*name = "DatabaseSettingNamespace";
	uk = document-&gt;getElement(&amp;key);
	QI(uk, lb_I_String, DatabaseSettingNamespace)

	*name = "UsePlugin";
	uk = document-&gt;getElement(&amp;key);
	QI(uk, lb_I_Boolean, UsePlugin)

	*name = "XMIFileUMLProject";
	uk = document-&gt;getElement(&amp;key);
	QI(uk, lb_I_FileLocation, XMIFileUMLProject)
	
	*name = "XMIFileUMLProjectExport";
	uk = document-&gt;getElement(&amp;key);
	QI(uk, lb_I_FileLocation, XMIFileUMLProjectExport)
	
	*name = "GeneralDBSchemaname";
	uk = document-&gt;getElement(&amp;key);
	QI(uk, lb_I_String, GeneralDBSchemaname)
	
	*name = "XSLFileUMLExport";
	uk = document-&gt;getElement(&amp;key);
	QI(uk, lb_I_FileLocation, XSLFileUMLExport)
	
	*name = "XSLFileImportSettings";
	uk = document-&gt;getElement(&amp;key);
	QI(uk, lb_I_FileLocation, XSLFileImportSettings)
	
	*name = "XSLFileExportSettings";
	uk = document-&gt;getElement(&amp;key);
	QI(uk, lb_I_FileLocation, XSLFileExportSettings)
	
				

	if (
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM11" select="@name"/>
<xsl:variable name="FormularNameACM11">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM11"/>
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
		(<xsl:value-of select="$FormularNameACM11"/> != NULL) &amp;&amp;
</xsl:for-each>
		true) {

		_LOG &lt;&lt; "Start storing the data" LOG_

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM12" select="@name"/>
<xsl:variable name="FormularNameACM12">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM12"/>
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
		<xsl:value-of select="$FormularNameACM12"/>-&gt;accept(*&amp;aspect);
</xsl:for-each>

		UMLImportTargetDBName-&gt;accept(*&amp;aspect);
		UMLImportTargetDBUser-&gt;accept(*&amp;aspect);
		UMLImportTargetDBPass-&gt;accept(*&amp;aspect);

		DatabaseSettingNamespace-&gt;accept(*&amp;aspect);
		UsePlugin-&gt;accept(*&amp;aspect);
		XSLFileSystemDatabase-&gt;accept(*&amp;aspect);
		XSLFileApplicationDatabase-&gt;accept(*&amp;aspect);
		//UseOtherXSLFile-&gt;accept(*&amp;aspect);
		XMIFileUMLProject-&gt;accept(*&amp;aspect);
		XMIFileUMLProjectExport-&gt;accept(*&amp;aspect);
		GeneralDBSchemaname-&gt;accept(*&amp;aspect);
		XSLFileUMLExport-&gt;accept(*&amp;aspect);
		XSLFileImportSettings-&gt;accept(*&amp;aspect);
		XSLFileExportSettings-&gt;accept(*&amp;aspect);
		
		_LOG &lt;&lt; "End storing the data" LOG_
	}

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::load(lb_I_Database* iDB) {
	_LOG &lt;&lt; "lbDynamicAppInternalStorage::load(lb_I_Database*) called." LOG_
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Aspect, aspect)
	QI(op, lb_I_Aspect, aspect)

	if (aspect == NULL) {
	    _LOG &lt;&lt; "Error: aspect instance not available." LOG_
	}


	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)


<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM13" select="@name"/>
<xsl:variable name="FormularNameACM13">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM13"/>
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
	UAP(lb_I_<xsl:value-of select="$FormularNameACM13"/>, <xsl:value-of select="$FormularNameACM13"/>)
</xsl:for-each>

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM14" select="@name"/>
<xsl:variable name="FormularNameACM14">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM14"/>
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
	AQUIRE_PLUGIN(lb_I_<xsl:value-of select="$FormularNameACM14"/>, Model, <xsl:value-of select="$FormularNameACM14"/>, "'<xsl:value-of select="$FormularNameACM14"/>'")
</xsl:for-each>
	
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM15" select="@name"/>
<xsl:variable name="FormularNameACM15">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM15"/>
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
	if (<xsl:value-of select="$FormularNameACM15"/> == NULL)  {
		_LOG &lt;&lt; "lb_I_<xsl:value-of select="$FormularNameACM15"/> instance is NULL." LOG_
	}
</xsl:for-each>

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM16" select="@name"/>
<xsl:variable name="FormularNameACM16">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM16"/>
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
	meta-&gt;setStatusText("Info", "Load database configuration (<xsl:value-of select="$FormularNameACM16"/>) ...");
	<xsl:value-of select="$FormularNameACM16"/>-&gt;accept(*&amp;aspect);
</xsl:for-each>

	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Unknown, ukDoc)
	UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
	UAP(lb_I_Unknown, ukParams)
	UAP(lb_I_Parameter, params)

	ukParams = meta-&gt;getActiveDocument();
	QI(ukParams, lb_I_Parameter, params)

	_LOG &lt;&lt; "Retrieve document container with name 'ApplicationData'" LOG_

	*name = "ApplicationData";
	params-&gt;setCloning(false);
	document-&gt;setCloning(false);


	// Need to read the new application settings from a good place
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBPass)

	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XMIFileUMLProject)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XMIFileUMLProjectExport)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileUMLExport)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileImportSettings)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileExportSettings)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileSystemDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileApplicationDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DatabaseSettingNamespace)
	UAP_REQUEST(getModuleInstance(), lb_I_String, GeneralDBSchemaname)

	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, UsePlugin)
	//UAP_REQUEST(getModuleInstance(), lb_I_Boolean, UseOtherXSLFile)

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	QI(name, lb_I_KeyBase, key)

	UAP(lb_I_Parameter, SomeBaseSettings)
	
	SomeBaseSettings = meta-&gt;getPropertySet("DynamicAppDefaultSettings");

	if (SomeBaseSettings == NULL || SomeBaseSettings-&gt;Count() == 0) {
		// Firstly let them empty
		_LOG &lt;&lt; "Initialize the dynamic app import settings..." LOG_
		*UMLImportTargetDBName = "CRM";
		*UMLImportTargetDBUser = "&lt;dbuser&gt;";
		*UMLImportTargetDBPass = "&lt;dbpass&gt;";
		*GeneralDBSchemaname = "public";

		*DatabaseSettingNamespace = "DatabaseLayerGateway"; // When used, I can support this one yet. But not fully tested.
		XMIFileUMLProject-&gt;setData("");

		UsePlugin-&gt;setData(false);
		//UseOtherXSLFile-&gt;setData(true);

#ifdef WINDOWS
		///\todo Change the used files to refer the HOME versions.
		//installXMIFilesToHome();
		//installXSLFilesToHome();
        XMIFileUMLProject-&gt;setData("c:\\lbDMF\\UMLSamples\\SecondStageModels\\lbDMF Manager.xmi");
        XMIFileUMLProjectExport-&gt;setData("c:\\lbDMF\\UMLSamples\\SecondStageModels\\Export.xmi");
		XSLFileUMLExport-&gt;setData("c:\\lbDMF\\XSLT\\DMFToXMI\\gen_DMFToXMI.xsl");
        XSLFileImportSettings-&gt;setData("c:\\lbDMF\\XSLT\\XMIToDMF\\XMISettings.xsl");
        XSLFileExportSettings-&gt;setData("c:\\lbDMF\\XSLT\\DMFToXMI\\XMISettings.xsl");
        XSLFileSystemDatabase-&gt;setData("c:\\lbDMF\\XSLT\\XMIToDMF\\ImportUML-SystemDB.xsl");
        XSLFileApplicationDatabase-&gt;setData("c:\\lbDMF\\XSLT\\XMIToDMF\\ImportUML-ApplicationDB.xsl");
#endif
#ifdef LINUX
#ifndef OSX
		///\todo Change the used files to refer the HOME versions.
		//installXMIFilesToHome();
		//installXSLFilesToHome();
        XMIFileUMLProject-&gt;setData("/usr/share/lbdmf/UMLSamples/SecondStageModels/lbDMFManager.xmi");
        XMIFileUMLProjectExport-&gt;setData("/usr/share/lbdmf/UMLSamples/SecondStageModels/Export.xmi");
	XSLFileUMLExport-&gt;setData("/usr/share/lbdmf/DMFToXMI/gen_DMFToXMI.xsl");
        XSLFileImportSettings-&gt;setData("/usr/share/lbdmf/XMIToDMF/XMISettings.xsl");
        XSLFileExportSettings-&gt;setData("/usr/share/lbdmf/DMFToXMI/XMISettings.xsl");
        XSLFileSystemDatabase-&gt;setData("/usr/share/lbdmf/XMIToDMF/importUML-SystemDB.xsl");
        XSLFileApplicationDatabase-&gt;setData("/usr/share/lbdmf/XMIToDMF/importUML-ApplicationDB.xsl");
#endif
#endif
#ifdef OSX
        XMIFileUMLProject-&gt;setData("./wxWrapper.app/Contents/Resources/UMLSamples/SecondStageModels/lbDMF Manager.xmi");
        XMIFileUMLProjectExport-&gt;setData("./wxWrapper.app/Contents/Resources/UMLSamples/SecondStageModels/Export.xmi");
		XSLFileUMLExport-&gt;setData("./wxWrapper.app/Contents/Resources/XSLT/DMFToXMI/gen_DMFToXMI.xsl");
        XSLFileImportSettings-&gt;setData("./wxWrapper.app/Contents/Resources/XSLT/XMIToDMF/XMISettings.xsl");
        XSLFileExportSettings-&gt;setData("./wxWrapper.app/Contents/Resources/XSLT/DMFToXMI/XMISettings.xsl");
        XSLFileSystemDatabase-&gt;setData("./wxWrapper.app/Contents/Resources/XSLT/XMIToDMF/ImportUML-SystemDB.xsl");
        XSLFileApplicationDatabase-&gt;setData("./wxWrapper.app/Contents/Resources/XSLT/XMIToDMF/ImportUML-ApplicationDB.xsl");
#endif
	 } else {
		_LOG &lt;&lt; "Load the dynamic app import settings from parameter set..." LOG_
		*name = "UMLImportDBName";
		SomeBaseSettings-&gt;getUAPString(*&amp;name, *&amp;UMLImportTargetDBName);
		*name = "UMLImportDBUser";
		SomeBaseSettings-&gt;getUAPString(*&amp;name, *&amp;UMLImportTargetDBUser);
		*name = "UMLImportDBPass";
		SomeBaseSettings-&gt;getUAPString(*&amp;name, *&amp;UMLImportTargetDBPass);
		*name = "DatabaseSettingNamespace";
		SomeBaseSettings-&gt;getUAPString(*&amp;name, *&amp;DatabaseSettingNamespace);
		*name = "UsePlugin";
		SomeBaseSettings-&gt;getUAPBoolean(*&amp;name, *&amp;UsePlugin);
/*
		*name = "UseOtherXSLFile";
		SomeBaseSettings-&gt;getUAPBoolean(*&amp;name, *&amp;UseOtherXSLFile);
*/
		*name = "XSLFileSystemDatabase";
		SomeBaseSettings-&gt;getUAPFileLocation(*&amp;name, *&amp;XSLFileSystemDatabase);
		*name = "XSLFileApplicationDatabase";
		SomeBaseSettings-&gt;getUAPFileLocation(*&amp;name, *&amp;XSLFileApplicationDatabase);
		 *name = "XMIFileUMLProject";
		 SomeBaseSettings-&gt;getUAPFileLocation(*&amp;name, *&amp;XMIFileUMLProject);
		 *name = "XMIFileUMLProjectExport";
		 SomeBaseSettings-&gt;getUAPFileLocation(*&amp;name, *&amp;XMIFileUMLProjectExport);
		 *name = "GeneralDBSchemaname";
		 SomeBaseSettings-&gt;getUAPString(*&amp;name, *&amp;GeneralDBSchemaname);
		 *name = "XSLFileUMLExport";
		 SomeBaseSettings-&gt;getUAPFileLocation(*&amp;name, *&amp;XSLFileUMLExport);
		 *name = "XSLFileImportSettings";
		 SomeBaseSettings-&gt;getUAPFileLocation(*&amp;name, *&amp;XSLFileImportSettings);
		 *name = "XSLFileExportSettings";
		 SomeBaseSettings-&gt;getUAPFileLocation(*&amp;name, *&amp;XSLFileExportSettings);
	} 

	// DB Model insert removed. Where are the others? 

	*name = "UMLImportTargetDBName";
	QI(UMLImportTargetDBName, lb_I_Unknown, uk)
	document-&gt;insert(&amp;uk, &amp;key);
	
	*name = "UMLImportTargetDBUser";
	QI(UMLImportTargetDBUser, lb_I_Unknown, uk)
	document-&gt;insert(&amp;uk, &amp;key);
	
	*name = "UMLImportTargetDBPass";
	QI(UMLImportTargetDBPass, lb_I_Unknown, uk)
	document-&gt;insert(&amp;uk, &amp;key);
	
	*name = "DatabaseSettingNamespace";
	QI(DatabaseSettingNamespace, lb_I_Unknown, uk)
	document-&gt;insert(&amp;uk, &amp;key);
	
	*name = "UsePlugin";
	QI(UsePlugin, lb_I_Unknown, uk)
	document-&gt;insert(&amp;uk, &amp;key);

	_LOG &lt;&lt; "Loaded Use Plugin switch from database: " &lt;&lt; UsePlugin-&gt;charrep() LOG_

	*name = "XSLFileUMLExport";
	QI(XSLFileUMLExport, lb_I_Unknown, uk)
	document-&gt;insert(&amp;uk, &amp;key);
	
	*name = "XSLFileImportSettings";
	QI(XSLFileImportSettings, lb_I_Unknown, uk)
	document-&gt;insert(&amp;uk, &amp;key);
	
	*name = "XSLFileExportSettings";
	QI(XSLFileExportSettings, lb_I_Unknown, uk)
	document-&gt;insert(&amp;uk, &amp;key);
	
	*name = "XSLFileSystemDatabase";
	QI(XSLFileSystemDatabase, lb_I_Unknown, uk)
	document-&gt;insert(&amp;uk, &amp;key);
	
	*name = "XSLFileApplicationDatabase";
	QI(XSLFileApplicationDatabase, lb_I_Unknown, uk)
	document-&gt;insert(&amp;uk, &amp;key);
/*	
	*name = "UseOtherXSLFile";
	QI(UseOtherXSLFile, lb_I_Unknown, uk)
	document-&gt;insert(&amp;uk, &amp;key);
*/
	*name = "XMIFileUMLProject";
	QI(XMIFileUMLProject, lb_I_Unknown, uk)
	document-&gt;insert(&amp;uk, &amp;key);
	
	*name = "XMIFileUMLProjectExport";
	QI(XMIFileUMLProjectExport, lb_I_Unknown, uk)
	document-&gt;insert(&amp;uk, &amp;key);
	
	*name = "GeneralDBSchemaname";
	QI(GeneralDBSchemaname, lb_I_Unknown, uk)
	document-&gt;insert(&amp;uk, &amp;key);

	if (
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM17" select="@name"/>
<xsl:variable name="FormularNameACM17">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM17"/>
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
		(<xsl:value-of select="$FormularNameACM17"/> != NULL) &amp;&amp; 
</xsl:for-each>
		true) {
		// Here:
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularNameACM18" select="@name"/>
<xsl:variable name="FormularNameACM18">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularNameACM18"/>
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
		*name = "<xsl:value-of select="$FormularNameACM18"/>";
		QI(<xsl:value-of select="$FormularNameACM18"/>, lb_I_Unknown, uk)
		document-&gt;insert(&amp;uk, &amp;key);
</xsl:for-each>
	}		
	
	*name = "ApplicationData";
	params-&gt;setUAPContainer(*&amp;name, *&amp;document);
	
	params++;
	meta-&gt;setActiveDocument(*&amp;params);
	meta-&gt;setStatusText("Info", "Load database configuration done.");
	
	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::save(lb_I_Database* oDB) {
	lbErrCodes err = ERR_NONE;

	return err;
}

IMPLEMENT_FUNCTOR(instanceOflbDynamicAppBoUMLImportExport, lbDynamicAppBoUMLImportExport)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicAppBoUMLImportExport)
	ADD_INTERFACE(lb_I_StandaloneStreamable)
END_IMPLEMENT_LB_UNKNOWN()


lbDynamicAppBoUMLImportExport::lbDynamicAppBoUMLImportExport() {
	

	_CL_LOG &lt;&lt; "lbDynamicAppBoUMLImportExport::lbDynamicAppBoUMLImportExport() called." LOG_
}

lbDynamicAppBoUMLImportExport::~lbDynamicAppBoUMLImportExport() {
	_CL_LOG &lt;&lt; "lbDynamicAppBoUMLImportExport::~lbDynamicAppBoUMLImportExport() called." LOG_
}

lbErrCodes LB_STDCALL lbDynamicAppBoUMLImportExport::setData(lb_I_Unknown*) {
		_CL_VERBOSE &lt;&lt; "Error: lbDynamicAppBoUMLImportExport::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}


lbErrCodes LB_STDCALL lbDynamicAppBoUMLImportExport::load(lb_I_InputStream* iStream) {
	lbErrCodes err = ERR_NONE;
	xsltStylesheetPtr cur = NULL;
	xmlDocPtr doc, res;
	xmlDocPtr stylesheetdoc;
	
	const char *params[16 + 1];
	
	params[0] = NULL;

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)

	UAP_REQUEST(getModuleInstance(), lb_I_String, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBPass)

	UAP_REQUEST(getModuleInstance(), lb_I_String, overwrite)

	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileImportSettings)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileSystemDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileApplicationDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_String, writeXMISettings)

	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)
	ukDoc = metaapp-&gt;getActiveDocument();
	QI(ukDoc, lb_I_Parameter, document)
								
	if (document != NULL) {
		*param = "XSLFileImportSettings";
		document-&gt;getUAPFileLocation(*&amp;param, *&amp;XSLFileImportSettings);
		*param = "XSLFileSystemDatabase";
		document-&gt;getUAPFileLocation(*&amp;param, *&amp;XSLFileSystemDatabase);
		*param = "XSLFileApplicationDatabase";
		document-&gt;getUAPFileLocation(*&amp;param, *&amp;XSLFileApplicationDatabase);

		_LOG &lt;&lt; "Have got the following files: " &lt;&lt; XSLFileSystemDatabase-&gt;charrep() &lt;&lt; " and " &lt;&lt; XSLFileApplicationDatabase-&gt;charrep() LOG_		

		*param = "UMLImportDBName";
		document-&gt;getUAPString(*&amp;param, *&amp;DBName);
		*param = "UMLImportDBUser";
		document-&gt;getUAPString(*&amp;param, *&amp;DBUser);
		*param = "UMLImportDBPass";
		document-&gt;getUAPString(*&amp;param, *&amp;DBPass);

		*param = "overwriteDatabase";
		document-&gt;getUAPString(*&amp;param, *&amp;overwrite);
		
		*param = "writeXMISettings";
		document-&gt;getUAPString(*&amp;param, *&amp;writeXMISettings);
		if (writeXMISettings-&gt;charrep() == NULL) {
			_LOG &lt;&lt; "Warning: The writeXMISettings parameter was not passed. Set it to no." LOG_
			*writeXMISettings = "no";
		}
    }

	// Write the settings file for the application database here ...
	
	
	// If I import to a MS SQL server, then I need other settings. Always writing the 'wrong' default settings is not correct.
	if (*writeXMISettings == "yes") {
		if (XSLFileImportSettings-&gt;charrep() != NULL) {
			if (strcmp(XSLFileImportSettings-&gt;charrep(), "&lt;settings&gt;") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)
				
				oStream-&gt;setFileName(XSLFileImportSettings-&gt;charrep());
				if (oStream-&gt;open()) {
					oStream-&gt;setBinary();
					*oStream &lt;&lt; "&lt;xsl:stylesheet version=\"1.1\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\" xmlns:exsl=\"http://exslt.org/common\" extension-element-prefixes=\"exsl\"&gt;\n";
					*oStream &lt;&lt; "&lt;!--&lt;xsl:variable name=\"targetdatabase\" select=\"' '\"/&gt;--&gt;&lt;!-- Mapped to DefaultDatabaseSystem as in XSLT document defined. --&gt;\n";
					*oStream &lt;&lt; "&lt;!--&lt;xsl:variable name=\"targetdatabase\" select=\"'DatabaseLayerGateway'\"/&gt;--&gt;&lt;!-- Mapped to Sqlite (in XSLT document) --&gt;\n";
					*oStream &lt;&lt; "&lt;!--&lt;xsl:variable name=\"targetdatabase\" select=\"'MSSQL'\"/&gt;--&gt;\n";
					*oStream &lt;&lt; "&lt;!--&lt;xsl:variable name=\"targetdatabase\" select=\"'PostgreSQL'\"/&gt;--&gt;\n";
					*oStream &lt;&lt; "&lt;xsl:variable name=\"targetdatabase\" select=\"'" &lt;&lt; metaapp-&gt;getApplicationDatabaseBackend() &lt;&lt; "'\"/&gt;&lt;!-- Mapped from Application Database backend in the properties window group General --&gt;\n";
					*oStream &lt;&lt; "&lt;xsl:variable name=\"execute_droprules\" select=\"'" &lt;&lt; overwrite-&gt;charrep() &lt;&lt; "'\"/&gt;\n";
					
					DBName-&gt;replace("&gt;", "&amp;gt;");
					DBName-&gt;replace("&lt;", "&amp;lt;");
					DBUser-&gt;replace("&gt;", "&amp;gt;");
					DBUser-&gt;replace("&lt;", "&amp;lt;");
					DBPass-&gt;replace("&gt;", "&amp;gt;");
					DBPass-&gt;replace("&lt;", "&amp;lt;");
					
					*oStream &lt;&lt; "&lt;xsl:variable name=\"database_name\" select=\"'" &lt;&lt; DBName-&gt;charrep() &lt;&lt; "'\"/&gt;\n";
					*oStream &lt;&lt; "&lt;xsl:variable name=\"database_user\" select=\"'" &lt;&lt; DBUser-&gt;charrep() &lt;&lt; "'\"/&gt;\n";
					*oStream &lt;&lt; "&lt;xsl:variable name=\"database_pass\" select=\"'" &lt;&lt; DBPass-&gt;charrep() &lt;&lt; "'\"/&gt;\n";
					
					/// \todo Write additional XMI settings here.				
					
					
					*oStream &lt;&lt; "&lt;/xsl:stylesheet&gt;\n";
					oStream-&gt;close();
				}
			}
		}
	}
	xmlSubstituteEntitiesDefault(1);
#ifndef __WATCOMC__	
    xmlLoadExtDtdDefaultValue = 1;
#endif
#ifdef __WATCOMC__
    setxmlLoadExtDtdDefaultValue(1);
#endif
		
	// Read the provided stream as the XMI document to be translated.
		
	UAP(lb_I_String, xmidoc)
	xmidoc = iStream-&gt;getAsString();
	xmlChar* XMIURL = (xmlChar*) iStream-&gt;getFileName();
	doc = xmlReadMemory((char const*) xmidoc-&gt;charrep(), strlen(xmidoc-&gt;charrep()), (char const*) XMIURL, NULL, 0);
	if (doc == NULL) {
		_LOG &lt;&lt; "Error: Failed to load in-memory XMI document as an XML document." LOG_
		return err; 
	}
	
	// Read the stylesheet document to get SQL script for database creation
	metaapp-&gt;setStatusText("Info", "Importing application database model ...");

	if (metaapp-&gt;askYesNo("Would you create the database for the application to be imported ?")) {
		UAP(lb_I_String, styledoc)
		UAP(lb_I_InputStream, input)
		
		// May not initialized
		if (XSLFileApplicationDatabase-&gt;charrep() == NULL) {
			XSLFileApplicationDatabase-&gt;setData("");
		}
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, ts)
		*ts = XSLFileApplicationDatabase-&gt;charrep();
		ts-&gt;trim();
		XSLFileApplicationDatabase-&gt;setData(ts-&gt;charrep());
		
		if (strcmp(XSLFileApplicationDatabase-&gt;charrep(), "") == 0) {
			input = metaapp-&gt;askOpenFileReadStream("xsl|*.xsl");
			
			if (input == NULL) {
				return err;	
			}

			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
			XSLFileApplicationDatabase-&gt;setData((char*) input-&gt;getFileName());
			
			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, paramXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_String, parameterXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_String, valueXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, fileXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_Boolean, boolXSL)

			UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
			UAP_REQUEST(getModuleInstance(), lb_I_String, value)
			UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)
			
			parameter-&gt;setData("UML import settings");
			//--------------------------------------------
			
			parameterXSL-&gt;setData("XSL file for application database");
			fileXSL-&gt;setData(XSLFileApplicationDatabase-&gt;getData());
			paramXSL-&gt;setUAPFileLocation(*&amp;parameterXSL, *&amp;fileXSL);
			
			params-&gt;setUAPParameter(*&amp;parameter, *&amp;paramXSL);
			metaapp-&gt;showPropertyPanel(*&amp;params, true);
		} else {
			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
			REQUEST(getModuleInstance(), lb_I_InputStream, input)
			input-&gt;setFileName(XSLFileApplicationDatabase-&gt;charrep());
		}
		
		if (input-&gt;open()) {
			_LOG &lt;&lt; "Try to get the file as a string..." LOG_
			styledoc = input-&gt;getAsString();
			_LOG &lt;&lt; "Got the file as s string." LOG_
			
			xmlChar* URL = (xmlChar*) input-&gt;getFileName();
			_LOG &lt;&lt; "Read the string as an in memory XML document." LOG_
			stylesheetdoc = xmlReadMemory((char const*) styledoc-&gt;charrep(), strlen(styledoc-&gt;charrep()), (char const*) URL, NULL, 0);
			if (stylesheetdoc == NULL) {
				_LOG &lt;&lt; "Error: Failed to load in-memory XMI stylesheet document as an XML document (" &lt;&lt; input-&gt;getFileName() &lt;&lt; ")" LOG_
				return err; 
			}

			_LOG &lt;&lt; "Parse xml document as stylesheet." LOG_
			cur = xsltParseStylesheetDoc(stylesheetdoc);
			
			if (cur == NULL) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				
				*msg = _trans("Failed to parse XSL file.");
				
				metaapp-&gt;msgBox(_trans("Error"), msg-&gt;charrep());
				return err;
			}
			
			xmlChar* result = NULL;
			int len = 0;

			_LOG &lt;&lt; "Apply the stylesheet document." LOG_

			xsltTransformContextPtr ctxt;

			res = xsltApplyStylesheet(cur, doc, params);

			_LOG &lt;&lt; "Save resulting document as a string." LOG_

			if (res == NULL) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)

				*msg = _trans("Failed to translate XMI file.\n\nXMI document: ");
				*msg += (const char*) XMIURL;
				*msg += "\n\nStylesheet: ";
				*msg += (const char*) URL;
				metaapp-&gt;msgBox(_trans("Error"), msg-&gt;charrep());
				return err;
			}

			xsltSaveResultToString(&amp;result, &amp;len, res, cur);
			
			xsltFreeStylesheet(cur);
			xmlFreeDoc(res);
			
			// Apply the resulting SQL script to the database
			
			_LOG &lt;&lt; "Prepare database creation..." LOG_

			char* dbbackend = metaapp-&gt;getApplicationDatabaseBackend();
			
			UAP(lb_I_Database, database)
			UAP(lb_I_Query, sampleQuery)
			
			if (dbbackend != NULL &amp;&amp; strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
				_LOG &lt;&lt; "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, database)
				_LOG &lt;&lt; "Using built in database backend for UML import operation..." LOG_
			}

			if (database == NULL) {
				_LOG &lt;&lt; "Error: Could not load database backend, either plugin or built in version." LOG_
				return ERR_UML_IMPORT_LOADDATABASE_MODUL;
			}
				
			database-&gt;init();
			
			if ((database != NULL) &amp;&amp; (database-&gt;connect(DBName-&gt;charrep(), DBName-&gt;charrep(), DBUser-&gt;charrep(), DBPass-&gt;charrep()) != ERR_NONE)) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				*msg = "Could not login to given database.\n";
				*msg += "Please check the following:\n\n";
				*msg += "1. ODBC setup is correct.\n";
				*msg += "2. No spaces are in the database name.\n";
				*msg += "3. Database is created.\n";
				*msg += "4. Login credentials are correct.\n\n";
				*msg += "(Is the following setup correct:\nDatabase: ";
				*msg += DBName-&gt;charrep();
				*msg += "\nUser: ";
				*msg += DBUser-&gt;charrep();
				*msg += " ?";
				metaapp-&gt;msgBox("Error", msg-&gt;charrep());
				return ERR_DB_CONNECT;
			}
			
			sampleQuery = database-&gt;getQuery(DBName-&gt;charrep(), 0);
			
			if (result == NULL) {
				_LOG &lt;&lt; "Error: Did not got the translation from XSLT file." LOG_
				return err;
			}
			
			_LOG &lt;&lt; "Create database... (script is " &lt;&lt; (const char*) result &lt;&lt; ")" LOG_
			sampleQuery-&gt;skipFKCollecting();
			
			if ((metaapp-&gt;getApplicationDatabaseBackend() != NULL) &amp;&amp; (strcmp(metaapp-&gt;getApplicationDatabaseBackend(), "") == 0)) {
				// Do an additional SQL command to create the PostgreSQL plsql handler, but ignore any failures
				sampleQuery-&gt;query("CREATE OR REPLACE FUNCTION plpgsql_call_handler()"
								   "RETURNS language_handler AS"
								   "'$libdir/plpgsql', 'plpgsql_call_handler'"
								   "LANGUAGE 'c' VOLATILE;\n"
								   "CREATE LANGUAGE plpgsql HANDLER plpgsql_call_handler;");
			}
			
			if (sampleQuery-&gt;query((char*) result) != ERR_NONE) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				*msg = _trans("Failed to apply SQL Script imported from UML definition (XMI)!\n\nYou may have a permission problem when you manually have created\ntables with another user prior.\nPlease see into the logfile for more information.");
				metaapp-&gt;msgBox(_trans("Error"), msg-&gt;charrep());
				sampleQuery-&gt;enableFKCollecting();

				xmlFreeDoc(doc);
				
				xsltCleanupGlobals();
				xmlCleanupParser();	
				free(result);
				return err;
			} else {
				sampleQuery-&gt;close();
				database-&gt;close();
				_LOG &lt;&lt; "Database schema has been created." LOG_
				free(result);
			}
		}	
	}
	
	// Read the stylesheet document to import application definition into system database
	
	metaapp-&gt;setStatusText("Info", "Importing lbDMF application definition ...");

	// Write the settings file for the application database here ...
	
	// If I import to a MS SQL server, then I need other settings. Always writing the 'wrong' default settings is not correct.
	if (*writeXMISettings == "yes") {
		if (XSLFileImportSettings-&gt;charrep() != NULL) {
			if (strcmp(XSLFileImportSettings-&gt;charrep(), "&lt;settings&gt;") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)
				
				oStream-&gt;setFileName(XSLFileImportSettings-&gt;charrep());
				if (oStream-&gt;open()) {
					oStream-&gt;setBinary();
					*oStream &lt;&lt; "&lt;xsl:stylesheet version=\"1.1\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\" xmlns:exsl=\"http://exslt.org/common\" extension-element-prefixes=\"exsl\"&gt;\n";
					*oStream &lt;&lt; "&lt;!--&lt;xsl:variable name=\"targetdatabase\" select=\"' '\"/&gt;--&gt;&lt;!-- Mapped to DefaultDatabaseSystem as in XSLT document defined. --&gt;\n";
					*oStream &lt;&lt; "&lt;!--&lt;xsl:variable name=\"targetdatabase\" select=\"'DatabaseLayerGateway'\"/&gt;--&gt;&lt;!-- Mapped to Sqlite (in XSLT document) --&gt;\n";
					*oStream &lt;&lt; "&lt;!--&lt;xsl:variable name=\"targetdatabase\" select=\"'MSSQL'\"/&gt;--&gt;\n";
					*oStream &lt;&lt; "&lt;!--&lt;xsl:variable name=\"targetdatabase\" select=\"'PostgreSQL'\"/&gt;--&gt;\n";
					*oStream &lt;&lt; "&lt;xsl:variable name=\"targetdatabase\" select=\"'" &lt;&lt; metaapp-&gt;getSystemDatabaseBackend() &lt;&lt; "'\"/&gt;&lt;!-- Mapped from Application Database backend in the properties window group General --&gt;\n";
					*oStream &lt;&lt; "&lt;xsl:variable name=\"execute_droprules\" select=\"'" &lt;&lt; overwrite-&gt;charrep() &lt;&lt; "'\"/&gt;\n";

					DBName-&gt;replace("&gt;", "&amp;gt;");
					DBName-&gt;replace("&lt;", "&amp;lt;");
					DBUser-&gt;replace("&gt;", "&amp;gt;");
					DBUser-&gt;replace("&lt;", "&amp;lt;");
					DBPass-&gt;replace("&gt;", "&amp;gt;");
					DBPass-&gt;replace("&lt;", "&amp;lt;");

					*oStream &lt;&lt; "&lt;xsl:variable name=\"database_name\" select=\"'" &lt;&lt; DBName-&gt;charrep() &lt;&lt; "'\"/&gt;\n";
					*oStream &lt;&lt; "&lt;xsl:variable name=\"database_user\" select=\"'" &lt;&lt; DBUser-&gt;charrep() &lt;&lt; "'\"/&gt;\n";
					*oStream &lt;&lt; "&lt;xsl:variable name=\"database_pass\" select=\"'" &lt;&lt; DBPass-&gt;charrep() &lt;&lt; "'\"/&gt;\n";
					*oStream &lt;&lt; "&lt;/xsl:stylesheet&gt;\n";
					oStream-&gt;close();
				}
			}
		}
	}

	if (metaapp-&gt;askYesNo("Would you create the application definition for the application to be imported into the system database ?")) {
		UAP(lb_I_String, styledoc)
		UAP_REQUEST(getModuleInstance(), lb_I_InputStream, input)
		
		// May not initialized
		if (XSLFileSystemDatabase-&gt;charrep() == NULL) {
			XSLFileSystemDatabase-&gt;setData("");
		}
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, ts)
		*ts = XSLFileSystemDatabase-&gt;charrep();
		ts-&gt;trim();
		XSLFileSystemDatabase-&gt;setData(ts-&gt;charrep());
		
		if (strcmp(XSLFileSystemDatabase-&gt;charrep(), "") == 0) {
			input = metaapp-&gt;askOpenFileReadStream("xsl|*.xsl");
			
			if (input == NULL) {
				return err;	
			}

			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
			XSLFileSystemDatabase-&gt;setData((char*) input-&gt;getFileName());
			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, paramXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_String, parameterXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_String, valueXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, fileXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_Boolean, boolXSL)

			UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
			UAP_REQUEST(getModuleInstance(), lb_I_String, value)
			UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)
			
			parameter-&gt;setData("UML import settings");
			//--------------------------------------------
			
			parameterXSL-&gt;setData("XSL file for system database");
			fileXSL-&gt;setData(XSLFileSystemDatabase-&gt;getData());
			paramXSL-&gt;setUAPFileLocation(*&amp;parameterXSL, *&amp;fileXSL);
			
			params-&gt;setUAPParameter(*&amp;parameter, *&amp;paramXSL);
			metaapp-&gt;showPropertyPanel(*&amp;params, true);
		} else {
			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
			REQUEST(getModuleInstance(), lb_I_InputStream, input)
			input-&gt;setFileName(XSLFileSystemDatabase-&gt;charrep());
		}

		if (input-&gt;open()) {
			_LOG &lt;&lt; "Try to get the file as a string..." LOG_
			styledoc = input-&gt;getAsString();
			_LOG &lt;&lt; "Got the file as s string." LOG_
			
			xmlChar* URL = (xmlChar*) input-&gt;getFileName();
			_LOG &lt;&lt; "Read the string as an in memory XML document." LOG_
			stylesheetdoc = xmlReadMemory((char const*) styledoc-&gt;charrep(), strlen(styledoc-&gt;charrep()), (char const*) URL, NULL, 0);
			if (stylesheetdoc == NULL) {
				_LOG &lt;&lt; "Error: Failed to load in-memory XMI stylesheet document as an XML document." LOG_
				return err; 
			}

			_LOG &lt;&lt; "Parse xml document as stylesheet." LOG_
			cur = xsltParseStylesheetDoc(stylesheetdoc);
			
			xmlChar* result = NULL;
			int len = 0;

			_LOG &lt;&lt; "Apply the stylesheet document." LOG_

			res = xsltApplyStylesheet(cur, doc, params);

			if (res == NULL) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				
				*msg = _trans("Failed to translate XMI file.\n\nXMI document: ");
				*msg += (const char*) XMIURL;
				*msg += "\n\nStylesheet: ";
				*msg += (const char*) URL;
				metaapp-&gt;msgBox(_trans("Error"), msg-&gt;charrep());
				return err;
			}
			
			_LOG &lt;&lt; "Save resulting document as a string." LOG_

			xsltSaveResultToString(&amp;result, &amp;len, res, cur);
			
			xsltFreeStylesheet(cur);
			xmlFreeDoc(res);
			
			// Apply the resulting SQL script to the database
			
			_LOG &lt;&lt; "Prepare database creation..." LOG_

			char* dbbackend = metaapp-&gt;getSystemDatabaseBackend();
			
			UAP(lb_I_Database, database)
			UAP(lb_I_Query, sampleQuery)

			if (dbbackend != NULL &amp;&amp; strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
				_LOG &lt;&lt; "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, database)
				_LOG &lt;&lt; "Using built in database backend for UML import operation..." LOG_
			}

			if (database == NULL) {
				_LOG &lt;&lt; "Error: Could not load database backend, either plugin or built in version." LOG_
				return ERR_UML_IMPORT_LOADDATABASE_MODUL;
			}
				
			database-&gt;init();
			
			const char* lbDMFPasswd = getenv("lbDMFPasswd");
			const char* lbDMFUser   = getenv("lbDMFUser");
			
			if (!lbDMFUser) lbDMFUser = "dba";
			if (!lbDMFPasswd) lbDMFPasswd = "trainres";
			
			if ((database != NULL) &amp;&amp; (database-&gt;connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE)) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				*msg = "Could not login to given database.\n";
				*msg += "Please check the following:\n\n";
				*msg += "1. ODBC setup is correct.\n";
				*msg += "2. No spaces are in the database name.\n";
				*msg += "3. Database is created.\n";
				*msg += "4. Login credentials are correct.\n\n";
				*msg += "(Is the following setup correct:\nDatabase: ";
				*msg += DBName-&gt;charrep();
				*msg += "\nUser: ";
				*msg += DBUser-&gt;charrep();
				*msg += " ?";
				metaapp-&gt;msgBox("Error", msg-&gt;charrep());
				return ERR_DB_CONNECT;
			}
			
			sampleQuery = database-&gt;getQuery("lbDMF", 0);
			
			_LOG &lt;&lt; "Create system database... (script is " &lt;&lt; (const char*) result &lt;&lt; ")" LOG_
			sampleQuery-&gt;skipFKCollecting();
			
			if ((metaapp-&gt;getSystemDatabaseBackend() != NULL) &amp;&amp; (strcmp(metaapp-&gt;getSystemDatabaseBackend(), "") == 0)) {
				// Do an additional SQL command to create the PostgreSQL plsql handler, but ignore any failures
				sampleQuery-&gt;query("CREATE OR REPLACE FUNCTION plpgsql_call_handler()"
								   "RETURNS language_handler AS"
								   "'$libdir/plpgsql', 'plpgsql_call_handler'"
								   "LANGUAGE 'c' VOLATILE;\n"
								   "CREATE LANGUAGE plpgsql HANDLER plpgsql_call_handler;");
			}
			
			if (sampleQuery-&gt;query((char*) result) != ERR_NONE) {
				metaapp-&gt;msgBox("Error", "Failed to apply SQL Script imported from UML definition (XMI)!");
				sampleQuery-&gt;enableFKCollecting();

				xmlFreeDoc(doc);
				
				xsltCleanupGlobals();
				xmlCleanupParser();	
				free(result);
				
				return err;
			} else {
				sampleQuery-&gt;close();
				database-&gt;close();
				_LOG &lt;&lt; "Database has been filled." LOG_
				sampleQuery-&gt;enableFKCollecting();
				free(result);
			}
		}	
	}

	xmlFreeDoc(doc);
				
	xsltCleanupGlobals();
	xmlCleanupParser();	

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppBoUMLImportExport::save(lb_I_OutputStream* oStream) {
	lbErrCodes err = ERR_NONE;
	xsltStylesheetPtr cur = NULL;
	xmlDocPtr doc, res;
	xmlDocPtr stylesheetdoc;
	
	const char *params[16 + 1];
	
	_LOG &lt;&lt; "lbDynamicAppBoUMLImportExport::save(lb_I_OutputStream* oStream) called." LOG_
	
	params[0] = NULL;
	
	UAP(lb_I_Parameter, appparams)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)
	appparams = metaapp-&gt;getPropertySet("DynamicAppDefaultSettings");

	/* To save the output of generated content, I need to deactivate the generation into a file inside
	 * the XSL template. Therefore the template needs to support it and the settings here should be used.
	 */
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBPass)
	
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileExportSettings)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileUMLExport)
	
	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)
	ukDoc = metaapp-&gt;getActiveDocument();
	QI(ukDoc, lb_I_Parameter, document)
	
	if (document != NULL) {
		*param = "XSLFileExportSettings";
		document-&gt;getUAPFileLocation(*&amp;param, *&amp;XSLFileExportSettings);
		
		*param = "XSLFileUMLExport";
		document-&gt;getUAPFileLocation(*&amp;param, *&amp;XSLFileUMLExport);
		
		_LOG &lt;&lt; "Export definition for settings file is: " &lt;&lt; XSLFileExportSettings-&gt;charrep() LOG_
		_LOG &lt;&lt; "Export definition for UML XMI file is: " &lt;&lt; XSLFileUMLExport-&gt;charrep() LOG_
	}
	
	xmlSubstituteEntitiesDefault(1);
#ifndef __WATCOMC__	
    xmlLoadExtDtdDefaultValue = 1;
#endif
#ifdef __WATCOMC__
    setxmlLoadExtDtdDefaultValue(1);
#endif
	
	// Read the lbDMF XML formatted stream into a memory block to be translated.
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, exportparams)
	UAP(lb_I_Unknown, uk)
	QI(exportparams, lb_I_Unknown, uk)
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result) // Result is not filled (inconsistent). The function exportApplicationToXMLBuffer returns it in the parameter given.
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	
	if (dispatcher-&gt;dispatch("exportApplicationToXMLBuffer", uk.getPtr(), &amp;uk_result) == ERR_DISPATCH_FAILS) {
		_LOG &lt;&lt; "Error: Failed to dispatch a call to 'exportApplicationToXMLBuffer'!" LOG_
		return err;
	}
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_String, filename)
	param-&gt;setData("memorybuffer");
	exportparams-&gt;getUAPString(*&amp;param, *&amp;value);
	param-&gt;setData("filename");
	exportparams-&gt;getUAPString(*&amp;param, *&amp;filename);
	
	
	// Write the settings file for the application database here ...

	metaapp-&gt;setStatusText("Info", "Writing XMISettings ...");
	
	if (XSLFileExportSettings-&gt;charrep() != NULL) {
		if (strcmp(XSLFileExportSettings-&gt;charrep(), "&lt;settings&gt;") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)
			
			oStream-&gt;setFileName(XSLFileExportSettings-&gt;charrep());
			if (oStream-&gt;open()) {
				oStream-&gt;setBinary();
				*oStream &lt;&lt; "&lt;xsl:stylesheet version=\"1.1\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\" xmlns:exsl=\"http://exslt.org/common\" extension-element-prefixes=\"exsl\"&gt;\n";
				*oStream &lt;&lt; "&lt;xsl:variable name=\"targetdatabase\" select=\"'" &lt;&lt; metaapp-&gt;getApplicationDatabaseBackend() &lt;&lt; "'\"/&gt;\n";
				*oStream &lt;&lt; "&lt;xsl:variable name=\"stream_output\" select=\"'yes'\"/&gt;\n";
				
				/// \todo Write additional XMI settings here.				
				
				
				*oStream &lt;&lt; "&lt;/xsl:stylesheet&gt;\n";
				oStream-&gt;close();
			} else {
				metaapp-&gt;msgBox("Error", "Failed to write to XMISettings file. Please check file permissions.");
				return err;
			}
		}
	}

	if (value-&gt;charrep() == NULL) {
		metaapp-&gt;msgBox("Error", "Step 1 of exporting application definition has been failed. (This is the plain XML format, not the XMI).");
		return err;
	} else {
		_LOG &lt;&lt; "Generated XML file to transform: '" &lt;&lt; value-&gt;charrep() &lt;&lt; "'" LOG_
	}
	
	xmlChar* XMLURL = (xmlChar*) filename-&gt;charrep();
	doc = xmlReadMemory((char const*) value-&gt;charrep(), strlen(value-&gt;charrep()), (char const*) XMLURL, NULL, 0);
	if (doc == NULL) {
		_LOG &lt;&lt; "Error: Failed to load in-memory XML document." LOG_
		metaapp-&gt;setStatusText("Info", "Failed to translate application definition to XMI.");
		return err; 
	}
	
	UAP(lb_I_String, styledoc)
	UAP(lb_I_InputStream, input)
	
	// May not initialized
	if (XSLFileUMLExport-&gt;charrep() == NULL) {
		XSLFileUMLExport-&gt;setData("");
	}
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, ts)
	*ts = XSLFileUMLExport-&gt;charrep();
	ts-&gt;trim();
	XSLFileUMLExport-&gt;setData(ts-&gt;charrep());
		
	if (strcmp(XSLFileUMLExport-&gt;charrep(), "") == 0) {
		input = metaapp-&gt;askOpenFileReadStream("xsl|*.xsl");
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		XSLFileUMLExport-&gt;setData((char*) input-&gt;getFileName());
		
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, paramXSL)
		UAP_REQUEST(getModuleInstance(), lb_I_String, parameterXSL)
		UAP_REQUEST(getModuleInstance(), lb_I_String, valueXSL)
		UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, fileXSL)
		UAP_REQUEST(getModuleInstance(), lb_I_Boolean, boolXSL)
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
		UAP_REQUEST(getModuleInstance(), lb_I_String, value)
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)
		
		parameter-&gt;setData("UML export settings");
		//--------------------------------------------
		
		parameterXSL-&gt;setData("XSL file for application database");
		fileXSL-&gt;setData(XSLFileUMLExport-&gt;getData());
		paramXSL-&gt;setUAPFileLocation(*&amp;parameterXSL, *&amp;fileXSL);
		
		params-&gt;setUAPParameter(*&amp;parameter, *&amp;paramXSL);
		metaapp-&gt;showPropertyPanel(*&amp;params, true);
	} else {
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		REQUEST(getModuleInstance(), lb_I_InputStream, input)
		input-&gt;setFileName(XSLFileUMLExport-&gt;charrep());
	}

	metaapp-&gt;setStatusText("Info", "Start translating application definition to XMI ...");
	
	if (input-&gt;open()) {
		_LOG &lt;&lt; "Try to get the file as a string..." LOG_
		styledoc = input-&gt;getAsString();
		_LOG &lt;&lt; "Got the file as s string." LOG_
			
		xmlChar* URL = (xmlChar*) input-&gt;getFileName();
		_LOG &lt;&lt; "Read the string as an in memory XML document." LOG_
		stylesheetdoc = xmlReadMemory((char const*) styledoc-&gt;charrep(), strlen(styledoc-&gt;charrep()), (char const*) URL, NULL, 0);
		if (stylesheetdoc == NULL) {
			_LOG &lt;&lt; "Error: Failed to load in-memory XSL stylesheet document as an XML document (" &lt;&lt; input-&gt;getFileName() &lt;&lt; ")" LOG_
			metaapp-&gt;setStatusText("Info", "Failed to translate application definition to XMI.");
			return err; 
		}
			
		_LOG &lt;&lt; "Parse xml document as stylesheet." LOG_
		cur = xsltParseStylesheetDoc(stylesheetdoc);
			
		if (cur == NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			
			*msg = _trans("Failed to parse XSL file.");
				
			metaapp-&gt;msgBox(_trans("Error"), msg-&gt;charrep());
			metaapp-&gt;setStatusText("Info", "Failed to translate application definition to XMI.");
			return err;
		}
			
		xmlChar* result = NULL;
		int len = 0;
			
		_LOG &lt;&lt; "Apply the stylesheet document." LOG_
			
		xsltTransformContextPtr ctxt;
		
		res = xsltApplyStylesheet(cur, doc, params);
			
		_LOG &lt;&lt; "Save resulting document as a string." LOG_
			
		if (res == NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			
			*msg = _trans("Failed to translate XMI file.\n\nXMI document: ");
			*msg += (const char*) XMLURL;
			*msg += "\n\nStylesheet: ";
			*msg += (const char*) URL;
			metaapp-&gt;msgBox(_trans("Error"), msg-&gt;charrep());
			metaapp-&gt;setStatusText("Info", "Failed to translate application definition to XMI.");
			return err;
		}
			
		xsltSaveResultToString(&amp;result, &amp;len, res, cur);
			
		xsltFreeStylesheet(cur);
		xmlFreeDoc(res);
			
		if (result == NULL) {
			_LOG &lt;&lt; "Error: Did not got the translation from XSLT file." LOG_
			xmlFreeDoc(doc);
			
			xsltCleanupGlobals();
			xmlCleanupParser();	
			metaapp-&gt;setStatusText("Info", "Failed to translate application definition to XMI.");
			return err;
		}
		
		oStream-&gt;setBinary();
		*oStream &lt;&lt; (char*) result;
		oStream-&gt;close();
		xmlFreeDoc(doc);
			
		xsltCleanupGlobals();
		xmlCleanupParser();	
		free(result);
		metaapp-&gt;setStatusText("Info", "");
		return err;
}	

return err;
}

lbErrCodes LB_STDCALL lbDynamicAppBoUMLImportExport::load(lb_I_Database* iDB) {
lbErrCodes err = ERR_NONE;
return err;
}

lbErrCodes LB_STDCALL lbDynamicAppBoUMLImportExport::save(lb_I_Database* oDB) {
lbErrCodes err = ERR_NONE;
return err;
}


/*...sclass lbPluginDynamicAppXMLStorage implementation:0:*/
/*...slbPluginDynamicAppXMLStorage:0:*/
class lbPluginDynamicAppXMLStorage : public lb_I_PluginImpl {
public:
lbPluginDynamicAppXMLStorage();

virtual ~lbPluginDynamicAppXMLStorage();

bool LB_STDCALL canAutorun();
lbErrCodes LB_STDCALL autorun();
/*...sfrom plugin interface:8:*/
void LB_STDCALL initialize();

bool LB_STDCALL run();

lb_I_Unknown* LB_STDCALL peekImplementation();
lb_I_Unknown* LB_STDCALL getImplementation();
void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }
/*...e*/

DECLARE_LB_UNKNOWN()

UAP(lb_I_Unknown, ukActions)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDynamicAppXMLStorage)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDynamicAppXMLStorage, lbPluginDynamicAppXMLStorage)

/*...slbErrCodes LB_STDCALL lbPluginDynamicAppStorage\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDynamicAppXMLStorage::setData(lb_I_Unknown* uk) {
lbErrCodes err = ERR_NONE;

_CL_VERBOSE &lt;&lt; "lbPluginDynamicAppStorage::setData(...) called.\n" LOG_

return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDynamicAppXMLStorage::lbPluginDynamicAppXMLStorage() {
_CL_VERBOSE &lt;&lt; "lbPluginDynamicAppStorage::lbPluginDynamicAppStorage() called.\n" LOG_

}

lbPluginDynamicAppXMLStorage::~lbPluginDynamicAppXMLStorage() {
_CL_VERBOSE &lt;&lt; "lbPluginDynamicAppStorage::~lbPluginDynamicAppStorage() called.\n" LOG_
}

bool LB_STDCALL lbPluginDynamicAppXMLStorage::canAutorun() {
return false;
}

lbErrCodes LB_STDCALL lbPluginDynamicAppXMLStorage::autorun() {
lbErrCodes err = ERR_NONE;
return err;
}

void LB_STDCALL lbPluginDynamicAppXMLStorage::initialize() {
}

bool LB_STDCALL lbPluginDynamicAppXMLStorage::run() {
return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppXMLStorage::peekImplementation() {
lbErrCodes err = ERR_NONE;

if (ukActions == NULL) {
lbDynamicAppXMLStorage* DynamicAppStorage = new lbDynamicAppXMLStorage();

QI(DynamicAppStorage, lb_I_Unknown, ukActions)
} else {
_CL_VERBOSE &lt;&lt; "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
}

return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppXMLStorage::getImplementation() {
lbErrCodes err = ERR_NONE;

if (ukActions == NULL) {

_CL_VERBOSE &lt;&lt; "Warning: peekImplementation() has not been used prior.\n" LOG_

lbDynamicAppXMLStorage* DynamicAppStorage = new lbDynamicAppXMLStorage();


QI(DynamicAppStorage, lb_I_Unknown, ukActions)
}

lb_I_Unknown* r = ukActions.getPtr();
ukActions.resetPtr();
return r;
}
/*...e*/
void LB_STDCALL lbPluginDynamicAppXMLStorage::releaseImplementation() {
lbErrCodes err = ERR_NONE;

if (ukActions != NULL) {
		ukActions--;
		ukActions.resetPtr();
}
}
/*...e*/
/*...e*/

//==================================

/*...sclass lbPluginDynamicAppInternalStorage implementation:0:*/
/*...slbPluginDynamicAppInternalStorage:0:*/
class lbPluginDynamicAppInternalStorage : public lb_I_PluginImpl {
public:
lbPluginDynamicAppInternalStorage();

virtual ~lbPluginDynamicAppInternalStorage();

bool LB_STDCALL canAutorun();
lbErrCodes LB_STDCALL autorun();
/*...sfrom plugin interface:8:*/
void LB_STDCALL initialize();

bool LB_STDCALL run();

lb_I_Unknown* LB_STDCALL peekImplementation();
lb_I_Unknown* LB_STDCALL getImplementation();
void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }
/*...e*/

DECLARE_LB_UNKNOWN()

UAP(lb_I_Unknown, ukActions)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDynamicAppInternalStorage)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDynamicAppInternalStorage, lbPluginDynamicAppInternalStorage)

/*...slbErrCodes LB_STDCALL lbPluginDynamicAppStorage\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDynamicAppInternalStorage::setData(lb_I_Unknown* uk) {
lbErrCodes err = ERR_NONE;

_CL_VERBOSE &lt;&lt; "lbPluginDynamicAppStorage::setData(...) called.\n" LOG_

return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDynamicAppInternalStorage::lbPluginDynamicAppInternalStorage() {
_CL_VERBOSE &lt;&lt; "lbPluginDynamicAppStorage::lbPluginDynamicAppStorage() called.\n" LOG_

}

lbPluginDynamicAppInternalStorage::~lbPluginDynamicAppInternalStorage() {
_CL_VERBOSE &lt;&lt; "lbPluginDynamicAppStorage::~lbPluginDynamicAppStorage() called.\n" LOG_
}

bool LB_STDCALL lbPluginDynamicAppInternalStorage::canAutorun() {
return false;
}

lbErrCodes LB_STDCALL lbPluginDynamicAppInternalStorage::autorun() {
lbErrCodes err = ERR_NONE;
return err;
}

void LB_STDCALL lbPluginDynamicAppInternalStorage::initialize() {
}

bool LB_STDCALL lbPluginDynamicAppInternalStorage::run() {
return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppInternalStorage::peekImplementation() {
lbErrCodes err = ERR_NONE;

if (ukActions == NULL) {
lbDynamicAppInternalStorage* DynamicAppStorage = new lbDynamicAppInternalStorage();

QI(DynamicAppStorage, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE &lt;&lt; "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppInternalStorage::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE &lt;&lt; "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDynamicAppInternalStorage* DynamicAppStorage = new lbDynamicAppInternalStorage();
		
	
		QI(DynamicAppStorage, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDynamicAppInternalStorage::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/


/*...sclass lbPluginDynamicAppBoUMLImport implementation:0:*/
/*...slbPluginDynamicAppBoUMLImport:0:*/
class lbPluginDynamicAppBoUMLImport : public lb_I_PluginImpl {
public:
	lbPluginDynamicAppBoUMLImport();
	
	virtual ~lbPluginDynamicAppBoUMLImport();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukActions)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDynamicAppBoUMLImport)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDynamicAppBoUMLImport, lbPluginDynamicAppBoUMLImport)

/*...slbErrCodes LB_STDCALL lbPluginDynamicAppStorage\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDynamicAppBoUMLImport::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE &lt;&lt; "lbPluginDynamicAppStorage::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDynamicAppBoUMLImport::lbPluginDynamicAppBoUMLImport() {
	_CL_VERBOSE &lt;&lt; "lbPluginDynamicAppStorage::lbPluginDynamicAppStorage() called.\n" LOG_
	
}

lbPluginDynamicAppBoUMLImport::~lbPluginDynamicAppBoUMLImport() {
	_CL_VERBOSE &lt;&lt; "lbPluginDynamicAppStorage::~lbPluginDynamicAppStorage() called.\n" LOG_
}

bool LB_STDCALL lbPluginDynamicAppBoUMLImport::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDynamicAppBoUMLImport::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDynamicAppBoUMLImport::initialize() {
}
	
bool LB_STDCALL lbPluginDynamicAppBoUMLImport::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppBoUMLImport::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		lbDynamicAppBoUMLImportExport* DynamicAppStorage = new lbDynamicAppBoUMLImportExport();
		
		QI(DynamicAppStorage, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE &lt;&lt; "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppBoUMLImport::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE &lt;&lt; "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDynamicAppBoUMLImportExport* DynamicAppStorage = new lbDynamicAppBoUMLImportExport();
		
	
		QI(DynamicAppStorage, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDynamicAppBoUMLImport::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/
</xsl:template>
</xsl:stylesheet>

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

<!-- This template creates a pair of files per formular name -->
<xsl:template name="ProxyModul.cpp">
	<xsl:param name="ApplicationName"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>/*
	Automatically created file. Do not modify.
 */

#ifdef IMPLEMENT_PROXY_PLUGIN
#define <xsl:value-of select="$ApplicationName"/>_DLL

#include &lt;string.h&gt;
#include &lt;conio.h&gt;
#include &lt;lbConfigHook.h&gt;

#include &lt;appcs.h&gt;
#include &lt;appbus.h&gt;

class lbProxyModul : public lb_I_PluginModule {
public:
	
	lbProxyModul();
	virtual ~lbProxyModul();
	
	DECLARE_LB_UNKNOWN()
	
	void LB_STDCALL initialize();
	void LB_STDCALL install();
	
	DECLARE_PLUGINS()
};

class lbPlugin<xsl:value-of select="$ApplicationName"/> : public lb_I_PluginImpl {
public:
	lbPlugin<xsl:value-of select="$ApplicationName"/>();
	
	virtual ~lbPlugin<xsl:value-of select="$ApplicationName"/>();
	
	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
	/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();
	
	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
	/*...e*/
	
	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, uk<xsl:value-of select="$ApplicationName"/>)
};


IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbProxyModul)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbProxyModul)
	ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

BEGIN_PLUGINS(lbProxyModul)
ADD_PLUGIN(lbPlugin<xsl:value-of select="$ApplicationName"/>,			Proxy)
END_PLUGINS()

lbProxyModul::lbProxyModul() {
	ref = STARTREF;
}

lbProxyModul::~lbProxyModul() {

}

void LB_STDCALL lbProxyModul::initialize() {
	enumPlugins();
}

lbErrCodes LB_STDCALL lbProxyModul::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE &lt;&lt; "lbProxyModul::setData(...) for ApplicationBus not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPlugin<xsl:value-of select="$ApplicationName"/>)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPlugin<xsl:value-of select="$ApplicationName"/>, lbPlugin<xsl:value-of select="$ApplicationName"/>)

lbErrCodes LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$ApplicationName"/>::setData(...) called.\n" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbPlugin<xsl:value-of select="$ApplicationName"/>::lbPlugin<xsl:value-of select="$ApplicationName"/>() {
	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$ApplicationName"/>::lbPlugin<xsl:value-of select="$ApplicationName"/>() called.\n" LOG_
	ref = STARTREF;
}

lbPlugin<xsl:value-of select="$ApplicationName"/>::~lbPlugin<xsl:value-of select="$ApplicationName"/>() {
	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$ApplicationName"/>::~lbPlugin<xsl:value-of select="$ApplicationName"/>() called.\n" LOG_
}

bool LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::autorun() {
	lbErrCodes err = ERR_NONE;
	
	return err;
}

void LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::initialize() {
}

bool LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (uk<xsl:value-of select="$ApplicationName"/> == NULL) {
		<xsl:value-of select="$ApplicationName"/>FacadeProxy* transformer = new <xsl:value-of select="$ApplicationName"/>FacadeProxy();
		transformer->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		QI(transformer, lb_I_Unknown, uk<xsl:value-of select="$ApplicationName"/>)
	} else {
		_CL_VERBOSE &lt;&lt; "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return uk<xsl:value-of select="$ApplicationName"/>.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (uk<xsl:value-of select="$ApplicationName"/> == NULL) {
		
		_CL_VERBOSE &lt;&lt; "Warning: peekImplementation() has not been used prior.\n" LOG_
		
		<xsl:value-of select="$ApplicationName"/>FacadeProxy* transformer = new <xsl:value-of select="$ApplicationName"/>FacadeProxy();
		transformer->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		
		QI(transformer, lb_I_Unknown, uk<xsl:value-of select="$ApplicationName"/>)
	}
	
	lb_I_Unknown* r = uk<xsl:value-of select="$ApplicationName"/>.getPtr();
	uk<xsl:value-of select="$ApplicationName"/>.resetPtr();
	return r;
}

void LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (uk<xsl:value-of select="$ApplicationName"/> != NULL) {
		uk<xsl:value-of select="$ApplicationName"/>--;
		uk<xsl:value-of select="$ApplicationName"/>.resetPtr();
	}
}
#endif //IMPLEMENT_PROXY_PLUGIN

	</xsl:template>
</xsl:stylesheet>
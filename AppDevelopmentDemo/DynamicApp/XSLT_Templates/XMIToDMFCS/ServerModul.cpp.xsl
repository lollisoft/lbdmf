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

<!-- This template creates a pair of files per formular name -->
<xsl:template name="ServerModul.cpp">
	<xsl:param name="ApplicationName"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens at lollisoft.de)

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

#include &lt;string.h&gt;
#include &lt;conio.h&gt;
#include &lt;lbConfigHook.h&gt;

#include &lt;appcs.h&gt;
//#include &lt;appbus.h&gt;

#undef DLLEXPORT

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif
#ifdef LINUX 
#define DLLEXPORT
#endif

#include &lt;I<xsl:value-of select="$ApplicationName"/>_Entities.h&gt;
#include &lt;I<xsl:value-of select="$ApplicationName"/>.h&gt;

#include &lt;<xsl:value-of select="$ApplicationName"/>_FacadeServer.h&gt;

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

private:
	UAP(lb_I_Unknown, impl)
};

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
	_LOG &lt;&lt; "lbPlugin<xsl:value-of select="$ApplicationName"/>::lbPlugin<xsl:value-of select="$ApplicationName"/>() called." LOG_
	ref = STARTREF;
}

lbPlugin<xsl:value-of select="$ApplicationName"/>::~lbPlugin<xsl:value-of select="$ApplicationName"/>() {
	_LOG &lt;&lt; "lbPlugin<xsl:value-of select="$ApplicationName"/>::~lbPlugin<xsl:value-of select="$ApplicationName"/>() called.\n" LOG_
}

bool LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::canAutorun() {
	_LOG &lt;&lt; "lbPlugin<xsl:value-of select="$ApplicationName"/>::canAutorun() called.\n" LOG_
	return false;
}

lbErrCodes LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::autorun() {
	lbErrCodes err = ERR_NONE;
	_LOG &lt;&lt; "lbPlugin<xsl:value-of select="$ApplicationName"/>::autorun() called.\n" LOG_
	return err;
}

void LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::initialize() {
	_LOG &lt;&lt; "lbPlugin<xsl:value-of select="$ApplicationName"/>::initialize() called.\n" LOG_
}
	
bool LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::run() {
	_LOG &lt;&lt; "lbPlugin<xsl:value-of select="$ApplicationName"/>::run() called.\n" LOG_
	return true;
}

lb_I_Unknown* LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {
		<xsl:value-of select="$ApplicationName"/>* _<xsl:value-of select="$ApplicationName"/> = new <xsl:value-of select="$ApplicationName"/>();
		_<xsl:value-of select="$ApplicationName"/>-&gt;setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(_<xsl:value-of select="$ApplicationName"/>, lb_I_Unknown, impl)
	} else {
		_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$ApplicationName"/>::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return impl.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {
		_LOG &lt;&lt; "Warning: getImplementation() has not been used prior." LOG_
		<xsl:value-of select="$ApplicationName"/>* _<xsl:value-of select="$ApplicationName"/> = new <xsl:value-of select="$ApplicationName"/>();
		_<xsl:value-of select="$ApplicationName"/>-&gt;setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(_<xsl:value-of select="$ApplicationName"/>, lb_I_Unknown, impl)
	}
	
	lb_I_Unknown* r = impl.getPtr();
	impl.resetPtr();
	return r;
}

void LB_STDCALL lbPlugin<xsl:value-of select="$ApplicationName"/>::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (impl != NULL) {
		impl-&gt;release(__FILE__, __LINE__);
		impl.resetPtr();
	}
}

class lbServerModul : public lb_I_ApplicationServerModul {
public:
	lbServerModul();
	virtual ~lbServerModul();
	
	DECLARE_LB_UNKNOWN()
	
	virtual void LB_STDCALL initialize();

	DECLARE_PLUGINS()
	
	char* LB_STDCALL getServiceName();
	void LB_STDCALL registerModul(lb_I_ProtocolManager* pMgr, char* serverInstance);

	void LB_STDCALL install();
private:
	UAP(lb_I_Container, protocolHandlers)
	UAP(lb_I_Container, protocolHandlerInstances)
	
	char* LB_STDCALL getModuleName();
};

IMPLEMENT_FUNCTOR(instanceOfPluginServerModule, lbServerModul)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbServerModul)
	ADD_INTERFACE(lb_I_ApplicationServerModul)
END_IMPLEMENT_LB_UNKNOWN()

BEGIN_PLUGINS(lbServerModul)
	ADD_PLUGIN(lbPlugin<xsl:value-of select="$ApplicationName"/>,			<xsl:value-of select="$ApplicationName"/>)
END_PLUGINS()

lbServerModul::lbServerModul() {
	ref = STARTREF;
}

lbServerModul::~lbServerModul() {

}

void LB_STDCALL lbServerModul::initialize() {
	enumPlugins();
}

void LB_STDCALL lbServerModul::install() {

}

lbErrCodes LB_STDCALL lbServerModul::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE &lt;&lt; "lbServerModul::setData(...) for <xsl:value-of select="$ApplicationName"/> not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}

char* LB_STDCALL lbServerModul::getModuleName() {
	return "<xsl:value-of select="$ApplicationName"/>";
}

char* LB_STDCALL lbServerModul::getServiceName() {
	return "localhost/<xsl:value-of select="$ApplicationName"/>";
}

void LB_STDCALL lbServerModul::registerModul(lb_I_ProtocolManager* pMgr, char* serverInstance) {
	lbErrCodes err = ERR_NONE;
	_LOG &lt;&lt; "lbServerModul::registerModul(lb_I_ProtocolManager* pMgr) for <xsl:value-of select="$ApplicationName"/> called." LOG_
	initialize();
	
	if (protocolHandlerInstances == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, protocolHandlerInstances)
		protocolHandlerInstances-&gt;setCloning(false);
	} else {
		protocolHandlerInstances-&gt;deleteAll();
	}
	
	protocolHandlers = getPlugins();
	protocolHandlers-&gt;finishIteration();
	
	while (protocolHandlers-&gt;hasMoreElements()) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Plugin, pl)
		UAP(lb_I_Unknown, ukPl)
		UAP(lb_I_ProtocolTarget, pt)
		_LOG &lt;&lt; "Try to register a protocol handler." LOG_
		uk = protocolHandlers-&gt;nextElement();
		
		QI(uk, lb_I_Plugin, pl)
		
		if (pl == NULL) {
			_LOG &lt;&lt; "Error: Element in plugin list has no interface of type lb_I_Plugin (" &lt;&lt; uk-&gt;getClassName() &lt;&lt; ")." LOG_
			continue;
		}

		pl-&gt;initialize();
		ukPl = pl-&gt;getImplementation(); 
		
		if (ukPl == NULL) {
			_LOG &lt;&lt; "Error: Peeked plugin element is NULL" LOG_
			continue;
		}
		
		QI(ukPl, lb_I_ProtocolTarget, pt)
		
		if (pt != NULL) {
			_LOG &lt;&lt; "Register protocols for " &lt;&lt; pt-&gt;getClassName() LOG_
			pt-&gt;registerProtocols(*&amp;pMgr, serverInstance);
			//Ensure lifetime hold by plugin implementation and thus by this class.
			UAP_REQUEST(getModuleInstance(), lb_I_String, pluginName)
			UAP(lb_I_KeyBase, PluginKey)
			*pluginName = ukPl-&gt;getClassName();
			QI(pluginName, lb_I_KeyBase, PluginKey)
			protocolHandlerInstances-&gt;insert(&amp;ukPl, &amp;PluginKey);
		} else {
			_LOG &lt;&lt; "Have not got an interface of type lb_I_ProtocolTarget." LOG_
		}
	}
}
</xsl:template>
</xsl:stylesheet>
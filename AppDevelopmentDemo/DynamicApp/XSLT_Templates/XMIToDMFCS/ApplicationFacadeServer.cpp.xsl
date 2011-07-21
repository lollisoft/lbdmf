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
<xsl:template name="ApplicationFacadeServer.cpp">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="ApplicationName"/>
	<xsl:param name="FormularID"/>/*
	Automatically created file. Do not modify.
 */
 
#include &lt;lbConfigHook.h&gt;
#include &lt;lbInterfaces-sub-Project.h&gt;

#include &lt;I<xsl:value-of select="$ApplicationName"/>.h&gt;

#undef DLLEXPORT

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif
#ifdef LINUX 
#define DLLEXPORT
#endif

#include &lt;<xsl:value-of select="$ApplicationName"/>_FacadeServer.h&gt;
<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']">
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
<xsl:variable name="FormularID">
<xsl:value-of select="./@xmi:id"/>
</xsl:variable>
#include &lt;<xsl:value-of select="$FormularName"/>Entity.h&gt;
</xsl:for-each>

IMPLEMENT_FUNCTOR(instanceOf<xsl:value-of select="$ApplicationName"/>, <xsl:value-of select="$ApplicationName"/>)

BEGIN_IMPLEMENT_LB_UNKNOWN(<xsl:value-of select="$ApplicationName"/>)
	ADD_INTERFACE(lb_I_ProtocolTarget)
	ADD_INTERFACE(lb_I_<xsl:value-of select="$ApplicationName"/>_ProtocolTarget)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE &lt;&lt; "<xsl:value-of select="$ApplicationName"/>::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

<xsl:value-of select="$ApplicationName"/>::<xsl:value-of select="$ApplicationName"/>() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_String, ServerInstance)
}

<xsl:value-of select="$ApplicationName"/>::~<xsl:value-of select="$ApplicationName"/>() {

}

char* <xsl:value-of select="$ApplicationName"/>::getServiceName() {
        return "localhost/<xsl:value-of select="$ApplicationName"/>";
}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::registerProtocols(lb_I_ProtocolManager* protoMgr, const char* serverInstance) {
		_LOG &lt;&lt; "lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::registerProtocols(lb_I_ProtocolManager* protoMgr)" LOG_

		UAP_REQUEST(getModuleInstance(), lb_I_String, protocolScope)
		
		*ServerInstance = serverInstance;

<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']">
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
<xsl:variable name="FormularID">
<xsl:value-of select="./@xmi:id"/>
</xsl:variable>


		<xsl:choose>
				<xsl:when test="./xmi:Extension/stereotype[@name='form']">
		*protocolScope = serverInstance;
		*protocolScope += ".";
		*protocolScope += getClassName();
		*protocolScope += ".";
		*protocolScope += "open_<xsl:value-of select="@name"/>";
        protoMgr->addProtocolHandler(protocolScope->charrep(), this, (lbProtocolCallback) &amp;ApplicationBus::_open_<xsl:value-of select="@name"/>);

		*protocolScope = serverInstance;
		*protocolScope += ".";
		*protocolScope += getClassName();
		*protocolScope += ".";
		*protocolScope += "close_<xsl:value-of select="@name"/>";
        protoMgr->addProtocolHandler(protocolScope->charrep(), this, (lbProtocolCallback) &amp;ApplicationBus::_close_<xsl:value-of select="@name"/>);


		*protocolScope = serverInstance;
		*protocolScope += ".";
		*protocolScope += getClassName();
		*protocolScope += ".";
		*protocolScope += "first_<xsl:value-of select="@name"/>";
        protoMgr->addProtocolHandler(protocolScope->charrep(), this, (lbProtocolCallback) &amp;ApplicationBus::_first_<xsl:value-of select="@name"/>);

		
		*protocolScope = serverInstance;
		*protocolScope += ".";
		*protocolScope += getClassName();
		*protocolScope += ".";
		*protocolScope += "previous_<xsl:value-of select="@name"/>";
        protoMgr->addProtocolHandler(protocolScope->charrep(), this, (lbProtocolCallback) &amp;ApplicationBus::_previous_<xsl:value-of select="@name"/>);


		*protocolScope = serverInstance;
		*protocolScope += ".";
		*protocolScope += getClassName();
		*protocolScope += ".";
		*protocolScope += "next_<xsl:value-of select="@name"/>";
        protoMgr->addProtocolHandler(protocolScope->charrep(), this, (lbProtocolCallback) &amp;ApplicationBus::_next_<xsl:value-of select="@name"/>);

		
		*protocolScope = serverInstance;
		*protocolScope += ".";
		*protocolScope += getClassName();
		*protocolScope += ".";
		*protocolScope += "last_<xsl:value-of select="@name"/>";
        protoMgr->addProtocolHandler(protocolScope->charrep(), this, (lbProtocolCallback) &amp;ApplicationBus::_last_<xsl:value-of select="@name"/>);


		*protocolScope = serverInstance;
		*protocolScope += ".";
		*protocolScope += getClassName();
		*protocolScope += ".";
		*protocolScope += "get_<xsl:value-of select="@name"/>";
        protoMgr->addProtocolHandler(protocolScope->charrep(), this, (lbProtocolCallback) &amp;ApplicationBus::_get_<xsl:value-of select="@name"/>);

		
		*protocolScope = serverInstance;
		*protocolScope += ".";
		*protocolScope += getClassName();
		*protocolScope += ".";
		*protocolScope += "put_<xsl:value-of select="@name"/>";
        protoMgr->addProtocolHandler(protocolScope->charrep(), this, (lbProtocolCallback) &amp;ApplicationBus::_put_<xsl:value-of select="@name"/>);


		*protocolScope = serverInstance;
		*protocolScope += ".";
		*protocolScope += getClassName();
		*protocolScope += ".";
		*protocolScope += "put_<xsl:value-of select="@name"/>";
        protoMgr->addProtocolHandler(protocolScope->charrep(), this, (lbProtocolCallback) &amp;ApplicationBus::_put_<xsl:value-of select="@name"/>);


		*protocolScope = serverInstance;
		*protocolScope += ".";
		*protocolScope += getClassName();
		*protocolScope += ".";
		*protocolScope += "getAll_<xsl:value-of select="@name"/>";
        protoMgr->addProtocolHandler(protocolScope->charrep(), this, (lbProtocolCallback) &amp;ApplicationBus::_getAll_<xsl:value-of select="@name"/>);


		*protocolScope = serverInstance;
		*protocolScope += ".";
		*protocolScope += getClassName();
		*protocolScope += ".";
		*protocolScope += "getAll_<xsl:value-of select="@name"/>";
        protoMgr->addProtocolHandler(protocolScope->charrep(), this, (lbProtocolCallback) &amp;ApplicationBus::_getAll_<xsl:value-of select="@name"/>);
		
				</xsl:when>
			</xsl:choose>
		</xsl:for-each>
}

<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']">
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
<xsl:variable name="FormularID">
<xsl:value-of select="./@xmi:id"/>
</xsl:variable>


		<xsl:choose>
				<xsl:when test="./xmi:Extension/stereotype[@name='form']">
lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::_open_<xsl:value-of select="@name"/>(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result) {
	LB_PACKET_TYPE type;
    lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, protocolScope)
		
	*protocolScope = ServerInstance;
	*protocolScope += ".<xsl:value-of select="$ApplicationName"/>";
	*protocolScope += ".open_<xsl:value-of select="@name"/>";

	
	UAP(lb_I_String, backend)


	unsigned long pid = 0;
	unsigned long tid = 0;

/*...sfindBackend proto:0:*/
/*
	add("open_<xsl:value-of select="@name"/>")
	add("Your open_<xsl:value-of select="@name"/> message");
*/
/*...e*/

	if (request->requestString(protocolScope->charrep()) != ERR_NONE) {
		result->makeProtoErrAnswer("Error: open_<xsl:value-of select="@name"/> function identifer not sent", "<xsl:value-of select="$ApplicationName"/>::open_<xsl:value-of select="@name"/>(...)");
		return ERR_TRANSFER_PROTOCOL;
	}

	open_<xsl:value-of select="@name"/>();

    return err;
}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::open_<xsl:value-of select="@name"/>() {
	setLogEnabled(true);
	_CL_LOG &lt;&lt; "<xsl:value-of select="$ApplicationName"/>::open_<xsl:value-of select="@name"/>() called." LOG_
	setLogEnabled(false);
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::_close_<xsl:value-of select="@name"/>(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result) {
	LB_PACKET_TYPE type;
    lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, protocolScope)
		
	*protocolScope = ServerInstance;
	*protocolScope += ".<xsl:value-of select="$ApplicationName"/>";
	*protocolScope += ".close_<xsl:value-of select="@name"/>";

	
	UAP(lb_I_String, backend)


	unsigned long pid = 0;
	unsigned long tid = 0;

/*...sfindBackend proto:0:*/
/*
	add("close_<xsl:value-of select="@name"/>")
	add("Your close_<xsl:value-of select="@name"/> message");
*/
/*...e*/

	if (request->requestString(protocolScope->charrep()) != ERR_NONE) {
		result->makeProtoErrAnswer("Error: close_<xsl:value-of select="@name"/> function identifer not sent", "<xsl:value-of select="$ApplicationName"/>::close_<xsl:value-of select="@name"/>(...)");
		return ERR_TRANSFER_PROTOCOL;
	}

	close_<xsl:value-of select="@name"/>();

    return err;
}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::close_<xsl:value-of select="@name"/>() {
	setLogEnabled(true);
	_CL_LOG &lt;&lt; "<xsl:value-of select="$ApplicationName"/>::open_<xsl:value-of select="@name"/>() called." LOG_
	setLogEnabled(false);
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::_first_<xsl:value-of select="@name"/>(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result) {

}

lb_I_<xsl:value-of select="@name"/>* LB_STDCALL <xsl:value-of select="$ApplicationName"/>::first_<xsl:value-of select="@name"/>() {
	setLogEnabled(true);
	_CL_LOG &lt;&lt; "<xsl:value-of select="$ApplicationName"/>::open_<xsl:value-of select="@name"/>() called." LOG_
	setLogEnabled(false);

	<xsl:value-of select="@name"/>Entity* entity = new <xsl:value-of select="@name"/>Entity();
	entity-&gt;setManager(getModuleInstance(), __FILE__, __LINE__);
	lb_I_<xsl:value-of select="@name"/>Entity* e;
	entity->queryInterface("lb_I_<xsl:value-of select="@name"/>", (void**) &amp;e, __FILE__, __LINE__);
	
	return e;
}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::_previous_<xsl:value-of select="@name"/>(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result) {

}

lb_I_<xsl:value-of select="@name"/>* LB_STDCALL <xsl:value-of select="$ApplicationName"/>::previous_<xsl:value-of select="@name"/>() {
	setLogEnabled(true);
	_CL_LOG &lt;&lt; "<xsl:value-of select="$ApplicationName"/>::open_<xsl:value-of select="@name"/>() called." LOG_
	setLogEnabled(false);

	<xsl:value-of select="@name"/>Entity* entity = new <xsl:value-of select="@name"/>Entity();
	entity-&gt;setManager(getModuleInstance(), __FILE__, __LINE__);
	lb_I_<xsl:value-of select="@name"/>Entity* e;
	entity->queryInterface("lb_I_<xsl:value-of select="@name"/>", (void**) &amp;e, __FILE__, __LINE__);
	
	return e;
}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::_next_<xsl:value-of select="@name"/>(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result) {

}

lb_I_<xsl:value-of select="@name"/>* LB_STDCALL <xsl:value-of select="$ApplicationName"/>::next_<xsl:value-of select="@name"/>() {
	setLogEnabled(true);
	_CL_LOG &lt;&lt; "<xsl:value-of select="$ApplicationName"/>::open_<xsl:value-of select="@name"/>() called." LOG_
	setLogEnabled(false);

	<xsl:value-of select="@name"/>Entity* entity = new <xsl:value-of select="@name"/>Entity();
	entity-&gt;setManager(getModuleInstance(), __FILE__, __LINE__);
	lb_I_<xsl:value-of select="@name"/>Entity* e;
	entity->queryInterface("lb_I_<xsl:value-of select="@name"/>", (void**) &amp;e, __FILE__, __LINE__);
	
	return e;
}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::_last_<xsl:value-of select="@name"/>(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result) {

}

lb_I_<xsl:value-of select="@name"/>* LB_STDCALL <xsl:value-of select="$ApplicationName"/>::last_<xsl:value-of select="@name"/>() {
	setLogEnabled(true);
	_CL_LOG &lt;&lt; "<xsl:value-of select="$ApplicationName"/>::open_<xsl:value-of select="@name"/>() called." LOG_
	setLogEnabled(false);

	<xsl:value-of select="@name"/>Entity* entity = new <xsl:value-of select="@name"/>Entity();
	entity-&gt;setManager(getModuleInstance(), __FILE__, __LINE__);
	lb_I_<xsl:value-of select="@name"/>Entity* e;
	entity->queryInterface("lb_I_<xsl:value-of select="@name"/>", (void**) &amp;e, __FILE__, __LINE__);
	
	return e;
}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::_get_<xsl:value-of select="@name"/>(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result) {

}

lb_I_<xsl:value-of select="@name"/>* LB_STDCALL <xsl:value-of select="$ApplicationName"/>::get_<xsl:value-of select="@name"/>(lb_I_Integer* ID) {
	setLogEnabled(true);
	_CL_LOG &lt;&lt; "<xsl:value-of select="$ApplicationName"/>::open_<xsl:value-of select="@name"/>() called." LOG_
	setLogEnabled(false);

	<xsl:value-of select="@name"/>Entity* entity = new <xsl:value-of select="@name"/>Entity();
	entity-&gt;setManager(getModuleInstance(), __FILE__, __LINE__);
	lb_I_<xsl:value-of select="@name"/>Entity* e;
	entity->queryInterface("lb_I_<xsl:value-of select="@name"/>", (void**) &amp;e, __FILE__, __LINE__);
	
	return e;
}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::_put_<xsl:value-of select="@name"/>(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result) {

}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::put_<xsl:value-of select="@name"/>(lb_I_<xsl:value-of select="@name"/>* entity) {

}

lbErrCodes LB_STDCALL _put_<xsl:value-of select="@name"/>(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result) {

}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>::put_<xsl:value-of select="@name"/>(lb_I_Container* entities) {

}

lbErrCodes LB_STDCALL _getAll_<xsl:value-of select="@name"/>(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result) {

}

lb_I_Container* LB_STDCALL <xsl:value-of select="$ApplicationName"/>::getAll_<xsl:value-of select="@name"/>(lb_I_Integer* offset, lb_I_Integer* amount) {

}

lbErrCodes LB_STDCALL _getAll_<xsl:value-of select="@name"/>(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result) {

}

lb_I_Container* LB_STDCALL <xsl:value-of select="$ApplicationName"/>::getAll_<xsl:value-of select="@name"/>(lb_I_String* searchOnColumn, lb_I_String* searchCriteria) {

}
				</xsl:when>
			</xsl:choose>
		</xsl:for-each>

</xsl:template>


<xsl:template name="PutEntity">
	<xsl:param name="ApplicationName"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormularName"/>
	<xsl:param name="FunctionName"/>
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)
	
	
	ABSConnection-&gt;gethostname(*&amp;temp);
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, user_info)
	
	user_info-&gt;setServerSide(0);
	result-&gt;setServerSide(0);
	
	
	user_info-&gt;setClientPid(lbGetCurrentProcessId());
	user_info-&gt;setClientTid(lbGetCurrentThreadId());

	UAP_REQUEST(getModuleInstance(), lb_I_String, requestString)
	
	*requestString = serverInstance-&gt;charrep();
	*requestString += ".<xsl:value-of select="$ApplicationName"/>.<xsl:value-of select="$FunctionName"/>";
	
	user_info-&gt;add(requestString-&gt;charrep());

	// Code to map additional parameters
<xsl:for-each select="//packagedElement[@xmi:id=$FormularID]/ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="backendType"><xsl:call-template name="MapType"/></xsl:variable>
<xsl:if test="$backendType!='lb_I_Collection'">
<xsl:if test="@name!=''">	UAP(<xsl:value-of select="$backendType"/>, <xsl:value-of select="@name"/>)
</xsl:if>
</xsl:if>
</xsl:for-each>

	// Map values
<xsl:for-each select="//packagedElement[@xmi:id=$FormularID]/ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="backendType"><xsl:call-template name="MapType"/></xsl:variable>
<xsl:choose>
<xsl:when test="$backendType='lb_I_Collection'">
</xsl:when>
<xsl:when test="$backendType='lb_I_String'">
<xsl:if test="@name!=''">
<xsl:value-of select="'    '"/><xsl:value-of select="@name"/> = entity-&gt;get_<xsl:value-of select="@name"/>();
	
	if (<xsl:value-of select="@name"/> != NULL) {
		user_info-&gt;add("<xsl:value-of select="@name"/>");
		user_info-&gt;add(<xsl:value-of select="@name"/>-&gt;charrep());
	}
</xsl:if>
</xsl:when>
<xsl:when test="$backendType='lb_I_Integer'">
<xsl:if test="@name!=''">
<xsl:value-of select="'    '"/><xsl:value-of select="@name"/> = entity-&gt;get_<xsl:value-of select="@name"/>();
	
	if (<xsl:value-of select="@name"/> != NULL) {
		user_info-&gt;add("<xsl:value-of select="@name"/>");
		user_info-&gt;add((int) <xsl:value-of select="@name"/>-&gt;getData());
	}
</xsl:if>
</xsl:when>
</xsl:choose>
</xsl:for-each>

	// Code to send the request
	
	ABSConnection-&gt;init(NULL);
	
	*ABSConnection &lt;&lt; *&amp;user_info;
	
	if (ABSConnection-&gt;getLastError() != ERR_NONE) {
	    _LOG &lt;&lt; "Error in sending <xsl:value-of select="$FunctionName"/> data" LOG_
	}
	
	*ABSConnection &gt;&gt; *&amp;result;

	if (ABSConnection-&gt;getLastError() != ERR_NONE) {
	    _LOG &lt;&lt; "Error in recieving <xsl:value-of select="$FunctionName"/> answer" LOG_
	}

	ABSConnection-&gt;close();
</xsl:template>

<xsl:template name="RequestEntity">
	<xsl:param name="ApplicationName"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormularName"/>
	<xsl:param name="FunctionName"/>
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)
	
	
	ABSConnection-&gt;gethostname(*&amp;temp);
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, user_info)
	
	user_info-&gt;setServerSide(0);
	result-&gt;setServerSide(0);
	
	
	user_info-&gt;setClientPid(lbGetCurrentProcessId());
	user_info-&gt;setClientTid(lbGetCurrentThreadId());

	UAP_REQUEST(getModuleInstance(), lb_I_String, requestString)
	
	*requestString = serverInstance-&gt;charrep();
	*requestString += ".<xsl:value-of select="$ApplicationName"/>.<xsl:value-of select="$FunctionName"/>";
	
	user_info-&gt;add(requestString-&gt;charrep());

	// Code to map additional parameters

	// Code to send the request
	
	ABSConnection-&gt;init(NULL);
	
	*ABSConnection &lt;&lt; *&amp;user_info;
	
	if (ABSConnection-&gt;getLastError() != ERR_NONE) {
	    _LOG &lt;&lt; "Error in sending <xsl:value-of select="$FunctionName"/> data" LOG_
	}
	
	*ABSConnection &gt;&gt; *&amp;result;

	if (ABSConnection-&gt;getLastError() != ERR_NONE) {
	    _LOG &lt;&lt; "Error in recieving <xsl:value-of select="$FunctionName"/> answer" LOG_
	}

	ABSConnection-&gt;close();
	
	// Code to read back data
<xsl:for-each select="//packagedElement[@xmi:id=$FormularID]/ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="backendType"><xsl:call-template name="MapType"/></xsl:variable>
<xsl:if test="$backendType!='lb_I_Collection'">
<xsl:if test="@name!=''">
	UAP_REQUEST(getModuleInstance(), <xsl:value-of select="$backendType"/>, <xsl:value-of select="@name"/>)
</xsl:if>
</xsl:if>
</xsl:for-each>
<xsl:for-each select="//packagedElement[@xmi:id=$FormularID]/ownedAttribute[@xmi:type='uml:Property']">

<xsl:variable name="backendType"><xsl:call-template name="MapType"/></xsl:variable>
<xsl:choose>
<xsl:when test="$backendType='lb_I_Collection'">
</xsl:when>
<xsl:when test="$backendType='lb_I_String'">
<xsl:if test="@name!=''">
	char* _<xsl:value-of select="@name"/> = NULL;
	if (result-&gt;requestString("<xsl:value-of select="@name"/>", _<xsl:value-of select="@name"/>) != ERR_NONE) {
		_LOG &lt;&lt; "Error in recieving parameter from <xsl:value-of select="$FunctionName"/>. Parameter '<xsl:value-of select="@name"/>' wrong or not given." LOG_
	}
</xsl:if>
</xsl:when>
<xsl:when test="$backendType='lb_I_Integer'">
<xsl:if test="@name!=''">
	int _<xsl:value-of select="@name"/> = NULL;
	if (result-&gt;requestInteger("<xsl:value-of select="@name"/>", _<xsl:value-of select="@name"/>) != ERR_NONE) {
		_LOG &lt;&lt; "Error in recieving parameter from <xsl:value-of select="$FunctionName"/>. Parameter '<xsl:value-of select="@name"/>' wrong or not given." LOG_
	}
</xsl:if>
</xsl:when>
</xsl:choose>

</xsl:for-each>
	// Code to create the entity instance
	<xsl:value-of select="$FormularName"/>Entity* entity = new <xsl:value-of select="$FormularName"/>Entity();
	entity-&gt;setManager(getModuleInstance(), __FILE__, __LINE__);
	lb_I_<xsl:value-of select="$FormularName"/>Entity* e;
	entity->queryInterface("lb_I_<xsl:value-of select="$FormularName"/>", (void**) &amp;e, __FILE__, __LINE__);

<xsl:for-each select="//packagedElement[@xmi:id=$FormularID]/ownedAttribute[@xmi:type='uml:Property']">

<xsl:variable name="backendType"><xsl:call-template name="MapType"/></xsl:variable>
<xsl:choose>
<xsl:when test="$backendType='lb_I_Collection'">
</xsl:when>
<xsl:when test="$backendType='lb_I_String'">
<xsl:if test="@name!=''">
	UAP_REQUEST(getModuleInstance(), lb_I_String, s_<xsl:value-of select="@name"/>)
	*s_<xsl:value-of select="@name"/> = _<xsl:value-of select="@name"/>;
	if (e-&gt;set_<xsl:value-of select="@name"/>(&amp;*s_<xsl:value-of select="@name"/>) != ERR_NONE) {
		_LOG &lt;&lt; "Failed to set value for <xsl:value-of select="@name"/>." LOG_
	}
</xsl:if>
</xsl:when>
<xsl:when test="$backendType='lb_I_Integer'">
<xsl:if test="@name!=''">
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i_<xsl:value-of select="@name"/>)
	i_<xsl:value-of select="@name"/>-&gt;setData((int) _<xsl:value-of select="@name"/>);
	if (e-&gt;set_<xsl:value-of select="@name"/>(&amp;*i_<xsl:value-of select="@name"/>) != ERR_NONE) {
		_LOG &lt;&lt; "Failed to set value for <xsl:value-of select="@name"/>." LOG_
	}
</xsl:if>
</xsl:when>
</xsl:choose>

</xsl:for-each>

	return e;
</xsl:template>

<xsl:template name="RequestEntityByID">
	<xsl:param name="ApplicationName"/>
	<xsl:param name="FormularName"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FunctionName"/>
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)
	
	
	ABSConnection-&gt;gethostname(*&amp;temp);
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, user_info)
	
	user_info-&gt;setServerSide(0);
	result-&gt;setServerSide(0);
	
	
	user_info-&gt;setClientPid(lbGetCurrentProcessId());
	user_info-&gt;setClientTid(lbGetCurrentThreadId());

	UAP_REQUEST(getModuleInstance(), lb_I_String, requestString)
	
	*requestString = serverInstance-&gt;charrep();
	*requestString += ".<xsl:value-of select="$ApplicationName"/>.<xsl:value-of select="$FunctionName"/>";
	
	user_info-&gt;add(requestString-&gt;charrep());

	// Code to map additional parameters

    user_info->add("id");
    user_info->add(*&amp;ID);

	// Code to send the request
	
	ABSConnection-&gt;init(NULL);
	
	*ABSConnection &lt;&lt; *&amp;user_info;
	
	if (ABSConnection-&gt;getLastError() != ERR_NONE) {
	    _LOG &lt;&lt; "Error in sending <xsl:value-of select="$FunctionName"/> data" LOG_
	}
	
	*ABSConnection &gt;&gt; *&amp;result;

	if (ABSConnection-&gt;getLastError() != ERR_NONE) {
	    _LOG &lt;&lt; "Error in recieving <xsl:value-of select="$FunctionName"/> answer" LOG_
	}

	ABSConnection-&gt;close();
	
	// Code to read back data
<xsl:for-each select="//packagedElement[@xmi:id=$FormularID]/ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="backendType"><xsl:call-template name="MapType"/></xsl:variable>
<xsl:if test="$backendType!='lb_I_Collection'">
<xsl:if test="@name!=''">
	UAP_REQUEST(getModuleInstance(), <xsl:value-of select="$backendType"/>, <xsl:value-of select="@name"/>)
</xsl:if>
</xsl:if>
</xsl:for-each>
<xsl:for-each select="//packagedElement[@xmi:id=$FormularID]/ownedAttribute[@xmi:type='uml:Property']">

<xsl:variable name="backendType"><xsl:call-template name="MapType"/></xsl:variable>
<xsl:choose>
<xsl:when test="$backendType='lb_I_Collection'">
</xsl:when>
<xsl:when test="$backendType='lb_I_String'">
<xsl:if test="@name!=''">
	char* _<xsl:value-of select="@name"/> = NULL;
	if (result-&gt;requestString("<xsl:value-of select="@name"/>", _<xsl:value-of select="@name"/>) != ERR_NONE) {
		_LOG &lt;&lt; "Error in recieving parameter from <xsl:value-of select="$FunctionName"/>. Parameter '<xsl:value-of select="@name"/>' wrong or not given." LOG_
	}
</xsl:if>
</xsl:when>
<xsl:when test="$backendType='lb_I_Integer'">
<xsl:if test="@name!=''">
	int _<xsl:value-of select="@name"/> = NULL;
	if (result-&gt;requestInteger("<xsl:value-of select="@name"/>", _<xsl:value-of select="@name"/>) != ERR_NONE) {
		_LOG &lt;&lt; "Error in recieving parameter from <xsl:value-of select="$FunctionName"/>. Parameter '<xsl:value-of select="@name"/>' wrong or not given." LOG_
	}
</xsl:if>
</xsl:when>
</xsl:choose>

</xsl:for-each>
	// Code to create the entity instance
	<xsl:value-of select="$FormularName"/>Entity* entity = new <xsl:value-of select="$FormularName"/>Entity();
	entity-&gt;setManager(getModuleInstance(), __FILE__, __LINE__);
	lb_I_<xsl:value-of select="$FormularName"/>Entity* e;
	entity->queryInterface("lb_I_<xsl:value-of select="$FormularName"/>", (void**) &amp;e, __FILE__, __LINE__);

<xsl:for-each select="//packagedElement[@xmi:id=$FormularID]/ownedAttribute[@xmi:type='uml:Property']">

<xsl:variable name="backendType"><xsl:call-template name="MapType"/></xsl:variable>
<xsl:choose>
<xsl:when test="$backendType='lb_I_Collection'">
</xsl:when>
<xsl:when test="$backendType='lb_I_String'">
<xsl:if test="@name!=''">
	UAP_REQUEST(getModuleInstance(), lb_I_String, s_<xsl:value-of select="@name"/>)
	*s_<xsl:value-of select="@name"/> = _<xsl:value-of select="@name"/>;
	if (e-&gt;set_<xsl:value-of select="@name"/>(&amp;*s_<xsl:value-of select="@name"/>) != ERR_NONE) {
		_LOG &lt;&lt; "Failed to set value for <xsl:value-of select="@name"/>." LOG_
	}
</xsl:if>
</xsl:when>
<xsl:when test="$backendType='lb_I_Integer'">
<xsl:if test="@name!=''">
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i_<xsl:value-of select="@name"/>)
	i_<xsl:value-of select="@name"/>-&gt;setData((int) _<xsl:value-of select="@name"/>);
	if (e-&gt;set_<xsl:value-of select="@name"/>(&amp;*i_<xsl:value-of select="@name"/>) != ERR_NONE) {
		_LOG &lt;&lt; "Failed to set value for <xsl:value-of select="@name"/>." LOG_
	}
</xsl:if>
</xsl:when>
</xsl:choose>

</xsl:for-each>

	return e;
</xsl:template>

</xsl:stylesheet>
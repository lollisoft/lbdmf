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
<xsl:template name="Proxy.cpp">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>/*
	Automatically created file. Do not modify.
 */

#include &lt;lbConfigHook.h&gt;
#include &lt;lbInterfaces-sub-Project.h&gt;

#undef DLLEXPORT

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif
#ifdef LINUX 
#define DLLEXPORT
#endif



#include &lt;I<xsl:value-of select="$FormName"/>.h&gt;

/** \brief class <xsl:value-of select="$FormName"/>.
 * Documentation for <xsl:value-of select="$FormName"/>
 */

IMPLEMENT_FUNCTOR(instanceOf<xsl:value-of select="$FormName"/>Proxy, <xsl:value-of select="$FormName"/>)

BEGIN_IMPLEMENT_LB_UNKNOWN(<xsl:value-of select="$FormName"/>)
        ADD_INTERFACE(lb_I_<xsl:value-of select="$FormName"/>)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbDMFCS_<xsl:value-of select="$FormName"/>_Proxy::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE &lt;&lt; "lbDMFCS_<xsl:value-of select="$FormName"/>_Proxy::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

lbDMFCS_<xsl:value-of select="$FormName"/>_Proxy::lbDMFCS_<xsl:value-of select="$FormName"/>_Proxy() {
	ref = STARTREF;
	_CL_LOG &lt;&lt; "Init lbDMFCS_<xsl:value-of select="$FormName"/>_Proxy" LOG_
	
	REQUEST(getModuleInstance(), lb_I_String, serverInstance)
	
    if (ABSConnection == NULL) {
        /**
         * Initialize the tcp connection...
         */

        REQUEST(getModuleInstance(), lb_I_Transfer, ABSConnection)
        
		// The name of the lbDMF Busmaster must be defined in hosts or DNS
        ABSConnection-&gt;init("busmaster/busmaster");
        Connect();
		ABSConnection-&gt;close();
    }
    _LOG &lt;&lt; "lbDMFCS_<xsl:value-of select="$FormName"/>_Proxy Initialized" LOG_
}

lbDMFCS_<xsl:value-of select="$FormName"/>_Proxy::~lbDMFCS_<xsl:value-of select="$FormName"/>_Proxy() {

}

//\todo Remove as it is unused.
int lbDMFCS_<xsl:value-of select="$FormName"/>_Proxy::Connect() {
	char* answer;
	char buf[100] = "";
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, client)
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)
	client-&gt;setServerSide(0);
	result-&gt;setServerSide(0);
	
	ABSConnection-&gt;gethostname(*&amp;temp);
	
	client-&gt;add("Connect");
	client-&gt;add("Host");
	client-&gt;add(temp-&gt;charrep());
	client-&gt;add("Pid");
	client-&gt;add(lbGetCurrentProcessId());
	client-&gt;add("Tid");
	client-&gt;add(lbGetCurrentThreadId());

	_LOG &lt;&lt; "Client sends the packets..." LOG_
    *ABSConnection &lt;&lt; *&amp;client;
	_LOG &lt;&lt; "Client waits for answer..." LOG_
    *ABSConnection &gt;&gt; *&amp;result;
	_LOG &lt;&lt; "Connect returns with an answer..." LOG_
	// Handle the request
	int count = result-&gt;getPacketCount();

	result-&gt;resetPositionCount();
		
	while (count--) {
		LB_PACKET_TYPE type;
		int i = 0;
		char *buffer;
		char msg[100];
		result-&gt;getPacketType(type);

		switch (type) {
			case PACKET_LB_CHAR:
				result-&gt;get(buffer);
				
				if (strcmp(buffer, "Accept") == 0) {
					connected = true;
					_LOG &lt;&lt; "Connection accepted." LOG_
					result-&gt;incrementPosition();
					result-&gt;get(buffer);
					if (strcmp(buffer, "InstanceName") == 0) {
						result-&gt;incrementPosition();
						result-&gt;get(buffer);
						*serverInstance = buffer;
						_LOG &lt;&lt; "Have server instanve = " &lt;&lt; serverInstance-&gt;charrep() LOG_
						return 1;
					}
				}
				break;
				
			default:
				_LOG &lt;&lt; "Unknown packet type!" LOG_
				
				break;
		}
			
		result-&gt;incrementPosition();
	}

	_LOG &lt;&lt; "Connection failed!" LOG_
	connected = false;
                
	return 0;
}

int lbDMFCS_<xsl:value-of select="$FormName"/>_Proxy::Disconnect() {
	char* answer;
	char buf[100] = "";
	lb_I_Transfer_Data* result;

	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, client)

	client-&gt;add("Disconnect");
	client-&gt;add("Host");
	client-&gt;add("anakin");

    *ABSConnection &lt;&lt; *&amp;client;
    *ABSConnection &gt;&gt; *&amp;result;

	int count = result-&gt;getPacketCount();

	result-&gt;resetPositionCount();
		
	while (count--) {
		LB_PACKET_TYPE type;
		int i = 0;
		char *buffer;
		char msg[100];
		result-&gt;getPacketType(type);

		switch (type) {
			case PACKET_LB_CHAR:
				result-&gt;get(buffer);
				
				if (strcmp(buffer, "Succeed") == 0) {
					_CL_LOG &lt;&lt; "Disconnected successfull" LOG_
					connected = 0;
					return 1;
				} else {
					_CL_LOG &lt;&lt; "Disconnection failed!" LOG_
					return 0;
				}
				
				break;
				
			default:
				_CL_LOG &lt;&lt; "Unknown packet type!" LOG_
				
				break;
		}
			
		result-&gt;incrementPosition();
	}
                
    return 1;
}

 
<xsl:for-each select="//packagedElement[@xmi:id=$FormularID]/ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="backendType"><xsl:call-template name="MapType"/></xsl:variable>
<xsl:value-of select="$backendType"/>* lbDMFCS_<xsl:value-of select="$FormName"/>_Proxy::get_<xsl:value-of select="@name"/>() {

}

lbErrCodes lbDMFCS_<xsl:value-of select="$FormName"/>_Proxy::set_<xsl:value-of select="@name"/>(<xsl:value-of select="$backendType"/>* value) {

}

</xsl:for-each>
</xsl:template>
</xsl:stylesheet>
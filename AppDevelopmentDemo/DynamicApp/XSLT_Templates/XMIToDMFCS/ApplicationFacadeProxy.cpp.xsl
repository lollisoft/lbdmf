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
<xsl:template name="ApplicationFacadeProxy.cpp">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="ApplicationName"/>
	<xsl:param name="FormularID"/>/*
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

#include &lt;I<xsl:value-of select="$ApplicationName"/>_Entities.h&gt;
#include &lt;I<xsl:value-of select="$ApplicationName"/>.h&gt;

#include &lt;<xsl:value-of select="$ApplicationName"/>_FacadeProxy.h&gt;
#include &lt;<xsl:value-of select="$ApplicationName"/>_Entities.h&gt;

IMPLEMENT_FUNCTOR(instanceOf<xsl:value-of select="$ApplicationName"/>FacadeProxy, <xsl:value-of select="$ApplicationName"/>FacadeProxy)

BEGIN_IMPLEMENT_LB_UNKNOWN(<xsl:value-of select="$ApplicationName"/>FacadeProxy)
        ADD_INTERFACE(lb_I_<xsl:value-of select="$ApplicationName"/>)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>FacadeProxy::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE &lt;&lt; "<xsl:value-of select="$ApplicationName"/>FacadeProxy::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

<xsl:value-of select="$ApplicationName"/>FacadeProxy::<xsl:value-of select="$ApplicationName"/>FacadeProxy() {
	ref = STARTREF;
	_CL_LOG &lt;&lt; "Init <xsl:value-of select="$ApplicationName"/>FacadeProxy" LOG_
	
	REQUEST(getModuleInstance(), lb_I_String, ServerInstance)
	
    if (ABSConnection == NULL) {
        /**
         * Find the backend...
         */
		UAP_REQUEST(getModuleInstance(), lb_I_String, backend)
		UAP_REQUEST(getModuleInstance(), lb_I_ApplicationBus, applicationbus)

		backend = applicationbus->findBackend("<xsl:value-of select="$ApplicationName"/>");
		
        
        if (backend != NULL) {
			REQUEST(getModuleInstance(), lb_I_Transfer, ABSConnection)
			ABSConnection-&gt;init(backend->charrep());
			Connect();
			ABSConnection-&gt;close();
		} else {
			setLogActivated(true);
			_CL_LOG &lt;&lt; "<xsl:value-of select="$ApplicationName"/>FacadeProxy did not got backend address" LOG_
			_LOG &lt;&lt; "<xsl:value-of select="$ApplicationName"/>FacadeProxy did not got backend address" LOG_
			setLogActivated(false);
		}
    }
    _LOG &lt;&lt; "<xsl:value-of select="$ApplicationName"/>FacadeProxy Initialized" LOG_
}

<xsl:value-of select="$ApplicationName"/>FacadeProxy::~<xsl:value-of select="$ApplicationName"/>FacadeProxy() {

}

//\todo Remove as it is unused.
int <xsl:value-of select="$ApplicationName"/>FacadeProxy::Connect() {
	char* answer;
	char buf[100] = "";
	
	if (ABSConnection == NULL)
		return 0;
	
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
						*ServerInstance = buffer;
						_LOG &lt;&lt; "Have server instanve = " &lt;&lt; ServerInstance-&gt;charrep() LOG_
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

int <xsl:value-of select="$ApplicationName"/>FacadeProxy::Disconnect() {
	char* answer;
	char buf[100] = "";
	lb_I_Transfer_Data* result;

	if (ABSConnection == NULL)
		return 0;

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
lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>FacadeProxy::open_<xsl:value-of select="@name"/>() {
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)
	
	if (ABSConnection == NULL)
		return ERR_NOT_CONNECTED;

	ABSConnection-&gt;gethostname(*&amp;temp);
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, user_info)
	
	user_info-&gt;setServerSide(0);
	result-&gt;setServerSide(0);
	
	
	user_info-&gt;setClientPid(lbGetCurrentProcessId());
	user_info-&gt;setClientTid(lbGetCurrentThreadId());

	UAP_REQUEST(getModuleInstance(), lb_I_String, requestString)
	
	*requestString = ServerInstance-&gt;charrep();
	*requestString += ".<xsl:value-of select="$ApplicationName"/>.open_<xsl:value-of select="@name"/>";
	
	user_info-&gt;add(requestString-&gt;charrep());

	// Code to map additional parameters
	
	// Code to send the request
	
	ABSConnection-&gt;init(NULL);
	
	*ABSConnection &lt;&lt; *&amp;user_info;
	
	if (ABSConnection-&gt;getLastError() != ERR_NONE) {
	    _LOG &lt;&lt; "Error in sending open_<xsl:value-of select="@name"/> data" LOG_
	}
	
	*ABSConnection &gt;&gt; *&amp;result;

	if (ABSConnection-&gt;getLastError() != ERR_NONE) {
	    _LOG &lt;&lt; "Error in recieving open_<xsl:value-of select="@name"/> answer" LOG_
	}

	ABSConnection-&gt;close();
}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>FacadeProxy::close_<xsl:value-of select="@name"/>() {
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)
	
	if (ABSConnection == NULL)
		return ERR_NOT_CONNECTED;
	
	ABSConnection-&gt;gethostname(*&amp;temp);
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, user_info)
	
	user_info-&gt;setServerSide(0);
	result-&gt;setServerSide(0);
	
	
	user_info-&gt;setClientPid(lbGetCurrentProcessId());
	user_info-&gt;setClientTid(lbGetCurrentThreadId());

	UAP_REQUEST(getModuleInstance(), lb_I_String, requestString)
	
	*requestString = ServerInstance-&gt;charrep();
	*requestString += ".<xsl:value-of select="$ApplicationName"/>.close_<xsl:value-of select="@name"/>";
	
	user_info-&gt;add(requestString-&gt;charrep());

	// Code to map additional parameters
	
	// Code to send the request
	
	ABSConnection-&gt;init(NULL);
	
	*ABSConnection &lt;&lt; *&amp;user_info;
	
	if (ABSConnection-&gt;getLastError() != ERR_NONE) {
	    _LOG &lt;&lt; "Error in sending close_<xsl:value-of select="@name"/> data" LOG_
	}
	
	*ABSConnection &gt;&gt; *&amp;result;

	if (ABSConnection-&gt;getLastError() != ERR_NONE) {
	    _LOG &lt;&lt; "Error in recieving close_<xsl:value-of select="@name"/> answer" LOG_
	}

	ABSConnection-&gt;close();
}

lb_I_<xsl:value-of select="@name"/>* LB_STDCALL <xsl:value-of select="$ApplicationName"/>FacadeProxy::first_<xsl:value-of select="@name"/>() {
	if (ABSConnection == NULL)
		return NULL;

<xsl:call-template name="RequestEntity">
		<xsl:with-param name="ApplicationName"><xsl:value-of select="$ApplicationName"/></xsl:with-param>
		<xsl:with-param name="FormularName"><xsl:value-of select="$FormularName"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="./@xmi:id"/></xsl:with-param>
		<xsl:with-param name="FunctionName">first_<xsl:value-of select="@name"/></xsl:with-param>
</xsl:call-template>
}

lb_I_<xsl:value-of select="@name"/>* LB_STDCALL <xsl:value-of select="$ApplicationName"/>FacadeProxy::previous_<xsl:value-of select="@name"/>() {
	if (ABSConnection == NULL)
		return NULL;

<xsl:call-template name="RequestEntity">
		<xsl:with-param name="ApplicationName"><xsl:value-of select="$ApplicationName"/></xsl:with-param>
		<xsl:with-param name="FormularName"><xsl:value-of select="$FormularName"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="./@xmi:id"/></xsl:with-param>
		<xsl:with-param name="FunctionName">previous_<xsl:value-of select="@name"/></xsl:with-param>
</xsl:call-template>
}

lb_I_<xsl:value-of select="@name"/>* LB_STDCALL <xsl:value-of select="$ApplicationName"/>FacadeProxy::next_<xsl:value-of select="@name"/>() {
	if (ABSConnection == NULL)
		return NULL;

<xsl:call-template name="RequestEntity">
		<xsl:with-param name="ApplicationName"><xsl:value-of select="$ApplicationName"/></xsl:with-param>
		<xsl:with-param name="FormularName"><xsl:value-of select="$FormularName"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="./@xmi:id"/></xsl:with-param>
		<xsl:with-param name="FunctionName">next_<xsl:value-of select="@name"/></xsl:with-param>
</xsl:call-template>
}

lb_I_<xsl:value-of select="@name"/>* LB_STDCALL <xsl:value-of select="$ApplicationName"/>FacadeProxy::last_<xsl:value-of select="@name"/>() {
	if (ABSConnection == NULL)
		return NULL;

<xsl:call-template name="RequestEntity">
		<xsl:with-param name="ApplicationName"><xsl:value-of select="$ApplicationName"/></xsl:with-param>
		<xsl:with-param name="FormularName"><xsl:value-of select="$FormularName"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="./@xmi:id"/></xsl:with-param>
		<xsl:with-param name="FunctionName">last_<xsl:value-of select="@name"/></xsl:with-param>
</xsl:call-template>
}

lb_I_<xsl:value-of select="@name"/>* LB_STDCALL <xsl:value-of select="$ApplicationName"/>FacadeProxy::get_<xsl:value-of select="@name"/>(lb_I_Integer* ID) {
	if (ABSConnection == NULL)
		return NULL;

<xsl:call-template name="RequestEntityByID">
		<xsl:with-param name="ApplicationName"><xsl:value-of select="$ApplicationName"/></xsl:with-param>
		<xsl:with-param name="FormularName"><xsl:value-of select="$FormularName"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="./@xmi:id"/></xsl:with-param>
		<xsl:with-param name="FunctionName">last_<xsl:value-of select="@name"/></xsl:with-param>
</xsl:call-template>
}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>FacadeProxy::put_<xsl:value-of select="@name"/>(lb_I_<xsl:value-of select="@name"/>* entity) {
	if (ABSConnection == NULL)
		return ERR_NOT_CONNECTED;

<xsl:call-template name="PutEntity">
		<xsl:with-param name="ApplicationName"><xsl:value-of select="$ApplicationName"/></xsl:with-param>
		<xsl:with-param name="FormularName"><xsl:value-of select="$FormularName"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="./@xmi:id"/></xsl:with-param>
		<xsl:with-param name="FunctionName">put_<xsl:value-of select="@name"/>Entity</xsl:with-param>
</xsl:call-template>
}

lbErrCodes LB_STDCALL <xsl:value-of select="$ApplicationName"/>FacadeProxy::put_<xsl:value-of select="@name"/>(lb_I_Container* entities) {
	if (ABSConnection == NULL)
		return ERR_NOT_CONNECTED;
	return ERR_NONE;
}

lb_I_Container* LB_STDCALL <xsl:value-of select="$ApplicationName"/>FacadeProxy::getAll_<xsl:value-of select="@name"/>(lb_I_Integer* offset, lb_I_Integer* amount) {
	if (ABSConnection == NULL)
		return NULL;

	return NULL;
}

lb_I_Container* LB_STDCALL <xsl:value-of select="$ApplicationName"/>FacadeProxy::getAll_<xsl:value-of select="@name"/>(lb_I_String* searchOnColumn, lb_I_String* searchCriteria) {
	if (ABSConnection == NULL)
		return NULL;

	return NULL;
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
	
	*requestString = ServerInstance-&gt;charrep();
	*requestString += ".<xsl:value-of select="$ApplicationName"/>.<xsl:value-of select="$FunctionName"/>";
	
	user_info-&gt;add(requestString-&gt;charrep());

	// Code to map additional parameters
<xsl:for-each select="//packagedElement[@xmi:id=$FormularID]/ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="backendType"><xsl:call-template name="MapType"/></xsl:variable>
<xsl:if test="$backendType!='lb_I_Collection'">
<xsl:if test="@name!=''">	UAP(<xsl:value-of select="$backendType"/>, _<xsl:value-of select="@name"/>)
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
<xsl:value-of select="'    '"/>_<xsl:value-of select="@name"/> = entity-&gt;get_<xsl:value-of select="@name"/>();
	
	if (_<xsl:value-of select="@name"/> != NULL) {
		user_info-&gt;add("<xsl:value-of select="@name"/>");
		user_info-&gt;add(_<xsl:value-of select="@name"/>-&gt;charrep());
	}
</xsl:if>
</xsl:when>
<xsl:when test="$backendType='lb_I_Integer'">
<xsl:if test="@name!=''">
<xsl:value-of select="'    '"/>_<xsl:value-of select="@name"/> = entity-&gt;get_<xsl:value-of select="@name"/>();
	
	if (_<xsl:value-of select="@name"/> != NULL) {
		user_info-&gt;add("<xsl:value-of select="@name"/>");
		user_info-&gt;add((int) _<xsl:value-of select="@name"/>-&gt;getData());
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
	
	*requestString = ServerInstance-&gt;charrep();
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
	entity-&gt;setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	lb_I_<xsl:value-of select="$FormularName"/>* e;
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
	
	*requestString = ServerInstance-&gt;charrep();
	*requestString += ".<xsl:value-of select="$ApplicationName"/>.<xsl:value-of select="$FunctionName"/>";
	
	user_info-&gt;add(requestString-&gt;charrep());

	// Code to map additional parameters

    user_info->add("id");
    user_info->add((int)ID-&gt;getData());

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
	int _<xsl:value-of select="@name"/> = 0;
	if (result-&gt;requestInteger("<xsl:value-of select="@name"/>", _<xsl:value-of select="@name"/>) != ERR_NONE) {
		_LOG &lt;&lt; "Error in recieving parameter from <xsl:value-of select="$FunctionName"/>. Parameter '<xsl:value-of select="@name"/>' wrong or not given." LOG_
	}
</xsl:if>
</xsl:when>
</xsl:choose>

</xsl:for-each>
	// Code to create the entity instance
	<xsl:value-of select="$FormularName"/>Entity* entity = new <xsl:value-of select="$FormularName"/>Entity();
	entity-&gt;setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	lb_I_<xsl:value-of select="$FormularName"/>* e;
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
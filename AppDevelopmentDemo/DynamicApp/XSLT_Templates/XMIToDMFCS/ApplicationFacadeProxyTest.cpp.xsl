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
<xsl:template name="ApplicationFacadeProxyTest.cpp">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="ApplicationName"/>
	<xsl:param name="FormularID"/>
#include &lt;lbConfigHook.h&gt;
#include &lt;lbinclude.h&gt;
#include &lt;conio.h&gt;
#include &lt;signal.h&gt;

#include &lt;I<xsl:value-of select="$ApplicationName"/>_Entities.h&gt;
#include &lt;I<xsl:value-of select="$ApplicationName"/>.h&gt;

void handler(int sig) {
	COUT &lt;&lt; "Oops..." &lt;&lt; ENDL;
	exit(0);
}

int main(int argc, char** argv) {
	lbErrCodes err = ERR_NONE;
	int count = 0;
	//setLogActivated(true);

	/**
	 * This let the app not crashing. But the handler simply
	 * does exit(0), no cleanup yet ???
	 */
	signal(SIGINT, handler);
	signal(SIGILL, handler);

	{
		UAP_REQUEST(getModuleInstance(), lb_I_String, pre)
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		PM->initialize();
	
		UAP(lb_I_<xsl:value-of select="$ApplicationName"/>, client)
		setLogActivated(true);
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_<xsl:value-of select="$ApplicationName"/>, "Proxy", client, "'application proxy'")
	
		if (client != NULL) {
			_CL_LOG &lt;&lt; "Have got a proxy for lb_I_<xsl:value-of select="$ApplicationName"/>" LOG_
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

		<xsl:choose>
				<xsl:when test="./xmi:Extension/stereotype[@name='form']">
<xsl:call-template name="BasicEntityTests">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationName"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="./@xmi:id"/></xsl:with-param>
		<xsl:with-param name="FormularName"><xsl:value-of select="$FormularName"/></xsl:with-param>
</xsl:call-template>
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:report']">
				</xsl:when>
			</xsl:choose>
		</xsl:for-each>
		} else {
			_CL_LOG &lt;&lt; "Error: Can't find a proxy for lb_I_<xsl:value-of select="$ApplicationName"/>" LOG_
		}
		setLogActivated(false);
		
		PM-&gt;unload();
	}
	
	unHookAll();

	_CL_LOG &lt;&lt; "Ending server test thread" LOG_
	exit(0);
	return 0;
}
</xsl:template>

<xsl:template name="BasicEntityTests">
	<xsl:param name="ApplicationName"/>
	<xsl:param name="FormularName"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FunctionName"/>
			UAP(lb_I_<xsl:value-of select="$FormularName"/>, _<xsl:value-of select="$FormularName"/>)
			
			setLogActivated(false);
			if ((err = client->open_<xsl:value-of select="$FormularName"/>()) == ERR_NONE) {
				_<xsl:value-of select="$FormularName"/> = client->first_<xsl:value-of select="$FormularName"/>();
				if (_<xsl:value-of select="$FormularName"/> == NULL) {
					setLogActivated(true);
					_CL_LOG &lt;&lt; "Error: Can't get first of <xsl:value-of select="$FormularName"/>." LOG_
					setLogActivated(false);
				}
			} else {
				setLogActivated(true);
				_CL_LOG &lt;&lt; "Error: Can't open <xsl:value-of select="$FormularName"/>." LOG_
				if (err == ERR_NOT_CONNECTED) {
					_CL_LOG &lt;&lt; "Error: <xsl:value-of select="$FormularName"/> is not connected." LOG_
				}
				setLogActivated(false);
			}
</xsl:template>

</xsl:stylesheet>
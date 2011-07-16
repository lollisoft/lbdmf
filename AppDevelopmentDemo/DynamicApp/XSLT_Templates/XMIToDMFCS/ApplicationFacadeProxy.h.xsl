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
<xsl:template name="ApplicationFacadeProxy.h">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="ApplicationName"/>
	<xsl:param name="FormularID"/>/** \brief class lb_I_<xsl:value-of select="$ApplicationName"/>.
 * The lb_I_<xsl:value-of select="$ApplicationName"/> interface defines a thin facade around the internals of the application.
 */
class lb_I_<xsl:value-of select="$ApplicationName"/> :
public lb_I_Unknown {
public:
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
	// API for <xsl:value-of select="@name"/>.
	
	/** \brief Open a cursor <xsl:value-of select="@name"/>.
	 * This will open a cursor based mode.
	 */
	lbErrCodes open_<xsl:value-of select="@name"/>() = 0;

	/** \brief Closes a cursor <xsl:value-of select="@name"/>.
	 * This will close a cursor based mode.
	 */
	lbErrCodes close_<xsl:value-of select="@name"/>() = 0;

	/** \brief Navigation <xsl:value-of select="@name"/>.
	 */
	lb_I_<xsl:value-of select="@name"/>* first_<xsl:value-of select="@name"/>() = 0;

	/** \brief Navigation <xsl:value-of select="@name"/>.
	 */
	lb_I_<xsl:value-of select="@name"/>* previous_<xsl:value-of select="@name"/>() = 0;

	/** \brief Navigation <xsl:value-of select="@name"/>.
	 */
	lb_I_<xsl:value-of select="@name"/>* next_<xsl:value-of select="@name"/>() = 0;

	/** \brief Navigation <xsl:value-of select="@name"/>.
	 */
	lb_I_<xsl:value-of select="@name"/>* last_<xsl:value-of select="@name"/>() = 0;

	/** \brief Get one <xsl:value-of select="@name"/> by their ID.
	 * This will be used to edit a specific entiy by their id.
	 */
	lb_I_<xsl:value-of select="@name"/>* get_<xsl:value-of select="@name"/>(lb_I_Integer* ID) = 0;

	/** \brief Store this <xsl:value-of select="@name"/> entity.
	 * This will save the entity.
	 */
	lbErrCodes put_<xsl:value-of select="@name"/>(lb_I_<xsl:value-of select="@name"/>* entity) = 0;

	/** \brief Store these <xsl:value-of select="@name"/> entities.
	 * This will save the entity.
	 */
	lbErrCodes put_<xsl:value-of select="@name"/>(lb_I_Container* entities) = 0;

	/** \brief Get all <xsl:value-of select="@name"/> by offset and amount.
	 * The entities are stored by their ID ad key.
	 */
	lb_I_Container* getAll_<xsl:value-of select="@name"/>(lb_I_Integer* offset, lb_I_Integer* amount) = 0;

	/** \brief Get all <xsl:value-of select="@name"/> by the given search criteria.
	 * The entities are stored by their ID ad key.
	 */
	lb_I_Container* getAll_<xsl:value-of select="@name"/>(lb_I_String* searchOnColumn, lb_I_String* searchCriteria) = 0;
				</xsl:when>
			</xsl:choose>
		</xsl:for-each>
};
</xsl:template>
</xsl:stylesheet>
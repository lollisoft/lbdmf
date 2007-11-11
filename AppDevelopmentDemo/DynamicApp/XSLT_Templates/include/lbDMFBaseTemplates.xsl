<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">

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

<xsl:variable name="ApplicationID" select="//lbDMF/@applicationid"/>
<xsl:variable name="codegenbasedir" select="//lbDMF/applicationparameter/parameter[@applicationid=$ApplicationID][@name='codegenbasedir']/@value"/>
<xsl:variable name="codegentarget" select="//lbDMF/applicationparameter/parameter[@applicationid=$ApplicationID][@name='codegentarget']/@value"/>
<xsl:variable name="basedir">
<xsl:if test="$codegenbasedir=''"><xsl:value-of select="'.'"/></xsl:if>
<xsl:if test="$codegenbasedir!=''"><xsl:value-of select="$codegenbasedir"/></xsl:if>
</xsl:variable>

<xsl:variable name="pluginsdir">
<xsl:choose>
<xsl:when test="$codegentarget!=''">Code/Targets/<xsl:value-of select="$codegentarget"/>/Plugins</xsl:when>
<xsl:otherwise>Code/Targets/wxActiveRecords/Plugins</xsl:otherwise>
</xsl:choose>
</xsl:variable>
<xsl:variable name="appmoduledir">
<xsl:choose>
<xsl:when test="$codegentarget!=''">Code/Targets/<xsl:value-of select="$codegentarget"/>/Modules</xsl:when>
<xsl:otherwise>Code/Targets/wxActiveRecords/Modules</xsl:otherwise>
</xsl:choose>
</xsl:variable>

</xsl:stylesheet>
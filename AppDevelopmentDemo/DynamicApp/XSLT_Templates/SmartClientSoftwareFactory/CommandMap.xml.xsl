<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="exsl.xsl"/>

<xsl:template name="CommandMap.xml">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>&lt;?xml version="1.0" encoding="utf-8" ?&gt;
&lt;CommandMap xmlns="http://schemas.microsoft.com/pag/cab-command-map"&gt;
	&lt;Mapping Site="File"  Label="Show Customer" CommandName="ShowCustomer" /&gt;
	&lt;Mapping Site="File" Label="Disable Show Customer" CommandName="DisableShowCustomer" /&gt;
	&lt;Mapping Site="File" Label="Enable Show Customer" CommandName="EnableShowCustomer" /&gt;
	&lt;Mapping Site="File" Label="Hide Show Customer" CommandName="HideShowCustomer" /&gt;
&lt;/CommandMap&gt;
</xsl:template>
</xsl:stylesheet>
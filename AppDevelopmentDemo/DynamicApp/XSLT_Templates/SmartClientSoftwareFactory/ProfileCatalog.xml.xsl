<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="exsl.xsl"/>

<xsl:template name="ProfileCatalog.xml">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>&lt;?xml version="1.0" encoding="utf-8" ?&gt;
&lt;SolutionProfile xmlns="http://schemas.microsoft.com/pag/cab-profile" &gt;
	&lt;Modules&gt;
		&lt;ModuleInfo AssemblyFile="<xsl:value-of select="$ApplicationName"/>Module.dll" /&gt;
	&lt;/Modules&gt;
&lt;/SolutionProfile&gt;
</xsl:template>
</xsl:stylesheet>
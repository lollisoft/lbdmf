<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="exsl.xsl"/>

<xsl:template name="Settings.settings">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>&lt;?xml version='1.0' encoding='utf-8'?&gt;
&lt;SettingsFile xmlns="http://schemas.microsoft.com/VisualStudio/2004/01/settings" CurrentProfile="(Default)"&gt;
  &lt;Profiles&gt;
    &lt;Profile Name="(Default)" /&gt;
  &lt;/Profiles&gt;
  &lt;Settings /&gt;
&lt;/SettingsFile&gt;
</xsl:template>
</xsl:stylesheet>
<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<!--<xsl:variable name="targetdatabase" select="' '"/>--><!-- Mapped to DefaultDatabaseSystem as in XSLT document defined. -->
<!--<xsl:variable name="targetdatabase" select="'DatabaseLayerGateway'"/>--><!-- Mapped to Sqlite (in XSLT document) -->
<!--<xsl:variable name="targetdatabase" select="'MSSQL'"/>-->
<!--<xsl:variable name="targetdatabase" select="'PostgreSQL'"/>-->
<xsl:variable name="targetdatabase" select="'DatabaseLayerGateway'"/><!-- Mapped from Application Database backend in the properties window group General -->
<xsl:variable name="execute_droprules" select="'yes'"/>
<xsl:variable name="database_name" select="'BankTeller'"/>
<xsl:variable name="database_user" select="'&lt;dbuser&gt;'"/>
<xsl:variable name="database_pass" select="'&lt;dbpass&gt;'"/>
</xsl:stylesheet>

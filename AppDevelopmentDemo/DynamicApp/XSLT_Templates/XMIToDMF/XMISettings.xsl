<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<!--<xsl:variable name="targetdatabase" select="' '"/>--><!-- Mapped to DefaultDatabaseSystem as defined in XSLT document. -->
<!--<xsl:variable name="targetdatabase" select="'DatabaseLayerGateway'"/>--><!-- Mapped to Sqlite (in XSLT document) -->
<!--<xsl:variable name="targetdatabase" select="'MSSQL'"/>-->
<!--<xsl:variable name="targetdatabase" select="'PostgreSQL'"/>-->
<xsl:variable name="targetdatabase" select="'Sqlite'"/><!-- Mapped from system database backend in the properties window group UML import settings -->
<xsl:variable name="execute_droprules" select="'yes'"/>
<xsl:variable name="database_name" select="'CDKatalog'"/>
<xsl:variable name="database_user" select="'dbuser'"/>
<xsl:variable name="database_pass" select="'dbpass'"/>
</xsl:stylesheet>

#!/bin/sh

cd $DEVROOT/Projects/CPP

cat > AppDevelopment/XSLT_Templates/XMIToDMF/XMISettings.xsl << EOF
<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:variable name="targetdatabase" select="'DatabaseLayerGateway'"/>
<xsl:variable name="execute_droprules" select="'no'"/>
<xsl:variable name="database_name" select="'lbDMF'"/>
<xsl:variable name="database_user" select="'dba'"/>
<xsl:variable name="database_pass" select="'trainres'"/>
</xsl:stylesheet>
EOF

xsltproc AppDevelopment/XSLT_Templates/XMIToDMF/importUML-SystemDB.xsl AppDevelopment/DynamicApp/ModelExchange/lbDMFManagerBoUML.xmi > Database/lbDMF-Sqlite-SystemDB.sql
xsltproc AppDevelopment/XSLT_Templates/XMIToDMF/importUML-ApplicationDB.xsl AppDevelopment/DynamicApp/ModelExchange/lbDMFManagerBoUML.xmi > Database/lbDMF-Sqlite-ApplicationDB.sql

cat > AppDevelopment/XSLT_Templates/XMIToDMF/XMISettings.xsl << EOF
<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:variable name="targetdatabase" select="''"/>
<xsl:variable name="execute_droprules" select="'no'"/>
<xsl:variable name="database_name" select="'lbDMF'"/>
<xsl:variable name="database_user" select="'dba'"/>
<xsl:variable name="database_pass" select="'trainres'"/>
</xsl:stylesheet>
EOF

xsltproc AppDevelopment/XSLT_Templates/XMIToDMF/importUML-ApplicationDB.xsl AppDevelopment/DynamicApp/ModelExchange/lbDMFManagerBoUML.xmi > Database/lbDMF-PostgreSQL.sql
xsltproc AppDevelopment/XSLT_Templates/XMIToDMF/importUML-SystemDB.xsl AppDevelopment/DynamicApp/ModelExchange/lbDMFManagerBoUML.xmi >> Database/lbDMF-PostgreSQL.sql
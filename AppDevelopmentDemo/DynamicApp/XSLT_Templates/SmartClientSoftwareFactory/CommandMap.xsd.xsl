<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="exsl.xsl"/>

<xsl:template name="CommandMap.xsd">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>&lt;?xml version="1.0" encoding="utf-8"?&gt;
&lt;xs:schema id="CommandMap" targetNamespace="http://schemas.microsoft.com/pag/cab-command-map" elementFormDefault="qualified" xmlns="http://schemas.microsoft.com/pag/cab-command-map" xmlns:mstns="http://schemas.microsoft.com/pag/cab-command-map" xmlns:xs="http://www.w3.org/2001/XMLSchema"&gt;
	&lt;xs:complexType name="CommandMap"&gt;
		&lt;xs:sequence&gt;
			&lt;xs:element name="Mapping" type="Mapping" minOccurs="0" maxOccurs="unbounded" /&gt;
		&lt;/xs:sequence&gt;
	&lt;/xs:complexType&gt;
	&lt;xs:complexType name="Mapping"&gt;
		&lt;xs:attribute name="Site" type="xs:string" /&gt;
		&lt;xs:attribute name="CommandName" type="xs:string" /&gt;
		&lt;xs:attribute name="Label" type="xs:string" /&gt;
	&lt;/xs:complexType&gt;
	&lt;xs:element name="CommandMap" type="CommandMap" /&gt;
&lt;/xs:schema&gt;
</xsl:template>
</xsl:stylesheet>

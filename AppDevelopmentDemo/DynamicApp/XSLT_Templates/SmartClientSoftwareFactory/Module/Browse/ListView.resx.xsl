<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="ListView.resx">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>&lt;?xml version="1.0" encoding="utf-8"?&gt;
&lt;root&gt;
  &lt;xsd:schema id="root" xmlns="" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:msdata="urn:schemas-microsoft-com:xml-msdata"&gt;
    &lt;xsd:element name="root" msdata:IsDataSet="true"&gt;
      &lt;xsd:complexType&gt;
        &lt;xsd:choice maxOccurs="unbounded"&gt;
          &lt;xsd:element name="metadata"&gt;
            &lt;xsd:complexType&gt;
              &lt;xsd:sequence&gt;
                &lt;xsd:element name="value" type="xsd:string" minOccurs="0" /&gt;
              &lt;/xsd:sequence&gt;
              &lt;xsd:attribute name="name" use="required" type="xsd:string" /&gt;
              &lt;xsd:attribute name="type" type="xsd:string" /&gt;
              &lt;xsd:attribute name="mimetype" type="xsd:string" /&gt;
            &lt;/xsd:complexType&gt;
          &lt;/xsd:element&gt;
          &lt;xsd:element name="assembly"&gt;
            &lt;xsd:complexType&gt;
              &lt;xsd:attribute name="alias" type="xsd:string" /&gt;
              &lt;xsd:attribute name="name" type="xsd:string" /&gt;
            &lt;/xsd:complexType&gt;
          &lt;/xsd:element&gt;
          &lt;xsd:element name="data"&gt;
            &lt;xsd:complexType&gt;
              &lt;xsd:sequence&gt;
                &lt;xsd:element name="value" type="xsd:string" minOccurs="0" msdata:Ordinal="1" /&gt;
                &lt;xsd:element name="comment" type="xsd:string" minOccurs="0" msdata:Ordinal="2" /&gt;
              &lt;/xsd:sequence&gt;
              &lt;xsd:attribute name="name" type="xsd:string" use="required" msdata:Ordinal="1" /&gt;
              &lt;xsd:attribute name="type" type="xsd:string" msdata:Ordinal="3" /&gt;
              &lt;xsd:attribute name="mimetype" type="xsd:string" msdata:Ordinal="4" /&gt;
            &lt;/xsd:complexType&gt;
          &lt;/xsd:element&gt;
          &lt;xsd:element name="resheader"&gt;
            &lt;xsd:complexType&gt;
              &lt;xsd:sequence&gt;
                &lt;xsd:element name="value" type="xsd:string" minOccurs="0" msdata:Ordinal="1" /&gt;
              &lt;/xsd:sequence&gt;
              &lt;xsd:attribute name="name" type="xsd:string" use="required" /&gt;
            &lt;/xsd:complexType&gt;
          &lt;/xsd:element&gt;
        &lt;/xsd:choice&gt;
      &lt;/xsd:complexType&gt;
    &lt;/xsd:element&gt;
  &lt;/xsd:schema&gt;
  &lt;resheader name="resmimetype"&gt;
    &lt;value&gt;text/microsoft-resx&lt;/value&gt;
  &lt;/resheader&gt;
  &lt;resheader name="version"&gt;
    &lt;value&gt;2.0&lt;/value&gt;
  &lt;/resheader&gt;
  &lt;resheader name="reader"&gt;
    &lt;value&gt;System.Resources.ResXResourceReader, System.Windows.Forms, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089&lt;/value&gt;
  &lt;/resheader&gt;
  &lt;resheader name="writer"&gt;
    &lt;value&gt;System.Resources.ResXResourceWriter, System.Windows.Forms, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089&lt;/value&gt;
  &lt;/resheader&gt;
&lt;/root&gt;
</xsl:template>
</xsl:stylesheet>

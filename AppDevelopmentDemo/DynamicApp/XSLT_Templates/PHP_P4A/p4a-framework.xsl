<xsl:stylesheet
	    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
	    xmlns:UML="org.omg.xmi.namespace.UML" 
	    xmlns:exsl="http://exslt.org/common"
	    version="1.1"
	    extension-element-prefixes="exsl"
	    exclude-result-prefixes="UML">

<xsl:import href="exsl.xsl"/>

  <xsl:output method="text" indent="no"/>
  <xsl:template match="text()|@*">
    <xsl:value-of select="."/>
  </xsl:template>
  <xsl:template match="text()|@*"/>

  <xsl:variable name="derivedTagId" select="//UML:TagDefinition[@name='derived']/@xmi.id"/>

  <xsl:template name="XMI1_2_Root">
    <xsl:for-each select="XMI.content/UML:Model">
      <xsl:call-template name="XMI1_2_Model"/>
    </xsl:for-each>
    <!--xsl:for-each select="UML:Package|UML:Subsystem">
      <xsl:call-template name="XMI1.2_Package_Subsystem"/>
    </xsl:for-each-->
  </xsl:template>

  <xsl:template name="XMI1_2_Model">
    <xsl:variable name="modelID" select="@xmi.id"/>
    <xsl:element name="package">
      <xsl:attribute name="name">
        <xsl:value-of select="concat(@name, UML:ModelElement.name)"/>
      </xsl:attribute>
      <xsl:attribute name="id">
        <xsl:call-template name="XMI1_2_getID"/>
      </xsl:attribute>
      <xsl:apply-templates select="UML:Namespace.ownedElement/UML:Class"/>
    </xsl:element>
      <xsl:for-each select="UML:Namespace.ownedElement/UML:Class">
        <xsl:variable name="classID" select="@xmi.id"/>
        <xsl:call-template name="genAssociations">
          <xsl:with-param name="classID" select="$classID"/>
        </xsl:call-template>
      </xsl:for-each>
  </xsl:template>

  <xsl:template match="UML:Package|UML:Subsystem">
    <xsl:variable name="packageID" select="@xmi.id"/>
    <xsl:variable name="stereoTypeID" select="UML:ModelElement.stereotype//@xmi.idref"/>
    <xsl:variable name="stereoTypeName">
      <xsl:value-of select="//UML:Stereotype[@xmi.id = $stereoTypeID]/@name"/>
    </xsl:variable>
    <xsl:variable name="name" select="concat(@name, UML:ModelElement.name)"/>

<exsl:document href="{@name}/create-DB-{@name}.sh" method="text">#!/bin/sh
mysqladmin create <xsl:value-of select="@name"/>                                                                                                                                                                 
mysql <xsl:value-of select="@name"/> &lt; <xsl:value-of select="@name"/>.sql
    </exsl:document>

<exsl:document href="{@name}/index.php" method="text">&lt;?php
/*
 *  <xsl:value-of select="@name"/>
 */
define("P4A_LOCALE", 'en_US');
define("P4A_DSN", 'mysql://crm:@localhost/<xsl:value-of select="@name"/>');                                                   
//define("P4A_EXTENDED_ERRORS", true);                                                                                 
//define("P4A_AJAX_DEBUG", "/tmp/p4a_ajax_debug.txt");                                                                 
                                                                                                                       
require_once dirname(__FILE__) . '/../../p4a.php';                                                                     
                                                                                                                       
// Check Installation and configuration.                                                                               
// This lines should be removed after the first run.                                                                   
$check = p4a_check_configuration();                                                                                    
                                                                                                                       
// Here we go                                                                                                          
if (is_string($check)) {                                                                                               
    print $check;                                                                                                  
} else {                                                                                                               
    $p4a =&amp; p4a::singleton("<xsl:value-of select="@name"/>");                                                                  
    $p4a->main();                                                                                                  
}
</exsl:document>

<exsl:document href="{@name}/objects/{@name}.php" method="text">&lt;?php
class <xsl:value-of select="@name"/> extends P4A                                                                                                                                                                             
{                                                                                                                                                                                                                
        function <xsl:value-of select="@name"/>()                                                                                                                                                                            
	{                                                                                                                                                                                                        
	    parent::p4a();                                                                                                                                                                                                   
	    $this->setTitle("<xsl:value-of select="@name"/>");                                                                                                                                                                           
                                                                                                                                                                                                                 
	    // Menu                                                                                                                                                                                                          
	    $this->build("p4a_menu", "menu");                                                                                                                                                                                
	    $this->menu->addItem("<xsl:value-of select="@name"/>", "<xsl:value-of select="@name"/>");                                                                                                                                                                   
	    $this->intercept($this->menu->items-><xsl:value-of select="@name"/>, "onClick", "menuClick");                                                                                                                                          
      <xsl:variable name="packageName" select="@name"/>
	    
      <xsl:for-each select="UML:Namespace.ownedElement/UML:Class">
        <xsl:variable name="classID" select="@xmi.id"/>
	    $this->menu->items-><xsl:value-of select="$packageName"/>->addItem("<xsl:value-of select="@name"/>");
	    $this->intercept($this->menu->items-><xsl:value-of select="$packageName"/>->items-><xsl:value-of select="@name"/>, "onClick", "menuClick");                                                                                                                 
      </xsl:for-each>
	    
	    // Data Sources
      <xsl:for-each select="UML:Namespace.ownedElement/UML:Class">
        <xsl:variable name="classID" select="@xmi.id"/>
	    $this->build("p4a_db_source", "<xsl:value-of select="@name"/>");                                                                                                                                                                         
	    $this-><xsl:value-of select="@name"/>->setTable("<xsl:value-of select="@name"/>");                                                                                                                                                                               
	    $this-><xsl:value-of select="@name"/>->setPk("ID");                                                                                                                                                                                
	    $this-><xsl:value-of select="@name"/>->addOrder("ID");                                                                                                                                                                          
	    $this-><xsl:value-of select="@name"/>->load();                                                                                                                                                                                           
	    $this-><xsl:value-of select="@name"/>->fields->ID->setSequence("<xsl:value-of select="@name"/>_ID");                                                                                                                                                 
      </xsl:for-each>
	                                                                                                                                                                             
	    // Primary action                                                                                                                                                                                                
	    $this->openMask("Kunde");                                                                                                                                                                                     
        }                                                                                                                                                                                                        
                                                                                                                                                                                                         
	function menuClick()                                                                                                                                                                                     
	{                                                                                                                                                                                                        
	    $this->openMask($this->active_object->getName());                                                                                                                                                
	}                                                                                                                                                                                                        
} 
    </exsl:document>

    <xsl:element name="package">
      <xsl:attribute name="name">
        <xsl:value-of select="$name"/>
      </xsl:attribute>
      <xsl:apply-templates select="UML:Namespace.ownedElement/UML:Class"/>
    </xsl:element>
      <xsl:for-each select="UML:Namespace.ownedElement/UML:Class">
        <xsl:variable name="classID" select="@xmi.id"/>
        <xsl:call-template name="genAssociations">
          <xsl:with-param name="classID" select="$classID"/>
        </xsl:call-template>
      </xsl:for-each>
  </xsl:template>

  <xsl:template match="UML:Class">
    <!-- ****************** CLASS ********************* -->
    <xsl:variable name="classID" select="@xmi.id"/>
    <xsl:element name="class">
<exsl:document href="{../../@name}/objects/{@name}.php" method="text">&lt;?php
class <xsl:value-of select="@name"/> extends P4A_Mask                                                                                                                                                                                    
{                                                                                                                                                                                                                
        function <xsl:value-of select="@name"/>()                                                                                                                                                                                        
        {                                                                                                                                                                                         
	    $this->p4a_mask();                                                                                                                                                                                               
	    $p4a =&amp; p4a::singleton();                                                                                                                                                                                        
                                                                                                                                                                                                                 
	    $this->build("p4a_message", "message");                                                                                                                                                                          
	    $this->message->setWidth("800");                                                                                                                                                                                 
                                                                                                                                                                                                                 
	    $this->setSource($p4a-><xsl:value-of select="@name"/>);                                                                                                                                                                                  
	    $this->firstRow();                                                                                                                                                                                               
                                                                                                                                                                                         
	    $this->fields->ID->disable();                                                                                                                                                                              


	    $this->build("p4a_standard_toolbar", "toolbar");                                                                                                                                                                 
	    $this->toolbar->setMask($this);                                                                                                                                                                                  
                                                                                                                                                                                                                 
	    $this->build("p4a_table", "table");                                                                                                                                                                              
	    $this->table->setSource($p4a-><xsl:value-of select="@name"/>);                                                                                                                                                                           
	    $this->table->showNavigationBar();                                                                                                                                                                               
	    $this->table->setWidth(800);                                                                                                                                                                                     
                                                                                                                                                                                                                 
	    $this->build("p4a_frame", "sheet");                                                                                                                                                                              
	    $this->sheet->setWidth(800);                                                                                                                                                                                     
	    $this->sheet->anchorCenter($this->message);                                                                                                                                                                      
	    $this->sheet->anchor($this->table);                                                                                                                                                                              
                                                                                                                                                                                                                 
	    $this->fields->ID->setLabel("<xsl:value-of select="@name"/> ID");                                                                                                                                                                   
	    $this->table->cols->ID->setLabel("<xsl:value-of select="@name"/> ID");                                                                                                                                                              
	    $this->table->showNavigationBar();                                                                                                                                                                               
                                                                                                                                                                                                                 
	    $this->build("p4a_fieldset", "fields_sheet");                                                                                                                                                                    
	    $this->fields_sheet->setTitle("<xsl:value-of select="@name"/> detail");                                                                                                                                                                   
	    $this->fields_sheet->anchor($this->fields->ID);                                                                                                                                         
	    
<xsl:for-each select="./UML:Classifier.feature/UML:Attribute">
<xsl:variable name="type" select="./UML:StructuralFeature.type/UML:DataType/@xmi.idref"/>
	    $this->fields_sheet->anchor($this->fields-><xsl:value-of select="@name"/>);
</xsl:for-each>
                                                                                                                                                                                                                 
	    $this->sheet->anchor($this->fields_sheet);                                                                                                                                                                       
/*
    	    //Mandatory Fields                                                                                                                                                                                               
	    $this->mf = array("");                                                                                                                                                                                
	    foreach($this->mf as $mf){                                                                                                                                                                                       
		$this->fields->$mf->label->setFontWeight("bold");                                                                                                                                                                
	    }                                                                                                                                                                                                                
*/                                                                                                                                                                                                                 
	    $this->display("menu", $p4a->menu);                                                                                                                                                                              
	    $this->display("top", $this->toolbar);                                                                                                                                                                           
	    $this->display("main", $this->sheet);                                                                                                                                                                            
                                                                                                                                                                                                                 
<xsl:for-each select="./UML:Classifier.feature/UML:Attribute">
<xsl:variable name="type" select="./UML:StructuralFeature.type/UML:DataType/@xmi.idref"/>
<xsl:if test="position()=1">
	    $this->setFocus($this->fields-><xsl:value-of select="@name"/>);
</xsl:if>
</xsl:for-each>
	}                                                                                                                                                                                                                

	function saveRow()                                                                                                                                                                                               
	{                                                                                                                                                                                                                
	    $errors = array();                                                                                                                                                                                               
                                                                                                                                                                                                                 
	    foreach ($this->mf as $field) {                                                                                                                                                                                  
		if (strlen($this->fields->$field->getNewValue()) == 0) {                                                                                                                                                         
		    $errors[] = $field;                                                                                                                                                                                              
		}                                                                                                                                                                                                                
	    }                                                                                                                                                                                                                
                                                                                                                                                                                                                 
	    if (sizeof($errors) > 0) {                                                                                                                                                                                       
		$this->message->setValue("Please fill all required fields");                                                                                                                                                     
                                                                                                                                                                                                                 
		foreach ($errors as $field) {                                                                                                                                                                                    
		    $this->fields->$field->setStyleProperty("border", "1px solid red");                                                                                                                                              
		}                                                                                                                                                                                                                
	    } else {                                                                                                                                                                                                         
		parent::saveRow();                                                                                                                                                                                               
	    }                                                                                                                                                                                                                
	}                                                                                                                                                                                                                
                                                                                                                                                                                                                 
	function main()                                                                                                                                                                                                  
	{                                                                                                                                                                                                                
	    parent::main();                                                                                                                                                                                                  
/*                                                                                                                                                                                                     
	    foreach ($this->mf as $field) {                                                                                                                                                                                  
		$this->fields->$field->unsetStyleProperty("border");                                                                                                                                                             
	    }                                                                                                                                                                                                                
*/	    
	}                                                                                                                                                                                                                
} 	
    </exsl:document>
    
-- Class is <xsl:value-of select="@name"/>

CREATE TABLE <xsl:value-of select="@name"/> (
ID INTEGER NOT NULL,
PRIMARY KEY (id)<xsl:for-each select="./UML:Classifier.feature/UML:Attribute">,
<xsl:variable name="type" select="./UML:StructuralFeature.type/UML:DataType/@xmi.idref"/>
<xsl:value-of select="@name"/><xsl:value-of select="' '"/><xsl:variable name="UMLType" select="//UML:DataType[@xmi.id=$type]/@name"/>
<xsl:call-template name="convertTypes_DBTypes"><xsl:with-param name="typename" select="$UMLType"/></xsl:call-template>
</xsl:for-each>
);
    </xsl:element>
  </xsl:template>

  <xsl:template name="convertTypes_DBTypes">
    <xsl:param name="typename"/>
    <xsl:choose>
      <xsl:when test="$typename='int'">INTEGER</xsl:when>
      <xsl:when test="$typename='float'">DECIMAL</xsl:when>
      <xsl:when test="$typename='date'">DATE</xsl:when>
      <xsl:when test="$typename='string'">CHAR(100)</xsl:when>
    </xsl:choose>

  </xsl:template>

  <xsl:template name="genAssociations">
    <!-- ****************** CLASS ********************* -->
    <xsl:param name="classID"/>
    <xsl:call-template name="associationsForClass_12">
      <xsl:with-param name="id" select="$classID"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template name="associationsForClass_12">
    <xsl:param name="id"/>
    <!-- UML1.4: -->
    <xsl:for-each select="//UML:AssociationEnd/UML:AssociationEnd.participant/*[@xmi.idref = $id]">
      <!-- Choose only association ends where navigable is true. -->
      <xsl:variable name="thisEnd" select="../.."/>
      <xsl:variable name="thisEndId" select="$thisEnd/@xmi.id"/>
      <xsl:variable name="thisEndType" select="$thisEnd/@type"/>
      <xsl:variable name="thisClassName" select="//UML:Class[@xmi.id=$thisEndType]/@name"/>
      <xsl:variable name="otherEnd" select="../../../UML:AssociationEnd[@type != $thisEndType]"/>
      <xsl:variable name="otherEndType" select="../../../UML:AssociationEnd[@type != $thisEndType]/@type"/>
      <xsl:variable name="otherEndId" select="$otherEnd/@type"/>
      <xsl:variable name="otherClassID" select="../../../UML:AssociationEnd[@type=$otherEndId]/UML:AssociationEnd.participant/@xmi.idref"/>
      <xsl:variable name="otherClassName" select="//UML:Class[@xmi.id=$otherEndId]/@name"/>
<xsl:if test="../../../UML:AssociationEnd[@type=$otherEndId]/@aggregation='aggregate'">
-- Associations not in MySQL
</xsl:if>
    </xsl:for-each>
  </xsl:template>

</xsl:stylesheet>

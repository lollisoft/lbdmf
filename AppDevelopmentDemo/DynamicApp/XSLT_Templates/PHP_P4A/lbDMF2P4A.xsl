<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="exsl.xsl"/>

<xsl:output method="text" indent="no"/>

<xsl:template match="lbDMF">
<xsl:variable name="ApplicationID" select="//lbDMF/@applicationid"/>
<xsl:variable name="OrginalApplicationName" select="//lbDMF/applications/application[@ID=$ApplicationID]/@name"/>
<xsl:variable name="ApplicationName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$OrginalApplicationName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>

<!-- Create index.php -->
Have application ID = <xsl:value-of select="$ApplicationID"/>
Create <xsl:value-of select="$OrginalApplicationName"/>
Create <xsl:value-of select="$ApplicationName"/>/index.php

<exsl:document href="Code/Targets/PHP/{$ApplicationName}/index.php" method="text">&lt;?php
/*
 *  <xsl:value-of select="$ApplicationName"/>
 */
define("P4A_LOCALE", 'en_US');
define("P4A_DSN", 'pgsql://dba:trainres@vmhost/<xsl:value-of select="$ApplicationName"/>');                                                   
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
    $p4a = p4a::singleton("<xsl:value-of select="$ApplicationName"/>");                                                                  
    $p4a->main();                                                                                                  
}
</exsl:document>

<!-- Create main application php file -->

<exsl:document href="Code/Targets/PHP/{$ApplicationName}/objects/{$ApplicationName}.php" method="text">&lt;?php
class <xsl:value-of select="$ApplicationName"/> extends P4A
{
	public $menu = null;
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>
	    public $<xsl:value-of select="$FormularName"/> = null;
</xsl:for-each>


    public function __construct()                                                                                                                                                                            
	{                                                                                                                                                                                                        
	    parent::__construct();                                                                                                                                                                                                   
	    $this->setTitle("<xsl:value-of select="$ApplicationName"/>");                                                                                                                                                                           
                                                                                                                                                                                                                 
	    // Menu                                                                                                                                                                                                          
	    $this->build("p4a_menu", "menu");                                                                                                                                                                                
	    $this->menu->addItem("<xsl:value-of select="$ApplicationName"/>", "<xsl:value-of select="$ApplicationName"/>");                                                                                                                                                                   
	    $this->intercept($this->menu->items-><xsl:value-of select="$ApplicationName"/>, "onClick", "menuClick");                                                                                                                                          
      <xsl:variable name="packageName" select="$ApplicationName"/>
	    
		
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>
	    $this->menu->items-><xsl:value-of select="$ApplicationName"/>->addItem("<xsl:value-of select="$FormularName"/>")->implement("onclick", $this, "menuClick");                                                                                                            
</xsl:for-each>
	    
	    // Data Sources
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>
	    $this->build("p4a_db_source", "<xsl:value-of select="$FormularName"/>")
	    ->setTable("<xsl:value-of select="$FormularName"/>")
	    ->setPk("ID")
	    ->addOrder("ID")
	    ->load();
	    //$this-><xsl:value-of select="$FormularName"/>->fields->ID->setSequence("<xsl:value-of select="$FormularName"/>_ID");
</xsl:for-each>
                                                                                                                                                                             
	    // Primary action                                                                                                                                                                                                
	    //$this->openMask("Kunde");
		$this->openMask("P4A_Login_Mask");
		$this->active_mask->implement('onLogin', $this, 'login');
		$this->active_mask->username->setTooltip("Simply type p4a");
		$this->active_mask->password->setTooltip("Type p4a here too");
		$this->loginInfo();
    }                                                                                                                                                                                                        

	protected function loginInfo()                                                                                                                                                                                                                                                                                     
	{                                                                                                                                                                                                                                                                                                                  
		$this->messageInfo('To login type:<br />username: p4a<br />password: p4a', 'info');                                                                                                                                                                                                                        
	}

	public function login()
	{
		$username = $this->active_mask->username->getNewValue();
		$password = $this->active_mask->password->getNewValue();
 
		if ($username == "p4a" and $password == md5("p4a")) {
			$this->messageInfo("Login successful");         
			$this->openMask("Kunde");
		} else {
			$this->messageError("Login failed");
			$this->loginInfo();                       
		}
	}
	
	function menuClick()                                                                                                                                                                                     
	{                                                                                                                                                                                                        
	    $this->openMask($this->active_object->getName());                                                                                                                                                
	}                                                                                                                                                                                                        
} 
</exsl:document>

<!-- Build formular classes for each formular -->

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>
<xsl:variable name="FormularID" select="@ID"/>

<exsl:document href="Code/Targets/PHP/{$ApplicationName}/objects/{$FormularName}.php" method="text">&lt;?php

// FormularID = <xsl:value-of select="$FormularID"/>

class <xsl:value-of select="$FormularName"/> extends P4A_Base_Mask                                                                                                                                                                                    
{                                                                                                                                                                                                                
        public function __construct()                                                                                                                                                                                        
        {                                                                                                                                                                                         
	    parent::__construct();                                                                                                                                                                                               
	    $p4a = p4a::singleton();                                                                                                                                                                                        
                                                                                                                                                                                                                 
	    $this->build("p4a_message", "message");                                                                                                                                                                          
	    $this->message->setWidth("800");                                                                                                                                                                                 
                                                                                                                                                                                                                 
	    $this->setSource($p4a-><xsl:value-of select="$FormularName"/>);                                                                                                                                                                                  
	    $this->firstRow();                                                                                                                                                                                               
                                                                                                                                                                                         
	    $this->fields->ID->disable();                                                                                                                                                                              


	    $this->build("p4a_full_toolbar", "toolbar");                                                                                                                                                                 
	    $this->toolbar->setMask($this);                                                                                                                                                                                  
                                                                                                                                                                                                                 
	    $this->build("p4a_table", "table");                                                                                                                                                                              
	    $this->table->setSource($p4a-><xsl:value-of select="$FormularName"/>);                                                                                                                                                                           
	    $this->table->showNavigationBar();                                                                                                                                                                               
	    $this->table->setWidth(800);                                                                                                                                                                                     
                                                                                                                                                                                                                 
	    $this->build("p4a_frame", "sheet");                                                                                                                                                                              
	    $this->sheet->setWidth(800);                                                                                                                                                                                     
	    $this->sheet->anchorCenter($this->message);                                                                                                                                                                      
	    $this->sheet->anchor($this->table);                                                                                                                                                                              
                                                                                                                                                                                                                 
	    $this->fields->ID->setLabel("<xsl:value-of select="$FormularName"/> ID");                                                                                                                                                                   
	    $this->table->cols->ID->setLabel("<xsl:value-of select="$FormularName"/> ID");                                                                                                                                                              
	    $this->table->showNavigationBar();                                                                                                                                                                               
                                                                                                                                                                                                                 
	    $this->build("p4a_fieldset", "fields_sheet");                                                                                                                                                                    
	    $this->fields_sheet->setLabel("<xsl:value-of select="$FormularName"/> detail");                                                                                                                                                                   
	    $this->fields_sheet->anchor($this->fields->ID);                                                                                                                                         

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
// Set anchor ...
<xsl:choose>
	<xsl:when test="@isfk='1'">
	// FK <xsl:value-of select="@name"/>
	// Create a mapping instance for this combo box
	    $this->fields_sheet->anchor($this->fields-><xsl:value-of select="@name"/>);
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
	// Special column <xsl:value-of select="@name"/>
	    $this->fields_sheet->anchor($this->fields-><xsl:value-of select="@name"/>);
	</xsl:when>
	<xsl:otherwise>
		
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
	// Normal Bit column <xsl:value-of select="@name"/>
	    $this->fields_sheet->anchor($this->fields-><xsl:value-of select="@name"/>);
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
	// Normal Float column <xsl:value-of select="@name"/>
	    $this->fields_sheet->anchor($this->fields-><xsl:value-of select="@name"/>);
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
	// Normal Integer column <xsl:value-of select="@name"/>
	    $this->fields_sheet->anchor($this->fields-><xsl:value-of select="@name"/>);
			</xsl:when>
			<xsl:when test="@dbtype='String'">
	// Normal String column <xsl:value-of select="@name"/>
	    $this->fields_sheet->anchor($this->fields-><xsl:value-of select="@name"/>);
			</xsl:when>
			<xsl:otherwise>
	// Unknown column <xsl:value-of select="@name"/>
	    $this->fields_sheet->anchor($this->fields-><xsl:value-of select="@name"/>);
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
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
                                                                                                                                                                                                                 
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
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
</xsl:for-each>

</xsl:template>

<!-- here is the template that does the replacement -->
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


</xsl:stylesheet>

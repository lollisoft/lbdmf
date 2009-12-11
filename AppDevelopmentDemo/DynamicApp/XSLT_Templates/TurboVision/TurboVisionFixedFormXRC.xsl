<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002-2009  Lothar Behrens (lothar.behrens@lollisoft.de)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
-->
<xsl:import href="../include/exsl.xsl"/>

<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>

<xsl:import href="DialogBlocksXMLSnippets.xsl"/>

<!-- Start PJD File BIG -->
<xsl:template name="createFormClassImplPJDFile">
		<xsl:param name="ApplicationID"/>
<!-- Create the PJD file for all formulars -->
<exsl:document href="{$basedir}/{$pluginsdir}/{$ApplicationName}/{$ApplicationName}Formulare.pjd" method="text">&lt;?xml version="1.0" encoding="UTF-8"?&gt;
&lt;anthemion-project version="1.0.0.0" xmlns="http://www.anthemion.co.uk"&gt;
  &lt;header&gt;
    &lt;long name="name_counter"&gt;0&lt;/long&gt;
    &lt;string name="html_path"&gt;""&lt;/string&gt;
    &lt;string name="title"&gt;""&lt;/string&gt;
    &lt;string name="author"&gt;""&lt;/string&gt;
    &lt;string name="description"&gt;""&lt;/string&gt;
    &lt;string name="xrc_filename"&gt;"<xsl:value-of select="$ApplicationName"/>Forms.xrc"&lt;/string&gt;
    &lt;bool name="convert_images_to_xpm"&gt;0&lt;/bool&gt;
    &lt;bool name="inline_images"&gt;0&lt;/bool&gt;
    &lt;bool name="generate_cpp_for_xrc"&gt;1&lt;/bool&gt;
    &lt;bool name="use_help_text_for_tooltips"&gt;1&lt;/bool&gt;
    &lt;bool name="translate_strings"&gt;1&lt;/bool&gt;
    &lt;bool name="extract_strings"&gt;0&lt;/bool&gt;
    &lt;string name="user_name"&gt;"Lothar Behrens"&lt;/string&gt;
    &lt;string name="copyright_string"&gt;"Copyright (c) 2000-2007"&lt;/string&gt;
    &lt;string name="resource_prefix"&gt;""&lt;/string&gt;
    &lt;bool name="use_two_step_construction"&gt;0&lt;/bool&gt;
    &lt;bool name="use_enums"&gt;0&lt;/bool&gt;
    &lt;string name="current_platform"&gt;"&amp;lt;All platforms&amp;gt;"&lt;/string&gt;
    &lt;string name="target_wx_version"&gt;"2.6.3"&lt;/string&gt;
    &lt;string name="cpp_header_comment"&gt;"/////////////////////////////////////////////////////////////////////////////
// Name:        %HEADER-FILENAME%
// Purpose:     
// Author:      %AUTHOR%
// Modified by: 
// Created:     %DATE%
// RCS-ID:      
// Copyright:   %COPYRIGHT%
// Licence:     
/////////////////////////////////////////////////////////////////////////////

"&lt;/string&gt;
    &lt;string name="cpp_implementation_comment"&gt;"/////////////////////////////////////////////////////////////////////////////
// Name:        %SOURCE-FILENAME%
// Purpose:     
// Author:      %AUTHOR%
// Modified by: 
// Created:     %DATE%
// RCS-ID:      
// Copyright:   %COPYRIGHT%
// Licence:     
/////////////////////////////////////////////////////////////////////////////

"&lt;/string&gt;
    &lt;string name="cpp_symbols_file_comment"&gt;"/////////////////////////////////////////////////////////////////////////////
// Name:        %SYMBOLS-FILENAME%
// Purpose:     Symbols file
// Author:      %AUTHOR%
// Modified by: 
// Created:     %DATE%
// RCS-ID:      
// Copyright:   %COPYRIGHT%
// Licence:     
/////////////////////////////////////////////////////////////////////////////

"&lt;/string&gt;
    &lt;string name="cpp_header_preamble"&gt;"#if defined(__GNUG__) &amp;amp;&amp;amp; !defined(NO_GCC_PRAGMA)
#pragma interface &amp;quot;%HEADER-FILENAME%&amp;quot;
#endif

"&lt;/string&gt;
    &lt;string name="cpp_implementation_preamble"&gt;"#if defined(__GNUG__) &amp;amp;&amp;amp; !defined(NO_GCC_PRAGMA)
#pragma implementation &amp;quot;%HEADER-FILENAME%&amp;quot;
#endif

// For compilers that support precompilation, includes &amp;quot;wx/wx.h&amp;quot;.
#include &amp;quot;wx/wxprec.h&amp;quot;

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include &amp;quot;wx/wx.h&amp;quot;
#endif

"&lt;/string&gt;
    &lt;string name="cpp_function_declaration_comment"&gt;"	/// %BODY%
"&lt;/string&gt;
    &lt;string name="cpp_function_implementation_comment"&gt;"
/*!
 * %BODY%
 */

"&lt;/string&gt;
    &lt;string name="resource_file_header"&gt;"app_resources.h"&lt;/string&gt;
    &lt;string name="resource_file_implementation"&gt;"app_resources.cpp"&lt;/string&gt;
    &lt;string name="resource_class_name"&gt;"AppResources"&lt;/string&gt;
    &lt;string name="app_file_header"&gt;"app.h"&lt;/string&gt;
    &lt;string name="app_file_implementation"&gt;"app.cpp"&lt;/string&gt;
    &lt;string name="app_class_name"&gt;"Application"&lt;/string&gt;
    &lt;bool name="generate_app_class"&gt;0&lt;/bool&gt;
    &lt;string name="external_symbol_filenames"&gt;""&lt;/string&gt;
    &lt;string name="configuration"&gt;"&amp;lt;None&amp;gt;"&lt;/string&gt;
    &lt;string name="source_encoding"&gt;"iso-8859-1"&lt;/string&gt;
    &lt;string name="xrc_encoding"&gt;"utf-8"&lt;/string&gt;
    &lt;string name="project_encoding"&gt;"utf-8"&lt;/string&gt;
    &lt;string name="resource_archive"&gt;""&lt;/string&gt;
    &lt;long name="text_file_type"&gt;0&lt;/long&gt;
    &lt;bool name="use_tabs"&gt;0&lt;/bool&gt;
    &lt;long name="indent_size"&gt;4&lt;/long&gt;
    &lt;string name="whitespace_after_return_type"&gt;" "&lt;/string&gt;
    &lt;string name="resource_xrc_cpp"&gt;""&lt;/string&gt;
    &lt;bool name="use_resource_archive"&gt;0&lt;/bool&gt;
    &lt;bool name="use_generated_xrc_cpp"&gt;0&lt;/bool&gt;
    &lt;bool name="always_generate_xrc"&gt;1&lt;/bool&gt;
    &lt;bool name="archive_xrc_files"&gt;1&lt;/bool&gt;
    &lt;bool name="archive_image_files"&gt;1&lt;/bool&gt;
    &lt;bool name="archive_all_image_files"&gt;0&lt;/bool&gt;
    &lt;bool name="xrc_retain_relative_paths"&gt;1&lt;/bool&gt;
  &lt;/header&gt;
  &lt;data&gt;
    &lt;document&gt;
      &lt;string name="title"&gt;""&lt;/string&gt;
      &lt;string name="type"&gt;"data-document"&lt;/string&gt;
      &lt;string name="filename"&gt;""&lt;/string&gt;
      &lt;string name="icon-name"&gt;""&lt;/string&gt;
      &lt;long name="is-transient"&gt;0&lt;/long&gt;
      &lt;long name="owns-file"&gt;1&lt;/long&gt;
      &lt;long name="title-mode"&gt;0&lt;/long&gt;
      &lt;long name="locked"&gt;0&lt;/long&gt;
      &lt;document&gt;
        &lt;string name="title"&gt;"Configurations"&lt;/string&gt;
        &lt;string name="type"&gt;"config-data-document"&lt;/string&gt;
        &lt;string name="filename"&gt;""&lt;/string&gt;
        &lt;string name="icon-name"&gt;""&lt;/string&gt;
        &lt;long name="is-transient"&gt;0&lt;/long&gt;
        &lt;long name="owns-file"&gt;1&lt;/long&gt;
        &lt;long name="title-mode"&gt;0&lt;/long&gt;
        &lt;long name="locked"&gt;0&lt;/long&gt;
        &lt;string name="template-name"&gt;""&lt;/string&gt;
        &lt;bool name="dirty"&gt;1&lt;/bool&gt;
        &lt;string name="Compiler name"&gt;""&lt;/string&gt;
        &lt;string name="Build mode"&gt;"Debug"&lt;/string&gt;
        &lt;string name="Unicode mode"&gt;"ANSI"&lt;/string&gt;
        &lt;string name="Shared mode"&gt;"Static"&lt;/string&gt;
        &lt;string name="Modularity"&gt;"Modular"&lt;/string&gt;
        &lt;string name="GUI mode"&gt;"GUI"&lt;/string&gt;
        &lt;string name="Toolkit"&gt;"wxMac"&lt;/string&gt;
        &lt;string name="Runtime linking"&gt;"Dynamic"&lt;/string&gt;
        &lt;string name="Use exceptions"&gt;"Yes"&lt;/string&gt;
        &lt;string name="Use ODBC"&gt;"No"&lt;/string&gt;
        &lt;string name="Use OpenGL"&gt;"No"&lt;/string&gt;
        &lt;string name="wxWidgets version"&gt;"%WXVERSION%"&lt;/string&gt;
        &lt;string name="Executable name"&gt;"%EXECUTABLE%"&lt;/string&gt;
        &lt;string name="Program arguments"&gt;""&lt;/string&gt;
        &lt;string name="Working path"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Output path"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Objects path"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Compiler location"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="wxWidgets location"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="C++ command"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Resource compiler"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Make command"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Project makefile"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="wxWidgets makefile"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Compiler bin path"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Compiler include path"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Compiler lib path"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Preprocessor flags"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Optimizations"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Warnings"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Debug flags"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Libraries"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Library path"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Linker flags"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Include path"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Resource flags"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="Resource path"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="wxWidgets build path"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="wxWidgets build command"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="wxWidgets clean command"&gt;"%AUTO%"&lt;/string&gt;
        &lt;string name="PATH variable"&gt;"%AUTO%"&lt;/string&gt;
      &lt;/document&gt;
    &lt;/document&gt;
  &lt;/data&gt;

  &lt;documents&gt;
    &lt;document&gt;
      &lt;string name="title"&gt;"Projects"&lt;/string&gt;
      &lt;string name="type"&gt;"root-document"&lt;/string&gt;
      &lt;string name="filename"&gt;""&lt;/string&gt;
      &lt;string name="icon-name"&gt;"project"&lt;/string&gt;
      &lt;long name="is-transient"&gt;1&lt;/long&gt;
      &lt;long name="owns-file"&gt;1&lt;/long&gt;
      &lt;long name="title-mode"&gt;0&lt;/long&gt;
      &lt;long name="locked"&gt;1&lt;/long&gt;
      &lt;document&gt;
        &lt;string name="title"&gt;"Windows"&lt;/string&gt;
        &lt;string name="type"&gt;"html-document"&lt;/string&gt;
        &lt;string name="filename"&gt;""&lt;/string&gt;
        &lt;string name="icon-name"&gt;"dialogsfolder"&lt;/string&gt;
        &lt;long name="is-transient"&gt;1&lt;/long&gt;
        &lt;long name="owns-file"&gt;1&lt;/long&gt;
        &lt;long name="title-mode"&gt;0&lt;/long&gt;
        &lt;long name="locked"&gt;1&lt;/long&gt;
		
<!-- App level informations -->
		
        &lt;document&gt; 
          &lt;string name="title"&gt;"<xsl:value-of select="$ApplicationName"/>App"&lt;/string&gt;
          &lt;string name="type"&gt;"dialog-document"&lt;/string&gt;
          &lt;string name="filename"&gt;""&lt;/string&gt;
          &lt;string name="icon-name"&gt;"app"&lt;/string&gt;
          &lt;long name="is-transient"&gt;0&lt;/long&gt;
          &lt;long name="owns-file"&gt;1&lt;/long&gt;
          &lt;long name="title-mode"&gt;0&lt;/long&gt;
          &lt;long name="locked"&gt;0&lt;/long&gt;
          &lt;string name="created"&gt;"11/11/2007"&lt;/string&gt;
          &lt;string name="proxy-type"&gt;"wbAppProxy"&lt;/string&gt;
          &lt;long name="base-id"&gt;10000&lt;/long&gt;
          &lt;bool name="use-id-prefix"&gt;0&lt;/bool&gt;
          &lt;string name="id-prefix"&gt;""&lt;/string&gt;
          &lt;bool name="use-id-suffix"&gt;0&lt;/bool&gt;
          &lt;string name="id-suffix"&gt;""&lt;/string&gt;
          &lt;long name="use-xrc"&gt;0&lt;/long&gt;
          &lt;string name="proxy-Class"&gt;"<xsl:value-of select="$ApplicationName"/>App"&lt;/string&gt;
          &lt;string name="proxy-Base class"&gt;"wxApp"&lt;/string&gt;
          &lt;string name="proxy-Implementation filename"&gt;"<xsl:value-of select="$ApplicationName"/>App.cpp"&lt;/string&gt;
          &lt;string name="proxy-Header filename"&gt;"<xsl:value-of select="$ApplicationName"/>App.h"&lt;/string&gt;
          &lt;string name="proxy-Event sources"&gt;""&lt;/string&gt;
          &lt;string name="proxy-Main window"&gt;""&lt;/string&gt;
        &lt;/document&gt;
<!-- Formular level informations -->
<!-- === Formular specific template ====================================================================== -->
<xsl:for-each select="//lbDMF/formulare/formular[@applicationid=$ApplicationID]">
<xsl:variable name="FormularID" select="@ID"/>
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
        &lt;document&gt;
<xsl:call-template name="create_formularlevel_prefix">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormularName" select="$FormularName"/>
</xsl:call-template>
<!-- Field level douments -->
          &lt;document&gt;
<xsl:call-template name="create_boxsizer_prefix_vertical">
</xsl:call-template>

<!-- Real field setup per database column -->
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:variable name="ItemID" select="@ID"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
<xsl:call-template name="create_choice_control_horizontal">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
<xsl:call-template name="create_special_control_horizontal">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
<xsl:call-template name="create_checkbox_control_horizontal">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
<xsl:call-template name="create_text_control_horizontal">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
<xsl:call-template name="create_text_control_horizontal">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
			</xsl:when>
			<xsl:when test="@dbtype='String'">
<xsl:call-template name="create_text_control_horizontal">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each><!-- Field -->
            &lt;document&gt;
<xsl:call-template name="create_boxsizer_prefix_horizontal"/>
<xsl:for-each select="//lbDMF/formularactions/action[@formularid=$FormularID]">

<xsl:variable name="EventIdentifer">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="@event"/>
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
              &lt;document&gt;
	<xsl:variable name="ActionID" select="@actionid"/>
<xsl:call-template name="create_button_control">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="//lbDMF/actions/action[@ID=$ActionID]/@name"/></xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
</xsl:for-each>
            &lt;/document&gt;
<!-- Add and remove button -->
<xsl:call-template name="create_addrem_controls_horizontal">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
</xsl:call-template>
<!-- Navigation buttons -->
<xsl:call-template name="create_navi_controls_horizontal">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
</xsl:call-template>
          &lt;/document&gt;
        &lt;/document&gt;
</xsl:for-each>
      &lt;/document&gt;
      &lt;document&gt;
        &lt;string name="title"&gt;"Sources"&lt;/string&gt;
        &lt;string name="type"&gt;"html-document"&lt;/string&gt;
        &lt;string name="filename"&gt;""&lt;/string&gt;
        &lt;string name="icon-name"&gt;"sourcesfolder"&lt;/string&gt;
        &lt;long name="is-transient"&gt;1&lt;/long&gt;
        &lt;long name="owns-file"&gt;1&lt;/long&gt;
        &lt;long name="title-mode"&gt;0&lt;/long&gt;
        &lt;long name="locked"&gt;1&lt;/long&gt;
        &lt;document&gt;
          &lt;string name="title"&gt;"<xsl:value-of select="$ApplicationName"/>Formular.rc"&lt;/string&gt;
          &lt;string name="type"&gt;"source-editor-document"&lt;/string&gt;
          &lt;string name="filename"&gt;"<xsl:value-of select="$ApplicationName"/>Formular.rc"&lt;/string&gt;
          &lt;string name="icon-name"&gt;"source-editor"&lt;/string&gt;
          &lt;long name="is-transient"&gt;0&lt;/long&gt;
          &lt;long name="owns-file"&gt;0&lt;/long&gt;
          &lt;long name="title-mode"&gt;1&lt;/long&gt;
          &lt;long name="locked"&gt;0&lt;/long&gt;
          &lt;string name="created"&gt;"11/11/2007"&lt;/string&gt;
          &lt;string name="language"&gt;""&lt;/string&gt;
        &lt;/document&gt;
      &lt;/document&gt;
      &lt;document&gt;
        &lt;string name="title"&gt;"Images"&lt;/string&gt;
        &lt;string name="type"&gt;"html-document"&lt;/string&gt;
        &lt;string name="filename"&gt;""&lt;/string&gt;
        &lt;string name="icon-name"&gt;"bitmapsfolder"&lt;/string&gt;
        &lt;long name="is-transient"&gt;1&lt;/long&gt;
        &lt;long name="owns-file"&gt;1&lt;/long&gt;
        &lt;long name="title-mode"&gt;0&lt;/long&gt;
        &lt;long name="locked"&gt;1&lt;/long&gt;
      &lt;/document&gt;
    &lt;/document&gt;
  &lt;/documents&gt;

&lt;/anthemion-project&gt;
<!-- End Formular definition -->
</exsl:document>
</xsl:template>
<!-- End PJD File BIG -->

<!-- Start XRC File -->
<xsl:template name="createFormClassImplXRCLayoutFile">
		<xsl:param name="ApplicationID"/>
<!-- Create the XRC file for the formular -->
<exsl:document href="{$basedir}/{$pluginsdir}/{$ApplicationName}/{$ApplicationName}Forms.xrc" method="text">&lt;?xml version="1.0" encoding="UTF-8"?&gt;
&lt;resource version="2.3.0.1" xmlns="http://www.wxwidgets.org/wxxrc"&gt;
<!--
 Implementation class for fixed database formular header file
 Application: <xsl:value-of select="$ApplicationName"/>
 Formular: <xsl:value-of select="$FormName"/>
-->
<xsl:for-each select="//lbDMF/formulare/formular[@applicationid=$ApplicationID]">
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


<xsl:call-template name="createFormClassImplXRCLayout_Panel">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="ParamFormularName"><xsl:value-of select="$FormularName"/></xsl:with-param>
</xsl:call-template>
</xsl:for-each>
&lt;/resource&gt;
</exsl:document>
</xsl:template>
<!-- End XRC File -->

<xsl:template name="createFormClassImplXRCLayout_Panel_Field">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="ParamFormularName"/>
		<xsl:param name="FieldName"/>
		<xsl:param name="TableName"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
		&lt;object class="sizeritem"&gt;
			&lt;flag&gt;wxGROW|wxALL&lt;/flag&gt;
			&lt;border&gt;5&lt;/border&gt;
			&lt;option&gt;0&lt;/option&gt;
			&lt;object class="wxBoxSizer"&gt;
				&lt;orient&gt;wxHORIZONTAL&lt;/orient&gt;
				&lt;object class="sizeritem"&gt;
					&lt;flag&gt;wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
					&lt;border&gt;5&lt;/border&gt;
					&lt;option&gt;1&lt;/option&gt;
					&lt;object class="wxStaticText" name="lbl<xsl:value-of select="$FieldName"/>"&gt;
						&lt;label&gt;<xsl:value-of select="$FieldName"/>&lt;/label&gt;
					&lt;/object&gt;
				&lt;/object&gt;
				&lt;object class="sizeritem"&gt;
					&lt;flag>wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
					&lt;border&gt;5&lt;/border&gt;
					&lt;option&gt;1&lt;/option&gt;
					&lt;object class="wxChoice" name="<xsl:value-of select="$FieldName"/>"&gt;
					&lt;/object&gt;
				&lt;/object&gt;
			&lt;/object&gt;
		&lt;/object&gt;
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
&gt;!-- Special column <xsl:value-of select="$FieldName"/> --&gt;
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
		&lt;object class="sizeritem"&gt;
			&lt;flag&gt;wxGROW|wxALL&lt;/flag&gt;
			&lt;border&gt;5&lt;/border&gt;
			&lt;option&gt;1&lt;/option&gt;
			&lt;object class="wxBoxSizer"&gt;
				&lt;orient&gt;wxHORIZONTAL&lt;/orient&gt;
				&lt;object class="sizeritem"&gt;
					&lt;flag&gt;wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
					&lt;border&gt;5&lt;/border&gt;
					&lt;option&gt;1&lt;/option&gt;
					&lt;object class="wxStaticText" name="lbl<xsl:value-of select="$FieldName"/>"&gt;
						&lt;label&gt;<xsl:value-of select="$FieldName"/>&lt;/label&gt;
					&lt;/object&gt;
				&lt;/object&gt;
				&lt;object class="sizeritem"&gt;
					&lt;flag>wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
					&lt;border&gt;5&lt;/border&gt;
					&lt;option&gt;1&lt;/option&gt;
					&lt;object class="wxCheckBox" name="<xsl:value-of select="$FieldName"/>"&gt;
					&lt;/object&gt;
				&lt;/object&gt;
			&lt;/object&gt;
		&lt;/object&gt;
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
		&lt;object class="sizeritem"&gt;
			&lt;flag&gt;wxGROW|wxALL&lt;/flag&gt;
			&lt;border&gt;5&lt;/border&gt;
			&lt;option&gt;1&lt;/option&gt;
			&lt;object class="wxBoxSizer"&gt;
				&lt;orient&gt;wxHORIZONTAL&lt;/orient&gt;
				&lt;object class="sizeritem"&gt;
					&lt;flag&gt;wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
					&lt;border&gt;5&lt;/border&gt;
					&lt;option&gt;1&lt;/option&gt;
					&lt;object class="wxStaticText" name="lbl<xsl:value-of select="$FieldName"/>"&gt;
						&lt;label&gt;<xsl:value-of select="$FieldName"/>&lt;/label&gt;
					&lt;/object&gt;
				&lt;/object&gt;
				&lt;object class="sizeritem"&gt;
					&lt;flag>wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
					&lt;border&gt;5&lt;/border&gt;
					&lt;option&gt;1&lt;/option&gt;
					&lt;object class="wxTextCtrl" name="<xsl:value-of select="$FieldName"/>"&gt;
					&lt;/object&gt;
				&lt;/object&gt;
			&lt;/object&gt;
		&lt;/object&gt;
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
		&lt;object class="sizeritem"&gt;
			&lt;flag&gt;wxGROW|wxALL&lt;/flag&gt;
			&lt;border&gt;5&lt;/border&gt;
			&lt;option&gt;1&lt;/option&gt;
			&lt;object class="wxBoxSizer"&gt;
				&lt;orient&gt;wxHORIZONTAL&lt;/orient&gt;
				&lt;object class="sizeritem"&gt;
					&lt;flag&gt;wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
					&lt;border&gt;5&lt;/border&gt;
					&lt;option&gt;1&lt;/option&gt;
					&lt;object class="wxStaticText" name="lbl<xsl:value-of select="$FieldName"/>"&gt;
						&lt;label&gt;<xsl:value-of select="$FieldName"/>&lt;/label&gt;
					&lt;/object&gt;
				&lt;/object&gt;
				&lt;object class="sizeritem"&gt;
					&lt;flag>wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
					&lt;border&gt;5&lt;/border&gt;
					&lt;option&gt;1&lt;/option&gt;
					&lt;object class="wxTextCtrl" name="<xsl:value-of select="$FieldName"/>"&gt;
					&lt;/object&gt;
				&lt;/object&gt;
			&lt;/object&gt;
		&lt;/object&gt;
			</xsl:when>
			<xsl:when test="@dbtype='String'">
		&lt;object class="sizeritem"&gt;
			&lt;flag&gt;wxGROW|wxALL&lt;/flag&gt;
			&lt;border&gt;5&lt;/border&gt;
			&lt;option&gt;1&lt;/option&gt;
			&lt;object class="wxBoxSizer"&gt;
				&lt;orient&gt;wxHORIZONTAL&lt;/orient&gt;
				&lt;object class="sizeritem"&gt;
					&lt;flag&gt;wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
					&lt;border&gt;5&lt;/border&gt;
					&lt;option&gt;1&lt;/option&gt;
					&lt;object class="wxStaticText" name="lbl<xsl:value-of select="$FieldName"/>"&gt;
						&lt;label&gt;<xsl:value-of select="$FieldName"/>&lt;/label&gt;
					&lt;/object&gt;
				&lt;/object&gt;
				&lt;object class="sizeritem"&gt;
					&lt;flag>wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
					&lt;border&gt;5&lt;/border&gt;
					&lt;option&gt;1&lt;/option&gt;
					&lt;object class="wxTextCtrl" name="<xsl:value-of select="$FieldName"/>"&gt;
					&lt;/object&gt;
				&lt;/object&gt;
			&lt;/object&gt;
		&lt;/object&gt;
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:template>

<xsl:template name="createFormClassImplXRCLayout_Panel_AddDelete">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="ParamFormularName"/>
            &lt;object class="sizeritem"&gt;
                &lt;flag&gt;0&lt;/flag&gt;
                &lt;border&gt;0&lt;/border&gt;
                &lt;object class="wxBoxSizer"&gt;
                    &lt;orient&gt;wxHORIZONTAL&lt;/orient&gt;
                    &lt;object class="sizeritem"&gt;
                        &lt;flag&gt;wxGROW|wxALL&lt;/flag&gt;
                        &lt;border&gt;5&lt;/border&gt;
                        &lt;option&gt;1&lt;/option&gt;
                        &lt;object class="wxButton" name="Add"&gt;
                            &lt;label&gt;Add&lt;/label&gt;
                        &lt;/object&gt;
                    &lt;/object&gt;
                    &lt;object class="sizeritem"&gt;
                        &lt;flag&gt;wxGROW|wxALL&lt;/flag&gt;
                        &lt;border&gt;5&lt;/border&gt;
                        &lt;option&gt;1&lt;/option&gt;
                        &lt;object class="wxButton" name="Delete"&gt;
                            &lt;label&gt;Delete&lt;/label&gt;
                        &lt;/object&gt;
                    &lt;/object&gt;
                &lt;/object&gt;
            &lt;/object&gt;
</xsl:template>

<xsl:template name="createFormClassImplXRCLayout_Panel_Navi">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="ParamFormularName"/>
            &lt;object class="sizeritem"&gt;
                &lt;flag&gt;wxALIGN_CENTER_HORIZONTAL|wxALL&lt;/flag&gt;
                &lt;border&gt;5&lt;/border&gt;
                &lt;option&gt;1&lt;/option&gt;
                &lt;object class="wxBoxSizer"&gt;
                    &lt;orient&gt;wxHORIZONTAL&lt;/orient&gt;
                    &lt;object class="sizeritem"&gt;
                        &lt;flag&gt;wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
                        &lt;border&gt;5&lt;/border&gt;
                        &lt;option&gt;1&lt;/option&gt;
                        &lt;object class="wxButton" name="First"&gt;
                            &lt;label&gt;First&lt;/label&gt;
                        &lt;/object&gt;
                    &lt;/object&gt;
                    &lt;object class="sizeritem"&gt;
                        &lt;flag&gt;wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
                        &lt;border&gt;5&lt;/border&gt;
                        &lt;option&gt;1&lt;/option&gt;
                        &lt;object class="wxButton" name="Prev"&gt;
                            &lt;label&gt;Prev&lt;/label&gt;
                        &lt;/object&gt;
                    &lt;/object&gt;
                    &lt;object class="sizeritem"&gt;
                        &lt;flag&gt;wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
                        &lt;border&gt;5&lt;/border&gt;
                        &lt;option&gt;1&lt;/option&gt;
                        &lt;object class="wxButton" name="Next"&gt;
                            &lt;label&gt;Next&lt;/label&gt;
                        &lt;/object&gt;
                    &lt;/object&gt;
                    &lt;object class="sizeritem"&gt;
                        &lt;flag&gt;wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
                        &lt;border&gt;5&lt;/border&gt;
                        &lt;option&gt;1&lt;/option&gt;
                        &lt;object class="wxButton" name="Last"&gt;
                            &lt;label&gt;Last&lt;/label&gt;
                        &lt;/object&gt;
                    &lt;/object&gt;
                &lt;/object&gt;
            &lt;/object&gt;
</xsl:template>

<xsl:template name="createFormClassImplXRCLayout_Panel_Actions">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="ParamFormularName"/>
            &lt;object class="sizeritem"&gt;
                &lt;flag&gt;wxGROW|wxALL&lt;/flag&gt;
                &lt;border&gt;5&lt;/border&gt;
                &lt;option&gt;1&lt;/option&gt;
                &lt;object class="wxBoxSizer"&gt;
                    &lt;orient&gt;wxHORIZONTAL&lt;/orient&gt;
<xsl:for-each select="//lbDMF/formularactions/action[@formularid=$FormularID]">
<xsl:variable name="EventIdentifer">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="@event"/>
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
	<xsl:variable name="ActionID" select="@actionid"/>&lt;object class="sizeritem"&gt;
                        &lt;flag&gt;wxALIGN_CENTER_VERTICAL|wxALL&lt;/flag&gt;
                        &lt;border&gt;5&lt;/border&gt;
                        &lt;option&gt;1&lt;/option&gt;
                        &lt;object class="wxButton" name="<xsl:value-of select="//lbDMF/actions/action[@ID=$ActionID]/@name"/>"&gt;
                            &lt;label&gt;<xsl:value-of select="//lbDMF/actions/action[@ID=$ActionID]/@name"/>&lt;/label&gt;
                        &lt;/object&gt;
                    &lt;/object&gt;
<xsl:call-template name="create_button_control">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="//lbDMF/actions/action[@ID=$ActionID]/@name"/></xsl:with-param>
</xsl:call-template>
</xsl:for-each>
                &lt;/object&gt;
            &lt;/object&gt;
</xsl:template>


<xsl:template name="createFormClassImplXRCLayout_Panel">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="ParamFormularName"/>&lt;object class="wxPanel" name="ID_<xsl:value-of select="$ApplicationName"/><xsl:value-of select="$ParamFormularName"/>PANEL" subclass="<xsl:value-of select="$ApplicationName"/><xsl:value-of select="$ParamFormularName"/>Panel"&gt;
        &lt;size&gt;400,300&lt;/size&gt;
        &lt;object class="wxBoxSizer"&gt;
            &lt;orient&gt;wxVERTICAL&lt;/orient&gt;
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<!-- Data fields -->
<xsl:call-template name="createFormClassImplXRCLayout_Panel_Field">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="ParamFormularName"><xsl:value-of select="$ParamFormularName"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="TableName"><xsl:value-of select="$TableName"/></xsl:with-param>
</xsl:call-template>
</xsl:for-each>
<!-- Action buttons -->
<xsl:call-template name="createFormClassImplXRCLayout_Panel_Actions">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="ParamFormularName"><xsl:value-of select="$ParamFormularName"/></xsl:with-param>
</xsl:call-template>
<!-- Add and delete buttons -->
<xsl:call-template name="createFormClassImplXRCLayout_Panel_AddDelete">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="ParamFormularName"><xsl:value-of select="$ParamFormularName"/></xsl:with-param>
</xsl:call-template>
<!-- Navigation buttons -->
<xsl:call-template name="createFormClassImplXRCLayout_Panel_Navi">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="ParamFormularName"><xsl:value-of select="$ParamFormularName"/></xsl:with-param>
</xsl:call-template>
        &lt;/object&gt;
    &lt;/object&gt;
</xsl:template>

<xsl:template name="createFormClassImplXRCLayout_ClassImpl">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
</xsl:template>

<xsl:template name="createFormClassImplXRCLayout_ClassDecl">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
</xsl:template>


<xsl:template name="createFormClassImplXRCLayout_InitRountine">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>


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

// Initialization of the form via source code
#include &lt;wx/xrc/xmlres.h&gt;

void LB_STDCALL <xsl:value-of select="$FormularName"/>::init() {
	lbErrCodes err = ERR_NONE;
	char prefix[100] = "";
	sprintf(prefix, "%p", this);

	_LOG &lt;&lt; "<xsl:value-of select="$FormularName"/>::init() called." LOG_

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, params)
	
	if (ImageButtonMapperList == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, ImageButtonMapperList)
	}
		
	SetName(formName);

    if (!wxXmlResource::Get()->LoadPanel(this, NULL, _T("ID_<xsl:value-of select="$ApplicationName"/><xsl:value-of select="$FormularName"/>PANEL"))) {
        _LOG &lt;&lt; "Missing wxXmlResource::Get()-&gt;Load() in OnInit()?" LOG_
	}
	
	if (database != NULL) {
		_CL_LOG &lt;&lt; "WARNING: Database instance available!" LOG_
	}
	
	REQUEST(manager.getPtr(), lb_I_Database, database)

	database->init();
	if (database->connect("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 
						"<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 
	"<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBUser'][@applicationid=$ApplicationID]/@value"/>", "<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBPass'][@applicationid=$ApplicationID]/@value"/>") != ERR_NONE) {
		_LOG &lt;&lt; "Error: Could not connect to given database: '" &lt;&lt; DBName->charrep() &lt;&lt; "'" LOG_

		return;
	}

	if (_DBName == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, _DBName)
		_DBName->setData("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>");
	}
	if (_DBUser == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, _DBUser)
		_DBUser->setData("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBUser'][@applicationid=$ApplicationID]/@value"/>");
	}
	if (_DBPass == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, _DBPass)
		_DBPass->setData("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBPass'][@applicationid=$ApplicationID]/@value"/>");
	}

	sampleQuery = database->getQuery("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 0);

	int DatabaseFirst;
	int DatabaseNext;
	int DatabasePrev;
	int DatabaseLast;
	int DatabaseAdd;
	int DatabaseDelete;
	
	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, eman)
	UAP_REQUEST(manager.getPtr(), lb_I_Dispatcher, dispatcher)

	char eventName[100] = "";
		
	sprintf(eventName, "%pDatabaseFirst", this);
	eman->registerEvent(eventName, DatabaseFirst);

	sprintf(eventName, "%pDatabaseNext", this);
	eman->registerEvent(eventName,  DatabaseNext);

	sprintf(eventName, "%pDatabasePrev", this);
	eman->registerEvent(eventName,  DatabasePrev);

	sprintf(eventName, "%pDatabaseLast", this);
	eman->registerEvent(eventName,  DatabaseLast);

	sprintf(eventName, "%pDatabaseAdd", this);
	eman->registerEvent(eventName,  DatabaseAdd);

	sprintf(eventName, "%pDatabaseDelete", this);
	eman->registerEvent(eventName,  DatabaseDelete);

	sprintf(eventName, "%pImageButtonClick", this);
	eman->registerEvent(eventName,  DatabaseDelete);

	dispatcher-&gt;setEventManager(eman.getPtr());

	registerEventHandler(dispatcher.getPtr());

	/// Did I need that here ? 
	sampleQuery-&gt;enableFKCollecting();

	sampleQuery-&gt;setAutoRefresh(meta->getAutorefreshData());

	if (SQLString == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SQLString)
<xsl:variable name="tempQuery" select="//lbDMF/formularparameter/parameter[@formularid=$FormularID][@name='query']/@value"/>
<xsl:variable name="Query">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempQuery"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'&quot;'"/>
		<xsl:with-param name="substringOut" select="'\&quot;'"/>
	</xsl:call-template>
</xsl:variable>
		SQLString->setData("<xsl:value-of select="$Query"/>");
	}

	sampleQuery->query(SQLString->charrep(), false);

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:for-each select="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@readonly='1']">
	sampleQuery->setReadonly("<xsl:value-of select="@name"/>"); // <xsl:value-of select="@tablename"/>
</xsl:for-each>
</xsl:for-each>
	sampleQuery-&gt;bind();
	sampleQuery-&gt;first();

	//UAP(lb_I_String, s)
	//int i = 0;
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
	// FK <xsl:value-of select="@name"/>
	// Create a mapping instance for this combo box
	UAP(lb_I_Unknown, ukComboboxMapper_<xsl:value-of select="@name"/>)
	UAP(lb_I_Container, ComboboxMapper_<xsl:value-of select="@name"/>)

	UAP_REQUEST(manager.getPtr(), lb_I_String, cbName_<xsl:value-of select="@name"/>)
	UAP(lb_I_KeyBase, key_cbName_<xsl:value-of select="@name"/>)
	QI(cbName_<xsl:value-of select="@name"/>, lb_I_KeyBase, key_cbName_<xsl:value-of select="@name"/>)

	// This is the input parameter

	cbName_<xsl:value-of select="@name"/>->setData("<xsl:value-of select="@name"/>");

	wxChoice *cbox_<xsl:value-of select="@name"/>;

		
	cbox_<xsl:value-of select="@name"/> = (wxChoice*) FindWindowByName("<xsl:value-of select="@name"/>", this);
	getForeignKeyMappingData_<xsl:value-of select="@name"/>(cbox_<xsl:value-of select="@name"/>);

	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
	// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
	// Normal Bit column <xsl:value-of select="@name"/>
	wxCheckBox *check<xsl:value-of select="@name"/>;
	check<xsl:value-of select="@name"/> = (wxCheckBox*) FindWindowByName("<xsl:value-of select="@name"/>", this);
				<xsl:for-each select="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@readonly='1']">
	check<xsl:value-of select="@name"/>-&gt;Disable();
				</xsl:for-each>
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
	// Normal Float column <xsl:value-of select="@name"/>
	wxTextValidator val<xsl:value-of select="@name"/> = wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST, new wxString(""));
						
	wxArrayString ValArray<xsl:value-of select="@name"/>;
	ValArray<xsl:value-of select="@name"/>.Add(".");
	ValArray<xsl:value-of select="@name"/>.Add("-");
	ValArray<xsl:value-of select="@name"/>.Add("0");
	ValArray<xsl:value-of select="@name"/>.Add("1");
	ValArray<xsl:value-of select="@name"/>.Add("2");
	ValArray<xsl:value-of select="@name"/>.Add("3");
	ValArray<xsl:value-of select="@name"/>.Add("4");
	ValArray<xsl:value-of select="@name"/>.Add("5");
	ValArray<xsl:value-of select="@name"/>.Add("6");
	ValArray<xsl:value-of select="@name"/>.Add("7");
	ValArray<xsl:value-of select="@name"/>.Add("8");
	ValArray<xsl:value-of select="@name"/>.Add("9");
						
	val<xsl:value-of select="@name"/>.SetIncludes(ValArray<xsl:value-of select="@name"/>);

	//s = sampleQuery-&gt;getAsString(++i);
						
	wxTextCtrl *text<xsl:value-of select="@name"/>;
	text<xsl:value-of select="@name"/> = (wxTextCtrl*) FindWindowByName("<xsl:value-of select="@name"/>", this);
	text<xsl:value-of select="@name"/>-&gt;SetValidator(val<xsl:value-of select="@name"/>);
				<xsl:for-each select="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@readonly='1']">
	text<xsl:value-of select="@name"/>-&gt;Disable();
				</xsl:for-each>
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
	// Normal Integer column <xsl:value-of select="@name"/>
	wxTextValidator val<xsl:value-of select="@name"/> = wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST, new wxString(""));
						
	wxArrayString ValArray<xsl:value-of select="@name"/>;
	ValArray<xsl:value-of select="@name"/>.Add("0");
	ValArray<xsl:value-of select="@name"/>.Add("1");
	ValArray<xsl:value-of select="@name"/>.Add("2");
	ValArray<xsl:value-of select="@name"/>.Add("3");
	ValArray<xsl:value-of select="@name"/>.Add("4");
	ValArray<xsl:value-of select="@name"/>.Add("5");
	ValArray<xsl:value-of select="@name"/>.Add("6");
	ValArray<xsl:value-of select="@name"/>.Add("7");
	ValArray<xsl:value-of select="@name"/>.Add("8");
	ValArray<xsl:value-of select="@name"/>.Add("9");
	ValArray<xsl:value-of select="@name"/>.Add("-");
						
	val<xsl:value-of select="@name"/>.SetIncludes(ValArray<xsl:value-of select="@name"/>);

	//s = sampleQuery-&gt;getAsString(++i);
					
	wxTextCtrl *text<xsl:value-of select="@name"/>;
	text<xsl:value-of select="@name"/> = (wxTextCtrl*) FindWindowByName("<xsl:value-of select="@name"/>", this);
	text<xsl:value-of select="@name"/>-&gt;SetValidator(val<xsl:value-of select="@name"/>);
	<xsl:for-each select="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@readonly='1']">
	text<xsl:value-of select="@name"/>-&gt;Disable();
	</xsl:for-each>
			</xsl:when>
			<xsl:when test="@dbtype='String'">
	// Normal String column <xsl:value-of select="@name"/>
						
	//s = sampleQuery->getAsString(++i);
						
	wxTextCtrl *text<xsl:value-of select="@name"/>;
	text<xsl:value-of select="@name"/> = (wxTextCtrl*) FindWindowByName("<xsl:value-of select="@name"/>", this);
	<xsl:for-each select="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@readonly='1']">
	text<xsl:value-of select="@name"/>-&gt;Disable();
	</xsl:for-each>
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

	wxButton *button1 = (wxButton*) FindWindowByName("First", this);
	wxButton *button2 = (wxButton*) FindWindowByName("Prev", this);
	wxButton *button3 = (wxButton*) FindWindowByName("Next", this);
	wxButton *button4 = (wxButton*) FindWindowByName("Last", this);
	
	// Remap the IDs to correctly route the events
	button1-&gt;SetId(DatabaseFirst);
	button2-&gt;SetId(DatabasePrev);
	button3-&gt;SetId(DatabaseNext);
	button4-&gt;SetId(DatabaseLast);
	
	firstButton = button1;
	prevButton = button2;
	nextButton = button3;
	lastButton = button4;

	button1-&gt;Disable();
	button2-&gt;Disable();

	wxButton *buttonAdd = (wxButton*) FindWindowByName("Add", this);
	wxButton *buttonDelete = (wxButton*) FindWindowByName("Delete", this);

	deleteButton = buttonDelete;
	addingButton = buttonAdd;
	int actionID = 0;

// Don't distinguish between action types
<xsl:for-each select="//lbDMF/formularactions/action[@formularid=$FormularID]">

<xsl:variable name="EventIdentifer">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="@event"/>
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

	UAP_REQUEST(getModuleInstance(), lb_I_String, actionWhat<xsl:value-of select="$EventIdentifer"/>)
	*actionWhat<xsl:value-of select="$EventIdentifer"/> = "<xsl:value-of select="@event"/>";
	char *eventName<xsl:value-of select="$EventIdentifer"/> = (char*) malloc(strlen(actionWhat<xsl:value-of select="$EventIdentifer"/>-&gt;charrep()) + 20);
	sprintf(eventName<xsl:value-of select="$EventIdentifer"/>, "%p(%s)", this, actionWhat<xsl:value-of select="$EventIdentifer"/>->charrep());
	eman->registerEvent(eventName<xsl:value-of select="$EventIdentifer"/>, actionID);
	
	_LOG &lt;&lt; "Registered action '<xsl:value-of select="@event"/>' to '" &lt;&lt; eventName<xsl:value-of select="$EventIdentifer"/> &lt;&lt; "' actionID " &lt;&lt; actionID LOG_
	
	<xsl:variable name="ActionID" select="@actionid"/>
	wxButton *actionButton<xsl:value-of select="$EventIdentifer"/>; // = new wxButton(this, actionID, _trans("<xsl:value-of select="//lbDMF/actions/action[@ID=$ActionID]/@name"/>")); //, wxPoint(), wxSize(100,20));

	actionButton<xsl:value-of select="$EventIdentifer"/> = (wxButton*) FindWindowByName("<xsl:value-of select="//lbDMF/actions/action[@ID=$ActionID]/@name"/>", this);
	actionButton<xsl:value-of select="$EventIdentifer"/>-&gt;SetId(actionID);


	dispatcher-&gt;addEventHandlerFn(this, (lbEvHandler) &amp;<xsl:value-of select="$FormularName"/>::OnActionButton_<xsl:value-of select="$EventIdentifer"/>, eventName<xsl:value-of select="$EventIdentifer"/>);
	this-&gt;Connect( actionID,  -1, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &amp;<xsl:value-of select="$FormularName"/>::OnDispatch);
	//sizerActions-&gt;Add(actionButton<xsl:value-of select="$EventIdentifer"/>, 1, wxEXPAND | wxALL, 5);
	free(eventName<xsl:value-of select="$EventIdentifer"/>);
</xsl:for-each>

	this->Connect( DatabaseFirst,  -1, wxEVT_COMMAND_BUTTON_CLICKED, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &amp;<xsl:value-of select="$FormularName"/>::OnDispatch);
	this-&gt;Connect( DatabaseNext,  -1, wxEVT_COMMAND_BUTTON_CLICKED,  
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &amp;<xsl:value-of select="$FormularName"/>::OnDispatch);
	this-&gt;Connect( DatabasePrev,  -1, wxEVT_COMMAND_BUTTON_CLICKED,  
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &amp;<xsl:value-of select="$FormularName"/>::OnDispatch);
	this-&gt;Connect( DatabaseLast,  -1, wxEVT_COMMAND_BUTTON_CLICKED,  
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &amp;<xsl:value-of select="$FormularName"/>::OnDispatch);

	this-&gt;Connect( DatabaseAdd,  -1, wxEVT_COMMAND_BUTTON_CLICKED,   
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &amp;<xsl:value-of select="$FormularName"/>::OnDispatch);
	this-&gt;Connect( DatabaseDelete, -1, wxEVT_COMMAND_BUTTON_CLICKED, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &amp;<xsl:value-of select="$FormularName"/>::OnDispatch);

	SetAutoLayout(TRUE);
	
	if (sampleQuery-&gt;dataFetched()) {
		sampleQuery-&gt;first();
		lbDBRead();
	} else {
		nextButton-&gt;Disable();
		lastButton-&gt;Disable();
		deleteButton-&gt;Disable();
	}
	_created = true;
}


</xsl:template>

</xsl:stylesheet>
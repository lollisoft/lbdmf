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
            Ginsterweg 4
            
            65760 Eschborn (germany)
-->
<xsl:import href="../include/exsl.xsl"/>

<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>


<xsl:template name="create_boxsizer_prefix_horizontal">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
              &lt;string name="title"&gt;"wxBoxSizer H"&lt;/string&gt;
              &lt;string name="type"&gt;"dialog-control-document"&lt;/string&gt;
              &lt;string name="filename"&gt;""&lt;/string&gt;
              &lt;string name="icon-name"&gt;"sizer"&lt;/string&gt;
              &lt;long name="is-transient"&gt;0&lt;/long&gt;
              &lt;long name="owns-file"&gt;1&lt;/long&gt;
              &lt;long name="title-mode"&gt;0&lt;/long&gt;
              &lt;long name="locked"&gt;0&lt;/long&gt;
              &lt;string name="created"&gt;"11/11/2007"&lt;/string&gt;
              &lt;string name="proxy-type"&gt;"wbBoxSizerProxy"&lt;/string&gt;
              &lt;string name="proxy-Orientation"&gt;"Horizontal"&lt;/string&gt;
              &lt;string name="proxy-Member variable name"&gt;""&lt;/string&gt;
              &lt;string name="proxy-AlignH"&gt;"Expand"&lt;/string&gt;
              &lt;string name="proxy-AlignV"&gt;"Centre"&lt;/string&gt;
              &lt;long name="proxy-Stretch factor"&gt;1&lt;/long&gt;
              &lt;long name="proxy-Border"&gt;5&lt;/long&gt;
              &lt;bool name="proxy-wxLEFT"&gt;1&lt;/bool&gt;
              &lt;bool name="proxy-wxRIGHT"&gt;1&lt;/bool&gt;
              &lt;bool name="proxy-wxTOP"&gt;1&lt;/bool&gt;
              &lt;bool name="proxy-wxBOTTOM"&gt;1&lt;/bool&gt;
              &lt;bool name="proxy-wxSHAPED"&gt;0&lt;/bool&gt;
              &lt;bool name="proxy-wxADJUST_MINSIZE"&gt;0&lt;/bool&gt;
              &lt;bool name="proxy-wxFIXED_MINSIZE"&gt;0&lt;/bool&gt;
              &lt;string name="proxy-Platform"&gt;"&amp;lt;Any platform&amp;gt;"&lt;/string&gt;
</xsl:template>

<xsl:template name="create_boxsizer_prefix_vertical">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
            &lt;string name="title"&gt;"wxBoxSizer V"&lt;/string&gt;
            &lt;string name="type"&gt;"dialog-control-document"&lt;/string&gt;
            &lt;string name="filename"&gt;""&lt;/string&gt;
            &lt;string name="icon-name"&gt;"sizer"&lt;/string&gt;
            &lt;long name="is-transient"&gt;0&lt;/long&gt;
            &lt;long name="owns-file"&gt;1&lt;/long&gt;
            &lt;long name="title-mode"&gt;0&lt;/long&gt;
            &lt;long name="locked"&gt;0&lt;/long&gt;
            &lt;string name="created"&gt;"11/11/2007"&lt;/string&gt;
            &lt;string name="proxy-type"&gt;"wbBoxSizerProxy"&lt;/string&gt;
            &lt;string name="proxy-Orientation"&gt;"Vertical"&lt;/string&gt;
            &lt;string name="proxy-Member variable name"&gt;""&lt;/string&gt;
            &lt;string name="proxy-AlignH"&gt;"Centre"&lt;/string&gt;
            &lt;string name="proxy-AlignV"&gt;"Centre"&lt;/string&gt;
            &lt;long name="proxy-Stretch factor"&gt;0&lt;/long&gt;
            &lt;long name="proxy-Border"&gt;5&lt;/long&gt;
            &lt;bool name="proxy-wxLEFT"&gt;1&lt;/bool&gt;
            &lt;bool name="proxy-wxRIGHT"&gt;1&lt;/bool&gt;
            &lt;bool name="proxy-wxTOP"&gt;1&lt;/bool&gt;
            &lt;bool name="proxy-wxBOTTOM"&gt;1&lt;/bool&gt;
            &lt;bool name="proxy-wxSHAPED"&gt;0&lt;/bool&gt;
            &lt;bool name="proxy-wxADJUST_MINSIZE"&gt;0&lt;/bool&gt;
            &lt;bool name="proxy-wxFIXED_MINSIZE"&gt;0&lt;/bool&gt;
            &lt;string name="proxy-Platform"&gt;"&amp;lt;Any platform&amp;gt;"&lt;/string&gt;
</xsl:template>

<xsl:template name="create_static_text">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="FieldName"/>
		<xsl:param name="ItemID"/>
                &lt;string name="title"&gt;"wxStaticText: ID_<xsl:value-of select="$FieldName"/>"&lt;/string&gt;
                &lt;string name="type"&gt;"dialog-control-document"&lt;/string&gt;
                &lt;string name="filename"&gt;""&lt;/string&gt;
                &lt;string name="icon-name"&gt;"statictext"&lt;/string&gt;
                &lt;long name="is-transient"&gt;0&lt;/long&gt;
                &lt;long name="owns-file"&gt;1&lt;/long&gt;
                &lt;long name="title-mode"&gt;0&lt;/long&gt;
                &lt;long name="locked"&gt;0&lt;/long&gt;
                &lt;string name="created"&gt;"11/11/2007"&lt;/string&gt;
                &lt;string name="proxy-type"&gt;"wbStaticTextProxy"&lt;/string&gt;
                &lt;string name="proxy-Id name"&gt;"lbl<xsl:value-of select="$FieldName"/>"&lt;/string&gt;
                &lt;long name="proxy-Id value"&gt;<xsl:value-of select="5000+$ItemID"/>&lt;/long&gt;
                &lt;string name="proxy-Class"&gt;"wxStaticText"&lt;/string&gt;
                &lt;string name="proxy-Base class"&gt;"wxStaticText"&lt;/string&gt;
                &lt;bool name="proxy-External implementation"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-Separate files"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Implementation filename"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Header filename"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Member variable name"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Label"&gt;"<xsl:value-of select="$FieldName"/>"&lt;/string&gt;
                &lt;long name="proxy-Wrapping width"&gt;-1&lt;/long&gt;
                &lt;string name="proxy-Help text"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Tooltip text"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Background colour"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Foreground colour"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Font"&gt;""&lt;/string&gt;
                &lt;bool name="proxy-Hidden"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-Enabled"&gt;1&lt;/bool&gt;
                &lt;string name="proxy-Platform"&gt;"&amp;lt;Any platform&amp;gt;"&lt;/string&gt;
                &lt;string name="proxy-Data variable"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Data validator"&gt;""&lt;/string&gt;
                &lt;bool name="proxy-wxALIGN_LEFT"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxALIGN_RIGHT"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxALIGN_CENTRE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxST_NO_AUTORESIZE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxNO_BORDER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxSIMPLE_BORDER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxDOUBLE_BORDER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxSUNKEN_BORDER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxRAISED_BORDER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxSTATIC_BORDER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxWANTS_CHARS"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxNO_FULL_REPAINT_ON_RESIZE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxFULL_REPAINT_ON_RESIZE"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Custom styles"&gt;""&lt;/string&gt;
                &lt;long name="proxy-X"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Y"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Width"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Height"&gt;-1&lt;/long&gt;
                &lt;string name="proxy-AlignH"&gt;"Centre"&lt;/string&gt;
                &lt;string name="proxy-AlignV"&gt;"Centre"&lt;/string&gt;
                &lt;long name="proxy-Stretch factor"&gt;1&lt;/long&gt;
                &lt;long name="proxy-Border"&gt;5&lt;/long&gt;
                &lt;bool name="proxy-wxLEFT"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxRIGHT"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxTOP"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxBOTTOM"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxSHAPED"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxADJUST_MINSIZE"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxFIXED_MINSIZE"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Custom arguments"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Custom ctor arguments"&gt;""&lt;/string&gt;
</xsl:template>

<xsl:template name="create_text_control">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="FieldName"/>
		<xsl:param name="ItemID"/>
                &lt;string name="title"&gt;"wxTextCtrl: ID_<xsl:value-of select="$FieldName"/>"&lt;/string&gt;
                &lt;string name="type"&gt;"dialog-control-document"&lt;/string&gt;
                &lt;string name="filename"&gt;""&lt;/string&gt;
                &lt;string name="icon-name"&gt;"textctrl"&lt;/string&gt;
                &lt;long name="is-transient"&gt;0&lt;/long&gt;
                &lt;long name="owns-file"&gt;1&lt;/long&gt;
                &lt;long name="title-mode"&gt;0&lt;/long&gt;
                &lt;long name="locked"&gt;0&lt;/long&gt;
                &lt;string name="created"&gt;"11/11/2007"&lt;/string&gt;
                &lt;string name="proxy-type"&gt;"wbTextCtrlProxy"&lt;/string&gt;
                &lt;string name="proxy-Id name"&gt;"<xsl:value-of select="$FieldName"/>"&lt;/string&gt;
                &lt;long name="proxy-Id value"&gt;<xsl:value-of select="6000+$ItemID"/>&lt;/long&gt;
                &lt;string name="proxy-Class"&gt;"wxTextCtrl"&lt;/string&gt;
                &lt;string name="proxy-Base class"&gt;"wxTextCtrl"&lt;/string&gt;
                &lt;bool name="proxy-External implementation"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-Separate files"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Implementation filename"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Header filename"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Member variable name"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Initial value"&gt;""&lt;/string&gt;
                &lt;long name="proxy-Max length"&gt;0&lt;/long&gt;
                &lt;string name="proxy-Help text"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Tooltip text"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Background colour"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Foreground colour"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Font"&gt;""&lt;/string&gt;
                &lt;bool name="proxy-Hidden"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-Enabled"&gt;1&lt;/bool&gt;
                &lt;string name="proxy-Platform"&gt;"&amp;lt;Any platform&amp;gt;"&lt;/string&gt;
                &lt;string name="proxy-Data variable"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Data validator"&gt;""&lt;/string&gt;
                &lt;bool name="proxy-wxTE_MULTILINE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxTE_PROCESS_ENTER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxTE_PROCESS_TAB"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxTE_PASSWORD"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxTE_READONLY"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxTE_RICH"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxTE_RICH2"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxTE_AUTO_URL"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxTE_NOHIDESEL"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxTE_LEFT"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxTE_CENTRE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxTE_RIGHT"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxHSCROLL"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxTE_CHARWRAP"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxTE_WORDWRAP"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxNO_BORDER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxSIMPLE_BORDER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxDOUBLE_BORDER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxSUNKEN_BORDER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxRAISED_BORDER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxSTATIC_BORDER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxWANTS_CHARS"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxNO_FULL_REPAINT_ON_RESIZE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxFULL_REPAINT_ON_RESIZE"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Custom styles"&gt;""&lt;/string&gt;
                &lt;long name="proxy-X"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Y"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Width"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Height"&gt;-1&lt;/long&gt;
                &lt;string name="proxy-AlignH"&gt;"Centre"&lt;/string&gt;
                &lt;string name="proxy-AlignV"&gt;"Centre"&lt;/string&gt;
                &lt;long name="proxy-Stretch factor"&gt;1&lt;/long&gt;
                &lt;long name="proxy-Border"&gt;5&lt;/long&gt;
                &lt;bool name="proxy-wxLEFT"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxRIGHT"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxTOP"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxBOTTOM"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxSHAPED"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxADJUST_MINSIZE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxFIXED_MINSIZE"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Custom arguments"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Custom ctor arguments"&gt;""&lt;/string&gt;
</xsl:template>

<xsl:template name="create_choice_control">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="FieldName"/>
		<xsl:param name="ItemID"/>
                &lt;string name="title"&gt;"wxChoice: ID_<xsl:value-of select="$FieldName"/>"&lt;/string&gt;
                &lt;string name="type"&gt;"dialog-control-document"&lt;/string&gt;
                &lt;string name="filename"&gt;""&lt;/string&gt;
                &lt;string name="icon-name"&gt;"choice"&lt;/string&gt;
                &lt;long name="is-transient"&gt;0&lt;/long&gt;
                &lt;long name="owns-file"&gt;1&lt;/long&gt;
                &lt;long name="title-mode"&gt;0&lt;/long&gt;
                &lt;long name="locked"&gt;0&lt;/long&gt;
                &lt;string name="created"&gt;"11/11/2007"&lt;/string&gt;
                &lt;string name="proxy-type"&gt;"wbChoiceProxy"&lt;/string&gt;
                &lt;string name="proxy-Id name"&gt;"ID_<xsl:value-of select="$FieldName"/>"&lt;/string&gt;
                &lt;long name="proxy-Id value"&gt;<xsl:value-of select="7000+$ItemID"/>&lt;/long&gt;
                &lt;string name="proxy-Class"&gt;"wxChoice"&lt;/string&gt;
                &lt;string name="proxy-Base class"&gt;"wxChoice"&lt;/string&gt;
                &lt;bool name="proxy-External implementation"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-Separate files"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Implementation filename"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Header filename"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Member variable name"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Strings"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Initial value"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Help text"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Tooltip text"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Background colour"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Foreground colour"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Font"&gt;""&lt;/string&gt;
                &lt;bool name="proxy-Hidden"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-Enabled"&gt;1&lt;/bool&gt;
                &lt;string name="proxy-Platform"&gt;"&amp;lt;Any platform&amp;gt;"&lt;/string&gt;
                &lt;string name="proxy-Data variable"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Data validator"&gt;""&lt;/string&gt;
                &lt;bool name="proxy-wxWANTS_CHARS"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxNO_FULL_REPAINT_ON_RESIZE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxFULL_REPAINT_ON_RESIZE"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Custom styles"&gt;""&lt;/string&gt;
                &lt;long name="proxy-X"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Y"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Width"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Height"&gt;-1&lt;/long&gt;
                &lt;string name="proxy-AlignH"&gt;"Centre"&lt;/string&gt;
                &lt;string name="proxy-AlignV"&gt;"Centre"&lt;/string&gt;
                &lt;long name="proxy-Stretch factor"&gt;1&lt;/long&gt;
                &lt;long name="proxy-Border"&gt;5&lt;/long&gt;
                &lt;bool name="proxy-wxLEFT"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxRIGHT"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxTOP"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxBOTTOM"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxSHAPED"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxADJUST_MINSIZE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxFIXED_MINSIZE"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Custom arguments"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Custom ctor arguments"&gt;""&lt;/string&gt;
</xsl:template>

<xsl:template name="create_button_control">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="FieldName"/>
		<xsl:param name="ItemID"/>
                &lt;string name="title"&gt;"wxButton: ID_<xsl:value-of select="$FieldName"/>"&lt;/string&gt;
                &lt;string name="type"&gt;"dialog-control-document"&lt;/string&gt;
                &lt;string name="filename"&gt;""&lt;/string&gt;
                &lt;string name="icon-name"&gt;"dialogcontrol"&lt;/string&gt;
                &lt;long name="is-transient"&gt;0&lt;/long&gt;
                &lt;long name="owns-file"&gt;1&lt;/long&gt;
                &lt;long name="title-mode"&gt;0&lt;/long&gt;
                &lt;long name="locked"&gt;0&lt;/long&gt;
                &lt;string name="created"&gt;"11/11/2007"&lt;/string&gt;
                &lt;string name="proxy-type"&gt;"wbButtonProxy"&lt;/string&gt;
                &lt;string name="proxy-Id name"&gt;"<xsl:value-of select="$FieldName"/>"&lt;/string&gt;
                &lt;long name="proxy-Id value"&gt;<xsl:value-of select="8000+$ItemID"/>&lt;/long&gt;
                &lt;string name="proxy-Class"&gt;"wxButton"&lt;/string&gt;
                &lt;string name="proxy-Base class"&gt;"wxButton"&lt;/string&gt;
                &lt;bool name="proxy-External implementation"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-Separate files"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Implementation filename"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Header filename"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Member variable name"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Label"&gt;"<xsl:value-of select="$FieldName"/>"&lt;/string&gt;
                &lt;bool name="proxy-Default"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Help text"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Tooltip text"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Background colour"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Foreground colour"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Font"&gt;""&lt;/string&gt;
                &lt;bool name="proxy-Hidden"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-Enabled"&gt;1&lt;/bool&gt;
                &lt;string name="proxy-Platform"&gt;"&amp;lt;Any platform&amp;gt;"&lt;/string&gt;
                &lt;bool name="proxy-wxBU_LEFT"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxBU_RIGHT"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxBU_TOP"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxBU_BOTTOM"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxBU_EXACTFIT"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxNO_BORDER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxWANTS_CHARS"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxNO_FULL_REPAINT_ON_RESIZE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxFULL_REPAINT_ON_RESIZE"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Custom styles"&gt;""&lt;/string&gt;
                &lt;long name="proxy-X"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Y"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Width"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Height"&gt;-1&lt;/long&gt;
                &lt;string name="proxy-AlignH"&gt;"Centre"&lt;/string&gt;
                &lt;string name="proxy-AlignV"&gt;"Centre"&lt;/string&gt;
                &lt;long name="proxy-Stretch factor"&gt;1&lt;/long&gt;
                &lt;long name="proxy-Border"&gt;5&lt;/long&gt;
                &lt;bool name="proxy-wxLEFT"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxRIGHT"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxTOP"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxBOTTOM"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxSHAPED"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxADJUST_MINSIZE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxFIXED_MINSIZE"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Custom arguments"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Custom ctor arguments"&gt;""&lt;/string&gt;
</xsl:template>

<xsl:template name="create_checkbox_control">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="FieldName"/>
		<xsl:param name="ItemID"/>
                &lt;string name="title"&gt;"wxCheckBox: ID_<xsl:value-of select="$FieldName"/>"&lt;/string&gt;
                &lt;string name="type"&gt;"dialog-control-document"&lt;/string&gt;
                &lt;string name="filename"&gt;""&lt;/string&gt;
                &lt;string name="icon-name"&gt;"checkbox"&lt;/string&gt;
                &lt;long name="is-transient"&gt;0&lt;/long&gt;
                &lt;long name="owns-file"&gt;1&lt;/long&gt;
                &lt;long name="title-mode"&gt;0&lt;/long&gt;
                &lt;long name="locked"&gt;0&lt;/long&gt;
                &lt;string name="created"&gt;"11/11/2007"&lt;/string&gt;
                &lt;string name="proxy-type"&gt;"wbCheckBoxProxy"&lt;/string&gt;
                &lt;string name="proxy-Id name"&gt;"ID_<xsl:value-of select="$FieldName"/>"&lt;/string&gt;
                &lt;long name="proxy-Id value"&gt;<xsl:value-of select="9000+$ItemID"/>&lt;/long&gt;
                &lt;string name="proxy-Class"&gt;"wxCheckBox"&lt;/string&gt;
                &lt;string name="proxy-Base class"&gt;"wxCheckBox"&lt;/string&gt;
                &lt;bool name="proxy-External implementation"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-Separate files"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Implementation filename"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Header filename"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Member variable name"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Label"&gt;"<xsl:value-of select="$FieldName"/>"&lt;/string&gt;
                &lt;bool name="proxy-Initial value"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Help text"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Tooltip text"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Data variable"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Data validator"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Background colour"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Foreground colour"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Font"&gt;""&lt;/string&gt;
                &lt;bool name="proxy-Hidden"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-Enabled"&gt;1&lt;/bool&gt;
                &lt;string name="proxy-Platform"&gt;"&amp;lt;Any platform&amp;gt;"&lt;/string&gt;
                &lt;bool name="proxy-wxALIGN_RIGHT"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxCHK_2STATE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxCHK_3STATE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxCHK_ALLOW_3RD_STATE_FOR_USER"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxWANTS_CHARS"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxNO_FULL_REPAINT_ON_RESIZE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxFULL_REPAINT_ON_RESIZE"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Custom styles"&gt;""&lt;/string&gt;
                &lt;long name="proxy-X"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Y"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Width"&gt;-1&lt;/long&gt;
                &lt;long name="proxy-Height"&gt;-1&lt;/long&gt;
                &lt;string name="proxy-AlignH"&gt;"Centre"&lt;/string&gt;
                &lt;string name="proxy-AlignV"&gt;"Centre"&lt;/string&gt;
                &lt;long name="proxy-Stretch factor"&gt;1&lt;/long&gt;
                &lt;long name="proxy-Border"&gt;5&lt;/long&gt;
                &lt;bool name="proxy-wxLEFT"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxRIGHT"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxTOP"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxBOTTOM"&gt;1&lt;/bool&gt;
                &lt;bool name="proxy-wxSHAPED"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxADJUST_MINSIZE"&gt;0&lt;/bool&gt;
                &lt;bool name="proxy-wxFIXED_MINSIZE"&gt;0&lt;/bool&gt;
                &lt;string name="proxy-Custom arguments"&gt;""&lt;/string&gt;
                &lt;string name="proxy-Custom ctor arguments"&gt;""&lt;/string&gt;
</xsl:template>

<xsl:template name="create_formularlevel_prefix">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="FormularName"/>
          &lt;string name="title"&gt;"<xsl:value-of select="$ApplicationName"/><xsl:value-of select="$FormularName"/>Panel"&lt;/string&gt;
          &lt;string name="type"&gt;"dialog-document"&lt;/string&gt;
          &lt;string name="filename"&gt;""&lt;/string&gt;
          &lt;string name="icon-name"&gt;"dialog"&lt;/string&gt;
          &lt;long name="is-transient"&gt;0&lt;/long&gt;
          &lt;long name="owns-file"&gt;1&lt;/long&gt;
          &lt;long name="title-mode"&gt;0&lt;/long&gt;
          &lt;long name="locked"&gt;0&lt;/long&gt;
          &lt;string name="created"&gt;"11/11/2007"&lt;/string&gt;
          &lt;string name="proxy-type"&gt;"wbDialogProxy"&lt;/string&gt;
          &lt;long name="base-id"&gt;10000&lt;/long&gt;
          &lt;bool name="use-id-prefix"&gt;0&lt;/bool&gt;
          &lt;string name="id-prefix"&gt;""&lt;/string&gt;
          &lt;bool name="use-id-suffix"&gt;0&lt;/bool&gt;
          &lt;string name="id-suffix"&gt;""&lt;/string&gt;
          &lt;long name="use-xrc"&gt;0&lt;/long&gt;
          &lt;string name="proxy-Id name"&gt;"ID_<xsl:value-of select="$ApplicationName"/><xsl:value-of select="$FormularName"/>PANEL"&lt;/string&gt;
          &lt;long name="proxy-Id value"&gt;<xsl:value-of select="11000+$FormularID"/>&lt;/long&gt;
          &lt;string name="proxy-Class"&gt;"<xsl:value-of select="$ApplicationName"/><xsl:value-of select="$FormularName"/>Panel"&lt;/string&gt;
          &lt;string name="proxy-Base class"&gt;"wxPanel"&lt;/string&gt;
          &lt;string name="proxy-Window kind"&gt;"wxPanel"&lt;/string&gt;
          &lt;string name="proxy-Implementation filename"&gt;"<xsl:value-of select="$ApplicationName"/><xsl:value-of select="$FormularName"/>panel.cpp"&lt;/string&gt;
          &lt;string name="proxy-Header filename"&gt;"<xsl:value-of select="$ApplicationName"/><xsl:value-of select="$FormularName"/>panel.h"&lt;/string&gt;
          &lt;string name="proxy-XRC filename"&gt;""&lt;/string&gt;
          &lt;string name="proxy-Title"&gt;"<xsl:value-of select="$ApplicationName"/><xsl:value-of select="$FormularName"/>Panel"&lt;/string&gt;
          &lt;bool name="proxy-Centre"&gt;1&lt;/bool&gt;
          &lt;string name="proxy-Icon"&gt;""&lt;/string&gt;
          &lt;bool name="proxy-Dialog units"&gt;0&lt;/bool&gt;
          &lt;string name="proxy-Help text"&gt;""&lt;/string&gt;
          &lt;string name="proxy-Tooltip text"&gt;""&lt;/string&gt;
          &lt;string name="proxy-Background colour"&gt;""&lt;/string&gt;
          &lt;string name="proxy-Foreground colour"&gt;""&lt;/string&gt;
          &lt;string name="proxy-Font"&gt;""&lt;/string&gt;
          &lt;bool name="proxy-Hidden"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-Enabled"&gt;1&lt;/bool&gt;
          &lt;string name="proxy-Platform"&gt;"&amp;lt;Any platform&amp;gt;"&lt;/string&gt;
          &lt;bool name="proxy-wxDEFAULT_DIALOG_STYLE"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxCAPTION"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxRESIZE_BORDER"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxTHICK_FRAME"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxSYSTEM_MENU"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxSTAY_ON_TOP"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxDIALOG_NO_PARENT"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxCLOSE_BOX"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxMAXIMIZE_BOX"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxMINIMIZE_BOX"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxDIALOG_MODAL"&gt;1&lt;/bool&gt;
          &lt;bool name="proxy-wxNO_BORDER"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxSIMPLE_BORDER"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxDOUBLE_BORDER"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxSUNKEN_BORDER"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxRAISED_BORDER"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxSTATIC_BORDER"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxWANTS_CHARS"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxNO_FULL_REPAINT_ON_RESIZE"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxFULL_REPAINT_ON_RESIZE"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxCLIP_CHILDREN"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxTAB_TRAVERSAL"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxWS_EX_VALIDATE_RECURSIVELY"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxWS_EX_BLOCK_EVENTS"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-wxWS_EX_TRANSIENT"&gt;0&lt;/bool&gt;
          &lt;string name="proxy-Custom styles"&gt;""&lt;/string&gt;
          &lt;bool name="proxy-wxDIALOG_EX_CONTEXTHELP"&gt;0&lt;/bool&gt;
          &lt;bool name="proxy-Fit to content"&gt;1&lt;/bool&gt;
          &lt;long name="proxy-X"&gt;-1&lt;/long&gt;
          &lt;long name="proxy-Y"&gt;-1&lt;/long&gt;
          &lt;long name="proxy-Width"&gt;400&lt;/long&gt;
          &lt;long name="proxy-Height"&gt;300&lt;/long&gt;
          &lt;bool name="proxy-AUI manager"&gt;0&lt;/bool&gt;
          &lt;string name="proxy-Event sources"&gt;""&lt;/string&gt;
</xsl:template>

<xsl:template name="create_special_control_horizontal">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="FieldName"/>
		<xsl:param name="ItemID"/>
            &lt;document&gt;
<xsl:call-template name="create_boxsizer_prefix_horizontal">
</xsl:call-template>
              &lt;document&gt;
<xsl:call-template name="create_static_text">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
              &lt;document&gt;
<xsl:call-template name="create_static_text">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName">Special Type</xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
            &lt;/document&gt;
</xsl:template>

<xsl:template name="create_unknown_control_horizontal">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="FieldName"/>
		<xsl:param name="ItemID"/>
            &lt;document&gt;
<xsl:call-template name="create_boxsizer_prefix_horizontal">
</xsl:call-template>
              &lt;document&gt;
<xsl:call-template name="create_static_text">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
              &lt;document&gt;
<xsl:call-template name="create_static_text">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName">Unknown Type</xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
            &lt;/document&gt;
</xsl:template>

<xsl:template name="create_checkbox_control_horizontal">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="FieldName"/>
		<xsl:param name="ItemID"/>
            &lt;document&gt;
<xsl:call-template name="create_boxsizer_prefix_horizontal">
</xsl:call-template>
              &lt;document&gt;
<xsl:call-template name="create_static_text">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
              &lt;document&gt;
<xsl:call-template name="create_checkbox_control">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
            &lt;/document&gt;
</xsl:template>

<xsl:template name="create_text_control_horizontal">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="FieldName"/>
		<xsl:param name="ItemID"/>
            &lt;document&gt;
<xsl:call-template name="create_boxsizer_prefix_horizontal">
</xsl:call-template>
              &lt;document&gt;
<xsl:call-template name="create_static_text">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
              &lt;document&gt;
<xsl:call-template name="create_text_control">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
            &lt;/document&gt;
</xsl:template>

<xsl:template name="create_choice_control_horizontal">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="FieldName"/>
		<xsl:param name="ItemID"/>
            &lt;document&gt;
<xsl:call-template name="create_boxsizer_prefix_horizontal">
</xsl:call-template>
              &lt;document&gt;
<xsl:call-template name="create_static_text">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
              &lt;document&gt;
<xsl:call-template name="create_choice_control">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="$FieldName"/></xsl:with-param>
		<xsl:with-param name="ItemID"><xsl:value-of select="$ItemID"/></xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
            &lt;/document&gt;
</xsl:template>

<xsl:template name="create_navi_controls_horizontal">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="FieldName"/>
            &lt;document&gt;
<xsl:call-template name="create_boxsizer_prefix_horizontal">
</xsl:call-template>
              &lt;document&gt;
<xsl:call-template name="create_button_control">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="'First'"/></xsl:with-param>
		<xsl:with-param name="ItemID">901</xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
              &lt;document&gt;
<xsl:call-template name="create_button_control">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="'Prev'"/></xsl:with-param>
		<xsl:with-param name="ItemID">902</xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
              &lt;document&gt;
<xsl:call-template name="create_button_control">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="'Next'"/></xsl:with-param>
		<xsl:with-param name="ItemID">903</xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
              &lt;document&gt;
<xsl:call-template name="create_button_control">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="'Last'"/></xsl:with-param>
		<xsl:with-param name="ItemID">904</xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
            &lt;/document&gt;
</xsl:template>

<xsl:template name="create_addrem_controls_horizontal">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="FieldName"/>
            &lt;document&gt;
<xsl:call-template name="create_boxsizer_prefix_horizontal">
</xsl:call-template>
              &lt;document&gt;
<xsl:call-template name="create_button_control">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="'Add'"/></xsl:with-param>
		<xsl:with-param name="ItemID">905</xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
              &lt;document&gt;
<xsl:call-template name="create_button_control">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="FieldName"><xsl:value-of select="'Delete'"/></xsl:with-param>
		<xsl:with-param name="ItemID">906</xsl:with-param>
</xsl:call-template>
              &lt;/document&gt;
            &lt;/document&gt;
</xsl:template>
</xsl:stylesheet>

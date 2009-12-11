<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
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
<!-- Helper to create multible files. -->
<xsl:import href="../include/exsl.xsl"/>

<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>

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



<xsl:template name="createwxLuaDatabasePanel">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="FormName"/>

<exsl:document href="{$basedir}/{$appmoduledir}/{$ApplicationName}_AppModule/{$FormName}.lua" method="text">
-- This file is autogenerated. Please do not modify. It would be overwritten.

-- Load the wxLua module, does nothing if running from wxLua, wxLuaFreeze, or wxLuaEdit
-- package.path = package.path..";/RDGD/Code/Targets/lbDMF/Modules/TemplateDesigner_AppModule/?.lua;./?.dll;./?.so;../lib/?.so;../lib/vc_dll/?.dll;../lib/bcc_dll/?.dll;../lib/mingw_dll/?.dll;"
-- require("wx")
package.cpath = package.cpath..";../../../../../Develop/projects/dll/?.dll;./?.dll;./?.so;../lib/?.so;../lib/vc_dll/?.dll;../lib/bcc_dll/?.dll;../lib/mingw_dll/?.dll;"
wx = require("ds289u") 

require("wxLuaHelper")

<xsl:value-of select="$FormName"/>Panel = {
    d3    = nil,
    curkey = nil,
    curid = 0,
    dbstate = DB_STATE_BROWSE,
    internalupdate = false,
    found = 0,

    searchInComboBox = nil,
    searchForTextCtrl = nil,

    ID_SELECTION_LIST = NewID(),

    ID_PaneBorderSize = NewID(),
    ID_SashSize = NewID(),
    ID_CaptionSize = NewID(),
    ID_BackgroundColor = NewID(),
    ID_SashColor = NewID(),
    ID_InactiveCaptionColor = NewID(),
    ID_InactiveCaptionGradientColor = NewID(),
    ID_InactiveCaptionTextColor = NewID(),
    ID_ActiveCaptionColor = NewID(),
    ID_ActiveCaptionGradientColor = NewID(),
    ID_ActiveCaptionTextColor = NewID(),
    ID_BorderColor = NewID(),
    ID_GripperColor = NewID(),
    ID_SEARCHIN = NewID(),

    m_frame = nil,
    m_border_size = nil,
    m_sash_size = nil,
    m_caption_size = nil,
    m_inactive_caption_text_color = nil,
    m_inactive_caption_gradient_color = nil,
    m_inactive_caption_color = nil,
    m_active_caption_text_color = nil,
    m_active_caption_gradient_color = nil,
    m_active_caption_color = nil,
    m_sash_color = nil,
    m_background_color = nil,
    m_border_color = nil,
    m_gripper_color = nil,


<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
   <xsl:value-of select="@name"/>ComboBox = nil,
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
   <xsl:value-of select="@name"/>CheckBox = nil,
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
   <xsl:value-of select="@name"/>TextBox = nil,
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
   <xsl:value-of select="@name"/>TextBox = nil,
			</xsl:when>
			<xsl:when test="@dbtype='String'">
   <xsl:value-of select="@name"/>TextBox = nil,
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
   <xsl:value-of select="@name"/>TextBox = nil,
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

    m_selection = nil,
}

function <xsl:value-of select="$FormName"/>Panel:create(parent, frame, _d3)
    self.this = wx.wxPanel(parent.this, wx.wxID_ANY, wx.wxDefaultPosition, wx.wxDefaultSize, wx.wxTAB_TRAVERSAL, "<xsl:value-of select="$FormName"/>")
    self.m_frame = frame
    local this = self.this

    self.d3 = _d3

        --//wxBoxSizer* vert = new wxBoxSizer(wxVERTICAL);

        --//vert:Add(1, 1, 1, wxEXPAND);

        local grid_sizer = wx.wxGridSizer(2,2,2,2);
        grid_sizer:SetHGap(5);

	local selection_sizer = wx.wxGridSizer(2,2,2,2);
        selection_sizer:SetHGap(5);

	-- The listbox, containing the first three text columns
	m_selection = wx.wxListCtrl(this, self.ID_SELECTION_LIST, wx.wxDefaultPosition, wx.wxSize(250, 150), wx.wxLC_REPORT+wx.wxLC_SINGLE_SEL);
	selection_sizer:Add(m_selection, 1, wx.wxEXPAND + wx.wxALL, 5);


    	this:Connect(self.ID_SELECTION_LIST, wx.wxEVT_COMMAND_LIST_ITEM_SELECTED, function (event)
                local row = event:GetIndex()
		    curid = m_selection:GetItemData(row)
		    self.ReadData()
            end)

    	this:Connect(self.ID_SELECTION_LIST, wx.wxEVT_COMMAND_LIST_COL_CLICK, self.OnListColClick)

	searchForTextCtrl = wx.wxTextCtrl(this, wx.wxID_ANY);
	selection_sizer:Add(searchForTextCtrl);

    local searchInChoices = {_("All"), <xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>_("<xsl:value-of select="@name"/>")<xsl:if test="position()!=last()">, </xsl:if></xsl:for-each>}

    	searchInComboBox = wx.wxComboBox(this, self.ID_SEARCHIN, _("All"),
                                   wx.wxDefaultPosition, wx.wxDefaultSize,
                                   searchInChoices,
                                   wx.wxCB_READONLY)
	selection_sizer:Add(searchInComboBox);

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
	local boxsizer<xsl:value-of select="@name"/>Label = wx.wxBoxSizer(wx.wxHORIZONTAL);
	local boxsizer<xsl:value-of select="@name"/>Control = wx.wxBoxSizer(wx.wxHORIZONTAL);

	<xsl:value-of select="@name"/>CheckBox = wx.wxComboBox(this, wx.wxID_ANY, wxT(""));

        boxsizer<xsl:value-of select="@name"/>Label:Add(wx.wxStaticText(this, wx.wxID_ANY, wxT("<xsl:value-of select="@name"/>:")));
        boxsizer<xsl:value-of select="@name"/>Control:Add(<xsl:value-of select="@name"/>CheckBox, 1, wx.wxEXPAND + wx.wxALL, 5);
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
	local boxsizer<xsl:value-of select="@name"/>Label = wx.wxBoxSizer(wx.wxHORIZONTAL);
	local boxsizer<xsl:value-of select="@name"/>Control = wx.wxBoxSizer(wx.wxHORIZONTAL);

	<xsl:value-of select="@name"/>CheckBox = wx.wxCheckBox(this, wx.wxID_ANY, "");

        boxsizer<xsl:value-of select="@name"/>Label:Add(wx.wxStaticText(this, wx.wxID_ANY, wxT("<xsl:value-of select="@name"/>:")));
        boxsizer<xsl:value-of select="@name"/>Control:Add(<xsl:value-of select="@name"/>CheckBox, 1, wx.wxEXPAND + wx.wxALL, 5);
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
	local boxsizer<xsl:value-of select="@name"/>Label = wx.wxBoxSizer(wx.wxHORIZONTAL);
	local boxsizer<xsl:value-of select="@name"/>Control = wx.wxBoxSizer(wx.wxHORIZONTAL);

	<xsl:value-of select="@name"/>TextBox = wx.wxTextCtrl(this, wx.wxID_ANY);

        boxsizer<xsl:value-of select="@name"/>Label:Add(wx.wxStaticText(this, wx.wxID_ANY, wxT("<xsl:value-of select="@name"/>:")));
        boxsizer<xsl:value-of select="@name"/>Control:Add(<xsl:value-of select="@name"/>TextBox, 1, wx.wxEXPAND + wx.wxALL, 5);
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
	local boxsizer<xsl:value-of select="@name"/>Label = wx.wxBoxSizer(wx.wxHORIZONTAL);
	local boxsizer<xsl:value-of select="@name"/>Control = wx.wxBoxSizer(wx.wxHORIZONTAL);

	<xsl:value-of select="@name"/>TextBox = wx.wxTextCtrl(this, wx.wxID_ANY);

        boxsizer<xsl:value-of select="@name"/>Label:Add(wx.wxStaticText(this, wx.wxID_ANY, wxT("<xsl:value-of select="@name"/>:")));
        boxsizer<xsl:value-of select="@name"/>Control:Add(<xsl:value-of select="@name"/>TextBox, 1, wx.wxEXPAND + wx.wxALL, 5);
			</xsl:when>
			<xsl:when test="@dbtype='String'">
	local boxsizer<xsl:value-of select="@name"/>Label = wx.wxBoxSizer(wx.wxHORIZONTAL);
	local boxsizer<xsl:value-of select="@name"/>Control = wx.wxBoxSizer(wx.wxHORIZONTAL);

	<xsl:value-of select="@name"/>TextBox = wx.wxTextCtrl(this, wx.wxID_ANY);

        boxsizer<xsl:value-of select="@name"/>Label:Add(wx.wxStaticText(this, wx.wxID_ANY, wxT("<xsl:value-of select="@name"/>:")));
        boxsizer<xsl:value-of select="@name"/>Control:Add(<xsl:value-of select="@name"/>TextBox, 1, wx.wxEXPAND + wx.wxALL, 5);
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
	local boxsizer<xsl:value-of select="@name"/>Label = wx.wxBoxSizer(wx.wxHORIZONTAL);
	local boxsizer<xsl:value-of select="@name"/>Control = wx.wxBoxSizer(wx.wxHORIZONTAL);

	<xsl:value-of select="@name"/>TextBox = wx.wxTextCtrl(this, wx.wxID_ANY);

        boxsizer<xsl:value-of select="@name"/>Label:Add(wx.wxStaticText(this, wx.wxID_ANY, wxT("<xsl:value-of select="@name"/>:")));
        boxsizer<xsl:value-of select="@name"/>Control:Add(<xsl:value-of select="@name"/>TextBox, 1, wx.wxEXPAND + wx.wxALL, 5);
			</xsl:when>
			<xsl:otherwise>
	-- <xsl:value-of select="@dbtype"/> not handled by XSLT template
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
        grid_sizer:Add(boxsizer<xsl:value-of select="@name"/>Label, 0, wx.wxALL, 5);  grid_sizer:Add(boxsizer<xsl:value-of select="@name"/>Control, 1, wx.wxEXPAND + wx.wxALL, 5);
</xsl:for-each>

        local cont_sizer = wx.wxBoxSizer(wx.wxVERTICAL);
        cont_sizer:Add(selection_sizer, 1, wx.wxEXPAND + wx.wxALL, 5);
        cont_sizer:Add(grid_sizer, 0, wx.wxEXPAND + wx.wxALL, 5);
        this:SetSizer(cont_sizer);
        this:GetSizer():SetSizeHints(this);
--#if 0
--        m_border_size:SetValue(frame:GetDockArt():GetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE));
--        m_sash_size:SetValue(frame:GetDockArt():GetMetric(wxAUI_DOCKART_SASH_SIZE));
--        m_caption_size:SetValue(frame:GetDockArt():GetMetric(wxAUI_DOCKART_CAPTION_SIZE));
--#endif

    self.PrepareList()
    self.FillList();

    return self
end



function <xsl:value-of select="$FormName"/>Panel:OnListColClick(event)
    local c = event:GetColumn()

    local k
    if c == 1 then
        k = "author"
    elseif c == 2 then
        k = "title"
    elseif c == 3 then
        k = "category"
    else
        k = "ID"
    end
    
    if k ~= curkey then
        curkey = k
        self.FillList()
    end
    
    event:Skip()
end

function <xsl:value-of select="$FormName"/>Panel:PrepareList()
    local info = wx.wxListItem()
    local index = -1
    info:SetMask(wx.wxLIST_MASK_FORMAT + wx.wxLIST_MASK_TEXT + wx.wxLIST_MASK_WIDTH)

    --info:SetAlign(wx.wxLIST_FORMAT_RIGHT)
    --info:SetText(_("Id"))
    --info:SetWidth(30)
    --m_selection:InsertColumn(0, info)

    info:SetAlign(wx.wxLIST_FORMAT_LEFT)

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
        -- <xsl:value-of select="@name"/>ComboBox:SetValue(q:GetString("<xsl:value-of select="@name"/>") or "")
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
			</xsl:when>
			<xsl:when test="@dbtype='String'">
    index = index + 1
    info:SetText(_("<xsl:value-of select="@name"/>"))
    info:SetWidth(80)
    m_selection:InsertColumn(index, info)
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
end

function <xsl:value-of select="$FormName"/>Panel:PrepareQuery()
    local f = searchInComboBox:GetStringSelection()
    local v = searchForTextCtrl:GetValue()
    --wx.wxMessageBox("f:"..f.." v:"..v, "test", wx.wxOK)

    --changed for export: local sql = "select id, category, title, author from book "
    local sql = ""
    
    if v and v ~= "" then
        if f and f ~= "" then
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:if test="position()=1">
		    sql = "select * from <xsl:value-of select="$FormName"/> "
</xsl:if>
</xsl:for-each>
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:if test="position()=1">
            if f == _("All") then
                sql = sql .. "where " .. 
</xsl:if>
</xsl:for-each>
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
                             "<xsl:value-of select="@name"/> like :<xsl:value-of select="position()"/><xsl:if test="position()=last()"> "</xsl:if><xsl:if test="position()!=last()"> or " ..</xsl:if>
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
                             "<xsl:value-of select="@name"/> like :<xsl:value-of select="position()"/><xsl:if test="position()=last()"> "</xsl:if><xsl:if test="position()!=last()"> or " ..</xsl:if>
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
                             "<xsl:value-of select="@name"/> like :<xsl:value-of select="position()"/><xsl:if test="position()=last()"> "</xsl:if><xsl:if test="position()!=last()"> or " ..</xsl:if>
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
                             "<xsl:value-of select="@name"/> like :<xsl:value-of select="position()"/><xsl:if test="position()=last()"> "</xsl:if><xsl:if test="position()!=last()"> or " ..</xsl:if>
			</xsl:when>
			<xsl:when test="@dbtype='String'">
                             "<xsl:value-of select="@name"/> like :<xsl:value-of select="position()"/><xsl:if test="position()=last()"> "</xsl:if><xsl:if test="position()!=last()"> or " ..</xsl:if>
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
                             "<xsl:value-of select="@name"/> like :<xsl:value-of select="position()"/><xsl:if test="position()=last()"> "</xsl:if><xsl:if test="position()!=last()"> or " ..</xsl:if>
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
<xsl:if test="position()!=last()">
            elseif f == _("<xsl:value-of select="@name"/>") then
                sql = sql .. "where <xsl:value-of select="@name"/> like :1 "
</xsl:if>
<xsl:if test="position()=last()">
            elseif f == _("<xsl:value-of select="@name"/>") then
                sql = sql .. "where <xsl:value-of select="@name"/> like :1 "
            end
</xsl:if>
      </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
<xsl:if test="position()!=last()">
            elseif f == _("<xsl:value-of select="@name"/>") then
                sql = sql .. "where <xsl:value-of select="@name"/> like :1 "
</xsl:if>
<xsl:if test="position()=last()">
            elseif f == _("<xsl:value-of select="@name"/>") then
                sql = sql .. "where <xsl:value-of select="@name"/> like :1 "
            end
</xsl:if>
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
<xsl:if test="position()!=last()">
            elseif f == _("<xsl:value-of select="@name"/>") then
                sql = sql .. "where <xsl:value-of select="@name"/> like :1 "
</xsl:if>
<xsl:if test="position()=last()">
            elseif f == _("<xsl:value-of select="@name"/>") then
                sql = sql .. "where <xsl:value-of select="@name"/> like :1 "
            end
</xsl:if>
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
<xsl:if test="position()!=last()">
            elseif f == _("<xsl:value-of select="@name"/>") then
                sql = sql .. "where <xsl:value-of select="@name"/> like :1 "
</xsl:if>
<xsl:if test="position()=last()">
            elseif f == _("<xsl:value-of select="@name"/>") then
                sql = sql .. "where <xsl:value-of select="@name"/> like :1 "
            end
</xsl:if>
			</xsl:when>
			<xsl:when test="@dbtype='String'">
<xsl:if test="position()!=last()">
            elseif f == _("<xsl:value-of select="@name"/>") then
                sql = sql .. "where <xsl:value-of select="@name"/> like :1 "
</xsl:if>
<xsl:if test="position()=last()">
            elseif f == _("<xsl:value-of select="@name"/>") then
                sql = sql .. "where <xsl:value-of select="@name"/> like :1 "
            end
</xsl:if>
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
<xsl:if test="position()!=last()">
            elseif f == _("<xsl:value-of select="@name"/>") then
                sql = sql .. "where <xsl:value-of select="@name"/> like :1 "
</xsl:if>
<xsl:if test="position()=last()">
            elseif f == _("<xsl:value-of select="@name"/>") then
                sql = sql .. "where <xsl:value-of select="@name"/> like :1 "
            end
</xsl:if>
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
        end
    else
    		    sql = "select * from <xsl:value-of select="$FormName"/> "
    end 
    
    -- sql = sql .. " order by " .. (curkey or "id") .. ";"
    -- wx.wxMessageBox(sql, "test", wx.wxOK)
    
    if sql == "" then
        return nil
    end

    local st = d3:PrepareStatement(sql)
    local pc = st:GetParamCount()
    while pc > 0 do
        st:Bind(pc, "%"..v.."%")
        pc = pc - 1
    end
    
    return st
end

function <xsl:value-of select="$FormName"/>Panel:FillList()
    local st = <xsl:value-of select="$FormName"/>Panel.PrepareQuery()
    
    local currow = 0
    local l_found = 0

    if st == nil then
        wx.wxMessageBox("Sql Statement ist nicht erstellt.", "Fehler", wx.wxOK)
        return;
    end

    local q = st:ExecuteQuery()
    m_selection:Freeze()
    m_selection:DeleteAllItems()
    while q:NextRow() do
	  local index = -1
        l_found = l_found + 1
        local id = q:GetInt("ID") or 0
        local row = m_selection:InsertItem(m_selection:GetItemCount(), tostring(id))
        m_selection:SetItemData(row, id)
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
        m_selection:SetItem(row, <xsl:value-of select="position()"/>, (q:GetString("<xsl:value-of select="@name"/>") or ""))
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
        -- m_selection:SetItem(row, <xsl:value-of select="position()"/>, (q:GetString("<xsl:value-of select="@name"/>") or ""))
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
        -- m_selection:SetItem(row, <xsl:value-of select="position()"/>, (q:GetString("<xsl:value-of select="@name"/>") or ""))
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
        -- m_selection:SetItem(row, <xsl:value-of select="position()"/>, (q:GetString("<xsl:value-of select="@name"/>") or ""))
			</xsl:when>
			<xsl:when test="@dbtype='String'">
        index = index + 1
        m_selection:SetItem(row, index, (q:GetString("<xsl:value-of select="@name"/>") or "Leer"))
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
        -- m_selection:SetItem(row, <xsl:value-of select="position()"/>, (q:GetString("<xsl:value-of select="@name"/>") or ""))
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
        if id == curid then
            currow = row
        end
    end
    m_selection:Thaw()
    
    q:Finalize()
    st:Finalize()

    found = l_found
    -- ShowFound()
    <xsl:value-of select="$FormName"/>Panel:SelectRow(currow)
end

function <xsl:value-of select="$FormName"/>Panel:SelectRow(row)
    local numrow = m_selection:GetItemCount()
    if numrow == 0 or row &lt; 0 or numrow &lt; row then
        return
    end

    m_selection:SetItemState(row, wx.wxLIST_STATE_FOCUSED, wx.wxLIST_STATE_FOCUSED)
    m_selection:SetItemState(row, wx.wxLIST_STATE_SELECTED, wx.wxLIST_STATE_SELECTED)
    m_selection:EnsureVisible(row)
end

function <xsl:value-of select="$FormName"/>Panel:ReadData()
    local sql = "select * from <xsl:value-of select="$FormName"/> where id = " .. tostring(curid) .. ";"

    --wx.wxMessageBox(sql, "Info")

    local q = d3:ExecuteQuery(sql)
    if q:NextRow() then
        internalupdate = true
        
        --local title = q:GetString("title") or ""
        --SetInfo(title)

        --FIXME if this would worked, internalupdate flag would be unnecessary!
        --categoryTextCtrl:ChangeValue(q:GetString("category") or "") 
        

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
        <xsl:value-of select="$FormName"/>Panel.<xsl:value-of select="@name"/>ComboBox:SetValue(q:GetString("<xsl:value-of select="@name"/>") or "")
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
        <xsl:value-of select="@name"/>TextBox:SetValue(q:GetString("<xsl:value-of select="@name"/>") or "")
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
        <xsl:value-of select="@name"/>TextBox:SetValue(q:GetString("<xsl:value-of select="@name"/>") or "")
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
        <xsl:value-of select="@name"/>TextBox:SetValue(q:GetString("<xsl:value-of select="@name"/>") or "")
			</xsl:when>
			<xsl:when test="@dbtype='String'">
        <xsl:value-of select="@name"/>TextBox:SetValue(q:GetString("<xsl:value-of select="@name"/>") or "")
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
        <xsl:value-of select="@name"/>TextBox:SetValue(q:GetString("<xsl:value-of select="@name"/>") or "")
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

        internalupdate = false
    end
    q:Finalize()
end

function <xsl:value-of select="$FormName"/>Panel:SaveData()
    local sql = ""
    --wx.wxMessageBox(dbstate, "test", wx.wxOK)
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:if test="position()=1">
    if dbstate == DB_STATE_ADD then
        sql = "insert into <xsl:value-of select="$FormName"/> ( " ..
</xsl:if>
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
	"<xsl:value-of select="@name"/>, " .. -- <xsl:value-of select="@tablename"/>
<xsl:if test="position()=last()">
              ") values ( " ..
</xsl:if>
</xsl:for-each>
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
	":<xsl:value-of select="position()"/>, " ..
<xsl:if test="position()=last()">
              ");"
    elseif dbstate == DB_STATE_EDIT then
        sql = "update book set " ..
</xsl:if>
</xsl:for-each>
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
	"<xsl:value-of select="@name"/> = :<xsl:value-of select="position()"/>, " ..
<xsl:if test="position()=last()">
              "where id = :<xsl:value-of select="position()+1"/>;"
    else
        error("Internal error: invalid dbstate")
    end
</xsl:if>
</xsl:for-each>

    if sql == "" then
	return;
    end

    local st,e = d3:PrepareStatement(sql)
    --if e then wx.wxMessageBox(e:GetMessage(), "test", wx.wxOK) end
    
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
    st:Bind( 1, <xsl:value-of select="@name"/>ComboBox:GetValue() or "")
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
    st:Bind( <xsl:value-of select="position()"/>, <xsl:value-of select="@name"/>CheckBox:GetValue() or "")
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
    st:Bind( <xsl:value-of select="position()"/>, <xsl:value-of select="@name"/>TextBox:GetValue() or "")
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
    st:Bind( <xsl:value-of select="position()"/>, <xsl:value-of select="@name"/>TextBox:GetValue() or "")
			</xsl:when>
			<xsl:when test="@dbtype='String'">
    st:Bind( <xsl:value-of select="position()"/>, <xsl:value-of select="@name"/>TextBox:GetValue() or "")
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
    st:Bind( <xsl:value-of select="position()"/>, <xsl:value-of select="@name"/>TextBox:GetValue() or "")
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
<xsl:if test="position()=last()">
    if dbstate == DB_STATE_EDIT then
        st:Bind(<xsl:value-of select="position()"/>+1, curid)
    end
</xsl:if>
</xsl:for-each>

    
    local rc,e = st:ExecuteUpdate()
    --if e then wx.wxMessageBox(e:GetMessage(), "test", wx.wxOK) end

    if dbstate == DB_STATE_ADD then
        curid = d3:GetLastRowId()
        -- ShowTotal()
        --clear search criteria to prevent surprises!
        searchForTextCtrl:SetValue("")
        searchInComboBox:SetStringSelection(_("All"))
    end
    
    dbstate = DB_STATE_BROWSE
    FillList() --lazy and easy way!
end

function <xsl:value-of select="$FormName"/>Panel:OnFirst(event)
end

function <xsl:value-of select="$FormName"/>Panel:OnPrev(event)
end

function <xsl:value-of select="$FormName"/>Panel:OnNext(event)
end

function <xsl:value-of select="$FormName"/>Panel:OnLast(event)
end



</exsl:document>
</xsl:template>


</xsl:stylesheet>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2000-2025  Lothar Behrens (lothar.behrens@lollisoft.de)

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
            Odenwaldstr. 14

            63150 Heusenstamm (germany)
-->
<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>

<xsl:template name="createFormClassImpl">
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

/////////////////////////////////////////////////////
// Generated By wxActiveRecordGenerator v 1.2.0-rc3
/////////////////////////////////////////////////////

#define AR_USE_SQLITE

#include "<xsl:value-of select="$ApplicationName"/><xsl:value-of select="$FormularName"/>Implementation.h"

/** ACTIVE_RECORD **/
<xsl:value-of select="$FormularName"/>::<xsl:value-of select="$FormularName"/>()
	:wxSqliteActiveRecord() {
}

<xsl:value-of select="$FormularName"/>::<xsl:value-of select="$FormularName"/>(const wxString&amp; name,const wxString&amp; server,const wxString&amp; user,const wxString&amp; password,const wxString&amp; table):wxSqliteActiveRecord(name,server,user,password,table){
}

<xsl:value-of select="$FormularName"/>::<xsl:value-of select="$FormularName"/>(DatabaseLayer* database,const wxString&amp; table):wxSqliteActiveRecord(database,table){
}

bool <xsl:value-of select="$FormularName"/>::Create(const wxString&amp; name,const wxString&amp; server,const wxString&amp; user,const wxString&amp; password,const wxString&amp; table){
	return wxSqliteActiveRecord::Create(name,server,user,password,table);
}

<xsl:value-of select="$FormularName"/>Row* <xsl:value-of select="$FormularName"/>::RowFromResult(DatabaseResultSet* result){
	<xsl:value-of select="$FormularName"/>Row* row=new <xsl:value-of select="$FormularName"/>Row(this);
	
	row->GetFromResult(result);
	
	return row;
}

<xsl:value-of select="$FormularName"/>Row* <xsl:value-of select="$FormularName"/>::New(){
	<xsl:value-of select="$FormularName"/>Row* newRow=new <xsl:value-of select="$FormularName"/>Row(this);
	garbageRows.Add(newRow);
	return newRow;
}
bool <xsl:value-of select="$FormularName"/>::Delete(int key){
	try{
		PreparedStatement* pStatement=m_database->PrepareStatement(wxString::Format(wxT("DELETE FROM %s WHERE id=?"),m_table.c_str()));
		pStatement->SetParamInt(1,key);
		pStatement->ExecuteUpdate();
		return true;
	}
	catch(DatabaseLayerException&amp; e){
		throw(e);
		return false;
	}
}



<xsl:value-of select="$FormularName"/>Row* <xsl:value-of select="$FormularName"/>::Id(int key){
	try{
		PreparedStatement* pStatement=m_database->PrepareStatement(wxString::Format(wxT("SELECT * FROM %s WHERE id=?"),m_table.c_str()));
		pStatement->SetParamInt(1,key);
		DatabaseResultSet* result= pStatement->ExecuteQuery();

		result->Next();
		<xsl:value-of select="$FormularName"/>Row* row=RowFromResult(result);
		garbageRows.Add(row);
		m_database->CloseResultSet(result);
		m_database->CloseStatement(pStatement);
		return row;
	}
	catch (DatabaseLayerException&amp; e)
	{
		ProcessException(e);
		return NULL;
	}
}




<xsl:value-of select="$FormularName"/>Row* <xsl:value-of select="$FormularName"/>::Where(const wxString&amp; whereClause){
	try{
		wxString prepStatement = wxString::Format(wxT("SELECT * FROM %s WHERE %s"),m_table.c_str(),whereClause.c_str());
		PreparedStatement* pStatement=m_database->PrepareStatement(prepStatement);
		DatabaseResultSet* result= pStatement->ExecuteQuery();
		
		if(!result->Next())
			return NULL;
		<xsl:value-of select="$FormularName"/>Row* row=RowFromResult(result);
		
		garbageRows.Add(row);
		m_database->CloseResultSet(result);
		m_database->CloseStatement(pStatement);						
		return row;
	}
	catch (DatabaseLayerException&amp; e)
	{
		ProcessException(e);
		return 0;
	}
}

<xsl:value-of select="$FormularName"/>RowSet* <xsl:value-of select="$FormularName"/>::WhereSet(const wxString&amp; whereClause,const wxString&amp; orderBy){
	<xsl:value-of select="$FormularName"/>RowSet* rowSet=new <xsl:value-of select="$FormularName"/>RowSet();
	try{
		wxString prepStatement=wxString::Format(wxT("SELECT * FROM %s WHERE %s"),m_table.c_str(),whereClause.c_str());
		if(!orderBy.IsEmpty())
			prepStatement+=wxT(" ORDER BY ")+orderBy;
		PreparedStatement* pStatement=m_database->PrepareStatement(prepStatement);
		DatabaseResultSet* result= pStatement->ExecuteQuery();
		
		if(result){
			while(result->Next()){
				rowSet->Add(RowFromResult(result));
			}
		}
		
		garbageRowSets.Add(rowSet);
		m_database->CloseResultSet(result);
		m_database->CloseStatement(pStatement);	
		return rowSet;
		
	}
	catch (DatabaseLayerException&amp; e)
	{
		ProcessException(e);
		return 0;
	}
}


<xsl:value-of select="$FormularName"/>RowSet* <xsl:value-of select="$FormularName"/>::All(const wxString&amp; orderBy){
	<xsl:value-of select="$FormularName"/>RowSet* rowSet=new <xsl:value-of select="$FormularName"/>RowSet();
	try{
		wxString prepStatement=wxString::Format(wxT("SELECT * FROM %s"),m_table.c_str());
		if(!orderBy.IsEmpty())
			prepStatement+=wxT(" ORDER BY ")+orderBy;
		PreparedStatement* pStatement=m_database->PrepareStatement(prepStatement);
		
		DatabaseResultSet* result= pStatement->ExecuteQuery();
		
		if(result){
			while(result->Next()){
				rowSet->Add(RowFromResult(result));
			}
		}
		garbageRowSets.Add(rowSet);
		m_database->CloseResultSet(result);
		m_database->CloseStatement(pStatement);	
		return rowSet;
		
	}
	catch (DatabaseLayerException&amp; e)
	{
		ProcessException(e);
		return 0;
	}
}

/** END ACTIVE RECORD **/

/** ACTIVE RECORD ROW **/

<xsl:value-of select="$FormularName"/>Row::<xsl:value-of select="$FormularName"/>Row():wxActiveRecordRow(){
	bool newRow=true;
}

<xsl:value-of select="$FormularName"/>Row::<xsl:value-of select="$FormularName"/>Row(<xsl:value-of select="$FormularName"/>* activeRecord):wxActiveRecordRow(activeRecord){
	bool newRow=true;
}

<xsl:value-of select="$FormularName"/>Row::<xsl:value-of select="$FormularName"/>Row(const <xsl:value-of select="$FormularName"/>Row&amp; src){
	if(&amp;src==this)
		return;
	newRow=src.newRow;
	
	<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@dbtype='String'">
	<xsl:value-of select="@name"/>=src.<xsl:value-of select="@name"/>;
	</xsl:when>
	<xsl:when test="@dbtype='Integer'">
	<xsl:value-of select="@name"/>=src.<xsl:value-of select="@name"/>;
	</xsl:when>
	<xsl:otherwise>
	//Unknown type <xsl:value-of select="@name"/>; // <xsl:value-of select="@tablename"/>
	</xsl:otherwise>
</xsl:choose>
	</xsl:for-each>
}

<xsl:value-of select="$FormularName"/>Row::<xsl:value-of select="$FormularName"/>Row(DatabaseLayer* database,const wxString&amp; table):wxActiveRecordRow(database,table){
	newRow=true;
}
	

<xsl:value-of select="$FormularName"/>Row&amp; <xsl:value-of select="$FormularName"/>Row::operator=(const <xsl:value-of select="$FormularName"/>Row&amp; src){
	if(&amp;src==this)
		return *this;
	newRow=src.newRow;

	<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@dbtype='String'">
	<xsl:value-of select="@name"/>=src.<xsl:value-of select="@name"/>;
	</xsl:when>
	<xsl:when test="@dbtype='Integer'">
	<xsl:value-of select="@name"/>=src.<xsl:value-of select="@name"/>;
	</xsl:when>
	<xsl:otherwise>
	//Unknown type <xsl:value-of select="@name"/>; // <xsl:value-of select="@tablename"/>
	</xsl:otherwise>
</xsl:choose>
	</xsl:for-each>
	return *this;
}

bool <xsl:value-of select="$FormularName"/>Row::GetFromResult(DatabaseResultSet* result){
	
	newRow=false;
	
	<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@dbtype='String'">
	<xsl:value-of select="@name"/>=result->GetResultString(wxT("<xsl:value-of select="@name"/>"));
	</xsl:when>
	<xsl:when test="@dbtype='Integer'">
	<xsl:value-of select="@name"/>=result->GetResultInt(wxT("<xsl:value-of select="@name"/>"));
	</xsl:when>
	<xsl:otherwise>
	//Unknown type <xsl:value-of select="@name"/>; // <xsl:value-of select="@tablename"/>
	</xsl:otherwise>
</xsl:choose>
	</xsl:for-each>
	return true;
}
	

bool <xsl:value-of select="$FormularName"/>Row::Save(){
	try{
		if(newRow){
			PreparedStatement* pStatement=m_database->PrepareStatement(wxString::Format(wxT("INSERT INTO %s (<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
	<xsl:if test="position()>1">,</xsl:if><xsl:value-of select="@name"/></xsl:for-each>) VALUES (<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
	<xsl:if test="position()>1">,</xsl:if>?</xsl:for-each>)"),m_table.c_str()));
			<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
			

<xsl:choose>
	<xsl:when test="@dbtype='String'">
			pStatement->SetParamString(<xsl:value-of select="position()"/>,<xsl:value-of select="@name"/>);
	</xsl:when>
	<xsl:when test="@dbtype='Integer'">
			pStatement->SetParamInt(<xsl:value-of select="position()"/>,<xsl:value-of select="@name"/>);
	</xsl:when>
	<xsl:otherwise>
	//Unknown type <xsl:value-of select="@name"/>; // <xsl:value-of select="@tablename"/>
	</xsl:otherwise>
</xsl:choose>


			
			
			
			</xsl:for-each>			
			pStatement->RunQuery();
			m_database->CloseStatement(pStatement);
			
			newRow=false;
		}
		else{
			PreparedStatement* pStatement=m_database->PrepareStatement(wxString::Format(wxT("UPDATE %s SET <xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
	<xsl:if test="position()>1">,</xsl:if><xsl:value-of select="@name"/>=?</xsl:for-each> WHERE id=?"),m_table.c_str()));
			<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@dbtype='String'">
			pStatement->SetParamString(<xsl:value-of select="position()"/>,<xsl:value-of select="@name"/>);
	</xsl:when>
	<xsl:when test="@dbtype='Integer'">
			pStatement->SetParamInt(<xsl:value-of select="position()"/>,<xsl:value-of select="@name"/>);
	</xsl:when>
	<xsl:otherwise>
			//Unknown type <xsl:value-of select="@name"/>; // <xsl:value-of select="@tablename"/>
	</xsl:otherwise>
			</xsl:choose><xsl:if test="position()=last()">
			// Fix by design pk name. It may be ok
			pStatement->SetParamInt(<xsl:value-of select="position()+1"/>, id);</xsl:if>	
						</xsl:for-each>			
			
			pStatement->RunQuery();
			m_database->CloseStatement(pStatement);

		}
		
		return true;
	}
	catch (DatabaseLayerException&amp; e)
	{
		wxActiveRecord::ProcessException(e);
		return false;
	}
}

bool <xsl:value-of select="$FormularName"/>Row::Delete(){
	try{
		PreparedStatement* pStatement=m_database->PrepareStatement(wxString::Format(wxT("DELETE FROM %s WHERE id=?"),m_table.c_str()));
		// Fix by design pk name. It may be ok
		pStatement->SetParamInt(1,id);
		pStatement->ExecuteUpdate();
		return true;
	}
	catch(DatabaseLayerException&amp; e){
		throw(e);
		return false;
	}
}





/** END ACTIVE RECORD ROW **/

/** ACTIVE RECORD ROW SET **/

<xsl:value-of select="$FormularName"/>RowSet::<xsl:value-of select="$FormularName"/>RowSet():wxActiveRecordRowSet(){
}

<xsl:value-of select="$FormularName"/>RowSet::<xsl:value-of select="$FormularName"/>RowSet(wxActiveRecord* activeRecord):wxActiveRecordRowSet(activeRecord){
}

<xsl:value-of select="$FormularName"/>RowSet::<xsl:value-of select="$FormularName"/>RowSet(DatabaseLayer* database,const wxString&amp; table):wxActiveRecordRowSet(database,table){
}

<xsl:value-of select="$FormularName"/>Row* <xsl:value-of select="$FormularName"/>RowSet::Item(unsigned long item){
	return (<xsl:value-of select="$FormularName"/>Row*)wxActiveRecordRowSet::Item(item);
}


bool <xsl:value-of select="$FormularName"/>RowSet::SaveAll(){
	try{
		m_database->BeginTransaction();
		for(unsigned long i=0;i&lt;Count();i++)
			Item(i)->Save();
		m_database->Commit();
		return true;
	}
	catch (DatabaseLayerException&amp; e)
	{
		m_database->RollBack();
		wxActiveRecord::ProcessException(e);
		return false;
	}
}

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
int <xsl:value-of select="$FormularName"/>RowSet::CMPFUNC_<xsl:value-of select="@name"/>(wxActiveRecordRow** item1,wxActiveRecordRow** item2){
	<xsl:value-of select="$FormularName"/>Row** m_item1=(<xsl:value-of select="$FormularName"/>Row**)item1;
	<xsl:value-of select="$FormularName"/>Row** m_item2=(<xsl:value-of select="$FormularName"/>Row**)item2;
<xsl:choose>
	<xsl:when test="@dbtype='String'">
	return (*m_item1)-><xsl:value-of select="@name"/>.Cmp((*m_item2)-><xsl:value-of select="@name"/>);
	</xsl:when>
	<xsl:when test="@dbtype='Integer'">
	if((*m_item1)-><xsl:value-of select="@name"/>&lt;(*m_item2)-><xsl:value-of select="@name"/>)
		return -1;
	else if((*m_item1)-><xsl:value-of select="@name"/>>(*m_item2)-><xsl:value-of select="@name"/>)
		return 1;
	else
		return 0;
	</xsl:when>
	<xsl:otherwise>
			//Unknown type <xsl:value-of select="@name"/>; // <xsl:value-of select="@tablename"/>
	</xsl:otherwise>
</xsl:choose>	
}
</xsl:for-each>

int <xsl:value-of select="$FormularName"/>RowSet::CMPFUNC_id(wxActiveRecordRow** item1,wxActiveRecordRow** item2){
	<xsl:value-of select="$FormularName"/>Row** m_item1=(<xsl:value-of select="$FormularName"/>Row**)item1;
	<xsl:value-of select="$FormularName"/>Row** m_item2=(<xsl:value-of select="$FormularName"/>Row**)item2;
	if((*m_item1)->id&lt;(*m_item2)->id)
		return -1;
	else if((*m_item1)->id>(*m_item2)->id)
		return 1;
	else
		return 0;
}


CMPFUNC_proto <xsl:value-of select="$FormularName"/>RowSet::GetCmpFunc(const wxString&amp; var) const{
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
	if(var==wxT("<xsl:value-of select="@name"/>")) return (CMPFUNC_proto)CMPFUNC_<xsl:value-of select="@name"/>;
</xsl:for-each>	
	if(var==wxT("id")) return (CMPFUNC_proto)CMPFUNC_id;
	return (CMPFUNC_proto)CMPFUNC_default;
}



/** END ACTIVE RECORD ROW SET **/

////@@begin custom implementations

////@@end custom implementations

</xsl:template>

</xsl:stylesheet>

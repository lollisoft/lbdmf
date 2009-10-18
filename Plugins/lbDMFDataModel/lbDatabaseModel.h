/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

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
*/
/*...e*/


class lbDBTableModel : public lb_I_DBTables {
public:
	lbDBTableModel();
	virtual ~lbDBTableModel();

	long		LB_STDCALL addTable(const char* catalog, const char* schema, const char* name, const char* type, const char* remarks, long _id = -1);
	bool		LB_STDCALL selectTable(long _id);
	int			LB_STDCALL getTableCount();
	bool		LB_STDCALL hasMoreTables();
	void		LB_STDCALL setNextTable();
	void		LB_STDCALL finishTableIteration();
	
	long		LB_STDCALL getTableID();
	char*		LB_STDCALL getTableCatalog();
	char*		LB_STDCALL getTableSchema();
	char*		LB_STDCALL getTableName();
	char*		LB_STDCALL getTableType();
	char*		LB_STDCALL getTableRemarks();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()

	UAP(lb_I_Container, Tables)
	UAP(lb_I_String, currentCatalog)
	UAP(lb_I_String, currentSchema)
	UAP(lb_I_String, currentName)
	UAP(lb_I_String, currentType)
	UAP(lb_I_String, currentRemarks)
	UAP(lb_I_Long, currentID)
	UAP(lb_I_Long, marked)
};

class lbDBColumnsModel : public lb_I_DBColumns {
public:
	lbDBColumnsModel();
	virtual ~lbDBColumnsModel();
	
	bool		LB_STDCALL addPagedConainer(lb_I_Container* pagedContainer);
	long		LB_STDCALL addColumn(const char* name, const char* comment, const char* typ, long len, bool isNullable, const char* PKTable, const char* PKField, const char* tablename, long _id = -1);
	bool		LB_STDCALL selectColumn(long _id);
	int			LB_STDCALL getColumnCount();
	bool		LB_STDCALL hasMoreColumns();
	void		LB_STDCALL setNextColumn();
	void		LB_STDCALL finishColumnIteration();

	bool		LB_STDCALL hasMorePages();
	void		LB_STDCALL setNextPage();
	void		LB_STDCALL finishPageIteration();
	


	long		LB_STDCALL getColumnID();
	char*		LB_STDCALL getColumnName();
	char*		LB_STDCALL getColumnComment();
	char*		LB_STDCALL getColumnTableName();
	char*		LB_STDCALL getColumnTyp();
	long		LB_STDCALL getColumnLen();
	bool		LB_STDCALL isNullable();
	char*		LB_STDCALL getColumnPKTable();
	char*		LB_STDCALL getColumnPKField();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	void		LB_STDCALL lookupPage(int index);

	DECLARE_LB_UNKNOWN()

	// Contains pages of containers with each about 1000 elements maximum
	UAP(lb_I_Container, ColumnsPages)

	UAP(lb_I_Container, Columns)
	UAP(lb_I_String, currentName)
	UAP(lb_I_String, currentComment)
	UAP(lb_I_String, currentTableName)
	UAP(lb_I_String, currentTyp)
	UAP(lb_I_String, currentPKTable)
	UAP(lb_I_String, currentPKField)
	UAP(lb_I_Long, currentID)
	UAP(lb_I_Long, currentLen)
	UAP(lb_I_Long, currentNullable)
	UAP(lb_I_Long, currentmarked)


	// Do not alloc new objects for each addColumn call.
	UAP(lb_I_String, Name)
	UAP(lb_I_String, Comment)
	UAP(lb_I_String, TableName)
	UAP(lb_I_String, Typ)
	UAP(lb_I_String, pkField)
	UAP(lb_I_String, pkTable)
	UAP(lb_I_Long, IsNullable)
	UAP(lb_I_Long, ID)
	UAP(lb_I_Long, Len)
	UAP(lb_I_Long, marked)

	UAP(lb_I_String, paramnameName)
	UAP(lb_I_String, paramnameComment)
	UAP(lb_I_String, paramnameTableName)
	UAP(lb_I_String, paramnameTyp)
	UAP(lb_I_String, paramnameLen)
	UAP(lb_I_String, paramnameNullable)
	UAP(lb_I_String, paramnamePKField)
	UAP(lb_I_String, paramnamePKTable)
	UAP(lb_I_String, paramnameID)
	UAP(lb_I_String, paramnamemarked)

};

class lbDBForeignKeysModel : public lb_I_DBForeignKeys {
public:
	lbDBForeignKeysModel();
	virtual ~lbDBForeignKeysModel();

	DECLARE_LB_UNKNOWN()

	/** \brief Add a foreign key information.
	 * This function is based on ODBC 1.0 and therefore didn't support the last three columns returned by the SQLForeignKeys function.
	 */
	long		LB_STDCALL addForeignKey(	const char* pktable_cat, const char* pktable_schem, const char* pktable_name, const char* pkcolumn_name, 
													const char* fktable_cat, const char* fktable_schem, const char* fktable_name, const char* fkcolumn_name, 
													long key_seq, long update_rule, long delete_rule, long _id = -1);
	bool		LB_STDCALL selectForeignKey(long _id);
	int			LB_STDCALL getForeignKeyCount();
	bool		LB_STDCALL hasMoreForeignKeys();
	void		LB_STDCALL setNextForeignKey();
	void		LB_STDCALL finishForeignKeyIteration();
	
	long		LB_STDCALL getForeignKeyID();
	char*		LB_STDCALL getForeignKeyPKTableCatalog();
	char*		LB_STDCALL getForeignKeyPKTableSchema();
	char*		LB_STDCALL getForeignKeyPKTableName();
	char*		LB_STDCALL getForeignKeyPKTableColumnName();

	char*		LB_STDCALL getForeignKeyFKTableCatalog();
	char*		LB_STDCALL getForeignKeyFKTableSchema();
	char*		LB_STDCALL getForeignKeyFKTableName();
	char*		LB_STDCALL getForeignKeyFKTableColumnName();

	long		LB_STDCALL getForeignKeyKeySequence();
	long		LB_STDCALL getForeignKeyUpdateRule();
	long		LB_STDCALL getForeignKeyDeleteRule();


	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();
	
	UAP(lb_I_Container, ForeignKeys)
	UAP(lb_I_String, currentPKTableCatalog)
	UAP(lb_I_String, currentPKTableSchema)
	UAP(lb_I_String, currentPKTableName)
	UAP(lb_I_String, currentPKTableColumnName)

	UAP(lb_I_String, currentFKTableCatalog)
	UAP(lb_I_String, currentFKTableSchema)
	UAP(lb_I_String, currentFKTableName)
	UAP(lb_I_String, currentFKTableColumnName)

	UAP(lb_I_Long, currentID)
	UAP(lb_I_Long, currentKeySequence)
	UAP(lb_I_Long, currentUpdateRule)
	UAP(lb_I_Long, currentDeleteRule)
	
	UAP(lb_I_Long, marked)
};

class lbDBPrimaryKeysModel : public lb_I_DBPrimaryKeys {
public:
	lbDBPrimaryKeysModel();
	virtual ~lbDBPrimaryKeysModel();

	DECLARE_LB_UNKNOWN()

	long		LB_STDCALL addPrimaryKey(	const char* pktable_cat, const char* pktable_schem, const char* pktable_name, const char* pkcolumn_name, 
													long key_seq, const char* column_name, long _id = -1);
	bool		LB_STDCALL selectPrimaryKey(long _id);
	int			LB_STDCALL getPrimaryKeyCount();
	bool		LB_STDCALL hasMorePrimaryKeys();
	void		LB_STDCALL setNextPrimaryKey();
	void		LB_STDCALL finishPrimaryKeyIteration();
	
	long		LB_STDCALL getPrimaryKeyID();
	char*		LB_STDCALL getPrimaryKeyTableCatalog();
	char*		LB_STDCALL getPrimaryKeyTableSchema();
	char*		LB_STDCALL getPrimaryKeyTableName();
	char*		LB_STDCALL getPrimaryKeyColumnName();
	char*		LB_STDCALL getPrimaryKeyColumnName_ODBC_V_2();

	long		LB_STDCALL getPrimaryKeySequence();


	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	UAP(lb_I_Container, PrimaryKeys)
	UAP(lb_I_String, currentTableCatalog)
	UAP(lb_I_String, currentTableSchema)
	UAP(lb_I_String, currentTableName)
	UAP(lb_I_String, currentColumnName)
	UAP(lb_I_String, currentColumnName_V2)
	
	UAP(lb_I_Long, currentID)
	UAP(lb_I_Long, currentKeySequence)
	UAP(lb_I_Long, marked)
};

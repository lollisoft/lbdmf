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
            Rosmarinstr. 3
            
            40235 Duesseldorf (germany)
*/
/*...e*/
/*...sclass lbDBReportAction:0:*/

#ifdef OSX
#include <repwrt.h>
#endif


class lbDBReportAction : public lb_I_DelegatedAction
{
public:
	lbDBReportAction();
	virtual ~lbDBReportAction();

	void LB_STDCALL setActionID(char* id);	
	void LB_STDCALL execute(lb_I_Parameter* params);

	void LB_STDCALL setDatabase(lb_I_Database* _db);
	
	DECLARE_LB_UNKNOWN()
	
protected:

	void LB_STDCALL openReport(lb_I_String* reportname, lb_I_Parameter* params);

	char* myActionID;
	UAP(lb_I_Database, db, __FILE__, __LINE__)
	UAP(lb_I_String, app, __FILE__, __LINE__)
	UAP(lb_I_String, masterForm, __FILE__, __LINE__)
	UAP(lb_I_String, SourceFieldName, __FILE__, __LINE__)
	UAP(lb_I_String, SourceFieldValue, __FILE__, __LINE__)
	UAP(lb_I_String, DBName, __FILE__, __LINE__)
	UAP(lb_I_String, DBUser, __FILE__, __LINE__)
	UAP(lb_I_String, DBPass, __FILE__, __LINE__)

	lb_I_DatabaseReport* report;
};
/*...e*/
/*...sclass lbDatabaseReport:0:*/
class lbDatabaseReport :
        public lb_I_DatabaseReport {
public:
	/**
	 * Default constructor - implemented in BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseDialog)
	 */
	lbDatabaseReport();

	/**
	 * Destructor
	 */
	virtual ~lbDatabaseReport();
	
	void LB_STDCALL init(char* SQLString, char* DBName, char* DBUser, char* DBPass);
	
	void LB_STDCALL destroy();
	void LB_STDCALL update();
	void LB_STDCALL show();
	void LB_STDCALL print();
	
	lbErrCodes LB_STDCALL setName(char const * name, char const * appention);
	
	DECLARE_LB_UNKNOWN()

	char* ReportFileName;
		
	char* ReportName;
	char* untranslated_ReportName;
	
	// ------ wxReportWriter code ------
	
	wxReportObj	*pObj;
	wxReportWriter	*pReport;

	// Array of report values
	wxString**	strValue;
};
/*...e*/

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_SINGLETON_FUNCTOR(instanceOfPluginModule)

DECLARE_FUNCTOR(instanceOflbDatabaseReport)
DECLARE_FUNCTOR(instanceOflbPluginDatabaseReport)

DECLARE_FUNCTOR(instanceOflbDBReportAction)

#ifdef __cplusplus
}
#endif

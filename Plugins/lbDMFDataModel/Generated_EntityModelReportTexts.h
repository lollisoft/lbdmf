
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
            Ginsterweg 4

            65760 Eschborn (germany)
*/
/*...e*/

/** \brief class ReportTexts.
 * Documentation for ReportTexts
 */
class lbReportTextsModel : public lb_I_ReportTexts {
public:
	lbReportTextsModel();
	virtual ~lbReportTextsModel();

	long		LB_STDCALL addReportTexts(int _line, const char* _text, long _elementid,  long _ReportTextsID = -1);

	bool		LB_STDCALL selectReportTexts(long _id);
	int			LB_STDCALL getReportTextsCount();
	bool		LB_STDCALL hasMoreReportTexts();
	void		LB_STDCALL setNextReportTexts();
	void		LB_STDCALL finishReportTextsIteration();


	int			LB_STDCALL get_line();
	char*		LB_STDCALL get_text();
	long		LB_STDCALL get_elementid();
	

	long		LB_STDCALL get_id();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	void		LB_STDCALL setOperator(lb_I_Unknown* db);
	lbErrCodes	LB_STDCALL ExecuteOperation(const char* operationName);

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()
	
	UAP(lb_I_Container, ReportTexts)
	

	UAP(lb_I_Integer, currentline)
			
	UAP(lb_I_String, currenttext)
			
	UAP(lb_I_Long, currentelementid)
	

	
	UAP(lb_I_Long, currentReportTextsID)

	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflbReportTextsModel)

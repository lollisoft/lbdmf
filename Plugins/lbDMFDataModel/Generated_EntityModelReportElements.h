
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

/** \brief class ReportElements.
 * Documentation for ReportElements
 */
class lbReportElementsModel : public lb_I_ReportElements {
public:
	lbReportElementsModel();
	virtual ~lbReportElementsModel();

	long		LB_STDCALL addReportElements(const char* _name, const char* _description, int _x, int _y, int _w, int _h, long _reportid, long _typ,  long _ReportElementsID = -1);

	bool		LB_STDCALL selectReportElements(long _id);
	int			LB_STDCALL getReportElementsCount();
	bool		LB_STDCALL hasMoreReportElements();
	void		LB_STDCALL setNextReportElements();
	void		LB_STDCALL finishReportElementsIteration();


	char*		LB_STDCALL get_name();
	char*		LB_STDCALL get_description();
	int			LB_STDCALL get_x();
	int			LB_STDCALL get_y();
	int			LB_STDCALL get_w();
	int			LB_STDCALL get_h();
	long		LB_STDCALL get_reportid();
	
	long		LB_STDCALL get_typ();
	

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
	
	UAP(lb_I_Container, ReportElements)
	

	UAP(lb_I_String, currentname)
			
	UAP(lb_I_String, currentdescription)
			
	UAP(lb_I_Integer, currentx)
			
	UAP(lb_I_Integer, currenty)
			
	UAP(lb_I_Integer, currentw)
			
	UAP(lb_I_Integer, currenth)
			
	UAP(lb_I_Long, currentreportid)
	
	UAP(lb_I_Long, currenttyp)
	

	
	UAP(lb_I_Long, currentReportElementsID)

	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflbReportElementsModel)

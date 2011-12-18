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




class lbReports : public lb_I_Reports {
public:
	lbReports();
	virtual ~lbReports();

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()

	virtual long		LB_STDCALL addReport(const char* name, const char* description, long _id = -1);

	virtual bool		LB_STDCALL selectReport(long _id);
	virtual int			LB_STDCALL getReportCount();
	virtual bool		LB_STDCALL hasMoreReports();
	virtual void		LB_STDCALL setNextReport();
	virtual void		LB_STDCALL finishReportIteration();

	virtual long		LB_STDCALL getID();
	virtual char*		LB_STDCALL getReportName();
	virtual char*		LB_STDCALL getReportDescription();
	
	bool		LB_STDCALL ismarked() { return false; }
	void		LB_STDCALL mark() { }
	void		LB_STDCALL unmark() { }

	void		LB_STDCALL deleteUnmarked() { }
	void		LB_STDCALL deleteMarked() { }

	void		LB_STDCALL setOperator(lb_I_Unknown* db);
	lbErrCodes	LB_STDCALL ExecuteOperation(const char* operationName);

	UAP(lb_I_Container, Reports)
	UAP(lb_I_Long, currentID)
	UAP(lb_I_String, currentName)
	UAP(lb_I_String, currentDescription)	
};

class lbReportParameters : public lb_I_ReportParameters {
public:
	lbReportParameters();
	virtual ~lbReportParameters();

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()

	virtual long		LB_STDCALL addParameter(long reportid, const char* name, const char* value, long _id = -1);

	virtual bool		LB_STDCALL selectParameter(long _id);
	virtual int			LB_STDCALL getParameterCount();
	virtual bool		LB_STDCALL hasMoreParameters();
	virtual void		LB_STDCALL setNextParameter();
	virtual void		LB_STDCALL finishParameterIteration();

	virtual long		LB_STDCALL getReportID();
	virtual long		LB_STDCALL getID();
	virtual char*		LB_STDCALL getParameterName();
	virtual char*		LB_STDCALL getParameterValue();
	
	bool		LB_STDCALL ismarked() { return false; }
	void		LB_STDCALL mark() { }
	void		LB_STDCALL unmark() { }

	void		LB_STDCALL deleteUnmarked() { }
	void		LB_STDCALL deleteMarked() { }

	void		LB_STDCALL setOperator(lb_I_Unknown* db);
	lbErrCodes	LB_STDCALL ExecuteOperation(const char* operationName);

	UAP(lb_I_Container, ReportParameters)
	UAP(lb_I_Long, currentID)
	UAP(lb_I_Long, currentReportID)
	UAP(lb_I_String, currentName)
	UAP(lb_I_String, currentValue)	
};

class lbReportElements : public lb_I_ReportElements {
public:
	lbReportElements();
	virtual ~lbReportElements();

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()

	long		LB_STDCALL addElement(long reportid, const char* name, long typ, long x, long y, long w, long h, const char* description, long _id = -1);

	bool		LB_STDCALL selectElement(long _id);
	int			LB_STDCALL getElementCount();
	bool		LB_STDCALL hasMoreElements();
	void		LB_STDCALL setNextElement();
	void		LB_STDCALL finishElementIteration();

	long		LB_STDCALL getElementReportID();
	long		LB_STDCALL getID();
	char*		LB_STDCALL getElementName();
	char*		LB_STDCALL getElementDescription();
	long		LB_STDCALL getElementTyp();
	long		LB_STDCALL getElementX();
	long		LB_STDCALL getElementY();
	long		LB_STDCALL getElementW();
	long		LB_STDCALL getElementH();

	bool		LB_STDCALL ismarked() { return false; }
	void		LB_STDCALL mark() { }
	void		LB_STDCALL unmark() { }

	void		LB_STDCALL deleteUnmarked() { }
	void		LB_STDCALL deleteMarked() { }

	void		LB_STDCALL setOperator(lb_I_Unknown* db);
	lbErrCodes	LB_STDCALL ExecuteOperation(const char* operationName);

	UAP(lb_I_Container, ReportElements)
	UAP(lb_I_Long, currentID)
	UAP(lb_I_Long, currentReportID)
	UAP(lb_I_Long, currentTyp)
	UAP(lb_I_Long, currentX)
	UAP(lb_I_Long, currentY)
	UAP(lb_I_Long, currentW)
	UAP(lb_I_Long, currentH)
	UAP(lb_I_String, currentName)
	UAP(lb_I_String, currentDescription)	
};

class lbReportElementTypes : public lb_I_ReportElementTypes {
public:
	lbReportElementTypes();
	virtual ~lbReportElementTypes();

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()

	virtual long		LB_STDCALL addElementType(const char* name, const char* description, long _id = -1);

	virtual bool		LB_STDCALL selectElementType(long _id);
	virtual int			LB_STDCALL getElementTypeCount();
	virtual bool		LB_STDCALL hasMoreElementTypes();
	virtual void		LB_STDCALL setNextElementType();
	virtual void		LB_STDCALL finishElementTypeIteration();

	virtual long		LB_STDCALL getID();
	virtual char*		LB_STDCALL getElementName();
	virtual char*		LB_STDCALL getElementDescription();

	bool		LB_STDCALL ismarked() { return false; }
	void		LB_STDCALL mark() { }
	void		LB_STDCALL unmark() { }

	void		LB_STDCALL deleteUnmarked() { }
	void		LB_STDCALL deleteMarked() { }

	void		LB_STDCALL setOperator(lb_I_Unknown* db);
	lbErrCodes	LB_STDCALL ExecuteOperation(const char* operationName);

	UAP(lb_I_Container, ElementTypes)
	UAP(lb_I_Long, currentID)
	UAP(lb_I_String, currentName)
	UAP(lb_I_String, currentDescription)	
};

class lbReportTexts : public lb_I_ReportTexts {
public:
	lbReportTexts();
	virtual ~lbReportTexts();
	
	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()

	long		LB_STDCALL addText(long elementid, long line, const char* text, long _id = -1);

	bool		LB_STDCALL selectText(long _id);
	int			LB_STDCALL getTextCount();
	bool		LB_STDCALL hasMoreTexts();
	void		LB_STDCALL setNextText();
	void		LB_STDCALL finishTextIteration();

	char*		LB_STDCALL getText();
	long		LB_STDCALL getLine();
	long		LB_STDCALL getElementID();
	long		LB_STDCALL getID();

	bool		LB_STDCALL ismarked() { return false; }
	void		LB_STDCALL mark() { }
	void		LB_STDCALL unmark() { }

	void		LB_STDCALL deleteUnmarked() { }
	void		LB_STDCALL deleteMarked() { }

	void		LB_STDCALL setOperator(lb_I_Unknown* db);
	lbErrCodes	LB_STDCALL ExecuteOperation(const char* operationName);

	UAP(lb_I_Container, ReportTexts)
	UAP(lb_I_Long, currentID)
	UAP(lb_I_Long, currentElementID)
	UAP(lb_I_String, currentText)
	UAP(lb_I_Long, currentLine)	
};

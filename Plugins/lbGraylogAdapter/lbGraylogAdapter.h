/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2015  Lothar Behrens (lothar.behrens@lollisoft.de)

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

class lbGraylogAdapter : public lb_I_Log {
public:
	lbGraylogAdapter();
	virtual ~lbGraylogAdapter();

	virtual void LB_STDCALL logdirect(const char *msg, const char *f, int level);
	virtual void LB_STDCALL logdirect(const char *msg, const char *f, int level, const char* file, int line);

/*...slb_I_Log:0:*/
	virtual void LB_STDCALL log(const char *msg, long line, const char* file);
	virtual void LB_STDCALL log(int log);
	virtual void LB_STDCALL enable(const char *where);
	virtual void LB_STDCALL disable(const char *where);
	virtual void LB_STDCALL event_begin(const char *event);
	virtual void LB_STDCALL event_end(const char *event);
	virtual void LB_STDCALL setPrefix(const char* p);
	virtual lb_I_Log& LB_STDCALL operator<< (const int i);
	virtual lb_I_Log& LB_STDCALL operator<< (const long i);
	virtual lb_I_Log& LB_STDCALL operator<< (const char c);
	virtual lb_I_Log& LB_STDCALL operator<< (const char* string);
	virtual void LB_STDCALL setCustomLogFile(const char* name);
/*...e*/
	
	DECLARE_LB_UNKNOWN()
	
/*...sprivate:0:*/
private:
	void LB_STDCALL _realloc(int add_size);
	
	static char prefix[100];
	static int level;    
	static int doLog;
	static int firstlog;
	static clock_t start_time, end_time;
	static char lastevent[100];
	static int beinlog;
// No file, because Graylog is located on a server
//	static char f[PATH_MAX];
//	static lbMutex* mutex;
	static char* logmessage;
	static int lastsize;
	/*...e*/
	
};


DECLARE_FUNCTOR(instanceOflbGraylogAdapter)

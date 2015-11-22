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

/*...sIncludes:0:*/
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <stdio.h>
#include <string.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX
#endif
/*...e*/

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#include <lbGraylogAdapter.h>

#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/helpers/appenderattachableimpl.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/pointer.h"
#include "log4cplus/helpers/property.h"
#include "log4cplus/spi/loggingevent.h"

#include <gelf4cplus/Gelf4CPlusAppenderFactory.hpp>

int lbGraylogAdapter::level = 0;
int lbGraylogAdapter::firstlog = 0;
int lbGraylogAdapter::beinlog = 0;
char* lbGraylogAdapter::logmessage = NULL;
int lbGraylogAdapter::lastsize = 0;
clock_t lbGraylogAdapter::start_time, lbGraylogAdapter::end_time;
int lbGraylogAdapter::doLog = FALSE;
char lbGraylogAdapter::prefix[100];
//lbMutex* lbGraylogAdapter::mutex;

#ifdef __cplusplus
extern "C" {       
#endif            
	
/*...sclass lbUsersModel implementation:0:*/
IMPLEMENT_FUNCTOR(instanceOflbGraylogAdapter, lbGraylogAdapter)

#ifdef __cplusplus
}
#endif 

BEGIN_IMPLEMENT_LB_UNKNOWN(lbGraylogAdapter)
	ADD_INTERFACE(lb_I_Log)
END_IMPLEMENT_LB_UNKNOWN()


lbGraylogAdapter::lbGraylogAdapter() {
	_CL_VERBOSE << "lbGraylogAdapter::lbGraylogAdapter() called." LOG_
	firstlog = 1;
	doLog = 1;
	logmessage = NULL;
	lastsize = 0;
	_CL_VERBOSE << "lbGraylogAdapter::lbGraylogAdapter() leaving" LOG_
}

lbGraylogAdapter::~lbGraylogAdapter() {
	_CL_VERBOSE << "lbGraylogAdapter::~lbGraylogAdapter() called." LOG_
	if (logmessage != NULL) {
		free(logmessage);
		logmessage = NULL;
	}
}

lbErrCodes LB_STDCALL lbGraylogAdapter::setData(lb_I_Unknown*) {
	_LOG << "Error: lbGraylogAdapter::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL lbGraylogAdapter::logdirect(const char *msg, const char *f, int level, const char* file, int line) {
	gelf4cplus::appender::Gelf4CPlusAppenderFactory factory;
	
	log4cplus::helpers::Properties props;
	
	props.setProperty("udp.host", "127.0.0.1");
	//props.setProperty("udp.port", "");
	
	log4cplus::SharedAppenderPtr appender = factory.createObject(props);
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, appName)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, app)

	appender->setName(LOG4CPLUS_TEXT("lbGraylogAdapter"));

	app->getApplicationName(&appName);
	
	if (! appender->getErrorHandler ())
		_CL_VERBOSE << "Error: No error handler configured." LOG_
		
		log4cplus::spi::InternalLoggingEvent event(
			log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(appName->charrep())).getName(),
			log4cplus::DEBUG_LOG_LEVEL, LOG4CPLUS_TEXT(msg), file, line);	
	
	appender->doAppend(event);	
	appender->close();
}


void LB_STDCALL lbGraylogAdapter::logdirect(const char *msg, const char *f, int level) {
	logdirect(msg, f, level, __FILE__, __LINE__);
}

void LB_STDCALL lbGraylogAdapter::setCustomLogFile(const char* name) {
// Ignored
}

void LB_STDCALL lbGraylogAdapter::log(const char *msg, long line, const char* file) {
	//lbLock lbLock(sect, "lbLockSection");
	
	_CL_VERBOSE << "Do log a line..." LOG_
	
	if (firstlog == 0) {
		lbGraylogAdapter log;// = lbGraylogAdapter();
	}
	
	if (doLog == true) {
		char *m = (char*) malloc(strlen(msg)+sizeof(line)+strlen(file)+10);
		
		sprintf(m, "%s: %ld - %s", file, line, msg);
		logdirect(m, NULL, level, file, line);
		free((void*) m);
	}

	_CL_VERBOSE << "Done log a line..." LOG_
}

void LB_STDCALL lbGraylogAdapter::log(int log) {
	if (firstlog == 0) {
		lbGraylogAdapter log;// = lbGraylogAdapter();
	}
	doLog = log;
}

void LB_STDCALL lbGraylogAdapter::setPrefix(const char* p) {
	//COUT << "lbGraylogAdapter::setPrefix(char* p) called" << ENDL;
	{
		//lbLock lbLock(sect, "lbLockSection");
		strcpy(prefix, p);
	}
}

void LB_STDCALL lbGraylogAdapter::enable(const char *where) {
	char buf[100];
	doLog = true;
	
	if (firstlog == 0) {
		lbGraylogAdapter log;// = lbGraylogAdapter();
	}
	
	sprintf(buf, "Log is enabled at %s", where);
	//      level++;
	logdirect(buf, NULL, level, __FILE__, __LINE__);
	//      level++;
}

void LB_STDCALL lbGraylogAdapter::disable(const char *where) {
	char buf[100];
	
	if (firstlog == 0) {
		lbGraylogAdapter log;// = lbGraylogAdapter();
	}
	
	if (level <= 0) {
		logdirect("lbGraylogAdapter: Function sequence error. Disable called before enable!", NULL, 0, __FILE__, __LINE__);
		return;
	}
	
	doLog = false;
	sprintf(buf, "Log is disabled at %s", where);
	//      level--;
	logdirect(buf, NULL, level, __FILE__, __LINE__);
	//      level--;
}

void LB_STDCALL lbGraylogAdapter::event_begin(const char *event) {
/*
	if (firstlog == 0) {
		lbGraylogAdapter log;// = lbGraylogAdapter();
	}
	if (doLog == true) {
		beinlog = 1;
		start_time = clock();
		
		_CL_VERBOSE << event LOG_
	}
*/
}

void LB_STDCALL lbGraylogAdapter::event_end(const char *event) {
/*
	char buf[100];
	if (firstlog == 0) {
		lbGraylogAdapter log;// = lbGraylogAdapter();
	}
	
	if (doLog == true) {
		beinlog = 0;
		end_time = clock();
		
		FILE *fp;
		
		if ((end_time - start_time) > 5)
		{
			fp = fopen( f, "a" );
			if( fp != NULL ) {
				// rest of code goes here
				
				fprintf( fp, "Message %s: Duration\tProcess\t%ld\t%lu\n",
						event, lbGetCurrentProcessId(), end_time - start_time);
				fclose( fp );
			}
		}
	}
*/
}

/**
 * My new - possible bugfree - log system
 */

void LB_STDCALL lbGraylogAdapter::_realloc(int add_size) {
	if (logmessage == NULL) {
		char* buf = (char*) malloc(add_size);
		buf[0] = 0;
		logmessage = buf;
		//logmessage = (char*) ::realloc((void*) logmessage, add_size);
		lastsize = add_size;
	} else {
		char* buf = (char*) malloc(lastsize+add_size);
		buf[0] = 0;
		buf = strcpy(buf, logmessage);
		free(logmessage);
		logmessage = buf;
		//logmessage = (char*) ::realloc((void*) logmessage, lastsize+add_size);
		lastsize += add_size;
	}
} 

lb_I_Log& LB_STDCALL lbGraylogAdapter::operator<< (/*lb_I_Log* logger,*/ const int i) {
	_realloc(strlen(itoa(i)) + 1);
	lastsize = lastsize + strlen(itoa(i)) + 1;
	strcat(logmessage, itoa(i));
	return *this;
}

lb_I_Log& LB_STDCALL lbGraylogAdapter::operator<< (/*lb_I_Log* logger,*/ const long i) {
	char buf[20];
	int len;
	sprintf(buf, "%ld", i);
	len = strlen(buf);
	_realloc(len + 1);
	lastsize = lastsize + len + 1;
	strcat(logmessage, buf);
	return *this;
}

lb_I_Log& LB_STDCALL lbGraylogAdapter::operator<< (/*lb_I_Log* logger,*/ const char c) {
	_realloc(lastsize + 2);
	lastsize = lastsize + 2;
	char add[2] = "";
	add[0] = c;
	strcat(logmessage, add);
	if (c == '\n') {
		logdirect(logmessage, NULL, 0, __FILE__, __LINE__);
		
		free(logmessage);
		logmessage = NULL;
		lastsize = 0;
	}
	return *this;
}

lb_I_Log& LB_STDCALL lbGraylogAdapter::operator<< (/*lb_I_Log* logger,*/ const char* string) {
	if (string != NULL) {
		_realloc(lastsize+strlen(string) + 10);
		lastsize = lastsize + strlen(string) + 10;
		strcat(logmessage, string);
		
		if (strcmp(string, "\n") == 0) {
			logdirect(logmessage, NULL, 0);
			free(logmessage);
			logmessage = NULL;
			lastsize = 0;
		}
	} else {
		
	}
	return *this;
}





/*...e*/

/*...sclass lbPluginGraylogAdapter implementation:0:*/
/*...slbPluginGraylogAdapter:0:*/
class lbPluginGraylogAdapter : public lb_I_PluginImpl {
public:
	lbPluginGraylogAdapter();
	
	virtual ~lbPluginGraylogAdapter();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukGraylogAdapter)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginGraylogAdapter)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginGraylogAdapter, lbPluginGraylogAdapter)

/*...slbErrCodes LB_STDCALL lbPluginGraylogAdapter\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginGraylogAdapter::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginGraylogAdapter::setData(...) called.\n" LOG_

	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginGraylogAdapter::lbPluginGraylogAdapter() {
	_CL_VERBOSE << "lbPluginGraylogAdapter::lbPluginGraylogAdapter() called.\n" LOG_
	
	
	;
}

lbPluginGraylogAdapter::~lbPluginGraylogAdapter() {
	_CL_VERBOSE << "lbPluginGraylogAdapter::~lbPluginGraylogAdapter() called.\n" LOG_
}

bool LB_STDCALL lbPluginGraylogAdapter::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL lbPluginGraylogAdapter::autorun() {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_Unknown, uk)
	
	uk = getImplementation();
	
	UAP(lb_I_Log, logger)
	
	QI(uk, lb_I_Log, logger)

	setLoggerInstance(*&logger);
	
	logger++;
	
	return err;
}

void LB_STDCALL lbPluginGraylogAdapter::initialize() {
}
	
bool LB_STDCALL lbPluginGraylogAdapter::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginGraylogAdapter\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginGraylogAdapter::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukGraylogAdapter == NULL) {
		lbGraylogAdapter* GraylogAdapter = new lbGraylogAdapter();
	
		QI(GraylogAdapter, lb_I_Unknown, ukGraylogAdapter)
	} else {
		_CL_VERBOSE << "lbPluginGraylogAdapter::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukGraylogAdapter.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginGraylogAdapter\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginGraylogAdapter::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukGraylogAdapter == NULL) {
		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
		lbGraylogAdapter* GraylogAdapter = new lbGraylogAdapter();
		
		QI(GraylogAdapter, lb_I_Unknown, ukGraylogAdapter)
	}
	
	lb_I_Unknown* r = ukGraylogAdapter.getPtr();
	ukGraylogAdapter.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginGraylogAdapter::releaseImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukGraylogAdapter != NULL) {
		ukGraylogAdapter--;
		ukGraylogAdapter.resetPtr();
	}
}
/*...e*/
/*...e*/



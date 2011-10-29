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

#ifdef _MSC_VER

#pragma warning( disable: 4101 )
#pragma warning( disable: 4172 )

#endif

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_CLASSES_DLL scope:0:*/
#define LB_CLASSES_DLL
#include <lbclasses-module.h>
/*...e*/

#include <lbobject.h>
#include <lbkey.h>

#ifdef __cplusplus
extern "C" {
#endif

IMPLEMENT_FUNCTOR(instanceOfLocale, lbLocale)

#ifdef __cplusplus
}
#endif


BEGIN_IMPLEMENT_LB_UNKNOWN(lbLocale)
        ADD_INTERFACE(lb_I_Locale)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbLocale::setData(lb_I_Unknown* uk) {
	return ERR_NONE;
}

/// \todo Use environment variable to select language.
lbLocale::lbLocale() {
	
   	
	;
	_lang = (char*) malloc(100);
	_lang[0] = 0;
	strcpy(_lang, "german");
	dbAvailable = true;
	//REQUEST(getModuleInstance(), lb_I_Translations, translations)
}

lbLocale::~lbLocale() {
	if (_lang) free(_lang);
	_CL_LOG << "lbLocale::~lbLocale() called." LOG_
}

void LB_STDCALL lbLocale::setLanguage(const char* lang) {
	if (_lang) free(_lang);
	_lang = (char*) malloc(strlen(lang)+1);
	_lang[0] = 0;
	strcpy(_lang, lang);
}

void LB_STDCALL lbLocale::setTranslationData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	QI(uk, lb_I_Translations, translations)
}


/// \todo Add default language in insert statement. This enables automatic creation of new languages, if selected.
void LB_STDCALL lbLocale::translate(char ** text, const char* to_translate) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	if (translations == NULL) {
		UAP(lb_I_Database, database)

		char* dbbackend = meta->getSystemDatabaseBackend();
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
			_LOG << "Using plugin (" << dbbackend << ") database backend for translation..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, database)
			_LOG << "Using built in database backend for translation..." LOG_
		}

		if (database == NULL) {
			dbAvailable = false;
			char* temp = *text;
			*text = (char*) malloc(strlen(to_translate)+1);
			*text[0] = 0;
			strcpy(*text, to_translate);
			if (temp) free(temp);
			return;
		}
		
		_LOG << "Translate text with SQL statements..." LOG_

		database->init();

		const char* lbDMFPasswd = getenv("lbDMFPasswd");
		const char* lbDMFUser   = getenv("lbDMFUser");

		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		if (!dbAvailable || database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE) {
			_LOG << "lbLocale::translate() Error: Failed to connect to the database." LOG_
			dbAvailable = false;
			char* temp = *text;
			*text = (char*) malloc(strlen(to_translate)+1);
			*text[0] = 0;
			strcpy(*text, to_translate);
			if (temp) free(temp);
			return;
		}

		UAP(lb_I_Query, sampleQuery)

			sampleQuery = database->getQuery("lbDMF", 0);

		char buffer[800] = "";

		sprintf(buffer, "select translated from translations where language = '%s' and text = '%s'", _lang, to_translate);

		sampleQuery->skipFKCollecting();
		sampleQuery->query(buffer);

		// Fill up the available applications for that user.

		lbErrCodes err = sampleQuery->first();

		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {

	        UAP_REQUEST(getModuleInstance(), lb_I_String, s1)

	        s1 = sampleQuery->getAsString(1);

			char* temp = *text;

			if (strcmp(s1->charrep(), "") == 0) {
				*text = (char*) malloc(strlen(to_translate) + 1);
				*text[0] = 0;
				strcpy(*text, to_translate);
			} else {
				*text = (char*) malloc(strlen(s1->charrep()) + 1);
				*text[0] = 0;
				strcpy(*text, s1->charrep());
			}
			if (temp) free(temp);
		} else {
			char* temp = *text;
			*text = (char*) malloc(strlen(to_translate) + 1);
			*text[0] = 0;
			if (temp) free(temp);

			_LOG << "Translation for '" << to_translate << "' not found. Insert into database" LOG_

				buffer[0] = 0;

			sprintf(buffer, "insert into translations (text, translated, language) values('%s', '%s', '%s')", to_translate, to_translate, _lang);

			/* Sybase SQL Anywhere 5.5 has problems with state 24000. Maybe an auto commit problem */
			UAP(lb_I_Query, sampleQuery1)
				sampleQuery1 = database->getQuery("lbDMF", 0);
			sampleQuery1->skipFKCollecting();
			sampleQuery1->query(buffer);
			sampleQuery1->enableFKCollecting();

			strcpy(*text, to_translate);
		}

		sampleQuery->enableFKCollecting();
	} else {
		if (translations->selectText(to_translate, _lang) == false) {
			UAP(lb_I_Database, database)

			char* dbbackend = meta->getApplicationDatabaseBackend();
			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
				_LOG << "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, database)
				_LOG << "Using built in database backend for UML import operation..." LOG_
			}

			_LOG << "Translate text with SQL statements..." LOG_

			database->init();

			const char* lbDMFPasswd = getenv("lbDMFPasswd");
			const char* lbDMFUser   = getenv("lbDMFUser");

			if (!lbDMFUser) lbDMFUser = "dba";
			if (!lbDMFPasswd) lbDMFPasswd = "trainres";

			if (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE) {
				char* temp = *text;
				*text = (char*) malloc(strlen(to_translate)+1);
				*text[0] = 0;
				strcpy(*text, to_translate);
				if (temp) free(temp);
				return;
			}
			char buffer[800] = "";
			char* temp = *text;
			*text = (char*) malloc(strlen(to_translate) + 1);
			*text[0] = 0;
			if (temp) free(temp);

			_LOG << "Translation for '" << to_translate << "' not found. Insert into database" LOG_

				buffer[0] = 0;

			sprintf(buffer, "insert into translations (text, translated, language) values('%s', '%s', '%s')", to_translate, to_translate, _lang);

			/* Sybase SQL Anywhere 5.5 has problems with state 24000. Maybe an auto commit problem */
			UAP(lb_I_Query, sampleQuery1)
				sampleQuery1 = database->getQuery("lbDMF", 0);
			sampleQuery1->skipFKCollecting();

			sampleQuery1->query(buffer);
			sampleQuery1->enableFKCollecting();

			// Also store into translations object.

			translations->addTranslation(to_translate, *text, _lang);

			strcpy(*text, to_translate);
		} else {
			UAP_REQUEST(getModuleInstance(), lb_I_String, s1)
			char* temp = *text;

			*s1 = translations->getTranslationTranslated();

			if (strcmp(s1->charrep(), "") == 0) {
				*text = (char*) malloc(strlen(to_translate) + 1);
				*text[0] = 0;
				strcpy(*text, to_translate);
			} else {
				*text = (char*) malloc(strlen(s1->charrep()) + 1);
				*text[0] = 0;
				strcpy(*text, s1->charrep());
			}
			if (temp) free(temp);
		}
	}
}


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

class lbTranslationsModel : public lb_I_Translations {
public:
	lbTranslationsModel();
	virtual ~lbTranslationsModel();

	DECLARE_LB_UNKNOWN()

	long		LB_STDCALL addTranslation(const char* text, const char* translated, const char* language, long _id = -1);
	bool		LB_STDCALL selectTranslation(long _id);
	bool		LB_STDCALL selectText(const char* text, const char* language);
	int		LB_STDCALL getTranslationsCount();
	bool		LB_STDCALL hasMoreTranslations();
	void		LB_STDCALL setNextTranslation();
	void		LB_STDCALL finishTranslationIteration();
	
	long		LB_STDCALL getTranslationID();
	char*		LB_STDCALL getTranslationText();
	char*		LB_STDCALL getTranslationTranslated();
	char*		LB_STDCALL getTranslationLanguage();
	
	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	UAP(lb_I_Container, Translations)
	UAP(lb_I_Container, Lookup)
	UAP(lb_I_Long, currentTranslationID)
	UAP(lb_I_String, currentTranslationText)
	UAP(lb_I_String, currentTranslationTranslated)
	UAP(lb_I_String, currentTranslationLanguage)

	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflbTranslationsModel)

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
#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif
/*...sincludes:0:*/

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include <conio.h>

#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <iostream>
#ifndef OSX
#ifndef USE_MPATROL
#include <malloc.h>
#endif
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif


/*...e*/

/*...sDocumentation:0:*/
/** \page Basetypes Testing DMF environment - Test basic data types.
 *
 * \section Introduction
 *
 * The sample is located in RegressionTests/Basetypes.
 *
 * \code
int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;

	mm = getModuleInstance();
	mm->setModuleManager(mm, __FILE__, __LINE__);

	_CL_LOG << "Test basetypes" LOG_

	UAP_REQUEST(mm, lb_I_String, string1)
	UAP_REQUEST(mm, lb_I_String, string2)

	string1->setData("Test basetypes...");
	string2->setData("Test basetypes...");

	if (*&string1 == *&string2) {
		_CL_LOG << "Strings are identical" LOG_
	} else {
		_CL_LOG << "Strings are not identical" LOG_
	}

	lb_I_String* s1 = string1.getPtr();
	lb_I_String* s2 = string2.getPtr();

        if (s1 == s2) {
                _CL_LOG << "Strings are identical" LOG_
        } else {
                _CL_LOG << "Strings are not identical" LOG_
        }

	if (string1->equals(*&string2)) {
                _CL_LOG << "Strings are identical" LOG_
        } else {
                _CL_LOG << "Strings are not identical" LOG_
        }

	if (string1 == s2) {
                _CL_LOG << "Strings are identical" LOG_
        } else {
                _CL_LOG << "Strings are not identical" LOG_
        }

        return 0;
}
 * \endcode
 *
 * \section Details
 *
 */
/*...e*/

int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;

	mm = getModuleInstance();
	mm->setModuleManager(mm, __FILE__, __LINE__);

	_CL_LOG << "Test basetypes" LOG_

	UAP_REQUEST(mm, lb_I_Long, l1)
	UAP_REQUEST(mm, lb_I_Long, l2)

	l1->setData(1);
	l2->setData(1);

	if (l1->equals(*&l2)) {
	    _CL_LOG << "Long values are equal." LOG_
	} else {
	    _CL_LOG << "Long values are not equal." LOG_
	}


	UAP_REQUEST(mm, lb_I_String, replaceTest)

	*replaceTest = "\"Hallo\"";
	replaceTest->replace("Hallo", "Duda");
	replaceTest->replace("\"", "'");
	replaceTest->replace("a'", "aaa'");
	printf("Replaced string: %s\n", replaceTest->charrep());

	*replaceTest = "Hallo == \"\"";
	replaceTest->replace("Hallo", "Duda");
	replaceTest->replace("\"", "&quot;");
	printf("Replaced string: %s\n", replaceTest->charrep());

	*replaceTest = "select \"lala\" from \"bla\" where \"lili\" = 'lolo'";
	replaceTest->replace("\"", "&quot;");
	printf("Replaced string: %s\n", replaceTest->charrep());


	UAP_REQUEST(mm, lb_I_String, string1)
	char buf1[100] = "";
	UAP_REQUEST(mm, lb_I_String, string2)
	char buf2[100] = "";

	string1->setData("Test basetypes...");
	string2->setData("Test basetypes...");

	_CL_LOG << "Test (*&string1 == *&string2)" LOG_

	if (*&string1 == *&string2) {
		_CL_LOG << "Strings are identical" LOG_
	} else {
		_CL_LOG << "Strings are not identical" LOG_
	}

	lb_I_String* s1 = string1.getPtr();
	lb_I_String* s2 = string1.getPtr();

	_CL_LOG << "String has " << s1->getRefCount() << " references." LOG_

	//s1->release(__FILE__, __LINE__);

	_CL_LOG << "Test (s1 == s2)" LOG_

        if (s1 == s2) {
                _CL_LOG << "Strings are identical" LOG_
        } else {
                _CL_LOG << "Strings are not identical" LOG_
        }

	_CL_LOG << "Test (string1->equals(*&string2))" LOG_

	if (string1->equals(*&string2)) {
                _CL_LOG << "Strings are identical" LOG_
        } else {
                _CL_LOG << "Strings are not identical" LOG_
        }

	_CL_LOG << "Test (string1 == s2)" LOG_

	if (string1 == s2) {
                _CL_LOG << "Strings are identical" LOG_
        } else {
                _CL_LOG << "Strings are not identical" LOG_
        }

	_CL_LOG << "Test Stream classes." LOG_

	UAP_REQUEST(mm, lb_I_OutputStream, out)

	out->setFileName("Test.txt");
	out->open();

	int n = 0;

	int count = 10;

	*out << count;
	for (int i = 0; i < count; i++) {
		*out << "Testline: " << i;
	}

	out->close();

	UAP_REQUEST(mm, lb_I_InputStream, in)

	in->setFileName("Test.txt");

	in->open();

	char* buf = NULL;

	*in >> count;

	for (int i = 0; i < count; i++) {
		n = 0;
		*in >> buf >> n;
		_CL_LOG << "'" << buf << "', " << n LOG_;
	}

	free(buf);
	buf = NULL;

	_CL_LOG << "Test string appending..." LOG_

	UAP_REQUEST(getModuleInstance(), lb_I_String, testappend)

	*testappend = "1 part.";
	*testappend += " 2 part.";
	*testappend += " 3 part.";
	*testappend += " 4 part.";
	*testappend += " 5 part.";
	*testappend += " 6 part.";
	*testappend += " 7 part.";
	*testappend += " 8 part.";
	*testappend += " 9 part.";
	*testappend += " 10 part.";
	*testappend += " 11 part.";


	_CL_LOG << "Produced this string: " << testappend->charrep() LOG_

        return 0;
}

/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2013  Lothar Behrens (lothar.behrens@lollisoft.de)

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

#ifndef LB_DIRECTORYBROWSER
#define LB_DIRECTORYBROWSER

class DirectoryBrowser : lb_I_DirectoryBrowser {
public:
	DirectoryBrowser();
	virtual ~DirectoryBrowser();
	
	DECLARE_LB_UNKNOWN()
	
	lb_I_Container* LB_STDCALL getDirectories(lb_I_String* path);
	lb_I_Container* LB_STDCALL getDirectories(const char* path);
	lb_I_Container* LB_STDCALL getFiles(lb_I_String* path);
	lb_I_Container* LB_STDCALL getFiles(const char* path);
};


#ifdef __cplusplus
extern "C" {
#endif

DECLARE_FUNCTOR(instanceOfDirectoryBrowser)

#ifdef __cplusplus
}
#endif

#endif // LB_DIRECTORYBROWSER

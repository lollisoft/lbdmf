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

#ifndef __LB_INTERFACES_SUB_WXWRAPPER__
#define __LB_INTERFACES_SUB_WXWRAPPER__

/**
 * Forward declarations, needed to use wx peers.
 * A peer is derived from the wrapped companion class.
 */

class lb_wxFrame;


/**
 * \brief Peer interfaces to its wx companions.
 *
 * Don't know, if this is really good. The derived class must be predefined and therefore
 * The derived class name is predefined.
 *
 * If others like to write another GUI wrapper, say, with MFC, they need to name their
 * class to this predefined name.
 */

class lb_I_wxFrame : public lb_I_Unknown,
public lb_I_EventSink
{
public:
	virtual lb_wxFrame* getPeer() = 0;
};

#endif // __LB_INTERFACES_SUB_WXWRAPPER__

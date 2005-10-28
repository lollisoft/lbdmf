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
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.92 $
 * $Name:  $
 * $Id: lbModule.cpp,v 1.92 2005/10/28 05:54:13 lollisoft Exp $
 *
 * $Log: lbModule.cpp,v $
 * Revision 1.92  2005/10/28 05:54:13  lollisoft
 * Fixed memory leak by explicitly deleting singleton instance 'lbModule'.
 * There is still a reference counting problem and the class contains a
 * reference counted instance of it's own. So normally it can't be deleted
 * while a call to release.
 *
 * Revision 1.91  2005/10/16 17:39:56  lollisoft
 * Improvements in memory usage.
 *
 * Revision 1.90  2005/08/10 22:01:49  lollisoft
 * Reactivated macro.
 *
 * Revision 1.89  2005/06/27 10:32:09  lollisoft
 * Mostly changes to conio.h conflicts while XCode build
 *
 * Revision 1.88  2005/05/04 22:09:38  lollisoft
 * Many memory leaks fixed. Changed _CL_LOG to _CL_VERBOSE.
 *
 * Revision 1.87  2005/05/03 21:16:22  lollisoft
 * Better memtrack support
 *
 * Revision 1.86  2005/05/01 21:27:09  lollisoft
 * Added informative filename to show when printing memory leaks.
 * One more debug line.
 *
 * Thanks to the trmem code from Open Watcom.
 *
 * Revision 1.85  2005/05/01 01:12:35  lollisoft
 * Found a really big memory leak. It happens due to missing setup of ref variable
 * in lbFunctorEntity class of lbModule.cpp.
 *
 * Due to the fact, that I use this class for each instance retrival, it wasted
 * much memory. More: See documentation in that class.
 *
 * Revision 1.84  2005/04/24 18:48:41  lollisoft
 * Little memory leak fixed.
 *
 * Revision 1.83  2005/03/31 09:00:17  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.82  2005/03/19 16:41:49  lollisoft
 * Implemented i18n.
 *
 * Revision 1.81  2005/03/14 18:59:01  lollisoft
 * Various changes and additions to make plugins also work with database forms
 *
 * Revision 1.80  2005/03/04 10:47:10  lollisoft
 * Little changes for my new Mac OS X
 *
 * Revision 1.79  2005/03/03 08:36:04  lollisoft
 * Return error codes, if unable to get a functor.
 *
 * Revision 1.78  2005/02/13 12:59:13  lollisoft
 * Removed unnessesary messages and in DllMain, changed _CL_VERBOSE to _CL_VERBOSE
 *
 * Revision 1.77  2005/02/10 17:02:26  lollisoft
 * Changes for Mac OS X
 *
 * Revision 1.76  2005/01/23 13:43:04  lollisoft
 * std:: is only under linux working
 *
 * Revision 1.75  2005/01/21 14:59:29  lollisoft
 * Removed some unused log messages
 *
 * Revision 1.74  2004/08/10 18:25:00  lollisoft
 * Lesser logging messages.
 *
 * Revision 1.73  2004/06/16 22:10:14  lollisoft
 * Added config for lb_I_Plugin
 *
 * Revision 1.72  2004/06/07 20:27:26  lollisoft
 * Initial plugin manager implementation
 *
 * Revision 1.71  2004/05/27 08:14:53  lollisoft
 * Implemented complete MSVC IDE project. It compiles, but has runtime errors. The project files have no clear location layout.
 *
 * Revision 1.70  2004/05/08 10:54:17  lollisoft
 * free memory bug, variable uninitialized
 *
 * Revision 1.69  2004/04/11 07:26:03  lollisoft
 * Resolved conflict
 *
 * Revision 1.68  2004/04/10 17:54:24  lollisoft
 * Current version runs on linux again. There was a bug in additional linux code to strcat to a variable. This variable was given as a parameter and therefore I cannot assume, that I am able to have a big enough buffer for that action. Electric Fence gave me the hint for that bug.
 *
 * Revision 1.67  2004/03/22 22:11:07  lollisoft
 * Current version works under linux
 *
 * Revision 1.66  2004/03/20 11:36:20  lollisoft
 * Added a hardcoded repository as an alternative to XML
 *
 * Revision 1.65  2004/02/02 22:07:50  lollisoft
 * Libraries compiles again under linux and most of the test application works. But have problems with database test.
 *
 * Revision 1.64  2004/01/24 16:19:03  lollisoft
 * minor change
 *
 * Revision 1.63  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.62  2003/08/22 17:33:16  lollisoft
 * removed debuging
 *
 * Revision 1.61  2003/08/18 22:05:56  lollisoft
 * Bug in new interface repository solved
 *
 * Revision 1.60  2003/08/16 17:59:07  lollisoft
 * Added usage for new interface repository, but deactivated
 * (//#define USE_INTERFACE_REPOSITORY)
 *
 * Revision 1.59  2003/08/08 16:35:17  lollisoft
 * New implementation of interface repository works, but I have problems with multiple module loading in lbhook
 *
 * Revision 1.58  2003/07/17 19:41:41  lollisoft
 * removed some log messages
 *
 * Revision 1.57  2003/07/17 18:51:41  lollisoft
 * Begin develop a hopefully faster and less memory consuming
 * XML wrapper.
 *
 * Revision 1.56  2003/07/15 22:20:43  lollisoft
 * Removed debug messages
 *
 * Revision 1.55  2003/07/10 21:11:50  lollisoft
 * More debug
 *
 * Revision 1.54  2003/06/16 21:48:06  lollisoft
 * Removed debug messages
 *
 * Revision 1.53  2003/06/09 14:50:33  lollisoft
 * Minor changes
 *
 * Revision 1.52  2003/05/24 02:11:47  lollisoft
 * Linux don't know DebugBreak()
 *
 * Revision 1.51  2003/04/28 20:32:07  lollisoft
 * Moved back to watcom
 *
 * Revision 1.50  2003/03/14 16:00:42  lollisoft
 * Removed the problem with _chkesp() failure. But still crash in my GUI app
 *
 * Revision 1.49  2003/02/17 21:34:35  lollisoft
 * Much problems with compilation solved, bu wy came this ??
 *
 * Revision 1.48  2003/01/27 21:18:34  lothar
 * More logging
 *
 * Revision 1.47  2003/01/24 17:55:55  lothar
 * Added debug information
 *
 * Revision 1.46  2003/01/15 22:42:20  lothar
 * Compiles with MSC
 *
 * Revision 1.45  2002/12/29 16:09:29  lothar
 * Intent to go public
 *
 * Revision 1.44  2002/12/09 19:37:16  lothar
 * removed debugging messages
 *
 * Revision 1.43  2002/12/07 16:11:26  lothar
 * minor changes
 *
 * Revision 1.42  2002/12/07 13:31:20  lothar
 * minor changes
 *
 * Revision 1.41  2002/12/07 06:54:59  lothar
 * Current Linux attempt is buggy
 *
 * Revision 1.40  2002/11/29 19:50:26  lothar
 * Compiles again under linux, but some problems at runtime with DOMString
 *
 * Revision 1.39  2002/10/17 17:36:44  lothar
 * Use of _CL_VERBOSE macro
 *
 * Revision 1.38  2002/10/11 17:20:57  lothar
 * Before CL_LOG change
 *
 * Revision 1.37  2002/10/04 16:53:11  lothar
 * Replaced old LOG macro with the new
 * _CL_VERBOSE << "text" << integer value LOG_
 * combination. This makes sprintf obsolete.
 *
 * Revision 1.36  2002/10/01 19:22:59  lothar
 * Broken
 *
 * Revision 1.35  2002/09/19 19:34:12  lothar
 * Buggy version - only, if menu is really created
 *
 * Revision 1.34  2002/08/31 10:49:14  lothar
 * Deactivated IR_USAGE
 *
 * Revision 1.33  2002/08/21 18:01:37  lothar
 * Implemented the new container functions for direct access
 *
 * Revision 1.32  2002/07/23 17:48:55  lothar
 * Current version runs
 *
 * Revision 1.31  2002/06/20 22:16:47  lothar
 * Found bug (really not a bug) about container deletion message.
 * Message removed by another order of UAP instances.
 *
 * Revision 1.30  2002/06/20 21:04:29  lothar
 * Using tracking for better debugging
 *
 * Revision 1.29  2002/06/01 09:16:06  lothar
 * Removed some unneccesary code
 *
 * Revision 1.28  2002/05/30 17:53:01  lothar
 * Current development seems to run
 *
 * Revision 1.27  2002/05/01 14:17:10  lothar
 * This version does not compile
 *
 * Revision 1.26  2002/04/25 18:07:57  lothar
 * Added Skiplist implementation
 *
 * Revision 1.25  2002/04/24 18:36:19  lothar
 * Dump references and print references
 *
 * Revision 1.24  2002/04/18 19:23:43  lothar
 * Does not compile ???
 *
 * Revision 1.23  2002/04/15 18:24:31  lothar
 * Huge changes - works good
 *
 * Revision 1.22  2002/02/25 06:17:19  lothar
 * Much changes
 * Program seems to run, but performance is very slow
 *
 * Revision 1.21  2001/12/15 17:53:26  lothar
 * Reactivated deleteValue usage
 *
 * Revision 1.19  2001/12/12 17:12:44  lothar
 * Hehe - runs on linux
 *
 * Revision 1.18  2001/10/08 20:11:22  lothar
 * This module now compiles under linux
 *
 * Revision 1.17  2001/10/08 19:34:27  lothar
 * Include lbXMLConfig.h no longer used
 *
 * Revision 1.15  2001/10/04 19:28:32  lothar
 * Current version seems to work good (without big memory holes)
 *
 * Revision 1.14  2001/08/18 07:38:55  lothar
 * Current version runs again. Module management is not ready.
 *
 * Revision 1.13  2001/07/18 22:43:55  lothar
 * Using more UAP's - works, but mem leak still there ?
 *
 * Revision 1.12  2001/07/18 05:50:18  lothar
 * Seems to work now (lbDOMNode::parent - refcount must be corrected)
 *
 * Revision 1.11  2001/07/12 20:45:46  lothar
 * Test UNKNOWN_AUTO_PTR, but a declaration does not
 * work in a class, because of the explicit reference argument.
 *
 * Revision 1.10  2001/07/11 16:04:33  lothar
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.9  2001/06/23 07:18:53  lothar
 * Interface repository now works with the basic test
 *
 **************************************************************/
/*...e*/

//#pragma warning( disable: 4101 )
//#pragma warning( disable: 4018 )
//#pragma warning( disable: 4229 )
//#pragma warning( disable: 4102 )

//#define IR_USAGE

#define USE_INTERFACE_REPOSITORY

/*...sincludes:0:*/
#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#ifdef OSX
#include <sys/malloc.h>
#endif
#ifndef OSX
#include <malloc.h>
#endif
#include <lbInterfaces.h>

/*...sLB_MODULE_DLL scope:0:*/
#define LB_MODULE_DLL
#include <lbmodule-module.h>
/*...e*/

#include <lbConfigHook.h>


#include <lbModule.h>
//#include <lbXMLConfig.h>
//#include <lbkey.h>
/*...e*/

class lbSkipListElement;
typedef lb_I_Element* Elem;
#define MAXLEVEL 9

char* strdup(const char* s) {
	if (s == NULL) return NULL;
	char* temp = (char*) malloc(strlen(s)+1);
	temp[0] = 0;
	strcpy(temp, s);
	return temp;
}

/*...sclass SkipNode:0:*/
class SkipNode {
  public:
    int myLevel;
    UAP(lb_I_Element, value, __FILE__, __LINE__)
    SkipNode** forward;
    
    SkipNode();
    SkipNode(lb_I_Element* r, int level);
    virtual ~SkipNode();
    
};
/*...e*/
/*...sclass SkipList:0:*/
class SkipList : public lb_I_Container {
private:
      SkipNode* head;
      SkipNode* skipiterator;
      int level;
      int flag;

      void AdjustHead(int& level) {level = MAXLEVEL;}

public:
	SkipList();
	virtual ~SkipList();
	
	
	DECLARE_LB_UNKNOWN()
	DECLARE_LB_I_CONTAINER_IMPL()

public:


	lb_I_Unknown* search(lb_I_KeyBase*);
	void insert(Elem);
      
      
      
	void remove(Elem);
	int can_dump();
	Elem dump_next();
};
/*...e*/
/*...sclass lbSkipListElement:0:*/
class lbSkipListElement : public lb_I_Element {
public:
    lbSkipListElement() { 
    	ref = STARTREF; 
    	next = NULL; 
    	data = NULL; 
    	key = NULL; 
    	manager = NULL;
    }
    virtual ~lbSkipListElement();
	
    lbSkipListElement(const lb_I_Element &e) { 
    	ref = STARTREF; 
    	next = e.getNext(); 
	manager = NULL;
    }

    DECLARE_LB_UNKNOWN()

    DECLARE_LB_ELEMENT(lbSkipListElement)
};
/*...e*/

/*...sclass lbSkipListContainer:0:*/
/*...sSkipNode implementation:0:*/
SkipNode::SkipNode() {
    	myLevel = MAXLEVEL;
    	value = NULL;
    	forward = new SkipNode* [myLevel+1];
    	for (int i=0; i<=myLevel; i++)
    	    forward[i] = NULL;
}
    
SkipNode::SkipNode(lb_I_Element* r, int level) {
        myLevel = level;
        value = r;
        forward = new SkipNode* [level+1];
        for (int i=0; i<=level; i++)
            forward[i] = NULL;
}
SkipNode::~SkipNode() { 
      _CL_VERBOSE << "SkipNode destructor called" LOG_
      delete [] forward; 
      _CL_VERBOSE << "Deleted forward array" LOG_
      
      if (value != NULL) RELEASE(value)
      _CL_VERBOSE << "Released value of this element" LOG_
}
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(SkipList)
	ADD_INTERFACE(lb_I_Container)
END_IMPLEMENT_LB_UNKNOWN()


lbErrCodes LB_STDCALL SkipList::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "SkipList::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}
SkipList::SkipList() {
	iteration = 0;
	head = new SkipNode();
	skipiterator = NULL;
	flag = 1;
	level = MAXLEVEL;
	_CL_VERBOSE << "SkipList::SkipList() in " << __FILE__ << " called" LOG_
}

SkipList::~SkipList() {
	delete head;
}
/*...sSkipList\58\\58\Count\40\\41\:0:*/
int LB_STDCALL SkipList::Count() { 
        return count; 
} 
/*...e*/
/*...sSkipList\58\\58\deleteAll\40\\41\:0:*/
void LB_STDCALL SkipList::deleteAll() { 
	_CL_VERBOSE << "DeleteAll() called" LOG_
	delete head;
	_CL_VERBOSE << "Deleted head" LOG_
	head = new SkipNode();
	_CL_VERBOSE << "New head created" LOG_
	level = MAXLEVEL;

	iteration = 0;
	skipiterator = NULL;
} 
/*...e*/
/*...sSkipList\58\\58\exists\40\lb_I_KeyBase\42\\42\ const key\41\:0:*/
int LB_STDCALL SkipList::exists(lb_I_KeyBase** const key) { 
    lb_I_Unknown* s = search(*key);
    
    if (s == NULL) return 0;	

    return 1; 
} 
/*...e*/
/*...sSkipList\58\\58\insert\40\lb_I_Unknown\42\\42\ const e\44\ lb_I_KeyBase\42\\42\ const key\41\:0:*/
lbErrCodes LB_STDCALL SkipList::insert(lb_I_Unknown** const e, lb_I_KeyBase** const key) { 
        lbErrCodes err = ERR_NONE; 
        
        lbSkipListElement* el = new lbSkipListElement(*e, *key);

        insert(el);
        
        return err; 
} 
/*...e*/
/*...sSkipList\58\\58\remove\40\lb_I_KeyBase\42\\42\ const key\41\:0:*/
lbErrCodes LB_STDCALL SkipList::remove(lb_I_KeyBase** const key) { 
        lbErrCodes err = ERR_NONE; 
        lbSkipListElement* el = new lbSkipListElement(*key, *key);
        
        remove(el);
        
        delete el;

        return err; 
} 
/*...e*/
/*...sSkipList\58\\58\_insert\40\lb_I_Unknown\42\\42\ const e\44\ lb_I_KeyBase\42\\42\ const key\41\:0:*/
lbErrCodes LB_STDCALL SkipList::_insert(lb_I_Unknown** const e, lb_I_KeyBase** const key) { 
/*...sbla:0:*/
#ifdef bla
    if (container_data == NULL) { 
        lbElement* _data = new lbElement(*e, *key); 
        _data->setModuleManager(manager.getPtr(), __FILE__, __LINE__); 

        _data->queryInterface("lb_I_Element", (void**) &container_data, __FILE__, __LINE__); 
        if (container_data == NULL) _CL_VERBOSE << "Could not get unknown interface of lbElement!" LOG_ 

        lb_I_Unknown* uk_o = NULL; 
        if ((uk_o = container_data->getObject()) == NULL) { 
                _CL_VERBOSE << "Failed to insert first element in SkipList::insert") LOG_ 
                return ERR_CONTAINER_INSERT; 
        } else RELEASE(uk_o); 
    } 
    else { 
        lb_I_Element* temp; 
        for (temp = container_data; temp != NULL; temp = temp->getNext()) { 
            lb_I_Element* next = temp->getNext(); 

            if (next != NULL) { 
                if (next->getKey() < *key) { 
                    lbElement* el = new lbElement(*e, *key, next); 
                    el->setModuleManager(manager.getPtr(), __FILE__, __LINE__); 
                    temp->setNext(el); 
                    return ERR_NONE; 
                } 
            } 
            else { 
            	lbElement* el = new lbElement(*e, *key, next); 
            	el->setModuleManager(manager.getPtr(), __FILE__, __LINE__); 
                temp->setNext(el); 
                return ERR_NONE; 
            } 
        } 
    } 
#endif    
/*...e*/
    return ERR_NONE; 
} 
/*...e*/
/*...sSkipList\58\\58\_remove\40\lb_I_KeyBase\42\\42\ const key\41\:0:*/
lbErrCodes LB_STDCALL SkipList::_remove(lb_I_KeyBase** const key) { 
/*...sbla:0:*/
#ifdef bla
    if (container_data == NULL) { 
        LOG("Error: Can't remove from empty container!"); 
        return ERR_CONTAINER_REMOVE; 
    } 

    lb_I_Element* pre = container_data; 
    container_data = container_data->getNext(); 

    if (pre->getKey() == *key) { 
        RELEASE(pre); 
        return ERR_NONE; 
    } 

    for (lb_I_Element* temp = container_data; temp != NULL; temp = container_data->getNext()) { 
        if (temp->getKey() == *key) { 
            pre->setNext(temp->getNext()); 
            RELEASE(temp); 
            return ERR_NONE; 
        } 
    } 
#endif
    _CL_VERBOSE << "Error: No object with that key" LOG_
/*...e*/
    return ERR_CONTAINER_REMOVE; 
} 
/*...e*/
/*...sSkipList\58\\58\hasMoreElements\40\\41\:0:*/
int LB_STDCALL SkipList::hasMoreElements() { 
    return can_dump();
} 
/*...e*/
/*...sSkipList\58\\58\nextElement\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL SkipList::nextElement() { 

	Elem e = dump_next();
	
	if(e != NULL) {
		return e->getObject();
	} else {
	        _CL_VERBOSE << "Error: Please call hasMoreElements first to check if any elements are available!" LOG_ 
	        return NULL; 
	}
} 
/*...e*/
/*...sSkipList\58\\58\getElement\40\lb_I_KeyBase\42\\42\ const key\41\:0:*/
lb_I_Unknown* LB_STDCALL SkipList::getElement(lb_I_KeyBase** const key) { 

    return search(*key);
} 
/*...e*/
/*...sSkipList\58\\58\setElement\40\lb_I_KeyBase\42\\42\ key\44\ lb_I_Unknown \42\\42\ const e\41\:0:*/
void LB_STDCALL SkipList::setElement(lb_I_KeyBase** key, lb_I_Unknown ** const e) { 
    remove(key); 
    insert(e, key); 
}
/*...e*/
lb_I_Unknown* LB_STDCALL SkipList::getElementAt(int i) {
        _CL_VERBOSE << "SkipList::getElementAt(int i) not implemented" LOG_
        int ii = 0;
        lb_I_Element* temp = container_data;
        while (temp != NULL) {
                if (ii == i) return temp->getObject();
                temp = temp->getNext();
        }
        return NULL;
}
lb_I_KeyBase* LB_STDCALL SkipList::getKeyAt(int i) {
        _CL_VERBOSE << "SkipList::getKeyAt(int i) not implemented" LOG_
        int ii = 0;
        lb_I_Element* temp = container_data;
        while (temp != NULL) {
                if (ii == i) return temp->getKey();
                temp = temp->getNext();
        }
        return NULL;
}


/*...srandomLevel\40\void\41\:0:*/
int randomLevel(void) { // Pick a level on exponential distribution
  int level;
  for (level=0; (rand()%2) == 0; level++); // Do nothing
  return level;
}
/*...e*/
/*...sSkipList\58\\58\search\40\lb_I_KeyBase\42\ searchKey\41\:0:*/
lb_I_Unknown* SkipList::search(lb_I_KeyBase* searchKey) { // Skiplist Search
  SkipNode *x = head;                  // Dummy header node
  
  if (x == NULL) _CL_VERBOSE << "Error: NULL pointer while searching in skiplist" LOG_
  
  for (int i=level; i>=0; i--) {
    while ((x->forward[i] != NULL) && (*(x->forward[i]->value) < searchKey)) {
      x = x->forward[i];
    }
  }
  x = x->forward[0];  // Move to actual record, if it exists
  if ((x != NULL) && (*(x->value) == searchKey)) {
  	return x->value->getObject();
  } else return NULL;
}
/*...e*/
/*...sSkipList\58\\58\insert\40\Elem newValue\41\:0:*/
void SkipList::insert(Elem newValue) { // Insert into skiplist
  SkipNode *x = head;           // Start at header node
  int i;
  int newLevel = randomLevel(); // Select level for new node

  if (newLevel > level) {       // New node will be deepest in list
    AdjustHead(newLevel);       // Add null pointers to header
    level = newLevel;
  }
	  
  SkipNode** update = NULL;    // Update tracks end of each level
  
  update = new SkipNode* [level+1]; 

  for(i=level; i>=0; i--) { // Search for insert position
    lb_I_Element* e = (x->forward[i] != NULL) ? x->forward[i]->value.getPtr() : NULL;
    while((x->forward[i] != NULL) && (*e < newValue->getKey())) {
      x = x->forward[i];
      e = x->forward[i] != NULL ? x->forward[i]->value.getPtr() : NULL;
    }
    update[i] = x;              // Keep track of end at level i
  }
  
  x = new SkipNode(newValue, newLevel); // Create new node
  
  for (i=0; i<=newLevel; i++) { // Splice into list
    x->forward[i] = update[i]->forward[i]; // Who x points to
    update[i]->forward[i] = x;             // Who y points to
  }
}
/*...e*/
/*...sSkipList\58\\58\remove\40\Elem searchKey\41\:0:*/
void SkipList::remove(Elem searchKey) {
    // update holds pointers to next elements of each level
    SkipNode** update = NULL;    // Update tracks end of each level
  
    update = new SkipNode* [level+1]; 
    
    SkipNode *x = head;                  // Dummy header node
    SkipNode *found = NULL;
    
    for (int i=level; i>=0; i--) {

      while ((x->forward[i] != NULL) && (*(x->forward[i]->value) < searchKey->getKey())) {
        x = x->forward[i];
      }
        
      update[i] = x;
    }

    x = x->forward[0];  // Move to actual record, if it exists
    
    if ((x != NULL) && (*(x->value) == searchKey->getKey())) found = x;
    else return;

    // element found, so rebuild list without node:
    if (*(found->value) == searchKey->getKey()) {
      for (int i=0; i<=level; i++) {
        if (update[i]->forward[i] == found) {
          update[i]->forward[i] = found->forward[i];
        }
      }
      
      // element can be freed now (would happen automatically):
      delete found;
      
      // maybe we have to downcorrect the level of the list: 
      while (level>0  &&  head->forward[level] != NULL && head->forward[level]->value==NULL) {
        level--;
      }
    }
  }


/*...e*/
/*...sSkipList\58\\58\can_dump\40\\41\:0:*/
void SkipList::finishIteration() {
	iteration = 0;
}

int SkipList::can_dump() {
	if (iteration == 0) { 
        	iteration = 1; 
	        skipiterator = head; 
		flag = 1;
	} 

	if (skipiterator == NULL) { 
	        iteration = 0; 
	        flag = 1;
	        return 0; 
	} 
	
//	if (flag == 0) return 0;
	
	return 1;
}
/*...e*/
/*...sSkipList\58\\58\dump_next\40\\41\:0:*/
Elem SkipList::dump_next() {
	if (skipiterator != NULL) {
		Elem e = skipiterator->value.getPtr();
		
		while (e == NULL) {
			skipiterator = skipiterator->forward[0];
			e = skipiterator->value.getPtr();
		}

		skipiterator = skipiterator->forward[0];
/*...sbla:0:*/
#ifdef bla		
		for(int i=0; i<=skipiterator->myLevel && flag != 0; i++)
			if (skipiterator->forward[i] == NULL){
				printf("No more elements in skiplist\n");
		        	flag = 0;
			}
#endif		
/*...e*/
		return e;
	} else {
		printf("Return NULL because skipiterator is NULL\n");
		return NULL;
	}
}

/*...sbla:0:*/
#ifdef bla
void dump() {
    SkipNode* temp = head;
    int flag = 1;

    for ( ; temp!= NULL; temp = temp->forward[0]) {
        COUT << "temp->value is " << temp->value << ENDL;
        for(int i=0; i<=temp->myLevel && flag != 0; i++)
            if (temp->forward[i] == NULL){
                COUT << " rest of list is empty" << ENDL;
                flag = 0;
            }
            else
                COUT<<"  point to "<<temp->forward[i]->value<<"\n";
    }
}
#endif
/*...e*/
/*...e*/


BEGIN_IMPLEMENT_LB_UNKNOWN(lbSkipListElement)
        ADD_INTERFACE(lb_I_Element)
END_IMPLEMENT_LB_UNKNOWN()

//IMPLEMENT_LB_ELEMENT(lbSkipListElement)

/*...sIMPLEMENT_LB_ELEMENT\40\lbSkipListElement\41\:0:*/

lbSkipListElement::lbSkipListElement(const lb_I_Unknown* o, const lb_I_KeyBase* _key, lb_I_Element *_next) { 
    ref = STARTREF; 
    manager = NULL; 
    if (_next == NULL) next = _next; 
    if (_next != NULL) { 
        _next->queryInterface("lb_I_Element", (void**) &next, __FILE__, __LINE__); 
    } 
    if (o == NULL) _CL_VERBOSE << "Error! Can't clone a NULL pointer" LOG_ 
    data = o->clone(__FILE__, __LINE__); 
    char ptr[20] = ""; 
    sprintf(ptr, "%p", (void*) data); 
    if (strcmp(ptr, "019a30c0") == 0) { 
    	_CL_VERBOSE << "Mysterious object found" LOG_ 
    } 
    if (data->getRefCount() > 1) { 
        _CL_VERBOSE << "Refcount after cloning is more than 1 !!!" LOG_ 
    } 
    lb_I_Unknown* uk_key = NULL; 
    key = (lb_I_KeyBase*) _key->clone(__FILE__, __LINE__); 
    if (key == NULL) _CL_VERBOSE << "Key cloning in constructor failed. May be a memory problem" LOG_ 
} 

lbSkipListElement::~lbSkipListElement() { 
        if (key != NULL) { 
                if (key->deleteState() != 1) _CL_VERBOSE << "Key wouldn't deleted in container element!" LOG_ 
                RELEASE(key); 
        } 
        if (data != NULL) { 
                if (data->deleteState() != 1) { 
                        lb_I_ConfigObject* node; 
                        data->queryInterface("lb_I_ConfigObject", (void**) &node, __FILE__, __LINE__); 
                        if (node != NULL) { 
	                        _CL_VERBOSE << "Data (lb_I_Unknown at " << 
	                        ltoa((void*) data) << 
	                        ") (created at: " << data->getCreationLoc() << 
	                        ") (refcount=" << data->getRefCount() << 
	                        ") (lbSkipListElement='" << data->getClassName() << 
	                        "', tagname='" << node->getName() << "') wouldn't deleted in container element!" LOG_ 
        	                node->release(__FILE__, __LINE__); 
                        } else { 
	                        _CL_VERBOSE << "Data (lb_I_Unknown at " << 
	                        ltoa((void*) data) << 
	                        ") (created at: " << data->getCreationLoc() << 
	                        ") (refcount=" << data->getRefCount() << 
	                        ") (lbSkipListElement='" << data->getClassName() << 
	                        "', tagname='" << node->getName() << "') wouldn't deleted in container element!" LOG_ 
        	        } 
                        char ptr[20] = ""; 
                        sprintf(ptr, "%p", (void*) data); 
                        manager->printReferences(ptr); 
                } 
                RELEASE(data); 
        } 
        key = NULL; 
        data = NULL; 
} 

lb_I_Unknown* lbSkipListElement::getObject() const { 
    lb_I_Unknown* uk = NULL; 
    data->queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__); 
    return uk; 
} 

lb_I_KeyBase* LB_STDCALL lbSkipListElement::getKey() const { 
        lb_I_KeyBase* kbase = NULL; 
        return key; 
} 

void LB_STDCALL lbSkipListElement::setNext(lb_I_Element *e) { 
        e->queryInterface("lb_I_Element", (void**) &next, __FILE__, __LINE__); 
} 

lb_I_Element* LB_STDCALL lbSkipListElement::getNext() const { 
        return next; 
} 
int LB_STDCALL lbSkipListElement::equals(const lb_I_Element* a) const { 
	return 0; 
} 

int LB_STDCALL lbSkipListElement::equals(const lb_I_KeyBase* _key) const { 
	return (*key == _key); 
} 
int LB_STDCALL lbSkipListElement::lessthan(const lb_I_KeyBase* _key) const { 
	return (*key < _key); 
}
/*...e*/


lbErrCodes LB_STDCALL lbSkipListElement::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbSkipListElement::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...sclass InstanceRepository:0:*/
/*...sreferenceList:0:*/
typedef struct _referenceList {
        char* file;
        int line;
        int count;
        
        _referenceList* next;
} referenceList, *preferenceList;
/*...e*/
/*...sinstanceList:0:*/
typedef struct _instanceList {
        char* addr;
        char* classname;
        char* file;
        int line;
        referenceList* rList;
        
        _instanceList* next;
} instanceList, *pinstanceList;
/*...e*/
/*...sclassnameList:0:*/
typedef struct _classnameList {
        char* classname;
        instanceList* instances;
        
        _classnameList* next;
} classnameList, *pclassnameList;
/*...e*/

class InstanceRepository;
InstanceRepository* IR = NULL;

/*...sclass lbInstance:0:*/
/*...sclass lbInstance:0:*/
class lbInstance : 
public lb_I_Instance
{
private:
        char* addr;
        char* classname;
        char* file;
        int line;
        char* key;

	DECLARE_LB_UNKNOWN()
	DECLARE_LB_KEYBASE()
	
public:
	lbInstance();
	virtual ~lbInstance();
	
	virtual char* LB_STDCALL getAddress();
	virtual char* LB_STDCALL getInstanceClassname();
	virtual char* LB_STDCALL getFile();
	virtual int LB_STDCALL getLine();
	
	virtual void LB_STDCALL setAddress(char* a);
	virtual void LB_STDCALL setClassname(char* c);
	virtual void LB_STDCALL setFile(char* f);
	virtual void LB_STDCALL setLine(int l);
	
	/**
	 * Build a string with classname + _ + file + _ + line as a key for the reference.
	 * If the release function is used directly, it shows me an unregistered reference,
	 * so I will find all non UAP pointers.
	 */
	virtual void LB_STDCALL addReference(char* classname, char* file, int line);
	virtual void LB_STDCALL delReference(char* classname, char* file, int line);
	
	UAP(lb_I_Container, references, __FILE__, __LINE__)
	lbErrCodes err;
};
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbInstance)
	ADD_INTERFACE(lb_I_KeyBase)
	ADD_INTERFACE(lb_I_Instance)
END_IMPLEMENT_LB_UNKNOWN()

lbInstance::lbInstance() {
	addr = NULL;
	classname = NULL;
	file = NULL;
	line = -1;
	key = NULL;
	_CL_VERBOSE << "lbInstance::lbInstance() called." LOG_
}

lbInstance::~lbInstance() {
	
}

/*...svoid LB_STDCALL lbInstance\58\\58\addReference\40\char\42\ classname\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL lbInstance::addReference(char* classname, char* file, int line) {
	if (references == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, references)
	}
	char* buf = new char[strlen(classname)+strlen(file)+10];
	buf[0] = 0;
	
	sprintf(buf, "%s_%s_%d", classname, file, line);
	
	lbStringKey* key = new lbStringKey(buf);

	if (manager == NULL) _CL_VERBOSE << "Error: InstanceRepository has got a NULL pointer for the manager" LOG_
	key->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	UAP(lb_I_KeyBase, _key, __FILE__, __LINE__)
	QI(key, lb_I_KeyBase, _key, __FILE__, __LINE__)

	UAP(lb_I_Unknown, element, __FILE__, __LINE__)
	element = references->getElement(&_key);
	
	if (element != NULL) {
		UAP(lb_I_InstanceReference, instance, __FILE__, __LINE__)
		QI(element, lb_I_InstanceReference, instance, __FILE__, __LINE__)
		if (instance != NULL) {
			instance->setCount(instance->getCount() + 1);
		}
	}
	
	delete [] buf;
}
/*...e*/
/*...svoid LB_STDCALL lbInstance\58\\58\delReference\40\char\42\ classname\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL lbInstance::delReference(char* classname, char* file, int line) {
        if (references == NULL) {
                REQUEST(manager.getPtr(), lb_I_Container, references)
        }

	char* buf = new char[strlen(classname)+strlen(file)+10];
	buf[0] = 0;
	
	sprintf(buf, "%s_%s_%d", classname, file, line);
	
	lbStringKey* key = new lbStringKey(buf);

	if (manager == NULL) _CL_VERBOSE << "Error: InstanceRepository has got a NULL pointer for the manager" LOG_
	key->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	UAP(lb_I_KeyBase, _key, __FILE__, __LINE__)
	QI(key, lb_I_KeyBase, _key, __FILE__, __LINE__)

	UAP(lb_I_Unknown, element, __FILE__, __LINE__)
	element = references->getElement(&_key);

	if (element != NULL) {
		UAP(lb_I_InstanceReference, instance, __FILE__, __LINE__)
		QI(element, lb_I_InstanceReference, instance, __FILE__, __LINE__)
		if (instance != NULL) {
			if (instance->getCount() == 0) {
				_CL_VERBOSE << "Warning: Reference count goes under 0!" LOG_
			}
			instance->setCount(instance->getCount() - 1);
		}
	}
	
	delete [] buf;
}
/*...e*/
/*...sper instance functions:0:*/
char* LB_STDCALL lbInstance::getAddress() {
	return addr;
}

char* LB_STDCALL lbInstance::getInstanceClassname() {
	return classname;
}

char* LB_STDCALL lbInstance::getFile() {
	return file;
}
	
int LB_STDCALL lbInstance::getLine() {
	return line;
}

void LB_STDCALL lbInstance::setAddress(char* a) {
	if (addr != NULL) free(addr);
	addr = strdup(a);
}

void LB_STDCALL lbInstance::setClassname(char* c) {
	if (classname != NULL) free(classname);
	classname = strdup(c);
}

void LB_STDCALL lbInstance::setFile(char* f) {
	if (file != NULL) free(file);
	file = strdup(f);
}

void LB_STDCALL lbInstance::setLine(int l) {
	line = l;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbInstance\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbInstance::setData(lb_I_Unknown* uk) {

	if (strcmp("lbInstance", uk->getClassName()) == 0) {
		lb_I_Instance* i;
		
		if (uk->queryInterface("lb_I_Instance", (void**) &i, __FILE__, __LINE__) != ERR_NONE) {
			_CL_VERBOSE << "Error: Failed to get interface lb_I_Instance" LOG_
		}
		
		if (i != NULL) {
			file = strdup(i->getFile());
			line = i->getLine();
			addr = strdup(i->getAddress());
			classname = strdup(i->getInstanceClassname());
		}
		return ERR_NONE;
	}
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...sImplementation for key:0:*/
// Implementation for key

char* LB_STDCALL lbInstance::getKeyType() const {
    return "string";
}

int LB_STDCALL lbInstance::equals(const lb_I_KeyBase* _key) const {
    return (strcmp(addr, ((const lbInstance*) _key)->addr) == 0);
}

int LB_STDCALL lbInstance::greater(const lb_I_KeyBase* _key) const {
    return (strcmp(addr, ((const lbInstance*) _key)->addr) > 0);
}

int LB_STDCALL lbInstance::lessthan(const lb_I_KeyBase* _key) const {
    return (strcmp(addr, ((const lbInstance*) _key)->addr) < 0);
}

char* LB_STDCALL lbInstance::charrep() const {
    return addr;
}
/*...e*/
/*...e*/
/*...sclass lbInstanceReference:0:*/
class lbInstanceReference : 
public lb_I_InstanceReference
{
private:
        char* file;
        int line;
        int count;

	DECLARE_LB_UNKNOWN()
	
public:
        lbInstanceReference();
        virtual ~lbInstanceReference();	

	virtual char* LB_STDCALL getFile();
	virtual int LB_STDCALL getLine();
	virtual int LB_STDCALL getCount();

	virtual void LB_STDCALL setFile(char* f);
	virtual void LB_STDCALL setLine(int l);
	virtual void LB_STDCALL setCount(int c);

};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbInstanceReference)
	ADD_INTERFACE(lb_I_InstanceReference)
END_IMPLEMENT_LB_UNKNOWN()

lbInstanceReference::lbInstanceReference() {
}

lbInstanceReference::~lbInstanceReference() {
}

int LB_STDCALL lbInstanceReference::getLine() {
	return line;
}

int LB_STDCALL lbInstanceReference::getCount() {
	return count;
}

char* LB_STDCALL lbInstanceReference::getFile() {
	return file;
}

void LB_STDCALL lbInstanceReference::setLine(int l) {
	line = l;
}

void LB_STDCALL lbInstanceReference::setCount(int c) {
	count = c;
}

void LB_STDCALL lbInstanceReference::setFile(char* f) {

}
	
lbErrCodes LB_STDCALL lbInstanceReference::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbInstanceReference::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}
#ifdef bla
/*...skey:0:*/
char* LB_STDCALL lbInstanceReference::getKeyType() const {
    return "lbInstanceReference";
}

int LB_STDCALL lbInstanceReference::equals(const lb_I_KeyBase* _key) const {
    return strcmp(key, ((lbInstanceReference*) _key)->key) == 0;
}

int LB_STDCALL lbInstanceReference::greater(const lb_I_KeyBase* _key) const {
    return strcmp(key, ((lbInstanceReference*) _key)->key) > 0;
}

int LB_STDCALL lbInstanceReference::lessthan(const lb_I_KeyBase* _key) const {
    return strcmp(key, ((lbInstanceReference*) _key)->key) < 0;
}

char* lbInstanceReference::charrep() const {
    
    return key;
}
/*...e*/
#endif
/*...e*/

char* Upper(char* string) {
	for (int i = 0; i < strlen(string); i++) string[i] = toupper(string[i]);
	return string;
}

/*...sclass InstanceRepository:0:*/
class InstanceRepository {
private:
        InstanceRepository() {}
public:
	InstanceRepository(lb_I_Module* m);
        virtual ~InstanceRepository();
        
        void LB_STDCALL createInstance(char* addr, char* classname, char* file, int line);
        void LB_STDCALL addReference(char* addr, char* classname, char* file, int line);
        void LB_STDCALL delReference(char* addr, char* classname, char* file, int line);
        void LB_STDCALL destroyInstance(char* addr, char* classname, char* file, int line);
        
	char* LB_STDCALL getCreationLoc(char* addr);
	void LB_STDCALL printReferences(char* addr);	
	void LB_STDCALL dumpReference(instanceList* i);

	void LB_STDCALL loadContainer(lb_I_Module* m);
        
        instanceList* iList;
        classnameList* cList;
        
        UAP(lb_I_Container, lb_iList, __FILE__, __LINE__)
        UAP(lb_I_Container, lb_cList, __FILE__, __LINE__)

private:
	int loadedContainer;
	int instances;
	int maxinstances;
	int references;
	lb_I_Module* manager;
	int skip;
	int skipreference;
};
/*...e*/
/*...sInstanceRepository\58\\58\InstanceRepository\40\lb_I_Module\42\ m\41\:0:*/
InstanceRepository::InstanceRepository(lb_I_Module* m) {
	manager = m;
        iList = NULL;
        cList = NULL;
        loadedContainer = 0;
        instances = 0;
        maxinstances = 1000;
        references = 0;
        skip = 0;
        skipreference = 0;
        lb_iList = NULL;
}
/*...e*/
/*...sInstanceRepository\58\\58\\126\InstanceRepository\40\\41\:0:*/
InstanceRepository::~InstanceRepository() {
        while (iList != NULL) {
                instanceList* temp = iList;
                iList = iList->next;
                dumpReference(temp);
                delete temp;
        }
        
        while (cList != NULL) {
                classnameList* temp = cList;
                cList = cList->next;
                delete temp;
        }
}
/*...e*/

/*...sInstanceRepository\58\\58\createInstance\40\char\42\ addr\44\ char\42\ classname\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL InstanceRepository::createInstance(char* addr, char* classname, char* file, int line) {
	// First check, if there is no instance
	
	if (skip > 0) return;
	
	instanceList* temp = iList;
	instances++;
/*	
	if (instances > maxinstances) {
		DebugBreak();
		maxinstances += 1000;
	}
*/	
	if (strcmp("lbInstance", classname) == 0) return;
	if (strcmp("lbStringKey", classname) == 0) return;
	
	if (loadedContainer == 1) {
/*...sprepare instance entry:16:*/
		lbInstance* inst = new lbInstance();
		inst->setModuleManager(manager, __FILE__, __LINE__);
	
		inst->setAddress(addr);
		inst->setClassname(classname);
		inst->setFile(file);
		inst->setLine(line);
/*...e*/
	
/*...sprepare key:16:*/
		lbStringKey *key = new lbStringKey(addr);

		if (manager == NULL) _CL_VERBOSE << "Error: InstanceRepository has got a NULL pointer for the manager" LOG_
		key->setModuleManager(manager, __FILE__, __LINE__);
/*...e*/

		//Stack overflow, because key get's cloned.
		skip++;		
		lb_iList->insert((lb_I_Unknown**) &inst, (lb_I_KeyBase**) &key);
		skip--;
		
		
/*...scheck inserted element:16:*/
		{
		lbErrCodes err = ERR_NONE;
		lbStringKey *key = new lbStringKey(addr);
		
		if (manager == NULL) _CL_VERBOSE << "Error: InstanceRepository has got a NULL pointer for the manager" LOG_
		key->setModuleManager(manager, __FILE__, __LINE__);
		UAP(lb_I_KeyBase, _key, __FILE__, __LINE__)
		QI(key, lb_I_KeyBase, _key, __FILE__, __LINE__)
		
		UAP(lb_I_Unknown, element, __FILE__, __LINE__)
		element = lb_iList->getElement(&_key);
		
		if (element == NULL) {
			_CL_VERBOSE << "Fatal: InstanceRepository::createInstance(...) could not find inserted element!!!" LOG_
			//exit(1);
		}
/*...e*/
		
		}
		
		
	} else {
/*...sfirst element:8:*/
	if (iList == NULL) {
		iList = new instanceList;
		char address[20] = "";
		sprintf(address, "%p", iList);
		iList->next = NULL;
		iList->rList = NULL;
		iList->addr = strdup(addr);
		iList->classname = strdup(classname);
		iList->file = strdup(file);
		iList->line = line;
		return;
	}
/*...e*/
/*...smore than one elements:8:*/
	while (temp != NULL) {
		if ((strcmp(Upper(temp->addr), Upper(addr)) == 0) && (strcmp(temp->classname, classname) == 0)) {
			_CL_VERBOSE << "Error: Instance " << 
			classname << " in " << file <<
			" at " << line << " already registered" LOG_
		} else if (strcmp(Upper(temp->addr), Upper(addr)) == 0) {
			_CL_VERBOSE << "Error: Found a registered object with the same address. Was it not deleted correctly?" LOG_
		} else if (temp->next == NULL) {
			// Insert it here
			instanceList* neu = new instanceList;
			
			neu->next = NULL;
			neu->rList = NULL;
			neu->addr = strdup(addr);
			neu->classname = strdup(classname);
			neu->file = strdup(file);
			neu->line = line;

			temp->next = neu;
			return;
		}
		temp = temp->next;
	}
/*...e*/
	}
}
/*...e*/
/*...sInstanceRepository\58\\58\addReference\40\char\42\ addr\44\ char\42\ classname\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL InstanceRepository::addReference(char* addr, char* classname, char* file, int line) {
	if (skipreference > 0) return;
	skipreference++;
	instanceList* temp = iList;
	lbErrCodes err;
	int foundReference = 0;
	
	if (strcmp(classname, "lbModule") == 0) return;
	if (loadedContainer == 1) {
		lbStringKey *key = new lbStringKey(addr);
		
		if (manager == NULL) _CL_VERBOSE << "Error: InstanceRepository has got a NULL pointer for the manager" LOG_
		key->setModuleManager(manager, __FILE__, __LINE__);
		UAP(lb_I_KeyBase, _key, __FILE__, __LINE__)
		QI(key, lb_I_KeyBase, _key, __FILE__, __LINE__)
		
		UAP(lb_I_Unknown, element, __FILE__, __LINE__)
		element = lb_iList->getElement(&_key);
		
		if (element != NULL) {
			UAP(lb_I_Instance, instance, __FILE__, __LINE__)
			QI(element, lb_I_Instance, instance, __FILE__, __LINE__)
			if (instance != NULL) {
				instance->addReference(classname, file, line);
			}
		}
	} else
	while (temp != NULL) {
/*...ssearch instance address:16:*/
		if (strcmp(Upper(temp->addr), Upper(addr)) == 0) {
			// Found the entry for this instance
			if (strcmp(temp->classname, classname) == 0) {
				referenceList* rL = temp->rList;
					
				while(rL != NULL) {
					if ((strcmp(rL->file, file) == 0) && (rL->line == line)) {
						rL->count++;
						foundReference = 1;
						break;
					}
					rL = rL->next;
				}
					
				if (foundReference == 0) {
					rL = new referenceList;
					rL->next = temp->rList;
					temp->rList = rL;
					
					rL->file = strdup(file);
					rL->line = line;
					rL->count = 1;
				}
			} else {
				_CL_VERBOSE << "Error: InstanceRepository::addReference() classname differs." << 
				"Stored: " << temp->classname << " Given: " << classname << 
				"\nStored was created in " <<
				 temp->file << " at " << temp->line << " with pointer " << addr LOG_ 
				return;
			}
		}
/*...e*/
		temp = temp->next;
	}
	
	skipreference--;
	
}
/*...e*/
/*...sInstanceRepository\58\\58\delReference\40\char\42\ addr\44\ char\42\ classname\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL InstanceRepository::delReference(char* addr, char* classname, char* file, int line) {
	if (skipreference > 0) return;
	skipreference++;
	instanceList* temp = iList;
	instanceList* prev = NULL;
        lbErrCodes err;
        int foundReference = 0;

	if (strcmp(classname, "lbStringKey") == 0) return;
        if (loadedContainer == 1) {
                lbStringKey *key = new lbStringKey(addr);

                if (manager == NULL) _CL_VERBOSE << "Error: InstanceRepository has got a NULL pointer for the manager" LOG_
                key->setModuleManager(manager, __FILE__, __LINE__);
                UAP(lb_I_KeyBase, _key, __FILE__, __LINE__)
                QI(key, lb_I_KeyBase, _key, __FILE__, __LINE__)

                UAP(lb_I_Unknown, element, __FILE__, __LINE__)
                element = lb_iList->getElement(&_key);

                if (element != NULL) {
                        UAP(lb_I_Instance, instance, __FILE__, __LINE__)
                        QI(element, lb_I_Instance, instance, __FILE__, __LINE__)
                        if (instance != NULL) {
                                instance->delReference(classname, file, line);
                        }
                }
        } else
	while (temp != NULL) {
/*...ssearch instance address:16:*/
		if (strcmp(Upper(temp->addr), Upper(addr)) == 0) {
			// Found the entry for this instance
			if (strcmp(temp->classname, classname) == 0) {
				referenceList* rList = temp->rList;
				referenceList* rPrev = NULL;
				
				if (rList == NULL) printf("Error: Reference list is NULL\n");
/*...sSearch in the references:48:*/
				while (rList != NULL) {
					#ifdef VERBOSE
					printf("Stored reference is in %s at %d\n", rList->file, rList->line);
					#endif
					if ((strcmp(rList->file, file) == 0) && (rList->line == line)) {
						foundReference = 1;
						if (rList->count > 1) {
							rList->count--;
							return;
						} else {
							if (rList->count != 1) _CL_VERBOSE << "Error: Reference count is wrong" LOG_
							
							if (rPrev == NULL) {
								temp->rList = rList->next;
								free(rList->file);
								delete rList;
							} else {
								rPrev = rList->next;
								free(rList->file);
								delete rList;
							}
							
							if (prev == NULL) {
								prev = temp;
								temp = temp->next;
								free(prev->classname);
								free(prev->file);
								if (temp == NULL) {
									delete iList;
									iList = NULL;
								}
								else {
									delete prev;
									prev = NULL;
								}
								return;
							} else {
								prev->next = temp->next;
								free(temp->classname);
								free(temp->file);
								delete temp;
								return;
							}
						}
					}
				
					rPrev = rList;
					rList = rList->next;
				}
/*...e*/
				
				if (foundReference == 0) {
					_CL_VERBOSE << "Error: Reference was not registered (classname=" << classname <<
					", file=" << file << ", line=" << line << ")" LOG_ 
				}
			} else {
				_CL_VERBOSE << "Error: InstanceRepository::delReference() classname differs" LOG_
				return;
			}
		}
		prev = temp;
		temp = temp->next;
/*...e*/
	}
	skipreference--;
}
/*...e*/
/*...sInstanceRepository\58\\58\destroyInstance\40\char\42\ addr\44\ char\42\ classname\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL InstanceRepository::destroyInstance(char* addr, char* classname, char* file, int line) {
	if (skip > 0) return;
	skip++;
	instanceList* temp = iList;
	instanceList* prev = NULL;

	if (loadedContainer == 1) {
/*...sprepare key:16:*/
		lbStringKey *key = new lbStringKey(addr);

		if (manager == NULL) _CL_VERBOSE << "Error: InstanceRepository has got a NULL pointer for the manager" LOG_
		key->setModuleManager(manager, __FILE__, __LINE__);
/*...e*/

		//Stack overflow, because key get's cloned.
		skip++;		
		lb_iList->remove((lb_I_KeyBase**) &key);
		skip--;
	} else {	
/*...sLinked list:16:*/
	while (temp != NULL) {
		if ((strcmp(Upper(temp->addr), Upper(addr)) == 0) && (strcmp(temp->classname, classname) == 0)) {
			if (prev == NULL) {
				if (temp->rList != NULL) {
					if (temp->rList->count >= 1) {
						_CL_VERBOSE << "Error: Destroying an instance, that always has references" LOG_
						referenceList* rTemp = temp->rList;
						
						while (rTemp != NULL) {
							_CL_VERBOSE << "Reference for " << classname << " is at " << 
							rTemp->file << ": " << rTemp->line <<
							" with " << rTemp->count << " references." LOG_
							referenceList* rPrev = rTemp;
							rTemp = rTemp->next;
							
							free(rPrev->file);
							delete rPrev;
						}
					} else {
						referenceList* rTemp = temp->rList;
						
						while (rTemp != NULL) {
							_CL_VERBOSE << "Reference for " << classname << " is at " << 
							rTemp->file << ": " << rTemp->line <<
							" with " << rTemp->count << " references." LOG_
							referenceList* rPrev = rTemp;
							rTemp = rTemp->next;
							
							free(rPrev->file);
							delete rPrev;
						}
					}
				} else {
					prev = temp;
					temp = temp->next;
					
					free(prev->addr);
					free(prev->file);
					free(prev->classname);
					delete prev;
				}
			} else {
				if (temp->rList != NULL) {
					if (temp->rList->count >= 1) {
						_CL_VERBOSE << "Error: Destroying an instance, that always has references" LOG_
						referenceList* rTemp = temp->rList;
						
						while (rTemp != NULL) {
							_CL_VERBOSE << "Reference for " << classname << " is at " << rTemp->file << ": " << 
							rTemp->line << " with " << rTemp->count << " references." LOG_
							referenceList* rPrev = rTemp;
							rTemp = rTemp->next;
							
							free(rPrev->file);
							delete rPrev;
						}
					} else {
						referenceList* rTemp = temp->rList;
						
						while (rTemp != NULL) {
							_CL_VERBOSE << "Reference for " << classname << " is at " << rTemp->file << ": " << 
							rTemp->line << " with " << rTemp->count << " references." LOG_
							referenceList* rPrev = rTemp;
							rTemp = rTemp->next;
							
							free(rPrev->file);
							delete rPrev;
						}
					}
					
				}  else {
				       prev->next = temp->next;

				       free(temp->addr);
				       free(temp->file);
				       free(temp->classname);
				       delete temp;
				}
			}
		}
		
		prev = temp;
		temp = temp->next;
	}
/*...e*/
	}
	skip--;
}
/*...e*/

/*...sInstanceRepository\58\\58\getCreationLoc\40\char\42\ addr\41\:0:*/
char* LB_STDCALL InstanceRepository::getCreationLoc(char* addr) {
	instanceList* temp = iList;
/*...sfirst element:8:*/
	if (iList == NULL) {
		return "No IR elements available";
	}
/*...e*/
/*...smore than one elements:8:*/
	while (temp != NULL) {
		static char buf[1000] = "";
		sprintf(buf, "Location File: %s, Line: %d", temp->file, temp->line);
		if (strcmp(Upper(temp->addr), Upper(addr)) == 0) {
			return buf;
		} 
		temp = temp->next;
	}
/*...e*/
	return strdup("No location stored");	
}
/*...e*/
/*...sInstanceRepository\58\\58\printReferences\40\char\42\ addr\41\:0:*/
void LB_STDCALL InstanceRepository::printReferences(char* addr) {
	instanceList* temp = iList;
	_CL_VERBOSE << "InstanceRepository::printReferences(char* addr) called" LOG_
	while(temp != NULL) {
		if (strcmp(Upper(temp->addr), Upper(addr)) == 0) {
			referenceList* rTemp = temp->rList;
			
			while(rTemp != NULL) {
				printf("Reference for %s in %f at %d with %d stored count's\n", 
				temp->classname, rTemp->file, rTemp->line, rTemp->count);
				rTemp = rTemp->next;
			}
		}
		temp = temp->next;
	}
	_CL_VERBOSE << "InstanceRepository::printReferences(char* addr) leaving" LOG_
}
/*...e*/
/*...sInstanceRepository\58\\58\dumpReference\40\instanceList\42\ i\41\:0:*/
void LB_STDCALL InstanceRepository::dumpReference(instanceList* i) {
	referenceList* rTemp = i->rList;
	while(rTemp != NULL) {
		printf("Instance for %s has a reference in %s at %d\n", 
			i->classname, rTemp->file, rTemp->line);
		rTemp = rTemp->next;
	}
}
/*...e*/
/*...sInstanceRepository\58\\58\loadContainer\40\lb_I_Module\42\ m\41\:0:*/
void LB_STDCALL InstanceRepository::loadContainer(lb_I_Module* m) {
	if (loadedContainer == 1) return;
	loadedContainer = 1;

	SkipList* instances = new SkipList();

	lb_iList = instances;
	
	instanceList* temp = iList;
	_CL_VERBOSE << "Info: InstanceRepository::loadContainer(...) is not implemented completely" LOG_
	while (temp != NULL) {
		printf("Have an instance %s in %s at %d\n", temp->classname, temp->file, temp->line);
		temp = temp->next;
	}

}
/*...e*/
/*...e*/

T_pLB_GET_UNKNOWN_INSTANCE DLL_LB_GET_UNKNOWN_INSTANCE;
/*...sclass lbModuleContainer:0:*/
class lbModuleContainer :       public lb_I_Container
{

public:
    lbModuleContainer(const lb_I_Container* c);
    lb_I_Container* operator= (const lb_I_Container* c);

public:

    lbModuleContainer();
    virtual ~lbModuleContainer();

    DECLARE_LB_UNKNOWN()

// This may be a string container

    DECLARE_LB_I_CONTAINER_IMPL()

};
/*...e*/

// A hardcoded interface repository
/*...sclass lbFunctorEntity:0:*/
class lbFunctorEntity : public lb_I_FunctorEntity
{
public:

        lbFunctorEntity() {
        
        	// The missing setup of ref has been resulting in to a really
        	// memory leak. Since this module and all its needed code, is
        	// used at every place, where an instance must be created.
        	//
        	// ref should go into a simple integer class with ++ and -- operators
        	// to handle refcounting correctly, even the ref is not setup like this
        	// construct.
        
        
        	ref = STARTREF;
        	_functor = NULL;
        	_module = NULL;
        	_interface = NULL;
        }
        
        virtual ~lbFunctorEntity() {
        	if (_functor) free(_functor);
        	if (_module) free(_module);
        	if (_interface) free(_interface);
        }

public:

        virtual void LB_STDCALL setFunctor(char* functor) {
        	if (_functor) free(_functor);
        	_functor = (char*) malloc(strlen(functor)+1);
        	_functor[0] = 0;
        	strcpy(_functor, functor);
        }
        
        virtual void LB_STDCALL setModule(char* module) {
        	if (_module) free(_module);
        	_module = (char*) malloc(strlen(module)+1);
        	_module[0] = 0;
        	strcpy(_module, module);
        }
        
        virtual void LB_STDCALL setInterface(char* iface) {
        	if (_interface) free(_interface);
        	_interface = (char*) malloc(strlen(iface)+1);
        	_interface[0] = 0;
        	strcpy(_interface, iface);
        }

	
public:

	DECLARE_LB_UNKNOWN()


        virtual char* LB_STDCALL getFunctor() {
        	return _functor;
        }
        
        virtual char* LB_STDCALL getModule() {
        	return _module;
        }
        
        virtual char* LB_STDCALL getInterface() {
        	return _interface;
	}

        friend class lb_I_InterfaceRepository;

	char* _functor;
	char* _module;
	char* _interface;
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbFunctorEntity)
        ADD_INTERFACE(lb_I_FunctorEntity)
END_IMPLEMENT_LB_UNKNOWN()



lbErrCodes lbFunctorEntity::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbFunctorEntity::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...sclass lbHCInterfaceRepository:0:*/
class lbHCInterfaceRepository : public lb_I_InterfaceRepository
{
public:
        lbHCInterfaceRepository();
        virtual ~lbHCInterfaceRepository();

        DECLARE_LB_UNKNOWN()

	void LB_STDCALL setCurrentSearchInterface(const char* iface);
	lb_I_FunctorEntity* LB_STDCALL getFirstEntity();

	void initIntefaceList();

	int errorsOccured;
	
	// Created once and contains all interface nodes
	unsigned int interfaces; // current interface index
	unsigned int len;
	
	/**
	 * Indicates the current search mode (currently only over interfaces).
	 */
	int CurrentSearchMode;
	char* searchArgument;
	
	/**
	 * Indicates an invalid search status like 
	 * 	noPrevious interface;
	 *	noNext     interface;
	 *
	 * Note:	Moving to first or last interface resets any invalid status.
	 */
	int invalidSearchStatus;
private:
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbHCInterfaceRepository)
        ADD_INTERFACE(lb_I_InterfaceRepository)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfHCInterfaceRepository, lbHCInterfaceRepository)

lbHCInterfaceRepository::lbHCInterfaceRepository() {	
	manager = NULL;
	ref = STARTREF;
	searchArgument = NULL;
	_CL_VERBOSE << "lbHCInterfaceRepository::lbHCInterfaceRepository() called." LOG_
}

lbHCInterfaceRepository::~lbHCInterfaceRepository() {
	_CL_VERBOSE << "lbHCInterfaceRepository::~lbHCInterfaceRepository() called." LOG_
	free(searchArgument);
}

lbErrCodes lbHCInterfaceRepository::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbHCInterfaceRepository::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL lbHCInterfaceRepository::setCurrentSearchInterface(const char* iface) {
	if (searchArgument) free(searchArgument);
	searchArgument = (char*) malloc (strlen(iface)+1);
	searchArgument[0] = 0;
	strcpy(searchArgument, iface);

	interfaces = 0;
	CurrentSearchMode = 1;
}

/*...slb_I_FunctorEntity\42\ LB_STDCALL lbHCInterfaceRepository\58\\58\getFirstEntity\40\\41\:0:*/
lb_I_FunctorEntity* LB_STDCALL lbHCInterfaceRepository::getFirstEntity() {
	if (CurrentSearchMode == 0) {
		printf("SearchMode not set. Please call first lbHCInterfaceRepository::setCurrentSearchInterface(char* iface)\nOr any further other setCurrentSearch<Mode>(char* argument) function\n");
		return NULL;
	}
	
	if (CurrentSearchMode != 1) {
		printf("SearchMode currently not provided.\n");
		return NULL;
	}

	char* module = NULL;
	char* functor = NULL;

// Add code here to overload exsisting interface definitions by custom repository

#ifndef LINUX
	#ifdef __WATCOMC__
	#define PREFIX "_"
	#endif
	#ifdef _MSC_VER
	#define PREFIX ""
	#endif
#endif
#ifdef LINUX
#define PREFIX ""
#endif

	if (strcmp(searchArgument, "lb_I_Container") == 0) {
	 	functor = PREFIX "instanceOfSkipList";
		module = "lbClasses";
	}
	
	if (strcmp(searchArgument, "lb_I_Log") == 0) {
		functor = PREFIX "instanceOfLogger";
		module = "lbClasses";
	}
	
	if (strcmp(searchArgument, "lb_I_KeyBase") == 0) {
		functor = PREFIX "instanceOfIntegerKey";
		module = "lbClasses";
	}
	
	if (strcmp(searchArgument, "lb_I_Integer") == 0) {
		functor = PREFIX "instanceOfInteger";
		module = "lbClasses";
	}
	
	if (strcmp(searchArgument, "lb_I_String") == 0) {
		functor = PREFIX "instanceOfString";
		module = "lbClasses";
	}
	
	if (strcmp(searchArgument, "lb_I_Parameter") == 0) {
		functor = PREFIX "instanceOfParameter";
		module = "lbClasses";
	}
	
	if (strcmp(searchArgument, "lb_I_Database") == 0) {
		functor = PREFIX "instanceOfDatabase";
		module = "lbDB";
	}
	
	if (strcmp(searchArgument, "lb_I_PluginManager") == 0) {
		functor = PREFIX "instanceOfPluginManager";
		module = "lbPluginManager";
	}
	
	if (strcmp(searchArgument, "lb_I_Plugin") == 0) {
		functor = PREFIX "instanceOfPlugin";
		module = "lbPluginManager";
	}
	
	if (strcmp(searchArgument, "lb_I_InterfaceRepository") == 0) {
	 	functor = "instanceOfInterfaceRepository";
		module = "lbDOMConfig";
	}
	
	if (strcmp(searchArgument, "lb_I_MetaApplication") == 0) {
		functor = PREFIX "instanceOfMetaApplication";
		module = "lbMetaApplication";
	}
	
	if (strcmp(searchArgument, "lb_I_EventMapper") == 0) {
		functor = PREFIX "instanceOfEventMapper";
		module = "lbMetaApplication";
	}
	
	if (strcmp(searchArgument, "lb_I_EventManager") == 0) {
		functor = PREFIX "instanceOfEventManager";
		module = "lbMetaApplication";
	}
	
	if (strcmp(searchArgument, "lb_I_Dispatcher") == 0) {
		functor = PREFIX "instanceOfDispatcher";
		module = "lbMetaApplication";
	}
	
	if (strcmp(searchArgument, "lb_I_EvHandler") == 0) {
		functor = PREFIX "instanceOfEvHandler";
		module = "lbMetaApplication";
	}

	if (strcmp(searchArgument, "lb_I_Locale") == 0) {
		functor = PREFIX "instanceOfLocale";
		module = "lbClasses";
	}
	
	lbFunctorEntity* fe = new lbFunctorEntity;
	fe->setModuleManager(manager.getPtr(), __FILE__, __LINE__);

	lb_I_FunctorEntity* _fe = NULL;
	fe->queryInterface("lb_I_FunctorEntity", (void**) &_fe, __FILE__, __LINE__);

	_fe->setModule(module);
	_fe->setFunctor(functor);

	return _fe;
}
/*...e*/
#ifdef bla
/*...slbErrCodes LB_STDCALL lbHCInterfaceRepository\58\\58\parse\40\\41\:0:*/
lbErrCodes LB_STDCALL lbHCInterfaceRepository::parse() {
	lbErrCodes err = ERR_NONE;
	char *filename = getenv("LBHOSTCFGFILE");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	COUT << "Parse file '" << filename << "'..." << ENDL;
#endif
/*...e*/

	if (filename != NULL) {

/*...sSetup objects:12:*/
	    // Begin parsing...
	    DOMParser parser;
	    parser.setDoValidation(true);

	    parser.setErrorHandler(errReporter);
		
/*...e*/


/*...stry parsing \40\no explicid allocation\41\:12:*/
	    // Parse the file and catch any exceptions that propogate out
	    try	
		{
		    errorsOccured = 0;
	            parser.parse(filename);
	
	            doc = parser.getDocument();
		}

		catch (const XMLException& )
	        {
			COUT << "Parse error\n" << ENDL;
			errorsOccured = 1;
			return ERR_XML_NOFILE;
		}
/*...e*/

	    // Clean up our parser and handler
	    //delete handler;

	} else return ERR_NO_ENVIRONMENT;
	return err;
}
/*...e*/
#endif
/*...svoid lbHCInterfaceRepository\58\\58\initIntefaceList\40\\41\:0:*/
void lbHCInterfaceRepository::initIntefaceList() {
	char* name = NULL;
	char* savename = NULL;
        savename = strdup("#document/dtdHostCfgDoc/Modules/Module/Functions/Function/Functor/InterfaceName");
        name = strrchr(savename, '/');
        if (name == NULL) name = savename;
//        DOMlist = doc.getElementsByTagName(((name[0] == '/') ? &name[1] : name));
//        len = DOMlist.getLength();
        // Cleanup
        free(savename);
}
/*...e*/
/*...e*/

lb_I_Container* moduleList = NULL;
/*...sclass lbModule and implementation:0:*/
/*...sclass lbModule:0:*/
class lbModule : 
                public lb_I_Module
{
public:
	lbModule();
	virtual ~lbModule();
	
        DECLARE_LB_UNKNOWN()

        virtual lbErrCodes LB_STDCALL initialize();
        virtual lbErrCodes LB_STDCALL request(const char* request, lb_I_Unknown** result);
        virtual lbErrCodes LB_STDCALL uninitialize();
        
	virtual void LB_STDCALL printReferences(char* addr);        

	virtual char* LB_STDCALL getCreationLoc(char* addr);
        virtual void LB_STDCALL notify_create(lb_I_Unknown* that, char* implName, char* file = "", int line = 0);
        virtual void LB_STDCALL notify_add(lb_I_Unknown* that, char* implName, char* file, int line);
        virtual void LB_STDCALL notify_release(lb_I_Unknown* that, char* implName, char* file, int line);
        virtual void LB_STDCALL notify_destroy(lb_I_Unknown* that, char* implName, char* file, int line);
        virtual int  LB_STDCALL can_delete(lb_I_Unknown* that, char* implName, char* file = "", int line = 0);
        
        virtual lbErrCodes LB_STDCALL getObjectInstance(const char* name, lb_I_Container*& inst);

        virtual lbErrCodes LB_STDCALL getFunctors(char* interfacename, lb_I_ConfigObject* node, lb_I_Unknown*& uk);
        virtual lbErrCodes LB_STDCALL getInstance(char* functorname, lb_I_ConfigObject* node, lb_I_Unknown*& uk);
        virtual lbErrCodes LB_STDCALL getDefaultImpl(char* interfacename, lb_I_ConfigObject** node, char*& implTor, char*& module);
	virtual lbErrCodes LB_STDCALL load(char* name);
        virtual lbErrCodes LB_STDCALL makeInstance(char* functor, char* module, lb_I_Unknown** instance);
        
protected:

#ifndef USE_INTERFACE_REPOSITORY
        void LB_STDCALL getXMLConfigObject(lb_I_XMLConfig** inst);
#endif
#ifdef USE_INTERFACE_REPOSITORY
        void LB_STDCALL getXMLConfigObject(lb_I_InterfaceRepository** inst);
#endif

        lb_I_ConfigObject* LB_STDCALL findFunctorNode(lb_I_ConfigObject** _node, const char* request);
        char* LB_STDCALL findFunctorModule(lb_I_ConfigObject** _node);
        char* LB_STDCALL findFunctorName(lb_I_ConfigObject** ___node);

        
        int internalInstanceRequest;
        UAP(lb_I_Container, loadedModules, __FILE__, __LINE__)
        UAP(lb_I_XMLConfig, xml_Instance, __FILE__, __LINE__)
	UAP(lb_I_InterfaceRepository, newInterfaceRepository, __FILE__, __LINE__)

        int system_up;
        int initializing;
};
/*...e*/

BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lbModule)
        ADD_INTERFACE(lb_I_Module)
END_IMPLEMENT_LB_UNKNOWN()

/*...slb_I_XMLConfig\42\ LB_STDCALL lbModule\58\\58\getXMLConfigObject\40\\41\:0:*/
extern "C" {
typedef lbErrCodes LB_FUNCTORCALL T_LB_GETXML_CONFIG_INSTANCE (lb_I_XMLConfig** inst, lb_I_Module* m, char* file, int line);
T_LB_GETXML_CONFIG_INSTANCE* DLL_LB_GETXML_CONFIG_INSTANCE;
}

#ifdef USE_INTERFACE_REPOSITORY
void LB_STDCALL lbModule::getXMLConfigObject(lb_I_InterfaceRepository** inst) {
        lbErrCodes err = ERR_NONE;
        char *libname = getenv("LBXMLLIB");
        char *ftrname = getenv("LBXMLFUNCTOR");
        char *cfgname = getenv("LBHOSTCFGFILE");
        
#define USE_HARDCODED_REPOSITORY        
#ifdef USE_HARDCODED_REPOSITORY        
#ifndef LINUX
	#ifdef __WATCOMC__
	#define PREFIX "_"
	#endif
	#ifdef _MSC_VER
	#define PREFIX ""
	#endif
#endif
#ifdef LINUX
#define PREFIX ""
#endif
	HINSTANCE h = getModuleHandle();
	setModuleHandle(h);
        if (newInterfaceRepository == NULL) {
                UAP(lb_I_Unknown, result, __FILE__, __LINE__)
                makeInstance(PREFIX "instanceOfHCInterfaceRepository", "lbModule", &result);
		result->queryInterface("lb_I_InterfaceRepository", (void**) inst, __FILE__, __LINE__);
        }
      
#endif

#ifndef USE_HARDCODED_REPOSITORY        

/*
 * Overwrite functor name and module name to use new interface repository. Config is done later.
 */

#ifndef linux
        libname = "lbDOMConfig"; // The same now
        ftrname = "instanceOfInterfaceRepository";
#endif

	HINSTANCE h = getModuleHandle();
	setModuleHandle(h);

        if (newInterfaceRepository == NULL) {
                UAP(lb_I_Unknown, result, __FILE__, __LINE__)
		
		printf("Make an instance of %s out of %s\n", ftrname, libname);
                makeInstance(ftrname, libname, &result);
		printf("Have created an interface for lb_I_InterfaceRepository at %p\n", result.getPtr());
		result->queryInterface("lb_I_InterfaceRepository", (void**) inst, __FILE__, __LINE__);
		result++;
        }
#endif                                
}                             
#endif

#ifndef USE_INTERFACE_REPOSITORY 

void LB_STDCALL lbModule::getXMLConfigObject(lb_I_XMLConfig** inst) {
	lbErrCodes err = ERR_NONE;
        char *libname = getenv("LBXMLLIB");
        char *ftrname = getenv("LBXMLFUNCTOR");
        char *cfgname = getenv("LBHOSTCFGFILE");

/*...sold style itreface repository:0:*/
	/**
	 * The UAP seems to try release it self. Because of the macro, it couldn't
	 * register a reference. The instance is not created yet!
	 *
	 * The reference will be created at the line with the QI macro, or a queryInterface()
	 *
	 *
	 */


	/**
	 * Because of not directly using this instance, I do not query an interface for it.
	 * Therefore it will generate the warning, that UAP is not set up correctly.
	 *
	 * The functor cannot use any interface, because it creates instances from real
	 * implementations. So I have to use a macro for using functors. Then I am able to set
	 * the file and line for this instance creation (also a reference !!!!)
	 */



        UAP(lb_I_XMLConfig, xml_I, __FILE__, __LINE__)

        if (libname == NULL) return;
        if (ftrname == NULL) return;
        if (cfgname == NULL) return;

	HINSTANCE h = getModuleHandle();
printf("Get module handle\n");
        if (lbLoadModule(libname, h) != ERR_NONE) {
                exit(1);
        }
printf("Set module handle\n");        
        setModuleHandle(h);
printf("Get function pointer\n");
        if ((err = lbGetFunctionPtr(ftrname, getModuleHandle(), (void**) &DLL_LB_GETXML_CONFIG_INSTANCE)) != ERR_NONE) {
            _CL_VERBOSE <<  "Kann Funktion '" << ftrname << "' nicht finden." LOG_  
            exit(1);
        }
	
	
	// !!!!
_CL_VERBOSE << "Lade XML Config DLL" LOG_	
        err = DLL_LB_GETXML_CONFIG_INSTANCE(&xml_I, this, __FILE__, __LINE__);
_CL_VERBOSE << "XML Config DLL geladen" LOG_
        // Debug helper
printf("Set up location\n");        
        xml_I.setLine(__LINE__);
        xml_I.setFile(__FILE__);


        if (xml_I == NULL) {
            _CL_VERBOSE << "Konnte XML Konfigurationsinstanz nicht bekommen.\n" LOG_
            exit(1);
        }
/*...sdoc:8:*/
        /**
         * Because of UNKNOWN_AUTO_PTR, here I must ensure, having one reference more than
         * it is returned by the functor. Increase it by a dummy call.
         *
         * The functor *MUST* call queryInterface it self. Using the macro, it should.
         */
        
        /**
         * The prior functor caused a object lock due to missing manager.
         * Because the functor is not designed to pass this manager, it's
         * internal use of queryInterface() locks the object.
         *
         * The object can be used, but there is no possibility to query
         * other interfaces (eg. do refcounting).
         *
         * Later, if the object will be deleted, it generates an error
         * due to it's locking.
         *
         * The setModuleManager() function resets this locking state and
         * corrects the values in module manager.
         */ 
/*...e*/

	UAP(lb_I_XMLConfig, _inst, __FILE__, __LINE__)
	
//printf("Query interface of instance at %p\n", xml_I);
//        QI(xml_I, lb_I_XMLConfig, _inst, __FILE__, __LINE__) 
//QI(source, interface, target, file, line)
	_inst.setFile(__FILE__);
	_inst.setLine(__LINE__);

	//if ((void**) &_inst == NULL) DebugBreak();
	_CL_VERBOSE << "Query interface for " << "lb_I_XMLConfig" LOG_
        err = xml_I->queryInterface("lb_I_XMLConfig", (void**) &_inst, __FILE__, __LINE__);


printf("Queried\n");        
        _inst++;
printf("Increase count\n");
        *inst = *&_inst;
printf("Increased\n");        
        /**
         * Set a flag, that say's system is up.
         */
        
        system_up = 1;
        
        if (*inst == NULL) { 
        	_CL_VERBOSE << "Error: queryInterface() does not return a pointer!" LOG_
        }
/*...e*/
}

#endif
/*...e*/


/*...sdebug helper:0:*/
/*...schar\42\ LB_STDCALL lbModule\58\\58\getCreationLoc\40\char\42\ addr\41\:0:*/
char* LB_STDCALL lbModule::getCreationLoc(char* addr) {
#ifdef IR_USAGE
	if (IR != NULL) {
		return IR->getCreationLoc(addr);
	} else {
		_CL_VERBOSE << "Error: Call sequence error!" LOG_
		return "Interface repository not initialized";
	}
#endif
#ifndef IR_USAGE
	return "IR is deactivated!";
#endif
}
/*...e*/
/*...svoid LB_STDCALL lbModule\58\\58\printReferences\40\char\42\ addr\41\:0:*/
void LB_STDCALL lbModule::printReferences(char* addr) {
	if (IR != NULL) {
	#ifdef VERBOSE
		IR->printReferences(addr);
	#endif
	}
}
/*...e*/
/*...svoid LB_STDCALL lbModule\58\\58\notify_create\40\lb_I_Unknown\42\ that\44\ char\42\ implName\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL lbModule::notify_create(lb_I_Unknown* that, char* implName, char* file, int line) {
#ifdef IR_USAGE
        char buf[1000] = "";
        char addr[20] = "";
        sprintf(addr, "%p", (void*) that);
        
        if (IR == NULL) {
        	IR = new InstanceRepository(this);
        }
        /**
         * Do not register lbInstance's itself, because they are used registering
         * other instances.
         */
        if (strcmp("lbInstance", implName) != 0) {
        	IR->createInstance(addr, implName, file, line);
        }
#ifdef VERBOSE
        _CL_VERBOSE << "lbModule::notify_create() called" LOG_
#endif
#endif
}
/*...e*/
/*...svoid LB_STDCALL lbModule\58\\58\notify_add\40\lb_I_Unknown\42\ that\44\ char\42\ implName\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL lbModule::notify_add(lb_I_Unknown* that, char* implName, char* file, int line) {
#ifdef IR_USAGE
        char addr[20] = "";
        sprintf(addr, "%p", (void*) that);

	if (IR == NULL) {
		_CL_VERBOSE << "Error: Initial lbModule::notify_create() was not done for " << implName << " in " << file << " at " << line << "!" LOG_
		return;
	}
	IR->addReference(addr, implName, file, line);
#endif
}
/*...e*/
/*...svoid LB_STDCALL lbModule\58\\58\notify_release\40\lb_I_Unknown\42\ that\44\ char\42\ implName\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL lbModule::notify_release(lb_I_Unknown* that, char* implName, char* file, int line) {
	/**
	 * A buffer with to few bytes may result in crashes. Because I do not make strlen checks,
	 * I must set the buffer to 
	 */
#ifdef IR_USAGE
        char addr[20] = "";

        sprintf(addr, "%p", (void*) that);


	if (that->getRefCount() == 0) {
		IR->delReference(addr, implName, file, line);
	} else {
	 	IR->delReference(addr, implName, file, line);       
	}
#endif
}
/*...e*/
/*...svoid LB_STDCALL lbModule\58\\58\notify_destroy\40\lb_I_Unknown\42\ that\44\ char\42\ implName\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL lbModule::notify_destroy(lb_I_Unknown* that, char* implName, char* file, int line) {
	/**
	 * A buffer with to few bytes may result in crashes. Because I do not make strlen checks,
	 * I must set the buffer to 
	 */
#ifdef IR_USAGE
        char addr[20] = "";

        sprintf(addr, "%p", (void*) that);


	if (that->getRefCount() == 0) {
		IR->destroyInstance(addr, implName, file, line);
	} else {
	 	IR->destroyInstance(addr, implName, file, line);       
	}
#endif
}
/*...e*/

/*...sint  LB_STDCALL lbModule\58\\58\can_delete\40\lb_I_Unknown\42\ that\44\ char\42\ implName\44\ char\42\ file\44\ int line\41\:0:*/
int  LB_STDCALL lbModule::can_delete(lb_I_Unknown* that, char* implName, char* file, int line) {
#ifdef IR_USAGE

#endif
        return 1;
}
/*...e*/
/*...e*/

lbModule::lbModule() {
                ref = STARTREF;
                loadedModules = NULL;
                internalInstanceRequest = 0;
                xml_Instance = NULL;
                system_up = 0;
                initializing = 0;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
                _CL_VERBOSE << "lbModule init manager" LOG_
#endif
/*...e*/
		setModuleManager(this, __FILE__, __LINE__);
		ref = STARTREF;
}
        
lbModule::~lbModule() {
                if (ref != STARTREF) COUT << "Error: Reference count mismatch" << ENDL;

                if (moduleList != NULL) moduleList->release(__FILE__, __LINE__);
/*...sVERBOSE:0:*/
#ifdef VERBOSE
                _CL_VERBOSE << "lbModule::~lbModule() called" LOG_
#endif
/*...e*/
}


/*...slbErrCodes lbModule\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbModule::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbModule::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbModule\58\\58\initialize\40\\41\:0:*/
lbErrCodes LB_STDCALL lbModule::initialize() {

	if (initializing == 1) {
		_CL_VERBOSE << "Warning: Initialize while initializing (loop)" LOG_
	}

	initializing = 1;

        if (moduleList != NULL) {
                _CL_VERBOSE << "Warning: lbModule::initialize() called more than once!" LOG_
                return ERR_NONE;
        }

#ifndef USE_INTERFACE_REPOSITORY        
        if (xml_Instance == NULL) {
                getXMLConfigObject(&xml_Instance);
                if (xml_Instance == NULL) {
                	_CL_VERBOSE << "Error: Functor has not returned a pointer!" LOG_
                	exit(1);
                }
	}
#endif
#ifdef USE_INTERFACE_REPOSITORY
        if (newInterfaceRepository == NULL) {
                getXMLConfigObject(&newInterfaceRepository);
                if (newInterfaceRepository == NULL) {
                        _CL_VERBOSE << "Error: Functor has not returned a pointer!" LOG_
                        exit(1);
                }
        }
#endif
        lbModuleContainer* MList = new lbModuleContainer();
               
        MList->setModuleManager(this, __FILE__, __LINE__);
        
        MList->queryInterface("lb_I_Container", (void**) &moduleList, __FILE__, __LINE__);

	if (moduleList == NULL) {
		_CL_VERBOSE << "Error: moduleList must now be initialized!" LOG_
	}
#ifdef IR_USAGE
	IR->loadContainer(this);
#endif

	initializing = 0;

        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL uninitialize\40\\41\:0:*/
lbErrCodes LB_STDCALL lbModule::uninitialize() {
        if (xml_Instance != NULL) {
        #ifndef USE_UAP
                RELEASE(xml_Instance);
                xml_Instance = NULL;
        #endif
        }
        if (moduleList != NULL) {
        #ifndef USE_UAP
                RELEASE(moduleList);
                moduleList = NULL;
        #endif
        }
        return ERR_NONE;
}
/*...e*/
// Helpers to abstract XML structure
/*...slbModule\58\\58\findFunctorNode\40\\46\\46\\46\\41\:0:*/
/**
 * Creates a view of needed data in a lb_I_ConfigObject.
 * The node then contains only one subtree for a functor.
 * 
 * Input:       A list of functor nodes in a view of a lb_I_ConfigObject
 *              
 *              The request itself
 *
 * Output:      Only one node from the list in a new view
 */
lb_I_ConfigObject* LB_STDCALL lbModule::findFunctorNode(lb_I_ConfigObject** _node, const char* request) {
        UAP(lb_I_ConfigObject, temp_node, __FILE__, __LINE__)
        lb_I_ConfigObject* node = *_node;
        
        temp_node.setDelete(0);


        lbErrCodes err = ERR_NONE;

        /**
         * This gets a reference for me. Autodeleted, if scope is leaved.
         */
        if ((err = node->getFirstChildren(&temp_node)) == ERR_NONE) {
                /**
                 * This is the functor node !! It has no attributes. All parents also contains
                 * the 'FunctionName' node, where the search criteria is stored. So the following
                 * must be done here to check if this node is the one be searched:
                 *
                 * Go up one node (in the tree), get all 'FunctionName' nodes by calling
                 * temp_node->getParentNode(). As the given node itself is a view of the DOM document,
                 * a question must be issued here:
                 *
                 * Has my implementation for this view any parents?
                 */
                 
                if (temp_node == NULL) {
                        _CL_VERBOSE << "temp_node is NULL!" LOG_
                } 
                if ((strcmp(temp_node->getName(), "Functor")) == 0) {
                        /**
                         * If I get a return value. It is a new reference.
                         * If I get a value by reference. It is a new reference.
                         *
                         * If I return a pointer from any interface reference,
                         * I *MUST* add a reference.
                         */
                        temp_node++;
                        return *&temp_node;
                }
                
        } else _CL_VERBOSE << "Get first child failed" LOG_

        while ((err = node->getNextChildren(&temp_node)) == ERR_NONE) {
                if ((strcmp(temp_node->getName(), "Functor")) == 0) {
                        temp_node++;
                        return *&temp_node;
                }
        }
        
        if (err == ERR_CONFIG_NO_MORE_CHILDS) {
                _CL_VERBOSE << "No more childs found" LOG_
        }

        #ifdef USE_UAP
        if (temp_node != NULL) RELEASE(temp_node);
        #endif
        
        _CL_VERBOSE << "Returning a NULL value" LOG_
        return NULL;
}
/*...e*/
/*...slbModule\58\\58\findFunctorModule\40\\46\\46\\46\\41\:0:*/
char* LB_STDCALL lbModule::findFunctorModule(lb_I_ConfigObject** _node) {
        lbErrCodes err = ERR_NONE;
        lb_I_ConfigObject* node = *_node;

        char buf[100] = "";
        
        if (node == NULL) {
                _CL_VERBOSE << "NULL pointer detected!" LOG_
                return "NULL";
        }
        
        if (strcmp (node->getName(), "Module") == 0) {
                { 
                UAP(lb_I_ConfigObject, temp_node, __FILE__, __LINE__)
                temp_node.setLine(__LINE__);
                temp_node.setFile(__FILE__);
                temp_node.setDelete(0);
                        if ((err = node->getFirstChildren(&temp_node)) == ERR_NONE) {
/*...swork on temp_node:32:*/
                        if ((strcmp(temp_node->getName(), "ModuleName")) == 0) {
                                char* value = NULL;
                                err = temp_node->getAttributeValue("Name", value);
                                
                                if (err != ERR_NONE) {
                                        _CL_VERBOSE << "Error while getting attribute value: " << value LOG_
                                        return "NULL";
                                } else {
                                        return value;
                                }
                        }               
/*...e*/
                        }
                }

                do {
                UAP(lb_I_ConfigObject, temp_node, __FILE__, __LINE__)
                temp_node.setLine(__LINE__);
                temp_node.setFile(__FILE__);
                temp_node.setDelete(0);
                        err = node->getNextChildren(&temp_node);
/*...swork on temp_node:24:*/
                        if ((strcmp(temp_node->getName(), "ModuleName")) == 0) {
                                char* value = NULL;

                                err = temp_node->getAttributeValue("Name", value);
                                
                                if (err != ERR_NONE) {
                                        _CL_VERBOSE << "Error while getting attribute value" LOG_
                                        return "NULL";
                                } else {
                                        return value;
                                }
                        }
/*...e*/
                } while (err == ERR_NONE);
        }
        else {
                UAP(lb_I_ConfigObject, temp_node, __FILE__, __LINE__)
                temp_node.setLine(__LINE__);
                temp_node.setFile(__FILE__);
                
                err = node->getParent(&temp_node);

                if (err == ERR_NONE) {
                        char* result = findFunctorModule(&temp_node);
                        
                        return result;
                }
                
        }

        return "NULL";
}
/*...e*/
/*...slbModule\58\\58\findFunctorName\40\\46\\46\\46\\41\:0:*/
char* LB_STDCALL lbModule::findFunctorName(lb_I_ConfigObject** ___node) {
        /**
         * Go up one level and get the children 'FunctionName'
         */
         
        UAP(lb_I_ConfigObject, _node, __FILE__, __LINE__)
        _node.setLine(__LINE__);
        _node.setFile(__FILE__);
        _node.setDelete(0);
        
        UAP(lb_I_ConfigObject, __node, __FILE__, __LINE__)
	__node.setLine(__LINE__);
	__node.setFile(__FILE__);
        __node.setDelete(0);
        
        lbErrCodes err = ERR_NONE;
        lb_I_ConfigObject* node = *___node;
        char buf[100] = "";
        
        /**
         * Warning!
         * 
         * This is hard coded moving in a tree of a xml document.
         */
        
        if ((err = node->getParent(&_node)) != ERR_NONE) {
                _CL_VERBOSE << "Some errors have ocured while getting a parent node!" LOG_
        } 
        
        if ((err = _node->getParent(&__node)) != ERR_NONE) {
                _CL_VERBOSE << "Some errors have ocured while getting a parent node!" LOG_
        }
        
        if (_node != NULL) {
                int first = 1;

                
                while (err == ERR_NONE) {
                        UAP(lb_I_ConfigObject, child, __FILE__, __LINE__)
                        child.setFile(__FILE__);
                        child.setLine(__LINE__);
                        child.setDelete(0);
                        
                        if (first == 1) {
                                err = __node->getFirstChildren(&child);
                                
                                if (err != ERR_NONE) {
                                        _CL_VERBOSE << "Error. Children expected" LOG_
                                        return NULL;
                                }
                                first = 0;
                        } else err = __node->getNextChildren(&child);
                        
                        /**
                         * Check that node...
                         */
                         
                        if (err != ERR_NONE) break; 
                 
                        if (strcmp(child->getName(), "FunctionName") == 0) {
                                /**
                                 * Have the node. Here I must get an attribute...
                                 */
                                 
                                char* value = NULL; 
                                err = child->getAttributeValue("Name", value); 
                                
                                if (err != ERR_NONE) {
                                        _CL_VERBOSE << "Error while getting attribute value" LOG_
                                        return NULL;
                                } else {
                                #ifdef VERBOSE
                                        COUT << "Found function name '" << value << "'" << ENDL;
                                #endif
                                        return value;
                                }
                        }
                }
        } else {
                _CL_VERBOSE << "A parent node was not found!?" LOG_
        }
        
        char *result = new char[100];
        result[0] = 0;
        return result;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\getDefaultImpl\40\char\42\ interfacename\44\ lb_I_ConfigObject\42\\42\ node\44\ char\42\\38\ implTor\44\ char\42\\38\ module\41\:0:*/
lbErrCodes LB_STDCALL lbModule::getDefaultImpl(char* interfacename, lb_I_ConfigObject** node, char*& implTor, char*& module) {
        lbErrCodes err = ERR_NONE;
        int count = 0;
        UAP(lb_I_ConfigObject, _node, __FILE__, __LINE__)
        _node = *node;
        _node++; // UAP must check the pointer here too

        implTor = new char[100];
        module = new char[100];

{
        UAP(lb_I_ConfigObject, temp_node, __FILE__, __LINE__)
        
        /**
         * Use _node instead of the interface pointer. Later UAP will be able to check
         * if the interface pointer is valid. (Inside the -> operator)
         */
        
/*...sget first children:8:*/
        if ((err = _node->getFirstChildren(&temp_node)) == ERR_NONE) {
                if (temp_node == NULL) {
                        _CL_VERBOSE << "temp_node is NULL!" LOG_
                } 

                if ((strcmp(temp_node->getName(), "StandardFunctor")) == 0) {
                        lb_I_Unknown* uk = NULL;
                        char* attr = NULL;
                        
                        temp_node->getAttributeValue("Interface", attr);

                        if (strcmp(interfacename, attr) == 0) {
                                temp_node->getAttributeValue("Module", module);
                                temp_node->getAttributeValue("Functor", implTor);
                                temp_node->deleteValue(attr);
                                return ERR_NONE;
                        }
                        
                        temp_node->deleteValue(attr);
                        
                }
                
        } else _CL_VERBOSE << "Get first child failed" LOG_
/*...e*/
}

/*...sget next children:0:*/
        err = ERR_NONE;
        while (err == ERR_NONE) {
                UAP(lb_I_ConfigObject, temp_node, __FILE__, __LINE__)
                
                err = _node->getNextChildren(&temp_node);
                
                if (temp_node == NULL) {
                        _CL_VERBOSE << "temp_node is NULL!" LOG_
                        continue;
                } 
                
                if ((strcmp(temp_node->getName(), "StandardFunctor")) == 0) {
                        lb_I_Unknown* uk = NULL;
                        char* attr = NULL;
                        
                        temp_node->getAttributeValue("Interface", attr);
                        
                        if (strcmp(interfacename, attr) == 0) {
                                
                                temp_node->getAttributeValue("Module", module);
                                temp_node->getAttributeValue("Functor", implTor);
                                temp_node->deleteValue(attr);
                                
                                return ERR_NONE;
                        }
                        temp_node->deleteValue(attr);
                }
        }

/*...e*/

        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\getFunctors\40\char\42\ interfacename\44\ lb_I_ConfigObject\42\ node\44\ lb_I_Unknown\42\\38\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbModule::getFunctors(char* interfacename, lb_I_ConfigObject* node, lb_I_Unknown*& uk) {
/*...sbla:0:*/
#ifdef bla
        lbModuleContainer* functors = new lbModuleContainer();

        UAP(lb_I_ConfigObject, temp_node)

        lbErrCodes err = ERR_NONE;
        int count = 0;

        if ((err = node->getFirstChildren(&temp_node)) == ERR_NONE) {
                lb_I_Attribute* attribute;
                
                if (temp_node == NULL) {
                        _CL_VERBOSE << "temp_node is NULL!" LOG_
                } 
                
                if ((strcmp(temp_node->getName(), "InterfaceName")) == 0) {
                        //return temp_node;
                        lb_I_Unknown* uk = NULL;
                        
                        if (temp_node->queryInterface("lb_I_Unknown", (void**) &uk) != ERR_NONE) {
                                _CL_VERBOSE << "Error: Could not get unknown interface!" LOG_
                                exit(1);
                        }
                        
                        if (uk == NULL) {
                                _CL_VERBOSE << "Error: Don't expect a NULL pointer here!" LOG_
                                exit(1);
                        }
                        
                        char* functor = NULL;
                        char* module = NULL;
                        
                        if ((err == getDefaultImpl("lb_I_Integer", node, functor, module)) != ERR_NONE) {
                                _CL_VERBOSE << "Oops!" LOG_
                        }
                        
                        
                        
                        //lbKey* key = new lbKey(++count);
                        
                        //functors->insert(uk, key);
                }
                
        } else _CL_VERBOSE << "Get first child failed" LOG_

        while ((err = node->getNextChildren(temp_node)) == ERR_NONE) {
                if ((strcmp(temp_node->getName(), "InterfaceName")) == 0) {
                        //return temp_node;

                        lb_I_Unknown* uk = NULL;
                        
                        if (temp_node->queryInterface("lb_I_Unknown", (void**) &uk) != ERR_NONE) {
                                _CL_VERBOSE << "Error: Could not get unknown interface!" LOG_
                                exit(1);
                        }
                        
                        if (uk == NULL) {
                                _CL_VERBOSE << "Error: Don't expect a NULL pointer here!" LOG_
                                exit(1);
                        }
                        
                        //lbKey* key = new lbKey(++count);
                        
                        //functors->insert(uk, key);
                }
        }
        
        if (err == ERR_CONFIG_NO_MORE_CHILDS) {
                _CL_VERBOSE << "No more childs found" LOG_
        }

        if (temp_node != NULL) RELEASE(temp_node);
#endif
/*...e*/
        _CL_VERBOSE << "lbModule::getFunctors(...) not implemented" LOG_
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\makeInstance\40\char\42\ functor\44\ char\42\ module\44\ lb_I_Unknown\42\\42\ instance\41\:0:*/
lbErrCodes LB_STDCALL lbModule::makeInstance(char* functor, char* module, lb_I_Unknown** instance) {
char msg[1000] = "";
lbErrCodes err = ERR_NONE;
                        /**
                         * ModuleHandle is the result for this loaded module.
                         */
         		HINSTANCE h = getModuleHandle();
         	
			char* _module = (char*) malloc(strlen(module)+10);
			_module[0] = 0;
			strcpy(_module, module);
	
			#ifdef LINUX
			if (strchr(_module, '.') == NULL) strcat(_module, ".so");
			#endif
		
                        if ((err = lbLoadModule(_module, h)) != ERR_NONE) {
                                // report error if still loaded
                                _CL_VERBOSE << "Error: Could not load the module '" << module << "'" LOG_
                                
                                free(_module);
                                
                                return err; 
                        }

                        setModuleHandle(h);
                        
                        if (getModuleHandle() == 0) _CL_VERBOSE << "Error: Module could not be loaded '" << module << "'" LOG_

                        if ((err = lbGetFunctionPtr(functor, getModuleHandle(), (void**) &DLL_LB_GET_UNKNOWN_INSTANCE)) != ERR_NONE) {
                                free(_module);
                                
                                return err;
                        } else {
                                err = DLL_LB_GET_UNKNOWN_INSTANCE(instance, this, __FILE__, __LINE__);

                                if (err != ERR_NONE) 
                                {
                                	_CL_VERBOSE << "Could not get an instance of type " << instance << " !" LOG_
                                	
                                	free(_module);
                                	
                                	return err;
                                }
                                if ((*instance) == NULL) _CL_VERBOSE << "Something goes wrong while calling functor" LOG_
                        }

	free (_module);
        return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lbModule::getInstance(char* functorname, lb_I_ConfigObject* node, lb_I_Unknown*& uk) {
        return ERR_NONE;
}
/*...e*/

/*...sclass lbNamedValue:0:*/
class lbNamedValue :    public lb_I_Unknown {
public:
        lbNamedValue() {
                name = strdup("");
        }
        
        virtual ~lbNamedValue() {
                free(name);
        }

        DECLARE_LB_UNKNOWN()

        lbErrCodes getName(char* & _name);
        lbErrCodes setName(const char* const _name);
        
        /**
         * This is a one value container. Objects in a container are copies of inserted
         * ones. This prevents manipulation of an object outside of the container.
         *
         * A modification must explicidly set into the container via the set function.
         */
        lbErrCodes setValue(lb_I_Unknown* _value);
        lbErrCodes getValue(lb_I_Unknown* & _value);
        
        char*         name;
        lb_I_Unknown* uk_value;
};
/*...e*/
/*...sclass lbElement:0:*/
class lbElement : public lb_I_Element {
private:

public:
    lbElement() { ref = STARTREF; next = NULL; data = NULL; key = NULL; }
    virtual ~lbElement();
        
    lbElement(const lb_I_Element &e) { ref = STARTREF; next = e.getNext(); }

    DECLARE_LB_UNKNOWN()

    DECLARE_LB_ELEMENT(lbElement)

    int operator == (const lb_I_Element &a) const;

    int operator == (const lb_I_KeyBase &key) const;

};
/*...e*/

/*...simplementation of lbModuleContainer:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbModuleContainer)
        ADD_INTERFACE(lb_I_Container)
END_IMPLEMENT_LB_UNKNOWN()

lbModuleContainer::lbModuleContainer() {
    iteration = 0;
    ref = STARTREF;
    iterator = NULL;
    count = 0;
    container_data = NULL;
}

lbModuleContainer::~lbModuleContainer() {
}


IMPLEMENT_LB_I_CONTAINER_IMPL(lbModuleContainer)

lbErrCodes lbModuleContainer::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbModuleContainer::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...simplementation of lbElement:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbElement)
        ADD_INTERFACE(lb_I_Element)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_LB_ELEMENT(lbElement)

lbErrCodes lbElement::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbElement::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...simplementation of lbNamedValue:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbNamedValue)
// No additionally interface, because it's not used externally yet.
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbNamedValue::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbNamedValue::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbNamedValue\58\\58\setName\40\\41\:0:*/
lbErrCodes lbNamedValue::setName(const char* const _name) {
        name = strdup((_name == NULL) ? "" : _name);
        return ERR_NONE;
}
/*...e*/
/*...slbNamedValue\58\\58\getName\40\\41\:0:*/
lbErrCodes lbNamedValue::getName(char* & _name) {
        _name = strdup(name);
        return ERR_NONE;
}
/*...e*/
/*...slbNamedValue\58\\58\setValue\40\\41\:0:*/
lbErrCodes lbNamedValue::setValue(lb_I_Unknown* _value) {
        if (uk_value != NULL) RELEASE(uk_value);
        
        // clone() set's the ref counter to 1, so a release above deletes the object.
        uk_value = _value->clone(__FILE__, __LINE__);
        return ERR_NONE;
}
/*...e*/
/*...slbNamedValue\58\\58\getValue\40\\41\:0:*/
lbErrCodes lbNamedValue::getValue(lb_I_Unknown* & _value) {
        _value = uk_value->clone(__FILE__, __LINE__);
        
        return ERR_NONE;
}
/*...e*/

lbNamedValue* namedValue = NULL;
//lb_I_Container* moduleList = NULL;

typedef struct instances_of_module {
        char* moduleName;
        int   count;
} instModule;



/*...sDocu for Module management:0:*/
/**
 * lbModule is a manager for creating instances of interfaces, regartless where
 * it came from. lbModule must be responsible for the following tasks:
 *
 * Knowing of loaded modules,
 * loading new modules,
 * releasing a module, if no more instances from there are in use.
 *
 *
 * So these functions may be declared for that issues:
 *
 * protected:
 * // Handle is managed internally
 * lbErrCodes lbModule::loadModule(const char* modulename);
 *
 * // Not the handle is needed. A module can only loaded once in a process.
 * lbErrCodes lbModule::unloadModule(const char* modulename);   
 *
 *
 * A general problem here is, that a bootstraping of some base instances must be
 * made. For the module management I need a container instance. For this problem,
 * It may be usefull to implement simple classes for that interfaces.
 *
 *
 *
 */
/*...e*/

/*...slbModule\58\\58\request\40\\46\\46\\46\\41\:0:*/
/**
 * The requestable interface simply return result of 'spoken' requests.
 * The 'spoken' request may be only one word or it may a sentence.
 *
 * A possible request may like this:
 *      get instance from interface '<parameter>'
 *
 * With this, a requestable object may be instructable by a simple script
 * language.
 */
lbErrCodes LB_STDCALL lbModule::request(const char* request, lb_I_Unknown** result) {
        lbErrCodes err = ERR_NONE;
        char buf[1000] = "";
        if (moduleList == NULL) {
        	_CL_VERBOSE << "lbModule::request(...) calls initialize()." LOG_
                initialize();
        }
	
        char* functorName = NULL;
	buf[0] = 0;
        UAP(lb_I_ConfigObject, config, __FILE__, __LINE__)
        UAP(lb_I_ConfigObject, impl, __FILE__, __LINE__)

// Using this has been resulted in memory leak
//        config.setLine(__LINE__);
//        config.setFile(__FILE__);
        /**
         * impl is not returned in any way, I think, so it is allowed to delete the object
         * at lost of focus.
         */
         
#ifdef USE_INTERFACE_REPOSITORY
	if (newInterfaceRepository != NULL) {
		newInterfaceRepository->setCurrentSearchInterface(request);
		UAP(lb_I_FunctorEntity, e, __FILE__, __LINE__)
		
		e = newInterfaceRepository->getFirstEntity();
		
		char* functor = e->getFunctor();
		char* module  = e->getModule();
		
		UAP(lb_I_Unknown, _result, __FILE__, __LINE__)
		makeInstance(functor, module, &_result);

		//QI(result, lb_I_InterfaceRepository, newInterfaceRepository, __FILE__, __LINE__)		
		*result = _result.getPtr();
		(*result)->setModuleManager(this, __FILE__, __LINE__);
		_result++;

	} else {
		printf("Error: Have no interface repository to locate configuration for %s\n", request); 
	}

#endif
#ifndef USE_INTERFACE_REPOSITORY        
/*...sget my unknown interface:8:*/
        if (strcmp(request, "instance/XMLConfig") == 0) {
printf("Get unknown interface of XMLConfig object\n");                
                xml_Instance->queryInterface("lb_I_Unknown", (void**) result, __FILE__, __LINE__);
                
                return ERR_NONE;
        }
/*...e*/
        else {
/*...sget any interface:8:*/
        /**
         * Here should be created an unknown object. The mapping of a real
         * instance is done in the xml file instead of if blocks.
         */
                char* node = "#document/dtdHostCfgDoc/Modules/Module/Functions/Function/Functor/InterfaceName";
                int count = 0;
                                        // request is a functor
                /**
                 * Get the nodes that match the path in 'node'. It may simple to change this
                 * to get all 'InterfaceName' entries. It should work the same way.
                 *
                 * 1. It is better to let this as it is. In the new XML file, an interfacename
                 * is a chield of the functor. I must find the functor's that implements the
                 * requiered interface.
                 *
                 * findFunctorNode, implemented as now, has a bug: It returns every times the
                 * first element.
                 * It should be an iterator to get all the elements found by hasConfigobject.
                 * Leaving the current technique, enables the searchability for functors dirctly
                 * and also enables the search for interfaces.
                 *
                 * The only thing, that must not appear, is an interfacename is the same as a
                 * functor !
                 */
                if (xml_Instance->hasConfigObject(node, count) == ERR_NONE) {
                        char* moduleName = NULL;
                        lb_I_ConfigObject* implementations = NULL;
                        char* value = NULL;
                        /**
                         * Get the list of found objects as a list.
                         * The result is a view of notes in a max deep
                         * of one level.
                         */
                        xml_Instance->getConfigObject(&config, node);
                        track_Object(*&config, "Test object given by xml_Instance->getConfigObject()");
                        #ifdef VERBOSE
                        printf("The config object has %d references\n", config->getRefCount());
			#endif
                        /**
                         * Check, which element implements the requested interface.
                         * If there are more than one for an interface, get the first.
                         * Later, get the default.
                         */
                        // May be the same bug as in internal ...
                        // It was the self pointed parent member
                        // config++;
                        if ((err = config->getFirstChildren(&impl)) == ERR_NONE) {
                                impl.setLine(__LINE__);
                                impl.setFile(__FILE__);
                                err = impl->getAttributeValue("Name", value);

                                if (strcmp(value, request) == 0) {
                                        //impl is the needed object     
                                } else {
                                        int stop = 1;
                                        while (stop == 1) {
                                                RELEASE(impl);
                                                
                                                if ((err = config->getNextChildren(&impl)) != ERR_NONE) {
			                                impl.setLine(__LINE__);
                        			        impl.setFile(__FILE__);
                                                        stop = 0;
                                                        break;
                                                } else {
							impl.setLine(__LINE__);
							impl.setFile(__FILE__);
						}

                                                if (value != NULL) 
                                                {
                                                        impl->deleteValue(value);
                                                        value = NULL;
                                                }

                                                err = impl->getAttributeValue("Name", value);

                                                if (strcmp(value, request) == 0) {
                                                        stop = 0;
                                                }
                                        }
                                }
                        }

                        if (value == NULL) {
                                _CL_VERBOSE << "return ERR_MODULE_NO_INTERFACE" LOG_
                                return ERR_MODULE_NO_INTERFACE;
                        }
                        if (strcmp(request, value) != 0) {
                                _CL_VERBOSE << "Error: There is no implementation for wanted interface" LOG_
                                
                                if (value != NULL) {
                                        impl->deleteValue(value);
                                }
                                return ERR_MODULE_NO_INTERFACE;
                        }
                        if (value != NULL) {
                                impl->deleteValue(value);
                        }
                        moduleName = findFunctorModule(&impl);
                        functorName = findFunctorName(&impl);
                        if (value != NULL) {
                                impl->deleteValue(value);
                        }
                        makeInstance(functorName, moduleName, result);
                        if ((*result) == NULL) {
                        	_CL_VERBOSE << "Error: makeInstance has been failed for '" <<
                        	request << "', '" << functorName << "', '" << moduleName << "'" LOG_
				printf("Error: Instance is a NULL pointer %s\n", functorName);
                        }
                        (*result)->setModuleManager(this, __FILE__, __LINE__);
                        notify_create(*result, (*result)->getClassName());
                        if (moduleName != NULL) impl->deleteValue(moduleName);
                        if (functorName != NULL) impl->deleteValue(functorName);
                } else {
                        COUT << "Something goes wrong!" << ENDL;
                        COUT << "xml_Instance->hasConfigObject() returns <> ERR_NONE!" << ENDL;
                }
                
                
/*...e*/
        }
        if (functorName != NULL) impl->deleteValue(functorName);
#endif
        return ERR_NONE;
}
/*...e*/

IMPLEMENT_SINGLETON_FUNCTOR(getlb_ModuleInstance, lbModule)

/*...slbErrCodes lbModule\58\\58\load\40\char\42\ name\41\:0:*/
lbErrCodes lbModule::load(char* name) {
printf("lbModule::load(%s) called\n", name);
#ifndef USE_INTERFACE_REPOSITORY
        UAP(lb_I_XMLConfig, xml_Instance, __FILE__, __LINE__)

        getXMLConfigObject(&xml_Instance);
        
        COUT << "lbModule::load(char* name) called" << ENDL;

        if (xml_Instance != NULL) {
            if (xml_Instance->parse() != ERR_NONE) {
                _CL_VERBOSE << "Error while parsing XML document\n" LOG_
            }
        }
#endif
        
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\getObjectInstance\40\const char\42\ name\44\ lb_I_Container\42\\38\ inst\41\:0:*/
lbErrCodes lbModule::getObjectInstance(const char* name, lb_I_Container*& inst) {
        return ERR_NONE;
}
/*...e*/

/*...slbErrCodes DLLEXPORT LB_STDCALL lb_releaseInstance\40\lb_I_Unknown \42\ inst\41\:0:*/
lbErrCodes DLLEXPORT LB_STDCALL lb_releaseInstance(lb_I_Unknown * inst) {
        RELEASE(inst);
        return ERR_NONE;
}
/*...e*/

#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";

        switch (reason) {
                case DLL_PROCESS_ATTACH:
                	TRMemOpen();
                	
                	if (isSetTRMemTrackBreak()) setTRMemTrackBreak(getTRMemTrackBreak());
                	
                	TRMemSetModuleName(__FILE__);
                	
                        if (situation) {
                                _CL_VERBOSE << "DLL statically loaded." LOG_
                        }
                        else {
                                _CL_VERBOSE << "DLL dynamically loaded.\n" LOG_
                        }
                        break;
                case DLL_THREAD_ATTACH:
                        _CL_VERBOSE << "New thread starting.\n" LOG_
                        break;
                case DLL_PROCESS_DETACH:
                	_CL_VERBOSE << "DLL_PROCESS_DETACH for " << __FILE__ LOG_                        
                        if (situation)
                        {
                                _CL_LOG << "DLL " << __FILE__ << " released by system." LOG_
                        }
                        else
                        {
                                _CL_LOG << "DLL " << __FILE__ << " released by program.\n" LOG_
                        }
                        break;
                case DLL_THREAD_DETACH:
                        _CL_VERBOSE << "Thread terminating.\n" LOG_
                default:
                        return FALSE;
        }
        
        return TRUE;
}
/*...e*/
#endif

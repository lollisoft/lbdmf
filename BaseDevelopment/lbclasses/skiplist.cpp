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
            
            40235 DÅsseldorf (germany)
*/
/*...e*/

#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif

// skiplist.cpp
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.19 $
 * $Name:  $
 * $Id: skiplist.cpp,v 1.19 2004/06/09 07:03:23 lollisoft Exp $
 *
 * $Log: skiplist.cpp,v $
 * Revision 1.19  2004/06/09 07:03:23  lollisoft
 * Still problems with undeleted container data ??
 *
 * Revision 1.18  2004/01/24 16:15:02  lollisoft
 * minor changes
 *
 * Revision 1.17  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.16  2003/08/16 18:07:00  lollisoft
 * Added my new address due to move
 *
 * Revision 1.15  2003/07/31 20:18:25  lollisoft
 * Removed logging messages
 *
 * Revision 1.14  2003/06/16 21:49:42  lollisoft
 * Bugfix ??
 *
 * Revision 1.13  2003/02/17 21:34:41  lollisoft
 * Much problems with compilation solved, bu wy came this ??
 *
 * Revision 1.12  2003/01/19 17:31:25  lolli
 * Runs now with MSC
 *
 * Revision 1.11  2002/12/29 16:05:10  lolli
 * Intent to go public
 *
 * Revision 1.10  2002/11/29 19:50:27  lothar
 * Compiles again under linux, but some problems at runtime with DOMString
 *
 * Revision 1.9  2002/10/17 17:35:13  lolli
 * Use of _CL_LOG macro
 *
 * Revision 1.8  2002/10/04 16:53:14  lolli
 * Replaced old LOG macro with the new
 * _LOG << "text" << integer value LOG_
 * combination. This makes sprintf obsolete.
 *
 * Revision 1.7  2002/09/12 18:36:12  lolli
 * Removed some log messages
 *
 * Revision 1.6  2002/09/07 09:57:13  lolli
 * First working callback function
 *
 * Revision 1.5  2002/08/21 18:44:29  lolli
 * Implemented the new container functions for direct access
 *
 * Revision 1.4  2002/06/01 08:59:27  lolli
 * Bug due to position of module definition for export
 *
 * Revision 1.3  2002/05/01 14:17:13  lolli
 * This version does not compile
 *
 * Revision 1.2  2002/04/15 18:24:33  lolli
 * Huge changes - works good
 *
 * Revision 1.1  2002/03/03 08:33:57  lolli
 * Initial non interface based skiplist
 *
 **************************************************************/
/*...e*/
/*...sincludes:0:*/
#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#ifdef LINUX
#include <string.h>
#endif

#include <lbInterfaces.h>
#include <lbConfigHook.h>

/*...sLB_CLASSES_DLL scope:0:*/
#define LB_CLASSES_DLL
#include <lbclasses-module.h>
/*...e*/

#include <skiplist.h>
/*...e*/
/*...sfunctor:0:*/
#ifdef __cplusplus
extern "C" {
#endif

IMPLEMENT_FUNCTOR(instanceOfSkipList, SkipList)

#ifdef __cplusplus
}
#endif
/*...e*/

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
printf("SkipNode::~SkipNode() called\n");
      delete [] forward; 
      
//      if (value != NULL) RELEASE(value)
}
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(SkipList)
	ADD_INTERFACE(lb_I_Container)
END_IMPLEMENT_LB_UNKNOWN()


lbErrCodes LB_STDCALL SkipList::setData(lb_I_Unknown* uk) {
	_CL_LOG << "SkipList::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}
SkipList::SkipList() {
	iteration = 0;
	head = new SkipNode();
	skipiterator = NULL;
	flag = 1;
	level = MAXLEVEL;
	count = 0;
	ref = STARTREF;
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
	delete head;
	head = new SkipNode();
	level = MAXLEVEL;

	iteration = 0;
	skipiterator = NULL;
	count = 0;
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
        el->setModuleManager(manager.getPtr(), __FILE__, __LINE__);

        insert(el);
        if (search(*key) == NULL) {
        	_LOG << "Error: SkipList::insert(...) failed" LOG_
        } else {
        	count++;
        }
        
        return err; 
} 
/*...e*/
/*...sSkipList\58\\58\remove\40\lb_I_KeyBase\42\\42\ const key\41\:0:*/
lbErrCodes LB_STDCALL SkipList::remove(lb_I_KeyBase** const key) { 
        lbErrCodes err = ERR_NONE; 
        lbSkipListElement* el = new lbSkipListElement(NULL, *key);
        
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
        if (container_data == NULL) _LOG << "Could not get unknown interface of lbElement!" LOG_

        lb_I_Unknown* uk_o = NULL; 
        if ((uk_o = container_data->getObject()) == NULL) { 
                _LOG << "Failed to insert first element in SkipList::insert" LOG_
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
    _LOG << "SkipList::_remove(lb_I_KeyBase** const key) is Obsolete" LOG_ 
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
	        _LOG << "Error: Please call hasMoreElements first to check if any elements are available!" LOG_
        	getch(); 
	        return NULL; 
	}
} 
/*...e*/
/*...sSkipList\58\\58\getElement\40\lb_I_KeyBase\42\\42\ const key\41\:0:*/
lb_I_Unknown* LB_STDCALL SkipList::getElement(lb_I_KeyBase** const key) { 
    lb_I_Unknown* e = search(*key);
    
    if (e == NULL) {
    	_LOG << "SkipList::getElement(...) returns a NULL pointer!" LOG_
	printf("SkipList::getElement(lb_I_KeyBase** const key) searches for '%s'\n", (*key)->charrep());
    }
    
    return e;
} 
/*...e*/
/*...sSkipList\58\\58\setElement\40\lb_I_KeyBase\42\\42\ key\44\ lb_I_Unknown \42\\42\ const e\41\:0:*/
void LB_STDCALL SkipList::setElement(lb_I_KeyBase** key, lb_I_Unknown ** const e) { 
    remove(key); 
    insert(e, key); 
}
/*...e*/
lb_I_Unknown* LB_STDCALL SkipList::getElementAt(int i) {
        _LOG << "SkipList::getElementAt(int i) not implemented" LOG_
        int ii = 0;
        lb_I_Element* temp = container_data;
        while (temp != NULL) {
                if (ii == i) return temp->getObject();
                temp = temp->getNext();
        }
        return NULL;
}
lb_I_KeyBase* LB_STDCALL SkipList::getKeyAt(int i) {
        _LOG << "SkipList::getKeyAt(int i) not implemented" LOG_
        int ii = 0;
        lb_I_Element* temp = container_data;
        while (temp != NULL) {
                if (ii == i) return temp->getKey();
                temp = temp->getNext();
                ii++;
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
  
  if (x == NULL) _LOG << "Error: NULL pointer while searching in skiplist" LOG_
  
  for (int i=level; i>=0; i--) {
    while ((x->forward[i] != NULL) && (*(x->forward[i]->value->getKey()) < searchKey)) {
      x = x->forward[i];
    }
  }
  x = x->forward[0];  // Move to actual record, if it exists

  if ((x != NULL) && (*(x->value->getKey()) == searchKey)) {
  	return x->value->getObject();
  } else {
  	return NULL;
  }
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
    count--;
  }


/*...e*/
/*...sSkipList\58\\58\can_dump\40\\41\:0:*/
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
        cout << "temp->value is " << temp->value << endl;
        for(int i=0; i<=temp->myLevel && flag != 0; i++)
            if (temp->forward[i] == NULL){
                cout << " rest of list is empty" << endl;
                flag = 0;
            }
            else
                cout<<"  point to "<<temp->forward[i]->value<<"\n";
    }
}
#endif
/*...e*/
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbSkipListElement)
        ADD_INTERFACE(lb_I_Element)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_LB_ELEMENT(lbSkipListElement)

lbErrCodes LB_STDCALL lbSkipListElement::setData(lb_I_Unknown* uk) {
	_LOG << "lbSkipListElement::setData(...) not implemented yet" LOG_

	return ERR_NOT_IMPLEMENTED;
}

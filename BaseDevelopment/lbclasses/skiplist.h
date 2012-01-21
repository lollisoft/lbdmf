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

#ifndef LB_SKIPLIST
#define LB_SKIPLIST

class lbSkipListElement;
typedef lb_I_Element* Elem;
#define MAXLEVEL 20


/*...sclass SkipNode:0:*/
class SkipNode {
  public:
    SkipNode();
    SkipNode(lb_I_Element* r, int level);
    SkipNode(const SkipNode &s);
    virtual ~SkipNode();

    void detach();
    
    void resetForward() {
    	delete [] forward;
    	forward = NULL;
    }
    
    int myLevel;
    UAP(lb_I_Element, value)
    //char buffer[100];
    SkipNode** forward;
};
/*...e*/
/*...sclass SkipList:0:*/
class SkipList : public lb_I_Container {
private:
      SkipNode*		head;
      SkipNode*		skipiterator;
      lb_I_KeyBase*	_currentKey;
	  
      int level;
      int flag;

      void AdjustHead(int& level) {level = MAXLEVEL;}

public:
	SkipList();
	virtual ~SkipList();

	lb_I_Iterator* LB_STDCALL getIterator();
	
	DECLARE_LB_UNKNOWN()
	DECLARE_LB_I_CONTAINER_IMPL()

public:


	lb_I_Unknown* search(lb_I_KeyBase* searchKey, bool setIterator = false);
	void insert(Elem);
      
      
      
	void remove(Elem);
	int can_dump();
	Elem dump_next();
};
/*...e*/

class Iterator : public lb_I_Iterator
{
private:
	SkipNode*		head;
	SkipNode*		skipiterator;
	lb_I_KeyBase*	_currentKey;
	  
	int level;
	int flag;
	int count;
	bool cloning;
	int iteration;
	lb_I_Element* iterator;
	bool canDeleteObjects;
	lb_I_Element* container_data;

	int can_dump();
	Elem dump_next();

public:
	Iterator();
	virtual ~Iterator();
	Iterator(SkipNode* _head, int _count);

	DECLARE_LB_UNKNOWN()

		
	/** \brief Number of objects in the container.
	 *
	 */
    int LB_STDCALL Count();

	/** \brief Returns 1 if elements are iterable.
	 *
	 */
    int LB_STDCALL hasMoreElements();

	/** \brief Get next element.
	 *
	 */
    lb_I_Unknown* LB_STDCALL nextElement();

	/** \brief Stops the iteration modus, begun with hasMoreElements.
	 *
	 * Use this function to stop the iteration. You must use this function to
	 * be able to restart iteration. If hasMoreElements returns 0, the
	 * iteration is finished automatically.
	 */
    void LB_STDCALL finishIteration();
	
	/** \brief Get current key based on iterator position.
	 *
	 */
	lb_I_KeyBase* LB_STDCALL currentKey();
};


/*...sclass lbSkipListElement:0:*/
class lbSkipListElement : public lb_I_Element {
public:
    lbSkipListElement();
    virtual ~lbSkipListElement();
	
    lbSkipListElement(const lb_I_Element &e);

    DECLARE_LB_UNKNOWN()

    DECLARE_LB_ELEMENT(lbSkipListElement)
#ifndef UNIX
#ifndef _MSC_VER
//    lb_I_Unknown* getObject() const;
#endif
#endif
};
/*...e*/

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_FUNCTOR(instanceOfSkipList)

#ifdef __cplusplus
}
#endif

#endif

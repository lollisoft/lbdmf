


/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.4 $
 * $Name:  $
 * $Id: lbkey.h,v 1.4 2000/07/06 06:09:32 lolli Exp $
 * $Log: lbkey.h,v $
 * Revision 1.4  2000/07/06 06:09:32  lolli
 * Constructor now with const parameter
 *
 * Revision 1.3  2000/06/24 21:32:08  lolli
 * Socket bugfix
 *
 * Revision 1.2  2000/04/27 01:36:24  lolli
 * Commit in order of data GAU
 *
 * Revision 1.1.1.1  2000/03/06 20:54:58  lolli
 * Imported
 *
 * Revision 1.4  2000/01/23 14:32:55  lolli
 * Corrected error in revision conflict
 *
 * Revision 1.2  1999/11/25 20:48:49  lothar
 * Checked in due to working directory change
 *
 * Revision 1.1  1999/10/08 21:27:00  Administrator
 * Initial
 *
 ************************************************************************************************************/

#ifndef LB_KEY
#define LB_KEY

#undef DLLEXPORT

#ifdef LB_CONTAINER_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef LB_CONTAINER_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif

class DLLEXPORT lbKeyBase {
public:

    virtual int operator == (const lbKeyBase &_key);
    virtual int operator > (const lbKeyBase &_key);

    virtual int equals(const lbKeyBase &_key) = 0;
    virtual int greater(const lbKeyBase &_key) = 0;
    virtual lbKeyBase* clone() const = 0;

    virtual char* charrep() = 0;
};

class DLLEXPORT lbKey : public lbKeyBase {
public:
    lbKey();
    lbKey(int _key);
    lbKey(const lbKeyBase & k);
    virtual ~lbKey();

    // Must be implemented
    virtual int equals(const lbKeyBase &_key);
    virtual int greater(const lbKeyBase &_key);
    lbKeyBase* clone() const;

    virtual char* charrep();
private:

    int key;
};

class DLLEXPORT lbKeyUL : public lbKeyBase {
public:
    lbKeyUL();
    lbKeyUL(unsigned long _key);
    lbKeyUL(const lbKeyBase & k);
    virtual ~lbKeyUL();

    // Must be implemented
    virtual int equals(const lbKeyBase &_key);
    virtual int greater(const lbKeyBase &_key);
    lbKeyBase* clone() const;

    virtual char* charrep();
private:

    unsigned long key;
};

class DLLEXPORT lbStringKey : public lbKeyBase {
public:
    lbStringKey(const char* _key);
    lbStringKey(const lbStringKey & k);
    virtual ~lbStringKey();

    // Must be implemented
    virtual int equals(const lbKeyBase &_key);
    virtual int greater(const lbKeyBase &_key);
    lbKeyBase* clone() const;

    virtual char* charrep();
private:
    char* key;    
};

#endif //LB_ELEMENT


/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.6 $
 * $Name:  $
 * $Id: lbkey.h,v 1.6 2001/03/14 20:52:51 lolli Exp $
 * $Log: lbkey.h,v $
 * Revision 1.6  2001/03/14 20:52:51  lolli
 * Compiles and links now, but it will not run
 *
 * Revision 1.5  2000/10/05 22:56:45  lothar
 * Most changes are interface issues
 *
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
/*...e*/

#ifndef LB_KEY
#define LB_KEY

/*...sDLLEXPORT:0:*/
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
/*...e*/

/*...sclass DLLEXPORT lbKeyBase:0:*/
class DLLEXPORT lbKeyBase : public lb_I_KeyBase {
public:

//    virtual int operator == (const lb_I_KeyBase &_key) const;
//    virtual int operator > (const lb_I_KeyBase &_key) const;

    virtual int equals(const lb_I_KeyBase* _key) const = 0;
    virtual int greater(const lb_I_KeyBase* _key) const = 0;
    virtual lb_I_KeyBase* clone() const = 0;

    virtual char* charrep() = 0;
};
/*...e*/
/*...sclass DLLEXPORT lbKey \58\ public lbKeyBase:0:*/
class DLLEXPORT lbKey : public lbKeyBase {
public:
    lbKey();
    lbKey(int _key);
    lbKey(const lb_I_KeyBase* k);
    virtual ~lbKey();

    // Must be implemented
    virtual int equals(const lb_I_KeyBase* _key) const;
    virtual int greater(const lb_I_KeyBase* _key) const;
    lb_I_KeyBase* clone() const;

    virtual char* charrep();
    virtual char* getMainInterface() const { return "intKey"; }
private:

    int key;
};
/*...e*/
/*...sclass DLLEXPORT lbKeyUL \58\ public lbKeyBase:0:*/
class DLLEXPORT lbKeyUL : public lbKeyBase {
public:
    lbKeyUL();
    lbKeyUL(unsigned long _key);
    lbKeyUL(const lb_I_KeyBase* k);
    virtual ~lbKeyUL();

    // Must be implemented
    virtual int equals(const lb_I_KeyBase* _key) const;
    virtual int greater(const lb_I_KeyBase* _key) const;
    lb_I_KeyBase* clone() const;

    virtual char* charrep();
    virtual char* getMainInterface() const { return "ULKey"; }
private:

    unsigned long key;
};
/*...e*/
/*...sclass DLLEXPORT lbStringKey \58\ public lbKeyBase:0:*/
class DLLEXPORT lbStringKey : public lbKeyBase {
public:
    lbStringKey(const char* _key);
    lbStringKey(const lb_I_KeyBase* k);
    virtual ~lbStringKey();

    // Must be implemented
    virtual int equals(const lb_I_KeyBase* _key) const;
    virtual int greater(const lb_I_KeyBase* _key) const;
    lb_I_KeyBase* clone() const;

    virtual char* charrep();
    virtual char* getMainInterface() const { return "stringKey"; }
private:
    char* key;    
};
/*...e*/

#endif //LB_ELEMENT

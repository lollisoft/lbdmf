
/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.14 $
 * $Name:  $
 * $Id: lbkey.h,v 1.14 2002/11/29 19:50:27 lothar Exp $
 * $Log: lbkey.h,v $
 * Revision 1.14  2002/11/29 19:50:27  lothar
 * Compiles again under linux, but some problems at runtime with DOMString
 *
 * Revision 1.13  2002/06/20 21:02:56  lolli
 * Added missing code for _MSC_VER
 *
 * Revision 1.12  2002/05/30 17:53:03  lolli
 * Current development seems to run
 *
 * Revision 1.11  2002/04/15 18:24:33  lolli
 * Huge changes - works good
 *
 * Revision 1.10  2001/12/12 17:12:45  lothar
 * Hehe - runs on linux
 *
 * Revision 1.9  2001/07/11 16:04:35  lolli
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.8  2001/06/21 06:34:42  lolli
 * Now using interface macros
 *
 * Revision 1.7  2001/03/30 20:08:07  lolli
 * Commit due to possible head crash on anakin (Linux)
 *
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

/*...sclass lbKey \58\ public lb_I_KeyBase:0:*/
class lbKey : public lb_I_KeyBase {
public:
#ifdef _MSC_VER
	lbKey(char* file, int line) { key = 0; strcpy(keyType, "int"); }
#endif

	lbKey();
	lbKey(int _key);
	lbKey(const lb_I_KeyBase* k);
	virtual ~lbKey();

	DECLARE_LB_UNKNOWN()

	DECLARE_LB_KEYBASE()
	
private:

	char keyType[10];
	int key;
};
/*...e*/
/*...sclass lbKeyUL \58\ public lb_I_KeyBase:0:*/
class lbKeyUL : public lb_I_KeyBase {
public:
#ifdef _MSC_VER
	lbKeyUL(char* file, int line) { key = 0; strcpy(keyType, "UL"); }
#endif
    lbKeyUL();
    lbKeyUL(unsigned long _key);
    lbKeyUL(const lb_I_KeyBase* k);
    virtual ~lbKeyUL();

    DECLARE_LB_UNKNOWN()
    
    DECLARE_LB_KEYBASE()

private:

    char keyType[10];
    unsigned long key;
};
/*...e*/
/*...sclass lbStringKey \58\ public lb_I_KeyBase:0:*/
class 
#ifdef WINDOWS
#ifdef HOOK_DLL
LB_DLLEXPORT
#endif
#ifndef HOOK_DLL
LB_DLLIMPORT
#endif
#endif
lbStringKey : public lb_I_KeyBase {
public:
#ifdef _MSC_VER
     lbStringKey(char* file, int line) { key = ""; strcpy(keyType, "string"); }
#endif
    lbStringKey();
    lbStringKey(const char* _key);
    lbStringKey(const lb_I_KeyBase* k);
    virtual ~lbStringKey();

    DECLARE_LB_UNKNOWN()
    
    DECLARE_LB_KEYBASE()

private:

    char keyType[10];
    char* key;    
};
/*...e*/

#ifdef __cplusplus
extern "C" {
#endif            

DECLARE_FUNCTOR(instanceOfIntegerKey)

#ifdef __cplusplus
}
#endif            

#endif //LB_ELEMENT

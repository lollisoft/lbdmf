/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.3 $
 * $Name:  $
 * $Id: lbGlobal.h,v 1.3 2000/06/24 21:14:16 lolli Exp $
 *
 * $Log: lbGlobal.h,v $
 * Revision 1.3  2000/06/24 21:14:16  lolli
 * Many changes
 *
 * Revision 1.2  2000/05/04 23:51:43  lolli
 * Added define for logfile mutex
 *
 * Revision 1.1  2000/04/30 14:28:43  lolli
 * Initial
 *
 **************************************************************/

/*...e*/


#ifndef __LB_GLOBAL__
#define __LB_GLOBAL__

/*...sComponentTypes:0:*/
enum ComponentTypes {
	GUI,		// 
	EVENTHANDLER,	// A GUI component can recieve events
	EVENTRAISER,	// This is an active component
};
/*...e*/
/*...sGUITypes:0:*/
enum GUITypes { 
	LB_MENUBAR, 
	LB_MENU, 
	LB_MENUENTRY, 
	LB_APP_TITLE
};
/*...e*/

#define LB_LOGFILE_MUTEX 1
#define LB_SEND_MUTEX 2
#define LB_RECV_MUTEX 3

#endif


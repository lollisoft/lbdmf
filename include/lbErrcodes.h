/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.1 $
 * $Name:  $
 * $Id: lbErrcodes.h,v 1.1 2000/07/06 06:14:24 lolli Exp $
 *
 * $Log: lbErrcodes.h,v $
 * Revision 1.1  2000/07/06 06:14:24  lolli
 * Initial
 *
 **************************************************************/

/*...e*/


#ifndef __LB_ERRCODES__
#define __LB_ERRCODES__

/*...slbErrCodes:0:*/
enum lbErrCodes { 
	ERR_NONE = 0,
/* Errcodes for dispatcher */
	ERR_DISP_HANDLER_EXSISTS,

/* Errcodes for appbus dispatcher in connected state */
	ERR_APPBUS_DISPATCH, 		// Haeder found, but unknown identifer
	ERR_APPBUS_DISPATCH_HAEDER,	// No dispatch haeder found
	ERR_APPBUS_ECHO,		// Test server for echo
	
/* Errcodes for container */
	ERR_CONTAINER_INSERT,
	ERR_CONTAINER_REMOVE,

	ERR_APP_SERVER_HANDLECONNECT,
	ERR_APP_SERVER_HANDLEDISCONNECT,
	ERR_APP_SERVER_REQUEST_CHAR,
	ERR_APP_SERVER_REQUEST_INTEGER,
	ERR_APP_SERVER_WAIT_REQUEST,
	ERR_APP_SERVER_SEND_REQUEST,
	ERR_APP_SERVER_ADDHANDLER,

	ERR_APPBUS_SERVER_ANOUNCECLIENT,

	ERR_TRANSFER_DATA_INCORRECT_TYPE,
	ERR_TRANSFER_FAILED,
	ERR_TRANSFER_NULLPTR,
	ERR_TRANSFER_ENDED,
	ERR_TRANSFER_SEND_DATATYPE,
	
	ERR_SOCKET_UNKNOWN,
	ERR_SOCKET_STATE,
	ERR_SOCKET_CLOSE_CLIENT,
	ERR_SOCKET_CLOSE_SERVER,
	ERR_SOCKET_NEAGLEOFF,
	ERR_SOCKET_NOT_IMPLEMENTED,
	ERR_SOCKET_CLIENT_S_INVALID,
	ERR_SOCKET_SERVER_S_INVALID,
	ERR_SOCKET_RECV,
	ERR_SOCKET_UNCONNECTED,
	ERR_SOCKET_CLOSED
};
/*...e*/

#define LB_LOGFILE_MUTEX 1

#endif

/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.5 $
 * $Name:  $
 * $Id: lbErrcodes.h,v 1.5 2001/02/06 20:38:16 lothar Exp $
 *
 * $Log: lbErrcodes.h,v $
 * Revision 1.5  2001/02/06 20:38:16  lothar
 * Commit for backup the data
 *
 * Revision 1.4  2000/10/21 10:41:20  lothar
 * Added errcodes for lbDOMConfig results
 *
 * Revision 1.3  2000/10/05 23:07:20  lothar
 * Much changes
 *
 * Revision 1.2  2000/08/01 05:55:08  lolli
 * Currently runs with new interface
 *
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

/* A yet not specified err code */
	
	ERR_UNSPECIFIED,
	ERR_NOT_IMPLEMENTED,
	ERR_NO_OBJECT,
	ERR_MORE_OBJECTS,
	ERR_SINGLE_OBJECT,
	ERR_NO_INTERFACE,
	
/* Errcodes for dispatcher */

	ERR_DISP_HANDLER_EXSISTS,

/* Errcodes for appbus dispatcher in connected state */

	ERR_APPBUS_DISPATCH, 		// Haeder found, but unknown identifer
	ERR_APPBUS_DISPATCH_HAEDER,	// No dispatch haeder found
	ERR_APPBUS_ECHO,		// Test server for echo


	ERR_NO_ENVIRONMENT,		// Any needed env var is not set

/* Module error codes */

	ERR_MODULE_NOT_FOUND,
	ERR_FUNCTION_NOT_FOUND,
	
/* Errcodes for dealing with XML */

	ERR_XML_NOFILE,	
	ERR_XML_INIT,
	ERR_XML_GENERAL_PARSE_FAILED,

/* Errcodes for lb_I_ConfigObject */

	ERR_CONFIG_NO_CHILDS,
	ERR_CONFIG_NO_MORE_CHILDS,
	ERR_CONFIG_EMPTY_CONTAINER,
	ERR_CONFIG_CONTAINER_BOUND,
	ERR_CONFIG_INTERNAL,
	
/* Errcodes for container */
	ERR_CONTAINER_INSERT,
	ERR_CONTAINER_REMOVE,

	ERR_APP_SERVER_DISPATCH,	// Unknown protocol header
	ERR_APP_SERVER_HANDLECONNECT,
	ERR_APP_SERVER_HANDLEDISCONNECT,
	ERR_APP_SERVER_REQUEST_CHAR,
	ERR_APP_SERVER_REQUEST_INTEGER,
	ERR_APP_SERVER_WAIT_REQUEST,
	ERR_APP_SERVER_SEND_REQUEST,
	ERR_APP_SERVER_ADDHANDLER,
	
	ERR_APP_CLIENT_ADDHANDLER,

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

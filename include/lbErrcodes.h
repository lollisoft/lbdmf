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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/
/*...e*/
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.35 $
 * $Name:  $
 * $Id: lbErrcodes.h,v 1.35 2008/04/18 05:48:27 lollisoft Exp $
 *
 * $Log: lbErrcodes.h,v $
 * Revision 1.35  2008/04/18 05:48:27  lollisoft
 * Added an error code when UML import with database backend plugin does not work.
 *
 * Revision 1.34  2007/11/22 16:13:28  lollisoft
 * New module error code.
 *
 * Revision 1.33  2007/09/23 11:20:00  lollisoft
 * New error code to catch unknown column names.
 *
 * Revision 1.32  2007/08/08 19:48:50  lollisoft
 * Changes to allow using BLOB data fields. Not completely finished.
 *
 * Revision 1.31  2007/04/22 13:39:42  lollisoft
 * Added another error code.
 *
 * Revision 1.30  2007/01/29 20:12:59  lollisoft
 * Checkin for Linux.
 *
 * Revision 1.29  2006/06/24 06:19:54  lollisoft
 * Commit due to travel to Duesseldorf.
 *
 * Revision 1.28  2006/06/11 16:26:19  lollisoft
 * More error codes.
 *
 * Revision 1.27  2006/02/21 19:35:52  lollisoft
 * Implemented autoload mechanism of last loaded application.
 * It demonstrates the new capabilities operating with files.
 *
 * Revision 1.26  2006/01/22 13:32:29  lollisoft
 * New mutex id's. Why is this here ?
 *
 * Revision 1.25  2005/12/02 17:45:59  lollisoft
 * New DB message code.
 *
 * Revision 1.24  2005/12/02 00:28:43  lollisoft
 * Deleting a row works for some tests. Deleting data in join queries is not tested
 * and would propably not work. This is at least due to lack of creating a delete
 * statement per related table.
 *
 * Now this deleting also includes the ability to reopen the query as needed.
 * Form code is adopted to the case if there are no peek aheads are done
 * while fetching new data.
 *
 * Code cleanup would be done later.
 *
 * Revision 1.23  2005/10/09 22:42:09  lollisoft
 * Bugfix, if no parameter found with that name.
 *
 * Revision 1.22  2005/03/31 09:14:35  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.21  2004/08/16 05:10:00  lollisoft
 * New error codes for database class
 *
 * Revision 1.20  2003/12/13 10:56:26  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.19  2003/11/27 23:20:01  lollisoft
 * Attempt to implement write access to databases
 *
 * Revision 1.18  2003/06/26 20:12:02  lollisoft
 * More error codes for db library
 *
 * Revision 1.17  2003/06/13 17:10:09  lollisoft
 * Added ERR_DB_FETCHNEXT
 *
 * Revision 1.16  2003/06/10 21:24:10  lollisoft
 * lbDB additions
 *
 * Revision 1.15  2002/12/29 16:09:29  lothar
 * Intent to go public
 *
 * Revision 1.14  2002/10/28 18:38:07  lothar
 * Current version works
 *
 * Revision 1.13  2002/09/07 09:57:10  lothar
 * First working callback function
 *
 * Revision 1.12  2002/08/21 18:51:48  lothar
 * New err code for event manager
 *
 * Revision 1.11  2002/04/15 18:25:16  lothar
 * Huge changes - works good
 *
 * Revision 1.10  2002/02/25 06:36:48  lothar
 * Added some codes
 *
 * Revision 1.9  2001/08/18 07:38:55  lothar
 * Current version runs again. Module management is not ready.
 *
 * Revision 1.8  2001/07/11 16:03:03  lothar
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.7  2001/05/01 15:51:49  lothar
 * First instance could be loaded over the new module management
 *
 * Revision 1.6  2001/03/30 20:08:05  lothar
 * Commit due to possible head crash on anakin (Linux)
 *
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
	ERR_FUNCTOR,

/* General error codes (semantics like function sequence handling) */

	ERR_FUNCTION_SEQUENCE,

/* Errcodes for reference counting */
	
	ERR_REFERENCE_COUNTING,
	ERR_INSTANCE_STILL_USED,
	// To see if the instance was deleted, not released
	ERR_RELEASED,

/* Errcodes for event manager */

	ERR_EVENT_EXISTS,
	ERR_EVENT_NOTREGISTERED,
	
/* Errcodes for dispatcher */

	ERR_DISP_HANDLER_EXSISTS,
	ERR_REGISTER_HANDLER,
	ERR_DISPATCH_FAILS,
	ERR_DISPATCH_PARAMETER_WRONG,

/* Errcodes for appbus dispatcher in connected state */

	ERR_APPBUS_DISPATCH, 		// Haeder found, but unknown identifer
	ERR_APPBUS_DISPATCH_HAEDER,	// No dispatch haeder found
	ERR_APPBUS_ECHO,		// Test server for echo


	ERR_NO_ENVIRONMENT,		// Any needed env var is not set

/* Module error codes */

	ERR_MODULE_INVALID_PARAMETER,
	ERR_MODULE_NOT_FOUND,
	ERR_FUNCTION_NOT_FOUND,
	ERR_MODULE_NO_INTERFACE,
	ERR_STATE_FURTHER_LOCK,		/**
					 * Object has increased refcount, but hasn't manager available.
					 * Object is locked!
					 */
	
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
	
/* Errcodes for threads */	
	LB_THREAD_ERROR,

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
	ERR_TRANSFER_PROTOCOL,
	
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
	ERR_SOCKET_CLOSED,

/* Errcodes for the database module */

	ERR_DB_EXECDIRECT,	
	ERR_DB_INIT,
	ERR_DB_ALLOCSTATEMENT,
	ERR_DB_QUERYFAILED,
	ERR_DB_UPDATEFAILED,
	ERR_DB_CONNECT,
	ERR_DB_FETCHFIRST,
	ERR_DB_FETCHLAST,
	ERR_DB_NODATA,
	ERR_DB_READONLY,
	ERR_DB_STILL_ADDING,
	ERR_DB_ROWDELETED,
	ERR_UPDATE_FAILED,
	WARN_DB_NODATA,
	INFO_DB_REOPENED,
	ERR_DB_COLUMN_NOT_FOUND,
	
/* Errcodes for parameter handling */	
	
	ERR_PARAM_NOT_FOUND,
	
	ERR_FILE_WRITE_DEFAULT,
	ERR_FILE_READ_DEFAULT,
	ERR_FILE_WRITE,
	ERR_FILE_READ,
	
	ERR_PLUGIN_NOT_INITIALIZED,
	
	ERR_MEMORY_ALLOC,
	
	ERR_UML_IMPORT_LOADDATABASE_MODUL
};
/*...e*/

#define LB_LOGFILE_MUTEX 1
#define LB_INPUTFILE_MUTEX 2
#define LB_OUTPUTFILE_MUTEX 3

#endif

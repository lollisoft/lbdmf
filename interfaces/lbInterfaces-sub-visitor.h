/*...sLicense:0:*/
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
 p-Mail: See my current address on http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=6
 
 */
/*...e*/

//#include <lbInterfaces-lbDMFManager.h>

/** \brief Stores version information.
 * The version information stored in a document is represented by this class. A versionable document is in most cases a composition of many elements.
 * As a sample the lb_I_Application may store many information that should be versionable. The application defines a storage namespace to define, who
 * is responsible for storing and loading the data. Different versions could be created over time. This should be detected.
 */
class lb_I_DocumentVersion :
public lb_I_Unknown
{
public:
	virtual void LB_STDCALL setInvalid() = 0;
	virtual bool LB_STDCALL isValidVersion() = 0;

	virtual void LB_STDCALL setData(lb_I_String* _Interface, lb_I_String* _Functor, lb_I_String* _Module, lb_I_String* _ModuleVersion, lb_I_String* _StoragePluginNamespace, lb_I_String* _StoragePluginVersion) = 0;

	virtual void LB_STDCALL setData(const char* _Interface, const char* _Functor, const char* _Module, const char* _ModuleVersion, const char* _StoragePluginNamespace, const char* _StoragePluginVersion) = 0;

	/** \brief Adding an interface lets automatically detect the correct composite container based on an interface.
	 * A case may be the loading of a document by double clicking it in the file explorer. Typically the file is linked
	 * to an application. But in the case of this framework and the intent to develop application prototypes, different
	 * logical applications may be loaded by the application using modules and their functors.
	 *
	 * For this case I need a module name, functor name and the interface.
	 */
	virtual lb_I_String* LB_STDCALL getInterface() = 0;
	
	/** \brief Get the functor that creates the instance to load the data into it.
	 * The functor creates an instance that must be passed to the visitor.
	 */
	virtual lb_I_String* LB_STDCALL getFunctor() = 0;
	
	/** \brief Get the module from where the instance comes to load the data into it.
	 * The functor creates an instance that must be passed to the visitor.
	 */
	virtual lb_I_String* LB_STDCALL getModule() = 0;
	
	/** \brief Get the module version.
	 * This is not yet supported by the module. It may be depend upon a SCM version tag like CVS. In conjunction with
	 * the storage plugin version it is a matching of correct participants.
	 */
	virtual lb_I_String* LB_STDCALL getModuleVersion() = 0;
	
	/** \brief The namespace of the storage handler.
	 * The namespace selects a generic storage mechanism, such as internal, XML or JSON.
	 * I don't yet know how to detect this format as I don't know how to then read the
	 * version information to become knowledge of that format. In the end it may be file
	 * extensions to identify that.
	 *
	 * Also, currently the XML and the JSON are used for import and export capabilities.
	 * They are not yet used for primary storage.
	 */
	virtual lb_I_String* LB_STDCALL getStoragePluginNamespace() = 0;
	
	/** \brief The version of the plugin.
	 * Also a plugin may have a version. Thechnically I should manage document versions manually and not with the SCM
	 * numbering at each commit, as this leads to much intermediate versions to match.
	 */
	virtual lb_I_String* LB_STDCALL getStoragePluginVersion() = 0;
};

/*...sclass lb_I_Aspect:0:*/
/** \brief Visitor base for all my interfaces.
 *
 * Implement a new class for a new operation such as save/load to/from file.
 *
 */
class lb_I_Aspect :
public lb_I_Unknown
{ // abstract interface for visitors 
public: 

	/** \brief Set the context in a form of a namespace.
	 * The context of the object means that an extension object of the given context should be used.
	 * If a visitor is called with an extensible object, it cannot handle the operation as it is unknown
	 * to the visitor. The context namespace the visitor is currently in should therefore taken to lookup
	 * the proper extension object that will handle the operation.
	 *
	 * For that operation to succeed it requires a mapping from the object (operator) to the extension object
	 * (operation) at runtime. Either the classname could be used or the interface the operator implements.
	 * As the operator currently is not capable to tell about the main interface, the classname must be used.
	 *
	 * To easily lookup an extension object by the context, it should be combined with the classname to form a
	 * new namespace that stands for the implementation of the specific extension object in question.
	 */
	virtual void setContextNamespace(const char* _namespace) = 0;

// The lb_I_Streamable interface would possibly go impossible
//virtual void LB_STDCALL visit(lb_I_Unknown*) { printf("Error: Catch all visitor called!\n"); }

virtual void LB_STDCALL visit(lb_I_DocumentVersion*) = 0;

virtual void LB_STDCALL visit(lb_I_SecurityProvider*) = 0;
virtual void LB_STDCALL visit(lb_I_LogonHandler*) = 0;
virtual void LB_STDCALL visit(lb_I_LogonPage*) = 0;     // Conflict with the catchall. Don't use MI.
virtual void LB_STDCALL visit(lb_I_AppSelectPage*) = 0; // As above
virtual void LB_STDCALL visit(lb_I_GUIApp*) = 0;        // This is the wxApp class !! ??
virtual void LB_STDCALL visit(lb_I_GUI*) = 0;
virtual void LB_STDCALL visit(lb_I_Frame*) = 0;
virtual void LB_STDCALL visit(lb_I_KeyBase*) = 0; 
virtual void LB_STDCALL visit(lb_I_Boolean*) = 0; 
virtual void LB_STDCALL visit(lb_I_String*) = 0; 
virtual void LB_STDCALL visit(lb_I_Integer*) = 0; 
virtual void LB_STDCALL visit(lb_I_Long*) = 0;
virtual void LB_STDCALL visit(lb_I_Container*) = 0; 
virtual void LB_STDCALL visit(lb_I_Database*) = 0; 
virtual void LB_STDCALL visit(lb_I_ColumnBinding*) = 0; 
virtual void LB_STDCALL visit(lb_I_BoundColumn*) = 0; 
virtual void LB_STDCALL visit(lb_I_Query*) = 0; 
virtual void LB_STDCALL visit(lb_I_MVC_View*) = 0; 
virtual void LB_STDCALL visit(lb_I_Connection*) = 0; 
virtual void LB_STDCALL visit(lb_I_InterfaceRepository*) = 0; 
virtual void LB_STDCALL visit(lb_I_Element*) = 0; 
virtual void LB_STDCALL visit(lb_I_Module*) = 0; 
virtual void LB_STDCALL visit(lb_I_FunctorEntity*) = 0;
virtual void LB_STDCALL visit(lb_I_InstanceReference*) = 0;
virtual void LB_STDCALL visit(lb_I_EventManager*) = 0;
virtual void LB_STDCALL visit(lb_I_EventMapper*) = 0;
virtual void LB_STDCALL visit(lb_I_Application*) = 0;
virtual void LB_STDCALL visit(lb_I_MetaApplication*) = 0;
virtual void LB_STDCALL visit(lb_I_EvHandler*) = 0;
virtual void LB_STDCALL visit(lb_I_Dispatcher*) = 0;
virtual void LB_STDCALL visit(lb_I_InputStream*) = 0;
virtual void LB_STDCALL visit(lb_I_OutputStream*) = 0;
virtual void LB_STDCALL visit(lb_I_FileOperation*) = 0;
virtual void LB_STDCALL visit(lb_I_Locale*) = 0;
virtual void LB_STDCALL visit(lb_I_Parameter*) = 0;
virtual void LB_STDCALL visit(lb_I_Reference*) = 0;
virtual void LB_STDCALL visit(lb_I_Log*) = 0;
virtual void LB_STDCALL visit(lb_I_Plugin*) = 0;
virtual void LB_STDCALL visit(lb_I_PluginImpl*) = 0;
virtual void LB_STDCALL visit(lb_I_PluginManager*) = 0;
virtual void LB_STDCALL visit(lb_I_PluginModule*) = 0;
virtual void LB_STDCALL visit(lb_I_wxFrame*) = 0;
virtual void LB_STDCALL visit(lb_I_Window*) = 0;
virtual void LB_STDCALL visit(lb_I_Form*) = 0;
virtual void LB_STDCALL visit(lb_I_MasterDetailFormDefinition*) = 0;
virtual void LB_STDCALL visit(lb_I_DatabaseReport*) = 0;
virtual void LB_STDCALL visit(lb_I_CodeGenerator*) = 0;
virtual void LB_STDCALL visit(lb_I_Streamable*) = 0;
virtual void LB_STDCALL visit(lb_I_DatabaseOperation*) = 0;

virtual void LB_STDCALL visit(lb_I_FileLocation*) = 0;
virtual void LB_STDCALL visit(lb_I_DirLocation*) = 0;
virtual void LB_STDCALL visit(lb_I_Socket*) = 0;
virtual void LB_STDCALL visit(lb_I_Transfer*) = 0;
virtual void LB_STDCALL visit(lb_I_Transfer_Data*) = 0;
virtual void LB_STDCALL visit(lb_I_Transfer_DataObject*) = 0;
virtual void LB_STDCALL visit(lb_I_Thread*) = 0;
virtual void LB_STDCALL visit(lb_I_Lock*) = 0;
virtual void LB_STDCALL visit(lb_I_Mutex*) = 0;
virtual void LB_STDCALL visit(lb_I_CriticalSection*) = 0;
	
	
virtual void LB_STDCALL visit(lb_I_ThreadImplementation*) = 0;
virtual void LB_STDCALL visit(lb_I_DispatchProtocol*) = 0;
virtual void LB_STDCALL visit(lb_I_ProtocolTarget*) = 0;
virtual void LB_STDCALL visit(lb_I_CallbackTarget*) = 0;
virtual void LB_STDCALL visit(lb_I_ProtocolManager*) = 0;
virtual void LB_STDCALL visit(lb_I_ApplicationServer*) = 0;
virtual void LB_STDCALL visit(lb_I_DispatchFunction*) = 0;
virtual void LB_STDCALL visit(lb_I_ApplicationClient*) = 0;
virtual void LB_STDCALL visit(lb_I_ApplicationServerThread*) = 0;
virtual void LB_STDCALL visit(lb_I_Proxy*) = 0;
virtual void LB_STDCALL visit(lb_I_DBColumns*) = 0;
virtual void LB_STDCALL visit(lb_I_DBTables*) = 0;
virtual void LB_STDCALL visit(lb_I_DBPrimaryKeys*) = 0;
virtual void LB_STDCALL visit(lb_I_DBForeignKeys*) = 0;

//virtual void LB_STDCALL visit(lb_I_DBReportProperties*) = 0;
//virtual void LB_STDCALL visit(lb_I_DBReportTextblock*) = 0;

// Entities that are generated, are of dynamic nature. They need a delegated visitor.
//#include <lbInterfaces-lbDMFManager-sub-visitor.h>

virtual void LB_STDCALL visit(lb_I_ExtensibleObject*) = 0;

virtual void LB_STDCALL visit(lb_I_BinaryData*) = 0;
virtual void LB_STDCALL visit(lb_I_TestMethod*) = 0;
virtual void LB_STDCALL visit(lb_I_TestFixture*) = 0;
virtual void LB_STDCALL visit(lb_I_CryptoStream*) = 0;
virtual void LB_STDCALL visit(lb_I_DispatchInterceptor*) = 0;
virtual void LB_STDCALL visit(lb_I_VisitableHelper*) = 0;
virtual void LB_STDCALL visit(lb_I_ExtensionObject*) = 0;
//virtual ~Aspect(){} 
};   
/*...e*/

/*...sclass lb_I_FileOperation:0:*/
/** \brief Base for any file operation.
 *
 * To be capable to operate on files, You need to open that file and close it.
 */
class lb_I_FileOperation :
public lb_I_Aspect
{
protected:
        lb_I_FileOperation() {}
        virtual ~lb_I_FileOperation() {}
        
public:
        /** \brief Start the operation.
         *
         * Starts a file operation by means of implementation. See lbInputStreanOpr or
         * lbOutputStreamOpr. They internally use lbInputStream and lbOutputStream.
         *
         * If a file operation is not started by calling begin. It can not be used, or
         * it should do nothing. 
         *
         * \param file  Provide a filename to internally create a file based stream.
         */
        virtual bool LB_STDCALL begin(const char* file) = 0;
        
        /** \brief Start the operation.
         *
         * Starts a file operation by means of implementation. See lbInputStreanOpr or
         * lbOutputStreamOpr. They internally use lbInputStream and lbOutputStream.
         *
         * If a file operation is not started by calling begin. It can not be used, or
         * it should do nothing. 
         *
         * \param stream        Provide an exsisting stream. To be used for cascaded operations.
         */
        virtual bool LB_STDCALL begin(lb_I_Stream* stream) = 0;
        
        /** \brief End the operation.
         *
         * This closes the file and disables the operation.
         */
        virtual void LB_STDCALL end() = 0;
        
        /** \brief Get access to stream.
         *
         * This allows storage handling for private data.
         */
        virtual lb_I_Stream* LB_STDCALL getStream() = 0;
};
/*...e*/

/*...sclass lb_I_DatabaseOperation:0:*/
class lb_I_DatabaseOperation :
public lb_I_Aspect
{
protected:
        lb_I_DatabaseOperation() {}
        virtual ~lb_I_DatabaseOperation() {}
        
public:
        /** \brief Start the operation.
         *
         * Start the database operation with the given parameters.
         */
        virtual bool LB_STDCALL begin(const char* connectionname, const char* DBName, const char* DBUser, const char* DBPass) = 0;
        
        /** \brief Start the operation.
         *
         * Start the database operation with the given database instance.
         */
        virtual bool LB_STDCALL begin(const char* connectionname, lb_I_Database* _db) = 0;
        
        /** \brief End the operation.
         *
         * This closes the file and disables the operation.
         */
        virtual void LB_STDCALL end() = 0;
        
        /** \brief Get access to the database.
         *
         * This allows storage handling for private data.
         */
        virtual lb_I_Database* LB_STDCALL getDatabase() = 0;
};
/*...e*/

/** \brief Extension for the visitor.
 * The visitor extension object is required to take responsibility to execute the operation in the context of the current viritor.
 * That is for sample saving to a stream, the extension does this for the current extended object.
 */
class lb_I_VisitorExtension : public lb_I_ExtensionObject {
public:
	virtual void LB_STDCALL setOperator(lb_I_Aspect* operation) = 0;
	virtual void LB_STDCALL execute() = 0;
};
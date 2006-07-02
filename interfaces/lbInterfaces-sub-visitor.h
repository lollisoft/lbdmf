/** \brief Visitor base for all my interfaces.
 *
 * Implement a new class for a new operation such as save/load to/from file.
 *
 */

class lb_I_Aspect :
public lb_I_Unknown
{ // abstract interface for visitors 
public: 

// The lb_I_Streamable interface would possibly go impossible
//virtual void LB_STDCALL visit(lb_I_Unknown*) { printf("Error: Catch all visitor called!\n"); }
virtual void LB_STDCALL visit(lb_I_LogonHandler*) = 0;
virtual void LB_STDCALL visit(lb_I_LogonPage*) = 0;     // Conflict with the catchall. Don't use MI.
virtual void LB_STDCALL visit(lb_I_AppSelectPage*) = 0; // As above
virtual void LB_STDCALL visit(lb_I_GUIApp*) = 0;        // This is the wxApp class !! ??
virtual void LB_STDCALL visit(lb_I_GUI*) = 0;
virtual void LB_STDCALL visit(lb_I_Frame*) = 0;
virtual void LB_STDCALL visit(lb_I_KeyBase*) = 0; 
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
virtual void LB_STDCALL visit(lb_I_Action*) = 0;
virtual void LB_STDCALL visit(lb_I_Form*) = 0;
virtual void LB_STDCALL visit(lb_I_MasterDetailFormDefinition*) = 0;
virtual void LB_STDCALL visit(lb_I_DelegatedAction*) = 0;
virtual void LB_STDCALL visit(lb_I_DatabaseReport*) = 0;
virtual void LB_STDCALL visit(lb_I_CodeGenerator*) = 0;
virtual void LB_STDCALL visit(lb_I_Streamable*) = 0;
virtual void LB_STDCALL visit(lb_I_DatabaseOperation*) = 0;
virtual void LB_STDCALL visit(lb_I_UserAccounts*) = 0;
virtual void LB_STDCALL visit(lb_I_Applications*) = 0;
virtual void LB_STDCALL visit(lb_I_User_Applications*) = 0;
virtual void LB_STDCALL visit(lb_I_Formulars*) = 0;
virtual void LB_STDCALL visit(lb_I_ParameterTable*) = 0;
virtual void LB_STDCALL visit(lb_I_ApplicationParameter*) = 0;
virtual void LB_STDCALL visit(lb_I_FormularParameter*) = 0;
virtual void LB_STDCALL visit(lb_I_Actions*) = 0;
virtual void LB_STDCALL visit(lb_I_Formular_Actions*) = 0;
virtual void LB_STDCALL visit(lb_I_Action_Types*) = 0;
virtual void LB_STDCALL visit(lb_I_Action_Steps*) = 0;
virtual void LB_STDCALL visit(lb_I_Translations*) = 0;
//virtual ~Aspect(){} 
};   

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
	 * \param file	Provide a filename to internally create a file based stream.
	 */
	virtual bool LB_STDCALL begin(char* file) = 0;
	
	/** \brief Start the operation.
	 *
	 * Starts a file operation by means of implementation. See lbInputStreanOpr or
	 * lbOutputStreamOpr. They internally use lbInputStream and lbOutputStream.
	 *
	 * If a file operation is not started by calling begin. It can not be used, or
	 * it should do nothing. 
	 *
	 * \param stream	Provide an exsisting stream. To be used for cascaded operations.
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
	virtual bool LB_STDCALL begin(const char* DBName, const char* DBUser, const char* DBPass) = 0;
	
	/** \brief Start the operation.
	 *
	 * Start the database operation with the given database instance.
	 */
	virtual bool LB_STDCALL begin(lb_I_Database* _db) = 0;
	
	/** \brief End the operation.
	 *
	 * This closes the file and disables the operation.
	 */
	virtual void LB_STDCALL end() = 0;
	
	/** \brief Get access to stream.
	 *
	 * This allows storage handling for private data.
	 */
	//virtual lb_I_Stream* LB_STDCALL getStream() = 0;
};

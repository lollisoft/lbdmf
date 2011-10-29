/*...sclass lb_I_UserAccounts:0:*/
class lb_I_UserAccounts : public lb_I_TableModule {
public:
	/** \brief Add an user account and get it's ID.
	 *
	 * This function only works, when a super user has already logged in.
	 * If there is no such user and no database available, the current user
	 * id would be used for a local super user.
	 *
	 * The database's stored super user has more priority over the local.
	 * Locally logged in super users didn't get access to the user accounts
	 * in the database. So if the database is back any how, the user must
	 * login to the database's super user.
	 *
	 * If the passwords are inconsistent and the database is available again,
	 * the user must login arain to the database's user.
	 *
	 * If all that is ok, the super user could transfer the users to the local
	 * copy of users.
	 *
	 * Any better solutions ?
	 *
	 * Parameters:
	 *
	 *		_id would be automatically generated, if no third parameter is given.
	 *		This is the case, when the new entry would be added from user interaction and
	 *		later stored in the database.
	 *
	 *		It would be the best to directly store the new entry in the database and retrieve
	 *		the id for furter linking of applications to users.
	 *
	 * Returns -1, if given id exists (then repeat without that id).
	 * Returns -2, if user exists.
	 */
	virtual long		LB_STDCALL addAccount(const char* _user, const char* _pass, long _id = -1) = 0;

	/** \brief Select current user.
	 *
	 * Direct access by the given login name.
	 */
	virtual bool		LB_STDCALL selectAccount(const char* _user) = 0;

	/** \brief Select current user.
	 *
	 * Direct access by the given user number.
	 */
	virtual bool		LB_STDCALL selectAccount(long user_id) = 0;

	/** \brief Get the number of users.
	 */
	virtual long		LB_STDCALL getUserCount() = 0;

	/** \brief Begin or indicate end of iteration.
	 */
	virtual bool		LB_STDCALL hasMoreUsers() = 0;

	/** \brief Iterate to next user.
	 */
	virtual void		LB_STDCALL setNextUser() = 0;

	/** \brief Stop iteration.
	 */
	virtual void		LB_STDCALL finishUserIteration() = 0;

	/** \brief Get current user name (iteration).
	 */
	virtual char*		LB_STDCALL getUserName() = 0;

	/** \brief Get current user password.
	 */
	virtual char*		LB_STDCALL getUserPassword() = 0;
};
/*...e*/

/*...sclass lb_I_Applications:0:*/
class lb_I_Applications : public lb_I_TableModule {
public:
	/** \brief Add a new application.
	 *
	 * The given _id is used for later linking of users to specific applications.
	 * Using _id's default value indicates a new entry in the database. Else a readout from stream/database.
	 * When using default id value, internally a 'virtual' id must be assigned, to be able to store relations.
	 *
	 * To avoid extra functions, these 'virtual' id's would be negative. This could be determined my the
	 * database stream handler.
	 */
	virtual long LB_STDCALL addApplication(const char* application, const char* titel, const char* modulename, const char* functor, const char* _interface, long _id = -1) = 0;

	/** \brief Select current application.
	 *
	 * Direct access by application name.
	 */
	virtual bool LB_STDCALL selectApplication(const char* application) = 0;

	/** \brief Select current application.
	 *
	 * Direct access by application id.
	 */
	virtual bool LB_STDCALL selectApplication(long _id) = 0;

	/** \brief Get the number of applications.
	 */
	virtual int LB_STDCALL getApplicationCount() = 0;

	/** \brief Begin or indicate end of iteration.
	 */
	virtual bool		LB_STDCALL hasMoreApplications() = 0;

	/** \brief Iterate to next application.
	 */
	virtual void		LB_STDCALL setNextApplication() = 0;

	/** \brief Stop iteration.
	 */
	virtual void		LB_STDCALL finishApplicationIteration() = 0;

	/** \brief Get current application name (iteration).
	 */
	virtual char*		LB_STDCALL getApplicationName() = 0;

	/** \brief Get current application name (iteration).
	 */
	virtual char*		LB_STDCALL getApplicationTitle() = 0;

	/** \brief Get current application name (iteration).
	 */
	virtual char*		LB_STDCALL getApplicationFunctor() = 0;

	/** \brief Get current application name (iteration).
	 */
	virtual char*		LB_STDCALL getApplicationModule() = 0;

	/** \brief Get current application name (iteration).
	 */
	virtual char*		LB_STDCALL getApplicationInterface() = 0;
};
/*...e*/

class lb_I_Applications_Formulars : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addRelation(long app_id, long form_id, long _id = -1) = 0;

	/** \brief Select relation by id.
	 */
	virtual bool		LB_STDCALL selectRelation(long _id) = 0;
	virtual int			LB_STDCALL getRelationCount() = 0;
	virtual bool		LB_STDCALL hasMoreRelations() = 0;
	virtual void		LB_STDCALL setNextRelation() = 0;
	virtual void		LB_STDCALL finishRelationIteration() = 0;

	virtual long		LB_STDCALL getApplicationID() = 0;
	virtual long		LB_STDCALL getFormularID() = 0;
};

/*...sclass lb_I_User_Applications:0:*/
class lb_I_User_Applications : public lb_I_TableModule {
public:
	/** \brief Add a new application.
	 *
	 * The given _id is used for later linking of users to specific applications.
	 * Using _id's default value indicates a new entry in the database. Else a readout from stream/database.
	 * When using default id value, internally a 'virtual' id must be assigned, to be able to store relations.
	 *
	 * To avoid extra functions, these 'virtual' id's would be negative. This could be determined my the
	 * database stream handler.
	 */
	virtual long LB_STDCALL addRelation(long app_id, long user_id, long _id = -1) = 0;

	/** \brief Select relation by id.
	 */
	virtual bool LB_STDCALL selectRelation(long _id) = 0;

	/** \brief Hide entities, not related to filter.
	 *
	 * Multiple filters are logically or'ed, but different filter names are and'ed.
	 */
	virtual bool LB_STDCALL addFilter(const char* filter, const char* value) = 0;

	/** \brief Remove filter.
	 *
	 * Removes all or specified filter(s).
	 */
	virtual bool LB_STDCALL resetFilter(const char* filter = "") = 0;

	/** \brief Get the number of applications.
	 */
	virtual int LB_STDCALL getRelationCount() = 0;

	/** \brief Begin or indicate end of iteration.
	 */
	virtual bool		LB_STDCALL hasMoreRelations() = 0;

	/** \brief Iterate to next application.
	 */
	virtual void		LB_STDCALL setNextRelation() = 0;

	/** \brief Stop iteration.
	 */
	virtual void		LB_STDCALL finishRelationIteration() = 0;

	/** \brief Get current applications id.
	 *
	 * Each application entry has an associated id.
	 */
	virtual long		LB_STDCALL getApplicationID() = 0;

	/** \brief Get current users id.
	 *
	 */
	virtual long		LB_STDCALL getUserID() = 0;

	virtual long		LB_STDCALL getID() = 0;
};
/*...e*/

/*...sclass lb_I_Formulars:0:*/
class lb_I_Formulars : public lb_I_TableModule {
public:
	/** \brief Ignore all other data.
	 *
	 * This will be used to ignore all data not from the specific application.
	 */
	//virtual void		LB_STDCALL setApplicationFilter(long anwendung_id) = 0;

	virtual long		LB_STDCALL addFormular(const char* name, const char* toolbarimage, const char* menuname, const char* eventname, const char* menuhilfe, long anwendung_id, long typ, long formular_id = -1) = 0;
	virtual bool		LB_STDCALL selectFormular(long _id) = 0;
	virtual int			LB_STDCALL getFormularCount() = 0;
	virtual bool		LB_STDCALL hasMoreFormulars() = 0;
	virtual void		LB_STDCALL setNextFormular() = 0;
	virtual void		LB_STDCALL finishFormularIteration() = 0;

	virtual char*		LB_STDCALL getName() = 0;
	virtual char*		LB_STDCALL getMenuName() = 0;
	virtual char*		LB_STDCALL getToolbarImage() = 0;
	virtual char*		LB_STDCALL getEventName() = 0;
	virtual char*		LB_STDCALL getMenuHelp() = 0;
	virtual long		LB_STDCALL getApplicationID() = 0;
	virtual long		LB_STDCALL getTyp() = 0;
};
/*...e*/

/*...sclass lb_I_Formulars:0:*/
class lb_I_Formular_Fields : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addField(const char* name, const char* tablename, const char* dbtype, bool isFK, const char* FKName, const char* FKTable, long formular_id, long fieldid = -1) = 0;
	virtual bool		LB_STDCALL selectField(long _id) = 0;
	virtual int			LB_STDCALL getFieldCount() = 0;
	virtual bool		LB_STDCALL hasMoreFields() = 0;
	virtual void		LB_STDCALL setNextField() = 0;
	virtual void		LB_STDCALL finishFieldsIteration() = 0;

	virtual char*		LB_STDCALL getName() = 0;
	virtual char*		LB_STDCALL getTableName() = 0;
	virtual char*		LB_STDCALL getDBType() = 0;
	virtual char*		LB_STDCALL getFKName() = 0;
	virtual char*		LB_STDCALL getFKTable() = 0;
	virtual long		LB_STDCALL getFormularID() = 0;
	virtual bool		LB_STDCALL isFK() = 0;
};
/*...e*/

/*...sclass lb_I_Formulars:0:*/
class lb_I_Column_Types : public lb_I_TableModule {
public:
	// const char* tablename, const char* name are together the logically key
	virtual long		LB_STDCALL addType(const char* tablename, const char* name, const char* specialcolumn, const char* controltype, bool readonly, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectType(const char* tablename, const char* name) = 0;
	virtual int			LB_STDCALL getTypeCount() = 0;
	virtual bool		LB_STDCALL hasMoreTypes() = 0;
	virtual void		LB_STDCALL setNextType() = 0;
	virtual void		LB_STDCALL finishTypeIteration() = 0;

	virtual char*		LB_STDCALL getTableName() = 0;
	virtual char*		LB_STDCALL getName() = 0;
	virtual char*		LB_STDCALL getSpecialColumn() = 0;
	virtual char*		LB_STDCALL getControlType() = 0;
	virtual bool		LB_STDCALL getReadonly() = 0;
};
/*...e*/


/*...sclass lb_I_ParameterTable:0:*/
class lb_I_ParameterTable : public lb_I_TableModule {
public:
	virtual bool		LB_STDCALL selectParameter(long _id) = 0;

	virtual int			LB_STDCALL getParameterCount() = 0;
	virtual bool		LB_STDCALL hasMoreParameters() = 0;
	virtual void		LB_STDCALL setNextParameter() = 0;
	virtual void		LB_STDCALL finishParameterIteration() = 0;

	virtual char*		LB_STDCALL getParameterName() = 0;
	virtual char*		LB_STDCALL getParameterValue() = 0;
};
/*...e*/

/*...sclass lb_I_FormularParameter:0:*/
class lb_I_FormularParameter : public lb_I_ParameterTable {
public:
	virtual long		LB_STDCALL addParameter(const char* name, const char* value, long formular_id, long _id = -1) = 0;
	virtual long		LB_STDCALL getFormularID() = 0;
	virtual char*		LB_STDCALL getParameter(const char* name, long formular_id) = 0;
};
/*...e*/

/*...sclass lb_I_ApplicationParameter:0:*/
class lb_I_ApplicationParameter : public lb_I_ParameterTable {
public:
	virtual long		LB_STDCALL addParameter(const char* name, const char* value, long anwendungs_id, long _id = -1) = 0;
	virtual long		LB_STDCALL getApplicationID() = 0;
	virtual char*		LB_STDCALL getParameter(const char* name, long application_id) = 0;
};
/*...e*/

/*...sclass lb_I_FKPK_Mapping:0:*/
class lb_I_FKPK_Mapping : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addMapping(const char* PKTable, const char* PKName, const char* FKTable, const char* FKName, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectMapping(long _id) = 0;
	virtual int			LB_STDCALL getMappingCount() = 0;
	virtual bool		LB_STDCALL hasMoreMappings() = 0;
	virtual void		LB_STDCALL setNextMapping() = 0;
	virtual void		LB_STDCALL finishMappingIteration() = 0;

	virtual char*		LB_STDCALL getPKTable() = 0;
	virtual char*		LB_STDCALL getPKName() = 0;
	virtual char*		LB_STDCALL getFKTable() = 0;
	virtual char*		LB_STDCALL getFKName() = 0;
};
/*...e*/

/*...sclass lb_I_Actions:0:*/
class lb_I_Actions : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addAction(const char* name, long typ, const char* source, long target, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectAction(long _id) = 0;
	virtual int			LB_STDCALL getActionCount() = 0;
	virtual bool		LB_STDCALL hasMoreActions() = 0;
	virtual void		LB_STDCALL setNextAction() = 0;
	virtual void		LB_STDCALL finishActionIteration() = 0;

	virtual long		LB_STDCALL getActionTyp() = 0;
	virtual long		LB_STDCALL getActionTarget() = 0;

	virtual char*		LB_STDCALL getActionSource() = 0;
	virtual char*		LB_STDCALL getActionName() = 0;
};
/*...e*/

/*...sclass lb_I_Action_Steps:0:*/
class lb_I_Action_Steps : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addActionStep(const char* bezeichnung, long actionid, long orderNo, long type, const char* what, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectActionStep(long _id) = 0;
	virtual int			LB_STDCALL getActionStepCount() = 0;
	virtual bool		LB_STDCALL hasMoreActionSteps() = 0;
	virtual void		LB_STDCALL setNextActionStep() = 0;
	virtual void		LB_STDCALL finishActionStepIteration() = 0;

	virtual long		LB_STDCALL getActionStepActionID() = 0;
	virtual long		LB_STDCALL getActionStepOrderNo() = 0;
	virtual long		LB_STDCALL getActionStepType() = 0;

	virtual char*		LB_STDCALL getActionStepBezeichnung() = 0;
	virtual char*		LB_STDCALL getActionStepWhat() = 0;
};
/*...e*/

/*...sclass lb_I_Action_Steps:0:*/
class lb_I_Action_Step_Transitions : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addTransition(const char* decision, long src_actionid, long dst_actionid, const char* description, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectTransition(long _id) = 0;
	virtual int			LB_STDCALL getActionStepTransitionsCount() = 0;
	virtual bool		LB_STDCALL hasMoreActionStepTransitions() = 0;
	virtual void		LB_STDCALL setNextActionStepTransition() = 0;
	virtual void		LB_STDCALL finishActionStepTransitionIteration() = 0;

	virtual long		LB_STDCALL getActionStepTransitionSrcActionID() = 0;
	virtual long		LB_STDCALL getActionStepTransitionDstActionID() = 0;

	virtual char*		LB_STDCALL getActionStepTransitionDecision() = 0;
	virtual char*		LB_STDCALL getActionStepTransitionDescription() = 0;
};
/*...e*/

/*...sclass lb_I_Action_Types:0:*/
class lb_I_Action_Types : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addActionTypes(const char* bezeichnung, const char* action_handler , const char* module, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectActionType(long _id) = 0;
	virtual int			LB_STDCALL getActionTypesCount() = 0;
	virtual bool		LB_STDCALL hasMoreActionTypes() = 0;
	virtual void		LB_STDCALL setNextActionType() = 0;
	virtual void		LB_STDCALL finishActionTypeIteration() = 0;

	virtual char*		LB_STDCALL getActionTypeBezeichnung() = 0;
	virtual char*		LB_STDCALL getActionTypeHandler() = 0;
	virtual char*		LB_STDCALL getActionTypeModule() = 0;
};
/*...e*/

/*...sclass lb_I_Action_Types:0:*/
class lb_I_Action_Parameters : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addActionParameter(const char* description, const char* name, const char* value, const char* _interface, long actionid, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectActionParameter(long _id) = 0;
	virtual int			LB_STDCALL getActionParametersCount() = 0;
	virtual bool		LB_STDCALL hasMoreActionParameters() = 0;
	virtual void		LB_STDCALL setNextActionParameter() = 0;
	virtual void		LB_STDCALL finishActionParameterIteration() = 0;

	virtual long		LB_STDCALL getActionParameterActionID() = 0;

	virtual char*		LB_STDCALL getActionParameterDescription() = 0;
	virtual char*		LB_STDCALL getActionParameterName() = 0;
	virtual char*		LB_STDCALL getActionParameterValue() = 0;
	virtual char*		LB_STDCALL getActionParameterInterface() = 0;
};
/*...e*/

/*...sclass lb_I_Action_Types:0:*/
class lb_I_ActionStep_Parameters : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addActionStepParameter(const char* description, const char* name, const char* value, const char* _interface, long actionid, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectActionStepParameter(long _id) = 0;
	virtual int			LB_STDCALL getActionStepParametersCount() = 0;
	virtual bool		LB_STDCALL hasMoreActionStepParameters() = 0;
	virtual void		LB_STDCALL setNextActionStepParameter() = 0;
	virtual void		LB_STDCALL finishActionStepParameterIteration() = 0;

	virtual long		LB_STDCALL getActionStepParameterActionID() = 0;

	virtual char*		LB_STDCALL getActionStepParameterDescription() = 0;
	virtual char*		LB_STDCALL getActionStepParameterName() = 0;
	virtual char*		LB_STDCALL getActionStepParameterValue() = 0;
	virtual char*		LB_STDCALL getActionStepParameterInterface() = 0;
};
/*...e*/

/*...sclass lb_I_Formular_Actions:0:*/
class lb_I_Formular_Actions : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addFormularAction(long formular, long action, const char* event, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectFormularAction(long _id) = 0;
	virtual int			LB_STDCALL getFormularActionsCount() = 0;
	virtual bool		LB_STDCALL hasMoreFormularActions() = 0;
	virtual void		LB_STDCALL setNextFormularAction() = 0;
	virtual void		LB_STDCALL finishFormularActionIteration() = 0;

	virtual long		LB_STDCALL getFormularActionFormularID() = 0;
	virtual long		LB_STDCALL getFormularActionActionID() = 0;

	virtual char*		LB_STDCALL getFormularActionEvent() = 0;
};
/*...e*/

/*...sclass lb_I_Translations:0:*/
class lb_I_Translations : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addTranslation(const char* text, const char* translated, const char* language, long _id = -1) = 0;
	virtual bool		LB_STDCALL selectTranslation(long _id) = 0;
	virtual bool		LB_STDCALL selectText(const char* text, const char* language) = 0;
	virtual int			LB_STDCALL getTranslationsCount() = 0;
	virtual bool		LB_STDCALL hasMoreTranslations() = 0;
	virtual void		LB_STDCALL setNextTranslation() = 0;
	virtual void		LB_STDCALL finishTranslationIteration() = 0;

	virtual char*		LB_STDCALL getTranslationText() = 0;
	virtual char*		LB_STDCALL getTranslationTranslated() = 0;
	virtual char*		LB_STDCALL getTranslationLanguage() = 0;
};
/*...e*/

/** \brief A class to store report information.
 *
 * This is the internal storage for report information. It will be used in the visitor plugin to transfer
 * the data between database meta information and internal file format or XML.
 */
class lb_I_Reports : public lb_I_TableModule {
public:
/// \todo Probably add a report type to add support for other reporting engines.
	virtual long		LB_STDCALL addReport(const char* name, const char* description, long _id = -1) = 0;

	virtual bool		LB_STDCALL selectReport(long _id) = 0;
	virtual int			LB_STDCALL getReportCount() = 0;
	virtual bool		LB_STDCALL hasMoreReports() = 0;
	virtual void		LB_STDCALL setNextReport() = 0;
	virtual void		LB_STDCALL finishReportIteration() = 0;

	virtual char*		LB_STDCALL getReportName() = 0;
	virtual char*		LB_STDCALL getReportDescription() = 0;
};

/** \brief A class to store report parameter information.
 *
 * This is the internal storage for report parameter information. It will be used in the visitor plugin to transfer
 * the data between database meta information and internal file format or XML.
 */
class lb_I_ReportParameters : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addParameter(long reportid, const char* name, const char* value, long _id = -1) = 0;

	virtual bool		LB_STDCALL selectParameter(long _id) = 0;
	virtual int			LB_STDCALL getParameterCount() = 0;
	virtual bool		LB_STDCALL hasMoreParameters() = 0;
	virtual void		LB_STDCALL setNextParameter() = 0;
	virtual void		LB_STDCALL finishParameterIteration() = 0;

	virtual long		LB_STDCALL getReportID() = 0;
	virtual char*		LB_STDCALL getParameterName() = 0;
	virtual char*		LB_STDCALL getParameterValue() = 0;
};

/** \brief A class to store report elements information.
 *
 * This is the internal storage for report elements information. It will be used in the visitor plugin to transfer
 * the data between database meta information and internal file format or XML.
 */
class lb_I_ReportElements : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addElement(long reportid, const char* name, long typ, long x, long y, long w, long h, const char* description, long _id = -1) = 0;

	virtual bool		LB_STDCALL selectElement(long _id) = 0;
	virtual int			LB_STDCALL getElementCount() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishElementIteration() = 0;

	virtual long		LB_STDCALL getElementReportID() = 0;
	virtual char*		LB_STDCALL getElementName() = 0;
	virtual char*		LB_STDCALL getElementDescription() = 0;
	virtual long		LB_STDCALL getElementTyp() = 0;
	virtual long		LB_STDCALL getElementX() = 0;
	virtual long		LB_STDCALL getElementY() = 0;
	virtual long		LB_STDCALL getElementW() = 0;
	virtual long		LB_STDCALL getElementH() = 0;
};

/** \brief A class to store report element types information.
 *
 * This is the internal storage for report element types information. It will be used in the visitor plugin to transfer
 * the data between database meta information and internal file format or XML.
 */
class lb_I_ReportElementTypes : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addElementType(const char* name, const char* description, long _id = -1) = 0;

	virtual bool		LB_STDCALL selectElementType(long _id) = 0;
	virtual int			LB_STDCALL getElementTypeCount() = 0;
	virtual bool		LB_STDCALL hasMoreElementTypes() = 0;
	virtual void		LB_STDCALL setNextElementType() = 0;
	virtual void		LB_STDCALL finishElementTypeIteration() = 0;

	virtual char*		LB_STDCALL getElementName() = 0;
	virtual char*		LB_STDCALL getElementDescription() = 0;
};

/** \brief A class to store report texts information.
 *
 * This is the internal storage for report texts information. It will be used in the visitor plugin to transfer
 * the data between database meta information and internal file format or XML.
 */
class lb_I_ReportTexts : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addText(long elementid, long line, const char* text, long _id = -1) = 0;

	virtual bool		LB_STDCALL selectText(long _id) = 0;
	virtual int			LB_STDCALL getTextCount() = 0;
	virtual bool		LB_STDCALL hasMoreTexts() = 0;
	virtual void		LB_STDCALL setNextText() = 0;
	virtual void		LB_STDCALL finishTextIteration() = 0;

	virtual char*		LB_STDCALL getText() = 0;
	virtual long		LB_STDCALL getLine() = 0;
	virtual long		LB_STDCALL getElementID() = 0;
};

/*...slbDMF Formular action interfaces:0:*/
/**
 * \brief This interface is intended as a way to delegate actions.
 *
 * Actions may be issued with buttons, validations or any other source like
 * timer events. The goal of this attempt is to abstract the action so it can
 * be simply used in a form without knowing the type of the action target.
 */
class lb_I_Action : public lb_I_VisitableHelper {
public:

	/** \brief Execute the action with the given parameter list.
	 */
	virtual void LB_STDCALL execute(lb_I_Parameter* params) = 0;

	/** \brief What is my action (from the database).
	 */
	virtual void LB_STDCALL setActionID(long id) = 0;
};

/// \todo Think about the interface name.
/**
 * \brief This interface is intended as a way to delegate action steps.
 *
 * Means, that the main action (lb_I_Action) could have multiple steps,
 * to be performed for one action, that may be visible with a button for
 * example.
 */
class lb_I_DelegatedAction : public lb_I_VisitableHelper {
public:
	/** \brief The delegated action.
	 * Initially this function did not give back a long value. Now the long value returned means the next
	 * action step (ID) to be executed. When -1 is returned a linear action is used and no 'jumps' are used
	 * for this action.
	 *
	 * If an ID other than -1 and 0 is returned the next step is the action step with the returned ID.
	 * If 0 is returned, the processing of the action will be stopped.
	 * A value other than -1 and 0 could be returned if there is given a transition object that describes the
	 * possible values returned.
	 */
	virtual long LB_STDCALL execute(lb_I_Parameter* params) = 0;
	virtual void LB_STDCALL setActionID(long id) = 0;
	/** \brief Set a transition object.
	 * Use this function to activate an action step than is non linear, thus it could have more than one outgoing
	 * transition.
	 *
	 * Nonlinear actionsteps are those you could create with an UML Activity diagram and translate it to the underlying
	 * datastructure representing the activity as an action with actionsteps.
	 *
	 * If an actionstep has transitions with expressions the used expression identifers must be passed in the params container to execute
	 * the expression (mostly this should be a boolean expression).
	 */
	virtual void LB_STDCALL setTransitions(lb_I_Action_Step_Transitions* myTransitions) = 0;

	/** \brief Each action step probably has some parameters.
	 * Some of the execution parameters are system parameters that do not have anything todo with bussiness logic.
	 * The current implementation of the passed parameter source field and source form are too weak. These parameters
	 * should be configured in the action parameters list and the code should pass them based on that configuration.
	 *
	 * Due to the two step implementation of actions and action steps and the truth that action steps sometimes need
	 * parameters passed trough from the action I define two different sets of action parameters. One for the action
	 * and one per action step.
	 *
	 * These action parameter sets are informations about what should be passed to the action or action step. It is not
	 * the instance of those parameters. The instances must be passed by the execute method.
	 */
	virtual void LB_STDCALL setParameter(lb_I_ActionStep_Parameters* myParams) = 0;

};
/*...e*/
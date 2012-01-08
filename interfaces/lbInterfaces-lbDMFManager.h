
class lb_I_Actions : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addActions(const char* _target, const char* _source, const char* _name, long _typ,  long _ActionsID = -1) = 0;

	virtual bool		LB_STDCALL selectActions(long _id) = 0;
	virtual int			LB_STDCALL getActionsCount() = 0;
	virtual bool		LB_STDCALL hasMoreActions() = 0;
	virtual void		LB_STDCALL setNextActions() = 0;
	virtual void		LB_STDCALL finishActionsIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_target() = 0;
			    virtual char* LB_STDCALL get_source() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			    virtual long LB_STDCALL get_typ() = 0;
	};

class lb_I_Action_Steps : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addAction_Steps(const char* _bezeichnung, const char* _what, long _a_order_nr, long _type, long _actionid,  long _Action_StepsID = -1) = 0;

	virtual bool		LB_STDCALL selectAction_Steps(long _id) = 0;
	virtual int			LB_STDCALL getAction_StepsCount() = 0;
	virtual bool		LB_STDCALL hasMoreAction_Steps() = 0;
	virtual void		LB_STDCALL setNextAction_Steps() = 0;
	virtual void		LB_STDCALL finishAction_StepsIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_bezeichnung() = 0;
			    virtual char* LB_STDCALL get_what() = 0;
			    virtual long LB_STDCALL get_a_order_nr() = 0;
			    virtual long LB_STDCALL get_type() = 0;
	    virtual long LB_STDCALL get_actionid() = 0;
	};

class lb_I_UserAccounts : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addUserAccounts(const char* _passwort, const char* _userid, const char* _vorname, const char* _name,  long _UserAccountsID = -1) = 0;

	virtual bool		LB_STDCALL selectUserAccounts(long _id) = 0;
	virtual int			LB_STDCALL getUserAccountsCount() = 0;
	virtual bool		LB_STDCALL hasMoreUserAccounts() = 0;
	virtual void		LB_STDCALL setNextUserAccounts() = 0;
	virtual void		LB_STDCALL finishUserAccountsIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_passwort() = 0;
			    virtual char* LB_STDCALL get_userid() = 0;
			    virtual char* LB_STDCALL get_vorname() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			};

class lb_I_Formulars : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addFormulars(const char* _name, const char* _menuname, const char* _menuhilfe, const char* _eventname, const char* _toolbarimage, long _anwendungid, long _typ,  long _FormularsID = -1) = 0;

	virtual bool		LB_STDCALL selectFormulars(long _id) = 0;
	virtual int			LB_STDCALL getFormularsCount() = 0;
	virtual bool		LB_STDCALL hasMoreFormulars() = 0;
	virtual void		LB_STDCALL setNextFormulars() = 0;
	virtual void		LB_STDCALL finishFormularsIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_menuname() = 0;
			    virtual char* LB_STDCALL get_menuhilfe() = 0;
			    virtual char* LB_STDCALL get_eventname() = 0;
			    virtual char* LB_STDCALL get_toolbarimage() = 0;
			    virtual long LB_STDCALL get_anwendungid() = 0;
	    virtual long LB_STDCALL get_typ() = 0;
	};

class lb_I_FormularParameter : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addFormularParameter(const char* _parametervalue, const char* _parametername, long _formularid,  long _FormularParameterID = -1) = 0;

	virtual bool		LB_STDCALL selectFormularParameter(long _id) = 0;
	virtual int			LB_STDCALL getFormularParameterCount() = 0;
	virtual bool		LB_STDCALL hasMoreFormularParameter() = 0;
	virtual void		LB_STDCALL setNextFormularParameter() = 0;
	virtual void		LB_STDCALL finishFormularParameterIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_parametervalue() = 0;
			    virtual char* LB_STDCALL get_parametername() = 0;
			    virtual long LB_STDCALL get_formularid() = 0;
	};

class lb_I_User_Applications : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addUser_Applications(long _userid, long _anwendungenid,  long _User_ApplicationsID = -1) = 0;

	virtual bool		LB_STDCALL selectUser_Applications(long _id) = 0;
	virtual int			LB_STDCALL getUser_ApplicationsCount() = 0;
	virtual bool		LB_STDCALL hasMoreUser_Applications() = 0;
	virtual void		LB_STDCALL setNextUser_Applications() = 0;
	virtual void		LB_STDCALL finishUser_ApplicationsIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_userid() = 0;
	    virtual long LB_STDCALL get_anwendungenid() = 0;
	};

class lb_I_Applications_Formulars : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addApplications_Formulars(long _anwendungid, long _formularid,  long _Applications_FormularsID = -1) = 0;

	virtual bool		LB_STDCALL selectApplications_Formulars(long _id) = 0;
	virtual int			LB_STDCALL getApplications_FormularsCount() = 0;
	virtual bool		LB_STDCALL hasMoreApplications_Formulars() = 0;
	virtual void		LB_STDCALL setNextApplications_Formulars() = 0;
	virtual void		LB_STDCALL finishApplications_FormularsIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_anwendungid() = 0;
	    virtual long LB_STDCALL get_formularid() = 0;
	};

class lb_I_Applications : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addApplications(const char* _titel, const char* _name, const char* _interface, const char* _functor, const char* _modulename,  long _ApplicationsID = -1) = 0;

	virtual bool		LB_STDCALL selectApplications(long _id) = 0;
	virtual int			LB_STDCALL getApplicationsCount() = 0;
	virtual bool		LB_STDCALL hasMoreApplications() = 0;
	virtual void		LB_STDCALL setNextApplications() = 0;
	virtual void		LB_STDCALL finishApplicationsIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_titel() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_interface() = 0;
			    virtual char* LB_STDCALL get_functor() = 0;
			    virtual char* LB_STDCALL get_modulename() = 0;
			};

class lb_I_Translations : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addTranslations(const char* _translated, const char* _text, const char* _language,  long _TranslationsID = -1) = 0;

	virtual bool		LB_STDCALL selectTranslations(long _id) = 0;
	virtual int			LB_STDCALL getTranslationsCount() = 0;
	virtual bool		LB_STDCALL hasMoreTranslations() = 0;
	virtual void		LB_STDCALL setNextTranslations() = 0;
	virtual void		LB_STDCALL finishTranslationsIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_translated() = 0;
			    virtual char* LB_STDCALL get_text() = 0;
			    virtual char* LB_STDCALL get_language() = 0;
			};

class lb_I_Formular_Actions : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addFormular_Actions(const char* _event, long _action, long _formular,  long _Formular_ActionsID = -1) = 0;

	virtual bool		LB_STDCALL selectFormular_Actions(long _id) = 0;
	virtual int			LB_STDCALL getFormular_ActionsCount() = 0;
	virtual bool		LB_STDCALL hasMoreFormular_Actions() = 0;
	virtual void		LB_STDCALL setNextFormular_Actions() = 0;
	virtual void		LB_STDCALL finishFormular_ActionsIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_event() = 0;
			    virtual long LB_STDCALL get_action() = 0;
	    virtual long LB_STDCALL get_formular() = 0;
	};

class lb_I_ApplicationParameter : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addApplicationParameter(const char* _parametername, const char* _parametervalue, long _anwendungid,  long _ApplicationParameterID = -1) = 0;

	virtual bool		LB_STDCALL selectApplicationParameter(long _id) = 0;
	virtual int			LB_STDCALL getApplicationParameterCount() = 0;
	virtual bool		LB_STDCALL hasMoreApplicationParameter() = 0;
	virtual void		LB_STDCALL setNextApplicationParameter() = 0;
	virtual void		LB_STDCALL finishApplicationParameterIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_parametername() = 0;
			    virtual char* LB_STDCALL get_parametervalue() = 0;
			    virtual long LB_STDCALL get_anwendungid() = 0;
	};

class lb_I_Reports : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addReports(const char* _description, const char* _name,  long _ReportsID = -1) = 0;

	virtual bool		LB_STDCALL selectReports(long _id) = 0;
	virtual int			LB_STDCALL getReportsCount() = 0;
	virtual bool		LB_STDCALL hasMoreReports() = 0;
	virtual void		LB_STDCALL setNextReports() = 0;
	virtual void		LB_STDCALL finishReportsIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_description() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			};

class lb_I_ReportParameters : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addReportParameters(long _value, const char* _name, long _reportid,  long _ReportParametersID = -1) = 0;

	virtual bool		LB_STDCALL selectReportParameters(long _id) = 0;
	virtual int			LB_STDCALL getReportParametersCount() = 0;
	virtual bool		LB_STDCALL hasMoreReportParameters() = 0;
	virtual void		LB_STDCALL setNextReportParameters() = 0;
	virtual void		LB_STDCALL finishReportParametersIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_value() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			    virtual long LB_STDCALL get_reportid() = 0;
	};

class lb_I_ReportElements : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addReportElements(const char* _name, const char* _description, long _x, long _y, long _w, long _h, long _reportid, long _typ,  long _ReportElementsID = -1) = 0;

	virtual bool		LB_STDCALL selectReportElements(long _id) = 0;
	virtual int			LB_STDCALL getReportElementsCount() = 0;
	virtual bool		LB_STDCALL hasMoreReportElements() = 0;
	virtual void		LB_STDCALL setNextReportElements() = 0;
	virtual void		LB_STDCALL finishReportElementsIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_description() = 0;
			    virtual long LB_STDCALL get_x() = 0;
			    virtual long LB_STDCALL get_y() = 0;
			    virtual long LB_STDCALL get_w() = 0;
			    virtual long LB_STDCALL get_h() = 0;
			    virtual long LB_STDCALL get_reportid() = 0;
	    virtual long LB_STDCALL get_typ() = 0;
	};

class lb_I_ReportElementTypes : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addReportElementTypes(const char* _name, const char* _description,  long _ReportElementTypesID = -1) = 0;

	virtual bool		LB_STDCALL selectReportElementTypes(long _id) = 0;
	virtual int			LB_STDCALL getReportElementTypesCount() = 0;
	virtual bool		LB_STDCALL hasMoreReportElementTypes() = 0;
	virtual void		LB_STDCALL setNextReportElementTypes() = 0;
	virtual void		LB_STDCALL finishReportElementTypesIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_description() = 0;
			};

class lb_I_ReportTexts : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addReportTexts(long _line, const char* _text, long _elementid,  long _ReportTextsID = -1) = 0;

	virtual bool		LB_STDCALL selectReportTexts(long _id) = 0;
	virtual int			LB_STDCALL getReportTextsCount() = 0;
	virtual bool		LB_STDCALL hasMoreReportTexts() = 0;
	virtual void		LB_STDCALL setNextReportTexts() = 0;
	virtual void		LB_STDCALL finishReportTextsIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_line() = 0;
			    virtual char* LB_STDCALL get_text() = 0;
			    virtual long LB_STDCALL get_elementid() = 0;
	};

class lb_I_Formular_Fields : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addFormular_Fields(const char* _fkname, const char* _fktable, const char* _dbtype, bool _isforeignkey, const char* _name, const char* _tablename, long _formularid,  long _Formular_FieldsID = -1) = 0;

	virtual bool		LB_STDCALL selectFormular_Fields(long _id) = 0;
	virtual int			LB_STDCALL getFormular_FieldsCount() = 0;
	virtual bool		LB_STDCALL hasMoreFormular_Fields() = 0;
	virtual void		LB_STDCALL setNextFormular_Fields() = 0;
	virtual void		LB_STDCALL finishFormular_FieldsIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_fkname() = 0;
			    virtual char* LB_STDCALL get_fktable() = 0;
			    virtual char* LB_STDCALL get_dbtype() = 0;
			    virtual bool LB_STDCALL get_isforeignkey() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_tablename() = 0;
			    virtual long LB_STDCALL get_formularid() = 0;
	};

class lb_I_Action_Step_Transitions : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addAction_Step_Transitions(const char* _expression, long _src_actionid, long _dst_actionid, const char* _description,  long _Action_Step_TransitionsID = -1) = 0;

	virtual bool		LB_STDCALL selectAction_Step_Transitions(long _id) = 0;
	virtual int			LB_STDCALL getAction_Step_TransitionsCount() = 0;
	virtual bool		LB_STDCALL hasMoreAction_Step_Transitions() = 0;
	virtual void		LB_STDCALL setNextAction_Step_Transitions() = 0;
	virtual void		LB_STDCALL finishAction_Step_TransitionsIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_expression() = 0;
			    virtual long LB_STDCALL get_src_actionid() = 0;
	    virtual long LB_STDCALL get_dst_actionid() = 0;
	    virtual char* LB_STDCALL get_description() = 0;
			};

class lb_I_Column_Types : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addColumn_Types(const char* _name, const char* _tablename, bool _ro, bool _specialcolumn, const char* _controltype,  long _Column_TypesID = -1) = 0;

	virtual bool		LB_STDCALL selectColumn_Types(long _id) = 0;
	virtual int			LB_STDCALL getColumn_TypesCount() = 0;
	virtual bool		LB_STDCALL hasMoreColumn_Types() = 0;
	virtual void		LB_STDCALL setNextColumn_Types() = 0;
	virtual void		LB_STDCALL finishColumn_TypesIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_tablename() = 0;
			    virtual bool LB_STDCALL get_ro() = 0;
			    virtual bool LB_STDCALL get_specialcolumn() = 0;
			    virtual char* LB_STDCALL get_controltype() = 0;
			};

class lb_I_FKPK_Mapping : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addFKPK_Mapping(const char* _pktable, const char* _pkname, const char* _fktable, const char* _fkname,  long _FKPK_MappingID = -1) = 0;

	virtual bool		LB_STDCALL selectFKPK_Mapping(long _id) = 0;
	virtual int			LB_STDCALL getFKPK_MappingCount() = 0;
	virtual bool		LB_STDCALL hasMoreFKPK_Mapping() = 0;
	virtual void		LB_STDCALL setNextFKPK_Mapping() = 0;
	virtual void		LB_STDCALL finishFKPK_MappingIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_pktable() = 0;
			    virtual char* LB_STDCALL get_pkname() = 0;
			    virtual char* LB_STDCALL get_fktable() = 0;
			    virtual char* LB_STDCALL get_fkname() = 0;
			};

class lb_I_Action_Types : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addAction_Types(const char* _bezeichnung, const char* _action_handler, const char* _module,  long _Action_TypesID = -1) = 0;

	virtual bool		LB_STDCALL selectAction_Types(long _id) = 0;
	virtual int			LB_STDCALL getAction_TypesCount() = 0;
	virtual bool		LB_STDCALL hasMoreAction_Types() = 0;
	virtual void		LB_STDCALL setNextAction_Types() = 0;
	virtual void		LB_STDCALL finishAction_TypesIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_bezeichnung() = 0;
			    virtual char* LB_STDCALL get_action_handler() = 0;
			    virtual char* LB_STDCALL get_module() = 0;
			};

class lb_I_Action_Parameters : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addAction_Parameters(const char* _name, const char* _value, const char* _interface, const char* _description, long _actionid,  long _Action_ParametersID = -1) = 0;

	virtual bool		LB_STDCALL selectAction_Parameters(long _id) = 0;
	virtual int			LB_STDCALL getAction_ParametersCount() = 0;
	virtual bool		LB_STDCALL hasMoreAction_Parameters() = 0;
	virtual void		LB_STDCALL setNextAction_Parameters() = 0;
	virtual void		LB_STDCALL finishAction_ParametersIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_value() = 0;
			    virtual char* LB_STDCALL get_interface() = 0;
			    virtual char* LB_STDCALL get_description() = 0;
			    virtual long LB_STDCALL get_actionid() = 0;
	};

class lb_I_ActionStep_Parameters : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addActionStep_Parameters(const char* _description, const char* _name, const char* _value, const char* _interface, long _action_step_id,  long _ActionStep_ParametersID = -1) = 0;

	virtual bool		LB_STDCALL selectActionStep_Parameters(long _id) = 0;
	virtual int			LB_STDCALL getActionStep_ParametersCount() = 0;
	virtual bool		LB_STDCALL hasMoreActionStep_Parameters() = 0;
	virtual void		LB_STDCALL setNextActionStep_Parameters() = 0;
	virtual void		LB_STDCALL finishActionStep_ParametersIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_description() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_value() = 0;
			    virtual char* LB_STDCALL get_interface() = 0;
			    virtual long LB_STDCALL get_action_step_id() = 0;
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

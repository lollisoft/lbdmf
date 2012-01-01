
class lb_I_Actions : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addActions(long typ, const char* _name, const char* _source, const char* _target,  long ActionsID = -1) = 0;
	virtual bool		LB_STDCALL selectActions(long _id) = 0;
	virtual int			LB_STDCALL getActionsCount() = 0;
	virtual bool		LB_STDCALL hasMoreActions() = 0;
	virtual void		LB_STDCALL setNextActions() = 0;
	virtual void		LB_STDCALL finishActionsIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_typ() = 0;
	    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_source() = 0;
			    virtual char* LB_STDCALL get_target() = 0;
			};

class lb_I_Action_Steps : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addAction_Steps(long actionid, long type, int _a_order_nr, const char* _what, const char* _bezeichnung,  long Action_StepsID = -1) = 0;
	virtual bool		LB_STDCALL selectAction_Steps(long _id) = 0;
	virtual int			LB_STDCALL getAction_StepsCount() = 0;
	virtual bool		LB_STDCALL hasMoreAction_Steps() = 0;
	virtual void		LB_STDCALL setNextAction_Steps() = 0;
	virtual void		LB_STDCALL finishAction_StepsIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_actionid() = 0;
	    virtual long LB_STDCALL get_type() = 0;
	    virtual int LB_STDCALL get_a_order_nr() = 0;
			    virtual char* LB_STDCALL get_what() = 0;
			    virtual char* LB_STDCALL get_bezeichnung() = 0;
			};

class lb_I_UserAccounts : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addUserAccounts(const char* _name, const char* _vorname, const char* _userid, const char* _passwort,  long UserAccountsID = -1) = 0;
	virtual bool		LB_STDCALL selectUserAccounts(long _id) = 0;
	virtual int			LB_STDCALL getUserAccountsCount() = 0;
	virtual bool		LB_STDCALL hasMoreUserAccounts() = 0;
	virtual void		LB_STDCALL setNextUserAccounts() = 0;
	virtual void		LB_STDCALL finishUserAccountsIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_vorname() = 0;
			    virtual char* LB_STDCALL get_userid() = 0;
			    virtual char* LB_STDCALL get_passwort() = 0;
			};

class lb_I_Formulars : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addFormulars(long typ, long anwendungid, const char* _toolbarimage, const char* _eventname, const char* _menuhilfe, const char* _menuname, const char* _name,  long FormularsID = -1) = 0;
	virtual bool		LB_STDCALL selectFormulars(long _id) = 0;
	virtual int			LB_STDCALL getFormularsCount() = 0;
	virtual bool		LB_STDCALL hasMoreFormulars() = 0;
	virtual void		LB_STDCALL setNextFormulars() = 0;
	virtual void		LB_STDCALL finishFormularsIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_typ() = 0;
	    virtual long LB_STDCALL get_anwendungid() = 0;
	    virtual char* LB_STDCALL get_toolbarimage() = 0;
			    virtual char* LB_STDCALL get_eventname() = 0;
			    virtual char* LB_STDCALL get_menuhilfe() = 0;
			    virtual char* LB_STDCALL get_menuname() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			};

class lb_I_FormularParameter : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addFormularParameter(long formularid, const char* _parametername, const char* _parametervalue,  long FormularParameterID = -1) = 0;
	virtual bool		LB_STDCALL selectFormularParameter(long _id) = 0;
	virtual int			LB_STDCALL getFormularParameterCount() = 0;
	virtual bool		LB_STDCALL hasMoreFormularParameter() = 0;
	virtual void		LB_STDCALL setNextFormularParameter() = 0;
	virtual void		LB_STDCALL finishFormularParameterIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_formularid() = 0;
	    virtual char* LB_STDCALL get_parametername() = 0;
			    virtual char* LB_STDCALL get_parametervalue() = 0;
			};

class lb_I_User_Applications : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addUser_Applications(long anwendungenid, long userid,  long User_ApplicationsID = -1) = 0;
	virtual bool		LB_STDCALL selectUser_Applications(long _id) = 0;
	virtual int			LB_STDCALL getUser_ApplicationsCount() = 0;
	virtual bool		LB_STDCALL hasMoreUser_Applications() = 0;
	virtual void		LB_STDCALL setNextUser_Applications() = 0;
	virtual void		LB_STDCALL finishUser_ApplicationsIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_anwendungenid() = 0;
	    virtual long LB_STDCALL get_userid() = 0;
	};

class lb_I_Applications_Formulars : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addApplications_Formulars(long formularid, long anwendungid,  long Applications_FormularsID = -1) = 0;
	virtual bool		LB_STDCALL selectApplications_Formulars(long _id) = 0;
	virtual int			LB_STDCALL getApplications_FormularsCount() = 0;
	virtual bool		LB_STDCALL hasMoreApplications_Formulars() = 0;
	virtual void		LB_STDCALL setNextApplications_Formulars() = 0;
	virtual void		LB_STDCALL finishApplications_FormularsIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_formularid() = 0;
	    virtual long LB_STDCALL get_anwendungid() = 0;
	};

class lb_I_Applications : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addApplications(const char* _modulename, const char* _functor, const char* _interface, const char* _name, const char* _titel,  long ApplicationsID = -1) = 0;
	virtual bool		LB_STDCALL selectApplications(long _id) = 0;
	virtual int			LB_STDCALL getApplicationsCount() = 0;
	virtual bool		LB_STDCALL hasMoreApplications() = 0;
	virtual void		LB_STDCALL setNextApplications() = 0;
	virtual void		LB_STDCALL finishApplicationsIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_modulename() = 0;
			    virtual char* LB_STDCALL get_functor() = 0;
			    virtual char* LB_STDCALL get_interface() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_titel() = 0;
			};

class lb_I_Uebersetzungen : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addUebersetzungen(const char* _text, const char* _translated,  long UebersetzungenID = -1) = 0;
	virtual bool		LB_STDCALL selectUebersetzungen(long _id) = 0;
	virtual int			LB_STDCALL getUebersetzungenCount() = 0;
	virtual bool		LB_STDCALL hasMoreUebersetzungen() = 0;
	virtual void		LB_STDCALL setNextUebersetzungen() = 0;
	virtual void		LB_STDCALL finishUebersetzungenIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_text() = 0;
			    virtual char* LB_STDCALL get_translated() = 0;
			};

class lb_I_Formular_Actions : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addFormular_Actions(long formular, long action, const char* _event,  long Formular_ActionsID = -1) = 0;
	virtual bool		LB_STDCALL selectFormular_Actions(long _id) = 0;
	virtual int			LB_STDCALL getFormular_ActionsCount() = 0;
	virtual bool		LB_STDCALL hasMoreFormular_Actions() = 0;
	virtual void		LB_STDCALL setNextFormular_Actions() = 0;
	virtual void		LB_STDCALL finishFormular_ActionsIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_formular() = 0;
	    virtual long LB_STDCALL get_action() = 0;
	    virtual char* LB_STDCALL get_event() = 0;
			};

class lb_I_ApplicationParameter : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addApplicationParameter(long anwendungid, const char* _parametername, const char* _parametervalue,  long ApplicationParameterID = -1) = 0;
	virtual bool		LB_STDCALL selectApplicationParameter(long _id) = 0;
	virtual int			LB_STDCALL getApplicationParameterCount() = 0;
	virtual bool		LB_STDCALL hasMoreApplicationParameter() = 0;
	virtual void		LB_STDCALL setNextApplicationParameter() = 0;
	virtual void		LB_STDCALL finishApplicationParameterIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_anwendungid() = 0;
	    virtual char* LB_STDCALL get_parametername() = 0;
			    virtual char* LB_STDCALL get_parametervalue() = 0;
			};

class lb_I_Reportdefinitionen : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addReportdefinitionen(const char* _name, const char* _description,  long ReportdefinitionenID = -1) = 0;
	virtual bool		LB_STDCALL selectReportdefinitionen(long _id) = 0;
	virtual int			LB_STDCALL getReportdefinitionenCount() = 0;
	virtual bool		LB_STDCALL hasMoreReportdefinitionen() = 0;
	virtual void		LB_STDCALL setNextReportdefinitionen() = 0;
	virtual void		LB_STDCALL finishReportdefinitionenIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_description() = 0;
			};

class lb_I_Reportparameter : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addReportparameter(long reportid, const char* _name, int _value,  long ReportparameterID = -1) = 0;
	virtual bool		LB_STDCALL selectReportparameter(long _id) = 0;
	virtual int			LB_STDCALL getReportparameterCount() = 0;
	virtual bool		LB_STDCALL hasMoreReportparameter() = 0;
	virtual void		LB_STDCALL setNextReportparameter() = 0;
	virtual void		LB_STDCALL finishReportparameterIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_reportid() = 0;
	    virtual char* LB_STDCALL get_name() = 0;
			    virtual int LB_STDCALL get_value() = 0;
			};

class lb_I_Formular_Fields : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addFormular_Fields(long formularid, const char* _tablename, const char* _name, bool _isforeignkey, const char* _dbtype, const char* _fktable, const char* _fkname,  long Formular_FieldsID = -1) = 0;
	virtual bool		LB_STDCALL selectFormular_Fields(long _id) = 0;
	virtual int			LB_STDCALL getFormular_FieldsCount() = 0;
	virtual bool		LB_STDCALL hasMoreFormular_Fields() = 0;
	virtual void		LB_STDCALL setNextFormular_Fields() = 0;
	virtual void		LB_STDCALL finishFormular_FieldsIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_formularid() = 0;
	    virtual char* LB_STDCALL get_tablename() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			    virtual bool LB_STDCALL get_isforeignkey() = 0;
			    virtual char* LB_STDCALL get_dbtype() = 0;
			    virtual char* LB_STDCALL get_fktable() = 0;
			    virtual char* LB_STDCALL get_fkname() = 0;
			};

class lb_I_Action_Step_Transitions : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addAction_Step_Transitions(const char* _description, long dst_actionid, long src_actionid, const char* _expression,  long Action_Step_TransitionsID = -1) = 0;
	virtual bool		LB_STDCALL selectAction_Step_Transitions(long _id) = 0;
	virtual int			LB_STDCALL getAction_Step_TransitionsCount() = 0;
	virtual bool		LB_STDCALL hasMoreAction_Step_Transitions() = 0;
	virtual void		LB_STDCALL setNextAction_Step_Transitions() = 0;
	virtual void		LB_STDCALL finishAction_Step_TransitionsIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_description() = 0;
			    virtual long LB_STDCALL get_dst_actionid() = 0;
	    virtual long LB_STDCALL get_src_actionid() = 0;
	    virtual char* LB_STDCALL get_expression() = 0;
			};

class lb_I_Column_Types : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addColumn_Types(const char* _controltype, bool _specialcolumn, bool _ro, const char* _tablename, const char* _name,  long Column_TypesID = -1) = 0;
	virtual bool		LB_STDCALL selectColumn_Types(long _id) = 0;
	virtual int			LB_STDCALL getColumn_TypesCount() = 0;
	virtual bool		LB_STDCALL hasMoreColumn_Types() = 0;
	virtual void		LB_STDCALL setNextColumn_Types() = 0;
	virtual void		LB_STDCALL finishColumn_TypesIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_controltype() = 0;
			    virtual bool LB_STDCALL get_specialcolumn() = 0;
			    virtual bool LB_STDCALL get_ro() = 0;
			    virtual char* LB_STDCALL get_tablename() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			};

class lb_I_FKPK_Mapping : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addFKPK_Mapping(const char* _fkname, const char* _fktable, const char* _pkname, const char* _pktable,  long FKPK_MappingID = -1) = 0;
	virtual bool		LB_STDCALL selectFKPK_Mapping(long _id) = 0;
	virtual int			LB_STDCALL getFKPK_MappingCount() = 0;
	virtual bool		LB_STDCALL hasMoreFKPK_Mapping() = 0;
	virtual void		LB_STDCALL setNextFKPK_Mapping() = 0;
	virtual void		LB_STDCALL finishFKPK_MappingIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_fkname() = 0;
			    virtual char* LB_STDCALL get_fktable() = 0;
			    virtual char* LB_STDCALL get_pkname() = 0;
			    virtual char* LB_STDCALL get_pktable() = 0;
			};

class lb_I_Action_Types : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addAction_Types(const char* _module, const char* _action_handler, const char* _bezeichnung,  long Action_TypesID = -1) = 0;
	virtual bool		LB_STDCALL selectAction_Types(long _id) = 0;
	virtual int			LB_STDCALL getAction_TypesCount() = 0;
	virtual bool		LB_STDCALL hasMoreAction_Types() = 0;
	virtual void		LB_STDCALL setNextAction_Types() = 0;
	virtual void		LB_STDCALL finishAction_TypesIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_module() = 0;
			    virtual char* LB_STDCALL get_action_handler() = 0;
			    virtual char* LB_STDCALL get_bezeichnung() = 0;
			};

class lb_I_Action_Parameters : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addAction_Parameters(const char* _description, const char* _interface, const char* _value, const char* _name,  long Action_ParametersID = -1) = 0;
	virtual bool		LB_STDCALL selectAction_Parameters(long _id) = 0;
	virtual int			LB_STDCALL getAction_ParametersCount() = 0;
	virtual bool		LB_STDCALL hasMoreAction_Parameters() = 0;
	virtual void		LB_STDCALL setNextAction_Parameters() = 0;
	virtual void		LB_STDCALL finishAction_ParametersIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_description() = 0;
			    virtual char* LB_STDCALL get_interface() = 0;
			    virtual char* LB_STDCALL get_value() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			};

class lb_I_ActionStep_Parameters : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL addActionStep_Parameters(long action_step_id, const char* _interface, const char* _value, const char* _name, const char* _description,  long ActionStep_ParametersID = -1) = 0;
	virtual bool		LB_STDCALL selectActionStep_Parameters(long _id) = 0;
	virtual int			LB_STDCALL getActionStep_ParametersCount() = 0;
	virtual bool		LB_STDCALL hasMoreActionStep_Parameters() = 0;
	virtual void		LB_STDCALL setNextActionStep_Parameters() = 0;
	virtual void		LB_STDCALL finishActionStep_ParametersIteration() = 0;

	virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_action_step_id() = 0;
	    virtual char* LB_STDCALL get_interface() = 0;
			    virtual char* LB_STDCALL get_value() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_description() = 0;
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

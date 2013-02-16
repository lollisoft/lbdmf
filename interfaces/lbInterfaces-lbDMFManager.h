
class lb_I_Actions : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(const char* _target, const char* _source, const char* _name, long _typ,  long _ActionsID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_target() = 0;
			    virtual char* LB_STDCALL get_source() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			    virtual long LB_STDCALL get_typ() = 0;
	};

class lb_I_Action_Steps : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(const char* _bezeichnung, const char* _what, long _a_order_nr, long _type, long _actionid,  long _Action_StepsID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

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
	virtual long		LB_STDCALL add(const char* _passwort, const char* _userid, const char* _vorname, const char* _name, const char* _secret,  long _UserAccountsID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_passwort() = 0;
			    virtual char* LB_STDCALL get_userid() = 0;
			    virtual char* LB_STDCALL get_vorname() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_secret() = 0;
			};

class lb_I_Formulars : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(const char* _name, const char* _menuname, const char* _menuhilfe, const char* _eventname, const char* _toolbarimage, long _anwendungid, long _typ,  long _FormularsID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

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
	virtual long		LB_STDCALL add(const char* _parametervalue, const char* _parametername, long _formularid,  long _FormularParameterID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_parametervalue() = 0;
			    virtual char* LB_STDCALL get_parametername() = 0;
			    virtual long LB_STDCALL get_formularid() = 0;
	};

class lb_I_User_Applications : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(long _userid, long _anwendungenid,  long _User_ApplicationsID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_userid() = 0;
	    virtual long LB_STDCALL get_anwendungenid() = 0;
	};

class lb_I_Applications_Formulars : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(long _anwendungid, long _formularid,  long _Applications_FormularsID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_anwendungid() = 0;
	    virtual long LB_STDCALL get_formularid() = 0;
	};

class lb_I_Applications : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(const char* _titel, const char* _name, const char* _interface, const char* _functor, const char* _modulename,  long _ApplicationsID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

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
	virtual long		LB_STDCALL add(const char* _translated, const char* _text, const char* _language,  long _TranslationsID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_translated() = 0;
			    virtual char* LB_STDCALL get_text() = 0;
			    virtual char* LB_STDCALL get_language() = 0;
			};

class lb_I_Formular_Actions : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(const char* _event, long _action, long _formular,  long _Formular_ActionsID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_event() = 0;
			    virtual long LB_STDCALL get_action() = 0;
	    virtual long LB_STDCALL get_formular() = 0;
	};

class lb_I_ApplicationParameter : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(const char* _parametername, const char* _parametervalue, long _anwendungid,  long _ApplicationParameterID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_parametername() = 0;
			    virtual char* LB_STDCALL get_parametervalue() = 0;
			    virtual long LB_STDCALL get_anwendungid() = 0;
	};

class lb_I_Reports : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(const char* _description, const char* _name,  long _ReportsID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_description() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			};

class lb_I_ReportParameters : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(long _value, const char* _name, long _reportid,  long _ReportParametersID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_value() = 0;
			    virtual char* LB_STDCALL get_name() = 0;
			    virtual long LB_STDCALL get_reportid() = 0;
	};

class lb_I_ReportElements : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(const char* _name, const char* _description, long _x, long _y, long _w, long _h, long _reportid, long _typ,  long _ReportElementsID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

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
	virtual long		LB_STDCALL add(const char* _name, const char* _description,  long _ReportElementTypesID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_name() = 0;
			    virtual char* LB_STDCALL get_description() = 0;
			};

class lb_I_ReportTexts : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(long _line, const char* _text, long _elementid,  long _ReportTextsID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual long LB_STDCALL get_line() = 0;
			    virtual char* LB_STDCALL get_text() = 0;
			    virtual long LB_STDCALL get_elementid() = 0;
	};

class lb_I_Formular_Fields : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(const char* _fkname, const char* _fktable, const char* _dbtype, bool _isforeignkey, const char* _name, const char* _tablename, long _formularid,  long _Formular_FieldsID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

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
	virtual long		LB_STDCALL add(const char* _expression, long _src_actionid, long _dst_actionid, const char* _description,  long _Action_Step_TransitionsID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_expression() = 0;
			    virtual long LB_STDCALL get_src_actionid() = 0;
	    virtual long LB_STDCALL get_dst_actionid() = 0;
	    virtual char* LB_STDCALL get_description() = 0;
			};

class lb_I_Column_Types : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(const char* _name, const char* _tablename, bool _ro, bool _specialcolumn, const char* _controltype,  long _Column_TypesID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

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
	virtual long		LB_STDCALL add(const char* _pktable, const char* _pkname, const char* _fktable, const char* _fkname,  long _FKPK_MappingID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_pktable() = 0;
			    virtual char* LB_STDCALL get_pkname() = 0;
			    virtual char* LB_STDCALL get_fktable() = 0;
			    virtual char* LB_STDCALL get_fkname() = 0;
			};

class lb_I_Action_Types : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(const char* _bezeichnung, const char* _action_handler, const char* _module,  long _Action_TypesID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

	// Derived from lb_I_TableModule
	//virtual long LB_STDCALL get_id() = 0;

    virtual char* LB_STDCALL get_bezeichnung() = 0;
			    virtual char* LB_STDCALL get_action_handler() = 0;
			    virtual char* LB_STDCALL get_module() = 0;
			};

class lb_I_Action_Parameters : public lb_I_TableModule {
public:
	virtual long		LB_STDCALL add(const char* _name, const char* _value, const char* _interface, const char* _description, long _actionid,  long _Action_ParametersID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

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
	virtual long		LB_STDCALL add(const char* _description, const char* _name, const char* _value, const char* _interface, long _action_step_id,  long _ActionStep_ParametersID = -1) = 0;

	virtual bool		LB_STDCALL selectById(long _id) = 0;
	virtual int			LB_STDCALL Count() = 0;
	virtual bool		LB_STDCALL hasMoreElements() = 0;
	virtual void		LB_STDCALL setNextElement() = 0;
	virtual void		LB_STDCALL finishIteration() = 0;

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

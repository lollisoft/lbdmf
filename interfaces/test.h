/*...sBEGIN_IMPLEMENT_LB_UNKNOWN:0:*/


#define BEGIN_IMPLEMENT_LB_UNKNOWN(classname) \
char* LB_STDCALL classname::getClassName() { \
	return #classname; \
} \
char* LB_STDCALL classname::_queryInterface(char* name, void** unknown, char* file, int line) { \
	static char ID[1000] = ""; \
	sprintf(ID, "FILE:%s,LINE:%d", file, line); \
	\
	lbErrCodes err = ERR_NONE; \
	if ((err = queryInterface(name, unknown, file, line)) != ERR_NONE) { \
		CL_LOG("Error: queryInterface failed (in _queryInterface)!") \
		return ""; \
	} \
	\
	return ID; \
} \
lb_I_Module* LB_STDCALL classname::getModuleManager() { \
		lbErrCodes err = ERR_NONE; \
		UAP(lb_I_Module, _mm, __FILE__, __LINE__) \
		if (manager == NULL) { \
			CL_LOG("Error: Can't return module manager. Call setModuleManager(...) on me first!"); \
			return NULL; \
		} \
		QI(manager, lb_I_Module, _mm, __FILE__, __LINE__) \
		return _mm.getPtr(); \
} \
\
void LB_STDCALL classname::setModuleManager(lb_I_Module* m, char* file, int line) { \
	if (m == NULL) { \
		char buf[100] = ""; \
		sprintf(buf, "Error: Set module manager with a NULL pointer in %s while setModuleManager(...)!", #classname); \
		CL_LOG(buf); \
		return; \
	} \
	\
	further_lock = 0; \
	if (debug_macro == 1) { \
		CL_LOG("Warning: setModuleManager() must be enhanced by module manager use"); \
	} \
	if (m != manager.getPtr()) m->queryInterface("lb_I_Module", (void**) &manager, file, line); \
	manager.setLine(__LINE__); \
	manager.setFile(__FILE__); \
	\
	if (manager != NULL) { \
		char *datei = strrchr(file, '\\'); \
		if (datei == NULL) \
			datei = file; \
		else \
			datei++; \
		manager->notify_create(this, #classname, datei, line); \
	} else { \
		char buf[100]; \
		sprintf(buf, "Error: Query interface failed for manager in %s while setModuleManager(...)!", #classname); \
		CL_LOG(buf) \
	} \
} \
\
void LB_STDCALL classname::resetRefcount() { ref = STARTREF; } \
int LB_STDCALL classname::deleteState() { \
	return (ref-1 == STARTREF) ? 1 : 0; \
} \
char*      LB_STDCALL classname::getCreationLoc() const { \
	char buf[20] = ""; \
	sprintf(buf, "%p", (void*) this); \
	if (manager != NULL) return manager->getCreationLoc(buf); \
	return strdup("Have no manager - location can't be found"); \
} \
lbErrCodes LB_STDCALL classname::release(char* file, int line) { \
        ref--; \
	char ptr[20] = ""; \
	sprintf(ptr, "%p", this); \
	if (strcmp(ptr, (get_trackObject() == NULL) ? "" : get_trackObject()) == 0) { \
		char buf[1000] = ""; \
		sprintf(buf, "Release interface for instance %s called (%d) at line %d in file %s\n", ptr, ref+1, line, file); \
		CL_LOG(buf); \
	} \
        if (manager != NULL) { \
        	manager->notify_release(this, #classname, file, line); \
        } \
	\
        if (ref == STARTREF) { \
        	if (manager != NULL) { \
        		if (manager->can_delete(this, #classname) == 1)	{ \
        			track_Object(this, "Tracked object will be deleted"); \
        			delete this; \
        			return ERR_RELEASED; \
        		} \
        		else \
        			CL_LOG("Error: Instance has been deleted prior!"); \
        	} \
        	return ERR_NONE; \
        } \
        char buf[1000] = ""; \
        if (ref < STARTREF) { \
        	sprintf(buf, "Error: Reference count of instance %p of object type %s is less than %d (%d) !!!", (void*) this, #classname, STARTREF, ref); \
        	CL_LOG(buf); \
        	return ERR_REFERENCE_COUNTING; \
        } \
        return ERR_INSTANCE_STILL_USED; \
} \
\
lb_I_Unknown* LB_STDCALL classname::clone(char* file, int line) const { \
\
	char ptr[20] = ""; \
	sprintf(ptr, "%p", (lb_I_Unknown*) this); \
	classname* cloned = new classname(__FILE__, __LINE__); \
	if (strcmp(ptr, (get_trackObject() == NULL) ? "" : get_trackObject()) == 0) { \
		char buf[1000] = ""; \
		sprintf(buf, "Clone instance %s called (references:%d) at line %d in file %s\n", ptr, ref+1, line, file); \
		CL_LOG(buf); \
	} \
	cloned->setDebug(0); \
	lb_I_Unknown* uk_this; \
	sprintf(ptr, "%p", (lb_I_Unknown*) cloned); \
	if (strcmp(ptr, (get_trackObject() == NULL) ? "" : get_trackObject()) == 0) { \
		char buf[1000] = ""; \
		sprintf(buf, "Cloned instance %s match tracked object (%d) at line %d in file %s.\nOrginal is %p", ptr, ref+1, line, file, (lb_I_Unknown*) this); \
		CL_LOG(buf); \
	} \
\
	lb_I_Unknown* uk_cloned = NULL; \
\
	cloned->setFurtherLock(0); \
	if (manager == NULL) CL_LOG(#classname "::clone() can't be used because manager is a NULL pointer!"); \
	cloned->setModuleManager(manager.getPtr(), file, line); \
	if (cloned->queryInterface("lb_I_Unknown", (void**) &uk_cloned, file, line) != ERR_NONE) { \
		CL_LOG("Error while getting interface"); \
	} \
\
	uk_cloned->setData((lb_I_Unknown*) this); \
\
	cloned->resetRefcount(); \
	\
	if (manager != NULL) { \
		lb_I_Unknown* that = (lb_I_Unknown*) cloned; \
	        manager->notify_add(that, cloned->getClassName(), file, line); \
	} \
        else \
		if (debug_macro == 1) { \
                	CL_LOG("Module manager was not set!"); \
		} \
	\
	lb_I_Unknown* uk = NULL; \
	if (uk_cloned->queryInterface("lb_I_Unknown", (void**) &uk, file, line) != ERR_NONE) { \
		CL_LOG("Error while getting unknown interface of cloned object"); \
	} \
\
	if (uk->getRefCount() > 1) { \
		char buf[1000] = ""; \
		sprintf(buf, "Cloned object has %d references\n", uk->getRefCount()); \
		CL_LOG(buf); \
	} \
	return uk; \
\
} \
\
lbErrCodes LB_STDCALL classname::queryInterface(char* name, void** unknown, char* file, int line) { \
	char buf[1000] = ""; \
	char iFaces[1000] = ""; \
	char _classname[100] = #classname; \
	if (further_lock == 1) { \
		CL_LOG("Error: Object has been locked due to missing module manager (call setModuleManager(...) on me first)!"); \
		return ERR_STATE_FURTHER_LOCK; \
	} \
	if (unknown == NULL) { \
		sprintf(buf, "Error: Got NULL pointer reference while queryInterface() called for %s ! Did you coded it this way: (void**) &variable ?", name); \
		CL_LOG(buf); \
	} \
\
	char ptr[20] = ""; \
	sprintf(ptr, "%p", this); \
	if (strcmp(ptr, (get_trackObject() == NULL) ? "" : get_trackObject()) == 0) { \
		sprintf(buf, "Query interface for instance %s called (%d) at line %d in file %s\n", ptr, ref+1, line, file); \
		CL_LOG(buf); \
	} \
\
	strcat(iFaces, "lb_I_Unknown, "); \
        if (strcmp(name, "lb_I_Unknown") == 0) { \
        	if (ref < STARTREF) { \
        		CL_LOG("Reference count error in queryInterface (" #classname ")"); \
        	} \
                ref++; \
                *unknown = (lb_I_Unknown*) this; \
                if (manager != NULL) { \
                	lb_I_Unknown* that = (lb_I_Unknown*) this; \
                	if (strcmp(_classname, "lbModule") == 0) { \
                		char buf[1000] = ""; \
                		sprintf(buf, "Register reference for %s in %s at %d", _classname, file, line); \
                		CL_LOG(buf) \
                	} \
		        manager->notify_add(that, _classname, file, line); \
		} \
		else { \
	        	setFurtherLock(1); \
	        	CL_LOG("Lock object due to missing manager!") \
	        	return ERR_STATE_FURTHER_LOCK; \
		} \
                return ERR_NONE; \
        }

/*...e*/

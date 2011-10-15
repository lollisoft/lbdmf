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
 p-Mail: See my current address on http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=6
 
 */
/*...e*/
/*...sincludes:0:*/
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#include <io.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#include <conio.h>

#include <json.h>
#include <json_helper.h>
        
#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#ifndef OSX
#include <malloc.h>
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
/*...e*/

/*...e*/

/*...slbJSONOutputStream:0:*/
/** \brief Implementation of JSON input stream.
 *
 * Implements lb_I_Aspect to allow getting calls from objects, I support.
 * Implements lb_I_FileOperation to specify, that this operation has to do
 * with files. Here loading from file.
 */
class lbJSONOutputStream : 
        public lb_I_FileOperation {
public:
        lbJSONOutputStream();
        virtual ~lbJSONOutputStream();
        
        DECLARE_LB_UNKNOWN()

/*...sUnimplemented visitors:8:*/
	void LB_STDCALL visit(lb_I_LogonHandler*) { _CL_LOG << "visit(lb_I_LogonHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_LogonPage*) { _CL_LOG << "visit(lb_I_LogonPage*)" LOG_ }
	void LB_STDCALL visit(lb_I_AppSelectPage*) { _CL_LOG << "visit(lb_I_AppSelectPage*)" LOG_ }
	void LB_STDCALL visit(lb_I_GUI*) { _CL_LOG << "visit(lb_I_GUI*)" LOG_ }
	void LB_STDCALL visit(lb_I_GUIApp*) { _CL_LOG << "visit(lb_I_GUIApp*)" LOG_ }
	void LB_STDCALL visit(lb_I_Frame*) { _CL_LOG << "visit(lb_I_Frame*)" LOG_ }
	void LB_STDCALL visit(lb_I_KeyBase*) { _CL_LOG << "visit(lb_I_KeyBase*)" LOG_ } 
	void LB_STDCALL visit(lb_I_String*); // { _CL_LOG << "visit(lb_I_String*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Integer*); // { _CL_LOG << "visit(lb_I_Integer*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Long*); //;{ _CL_LOG << "visit(lb_I_Long*)" LOG_ }
	void LB_STDCALL visit(lb_I_Container*) { _CL_LOG << "visit(lb_I_Container*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Database*) { _CL_LOG << "visit(lb_I_Database*)" LOG_ } 
	void LB_STDCALL visit(lb_I_ColumnBinding*) { _CL_LOG << "visit(lb_I_ColumnBinding*)" LOG_ } 
	void LB_STDCALL visit(lb_I_BoundColumn*) { _CL_LOG << "visit(lb_I_BoundColumn*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Query*) { _CL_LOG << "visit(lb_I_Query*)" LOG_ } 
	void LB_STDCALL visit(lb_I_MVC_View*) { _CL_LOG << "visit(lb_I_MVC_View*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Connection*) { _CL_LOG << "visit(lb_I_Connection*)" LOG_ } 
	void LB_STDCALL visit(lb_I_InterfaceRepository*) { _CL_LOG << "visit(lb_I_InterfaceRepository*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Element*) { _CL_LOG << "visit(lb_I_Element*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Module*) { _CL_LOG << "visit(lb_I_Module*)" LOG_ } 
	void LB_STDCALL visit(lb_I_FunctorEntity*) { _CL_LOG << "visit(lb_I_FunctorEntity*)" LOG_ }
	void LB_STDCALL visit(lb_I_InstanceReference*) { _CL_LOG << "visit(lb_I_InstanceReference*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventHandler*) { _CL_LOG << "visit(lb_I_EventHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventManager*) { _CL_LOG << "visit(lb_I_EventManager*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventMapper*) { _CL_LOG << "visit(lb_I_EventMapper*)" LOG_ }
	void LB_STDCALL visit(lb_I_EvHandler*) { _CL_LOG << "visit(lb_I_EvHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_Dispatcher*); // { _CL_LOG << "visit(lb_I_Dispatcher*)" LOG_ }
	void LB_STDCALL visit(lb_I_InputStream*) { _CL_LOG << "visit(lb_I_InputStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_OutputStream*) { _CL_LOG << "visit(lb_I_OutputStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_FileOperation*) { _CL_LOG << "visit(lb_I_FileOperation*)" LOG_ }
	void LB_STDCALL visit(lb_I_Locale*) { _CL_LOG << "visit(lb_I_Locale*)" LOG_ }
	void LB_STDCALL visit(lb_I_Parameter*); // { _CL_LOG << "visit(lb_I_Parameter*)" LOG_ }
	void LB_STDCALL visit(lb_I_Reference*) { _CL_LOG << "visit(lb_I_Reference*)" LOG_ }
	void LB_STDCALL visit(lb_I_Log*) { _CL_LOG << "visit(lb_I_Log*)" LOG_ }
	void LB_STDCALL visit(lb_I_Plugin*) { _CL_LOG << "visit(lb_I_Plugin*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginImpl*) { _CL_LOG << "visit(lb_I_PluginImpl*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginManager*) { _CL_LOG << "visit(lb_I_PluginManager*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginModule*) { _CL_LOG << "visit(lb_I_PluginModule*)" LOG_ }
	void LB_STDCALL visit(lb_I_wxFrame*) { _CL_LOG << "visit(lb_I_wxFrame*)" LOG_ }
	void LB_STDCALL visit(lb_I_Window*) { _CL_LOG << "visit(lb_I_Window*)" LOG_ }
	void LB_STDCALL visit(lb_I_Action*) { _CL_LOG << "visit(lb_I_Action*)" LOG_ }
	void LB_STDCALL visit(lb_I_DelegatedAction*) { _CL_LOG << "visit(lb_I_DelegatedAction*)" LOG_ }
	void LB_STDCALL visit(lb_I_Form*) { _CL_LOG << "visit(lb_I_Form*)" LOG_ }
	void LB_STDCALL visit(lb_I_MasterDetailFormDefinition*) { _CL_LOG << "visit(lb_I_MasterDetailFormDefinition*)" LOG_ }
	void LB_STDCALL visit(lb_I_DatabaseReport*) { _CL_LOG << "visit(lb_I_DatabaseReport*)" LOG_ }
	void LB_STDCALL visit(lb_I_CodeGenerator*) { _CL_LOG << "visit(lb_I_CodeGenerator*)" LOG_ }
	void LB_STDCALL visit(lb_I_Boolean*); // { _CL_LOG << "visit(lb_I_Boolean*)" LOG_ }
	void LB_STDCALL visit(lb_I_DatabaseOperation* pm) { _CL_LOG << "visit(lb_I_DatabaseOperation*)" LOG_ }
	void LB_STDCALL visit(lb_I_ParameterTable*) { _CL_LOG << "visit(lb_I_ParameterTable*)" LOG_ }
	void LB_STDCALL visit(lb_I_Socket*) { _CL_LOG << "visit(lb_I_Socket*)" LOG_ }
	void LB_STDCALL visit(lb_I_Transfer*) { _CL_LOG << "visit(lb_I_Transfer*)" LOG_ }
	void LB_STDCALL visit(lb_I_Transfer_Data*) { _CL_LOG << "visit(lb_I_Transfer_Data*)" LOG_ }
	void LB_STDCALL visit(lb_I_Transfer_DataObject*) { _CL_LOG << "visit(lb_I_Transfer_DataObject*)" LOG_ }
	void LB_STDCALL visit(lb_I_Thread*) { _CL_LOG << "visit(lb_I_Thread*)" LOG_ }
	void LB_STDCALL visit(lb_I_Mutex*) { _CL_LOG << "visit(lb_I_Mutex*)" LOG_ }
	void LB_STDCALL visit(lb_I_CriticalSection*) { _CL_LOG << "visit(lb_I_CriticalSection*)" LOG_ }
	void LB_STDCALL visit(lb_I_Lock*) { _CL_LOG << "visit(lb_I_Lock*)" LOG_ }
		
	void LB_STDCALL visit(lb_I_ThreadImplementation*) { _CL_LOG << "visit(lb_I_ThreadImplementation*)" LOG_ }
	void LB_STDCALL visit(lb_I_DispatchProtocol*) { _CL_LOG << "visit(lb_I_DispatchProtocol*)" LOG_ }
	void LB_STDCALL visit(lb_I_ProtocolTarget*) { _CL_LOG << "visit(lb_I_ProtocolTarget*)" LOG_ }
	void LB_STDCALL visit(lb_I_CallbackTarget*) { _CL_LOG << "visit(lb_I_CallbackTarget*)" LOG_ }
	void LB_STDCALL visit(lb_I_ProtocolManager*) { _CL_LOG << "visit(lb_I_ProtocolManager*)" LOG_ }
	void LB_STDCALL visit(lb_I_ApplicationServer*) { _CL_LOG << "visit(lb_I_ApplicationServer*)" LOG_ }
	void LB_STDCALL visit(lb_I_ApplicationServerThread*) { _CL_LOG << "visit(lb_I_ApplicationServerThread*)" LOG_ }
	void LB_STDCALL visit(lb_I_DispatchFunction*) { _CL_LOG << "visit(lb_I_DispatchFunction*)" LOG_ }
	void LB_STDCALL visit(lb_I_ApplicationClient*) { _CL_LOG << "visit(lb_I_ApplicationClient*)" LOG_ }
	void LB_STDCALL visit(lb_I_Proxy*) { _CL_LOG << "visit(lb_I_Proxy*)" LOG_ }
	void LB_STDCALL visit(lb_I_BinaryData*) { _CL_LOG << "visit(lb_I_BinaryData*)" LOG_ }
	void LB_STDCALL visit(lb_I_TestMethod*) { _CL_LOG << "visit(lb_I_TestMethod*)" LOG_ }
	void LB_STDCALL visit(lb_I_TestFixture*) { _CL_LOG << "visit(lb_I_TestFixture*)" LOG_ }
	void LB_STDCALL visit(lb_I_CryptoStream*) { _CL_LOG << "visit(lb_I_CryptoStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_DispatchInterceptor*) { _CL_LOG << "visit(lb_I_DispatchInterceptor*)" LOG_ }
	void LB_STDCALL visit(lb_I_VisitableHelper*) { _CL_LOG << "visit(lb_I_VisitableHelper*)" LOG_ }
/*...e*/
        
        void LB_STDCALL visit(lb_I_Streamable* pm);
        void LB_STDCALL visit(lb_I_Application*);
        void LB_STDCALL visit(lb_I_MetaApplication*);
        void LB_STDCALL visit(lb_I_UserAccounts*);
        void LB_STDCALL visit(lb_I_Applications*);
        void LB_STDCALL visit(lb_I_User_Applications*);
        void LB_STDCALL visit(lb_I_Formulars*);
        void LB_STDCALL visit(lb_I_Formular_Fields*);
        void LB_STDCALL visit(lb_I_Column_Types*);
        void LB_STDCALL visit(lb_I_ApplicationParameter*);
        void LB_STDCALL visit(lb_I_FormularParameter*);
        void LB_STDCALL visit(lb_I_Actions*);
        void LB_STDCALL visit(lb_I_Formular_Actions*);
        void LB_STDCALL visit(lb_I_Action_Types*);
        void LB_STDCALL visit(lb_I_Action_Steps*);
        void LB_STDCALL visit(lb_I_Translations*);
        void LB_STDCALL visit(lb_I_FileLocation*);
        void LB_STDCALL visit(lb_I_DirLocation*);
        void LB_STDCALL visit(lb_I_DBColumns*);
        void LB_STDCALL visit(lb_I_DBTables*);
        void LB_STDCALL visit(lb_I_DBPrimaryKeys*);
        void LB_STDCALL visit(lb_I_DBForeignKeys*);

        void LB_STDCALL visit(lb_I_DBReportTextblock*);
        void LB_STDCALL visit(lb_I_DBReportProperties*);

        void LB_STDCALL visit(lb_I_Reports*);
        void LB_STDCALL visit(lb_I_ReportParameters*);
        void LB_STDCALL visit(lb_I_ReportElements*);
        void LB_STDCALL visit(lb_I_ReportElementTypes*);
        void LB_STDCALL visit(lb_I_ReportTexts*);
        void LB_STDCALL visit(lb_I_Applications_Formulars*);
        void LB_STDCALL visit(lb_I_Action_Step_Transitions*);
        void LB_STDCALL visit(lb_I_ActionStep_Parameters*);
        void LB_STDCALL visit(lb_I_Action_Parameters*);

        /** \brief Create a new pair.
         * If a current value exisits, the current value is stored with the current name in current node.
         * A new current node is created and a name is attached to the node. The current value is set to NULL.
         * AddPair should be called before calling the operators to save the value for.
         *
         * A call sequence could look like this:
         *
         * AddPair("MainDocument") << "Name of the document";
         * AddArray("structuredData") << intVal1 << strVal1 << strVal2 << intVal2;
         * AddArray("MyUsers").AddPair("Name") << "Lothar".AddPair("Password") << "Lala";
         * AddArray("MyForms").AddPair("Name") << "Form1".AddPair("Param1") << "Value1".AddArray("Details") << "la1" << 1 << "bla1" << 2;
         */
        json_t* LB_STDCALL addPair(json_t* parent, char* name);
        
        json_t* LB_STDCALL addObject(json_t* parent, char* name);
                
                
        /** \brief Create a new array.
         * If a current value exisits, the current value is stored with the current name in current node.
         * A new current node is created and a name is attached to the node. The current value is set to a value of type array.
         */
        json_t* LB_STDCALL addArray(json_t* parent, char* name);
        
        // Basic json types to store
        lbJSONOutputStream& LB_STDCALL operator << (char*);
        lbJSONOutputStream& LB_STDCALL operator << (int);
        lbJSONOutputStream& LB_STDCALL operator << (long);
        lbJSONOutputStream& LB_STDCALL operator << (bool);

                
        /** \brief Start save operation.
         *
         * This initializes an input file stream with a given name.
         * For each object, you will save, call their accept() member function.
         */
        bool LB_STDCALL begin(const char* file);

        bool LB_STDCALL begin(lb_I_Stream* stream);

        
        /** \brief End save operation.
         *
         * This closes the file and thus disables visit members.
         */
        void LB_STDCALL end();
                
        lb_I_Stream* LB_STDCALL getStream();
        
        UAP(lb_I_OutputStream, oStream)
                
        /** \brief The root element.
         * This element stores all other elements, such as current node or currentarray.
         * Each element must be named or be a pair. Thus an array cannot stand alone.
         *
         * The structure of a JSON file can be as follows:
         * \pre

                 object
                         {}
                         { members }
                 members
                         pair
                         pair , members
                 pair
                         string : value
                 array
                         []
                         [ elements ]
                 elements
                         value 
                         value , elements
                 value
                         string
                         number
                         object
                         array
                         true
                         false
                         null

         */
        json_t* root;
                
        /** \brief The current node.
         * The current node is that node I currently operate on. At the beginning it is the root node.
         */
        json_t* currentnode;

        /** \brief The name of the current node.
         * Each node in root must be a pair. Thus it contains always named values.
         */
        json_t* currentname;    

        /** \brief The value of the current node.
         * Each node in root must be a pair. Thus it contains always named values.
         */
        json_t* currentvalue;
                
        json_t* currentobject;
        json_t* currentobjectname;
};
/*...e*/


BEGIN_IMPLEMENT_LB_UNKNOWN(lbJSONOutputStream)
        ADD_INTERFACE(lb_I_Aspect)
        ADD_INTERFACE(lb_I_FileOperation)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbJSONOutputStream, lbJSONOutputStream)


/*...slbErrCodes LB_STDCALL lbJSONOutputStream\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbJSONOutputStream::setData(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_NONE;
                
        _CL_LOG << "lbJSONOutputStream::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbJSONOutputStream\58\\58\lbJSONOutputStream\40\\41\:0:*/
lbJSONOutputStream::lbJSONOutputStream() 
{
        _CL_LOG << "lbJSONOutputStream::lbJSONOutputStream() called." LOG_
        
#ifndef __WATCOMC__
        setlocale (LC_ALL, ""); /// \todo Check is all platforms support this.
#endif
        root = json_new_object(); // Create the root note
        currentnode = currentname = currentobject = currentvalue = NULL;
}
/*...e*/
/*...slbJSONOutputStream\58\\58\\126\lbJSONOutputStream\40\\41\:0:*/
lbJSONOutputStream::~lbJSONOutputStream() {
        _CL_LOG << "lbJSONOutputStream::~lbJSONOutputStream() called." LOG_
}
/*...e*/

bool LB_STDCALL lbJSONOutputStream::begin(const char* file) {
        if (oStream == NULL) { 
                REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)
                
                oStream->setFileName(file);
                bool ret = oStream->open();

                if (!ret) {
                        _CL_LOG << "lbJSONOutputStream::begin(" << file << ") Error: Open file failed." LOG_
                }

                return ret;
        } else {
                _CL_LOG << "Error: lbJSONOutputStream::begin(...) called prior!" LOG_
        }
        
        return false;
}

bool LB_STDCALL lbJSONOutputStream::begin(lb_I_Stream* stream) {
        lbErrCodes err = ERR_NONE;
        if (stream != NULL) {
                _CL_LOG << "lbJSONOutputStream::begin(lb_I_Stream*): Got a stream (" << stream->getClassName() << ")." LOG_
                QI(stream, lb_I_OutputStream, oStream)
                bool ret = oStream->open();

                if (!ret) {
                        _CL_LOG << "lbJSONOutputStream::begin(lb_I_Stream* stream) Error: Open file failed." LOG_
                }
                
                return ret;
        } else {
                _CL_LOG << "lbJSONOutputStream::begin(lb_I_Stream* stream) Error: Uninitialized stream onject (NULL pointer)!" LOG_
        }
        
        return false;
}


void LB_STDCALL lbJSONOutputStream::visit(lb_I_Streamable* pm) {
        if (oStream != NULL) {
                // lb_I_Streamable is generic and selfsaving.
                pm->save(oStream.getPtr());
        } else {
                _CL_LOG << "lbJSONOutputStream::visit(lb_I_ProjectManager* pm) Error: No input stream available. Could not read from stream!" LOG_
        }

}

lbJSONOutputStream& LB_STDCALL lbJSONOutputStream::operator << (char* s) {
        if (currentnode != NULL) {
                json_t* value = json_new_string(s);
                if (json_insert_child(currentnode, value) != JSON_OK) {
                        _LOG << "lbJSONOutputStream::operator << (char*) Error: Failed inserting child." LOG_
                }
                if (currentnode->type != JSON_ARRAY) currentnode = NULL; // Only one object could be added
        } else {
                _LOG << "Error: Could not add an element." LOG_
        }
        
        return *this;
}

lbJSONOutputStream& LB_STDCALL lbJSONOutputStream::operator << (int i) {
        if (currentnode != NULL) {
                UAP_REQUEST(getModuleInstance(), lb_I_Integer, I)
                I->setData(i);
                json_t* value = json_new_number(I->charrep());
                if (json_insert_child(currentnode, value) != JSON_OK) {
                        _LOG << "lbJSONOutputStream::operator << (int) Error: Failed inserting child." LOG_
                }
                if (currentnode->type != JSON_ARRAY) currentnode = NULL; // Only one object could be added
        } else {
                _LOG << "Error: Could not add an element." LOG_
        }
        return *this;
}

lbJSONOutputStream& LB_STDCALL lbJSONOutputStream::operator << (long l) {
        if (currentnode != NULL) {
                UAP_REQUEST(getModuleInstance(), lb_I_Long, L)
                L->setData(l);
                json_t* value = json_new_number(L->charrep());
                if (json_insert_child(currentnode, value) != JSON_OK) {
                        _LOG << "lbJSONOutputStream::operator << (long) Error: Failed inserting child." LOG_
                }
                if (currentnode->type != JSON_ARRAY) currentnode = NULL; // Only one object could be added
        } else {
                _LOG << "Error: Could not add an element." LOG_
        }
        return *this;
}

lbJSONOutputStream& LB_STDCALL lbJSONOutputStream::operator << (bool b) {
        if (currentnode != NULL) {
                json_t* value = (b == true) ? json_new_true() : json_new_false();
                if (json_insert_child(currentnode, value) != JSON_OK) {
                        _LOG << "lbJSONOutputStream::operator << (bool) Error: Failed inserting child." LOG_
                }
                if (currentnode->type != JSON_ARRAY) currentnode = NULL; // Only one object could be added
        } else {
                _LOG << "Error: Could not add an element." LOG_
        }
        return *this;
}

json_t* LB_STDCALL lbJSONOutputStream::addArray(json_t* parent, char* name) {
        json_t* array = json_new_array();
        json_t* arrayname = json_new_string(name);
        
        if (json_insert_child(arrayname, array) != JSON_OK) {
                _LOG << "lbJSONOutputStream::addArray(" << name << ") Error: Failed inserting child." LOG_
        }

		if (parent->type == JSON_STRING) {
			json_t* object = json_new_object();
			if (json_insert_child(parent, object) != JSON_OK) {
				_LOG << "lbJSONOutputStream::addArray(" << name << ") Error: Failed inserting child." LOG_
			}
			if (json_insert_child(arrayname, array) != JSON_OK) {
				_LOG << "lbJSONOutputStream::addArray(" << name << ") Error: Failed inserting child." LOG_
			}
			if (json_insert_child(object, arrayname) != JSON_OK) {
				_LOG << "lbJSONOutputStream::addArray(" << name << ") Error: Failed inserting child." LOG_
			}
			return object;
		} else {
			if (json_insert_child(parent, arrayname) != JSON_OK) {
				_LOG << "lbJSONOutputStream::addArray(" << name << ") Error: Failed inserting child." LOG_
			}
		}
	
        
        return array;
}

json_t* LB_STDCALL lbJSONOutputStream::addPair(json_t* parent, char* name) {
        json_t* pair = json_new_string(name);
        if (json_insert_child(parent, pair) != JSON_OK) {
                _LOG << "lbJSONOutputStream::addPair(" << name << ") Error: Failed inserting child." LOG_
        }
        return pair;
}

json_t* LB_STDCALL lbJSONOutputStream::addObject(json_t* parent, char* name) {
        json_t* object = json_new_object();
        json_t* objectname = json_new_string(name);
        if (json_insert_child(object, objectname) != JSON_OK) {
                _LOG << "lbJSONOutputStream::addPair(" << name << ") Error: Failed inserting child." LOG_
        }
        if (json_insert_child(parent, object) != JSON_OK) {
                _LOG << "lbJSONOutputStream::addPair(" << name << ") Error: Failed inserting child." LOG_
        }
        return objectname;
}

/** \brief Store a boolean value.
 * If the current value element is NULL it will create an element of type JSON_TRUE or JSON_FALSE to be stored in the tree by you.
 * If the current value element is not NULL, it must be an array to enable storing subsequent elements easily.
 * 
 * That way you have to create an array before storing subsequent simply types or your call will fail in the second round.
 */
void LB_STDCALL lbJSONOutputStream::visit(lb_I_Boolean* b) {
        *this << (bool) b->getData();
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_String* s) {
        *this << s->charrep();
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Long* l) {
        *this << l->getData();
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Integer* i) {
        *this << i->getData();
}



void LB_STDCALL lbJSONOutputStream::visit(lb_I_ActionStep_Parameters* actionstepparameters) {
        int count;
        
        count = actionstepparameters->getActionStepParametersCount();
        *oStream << count;

        actionstepparameters->finishActionStepParameterIteration();
        
        while (actionstepparameters->hasMoreActionStepParameters()) {
                actionstepparameters->setNextActionStepParameter();
                
                *oStream << actionstepparameters->getActionStepParameterID();
                *oStream << actionstepparameters->getActionStepParameterActionID();
                
                *oStream << actionstepparameters->getActionStepParameterDescription();
                *oStream << actionstepparameters->getActionStepParameterName();
                *oStream << actionstepparameters->getActionStepParameterValue();
                *oStream << actionstepparameters->getActionStepParameterInterface();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Action_Parameters* actionparameters) {
        int count;
        
        count = actionparameters->getActionParametersCount();
        *oStream << count;
        
        actionparameters->finishActionParameterIteration();
        
        while (actionparameters->hasMoreActionParameters()) {
                actionparameters->setNextActionParameter();
                
                *oStream << actionparameters->getActionParameterID();
                *oStream << actionparameters->getActionParameterActionID();
                
                *oStream << actionparameters->getActionParameterDescription();
                *oStream << actionparameters->getActionParameterName();
                *oStream << actionparameters->getActionParameterValue();
                *oStream << actionparameters->getActionParameterInterface();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Applications_Formulars* applicationformulars) {
        int count;

        count = applicationformulars->getRelationCount();
        *oStream << count;
        
        applicationformulars->finishRelationIteration();
        
        while (applicationformulars->hasMoreRelations()) {
                applicationformulars->setNextRelation();
                
                *oStream << applicationformulars->getID();
                *oStream << applicationformulars->getApplicationID();
                *oStream << applicationformulars->getFormularID();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Parameter* params) {
    json_t* params_array = addArray((currentnode != NULL) ? currentnode : root, (char*)"lb_I_Parameter"); // Array with parameters, or recursive arrays
	
	if (params_array->type == JSON_OBJECT) {
		params_array = params_array->child->child;
	}
	
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, f)
	UAP_REQUEST(getModuleInstance(), lb_I_String, s)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, l)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)
	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, b)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, p)
	
	UAP(lb_I_Container, container)
	
	container = params->getParameterList();
	
	container->finishIteration();
	
	while (container->hasMoreElements()) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_KeyBase, key)
		uk = container->nextElement();
		key = container->currentKey();
		
		currentnode = addObject(params_array, key->charrep());
		
		if (strcmp(uk->getClassName(), p->getClassName()) == 0) {
			p->setData(*&uk);
			visit(*&p); // Recursive call
		}
		if (strcmp(uk->getClassName(), f->getClassName()) == 0) {
			f->setData(*&uk);
			visit(*&f);
		}
		if (strcmp(uk->getClassName(), s->getClassName()) == 0) {
			s->setData(*&uk);
			visit(*&s);
		}
		if (strcmp(uk->getClassName(), l->getClassName()) == 0) {
			l->setData(*&uk);
			visit(*&l);
		}
		if (strcmp(uk->getClassName(), i->getClassName()) == 0) {
			i->setData(*&uk);
			visit(*&l);
		}
		if (strcmp(uk->getClassName(), b->getClassName()) == 0) {
			b ->setData(*&uk);
			visit(*&b);
		}
		
	}
	
	
#ifdef bla      
	int count;
	
	count = params->Count();
	*oStream << count;
	
	UAP(lb_I_Container, container)
	
	container = params->getParameterList();
	
	if (count == 0) return;
	
	container->finishIteration();
	
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, f)
	UAP_REQUEST(getModuleInstance(), lb_I_String, s)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, l)
	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, b)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, p)
	
	while (container->hasMoreElements()) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_KeyBase, key)
		uk = container->nextElement();
		key = container->currentKey();
		
		*oStream << key->charrep();
		*oStream << uk->getClassName();
		
		_LOG << "Writing object name '" << key->charrep() << "' of type '" << uk->getClassName() << "'." LOG_ 
		
		if (strcmp(uk->getClassName(), p->getClassName()) == 0) {
			p->setData(*&uk);
			visit(*&p);
		}
		if (strcmp(uk->getClassName(), f->getClassName()) == 0) {
			f->setData(*&uk);
			visit(*&f);
		}
		if (strcmp(uk->getClassName(), s->getClassName()) == 0) {
			s->setData(*&uk);
			visit(*&s);
		}
		if (strcmp(uk->getClassName(), l->getClassName()) == 0) {
			l->setData(*&uk);
			visit(*&l);
		}
		if (strcmp(uk->getClassName(), b->getClassName()) == 0) {
			b ->setData(*&uk);
			visit(*&b);
		}
	}
#endif
}



void LB_STDCALL lbJSONOutputStream::visit(lb_I_Action_Step_Transitions* transition) {
        int count;

        count = transition->getActionStepTransitionsCount();
        *oStream << count;
        
        transition->finishActionStepTransitionIteration();
        
        while (transition->hasMoreActionStepTransitions()) {
                transition->setNextActionStepTransition();
                
                *oStream << transition->getActionStepTransitionID();
                *oStream << transition->getActionStepTransitionSrcActionID();
                *oStream << transition->getActionStepTransitionDstActionID();
                *oStream << transition->getActionStepTransitionDecision();
                *oStream << transition->getActionStepTransitionDescription();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Reports* reports) {
        int count;

        count = reports->getReportCount();
        *oStream << count;
        
        reports->finishReportIteration();
        
        while (reports->hasMoreReports()) {
                reports->setNextReport();
                
                *oStream << reports->getReportID();
                *oStream << reports->getReportName();
                *oStream << reports->getReportDescription();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_ReportParameters* reportparameters) {
        int count;

        count = reportparameters->getParameterCount();
        *oStream << count;
        
        reportparameters->finishParameterIteration();
        
        while (reportparameters->hasMoreParameters()) {
                reportparameters->setNextParameter();
                
                *oStream << reportparameters->getParameterID();
                *oStream << reportparameters->getReportID();
                *oStream << reportparameters->getParameterName();
                *oStream << reportparameters->getParameterValue();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_ReportElements* reportelements) {
        int count;

        count = reportelements->getElementCount();
        *oStream << count;
        
        reportelements->finishElementIteration();
        
        while (reportelements->hasMoreElements()) {
                reportelements->setNextElement();
                
                *oStream << reportelements->getElementID();
                *oStream << reportelements->getElementReportID();
                *oStream << reportelements->getElementName();
                *oStream << reportelements->getElementTyp();
                *oStream << reportelements->getElementX();
                *oStream << reportelements->getElementY();
                *oStream << reportelements->getElementW();
                *oStream << reportelements->getElementH();
                *oStream << reportelements->getElementDescription();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_ReportElementTypes* reportelementtypes) {
        int count;

        count = reportelementtypes->getElementTypeCount();
        *oStream << count;
        
        reportelementtypes->finishElementTypeIteration();
        
        while (reportelementtypes->hasMoreElementTypes()) {
                reportelementtypes->setNextElementType();
                
                *oStream << reportelementtypes->getElementID();
                *oStream << reportelementtypes->getElementName();
                *oStream << reportelementtypes->getElementDescription();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_ReportTexts* reporttexts) {
        int count;

        count = reporttexts->getTextCount();
        *oStream << count;
        
        reporttexts->finishTextIteration();
        
        while (reporttexts->hasMoreTexts()) {
                reporttexts->setNextText();
                
                *oStream << reporttexts->getID();
                *oStream << reporttexts->getElementID();
                *oStream << reporttexts->getLine();
                *oStream << reporttexts->getText();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_DBReportTextblock*) {

}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_DBReportProperties*) {

}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_UserAccounts* users) {
        int count;

        count = users->getUserCount();
        *oStream << count;
        
        users->finishUserIteration();
        
        while (users->hasMoreUsers()) {
                users->setNextUser();
                
                *oStream << users->getUserID();
                *oStream << users->getUserName();
                *oStream << users->getUserPassword();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_DBColumns* columns) {
        int count;

        count = columns->getColumnCount();
        *oStream << count;
        
        columns->finishColumnIteration();
        
        while (columns->hasMoreColumns()) {
                columns->setNextColumn();
                
                *oStream << columns->getColumnID();
                *oStream << columns->getColumnName();
                *oStream << columns->getColumnComment();
                *oStream << columns->getColumnTyp();
                *oStream << columns->getColumnLen();
                *oStream << columns->getColumnPKTable();
                *oStream << columns->getColumnPKField();
                *oStream << columns->getColumnTableName();
                (columns->isNullable() == true) ? *oStream << 1 : *oStream << 0;
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_DBTables* tables) {
        int count;

        count = tables->getTableCount();
        *oStream << count;
        
        tables->finishTableIteration();
        
        while (tables->hasMoreTables()) {
                tables->setNextTable();
                
                *oStream << tables->getTableID();
                *oStream << tables->getTableCatalog();
                *oStream << tables->getTableSchema();
                *oStream << tables->getTableName();
                *oStream << tables->getTableType();
                *oStream << tables->getTableRemarks();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_DBForeignKeys* fkeys) {
        int count;

        count = fkeys->getForeignKeyCount();
        *oStream << count;
        
        fkeys->finishForeignKeyIteration();
        
        while (fkeys->hasMoreForeignKeys()) {
                fkeys->setNextForeignKey();
                
                *oStream << fkeys->getForeignKeyID();
                
                *oStream << fkeys->getForeignKeyPKTableCatalog();
                *oStream << fkeys->getForeignKeyPKTableSchema();
                *oStream << fkeys->getForeignKeyPKTableName();
                *oStream << fkeys->getForeignKeyPKTableColumnName();
                
                *oStream << fkeys->getForeignKeyFKTableCatalog();
                *oStream << fkeys->getForeignKeyFKTableSchema();
                *oStream << fkeys->getForeignKeyFKTableName();
                *oStream << fkeys->getForeignKeyFKTableColumnName();
                
                *oStream << fkeys->getForeignKeyKeySequence();
                *oStream << fkeys->getForeignKeyUpdateRule();
                *oStream << fkeys->getForeignKeyDeleteRule();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_DBPrimaryKeys* pkeys) {
        int count;

        count = pkeys->getPrimaryKeyCount();
        *oStream << count;
        
        pkeys->finishPrimaryKeyIteration();
        
        while (pkeys->hasMorePrimaryKeys()) {
                pkeys->setNextPrimaryKey();
                
                *oStream << pkeys->getPrimaryKeyID();
                *oStream << pkeys->getPrimaryKeyTableCatalog();
                *oStream << pkeys->getPrimaryKeyTableSchema();
                *oStream << pkeys->getPrimaryKeyTableName();
                *oStream << pkeys->getPrimaryKeyColumnName();
                *oStream << pkeys->getPrimaryKeySequence();
                *oStream << pkeys->getPrimaryKeyColumnName_ODBC_V_2();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Translations* trans) {
        int count;

        count = trans->getTranslationsCount();
        *oStream << count;
        
        trans->finishTranslationIteration();
        
        while (trans->hasMoreTranslations()) {
                trans->setNextTranslation();
                
                *oStream << trans->getTranslationID();
                *oStream << trans->getTranslationText();
                *oStream << trans->getTranslationTranslated();
                *oStream << trans->getTranslationLanguage();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_FormularParameter* forms) {
        int count;

        count = forms->getParameterCount();
        *oStream << count;
        
        forms->finishParameterIteration();
        
        while (forms->hasMoreParameters()) {
                forms->setNextParameter();
                
                *oStream << forms->getParameterID();
                *oStream << forms->getParameterName();
                *oStream << forms->getParameterValue();
                *oStream << forms->getFormularID();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Actions* actions) {
        int count;

        count = actions->getActionCount();
        *oStream << count;
        
        actions->finishActionIteration();
        
        while (actions->hasMoreActions()) {
                actions->setNextAction();
                
                *oStream << actions->getActionID();
                *oStream << actions->getActionName();
                *oStream << actions->getActionSource();
                *oStream << actions->getActionTyp();
                *oStream << actions->getActionTarget();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Action_Steps* action_steps) {
        int count;

        count = action_steps->getActionStepCount();
        *oStream << count;

        _LOG << "lbJSONOutputStream::visit(lb_I_Action_Steps* action_steps) called." LOG_

        action_steps->finishActionStepIteration();
        
        while (action_steps->hasMoreActionSteps()) {
                action_steps->setNextActionStep();

                _LOG << "lbJSONOutputStream::visit(lb_I_Action_Steps* action_steps) writes an entry." LOG_
                
                *oStream << action_steps->getActionStepID();
                *oStream << action_steps->getActionStepActionID();
                *oStream << action_steps->getActionStepOrderNo();
                *oStream << action_steps->getActionStepType();
                *oStream << action_steps->getActionStepBezeichnung();
                *oStream << action_steps->getActionStepWhat();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Action_Types* action_types) {
        int count;

        count = action_types->getActionTypesCount();
        *oStream << count;
        
        action_types->finishActionTypeIteration();
        
        while (action_types->hasMoreActionTypes()) {
                action_types->setNextActionType();
                
                *oStream << action_types->getActionTypeID();
                *oStream << action_types->getActionTypeBezeichnung();
                *oStream << action_types->getActionTypeHandler();
                *oStream << action_types->getActionTypeModule();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Formular_Actions* formular_actions) {
        int count;

        count = formular_actions->getFormularActionsCount();
        *oStream << count;
        
        formular_actions->finishFormularActionIteration();
        
        while (formular_actions->hasMoreFormularActions()) {
                formular_actions->setNextFormularAction();
                
                *oStream << formular_actions->getFormularActionID();
                *oStream << formular_actions->getFormularActionFormularID();
                *oStream << formular_actions->getFormularActionActionID();
                *oStream << formular_actions->getFormularActionEvent();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_FileLocation* fileloc) {
                *oStream << fileloc->charrep();
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_DirLocation* fileloc) {
                *oStream << fileloc->charrep();
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_ApplicationParameter* apps) {
        int count;

        count = apps->getParameterCount();
        *oStream << count;
        
        apps->finishParameterIteration();
        
        while (apps->hasMoreParameters()) {
                apps->setNextParameter();
                
                *oStream << apps->getParameterID();
                *oStream << apps->getParameterName();
                *oStream << apps->getParameterValue();
                *oStream << apps->getApplicationID();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Formulars* forms) {
        int count;

        count = forms->getFormularCount();
        *oStream << count;
        
        forms->finishFormularIteration();
        
        while (forms->hasMoreFormulars()) {
                forms->setNextFormular();
                
                *oStream << forms->getFormularID();
                *oStream << forms->getName();
                *oStream << forms->getMenuName();
                *oStream << forms->getEventName();
                *oStream << forms->getMenuHelp();
                *oStream << forms->getApplicationID();
                *oStream << forms->getTyp();
                *oStream << forms->getToolbarImage();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Formular_Fields* formularfields) {
        int count;

        count = formularfields->getFieldCount();
        *oStream << count;
        
        formularfields->finishFieldsIteration();
        
        while (formularfields->hasMoreFields()) {
                formularfields->setNextField();
                
                *oStream << formularfields->getID();
                *oStream << formularfields->getName();
                *oStream << formularfields->getTableName();
                *oStream << formularfields->getDBType();
                if (formularfields->isFK())
                        *oStream << (long) 1;
                else
                        *oStream << (long) 0;
                *oStream << formularfields->getFKName();
                *oStream << formularfields->getFKTable();
                *oStream << formularfields->getFormularID();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Column_Types* columntypes) {
        int count;

        count = columntypes->getTypeCount();
        *oStream << count;
        
        columntypes->finishTypeIteration();
        
        while (columntypes->hasMoreTypes()) {
                columntypes->setNextType();
                
                *oStream << columntypes->getTableName();
                *oStream << columntypes->getName();
                *oStream << columntypes->getSpecialColumn();
                *oStream << columntypes->getControlType();
                if (columntypes->getReadonly() == true) 
                        *oStream << (long) 1;
                else
                        *oStream << (long) 0;
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Applications* app) {
        int count;

        count = app->getApplicationCount();
        *oStream << count;
        
        app->finishApplicationIteration();
        
        while (app->hasMoreApplications()) {
                app->setNextApplication();
                
                _CL_LOG << "Save application: '" << app->getApplicationName() << 
                "', title: '" << app->getApplicationTitle() <<
                "', module: '" << app->getApplicationModule() <<
                "', functor: '" << app->getApplicationFunctor() <<
                "', interface: '" << app->getApplicationInterface()
                  LOG_
                
                *oStream << app->getApplicationID();
                *oStream << app->getApplicationName();
                *oStream << app->getApplicationTitle();
                *oStream << app->getApplicationModule();
                *oStream << app->getApplicationFunctor();
                *oStream << app->getApplicationInterface();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_User_Applications* app) {
        int count;

        count = app->getRelationCount();
        *oStream << count;
        
        app->finishRelationIteration();
        
        while (app->hasMoreRelations()) {
                app->setNextRelation();
                
                *oStream << app->getID();
                *oStream << app->getUserID();
                *oStream << app->getApplicationID();
        }
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_MetaApplication* app) {
        _LOG << "Save a lb_I_MetaApplication object." LOG_

        UAP_REQUEST(getModuleInstance(), lb_I_String, temp)
        bool  b;
        int count;

        b = app->getAutorefreshData();
        *oStream << b;

        app->getApplicationName(&temp);
        *oStream << temp->charrep();

        app->getUserName(&temp);
        *oStream << temp->charrep();

        b = app->getAutoload();
        *oStream << b;

        b = app->getAutoselect();
        *oStream << b;

        b = app->getGUIMaximized();
        *oStream << b;
        
        *oStream << app->getDirLocation();
        
        *oStream << app->isPropertyPaneLayoutFloating();
        
        *oStream << app->isPropertyPaneLayoutLeft();

        *oStream << app->getLoadFromDatabase();
        
        *oStream << app->getApplicationDatabaseBackend();

        *oStream << app->getSystemDatabaseBackend();

        *oStream << app->usingApplicationDatabaseBackend();

        *oStream << app->usingSystemDatabaseBackend();

}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Dispatcher* disp) {
        UAP_REQUEST(getModuleInstance(), lb_I_String, temp)
        temp = disp->getInterceptorDefinitions();
        *oStream << temp->charrep();
}

void LB_STDCALL lbJSONOutputStream::visit(lb_I_Application*) {
        _CL_LOG << "Save a lb_I_Application object." LOG_
        
        lbErrCodes err = ERR_NONE;
        
        // Get the document via the active document from meta application.
        // This way no extra interface is needed (container with named elements)
        
        UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
        UAP_REQUEST(getModuleInstance(), lb_I_String, param)
        UAP_REQUEST(getModuleInstance(), lb_I_String, StorageInterface)
        UAP_REQUEST(getModuleInstance(), lb_I_String, StorageNamespace)
        
        UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
        UAP(lb_I_Plugin, pl)
        UAP(lb_I_Unknown, ukPl)
        
        UAP(lb_I_Unknown, ukDoc)
        UAP(lb_I_Parameter, document)
        
        ukDoc = meta->getActiveDocument();
        
        QI(ukDoc, lb_I_Parameter, document)
        
        if (document != NULL) {
                *param = "StorageDelegateNamespace";
                document->getUAPString(*&param, *&StorageNamespace);
                
                // Get the plugin that is responsible to save the data.         
                pl = PM->getFirstMatchingPlugin("lb_I_StandaloneStreamable", StorageNamespace->charrep());
                
                if (pl != NULL) {
                        ukPl = pl->getImplementation();
                } else {
                        _LOG << "No 'lb_I_StandaloneStreamable' plugin with namespace '" << StorageNamespace->charrep() << "' available." LOG_  
                }
                
                UAP(lb_I_StandaloneStreamable, mystream)
        
                if (ukPl != NULL) QI(ukPl, lb_I_StandaloneStreamable, mystream)
                        
                if (mystream == NULL) {
                        _LOG << "Error: Found a lb_I_StandaloneStreamable plugin via PM->getFirstMatchingPlugin(...), but QI failed." LOG_
                } else {
                        //isFileAvailable = fOp->begin(filename->charrep()); 
                        
                        mystream->setOperator(this);
                        mystream->save(*&oStream);
                }
        }
}

void LB_STDCALL lbJSONOutputStream::end() {
        if (oStream == NULL) {
                _CL_LOG << "lbJSONOutputStream::end() Error: Not opened." LOG_
        }
        char* buffer = NULL;
        if (root) {
                json_tree_to_string(root, &buffer);
                json_render_tree(root);
        }
        
        if (buffer) {
                oStream->setBinary();
                *oStream << buffer;
                free(buffer);
        }       
        oStream->close();
}

lb_I_Stream* LB_STDCALL lbJSONOutputStream::getStream() {
        lbErrCodes err = ERR_NONE;
        
        UAP(lb_I_Stream, s)
        QI(oStream, lb_I_Stream, s)
        s++;
        
        return s.getPtr();
}

/*...sclass lbPluginJSONOutputStream implementation:0:*/
/*...slbPluginJSONOutputStream:0:*/
class lbPluginJSONOutputStream : public lb_I_PluginImpl {
public:
	lbPluginJSONOutputStream();
	
	virtual ~lbPluginJSONOutputStream();
	
	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
	/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();
	
	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
	/*...e*/
	
	DECLARE_LB_UNKNOWN()
	
private:
	UAP(lb_I_Unknown, impl)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginJSONOutputStream)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginJSONOutputStream, lbPluginJSONOutputStream)

/*...slbErrCodes LB_STDCALL lbPluginJSONOutputStream\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginJSONOutputStream::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPluginJSONOutputStream::setData(...) called.\n" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginJSONOutputStream::lbPluginJSONOutputStream() {
	_CL_VERBOSE << "lbPluginJSONOutputStream::lbPluginJSONOutputStream() called.\n" LOG_
	
}

lbPluginJSONOutputStream::~lbPluginJSONOutputStream() {
	_CL_VERBOSE << "lbPluginJSONOutputStream::~lbPluginJSONOutputStream() called.\n" LOG_
}

bool LB_STDCALL lbPluginJSONOutputStream::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginJSONOutputStream::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginJSONOutputStream::initialize() {
}

bool LB_STDCALL lbPluginJSONOutputStream::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginJSONOutputStream\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginJSONOutputStream::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (impl == NULL) {
		lbJSONOutputStream* OutputStream = new lbJSONOutputStream();
		
		
		QI(OutputStream, lb_I_Unknown, impl)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return impl.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginJSONOutputStream\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginJSONOutputStream::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (impl == NULL) {
		
		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior." LOG_
		
		lbJSONOutputStream* OutputStream = new lbJSONOutputStream();
		
		
		QI(OutputStream, lb_I_Unknown, impl)
	}
	
	lb_I_Unknown* r = impl.getPtr();
	impl.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginJSONOutputStream::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (impl != NULL) {
		impl->release(__FILE__, __LINE__);
		impl.resetPtr();
	}
}
/*...e*/
/*...e*/

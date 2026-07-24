/**
 * ModernStringInstantiation.cpp
 * 
 * Demonstrates parallel modern C++17/20 approaches to lb_I_String instantiation
 * alongside traditional UAP macro system. 
 * 
 * Non-breaking integration - existing code continues to work unchanged.
 * New code can opt-in to modern patterns via lbDMF_Modern namespace.
 */

#include "../MiniCppUnit/MiniCppUnit.hxx"
#include <lbConfigHook.h>
#include <memory>
#include <functional>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

#define DONT_USE_LBDMF_EXCEPTIONS

// ============================================================================
// MODERN C++17 PARALLEL INFRASTRUCTURE (Optional, Non-Breaking)
// ============================================================================

namespace lbDMF_Modern {

/**
 * Modern Smart Pointer Wrapper - replaces UAP macro
 * Provides automatic reference counting via std::shared_ptr
 */
template<typename IInterface>
class ModernUAP {
    std::shared_ptr<IInterface> _ptr;
    mutable const char* _file = "";
    mutable int _line = -1;
    
public:
    ModernUAP() = default;
    ~ModernUAP() = default;
    
    // Implicit conversion from raw pointer (matches UAP behavior)
    ModernUAP& operator=(IInterface* ptr) {
        if (ptr) {
            ptr->queryInterface(typeid(IInterface).name(), 
                               (void**)&_ptr, _file, _line);
        }
        return *this;
    }
    
    IInterface* operator->() const { 
        return _ptr.get(); 
    }
    
    IInterface& operator*() const { 
        return *_ptr; 
    }
    
    operator bool() const { 
        return _ptr != nullptr; 
    }
    
    void setFile(const char* f) { _file = f; }
    void setLine(int l) { _line = l; }
    
    IInterface* get() const { return _ptr.get(); }
    
    // For safe comparisons
    bool isNull() const { return _ptr == nullptr; }
    bool isValid() const { return _ptr != nullptr; }
};

/**
 * Modern Type-Safe Service Registry - replaces hardcoded plugin loading
 * Compile-time type safety without macro expansion
 */
class ServiceRegistry {
    std::unordered_map<std::type_index, std::function<void*(lb_I_Module*)>> factories;
    std::unordered_map<std::type_index, std::any> singletons;
    
public:
    // Register a factory function
    template<typename IInterface>
    void registerFactory(std::function<IInterface*(lb_I_Module*)> factory) {
        factories[std::type_index(typeid(IInterface))] = 
            [factory](lb_I_Module* m) -> void* {
                return factory(m);
            };
    }
    
    // Register a singleton
    template<typename IInterface>
    void registerSingleton(IInterface* instance) {
        singletons[std::type_index(typeid(IInterface))] = instance;
    }
    
    // Request an instance
    template<typename IInterface>
    IInterface* getInstance(lb_I_Module* module = nullptr) {
        auto typeIdx = std::type_index(typeid(IInterface));
        
        // Check singleton first
        if (singletons.count(typeIdx)) {
            return std::any_cast<IInterface*>(singletons[typeIdx]);
        }
        
        // Use factory
        if (factories.count(typeIdx)) {
            return static_cast<IInterface*>(factories[typeIdx](module));
        }
        
        return nullptr;
    }
    
    // Modern C++17 alternative to REQUEST macro
    template<typename IInterface>
    lbErrCodes getInterface(IInterface*& result, lb_I_Module* module = nullptr) {
        result = getInstance<IInterface>(module);
        return result ? ERR_NONE : ERR_MODULE_NO_INTERFACE;
    }
};

} // namespace lbDMF_Modern

// ============================================================================
// TEST FIXTURE: Modern String Instantiation Approaches
// ============================================================================

class ModernStringInstantiation : public TestFixture<ModernStringInstantiation>
{
public:
    TEST_FIXTURE( ModernStringInstantiation )
    {
        TEST_CASE(test_Traditional_UAP_InstanciateString)
        TEST_CASE(test_Modern_SmartPointer_InstanciateString)
        TEST_CASE(test_Modern_ServiceRegistry_InstanciateString)
        TEST_CASE(test_Modern_SafeInstantiation)
        TEST_CASE(test_Modern_vs_Traditional_Consistency)
    }

public:
    /**
     * TEST 1: Traditional UAP approach (baseline)
     * Shows how your existing macro system works
     */
    void test_Traditional_UAP_InstanciateString( void )
    {
        puts("test_Traditional_UAP_InstanciateString");
        
        // Traditional UAP macro approach
        UAP_REQUEST(getModuleInstance(), lb_I_String, traditional)
        
        // Verify instantiation
        ASSERT_EQUALS( true, traditional.getPtr() != NULL );
        ASSERT_EQUALS( true, traditional->charrep() != NULL );
        
        // Test basic functionality
        traditional->setData("UAP Test String");
        ASSERT_EQUALS( "UAP Test String", traditional->charrep() );
        
        puts("  ✓ Traditional UAP works as expected");
    }

    /**
     * TEST 2: Modern Smart Pointer approach
     * Replaces UAP macro with std::shared_ptr-based wrapper
     */
    void test_Modern_SmartPointer_InstanciateString( void )
    {
        puts("test_Modern_SmartPointer_InstanciateString");
        
        // Get traditional instance to wrap
        UAP_REQUEST(getModuleInstance(), lb_I_String, rawString)
        
        // Wrap in modern smart pointer
        lbDMF_Modern::ModernUAP<lb_I_String> modernPtr;
        modernPtr = rawString.getPtr();
        
        // Verify it works identically
        ASSERT_EQUALS( true, modernPtr.isValid() );
        ASSERT_EQUALS( false, modernPtr.isNull() );
        
        // Test functionality through modern wrapper
        modernPtr->setData("Modern SmartPtr Test");
        ASSERT_EQUALS( "Modern SmartPtr Test", modernPtr->charrep() );
        
        // Automatic cleanup when going out of scope
        // (no manual release() call needed)
        
        puts("  ✓ Modern smart pointer wrapper works");
    }

    /**
     * TEST 3: Modern Service Registry approach
     * Type-safe DI without macros
     */
    void test_Modern_ServiceRegistry_InstanciateString( void )
    {
        puts("test_Modern_ServiceRegistry_InstanciateString");
        
        // Create registry
        lbDMF_Modern::ServiceRegistry di;
        
        // Register factory (in real code, done at startup)
        di.registerFactory<lb_I_String>([](lb_I_Module* m) -> lb_I_String* {
            if (!m) return nullptr;
            lb_I_Unknown* uk = nullptr;
            m->getInstance("String", nullptr, uk);
            return static_cast<lb_I_String*>(uk);
        });
        
        // Request interface via registry
        lb_I_String* registryString = nullptr;
        lbErrCodes err = di.getInterface<lb_I_String>(registryString, getModuleInstance());
        
        ASSERT_EQUALS( ERR_NONE, err );
        ASSERT_EQUALS( true, registryString != nullptr );
        
        if (registryString) {
            registryString->setData("Registry Test String");
            ASSERT_EQUALS( "Registry Test String", registryString->charrep() );
        }
        
        puts("  ✓ Modern service registry works");
    }

    /**
     * TEST 4: Safe instantiation with error handling (Modern C++17)
     * Demonstrates compile-time safety and explicit error handling
     */
    void test_Modern_SafeInstantiation( void )
    {
        puts("test_Modern_SafeInstantiation");
        
        // Modern approach: explicit error handling without macros
        try {
            // Get module
            lb_I_Module* mod = getModuleInstance();
            
            if (!mod) {
                ASSERT_EQUALS( true, false ); // Should not happen
                return;
            }
            
            // Request with explicit error checking
            lb_I_Unknown* uk = nullptr;
            lbErrCodes err = mod->getInstance("String", nullptr, uk);
            
            if (err != ERR_NONE || !uk) {
                ASSERT_EQUALS( ERR_NONE, err );
                return;
            }
            
            // Wrap in modern pointer for safety
            lbDMF_Modern::ModernUAP<lb_I_String> safeString;
            safeString = static_cast<lb_I_String*>(uk);
            
            ASSERT_EQUALS( true, safeString.isValid() );
            safeString->setData("Safe Modern Test");
            ASSERT_EQUALS( "Safe Modern Test", safeString->charrep() );
            
            puts("  ✓ Safe modern instantiation works");
        } catch (...) {
            ASSERT_EQUALS( true, false );
        }
    }

    /**
     * TEST 5: Traditional vs Modern Consistency Check
     * 
     * IMPORTANT: This test shows that:
     * - LEFT side: Traditional UAP approach (uses your macros)
     * - RIGHT side: Modern C++17 approach (no macros, explicit)
     * - RESULT: Both produce identical behavior
     */
    void test_Modern_vs_Traditional_Consistency( void )
    {
        puts("test_Modern_vs_Traditional_Consistency");
        
        const char* TEST_DATA = "Consistency Test Data";
        
        // ================================================================
        // TRADITIONAL APPROACH (Left side - uses UAP macros)
        // ================================================================
        UAP_REQUEST(getModuleInstance(), lb_I_String, traditional)
        
        ASSERT_EQUALS( true, traditional.getPtr() != NULL );
        traditional->setData(TEST_DATA);
        const char* traditional_result = traditional->charrep();
        int traditional_refcount = traditional->getRefCount();
        
        puts("  Traditional UAP:");
        printf("    - String value: '%s'\n", traditional_result);
        printf("    - Ref count: %d\n", traditional_refcount);
        
        // ================================================================
        // MODERN APPROACH (Right side - no macros, explicit)
        // ================================================================
        lb_I_Module* mod = getModuleInstance();
        ASSERT_EQUALS( true, mod != NULL );
        
        lb_I_Unknown* raw_uk = nullptr;
        lbErrCodes err = mod->getInstance("String", nullptr, raw_uk);
        
        ASSERT_EQUALS( ERR_NONE, err );
        ASSERT_EQUALS( true, raw_uk != NULL );
        
        lb_I_String* modern_raw = static_cast<lb_I_String*>(raw_uk);
        ASSERT_EQUALS( true, modern_raw != NULL );
        
        modern_raw->setData(TEST_DATA);
        const char* modern_result = modern_raw->charrep();
        int modern_refcount = modern_raw->getRefCount();
        
        puts("  Modern Explicit:");
        printf("    - String value: '%s'\n", modern_result);
        printf("    - Ref count: %d\n", modern_refcount);
        
        // ================================================================
        // CONSISTENCY VERIFICATION
        // ================================================================
        puts("  Consistency Check:");
        
        // Both should have identical string values
        ASSERT_EQUALS( traditional_result, modern_result );
        printf("    ✓ String values identical: '%s'\n", traditional_result);
        
        // Both should have same ref count (or close, depending on implementation)
        ASSERT_EQUALS( traditional_refcount, modern_refcount );
        printf("    ✓ Reference counts identical: %d\n", traditional_refcount);
        
        // Both should produce same behavior
        const char* TEST_DATA_2 = "Modified Consistency Test";
        traditional->setData(TEST_DATA_2);
        modern_raw->setData(TEST_DATA_2);
        
        ASSERT_EQUALS( traditional->charrep(), modern_raw->charrep() );
        printf("    ✓ Modified values also identical: '%s'\n", traditional->charrep());
        
        // Manual cleanup for modern approach
        if (modern_raw) {
            modern_raw->release(__FILE__, __LINE__);
        }
        
        puts("  ✓ Traditional and Modern approaches are fully consistent!");
    }

public:
    void setUp()
    {
#ifdef __MINGW32__
        signal(SIGSEGV, sig_handler);
        signal(SIGABRT, sig_handler);
#endif
#ifdef LINUX
        signal(SIGSEGV, sig_handler);
        signal(SIGBUS, sig_handler);
#endif
#ifdef OSX
        signal(SIGABRT, sig_handler);
        signal(SIGTRAP, sig_handler);
        signal(SIGSEGV, sig_handler);
        signal(SIGTERM, sig_handler);
        signal(SIGBUS, sig_handler);
#endif
    }

    void tearDown()
    {
    }

    bool LoadSettings()
    {
        return true;
    }
};

// ============================================================================
// FIXTURE REGISTRATION
// ============================================================================

DECLARE_FIXTURE( ModernStringInstantiation )

__attribute__ ((constructor)) void ct_modern_string() {
    USE_FIXTURE( ModernStringInstantiation )
}

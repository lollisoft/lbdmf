class lb_I_test {
protected:
        lb_I_test() {}
        virtual ~lb_I_test() {}
public:

        virtual void release() = 0;
};

#undef DLLEXPORT

#ifdef LB_MODULE_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef LB_MODULE_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif

class test : public lb_I_test {
public:
        test();
        virtual ~test();
        
        virtual void release();
};


void DLLEXPORT getInstance(lb_I_test*& inst);


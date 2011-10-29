/*...sclass lbLocale:0:*/
class lbLocale : public lb_I_Locale
{
public:

        void LB_STDCALL setLanguage(const char* lang);

		void LB_STDCALL translate(char ** text, const char* to_translate);
		void LB_STDCALL setTranslationData(lb_I_Unknown* uk);

        UAP(lb_I_Translations, translations)
        char* _lang;
		bool  dbAvailable;

		DECLARE_LB_UNKNOWN()

public:
        lbLocale();
        virtual ~lbLocale();

};
/*...e*/
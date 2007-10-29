<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>

<xsl:template name="createFormPlugin">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>


<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>

class lbPlugin<xsl:value-of select="$FormularName"/> : public lb_I_PluginImpl {
public:
	lbPlugin<xsl:value-of select="$FormularName"/>();
	
	virtual ~lbPlugin<xsl:value-of select="$FormularName"/>();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukActions)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPlugin<xsl:value-of select="$FormularName"/>)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPlugin<xsl:value-of select="$FormularName"/>, lbPlugin<xsl:value-of select="$FormularName"/>)

lbErrCodes LB_STDCALL lbPlugin<xsl:value-of select="$FormularName"/>::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$FormularName"/>::setData(...) called.\n" LOG_

    return ERR_NOT_IMPLEMENTED;
}

lbPlugin<xsl:value-of select="$FormularName"/>::lbPlugin<xsl:value-of select="$FormularName"/>() {
	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$FormularName"/>::lbPlugin<xsl:value-of select="$FormularName"/>() called.\n" LOG_
	ref = STARTREF;
}

lbPlugin<xsl:value-of select="$FormularName"/>::~lbPlugin<xsl:value-of select="$FormularName"/>() {
	_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$FormularName"/>::~lbPlugin<xsl:value-of select="$FormularName"/>() called.\n" LOG_
}

bool LB_STDCALL lbPlugin<xsl:value-of select="$FormularName"/>::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPlugin<xsl:value-of select="$FormularName"/>::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPlugin<xsl:value-of select="$FormularName"/>::initialize() {
}
	
bool LB_STDCALL lbPlugin<xsl:value-of select="$FormularName"/>::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPlugin<xsl:value-of select="$FormularName"/>::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		<xsl:value-of select="$FormularName"/>* _<xsl:value-of select="$FormularName"/> = new <xsl:value-of select="$FormularName"/>();
		_<xsl:value-of select="$FormularName"/>->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(_<xsl:value-of select="$FormularName"/>, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE &lt;&lt; "lbPlugin<xsl:value-of select="$FormularName"/>::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPlugin<xsl:value-of select="$FormularName"/>::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE &lt;&lt; "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		<xsl:value-of select="$FormularName"/>* _<xsl:value-of select="$FormularName"/> = new <xsl:value-of select="$FormularName"/>();
		_<xsl:value-of select="$FormularName"/>->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(_<xsl:value-of select="$FormularName"/>, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}

void LB_STDCALL lbPlugin<xsl:value-of select="$FormularName"/>::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
</xsl:template>

</xsl:stylesheet>
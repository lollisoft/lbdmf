#ifndef lbDMFFormularFieldShape_H
#define lbDMFFormularFieldShape_H

// include main wxSF header file
#include <wx/wxsf/wxShapeFramework.h>
#include <lbDMFBaseDesignShape.h>

class lbDMFFormularFieldShape : public lbDMFBaseDesignShape
{
public:
    // enable RTTI information and define xsSerializable::Clone() function used by
	// wxXmlSerilizer::CopyItems() function, the data (shape) manager's
	// copy constructor and in some cases also by the canvas history manager.
    XS_DECLARE_CLONABLE_CLASS(lbDMFFormularFieldShape);

    // default constructor used by RTTI
    lbDMFFormularFieldShape();
    // copy constructor needed by the xsSerializable::Clone() function
    lbDMFFormularFieldShape(const lbDMFFormularFieldShape& obj);
    // destructor
    virtual ~lbDMFFormularFieldShape();
	
	void SetFormularFieldName(const wxString& name);
protected:
};



#endif // lbDMFFormularFieldShape_H

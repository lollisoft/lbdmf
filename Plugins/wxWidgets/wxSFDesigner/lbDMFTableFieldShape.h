#ifndef lbDMFTableFieldShape_H
#define lbDMFTableFieldShape_H

// include main wxSF header file
#include <wx/wxsf/wxShapeFramework.h>
#include <lbDMFBaseDesignShape.h>

class lbDMFTableFieldShape : public lbDMFBaseDesignShape
{
public:
    // enable RTTI information and define xsSerializable::Clone() function used by
	// wxXmlSerilizer::CopyItems() function, the data (shape) manager's
	// copy constructor and in some cases also by the canvas history manager.
    XS_DECLARE_CLONABLE_CLASS(lbDMFTableFieldShape);

    // default constructor used by RTTI
    lbDMFTableFieldShape();
    // copy constructor needed by the xsSerializable::Clone() function
    lbDMFTableFieldShape(const lbDMFTableFieldShape& obj);
    // destructor
    virtual ~lbDMFTableFieldShape();
	
	void SetTableFieldName(const wxString& name);
protected:
};



#endif // lbDMFTableFieldShape_H

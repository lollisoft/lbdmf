#ifndef lbDMFTableShape_H
#define lbDMFTableShape_H

// include main wxSF header file
#include <wx/wxsf/wxShapeFramework.h>
#include <lbDMFBaseDesignShape.h>

class lbDMFTableShape : public lbDMFBaseDesignShape
{
public:
    // enable RTTI information and define xsSerializable::Clone() function used by
	// wxXmlSerilizer::CopyItems() function, the data (shape) manager's
	// copy constructor and in some cases also by the canvas history manager.
    XS_DECLARE_CLONABLE_CLASS(lbDMFTableShape);

    // default constructor used by RTTI
    lbDMFTableShape();
    // copy constructor needed by the xsSerializable::Clone() function
    lbDMFTableShape(const lbDMFTableShape& obj);
    // destructor
    virtual ~lbDMFTableShape();
	
	void SetTableName(const wxString& name);
protected:
};



#endif // lbDMFFormularShape_H

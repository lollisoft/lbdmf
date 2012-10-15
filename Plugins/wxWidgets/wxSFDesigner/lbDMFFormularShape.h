#ifndef lbDMFFormularShape_H
#define lbDMFFormularShape_H

// include main wxSF header file
#include <wx/wxsf/wxShapeFramework.h>
#include <lbDMFBaseDesignShape.h>

class lbDMFFormularShape : public lbDMFBaseDesignShape
{
public:
    // enable RTTI information and define xsSerializable::Clone() function used by
	// wxXmlSerilizer::CopyItems() function, the data (shape) manager's
	// copy constructor and in some cases also by the canvas history manager.
    XS_DECLARE_CLONABLE_CLASS(lbDMFFormularShape);

    // default constructor used by RTTI
    lbDMFFormularShape();
    // copy constructor needed by the xsSerializable::Clone() function
    lbDMFFormularShape(const lbDMFFormularShape& obj);
    // destructor
    virtual ~lbDMFFormularShape();
	
protected:
};



#endif // lbDMFFormularShape_H

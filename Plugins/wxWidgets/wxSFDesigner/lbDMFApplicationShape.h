#ifndef lbDMFApplicationShape_H
#define lbDMFApplicationShape_H

// include main wxSF header file
#include <wx/wxsf/wxShapeFramework.h>
#include <lbDMFBaseDesignShape.h>

class lbDMFApplicationShape : public lbDMFBaseDesignShape
{
public:
    // enable RTTI information and define xsSerializable::Clone() function used by
	// wxXmlSerilizer::CopyItems() function, the data (shape) manager's
	// copy constructor and in some cases also by the canvas history manager.
    XS_DECLARE_CLONABLE_CLASS(lbDMFApplicationShape);

    // default constructor used by RTTI
    lbDMFApplicationShape();
    // copy constructor needed by the xsSerializable::Clone() function
    lbDMFApplicationShape(const lbDMFApplicationShape& obj);
    // destructor
    virtual ~lbDMFApplicationShape();

protected:
};



#endif // lbDMFApplicationShape_H

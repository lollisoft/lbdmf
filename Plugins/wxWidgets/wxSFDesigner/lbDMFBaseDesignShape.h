#ifndef lbDMFBaseDesignShape_H
#define lbDMFBaseDesignShape_H

// include main wxSF header file
#include <wx/wxsf/wxShapeFramework.h>


class lbDMFBaseDesignShape : public wxSFFlexGridShape
{
public:
    // enable RTTI information and define xsSerializable::Clone() function used by
	// wxXmlSerilizer::CopyItems() function, the data (shape) manager's
	// copy constructor and in some cases also by the canvas history manager.
    XS_DECLARE_CLONABLE_CLASS(lbDMFBaseDesignShape);

    // default constructor used by RTTI
    lbDMFBaseDesignShape();
    // user constructor
    lbDMFBaseDesignShape(wxString imagePath, wxString defaultText);
    // copy constructor needed by the xsSerializable::Clone() function
    lbDMFBaseDesignShape(const lbDMFBaseDesignShape& obj);
    // destructor
    virtual ~lbDMFBaseDesignShape();

protected:
    // protected data members
    wxSFEditTextShape* m_pModelName;
    wxSFBitmapShape* m_pBitmap;
    wxString m_sDescription;

    // protected functions;
    virtual void Initialize(wxString imagePath, wxString defaultText);
};



#endif // lbDMFBaseDesignShape_H

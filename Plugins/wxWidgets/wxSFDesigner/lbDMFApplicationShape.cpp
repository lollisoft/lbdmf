#include <wx/string.h>
#include <lbDMFApplicationShape.h>
#include <wx/filename.h>

// implement RTTI information and xsSerializable::Clone() functions
XS_IMPLEMENT_CLONABLE_CLASS(lbDMFApplicationShape, lbDMFBaseDesignShape);

lbDMFApplicationShape::lbDMFApplicationShape()
{
    // disable serialization of polygon vertices, because they are always set
    // in this constructor
	//EnablePropertySerialization(wxT("vertices"), false);

    // initialize shape
    Initialize("toolbarimages/kthememgr.png", "Enter application name");
}

lbDMFApplicationShape::lbDMFApplicationShape(const lbDMFApplicationShape& obj)
: lbDMFBaseDesignShape(obj)
{
}

lbDMFApplicationShape::~lbDMFApplicationShape()
{
}

void lbDMFApplicationShape::SetApplicationName(const wxString& name) {
	m_pModelName->SetText(name);
}



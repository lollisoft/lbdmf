#include <lbDMFTableShape.h>
#include <wx/filename.h>

// implement RTTI information and xsSerializable::Clone() functions
XS_IMPLEMENT_CLONABLE_CLASS(lbDMFTableShape, lbDMFBaseDesignShape);

lbDMFTableShape::lbDMFTableShape()
{
    // disable serialization of polygon vertices, because they are always set
    // in this constructor
	//EnablePropertySerialization(wxT("vertices"), false);

    // initialize shape
    Initialize("toolbarimages/table.png", "Enter form name");
}

lbDMFTableShape::lbDMFTableShape(const lbDMFTableShape& obj)
: lbDMFBaseDesignShape(obj)
{
}

lbDMFTableShape::~lbDMFTableShape()
{
}

void lbDMFTableShape::SetTableName(const wxString& name) {
	m_pModelName->SetText(name);
}


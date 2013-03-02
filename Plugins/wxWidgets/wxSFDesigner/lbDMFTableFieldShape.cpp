#include <lbDMFTableFieldShape.h>
#include <wx/filename.h>

// implement RTTI information and xsSerializable::Clone() functions
XS_IMPLEMENT_CLONABLE_CLASS(lbDMFTableFieldShape, lbDMFBaseDesignShape);

lbDMFTableFieldShape::lbDMFTableFieldShape()
{
    // disable serialization of polygon vertices, because they are always set
    // in this constructor
	//EnablePropertySerialization(wxT("vertices"), false);

    // initialize shape
    Initialize("toolbarimages/table_column.png", "Enter form name");
}

lbDMFTableFieldShape::lbDMFTableFieldShape(const lbDMFTableFieldShape& obj)
: lbDMFBaseDesignShape(obj)
{
}

lbDMFTableFieldShape::~lbDMFTableFieldShape()
{
}

void lbDMFTableFieldShape::SetTableFieldName(const wxString& name) {
	m_pModelName->SetText(name);
}


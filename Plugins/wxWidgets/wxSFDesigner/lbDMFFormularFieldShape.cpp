#include <lbDMFFormularFieldShape.h>
#include <wx/filename.h>

// implement RTTI information and xsSerializable::Clone() functions
XS_IMPLEMENT_CLONABLE_CLASS(lbDMFFormularFieldShape, lbDMFBaseDesignShape);

lbDMFFormularFieldShape::lbDMFFormularFieldShape()
{
    // disable serialization of polygon vertices, because they are always set
    // in this constructor
	//EnablePropertySerialization(wxT("vertices"), false);

    // initialize shape
    Initialize("toolbarimages/formular_field.png", "Enter form name");
}

lbDMFFormularFieldShape::lbDMFFormularFieldShape(const lbDMFFormularFieldShape& obj)
: lbDMFBaseDesignShape(obj)
{
}

lbDMFFormularFieldShape::~lbDMFFormularFieldShape()
{
}

void lbDMFFormularFieldShape::SetFormularFieldName(const wxString& name) {
	m_pModelName->SetText(name);
}


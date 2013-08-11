#include <lbDMFFormularShape.h>
#include <wx/filename.h>

// implement RTTI information and xsSerializable::Clone() functions
XS_IMPLEMENT_CLONABLE_CLASS(lbDMFFormularShape, lbDMFBaseDesignShape);

lbDMFFormularShape::lbDMFFormularShape()
{
    // disable serialization of polygon vertices, because they are always set
    // in this constructor
	//EnablePropertySerialization(wxT("vertices"), false);

    // initialize shape
    Initialize("toolbarimages/kpersonalizer.png", "Enter form name");
}

lbDMFFormularShape::lbDMFFormularShape(const lbDMFFormularShape& obj)
: lbDMFBaseDesignShape(obj)
{
}

lbDMFFormularShape::~lbDMFFormularShape()
{
}

void lbDMFFormularShape::SetFormularName(const wxString& name) {
	m_pModelName->SetText(name);
}

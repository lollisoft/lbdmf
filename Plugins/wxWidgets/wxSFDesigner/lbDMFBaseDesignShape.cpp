#include <lbDMFBaseDesignShape.h>
#include <wx/filename.h>

// implement RTTI information and xsSerializable::Clone() functions
XS_IMPLEMENT_CLONABLE_CLASS(lbDMFBaseDesignShape, wxSFFlexGridShape);

lbDMFBaseDesignShape::lbDMFBaseDesignShape()
{
}

lbDMFBaseDesignShape::lbDMFBaseDesignShape(wxString imagePath, wxString defaultText)
{
    // disable serialization of polygon vertices, because they are always set
    // in this constructor
	//EnablePropertySerialization(wxT("vertices"), false);
	
    // initialize shape
    Initialize(imagePath, defaultText);
}

lbDMFBaseDesignShape::lbDMFBaseDesignShape(const lbDMFBaseDesignShape& obj)
: wxSFFlexGridShape()
{
	// clone source child text object..
    m_pModelName = (wxSFEditTextShape*)obj.m_pModelName->Clone();
	if( m_pModelName )
	{
		// .. and append it to this shapes as its child
		AddChild(m_pModelName);
		// this object is created by the parent class constructor and not
		// by the serializer (only its properties are deserialized)
		XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pModelName, wxT("modelname"));
	}
	
	m_pBitmap = (wxSFBitmapShape*)obj.m_pBitmap->Clone();
	if( m_pBitmap )
	{
		// .. and append it to this shapes as its child
		AddChild(m_pBitmap);
		// this object is created by the parent class constructor and not
		// by the serializer (only its properties are deserialized)
		XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pBitmap, wxT("image"));
	}
}

lbDMFBaseDesignShape::~lbDMFBaseDesignShape()
{
}

void lbDMFBaseDesignShape::Initialize(wxString imagePath, wxString defaultText)
{
    // initialize custom data members...
    m_sDescription = wxT("Insert some shape's description text here...");
    // now tell the serializer that this data member should be serialized
    // (see library documentation to get more info about available serialization
    // macros (supported data types))
    XS_SERIALIZE(m_sDescription, wxT("description"));

    // polygon-based shapes can be connected either to the vertices or to the
    // nearest border point (default value is TRUE).
    //SetConnectToVertex(false);

    // set accepted connections for the new shape
	SetFill(*wxTRANSPARENT_BRUSH);
	SetBorder(wxPen(*wxBLACK, 1, wxDOT));
	SetDimensions(2, 2);
	AcceptChild(wxT("All"));
	AcceptConnection(wxT("All"));
	AcceptSrcNeighbour(wxT("All"));
	AcceptTrgNeighbour(wxT("All"));
	
	
	m_pBitmap = new wxSFBitmapShape(); //
	
	if (m_pBitmap) {
		// create relative path
		wxFileName path( imagePath );
		path.MakeRelativeTo( wxGetCwd() );

		// create image from BMP file
		m_pBitmap->CreateFromFile( path.GetFullPath(), wxBITMAP_TYPE_PNG );

		// set shape policy
		//m_pBitmap->AcceptConnection(wxT("All"));
		//m_pBitmap->AcceptSrcNeighbour(wxT("All"));
		//m_pBitmap->AcceptTrgNeighbour(wxT("All"));
		m_pBitmap->SetStyle(sfsALWAYS_INSIDE /*| sfsHOVERING*/ | sfsPROCESS_DEL | sfsPROPAGATE_DRAGGING | sfsPROPAGATE_SELECTION);
		SF_ADD_COMPONENT( m_pBitmap, wxT("image") );
		InsertToGrid(0, 0, m_pBitmap);
	}
	
	// create associated shape(s)
	m_pModelName = new wxSFEditTextShape();
    // set some properties
    if(m_pModelName)
    {
        // set text
        m_pModelName->SetText(wxT(defaultText));

        // set alignment
        m_pModelName->SetVAlign(wxSFShapeBase::valignMIDDLE);
        m_pModelName->SetHAlign(wxSFShapeBase::halignCENTER);

        // set required shape style(s)
		m_pModelName->SetStyle(sfsALWAYS_INSIDE /*| sfsHOVERING*/ | sfsPROCESS_DEL | sfsPROPAGATE_DRAGGING | sfsPROPAGATE_SELECTION);
		// you can also force displaying of the shapes handles even if the interactive
		// size change is not allowed:
		//m_pText->AddStyle(sfsSHOW_HANDLES);

        // components of composite shapes created at runtime in parent shape's
        // constructor cannot be fully serialized (it means created by
		// the serializer) so it is important to disable their standard serialization
        // but they can be still serialized as the parent shape's properties 
		// in the standard way by the following macro:
		SF_ADD_COMPONENT( m_pModelName, wxT("modelname") );
		InsertToGrid(1, 1, m_pModelName);
    }
}



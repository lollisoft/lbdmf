/***************************************************************
 * Name:      ShapeBase.h
 * Purpose:   Implements shape base class
 * Author:    Michal Bližňák (michal.bliznak@tiscali.cz)
 * Created:   2007-07-22
 * Copyright: Michal Bližňák
 * License:   wxWidgets license (www.wxwidgets.org)
 * Notes:
 **************************************************************/

#include <wx/dataobj.h>
#include "ShapeBase.h"
#include "ShapeCanvas.h"
#include "TextShape.h"

#include <wx/variant.h>
#include <wx/listimpl.cpp>

WX_DEFINE_EXPORTED_LIST(ShapeList);

ShapeList m_lstProcessed;

IMPLEMENT_DYNAMIC_CLASS(wxSFShapeBase, xsSerializable);

wxSFShapeBase::wxSFShapeBase(void)
{
	// initialize data members
	m_fSelected = false;
	m_fMouseOver = false;
	m_fFirstMove = false;
	m_fHighlighParent = false;
	m_pParentManager = NULL;
	m_pUserData = NULL;

	// archived properties
	m_fVisible = sfdvBASESHAPE_VISIBILITY;
	m_fActive = sfdvBASESHAPE_ACTIVITY;
	m_nStyle = sfdvBASESHAPE_DEFAULT_STYLE;
	m_nRelativePosition = sfdvBASESHAPE_POSITION;
	m_nHoverColor = sfdvBASESHAPE_HOVERCOLOUR;
	m_nVAlign = sfdvBASESHAPE_VALIGN;
	m_nHAlign = sfdvBASESHAPE_HALIGN;
	m_nVBorder = sfdvBASESHAPE_VBORDER;
	m_nHBorder = sfdvBASESHAPE_HBORDER;

    // mark serialized properties
    XS_SERIALIZE(m_nId, wxT("id"));
    XS_SERIALIZE_EX(m_fActive, wxT("active"), sfdvBASESHAPE_ACTIVITY);
    XS_SERIALIZE_EX(m_fVisible, wxT("visibility"), sfdvBASESHAPE_VISIBILITY);
    XS_SERIALIZE_EX(m_nStyle, wxT("style"), sfdvBASESHAPE_DEFAULT_STYLE);
    XS_SERIALIZE(m_arrAcceptedChildren, wxT("accepted_children"));
    XS_SERIALIZE(m_arrAcceptedConnections, wxT("accepted_connections"));
    XS_SERIALIZE(m_arrAcceptedSrcNeighbours, wxT("accepted_src_neighbours"));
    XS_SERIALIZE(m_arrAcceptedTrgNeighbours, wxT("accepted_trg_neighbours"));
    XS_SERIALIZE_EX(m_nHoverColor, wxT("hover_color"), sfdvBASESHAPE_HOVERCOLOUR);
    XS_SERIALIZE(m_nRelativePosition, wxT("relative_position"));
#if wxCHECK_VERSION(2, 8, 0)
    XS_SERIALIZE_LONG_EX(m_nHAlign, wxT("halign"), sfdvBASESHAPE_HALIGN);
#else // replacement code for old version
	long int temp = m_nHAlign;
	AddProperty(new xsProperty(&temp, wxString(wxT("halign")), sfdvBASESHAPE_HALIGN));
#endif
#if wxCHECK_VERSION(2, 8, 0)
    XS_SERIALIZE_LONG_EX(m_nVAlign, wxT("valign"), (long)sfdvBASESHAPE_VALIGN);
#else // replacement code for old version
	temp = m_nVAlign;
	AddProperty(new xsProperty(&temp, wxString(wxT("valign")), sfdvBASESHAPE_VALIGN));
#endif
    XS_SERIALIZE_EX(m_nHBorder, wxT("hborder"), sfdvBASESHAPE_HBORDER);
    XS_SERIALIZE_EX(m_nVBorder, wxT("vborder"), sfdvBASESHAPE_VBORDER);
    XS_SERIALIZE(m_pUserData, wxT("user_data"));


	m_lstHandles.DeleteContents(true);
}

wxSFShapeBase::wxSFShapeBase(const wxRealPoint& pos, wxSFDiagramManager* manager)
{
	wxASSERT_MSG(manager, wxT("Shape manager has not been properly set in shape constructor."));

	// initialize data members
	m_pParentManager = manager;
    m_pUserData = NULL;

	if(m_pParentManager)
	{
		if( m_pParentManager->GetShapeCanvas() )m_nHoverColor = m_pParentManager->GetShapeCanvas()->GetHoverColour();
		else
            m_nHoverColor = sfdvBASESHAPE_HOVERCOLOUR;
	}
	else
	{
		m_nHoverColor = sfdvBASESHAPE_HOVERCOLOUR;
	}

	m_fSelected = false;
	m_fMouseOver = false;
	m_fFirstMove = false;
	m_fHighlighParent = false;

	// archived properties
	m_fVisible = sfdvBASESHAPE_VISIBILITY;
	m_fActive = sfdvBASESHAPE_ACTIVITY;
	m_nStyle = sfdvBASESHAPE_DEFAULT_STYLE;
	m_nVAlign = sfdvBASESHAPE_VALIGN;
	m_nHAlign = sfdvBASESHAPE_HALIGN;
	m_nVBorder = sfdvBASESHAPE_VBORDER;
	m_nHBorder = sfdvBASESHAPE_HBORDER;

	wxSFShapeBase* m_pParentShape = GetParentShape();
	if(m_pParentShape)m_nRelativePosition = pos - m_pParentShape->GetAbsolutePosition();
	else
		m_nRelativePosition = sfdvBASESHAPE_POSITION;

    // mark serialized properties
    XS_SERIALIZE(m_nId, wxT("id"));
    XS_SERIALIZE_EX(m_fActive, wxT("active"), sfdvBASESHAPE_ACTIVITY);
    XS_SERIALIZE_EX(m_fVisible, wxT("visibility"), sfdvBASESHAPE_VISIBILITY);
    XS_SERIALIZE_EX(m_nStyle, wxT("style"), sfdvBASESHAPE_DEFAULT_STYLE);
    XS_SERIALIZE(m_arrAcceptedChildren, wxT("accepted_children"));
    XS_SERIALIZE(m_arrAcceptedConnections, wxT("accepted_connections"));
    XS_SERIALIZE(m_arrAcceptedSrcNeighbours, wxT("accepted_src_neighbours"));
    XS_SERIALIZE(m_arrAcceptedTrgNeighbours, wxT("accepted_trg_neighbours"));
    XS_SERIALIZE_EX(m_nHoverColor, wxT("hover_color"), sfdvBASESHAPE_HOVERCOLOUR);
    XS_SERIALIZE(m_nRelativePosition, wxT("relative_position"));
#if wxCHECK_VERSION(2, 8, 0)
    XS_SERIALIZE_LONG_EX(m_nHAlign, wxT("halign"), sfdvBASESHAPE_HALIGN);
#else // replacement code for old version
	long int temp = m_nHAlign;
	AddProperty(new xsProperty(&temp, wxString(wxT("halign")), sfdvBASESHAPE_HALIGN));
#endif
#if wxCHECK_VERSION(2, 8, 0)
    XS_SERIALIZE_LONG_EX(m_nVAlign, wxT("valign"), (long)sfdvBASESHAPE_VALIGN);
#else // replacement code for old version
	temp = m_nVAlign;
	AddProperty(new xsProperty(&temp, wxString(wxT("valign")), sfdvBASESHAPE_VALIGN));
#endif
    XS_SERIALIZE_EX(m_nHBorder, wxT("hborder"), sfdvBASESHAPE_HBORDER);
    XS_SERIALIZE_EX(m_nVBorder, wxT("vborder"), sfdvBASESHAPE_VBORDER);
    XS_SERIALIZE(m_pUserData, wxT("user_data"));

	m_lstHandles.DeleteContents(true);
}

wxSFShapeBase::wxSFShapeBase(wxSFShapeBase& obj) : xsSerializable(obj)
{
	// initialize data members
	m_fSelected = obj.m_fSelected;
	m_fMouseOver = obj.m_fMouseOver;
	m_fFirstMove = obj.m_fFirstMove;
	m_fVisible = obj.m_fVisible;
	m_fActive = obj.m_fActive;
	m_nStyle = obj.m_nStyle;
	m_nVAlign = obj.m_nVAlign;
	m_nHAlign = obj.m_nHAlign;
	m_nVBorder = obj.m_nVBorder;
	m_nHBorder = obj.m_nHBorder;

	WX_APPEND_ARRAY(m_arrAcceptedChildren, obj.m_arrAcceptedChildren);
	WX_APPEND_ARRAY(m_arrAcceptedSrcNeighbours, obj.m_arrAcceptedSrcNeighbours);
	WX_APPEND_ARRAY(m_arrAcceptedTrgNeighbours, obj.m_arrAcceptedTrgNeighbours);
	WX_APPEND_ARRAY(m_arrAcceptedConnections, obj.m_arrAcceptedConnections);

	m_nHoverColor = obj.m_nHoverColor;

	m_nRelativePosition = obj.m_nRelativePosition;

	m_pParentManager = obj.m_pParentManager;
    m_pUserData = obj.m_pUserData;

    // copy serialized properties
    wxPropertyListNode* node = obj.m_lstProperties.GetFirst();
    while(node)
    {
        m_lstProperties.Append(node->GetData());
        node = node->GetNext();
    }

    m_lstHandles.DeleteContents(true);
}

wxSFShapeBase::~wxSFShapeBase(void)
{
	// clear handles
	m_lstHandles.Clear();
	// delete user data
	if(m_pUserData && (m_nStyle & sfsDELETE_USER_DATA))delete m_pUserData;
}


//----------------------------------------------------------------------------------//
// Public functions
//----------------------------------------------------------------------------------//

wxRect wxSFShapeBase::GetBoundingBox()
{
	// HINT: overload it for custom actions...

	return wxRect();
}

void wxSFShapeBase::GetCompleteBoundingBox(wxRect &rct, int mask)
{
    m_lstProcessed.Clear();
    _GetCompleteBoundingBox(rct, mask);
}

void wxSFShapeBase::_GetCompleteBoundingBox(wxRect &rct, int mask)
{
    //wxASSERT(m_pParentManager);
    if(!m_pParentManager)return;

    if( m_lstProcessed.IndexOf(this) != wxNOT_FOUND )return;
    else
        m_lstProcessed.Append(this);

	ShapeList lstChildren;
	//SerializableList lstConnections;

	// firts, get bounding box of the current shape
	if(mask & bbSELF)
	{
		if(rct.IsEmpty())rct = this->GetBoundingBox().Inflate((int)m_nHBorder, (int)m_nVBorder);
		else
			rct.Union(this->GetBoundingBox().Inflate((int)m_nHBorder, (int)m_nVBorder));
	}
	else
		mask |= bbSELF;

	// get list of all connection lines assigned to the shape and find their child shapes
	if(mask & bbCONNECTIONS)
	{
		wxSFShapeBase *pLine;

        ShapeList lstLines;
        m_pParentManager->GetAssignedConnections(this, lineBOTH, lstLines);

		wxShapeListNode* node = lstLines.GetFirst();
		while(node)
		{
			pLine = node->GetData();

			//rct.Union(pLine->GetBoundingBox());
			lstChildren.Append(pLine);

			// get children of the connections
			pLine->GetChildren(lstChildren);

			node = node->GetNext();
		}
	}

	// get children of this shape
	if(mask & bbCHILDREN)
	{
		this->GetChildren(lstChildren);

		// now, call this function for all children recursively...
		wxShapeListNode* node = lstChildren.GetFirst();
		while(node)
		{
		    node->GetData()->_GetCompleteBoundingBox(rct, mask);
			node = node->GetNext();
		}
	}
}

bool wxSFShapeBase::IsInside(const wxPoint& pos)
{
	// HINT: overload it for custom actions...

#if wxCHECK_VERSION(2, 8, 0)
	return this->GetBoundingBox().Contains(pos);
#else // replacement code for old version
	return this->GetBoundingBox().Inside(pos);
#endif
}

bool wxSFShapeBase::Intersects(const wxRect& rct)
{
	// HINT: overload it for custom actions...

	return rct.Intersects(this->GetBoundingBox());
}

wxRealPoint wxSFShapeBase::GetAbsolutePosition()
{
	// HINT: overload it for custom actions...

	wxSFShapeBase* m_pParentShape = GetParentShape();
	if(m_pParentShape)
	{
		return m_nRelativePosition + m_pParentShape->GetAbsolutePosition();
	}
	else
		return m_nRelativePosition;
}

wxRealPoint wxSFShapeBase::GetCenter()
{
    // HINT: override it for custom actions

    wxRect shpBB = this->GetBoundingBox();
    return wxRealPoint(shpBB.GetLeft() + shpBB.GetWidth()/2, shpBB.GetTop() + shpBB.GetHeight()/2);
}

wxRealPoint wxSFShapeBase::GetBorderPoint(const wxRealPoint& to)
{
    // HINT: override it for custom actions

    return wxRealPoint();
}

void wxSFShapeBase::ShowHandles(bool show)
{
	wxCHandleListNode *node = m_lstHandles.GetFirst();
	while(node)
	{
		node->GetData()->Show(show);
		node = node->GetNext();
	}
}

void wxSFShapeBase::MoveTo(double x, double y)
{
	// HINT: overload it for custom actions...

	wxSFShapeBase* m_pParentShape = GetParentShape();
	if(m_pParentShape)
	{
		m_nRelativePosition = wxRealPoint(x, y) - m_pParentShape->GetAbsolutePosition();
	}
	else
	{
		m_nRelativePosition.x = x;
		m_nRelativePosition.y = y;
	}
}

void wxSFShapeBase::MoveTo(const wxRealPoint& pos)
{
	this->MoveTo(pos.x, pos.y);
}

void wxSFShapeBase::MoveBy(double x, double y)
{
	// HINT: overload it for custom actions...

	m_nRelativePosition.x += x;
	m_nRelativePosition.y += y;
}

void wxSFShapeBase::MoveBy(const wxRealPoint& delta)
{
	this->MoveBy(delta.x, delta.y);
}

void wxSFShapeBase::Scale(double x, double y, bool children)
{
	// HINT: overload it for custom actions...

	if(children)
	{
	    ScaleChildren(x, y);
	}

    Update();
}

void wxSFShapeBase::Scale(const wxRealPoint& scale, bool children)
{
	this->Scale(scale.x, scale.y, children);
}

void wxSFShapeBase::ScaleChildren(double x, double y)
{
	ShapeList m_lstChildren;
	GetChildren(m_lstChildren, sfRECURSIVE);

	wxShapeListNode *node = m_lstChildren.GetFirst();
	while(node)
	{
		wxSFShapeBase* pShape = node->GetData();

        if((pShape->GetStyle() & sfsSIZE_CHANGE) && !pShape->IsKindOf(CLASSINFO(wxSFTextShape)))
		{
		    pShape->Scale(x, y, sfWITHOUTCHILDREN);
		}

		if( (pShape->GetVAlign() == valignNONE) || (pShape->GetHAlign() == halignNONE) )
		{
            pShape->SetRelativePosition(pShape->GetRelativePosition().x*x, pShape->GetRelativePosition().y*y);
		}

        // re-align shapes which have set any alignment mode
		pShape->DoAlignment();

		node = node->GetNext();
	}
}

void wxSFShapeBase::Update()
{
    // do self-alignment
    DoAlignment();

    // fit the shape to its children
    this->FitToChildren();

    // do alignment of shape's children (if required)
    if( !this->IsKindOf(CLASSINFO(wxSFLineShape)) )
    {
        wxShapeListNode* node = (wxShapeListNode*)GetFirstChildNode();
        while(node)
        {
            node->GetData()->DoAlignment();
            node = node->GetNext();
        }
    }

    // do it recursively on all parent shapes
    if( GetParentShape() )GetParentShape()->Update();
}

bool wxSFShapeBase::AcceptCurrentlyDraggedShapes()
{
    //wxASSERT(m_pParentManager);
    //wxASSERT(m_pParentManager->GetShapeCanvas());

    if(!m_pParentManager || !m_pParentManager->GetShapeCanvas())return false;

    if(!IsChildAccepted(wxT("All")))
    {
        ShapeList lstSelection;
        m_pParentManager->GetShapeCanvas()->GetSelectedShapes(lstSelection);

        wxShapeListNode* node = lstSelection.GetFirst();
        while(node)
        {
            if(m_arrAcceptedChildren.Index(node->GetData()->GetClassInfo()->GetClassName()) == wxNOT_FOUND)return false;
            node = node->GetNext();
        }
    }
	return true;
}

bool wxSFShapeBase::IsChildAccepted(const wxString& type)
{
    if( m_arrAcceptedChildren.Index(type) != wxNOT_FOUND )return true;
    else if( m_arrAcceptedChildren.Index(wxT("All")) != wxNOT_FOUND )return true;
    else
        return false;
}

bool wxSFShapeBase::IsSrcNeighbourAccepted(const wxString& type)
{
    if( m_arrAcceptedSrcNeighbours.Index(type) != wxNOT_FOUND )return true;
    else if( m_arrAcceptedSrcNeighbours.Index(wxT("All")) != wxNOT_FOUND )return true;
    else
        return false;
}

bool wxSFShapeBase::IsTrgNeighbourAccepted(const wxString& type)
{
    if( m_arrAcceptedTrgNeighbours.Index(type) != wxNOT_FOUND )return true;
    else if( m_arrAcceptedTrgNeighbours.Index(wxT("All")) != wxNOT_FOUND )return true;
    else
        return false;
}

bool wxSFShapeBase::IsConnectionAccepted(const wxString& type)
{
    if( m_arrAcceptedConnections.Index(type) != wxNOT_FOUND )return true;
    else if( m_arrAcceptedConnections.Index(wxT("All")) != wxNOT_FOUND )return true;
    else
        return false;
}

void wxSFShapeBase::FitToChildren()
{
	// HINT: overload it for custom actions...

	/*wxSFShapeBase* m_pParentShape = GetParentShape();
	if(m_pParentShape)m_pParentShape->FitToChildren();*/
}

wxSFShapeBase* wxSFShapeBase::GetParentShape()
{
    //wxASSERT(m_pParentManager);

    if(m_pParentManager && (m_pParentManager->GetRootItem() != m_pParentItem) )
    {
        return (wxSFShapeBase*)m_pParentItem;
    }
    else
        return NULL;
}

void wxSFShapeBase::SetUserData(xsSerializable* data)
{
    m_pUserData = data;
    if( m_pUserData )
    {
        // let associated data to know its parent shape
        m_pUserData->SetParent(this);
    }
}

//----------------------------------------------------------------------------------//
// Drawing functions
//----------------------------------------------------------------------------------//

void wxSFShapeBase::Refresh()
{
    Refresh(this->GetBoundingBox());
}

void wxSFShapeBase::Draw(wxSFScaledPaintDC& dc, bool children)
{
    if(!m_pParentManager || !m_pParentManager->GetShapeCanvas())return;
    if(!m_fVisible)return;

	// first, draw itself
	if(m_fMouseOver && ( m_fHighlighParent || (m_nStyle & sfsHOVERING) ))
	{
		if(m_fHighlighParent)
		{
			this->DrawHighlighted(dc);
		}
		else
			this->DrawHover(dc);
	}
	else this->DrawNormal(dc);

	if(m_fSelected)this->DrawSelected(dc);

	// ... then draw child shapes
	if(children)
	{
        wxShapeListNode *node = (wxShapeListNode*)GetFirstChildNode();
        while(node)
        {
            node->GetData()->Draw(dc);
            node = node->GetNext();
        }
	}
}

void wxSFShapeBase::DrawNormal(wxSFScaledPaintDC& dc)
{
	// HINT: overload it for custom actions...
}

void wxSFShapeBase::DrawSelected(wxSFScaledPaintDC& dc)
{
	// HINT: overload it for custom actions...

	wxCHandleListNode *node = m_lstHandles.GetFirst();
	while(node)
	{
		node->GetData()->Draw(dc);
		node = node->GetNext();
	}
}

void wxSFShapeBase::DrawHover(wxSFScaledPaintDC& dc)
{
	// HINT: overload it for custom actions...
}

void wxSFShapeBase::DrawHighlighted(wxSFScaledPaintDC& dc)
{
	// HINT: overload it for custom actions...
}

//----------------------------------------------------------------------------------//
// other functions
//----------------------------------------------------------------------------------//

void wxSFShapeBase::CreateHandles()
{
	// HINT: overload it for custom actions...
}

void wxSFShapeBase::GetChildren(ShapeList& children, bool recursive)
{
    wxSerializableListNode *node = GetFirstChildNode();
    while(node)
    {
        wxSFShapeBase *pShape = (wxSFShapeBase*)node->GetData();

        children.Append(pShape);
        if(recursive)pShape->GetChildren(children, recursive);

        node = node->GetNext();
    }
}

void wxSFShapeBase::GetNeighbours(ShapeList& neighbours, CONNECTMODE condir, bool direct)
{
    if( !this->IsKindOf(CLASSINFO(wxSFLineShape)) )
    {
        m_lstProcessed.Clear();
        this->_GetNeighbours(neighbours, condir, direct);
        // delete starting object if necessary (can be added in a case of complex connection network)
        neighbours.DeleteObject(this);
    }
}

void wxSFShapeBase::_GetNeighbours(ShapeList& neighbours, CONNECTMODE condir, bool direct)
{
    //wxASSERT(m_pParentManager);

    if( m_pParentManager )
    {
        if( m_lstProcessed.IndexOf(this) != wxNOT_FOUND )return;

        ShapeList lstConnections;
        wxSFLineShape *pLine;
        wxSFShapeBase *pOposite = NULL;

        m_pParentManager->GetAssignedConnections(this, condir, lstConnections);

        // find oposite shpes in direct branches
        wxShapeListNode *node = lstConnections.GetFirst();
        while(node)
        {
            pLine = (wxSFLineShape*)node->GetData();
            switch(condir)
            {
                case lineSTARTING:
                    pOposite = m_pParentManager->FindShape(pLine->GetTrgShapeId());
                    break;

                case lineENDING:
                    pOposite = m_pParentManager->FindShape(pLine->GetSrcShapeId());
                    break;

                case lineBOTH:
                    {
                        if(m_nId == pLine->GetSrcShapeId())pOposite = m_pParentManager->FindShape(pLine->GetTrgShapeId());
                        else
                            pOposite = m_pParentManager->FindShape(pLine->GetSrcShapeId());
                    }
            }

            // add oposite shape to the list (if applicable)
            if(pOposite && !pOposite->IsKindOf(CLASSINFO(wxSFLineShape)) && ( neighbours.IndexOf(pOposite) == wxNOT_FOUND )) neighbours.Append(pOposite);

            // find next shapes
            if( !direct && pOposite )
            {
                // in the case of indirect branches we must differentiate between connections
                // and ordinary shapes
                m_lstProcessed.Append(this);

                if( pOposite->IsKindOf(CLASSINFO(wxSFLineShape)) )
                {
                    pLine = (wxSFLineShape*)pOposite;
                    switch(condir)
                    {
                        case lineSTARTING:
                            {
                                pOposite = m_pParentManager->FindShape( pLine->GetSrcShapeId() );

                                if( pOposite->IsKindOf(CLASSINFO(wxSFLineShape)) )pOposite->_GetNeighbours(neighbours, condir, direct);
                                else if( neighbours.IndexOf(pOposite) == wxNOT_FOUND )neighbours.Append(pOposite);
                            }
                            break;

                        case lineENDING:
                            {
                                pOposite = m_pParentManager->FindShape( pLine->GetTrgShapeId() );

                                if( pOposite->IsKindOf(CLASSINFO(wxSFLineShape)) )pOposite->_GetNeighbours(neighbours, condir, direct);
                                else if( neighbours.IndexOf(pOposite) == wxNOT_FOUND )neighbours.Append(pOposite);
                            }
                            break;

                        case lineBOTH:
                            {
                                pOposite = m_pParentManager->FindShape( pLine->GetSrcShapeId() );
                                if( pOposite->IsKindOf(CLASSINFO(wxSFLineShape)) )pOposite->_GetNeighbours(neighbours, condir, direct);
                                else if( neighbours.IndexOf(pOposite) == wxNOT_FOUND )neighbours.Append(pOposite);

                                pOposite = m_pParentManager->FindShape( pLine->GetTrgShapeId() );
                                if( pOposite->IsKindOf(CLASSINFO(wxSFLineShape)) )pOposite->_GetNeighbours(neighbours, condir, direct);
                                else if( neighbours.IndexOf(pOposite) == wxNOT_FOUND )neighbours.Append(pOposite);
                            }
                            break;
                    }
                }
                else
                    pLine->_GetNeighbours(neighbours, condir, direct);
            }

            node = node->GetNext();
        }
    }
}

wxSFShapeCanvas* wxSFShapeBase::GetParentCanvas()
{
    //wxASSERT(m_pParentManager);
    if( !m_pParentManager )return NULL;

    return m_pParentManager->GetShapeCanvas();
}

void wxSFShapeBase::Refresh(const wxRect& rct)
{
    //wxASSERT(m_pParentManager);
    //wxASSERT(m_pParentManager->GetShapeCanvas());

	if(m_pParentManager && m_pParentManager->GetShapeCanvas())
	{
		m_pParentManager->GetShapeCanvas()->RefreshCanvas(false, rct);
	}
}

wxSFShapeHandle* wxSFShapeBase::GetHandle(wxSFShapeHandle::HANDLETYPE type, long id)
{
	wxCHandleListNode *node = m_lstHandles.GetFirst();
	while(node)
	{
		wxSFShapeHandle *hnd = node->GetData();
		if((hnd->GetType() == type) && ((id == -1)||(id == hnd->GetId())))return hnd;
		node = node->GetNext();
	}
	return NULL;
}

void wxSFShapeBase::AddHandle(wxSFShapeHandle::HANDLETYPE type, long id)
{
	wxSFShapeHandle* pHnd = GetHandle(type, id);
	if(!pHnd)
	{
		m_lstHandles.Append(new wxSFShapeHandle(this, type, id));
	}
}

void wxSFShapeBase::RemoveHandle(wxSFShapeHandle::HANDLETYPE type, long id)
{
	wxSFShapeHandle* pHnd = GetHandle(type, id);
	if(pHnd)
	{
		m_lstHandles.DeleteObject(pHnd);
	}
}

void wxSFShapeBase::DoAlignment()
{
    wxSFShapeBase *pParent = this->GetParentShape();

    if(pParent)
    {
        wxRect parentBB;
        if(pParent->IsKindOf(CLASSINFO(wxSFLineShape)))
        {
            wxRealPoint pos = pParent->GetAbsolutePosition();
            parentBB = wxRect((int)pos.x, (int)pos.y, 1, 1);
        }
        else
            parentBB = pParent->GetBoundingBox();

        wxRect shapeBB = this->GetBoundingBox();


        // do vertical alignment
        switch(m_nVAlign)
        {
            case valignTOP:
                m_nRelativePosition.y = m_nVBorder;
                break;

            case valignMIDDLE:
                m_nRelativePosition.y = parentBB.GetHeight()/2 - shapeBB.GetHeight()/2;
                break;

            case valignBOTTOM:
                m_nRelativePosition.y = parentBB.GetHeight() - shapeBB.GetHeight() - m_nVBorder;

            default:
                break;
        }

        // do horizontal alignment
        switch(m_nHAlign)
        {
            case halignLEFT:
                m_nRelativePosition.x = m_nHBorder;
                break;

            case halignCENTER:
                m_nRelativePosition.x = parentBB.GetWidth()/2 - shapeBB.GetWidth()/2;
                break;

            case halignRIGHT:
                m_nRelativePosition.x = parentBB.GetWidth() - shapeBB.GetWidth() - m_nHBorder;

            default:
                break;
        }
    }
}

//----------------------------------------------------------------------------------//
// Events handling
//----------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------//
// Public virtual event handlers

void wxSFShapeBase::OnLeftClick(const wxPoint& pos)
{
	// HINT: overload it for custom actions...
}

void wxSFShapeBase::OnRightClick(const wxPoint& pos)
{
	// HINT: overload it for custom actions...
}

void wxSFShapeBase::OnLeftDoubleClick(const wxPoint& pos)
{
	// HINT: overload it for custom actions...
}

void wxSFShapeBase::OnRightDoubleClick(const wxPoint& pos)
{
	// HINT: overload it for custom actions...
}

void wxSFShapeBase::OnBeginDrag(const wxPoint& pos)
{
	// HINT: overload it for custom actions...
}

void wxSFShapeBase::OnDragging(const wxPoint& pos)
{
	// HINT: overload it for custom actions...
}

void wxSFShapeBase::OnEndDrag(const wxPoint& pos)
{
	// HINT: overload it for custom actions...
}

void wxSFShapeBase::OnHandle(wxSFShapeHandle& handle)
{
	// HINT: overload it for custom actions...
}

void wxSFShapeBase::OnBeginHandle(wxSFShapeHandle& handle)
{
	// HINT: overload it for custom actions...
}

void wxSFShapeBase::OnEndHandle(wxSFShapeHandle& handle)
{
	// HINT: overload it for custom actions...
}

bool wxSFShapeBase::OnKey(int key)
{
	// HINT: overload it for custom actions...

    return TRUE;
}

void wxSFShapeBase::OnMouseEnter(const wxPoint& pos)
{
	// HINT: overload it for custom actions...
}

void wxSFShapeBase::OnMouseOver(const wxPoint& pos)
{
	// HINT: overload it for custom actions...
}

void wxSFShapeBase::OnMouseLeave(const wxPoint& pos)
{
	// HINT: overload it for custom actions...
}

//----------------------------------------------------------------------------------//
// Original private event handlers

void wxSFShapeBase::_OnBeginDrag(const wxPoint& pos)
{
	m_fFirstMove = true;

	this->OnBeginDrag(pos);
}

void wxSFShapeBase::_OnDragging(const wxPoint& pos)
{
    //wxASSERT(m_pParentManager);
    if( !m_pParentManager )return;

//	if(m_fVisible && m_fActive && m_fPositionChange)
	if(m_fVisible && m_fActive && (m_nStyle & sfsPOSITION_CHANGE))
	{
		if(m_fFirstMove)
		{
			m_nMouseOffset = wxRealPoint(pos.x, pos.y) - this->GetAbsolutePosition();
		}

        // get shape BB BEFORE movement and combine it with BB of assigned lines
		wxRect prevBB;
		GetCompleteBoundingBox(prevBB, bbSELF | bbCONNECTIONS | bbCHILDREN);

		this->MoveTo(pos.x - m_nMouseOffset.x, pos.y - m_nMouseOffset.y);
        this->OnDragging(pos);

        // get shape BB AFTER movement and combine it with BB of assigned lines
		wxRect currBB;
		GetCompleteBoundingBox(currBB, bbSELF | bbCONNECTIONS | bbCHILDREN);

		// update canvas
		if(m_pParentManager->GetShapeCanvas())
		{
			const wxRect unionRect = prevBB.Union(currBB);
			Refresh(unionRect);
		}

		m_fFirstMove = false;
	}
}

void wxSFShapeBase::_OnEndDrag(const wxPoint& pos)
{
    this->OnEndDrag(pos);
}

void wxSFShapeBase::_OnMouseMove(const wxPoint& pos)
{
    //wxASSERT(m_pParentManager);
    if( !m_pParentManager )return;

	if(m_fVisible && m_fActive)
	{
		bool fUpdateShape = false;
		wxSFShapeCanvas *pCanvas = m_pParentManager->GetShapeCanvas();

		// send the event to child handles too...
		wxCHandleListNode *node = m_lstHandles.GetFirst();
		while(node)
		{
			node->GetData()->OnMouseMove(pos);
			node = node->GetNext();
		}

		// determine, whether the shape should be highlighted for any reason
		if(pCanvas)
		{
		    switch(pCanvas->GetMode())
		    {
            case wxSFShapeCanvas::modeSHAPEMOVE:
                {
                    if(ContainsStyle(sfsHIGHLIGHTING))
                    {
                        if(pCanvas->GetShapeAtPosition(pos, 1, wxSFShapeCanvas::searchUNSELECTED) == this)
                        {
                            fUpdateShape = m_fHighlighParent = AcceptCurrentlyDraggedShapes();
                        }
                    }
                }
                break;

            case wxSFShapeCanvas::modeHANDLEMOVE:
                {
                    if(ContainsStyle(sfsHOVERING))
                    {
                        if(pCanvas->GetShapeAtPosition(pos, 1, wxSFShapeCanvas::searchUNSELECTED) == this)fUpdateShape = true;
                        m_fHighlighParent = false;
                    }
                }
                break;

            default:
                {
                    if(ContainsStyle(sfsHOVERING))
                    {
                        if(pCanvas->GetShapeAtPosition(pos) == this)fUpdateShape = true;
                        m_fHighlighParent = false;
                    }
                }
                break;
		    }
		}

		if(IsInside(pos) && fUpdateShape)
		{
			if(!m_fMouseOver)
			{
				m_fMouseOver = true;
				this->OnMouseEnter(pos);
			}
			else
			    this->OnMouseOver(pos);

			Refresh();
		}
		else
		{
			if(m_fMouseOver)
			{
				m_fMouseOver = false;
				this->OnMouseLeave(pos);
				Refresh();
			}
		}
	}
}

void wxSFShapeBase::_OnKey(int key)
{
    //wxASSERT(m_pParentManager);

    if(!m_pParentManager)return;

    wxSFShapeCanvas *pCanvas = m_pParentManager->GetShapeCanvas();

    //wxASSERT(pCanvas);

    if(!pCanvas)return;

	if(m_fVisible && m_fActive && m_fSelected)
	{
		double dx = 1, dy = 1;
		bool fRefreshAll = false;
		wxRect prevBB;


		if(pCanvas->IsGridUsed())
		{
			dx = pCanvas->GetGrid().x;
			dy = pCanvas->GetGrid().y;
		}

		ShapeList lstSelection;
		pCanvas->GetSelectedShapes(lstSelection);
		if((lstSelection.GetCount() > 1) && (lstSelection.IndexOf(this) != wxNOT_FOUND))
		{
		    fRefreshAll = true;
		}

		if(!fRefreshAll)
		{
            GetCompleteBoundingBox(prevBB, bbSELF | bbCONNECTIONS | bbCHILDREN);
		}

        if(this->OnKey(key))
        {
            switch(key)
            {
            case WXK_LEFT:
                if(ContainsStyle(sfsPOSITION_CHANGE))MoveBy(-dx, 0);
                break;

            case WXK_RIGHT:
                if(ContainsStyle(sfsPOSITION_CHANGE))MoveBy(dx, 0);
                break;

            case WXK_UP:
                if(ContainsStyle(sfsPOSITION_CHANGE))MoveBy(0, -dy);
                break;

            case WXK_DOWN:
                if(ContainsStyle(sfsPOSITION_CHANGE))MoveBy(0, dy);
                break;
            }
        }

        if(!fRefreshAll)
        {
            wxRect currBB;
            GetCompleteBoundingBox(currBB, bbSELF | bbCONNECTIONS | bbCHILDREN);

            prevBB.Union(currBB);
            Refresh(prevBB);
        }
        else
            pCanvas->Refresh(false);
	}
}

void wxSFShapeBase::_OnHandle(wxSFShapeHandle& handle)
{
   // wxASSERT(m_pParentManager);
    wxSFShapeBase* pChild;

    if( !m_pParentManager )return;

    // call appropriate user-defined handler
	this->OnHandle(handle);

    // align children
    wxShapeListNode *node = (wxShapeListNode*)GetFirstChildNode();
    while(node)
    {
        pChild = node->GetData();

        if((pChild->GetVAlign() != valignNONE) || (pChild->GetHAlign() != halignNONE))
        {
            node->GetData()->DoAlignment();
        }
        node = node->GetNext();
    }
    // update shape
    Update();

    // refresh canvas
    if( m_pParentManager->GetShapeCanvas() )m_pParentManager->GetShapeCanvas()->Refresh(false);

}
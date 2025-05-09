/***************************************************************
 * Name:      RectShapeXml.cpp
 * Purpose:   Implements rectangular shape's serialization cap.
 * Author:    Michal Bližňák (michal.bliznak@tiscali.cz)
 * Created:   2007-07-22
 * Copyright: Michal Bližňák
 * License:   wxWidgets license (www.wxwidgets.org)
 * Notes:
 **************************************************************/

#ifdef LINUX

#ifdef LBWXVERSION_CURRENT

#define IGNORE_THIS

#endif

#endif

#ifndef IGNORE_THIS

#include "RectShape.h"
#include "CommonFcn.h"

//----------------------------------------------------------------------------------//
// Serialization
//----------------------------------------------------------------------------------//

wxXmlNode* wxSFRectShape::Serialize(wxXmlNode* node)
{
	// HINT: overload it for custom actions...

	if(node)
	{
		node = wxSFShapeBase::Serialize(node);
	}

	return node;
}

void wxSFRectShape::Deserialize(wxXmlNode* node)
{
	// HINT: overload it for custom actions...

	wxSFShapeBase::Deserialize(node);
}

#endif

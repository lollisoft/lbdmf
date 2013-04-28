<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002-2013  Lothar Behrens (lothar.behrens@lollisoft.de)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
            Ginsterweg 4
            
            65760 Eschborn (germany)
-->
<xsl:output method="text"/>

<!-- Handling of found associations -->

<xsl:template name="Translate.Association.SqlServer">
    <xsl:param name="ID"/><!--  -->
    <xsl:param name="ReferencingClassID"/><!--  -->
    <xsl:param name="ReferencedClassID"/><!--  -->
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
	
-- Create a foreign key relation for <xsl:value-of select="$ReferencingClassID"/> to <xsl:value-of select="$ReferencedClassID"/>	
	
</xsl:template>

</xsl:stylesheet>

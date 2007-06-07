<?php

//
//  Copyright (C) 2004-2007 by Autodesk, Inc.
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of version 2.1 of the GNU Lesser
//  General Public License as published by the Free Software Foundation.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

class ErrorMessages
{
    const XmlNotFound = "Cannot open xml from describe schema";
    const XslNotFound = "Cannot find xsl file: displayschema.xsl";
    const SessionExpired = "Session has expired. Please refresh page.";
    const NullExtent = "Extent is null. Cannot display feature.";
}

class PageNavigation
{
    const First = "FIRST";
    const Prev = "PREV";
    const Next = "NEXT";
    const Last = "LAST";
    const Current = "Page %s of %s";
}

class ConfirmationDialog
{
    const Preview = "This feature source contains %s features. Would you like to continue?";
}

class DisplayHeadings
{
    const MainHeading = "Describe Schema";
    const ClassName = "Class: %s";
}

class FormText
{
    const InputResourceId = "Resource ID:";
    const InputSchema = "Schema:";
    const InputClass = "Class:";
    const FindButton = "Find";
}

?>

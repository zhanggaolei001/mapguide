//
//  Copyright (C) 2007 by Autodesk, Inc.
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

#ifndef TEXT_H_
#define TEXT_H_

#include "MdfModel.h"
#include "GraphicElement.h"
#include "TextFrame.h"

BEGIN_NAMESPACE_MDFMODEL

    //-------------------------------------------------------------------------
    // DESCRIPTION: Building block of the graphics of a SymbolDefinition.
    //-------------------------------------------------------------------------
    class MDFMODEL_API Text : public GraphicElement
    {
    public:
        // Construction, destruction, initialization
        Text();
        virtual ~Text();

        const MdfString& GetString() const;
        void SetString(const MdfString& string);

        const MdfString& GetFontName() const;
        void SetFontName(const MdfString& fontName);

        const MdfString& GetBold() const;
        void SetBold(const MdfString& bold);

        const MdfString& GetItalic() const;
        void SetItalic(const MdfString& italic);

        const MdfString& GetUnderlined() const;
        void SetUnderlined(const MdfString& underlined);

        const MdfString& GetHeight() const;
        void SetHeight(const MdfString& height);

        const MdfString& GetHeightScalable() const;
        void SetHeightScalable(const MdfString& heightScalable);

        const MdfString& GetPositionX() const;
        void SetPositionX(const MdfString& positionX);

        const MdfString& GetPositionY() const;
        void SetPositionY(const MdfString& positionY);

        const MdfString& GetAngle() const;
        void SetAngle(const MdfString& angle);

        const MdfString& GetHorizontalAlignment() const;
        void SetHorizontalAlignment(const MdfString& hAlignment);

        const MdfString& GetVerticalAlignment() const;
        void SetVerticalAlignment(const MdfString& vAlignment);

        const MdfString& GetJustification() const;
        void SetJustification(const MdfString& justification);

        const MdfString& GetLineSpacing() const;
        void SetLineSpacing(const MdfString& lineSpacing);

        const MdfString& GetTextColor() const;
        void SetTextColor(const MdfString& textColor);

        const MdfString& GetGhostColor() const;
        void SetGhostColor(const MdfString& ghostColor);

        TextFrame* GetFrame();
        void AdoptFrame(TextFrame* frame);
        TextFrame* OrphanFrame();

        virtual void AcceptVisitor(IGraphicElementVisitor& igeVisitor);

    private:
        // Hidden copy constructor and assignment operator.
        Text(const Text&);
        Text& operator=(const Text&);

        // Data members
        MdfString m_sString;
        MdfString m_sFontName;

        MdfString m_sBold;
        MdfString m_sItalic;
        MdfString m_sUnderlined;

        MdfString m_sHeight;
        MdfString m_sHeightScalable;
        MdfString m_sPositionX;
        MdfString m_sPositionY;
        MdfString m_sAngle;

        MdfString m_sHAlignment;
        MdfString m_sVAlignment;
        MdfString m_sJustification;

        MdfString m_sLineSpacing;
        MdfString m_sTextColor;
        MdfString m_sGhostColor;

        TextFrame* m_pFrame;
    };

END_NAMESPACE_MDFMODEL
#endif // TEXT_H_

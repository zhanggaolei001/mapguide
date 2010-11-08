//
//  Copyright (C) 2004-2010 by Autodesk, Inc.
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

#ifndef GRIDSURFACESTYLE_H_
#define GRIDSURFACESTYLE_H_

#include "FeatureTypeStyle.h"
#include <vector>

BEGIN_NAMESPACE_MDFMODEL

    //-------------------------------------------------------------------------
    // DESCRIPTION:
    // Class GridSurfaceStyle is used to specify how to calculate the pixel
    // elevation. It adjusts the elevation data before the graphic system shows
    // it for better appearance.
    //-------------------------------------------------------------------------
class MDFMODEL_API GridSurfaceStyle : public FeatureTypeStyle
    {
    public:
        GridSurfaceStyle();
        virtual ~GridSurfaceStyle();

        // Implementation of FeatureTypeStyle Visitor pattern method.
        virtual void AcceptVisitor(IFeatureTypeStyleVisitor& iftsVisitor);

        // Property : Band
        const MdfString& GetBand() const;
        void SetBand(const MdfString& strElevationBandName);

        // Property: ZeroValue, optional
        // Use 0 if not specified.
        double GetZeroValue() const;
        void SetZeroValue(double dZeroValue);

        // Property: Scale Factor, optional
        // Use 1 if not specified.
        double GetScaleFactor() const;
        void SetScaleFactor(double dScaleFactor);

        // Property: Default Color
        const MdfString& GetDefaultColor() const;
        void SetDefaultColor(const MdfString& strDefaultColor);

    private:
        // Hidden copy constructor and assignment operator.
        GridSurfaceStyle(const GridSurfaceStyle&);
        GridSurfaceStyle& operator=(const GridSurfaceStyle&);

        // Band
        MdfString m_strElevationBandName;

        // Zero Value
        double    m_dZeroValue;

        // Scale Factor
        double    m_dScaleFactor;

        // Default Color
        MdfString m_strDefaultColor;
    };

END_NAMESPACE_MDFMODEL
#endif // GRIDSURFACESTYLE_H_
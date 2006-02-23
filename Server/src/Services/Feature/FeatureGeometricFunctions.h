//
//  Copyright (C) 2004-2006  Autodesk, Inc.
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

#ifndef _MGFEATURE_GEOMETRIC_DISTRIBUTION_H_
#define _MGFEATURE_GEOMETRIC_DISTRIBUTION_H_

class MgDisposable;
class FdoFunction;
class MgReader;
class MgFeatureDistribution;
class MgGeometry;
class MgGeometryCollection;

class MgFeatureGeometricFunctions : public MgFeatureDistribution
{
    DECLARE_CLASSNAME(MgFeatureGeometricFunctions)

public:

    MgFeatureGeometricFunctions(MgReader* reader, FdoFunction* customFunction, CREFSTRING propertyAlias);
    virtual MgReader* Execute();

protected:

    MgFeatureGeometricFunctions();
    virtual ~MgFeatureGeometricFunctions();
    virtual void Dispose() { delete this; }

private:

    struct CoordinateCollection
    {
        std::vector<double> x_coords;
        std::vector<double> y_coords;
        std::vector<double> z_coords;
        std::vector<double> m_coords;
    };

    MgGeometry* GetValue();

    void Initialize(MgReader* reader, FdoFunction* customFunction, CREFSTRING propertyAlias);

    MgGeometryCollection* ExecuteOperation(MgGeometryCollection* geomCollection);
    MgGeometryCollection* ComputeExtents(MgGeometryCollection* geomCol);
    MgGeometry* ComputeExtents(CoordinateCollection& lowerLeft, CoordinateCollection& upperRight);
    void AddCoordinate(MgCoordinate* coord, CoordinateCollection& coords);

    MgReader* GetReader(MgGeometryCollection* returnGeom);

    void CheckSupportedPropertyType();

private:

    STRING m_propertyName;
    INT16 m_type;
    Ptr<MgReader> m_reader;
    FdoFunction* m_customFunction;
    STRING m_propertyAlias;
};

#endif

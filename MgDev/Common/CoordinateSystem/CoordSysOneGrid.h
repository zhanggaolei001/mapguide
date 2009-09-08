//
//  Copyright (C) 2004-2009 by Autodesk, Inc.
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

#ifndef _CCOORDINATESYSTEMGRIDBASE_H_
#define _CCOORDINATESYSTEMGRIDBASE_H_

namespace CSLibrary
{

///////////////////////////////////////////////////////////////////////////////
// CCoordinateSystemOneGrid
//
// An object which encapsulates the functionality of a single grid; a single
// grid being a grid based on one grid coordinate system and one viewport
// coordinate system.
//
// While a generic grid will always consist of a single instance of an object
// of this type, an MGRS grid (for example) may require several instances of
// this object, using different grid coordinate systems, to accurately
// represent the actual overall grid.  Thus, we encapsulate most basic grid
// functionality in this object.
//
// The object includes a STRING data member which can carry a label which users
// may use at their convenience.  This object does nothing with the label
// other than enable the user to set it and retrieve it.

class CCoordinateSystemOneGrid : public MgGuardDisposable
{
public:
    static const INT32 MaxCurvePoints;
    CCoordinateSystemOneGrid (void);
    CCoordinateSystemOneGrid (MgCoordinateSystemGridBoundary* frameBoundary,
                              MgCoordinateSystem* gridCRS,
                              MgCoordinateSystem* frameCRS);
    ~CCoordinateSystemOneGrid (void);

    void SetUp (MgCoordinateSystemGridBoundary* frameBoundary,
                MgCoordinateSystem* gridCRS,
                MgCoordinateSystem* frameCRS);

    // Returns true if the grid coordinate system is geographic; use this to
    // determine if this is a graticule (as opposed to a grid).
    bool IsGeographic (void);
    INT32 GetUserID (void);
    STRING GetLabel (void);
    void SetUserID (INT32 userID);
    void SetLabel (CREFSTRING label);

    MgCoordinate* ConvertToGrid (MgCoordinate* frameCoordinate);
    MgCoordinate* ConvertToFrame (MgCoordinate* gridCoordinate);
    MgCoordinateSystemGridLineCollection* GetGridLines (MgCoordinateSystemGridSpecification* specs);
    CCoordinateSystemGridTickCollection* GetBoundaryTicks (MgCoordinateSystemGridSpecification* specs);

protected:
    MgCoordinateSystem* GetFrameCRS (void);
    MgCoordinateSystem* GetGridCRS (void);
    void GenerateGridBoundary (double boundaryPrecision);
    void GetGeographicExtents (double& longMin,double& longMax,double& latMin,double& latMax,double precision = 1.0E-05);
    void GetGridExtents (double& eastMin,double& eastMax,double& northMin,double& northMax,double precision = 0.25);
    void Dispose (void);

    INT32 m_UserID;                                      // For user convenience (i.e. UTM zone)
    INT32 m_MaxCurvePoints;
    STRING m_Label;                                      // For user conveinence (i.e. MGRS)
    Ptr<MgCoordinateSystem> m_GridCRS;                   // The grid coordinate system
    Ptr<MgCoordinateSystem> m_FrameCRS;                  // The frame coordinate system
    Ptr<MgCoordinateSystemTransform> m_ToFrameXform;     // Converts grid coordinates to frame coordinates
    Ptr<MgCoordinateSystemTransform> m_ToGridXform;      // Converts frame coordinates to grid coordinates
    double m_BoundaryPrecision;                          // Precision at which the boundary conversion was perfromed
    Ptr<MgCoordinateSystemGridBoundary> m_FrameBoundary; // Grid boundary in frame coordinates
    Ptr<MgCoordinateSystemGridBoundary> m_GridBoundary;  // Grid boundary in grid coordinates

private:
    // Not implemented
    CCoordinateSystemOneGrid (const CCoordinateSystemOneGrid& source);
    CCoordinateSystemOneGrid& operator= (const CCoordinateSystemOneGrid& rhs);
};

//=============================================================================
// This object was invented to carry multiple MGRS grids, but is no longer used
// as there is now a CCoordinateSystemMgrsZone object and a related collection
// object.  WHen we're ready for code complete and we don't seem to need this
// for anything, we should delete it. 
class CCoordinateSystemGridCollection : public MgGuardDisposable
{
public:
    CCoordinateSystemGridCollection (void);
    ~CCoordinateSystemGridCollection (void);

    INT32 GetCount () const;
    CCoordinateSystemOneGrid* GetItem (INT32 index) const;
    void RemoveAt (INT32 index);
    void Clear();
    void SetItem (INT32 index, CCoordinateSystemOneGrid* value);
    void Add (CCoordinateSystemOneGrid* value);

protected:
    void Dispose (void);

private:
    // Data Members
    Ptr<MgDisposableCollection> m_OneGridCollection;

    // Member functions not implemented.
    CCoordinateSystemGridCollection  (const CCoordinateSystemGridCollection & source);
    CCoordinateSystemGridCollection& operator= (const CCoordinateSystemGridCollection & rhs);
};

}   /* namespace CSLibrary */

#endif /* _CCOORDINATESYSTEMGRIDBASE_H_ */

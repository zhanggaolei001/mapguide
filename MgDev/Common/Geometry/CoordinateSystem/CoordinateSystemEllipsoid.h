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

#ifndef _MGCOORDINATESYSTEMELLIPSOID_H_
#define _MGCOORDINATESYSTEMELLIPSOID_H_

class MgCoordinateSystemEllipsoid : public MgGuardDisposable
{
    DECLARE_CLASSNAME(MgCoordinateSystemEllipsoid)

PUBLISHED_API:
    virtual STRING GetCode()=0;  /// __get
    virtual void SetCode(CREFSTRING sCode)=0;
    virtual bool IsLegalCode(CREFSTRING sCode)=0;
    virtual bool IsValid()=0;
    virtual bool IsUsable()=0;
    virtual bool IsSameAs(MgGuardDisposable *pDef)=0;
    virtual MgCoordinateSystemEllipsoid* CreateClone()=0;
    virtual STRING GetDescription()=0;  /// __get
    virtual void SetDescription(CREFSTRING sDesc)=0;
    virtual bool IsLegalDescription(CREFSTRING sDesc)=0;
    virtual STRING GetGroup()=0;
    virtual void SetGroup(CREFSTRING sGroup)=0;
    virtual bool IsLegalGroup(CREFSTRING sGroup)=0;
    virtual STRING GetSource()=0;
    virtual void SetSource(CREFSTRING sSource)=0;
    virtual bool IsLegalSource(CREFSTRING sSource)=0;
    virtual bool IsProtected()=0;
    virtual INT16 GetAge()=0;
    virtual void SetProtectMode(bool bIsProtected)=0;
    virtual bool IsEncrypted()=0;
    virtual void SetEncryptMode(bool bIsEncrypted)=0;
    virtual double GetEquatorialRadius()=0;
    virtual double GetPolarRadius()=0;
    virtual double GetFlatteningRatio()=0;
    virtual double GetEccentricity()=0;
    virtual void SetRadii(double dEquatorialRadius, double dPolarRadius)=0;
    virtual double FlatteningRatioToEccentricity(double dFlat)=0;
    virtual double EccentricityToFlatteningRatio(double dEccent)=0;
    virtual double EquatorialRadiusFromPolarRadiusFlatteningRatio(double dPolarRadius, double dFlatteningRatio)=0;
    virtual double PolarRadiusFromEquatorialRadiusFlatteningRatio(double dEquatorialRadius, double dFlatteningRatio)=0;
    virtual double GetGreatCircleDistance(double dLongitude1, double dLatitude1, double dLongitude2, double dLatitude2)=0;
    virtual double GetGreatCircleAzimuth(double dLongitude1, double dLatitude1, double dLongitude2, double dLatitude2)=0;
    virtual double GetRadiusMin()=0;
    virtual double GetRadiusMax()=0;
    virtual bool IsLegalRadius(double dRadius)=0;
    virtual double GetFlatteningRatioMin()=0;
    virtual double GetFlatteningRatioMax()=0;
    virtual bool IsLegalFlatteningRatio(double dFlat)=0;
    virtual double FlatteningRatioFromRadii(double dEquatorialRadius, double dPolarRadius)=0;
    virtual MgCoordinateSystemCatalog* GetCatalog()=0;

protected:
    /////////////////////////////////////////////////////////////////
    /// \brief
    /// Get the class Id
    ///
    /// \return
    /// The integer value
    ///
    INT32 GetClassId(){return m_cls_id;};

CLASS_ID:
    static const INT32 m_cls_id = CoordinateSystem_CoordinateSystemEllipsoid;
};

#endif //_MGCOORDINATESYSTEMELLIPSOID_H_

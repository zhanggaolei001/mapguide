/*
 * Copyright (c) 2001-2006
 *     DecisionSoft Limited. All rights reserved.
 * Copyright (c) 2004-2006
 *     Progress Software Corporation. All rights reserved.
 * Copyright (c) 2004-2006
 *     Oracle. All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 *
 * $Id: ATAnySimpleTypeImpl.hpp,v 1.7 2006/11/01 16:37:20 jpcs Exp $
 */

#ifndef _ATANYSIMPLETYPEIMPL_HPP
#define _ATANYSIMPLETYPEIMPL_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xqilla/items/ATAnySimpleType.hpp>

#include <xqilla/framework/XQillaExport.hpp>
class DynamicContext;

/**
 * This class represents the atomic types (ie, the simple types 
 * which are not list or union types) with type annotation
 * xs:anySimpleType */
class XQILLA_API ATAnySimpleTypeImpl : public ATAnySimpleType
{

public:

  /* constructor */
  ATAnySimpleTypeImpl(const XMLCh*, const XMLCh*, const XMLCh* value, const StaticContext* context);

  virtual void *getInterface(const XMLCh *name) const;

  /* Get the name of the primitive type (basic type) of this type
   * (ie "decimal" for xs:decimal) */
  virtual const XMLCh* getPrimitiveTypeName() const;

  /* Get the namespace URI for this type */
  virtual const XMLCh* getTypeURI() const;

  /* Get the name of this type  (ie "integer" for xs:integer) */
  virtual const XMLCh* getTypeName() const;

  /* returns the XMLCh* (canonical) representation of this type */
  virtual const XMLCh* asString(const DynamicContext* context) const;

  /* returns true if the two objects' URI are equal (string comparison)
   * false otherwise */
  virtual bool equals(const AnyAtomicType::Ptr &target, const DynamicContext* context) const;
  
  /* Get the primitive index associated with this type */
  static AnyAtomicType::AtomicObjectType getTypeIndex(); 

  /* Get the primitive type name */
  static const XMLCh* getPrimitiveName();

  /* Get the primitive index associated with this type */
  virtual AnyAtomicType::AtomicObjectType getPrimitiveTypeIndex() const;

protected:
  
  /* If possible, cast this type to the target type */
  virtual AnyAtomicType::Ptr castAsInternal(AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) const;

private:

  /*The value of this URI*/
  const XMLCh* _value;
 
};

#endif // _ATANYSIMPLETYPEIMPL_HPP

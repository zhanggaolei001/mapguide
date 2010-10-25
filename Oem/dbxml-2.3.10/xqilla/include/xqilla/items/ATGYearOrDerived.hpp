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
 * $Id: ATGYearOrDerived.hpp,v 1.8 2006/11/01 16:37:14 jpcs Exp $
 */

#ifndef _ATGYEARORDERIVED_HPP
#define _ATGYEARORDERIVED_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/items/DateOrTimeType.hpp>
#include <xqilla/items/Timezone.hpp>

class DynamicContext;

class XQILLA_API ATGYearOrDerived : public DateOrTimeType
{
public:
  typedef RefCountPointer<const ATGYearOrDerived> Ptr;

  /* Get the name of the primitive type (basic type) of this type
   * (ie "decimal" for xs:decimal) */
  virtual const XMLCh* getPrimitiveTypeName() const = 0;

  /* Get the namespace URI for this type */
  virtual const XMLCh* getTypeURI() const = 0;

  /* Get the name of this type  (ie "integer" for xs:integer) */
  virtual const XMLCh* getTypeName() const = 0;

  /* returns the XMLCh* (canonical) representation of this type */
  virtual const XMLCh* asString(const DynamicContext* context) const = 0;

  /* returns true if the two objects are equal 
   * false otherwise */
  virtual bool equals(const AnyAtomicType::Ptr &target, const DynamicContext* context) const = 0;

  /** Returns less than 0 if this is less that other,
      0 if they are the same, and greater than 0 otherwise */
  virtual int compare(const ATGYearOrDerived::Ptr &other, const DynamicContext *context) const = 0;
 
  /** Returns true if a timezone is defined for this.  False otherwise.*/
  virtual bool hasTimezone() const = 0;

  /** Sets the timezone to the given timezone.*/
  virtual ATGYearOrDerived::Ptr setTimezone(const Timezone::Ptr &timezone, const DynamicContext* context) const = 0;

  virtual AnyAtomicType::AtomicObjectType getPrimitiveTypeIndex() const = 0;
};

#endif //  _ATGYEARORDERIVED_HPP
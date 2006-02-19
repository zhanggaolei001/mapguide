/*
 * Copyright (c) 2001, DecisionSoft Limited All rights reserved.
 * Please see LICENSE.TXT for more information.
 */

#include "../config/pathan_config.h"
#include <assert.h>
#include <pathan/operators/GreaterThanEqual.hpp>
#include <pathan/operators/LessThan.hpp>
#include <pathan/ATBooleanOrDerived.hpp>
#include <pathan/DynamicContext.hpp>
#include <pathan/internal/collations/CodepointCollation.hpp>
#include <pathan/exceptions/XPath2ErrorException.hpp>

/*static*/ const XMLCh GreaterThanEqual::name[]={ XERCES_CPP_NAMESPACE_QUALIFIER chLatin_g, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chNull };

GreaterThanEqual::GreaterThanEqual(const VectorOfDataItems &args, XPath2MemoryManager* memMgr)
  : ComparisonOperator(name, args, memMgr)
{
}

/*static*/ bool GreaterThanEqual::greater_than_equal(const AnyAtomicType::Ptr &arg1, const AnyAtomicType::Ptr &arg2, Collation* collation, DynamicContext* context)
{
    // A ge B numeric               numeric                 op:numeric-greater-than(A, B) or op:numeric-equal(A, B)
    // A ge B xs:boolean            xs:boolean              fn:not(op:boolean-less-than(A, B))
    // A ge B xs:string             xs:string               op:numeric-greater-than(fn:compare(A, B), -1)
    // A ge B xs:date               xs:date                 fn:not(op:date-less-than(A, B))
    // A ge B xs:time               xs:time                 fn:not(op:time-less-than(A, B))
    // A ge B xs:dateTime           xs:dateTime             fn:not(op:datetime-less-than(A, B))
    // A ge B xdt:yearMonthDuration xdt:yearMonthDuration   fn:not(op:yearMonthDuration-less-than(A, B))
    // A ge B xdt:dayTimeDuration   xdt:dayTimeDuration     fn:not(op:dayTimeDuration-less-than(A, B))
    // numeric values need a special comparison, for the others we can just rely on LessThan
    if(arg1->isNumericValue()) {
        if(arg2->isNumericValue()) {
            return ((Numeric*)(const AnyAtomicType*)arg1)->greaterThan((const Numeric::Ptr )arg2, context) ||
                   ((Numeric*)(const AnyAtomicType*)arg1)->equals((const Numeric::Ptr )arg2, context) ;
        } else {
            DSLthrow(XPath2ErrorException,X("GreaterThanEqual::greater_than_equal"), X("An attempt to compare a numeric type to a non numeric type has occurred"));
        }
    }

    return !LessThan::less_than(arg1,arg2,collation,context);
}

bool GreaterThanEqual::execute(const AnyAtomicType::Ptr &atom1, const AnyAtomicType::Ptr &atom2, DynamicContext *context) const
{
  Collation* collation=context->getDefaultCollation();
  if(collation==NULL)
    collation=context->getCollation(CodepointCollation::getCodepointCollationName());
  return greater_than_equal(atom1,atom2,collation,context);
}


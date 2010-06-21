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
 * $Id: FunctionSubstringBefore.cpp,v 1.14 2006/11/01 16:37:20 jpcs Exp $
 */

#include "../config/xqilla_config.h"
#include <xqilla/functions/FunctionSubstringBefore.hpp>
#include <xqilla/items/ATStringOrDerived.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/context/Collation.hpp>
#include <xqilla/context/impl/CodepointCollation.hpp>
#include <xqilla/exceptions/FunctionException.hpp>
#include <xqilla/exceptions/XPath2ErrorException.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xqilla/items/ATAnyURIOrDerived.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xercesc/util/XMLUni.hpp>

const XMLCh FunctionSubstringBefore::name[] = {
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_s, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_u, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_b, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_s, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_t, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_i, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_n, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_g, 
  XERCES_CPP_NAMESPACE_QUALIFIER chDash,    XERCES_CPP_NAMESPACE_QUALIFIER chLatin_b, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_f, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_o, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_r, 
  XERCES_CPP_NAMESPACE_QUALIFIER chLatin_e, XERCES_CPP_NAMESPACE_QUALIFIER chNull 
};
const unsigned int FunctionSubstringBefore::minArgs = 2;
const unsigned int FunctionSubstringBefore::maxArgs = 3;

/**
 * fn:substring-before($arg1 as xs:string?, $arg2 as xs:string?) as xs:string
 * fn:substring-before($arg1 as xs:string?, $arg2 as xs:string?, $collation as xs:string) as xs:string
**/

FunctionSubstringBefore::FunctionSubstringBefore(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr)
  : ConstantFoldingFunction(name, minArgs, maxArgs, "string?,string?,string", args, memMgr)
{
  _src.getStaticType().flags = StaticType::STRING_TYPE;
}

Sequence FunctionSubstringBefore::collapseTreeInternal(DynamicContext* context, int flags) const
{
  XPath2MemoryManager* memMgr = context->getMemoryManager();

  Sequence str1=getParamNumber(1,context)->toSequence(context);
  Sequence str2=getParamNumber(2,context)->toSequence(context);

  ATStringOrDerived::Ptr container = NULL;
  if(str1.isEmpty())
    container=context->getItemFactory()->createString(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgZeroLenString, context);
  else
    container=(const ATStringOrDerived::Ptr )str1.first();
  ATStringOrDerived::Ptr pattern = NULL;
  if(str2.isEmpty())
    pattern=context->getItemFactory()->createString(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgZeroLenString, context);
  else
    pattern=(const ATStringOrDerived::Ptr )str2.first();
  if(pattern->getLength()==0)
    return Sequence(pattern, memMgr);

  Collation* collation=NULL;
  if(getNumArgs()>2) {
    Sequence collArg = getParamNumber(3,context)->toSequence(context);
    const XMLCh* collName=collArg.first()->asString(context);
    try {
      context->getItemFactory()->createAnyURI(collName, context);
    } catch(XPath2ErrorException &e) {
      XQThrow(FunctionException, X("FunctionSubstringAfter::collapseTreeInternal"), X("Invalid collationURI"));  
    }
    collation=context->getCollation(collName, this);
  }
  else
    collation=context->getDefaultCollation(this);

  return Sequence(((const ATStringOrDerived*)container)->substringBefore(pattern, collation, context), memMgr);
}

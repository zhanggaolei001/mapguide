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
 * $Id: FunctionResolveURI.hpp,v 1.11 2006/11/01 16:37:13 jpcs Exp $
 */


#ifndef _FUNCTIONRESOLVEURI_HPP
#define _FUNCTIONRESOLVEURI_HPP

#include <xqilla/framework/XQillaExport.hpp>
#include <xqilla/ast/XQFunction.hpp>

/***
 *  Returns an absolute anyURI given a base URI and a relative URI.
 *
 *  fn:resolve-uri(anyURI $relative) => anyURI
 *  fn:resolve-uri(anyURI $relative, anyURI $base) => anyURI
 */
class XQILLA_API FunctionResolveURI : public XQFunction
{
public:
  static const XMLCh name[];
  static const unsigned int minArgs;
  static const unsigned int maxArgs;

  FunctionResolveURI(const VectorOfASTNodes &args, XPath2MemoryManager* memMgr);
  
  ASTNode* staticResolution(StaticContext *context);
  virtual ASTNode *staticTyping(StaticContext *context);

 /** 
  * Returns an absolute anyURI given a base URI and a relative URI.
  **/
  Sequence collapseTreeInternal(DynamicContext* context, int flags=0) const;

private:
  const XMLCh *baseURI_;
};

#endif // _FUNCTIONRESOLVEURI_HPP






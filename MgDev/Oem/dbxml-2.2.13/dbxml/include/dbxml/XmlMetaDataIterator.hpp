//
// See the file LICENSE for redistribution information.
//
// Copyright (c) 2002-2005
//	Sleepycat Software.  All rights reserved.
//
// $Id: XmlMetaDataIterator.hpp,v 1.4 2005/04/05 16:43:54 bostic Exp $
//

#ifndef __XMLMETADATAITERATOR_HPP
#define	__XMLMETADATAITERATOR_HPP

#include "XmlPortability.hpp"
#include "DbXmlFwd.hpp"
#include <string>

namespace DbXml
{

class MetaDataIterator;
	
class DBXML_EXPORT XmlMetaDataIterator
{
public:
	/** @name For Reference Counting */
	XmlMetaDataIterator();
	XmlMetaDataIterator(const XmlMetaDataIterator&);
	XmlMetaDataIterator &operator=(const XmlMetaDataIterator &);
	virtual ~XmlMetaDataIterator();
	bool isNull() const { return i_ == 0; }

	/** @name Iterator Methods */
	bool next(std::string &uri, std::string &name, XmlValue &value);
	void reset();
	
	/** @name Private Methods (for internal use) */
	// @{
	
	XmlMetaDataIterator(MetaDataIterator *document);
	operator MetaDataIterator &() const {
		return *i_;
	}
	operator MetaDataIterator *() const {
		return i_;
	}
	
	//@}
	
private:
	MetaDataIterator *i_;
};

}

#endif

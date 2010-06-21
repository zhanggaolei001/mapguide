//
// See the file LICENSE for redistribution information.
//
// Copyright (c) 2002,2006 Oracle.  All rights reserved.
//
// $Id: EventReader.hpp,v 1.4 2006/10/30 17:45:56 bostic Exp $
//

#ifndef __DBXMLEVENTREADER_HPP
#define __DBXMLEVENTREADER_HPP
	
#include <dbxml/XmlEventReader.hpp>

namespace DbXml
{

class NsNode;
class NsDocument;
	
/**
 * EventReader
 *
 * This class is a subclass of XmlEventReader, and is a shared
 * base class for internal implementations of that class:
 *  NsEventReader and NsDomReader
 *
 * This class is abstract
 */
class EventReader : public XmlEventReader {
public:
	EventReader();
	virtual ~EventReader() {}
	//
	// Abstract interface
	//
	virtual const NsNode *getNsNode() const = 0;
	virtual const unsigned char *getVersion() const = 0;
	virtual const unsigned char *getEncoding() const = 0;
	virtual bool isStandalone() const = 0;
	virtual bool standaloneSet() const = 0;
	virtual bool encodingSet() const = 0;
	// this one has a default implementation
	virtual const unsigned char *getSystemId() const;

	//
	// Utility functions
	//
	void throwIllegalOperation(XmlEventType type, const char *method) const;
	void ensureType(XmlEventType type, const char *method) const;
	void ensureAttributes(int index, const char *method) const;
	const char *typeToString(XmlEventType type) const;

	//
	// common implementation of XmlEventReader interfaces
	//
	bool hasNext() const { return hasNext_; }
	void setReportEntityInfo(bool value);
	bool getReportEntityInfo() const;
	void setExpandEntities(bool value);
	bool getExpandEntities() const;
	bool hasEntityEscapeInfo() const;
	bool hasEmptyElementInfo() const;
	bool isWhiteSpace() const;
	XmlEventType nextTag();
	XmlEventType getEventType() const;

protected:
	bool expandEntities_;
	bool reportEntityInfo_;
	XmlEventType type_;
	unsigned char *value_;
	int valueLen_;
	bool hasNext_;
};

}

#endif

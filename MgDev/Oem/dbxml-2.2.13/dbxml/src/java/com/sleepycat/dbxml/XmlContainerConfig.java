//
// See the file LICENSE for redistribution information.
//
// Copyright (c) 2002-2005
//	Sleepycat Software.  All rights reserved.
//
// $Id: XmlContainerConfig.java,v 1.10 2005/11/21 21:46:38 gmf Exp $
//
//

package com.sleepycat.dbxml;
import com.sleepycat.db.DatabaseConfig;
import com.sleepycat.db.internal.DbConstants;

// Adds configuration for:
//    node indexing
// Use DatabaseConfig for:
//  checksum, encryption, transactional configuration
//
public class XmlContainerConfig extends DatabaseConfig {

    public static final XmlContainerConfig DEFAULT = new XmlContainerConfig();

    public boolean getIndexNodes() {
	return indexNodes;
    }

    public XmlContainerConfig setIndexNodes(boolean value) {
	this.indexNodes = value;
	return this;
    }

    public boolean getNodeContainer() {
	return nodeContainer;
    }

    public XmlContainerConfig setNodeContainer(boolean value) {
	this.nodeContainer = value;
	return this;
    }

    public boolean getAllowValidation() {
	return allowValidation;
    }

    public XmlContainerConfig setAllowValidation(boolean value) {
	this.allowValidation = value;
	return this;
    }

    /* package */
    int makeFlags(boolean threaded) {
		int flags = 0;
		if (indexNodes)
			flags |= dbxml_javaConstants.DBXML_INDEX_NODES;
		// Translations from DB
		if (getChecksum())
			flags |= dbxml_javaConstants.DBXML_CHKSUM;
		if (getEncrypted())
			flags |= dbxml_javaConstants.DBXML_ENCRYPT;
		if (getTransactional())
			flags |= dbxml_javaConstants.DBXML_TRANSACTIONAL;
		if (getAllowValidation())
			flags |= dbxml_javaConstants.DBXML_ALLOW_VALIDATION;
		if (getAllowCreate())
			flags |= DbConstants.DB_CREATE;
		if (getExclusiveCreate())
			flags |= DbConstants.DB_EXCL;
		if (getNoMMap())
			flags |= DbConstants.DB_NOMMAP;
		if (getReadOnly())
			flags |= DbConstants.DB_RDONLY;
		if (getDirtyRead())
		    // flags |= DbConstants.DB_READ_UNCOMMITTED;
		    flags |= 0x04000000; // was DB_DIRTY_READ
		if (threaded)
			flags |= DbConstants.DB_THREAD;
		if (getTransactionNotDurable())
			flags |= DbConstants.DB_TXN_NOT_DURABLE;
		return flags;
    }

    /* Flags */
    private boolean indexNodes = false;
    private boolean nodeContainer = true;
    private boolean allowValidation = false;
}

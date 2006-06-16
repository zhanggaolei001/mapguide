%include "exception.i"
%include "typemaps.i"

%{
#include "db_cxx.h"
#include "dbxml/DbXml.hpp"
#include <errno.h>
#include <fstream>

using namespace DbXml;

class XmlIndexDeclaration {
public:
	XmlIndexDeclaration() {}
	XmlIndexDeclaration(const std::string &uri, const std::string &name, const std::string &index) : uri(uri), name(name), index(index) {}
#ifndef SWIGJAVA	
	const std::string &get_uri() const { return uri; }
	const std::string &get_name() const { return name; }
	const std::string &get_index() const { return index; }
#endif
	std::string uri, name, index;
};

class XmlMetaData {
public:
	XmlMetaData() {}
	XmlMetaData(const std::string &uri, const std::string &name, const
		    XmlValue &value) : uri(uri), name(name), value(value) {}
	
	const std::string &get_uri() const { return uri; }
	const std::string &get_name() const { return name; }
	const XmlValue &get_value() const { return value; }
	std::string uri, name;
	XmlValue value;
};

%}

#if defined(SWIGJAVA)
%include "std_string.i"
%include "dbxml_java.i"
#elif defined(SWIGPYTHON)
%include "std_string.i"
%include "dbxml_python.i"
#elif defined(SWIGTCL8)
%include "std_string.i"
%include "dbxml_tcl.i"
#elif defined(SWIGCSHARP)
%include "dbxml_csharp.i"
#elif defined(SWIGPHP4)
%include "std_string.i"
%include "dbxml_php4.i"
#else
#error "Unknown SWIG target language"
#endif

#if defined(SWIGJAVA) || defined(SWIGPYTHON) || defined(SWIGCSHARP) || defined(SWIGTCL8)
#define DBXML_USEOVERLOADS
#endif

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
#define DBXML_USE_RESOLVER
#endif

typedef unsigned int u_int32_t;
typedef int int32_t;

class XmlManager;
class XmlDocument;
class XmlContainer;
class XmlIndexSpecification;
class XmlIndexLookup;
class XmlInputStream;
class XmlQueryContext;
class XmlResults;
class XmlUpdateContext;
class XmlValue;
class XmlQueryExpression;
class XmlModify;
class XmlTransaction;
class XmlMetaDataIterator;
class XmlStatistics;
#if defined(DBXML_USE_RESOLVER)
class XmlResolver;
#endif


#if defined(DBXML_USEOVERLOADS)
#define OVERLOAD_NAME(n)
#else
#define OVERLOAD_NAME(n) %name(n)
#endif

// SWIG will generate a class per enumeration by default

#ifndef SWIGJAVA
// For Java, this is done differently
enum {
	DB_CREATE, DB_DIRTY_READ, DB_EXCL,
	DB_NOMMAP, DB_RDONLY, DB_THREAD,
	DB_INIT_LOCK, DB_INIT_LOG, DB_INIT_MPOOL, DB_INIT_TXN,
	DB_SALVAGE, DB_AGGRESSIVE
};

#endif


#ifdef SWIGJAVA
%javaconst(1);
#endif

//
// see DbXmlFwd.hpp for these enums
//
// Global flags
enum {
	DBXML_ADOPT_DBENV =        0x00000001,
	DBXML_ALLOW_EXTERNAL_ACCESS = 0x00000002,
	DBXML_ALLOW_AUTO_OPEN    = 0x00000004,
	DBXML_ALLOW_VALIDATION  =  0x00100000,
	DBXML_TRANSACTIONAL =      0x00200000,
	DBXML_REVERSE_ORDER =      0x00100000,
	DBXML_INDEX_VALUES =       0x00200000,
	DBXML_CACHE_DOCUMENTS =    0x00400000,
	DBXML_CHKSUM =             0x00400000,
	DBXML_ENCRYPT =            0x00800000,
	DBXML_NO_INDEX_NODES =     0x10000000,
	DBXML_GEN_NAME =           0x20000000,
	DBXML_LAZY_DOCS =          0x40000000,
	DBXML_INDEX_NODES =        0x80000000
};

// LogLevel
enum {
    LEVEL_NONE = 0x00000000,  ///< No debug levels are enabled.
    LEVEL_DEBUG = 0x00000001,  ///< Program execution tracing messages.
    LEVEL_INFO = 0x00000002,  ///< Informational, just for interest.
    LEVEL_WARNING = 0x00000004,  ///< For warnings, bad things but recoverable.
    LEVEL_ERROR = 0x00000008,  ///< For errors that can't be recovered from.
    LEVEL_ALL = 0xFFFFFFFF  ///< All debug levels are enabled.
};

// LogCategory
enum {
    CATEGORY_NONE = 0x00000000,
    CATEGORY_INDEXER = 0x00000001,
    CATEGORY_QUERY = 0x00000002,
    CATEGORY_OPTIMIZER = 0x00000004,
    CATEGORY_DICTIONARY = 0x00000008,
    CATEGORY_CONTAINER = 0x00000010,
    CATEGORY_NODESTORE = 0x00000020,
    CATEGORY_MANAGER =    0x00000040,
    CATEGORY_ALL = 0xFFFFFFFF
};

//
// These strings are reproduced from src/dbxml/XmlNamespace.cpp.
// Using them as direct constants is simpler (from a SWIG point of view)
// than trying to reference their C++ values on demand.  This means
// maintaining them together, if they change.
//
%constant const char *metaDataNamespace_uri =  "http://www.sleepycat.com/2002/dbxml";
%constant const char *metaDataNamespace_prefix = "dbxml";
%constant const char *metaDataName_name = "name";
%constant const char *metaDataName_root = "root";

#ifdef SWIGTCL8
/* Put these at global scope for swig */
%typemap(in, numinputs = 0) int *majorp, int *minorp, int *patchp %{ $1 = NULL; %}
const char *dbxml_version(int *majorp, int *minorp, int *patchp);
void setLogLevel(enum LogLevel level, bool enabled) {
		DbXml::setLogLevel(level, enabled)
}
void setLogCategory(enum LogCategory category, bool enabled) {
		DbXml::setLogCategory(category, enabled)	
}
#endif /* SWIGTCL8 */

/*
 * All the methods that return pointers to allocated memory.
 * Required so the memory is freed when the objects are deleted.
 */
%newobject XmlManager::createContainer(const std::string &);
%newobject XmlManager::createContainer(const std::string &, // name
				       u_int32_t, //flags
				       enum XmlContainer::ContainerType=
				       XmlContainer::NodeContainer,
				       int mode=0);      // mode
%newobject XmlManager::createContainer(XmlTransaction &, const std::string &);
%newobject XmlManager::createContainer(XmlTransaction &, const std::string &,
				       u_int32_t,  // flags
				       enum XmlContainer::ContainerType=
				       XmlContainer::NodeContainer,
				       int mode=0);       // mode
%newobject XmlManager::openContainer(const std::string &);
%newobject XmlManager::openContainer(const std::string &, u_int32_t);
%newobject XmlManager::openContainer(XmlTransaction &, const std::string &);
%newobject XmlManager::openContainer(XmlTransaction &, const std::string &,
				     u_int32_t);
%newobject XmlManager::openContainer(XmlTransaction &, const std::string &,
				     u_int32_t, 
				     enum XmlContainer::ContainerType,
				     int mode = 0);
%newobject XmlManager::openContainer(const std::string &,
				     u_int32_t, 
				     enum XmlContainer::ContainerType,
				     int mode = 0);
%newobject XmlManager::createDocument();

%newobject XmlManager::createQueryContext(enum XmlQueryContext::ReturnType,
					  enum XmlQueryContext::EvaluationType);
%newobject XmlManager::createQueryContext(enum XmlQueryContext::ReturnType);
%newobject XmlManager::createQueryContext();

%newobject XmlManager::createUpdateContext();

%newobject XmlManager::prepare(const std::string &, XmlQueryContext &);
%newobject XmlManager::prepare(XmlTransaction &, const std::string &,
				XmlQueryContext &);
%newobject XmlManager::query(const std::string &, XmlQueryContext &, u_int32_t);
%newobject XmlManager::query(XmlTransaction &, const std::string &,
			      XmlQueryContext &, u_int32_t);
%newobject XmlManager::query(const std::string &, XmlQueryContext &);
%newobject XmlManager::query(XmlTransaction &, const std::string &,
			      XmlQueryContext &);
%newobject XmlManager::createResults();
%newobject XmlManager::createModify();


%newobject XmlManager::createTransaction(DbTxn *);
#ifndef SWIGJAVA
%newobject XmlManager::createTransaction();
%newobject XmlManager::createTransaction(u_int32_t);
%newobject XmlTransaction::createChild(u_int32_t);
%newobject XmlTransaction::createChild();
#endif

%newobject XmlContainer::getIndexSpecification() const;
%newobject XmlContainer::getIndexSpecification(XmlTransaction&) const;
%newobject XmlContainer::getIndexSpecification(XmlTransaction&, 
					       u_int32_t flags) const;
%newobject XmlManager::createIndexLookup(
	XmlContainer &cont,
	const std::string &uri, 
	const std::string &name,
	const std::string &index,
	const XmlValue &value = XmlValue(),
	enum XmlIndexLookup::Operation op = XmlIndexLookup::NONE);

%newobject XmlIndexLookup::execute(
	XmlQueryContext &ctx, u_int32_t flags = 0) const;
%newobject XmlIndexLookup::execute(
	XmlTransaction &, XmlQueryContext &ctx, u_int32_t flags = 0) const;
	
#ifndef SWIGJAVA
%newobject XmlContainer::getDocument(const std::string&);
%newobject XmlContainer::getDocument(XmlTransaction&, const std::string&);
#endif
%newobject XmlContainer::getDocument(const std::string&, u_int32_t);
%newobject XmlContainer::getDocument(XmlTransaction&, const std::string&,
				     u_int32_t);
%newobject XmlContainer::getAllDocuments(u_int32_t);
%newobject XmlContainer::getAllDocuments(XmlTransaction&, u_int32_t);
%newobject XmlContainer::lookupIndex(XmlQueryContext &, const std::string &,
				     const std::string &, const std::string &);
%newobject XmlContainer::lookupIndex(XmlQueryContext &, const std::string &,
				     const std::string &, const std::string &,
				     const XmlValue &, u_int32_t);
%newobject XmlContainer::lookupIndex(XmlQueryContext &, const std::string &,
				     const std::string &, const std::string &,
				     const XmlValue &);
%newobject XmlContainer::lookupIndex(XmlQueryContext &, const std::string &,
				     const std::string &, const std::string &,
				     const std::string &, const std::string &);
%newobject XmlContainer::lookupIndex(XmlQueryContext &, const std::string &,
				     const std::string &, const std::string &,
				     const std::string &, const std::string &,
				     const XmlValue &, u_int32_t);
%newobject XmlContainer::lookupIndex(XmlQueryContext &, const std::string &,
				     const std::string &, const std::string &,
				     const std::string &, const std::string &,
				     const XmlValue &);
%newobject XmlContainer::lookupIndex(XmlTransaction &, XmlQueryContext &,
				     const std::string &, const std::string &,
				     const std::string &);
%newobject XmlContainer::lookupIndex(XmlTransaction &, XmlQueryContext &,
				     const std::string &, const std::string &,
				     const std::string &, const XmlValue &,
				     u_int32_t);
%newobject XmlContainer::lookupIndex(XmlTransaction &, XmlQueryContext &,
				     const std::string &, const std::string &,
				     const std::string &, const XmlValue &);
%newobject XmlContainer::lookupIndex(XmlTransaction &, XmlQueryContext &,
				     const std::string &, const std::string &,
				     const std::string &, const std::string &,
				     const std::string &);
%newobject XmlContainer::lookupIndex(XmlTransaction &, XmlQueryContext &,
				     const std::string &, const std::string &,
				     const std::string &, const std::string &,
				     const std::string &, const XmlValue &,
				     u_int32_t);
%newobject XmlContainer::lookupIndex(XmlTransaction &, XmlQueryContext &,
				     const std::string &, const std::string &,
				     const std::string &, const std::string &,
				     const std::string &, const XmlValue &);
%newobject XmlContainer::lookupStatistics(const std::string &,
					  const std::string &, const std::string &);
%newobject XmlContainer::lookupStatistics(const std::string &,
					  const std::string &, const std::string &,
					  const XmlValue &);
%newobject XmlContainer::lookupStatistics(const std::string &,
					  const std::string &, const std::string &,
					  const std::string &, const std::string &);
%newobject XmlContainer::lookupStatistics(const std::string &,
					  const std::string &, const std::string &,
					  const std::string &, const std::string &,
					  const XmlValue &);
%newobject XmlContainer::lookupStatistics(XmlTransaction &,
				     const std::string &, const std::string &,
				     const std::string &);
%newobject XmlContainer::lookupStatistics(XmlTransaction &,
				     const std::string &, const std::string &,
				     const std::string &, const XmlValue &);
%newobject XmlContainer::lookupStatistics(XmlTransaction &,
				     const std::string &, const std::string &,
				     const std::string &, const std::string &,
				     const std::string &);
%newobject XmlContainer::lookupStatistics(XmlTransaction &,
				     const std::string &, const std::string &,
				     const std::string &, const std::string &,
				     const std::string &, const XmlValue &);

%newobject XmlDocument::getContent() const;
%newobject XmlDocument::getMetaDataIterator() const;
%newobject XmlDocument::getContentAsXmlInputStream() const;

%newobject XmlQueryContext::getVariableValue(const std::string&) const;

%newobject XmlQueryExpression::execute(XmlQueryContext &, u_int32_t) const;
%newobject XmlQueryExpression::execute(XmlQueryContext &) const;
%newobject XmlQueryExpression::execute(const XmlValue &, XmlQueryContext &,
				       u_int32_t) const;
%newobject XmlQueryExpression::execute(const XmlValue &, XmlQueryContext &) const;
%newobject XmlQueryExpression::execute(XmlTransaction &, XmlQueryContext &,
				       u_int32_t) const;
%newobject XmlQueryExpression::execute(XmlTransaction &, XmlQueryContext &) const;
%newobject XmlQueryExpression::execute(XmlTransaction &, const XmlValue &,
				       XmlQueryContext &, u_int32_t) const;
%newobject XmlQueryExpression::execute(XmlTransaction &, const XmlValue &,
				       XmlQueryContext &) const;


#if defined(SWIGJAVA) || defined(SWIGPYTHON) || defined(SWIGPHP4)
%newobject XmlResults::next();
%newobject XmlResults::previous();
%newobject XmlResults::peek();
#endif

#ifdef SWIGTCL8
%newobject XmlValue::asDocument(const XmlQueryContext*) const;
#endif

%newobject XmlValue::getParentNode() const;
%newobject XmlValue::getFirstChild() const;
%newobject XmlValue::getLastChild() const;
%newobject XmlValue::getPreviousSibling() const;
%newobject XmlValue::getNextSibling() const;
%newobject XmlValue::getAttributes() const;
%newobject XmlValue::getOwnerElement() const;
%newobject XmlValue::asBinary() const;

%newobject XmlIndexSpecification::find(const std::string&, const std::string&);
%newobject XmlIndexSpecification::next();

%newobject XmlMetaDataIterator::next();

#if defined(DBXML_USE_RESOLVER)
%newobject XmlResolver::resolveSchema(XmlTransaction*, XmlManager&, const std::string&, const std::string&) const;
%newobject XmlResolver::resolveEntity(XmlTransaction*, XmlManager&, const std::string&, const std::string&) const;
#endif

#ifdef SWIGJAVA
%nodefault XmlManager;
#endif

class XmlManager
{
public:

#ifndef SWIGJAVA
	XmlManager();
#endif	
#ifndef SWIGJAVA
OVERLOAD_NAME(XmlManagerWithFlags)
	XmlManager(u_int32_t flags);
#endif
OVERLOAD_NAME(XmlManagerFromEnv)	
	XmlManager(DbEnv *dbEnv, u_int32_t flags);
	~XmlManager();

#ifndef SWIGJAVA
	void setDefaultContainerFlags(u_int32_t flags);
	u_int32_t getDefaultContainerFlags();
#endif
	void setDefaultPageSize(u_int32_t pageSize);
	u_int32_t getDefaultPageSize();
	void setDefaultSequenceIncrement(u_int32_t incr);
	u_int32_t getDefaultSequenceIncrement();
	void setDefaultContainerType(enum XmlContainer::ContainerType type);
	enum XmlContainer::ContainerType getDefaultContainerType();
#ifndef SWIGJAVA
	DbEnv *getDbEnv();
#endif
	const std::string &getHome() const;
#if defined(DBXML_USE_RESOLVER)
	void registerResolver(const XmlResolver &resolver);
#endif

	int existsContainer(const std::string &name);
	void removeContainer(const std::string &name);
OVERLOAD_NAME(removeContainerWithTxn)
	void removeContainer(XmlTransaction &txn, const std::string &name);
	void renameContainer(const std::string &oldName,
			     const std::string &newName);
OVERLOAD_NAME(renameContainerWithTxn)
	void renameContainer(XmlTransaction &txn, const std::string &oldName,
			     const std::string &newName);
	void upgradeContainer(const std::string &name, XmlUpdateContext &uc);
	void reindexContainer(const std::string &name, XmlUpdateContext &uc,
			      u_int32_t flags = 0);
	void reindexContainer(XmlTransaction &txn, const std::string &name,
			      XmlUpdateContext &uc, u_int32_t flags = 0);
	%extend {

	XmlInputStream* createStdInInputStream() const {
		return self->createStdInInputStream();
	}

	XmlInputStream* createLocalFileInputStream(
		const std::string &filename) const {
		return self->createLocalFileInputStream(filename);
	}

	// The following method does not work correctly with Java
	// because the JNI layer copies the Java String, then
	// releases it upon return, leaving an invalid buffer.
	// It appears to work for Python
	// 
	XmlInputStream* createMemBufInputStream(
		const char *bytes, const unsigned int count,
		const char *id, const bool adopt = false) const {
		return self->createMemBufInputStream(bytes,
						     count,
						     id, adopt);
	}
	// This form *always* adopts the buffer, copied or not
	// It is supplied for use by Java, primarily
OVERLOAD_NAME(createMemBufInputStreamCopy)	
	XmlInputStream* createMemBufInputStream(
		const char *bytes, const unsigned int count,
		const bool copyBuffer) const {
		return self->createMemBufInputStream(bytes,
						     count,
						     copyBuffer);
	}

OVERLOAD_NAME(createURLInputStreamWithPublicID)
	XmlInputStream* createURLInputStream(
		const std::string &baseId, 
		const std::string &systemId, 
		const std::string &publicId) const {
		return self->createURLInputStream(baseId, systemId, publicId);
	}
	
	XmlInputStream* createURLInputStream(
		const std::string &baseId, 
		const std::string &systemId) const {
		return self->createURLInputStream(baseId, systemId);
	}

#ifndef SWIGJAVA // these are implemented in pure java
	XmlContainer *createContainer(const std::string &name) {
		return new XmlContainer(self->createContainer(name));
	}
OVERLOAD_NAME(createContainerWithTxn)
	XmlContainer *createContainer(
		XmlTransaction &txn, const std::string &name) {
		return new XmlContainer(self->createContainer(txn, name));
	}
OVERLOAD_NAME(openContainerWithTxn)
	XmlContainer *openContainer(XmlTransaction &txn,
				     const std::string &name) {
		return new XmlContainer(self->openContainer(txn, name));
	}
	XmlContainer *openContainer(const std::string &name) {
		return new XmlContainer(self->openContainer(name));
	}
#endif // SWIGJAVA

OVERLOAD_NAME(createContainerWithFlags)
	XmlContainer *createContainer(
		const std::string &name, u_int32_t flags,
		enum XmlContainer::ContainerType type =
		XmlContainer::NodeContainer,
		int mode = 0) {
		return new XmlContainer(
			self->createContainer(name, flags, type, mode));
	 }

OVERLOAD_NAME(createContainerWithTxnAndFlags)
	XmlContainer *createContainer(
		XmlTransaction &txn, const std::string &name, u_int32_t flags,
		enum XmlContainer::ContainerType type =
		XmlContainer::NodeContainer,
		int mode = 0) {
		return new XmlContainer(self->createContainer(txn, name, flags,
							      type, mode));
        }

OVERLOAD_NAME(openContainerWithFlags)
	XmlContainer *openContainer(const std::string &name, u_int32_t flags) {
		return new XmlContainer(self->openContainer(name, flags));
        }
OVERLOAD_NAME(openContainerWithTxnAndFlags)
	XmlContainer *openContainer(XmlTransaction &txn,
				     const std::string &name, u_int32_t flags) {
		return new XmlContainer(self->openContainer(txn, name, flags));
        }
OVERLOAD_NAME(openContainerWithType)
	XmlContainer *openContainer(const std::string &name,
				    u_int32_t flags, 
				    enum XmlContainer::ContainerType type,
				    int mode = 0) {
	    return new XmlContainer(self->openContainer(name,
						    flags, type, mode));
        }
OVERLOAD_NAME(openContainerWithTxnAndType)
	XmlContainer *openContainer(XmlTransaction &txn,
				    const std::string &name,
				    u_int32_t flags, 
				    enum XmlContainer::ContainerType type,
				    int mode = 0) {
	    return new XmlContainer(self->openContainer(txn, name,
						    flags, type, mode));
        }
}
%extend {
	void dumpContainer(const std::string &name, const char *filename) {
		std::ofstream out(filename);
		self->dumpContainer(name, &out);
		out.close();
	}

	void loadContainer(const std::string &name, const char *filename,
			   XmlUpdateContext &uc) {
		std::ifstream in(filename);
		unsigned long lineno = 0;
		self->loadContainer(name, &in, &lineno, uc);
		in.close();
	}
	void verifyContainer(const std::string &name, const char *filename,
			     u_int32_t flags = 0) {
		std::ofstream out;
		if (flags & DB_SALVAGE)
			out.open(filename);
		self->verifyContainer(name, &out, flags);
		if (flags & DB_SALVAGE)
			out.close();
	}
	XmlDocument *createDocument() {
		return new XmlDocument(self->createDocument());
	}

	XmlQueryContext *createQueryContext(
		enum XmlQueryContext::ReturnType rt,
		enum XmlQueryContext::EvaluationType et) {
		return new XmlQueryContext(self->createQueryContext(rt, et));
	}


OVERLOAD_NAME(createQueryContextDefaultAll)
	XmlQueryContext *createQueryContext() {
		return new XmlQueryContext(self->createQueryContext(
			XmlQueryContext::LiveValues, XmlQueryContext::Eager));
	}

OVERLOAD_NAME(createQueryContextDefaultEvalType)
	XmlQueryContext *createQueryContext(
		enum XmlQueryContext::ReturnType rt) {
		return new XmlQueryContext(self->createQueryContext(rt, XmlQueryContext::Eager));
	}

	XmlUpdateContext *createUpdateContext() {
		return new XmlUpdateContext(self->createUpdateContext());
	}

	XmlQueryExpression *prepare(const std::string &query,
				    XmlQueryContext &context) {
		return new XmlQueryExpression(self->prepare(query, context));
	}
OVERLOAD_NAME(prepareWithTxn)
	 XmlQueryExpression *prepare(XmlTransaction &txn,
				     const std::string &query,
				     XmlQueryContext &context){
		return new XmlQueryExpression(self->prepare(
						      txn,query, context));
	}
        XmlResults *query(const std::string &query, XmlQueryContext &context,
			  u_int32_t flags) {
		return new XmlResults(self->query(query, context, flags));
	}
OVERLOAD_NAME(queryWithTxn)
	XmlResults *query(XmlTransaction &txn, const std::string &query,
			  XmlQueryContext &context, u_int32_t flags) {
		return new XmlResults(self->query(txn, query, context, flags));
	}

OVERLOAD_NAME(queryDefaultFlags)
	XmlResults *query(const std::string &query, XmlQueryContext &context) {
		return new XmlResults(self->query(query, context, 0));
	}
OVERLOAD_NAME(queryWithTxnDefaultFlags)
	XmlResults *query(XmlTransaction &txn, const std::string &query,
			  XmlQueryContext &context) {
		return new XmlResults(self->query(txn, query, context, 0));
	}


	XmlResults *createResults() {
		return new XmlResults(self->createResults());
	}

	XmlModify *createModify() {
		return new XmlModify(self->createModify());
	}

OVERLOAD_NAME(createTransactionFromDbTxn)
	XmlTransaction *createTransaction(DbTxn *toAdopt) {
		return new XmlTransaction(self->createTransaction(toAdopt));
        }
#ifndef SWIGJAVA 
	XmlTransaction *createTransaction(u_int32_t flags) {
		return new XmlTransaction(self->createTransaction(flags));
	}
	
OVERLOAD_NAME(createTransactionDefaultFlags)
	XmlTransaction *createTransaction() {
		return new XmlTransaction(self->createTransaction((u_int32_t)0));
        }
#endif
		
        XmlIndexLookup *createIndexLookup(
		XmlContainer &cont,
		const std::string &uri, const std::string &name,
		const std::string &index,
		const XmlValue &value = XmlValue(),
		enum XmlIndexLookup::Operation op = XmlIndexLookup::NONE) {
		return new XmlIndexLookup(self->createIndexLookup(cont, uri,name,
								  index, value,
								  op));
	}

#ifndef SWIGTCL8
// These methods are at global scope (namespace DbXml)
// in C++ and in Tcl.
	static void setLogLevel(enum LogLevel level, bool enabled) {
		DbXml::setLogLevel(level, enabled);
	}

	static void setLogCategory(enum LogCategory category, bool enabled) {
		DbXml::setLogCategory(category, enabled);
	}
	static int get_version_major() {
		int major;
		(void)dbxml_version(&major, NULL, NULL);
		return major;
	}

	static int get_version_minor() {
		int minor;
		(void)dbxml_version(NULL, &minor, NULL);
		return minor;
	}

	static int get_version_patch() {
		int patch;
		(void)dbxml_version(NULL, NULL, &patch);
		return patch;
	}

	static const char *get_version_string() {
		return dbxml_version(NULL, NULL, NULL);
	}
#endif /* !SWIGTCL8 */
} /* extend */
};

class XmlIndexLookup
{
public:
	enum // Operation
	{
		NONE,
		EQ,
		GT,
		GTE,
		LT,
		LTE
	};
#ifndef SWIGJAVA
	XmlIndexLookup();
#endif
	XmlIndexLookup(const XmlIndexLookup &o);
	~XmlIndexLookup();
	bool isNull() const;
	const std::string &getIndex() const;
	void setIndex(const std::string &index);

	const std::string &getNodeURI() const;
	const std::string &getNodeName() const;
	void setNode(const std::string &uri, const std::string &name);

	const std::string &getParentURI() const;
	const std::string &getParentName() const;
	void setParent(const std::string &uri, const std::string &name);

	const XmlValue &getLowBoundValue() const;
	enum XmlIndexLookup::Operation getLowBoundOperation() const;
	void setLowBound(const XmlValue &value,
			 enum XmlIndexLookup::Operation op);

	const XmlValue &getHighBoundValue() const;
	enum XmlIndexLookup::Operation getHighBoundOperation() const;
	void setHighBound(const XmlValue &value,
			  enum XmlIndexLookup::Operation op);

	const XmlContainer &getContainer() const;
	void setContainer(XmlContainer &container);
%extend {
	XmlResults *execute(XmlQueryContext &context,
			    u_int32_t flags = 0) const {
		return new XmlResults(self->execute(context, flags));
	}
	OVERLOAD_NAME(executeWithTxn)
	XmlResults *execute(XmlTransaction &txn, XmlQueryContext &context,
			   u_int32_t flags = 0) const {
		return new XmlResults(self->execute(txn, context, flags));
	}
}

};
	
class XmlContainer
{
public:
	enum // ContainerType
	{
		WholedocContainer,
		NodeContainer
	};
#ifndef SWIGJAVA
	XmlContainer();
#endif
	XmlContainer(const XmlContainer &o);
	~XmlContainer();

	void sync();
#ifndef SWIGJAVA
	void close();
#endif SWIGJAVA

	bool addAlias(const std::string &alias);
	bool removeAlias(const std::string &alias);
	
	XmlManager &getManager();

	const std::string &getName() const;
	enum XmlContainer::ContainerType getContainerType() const;
	bool getIndexNodes() const;
	u_int32_t getPageSize() const;

	void setIndexSpecification(const XmlIndexSpecification &index,
				   XmlUpdateContext &uc);
	void addIndex(const std::string &uri, const std::string &name,
		      const std::string &index, XmlUpdateContext &uc);
OVERLOAD_NAME(addIndexWithTypes)
	void addIndex(const std::string &uri, const std::string &name,
		      enum XmlIndexSpecification::Type indexType,
		      enum XmlValue::Type syntaxType, 
		      XmlUpdateContext &uc);
	void deleteIndex(const std::string &uri, const std::string &name,
			 const std::string &index, XmlUpdateContext &uc);
	void replaceIndex(const std::string &uri, const std::string &name,
			  const std::string &index, XmlUpdateContext &uc);

	void addDefaultIndex(const std::string &index, XmlUpdateContext &uc);
	void deleteDefaultIndex(const std::string &index, XmlUpdateContext &uc);
	void replaceDefaultIndex(const std::string &index, XmlUpdateContext &uc);

OVERLOAD_NAME(setIndexSpecificationWithTxn)
	void setIndexSpecification(XmlTransaction &txn,
				   const XmlIndexSpecification &index,
				   XmlUpdateContext &uc);
OVERLOAD_NAME(addIndexWithTxn)
	void addIndex(XmlTransaction &txn, const std::string &uri,
		      const std::string &name, const std::string &index,
		      XmlUpdateContext &uc);
OVERLOAD_NAME(addIndexWithTypesAndTxn)
	void addIndex(XmlTransaction &txn,
		      const std::string &uri, const std::string &name,
		      enum XmlIndexSpecification::Type indexType,
		      enum XmlValue::Type syntaxType, 
		      XmlUpdateContext &uc);
OVERLOAD_NAME(deleteIndexWithTxn)
	void deleteIndex(XmlTransaction &txn, const std::string &uri,
			 const std::string &name, const std::string &index,
			 XmlUpdateContext &uc);
OVERLOAD_NAME(replaceIndexWithTxn)
	void replaceIndex(XmlTransaction &txn, const std::string &uri,
			  const std::string &name, const std::string &index,
			  XmlUpdateContext &uc);

OVERLOAD_NAME(addDefaultIndexWithTxn)
	void addDefaultIndex(XmlTransaction &txn, const std::string &index,
			     XmlUpdateContext &uc);
OVERLOAD_NAME(deleteDefaultIndexWithTxn)
	void deleteDefaultIndex(XmlTransaction &txn, const std::string &index,
				XmlUpdateContext &uc);
OVERLOAD_NAME(replaceDefaultIndexWithTxn)
	void replaceDefaultIndex(XmlTransaction &txn, const std::string &index,
				 XmlUpdateContext &uc);



	void putDocument(XmlDocument &document, XmlUpdateContext &context,
			 u_int32_t flags = 0);
OVERLOAD_NAME(putDocumentAsString)
	std::string putDocument(const std::string &name, const std::string &contents,
			 XmlUpdateContext &context, u_int32_t flags = 0);
	void deleteDocument(XmlDocument &document,
			    XmlUpdateContext &context);
OVERLOAD_NAME(deleteDocumentByName)
	void deleteDocument(const std::string &name,
			    XmlUpdateContext &context);
	void updateDocument(XmlDocument &document,
			    XmlUpdateContext &context);

OVERLOAD_NAME(putDocumentAsInputSource)
	std::string putDocument(const std::string &name,
				XmlInputStream *input,
				XmlUpdateContext &context,
				u_int32_t flags = 0);

OVERLOAD_NAME(putDocumentAsInputSourceWithTxn)
	std::string putDocument(XmlTransaction &txn,
				const std::string &name,
				XmlInputStream *input,
				XmlUpdateContext &context,
				u_int32_t flags = 0);
OVERLOAD_NAME(putDocumentWithTxn)
	void putDocument(XmlTransaction &txn, XmlDocument &document,
			 XmlUpdateContext &context, u_int32_t flags = 0);
OVERLOAD_NAME(putDocumentAsStringWithTxn)
	std::string putDocument(XmlTransaction &txn,
				const std::string &name,
				const std::string &contents,
				XmlUpdateContext &context,
				u_int32_t flags = 0);
OVERLOAD_NAME(deleteDocumentWithTxn)
	void deleteDocument(XmlTransaction &txn, XmlDocument &document,
			    XmlUpdateContext &context);
OVERLOAD_NAME(deleteDocumentByNameWithTxn)
	void deleteDocument(XmlTransaction &txn, const std::string &name,
			    XmlUpdateContext &context);
OVERLOAD_NAME(updateDocumentWithTxn)
	void updateDocument(XmlTransaction &txn, XmlDocument &document,
			    XmlUpdateContext &context);

	size_t getNumDocuments();
OVERLOAD_NAME(getNumDocumentWithTxn)
	size_t getNumDocuments(XmlTransaction &txn);

%extend {
	XmlIndexSpecification *getIndexSpecification() const {
		return new XmlIndexSpecification(self->getIndexSpecification());
	}
OVERLOAD_NAME(getIndexSpecificationWithTxn)
	XmlIndexSpecification *getIndexSpecification(
		XmlTransaction &txn) const {
		 return new XmlIndexSpecification(
			 self->getIndexSpecification(txn));
        }
OVERLOAD_NAME(getIndexSpecificationWithFlagsAndTxn)
	XmlIndexSpecification *getIndexSpecification(
		XmlTransaction &txn, u_int32_t flags) const {
		 return new XmlIndexSpecification(
			 self->getIndexSpecification(txn, flags));
	 }
#ifndef SWIGJAVA
	XmlDocument *getDocument(const std::string &name) {
		return new XmlDocument(self->getDocument(name, 0));
	}
OVERLOAD_NAME(getDocumentWithTxn)
	XmlDocument *getDocument(XmlTransaction &txn, const std::string &name)
	{
		return new XmlDocument(self->getDocument(txn, name, 0));
	}
#endif
OVERLOAD_NAME(getDocumentWithFlags)
	XmlDocument *getDocument(const std::string &name, u_int32_t flags) {
		return new XmlDocument(self->getDocument(name, flags));
	}
OVERLOAD_NAME(getDocumentWithFlagsAndTxn)
	XmlDocument *getDocument(XmlTransaction &txn, const std::string &name,
				 u_int32_t flags) {
		return new XmlDocument(self->getDocument(txn, name, flags));
	}
	XmlResults *getAllDocuments(u_int32_t flags) {
		   return new XmlResults(self->getAllDocuments(flags));
	}
OVERLOAD_NAME(getAllDocumentWithTxn)
	XmlResults *getAllDocuments(XmlTransaction &txn, u_int32_t flags) {
		   return new XmlResults(self->getAllDocuments(txn, flags));
	}

	XmlResults *lookupIndex(XmlQueryContext &context, const std::string &uri,
				const std::string &name, const std::string &index,
				const XmlValue &value = XmlValue(),
				u_int32_t flags = 0) {
		return new XmlResults(
			self->lookupIndex(context, uri, name, index,
					  value, flags));
	}
OVERLOAD_NAME(lookupEdgeIndex)
	XmlResults *lookupIndex(XmlQueryContext &context, const std::string &uri,
				const std::string &name,
				const std::string &parent_uri,
				const std::string &parent_name,
				const std::string &index,
				const XmlValue &value = XmlValue(),
				u_int32_t flags = 0) {
		return new XmlResults(self->lookupIndex(context, uri, name,
							parent_uri, parent_name,
							index, value, flags));
	}
OVERLOAD_NAME(lookupIndexWithTxn)
        XmlResults *lookupIndex(XmlTransaction &txn, XmlQueryContext &context,
				const std::string &uri, const std::string &name,
				const std::string &index,
				const XmlValue &value = XmlValue(),
				u_int32_t flags = 0) {
                return new XmlResults(self->lookupIndex(txn, context, uri, name,
							index, value, flags));
        }
OVERLOAD_NAME(lookupEdgeIndexWithTxn)
	XmlResults *lookupIndex(XmlTransaction &txn, XmlQueryContext &context,
				const std::string &uri, const std::string &name,
				const std::string &parent_uri,
				const std::string &parent_name,
				const std::string &index,
				const XmlValue &value = XmlValue(),
				u_int32_t flags = 0) {
	        return new XmlResults(self->lookupIndex(txn, context, uri, name,
							parent_uri, parent_name,
							index, value, flags));
	}
	XmlStatistics *lookupStatistics(const std::string &uri,
					const std::string &name,
					const std::string &index,
					const XmlValue &value = XmlValue()) {
		return new XmlStatistics(self->lookupStatistics(uri, name, index,
								value));
	}
OVERLOAD_NAME(lookupEdgeStatistics)
	XmlStatistics *lookupStatistics(const std::string &uri,
					const std::string &name,
					const std::string &parent_uri,
					const std::string &parent_name,
					const std::string &index,
					const XmlValue &value = XmlValue()) {
		return new XmlStatistics(self->lookupStatistics(uri, name,
								parent_uri,
								parent_name,
								index, value));
	}

OVERLOAD_NAME(lookupStatisticsWithTxn)
	XmlStatistics *lookupStatistics(XmlTransaction &txn,
					const std::string &uri,
					const std::string &name,
					const std::string &index,
					const XmlValue &value = XmlValue()) {
		return new XmlStatistics(self->lookupStatistics(txn, uri, name,
								index, value));
	}

OVERLOAD_NAME(lookupEdgeStatisticsWithTxn)
        XmlStatistics *lookupStatistics(XmlTransaction &txn,
					const std::string &uri,
					const std::string &name,
					const std::string &parent_uri,
					const std::string &parent_name,
					const std::string &index,
					const XmlValue &value = XmlValue()) {
		return new XmlStatistics(self->lookupStatistics(txn, uri, name,
								parent_uri,
								parent_name,
								index, value));
	}
} /* %extend */
};

class XmlDocument
{
public:
#ifndef SWIGJAVA
	XmlDocument();
#endif
	XmlDocument(const XmlDocument &o);
	~XmlDocument();

	void setName(const std::string &name);
	std::string getName() const;

#if !defined(SWIGTCL8) && !defined(SWIGPYTHON) && !defined(SWIGPHP4)
	/* 
	 * don't trust conversions with non utf-8 encodings 
	 * may be able to enable with some extra code/test
	 * force use of XmlData-based methods
	 */
	void setContent(const std::string &content);
OVERLOAD_NAME(setContentWithXmlData)
#endif
	void setContent(const XmlData &content);

	// input stream is owned by caller
	XmlInputStream *getContentAsXmlInputStream() const;
	// input stream is donated to callee
	void setContentAsXmlInputStream(XmlInputStream *adopted);

	void fetchAllData();
	void setMetaData(const std::string &uri,
			 const std::string &name, const XmlValue &value);
	bool getMetaData(const std::string &uri, const std::string &name,
			 XmlValue &value);
	void removeMetaData(const std::string &uri, const std::string &name);	
OVERLOAD_NAME(setMetaDataWithXmlData)
	void setMetaData(const std::string &uri,
			 const std::string &name, const XmlData &value);
#ifndef SWIGJAVA	
OVERLOAD_NAME(getMetaDataAsXmlData)
	bool getMetaData(const std::string &uri, const std::string &name,
			 XmlData &value);
#endif	
%extend {
	std::string getContentAsString() const {
		std::string s;
		return self->getContent(s);
	}
	const XmlData *getContent() const {
		return new XmlData(self->getContent());
	}
	const XmlData *getMetaData(const std::string &uri, const std::string &name) {
		XmlData data;
		bool ret = self->getMetaData(uri, name, data);
		if (ret)
			return new XmlData(data);
		return 0;
	}
	XmlMetaDataIterator *getMetaDataIterator() const {
		return new XmlMetaDataIterator(self->getMetaDataIterator());
	}
}
};

class XmlMetaDataIterator
{
public:
	XmlMetaDataIterator(const XmlMetaDataIterator &o);
	~XmlMetaDataIterator();

	void reset();

%extend {
	XmlMetaData *next() {
		XmlMetaData *idecl = new XmlMetaData;
		if (self->next(idecl->uri, idecl->name, idecl->value))
			return idecl;
		else
			delete idecl;
		return NULL;
	}
}
#if defined(SWIGPYTHON)
%pythoncode %{
	def __iter__(self): return self
%}
#endif

};

// A SWIG-only class to wrap the results of the
// XmlMetaDataIterator
class XmlMetaData {
public:
	~XmlMetaData();

	const std::string &get_uri() const;
	const std::string &get_name() const;
	const XmlValue &get_value() const;
};

class XmlQueryContext
{
public:
	enum // ReturnType
	{
		DeadValues,
		LiveValues
	};
	
	enum // EvaluationType
	{
		Eager,
		Lazy
	};
	
	/// Constructor.
#ifndef SWIGJAVA
	XmlQueryContext();
#endif
	XmlQueryContext(const XmlQueryContext &o);
	~XmlQueryContext();

	void setNamespace(const std::string &prefix, const std::string &uri);
	std::string getNamespace(const std::string &prefix);
	void removeNamespace(const std::string &prefix);
	void clearNamespaces(void);

	void setVariableValue(const std::string &name, const XmlValue &value);
	void setVariableValue(const std::string &name, XmlResults &value);
	
	void setBaseURI(const std::string &baseURI);
	std::string getBaseURI() const;
	void setReturnType(enum XmlQueryContext::ReturnType type);
	enum XmlQueryContext::ReturnType getReturnType() const;
	void setEvaluationType(
		enum XmlQueryContext::EvaluationType type);
	enum XmlQueryContext::EvaluationType getEvaluationType() const;
	void setDefaultCollection(const std::string &uri);
	std::string getDefaultCollection() const;
	
%extend {
	XmlValue *getVariableValue(const std::string &name) const {
		XmlValue *value = new XmlValue;
		try {
			if (self->getVariableValue(name, *value))
				return value;
			else {
				delete value;
				return NULL;
			}
		}
		catch(...) {
			delete value;
			throw;
		}
	}

	XmlResults *getVariableValues(const std::string &name) const {
		XmlResults *res = new XmlResults();
		try {
			if (self->getVariableValue(name, *res))
				return res;
			else {
				delete res;
				return NULL;
			}
		}
		catch(...) {
			delete res;
			throw;
		}
	}

#ifdef SWIGTCL8
	const std::string get(const char *name) const {
		XmlValue value;
		return self->getVariableValue(name, value) ? value.asString() : "";
	}
	
	void set(const std::string &name, const std::string &value) {
		XmlValue xval(value);
		self->setVariableValue(name, xval);
	}
	
	void setDebugVariable(const std::string &var) {
		self->setVariableValue("dbxml:debug", var);
	}
#endif /* SWIGTCL8 */
} /* %extend */
};

class XmlResults
{
public:
#ifndef SWIGJAVA
	XmlResults();
#endif
	~XmlResults();
	XmlResults(const XmlResults &results);

	bool hasNext();
	bool hasPrevious();
#if defined(SWIGJAVA) || defined(SWIGPYTHON) || defined(SWIGPHP4)
%extend {
	XmlValue *next() {
		XmlValue *value = new XmlValue;
		if (self->next(*value))
			return value;
		else {
			delete value;
			return NULL;
		}
	}
	XmlValue *previous() {
		XmlValue *value = new XmlValue;
		if (self->previous(*value))
			return value;
		else {
			delete value;
			return NULL;
		}
	}
	XmlValue *peek() {
		XmlValue *value = new XmlValue;
		if (self->peek(*value))
			return value;
		else {
			delete value;
			return NULL;
		}
	}
} /* %extend */
#else
	bool next(XmlValue &value);
	bool previous(XmlValue &value);
	bool peek(XmlValue &value);
#endif

OVERLOAD_NAME(nextDocument)
	bool next(XmlDocument &document);
OVERLOAD_NAME(previousDocument)
	bool previous(XmlDocument &document);
OVERLOAD_NAME(peekDocument)
	bool peek(XmlDocument &document);

#if defined(SWIGPYTHON)
%pythoncode %{
	def __iter__(self): return self
%}
#endif
	void reset();
	size_t size() const;
	void add(const XmlValue &value);

};

class XmlUpdateContext
{
public:
#ifndef SWIGJAVA
	XmlUpdateContext();
#endif
	XmlUpdateContext(const XmlUpdateContext &o);
	virtual ~XmlUpdateContext();

	void setApplyChangesToContainers(bool applyChanges);
	bool getApplyChangesToContainers() const;
};


class XmlValue
{
public:
	//NOTE: these enumerations MUST match those in XmlValue.hpp
	enum  //NodeType
	{
		ELEMENT_NODE = 1,
		ATTRIBUTE_NODE = 2,
		TEXT_NODE = 3,
		CDATA_SECTION_NODE = 4,
		ENTITY_REFERENCE_NODE = 5,
		ENTITY_NODE = 6,
		PROCESSING_INSTRUCTION_NODE = 7,
		COMMENT_NODE = 8,
		DOCUMENT_NODE = 9,
		DOCUMENT_TYPE_NODE = 10,
		DOCUMENT_FRAGMENT_NODE = 11,
		NOTATION_NODE = 12
	};

	enum // Type
	{
		NONE               = 0,
		NODE               = 3,

		/// abstract type (separates type ids for DB XML and
		/// XML Schema atomic types)
		ANY_SIMPLE_TYPE    = 10,

		ANY_URI            = 11,
		BASE_64_BINARY     = 12,
		BOOLEAN            = 13,
		DATE               = 14,
		DATE_TIME          = 15,
		/// not a built-in primitive type
		DAY_TIME_DURATION  = 16,
		DECIMAL            = 17,
		DOUBLE             = 18,
		DURATION           = 19,
		FLOAT              = 20,
		G_DAY              = 21,
		G_MONTH            = 22,
		G_MONTH_DAY        = 23,
		G_YEAR             = 24,
		G_YEAR_MONTH       = 25,
		HEX_BINARY         = 26,
		NOTATION           = 27,
		QNAME              = 28,
		STRING             = 29,
		TIME               = 30,
		/// not a built-in primitive type
		YEAR_MONTH_DURATION= 31,

		/// untyped atomic data
		UNTYPED_ATOMIC     = 32,
		BINARY		   = 40
	};
	XmlValue();
	XmlValue(const XmlValue &other);
OVERLOAD_NAME(XmlValueFromString)
	XmlValue(const std::string &v);
OVERLOAD_NAME(XmlValueFromDouble)
	XmlValue(double v);
#ifndef SWIGTCL8
	// Not included in Tcl because there is no way to distinguish between
	// a boolean and a number.
OVERLOAD_NAME(XmlValueFromBool)
	XmlValue(bool v);
#endif
OVERLOAD_NAME(XmlValueFromDocument)
	XmlValue(const XmlDocument &document);
OVERLOAD_NAME(XmlValueTypedFromString)
	XmlValue(enum XmlValue::Type type, const std::string &v);
OVERLOAD_NAME(XmlValueTypedFromXmlData)
	XmlValue(enum XmlValue::Type type, const XmlData &dbt);

	~XmlValue();
	enum XmlValue::Type getType() const;
	bool isNull() const;
	bool isType(enum XmlValue::Type type) const;

	bool isNumber() const;
	bool isString() const;
	bool isBoolean() const;
	bool isBinary() const;
	bool isNode() const;

	double asNumber() const;
	std::string asString() const;
OVERLOAD_NAME(asStringEncoded)
	std::string asString(const std::string &encoding) const;
	bool asBoolean() const;
%extend {
	XmlData * asBinary() const {
		XmlData data = self->asBinary();
		return new XmlData(data);
	}
}
#ifndef SWIGTCL8
	XmlDocument asDocument() const;
#else
%extend {
	XmlDocument *asDocument() const {
		return new XmlDocument(self->asDocument());
	}
}
#endif
	bool equals(const XmlValue &value) const;

	std::string getNodeName() const;
	std::string getNodeValue() const;
	std::string getNamespaceURI() const;
	std::string getPrefix() const;
	std::string getLocalName() const;
	short getNodeType() const;

%extend {
	XmlValue *getParentNode() const {
		return new XmlValue(self->getParentNode());
	}
	XmlValue *getFirstChild() const {
		return new XmlValue(self->getFirstChild());
	}
	XmlValue *getLastChild() const {
		return new XmlValue(self->getLastChild());
	}
	XmlValue *getPreviousSibling() const {
		return new XmlValue(self->getPreviousSibling());
	}
	XmlValue *getNextSibling() const {
		return new XmlValue(self->getNextSibling());
	}
	XmlResults *getAttributes() const {
		return new XmlResults(self->getAttributes());
	}
	XmlValue *getOwnerElement() const {
		return new XmlValue(self->getOwnerElement());
	}

	// allows scripted languages to emulate operator=
	static void setValue(XmlValue &to, const XmlValue &from) {
		to = from;
	}
}
};

class XmlIndexSpecification {
public:
	enum //Type 
	{
		UNIQUE_OFF = 0x00000000,
		UNIQUE_ON = 0x10000000,

		PATH_NONE = 0x00000000,
		PATH_NODE = 0x01000000,
		PATH_EDGE = 0x02000000,

		NODE_NONE = 0x00000000,
		NODE_ELEMENT = 0x00010000,
		NODE_ATTRIBUTE = 0x00020000,
		NODE_METADATA = 0x00030000,

		KEY_NONE = 0x00000000,
		KEY_PRESENCE = 0x00000100,
		KEY_EQUALITY = 0x00000200,
		KEY_SUBSTRING = 0x00000300
	};
#ifndef SWIGJAVA
	XmlIndexSpecification();
#endif
	virtual ~XmlIndexSpecification();

	void addIndex(const std::string &uri, const std::string &name,
		      enum XmlIndexSpecification::Type type,
		      enum XmlValue::Type syntax);
OVERLOAD_NAME(addIndexAsString)
	void addIndex(const std::string &uri, const std::string &name,
		      const std::string &index);
	void deleteIndex(const std::string &uri, const std::string &name,
		      enum XmlIndexSpecification::Type type,
		      enum XmlValue::Type syntax);
OVERLOAD_NAME(deleteIndexAsString)
	void deleteIndex(const std::string &uri, const std::string &name,
			 const std::string &index);
	void replaceIndex(const std::string &uri, const std::string &name,
		      enum XmlIndexSpecification::Type type,
		      enum XmlValue::Type syntax);
OVERLOAD_NAME(replaceIndexAsString)	
	void replaceIndex(const std::string &uri, const std::string &name,
			  const std::string &index);

	void addDefaultIndex(enum XmlIndexSpecification::Type type,
			     enum XmlValue::Type syntax);
OVERLOAD_NAME(addDefaultIndexAsString)
	void addDefaultIndex(const std::string &index);
	void deleteDefaultIndex(enum XmlIndexSpecification::Type type,
				enum XmlValue::Type syntax);
OVERLOAD_NAME(deleteDefaultIndexAsString)
	void deleteDefaultIndex(const std::string &index);
	void replaceDefaultIndex(enum XmlIndexSpecification::Type type,
				 enum XmlValue::Type syntax);
OVERLOAD_NAME(replaceDefaultIndexAsString)	
	void replaceDefaultIndex(const std::string &index);

	void reset();

%extend {
	XmlIndexDeclaration *find(const std::string &uri,
				  const std::string &name) {
		XmlIndexDeclaration *idecl =
			new XmlIndexDeclaration(uri, name, "");
		if (self->find(idecl->uri, idecl->name, idecl->index))
			return idecl;
		else {
			delete idecl;
			return NULL;
		}
	}
	
	XmlIndexDeclaration *next() {
		XmlIndexDeclaration *idecl = new XmlIndexDeclaration;
		if (self->next(idecl->uri, idecl->name, idecl->index))
			return idecl;
		else {
			delete idecl;
			return NULL;
		}
	}
}
	std::string getDefaultIndex() const;

	static enum XmlValue::Type getValueType(const std::string &index);

#if defined(SWIGPYTHON)
%pythoncode %{
	def __iter__(self): return self
%}
#endif
};

#ifndef SWIGJAVA
class XmlIndexDeclaration {
public:
	~XmlIndexDeclaration();

	const std::string &get_uri() const;
	const std::string &get_name() const;
	const std::string &get_index() const;
};
#endif

class XmlQueryExpression
{
public:
#ifndef SWIGJAVA
	XmlQueryExpression();
#endif
	XmlQueryExpression(const XmlQueryExpression &queryExpression);
	~XmlQueryExpression();

	const std::string & getQuery() const;
	std::string getQueryPlan() const;

%extend {
	XmlResults *execute(XmlQueryContext &context,
			    u_int32_t flags = 0) const {
		return new XmlResults(self->execute(context, flags));
	}
OVERLOAD_NAME(executeWithContextItem)
	 XmlResults *execute(const XmlValue &contextItem,
			     XmlQueryContext &context,
			     u_int32_t flags = 0) const {
		return new XmlResults(
			self->execute(contextItem, context, flags));
	}
OVERLOAD_NAME(executeWithTxn)
	 XmlResults *execute(XmlTransaction &txn, XmlQueryContext &context,
			     u_int32_t flags = 0) const {
		return new XmlResults(self->execute(txn, context, flags));
	}
OVERLOAD_NAME(executeWithContextItemAndTxn)
	 XmlResults *execute(XmlTransaction &txn, const XmlValue &contextItem,
			     XmlQueryContext &context,
			     u_int32_t flags = 0) const {
		return new XmlResults(self->execute(txn, contextItem,
						    context, flags));
	}
}
};

class XmlInputStream
{
#if defined(SWIGJAVA)
protected:
	XmlInputStream();
#endif
public:
	virtual ~XmlInputStream();
	// SWIG needs to know about pure virtuals; otherwise,
	// a reference will be generated.
	virtual unsigned int curPos() const = 0;
	virtual unsigned int readBytes(char *toFill,
				       const unsigned int maxToRead) = 0;
%extend {
	// allow wrapped languages to free C++ memory in the event
	// object is not donated to putDocument().
	void freeMemory() {
		delete self;
	}
}
};

#if defined(DBXML_USE_RESOLVER)

#if defined(SWIGJAVA)
%apply const std::string & {std::string &};
#endif

class XmlResolver
{
protected:
	XmlResolver();
public:
	virtual ~XmlResolver();
	virtual bool resolveDocument(XmlTransaction *txn,XmlManager &mgr,
				     const std::string &uri, XmlValue &res) const;
	virtual bool resolveCollection(XmlTransaction *txn, XmlManager &mgr,
				       const std::string &uri, XmlResults &res) const;
	virtual XmlInputStream *resolveSchema(XmlTransaction *txn, XmlManager &mgr,
					      const std::string &schemaLocation,
					      const std::string &nameSpace) const;
	virtual XmlInputStream *resolveEntity(XmlTransaction *txn, XmlManager &mgr,
					      const std::string &systemId,
					      const std::string &publicId) const;
};
#endif

class XmlModify
{
public:
	enum // XmlObject
	{
		Element,
		Attribute,
		Text,
		ProcessingInstruction,
		Comment
	};
#ifndef SWIGJAVA
	XmlModify();
#endif
	XmlModify(const XmlModify &o);
	~XmlModify();

	void addInsertBeforeStep(const XmlQueryExpression &selectionExpr,
				 enum XmlModify::XmlObject type,
				 const std::string &name,
				 const std::string &content);
	void addInsertAfterStep(const XmlQueryExpression &selectionExpr,
				enum XmlModify::XmlObject type,
				const std::string &name,
				const std::string &content);
	void addAppendStep(const XmlQueryExpression &selectionExpr,
			   enum XmlModify::XmlObject type,
			   const std::string &name,
			   const std::string &content, int location = -1);
	void addUpdateStep(const XmlQueryExpression &selectionExpr,
			   const std::string &content);
	void addRemoveStep(const XmlQueryExpression &selectionExpr);
	void addRenameStep(const XmlQueryExpression &selectionExpr,
			   const std::string &newName);

	void setNewEncoding(const std::string &newEncoding);

	unsigned int execute(XmlValue &toModify, XmlQueryContext &context,
			     XmlUpdateContext &uc) const;
OVERLOAD_NAME(executeOnResults)
	unsigned int execute(XmlResults &toModify, XmlQueryContext &context,
			     XmlUpdateContext &uc) const;
OVERLOAD_NAME(executeWithTxn)
	unsigned int execute(XmlTransaction &txn, XmlValue &toModify,
			     XmlQueryContext &context,
			     XmlUpdateContext &uc) const;
OVERLOAD_NAME(executeOnResultsWithTxn)
	unsigned int execute(XmlTransaction &txn, XmlResults &toModify,
			     XmlQueryContext &context,
			     XmlUpdateContext &uc) const;
};

class XmlTransaction
{
public:
	~XmlTransaction();
#ifndef SWIGJAVA
	XmlTransaction();
	XmlTransaction(const XmlTransaction &);

	void abort();
	void commit(u_int32_t flags);
	
%extend {
	XmlTransaction *createChild(u_int32_t flags = 0) {
		return new XmlTransaction(self->createChild(flags));
	}
OVERLOAD_NAME(commitDefaultFlags)
	void commit() {
	  self->commit(0);
	}
}

	DbTxn *getDbTxn();
#endif // !SWIGJAVA	
};

class XmlStatistics
{
public:
	XmlStatistics(const XmlStatistics&);
	~XmlStatistics();

	double getNumberOfIndexedKeys() const;
	double getNumberOfUniqueKeys() const;
	double getSumKeyValueSize() const;
};

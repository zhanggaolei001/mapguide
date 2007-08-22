/* Statistics classes */
%{
/*
 * These macros are used by code generated by the s_java script.
 */
#define JAVADB_STAT_INT(jenv, jobj, fid, statp, name)			\
		(*jenv)->SetIntField(jenv, jobj, fid, (jint)statp->name)

#define JAVADB_STAT_STRING(jenv, jobj, fid, statp, name)		\
		(*jenv)->SetObjectField(jenv, jobj, fid,		\
		    (*jenv)->NewStringUTF(jenv, statp->name))

#define JAVADB_STAT_LSN(jenv, jobj, fid, statp, name)			\
		(*jenv)->SetObjectField(jenv, jobj, fid,		\
		    __dbj_wrap_DB_LSN(jenv, &statp->name))

#define JAVADB_STAT_LONG(jenv, jobj, fid, statp, name)			\
		(*jenv)->SetLongField(jenv, jobj, fid,			\
		    (jlong)statp->name)

#define JAVADB_STAT_XID(jenv, jobj, fid, statp, name) {			\
	jobject jarr =							\
	    (*jenv)->NewByteArray(jenv, (jsize)DB_XIDDATASIZE);		\
	(*jenv)->SetByteArrayRegion(jenv, jarr,				\
	    0, (jsize)DB_XIDDATASIZE, (jbyte *)statp->name);		\
	(*jenv)->SetObjectField(jenv, jobj, fid, jarr);			\
	}

/*
 * We build the active list separately.
 */
#define JAVADB_STAT_ACTIVE(jenv, cl, jobj, statp, name) \
	do {} while(0)

#include "java_stat_auto.c"
%}

%define JAVA_STAT_CLASS(_ctype, _jtype, _name)
JAVA_TYPEMAP(_ctype, _jtype, jobject)
%typemap(out) _ctype %{
	$result = (*jenv)->NewObject(jenv, _name##_class, _name##_construct);
	if ($result != NULL)
		__dbj_fill_##_name(jenv, $result, $1);
	__os_ufree(NULL, $1);
%}
%enddef

JAVA_STAT_CLASS(DB_COMPACT *, com.sleepycat.db.CompactStats, compact)
%typemap(freearg) DB_COMPACT * %{ __dbj_fill_compact(jenv, $input, $1); %}
%typemap(in) DB_COMPACT * (DB_COMPACT compact) %{
        memset(&compact, 0, sizeof (DB_COMPACT));
        $1 = &compact;
        $1->compact_fillpercent = (*jenv)->GetIntField(jenv, $input,
            compact_compact_fillpercent_fid);
        $1->compact_timeout = (*jenv)->GetIntField(jenv, $input,
            compact_compact_timeout_fid);
        $1->compact_pages = (*jenv)->GetIntField(jenv, $input,
            compact_compact_pages_fid);
%}

JAVA_STAT_CLASS(DB_LOCK_STAT *, com.sleepycat.db.LockStats, lock_stat)
JAVA_STAT_CLASS(DB_LOG_STAT *, com.sleepycat.db.LogStats, log_stat)
JAVA_STAT_CLASS(DB_MPOOL_STAT *, com.sleepycat.db.CacheStats, mpool_stat)

JAVA_TYPEMAP(DB_MPOOL_FSTAT **, com.sleepycat.db.CacheFileStats[], jobjectArray)
%typemap(out) DB_MPOOL_FSTAT ** {
	int i, len;

	len = 0;
	while ($1[len] != NULL)
		len++;
	$result = (*jenv)->NewObjectArray(jenv, (jsize)len,
	    mpool_fstat_class, 0);
	if ($result == NULL) {
		__os_ufree(NULL, $1);
		return $null;
	}
	for (i = 0; i < len; i++) {
		jobject obj = (*jenv)->NewObject(jenv, mpool_fstat_class,
		    mpool_fstat_construct);
		if (obj == NULL) {
			__os_ufree(NULL, $1);
			return $null; /* an exception is pending */
		}
		(*jenv)->SetObjectArrayElement(jenv, $result, i, obj);
		__dbj_fill_mpool_fstat(jenv, obj, $1[i]);
	}
	__os_ufree(NULL, $1);
}

JAVA_STAT_CLASS(DB_MUTEX_STAT *, com.sleepycat.db.MutexStats, mutex_stat)
JAVA_STAT_CLASS(DB_REP_STAT *, com.sleepycat.db.ReplicationStats, rep_stat)
JAVA_STAT_CLASS(DB_SEQUENCE_STAT *, com.sleepycat.db.SequenceStats, seq_stat)
JAVA_TYPEMAP(DB_TXN_STAT *, com.sleepycat.db.TransactionStats, jobject)
%typemap(out) DB_TXN_STAT * {
	unsigned int i;
	jobjectArray actives;
	$result = (*jenv)->NewObject(jenv, txn_stat_class, txn_stat_construct);
	if ($result != NULL)
		__dbj_fill_txn_stat(jenv, $result, $1);

	actives = (*jenv)->NewObjectArray(jenv, (jsize)$1->st_nactive,
	    txn_active_class, 0);
	if (actives == NULL) {
		__os_ufree(NULL, $1);
		return $null;
	}
	(*jenv)->SetObjectField(jenv, $result,
	    txn_stat_st_txnarray_fid, actives);
	for (i = 0; i < $1->st_nactive; i++) {
		jobject obj = (*jenv)->NewObject(jenv, txn_active_class,
		    txn_active_construct);
		if (obj == NULL) {
			__os_ufree(NULL, $1);
			return $null; /* an exception is pending */
		}
		(*jenv)->SetObjectArrayElement(jenv, actives, (jsize)i, obj);
		__dbj_fill_txn_active(jenv, obj, &$1->st_txnarray[i]);
	}
	__os_ufree(NULL, $1);
}

/* Db.stat return - special case */
%typemap(out) void * %{
	if ($1 == NULL)
		$result = NULL;
	else {
		DB *db = (DB *)arg1;
		DBTYPE dbtype;
		int err;

		if ((err = db->get_type(db, &dbtype)) != 0) {
			__dbj_throw(jenv, err, NULL, NULL, DB2JDBENV);
			return $null;
		}

		switch (dbtype) {
			/* Btree and recno share the same stat structure */
		case DB_BTREE:
		case DB_RECNO:
			$result = (*jenv)->NewObject(jenv, bt_stat_class,
			    bt_stat_construct);
			if ($result != NULL)
				__dbj_fill_bt_stat(jenv, $result,
				    (DB_BTREE_STAT *)$1);
			break;

			/* Hash stat structure */
		case DB_HASH:
			$result = (*jenv)->NewObject(jenv, h_stat_class,
			    h_stat_construct);
			if ($result != NULL)
				__dbj_fill_h_stat(jenv, $result,
				    (DB_HASH_STAT *)$1);
			break;

		case DB_QUEUE:
			$result = (*jenv)->NewObject(jenv, qam_stat_class,
			    qam_stat_construct);
			if ($result != NULL)
				__dbj_fill_qam_stat(jenv, $result,
				    (DB_QUEUE_STAT *)$1);
			break;

			/* That's all the database types we're aware of! */
		default:
			__dbj_throw(jenv, EINVAL, "Db.stat only implemented for"
			    " BTREE, HASH, QUEUE and RECNO", NULL, DB2JDBENV);
			break;
		}

		__os_ufree(db->dbenv, $1);
	}
%}


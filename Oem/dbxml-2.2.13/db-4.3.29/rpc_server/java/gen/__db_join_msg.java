/*
 * Automatically generated by jrpcgen 0.95.1 on 12/18/01 7:23 PM
 * jrpcgen is part of the "Remote Tea" ONC/RPC package for Java
 * See http://acplt.org/ks/remotetea.html for details
 */
package com.sleepycat.db.rpcserver;
import org.acplt.oncrpc.*;
import java.io.IOException;

public class __db_join_msg implements XdrAble {
    public int dbpcl_id;
    public int [] curs;
    public int flags;

    public __db_join_msg() {
    }

    public __db_join_msg(XdrDecodingStream xdr)
           throws OncRpcException, IOException {
        xdrDecode(xdr);
    }

    public void xdrEncode(XdrEncodingStream xdr)
           throws OncRpcException, IOException {
        xdr.xdrEncodeInt(dbpcl_id);
        xdr.xdrEncodeIntVector(curs);
        xdr.xdrEncodeInt(flags);
    }

    public void xdrDecode(XdrDecodingStream xdr)
           throws OncRpcException, IOException {
        dbpcl_id = xdr.xdrDecodeInt();
        curs = xdr.xdrDecodeIntVector();
        flags = xdr.xdrDecodeInt();
    }

}
// End of __db_join_msg.java

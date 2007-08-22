/*
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2000,2006 Oracle.  All rights reserved.
 *
 * $Id: common_utils.h,v 1.4 2006/10/30 17:45:50 bostic Exp $
 */

#ifndef COMMON_UTILS_H
#define COMMON_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif
	
void dbxml_util_siginit();
int dbxml_util_interrupted();
void dbxml_util_sigresend();
void dbxml_set_signal_listener(void (*listener)(int));

#ifdef __cplusplus
}

namespace DbXml {
	// abstract class to call when a signal happens
	class SignalListener {
	public:
		virtual ~SignalListener() {}
		virtual void signal(int signo) = 0;
	};

	// class to wrap above interfaces
	class SigBlock {
	public:
		SigBlock();
		~SigBlock();
		bool isInterrupted() const;
		void setListener(SignalListener *listener);
	};
}

#endif

#endif

/*
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2000,2006 Oracle.  All rights reserved.
 *
 * $Id: SigBlock.cpp,v 1.2 2006/10/30 17:45:50 bostic Exp $
 */

#include "common_utils.h"

using namespace DbXml;

static SignalListener *sListener = 0;

static void sigblock_signal_listener(int signo)
{
	sListener->signal(signo);
}

SigBlock::SigBlock()
{
	dbxml_util_siginit();
}

SigBlock::~SigBlock()
{
	dbxml_set_signal_listener(0);
	sListener = 0;
	dbxml_util_sigresend();
}

bool SigBlock::isInterrupted() const
{
	return (dbxml_util_interrupted() ? true : false);
}

void SigBlock::setListener(SignalListener *listener)
{
	sListener = listener;

	if(sListener != 0)
		dbxml_set_signal_listener(sigblock_signal_listener);
	else dbxml_set_signal_listener(0);
}

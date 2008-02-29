//
// See the file LICENSE for redistribution information.
//
// Copyright (c) 2002,2006 Oracle.  All rights reserved.
//
// $Id: CompactCommand.hpp,v 1.2 2006/10/30 17:46:07 bostic Exp $
//

#ifndef __COMPACTCOMMAND_HPP
#define	__COMPACTCOMMAND_HPP

#include "ShellCommand.hpp"

class CompactCommand : public ShellCommand
{
public:
	CompactCommand() {};
	virtual ~CompactCommand() {};

	virtual std::string getCommandName() const;
	virtual std::string getBriefHelp() const;
	virtual std::string getMoreHelp() const;
	
	virtual void execute(Args &args, Environment &env);
};

#endif

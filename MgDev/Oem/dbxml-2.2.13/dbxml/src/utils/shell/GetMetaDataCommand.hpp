//
// See the file LICENSE for redistribution information.
//
// Copyright (c) 2002-2005
//	Sleepycat Software.  All rights reserved.
//
// $Id: GetMetaDataCommand.hpp,v 1.1 2005/04/04 21:45:02 gmf Exp $
//

#ifndef __GETMETADATACOMMAND_HPP
#define __GETMETADATACOMMAND_HPP

#include "ShellCommand.hpp"

class GetMetaDataCommand : public ShellCommand
{
public:
	GetMetaDataCommand() {};
	virtual ~GetMetaDataCommand() {};

	virtual std::string getCommandName() const;
	virtual std::string getBriefHelp() const;
	virtual std::string getMoreHelp() const;
	
	virtual void execute(Args &args, Environment &env);
};

#endif

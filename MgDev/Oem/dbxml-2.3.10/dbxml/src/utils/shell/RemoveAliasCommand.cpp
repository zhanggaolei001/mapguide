//
// See the file LICENSE for redistribution information.
//
// Copyright (c) 2002,2006 Oracle.  All rights reserved.
//
// $Id: RemoveAliasCommand.cpp,v 1.3 2006/10/30 17:46:08 bostic Exp $
//

#include "RemoveAliasCommand.hpp"

using namespace DbXml;
using namespace std;

string RemoveAliasCommand::getCommandName() const
{
	return "removeAlias";
}

string RemoveAliasCommand::getBriefHelp() const
{
	return "Remove an alias from the default container";
}

string RemoveAliasCommand::getMoreHelp() const
{
	return
		string("Usage: removeAlias <alias>\n")+
		string("This command uses the XmlContainer::removeAlias() method.\n");
}

void RemoveAliasCommand::execute(Args &args, Environment &env)
{
	if (args.size() != 2) {
		throw CommandException("Wrong number of arguments");
	}
	env.testContainer();
	env.container()->removeAlias(args[1]);
	if(env.verbose()) cout << "Removed alias: " << args[1] << endl;
}


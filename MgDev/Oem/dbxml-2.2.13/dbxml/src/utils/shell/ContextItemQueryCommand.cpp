//
// See the file LICENSE for redistribution information.
//
// Copyright (c) 2002-2005
//	Sleepycat Software.  All rights reserved.
//
// $Id: ContextItemQueryCommand.cpp,v 1.8 2005/04/20 18:31:38 bostic Exp $
//

#include "ContextItemQueryCommand.hpp"

using namespace DbXml;
using namespace std;

string ContextItemQueryCommand::getCommandNameCompat() const
{
	return "ciquery";
}

string ContextItemQueryCommand::getCommandName() const
{
	return "contextQuery";
}

string ContextItemQueryCommand::getBriefHelp() const
{
	return "Execute query expression using the last results as the context item";
}

string ContextItemQueryCommand::getMoreHelp() const
{
	return
		string("Usage: contextQuery <queryExpression>\n") +
		string("The query is run against the most recent results.\n") +
		string("This command uses XmlManager::prepare() to create a\n") +
		string("XmlQueryExpression, then loops through the XmlValue objects\n") +
		string("in results, calling execute(..., XmlValue &contextItem, ...)");
}

void ContextItemQueryCommand::execute(Args &args, Environment &env)
{
	if(args.size() != 2) {
		throw CommandException("Wrong number of arguments");
	}
	env.testResults();
	XmlResults newResults = env.db().createResults();
	env.results()->reset();

	if(env.txn()) {
		XmlQueryExpression expr = env.db().prepare(*env.txn(), args[1], env.context());

		XmlValue value;
		while(env.results()->next(value)) {
			XmlResults tmpResults = expr.execute(*env.txn(), value, env.context());

			XmlValue tmpValue;
			while(tmpResults.next(tmpValue)) {
				newResults.add(tmpValue);
			}
		}
	} else {
		XmlQueryExpression expr = env.db().prepare(args[1], env.context());

		XmlValue value;
		while(env.results()->next(value)) {
			XmlResults tmpResults = expr.execute(value, env.context());

			XmlValue tmpValue;
			while(tmpResults.next(tmpValue)) {
				newResults.add(tmpValue);
			}
		}
	}

	env.deleteResults();
	env.results() = new XmlResults(newResults);

	if(env.verbose()) cout << env.results()->size() << " objects returned for expression '"
			       << args[1] << "'\n" << endl;
}


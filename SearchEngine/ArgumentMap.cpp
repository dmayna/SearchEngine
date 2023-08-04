#include "ArgumentMap.h"
#include <ctype.h>
#include <string>

using namespace std;

ArgumentMap::ArgumentMap(vector<string> args)
{
	parse(args);
}

void ArgumentMap::parse(vector<string> args)
{
	for (size_t i = 0; i < args.size(); i++) {
		if (isFlag(args[i])) {
			if (i < args.size() - 1 && isValue(args[i + 1])) {
				ArgMap[args[i]] = args[i];
			}
			else {
				ArgMap[args[i]] = "";
			}
		}
	}
}

bool ArgumentMap::isFlag(string arg)
{
	if (arg == "") {
		return false;
	}
	return (arg.rfind("-", 0) == 0) && arg.length() >= 2 && !isdigit(arg[1]);
}


bool ArgumentMap::isValue(string arg)
{
	return !isFlag(arg);
}


size_t ArgumentMap::numFlags()
{
	return ArgMap.size();
}


bool ArgumentMap::hasFlag(string flag)
{
	return ArgMap.count(flag);
}


bool ArgumentMap::hasValue(string flag)
{
	return ArgMap.at(flag) == "";
}


string ArgumentMap::getString(string flag)
{
	return ArgMap.at(flag);
}


string ArgumentMap::getString(string flag, string defaultValue)
{
	if (ArgMap.at(flag) != "") {
		return ArgMap.at(flag);
	}
	else {
		return defaultValue;
	}
}


int ArgumentMap::getInteger(string flag, int defaultValue)
{
	try
	{
		return stoi(flag);
	}
	catch (std::invalid_argument const& e)
	{
		return defaultValue;
	}
	catch (std::out_of_range const& e)
	{
		return defaultValue;
	}
}

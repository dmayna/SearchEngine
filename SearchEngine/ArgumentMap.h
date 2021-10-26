#pragma once

#include <iostream>
#include <map>
#include <vector>
using namespace std;

/**
 * Parses and stores command-line arguments into simple key = value pairs.
 *
 * @author Dylan Maynard
 */
class ArgumentMap
{
public:
	/**
	 * Initializes this argument map and then parsers the arguments into
	 * flag/value pairs where possible. Some flags may not have associated values.
	 * If a flag is repeated, its value is overwritten.
	 *
	 * @param args the command line arguments to parse
	 */
	ArgumentMap(vector<string> args);

	/**
	 * Parses the arguments into flag/value pairs where possible. Some flags may
	 * not have associated values. If a flag is repeated, its value is
	 * overwritten.
	 *
	 * @param args the command line arguments to parse
	 */
	void parse(vector<string> args);

	/**
	 * Determines whether the argument is a flag. Flags start with a dash "-"
	 * character, followed by at least one other non-digit character.
	 *
	 * @param arg the argument to test if its a flag
	 * @return {@code true} if the argument is a flag
	 */
	static bool isFlag(string arg);

	/**
	 * Determines whether the argument is a value. Anything that is not a flag is
	 * considered a value.
	 *
	 * @param arg the argument to test if its a value
	 * @return {@code true} if the argument is a value
	 */
	static bool isValue(string arg);

	/**
	 * Returns the number of unique flags.
	 *
	 * @return number of unique flags
	 */
	size_t numFlags();

	/**
	 * Determines whether the specified flag exists.
	 *
	 * @param flag the flag find
	 * @return {@code true} if the flag exists
	 */
	bool hasFlag(string flag);

	/**
	 * Determines whether the specified flag is mapped to a non-null value.
	 *
	 * @param flag the flag to find
	 * @return {@code true} if the flag is mapped to a non-null value
	 */
	bool hasValue(string flag);

	/**
	 * Returns the value to which the specified flag is mapped as a
	 * {@link String}, or null if there is no mapping.
	 *
	 * @param flag the flag whose associated value is to be returned
	 * @return the value to which the specified flag is mapped, or {@code null} if
	 *         there is no mapping
	 */
	string getString(string flag);

	/**
	 * Returns the value to which the specified flag is mapped as a
	 * {@link String}, or the default value if there is no mapping.
	 *
	 * @param flag the flag whose associated value is to be returned
	 * @param defaultValue the default value to return if there is no mapping
	 * @return the value to which the specified flag is mapped, or the default
	 *         value if there is no mapping
	 */
	string getString(string flag, string defaultValue);

	/**
	 * Returns the value the specified flag is mapped as an int value, or the
	 * default value if unable to retrieve this mapping (including being unable to
	 * convert the value to an int or if no value exists).
	 *
	 * @param flag the flag whose associated value will be returned
	 * @param defaultValue the default value to return if there is no valid
	 *        mapping
	 * @return the value the specified flag is mapped as a int, or the default
	 *         value if there is no valid mapping
	 */
	int getInteger(string flag, int defaultValue);

private:
	/**
	 * Stores command-line arguments in key = value pairs.
	 */
	map<string, string> ArgMap;
};


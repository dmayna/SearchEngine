#pragma once

#include <iostream>
#include <vector>
using namespace std;

/**
 * A utility class for finding all text files in a directory 
 * @author Dylan Maynard
 */
class TextFileFinder
{
public:
	/**
	 * function that returns true if the path is a file that ends in a
	 * .txt or .text extension (case-insensitive). Useful for
	 */
	static bool isText(string inFile);

	/**
	 * Returns true if fullstring ends with ending otherwise returns false
	 *
	 * @param fullstring the strign to check ending
	 * @param ending the end of string to check if its in fullstring
	 * @return true or false
	 */
	static bool hasEnding(string const& fullString, string const& ending);

	/**
	 * Returns a list of text files using streams.
	 *
	 * @param start the initial path to search
	 * @return list of text files
	 * @throws IOException if an IO error occurs
	 */
	static vector<string> list(string start);
};


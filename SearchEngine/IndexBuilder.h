#pragma once

#include "InvertedIndex.h"
using namespace std;
/**
 *Builder for Inverted Index
 *
 * @author Dmayna
 */
class IndexBuilder
{
public:
	/**
	 * Builds Inverted Index
	 *
	 * @param dir Path of file or directory
	 * @param index Inverted index to use
	 * @throws IOException if unable to read or parse file
	 */
	static void buildIndex(string dir, InvertedIndex *index);

	/**
	 * parses a file and adds every stem word to inverted index
	 *
	 * @param file the file to parse
	 * @param index the inverted index to add to
	 * @throws IOException if unable to read or parse file
	 *
	 */
	static void parseFile(string file, InvertedIndex *index);
};


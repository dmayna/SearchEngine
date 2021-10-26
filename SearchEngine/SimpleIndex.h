#pragma once

#include <iostream>
#include <vector>
using namespace std;

/**
 * An index to store locations and the words found at those locations. Makes no
 * assumption about order or duplicates.
 *
 * @author Dylan Maynard
 */
class SimpleIndex
{
public:
	/**
	 * Adds the location and word.
	 *
	 * @param location the location the word was found
	 * @param word the word found
	 * @param position the word was found at
	 */
	virtual void add(string location, string word, int position) = 0;
	
	/**
	 * Adds the location and the provided words.
	 *
	 * @param location the location the words were found
	 * @param words the words found at that location
	 */
	void add(string location, vector<string> words);
	
	/**
	 * Returns the number of occurrences of words stored at the given path.
	 *
	 * @param word the word to lookup
	 * @param location the location to look at
	 * @return 0 if the word or location is not in the index or has no words, otherwise
	 *         the number of words stored for that element
	 */
	int size(string word, string location);
	
	/**
	 * Returns the number of words stored for the given path.
	 *
	 * @param word the word to lookup
	 * @return 0 if the location is not in the index or has no words, otherwise
	 *         the number of words stored for that element
	 */
	int size(string word);

	/**
	 * Returns the number of locations stored in the index.
	 *
	 * @return 0 if the index is empty, otherwise the number of locations in the
	 *         index
	 */
	int size();

	/**
	 * Determines whether the location is stored in the index.
	 *
	 * @param word the word to lookup
	 * @return {@true} if the location is stored in the index
	 */
	bool contains(string word);

	/**
	 * Determines whether the location is stored in the index and the word is
	 * stored for that location.
	 *
	 * @param location the location to lookup
	 * @param word the word in that location to lookup
	 * @return {@true} if the location and word is stored in the index
	 */
	bool contains(string word, string location);

	/**
	 * Determines whether the position of a specific word and location is stored in the index
	 * @param position the position to lookup
	 * @param location the location in that position lookup
	 * @param word the word in that location to lookup
	 * @return {@true} if the location and word is stored in the index
	 */
	bool contains(string word, string location, int position);
};
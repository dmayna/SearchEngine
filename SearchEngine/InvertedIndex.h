#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include "SimpleIndex.h"


class InvertedIndex : public SimpleIndex
{
public:
	/**
	 * Initializes this Index map.
	 */
	InvertedIndex();

	void add(string word, string location, int position);
	bool contains(string word);
	bool contains(string word, string location);
	bool contains(string word, string location, int position);
	size_t size(string word, string location);
	size_t size(string word);
	size_t size();

	/**
	 * Returns an unmodifiable view of the words stored in the index for the
	 * provided location, or an empty collection if the location is not in the
	 * index.
	 *
	 * @param word the word to lookup
	 * @return an unmodifiable view of the words stored for the location
	 */
	vector<string> getLocationsOfWord(string word);

	/**
	 * Returns an unmodifiable view of the words stored in the index.
	 *
	 * @return an unmodifiable view of the locations stored in the index
	 */
	vector<string> getWords();

	/**
	 * Returns word count for given location
	 *
	 * @param location to return word count for
	 * @return integer count for words in given file
	 */
	int getWordCount(string location);

	/**
	 * Returns an unmodifiable view of the words positions stored in the index for the
	 * provided location, or an empty collection if the location is not in the
	 * index.
	 *
	 * @param word the word to lookup
	 * @param location the location to lookup
	 * @return an unmodifiable view of the word positions stored for the location
	 */
	vector<int> getLocations(string word, string location);

	/**
	 * merges inverted index into this one
	 *
	 * @param local the inverted index to merge
	 */
	void merge(InvertedIndex* local);

	/**
	 * A result class that is able to be sorted by score, count and location
	 *
	 * @author Dylan Maynard
	 */
	class Result
	{
	public:
		Result(string location, InvertedIndex * index)
		{
			this->where = location;
			this->count = 0;
			this->score = 0;
			this->index = index;
		}

		/**
		 * Returns score of result
		 *
		 * @return score of result
		 */
		double getScore() {
			return this->score;
		}

		/**
		 * Returns count of result
		 *
		 * @return count of result
		 */
		size_t getCount() {
			return this->count;
		}

		/**
		 * Returns location of result
		 *
		 * @return location of result
		 */
		string getWhere() {
			return this->where;
		}

		/**
		 * Updates a search result with new word count and score
		 * @param key new updated key to use to update result
		 */
		void update(string key) {
			this->count += index->size(key, this->where);
			//cout << "update count: " << this->count << endl;
			this->score = (((double)count / (double)index->getWordCount(this->where)));
			//cout << "update word count: " << (double)index->getWordCount(this->where) << endl;
			//cout << "update score: " << this->score << endl;
		}

	private:
		/**
		 * Stores location of Path
		 */
		string where;

		/**
		 * Stores count at Path
		 */
		size_t count;

		/**
		 * Stores score of result
		 */
		double score;

		/**
		 * Stores pointer to index
		 */
		InvertedIndex * index;
	};

	/**
	 * performs partial or exact search on inverted index with queries depending on exact param
	 * @param queries to search for
	 * @param exact the tpye of search to perform
	 * @return a List of search results
	 */
	vector<InvertedIndex::Result> * search(set<string> queries, bool exact);

	/**
	 * performs partial search on inverted index with query
	 * @param queries to search for
	 * @return a List of search results
	 */
	vector<InvertedIndex::Result> * partialSearch(set<string> queries);

	/**
	 * performs exact search on inverted index with query
	 * @param queries to search for
	 * @return a List of search results
	 */
	vector<InvertedIndex::Result> * exactSearch(set<string> queries);

	/**
	 * found word in search and adds result to list
	 * @param results the list of results
	 * @param lookup the lookup map for inverted index
	 * @param queries to search for
	 * @param word the word searched for
	 */
	void foundWord(vector<Result> * results, map<string, Result> * lookup, set<string> queries, string word);

private:
	/**
	 * Stores locations of Paths and words found in that location in key = value pairs.
	 */
	map<string, map< string, vector<int>>> Map;

	/**
	 * Stores locations of Paths and word count found in that location in key = value pairs.
	 */
	map< string, int> WordCount;
};


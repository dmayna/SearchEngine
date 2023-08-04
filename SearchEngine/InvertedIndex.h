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
			where_ = location;
			count_ = 0;
			score_ = 0;
			index_ = index;
			//TODO add query
		}

		/**
		 * Returns score of result
		 *
		 * @return score of result
		 */
		double getScore() {
			return score_;
		}

		/**
		 * Returns count of result
		 *
		 * @return count of result
		 */
		size_t getCount() {
			return count_;
		}

		/**
		 * Returns location of result
		 *
		 * @return location of result
		 */
		string getWhere() {
			return where_;
		}

		/**
		 * Updates a search result with new word count and score
		 * @param key new updated key to use to update result
		 */
		void update(string key) {
			count_ += index_->size(key, where_);
			//cout << "update count: " << count_ << endl;
			score_ = (((double)count_ / (double)index_->getWordCount(where_)));
			//cout << "update word count: " << (double)index_->getWordCount(where_) << endl;
			//cout << "update score: " << score_ << endl;
		}

	private:
		/**
		 * Stores location of Path
		 */
		string where_;

		/**
		 * Stores count at Path
		 */
		size_t count_;

		/**
		 * Stores score of result
		 */
		double score_;

		/**
		 * Stores pointer to index
		 */
		InvertedIndex * index_;
	};

	/**
	 * performs partial or exact search on inverted index with queries depending on exact param
	 * @param queries to search for
	 * @param exact the tpye of search to perform
	 * @return a List of search results
	 */
	vector<InvertedIndex::Result *> * search(set<string> queries, bool exact);

	/**
	 * performs partial search on inverted index with query
	 * @param queries to search for
	 * @return a List of search results
	 */
	vector<InvertedIndex::Result *> * partialSearch(set<string> queries);

	/**
	 * performs exact search on inverted index with query
	 * @param queries to search for
	 * @return a List of search results
	 */
	vector<InvertedIndex::Result *> * exactSearch(set<string> queries);

	/**
	 * found word in search and adds result to list
	 * @param results the list of results
	 * @param lookup the lookup map for inverted index
	 * @param queries to search for
	 * @param word the word searched for
	 */
	void foundWord(vector<Result *> * results, map<string, Result *> * lookup, string word);

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


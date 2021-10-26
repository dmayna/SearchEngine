#include "InvertedIndex.h"
using namespace std;

InvertedIndex::InvertedIndex()
{
	cout << "Inverted Index created" << endl;
}

int InvertedIndex::getWordCount(string location)
{
	return WordCount[location];
}

void InvertedIndex::add(string word, string location, int position)
{
	if (Map[word].empty()) {
		vector<int> temp = { position };
		Map[word].insert(pair < string, vector<int> >(location, temp));
	}
	else {
		Map[word][location].push_back(position);
	}
	if (position > getWordCount(location)) {
		WordCount[location] = position;
	}
}

vector<string> InvertedIndex::getLocationsOfWord(string word)
{
	vector<string> locations;
	for (auto it = Map[word].begin(); it != Map[word].end(); it++)
	{
		locations.push_back(it->first);
	}
	return locations;
}

vector<string> InvertedIndex::getWords()
{
	vector<string> words;
	for (auto it = Map.begin(); it != Map.end(); it++)
	{
		words.push_back(it->first);
	}
	return words;
}

vector<int> InvertedIndex::getLocations(string word, string location)
{
	return Map[word][location];
}

bool InvertedIndex::contains(string word) {
	if (Map[word].empty()) {
		return false;
	}
	else {
		return true;
	}
}

bool InvertedIndex::contains(string word, string location)
{
	if (Map[word][location].empty()) {
		return false;
	}
	else {
		return true;
	}
}

bool InvertedIndex::contains(string word, string location, int position)
{
	for (int i : Map[word][location]) {
		if (position == i) {
			return true;
		}
	}
	return false;
}

int InvertedIndex::size()
{
	return Map.size();
}

int InvertedIndex::size(string word)
{
	return Map[word].size();
}

int InvertedIndex::size(string word, string location)
{
	return Map[word][location].size();
}

vector<InvertedIndex::Result> * InvertedIndex::search(set<string> queries, bool exact)
{
	if (exact) {
		return exactSearch(queries);
	}
	else {
		return partialSearch(queries);
	}
}

vector<InvertedIndex::Result> * InvertedIndex::exactSearch(set<string> queries)
{
	vector<InvertedIndex::Result> * results = new vector<InvertedIndex::Result>;
	static map<string, InvertedIndex::Result> * lookup = new map<string, InvertedIndex::Result>;
	for (string query : queries) {
		cout << query << endl;
		if (Map.contains(query)) {
			foundWord(results, lookup, queries, query);
		}
	}
	return results;
}

vector<InvertedIndex::Result> * InvertedIndex::partialSearch(set<string> queries)
{
	vector<InvertedIndex::Result> * results = new vector<InvertedIndex::Result>;
	map<string, InvertedIndex::Result> lookup;
	for (string query : queries) {
		// TODO
	}
	return results;
}

void InvertedIndex::merge(InvertedIndex* local)
{
	//TODO
}

void InvertedIndex::foundWord(vector<InvertedIndex::Result> * results, map<string, InvertedIndex::Result> * lookup, set<string> queries, string word)
{
	for (string path : InvertedIndex::getLocationsOfWord(word)) {
		if (!lookup->contains(path)) {
			InvertedIndex::Result * res = new InvertedIndex::Result(path, this);
			lookup->insert(pair<string, InvertedIndex::Result>(path, *res));
			results->push_back(*res);
		}
		lookup->at(path).update(word);
	}
}
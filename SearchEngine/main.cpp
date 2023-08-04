// SearchEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "ArgumentMap.h"
#include "InvertedIndex.h"
#include "IndexBuilder.h"
using namespace std;

int main(int argc, char** argv)
{
	// TODO add argument parsing, partial search not working
	// testing 
	vector<string> args;
	for (int i = 1; i < argc; i++)
	{
		args.push_back(argv[i]);
	}
	//ArgumentMap * ArgMap = new ArgumentMap(args);


	InvertedIndex * index = new InvertedIndex;
	// update dir string to path of folder with text to build index
	string dir = "/Users/dylan/projects/c++/test";
	IndexBuilder * builder = new IndexBuilder;
	builder->buildIndex(dir, index);
	set<string> queries = {"the"};
	vector<InvertedIndex::Result *> * results = index->search(queries, true);
	for (auto result : *results) {
		cout << "Location: " << result->getWhere() << " | Score: " << result->getScore() * 100 << "% | Count = " << result->getCount() << "\n";
	}
}



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
	for (size_t i = 1; i < argc; i++)
	{
		args.push_back(argv[i]);
	}
	ArgumentMap * ArgMap = new ArgumentMap(args);


	InvertedIndex * index = new InvertedIndex;
	string dir = "C:/Users/Dmayna/Desktop/test/";
	IndexBuilder * builder = new IndexBuilder;
	builder->buildIndex(dir, index);
	set<string> queries = { "a", "i" };
	vector<InvertedIndex::Result> * results = index->search(queries, true);
	for (auto result : *results) {
		cout << "Location: " << result.getWhere() << " | Score: " << result.getScore() * 100 << endl;
		printf("%1.2f\n", result.getScore());
	}
}



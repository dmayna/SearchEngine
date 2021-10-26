// SearchEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "InvertedIndex.h"
#include "IndexBuilder.h"
using namespace std;

int main()
{
	// TODO add argument parsing, partial search not working
	// testing 
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



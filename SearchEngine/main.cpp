// SearchEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "ArgumentMap.h"
#include "InvertedIndex.h"
#include "IndexBuilder.h"
#include "WebCrawler.h"

using namespace std;

int main(int argc, char** argv) {
	// TODO add argument parsing, partial search not working
	// testing 
	//vector<string> args;
	//for (int i = 1; i < argc; i++) {
		//args.push_back(argv[i]);
	//}
	//ArgumentMap * ArgMap = new ArgumentMap(args);


	InvertedIndex * index = new InvertedIndex;
	// update dir string to path of folder with text to build index
	string dir = "/Users/dylan/projects/c++/test";
	IndexBuilder * builder = new IndexBuilder;
	builder->buildIndex(dir, index);
	set<string> queries = {"the", "he"};
	vector<InvertedIndex::Result *> * results = index->search(queries, true);
	/*for (auto result : *results) {
		cout << "Query: " << result->getQuery() << "\n";
		cout << "Location: " << result->getWhere() << "\n";
		cout << "Word Count: " << index->getWordCount(result->getWhere()) << "\n";
		cout << "Score: " << result->getScore() * 100 << "%\n";
		cout << "Count = " << result->getCount() << "\n\n";
	}*/
	WebCrawler wc;
	//wc.addUrl("https://www.gutenberg.org/cache/epub/1513/pg1513.txt");
	wc.addUrl("https://example.com/");
	wc.crawl();

	return 0;
}
#include "IndexBuilder.h"
#include "TextFileFinder.h"
#include <filesystem>
#include <fstream>
#include <sstream>

using namespace std;
namespace fs = std::__fs::filesystem;

void IndexBuilder::buildIndex(string dir, InvertedIndex *index) {
	if (fs::is_regular_file(dir)) {
		parseFile(dir, index);
	}
	else {
		TextFileFinder tff;
		for (string p : tff.list(dir)) {
			parseFile(p, index);
		}
	}
}

/*void IndexBuilder::buildIndexWeb(string url, string webData, InvertedIndex *index) {
	int position = 1;
	istringstream iss(webData);
	do {
        string subs;
 
        // Get the word from the istringstream
        iss >> subs;
 
        // add the word fetched from
        // the istringstream to index
		index->add(subs, url, position);
        position++;
 
    } while (iss);
}*/

void IndexBuilder::parseFile(string file, InvertedIndex *index) {
	string word;
	int position = 1;
	
	ifstream readFile(file);
	while (readFile >> word) {
		string word_lower_case = "";
		for (size_t i = 0; i < word.length(); i++)
		{
			if (isalpha(word[i]))
			{
				word_lower_case+= tolower(word[i]);
			}
		}
		if (!word_lower_case.empty())
		{
			index->add(word_lower_case, file, position);
			//cout << "Added: [ " << word_lower_case << " ] from [ " << file << " ] at " << position << endl;
			position++;
		}
	}
}
#include "IndexBuilder.h"
#include "TextFileFinder.h"
#include <filesystem>
#include <fstream>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

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

void IndexBuilder::parseFile(string file, InvertedIndex *index) {
	string line;
	int position = 1;
	
	ifstream readFile(file);
	while (readFile >> line) {
		index->add(line, file, position);
		//cout << "Added: [ " << line << " ] from [ " << file << " ] at " << position << endl;
		position++;
	}
}
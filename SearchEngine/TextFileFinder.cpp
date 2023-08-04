#include "TextFileFinder.h"
#include <filesystem>


using namespace std;
namespace fs = std::__fs::filesystem;

bool TextFileFinder::isText(string inFile)
{
	if (fs::is_regular_file(inFile)) {
		for (unsigned int i = 0; i < inFile.size(); i++) {
			inFile[i] = tolower(inFile[i]);
		}
		return hasEnding(inFile, ".text") || hasEnding(inFile, ".txt");
	}
	return false;
}

bool TextFileFinder::hasEnding(string const& fullString, string const& ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}

vector<string> TextFileFinder::list(string start)
{
	vector<string> paths;
	for (const auto& p : fs::recursive_directory_iterator(start)) {
		paths.push_back(p.path().string());
	}
	return paths;
}

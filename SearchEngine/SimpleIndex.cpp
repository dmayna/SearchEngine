#include "SimpleIndex.h"

using namespace std;

void SimpleIndex::add(string location, vector<string> words)
{
	int i = 1;
	for (string word : words) {
		add(location, word, i);
		i += 1;
	}
}

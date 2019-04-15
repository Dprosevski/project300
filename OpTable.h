#ifndef OPTABLE_H
#define OPTABLE_H
#include <string>
#include <vector>

using namespace std;

class OpTable {
private:


public:
	OpTable();
	vector<string> mnem;
	vector<int> format;
	vector<string> op;
};
#endif
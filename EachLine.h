#ifndef EACHLINE_H
#define EACHLINE_H
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class EachLine {
private:


public:
	EachLine() {};
	string sym;
	string com;
	string var;
	string comment;
	string locCount;
	string mnem, op, objCode;
	int format;
};
#endif
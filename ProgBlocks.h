#ifndef PROGBLOCK_H
#define PROGBLOCK_H
#include <string>
#include <vector>

using namespace std;

class ProgBlock {
private:


public:
	ProgBlock() {};
	string name;
	int number;
	string address;
	string length;
	bool used = false;
};
#endif
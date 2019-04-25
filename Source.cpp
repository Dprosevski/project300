#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "EachLine.h"
#include "OpTable.h"
#include "SymTab.h"
//test
using namespace std;

string decToHex(int num);
string hexToBin(string hexString);
string binToHex(string binary);
string genObjectCode(string sym, string mnemonic, int form, string opcode, string variable, string loc, string nextLoc, string ta, string app, string nextMnemonic, string baseLoc, string baseV);
unsigned long  hexToDec(string hexString);

int main() {
	EachLine * line; //object for each line
	SymTab * symTab;
	OpTable opTab; //op table object
	vector<SymTab> symTabVec; //vector for each symbol
	vector<EachLine> lineObjects; //vector for each line
	ifstream inFile;
	string fileName = "Files\\functions.txt";
	string getLine;
	string word;
	string hex;
	string tempSymLoc, baseLoc, baseVar;
	int lineCount = 0;
	int tempInt;
	char temp;
	int col = 0;
	int stopW = 0;

	cout << "File name: " << fileName.substr(6, fileName.length()) << "\n\n";
	inFile.open(fileName);
	if (inFile.is_open()) {
		while (getline(inFile, getLine)) { //separate by new lines
			stringstream ss(getLine);
			col = 1;
			line = new EachLine;
			while (getline(ss, word, '\t')) { //separate lines by words
				temp = word[0]; //get the first char of the word
				tempInt = int(temp); //convert it to ASCII
				if (tempInt == 32) { //if space move to next word
					stopW = 1;
				}
				if (stopW == 1) {
					stopW = 0;
				}
				else {
					if (col == 1) {
						line->sym = word; //store the sym onto string
						cout << line->sym << "\t";
					}
					if (col == 2) {
						line->com = word; //store the command onto string
						cout << line->com << "\t";
					}
					if (col == 3) {
						line->var = word; //store the variable onto string
						cout << line->var << "\t";
					}
					if (col == 4) {
						line->comment = word; //store the comment onto string
						cout << line->comment << "\t";
					}
				}
				col++;
			}
			lineObjects.push_back(*line);
			cout << endl;
			lineCount++;
		}
	}

	int progStart = 0;
	stringstream ss(lineObjects[0].var); //get the starting loc from the first line
	ss >> progStart;
	int tempLength = 0;
	int count = 0;
	int i = progStart;
	int pass = 1;


	//Pass 1: find loc counter
	while (lineObjects[i].com != "END") {
		int k = 0;
		bool found = false;

		if (lineObjects[i].com == "START" || lineObjects[i].sym == ".") {
			found = true;
		}

		if (lineObjects[i].sym != "" && lineObjects[i].sym != ".") {
			symTab = new SymTab;
			symTab->locCount = lineObjects[i].locCount;
			symTab->symbol = lineObjects[i].sym;
			symTabVec.push_back(*symTab);
		}

		while (found == false && lineObjects[i].com != "") {
					   
			if (lineObjects[i].com == "BASE") {
				baseLoc = lineObjects[i - 1].locCount;
				baseVar = lineObjects[i].var;
				found == true;
			}
			if (lineObjects[i].com == opTab.mnem[k] || lineObjects[i].com == "+" + opTab.mnem[k]) {
				if (lineObjects[i].com == "RESW" || lineObjects[i].com == "RESB") {
					int memRes = 0;
					stringstream ss(lineObjects[i].var);
					ss >> memRes;
					count += (opTab.format[k] * memRes); //increase loc counter times memory reserved
					found = true;
				}

				else {
					if (lineObjects[i].com[0] == '+') {
						lineObjects[i].mnem = "+" + opTab.mnem[k]; //save menm code for the instruction format 4
						lineObjects[i].format = opTab.format[k] + 1; //save format 4 code for the instruction
						count += lineObjects[i].format; //increase loc counter
					}
					else {
						lineObjects[i].mnem = opTab.mnem[k]; //save menm code for the instruction format 3
						lineObjects[i].format = opTab.format[k]; //save format 3 code for the instruction
						count += lineObjects[i].format; //increase loc counter
					}
					lineObjects[i].op = opTab.op[k]; //save op code for the instruction
					found = true;
				}
			}
			k++;
		}

		if (lineObjects[i].var.length() != 0) {
			if (int(lineObjects[i].var[1]) == 39) {
				if (lineObjects[i].var[0] == 'C') {
					count += lineObjects[i].var.length() - 4; // - 4 because it ignores 3 characters C' ', 1 more since BYTE is 1 by default
				}
				if (lineObjects[i].var[0] == 'F') {
					count += (lineObjects[i].var.length() / 2) - 4; // - 4 because it ignores 3 characters C' ', 1 more since BYTE is 1 by default, /2 because hex
				}
			}
		}

		hex = decToHex(count);
		if (hex.length() < 4) { //if length of hex string is not 4 long add zeros to make it 4 long
			tempLength = 4 - hex.length();
			hex = string(tempLength, '0') + hex;
		}
		lineObjects[i + 1].locCount = hex;

		if (lineObjects[i + 1].locCount == lineObjects[i].locCount) { //if previous loc count is the same as current, make previous ""
			lineObjects[i].locCount = "";
		}
		if (lineObjects[i + 1].com == "END") { //make next location after end empty
			lineObjects[i + 1].locCount = "";
		}
		i++;
	}

	cout << "\n\n\nSYMTAB:\n";
	i = 0;
	while (i != (int)symTabVec.size()) {
		cout << left << symTabVec[i].symbol << "\t" << right << setfill('0') << setw(4) << symTabVec[i].locCount << endl;
		i++;
	}


	//Pass 2:
	for (int j = 0; j < (int)lineObjects.size() - 1; j++) {
		bool found = false;
		for (int s = 0; s < (int)symTabVec.size(); s++) {
			if (lineObjects[j].var.find(symTabVec[s].symbol) != std::string::npos) {
				tempSymLoc = symTabVec[s].locCount;
				found = true;
			}

			if (found == true) {
				if (symTabVec[0].appearance == "")
					symTabVec[0].appearance = lineObjects[j + 1].locCount;
				break;
			}
		}
		lineObjects[j].objCode = genObjectCode(lineObjects[j].sym, lineObjects[j].mnem, lineObjects[j].format, lineObjects[j].op, lineObjects[j].var, lineObjects[j].locCount, lineObjects[j + 1].locCount, tempSymLoc, symTabVec[0].appearance, lineObjects[j + 1].mnem, baseLoc, baseVar);
		tempSymLoc = "";
	}



	cout << "\n\n\n\nAfter assembler:\n\n";
	i = 0;
	while (i != lineCount) {
		if (lineObjects[i].locCount != "" || lineObjects[i].com == "START") {
			cout << right << lineObjects[i].locCount << "\t";
		}
		else {
			cout << "\t";
		}
		cout << i << "\t" << lineObjects[i].sym << "\t"
			<< lineObjects[i].com << "\t"
			<< setfill(' ') << setw(10) << lineObjects[i].var << "\t"
			<< left << setfill(' ') << setw(40) << lineObjects[i].comment << "\t"
			<< lineObjects[i].objCode << endl;
		i++;
	} //end of print


	/*
	string test1 = "ffffffff";
	cout << "Print here: " << hexToDec(test1);



	}*/


	cout << string(5, '\n'); //space 5 new lines for clarity
	inFile.close(); //close input file


	system("pause");
	return 0;
}




string genObjectCode(string sym, string mnem, int format, string op, string var, string locCount, string strNextLocCount, string strTa, string app, string nextMnem, string baseL, string baseV) {
	string  binString, hexString;
	int  intDisp, intTemp = 0;
	string n = "1", i = "1", x = "0", b = "0", p = "1", e = "0", disp, r1 = "0", r2 = "0";
	string A = "0", X = "1", L = "2", PC = "8", SW = "9", B = "3", S = "4", T = "5", F = "6";

	unsigned long TA = hexToDec(strTa);
	unsigned long BASE = hexToDec(baseL);
	unsigned long intLocCount = hexToDec(locCount);
	unsigned long intNextLocCount = hexToDec(strNextLocCount);


	if (format == 1) {
		if (var[0] == 'X' && int(var[1]) == 39) {
			hexString = var.substr(2, var.length() - 3);
		}
		else if (var[0] == 'C' && int(var[1]) == 39) {
			for (int i = 2; i < var.length() - 1; i++) {
				intTemp = int(var[i]);
				hexString += decToHex(intTemp);
			}
		}
		else {
			hexString = op;
		}
	}

	if (format == 2) {
		switch (var[0]) {
		case 'A': r1 = A;   break;
		case 'X': r1 = X; break;
		case 'L': r1 = L; break;
		case 'PC': r1 = PC; break;
		case 'SW': r1 = SW; break;
		case 'B': r1 = B; break;
		case 'S': r1 = S;   break;
		case 'T': r1 = T; ;    break;
		case 'F': r1 = F; break;
		default: r1 = "ERROR";
		}

		if (var.length() != 1) {
			switch (var[2]) {
			case 'A': r2 = A;   break;
			case 'X': r2 = X; break;
			case 'L': r2 = L; break;
			case 'PC': r2 = PC; break;
			case 'SW': r2 = SW; break;
			case 'B': r2 = B; break;
			case 'S': r2 = S;   break;
			case 'T': r2 = T; ;    break;
			case 'F': r2 = F; break;
			default: r2 = "ERROR";
			}
		}
		disp = r1 + r2;
		hexString = op + disp;
	}

	if (format == 3 || format == 4) {
		//n and i
		if (format == 4) {
			p = "0"; e = "1";
			disp = strTa;
			if (disp.length() < 5) {
				intTemp = 5 - disp.length();
				disp = string(intTemp, '0') + disp;
			}
		}
		if (var[0] == '#') {
			n = "0"; p = "0";
			if (var[1] > 48 && var[1] <= 57) { //check ascii to see if its a number
					disp = var.substr(1, var.length());
					stringstream ss(disp); //get the starting loc from the first line
					ss >> intTemp;
					disp = decToHex(intTemp);
					if (disp.length() < format && format == 3) {
						intTemp = format - disp.length();
						disp = string(intTemp, '0') + disp;
					}
					else if (format == 4) {
						if (disp.length() < format + 1) {
							intTemp = (format + 1) - disp.length();
							disp = string(intTemp, '0') + disp;
						}
					}
			}

			else {
				disp = decToHex(TA);
				if (nextMnem == "BASE") { //if case is base TA of base - next pc counter
					p = "1";
					intNextLocCount = intLocCount + format;
					disp = decToHex(TA - intNextLocCount);
				}

				if (disp.length() < 3) {
					intTemp = 3 - disp.length();
					disp = string(intTemp, '0') + disp;
				}
			}
		}
		else if (var[0] == '@') {
			disp = app.substr(1, app.length());
			i = "0";
		}
		else if (p == "1") {
			n = "1"; i = "1";
			intDisp = TA - intNextLocCount;
			disp = decToHex(intDisp);
			if (disp.length() < 3) {
				intTemp = 3 - disp.length();
				disp = string(intTemp, '0') + disp;
			}
			if (intDisp < 0) {
				if (mnem[0] == 'J') {
					int i = 0;
					//making absolute value, converting to binary and doing twos complement
					intTemp = abs(intDisp);
					disp = decToHex(intTemp);
					disp = hexToBin(disp);
					while (i < disp.length()) {
						if (disp[i] == '1') {
							disp[i] = '0';
						}
						else {
							disp[i] = '1';
						}
						i++;
					}
					for (i = disp.length() - 1; i >= 0; i--) {
						if (disp[i] == '1') {
							disp[i] = '0';
						}
						else {
							disp[i] = '1';
							break;
						}
					}
					disp = binToHex(disp);
					if (disp.length() < 3) {
						intTemp = 3 - disp.length();
						disp = string(intTemp, 'F') + disp;
					}
				}
				else if (var[0] == ' ') {
					//if end of subroutine go to start of it
				}
				else {
					p = "0"; b = "1";
					if (var == baseV) {
						disp = "000";
					}
					else {
						disp = decToHex(BASE);
					}
					if (disp.length() < 3) {
						intTemp = 3 - disp.length();
						disp = string(intTemp, '0') + disp;
					}
				}
			}
		}
		//x
		if (var.length() != 0) {
			if (var[0] == 'X' || var[var.length() - 1] == 'X') {
				x = "1";
			}
		}
		//exit
		if (sym == "EXIT") {
			disp = "000";
		}

		if (mnem == "RSUB") {
			b = "0";
			disp = "000";
		}

		if (op[0] != ' ') {
			binString = hexToBin(op).substr(0, 6); //convert to binary
		}

		binString += n + i + x + b + p + e;

		if (op[0] != ' ') {
			hexString = binToHex(binString) + disp; //convert to hex
		}
	}

	return hexString;
}


string decToHex(int num) {
	string hexaDec = "0123456789ABCDEF";
	string hex = "";

	while (num > 0) {
		hex = hexaDec[num % 16] + hex;
		num /= 16;
	}
	if (hex == "") {
		hex = "0";
	}
	return hex;
}

string hexToBin(string hexString) {
	int i = 0;
	string binary;

	while (hexString[i]) {
		switch (hexString[i]) {
		case '0': binary += "0000"; break;
		case '1': binary += "0001"; break;
		case '2': binary += "0010"; break;
		case '3': binary += "0011"; break;
		case '4': binary += "0100"; break;
		case '5': binary += "0101"; break;
		case '6': binary += "0110"; break;
		case '7': binary += "0111"; break;
		case '8': binary += "1000"; break;
		case '9': binary += "1001"; break;
		case 'A': binary += "1010"; break;
		case 'B': binary += "1011"; break;
		case 'C': binary += "1100"; break;
		case 'D': binary += "1101"; break;
		case 'E': binary += "1110"; break;
		case 'F': binary += "1111"; break;
		default: cout << "\nInvalid hexadecimal digit " << hexString[i];
		}
		i++;
	}
	return binary;
}


string binToHex(string binary) {
	int dec = 0, base = 1, tempLen = 0;
	string hexString;
	string binString = binary;

	for (int i = binString.length() - 1; i >= 0; i--) {
		if (binString[i] == '1') {
			dec += base;
		}
		base *= 2;
	}

	tempLen = binString.length() / 4; //to get length for Hex
	hexString = decToHex(dec);
	if (hexString.length() < tempLen) {
		hexString = "0" + hexString; //zero in the front get lost when converted to decimal (e.i. "04" becomes "4")
	}
	return hexString;
}

unsigned long hexToDec(string hexString) {
	char * theString;
	theString = new char[hexString.length() + 1];
	hexString.copy(theString, hexString.length() + 1);
	theString[hexString.length()] = '\0';
	unsigned long hex_value = strtoul(theString, 0, 16);
	delete[] theString;
	return hex_value;
}
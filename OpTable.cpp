#include "OpTable.h"

using namespace std;

OpTable::OpTable() {
	mnem.push_back("RESW");			format.push_back(3);		op.push_back(" ");
	mnem.push_back("RESB");			format.push_back(1);		op.push_back(" ");
	mnem.push_back("BASE");			format.push_back(NULL);		op.push_back(" ");
	mnem.push_back("BYTE");			format.push_back(1);		op.push_back(" ");
	mnem.push_back("EXTDEF");			format.push_back(NULL);		op.push_back(" "); //?
	mnem.push_back("EXTREF");			format.push_back(NULL);		op.push_back(" "); //?
	mnem.push_back("LTORG");			format.push_back(NULL);		op.push_back(" "); //?
	mnem.push_back("EQU");			format.push_back(NULL);		op.push_back(" "); //?
	mnem.push_back("CSECT");			format.push_back(NULL);		op.push_back(" "); //?
	mnem.push_back("WORD");			format.push_back(NULL);		op.push_back(" "); //?
	mnem.push_back("LDS");			format.push_back(3);		op.push_back("6C");
	mnem.push_back("LDT");			format.push_back(3);		op.push_back("74");
	mnem.push_back("LDX");			format.push_back(3);		op.push_back("04");
	mnem.push_back("LDA");			format.push_back(3);		op.push_back("00");
	mnem.push_back("ADD");			format.push_back(3);		op.push_back("18");
	mnem.push_back("STA");			format.push_back(3);		op.push_back("0C");
	mnem.push_back("ADDR");			format.push_back(2);		op.push_back("90");
	mnem.push_back("COMPR");		format.push_back(2);		op.push_back("A0");
	mnem.push_back("JLT");			format.push_back(3);		op.push_back("38");
	mnem.push_back("ADDF");			format.push_back(3);		op.push_back("58");
	mnem.push_back("AND");			format.push_back(3);		op.push_back("40");
	mnem.push_back("CLEAR");		format.push_back(2);		op.push_back("B4");
	mnem.push_back("COMP");			format.push_back(3);		op.push_back("28");
	mnem.push_back("COMPF");		format.push_back(3);		op.push_back("88");
	mnem.push_back("DIV");			format.push_back(3);		op.push_back("24");
	mnem.push_back("DIVF");			format.push_back(3);		op.push_back("64");
	mnem.push_back("DIVR");			format.push_back(2);		op.push_back("9C");
	mnem.push_back("FIX");			format.push_back(1);		op.push_back("C4");
	mnem.push_back("FLOAT");		format.push_back(1);		op.push_back("C0");
	mnem.push_back("HIO");			format.push_back(1);		op.push_back("F4");
	mnem.push_back("J");			format.push_back(3);		op.push_back("3C");
	mnem.push_back("JEQ");			format.push_back(3);		op.push_back("30");
	mnem.push_back("JGT");			format.push_back(3);		op.push_back("34");
	mnem.push_back("JSUB");			format.push_back(3);		op.push_back("48");
	mnem.push_back("LDB");			format.push_back(3);		op.push_back("68");
	mnem.push_back("LDCH");			format.push_back(3);		op.push_back("50");
	mnem.push_back("LDF");			format.push_back(3);		op.push_back("70");
	mnem.push_back("LDL");			format.push_back(3);		op.push_back("08");
	mnem.push_back("LPS");			format.push_back(3);		op.push_back("D0");
	mnem.push_back("MUL");			format.push_back(3);		op.push_back("20");
	mnem.push_back("MULF");			format.push_back(3);		op.push_back("60");
	mnem.push_back("MULR");			format.push_back(2);		op.push_back("98");
	mnem.push_back("NORM");			format.push_back(1);		op.push_back("C8");
	mnem.push_back("OR");			format.push_back(3);		op.push_back("44");
	mnem.push_back("RD");			format.push_back(3);		op.push_back("D8");
	mnem.push_back("RMO");			format.push_back(2);		op.push_back("AC");
	mnem.push_back("RSUB");			format.push_back(3);		op.push_back("4C");
	mnem.push_back("SHIFTL");		format.push_back(2);		op.push_back("A4");
	mnem.push_back("SHIFTR");		format.push_back(2);		op.push_back("A8");
	mnem.push_back("SIO");			format.push_back(1);		op.push_back("F0");
	mnem.push_back("SSK");			format.push_back(3);		op.push_back("EC");
	mnem.push_back("STB");			format.push_back(3);		op.push_back("78");
	mnem.push_back("STCH");			format.push_back(3);		op.push_back("54");
	mnem.push_back("STF");			format.push_back(3);		op.push_back("80");
	mnem.push_back("STI");			format.push_back(3);		op.push_back("D4");
	mnem.push_back("STL");			format.push_back(3);		op.push_back("14");
	mnem.push_back("STS");			format.push_back(3);		op.push_back("7C");
	mnem.push_back("STSW");			format.push_back(3);		op.push_back("E8");
	mnem.push_back("STT");			format.push_back(3);		op.push_back("84");
	mnem.push_back("STX");			format.push_back(3);		op.push_back("10");
	mnem.push_back("SUB");			format.push_back(3);		op.push_back("1C");
	mnem.push_back("SUBF");			format.push_back(3);		op.push_back("5C");
	mnem.push_back("SUBR");			format.push_back(2);		op.push_back("94");
	mnem.push_back("SVC");			format.push_back(2);		op.push_back("B0");
	mnem.push_back("TD");			format.push_back(3);		op.push_back("E0");
	mnem.push_back("TIO");			format.push_back(1);		op.push_back("F8");
	mnem.push_back("TIX");			format.push_back(3);		op.push_back("2C");
	mnem.push_back("TIXR");			format.push_back(2);		op.push_back("B8");
	mnem.push_back("WD");			format.push_back(3);		op.push_back("DC");
};
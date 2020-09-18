#include <iostream>
#include "output.hpp"
#include <sstream>

using namespace std;

void output::endScope(){
    cout << "---end scope---" << endl;
}

void output::printID(const string& id, int offset, const string& type) {
    cout << id << " " << type <<  " " << offset <<  endl;
}

string typeListToString(const std::vector<string>& argTypes) {
	stringstream res;
	res << "(";
	for(int i = 0; i < argTypes.size(); ++i) {
		res << argTypes[i];
		if (i + 1 < argTypes.size())
			res << ",";
	}
	res << ")";
	return res.str();
}

string typeAndNameListsToString(const std::vector<string>& memTypes, const std::vector<string>& memNames) {
	stringstream res;
	res << "{";
	for(int i = 0; i < memTypes.size(); ++i) {
		res << memTypes[i] << " " << memNames[i];;
		if (i + 1 < memTypes.size())
			res << ",";
	}
	res << "}";
	return res.str();
}

string output::makeFunctionType(const string& retType, std::vector<string>& argTypes)
{
	stringstream res;
	res << typeListToString(argTypes) << "->" << retType;
	return res.str();
}

void output::printStructType(const string& name, std::vector<string>& memTypes, std::vector<string>& memNames)
{
	cout << "struct " << name << " " << typeAndNameListsToString(memTypes, memNames) <<  endl;
}

void output::errorLex(int lineno){
    cout << "line " << lineno << ":" << " lexical error" << endl;
}

void output::errorSyn(int lineno){
    cout << "line " << lineno << ":" << " syntax error" << endl;
}

void output::errorUndef(int lineno, const string& id){
    cout << "line " << lineno << ":" << " variable " << id << " is not defined" << endl;
}

void output::errorDef(int lineno, const string& id){
    cout << "line " << lineno << ":" << " identifier " << id << " is already defined" << endl;
}

void output::errorUndefFunc(int lineno, const string& id) {
    cout << "line " << lineno << ":" << " function " << id << " is not defined" << endl;
}

void output::errorUndefStruct(int lineno, const string& id) {
    cout << "line " << lineno << ":" << " struct " << id << " is not defined" << endl;
}

void output::errorUndefStructMember(int lineno, const string& id) {
    cout << "line " << lineno << ":" << " struct member " << id << " is not defined" << endl;
}

void output::errorMismatch(int lineno){
    cout << "line " << lineno << ":" << " type mismatch" << endl;
}

void output::errorPrototypeMismatch(int lineno, const string& id, std::vector<string>& argTypes) {
    cout << "line " << lineno << ": prototype mismatch, function " << id << " expects arguments " << typeListToString(argTypes) << endl;
}
	
void output::errorUnexpectedBreak(int lineno) {
	cout << "line " << lineno << ":" << " unexpected break statement" << endl;	
}

void output::errorUnexpectedContinue(int lineno) {
	cout << "line " << lineno << ":" << " unexpected continue statement" << endl;	
}

void output::errorMainMissing() {
	cout << "Program has no 'void main()' function" << endl;
}

void output::errorByteTooLarge(int lineno, const string& value) {
	cout << "line " << lineno << ": byte value " << value << " out of range"<< endl;
} 

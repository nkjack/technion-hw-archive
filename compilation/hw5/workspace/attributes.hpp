#ifndef __ATTRIBUTES_H
#define __ATTRIBUTES_H

#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "output.hpp"

using namespace std;
using namespace output;

class Node {

    public:
        std::vector<string> types; // represent types
        std::vector<string> names; // represent names

        string value;
        int value_t;
        bool value_b;

        int line_num;
        string nonterminal;

        int reg;
		string quad;
		vector<int>* truelist;
		vector<int>* falselist;
		vector<int>* nextlist;
		vector<int>* breaklist;
		vector<int>* continuelist;

};


class RetType : public Node{
	public:
	RetType(char* yytext) {
		this->value = string(yytext);
		this->nonterminal = "RetType";
	}
};

class Type : public Node {
	public:
	Type(char* yytext) {

		this->value = yytext;
		this->nonterminal == "Type";
		this->types.push_back(this->value);
	}
};


class Bool : public Node {
	public:
	Bool(char* yytext, bool token_val) {
		this->value = yytext;
		this->value_b = token_val;
		this->types.push_back("BOOL");
		this->names.push_back("mock");
	}
};

class Rel : public Node {
	public:
	Rel(char* yytext) {
		this->value = yytext;
		this->nonterminal = "Rel";
	}
};

class Id : public Node {
	public:
	Id(char* yytext) {
		this->value = yytext;
		this->names.push_back(string(yytext));
	}
};

class String : public Node {
	public:
	String(char* yytext) {
		this->value = yytext;
		this->types.push_back("STRING");
		this->names.push_back("mock");
	}
};

class Num : public Node{
	public:
    Num(char* yytext) {
    	this->value_t = atoi(yytext);
    	this->value = yytext;
    	this->types.push_back("INT");
    	this->names.push_back("mock");
    }
};

class NumByte : public  Node {
	public:
	NumByte(string yytext, int yylineno) {
		this->value_t = atoi( yytext.c_str() );
		this->value = yytext;
		this->types.push_back("BYTE");
		this->names.push_back("mock");
		this->line_num = yylineno;
		if (this->value_t > 255 || this->value_t < 0) {
			errorByteTooLarge(yylineno, this->value);
			exit(1);
		}
	}
};

class Epsilon : public Node {
	public:
	Epsilon() {
		this->nonterminal = "epsilon";
	}
};



class BinOp : public Node {
	public:
	BinOp(Node* n1, Node* n2, string op, int yylineno){
		if ((n1->types.size() == 0) || (n2->types.size()==0)){
			errorMismatch(yylineno);
			exit(1);	
		}

		if (((n1->types[0] != "INT") && (n1->types[0] != "BYTE") ) || ((n2->types[0] != "INT")&&(n2->types[0] != "BYTE"))){
			errorMismatch(yylineno);
			exit(1);		
		}

		if (n1->types[0] == "INT" || n2->types[0] == "INT"){
			this->types.push_back("INT");
		}
		else{
			this->types.push_back("BYTE");	
		}
		
		this->names.push_back(op);
		this->nonterminal = "BinOp";
		this->line_num = yylineno;
	}
};



class BoolOp : public Node {
	public:
	BoolOp(Node* n1, Node* n2, string op ,int yylineno){
		if ((n1->types.size() == 0) || (n2->types.size()==0)){
			errorMismatch(yylineno);
			exit(1);	
		}
		if ((n1->types[0] == "BOOL") && (n2->types[0] == "BOOL")){
			this->types.push_back("BOOL");
			// this->value = n->value;
			// this->value_b = n->value_b;
			this->names.push_back(op);
			this->nonterminal = "BoolOp";
			this->line_num = yylineno;
		}
		else{
			errorMismatch(yylineno);
			exit(1);
		}
	}
};


class Relop : public Node {
	public:
	Relop(Node* n1, Node* n2, string op, int yylineno){
		if ((n1->types.size() == 0) || (n2->types.size()==0)){
			errorMismatch(yylineno);
			exit(1);	
		}

		this->types.push_back("BOOL");
		this->line_num = yylineno;
		this->nonterminal == "Relop";
		this->names.push_back(op);

		if (((n1->types[0] != "INT") && (n1->types[0] != "BYTE") ) || ((n2->types[0] != "INT")&&(n2->types[0] != "BYTE"))){
			errorMismatch(yylineno);
			exit(1);		
		}
	}
};



class Not : public Node {
	public:
	Not(Node* n, int yylineno){
		if (n->types[0] != "BOOL"){
			errorMismatch(yylineno);
			exit(1);
		}
		else{
			// this->value_b = !n->value_b;
			// this->value = n->value;
			this->types.push_back("BOOL");
			this->names.push_back("mock");
			this->line_num = yylineno;
		}
	}
};



#define YYSTYPE Node*

#endif
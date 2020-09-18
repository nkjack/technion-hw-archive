#ifndef __PARSER_H
#define __PARSER_H

#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include "SymbolTable.hpp"

using namespace std;
extern int yylineno; 

class Node{

    public:
        std::vector<Types> types; // represent types
        std::vector<string> names; // represent names

        string value;
        int value_t;
        bool value_b;

        string nonterminal;

};


// noam

class RetType : Node{
	RetType(char* yytext) : value(yytext), nonterminal("RetType") {
		// this->types[0] == this->value;
		// this->names.push_back("RetType");
	}
}
class Type : Node {
	Type(char* yytext) : value(yytext), nonterminal("Type"){
		// this->type[0] == this->value;
		// this->names.push_back("Type");
		if this->value == "BOOL"
			this->types.push_back(Types.BOOL);
		if this->value == "STRING"
			this->types.push_back(Types.STRING);
		if this->value == "INT"
			this->types.push_back(Types.INT);
		if this->value == "BYTE"
			this->types.push_back(Types.Byte);
	}
}

// class BoolOp : Node {
// 	BoolOp(char* yytext) : value(yytext), type("BoolOp"){
// }

class Bool : Node {
	Bool(char* yytext, bool token_val) : value(yytext),value_b(token_val){
		this->types.push_back(Types.BOOL);
		this->names.push_back("mock");
	}
}

class Rel : Node {
	Rel(char* yytext) : value(yytext), nonterminal("Rel"){
		// this->names.push_back("Rel");
	}
}

class Id : Node {
	Id(char* yytext) : value(yytext) {
		this->names.push_back(string(yytext));
		// name is Id?
	}
}

class String : Node {
	String(char* yytext) : value(yytext){
		this->types.push_back(Types.STRING);
		this->names.push_back("mock");
		// this->name[0] == "String";
	}
}

class Num : Node{
    Num(char* yytext) : value_t(atoi(yytext)), value(yytext) {
    	this->types.push_back(Types.INT);
    	this->names.push_back("mock");
    	// this->names[0] == "Num";
    }
};

class NumByte : Node {
	Num(string yytext) : value_t(atoi(yytext)),value(yytext) {
		this->types.push_back(Types.BYTE);
		this->names.push_back("mock");
		// this->name[0] == "NumByte";
		if {value_t > 255 || value_t < 0} {
			errorByteTooLarge(yylineno, value);
			exit(1);
		}
	}
}

class Epsilon : Node {
	Epsilon() : nonterminal("epsilon") {}
}

// class Exp : Node {
// 	Exp(Node* n, ){

// 	}
// }

class BinOp : Node {
	BinOp(Node* n_num, Node* b_binrest){
		if (n_num->types[0] == Types.INT || b_binrest->types[0] == Types.INT) {
			this->types.push_back(Types.INT);
		}
		else {
			this->types.push_back(Types.BYTE);
		}

		/*
		if (b_binrest->names[0] == "Plus"){
			this->value_t =  b_binrest->value_t + n_num->value_t;
			// this->value = str(this->value_t) need?
		}
		else if (b_binrest->names[0] == "Minus"){
			this->value_t =  b_binrest->value_t - n_num->value_t;
			// this->value = str(this->value_t) need?
		}
		else if (b_binrest->names[0] == "Mult"){
			this->value_t =  b_binrest->value_t * n_num->value_t;
			// this->value = str(this->value_t) need?
			if ((this->types[0] == "byte") && (this->value_t > 255 || this->value_t < 0)){
				errorByteTooLarge(yylineno, value);
				exit(1);
			}
		}
		else if (b_binrest->names[0] == "Div"){
			this->value_t = n_num->value_t / b_binrest->value_t ;
			// this->value = str(this->value_t) need?
		}
		*/

	}
}

class BinOpRest : Node {
	BinOpRest(Node* n, string op):{
		if (n->types[0] == Types.INT || n->types[0] == Types.BYTE) {
			this->types.push_back(n->type[0]);
			// this->value = n->value;
			// this->value_t = n->value_t;
			this->names.push_back(op);
			this->nonterminal = "BinOpRest";
		}
		else{
			errorMismatch(yylineno);
			exit(1);
		}
	}
}

class BoolOPRest : Node {
	BoolOPRest(Node* n, string op):{
		if (n->types[0] == Type.BOOl) {
			this->types.push_back(Types.BOOL);
			// this->value = n->value;
			// this->value_b = n->value_b;
			this->names.push_back(op);
			this->nonterminal = "BoolOpRest";
		}
		else{
			errorMismatch(yylineno);
			exit(1);
		}
	}
}
class Relop : Node {
	Relop(Node* n_num, Node* n_relrest){
		this->types.push_back(Types.Bool);
		if (n_relrest->nonterminal != "RelopRest"){
			errorMismatch(yylineno);
			exit(1);
		}
		/*
		if (n_relrest->names[0] == "<"){
			if (n_num->value_t < n_relrest->value_t){
				this->value_b = true;
				this->value = "true";
			}
			else{
				this->value_b = false;
				this->value = "false";	
			}
		}
		else if (n_relrest->names[0] == ">"){
			if (n_num->value_t > n_relrest->value_t){
				this->value_b = true;
				this->value = "true";
			}
			else{
				this->value_b = false;
				this->value = "false";	
			}
		}
		else if (n_relrest->names[0] == "<="){
			if (n_num->value_t <= n_relrest->value_t){
				this->value_b = true;
				this->value = "true";
			}
			else{
				this->value_b = false;
				this->value = "false";	
			}	
		}
		else if (n_relrest->names[0] == ">="){
			if (n_num->value_t >= n_relrest->value_t){
				this->value_b = true;
				this->value = "true";
			}
			else{
				this->value_b = false;
				this->value = "false";	
			}
		}
		else if (n_relrest->names[0] == "=="){
			if (n_num->value_t == n_relrest->value_t){
				this->value_b = true;
				this->value = "true";
			}
			else{
				this->value_b = false;
				this->value = "false";	
			}
		}
		else if (n_relrest->names[0] == "!="){
			if (n_num->value_t != n_relrest->value_t){
				this->value_b = true;
				this->value = "true";
			}
			else{
				this->value_b = false;
				this->value = "false";	
			}
		}
		else {
			//somthing wrong should not get here
		}
	}
	*/
}


class RelopRest : Node {
	RelopRest(Node* n_rel, Node* n_num):{
		if (n_num->types[0] == Types.INT || n_num->types[0] == Types.BYTE)  {
			// this->type = n_num->type;
			this->types.push_back(n_bum->types[0]);
			// this->value = n_num->value;
			// this->value_t = n_num->value_t;
			// this->names[0] = n_rel->value;
			this->nonterminal = "RelopRest";
		}
		else{
			errorMismatch(yylineno);
			exit(1);
		}
	}
}

class Not : Node {
	Not(Node* n){
		if (n->types[0] != Type.BOOL){
			errorMismatch(yylineno);
			exit(1);
		}
		else{
			// this->value_b = !n->value_b;
			// this->value = n->value;
			this->types.push_back(Types.BOOL);
			this->names.push_back("mock");
		}
	}
}


#define YYSTYPE Node*

#endif
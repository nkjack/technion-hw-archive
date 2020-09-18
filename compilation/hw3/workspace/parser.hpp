#ifndef __PARSER_H
#define __PARSER_H

#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

class Node{

    public:
        string type;

        int val_t;
        char val_byte;
        string val_str;
        char val_c;
        bool val_bool;
};

class BINOP : Node {
        
    public:
        exp1
        exp2




}


class Num : Node{
    Num(char* yytext) : val_t(atoi(yytext)), type("int") {}
};

class String : Node{
    String(char* yytext) : val_s(yytext), type("str") {}
};

class Int : Node{
    Int(char* yytext) : val_t(yytext), type("int") {}
};

class Byte : Node {
    Byte(char* yytext) : val_byte(atoi(yytext)), type("char"){}
};

class Bool : Node {

};
class Num_b : Node {

};



class program: Node {

};
class funcs: Node {

};
class funcdecl:Node {

};
class retype: Node {

};
class formals: Node {

};
class formalslist:Node {

};
class formaldecl:Node {

};
class preconditions:    Node{

};
class precondition: Node {

};
class statements: Node {

};
class statement: Node {

};
class open_statement: Node {

};
class closed_statement:Node {

};
class simple_statement: Node {

};
class call:Node {

};
class explist: Node {

};
class type: Node{

};
class exp: Node{

};

class ADD {

    Node arg1();
    Node arg2();

    int val;
}
























































#define YYSTYPE Node*




#endif
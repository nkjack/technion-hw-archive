#ifndef __HELPER_H
#define __HELPER_H

#include "parser.hpp"

void checkIfExpIsBool(Node* n, int yylineno){
	if (n->types.size() == 0){
		errorSyn(yylineno);
		exit(1);
	}

	if (n->types[0] != "bool"){
		errorSyn(yylineno);
		exit(1);
	}
}

#endif
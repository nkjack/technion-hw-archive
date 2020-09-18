%{
	#include "attributes.h"
	#include "truthval.tab.hpp"
%}

%option yylineno
%option noyywrap

%%

"true"	{ yylval.constVal = 1; return tkconst; }
"false"	{ yylval.constVal = 0; return tkconst; }
"and"	return tkand;
"or"	return tkor;
"("	return tklp;
")"	return tkrp;
[ \n\t]	;	// Whitespace

%%

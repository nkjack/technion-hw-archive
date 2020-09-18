%{
/* Declarations section */
#include "rana.hpp"
#include "parser.tab.hpp"
#include "output.hpp"
%}

%option yylineno
%option noyywrap
whitespace		([\t ])
%%
void {return VOID;}
int {return INT;}
byte {return BYTE;}
b return B;
bool {return BOOL;}
struct return STRUCT;
and return AND;
or return OR;
not return NOT;
true return TRUE;
false return FALSE;
(return) return RETURN;
if return IF;
else return ELSE;
while return WHILE;
break return BREAK;
continue return CONTINUE;
\; return SC;
\, return COMMA;
\. return PERIOD;
\( return LPAREN;
\) return RPAREN;
\{ return LBRACE;
\} return RBRACE;
\= return ASSIGN;
(\=\=|\!\=|\<|\>|\<\=|\>\=) {yylval.value = strdup(yytext); return RELOP;}
(\+|\-) {yylval.value = strdup(yytext);return PLUSMINUS;}
(\*|\/)  {yylval.value = strdup(yytext); return BINOP;}
[a-zA-Z][a-zA-Z0-9]* {yylval.type = strdup(yytext);return ID;}
0|[1-9][0-9]* {yylval.value = strdup(yytext); return NUM;} 
\"([^\n\r\"\\]|\\[rnt"\\])+\" {yylval.value = strdup(yytext); return STRING;}
(\/\/[^\r\n]*[\r|\n|\r\n]?) ;
{whitespace}+  ;
(\r)|(\n)      ; 
<<EOF>>  return EF;
.		output::errorLex(yylineno); exit(0);

%%
	
	

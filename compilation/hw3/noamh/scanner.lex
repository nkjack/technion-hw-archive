%{
#include "output.hpp"
#include "parser.tab.hpp"
void errorHandler();
%}

%option yylineno
%option noyywrap
whitespace ([\t\n\r ])

%%
void                            return VOID;
int                             return INT;
bool                            return BOOL;
and                             return AND;
or                              return OR;
not                             return NOT;
true                            return TRUE;
false                           return FALSE;
return                          return RETURN;
if                              return IF;
else                            return ELSE;
while                           return WHILE;
break                           return BREAKE;
continue                        return CONTINUE;
@pre                            return PRECOND;
;                               return SC;
,                               return COMMA;
\(                              return LPAREN;
\)                              return RPAREN;
\{                              return LBRACE;
\}                              return RBRACE;
\=                              return ASSIGN;
(\=\=|\!\=|\<|\>|\<\=|\>\=)     return RELOP;
[a-zA-Z][a-zA-Z0-9]*            return ID;
(0|[1-9][0-9]*)                 return NUM;
\"([^\n\r\"\\]|\\[rnt"\\])+\"   return STRING;
b                               return B;
\+|\-|\*|\/                     return BINOP;
(whitespace)+                   ;
\/\/[^\r\n]*[\r|\n|\r\n]?       ;
.                               errorHandler();
%%

void errorHandler()
{
    output::errorLex(yylineno);
    exit(0);
}

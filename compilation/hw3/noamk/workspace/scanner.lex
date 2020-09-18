%{
/* Declarations section */
#include <stdio.h>
#include <stdlib.h>

#include "parser.tab.hpp"

int comment_start_linenum;
%}

%option yylineno
%option noyywrap


%%
void	{yylval=new RetType(yytext);return VOID;} // {printf("%d %s %s\n", yylineno, "VOID", yytext);}
int 	{yylval=new Type(yytext) ;return INT;} // {printf("%d %s %s\n", yylineno, "INT", yytext);}
byte	{yylval=new Type(yytext);return BYTE;}// {printf("%d %s %s\n", yylineno, "BYTE", yytext);}
b 		{return B;}//{printf("%d %s %s\n", yylineno, "B", yytext);}
bool	{yylval=new Type(yytext);return BOOL;} //{printf("%d %s %s\n", yylineno, "BOOL", yytext);}
and		{return AND;} //{printf("%d %s %s\n", yylineno, "AND", yytext);}
or		{return OR;} //{printf("%d %s %s\n", yylineno, "OR", yytext);}
not		{return NOT;} // {printf("%d %s %s\n", yylineno, "NOT", yytext);}
true	{yylval = new Bool(yytext, true);return TRUE;} // {printf("%d %s %s\n", yylineno, "TRUE", yytext);}
false	{yylval = new Bool(yytext, false);return FALSE;} // {printf("%d %s %s\n", yylineno, "FALSE", yytext);}
return	{return RETURN;} // {printf("%d %s %s\n", yylineno, "RETURN", yytext);}
if 		{return IF;} //{printf("%d %s %s\n", yylineno, "IF", yytext);}
else	{return ELSE;} // {printf("%d %s %s\n", yylineno, "ELSE", yytext);}
while	{return WHILE;} // {printf("%d %s %s\n", yylineno, "WHILE", yytext);}
break		{return BREAK;} //{printf("%d %s %s\n", yylineno, "BREAK", yytext);}
continue 	{return CONTINUE;} // {printf("%d %s %s\n", yylineno, "CONTINUE", yytext);}
@pre  		{return PRECOND;} // {printf("%d %s %s\n", yylineno, "PRECOND", yytext);}
;			{return SC;} // {printf("%d %s %s\n", yylineno, "SC", yytext);}
,			{return COMMA;} // {printf("%d %s %s\n", yylineno, "COMMA", yytext);}
\(			{return LPAREN;} // {printf("%d %s %s\n", yylineno, "LPAREN", yytext);}
\)			{return RPAREN;} // {printf("%d %s %s\n", yylineno, "RPAREN", yytext);}
\{			{return LBRACE;} // {printf("%d %s %s\n", yylineno, "LBRACE", yytext);}
\}			{return RBRACE;} // {printf("%d %s %s\n", yylineno, "RBRACE", yytext);}
=			{return ASSIGN;} //{printf("%d %s %s\n", yylineno, "ASSIGN", yytext);}
==|\!=			{yylval= new Rel(yytext);return RELOP_EQ;}
\<|\>|\<=|\>= 	{yylval= new Rel(yytext)return RELOP;} // {printf("%d %s %s\n", yylineno, "RELOP", yytext);}
[\+]			{return PLUS;}
[\-]			{return MINUS;}
[\*]			{return MULT;} //{printf("%d %s %s\n", yylineno, "MULT", yytext);}
[\/]			{return DIV;} //{printf("%d %s %s\n", yylineno, "DIV", yytext);}
[a-zA-Z][a-zA-Z0-9]*		{yylval=new Id(yytext);return ID;} // {printf("%d %s %s\n", yylineno, "ID", yytext);}
0|[1-9][0-9]*				{yylval=new Num(yytext);return NUM;} // {printf("%d %s %s\n", yylineno, "NUM", yytext);}
\"([^\n\r\"\\]|\\[rnt"\\])+\"	{yylval=new String(yytext);return STRING;} // {printf("%d %s %s\n", yylineno, "STRING", yytext);} 
\/\/[^\r\n]*[\r|\n|\r\n]?		{} // {printf("%d %s %s\n", yylineno, "comment", yytext);}
([\t\n\r ])					{};
<<EOF>>                     {return EF;} // {printf("%d %s %s\n", yylineno, "EF", yytext);}
. 							errorLex(yylineno); // {printf("%d %s %s\n", yylineno, "UNRECOGNIZED_CHAR", yytext);}
%%

/* END of File*/
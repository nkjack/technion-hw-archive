%{
/* Declarations section */
#include "attributes.hpp"
#include "parser.tab.hpp"
#include <stdio.h>
#include <stdlib.h>

%}

%option yylineno
%option noyywrap


%%
void	{yylval=new RetType((char*)"VOID");return VOID;} 
int 	{yylval=new Type((char*)"INT") ;return INT;} 
byte	{yylval=new Type((char*)"BYTE");return BYTE;}
b 		{return B;}
bool	{yylval=new Type((char*)"BOOL");return BOOL;} 
and		{return AND;} 
or		{return OR;} 
not		{return NOT;} 
true	{yylval = new Bool(yytext, true);return TRUE;} 
false	{yylval = new Bool(yytext, false);return FALSE;} 
return	{return RETURN;} 
if 		{return IF;} 
else	{return ELSE;} 
while	{return WHILE;} 
break		{return BREAK;} 
continue 	{return CONTINUE;} 
@pre  		{return PRECOND;} 
;			{return SC;} 
,			{return COMMA;} 
\(			{return LPAREN;} 
\)			{return RPAREN;} 
\{			{return LBRACE;} 
\}			{return RBRACE;} 
=			{return ASSIGN;} 
==|\!=			{yylval= new Rel(yytext);return RELOP_EQ;}
\<|\>|\<=|\>= 	{yylval= new Rel(yytext);return RELOP;} 
[\+]			{return PLUS;}
[\-]			{return MINUS;}
[\*]			{return MULT;} 
[\/]			{return DIV;} 
[a-zA-Z][a-zA-Z0-9]*		{yylval=new Id(yytext);return ID;} 
0|[1-9][0-9]*				{yylval=new Num(yytext);return NUM;} 
\"([^\n\r\"\\]|\\[rnt"\\])+\"	{yylval=new String(yytext);return STRING;}
\/\/[^\r\n]*[\r|\n|\r\n]?		{} // {printf("%d %s %s\n", yylineno, "comment", yytext);}
([\t\n\r ])					{};
. 							{errorLex(yylineno); exit(1);} 
<<EOF>>						{return EF;}
%%

/* END of File*/
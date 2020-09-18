%{
/* Declarations section */
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    UNRECOGNIZED_CHAR,
    UNCLOSED_STRING,
    UNCLOSED_COMMENT,
    UNDEFINED_ESCAPE_SEQUENCE,
    BAD_RGB_PARAMS,
    NESTED_COMMENT,
} ErrorType;

void showToken(char * name);
void errorHandler(ErrorType err);
void handleString1();
void beginString1();
void endString1(char* name);
void handleString2();
void beginString2();
void endString2(char* name);
void handleSpecialChar1();
void finishComment();

void handleTab();
void handleR();
void handleNewLine();

void handleHex1();
void handleHex2();
void showRGB();
char* string_1;
char* string_2;

int comment_start_linenum;
%}

%option yylineno
%option noyywrap
digit ([0-9])
hex_digit ([0-9]|[a-fA-F])
letter ([a-zA-Z])
whitespace ([\t\n\r ])
left_comment (\/\*)
right_comment (\*\/)
valid_name_char ({letter}|[-_]|{digit})
rgb_element ({whitespace}*((\-)|(\+))?{digit}+{whitespace}*)
special_chars ((\\n)|(\\r)|(\\t)|(\\\\))
backslash (\\)
real_newline (\x0A|\x0D)
printable_char_for_tick_1 ((\\\\)|[\x20-\x26]|[\x28-\x5b]|[\x5d-\x7E])
tick_1 (\x27)
printable_char_for_tick_2 ((\\\\)|([\x20-\x21]|[\x23-\x5b]|[\x5d-\x7E]))
tick_2 (\x22)
printable_char (([\x09])|([\x0A])|([\x0D])|([\x20-\x7E])) 

%x STRING_1
%x STRING_2
%x HEX_COND_1
%x HEX_COND_2
%x BAD_STRING
%x COMMENT_COND
%x RGB_COND

%%
{left_comment}                                              {BEGIN(COMMENT_COND); comment_start_linenum = yylineno;}
<COMMENT_COND>{left_comment}                                errorHandler(NESTED_COMMENT);
<COMMENT_COND>{printable_char}			                    {};								
<COMMENT_COND>{right_comment}                               {BEGIN(INITIAL); finishComment();}
(({letter}|-{letter}){valid_name_char}*)			 			showToken("NAME");
#(({digit}|{letter}|-{letter}){valid_name_char}*)	 			showToken("HASHID");
@import 														showToken("IMPORT");
\!{whitespace}*[iI][mM][pP][oO][rR][tT][aA][nN][tT]				showToken("IMPORTANT");
{tick_1}													{ BEGIN(STRING_1); beginString1();}
<STRING_1>({printable_char_for_tick_1})* 	  				handleString1();
<STRING_1>(\\t)											handleTab();
<STRING_1>(\\r)											handleR();
<STRING_1>(\\n)											handleNewLine();
<STRING_1>{real_newline}									errorHandler(UNCLOSED_STRING);
<STRING_1>{backslash}										BEGIN(HEX_COND_1);
<HEX_COND_1>({hex_digit}){1,6}								{handleHex1();BEGIN(STRING_1);}
<HEX_COND_1>.												errorHandler(UNDEFINED_ESCAPE_SEQUENCE);
<STRING_1>{tick_1}											{endString1("STRING"); BEGIN(INITIAL);}
{tick_2}														{BEGIN(STRING_2); beginString2();}
<STRING_2>({printable_char_for_tick_2}|{special_chars})* 	handleString2();
<STRING_2>{real_newline}									errorHandler(UNCLOSED_STRING);
<STRING_2>{backslash}										BEGIN(HEX_COND_2);
<HEX_COND_2>({hex_digit}){1,6}								{handleHex2();BEGIN(STRING_2);}
<HEX_COND_2>.												errorHandler(UNDEFINED_ESCAPE_SEQUENCE);
<STRING_2>{tick_2}											{endString2("STRING"); BEGIN(INITIAL);}
[\>\+\~]														showToken("COMB");
:																showToken("COLON");
;																showToken("SEMICOLON");
\{															showToken("LBRACE");
\}																showToken("RBRACE");
\[																showToken("LBRACKET");
\]																showToken("RBRACKET");
=																showToken("EQUAL");
\*																showToken("ASTERISK");
\.																showToken("DOT");
((\-)|(\+))?((0x({hex_digit})+)|({digit})+)						showToken("NUMBER");
{digit}*(\.)?{digit}+(%|[a-z]+)									showToken("UNIT");
rgb\(                                                       BEGIN(RGB_COND);
<RGB_COND>{rgb_element}\,{rgb_element}\,{rgb_element}\)     {BEGIN(INITIAL); showRGB();}
<RGB_COND>.                                                 errorHandler(BAD_RGB_PARAMS);
{whitespace}													{};
. 																errorHandler(UNRECOGNIZED_CHAR);
%%


void errorHandler(ErrorType err){
    switch(err)
    {
        case UNRECOGNIZED_CHAR:
            printf("Error %s\n", yytext);
            exit(0);

        case UNCLOSED_STRING:
            printf("Error unclosed string\n");
            exit(0);

        case UNCLOSED_COMMENT:
            printf("Error unclosed comment\n");
            exit(0);

        case UNDEFINED_ESCAPE_SEQUENCE:
            printf("Error undefined escape sequence %s\n", yytext);
            exit(0);

        case BAD_RGB_PARAMS:
            printf("Error in rgb parameters\n");
            exit(0);

        case NESTED_COMMENT:
            printf("Warning nested comment\n");
            exit(0);

        default:
            printf("Unrecognized Error\n");
            exit(0);

    }
}

void showToken(char * name){
	printf("%d %s %s\n", yylineno, name, yytext);
}

void showRGB(){
	printf("%d RGB rgb(%s\n", yylineno, yytext);
}

void handleString1(){
	strcat(string_1, yytext);
}

void handleString2(){
	strcat(string_2, yytext);
}

void beginString1(){
	if (!string_1){
		free(string_1);
	}
	string_1 = malloc(1024);
}

void beginString2(){
	if (!string_2){
		free(string_2);
	}
	string_2 = malloc(1024);
}

void endString1(char* name){
	printf("%d %s %s\n", yylineno, name, string_1);

	if (!string_1){
		free(string_1);
	}
}

void endString2(char* name){
	printf("%d %s %s\n", yylineno, name, string_2);

	if (!string_2){
		free(string_2);
	}
}

void handleHex1(){
	// strcat(string_1, yytext);
	// int num = atoi(yytext);
	int bottom = (int)strtol("20", NULL, 16);
	int top = (int)strtol("7E", NULL, 16);
	int hex_tab = (int)strtol("09", NULL, 16);
	int hex_LF = (int)strtol("0A", NULL, 16);
	int hex_CR = (int)strtol("0D", NULL, 16);

	int num = (int)strtol(yytext, NULL, 16);
	if ((num <= top  && num >= bottom) || (num == hex_tab)|| (num == hex_CR)|| (num == hex_LF)){
		char c = (char)num;
		char output_c[1];
		output_c[0] = c;
		strcat(string_1, output_c);
	}
}

void handleHex2(){
	strcat(string_2, "\\");
	strcat(string_2, yytext);
}

void handleTab(){
	strcat(string_1,"\t");
}
void handleR(){
	strcat(string_1,"\r");
}
void handleNewLine(){
	strcat(string_1,"\n");
}

void finishComment(){
	printf("%d COMMENT %d\n", comment_start_linenum, yylineno - comment_start_linenum + 1);
}
/* END of File*/
// <COMMENT_COND>(\*([^\/])|(\/[^*])|[^*])*                    {};								
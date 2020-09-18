%{
/* Declarations section */
#include <stdio.h>
void showToken(char * name);
typdef enum {
    UNRECOGNIZED_CHAR,
    UNCLOSED_STRING,
    UNCLOSED_COMMENT,
    UNDEFINED_ESCAPE_SEQUENCE,
    BAD_RGB_PARAMS,
    NESTED_COMMENT,
} ErrorType
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

%x COMMENT_COND
%x BAD_COMMENT

%%
{left_comment}                                              BEGIN(COMMENT_COND);
<COMMENT_COND>{new_line}                                    count_new_line();
<COMMENT_COND>{left_comment}                                errorHandler(NESTED_COMMENT);
<COMMENT_COND>(\*([^\/])|(\\[^*])|[^*])*                    {};
<COMMENT_COND>{right_comment}                               {BEGIN(INITIAL); showToken("COMMENT");}
(({letter}|-{letter}){valid_name_char}*)			 		showToken("NAME");
#(({digit}|{letter}|-{letter}){valid_name_char}*)	 		showToken("HASHID");
@import 													showToken("IMPORT");
                                                            showToken("STRING")
\!{whitespace}*[iI][mM][pP][oO][rR][tT][aA][nN][tT]			showToken("IMPORTANT");
[\>\+\~]													showToken("COMB");
:															showToken("COLON");
;															showToken("SEMICOLON");
\{															showToken("LBRACE");
\}															showToken("RBRACE");
\[															showToken("LBRACKET");
\]															showToken("RBRACKET");
=															showToken("EQUAL");
\*															showToken("ASTERISK");
\.															showToken("DOT");
((\-)|(\+))?((0x({hex_digit})+)|({digit})+)					showToken("NUMBER");
{digit}*(\.)?{digit}+(%|[a-z]+)								showToken("UNIT");
rgb\({rgb_element}\,{rgb_element}\,{rgb_element}\)			showToken("RGB");
. 															errorHandler(UNRECOGNIZED_CHAR);
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
            printf("Unrecognized Error\n")
            exit(0);

    }
}

void showToken(char * name){
	printf("%d %s %s\n", yylineno, name, yytext);
}
/* END of File*/




{left_comment}(\*([^\/])|(\\[^*])|[^*])*{right_comment}         showToken("comment");
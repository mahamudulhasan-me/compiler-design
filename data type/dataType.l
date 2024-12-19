%{
#include <stdio.h>
%}

%option noyywrap

%%
0[xX][0-9a-fA-F]+ { printf("HEXADECIMAL: %s\n", yytext); }
[+-]?[0-9]*\.[0-9]+([eE][+-]?[0-9]+)? { printf("FLOATING-POINT: %s\n", yytext); }
[+-]?[0-9]+ { printf("INTEGER: %s\n", yytext); }
[ \t\n]+ ;  // Ignore spaces, tabs, and newlines
. { printf("UNKNOWN: %s\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}

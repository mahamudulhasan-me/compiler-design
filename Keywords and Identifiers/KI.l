%{
#include <stdio.h>
%}

%%

"int"|"float"|"if"|"else"|"while"|"return" { printf("KEYWORD: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("IDENTIFIER: %s\n", yytext); }
[ \t]+ ;  // Ignore spaces and tabs
\n ;      // Ignore newlines
. { printf("UNKNOWN: %s\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

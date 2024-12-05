%{
#include <stdio.h>
%}

%%
[0-9]+                      { printf("Integer: %s\n", yytext); }
[0-9]+\.[0-9]+              { printf("Floating-point: %s\n", yytext); }
[0-9]+[eE][-+]?[0-9]+       { printf("Scientific notation: %s\n", yytext); }
.                           { printf("Unrecognized character: %s\n", yytext); }
\n                          { /* Ignore newlines */ }
%%

int main() {
    printf("Enter a string of numbers (Ctrl+D to end):\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

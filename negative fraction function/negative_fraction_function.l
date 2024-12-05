%{
#include <stdio.h>
%}

%%
-[0-9]+/[0-9]+               { printf("Negative fraction: %s\n", yytext); }
-[0-9]+                      { printf("Negative integer: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*\([^)]*\) { printf("Function: %s\n", yytext); }
[ \t\n]+                     { /* Ignore whitespace */ }
.                            { printf("Unrecognized input: %s\n", yytext); }
%%

int main() {
    printf("Enter expressions (Ctrl+D to end):\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

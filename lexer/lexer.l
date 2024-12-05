%{
#include <stdio.h>
#include <string.h>
#undef yywrap
%}

%option noyywrap

%%
"if"|"else"|"while"|"return"          { printf("Keyword: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*                { printf("Identifier: %s\n", yytext); }
[0-9]+\.[0-9]+|[0-9]+                 { printf("Number: %s\n", yytext); }
"+"|"-"|"*"|"/"|"="                   { printf("Operator: %s\n", yytext); }
"("|")"                               { printf("Parenthesis: %s\n", yytext); }
[ \t\n]+                              { /* Ignore whitespace */ }
.                                     { printf("Unrecognized character: %s\n", yytext); }
%%

int main() {
    printf("Enter code (Ctrl+D to end):\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

%{
#include <stdio.h>
%}

%option noyywrap

%%
"if"|"else"|"while"|"return" { printf("KEYWORD: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("IDENTIFIER: %s\n", yytext); }
'\\'' { printf("CHARACTER: %s\n", yytext); }
[a-zA-Z]+ { printf("WORD: %s\n", yytext); }
[ \t]+ { printf("SPACE\n"); }
\n { printf("NEWLINE\n"); }
"+"|"-"|"*"|"/" { printf("OPERATOR: %s\n", yytext); }
"//".* { printf("COMMENT: %s\n", yytext); }
. { printf("UNKNOWN: %s\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}

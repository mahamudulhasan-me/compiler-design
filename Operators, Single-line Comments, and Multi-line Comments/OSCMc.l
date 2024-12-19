%{
#include <stdio.h>
%}

%option noyywrap

%%
"+"|"-"|"*"|"/"|"%"|"=" { printf("OPERATOR: %s\n", yytext); }
"//".*                  { printf("SINGLE-LINE COMMENT: %s\n", yytext); }
"/*"[^*]*"*"*([^*/][^*]*"*"*)*"*/" { printf("MULTI-LINE COMMENT: %s\n", yytext); }
[ \t\n]+                ;  // Ignore spaces, tabs, and newlines
.                       { printf("UNKNOWN: %s\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}

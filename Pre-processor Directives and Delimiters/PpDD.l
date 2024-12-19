%{
#include <stdio.h>
%}

%option noyywrap

%%
"#".* { printf("PREPROCESSOR DIRECTIVE: %s\n", yytext); }
"{"|"}"|"("|")"|"["|"]"|";"|","|":" { printf("DELIMITER: %s\n", yytext); }
[ \t\n]+ ;  // Ignore spaces, tabs, and newlines
. { printf("UNKNOWN: %s\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}

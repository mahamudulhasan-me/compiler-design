%{
#include <stdio.h>
int characters = 0, words = 0, spaces = 0, newlines = 0;
%}

%option noyywrap

%%
[a-zA-Z0-9]+   { words++; characters += yyleng; }
" "            { spaces++; characters++; }
\n             { newlines++; characters++; }
.              { characters++; }
%%

int main() {
    yylex();
    printf("Words: %d\nSpaces: %d\nCharacters: %d\nNewlines: %d\n", words, spaces, characters, newlines);
    return 0;
}

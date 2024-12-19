#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SYMBOLS 256

char grammar[MAX_SYMBOLS][MAX_SYMBOLS]; // Grammar rules
int num_rules;
char first[MAX_SYMBOLS][MAX_SYMBOLS]; // FIRST sets
char follow[MAX_SYMBOLS][MAX_SYMBOLS]; // FOLLOW sets
char non_terminals[MAX_SYMBOLS]; // List of non-terminals
int num_non_terminals;

void compute_first();
void compute_follow();
void add_to_set(char set[MAX_SYMBOLS][MAX_SYMBOLS], char symbol, char terminal);
void print_set(char set[MAX_SYMBOLS][MAX_SYMBOLS], char non_terminals[MAX_SYMBOLS], int num);

int main() {
    // Input grammar
    printf("Enter the number of grammar rules: ");
    scanf("%d", &num_rules);
    getchar(); // Clear newline character

    printf("Enter the grammar rules (e.g., S->AB|b):\n");
    for (int i = 0; i < num_rules; i++) {
        fgets(grammar[i], MAX_SYMBOLS, stdin);
        grammar[i][strcspn(grammar[i], "\n")] = '\0'; // Remove newline character
    }

    // List of non-terminals
    num_non_terminals = 0;
    for (int i = 0; i < num_rules; i++) {
        if (!strchr(non_terminals, grammar[i][0])) {
            non_terminals[num_non_terminals++] = grammar[i][0];
        }
    }

    // Compute FIRST and FOLLOW sets
    compute_first();
    compute_follow();

    // Print FIRST sets
    printf("\nFIRST sets:\n");
    print_set(first, non_terminals, num_non_terminals);

    // Print FOLLOW sets
    printf("\nFOLLOW sets:\n");
    print_set(follow, non_terminals, num_non_terminals);

    return 0;
}

void compute_first() {
    // Initialize FIRST sets
    for (int i = 0; i < num_non_terminals; i++) {
        first[non_terminals[i]][0] = '\0';
    }

    // Compute FIRST sets
    int changes;
    do {
        changes = 0;
        for (int i = 0; i < num_rules; i++) {
            char non_terminal = grammar[i][0];
            char *production = grammar[i] + 3; // Skip "A->"

            // Add terminals directly to FIRST set
            if (islower(production[0]) || isdigit(production[0]) || production[0] == '$') {
                if (!strchr(first[non_terminal], production[0])) {
                    add_to_set(first, non_terminal, production[0]);
                    changes = 1;
                }
            } else {
                // Add FIRST set of the non-terminal
                for (int j = 0; j < strlen(production); j++) {
                    char symbol = production[j];
                    if (isupper(symbol)) {
                        for (int k = 0; k < strlen(first[symbol]); k++) {
                            if (!strchr(first[non_terminal], first[symbol][k])) {
                                add_to_set(first, non_terminal, first[symbol][k]);
                                changes = 1;
                            }
                        }
                        if (strchr(first[symbol], '$')) {
                            continue;
                        }
                    }
                    break;
                }
            }
        }
    } while (changes);
}

void compute_follow() {
    // Initialize FOLLOW sets
    for (int i = 0; i < num_non_terminals; i++) {
        follow[non_terminals[i]][0] = '\0';
    }
    follow[non_terminals[0]][0] = '$'; // Add end-of-input marker to FOLLOW set of start symbol

    // Compute FOLLOW sets
    int changes;
    do {
        changes = 0;
        for (int i = 0; i < num_rules; i++) {
            char non_terminal = grammar[i][0];
            char *production = grammar[i] + 3; // Skip "A->"

            for (int j = 0; j < strlen(production); j++) {
                if (isupper(production[j])) {
                    char symbol = production[j];
                    if (j < strlen(production) - 1) {
                        char next_symbol = production[j + 1];
                        if (islower(next_symbol) || isdigit(next_symbol)) {
                            if (!strchr(follow[symbol], next_symbol)) {
                                add_to_set(follow, symbol, next_symbol);
                                changes = 1;
                            }
                        } else if (isupper(next_symbol)) {
                            for (int k = 0; k < strlen(first[next_symbol]); k++) {
                                if (first[next_symbol][k] != '$' && !strchr(follow[symbol], first[next_symbol][k])) {
                                    add_to_set(follow, symbol, first[next_symbol][k]);
                                    changes = 1;
                                }
                            }
                            if (strchr(first[next_symbol], '$')) {
                                for (int k = 0; k < strlen(follow[non_terminal]); k++) {
                                    if (!strchr(follow[symbol], follow[non_terminal][k])) {
                                        add_to_set(follow, symbol, follow[non_terminal][k]);
                                        changes = 1;
                                    }
                                }
                            }
                        }
                    } else {
                        for (int k = 0; k < strlen(follow[non_terminal]); k++) {
                            if (!strchr(follow[symbol], follow[non_terminal][k])) {
                                add_to_set(follow, symbol, follow[non_terminal][k]);
                                changes = 1;
                            }
                        }
                    }
                }
            }
        }
    } while (changes);
}

void add_to_set(char set[MAX_SYMBOLS][MAX_SYMBOLS], char symbol, char terminal) {
    int len = strlen(set[symbol]);
    set[symbol][len] = terminal;
    set[symbol][len + 1] = '\0';
}

void print_set(char set[MAX_SYMBOLS][MAX_SYMBOLS], char non_terminals[MAX_SYMBOLS], int num) {
    for (int i = 0; i < num; i++) {
        printf("%c: { ", non_terminals[i]);
        for (int j = 0; j < strlen(set[non_terminals[i]]); j++) {
            printf("%c ", set[non_terminals[i]][j]);
        }
        printf("}\n");
    }
}

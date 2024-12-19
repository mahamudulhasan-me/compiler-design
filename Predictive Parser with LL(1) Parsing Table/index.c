#include <stdio.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_LENGTH 100
#define MAX_NON_TERMINALS 10
#define MAX_TERMINALS 10

typedef struct {
    char non_terminal;                          // Non-terminal symbol
    char productions[MAX_RULES][MAX_LENGTH];   // Productions for the non-terminal
    int prod_count;                            // Number of productions
} GrammarRule;

// Global Parsing Table
char parse_table[MAX_NON_TERMINALS][MAX_TERMINALS][MAX_LENGTH];

// Global Terminal and Non-Terminal Lists
char terminals[MAX_TERMINALS];
char non_terminals[MAX_NON_TERMINALS];
int terminal_count = 0, non_terminal_count = 0;

// Function to check if a character is a terminal
int is_terminal(char c) {
    return (c >= 'a' && c <= 'z') || c == '+' || c == '*' || c == '(' || c == ')' || c == '$';
}

// Function to check if a character is a non-terminal
int is_non_terminal(char c) {
    return (c >= 'A' && c <= 'Z');
}

// Add terminal to the list (if not already present)
void add_terminal(char terminal) {
    for (int i = 0; i < terminal_count; i++) {
        if (terminals[i] == terminal) return;
    }
    terminals[terminal_count++] = terminal;
}

// Add non-terminal to the list (if not already present)
void add_non_terminal(char non_terminal) {
    for (int i = 0; i < non_terminal_count; i++) {
        if (non_terminals[i] == non_terminal) return;
    }
    non_terminals[non_terminal_count++] = non_terminal;
}

// Function to add a production to the parsing table
void add_to_table(char non_terminal, char terminal, const char* production) {
    int non_terminal_index = non_terminal - 'A';
    int terminal_index = strchr(terminals, terminal) - terminals;

    strcpy(parse_table[non_terminal_index][terminal_index], production);
}

// Function to compute FIRST sets and populate parsing table
void compute_first_and_table(GrammarRule* rules, int num_rules) {
    for (int i = 0; i < num_rules; i++) {
        GrammarRule* rule = &rules[i];
        for (int j = 0; j < rule->prod_count; j++) {
            char* production = rule->productions[j];
            char first_symbol = production[0];

            if (is_terminal(first_symbol)) {
                add_terminal(first_symbol);
                add_to_table(rule->non_terminal, first_symbol, production);
            } else if (is_non_terminal(first_symbol)) {
                add_non_terminal(first_symbol);
                // Assuming recursive call or manual computation for simplicity
                for (int k = 0; k < rules[i].prod_count; k++) {
                    char sub_first = rules[i].productions[k][0];
                    if (is_terminal(sub_first)) {
                        add_to_table(rule->non_terminal, sub_first, rules[i].productions[k]);
                    }
                }
            }
        }
    }
}

// Function to predict a production based on the parsing table
int predict(char non_terminal, char terminal) {
    int non_terminal_index = non_terminal - 'A';
    int terminal_index = strchr(terminals, terminal) - terminals;

    return strlen(parse_table[non_terminal_index][terminal_index]) > 0;
}

int main() {
    GrammarRule rules[MAX_NON_TERMINALS];
    int num_rules;

    // Input Grammar Rules
    printf("Enter the number of grammar rules: ");
    scanf("%d", &num_rules);

    for (int i = 0; i < num_rules; i++) {
        GrammarRule* rule = &rules[i];
        rule->prod_count = 0;

        printf("Enter the non-terminal for rule %d: ", i + 1);
        scanf(" %c", &rule->non_terminal);
        add_non_terminal(rule->non_terminal);

        int num_productions;
        printf("Enter the number of productions for %c: ", rule->non_terminal);
        scanf("%d", &num_productions);

        printf("Enter the productions for %c (one per line):\n", rule->non_terminal);
        for (int j = 0; j < num_productions; j++) {
            scanf("%s", rule->productions[rule->prod_count++]);
        }
    }

    // Initialize Parsing Table
    memset(parse_table, 0, sizeof(parse_table));
    compute_first_and_table(rules, num_rules);

    // Input String to Parse
    char input[MAX_LENGTH];
    printf("\nEnter the input string to parse (end with $): ");
    scanf("%s", input);

    // Parsing Stack
    char stack[MAX_LENGTH];
    int top = 0;
    stack[top++] = '$';
    stack[top++] = rules[0].non_terminal;  // Start symbol

    printf("\nParsing the input string...\n");
    int i = 0;
    while (stack[top - 1] != '$') {
        char stack_top = stack[top - 1];
        char current_input = input[i];

        if (stack_top == current_input) {
            printf("Match: %c\n", stack_top);
            top--;
            i++;
        } else if (is_non_terminal(stack_top)) {
            if (predict(stack_top, current_input)) {
                printf("Apply production: %s\n", parse_table[stack_top - 'A'][current_input - 'a']);
                top--;  // Pop non-terminal
            } else {
                printf("Error: No valid production for %c -> %c\n", stack_top, current_input);
                break;
            }
        } else {
            printf("Error: Unexpected symbol %c\n", current_input);
            break;
        }
    }

    if (stack[top - 1] == '$' && input[i] == '\0') {
        printf("Parsing Successful.\n");
    } else {
        printf("Parsing Failed.\n");
    }

    return 0;
}

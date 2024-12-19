#include <stdio.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_LENGTH 100
#define MAX_NON_TERMINALS 10

// Structure to store grammar rules for each non-terminal
typedef struct {
    char non_terminal;  // Non-terminal symbol
    char alpha[MAX_RULES][MAX_LENGTH];  // Left-recursive productions (A -> Aα)
    char beta[MAX_RULES][MAX_LENGTH];   // Non-recursive productions (A -> β)
    int alpha_count;  // Count of left-recursive productions
    int beta_count;   // Count of non-recursive productions
} GrammarRule;

// Function to remove left recursion from a single grammar rule
void remove_left_recursion(GrammarRule* rule) {
    // If there are no left-recursive productions, simply print the original rule
    if (rule->alpha_count == 0) {
        printf("%c -> ", rule->non_terminal);
        for (int i = 0; i < rule->beta_count; i++) {
            printf("%s", rule->beta[i]);
            if (i < rule->beta_count - 1) printf(" | ");
        }
        printf("\n");
        return;
    }

    // New non-terminal to handle left-recursive cases
    char new_non_terminal = rule->non_terminal + '\'';  // A' for non-terminal A

    // Print transformed rule for the original non-terminal without left recursion
    printf("%c -> ", rule->non_terminal);
    for (int i = 0; i < rule->beta_count; i++) {
        printf("%s%c", rule->beta[i], new_non_terminal);
        if (i < rule->beta_count - 1) printf(" | ");
    }
    printf("\n");

    // Print new rule for handling left-recursive productions
    printf("%c -> ", new_non_terminal);
    for (int i = 0; i < rule->alpha_count; i++) {
        printf("%s%c", rule->alpha[i], new_non_terminal);
        if (i < rule->alpha_count - 1) printf(" | ");
    }
    printf(" | epsilon\n"); // Use "epsilon" for the empty production
}

int main() {
    GrammarRule rules[MAX_NON_TERMINALS];  // Array to store rules for multiple non-terminals
    int num_non_terminals;

    // Input: number of non-terminals
    printf("Enter the number of non-terminals: ");
    scanf("%d", &num_non_terminals);

    // Input rules for each non-terminal
    for (int r = 0; r < num_non_terminals; r++) {
        GrammarRule* rule = &rules[r];
        rule->alpha_count = 0;
        rule->beta_count = 0;

        printf("\nEnter the non-terminal %d (single character): ", r + 1);
        scanf(" %c", &rule->non_terminal);

        int n;
        printf("Enter the number of productions for %c: ", rule->non_terminal);
        scanf("%d", &n);

        printf("Enter the productions for %c (one per line):\n", rule->non_terminal);

        // Input each production and categorize as left-recursive or non-recursive
        for (int i = 0; i < n; i++) {
            char production[MAX_LENGTH];
            scanf("%s", production);

            // Check if production is left-recursive (starts with the non-terminal itself)
            if (production[0] == rule->non_terminal) {
                strcpy(rule->alpha[rule->alpha_count++], production + 1); // Store α part (A -> Aα)
            } else {
                strcpy(rule->beta[rule->beta_count++], production); // Store β part (A -> β)
            }
        }
    }

    // Output: grammar without left recursion
    printf("\nGrammar without left recursion:\n");
    for (int r = 0; r < num_non_terminals; r++) {
        remove_left_recursion(&rules[r]);
    }

    return 0;
}

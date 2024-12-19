#include <stdio.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_LENGTH 100
#define MAX_NON_TERMINALS 10

// Structure to store grammar rules for each non-terminal
typedef struct {
    char non_terminal;
    char productions[MAX_RULES][MAX_LENGTH];
    int production_count;
} GrammarRule;

// Function to find the longest common prefix between two strings
int longest_common_prefix(char *str1, char *str2) {
    int i = 0;
    while (str1[i] && str2[i] && str1[i] == str2[i]) {
        i++;
    }
    return i;
}

// Function to perform left factoring on a single grammar rule
void left_factoring(GrammarRule* rule) {
    int prefix_length;
    int common_prefix[MAX_RULES] = {0}; // Array to mark which productions have been factored
    int new_non_terminal_counter = 1; // Counter to generate new non-terminals (e.g., H, H1, H2, etc.)

    // Start by identifying if any common prefix exists among all productions
    for (int i = 0; i < rule->production_count; i++) {
        if (common_prefix[i]) continue; // Skip already factored productions

        for (int j = i + 1; j < rule->production_count; j++) {
            prefix_length = longest_common_prefix(rule->productions[i], rule->productions[j]);
            if (prefix_length > 0) {
                // Left factoring is needed
                char prefix[MAX_LENGTH];
                strncpy(prefix, rule->productions[i], prefix_length);
                prefix[prefix_length] = '\0';

                // Print the factored production with a new non-terminal (e.g., H1, H2, etc.)
                char new_non_terminal = 'H' + new_non_terminal_counter - 1;  // New non-terminal name
                printf("%c -> %s%c\n", rule->non_terminal, prefix, new_non_terminal);

                // Print new rule for the factored out suffixes
                printf("%c -> ", new_non_terminal);
                int first = 1;
                for (int k = 0; k < rule->production_count; k++) {
                    if (longest_common_prefix(rule->productions[i], rule->productions[k]) == prefix_length) {
                        if (!first) printf(" | ");
                        printf("%s", rule->productions[k] + prefix_length);
                        common_prefix[k] = 1;
                        first = 0;
                    }
                }
                printf(" | epsilon\n");
                new_non_terminal_counter++;
                break;
            }
        }
    }

    // Print any unfactored productions
    for (int i = 0; i < rule->production_count; i++) {
        if (!common_prefix[i]) {
            printf("%c -> %s\n", rule->non_terminal, rule->productions[i]);
        }
    }
}

int main() {
    GrammarRule rules[MAX_NON_TERMINALS];
    int num_non_terminals;

    // Input: number of non-terminals
    printf("Enter the number of non-terminals: ");
    scanf("%d", &num_non_terminals);

    // Input rules for each non-terminal
    for (int r = 0; r < num_non_terminals; r++) {
        GrammarRule* rule = &rules[r];
        rule->production_count = 0;

        printf("\nEnter the non-terminal %d (single character): ", r + 1);
        scanf(" %c", &rule->non_terminal);

        int n;
        printf("Enter the number of productions for %c: ", rule->non_terminal);
        scanf("%d", &n);

        printf("Enter the productions for %c (one per line):\n", rule->non_terminal);

        for (int i = 0; i < n; i++) {
            scanf("%s", rule->productions[rule->production_count++]);
        }
    }

    // Output: grammar after left factoring
    printf("\nGrammar after left factoring:\n");

    for (int r = 0; r < num_non_terminals; r++) {
        left_factoring(&rules[r]);
    }

    return 0;
}

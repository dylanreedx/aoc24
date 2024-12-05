#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RULES 1000
#define MAX_PAGES 1000

typedef struct {
    int before;
    int after;
} Rule;

bool is_valid_update(int update[], int update_size, Rule rules[], int rule_count) {
    for (int i = 0; i < rule_count; i++) {
        int before = rules[i].before;
        int after = rules[i].after;

        int before_index = -1;
        int after_index = -1;

        // Find indices of `before` and `after` in the update
        for (int j = 0; j < update_size; j++) {
            if (update[j] == before) before_index = j;
            if (update[j] == after) after_index = j;
        }

        // If both pages are in the update, check the order
        if (before_index != -1 && after_index != -1 && before_index > after_index) {
            return false;  // Invalid if `before` appears after `after`
        }
    }
    return true;
}

int main() {
    FILE *file_ptr;
    char line[256];
    Rule rules[MAX_RULES];
    int updates[MAX_PAGES][MAX_PAGES];
    int update_sizes[MAX_PAGES];
    int rule_count = 0;
    int update_count = 0;

    // Open the input file
    file_ptr = fopen("input.prod", "r");
    if (file_ptr == NULL) {
        printf("File can't be opened\n");
        return 1;
    }

    // Read the rules
    while (fgets(line, sizeof(line), file_ptr)) {
        if (strchr(line, '|')) {  // It's a rule
            int before, after;
            sscanf(line, "%d|%d", &before, &after);
            rules[rule_count].before = before;
            rules[rule_count].after = after;
            rule_count++;
        } else if (strchr(line, ',')) {  // It's an update
            int *update = updates[update_count];
            int size = 0;

            char *token = strtok(line, ",");
            while (token) {
                update[size++] = atoi(token);
                token = strtok(NULL, ",");
            }
            update_sizes[update_count] = size;
            update_count++;
        }
    }
    fclose(file_ptr);

    // Validate updates and calculate the sum of middle pages
    int middle_sum = 0;

    for (int i = 0; i < update_count; i++) {
        if (is_valid_update(updates[i], update_sizes[i], rules, rule_count)) {
            int middle_index = update_sizes[i] / 2;
            middle_sum += updates[i][middle_index];
        }
    }

    printf("Sum of middle pages from valid updates: %d\n", middle_sum);

    return 0;
}

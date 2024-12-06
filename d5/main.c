#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RULES 1400
#define MAX_PAGES 1400

typedef struct {
    int before;
    int after;
} Rule;

typedef struct {
    int pages[MAX_PAGES];
    int size;
} Update;

// Function to check if an update is valid
bool is_valid_update(Update *update, Rule *rules, int rule_count) {
    for (int i = 0; i < rule_count; i++) {
        int before = rules[i].before;
        int after = rules[i].after;

        int before_index = -1, after_index = -1;
        for (int j = 0; j < update->size; j++) {
            if (update->pages[j] == before) before_index = j;
            if (update->pages[j] == after) after_index = j;
        }

        // If both pages are present and the order is wrong, the update is invalid
        if (before_index != -1 && after_index != -1 && before_index > after_index) {
            return false;
        }
    }
    return true;
}

// Function to reorder an invalid update
void reorder_update(Update *update, Rule *rules, int rule_count) {
    bool changed = true;

    while (changed) {
        changed = false;
        for (int i = 0; i < rule_count; i++) {
            int before = rules[i].before;
            int after = rules[i].after;

            int before_index = -1, after_index = -1;
            for (int j = 0; j < update->size; j++) {
                if (update->pages[j] == before) before_index = j;
                if (update->pages[j] == after) after_index = j;
            }

            if (before_index != -1 && after_index != -1 && before_index > after_index) {
                // Swap the pages to fix the order
                int temp = update->pages[before_index];
                update->pages[before_index] = update->pages[after_index];
                update->pages[after_index] = temp;
                changed = true;
            }
        }
    }
}

// Function to calculate the middle page
int middle_page(Update *update) {
    return update->pages[update->size / 2];
}

int main() {
    FILE *file_ptr = fopen("input.prod", "r");
    if (file_ptr == NULL) {
        printf("File can't be opened\n");
        return 1;
    }

    Rule rules[MAX_RULES];
    Update updates[MAX_PAGES];
    int rule_count = 0, update_count = 0;

    char line[256];

    // Read input
    while (fgets(line, sizeof(line), file_ptr)) {
        if (strchr(line, '|')) {
            int before, after;
            sscanf(line, "%d|%d", &before, &after);
            rules[rule_count++] = (Rule){before, after};
        } else if (strchr(line, ',')) {
            Update *update = &updates[update_count++];
            update->size = 0;
            char *token = strtok(line, ",");
            while (token) {
                update->pages[update->size++] = atoi(token);
                token = strtok(NULL, ",");
            }
        }
    }
    fclose(file_ptr);

    // Process updates
    int middle_sum = 0;
    for (int i = 0; i < update_count; i++) {
        if (!is_valid_update(&updates[i], rules, rule_count)) {
            // Reorder invalid update
            reorder_update(&updates[i], rules, rule_count);

            // Add middle page to the sum
            middle_sum += middle_page(&updates[i]);
        }
    }

    printf("Sum of middle pages from reordered invalid updates: %d\n", middle_sum);
    return 0;
}

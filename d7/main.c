#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 50
#define MAX_DIGITS 10
#define OPERATOR_COUNT 2

char operators[] = {'+', '*'};

void printValuesAnd2DArray(int values[], int digits[][10], int digit_counts[],
                           int rows) {
    printf("Values and 2D Array Contents:\n");
    for (int i = 0; i < rows; i++) {
        printf("Value: %d, Digits: ", values[i]);
        for (int j = 0; j < digit_counts[i]; j++) {
            printf("%d ", digits[i][j]);
        }
        printf("\n");
    }
}

void evaluateCombinations(int digits[], int num_digits, int target, int index,
                          int current_result, int *success_count, char last_operator) {
    // Base case: If we've processed all digits
    if (index == num_digits - 1) {
        if (current_result == target) {
            (*success_count)++;
        }
        return;
    }

    for (int op = 0; op < OPERATOR_COUNT; op++) {
        int next_result = current_result;

        if (operators[op] == '+') {
            // Perform addition and continue
            evaluateCombinations(digits, num_digits, target, index + 1,
                                 next_result + digits[index + 1],
                                 success_count, '+');
        } else if (operators[op] == '*') {
            if (last_operator == '+') {
                // Adjust for precedence: backtrack and apply multiplication
                int adjusted_result = (current_result - digits[index])
                                      + (digits[index] * digits[index + 1]);
                evaluateCombinations(digits, num_digits, target, index + 1,
                                     adjusted_result,
                                     success_count, '*');
            } else {
                // Perform multiplication as normal
                evaluateCombinations(digits, num_digits, target, index + 1,
                                     next_result * digits[index + 1],
                                     success_count, '*');
            }
        }
    }
}

int calculateCombinations(int values[], int digits[][10], int digit_counts[],
                           int num_equations) {
    int success_count;

    for (int eq = 0; eq < num_equations; eq++) {
        success_count = 0;

        evaluateCombinations(digits[eq], digit_counts[eq], values[eq], 0,
                             digits[eq][0], &success_count, '+');

        printf("Value: %d, Success Count: %d\n", values[eq], success_count);
    }
}


int main() {
    FILE *file_ptr;
    char line[LINE_LENGTH];
    int values[LINE_LENGTH];
    int digits[LINE_LENGTH][MAX_DIGITS];
    int digit_counts[LINE_LENGTH];
    int value_count = 0;

    file_ptr = fopen("input.test", "r");
    if (file_ptr == NULL) {
        printf("File can't be opened\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file_ptr) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        char *value = strtok(line, ":");
        if (value == NULL) {
            printf("Error: Invalid line format\n");
            return 1;
        }
        values[value_count] = atoi(value);
        char *d = strtok(NULL, ":");

        if (d == NULL) {
            printf("Error: Missing digits after value\n");
            return 1;
        }

        digit_counts[value_count] = 0;

        char *digit = strtok(d, " ");
        while (digit != NULL) {
            digits[value_count][digit_counts[value_count]++] = atoi(digit);
            digit = strtok(NULL, " ");
        }

        value_count++;
    }

    fclose(file_ptr);

    printValuesAnd2DArray(values, digits, digit_counts, value_count);

    calculateCombinations(values, digits, digit_counts, value_count);
    return 0;
}

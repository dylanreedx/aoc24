#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH 100
#define MAX_LINES 1000

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to count occurrences of a number in an array
int count_occurrences(int *array, int size, int value) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            count++;
        }
    }
    return count;
}

int main() {
    FILE *file_ptr;
    char line[LINE_LENGTH];
    int first_array[MAX_LINES];
    int second_array[MAX_LINES];
    int count = 0;

    // Open the file
    file_ptr = fopen("inputcpy.txt", "r");
    if (file_ptr == NULL) {
        printf("File can't be opened\n");
        return 1;
    }

    // Read the file and populate the arrays
    while (fgets(line, sizeof(line), file_ptr) != NULL) {
        int first_number, second_number;

        if (sscanf(line, "%d %d", &first_number, &second_number) == 2) {
            first_array[count] = first_number;
            second_array[count] = second_number;
            count++;
        } else {
            fprintf(stderr, "Invalid input: %s", line);
        }
    }
    fclose(file_ptr);

    // Calculate the similarity score
    int similarity_score = 0;
    printf("Calculating similarity score...\n");
    for (int i = 0; i < count; i++) {
        int occurrences = count_occurrences(second_array, count, first_array[i]);
        similarity_score += first_array[i] * occurrences;
        printf("Number: %d, Occurrences in right array: %d, Contribution to score: %d\n",
               first_array[i], occurrences, first_array[i] * occurrences);
    }

    // Print the similarity score
    printf("Total Similarity Score: %d\n", similarity_score);

    return 0;
}

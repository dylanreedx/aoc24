#include <stdio.h>
#include <string.h>

#define GRID_SIZE 200
#define WORD "XMAS"

// Directions: (row change, col change)
int directions[8][2] = {
    {0, 1},   // Right
    {0, -1},  // Left
    {1, 0},   // Down
    {-1, 0},  // Up
    {1, 1},   // Down-Right
    {-1, -1}, // Up-Left
    {1, -1},  // Down-Left
    {-1, 1}   // Up-Right
};

// Function to check if the word exists starting at (row, col) in a given direction
int search_direction(char grid[GRID_SIZE][GRID_SIZE], int rows, int cols, int row, int col, int dir_row, int dir_col, const char *word) {
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        int new_row = row + i * dir_row;
        int new_col = col + i * dir_col;

        // Check bounds
        if (new_row < 0 || new_row >= rows || new_col < 0 || new_col >= cols) {
            return 0;
        }

        // Check character match
        if (grid[new_row][new_col] != word[i]) {
            return 0;
        }
    }

    return 1; // Word found
}

// Function to count occurrences of the word in the grid
int count_word_occurrences(char grid[GRID_SIZE][GRID_SIZE], int rows, int cols, const char *word) {
    int count = 0;
    int word_length = strlen(word);

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            // Check all 8 directions
            for (int d = 0; d < 8; d++) {
                if (search_direction(grid, rows, cols, row, col, directions[d][0], directions[d][1], word)) {
                    count++;
                }
            }
        }
    }

    return count;
}

int main() {
    FILE *file_ptr;
    char grid[GRID_SIZE][GRID_SIZE] = {0};
    char line[GRID_SIZE];
    int rows = 0;
    int cols = 0;

    // Read the input file into the grid
    file_ptr = fopen("input.prod", "r");
    if (file_ptr == NULL) {
        printf("File can't be opened\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file_ptr) != NULL) {
        cols = strlen(line);
        if (line[cols - 1] == '\n') {
            line[--cols] = '\0'; // Remove newline character
        }
        strcpy(grid[rows++], line);
    }

    fclose(file_ptr);

    // Count occurrences of the word
    int count = count_word_occurrences(grid, rows, cols, WORD);
    printf("Total occurrences of '%s': %d\n", WORD, count);

    return 0;
}

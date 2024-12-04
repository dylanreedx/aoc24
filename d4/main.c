#include <stdio.h>
#include <string.h>

#define GRID_SIZE 200

int search_xmas(char grid[GRID_SIZE][GRID_SIZE], int rows, int cols, int row, int col) {
    if (grid[row][col] != 'A') {
        return 0;
    }

    if (row - 1 < 0 || row + 1 >= rows || col - 1 < 0 || col + 1 >= cols) {
        return 0;
    }

    char top_left = grid[row - 1][col - 1];
    char bottom_right = grid[row + 1][col + 1];
    int diagonal1_valid = (top_left == 'M' && bottom_right == 'S') || (top_left == 'S' && bottom_right == 'M');

    char top_right = grid[row - 1][col + 1];
    char bottom_left = grid[row + 1][col - 1];
    int diagonal2_valid = (top_right == 'M' && bottom_left == 'S') || (top_right == 'S' && bottom_left == 'M');

    if (diagonal1_valid && diagonal2_valid) {
        return 1;
    }

    return 0;
}

int count_xmas_patterns(char grid[GRID_SIZE][GRID_SIZE], int rows, int cols) {
    int count = 0;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            count += search_xmas(grid, rows, cols, row, col);
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

    file_ptr = fopen("input.prod", "r");
    if (file_ptr == NULL) {
        printf("File can't be opened\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file_ptr) != NULL) {
        cols = strlen(line);
        if (line[cols - 1] == '\n') {
            line[--cols] = '\0';
        }
        strcpy(grid[rows++], line);
    }

    fclose(file_ptr);

    int count = count_xmas_patterns(grid, rows, cols);
    printf("Total X-MAS patterns: %d\n", count);

    return 0;
}

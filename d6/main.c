#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 500
#define MAX_ROWS 500
#define MAX_COLS 500

typedef struct {
    char **grid;
    int rows;
    int cols;
} Map;

typedef struct {
    int x;
    int y;
} Point;

Point directions[] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};

void initialize_map(Map *map, int max_rows, int max_cols) {
    map->rows = 0;
    map->cols = 0;
    map->grid = malloc(max_rows * sizeof(char *));
    for (int i = 0; i < max_rows; i++) {
        map->grid[i] = malloc(max_cols * sizeof(char));
        memset(map->grid[i], ' ', max_cols);
    }
}

void free_map(Map *map, int max_rows) {
    for (int i = 0; i < max_rows; i++) {
        free(map->grid[i]);
    }
    free(map->grid);
}

void load_map_from_file(Map *map, const char *filename) {
    FILE *file_ptr = fopen(filename, "r");
    if (file_ptr == NULL) {
        printf("File can't be opened\n");
        exit(1);
    }

    char line[LINE_LENGTH];
    while (fgets(line, sizeof(line), file_ptr) != NULL) {
        int cols = strlen(line);
        if (line[cols - 1] == '\n') {
            line[--cols] = '\0';
        }
        strcpy(map->grid[map->rows++], line);
        if (cols > map->cols) {
            map->cols = cols;
        }
    }

    fclose(file_ptr);
}

void print_map(const Map *map) {
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            printf("%c", map->grid[i][j]);
        }
        printf("\n");
    }
}

void traverse_and_mark(Map *map, int start_x, int start_y, int dir_index) {
    const char obstruction = '#';
    const char guard = '^';
    int x = start_x, y = start_y;

    while (true) {
        if (map->grid[x][y] != guard) {
            map->grid[x][y] = 'X';
        }

        Point direction = directions[dir_index];
        int new_x = x + direction.x;
        int new_y = y + direction.y;

        if (new_x < 0 || new_x >= map->rows || new_y < 0 || new_y >= map->cols) {
            break;
        }

        if (map->grid[new_x][new_y] == obstruction) {
            dir_index = (dir_index + 1) % 4;
            continue;
        }

        x = new_x;
        y = new_y;
    }
}

void mark_guard_paths(Map *map) {
    const char guards[] = {'^', 'v', '<', '>'};

    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            for (int g = 0; g < 4; g++) {
                if (map->grid[i][j] == guards[g]) {
                    traverse_and_mark(map, i, j, g);
                }
            }
        }
    }
}

int count_markings(const Map *map) {
    int count = 0;
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            if (map->grid[i][j] == 'X') {
                count++;
            }
        }
    }
    return count;
}

int main() {
    Map map;
    initialize_map(&map, MAX_ROWS, MAX_COLS);

    load_map_from_file(&map, "input.prod");

    printf("Original Map:\n");
    print_map(&map);

    mark_guard_paths(&map);

    printf("\nMap with Guard Path:\n");
    print_map(&map);

    int markings = count_markings(&map);
    printf("\nTotal Markings: %d\n", markings);

    free_map(&map, MAX_ROWS);

    return 0;
}

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 200

bool is_safe(int *levels, int count) {
  bool increasing = true;
  bool decreasing = true;

  for (int i = 1; i < count; i++) {
    int diff = levels[i] - levels[i - 1];
    if (abs(diff) < 1 || abs(diff) > 3) {
      printf("Failed difference check at index %d: %d -> %d (diff: %d)\n",
             i - 1, levels[i - 1], levels[i], diff);
      return false; // Adjacent levels differ by less than 1 or more than 3.
    }
    if (diff < 0) {
      increasing = false; // Not increasing.
    }
    if (diff > 0) {
      decreasing = false; // Not decreasing.
    }
  }

  printf("Report is %s\n", (increasing || decreasing) ? "SAFE" : "UNSAFE");
  return increasing || decreasing; // Must be either increasing or decreasing.
}

bool problem_dampener(int *levels, int count) {
  for (int i = 0; i < count; i++) {
    int modified[LINE_LENGTH];
    int modified_count = 0;

    // Create a new array without the i-th level.
    for (int j = 0; j < count; j++) {
      if (j != i) {
        modified[modified_count++] = levels[j];
      }
    }

    // Check if the modified array is safe.
    if (is_safe(modified, modified_count)) {
      return true;
    }
  }
  return false;
}

int main() {
  FILE *file_ptr;
  char line[LINE_LENGTH];
  int safe_count = 0;

  file_ptr = fopen("rinput.txt", "r");
  if (file_ptr == NULL) {
    printf("File can't be opened\n");
    return 1;
  }

  while (fgets(line, sizeof(line), file_ptr) != NULL) {
    // Strip trailing newline if present.
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }

    int levels[LINE_LENGTH] = {0};
    int count = 0;

    // Parse numbers in the line.
    char *token = strtok(line, " ");
    while (token != NULL) {
      levels[count++] = atoi(token);
      token = strtok(NULL, " ");
    }

    // Print parsed levels for debugging.
    printf("Parsed levels (%d): ", count);
    for (int i = 0; i < count; i++) {
      printf("%d ", levels[i]);
    }
    printf("\n");

    // Check if the report is safe.
    if (is_safe(levels, count)) {
      safe_count++;
    } else if (problem_dampener(levels, count)) {
      safe_count++;
    }
  }

  fclose(file_ptr);
  printf("Total safe reports: %d\n", safe_count);
  return 0;
}

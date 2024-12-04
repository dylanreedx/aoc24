#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 200



int main() {
  FILE *file_ptr;
  char line[LINE_LENGTH];

  file_ptr = fopen("input.txt", "r");
  if (file_ptr == NULL) {
    printf("File can't be opened\n");
    return 1;
  }

  while (fgets(line, sizeof(line), file_ptr) != NULL) {
    // char *token = strtok(line, " ");
  }


  fclose(file_ptr);

  return 0;
}

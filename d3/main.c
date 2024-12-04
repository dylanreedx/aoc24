#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 5000
#define MAX_PRODUCTS 5000

// xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))
// Only the four highlighted sections are real mul instructions. Adding up the
// result of each instruction produces 161 (2*4 + 5*5 + 11*8 + 8*5).
//
// The do() instruction enables future mul instructions.
// The don't() instruction disables future mul instructions.

void print_valid_prods(int *valid_prods, int count) {
  for (int i = 0; i < count; i++) {
    printf("%d ", valid_prods[i]);
  }
  printf("\n");
}

int main() {
  FILE *file_ptr;
  char line[LINE_LENGTH];
  int prod_count = 0;
  int i = 0;
  int valid_prods[MAX_PRODUCTS];
  bool mul_enabled = true;

  file_ptr = fopen("rinput.txt", "r");
  if (file_ptr == NULL) {
    printf("File can't be opened\n");
    return 1;
  }

  while (fgets(line, sizeof(line), file_ptr) != NULL) {
    printf("Processing line: %s", line);

    int i = 0; // Initialize index for each line
    while (line[i] != '\0') {
      if (line[i] == 'd' && line[i + 1] == 'o' && line[i + 2] == 'n' &&
          line[i + 3] == '\'' && line[i + 4] == 't' && line[i + 5] == '(' &&
          line[i + 6] == ')') {
              mul_enabled = false;
      }
        if (line[i] == 'd' && line[i + 1] == 'o' && line[i + 2] == '(' &&
            line[i + 3] == ')') {
                mul_enabled = true;
        }
      // Check for "mul("
      if (mul_enabled && line[i] == 'm' && line[i + 1] == 'u' && line[i + 2] == 'l' &&
          line[i + 3] == '(') {
        i += 4; // Move to the character after '('

        // Parse the first number
        int a = 0;
        while (isdigit(line[i])) {
          a = a * 10 + (line[i] - '0');
          i++;
        }

        if (line[i] != ',') {
          i++; // Skip invalid syntax
          continue;
        }
        i++; // Move past the comma

        // Parse the second number
        int b = 0;
        while (isdigit(line[i])) {
          b = b * 10 + (line[i] - '0');
          i++;
        }

        if (line[i] != ')') {
          i++; // Skip invalid syntax
          continue;
        }
        i++; // Move past the closing parenthesis

        // Valid mul(X,Y), calculate product
        valid_prods[prod_count++] = a * b;
      } else {
        i++;
      }
    }
  }

  fclose(file_ptr);

  // printf("Valid Products: ");
  print_valid_prods(valid_prods, prod_count);

  int sum = 0;
  for (int i = 0; i < prod_count; i++) {
    sum += valid_prods[i];
  }
  printf("Sum of valid products: %d\n", sum);

  return 0;
}

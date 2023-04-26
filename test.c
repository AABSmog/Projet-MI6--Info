#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000

void find_word_in_file(const char* filename, const char* word) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int line_number = 0;

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        line_number++;
        char* line_ptr = line;
        char* word_ptr = word;

        while (*line_ptr != '\0') {
            if (tolower(*line_ptr) == tolower(*word_ptr)) {
                line_ptr++;
                word_ptr++;
                if (*word_ptr == '\0') {
                    printf("Found '%s' in line %d: %s", word, line_number, line);
                    break;
                }
            } else {
                line_ptr++;
                word_ptr = word;
            }
        }
    }

    fclose(fp);
}
int main() {
    find_word_in_file("produit.txt", "coc1");
    return 0;
}

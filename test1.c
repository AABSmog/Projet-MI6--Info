#include <stdlib.h>
#include <stdio.h>

int main() {
    char str[] = "1234B";
    char *endptr;
    long int n = strtol(str, &endptr, 10);
    printf("La chaîne '%s' convertie en entier est : %ld\n", str, n);
    printf("Le premier caractère non utilisé est : '%s'\n", endptr);
    return 0;
}

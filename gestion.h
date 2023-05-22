#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 10000
#define MAX_STOCK 200
int managestock(char* file);
void addproduct(char* file);
void modifystock(char *file, int ref, int quant);
void outofstock(char *file);
void searchrefproduct(char *file, int number);
void searchnameproduct(char *file, char *word);
void lowstock(char *file);
int management(int n);
#ifndef GESTION_H
#define GESTION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000
#define MAX_STOCK 200
int managestock(char *file);
int addproduct(char* file);
void modifystock(char *file, int ref, int quant);
void outofstock(char *file);
int searchrefproduct(char *file, int number);
void searchnameproduct(char *file, char *word);
void lowstock(char *file);
int management(int n);
void displaystock(char *file);
#endif
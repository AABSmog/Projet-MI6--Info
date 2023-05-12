#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000
void ajouterproduit(char* fichier);
void modifierstock(char *fichier, int reference, int quant);
void afficherstockepuise(char *fichier);
void numinfile(char *fichier, int num);
void wordinfile(char *fichier, char *mot);
int gestion(int n);
void afficherstockfaible(char *fichier);
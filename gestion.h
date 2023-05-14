#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000
void ajouterproduit(char* fichier);
void modifierstock(char *fichier, int reference, int quant);
void afficherstockepuise(char *fichier);
void chercherrefproduit(char *fichier, int num);
void cherchernomproduit(char *fichier, char *mot);
void afficherstockfaible(char *fichier);
int gestion(int n);
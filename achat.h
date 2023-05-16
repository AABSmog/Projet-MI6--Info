#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

void afficher_stock(char * fichier);
void acheter(int ref, int quantite, char id[]);
void espace_achat(char id[]);
 void connect_by_id(char *id);
 int achat(int n);
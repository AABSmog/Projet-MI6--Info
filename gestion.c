#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int checkItem(FILE *fileptr)
{
  int access;
  int nom[100];
  int ref;
  printf("Voulez vous trouver un produit en utilisant son nom ou sa référence. \n");
  printf("Ecrire 1 si vous voulez utiliser le nom ou 2 si vous voulez utiliser la référence. \n");
  scanf(" %d", &access);
  printf("test");
  if (access == 1)
  {
    printf("Saisir le nom de votre produit \n");
    scanf("%s", nom);
  }
  else if (access == 2)
  {
    printf("Saisir la référence de votre produit \n");
    scanf("%d", &ref);
  }
  FILE *fptr;
  char filename[] = "produit.txt";
  int ligne[100];
  fptr = fopen(filename, "r");
  if (fptr == NULL)
  {
    printf("Erreur: Impossible d'ouvrir le fichier %s.\n", filename);
    exit(1);
  }
  if (access == 1)
  {
    int num_ligne = 1;
    int ligne_trouvee = 0;
    while (fgets(ligne, sizeof(ligne), fptr))
    {
      if (strcasecmp(ligne, nom))
      {
        printf("Le produit \"%s\" a été trouvé en stock.\n", nom);
        printf("%s", ligne);
        ligne_trouvee = 1;
        break;
      }
      else
      {
        num_ligne++;
      }
    }
    fclose(fptr);
    return 0;
  }
}
int main(){
  FILE *fptr;
  int identifiant;
  int i=3;
  printf("Veuillez saisir votre identifiant.\n");
  scanf("%d",&identifiant);
  while(i!=0){
    if(identifiant!=123321 && identifiant!=987789){
    printf("Identifiant non reconnue.\n");
    printf("Il vous reste %d tentatives.Veuilliez resaisir votre identifiant.\n",i);
    scanf("%d",&identifiant);
    i--;
  }
  else if(identifiant==123321||identifiant==987789){
  checkItem(fptr);
  return 0;
  }
  }
  if(i==0){
    printf("Les identifiants saisis ne sont pas enregistrés dans notre système.");
    return 0;
  }
}
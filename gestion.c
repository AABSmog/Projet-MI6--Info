#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000
void augmenterstock(char *fichier, int reference, int quant)
{
  FILE *fp = fopen(fichier, "r");
  FILE *tempo = fopen("tempo.txt", "w");
  if (fp == NULL || tempo == NULL)
  {
    printf("Erreur en ouvrant le fichier %s \n", fichier);
    exit(1);
  }
  char ligne[MAX];
  int trouve = 0;
  while (fgets(ligne, sizeof(ligne), fp))
  {
    char produit[MAX];
    int ref;
    int quantite;
    float prix;
    int taille;
    sscanf(ligne, "%s %d %d %f %d", produit, &ref, &quantite, &prix, &taille);
    if (reference == ref)
    {
      quantite=quant+quantite;
      trouve=1;
    }
    fprintf(tempo,"%s %d %d %f %d \n", produit, ref, quantite, prix,taille);
  }
  fclose(fp);
  fclose(tempo);
  remove(fichier);
  rename("tempo.txt", fichier);
  if(trouve==1){
    printf("Le stock de ce produit a ete bien modifie. \n");
  }
  else if(trouve==0){
    printf("Ce produit n'est pas en stock. \n");
  }
}
  void afficherstockepuise(char * fichier)
  {
    FILE *fp = fopen(fichier, "r");
    if (fp == NULL)
    {
      printf("Erreur en ouvrant le fichier %s \n", fichier);
      exit(1);
    }
    char ligne[MAX];
    int stockEpuise = 0;
    printf("Produits avec un stock epuise :\n");
    while (fgets(ligne, sizeof(ligne), fp))
    {
      char produit[MAX];
      int ref;
      int quantite;
      float prix;
      int taille;
      sscanf(ligne, "%s %d %d %f %d", produit, &ref, &quantite, &prix, &taille);
      if (quantite == 0)
      {
        printf("Nom: %s Reference: %d Stock: %d Prix: %f Taille: %d \n", produit, ref, quantite, prix, taille);
        stockEpuise = 1;
      }
    }
    if (stockEpuise == 0)
    {
      printf("Aucun produit avec un stock epuise.\n");
    }
    fclose(fp);
  }
  void numinfile(char *fichier, int num)
  {
    FILE *fp = fopen(fichier, "r");
    if (fp == NULL)
    {
      printf("Erreur en ouvrant le fichier %s \n", fichier);
      exit(2);
    }
    char ligne[MAX];
    int trouve = 0;
    while (fgets(ligne, sizeof(ligne), fp))
    {
      char produit[MAX];
      int ref;
      int quantite;
      float prix;
      int taille;
      sscanf(ligne, "%s %d %d %f %d", produit, &ref, &quantite, &prix, &taille);
      if (ref == num)
      {
        printf("Le produit de reference '%d' a ete trouve en stock \n", num);
        printf("Nom: %s Reference: %d Stock: %d Prix: %f Taille: %d \n", produit, ref, quantite, prix, taille);
        trouve = 1;
        break;
      }
    }
    if (trouve == 0)
    {
      printf("Le produit de reference %d n'a pas ete trouve en stock \n", num);
    }
    fclose(fp);
  }

  void wordinfile(char *fichier, char *mot)
  {
    FILE *fp = fopen(fichier, "r");
    if (fp == NULL)
    {
      printf("Erreur en ouvrant le fichier %s \n", fichier);
      exit(3);
    }
    char ligne[MAX];
    int num_ligne = 0;
    int trouve = 0;
    while (fgets(ligne, MAX, fp) != NULL)
    {
      num_ligne++;
      char *ptr_ligne = ligne;
      char *ptr_mot = mot;
      while (*ptr_ligne != 0)
      {
        if (tolower(*ptr_ligne) == tolower(*ptr_mot))
        {
          ptr_ligne++;
          ptr_mot++;
          if (*ptr_mot == '\0')
          {
            printf("Le produit '%s' a ete trouve en stock \n", mot);
            printf("Voici ses informations : \n");
            printf("%s", ligne);
            trouve = 1;
            break;
          }
        }
        else
        {
          ptr_ligne++;
          ptr_mot = mot;
        }
      }
      if (trouve == 1)
      {
        break;
      }
    }
    if (trouve == 0)
    {
      printf("Ce produit n'est pas en stock \n");
    }
    fclose(fp);
  }

  int checkItem(FILE * fileptr)
  {
    int access;
    char nom[100];
    int ref;
    printf("Voulez vous trouver un produit en utilisant son nom ou sa reference. \n");
    printf("Ecrire 1 si vous voulez utiliser le nom ou 2 si vous voulez utiliser la reference. \n");
    scanf(" %d", &access);
    if (access == 1)
    {
      printf("Saisir le nom de votre produit \n");
      scanf("%s", nom);
      wordinfile("produit.txt", nom);
    }
    else if (access == 2)
    {
      printf("Saisir la reference de votre produit \n");
      scanf("%d", &ref);
      numinfile("produit.txt", ref);
    }
  }
  int main()
  {
    FILE *fptr;
    int identifiant;
    int i = 3;
    int a;
    printf("Veuillez saisir votre identifiant.\n");
    scanf("%d", &identifiant);
    while (i != 0)
    {
      if (identifiant != 123321 && identifiant != 987789)
      {
        printf("Identifiant non reconnue.\n");
        printf("Il vous reste %d tentatives.Veuilliez resaisir votre identifiant.\n", i);
        scanf("%d", &identifiant);
        i--;
      }
      else if (identifiant == 123321 || identifiant == 987789)
      {
        afficherstockepuise("produit.txt");
        printf("Voulez vous :\n");
        printf("1.Cherchez un produit ?\n");
        printf("2.Augmenter le stock d'un produit ?\n");
        scanf("%d", &a);
        if (a == 1)
        {
          checkItem(fptr);
          return 0;
        }
        else if (a == 2)
        {
        int reference;
        int quant;
        printf("Veuillez saisir la reference du produit que vous voulez augmenter en stock: ");
        scanf("%d",&reference);
        printf("\n");
        printf("Veuilliez saisir la quantite a ajouter en stock: ");
        scanf("%d",&quant);
        printf("\n");
        augmenterstock("produit.txt",reference,quant);
        }
      }
      if (i == 0)
      {
        printf("Les identifiants saisis ne sont pas enregistres dans notre systeme.");
        return 0;
      }
    }
  }
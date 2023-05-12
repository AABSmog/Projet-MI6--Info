#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000
void ajouterproduit(char *fichier)
{
  FILE *fp = fopen(fichier, "a");
  if (fp == NULL)
  {
    printf("Erreur en ouvrant le fichier %s \n", fichier);
    exit(1);
  }
  char produit[MAX];
  int ref;
  int quantite;
  float prix;
  int taille;
  printf("Saisir le nom du produit :\n");
  scanf("%s", produit);
  printf("Saisir la reference du produit :\n");
  scanf("%d", &ref);
  printf("Saisir la quantite en stock :\n");
  scanf("%d", &quantite);
  printf("Saisir le prix du produit :\n");
  scanf("%f", &prix);
  printf("Saisir la taille du produit :\n");
  scanf("%d", &taille);
  fprintf(fp, "\n%s %d %d %f %d", produit, ref, quantite, prix, taille);
  fclose(fp);
  printf("Le produit a ete ajoute avec succes.\n");
}
void modifierstock(char *fichier, int reference, int quant)
{
  FILE *fp = fopen(fichier, "r");
  FILE *tempo = fopen("tempo.txt", "w");
  if (fp == NULL || tempo == NULL)
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
    if (reference == ref)
    {
      quantite = quant + quantite;
      trouve = 1;
    }
    fprintf(tempo, "%s %d %d %f %d \n", produit, ref, quantite, prix, taille);
  }
  fclose(fp);
  fclose(tempo);
  remove(fichier);
  rename("tempo.txt", fichier);
  if (trouve == 1)
  {
    printf("Le stock de ce produit a ete bien modifie. \n");
  }
  else if (trouve == 0)
  {
    printf("Ce produit n'est pas en stock. \n");
  }
}
void afficherstockepuise(char *fichier)
{
  FILE *fp = fopen(fichier, "r");
  if (fp == NULL)
  {
    printf("Erreur en ouvrant le fichier %s \n", fichier);
    exit(3);
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
    exit(4);
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
      printf("Voici ses informations : \n");
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
    exit(5);
  }
  char ligne[MAX];
  int num_ligne = 0;
  int trouve = 0;
  char produit[MAX];
  int ref;
  int quantite;
  float prix;
  int taille;
  while (fgets(ligne, MAX, fp) != NULL)
  {
    num_ligne++;
    char *ptr_ligne = ligne;
    char *ptr_mot = mot;
    while (*ptr_ligne != 0)
    {
      sscanf(ligne, "%s %d %d %f %d", produit, &ref, &quantite, &prix, &taille);
      if (tolower(*ptr_ligne) == tolower(*ptr_mot))
      {
        ptr_ligne++;
        ptr_mot++;
        if (*ptr_mot == '\0' && *ptr_ligne == ' ')
        {
          printf("Le produit '%s' a ete trouve en stock \n", mot);
          printf("Voici ses informations : \n");
          printf("Nom: %s Reference: %d Stock: %d Prix: %f Taille: %d \n", produit, ref, quantite, prix, taille);
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
int main()
{
  int identifiant;
  int i = 3;
  int a;
  char nom[MAX];
  int ref;
  printf("Veuillez saisir votre identifiant.\n");
  scanf("%d", &identifiant);
  while (i != 0)
  {
    if (identifiant != 123321 && identifiant != 987789)
    {
      i--;
      printf("Identifiant non reconnue.\n");
      printf("Il vous reste %d tentatives.Veuilliez resaisir votre identifiant.\n", i);
      scanf("%d", &identifiant);
    }
    else if (identifiant == 123321 || identifiant == 987789)
    {
      afficherstockepuise("produit.txt");
      printf("MODE GESTION : \n");
      printf("Voulez vous :\n");
      printf("1.Cherchez un produit en utilisant son nom ?\n");
      printf("2.Cherchez un produit en utilisant sa reference ?\n");
      printf("3.Modifier le stock d'un produit ?\n");
      printf("4.Ajouter un produit au stock ?\n");
      printf("5.Quitter le programme de gestion ? \n");
      scanf("%d", &a);
      if (a == 1)
      {
        printf("Saisir le nom de votre produit \n");
        scanf("%s", nom);
        wordinfile("produit.txt", nom);
        return 0;
      }
      else if (a == 2)
      {
        printf("Saisir la reference de votre produit \n");
        scanf("%d", &ref);
        numinfile("produit.txt", ref);
        return 0;
      }
      else if (a == 3)
      {
        int reference;
        int quant;
         int n=0;
        printf("Voulez vous: \n");
        printf("1.Augmenter le stock ? \n");
        printf("2.Reduire le stock ? \n");
        scanf("%d",&n);
        if(n==1){
        printf("Veuillez saisir la reference du produit que vous voulez augmenter en stock: ");
        scanf("%d", &reference);
        printf("\n");
        printf("Veuilliez saisir la quantite a ajouter en stock: ");
        scanf("%d", &quant);
        printf("\n");
        modifierstock("produit.txt", reference, quant);
        return 0;
        }
        else if(n==2){
          printf("Veuillez saisir la reference du produit que vous voulez reduire en stock en stock: ");
        scanf("%d", &reference);
        printf("\n");
        printf("Veuilliez saisir la quantite a reduire en stock: ");
        scanf("%d", &quant);
        printf("\n");
        modifierstock("produit.txt", reference,-quant);
        return 0;
        }
        else{
          printf("Erreur: veuillez saisir soi 1 soi 2. \n");
          return 0;
        }
      }
      else if (a == 4)
      {
        ajouterproduit("produit.txt");
        return 0;
      }
      else if (a == 5)
      {
        return 0;
      }
      else
      {
        printf("Erreur: veuillez choisir un nombre entre 1 et 4. \n");
        return 0;
      }
    }
    if (i == 0)
    {
      printf("Les identifiants saisis ne sont pas enregistres dans notre systeme.");
      return 0;
    }
  }
  return 0;
}
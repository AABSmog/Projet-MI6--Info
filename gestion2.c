#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000
#define MAX_STOCK 200
//définir les fonctions qu'on va utiliser
void ajouterproduit();
void modifierstock();
void afficherstock();
void afficherstockepuise();
void chercherrefproduit();
void cherchernomproduit();
void afficherstockfaible();
int gererstock();
//définir une structure de produits 
typedef struct{
char produit[MAX];
int ref;
  int quantite;
  float prix;
  int taille;
}Produit;
int gererstock(char *fichier){
  FILE *fp=fopen(fichier,"r");
  if(fp==NULL){
    printf("Erreur en ouvrant le fichier %s \n",fichier);
    exit(1);
  }
  char ligne[MAX];
  int q;
  q=0;
  while(fgets(ligne,sizeof(ligne),fp)){
    Produit prod;
    sscanf(ligne, "%s %d %d %f %d", prod.produit, &prod.ref, &prod.quantite, &prod.prix, &prod.taille);
    q=q+(prod.quantite*prod.taille);
  }
  return q;
}
// une fonction pour ajouter des produits au stock
void ajouterproduit(char *fichier)
{
  //ouvrir le fichier en mode écriture en partant de la fin
  FILE *fp = fopen(fichier, "a");
  if (fp == NULL)//tester si le fichier s'ouvre correctement ou pas
  {
    //si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", fichier);
    exit(1);
  }
  // définir le produit
  Produit prod;
  // demander les informations du produit à l'utilisateur
  printf("Veuillez saisir le nom du produit :\n");
  scanf("%s", prod.produit);
  printf("Veuillez saisir la reference du produit :\n");
  scanf("%d", &prod.ref);
  printf("Veuillez saisir la quantite en stock :\n");
  scanf("%d", &prod.quantite);
  printf("Veuillez saisir le prix du produit :\n");
  scanf("%f", &prod.prix);
  printf("Veuillez saisir la taille du produit :\n");
  scanf("%d", &prod.taille);
  int q;
  q=gererstock(fichier)+prod.taille*prod.quantite;
  printf("%d ",q);
  if(q>MAX_STOCK){
    printf("Le produit n'a pas ete ajoute au stock \nVous ne pouvez pas depasser la limite du stock\n");
    return 0;
  }
  else if(q>=0 && q<=MAX_STOCK){
  // ajouter au fichier le nouveau produit
  fprintf(fp, "\n%s %d %d %f %d", prod.produit, prod.ref, prod.quantite, prod.prix, prod.taille);
  }
  //fermer le fichier
  fclose(fp);
  printf("Ce produit a ete ajoute avec succes.\n");
}
// une fonction pour modifier le stock d'un produit(soi l'augmenter ou le réduire)
void modifierstock(char *fichier, int reference, int quant)
{
  //créer un fichier temporaire en mode écriture
  FILE *tempor = fopen("temporaire.txt", "w");
  //ouvrir le fichier principal en mode lecture
  FILE *fp = fopen(fichier, "r");
  if (tempor == NULL || fp == NULL)//tester si le fichier s'ouvre correctement ou pas
  {
     //si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", fichier);
    exit(2);
  }
  int trouve;
  trouve=0;
  char ligne[MAX];
  //lire le fichier ligne par ligne
  while (fgets(ligne, sizeof(ligne), fp))
  {
    Produit prod;
    // lire les informations du produit dans le fichier
    sscanf(ligne, "%s %d %d %f %d", prod.produit, &prod.ref, &prod.quantite, &prod.prix, &prod.taille);
    if (reference == prod.ref)//voir si la réference du produit est la même que celle recherchée
    {
      // modifier la quantité du produit
      prod.quantite = quant + prod.quantite;
      trouve = 1;
    }
    // ajouter chaque ligne dans le fichier temporaraire
    fprintf(tempor, "%s %d %d %f %d \n", prod.produit, prod.ref, prod.quantite, prod.prix, prod.taille);
  }
  if (trouve == 1)
  //si le produit a été trouvé et modifié, ce message sera affiché 
  {
    printf("Le stock de ce produit a ete bien modifie. \n");
  }
  else if (trouve == 0)
  //si le produit n'a pas été trouvé et modifié, ce message sera affiché 
  {
    printf("Ce produit n'est pas en stock. \n");
  }
  // fermer le fichier principal 
  fclose(fp);
  //fermer le fichier temporaire
  fclose(tempor);
  //supprimer le fichier principal
  remove(fichier);
  //renommer le fichier temporaire avec le nom du fichier principal
  rename("temporaire.txt", fichier);
}
//une fonction pour afficher les produits avec 0 en stock
void afficherstockepuise(char *fichier)
{
  //ouvrir le fichier en mode lecture
  FILE *fp = fopen(fichier, "r");
  if (fp == NULL)//tester si le fichier s'ouvre correctement ou pas
  {
     //si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", fichier);
    exit(3);
  }
  char ligne[MAX];
  int stockepuise;
  stockepuise=0;
  printf("Produits avec un stock epuise :\n");
  //lire le fichier ligne par ligne
  while (fgets(ligne, sizeof(ligne), fp))
  {
    Produit prod;
    sscanf(ligne, "%s %d %d %f %d", prod.produit, &prod.ref, &prod.quantite, &prod.prix, &prod.taille);
    if (prod.quantite == 0)//si la quantité du produit est égale à 0
    {
      //afficher toutes les informations du produit avec le stock à 0
      printf("Nom: %s Reference: %d Stock: %d Prix: %f Taille: %d \n", prod.produit, prod.ref, prod.quantite, prod.prix, prod.taille);
      stockepuise = 1;
    }
  }
  if (stockepuise == 0)//si aucun produit n'as un stock à 0
  {
    printf("Aucun produit avec un stock epuise.\n");
  }
  //fermer le fichier
  fclose(fp);
}
//une fonction pour afficher un produit à partir de sa réference
void chercherrefproduit(char *fichier, int num)
{
  //ouvrir le fichier en mode lecture
  FILE *fp = fopen(fichier, "r");
  if (fp == NULL)
  {
     //si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", fp);
    exit(4);
  }
  int trouve;
  trouve=0;
  char ligne[MAX];
  while (fgets(ligne, sizeof(ligne), fp))
  {
    Produit prod;
    sscanf(ligne, "%s %d %d %f %d", prod.produit, &prod.ref, &prod.quantite, &prod.prix, &prod.taille);
    if (prod.ref == num)//si la réference d'un produit est la même que la réference saisie par l'utilisateur
    {
      //afficher toutes les informations du produit
      printf("Le produit de reference '%d' a ete trouve en stock \nVoici ses informations : \n", num);
      printf("Nom: %s Reference: %d Stock: %d Prix: %f Taille: %d \n", prod.produit, prod.ref, prod.quantite, prod.prix, prod.taille);
      trouve = 1;
      break;
    }
  }
  if (trouve == 0)//si aucune réference des produits n'est la même que celle saisie par l'utilisateur
  {
    printf("Le produit de reference %d n'a pas ete trouve en stock \n", num);
  }
  //fermer le fichier
  fclose(fp);
}
//une fonction pour afficher un produit à partir de son nom
void cherchernomproduit(char *fichier, char *mot)
{
  //ouvrir le fichier en mode lecture
  FILE *fp = fopen(fichier, "r");
  if (fp == NULL)
  {
    //si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", fp);
    exit(5);
  }
  int trouve;
  trouve=0;
  char ligne[MAX];
  Produit prod;
  while (fgets(ligne, MAX, fp) != NULL)
  {
    //définir un pointeur sur la ligne
    char *ptr_ligne = ligne;
    //définir un pointeur sur le nom du produit
    char *ptr_mot = mot;
    while (*ptr_ligne != 0)//parcourir caractére par caractére de la ligne
    {
      sscanf(ligne, "%s %d %d %f %d",prod.produit, &prod.ref, &prod.quantite, &prod.prix, &prod.taille);
      if (tolower(*ptr_ligne) == tolower(*ptr_mot))//si le caractére de la ligne et celui du nom sont les mêmes
      {
        //avancer d'un caractére dans la ligne et dans le nom
        ptr_mot++;
        ptr_ligne++;
        if (*ptr_mot == '\0' && *ptr_ligne == ' ')//si c'est la fin du nom de produit et le caractére suivant dans la ligne est un espace
        {
          printf("Le produit '%s' a ete trouve en stock \nVoici ses informations : \n", mot);
          printf("Nom: %s Reference: %d Stock: %d Prix: %f Taille: %d \n", prod.produit, prod.ref, prod.quantite, prod.prix, prod.taille);
          trouve = 1;
          break;
        }
      }
      else
      {
        //avancer au prochain caractére de la ligne
        ptr_ligne++;
        //reinitialiser le pointeur du nom de produit
        ptr_mot = mot;
      }
    }
  }
  if (trouve == 0)//si le produit n'as pas été trouvé
  {
    printf("Ce produit n'est pas en stock \n");
  }
  //fermer le fichier
  fclose(fp);
}
void afficherstockfaible(char *fichier)
{
  //ouvrir le fichier en mode lecture
  FILE *fp = fopen(fichier, "r");
  if (fp == NULL)
  {
    //si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", fichier);
    exit(6);
  }
  char produits[5][MAX];
  char ligne[MAX];
  int quantites[5];
  for (int i = 0; i < 5; i++)//initialiser les valeurs du tableau de quantités 
  {
    quantites[i] = MAX;
  }
  while (fgets(ligne, sizeof(ligne), fp))
  {
    Produit prod;
    sscanf(ligne, "%s %d %d %f %d", prod.produit, &prod.ref, &prod.quantite, &prod.prix, &prod.taille);
    if (prod.quantite < quantites[4] && prod.quantite > 0) 
    {
      int i = 4;
      while (prod.quantite < quantites[i-1] && i >0)
      {
        quantites[i] = quantites[i-1];
        strcpy(produits[i], produits[i-1]);
        i--;
      }
      quantites[i] = prod.quantite;
      strcpy(produits[i], ligne);
    }
  }
  printf("5 produits avec le stock le plus faible :\n");
  for (int i = 0; i < 5; i++)//une boucle pour afficher les produits avec les faibles stocks
  {
    if (quantites[i] != MAX)
    {
      Produit prod;
      sscanf(produits[i],"%s %d %d %f %d ", prod.produit,&prod.ref,&prod.quantite,&prod.prix,&prod.taille);
      printf("Nom: %s Reference: %d Stock: %d Prix: %f Taille: %d \n", prod.produit,prod.ref,prod.quantite,prod.prix,prod.taille);
    }
  }
  //fermer le fichier
  fclose(fp);
}
int main()
{
  int identifiant;
  int i;
  i=3;
  int a ;
  a=0;
  char nom[MAX];
  int ref;
  ref=0;
  int choix;
  choix=0;
  printf("Veuillez saisir votre identifiant.\n");
  scanf("%d", &identifiant);
  while (i != 0 && choix==0)
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
      choix++;
      printf("MODE GESTION : \n");
      afficherstockepuise("produit.txt");
      afficherstockfaible("produit.txt");
      gererstock("produit.txt");
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
        cherchernomproduit("produit.txt", nom);
      }
      else if (a == 2)
      {
        printf("Saisir la reference de votre produit \n");
        scanf("%d", &ref);
        chercherrefproduit("produit.txt", ref);
      }
      else if (a == 3)
      {
        int reference;
        reference=0;
        int quant;
        quant=0;
        int n;
        n=0;
        printf("Voulez vous: \n");
        printf("1.Augmenter le stock ? \n");
        printf("2.Reduire le stock ? \n");
        scanf("%d", &n);
        if (n == 1)
        {
          printf("Veuillez saisir la reference du produit que vous voulez augmenter en stock: ");
          scanf("%d", &reference);
          printf("\n");
          printf("Veuilliez saisir la quantite a ajouter en stock: ");
          scanf("%d", &quant);
          printf("\n");
          modifierstock("produit.txt", reference, quant);
        }
        else if (n == 2)
        {
          printf("Veuillez saisir la reference du produit que vous voulez reduire en stock en stock: ");
          scanf("%d", &reference);
          printf("\n");
          printf("Veuilliez saisir la quantite a reduire en stock: ");
          scanf("%d", &quant);
          printf("\n");
          modifierstock("produit.txt", reference, -quant);
          
        }
        else
        {
          printf("Erreur: veuillez saisir soi 1 soi 2. \n");
        }
      }
      else if (a == 4)
      {
        ajouterproduit("produit.txt");
      }
      else if (a == 5)
      {
        printf("Merci pour votre visite ! \n");
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
while(i!=0 && choix!=0 && (identifiant == 123321 || identifiant == 987789)){
      printf("Souhaitez vous faire autre chose ?\n");
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
        cherchernomproduit("produit.txt", nom);
      }
      else if (a == 2)
      {
        printf("Saisir la reference de votre produit \n");
        scanf("%d", &ref);
        chercherrefproduit("produit.txt", ref);
      }
      else if (a == 3)
      {
        int reference;
        reference=0;
        int quant;
        quant=0;
        int n;
        n=0;
        printf("Voulez vous: \n");
        printf("1.Augmenter le stock ? \n");
        printf("2.Reduire le stock ? \n");
        scanf("%d", &n);
        if (n == 1)
        {
          printf("Veuillez saisir la reference du produit que vous voulez augmenter en stock: ");
          scanf("%d", &reference);
          printf("\n");
          printf("Veuilliez saisir la quantite a ajouter en stock: ");
          scanf("%d", &quant);
          printf("\n");
          modifierstock("produit.txt", reference, quant);
        }
        else if (n == 2)
        {
          printf("Veuillez saisir la reference du produit que vous voulez reduire en stock en stock: ");
          scanf("%d", &reference);
          printf("\n");
          printf("Veuilliez saisir la quantite a reduire en stock: ");
          scanf("%d", &quant);
          printf("\n");
          modifierstock("produit.txt", reference, -quant);
        }
        else
        {
          printf("Erreur: veuillez saisir soi 1 soi 2. \n");
        }
      }
      else if (a == 4)
      {
        ajouterproduit("produit.txt");
      }
      else if (a == 5)
      {
        printf("Merci pour votre visite ! \n");
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
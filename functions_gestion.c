#include"gestion.h"
void ajouterproduit();
void modifierstock();
void afficherstock();
void afficherstockepuise();
void chercherrefproduit();
void cherchernomproduit();
void afficherstockfaible();
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
  // définir les informations du produit
  char produit[MAX];
  int ref;
  int quantite;
  float prix;
  int taille;
  // demander les informations du produit à l'utilisateur
  printf("Veuillez saisir le nom du produit :\n");
  scanf("%s", produit);
  printf("Veuillez saisir la reference du produit :\n");
  scanf("%d", &ref);
  printf("Veuillez saisir la quantite en stock :\n");
  scanf("%d", &quantite);
  printf("Veuillez saisir le prix du produit :\n");
  scanf("%f", &prix);
  printf("Veuillez saisir la taille du produit :\n");
  scanf("%d", &taille);
  // ajouter au fichier le nouveau produit
  fprintf(fp, "\n%s %d %d %f %d", produit, ref, quantite, prix, taille);
  //fermer le fichier
  fclose(fp);
  printf("Ce produit a ete ajoute avec succes.\n");
}
// une fonction pour modifier le stock d'un produit(soi l'augmenter ou le réduire)
void modifierstock(char *fichier, int reference, int quant)
{
  //ouvrir le fichier principal en mode lecture
  FILE *fp = fopen(fichier, "r");
  //créer un fichier temporaire en mode lecture
  FILE *tempor = fopen("temporaire.txt", "w");
  if (fp == NULL || tempor == NULL)//tester si le fichier s'ouvre correctement ou pas
  {
     //si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", fichier);
    exit(2);
  }
  char ligne[MAX];
  int trouve = 0;
  //lire le fichier ligne par ligne
  while (fgets(ligne, sizeof(ligne), fp))
  {
    char produit[MAX];
    int ref;
    int quantite;
    float prix;
    int taille;
    // lire les informations du produit dans le fichier
    sscanf(ligne, "%s %d %d %f %d", produit, &ref, &quantite, &prix, &taille);
    if (reference == ref)//voir si la réference du produit est la même que celle recherchée
    {
      // modifier la quantité du produit
      quantite = quant + quantite;
      trouve = 1;
    }
    // ajouter chaque ligne dans le fichier temporaraire
    fprintf(tempor, "%s %d %d %f %d \n", produit, ref, quantite, prix, taille);
  }
  // fermer le fichier principal 
  fclose(fp);
  //fermer le fichier temporaire
  fclose(tempor);
  //supprimer le fichier principal
  remove(fichier);
  //renommer le fichier principal avec le nom du fichier principal
  rename("temporaire.txt", fichier);
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
  int stockepuise = 0;
  printf("Produits avec un stock epuise :\n");
  //lire le fichier ligne par ligne
  while (fgets(ligne, sizeof(ligne), fp))
  {
    char produit[MAX];
    int ref;
    int quantite;
    float prix;
    int taille;
    sscanf(ligne, "%s %d %d %f %d", produit, &ref, &quantite, &prix, &taille);
    if (quantite == 0)//si la quantité du produit est égale à 0
    {
      //afficher toutes les informations du produit avec le stock à 0
      printf("Nom: %s Reference: %d Stock: %d Prix: %f Taille: %d \n", produit, ref, quantite, prix, taille);
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
    if (ref == num)//si la réference d'un produit est la même que la réference saisie par l'utilisateur
    {
      //afficher toutes les informations du produit
      printf("Le produit de reference '%d' a ete trouve en stock \n", num);
      printf("Voici ses informations : \n");
      printf("Nom: %s Reference: %d Stock: %d Prix: %f Taille: %d \n", produit, ref, quantite, prix, taille);
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
  char ligne[MAX];
  int num_ligne = 0;
  int trouve = 0;
  char produit[MAX];
  int ref = 0;
  int quantite = 0;
  float prix = 0;
  int taille = 0;
  while (fgets(ligne, MAX, fp) != NULL)
  {
    num_ligne++;
    //définir un pointeur sur la ligne
    char *ptr_ligne = ligne;
    //définir un pointeur sur le nom du produit
    char *ptr_mot = mot;
    while (*ptr_ligne != 0)//parcourir caractére par caractére de la ligne
    {
      sscanf(ligne, "%s %d %d %f %d", produit, &ref, &quantite, &prix, &taille);
      if (tolower(*ptr_ligne) == tolower(*ptr_mot))//si le caractére de la ligne et celui du nom sont les mêmes
      {
        //avancer d'un caractére dans la ligne et dans le nom
        ptr_ligne++;
        ptr_mot++;
        if (*ptr_mot == '\0' && *ptr_ligne == ' ')//si c'est la fin du nom de produit et le caractére suivant dans la ligne est un espace
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
        //avancer au prochain caractére de la ligne
        ptr_ligne++;
        //reinitialiser le pointeur du nom de produit
        ptr_mot = mot;
      }
    }
    if (trouve == 1)
    {
      break;
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
  char ligne[MAX];
  char produits[5][MAX];
  int quantites[5];
  for (int i = 0; i < 5; i++)//initialiser les valeurs du tableau de quantités 
  {
    quantites[i] = MAX;
  }
  while (fgets(ligne, sizeof(ligne), fp))
  {
    char produit[MAX];
    int ref = 0;
    int quantite = 0;
    float prix = 0;
    int taille = 0;
    sscanf(ligne, "%s %d %d %f %d", produit, &ref, &quantite, &prix, &taille);
    if (quantite > 0 && quantite < quantites[4]) 
    {
      int i = 4;
      while (i > 0 && quantite < quantites[i - 1])
      {
        quantites[i] = quantites[i - 1];
        strcpy(produits[i], produits[i - 1]);
        i--;
      }
      quantites[i] = quantite;
      strcpy(produits[i], ligne);
    }
  }
  printf("Les produits avec le stock le plus faible :\n");
  for (int i = 0; i < 5; i++)
  {
    if (quantites[i] != MAX)
    {
      printf("%s", produits[i]);
    }
  }
  fclose(fp);
}
int gestion(int n)
{
  int identifiant;
  int i = 3;
  int a = 0;
  char nom[MAX];
  int ref = 0;
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
      afficherstockfaible("produit.txt");
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
        cherchernomproduit("produit.txt", nom);
        return 0;
      }
      else if (a == 2)
      {
        printf("Saisir la reference de votre produit \n");
        scanf("%d", &ref);
        chercherrefproduit("produit.txt", ref);
        return 0;
      }
      else if (a == 3)
      {
        int reference = 0;
        int quant = 0;
        int n = 0;
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
          return 0;
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
          return 0;
        }
        else
        {
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
  return 0;
}
#include "gestion.h"
#include "main.h"
// définir les fonctions qu'on va utiliser
int managestock();
int addproduct();
void modifystock();
void outofstock();
int searchrefproduct();
void searchnameproduct();
void lowstock();
int management();
void displaystock();
int scanint();
float scanfloat();
int searchsizeproduct();
// définir une structure de produits
typedef struct
{
  char name[MAX];
  int reference;
  int quantity;
  float price;
  int size;
} Product;
// une fonction pour afficher des produits en utilisant leur taille
int searchsizeproduct(char *file, int number)
{
  // ouvrir le fichier en mode lecture
  FILE *fp = fopen(file, "r");
  if (fp == NULL)
  {
    // si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", fp);
    exit(1);
  }
  int found;
  found = 0;
  char line[MAX];
  printf("Les produits avec la taille %d sont : \n", number);
  while (fgets(line, sizeof(line), fp))
  {
    Product prod;
    sscanf(line, "%s %d %d %f %d", prod.name, &prod.reference, &prod.quantity, &prod.price, &prod.size);
    if (prod.size == number) // si la taille d'un produit est la même que la taille saisie par l'utilisateur
    {
      // afficher toutes les informations du produit
      printf("Nom: %s Reference: %d Stock: %d Prix: %.02f Taille: %d \n", prod.name, prod.reference, prod.quantity, prod.price, prod.size);
      found = 1;
    }
  }
  if (found == 0) // si aucune réference des produits n'est la même que celle saisie par l'utilisateur
  {
    printf("Il n'y a aucun produit de taille %d.\n", number);
    fclose(fp);
    return 0;
  }
  printf("\n");
  // fermer le fichier
  fclose(fp);
}
// une fonction pour verifier le retour du scanf d'un int
int scanint(char *input)
{
  int a = scanf("%s", input);
  while (!isdigit(input[0])) // voir si le premier caractere de la cdc est un chiffre
  {
    printf("Veuillez resaisir votre nombre : ");
    scanf("%s", input);
  }
  return atoi(input); // changer la cdc en int
}
// une fonction pour tester le retour d'un scanf d'un float
float scanfloat(char *input)
{
  scanf("%s", input);
  char *ptr;
  float number = strtof(input, &ptr); // convertir la chaine de caractere en float
  while (*ptr != '\0')
  {
    printf("Veuillez resaisir un nombre : ");
    scanf("%s", input);
    number = strtof(input, &ptr);
  }
  return number;
}
// une fonction pour gérer le stock(le calculer)
int managestock(char *file)
{
  FILE *fp = fopen(file, "r");
  if (fp == NULL)
  {
    printf("Erreur en ouvrant fichier %s \n", file);
    exit(1);
  }
  char line[MAX];
  int q;
  q = 0;
  while (fgets(line, sizeof(line), fp))
  {
    Product prod;
    sscanf(line, "%s %d %d %f %d", prod.name, &prod.reference, &prod.quantity, &prod.price, &prod.size);
    q = q + (prod.quantity * prod.size); // faire la somme de la quantité pour savoir si on a depassé le max stock ou pas
  }
  fclose(fp);
  return q;
}
// une fonction pour ajouter des produits au stock
int addproduct(char *file)
{
  // ouvrir le fichier en mode écriture et lecture
  FILE *fp = fopen(file, "a+");
  char line[MAX];
  if (fp == NULL) // tester si le fichier s'ouvre correctement ou pas
  {
    // si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", file);
    exit(2);
  }
  // définir le produit
  Product prod1;
  char input[MAX];
  // demander les informations du produit à l'utilisateur
  printf("Saisir le nom de votre produit::\n");
  scanf("%s", prod1.name);
  printf("Saisir la reference de votre produit:\n");
  prod1.reference = scanint(input);
  while (fgets(line, sizeof(line), fp)) // une boucle pour voir si la réference saisie par l'utilisateur existe deja dans le fichier
  {
    Product prod;
    sscanf(line, "%s %d %d %f %d", prod.name, &prod.reference, &prod.quantity, &prod.price, &prod.size);
    if (prod.reference == prod1.reference) // si la réference d'un produit est la même que la réference saisie par l'utilisateur
    {
      printf("Erreur : cette reference existe deja dans le magasin \n");
      printf("Impossible d'ajouter ce produit \n");
      fclose(fp);
      return 0;
    }
  }
  int try = 2;
  while (prod1.reference < 1000 || prod1.reference > 10000 && try != 0) // une boucle pour redemander à l'utilisateur de saisir la resaisir si celle saisie avant est incorrect
  {
    printf("Veuillez resaisir la reference de votre produit : ");
    prod1.reference = scanint(input);
    printf("\n");
    try--;
  }
  if (try == 0) // si l'utilisateur n'a pas saisie la bonne information apres plusieurs tentatives
  {
    printf("La reference saisie est incorrect \n");
    fclose(fp);
    return 0;
  }
  printf("Saisir la quantite de votre produit : ");
  prod1.quantity = scanint(input);
  printf("\n");
  while (prod1.quantity < 0 && try != 0) // une boucle pour redemander à l'utilisateur de saisir la quantité si celle saisie avant est incorrect
  {
    printf("Veuillez resaisir la quantite de votre produit(>0): \n");
    prod1.quantity = scanint(input);
    try--;
  }
  if (try == 0)
  {
    printf("La quantite saisie est incorrect \n"); // si l'utilisateur n'a pas saisie la bonne information apres plusieurs tentatives
    fclose(fp);
    return 0;
  }
  try = 2;
  printf("Saisir le prix de votre produit:\n");
  prod1.price = scanfloat(input);
  while (prod1.price < 0 && try != 0) // de même
  {
    printf("Veuillez resaisir le prix de votre produit(>0): \n");
    prod1.price = scanfloat(input);
    try--;
  }
  if (try == 0)
  {
    printf("Le prix saisi est incorrect \n");
    fclose(fp);
    return 0;
  }
  try = 2;
  printf("Saisir la taille de votre produit:\n");
  prod1.size = scanint(input);
  while (prod1.size != 1 && prod1.size != 2 && prod1.size != 3 && try != 0) // de même
  {
    printf("Veuillez resaisir la taille de votre produit(1,2 ou 3): \n");
    prod1.size = scanint(input);
    try--;
  }
  if (try == 0)
  {
    printf("La taille saisie est incorrect \n");
    fclose(fp);
    return 0;
  }
  int q;
  q = managestock(file) + prod1.size * prod1.quantity;
  if (q > MAX_STOCK) // voir si l'utilisateur a dépassé la quantité autorisée du stock
  {
    printf("Le produit n'a pas ete ajoute.\nVous n'avez pas de place dans votre magasin.\n");
  }
  else if (q < 0)
  {
    printf("Le produit n'a pas ete ajoute.\nVous ne pouvez pas avoir un stock negatif.\n");
  }
  else if (q >= 0 && q <= MAX_STOCK)
  {
    // ajouter au fichier le nouveau produit
    fprintf(fp, "\n%s %d %d %f %d", prod1.name, prod1.reference, prod1.quantity, prod1.price, prod1.size);
  }
  // fermer le fichier
  fclose(fp);
  printf("\nLe produit a ete bien ajoute.\n");
  return 0;
}
// une fonction pour modifier le stock d'un produit(soi l'augmenter ou le réduire)
void modifystock(char *file, int ref, int quant)
{
  // ouvrir le fichier principal en mode lecture
  FILE *fp = fopen(file, "r");
  // créer un fichier temporaire en mode ecriture
  FILE *tempor = fopen("temporary.txt", "w");
  if (tempor == NULL || fp == NULL) // tester si le fichier s'ouvre correctement ou pas
  {
    // si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur ouvrant le fichier %s \n", file);
    exit(3);
  }
  int found;
  found = 0;
  char line[MAX];
  // lire le fichier ligne par ligne
  while (fgets(line, sizeof(line), fp))
  {
    Product prod;
    // lire les informations du produit dans le fichier
    sscanf(line, "%s %d %d %f %d", prod.name, &prod.reference, &prod.quantity, &prod.price, &prod.size);
    if (ref == prod.reference) // voir si la réference du produit est la même que celle recherchée
    {
      if (prod.quantity + quant >= 0)
      {
        int q = 0;
        q = managestock(file) + (quant * prod.size);
        if (q >= 0 && q <= MAX_STOCK)
        {
          // modifier la quantité du produit
          prod.quantity = quant + prod.quantity;
          found = 1;
        }
        else if (q > MAX_STOCK) // voir si la limite de stock a été depassé ou pas
        {
          printf("Vous n'avez pas de place dans votre magasin pour ajouter une telle quantite.\n");
          found = 3;
        }
        else if (q < 0)
        {
          printf("Vous ne pouvez pas reduire le stock de cette quantite.\n");
          found = 3;
        }
      }
      else if (prod.quantity + quant < 0) // voir si la quantité est négatif
      {
        printf("Vous ne pouvez pas reduire le stock d'une telle quantite \n");
        found = 3;
      }
    }
    // ajouter chaque ligne dans le fichier temporaraire
    fprintf(tempor, "%s %d %d %f %d \n", prod.name, prod.reference, prod.quantity, prod.price, prod.size);
  }
  // fermer le fichier principal
  fclose(fp);
  // fermer le fichier temporaire
  fclose(tempor);
  // supprimer le fichier principal
  remove(file);
  // renommer le fichier temporaire avec le nom du fichier principal
  rename("temporary.txt", file);
  if (found == 1)
  // si le produit a été trouvé et modifié, ce message sera affiché
  {
    printf("Le stock a ete modifie. \n");
  }
  else if (found == 0)
  // si le produit n'a pas été trouvé et modifié, ce message sera affiché
  {
    printf("Ce produit est indisponible.\n");
  }
  printf("\n");
}
// une fonction pour afficher les produits avec 0 en stock
void outofstock(char *file)
{
  // ouvrir le fichier en mode lecture
  FILE *fp = fopen(file, "r");
  if (fp == NULL) // tester si le fichier s'ouvre correctement ou pas
  {
    // si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", file);
    exit(4);
  }
  char line[MAX];
  int nostock;
  nostock = 0;
  printf("Produits en rupture de stock :\n");
  // lire le fichier ligne par ligne
  while (fgets(line, sizeof(line), fp))
  {
    Product prod;
    sscanf(line, "%s %d %d %f %d", prod.name, &prod.reference, &prod.quantity, &prod.price, &prod.size);
    if (prod.quantity == 0) // si la quantité du produit est égale à 0
    {
      // afficher toutes les informations du produit avec le stock à 0
      printf("Nom: %s Reference: %d Stock: %d Prix: %.02f Taille: %d \n", prod.name, prod.reference, prod.quantity, prod.price, prod.size);
      nostock = 1;
    }
  }
  if (nostock == 0) // si aucun produit n'as un stock à 0
  {
    printf("Il n'y a aucun produit en rupture de stock.\n");
  }
  printf("\n");
  // fermer le fichier
  fclose(fp);
}
// une fonction pour afficher un produit à partir de sa réference
int searchrefproduct(char *file, int number)
{
  // ouvrir le fichier en mode lecture
  FILE *fp = fopen(file, "r");
  if (fp == NULL)
  {
    // si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", fp);
    exit(5);
  }
  int found;
  found = 0;
  char line[MAX];
  while (fgets(line, sizeof(line), fp))
  {
    Product prod;
    sscanf(line, "%s %d %d %f %d", prod.name, &prod.reference, &prod.quantity, &prod.price, &prod.size);
    if (prod.reference == number) // si la réference d'un produit est la même que la réference saisie par l'utilisateur
    {
      // afficher toutes les informations du produit
      printf("Le produit avec la reference '%d' a ete trouve en stock.\nVoici ses informations :\n", number);
      printf("Nom: %s Reference: %d Stock: %d Prix: %.02f Taille: %d \n", prod.name, prod.reference, prod.quantity, prod.price, prod.size);
      printf("\n");
      found = 1;
      fclose(fp);
      return 1;
      break;
    }
  }
  if (found == 0) // si aucune réference des produits n'est la même que celle saisie par l'utilisateur
  {
    printf("Ce produit est indisponible.\n");
    fclose(fp);
    return 0;
  }
  printf("\n");
  // fermer le fichier
  fclose(fp);
}
// une fonction pour afficher un produit à partir de son nom
void searchnameproduct(char *file, char *word)
{
  // ouvrir le fichier en mode lecture
  FILE *fp = fopen(file, "r");
  if (fp == NULL)
  {
    // si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", fp);
    exit(6);
  }
  int found;
  found = 0;
  char line[MAX];
  Product prod;
  while (fgets(line, MAX, fp) != NULL)
  {
    // définir un pointeur sur la ligne
    char *ptr_line = line;
    // définir un pointeur sur le nom du produit
    char *ptr_word = word;
    while (*ptr_line != 0) // parcourir caractére par caractére de la ligne
    {
      sscanf(line, "%s %d %d %f %d", prod.name, &prod.reference, &prod.quantity, &prod.price, &prod.size);
      if (tolower(*ptr_line) == tolower(*ptr_word)) // si le caractére de la ligne et celui du nom sont les mêmes
      {
        // avancer d'un caractére dans la ligne et dans le nom
        ptr_word++;
        ptr_line++;
        if (*ptr_word == '\0' && *ptr_line == ' ') // si c'est la fin du nom de produit et le caractére suivant dans la ligne est un espace
        {
          printf("Le produit '%s' a ete trouve en stock.\nVoici ses informations : \n", word);
          printf("Nom: %s Reference: %d Stock: %d Prix: %.02f Taille: %d \n", prod.name, prod.reference, prod.quantity, prod.price, prod.size);
          printf("\n");
          found = 1;
          break;
        }
      }
      else
      {
        // avancer au prochain caractére
        ptr_line++;
        // reinitialiser le pointeur du nom de produit
        ptr_word = word;
      }
    }
  }
  if (found == 0) // si le produit n'as pas été trouvé
  {
    printf("Ce produit est indisponible.\n");
  }
  printf("\n");
  // fermer le fichier
  fclose(fp);
}
void lowstock(char *file)
{
  // ouvrir le fichier en mode lecture
  FILE *fp = fopen(file, "r");
  if (fp == NULL)
  {
    // si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", file);
    exit(7);
  }
  char products[5][MAX];
  char line[MAX];
  int quantities[5];
  for (int i = 0; i < 5; i++) // initialiser les valeurs du tableau de quantités
  {
    quantities[i] = MAX;
  }
  while (fgets(line, sizeof(line), fp))
  {
    Product prod;
    sscanf(line, "%s %d %d %f %d", prod.name, &prod.reference, &prod.quantity, &prod.price, &prod.size);
    if (prod.quantity < quantities[4] && prod.quantity > 0) // voir si la quantite est inferieur à la quantite finale du tableau
    {
      int i = 4;
      while (prod.quantity < quantities[i - 1] && i > 0)
      {
        quantities[i] = quantities[i - 1];    // changer la valeur de la quantite par celle d'avant
        strcpy(products[i], products[i - 1]); // copier la ligne du produit dans la ligne d'avant
        i--;
      }
      // inserer les quantités et produits à la position correcte
      quantities[i] = prod.quantity;
      strcpy(products[i], line);
    }
  }
  printf("5 produits avec le stock le plus faible:\n");
  for (int i = 0; i < 5; i++) // une boucle pour afficher les produits avec les faibles stocks
  {
    if (quantities[i] != MAX)
    {
      Product prod;
      sscanf(products[i], "%s %d %d %f %d ", prod.name, &prod.reference, &prod.quantity, &prod.price, &prod.size);
      printf("Nom: %s Reference: %d Stock: %d Prix: %.02f Taille: %d \n", prod.name, prod.reference, prod.quantity, prod.price, prod.size);
    }
  }
  printf("\n");
  // fermer le fichier
  fclose(fp);
}
// une fonction pour afficher tous les produits du magasin
void displaystock(char *file)
{
  FILE *fp = fopen(file, "r");
  if (fp == NULL)
  {
    printf("Erreur en ouvrant le fichier %s \n", file);
    exit(1);
  }
  char line[MAX];
  while (fgets(line, sizeof(line), fp)) // parcourir tout le fichier
  {
    Product prod;
    sscanf(line, "%s %d %d %f %d ", prod.name, &prod.reference, &prod.quantity, &prod.price, &prod.size);
    printf("Nom:%s Reference:%d Quantite:%d Prix:%.02f Taille : %d \n", prod.name, prod.reference, prod.quantity, prod.price, prod.size);
  }
  printf("\n");
  fclose(fp);
}
int management(int n)
{
  // declaration des variables qu'on va utiliser
  int identifier;
  char input[MAX];
  identifier = 0;
  int i;
  i = 2;
  int a;
  a = 0;
  char name[MAX];
  int ref;
  ref = 10;
  int choice;
  choice = 0;
  printf("Veuillez entrer votre ID.\n"); // demander à l'utilisateur de saisir l'ID gestionnnaire
  identifier = scanint(input);
  while (i != 0 && choice == 0)
  {
    if (identifier != 123321 && identifier != 987789) // si la reference est incorrecte, donner à l'utilisteur la possibilité de la resaisir
    {
      printf("ID non reconnue.\n");
      printf("Vous avez %d tentatives restantes.\nVeuillez resaisir votre ID.\n", i);
      identifier = scanint(input);
      i--;
    }
    else if (identifier == 123321 || identifier == 987789)
    {
      choice++;
      printf("MODE GESTION : \n");
      outofstock("produit.txt");  // afficher automatiquement les produits en rupture de stock
      lowstock("produit.txt");    // afficher les 5 produits avec le stock le plus faible
      printf("Voulez vous : \n"); // donner le choix à l'utilisateur de faire l'une des actions suivantes
      printf("1.Chercher un produit en utilisant son nom ?\n");
      printf("2.Chercher un produit en utilisant sa reference ?\n");
      printf("3.Modifier le stock d'un produit ?\n");
      printf("4.Ajouter un produit au stock ?\n");
      printf("5.Afficher tous les produits ? \n");
      printf("6.Afficher des produits de la meme taille ?\n");
      printf("7.Changer de mode ? \n");
      printf("8.Quitter le programme ? \n");
      printf("Votre choix : ");
      a = scanint(input);
      printf("\n");
      if (a == 1)
      {
        printf("Entrer le nom du produit : ");
        scanf("%s", name);
        printf("\n");
        searchnameproduct("produit.txt", name);
      }
      else if (a == 2)
      {
        int try = 2;
        printf("Entrer la reference du produit (comprise entre 1000 et 10000): ");
        while (try > 0) // donner la possibilité de resaisir la reference
        {
          if ((ref = scanint(input))) // saisir la reference
          {
            printf("\n");
            if (ref >= 1000 && ref <= 10000)
            {
              searchrefproduct("produit.txt", ref);
              break;
            }
            else if (ref < 1000 || ref > 10000) // demander à l'utilisateur de la resaisir
            {
              printf("Veuillez resaisir la reference \n");
              try--;
            }
          }
        }
        if (try == 0) // si l'utilisateur n'a pas saisie la bonne information apres plusieurs tentatives
        {
          printf("La reference est incorrect.\n");
          return 0;
        }
      }
      else if (a == 3)
      {
        int try = 2;
        int reference;
        reference = 0;
        int quant;
        quant = 0;
        int n;
        n = 0;
        printf("Voulez vous : \n");
        printf("1.Augmenter le stock ? \n");
        printf("2.Reduire le stock ? \n");
        n = scanint(input);
        if (n == 1)
        {
          printf("Entrer la reference du produit (comprise entre 1000 et 10000): ");
          while (try > 0)
          {
            if ((reference = scanint(input)))
            {
              printf("\n");
              if (reference >= 1000 && reference <= 10000)
              {
                int i = searchrefproduct("produit.txt", reference); // chercher si le produit existe ou pas
                if (i == 0)                                         // si le produit d'une telle reference n'existe pas
                {
                  printf("Veuillez resaisir la reference \n");
                  try--;
                }
                else if (i == 1) // si le produit existe, demander la quantité à modifier
                {
                  break;
                }
              }
            }
            else
            {
              printf("Veuillez resaisir la reference : ");
              try--;
            }
          }
          if (try == 0)
          {
            printf("La reference est incorrect.\n"); // si l'utilisateur n'a pas saisie la bonne information apres plusieurs tentatives
            return 0;
          }
          printf("\n");
          try = 2;
          printf("Veuillez entrer la quantite a ajouter au stock (>0) : ");
          while (try > 0)
          {
            if ((quant = scanint(input)))
            {
              printf("\n");
              if (quant > 0)
                break;
            }
            printf("Veuillez resaisir la quantite : ");
            try--;
          }
          if (try == 0)
          {
            printf("La quantite est incorrect.\n");
            return 0;
          }
          printf("\n");
          modifystock("produit.txt", reference, quant);
        }
        else if (n == 2) // comme le cas de l'augmentation du stock
        {
          try = 2;
          printf("Entrer la reference du produit (comprise entre 1000 et 10000): ");
          while (try > 0)
          {
            if ((reference = scanint(input)))
            {
              printf("\n");
              if (reference >= 1000 && reference <= 10000)
              {
                int i = searchrefproduct("produit.txt", reference);
                if (i == 0)
                {
                  printf("Veuillez resaisir la reference : ");
                  try--;
                }
                else if (i == 1)
                {
                  break;
                }
              }
            }
            else
            {
              printf("Veuillez resaisir la reference : ");
              try--;
            }
          }
          if (try == 0)
          {
            printf("La reference est incorrect.\n");
            return 0;
          }
          printf("\n");
          try = 2;
          printf("Veuillez entrer la quantite a reduire dans le stock (>0): ");
          while (try > 0)
          {
            if ((quant = scanint(input)))
            {
              printf("\n");
              if (quant > 0)
                break;
            }
            printf("Veuillez resaisir la quantite : ");
            scanf("%d", &quant);
            try--;
          }
          if (try == 0)
          {
            printf("La quantite est incorrect.\n");
            return 0;
          }
          printf("\n");
          modifystock("produit.txt", reference, -quant);
        }
        else
        {
          printf("Erreur : veuillez saisir soi 1 soi 2. \n");
        }
      }
      else if (a == 4)
      {
        addproduct("produit.txt");
      }
      else if (a == 5)
      {
        displaystock("produit.txt");
      }
      else if (a == 6)
      {
        printf("Veuillez saisir la taille : \n");
        printf("1 pour petit, 2 pour moyen et 3 pour grand. \n");
        printf("Votre choix : ");
        int number = scanint(input);
        searchsizeproduct("produit.txt", number);
      }
      else if (a == 7)
      {
        main_menu();
      }
      else if (a == 8)
      {
        printf("Merci pour votre visite ! \n");
        return 0;
      }
      else
      {
        printf("Erreur : veuillez choisir un nombre entre 1 et 8. \n");
      }
    }
  }
  if (i == 0) // si l'utilisateur n'a pas saisie la bonne information apres plusieurs tentatives
  {
    printf("Votre ID est incorrect ou n'est pas enregistre dans le systeme.\nPour plus d'informations, veuillez consulter votre manager.\n");
    return 0;
  }
  while (i != 0 && choice != 0 && (identifier == 123321 || identifier == 987789)) // comme la premiere boucle de la fonction management
  {
    printf("Voulez vous faire autre chose ?\n");
    printf("1.Chercher un produit en utilisant son nom ?\n");
    printf("2.Chercher un produit en utilisant sa reference ?\n");
    printf("3.Modifier le stock d'un produit ?\n");
    printf("4.Ajouter un produit au stock ?\n");
    printf("5.Afficher tous les produits ? \n");
    printf("6.Afficher des produits de la meme taille ?\n");
    printf("7.Changer de mode ? \n");
    printf("8.Quitter le programme ? \n");
    printf("Votre choix : ");
    a = scanint(input);
    printf("\n");
    if (a == 1)
    {
      printf("Entrer le nom du produit : ");
      scanf("%s", name);
      printf("\n");
      searchnameproduct("produit.txt", name);
    }
    else if (a == 2)
    {
      int try = 2;
      printf("Entrer la reference du produit (comprise entre 1000 et 10000): ");
      while (try > 0) // donner la possibilité de resaisir la reference
      {
        if ((ref = scanint(input))) // saisir la reference
        {
          printf("\n");
          if (ref >= 1000 && ref <= 10000)
          {
            searchrefproduct("produit.txt", ref);
            break;
          }
          else if (ref < 1000 || ref > 10000) // demander à l'utilisateur de la resaisir
          {
            printf("Veuillez resaisir la reference \n");
            try--;
          }
        }
      }
      if (try == 0) // si l'utilisateur n'a pas saisie la bonne information apres plusieurs tentatives
      {
        printf("La reference est incorrect.\n");
        return 0;
      }
    }
    else if (a == 3)
    {
      int try = 2;
      int reference;
      reference = 0;
      int quant;
      quant = 0;
      int n;
      n = 0;
      printf("Voulez vous : \n");
      printf("1.Augmenter le stock ? \n");
      printf("2.Reduire le stock ? \n");
      n = scanint(input);
      if (n == 1)
      {
        printf("Entrer la reference du produit (comprise entre 1000 et 10000): ");
        while (try > 0)
        {
          if ((reference = scanint(input)))
          {
            printf("\n");
            if (reference >= 1000 && reference <= 10000)
            {
              int i = searchrefproduct("produit.txt", reference); // chercher si le produit existe ou pas
              if (i == 0)                                         // si le produit d'une telle reference n'existe pas
              {
                printf("Veuillez resaisir la reference \n");
                try--;
              }
              else if (i == 1) // si le produit existe, demander la quantité à modifier
              {
                break;
              }
            }
          }
          else
          {
            printf("Veuillez resaisir la reference : ");
            try--;
          }
        }
        if (try == 0)
        {
          printf("La reference est incorrect.\n"); // si l'utilisateur n'a pas saisie la bonne information apres plusieurs tentatives
          return 0;
        }
        printf("\n");
        try = 2;
        printf("Veuillez entrer la quantite a ajouter au stock (>0) : ");
        while (try > 0)
        {
          if ((quant = scanint(input)))
          {
            printf("\n");
            if (quant > 0)
              break;
          }
          printf("Veuillez resaisir la quantite : ");
          try--;
        }
        if (try == 0)
        {
          printf("La quantite est incorrect.\n");
          return 0;
        }
        printf("\n");
        modifystock("produit.txt", reference, quant);
      }
      else if (n == 2) // comme le cas de l'augmentation du stock
      {
        try = 2;
        printf("Entrer la reference du produit (comprise entre 1000 et 10000): ");
        while (try > 0)
        {
          if ((reference = scanint(input)))
          {
            printf("\n");
            if (reference >= 1000 && reference <= 10000)
            {
              int i = searchrefproduct("produit.txt", reference);
              if (i == 0)
              {
                printf("Veuillez resaisir la reference : ");
                try--;
              }
              else if (i == 1)
              {
                break;
              }
            }
          }
          else
          {
            printf("Veuillez resaisir la reference : ");
            try--;
          }
        }
        if (try == 0)
        {
          printf("La reference est incorrect.\n");
          return 0;
        }
        printf("\n");
        try = 2;
        printf("Veuillez entrer la quantite a reduire dans le stock (>0): ");
        while (try > 0)
        {
          if ((quant = scanint(input)))
          {
            printf("\n");
            if (quant > 0)
              break;
          }
          printf("Veuillez resaisir la quantite : ");
          scanf("%d", &quant);
          try--;
        }
        if (try == 0)
        {
          printf("La quantite est incorrect.\n");
          return 0;
        }
        printf("\n");
        modifystock("produit.txt", reference, -quant);
      }
      else
      {
        printf("Erreur : veuillez saisir soi 1 soi 2. \n");
      }
    }
    else if (a == 4)
    {
      addproduct("produit.txt");
    }
    else if (a == 5)
    {
      displaystock("produit.txt");
    }
    else if (a == 6)
    {
      printf("Veuillez saisir la taille : \n");
      printf("1 pour petit, 2 pour moyen et 3 pour grand. \n");
      printf("Votre choix : ");
      int number = scanint(input);
      searchsizeproduct("produit.txt", number);
    }
    else if (a == 7)
    {
      main_menu();
    }
    else if (a == 8)
    {
      printf("Merci pour votre visite ! \n");
      return 0;
    }
    else
    {
      printf("Erreur : veuillez choisir un nombre entre 1 et 8. \n");
    }
  }
}
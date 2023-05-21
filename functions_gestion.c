#include "gestion.h"
// définir les fonctions qu'on va utiliser
int managestock();
void addproduct();
void modifystock();
void outofstock();
void searchrefproduct();
void searchnameproduct();
void lowstock();
int management();
// définir une structure de produits
typedef struct
{
  char name[MAX];
  int reference;
  int quantity;
  float price;
  int size;
} Product;
// une fonction pour gérer le stock(le calculer)
int managestock(char *file)
{
  FILE *fp = fopen(file, "r");
  if (fp == NULL)
  {
    printf("Error opening file %s \n", file);
    exit(1);
  }
  char line[MAX];
  int q;
  q = 0;
  while (fgets(line, sizeof(line), fp))
  {
    Product prod;
    sscanf(line, "%s %d %d %f %d", prod.name, &prod.reference, &prod.quantity, &prod.price, &prod.size);
    q = q + (prod.quantity * prod.size);
  }
  return q;
}
// une fonction pour ajouter des produits au stock
void addproduct(char *file)
{
  // ouvrir le fichier en mode écriture en partant de la fin
  FILE *fp = fopen(file, "a");
  if (fp == NULL) // tester si le fichier s'ouvre correctement ou pas
  {
    // si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Error opening file %s \n", file);
    exit(2);
  }
  // définir le produit
  Product prod;
  // demander les informations du produit à l'utilisateur
  printf("Enter the name of the product:\n");
  scanf("%s", prod.name);
  printf("Enter the reference of the product:\n");
  scanf("%d", &prod.reference);
  printf("Enter the quantity of the product:\n");
  scanf("%d", &prod.quantity);
  while (prod.quantity < 0)
  {
    printf("Please re-enter the quantity of the product\n");
    scanf("%d", &prod.quantity);
  }
  printf("Enter the price of the product:\n");
  scanf("%f", &prod.price);
  while (prod.price < 0)
  {
    printf("Please re-enter the price of the product\n");
    scanf("%d", &prod.price);
  }
  printf("Enter the size of the product:\n");
  scanf("%d", &prod.size);
  while (prod.size != 1 || prod.size != 2 || prod.size != 3)
  {
    printf("Please re-enter the size of the product \n");
    scanf("%d", &prod.size);
  }
  int q;
  q = managestock(file) + prod.size * prod.quantity;
  printf("%d ", q);
  if (q > MAX_STOCK)//voir si l'utilisateur a dépassé la quantité autorisée du stock
  {
    printf("The product wasn't added to your shop\nYou don't have enough place in your stock\n");
  }
  else if (q < 0)
  {
    printf("The product wasn't added to your shop\nYou can't have a negatif stock\n");
  }
  else if (q >= 0 && q <= MAX_STOCK)
  {
    // ajouter au fichier le nouveau produit
    fprintf(fp, "\n%s %d %d %f %d", prod.name, prod.reference, prod.quantity, prod.price, prod.size);
  }
  // fermer le fichier
  fclose(fp);
  printf("The product was added successfully\n");
}
// une fonction pour modifier le stock d'un produit(soi l'augmenter ou le réduire)
void modifystock(char *file, int ref, int quant)
{
  // ouvrir le fichier principal en mode lecture
  FILE *fp = fopen(file, "r");
  // créer un fichier temporaire en mode lecture
  FILE *tempor = fopen("temporary.txt", "w");
  if (tempor == NULL || fp == NULL) // tester si le fichier s'ouvre correctement ou pas
  {
    // si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Error opening file %s \n", file);
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
      int q = 0;
      q = managestock(file) + (quant * prod.size);
      if (q >= 0 && q <= MAX_STOCK)
      {
        // modifier la quantité du produit
        prod.quantity = quant + prod.quantity;
        found = 1;
      }
      else if (q > MAX_STOCK)
      {
        printf("You don't have enough place in your stock to add such quantity\n");
        found = 3;
      }
      else if (q < 0)
      {
        printf("You can't reduce your stock by such quantity \n");
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
    printf("The stock was modified \n");
  }
  else if (found == 0)
  // si le produit n'a pas été trouvé et modifié, ce message sera affiché
  {
    printf("This product isn't available in stock  \n");
  }
}
// une fonction pour afficher les produits avec 0 en stock
void outofstock(char *file)
{
  // ouvrir le fichier en mode lecture
  FILE *fp = fopen(file, "r");
  if (fp == NULL) // tester si le fichier s'ouvre correctement ou pas
  {
    // si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Error opening file %s \n", file);
    exit(4);
  }
  char line[MAX];
  int nostock;
  nostock = 0;
  printf("Products that are out of stock :\n");
  // lire le fichier ligne par ligne
  while (fgets(line, sizeof(line), fp))
  {
    Product prod;
    sscanf(line, "%s %d %d %f %d", prod.name, &prod.reference, &prod.quantity, &prod.price, &prod.size);
    if (prod.quantity == 0) // si la quantité du produit est égale à 0
    {
      // afficher toutes les informations du produit avec le stock à 0
      printf("Name: %s Reference: %d Stock: %d Price: %f Size: %d \n", prod.name, prod.reference, prod.quantity, prod.price, prod.size);
      nostock = 1;
    }
  }
  if (nostock == 0) // si aucun produit n'as un stock à 0
  {
    printf("There is no product out of stock\n");
  }
  // fermer le fichier
  fclose(fp);
}
// une fonction pour afficher un produit à partir de sa réference
void searchrefproduct(char *file, int number)
{
  // ouvrir le fichier en mode lecture
  FILE *fp = fopen(file, "r");
  if (fp == NULL)
  {
    // si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Error opening file %s \n", fp);
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
      printf("The product with the reference '%d' was found in stock\nHere are its informations:\n", number);
      printf("Name: %s Reference: %d Stock: %d Price: %f Size: %d \n", prod.name, prod.reference, prod.quantity, prod.price, prod.size);
      found = 1;
      break;
    }
  }
  if (found == 0) // si aucune réference des produits n'est la même que celle saisie par l'utilisateur
  {
    printf("The product with the reference '%d' wasn't found in stock\n", number);
  }
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
    printf("Error opening file %s \n", fp);
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
          printf("The product '%s' was found in stock \nHere are its informations : \n", word);
          printf("Name: %s Reference: %d Stock: %d Price: %f Size: %d \n", prod.name, prod.reference, prod.quantity, prod.price, prod.size);
          found = 1;
          break;
        }
      }
      else
      {
        // avancer au prochain caractére de la ligne
        ptr_line++;
        // reinitialiser le pointeur du nom de produit
        ptr_word = word;
      }
    }
  }
  if (found == 0) // si le produit n'as pas été trouvé
  {
    printf("This product isn't in stock\n");
  }
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
    printf("Error opening file %s \n", file);
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
    if (prod.quantity < quantities[4] && prod.quantity > 0)
    {
      int i = 4;
      while (prod.quantity < quantities[i - 1] && i > 0)
      {
        quantities[i] = quantities[i - 1];
        strcpy(products[i], products[i - 1]);
        i--;
      }
      quantities[i] = prod.quantity;
      strcpy(products[i], line);
    }
  }
  printf("5 products with the lowest stock:\n");
  for (int i = 0; i < 5; i++) // une boucle pour afficher les produits avec les faibles stocks
  {
    if (quantities[i] != MAX)
    {
      Product prod;
      sscanf(products[i], "%s %d %d %f %d ", prod.name, &prod.reference, &prod.quantity, &prod.price, &prod.size);
      printf("Name: %s Reference: %d Stock: %d Price: %f Size: %d \n", prod.name, prod.reference, prod.quantity, prod.price, prod.size);
    }
  }
  // fermer le fichier
  fclose(fp);
}
int management(int n)
{
  int identifier;
  identifier = 0;
  int i;
  i = 3;
  int a;
  a = 0;
  char name[MAX];
  int ref;
  ref = 0;
  int choice;
  choice = 0;
  printf("Please enter your management ID.\n");
  scanf("%d", &identifier);
  while (i != 0 && choice == 0)
  {
    if (identifier != 123321 && identifier != 987789)
    {
      i--;
      printf("ID not recognized.\n");
      printf("You have %d attempts left.\nPlease re-enter your management ID.\n", i);
      scanf("%d", &identifier);
    }
    else if (identifier == 123321 || identifier == 987789)
    {
      choice++;
      printf("MODE GESTION : \n");
      outofstock("produit.txt");
      lowstock("produit.txt");
      printf("Would you like to :\n");
      printf("1.Search for a product using its name ?\n");
      printf("2.Search for a product using its reference ?\n");
      printf("3.Modify the stock of a product ?\n");
      printf("4.Add a product to stock ?\n");
      printf("5.Leave the management programme ? \n");
      scanf("%d", &a);
      if (a == 1)
      {
        printf("Enter the name of the product \n");
        scanf("%s", name);
        searchnameproduct("produit.txt", name);
      }
      else if (a == 2)
      {
        printf("Enter the reference of the product \n");
        scanf("%d", &ref);
        searchrefproduct("produit.txt", ref);
      }
      else if (a == 3)
      {
        int reference;
        reference = 0;
        int quant;
        quant = 0;
        int n;
        n = 0;
        printf("Would yo like to: \n");
        printf("1.Increase the stock ? \n");
        printf("2.Reduce the stock ? \n");
        scanf("%d", &n);
        if (n == 1)
        {
          printf("Please enter the reference of the product you want to increase in stock: ");
          scanf("%d", &reference);
          printf("\n");
          printf("Please enter the quantity you want to add to stock ");
          scanf("%d", &quant);
          printf("\n");
          modifystock("produit.txt", reference, quant);
        }
        else if (n == 2)
        {
          printf("Please enter the reference of the product you want to reduce in stock: ");
          scanf("%d", &reference);
          printf("\n");
          printf("Please enter the quantity you want to reduce in stock: ");
          scanf("%d", &quant);
          printf("\n");
          modifystock("produit.txt", reference, -quant);
        }
        else
        {
          printf("Error: please enter either 1 or 2. \n");
        }
      }
      else if (a == 4)
      {
        addproduct("produit.txt");
      }
      else if (a == 5)
      {
        printf("Thanks for your visit ! \n");
        return 0;
      }
      else
      {
        printf("Error:please choose a number between 1 and 5. \n");
        return 0;
      }
    }
    if (i == 0)
    {
      printf("Your ID is either uncorrect or not registered in the program.\nFor further information, please check with your manager.\n");
      return 0;
    }
  }
  while (i != 0 && choice != 0 && (identifier == 123321 || identifier == 987789))
  {
    printf("Would you like to do something else ?\n");
    printf("1.Search for a product using its name ?\n");
    printf("2.Search for a product using its reference ?\n");
    printf("3.Modify the stock of a product ?\n");
    printf("4.Add a product to stock ?\n");
    printf("5.Leave the management programme ? \n");
    scanf("%d", &a);
    if (a == 1)
    {
      printf("Enter the name of the product \n");
      scanf("%s", name);
      searchnameproduct("produit.txt", name);
    }
    else if (a == 2)
    {
      printf("Enter the reference of the product \n");
      scanf("%d", &ref);
      searchrefproduct("produit.txt", ref);
    }
    else if (a == 3)
    {
      int reference;
      reference = 0;
      int quant;
      quant = 0;
      int n;
      n = 0;
      printf("Would yo like to: \n");
      printf("1.Increase the stock ? \n");
      printf("2.Reduce the stock ? \n");
      scanf("%d", &n);
      if (n == 1)
      {
        printf("Please enter the reference of the product you want to increase in stock: ");
        scanf("%d", &reference);
        printf("\n");
        printf("Please enter the quantity you want to add to stock ");
        scanf("%d", &quant);
        printf("\n");
        modifystock("produit.txt", reference, quant);
      }
      else if (n == 2)
      {
        printf("Please enter the reference of the product you want to reduce in stock: ");
        scanf("%d", &reference);
        printf("\n");
        printf("Please enter the quantity you want to reduce in stock: ");
        scanf("%d", &quant);
        printf("\n");
        modifystock("produit.txt", reference, -quant);
      }
      else
      {
        printf("Error: please enter either 1 or 2. \n");
      }
    }
    else if (a == 4)
    {
      addproduct("produit.txt");
    }
    else if (a == 5)
    {
      printf("Thanks for your visit ! \n");
      return 0;
    }
    else
    {
      printf("Error:please choose a number between 1 and 5. \n");
      return 0;
    }
  }
  return 0;
}
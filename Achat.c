#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Clients.h"
#include "gestion.h"
#include "main.h"

#define MAX 1000
int buying();

int getref(int ref)
{
  // zone de declaration d'un pointeur vers un fichier
  FILE *file;
  // zone de declaration de 3 tableau de char et un pointeur vers un char
  char line[100], name[100], file_name[100], *refh;
  // declaration de variables entières
  int reference, stock, size, c = 0, i = 0;
  // declaration de variable flottante
  float price;
  // ouverture du fichier produit.txt en mode lecture
  file = fopen("produit.txt", "r");
  // parcours jusqu'à la fin du fichier ou jusqu'à trouver la reference recherchée
  while (fgets(line, sizeof(line), file) != NULL)
  {
    // scan des différences references
    sscanf(line, "%s %d %d %f %d", name, &reference, &stock, &price, &size);
    if (reference == ref)
    {
      c = 1;        // indiquer qu'on a trouvé la reference recherchée
      fclose(file); // sort de la boucle la plus proche
      return 1;
      break;
    }
  }
  if (c == 1)
  {
    // si on a trouvé on ne fait rien de particulier
  }
  else
  {
    // si on a pas trouvé on met un message d'erreur et on stop le programme
    printf("Reference introuvable.\n");
    fclose(file);
    return 0;
  }
}
// fonction pour afficher le message d'erreur.
void display_stock(char *file1)
{
  // Déclaration d'un pointeur vers un fichier
  FILE *file;
  // Déclaration des variables entiere
  int reference, quantity, size;
  // Declaration de variable flotante
  float price;
  // declaration de tableau de caractere
  char name[100];
  char line[100];
  // Ouverture du fichier "produit.txt" en mode lecture
  file = fopen(file1, "r");
  if (file == NULL)
  {
    printf("Erreur en ouvrant fichier %s \n", file);
    exit(1);
  }
  // scan les infos de la premiere ligne
  sscanf(line, "%s %d %d %f %d ", name, &reference, &quantity, &price, &size); // verif si la fonction retourne le bon num
  // parcours du fichier ligen par ligne
  while (fscanf(file, "%s %d %d %f %d", name, &reference, &quantity, &price, &size) == 5)
  {
    if (quantity != 0)
    {
      // affichage du stock
      printf("Nom : %s Reference : %d Quantite : %d Prix:%.02f Taille : %d \n", name, reference, quantity, price, size);
    }
    else if (quantity == 0)
    {
    }
  }
  // fermeture du fichier
  fclose(file);
}
float buy(int ref, int quantity, char id[])
{
  float spent = 0;
  // decaration d'un pointeur vers un fichier
  FILE *file;
  FILE *fk;
  char line[100], name[100], file_name[100], filenameb[60], bal[30], *refh;
  int reference, stock, size, c = 0, i = 0;
  float price, x, y;
  // ouverture du fichier produit.txt
  file = fopen("produit.txt", "r");
  sprintf(filenameb, "Acc_balance/%s.txt", id); // création d'un fichier historique
  fk = fopen(filenameb, "r+");
  fgets(bal, sizeof(bal), fk);
  x = atof(bal);
  // parcours du fichier ligne par ligne jusquà la fin ou jusqu'à ce qu'on trouve la reference correspondante
  while (fgets(line, sizeof(line), file) != NULL)
  {
    sscanf(line, "%s %d %d %f %d", name, &reference, &stock, &price, &size);
    y = quantity * price;
    if (reference == ref && stock - quantity >= 0 && y <= x)
    {
      // diminue le stock quand on fait un acaht
      modifystock("produit.txt", ref, -quantity);
      // calcul des depenses
      spent = spent + price * quantity;
        for (i = 0; i < quantity; i++)
      {
        change_last(ref, id);
      }
      modify_balance(y * -1, id);
      fclose(fk);
      c = 1; // montrer qu'on a trouvé le produit
      break; // sort de la boucle la plus proche
    }
    else
    {
    }
  }
  if (c == 1)
  {
    // si on trouve le produit ne rien faire en particulier
  }
  else
  {
    // si on ne trouve pas, afficher un message d'erreur et quitter le programme
    printf("Impossible de faire cette achat.\n");
    return 0;
  }
  // fermeture du fichier
  fclose(file);
  return spent;
}

void shopping_area(char id[])
{
  // declaration de variable
  int choice, ref, quant;
  float spent = 0.0, balr;
  char name[50], firstname[50];
  char input[MAX];
  // ouverture d'un menu doté de la capacité de se reouvrir automatiquement quand l'utilisateur rentre un mauvais choix
  do
  {
    printf("\nVous voila dans la zone achat!\n");
    printf("Vous voulez:\n");
    printf("1.Afficher les produits disponibles.\n");
    printf("2.Acheter un article.\n");
    printf("3.Acceder a l'historique d'achat.\n");
    printf("4.Rajouter de l'argent sur votre compte\n");
    printf("5.Quitter et ayez la possibilite de supprimer votre compte.\n");
    printf("6.Aller au menu principal.");
    printf("\nVotre choix:");
    choice = scanint(input);
    printf("\n");
    if (choice == 1)
    {
      // rentrer dans la fonction d'affichage de stock
      display_stock("produit.txt");
      printf("\n");
    }
    else if (choice == 2)
    {
      // demander à l'utilisateur de rentrer la reference et la quantite du produit qu'il souhaite acheter et entrer ces parametres dans la fonction buy
      printf("Donnez la reference du produit que vous souhaitez acheter:");
      ref = scanint(input);
      // verifie si la ref est bonne ou pas
      int i = getref(ref);
      if (i == 1)
      {
        printf("Donnez la quantite que vous souhaitez acheter de ce produit:");
        quant = scanint(input);
        // recuperation de la depense totale
        spent = buy(ref, quant, id) + spent;
      }
      // affichage de la depense totale
      printf("Vous avez de depenser: %.02f \n", spent);
    }
    else if (choice == 3)
    {
      // acceder à l'historique
      history(id);
    }
    else if (choice == 4)
    {
      printf("Veuillez rentrer un montant a recharger.\n");
      balr = scanfloat(input);
      modify_balance(balr, id);
    }
    else if (choice == 5)
    {
      printf("A la prochaine!\n");
      int n=0;
      buying(n);
    }
    else if (choice == 6)
    {
      main_menu();
    }
    else
    {
      printf("Erreur veuillez rentrer un nombre entre 1 et 6.\n");
      break;
    }
  } while (choice != 5);
}
void connect_by_id(char *id)
{
  // declaration de variable
  FILE *file;
  char line[100], username[100], name[100], firstname[100];
  int c = 0;
  // verification du pointeur id
  if (id == NULL)
  {
    printf("erreur:\n");
  }
  // ouverture du fichier ID.txt
  file = fopen("ID.txt", "r");
  // verification du pointeur
  if (file == NULL)
  {
    printf("erreur");
    exit(1);
  }
  // parcours du fichier ligne par ligne
  while (fgets(line, sizeof(line), file) != NULL || c == 1)
  {
    // scan des infos de chaque ligne
    sscanf(line, "%s %s %s", username, name, firstname);
    // comparaison de l'id rentré avce les id presents dans le fichier
    if (strcmp(id, username) == 0)
    {
      printf("Bienvenue %s %s!\n", name, firstname);
      c = 1; // indiquer qu'on a trouvé l'id
      break; // sortir de la boucle la plus proche
    }
  }
  if (c == 1)
  {
    // si l'utilisateur à reussi à se connecter il rentre immediatement dans la zone d'achat
    fclose(file);
    shopping_area(id);
  }
  else
  {
    // si l'utilisateur n'a pas pu se connecter afficher id introuvable
    printf("Identifiant introuvable.\n");
  }
  // fermer le fichier
  fclose(file);
}

int buying(int n)
{
  // declaration de variable
  int choice = 0;
  float balr;
  char name[50], firstname[50], id[100];
  char input[MAX];
  printf("\nMODE ACHAT:\n");
  // ouverture d'un menu qui a la capacité de se reouvrir dès que l'utilisateur se trompe de totalement de choix
  do
  {
    printf("Vous voulez:\n");
    printf("1.Creer un compte.\n");
    printf("2.Vous connecter.\n");
    printf("3.Supprimer votre compte.\n");
    printf("4.Quitter le programme .\n");
    printf("5.Revenir au menu principal.\n\n");
    printf("Votre choix:");
    choice = scanint(input);
    if (choice == 1)
    {
      // demander à l'utilisateur de donner son nom et son prenom pour les rentrer en parametre dans la fonction client_creation
      printf("Quel est votre nom? si vous en avez 2 reliez les par un underscore:\n");
      scanf("%s", name);
      printf("Entrez votre prenom:\n");
      scanf("%s", firstname);
      client_creation(name, firstname);
    }
    else if (choice == 2)
    {
      // demande à l'utilisateur de rentrer son id pour se connecter
      printf("Entrez votre ID:");
      scanf("%s", id);
      connect_by_id(id);
    }
    else if (choice == 3)
    {
      // demander à l'utilisateur son ID pour le supprimer
      printf("Entrez votre ID:\n");
      scanf("%s", id);
      suppression_id(id);
    }

    else if (choice == 4)
    {
      // message d' au revoir
      printf("Merci pour votre visite !");
      exit(0);
    }
    else if (choice == 5)
    {
      main_menu();
    }
    else
    {
      // message indiquant quel type de coordonnées on doit rentrer
      printf("Erreur veuillez rentrer un nombre entre 1 et 6.\n");
      break;
    }
  } while (choice != 4);
  exit(0);
}
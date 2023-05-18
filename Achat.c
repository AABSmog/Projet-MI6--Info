#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include"Clients.h"
#define MAX 1000

void modifierstock1(char *fichier, int reference, int quant)
{

  char prod[50];
  int ref, quantite, taille;
  float prix;
  // créer un fichier temporaire en mode lecture
  FILE *tempor = fopen("temporaire.txt", "w");
  // ouvrir le fichier principal en mode lecture
  FILE *fp = fopen(fichier, "r");
  if (tempor == NULL || fp == NULL) // tester si le fichier s'ouvre correctement ou pas
  {
    // si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", fichier);
    exit(2);
  }
  int trouve;
  trouve = 0;
  char ligne[MAX];
  // lire le fichier ligne par ligne
  while (fgets(ligne, sizeof(ligne), fp))
  {
    // lire les informations du produit dans le fichier
    sscanf(ligne, "%s %d %d %f %d", prod,  &ref, &quantite, &prix, &taille);
    if (reference == ref) // voir si la réference du produit est la même que celle recherchée
    {
      // modifier la quantite du produit
      quantite = quant + quantite;
      trouve = 1;
    }
    // ajouter chaque ligne dans le fichier temporaraire
    fprintf(tempor, "%s %d %d %f %d \n", prod, ref, quantite, prix, taille);
  }
  if (trouve == 1)
  // si le produit a été trouvé et modifié, ce message sera affiché
  {
    printf("Le stock de ce produit a ete bien modifie. \n");
  }
  else if (trouve == 0)
  // si le produit n'a pas été trouvé et modifié, ce message sera affiché
  {
    printf("Ce produit n'est pas en stock. \n");
  }
  // fermer le fichier principal
  fclose(fp);
  // fermer le fichier temporaire
  fclose(tempor);
  // supprimer le fichier principal
  remove(fichier);
  // renommer le fichier temporaire avec le nom du fichier principal
  rename("temporaire.txt", fichier);
}
void afficher_stock(char * fichier){
  FILE *file;
  int reference, quantite, taille;
  float prix;
  char nom[100];
  char line[100];
  file=fopen(fichier, "r");
  sscanf(line,"%s %d %d %f %d ",nom, &reference, &quantite, &prix,&taille);
  while( fscanf(file, "%s %d %d %f %d", nom, &reference, &quantite, &prix, &taille)==5){  
    printf("Nom:%s Reference:%d quantite:%d prix:%f taille : %d \n",nom, reference, quantite, prix,taille);
  }
  fclose(file);
}
void acheter(int ref, int quantite, char id[]){
  float depense=0;
  FILE *file, *file2;
  char line[100], name[100], nom_fichier[100];
  int reference, stock;
  float prix;
  file=fopen("produit.txt", "r");
  while(fgets(line, sizeof(line), file)!= NULL){
    sscanf(line,"%s %d %d %f", name, &reference, &stock, &prix);
    if(reference==ref){
       modifierstock1("produit.txt", ref,-quantite);
       depense= depense + prix*quantite;
      printf("vous venez de depenser: %f\n",depense);
      break;
    }
  else{
    printf("identifiant introuvable\n");
  }   
  }
    printf("identifiant introuvable\n");   
  fclose(file);
}

void espace_achat(char id[]){
  int choice, ref, quant;
  char nom[50], prenom[50];
  do{
  printf("Vous voilà dans la zone achat!\n");
  printf("Vous voulez:\n");
  printf("1.Afficher les produits disponibles.\n");
  printf("2.Acheter un article.\n");
  printf("3.Acceder à l'historique d'achat.\n");
  printf("4.Quitter et ayez la possibilite de supprimer votre.\n");
  printf("Votre choix:");
  scanf("%d", &choice);
   if(choice==1){    
     afficher_stock("produit.txt");
    }
    else if(choice==2){
      printf("Donnez la référence du produit que vous souhaitez acheter:");
      scanf("%d", &ref);
      printf("\nDonnez la quantite que vus souhaitez acheter de ce produit:");
      scanf("%d", &quant);
      acheter(ref, quant, id);
    }
    else if(choice==3){
      //fonction historique assane
    }
    else if(choice==4){
      printf("A la prochaine!\n");
      espace_achat(id);
    }
    else{
      printf("Erreur veuillez rentrer un nombre entre 1; 2; 3 et 4.\n");
    } 
  }while(choice!=4);
}
  void connect_by_id(char *id){
  FILE *file;
  char line[100], username[100], name[100], firstname[100];
  if(id==NULL){
    printf("erreur:\n");
  }
  file=fopen("ID.txt", "r");
  if(file==NULL){
    printf("erreur");
    exit(1);
  }
  while(fgets(line, sizeof(line), file)!= NULL){
    sscanf(line,"%s %s %s", username, name, firstname);
    if(strcmp(id,username)==0){
     printf("Bienvenu %s %s!\n", name, firstname);
      break;
    }
   else{
      printf("Identifiant introuvable.\n");
    }
  }
  espace_achat(id);
  fclose(file);
}

int achat(int n) {
   int choice;
  char nom[50], prenom[50], id[100];
  do{
    printf("Mode achat:\n");
    printf("Vous voulez:\n");
    printf("1.Creer un compte.\n");
    printf("2.Vous connecter.\n");
    printf("3.Suprimer votre compte.\n");
    printf("4.Quitter le mode achat et retour au choix du mode.\n\n");
    printf("Votre choix:");
    scanf("%d", &choice);
    if(choice==1){
       printf("Quel est votre nom? si vous en avez 2 reliez les par un underscore:\n");
       scanf("%s", nom);
       printf("Entrez votre prenom:\n");
       scanf("%s", prenom);
       creation_client(nom,prenom);
     }
     else if(choice==2){
       printf("Entrez votre ID:\n");
       scanf("%s", id);
       connect_by_id(id);
     }
      else if(choice==3){
       printf("Entrez vos ID:\n");
       scanf("%s", id);
       supp_client_par_id(id);
     }
     else if(choice==4){
        break;
     }
      else{
       printf("Erreur veuillez rentrer un nombre entre 1; 2; 3 et 4.\n");
     }
  }while(choice!=4);
  return 0;
}

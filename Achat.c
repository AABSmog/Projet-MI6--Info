#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include"Clients.h"

#define MAX 1000

void rageQuit(char* msg, int errorCode){
  if(msg != NULL){
    printf("%s\n", msg);
  }
  if(errorCode == 0){
    errorCode = 99;    
  }
  exit(errorCode);
}// fonction pour afficher le message d'erreur.




void modifierstock1(char *fichier, int reference, int quant)
{

  char prod[50];
  int ref, quantite, taille;
  float prix;
  // ouvrir le fichier principal en mode lecture
  FILE *fp = fopen(fichier, "r");
    // créer un fichier temporaire en mode lecture
  FILE *tempor = fopen("temporaire.txt", "w");
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
      if(quantite<0){
        printf("Le stock est insufisant ERROR.\n");
        exit (1);
      }
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

//verif parametre


  file=fopen(fichier, "r");


  sscanf(line,"%s %d %d %f %d ",nom, &reference, &quantite, &prix,&taille);// verif si la fonction retourne le bon num
  while( fscanf(file, "%s %d %d %f %d", nom, &reference, &quantite, &prix, &taille)==5){  
    printf("Nom:%s Reference:%d quantite:%d prix:%f taille : %d \n",nom, reference, quantite, prix,taille);
  }
  fclose(file);
}
void acheter(int ref, int quantite, char id[]){
  float depense=0;
  FILE *file;
  char line[100], name[100], nom_fichier[100], *refh;
  int reference, stock, taille, c=0;
  float prix;
  file=fopen("produit.txt", "r");
  while(fgets(line, sizeof(line), file)!= NULL){
    sscanf(line,"%s %d %d %f %d", name, &reference, &stock, &prix, &taille);
    if(reference==ref){
       fclose(file);
       modifierstock1("produit.txt", ref,-quantite);
       depense= depense + prix*quantite;
       change_last(ref,id);
      printf("vous venez de depenser: %f\n",depense);
      c=1;
      break;
    }
  }
  if(c==1){

  }
  else{
     printf("Reference introuvable. Recommence la procedure en tapant 2 pour pouvoir acheter un article et rentre une bonne reference ;)\n"); 
  }    
  fclose(file);
}

void espace_achat(char id[]){
  int choice, ref, quant;
  char nom[50], prenom[50];
  do{
  printf("\nVous voilà dans la zone achat!\n");
  printf("Vous voulez:\n");
  printf("1.Afficher les produits disponibles.\n");
  printf("2.Acheter un article.\n");
  printf("3.Acceder à l'historique d'achat.\n");
  printf("4.Quitter et ayez la possibilite de supprimer votre compte.\n");
  printf("\nVotre choix:");
  scanf("%d", &choice);
  printf("\n");
   if(choice==1){    
     afficher_stock("produit.txt");
     printf("\n");
    }
    else if(choice==2){
      printf("Donnez la reference du produit que vous souhaitez acheter:");
      scanf("%d", &ref);
      printf("Donnez la quantite que vous souhaitez acheter de ce produit:");
      scanf("%d", &quant);
      acheter(ref, quant, id);
    }
    else if(choice==3){
      history(id);
    }
    else if(choice==4){
      printf("A la prochaine!\n");
    }
    else{
      printf("Erreur veuillez rentrer un nombre entre 1; 2; 3 et 4.\n");
    } 
  }while(choice!=4);
}
  void connect_by_id(char *id){
  FILE *file;
  char line[100], username[100], name[100], firstname[100];
  int c=0;
  if(id==NULL){
    printf("erreur:\n");
  }
  file=fopen("ID.txt", "r");
  if(file==NULL){
    printf("erreur");
    exit(1);
  }
  while(fgets(line, sizeof(line), file)!= NULL || c==1){
    sscanf(line,"%s %s %s", username, name, firstname);
    if(strcmp(id,username)==0){
     printf("Bienvenue %s %s!\n", name, firstname);
     c=1;
     break;
    }
  }
   if(c==1){
     fclose(file);
     espace_achat(id);
   }
   else{
    printf("Identifiant introuvable.\n");   
   }
  fclose(file);
}

int achat(int n) {
   int choice=0;
  char nom[50], prenom[50], id[100];
  do{
    printf("\nMode achat:\n");
    printf("Vous voulez:\n");
    printf("1.Creer un compte.\n");
    printf("2.Vous connecter.\n");
    printf("3.Supprimer votre compte.\n");
    printf("4.Quitter le programme .\n\n");
    printf("Votre choix:");
    scanf(" %d", &choice);
    if(choice==1){
       printf("Quel est votre nom? si vous en avez 2 reliez les par un underscore:\n");
       scanf("%s", nom);
       printf("Entrez votre prenom:\n");
       scanf("%s", prenom);
       client_creation(nom,prenom);
     }
     else if(choice==2){
       printf("Entrez votre ID:");
       scanf("%s", id);
       connect_by_id(id);
     }
      else if(choice==3){
       printf("Entrez vos ID:\n");
       scanf("%s", id);
       suppression_id(id);
     }
     else if(choice==4){
        return 0;
     }
      else{
       printf("Erreur veuillez rentrer un nombre entre 1; 2; 3 et 4.\n");
       return 0;
     }
  }while(choice!=4);
  return 0;
}
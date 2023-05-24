#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include"Clients.h"

#define MAX 1000

void getref(int ref){
  FILE *file;
  char line[100], name[100], file_name[100], *refh;
  int reference, stock, size, c=0, i = 0;
  float price;
  file=fopen("produit.txt", "r");
  while(fgets(line, sizeof(line), file)!= NULL){
    sscanf(line,"%s %d %d %f %d", name, &reference, &stock, &price, &size);
    if(reference==ref){
      c=1;
      break;
    }
  }
  if(c==1){

  }
  else{
     printf("Reference introuvable. Recommencez la procedure en tapant 2 pour pouvoir acheter un article et rentrez une bonne reference ;)\n");
     exit(0);
  }    
  fclose(file);
}
  

void rageQuit(char* msg, int errorCode){
  if(msg != NULL){
    printf("%s\n", msg);
  }
  if(errorCode == 0){
    errorCode = 99;    
  }
  exit(errorCode);
}// fonction pour afficher le message d'erreur.




void modifystock1(char *file, int reference, int quant)
{

  char prod[50];
  int ref, quantity, size;
  float price;
  // ouvrir le fichier principal en mode lecture
  FILE *fp = fopen(file, "r");
    // creer un fichier temporaire en mode lecture
  FILE *tempor = fopen("temporaire.txt", "w");
  if (tempor == NULL || fp == NULL) // tester si le fichier s'ouvre correctement ou pas
  {
    // si le fichier ne s'ouvre pas correctement, afficher un message d'erreur et terminer le programme
    printf("Erreur en ouvrant le fichier %s \n", file);
    exit(2);
  }
  int find;
  find = 0;
  char line[MAX];
  // lire le fichier ligne par ligne
  while (fgets(line, sizeof(line), fp))
  {
    // lire les informations du produit dans le fichier
    sscanf(line, "%s %d %d %f %d", prod,  &ref, &quantity, &price, &size);
    if (reference == ref) // voir si la reference du produit est la même que celle recherchee
    {
      // modifier la quantite du produit
      quantity = quant + quantity;
      find = 1;
      if(quantity<0){
        printf("Le stock est insuffisant ERROR.\n");
        exit(0);
      }
    }
    // ajouter chaque ligne dans le fichier temporaraire
    fprintf(tempor, "%s %d %d %f %d \n", prod, ref, quantity, price, size);
  }
  if (find == 1)
  // si le produit a été trouvé et modifié, ce message sera affiché
  {
    printf("Le stock de ce produit a ete bien modifie. \n");
  }
  else if (find == 0)
  // si le produit n'a pas été trouvé et modifié, ce message sera affiché
  {
    printf("Ce produit n'est pas en stock. \n");
  }
  // fermer le fichier principal
  fclose(fp);
  // fermer le fichier temporaire
  fclose(tempor);
  // supprimer le fichier principal
  remove(file);
  // renommer le fichier temporaire avec le nom du fichier principal
  rename("temporaire.txt", file);
}
void display_stock(char *file1){
  FILE *file;
  int reference, quantity, size;
  float price;
  char name[100];
  char line[100];
//verif parametre
  file=fopen(file1, "r");
  sscanf(line,"%s %d %d %f %d ",name, &reference, &quantity, &price,&size);//verif si la fonction retourne le bon num
  while( fscanf(file, "%s %d %d %f %d", name, &reference, &quantity, &price, &size)==5){ 
    if(quantity!=0){ 
    printf("Nom:%s Reference:%d quantite:%d prix:%f taille : %d \n",name, reference, quantity, price,size);
  }
  else if(quantity==0){}
  }
  fclose(file);
}
int buy(int ref, int quantity, char id[]){
  float spent=0;
  FILE *file;
  char line[100], name[100], file_name[100], *refh;
  int reference, stock, size, c=0, i = 0;
  float price;
  file=fopen("produit.txt", "r");
  while(fgets(line, sizeof(line), file)!= NULL){
    sscanf(line,"%s %d %d %f %d", name, &reference, &stock, &price, &size);
    if(reference==ref){
       fclose(file);
       modifystock1("produit.txt", ref,-quantity);
       spent= spent + price*quantity;
       for(i = 0; i < quantity; i++ ){
       change_last(ref,id);
       }
      printf("Vous venez de depenser: %f\n",spent);
      c=1;
      break;
    }
  }
  if(c==1){

  }
  else{
     printf("Reference introuvable. Recommencez la procedure en tapant 2 pour pouvoir acheter un article et rentrez une bonne reference ;)\n");
     exit(0);
  }    
  fclose(file);
  return spent;
}

void shopping_area(char id[]){
  int choice, ref, quant;
  char name[50], firstname[50];
  do{
  printf("\nVous voila dans la zone achat!\n");
  printf("Vous voulez:\n");
  printf("1.Afficher les produits disponibles.\n");
  printf("2.Acheter un article.\n");
  printf("3.Acceder a l'historique d'achat.\n");
  printf("4.Quitter et ayez la possibilite de supprimer votre compte.\n");
  printf("\nVotre choix:");
  scanf("%d", &choice);
  printf("\n");
   if(choice==1){    
     display_stock("produit.txt");
     printf("\n");
    }
    else if(choice==2){
      printf("Donnez la reference du produit que vous souhaitez acheter:");
      scanf("%d", &ref);
      getref(ref);
      printf("Donnez la quantite que vous souhaitez acheter de ce produit:");
      scanf("%d", &quant);
      buy(ref, quant, id);
    }
    else if(choice==3){
      history(id);
    }
    else if(choice==4){
      printf("A la prochaine!\n");
    }
    else{
      printf("Erreur veuillez rentrer un nombre entre 1; 2; 3 et 4.\n");
      break;
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
     shopping_area(id);
   }
   else{
    printf("Identifiant introuvable.\n");   
   }
  fclose(file);
}

int buying(int n) {
   int choice=0;
  char name[50], firstname[50], id[100];
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
       scanf("%s", name);
       printf("Entrez votre prenom:\n");
       scanf("%s", firstname);
       client_creation(name, firstname);
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
      printf("Merci pour votre visite !");
      exit(0);
     }
      else{
       printf("Erreur veuillez rentrer un nombre entre 1; 2; 3 et 4.\n");
       return 0;
     }
  }while(choice!=4);
  exit(0);
}
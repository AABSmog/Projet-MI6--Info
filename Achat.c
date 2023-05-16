#include"achat.h"

void modifierstock1(char *fichier, int reference, int quant)
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
}
void afficher_stock(char * fichier){
  FILE *file;
  int reference, quantite,taille;
  float prix;
  char nom[100];
  char line[100];
  file=fopen("produit.txt", "r");
  sscanf(line, "%s %d %d %f %d", nom, &reference, &quantite, &prix, &taille);
  while( fscanf(file, "%s %d %d %f %d", nom, &reference, &quantite, &prix, &taille)==5){     
    printf("Nom:%s Reference:%d quantité:%d prix:%f taille:%d\n", nom, reference, quantite, prix, taille);
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
       modifierstock1("produit.txt", ref, -quantite);
       depense= depense + prix*quantite;
      printf("vous venez de depenser: %f\n",depense);
    }
  else{
    printf("identifiant introuvable\n");
  }   
  }
  /*sprintf(nom_fichier, "historique_%s.txt", id);
    file2=fopen(nom_fichier, "a");
  if(file==NULL){
    printf("erreur.\n");
    exit(2);
  }
    fprintf(file2,"%s %d %d %f", name, ref, quantite, prix);
    fclose(file2);*/
  fclose(file);
 
}


char nom_produit_id(int idp[5]){
  char line[1000];
    int line_number = 0;
    FILE * fp;
    strtok(idp, "\n");
    fp = fopen("produit.txt","r");
    if (fp == NULL) {
        printf("Fichier Non-existant\n" );
    }
    while (fgets(line, sizeof(line), fp)) {
        line_number++;
        if (strstr(line, mot) != NULL) {
            return(line_number);
            fclose(fp);
            exit(0);
        }
    }
    fclose(fp);
}

}

void espace_achat(char id[18]){
  int choice, ref, quant;
  char nom[50], prenom[50];
  do{
  printf("Vous voilà dans la zone achat!\n");
  printf("Vous voulez:\n");
  printf("1.Afficher les produits disponibles.\n");
  printf("2.Acheter un article.\n");
  printf("3.Acceder à l'historique d'achat.\n");
  printf("4.Quitter.\n");
  printf("Votre choix:");
  scanf("%d", &choice);
   if(choice==1){    
     afficher_stock("produit.txt");
    }
    else if(choice==2){
      printf("Donnez la référence du produit que vous souhaitez acheter:");
      scanf("%d", &ref);
      printf("\nDonnez la quantité que vus souhaitez acheter de ce produit:");
      scanf("%d", &quant);
      acheter(ref, quant, id);
    }
    else if(choice==3){
      //fonction historique assane
    }
    else if(choice==4){
      printf("A la prochaine!\n");
      break;
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
  char id[10]="allanska";
  printf("Hello World\n");
  connect_by_id(id);
  return 0;
}
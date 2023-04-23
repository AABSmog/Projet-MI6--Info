#include<stdio.h>
#include<stdlib.h>
typedef struct{
char nom[50];
int reference;
int quantite;
float prix;
int taille;
}produit;
typedef struct{
produit produit[100];

}tproduit;
typedef struct{
char nom[50];
char prenom[50];
}client;
produit showlow(produit p){
if(p.quantite==0){
printf("Le produit %c est en rupture de stock \n",p.nom);
}
}
int main(){
 produit p;
  scanf("%s",p.nom);
  printf("Ok\n");
  scanf("%d",&p.quantite);
  showlow(p);
  return 0;
}
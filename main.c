#include"gestion.h"
#include"achat.h"
#include"Clients.h"

int main(){
    int n;
    printf("Bienvenue dans votre magasin des boissons XYZ.\n");
    printf("Voulez vous: \n");
    printf("1.Acceder au mode gestion ?\n");
    printf("2.Acceder au mode d'achat ?\n");
    printf("3.Quitter le magasin ?\n");
    printf("Votre choix:");
    scanf("%d",&n);
    if(n==1){
        management(n);
    }
    else if(n==2){
        achat(n);
    }
    else if(n==3){
        return 0;
    }
    else{
        printf("Erreur : veuillez choisir un nombre entre 1 et 3.\n");
    }
    return 0;
}
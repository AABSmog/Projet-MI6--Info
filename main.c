#include"gestion.h"
#include"function_achat.h"
int main(){
    int n;
    printf("Bienvenue dans votre magasin XYZ.\n");
    printf("Voulez vous:\n");
    printf("1.Acceder au mode de gestion ?\n");
    printf("2.Acceder au mode d'achat ?\n");
    printf("3.Quitter le programme ?\n");
    scanf("%d",&n);
    if(n==1){
        gestion(n);
    }
    else if(n==2){
        achat(n);
    }
    else if(n==3){
        return 0;
    }
    else{
        printf("Erreur: veuillez saisir un nombre entre 1 et 3. \n");
    }
    return 0;
}
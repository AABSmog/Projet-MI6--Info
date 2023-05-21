#include"gestion.h"
#include"achat.h"
#include"Clients.h"

int main(){
    int n;
    printf("Welcome to your drinks' shop XYZ.\n");
    printf("Would you like to:\n");
    printf("1.Access the management mode ?\n");
    printf("2.Access the buyer's mode ?\n");
    printf("3.Leave the shop ?\n");
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
        printf("Error: please choose a number between 1 and 3. \n");
    }
    return 0;
}
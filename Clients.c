#include <stdio.h>
void Creation_client(char nom[50],char prenom[50]){
    FILE *fp;
    fp = fopen("ID.txt","r+");
    fprintf(fp ,"%c %c",nom, prenom);
}

int main() {
    return 0;
    Creation_client("Bomboclaat ","Haagrah");
}
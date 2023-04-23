#define EOL #
#include <stdio.h>
void Creation_client(char nom[50],char prenom[50]){
    FILE * fp;
    fp = fopen("ID.txt","w+");
    
    fprintf(fp ,"%s %s",nom, prenom);
    fclose(fp);
    
}

int main() {
    Creation_client("Bomboclaat","Haagrah");
    return 0;
}
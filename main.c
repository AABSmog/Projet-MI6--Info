#include "gestion.h"
#include "achat.h"
#include "Clients.h"

void main_menu()
{
    int n;
    printf("Bienvenue dans votre magasin des boissons XYZ.\n");
    printf("Voulez vous: \n");
    printf("1.Acceder au mode gestion ?\n");
    printf("2.Acceder au mode d'achat ?\n");
    printf("3.Quitter le magasin ?\n");
    printf("Votre choix:");
    scanf("%d", &n);
    if (n == 1)
    {
        management(n);
    }
    else if (n == 2)
    {
        buying(n);
    }
    else if (n == 3)
    {
        printf("Merci pour votre visite !\n");
        exit(0);
    }
    int try = 2;
    while (n != 1 && n != 2 && n != 3 && try != 0)
    {
        printf("Choix invalide : \n");
        printf("1.Acceder au mode gestion ?\n");
        printf("2.Acceder au mode d'achat ?\n");
        printf("3.Quitter le magasin ?\n");
        scanf("%d", &n);
        try--;
        if (n == 1)
        {
            management(n);
        }
        else if (n == 2)
        {
            buying(n);
        }
        else if (n == 3)
        {
            printf("Merci pour votre visite !\n");
            exit(0);
        }
    }
    if (try == 0)
    {
        printf("Choix invalide. \n");
        exit(0);
    }
}

int main()
{
    main_menu();
    return 0;
}
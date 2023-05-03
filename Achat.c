#include "function.h"

// ... Insérez les structures et les fonctions ici ...

int main() {
    int id;
    Client clients[100]; // Un tableau pour stocker les clients (ajustez la taille si nécessaire)
    int nb_clients = 0; // Le nombre de clients dans le tableau

    Produit produits[100]; // Un tableau pour stocker les produits (ajustez la taille si nécessaire)
    int nb_produits = 0; // Le nombre de produits dans le tableau

    // Chargement des informations des clients et des produits
     load_clients(clients, &nb_clients);
     load_produits(produits, &nb_produits);

  //creer_produit(*nom, prix, quantite_stock); erreur à regler

    bool quitter = false;
    while (!quitter) {
        printf("MODE ACHAT\n");
        printf("1. Se connecter\n");
        printf("2. Créer un compte\n");
        printf("3. Supprimer un compte\n");
        printf("4. Quitter\n\n");
        printf("Choisissez une option: ");
        int option;
        scanf("%d", &option);

        switch (option) {
            case 1: {
                // Se connecter
              connecter_client(clients, nb_clients, produits, nb_produits);
              quitter = true;
              save_produits(produits, nb_produits);
                break;
            }
            case 2: {
                // Créer un compte
                creer_compte(clients, &nb_clients);
                quitter = true;
                save_clients(clients, nb_clients);
                break;
            }
            
          case 3: {
               printf("Veuillez entrer votre id:");
               scanf("%d",&id);
               supprimer_client(clients, &nb_clients, id);
               quitter = true;
            break;
          }
          case 4: 
                quitter = true;
                break;
            default:
                printf("Option invalide. Veuillez réessayer.\n");
            
        }
    }

    // Sauvegardez les informations des clients et des produits dans les fichiers
  

    return 0;
}

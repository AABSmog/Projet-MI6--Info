#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structure pour stocker les informations d'un produit
typedef struct {
    int id;
    char nom[50];
    float prix;
    int quantite_stock;
} Produit;

// Structure pour stocker les informations d'un achat
typedef struct {
    int id_produit;
    int quantite;
} Achat;

// Structure pour stocker les informations d'un client
typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char email[50];
    Achat achats[100]; // Un tableau pour stocker les achats d'un client (ajustez la taille si nécessaire)
    int nb_achats; // Le nombre d'achats effectués par le client
    int tel;
    float depenses_totales;
} Client;


// Fonction pour lire les informations des clients à partir d'un fichier
void lire_clients(Client clients[], int *nb_clients) {
    FILE *file = fopen("clients.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier clients.txt\n");
        return;
    }

    *nb_clients = 0;
    while (!feof(file)) {
        Client client;
        int result = fscanf(file, "%d %s %d", &client.id, client.nom, &client.nb_achats);
        if (result != 3) {
            break;
        }

        clients[*nb_clients] = client;
        (*nb_clients)++;
    }

    fclose(file);
}

// Fonction pour écrire les informations des clients dans un fichier
void ecrire_clients(Client clients[], int nb_clients) {
    FILE *file = fopen("clients.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier clients.txt\n");
        return;
    }

    for (int i = 0; i < nb_clients; i++) {
        Client client = clients[i];
        fprintf(file, "%d %s %d\n", client.id, client.nom, client.nb_achats);
    }

    fclose(file);
}

// Fonction pour lire les informations des produits à partir d'un fichier
void lire_produits(Produit produits[], int *nb_produits) {
    FILE *file = fopen("produits.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier produits.txt\n");
        return;
    }

    *nb_produits = 0;
    while (!feof(file)) {
        Produit produit;
        int result = fscanf(file, "%d %s %f %d", &produit.id, produit.nom, &produit.prix, &produit.quantite_stock);
        if (result != 4) {
            break;
        }

        produits[*nb_produits] = produit;
        (*nb_produits)++;
    }

    fclose(file);
}

// Fonction pour écrire les informations des produits dans un fichier
void ecrire_produits(Produit produits[], int nb_produits) {
    FILE *file = fopen("produits.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier produits.txt\n");
        return;
    }

    for (int i = 0; i < nb_produits; i++) {
        Produit produit = produits[i];
        fprintf(file, "%d %s %.2f %d\n", produit.id, produit.nom, produit.prix, produit.quantite_stock);
    }

    fclose(file);
}

void load_clients(Client clients[], int *nb_clients) {
    FILE *file = fopen("clients.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier clients.txt\n");
        return;
    }

    *nb_clients = 0;
    while (!feof(file)) {
        Client client;
        int result = fscanf(file, "%d %s %s", &client.id, client.nom, client.email);
        if (result != 3) {
            break;
        }

        clients[*nb_clients] = client;
        (*nb_clients)++;
    }

    fclose(file);
}

void load_produits(Produit produits[], int *nb_produits) {
    FILE *file = fopen("produits.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier produits.txt\n");
        return;
    }

    *nb_produits = 0;
    while (!feof(file)) {
        Produit produit;
        int result = fscanf(file, "%d %s %f %d", &produit.id, produit.nom, &produit.prix, &produit.quantite_stock);
        if (result != 4) {
            break;
        }

        produits[*nb_produits] = produit;
        (*nb_produits)++;
    }

    fclose(file);
}

void afficher_derniers_achats(Client *client, Produit produits[], int nb_produits) {
    printf("Les trois derniers achats de %s:\n", client->nom);

    int debut = client->nb_achats - 3;
    if (debut < 0) {
        debut = 0;
    }

    for (int i = debut; i < client->nb_achats; i++) {
        Achat achat = client->achats[i];
        Produit *produit = NULL;

        // Recherche du produit par ID
        for (int j = 0; j < nb_produits; j++) {
            if (produits[j].id == achat.id_produit) {
                produit = &produits[j];
                break;
            }
        }

        if (produit != NULL) {
            printf("%d x %s (ID: %d) au prix de %.2f€\n", achat.quantite, produit->nom, produit->id, produit->prix);
        } else {
            printf("Produit avec ID %d non trouvé\n", achat.id_produit);
        }
    }
}

Produit* rechercher_produit_par_nom(const char *nom_recherche, Produit produits[], int nb_produits) {
    for (int i = 0; i < nb_produits; i++) {
        if (strcmp(produits[i].nom, nom_recherche) == 0) {
            return &produits[i];
        }
    }
    return NULL;
}

Produit *rechercher_produit_par_id(int id) {
    FILE *f = fopen("produits.txt", "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier produits.txt\n");
        return NULL;
    }

    Produit *produit = malloc(sizeof(Produit));
    int trouve = 0;

    while (!trouve && fscanf(f, "%d;%[^;];%f;%d", &produit->id, produit->nom, &produit->prix, &produit->quantite_stock) == 4) {
        if (produit->id == id) {
            trouve = 1;
        }
    }

    fclose(f);

    if (!trouve) {
        free(produit);
        return NULL;
    }

    return produit;
}


/*bool acheter_produit(Client *client, Produit *produit, int quantite) {
    if (produit->quantite_stock < quantite) {
        printf("Désolé, il ne reste que %d unités de %s en stock.\n", produit->quantite_stock, produit->nom);
        return false;
    }

    // Mettre à jour la quantité en stock du produit
    produit->quantite_stock -= quantite;

    // Ajouter l'achat au client
    Achat achat;
    achat.id_produit = produit->id;
    achat.quantite = quantite;
    client->achats[client->nb_achats] = achat;
    client->nb_achats++;

    printf("Vous avez acheté %d x %s (ID: %d) au prix de %.2f€\n", quantite, produit->nom, produit->id, produit->prix);

    return true;
}*/
void acheter_produit(Produit *produit, Client *client) {
    if (produit->quantite_stock <= 0) {
        printf("Désolé, ce produit n'est plus en stock.\n");
        return;
    }

    // Réduire la quantité en stock du produit
    produit->quantite_stock--;

    // Ajouter le produit aux achats du client
    client->nb_achats++;

    // Mettre à jour les dépenses totales du client
    client->depenses_totales += produit->prix;

    printf("Achat réussi!\n");
}

float calculer_prix_total_achats(Client *client, Produit produits[], int nb_produits) {
    float prix_total = 0.0;

    for (int i = 0; i < client->nb_achats; i++) {
        Achat achat = client->achats[i];
        Produit *produit = NULL;

        // Recherche du produit par ID
        for (int j = 0; j < nb_produits; j++) {
            if (produits[j].id == achat.id_produit) {
                produit = &produits[j];
                break;
            }
        }

        if (produit != NULL) {
            prix_total += achat.quantite * produit->prix;
        } else {
            printf("Produit avec ID %d non trouvé\n", achat.id_produit);
        }
    }

    return prix_total;
}
void save_clients(Client clients[], int nb_clients) {
    FILE *file = fopen("clients.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier clients.txt\n");
        return;
    }

    // Écrire les informations de chaque client dans le fichier
    for (int i = 0; i < nb_clients; i++) {
        Client client = clients[i];
        fprintf(file, "%d %s %d\n", client.id, client.nom, client.nb_achats);
    }

    fclose(file);
    printf("Clients sauvegardés avec succès dans clients.txt\n");
}
void supprimer_client(Client clients[], int *nb_clients, int id_client) {
    int index_client = -1;

    // Rechercher l'index du client avec l'ID correspondant
    for (int i = 0; i < *nb_clients; i++) {
        if (clients[i].id == id_client) {
            index_client = i;
            break;
        }
    }

    if (index_client == -1) {
        printf("Aucun client trouvé avec cet ID.\n");
        return;
    }

    // Supprimer le client en décalant les éléments restants
    for (int i = index_client; i < *nb_clients - 1; i++) {
        clients[i] = clients[i + 1];
    }

    // Mettre à jour le nombre de clients
    (*nb_clients)--;

    // Supprimer le client du fichier en sauvegardant la liste mise à jour des clients
    save_clients(clients, *nb_clients);

    printf("Client supprimé avec succès.\n");
}

void afficher_produits(Produit produits[], int nb_produits) {
    printf("+-----+------------------+---------+---------------+\n");
    printf("| ID  | Nom du produit   |  Prix   |  Stock        |\n");
    printf("+--1--+-inazuma eleven1--+---50$---+----10---------+\n");
    printf("+--2--+-inazuma eleven2--+---50$---+----10---------+\n");
    printf("+--3--+-inazuma eleven3--+---50$---+----10---------+\n");
    printf("+--4--+-inazuma eleven4--+---50$---+----10---------+\n");

    for (int i = 0; i < nb_produits; i++) {
        printf("| %3d | %-16s | %7.2f | %13d |\n", produits[i].id, produits[i].nom, produits[i].prix, produits[i].quantite_stock);
        printf("+-----+------------------+---------+---------------+\n");
    }
}
Client* connecter_client(char id[18]) {
    int id_client;
    int index_client = -1;

    printf("Veuillez entrer votre ID client: ");
    scanf("%d", &id_client);

    // Rechercher le client avec l'ID correspondant
    for (int i = 0; i < nb_clients; i++) {
        if (clients[i].id == id_client) {
            index_client = i;
            break;
        }
    }

    if (index_client == -1) {
        printf("Aucun client trouvé avec cet ID.\n");
        return NULL;
    }

    printf("Client connecté avec succès!\n");

    // Afficher les trois derniers achats du client
    afficher_derniers_achats(&clients[index_client], produits, nb_produits);

    // Afficher les produits disponibles
    printf("\nProduits disponibles :\n");
    afficher_produits(produits, nb_produits);

    int choix_produit;
    int continuer_achat = 1;

    while (continuer_achat) {
        printf("\nEntrez l'ID du produit que vous souhaitez acheter (0 pour quitter) : ");
        scanf("%d", &choix_produit);

        if (choix_produit == 0) {
            continuer_achat = 0;
        } else {
            Produit* produit = rechercher_produit_par_id(choix_produit);
            if (produit != NULL) {
                acheter_produit(produit, &clients[index_client]);
                printf("Vous avez acheté : %s\n", produit->nom);
                printf("Total des dépenses : %.2f\n", clients[index_client].depenses_totales);
            } else {
                printf("Produit introuvable. Veuillez essayer à nouveau.\n");
            }
        }
    }

    // Retourner un pointeur vers le client connecté
    return &clients[index_client];
}

// Trouver un ID libre pour un nouveau client
int trouver_id_libre(Client clients[], int nb_clients) {
    int id_candidat = 1;
    int id_trouve = 0;

    while (!id_trouve) {
        id_trouve = 1;
        for (int i = 0; i < nb_clients; i++) {
            if (clients[i].id == id_candidat) {
                id_trouve = 0;
                break;
            }
        }
        if (id_trouve) {
            return id_candidat;
        }
        id_candidat++;
    }

    return id_candidat;
}

Client* creer_compte(Client clients[], int *nb_clients) {
    // Création du nouveau client
    Client nouveau_client;
    nouveau_client.id = trouver_id_libre(clients, *nb_clients); // Attribution d'un ID libre
    printf("Veuillez entrer votre nom: ");
    scanf("%s", nouveau_client.nom);
    nouveau_client.nb_achats = 0;

    // Ajout du nouveau client au tableau de clients
    clients[*nb_clients] = nouveau_client;
    (*nb_clients)++;

    printf("Compte créé avec succès! Votre ID client est: %d\n", nouveau_client.id);

    // Retourner un pointeur vers le nouveau compte client créé
    return &clients[*nb_clients - 1];
}

void save_produits(Produit produits[], int nb_produits) {
    FILE *file = fopen("produits.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier produits.txt\n");
        return;
    }

    // Écrire les informations de chaque produit dans le fichier
    for (int i = 0; i < nb_produits; i++) {
        Produit produit = produits[i];
        fprintf(file, "%d %s %.2f %d\n", produit.id, produit.nom, produit.prix, produit.quantite_stock);
    }

    fclose(file);
    printf("Produits sauvegardés avec succès dans produits.txt\n");
}

int get_next_product_id() {
    FILE *f = fopen("produits.txt", "r");
    if (f == NULL) {
        return 1;
    }

    int max_id = 0;
    Produit produit;

    while (fscanf(f, "%d;%[^;];%f;%d", &produit.id, produit.nom, &produit.prix, &produit.quantite_stock) == 4) {
        if (produit.id > max_id) {
            max_id = produit.id;
        }
    }

    fclose(f);

    return max_id + 1;
}

void creer_produit(const char *nom, float prix, int quantite_stock) {
    int next_id = get_next_product_id();

    Produit nouveau_produit = {next_id, "", prix, quantite_stock};
    strncpy(nouveau_produit.nom, nom, sizeof(nouveau_produit.nom) - 1);

    FILE *f = fopen("produits.txt", "a");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier produits.txt\n");
        return;
    }

    fprintf(f, "%d;%s;%.2f;%d\n", nouveau_produit.id, nouveau_produit.nom, nouveau_produit.prix, nouveau_produit.quantite_stock);
    fclose(f);
}

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
    char email[50];
    Achat achats[100]; // Un tableau pour stocker les achats d'un client (ajustez la taille si nécessaire)
    int nb_achats; // Le nombre d'achats effectués par le client
} Client;

void lire_clients(Client clients[], int *nb_clients);
void ecrire_clients(Client clients[], int nb_clients);
void lire_produits(Produit produits[], int *nb_produits);
void ecrire_produits(Produit produits[], int nb_produits);
void load_clients(Client clients[], int *nb_clients);
void load_produits(Produit produits[], int *nb_produits);
void afficher_derniers_achats(Client *client, Produit produits[], int nb_produits);
Produit* rechercher_produit_par_nom(const char *nom_recherche, Produit produits[], int nb_produits);
void acheter_produit(Produit *produit, Client *client);
float calculer_prix_total_achats(Client *client, Produit produits[], int nb_produits);
void supprimer_client(Client clients[], int *nb_clients, int id_client);
void afficher_produits(Produit produits[], int nb_produits);
Client* connecter_client(Client clients[], int nb_clients, Produit produits[], int nb_produits);
int trouver_id_libre(Client clients[], int nb_clients);
Client* creer_compte(Client clients[], int *nb_clients);
void save_produits(Produit produits[], int nb_produits);
void save_clients(Client clients[], int nb_clients);
int get_next_product_id();
void creer_produit(const char *nom, float prix, int quantite_stock);
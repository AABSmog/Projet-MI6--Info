#define EOL #
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ID_LENGTH 18
#define MAX_NAME_LENGTH 50
#define NUM_IDS 10617
#define MAX 1000
#define NB_DERNIERS_ACHATS 3


typedef struct {
    char nom[MAX];
    int ref;
    int quantite;
    float prix;
    int taille;
} Produit;

typedef struct {
    int ref;
    int quantite;
    float prix_total;
} Achat;

typedef struct {
    Achat achats[3];
    int nb_achats;
} Historique;

typedef struct {
    char id_client[MAX];
    Achat achats[NB_DERNIERS_ACHATS];
} Client;

void create_user(char firstName[MAX_NAME_LENGTH], char lastName[MAX_NAME_LENGTH]);
void connect_by_id(char id[MAX_ID_LENGTH]);
void ajouter_achat(char *fichier, char *id_client, char *nom_produit, int ref_produit, int quantite);
void afficher_historique_achat(char *fichier, char *id_client);
void espace_client(char identifiant[]);
void acheter_produit(char *fichier, char *nom_produit, char *ref_produit, int quantite, char *id);
void ecrire_historique(Client *client);
void afficher_dernieres_lignes(char* nom_fichier, int n);
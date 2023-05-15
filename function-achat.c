#include "clients.h"
#include "function_achat.h"
#include "gestion.h"

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
#define MAX_ACHATS 100  // Maximum number of purchases we'll track
#define NB_DERNIERS_ACHATS 3
#define TAILLE_LIGNE 1024
#define MAX 256


typedef struct {
    char nom[MAX];
    int ref;
    int quantite;
    float prix;
    int taille;
} Produit;

typedef struct {
    char nom_produit[MAX];
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
} client;


void afficherProduitsDisponibles(char *fichier) {
    FILE *fp = fopen("produit.txt", "r");
    if (fp == NULL) {
        printf("Erreur en ouvrant le fichier %s \n", fichier);
        exit(6);
    }
    char ligne[MAX];
    printf("Produits disponibles en stock :\n");
    while (fgets(ligne, sizeof(ligne), fp)) {
        char produit[MAX];
        int ref;
        int quantite;
        float prix;
        int taille;
        sscanf(ligne, "%s %d %d %f %d", produit, &ref, &quantite, &prix, &taille);
        if (quantite > 0) {
            printf("Nom: %s Reference: %d Stock: %d Prix: %f Taille: %d \n", produit, ref, quantite, prix, taille);
        }
    }
    fclose(fp);
}





/*void acheter_produit(char *fichier, char *nom_produit, int ref_produit, int quantite) {
    FILE *fp = fopen(fichier, "r+");
    if (fp == NULL) {
        printf("Erreur en ouvrant le fichier %s \n", fichier);
        return;
    }

    char ligne[MAX];
    int trouve = 0;
    float total_depense = 0;
    
    while (fgets(ligne, sizeof(ligne), fp)) {
        char produit[MAX];
        int ref;
        int quantite_en_stock;
        float prix;
        int taille;

        sscanf(ligne, "%s %d %d %f %d", produit, &ref, &quantite_en_stock, &prix, &taille);

        if (strcmp(produit, nom_produit) == 0 && ref == ref_produit) {
            trouve = 1;

            if (quantite_en_stock < quantite) {
                printf("Quantité insuffisante en stock pour %s. Achat impossible.\n", nom_produit);
                break;
            } else {
                // Mise à jour du stock dans le fichier
                fseek(fp, -strlen(ligne), SEEK_CUR);
                fprintf(fp, "%s %d %d %f %d\n", produit, ref, quantite_en_stock - quantite, prix, taille);

                total_depense += quantite * prix;
                printf("Vous avez acheté %d unité(s) de %s pour un total de %.2f€.\n", quantite, nom_produit, total_depense);

                break;
            }
        }
    }

    if (trouve == 0) {
        printf("Le produit %s n'a pas été trouvé dans le stock.\n", nom_produit);
    }

    fclose(fp);
}*/

void acheter_produit(char *fichier, char nom_produit[], char *ref_produit, int quantite, char id[])
{
  // Diminue le stock du produit
  modifierstock(fichier, ref_produit, -quantite);
  printf("Vous avez acheté %d unités du produit %s.\n", quantite, nom_produit);
}

void espace_client(char identifiant[]) {
  client client;
    FILE *fp = fopen("produit.txt", "r+");
    if (fp == NULL) {
        printf("Erreur en ouvrant le fichier produit.txt\n");
        exit(1);
    }

    Historique historique = { .nb_achats = 0 };
    float depenses_totales = 0.0;
 int choix;
 int choix2;
    do {
        printf("MENU ESPACE CLIENT\n");
        printf("1. Afficher les produits disponibles\n");
        printf("2. Acheter un produit\n");
        printf("3. Afficher l'historique des achats\n");
        printf("4. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);
      int ref, quantite;
      char nom_prod[MAX_NAME_LENGTH];
        switch (choix) {
            case 1:
                afficherProduitsDisponibles(fp);
                break;
            case 2: 
                printf("Entrez la référence du produit: ");
                scanf("%d", &ref);                    
                printf("Entrez la quantité souhaitée: ");
                scanf("%d", &quantite);
                printf("Entrez le nom du produit");
                scanf("%s", nom_prod);
                acheter_produit("produit.txt", nom_prod,  ref, quantite, identifiant);
                break;
            case 3:
                afficher_historique_achat("historique_achat.txt", identifiant);
                break;
            case 4:
                printf("Merci d'avoir utilisé notre programme. À bientôt !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix!=4);

    fclose(fp);
}

// Connexion d'un utilisateur par ID
void connect_by_id(char id[MAX_ID_LENGTH]){
    FILE * file;
    char line[1000];
    char userId[MAX_ID_LENGTH], firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH];

    // Ouvrez le fichier en mode lecture
    file = fopen("ID.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    // Recherchez l'ID dans le fichier
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %s", userId, firstName, lastName);
        if (strcmp(userId, id) == 0) {
            printf("Bienvenue %s %s!\n", firstName, lastName);
            fclose(file);
            //afficherProduitsDisponibles("produit.txt");
            espace_client(id);
        }
    }

    printf("ID invalide.\n");
    fclose(file);
}


int main(int n) {
    int choice;
    char id[MAX_ID_LENGTH], firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH];

    printf("Bienvenue dans le mode achat:\n");
    printf("Voulez vous:\n");
    printf("1.Creer votre compte:\n");
    printf("2.Vous connecter:\n");
    printf("3.Supprimer votre compte:\n");    
  do{
    printf("Votre choix: ");
    scanf(" %d", &choice);
    if (choice == 1) {
        printf("Veuillez entrer votre prénom :\n");
        scanf("%s", firstName);

        printf("Veuillez entrer votre nom :\n");
        scanf("%s", lastName);

        create_user(firstName, lastName);

    }
    else if (choice == 2) {
        printf("Veuillez entrer votre ID :\n");
        scanf("%s", id);

        connect_by_id(id);

    }
    else if (choice == 3) {
        printf("Veuillez entrer votre ID :\n");
        scanf("%s", id);

        delete_user_by_id(id);

    }
    else {
        printf("Choix non valide. Veuillez rentrer une valeur égale à 1; 2 ou 3.\n");
    }
  }while(choice!=1 && choice!=2 && choice!=3 );

    return 0;
}

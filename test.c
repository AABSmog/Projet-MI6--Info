#include <stdio.h>
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD
#include <stdbool.h>

// ... Insérez les structures et les fonctions ici ...

int main() {
    Client clients[100]; // Un tableau pour stocker les clients (ajustez la taille si nécessaire)
    int nb_clients = 0; // Le nombre de clients dans le tableau

    Produit produits[100]; // Un tableau pour stocker les produits (ajustez la taille si nécessaire)
    int nb_produits = 0; // Le nombre de produits dans le tableau

    // Chargement des informations des clients et des produits
    // load_clients(clients, &nb_clients);
    // load_produits(produits, &nb_produits);

    bool quitter = false;
    while (!quitter) {
        printf("MODE ACHAT\n");
        printf("1. Se connecter\n");
        printf("2. Créer un compte\n");
        printf("3. Quitter\n");
        printf("Choisissez une option: ");
        int option;
        scanf("%d", &option);

        switch (option) {
            case 1: {
                // Se connecter
                // connecter_client(clients, nb_clients, produits, nb_produits);
                break;
            }
            case 2: {
                // Créer un compte
                // creer_compte(clients, &nb_clients);
                break;
            }
            case 3:
                quitter = true;
                break;
            default:
                printf("Option invalide. Veuillez réessayer.\n");
        }
    }

    // Sauvegardez les informations des clients et des produits dans les fichiers
    // save_clients(clients, nb_clients);
    // save_produits(produits, nb_produits);

=======
#include <ctype.h>

#define MAX_LINE_LENGTH 1000

void find_word_in_file(const char* filename, const char* word) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int line_number = 0;

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        line_number++;
        char* line_ptr = line;
        char* word_ptr = word;

        while (*line_ptr != '\0') {
            if (tolower(*line_ptr) == tolower(*word_ptr)) {
                line_ptr++;
                word_ptr++;
                if (*word_ptr == '\0') {
                    printf("Found '%s' in line %d: %s", word, line_number, line);
                    break;
                }
            } else {
                line_ptr++;
                word_ptr = word;
            }
        }
    }

    fclose(fp);
}
int main() {
    find_word_in_file("produit.txt", "coc1");
>>>>>>> dc099a736f503ba3e9b69cffff744db5995c70d4
    return 0;
}

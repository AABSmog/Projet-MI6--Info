#ifndef ACHAT_H
    #define ACHAT_H
    #include <stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<errno.h>
    void modifystock1(char *fichier, int reference, int quant);
    void display_stock(char * fichier);
    void buy(int ref, int quantite, char id[]);
    void shopping_area(char id[]);
    void connect_by_id(char *id);
    int buying(int n);
    int menu_principal();
#endif
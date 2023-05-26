#ifndef CLIENTS_H    
    #define CLIENTS_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <time.h>
    #define MAX 1000
    bool read_if_id(char str[18]);
    void client_creation(char name[50], char surname[50]);
    int line_id(char id[18]);
    void suppression_id(char id[18]);
    void change_last(int pc, char id[18]);
    void history(char id[18]);
    void modify_balance(int mod, char id[18]);
#endif
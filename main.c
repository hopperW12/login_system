#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "database.h"
#include "scipher.h"
#include "main.h"

int status;

/*
 * 0 - volba
 * 1 - login
 * 2 - registrace
 *
 * 4 - user info
 *
 */

int main() {
    init();
    insertUser("admin", convertToCipher("admin"));
    status = 0;

    userExist("admin");

    printf("%s", getPassword("admin"));

    /*while (1) {
        if (status == 0) {
            info();
            int typ;
            printf("\nVyber volbu: ");
            scanf("%d", &typ);
            if (typ == 1) {
                status = 1;
                clearConsole();
                info();
                continue;
            } else if (typ == 2) {
                status = 2;
                clearConsole();
                info();
                continue;
            } else if (typ == 9) {
                printf("\nProgram ukoncen.\n");
                return 0;
            } else {
                printf("\nTato volba neexistuje.\n\n");
                continue;
            }
        } else if (status == 1) {
            printf("Zadej jmeno: ");
            char username[usernameLen] = "";
            scanf("%s", username);
            if (strcmp(username, "exit") == 0) {
                status = 0;
                clearConsole();
                info();
                continue;
            } else if (strlen(username) > usernameLen) {
                printf("Tento uzivatel neexisuje.\n\n");
                continue;
            } else {
                if (!userExist(username)) {
                    printf("Tento uzivatel neexisuje.\n\n");
                    continue;
                }
                char password[passwordLen];
                printf("Zadej heslo: ");
                scanf("%s", password);
                char *userPassword = getPassword(username);
                printf("fsffdsf");
                if (strcmp(password, userPassword) == 0) {
                    status = 4;
                    clearConsole();
                    info();

                    printf("\nInformace o uctu: \n\n");
                    printf("Jmeno: %s", username);
                    printf("Posledni prihlaseni: \n\n");
                    continue;
                } else {
                    printf("Spatne udaje!.\n\n");
                    continue;
                }
            }
        }
    }*/
}



void info() {
    switch (status) {
        case 0:
            printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
            printf("            Vitej v systemu!\n\n");
            printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            printf("\n");
            printf("1. - Prihlaseni\n");
            printf("2. - Registrace\n");
            printf("9. - Exit\n");
            break;
        case 1:
            printf("Pokud se chces vratit zpet zadej: exit\n\n");
            break;
        case 4:
            printf("Uspesne prihlaseni.\n");
            break;
    }
}

void clearConsole() {
    system("cls");
}

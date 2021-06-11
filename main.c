#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

bool isAdmin;

int main() {
    init();

    char *rootPassword = convertToCipher("admin");
    insertUser("admin", rootPassword);
    free(rootPassword);

    status = 0;
    isAdmin = false;

    info();
    while (1) {
        /*
         *
         * Vyber volby (registrace/prihlaseni/vypnutí programu)
         *
         */
        if (status == 0) {

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
        /*
         *
         * Prihlaseni
         *
         */
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

                char *convertPassword = convertToCipher(password);
                char *userPassword = getPassword(username);

                if (strcmp(convertPassword, userPassword) == 0) {

                    status = 4;
                    clearConsole();
                    info();

                    if (strcmp(username, "admin") == 0) isAdmin = true;
                    else isAdmin = false;

                    printf("\nInformace o uctu: \n\n");
                    printf("Jmeno: %s\n\n", username);
                    printf("Pro odhlaseni napis: logout\n");

                    free(userPassword);
                    free(convertPassword);

                    continue;
                } else {
                    printf("Spatne udaje!.\n\n");

                    free(userPassword);
                    free(convertPassword);

                    continue;
                }
            }
        /*
         *
         * Registrace
         *
         */
        } else if (status == 2) {

            printf("Zadej jmeno: ");
            char username[usernameLen] = "";
            scanf("%s", username);
            printf("Zadej heslo: ");

            if (userExist(username)) {
                printf("Tento uzivatel existuje!\n");
                continue;
            }

            char password[passwordLen] = "";
            scanf("%s", password);

            printf("Zadej znova heslo: ");
            char confirm[passwordLen] = "";
            scanf("%s", confirm);

            if (strcmp(password, confirm) != 0) {
                printf("Hesla se neshoduji.\n");
                continue;
            }

            char *convertPassword = convertToCipher(password);
            insertUser(username, convertPassword);

            status = 0;
            clearConsole();
            info();

            printf("\nUzivatel byl upspesne vytvoren. \n");

            free(convertPassword);
        /*
         *
         * Akce uprostre uzivatelskeho rozhrani
         *
         */
        } else if (status == 4) {
            char command[255];
            printf("Prikaz: ");
            scanf("%s", command);

            if (strcmp(command, "logout") == 0) {

                status = 0;
                clearConsole();
                info();
                continue;

            } else if (strcmp(command, "counter") == 0) {

                printf("Napis pocet cisel, ktery se chces secit: ");
                int count;
                scanf("%d", &count);
                printf("Napis cisla (%dx)\n", count);

                int numbers[count];
                for (int i = 0; i < count; i++) {
                    scanf("%d", &numbers[i]);
                }

                int value = 0;
                for (int i = 0; i < count; i++) {
                    value += numbers[i];
                }

                printf("Soucet: %d\n", value);
                continue;

            } else if (isAdmin && strcmp(command, "users") == 0) {
                printAllUsers();
                continue;

            } else {
                printf("Tento prikaz neexistuje.\n");
                continue;

            }
        }
    }
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
            printf("             \nPrihlaseni\n\n");
            printf("Pokud se chces vratit zpet zadej: exit\n\n");
            break;
        case 2:
            printf("             \nRegistrace\n\n");
            printf("Pokud se chces vratit zpet zadej: exit\n\n");
            break;
        case 4:
            printf("Uspesne prihlaseni.\n");
            break;
        default:
            break;
    }
}

void clearConsole() {
    system("cls");
}

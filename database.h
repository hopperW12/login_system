#ifndef LS_SYSTEM_DATABASE_H
#define LS_SYSTEM_DATABASE_H

#include <stdbool.h>

void init();
bool insertUser(char *username, char *password);
bool userExist(char *username);
char *getPassword(char *username);

void printAllUsers();

#endif //LS_SYSTEM_DATABASE_H

#ifndef LS_SYSTEM_DATABASE_H
#define LS_SYSTEM_DATABASE_H

#include <stdbool.h>

void init();
bool createUser(char *username, char *password);
bool userExist(char *username);
bool deleteUser(char *username);


int *callbackGetAll(void *NotUsed, int argc, char **argv, char **azColName);


#endif //LS_SYSTEM_DATABASE_H

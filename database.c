#include <sqlite3.h>
#include <stdio.h>
#include "database.h">

char *databaseName = "database.db";

void init() {
    sqlite3 *db;
    int rc = sqlite3_open(databaseName, &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
    }

    //Vytváření tabulky users
    char *sql = "CREATE TABLE IF NOT EXISTS `users` (name VARCHAR(25) PRIMARY KEY, password VARCHAR(256));";
    char *err_msg;

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_close(db);
    }

    sqlite3_close(db);
}

bool userExist(char *username) {
    sqlite3 *db;
    int rc = sqlite3_open(databaseName, &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
    }

    char *sql = "SELECT * FROM users";
    char *err_msg;
    rc = sqlite3_exec(db, sql, callbackGetAll, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_close(db);
        return false;
    }
    sqlite3_close(db);

    return false;
}

int *callbackGetAll(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;

    for (int i = 0; i < argc; i++) {

    }
}

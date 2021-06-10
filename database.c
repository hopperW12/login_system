#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define usersLimit 50
#define passwordLen 25
#define usernameLen 25

char *databaseName = "database.db";

void init() {
    sqlite3 *db;
    int rc = sqlite3_open(databaseName, &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return;
    }

    //Vytváření tabulky users
    char *sql = "CREATE TABLE IF NOT EXISTS users(username VARCHAR(25) PRIMARY KEY, password VARCHAR(256));";
    char *err_msg;

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        printf("SQL Error: %s\n", err_msg);
        sqlite3_close(db);
        return;
    }

    sqlite3_close(db);
    printf("Init database\n");
}

bool insertUser(char *username, char *password) {
    sqlite3 *db;
    int rc = sqlite3_open(databaseName, &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return false;
    }
    char *sql = "REPLACE INTO users(username, password) VALUES(?, ?);";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        printf("SQL Error: %s\n", sqlite3_errmsg(db));
        return false;
    }
    sqlite3_bind_blob(stmt, 1, username, strlen(username), SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, password, strlen(password), SQLITE_STATIC);
    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        printf("SQL Error: %s\n", sqlite3_errmsg(db));
        return false;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}

char *getPassword(char *username) {

}

bool userExist(char *username) {

    char tempUsernames[usersLimit][usernameLen] = {'\0'};

    sqlite3 *db;
    int rc = sqlite3_open(databaseName, &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return false;
    }

    sqlite3_stmt * stmt;
    char *sql = "SELECT * FROM users";
    char *err_msg;

    sqlite3_prepare(db, sql, -1 , &stmt, &err_msg);
    for (int i = 0; ; i++) {
        int s = sqlite3_step(stmt);
        if (s == SQLITE_ROW) {
            const char *username = sqlite3_column_text(stmt, 0);
            strncpy(tempUsernames[i], username, strlen(username));
        } else if (s == SQLITE_DONE) {
            break;
        } else {
            printf("SQL Error: %s\n", err_msg);
            return false;
        }
    }
    sqlite3_close(db);

    for (int i = 0; i < usersLimit; i++)
        if (strcmp(tempUsernames[i], username) == 0) return true;

    return false;
}


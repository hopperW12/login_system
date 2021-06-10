#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"

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
    sqlite3_bind_blob(stmt, 1, username, (int) strlen(username), SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, password, (int) strlen(password), SQLITE_STATIC);
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
    sqlite3 *db;
    sqlite3_stmt *stmt;

    int rc = sqlite3_open(databaseName, &db);
    if (rc != SQLITE_OK) {
        printf("SQL Error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return "";
    }

    char *sql = "SELECT * FROM users WHERE username = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("SQL Error: %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return "";
    }

    sqlite3_bind_blob(stmt, 1, username, (int) strlen(username), NULL);

    while (1) {
        int step = sqlite3_step(stmt);
        if (step == SQLITE_ROW) {
            printf("Return %s\n", sqlite3_column_text(stmt, 1));
            const char *password = (const char *) sqlite3_column_text(stmt, 1);
            char *pw = "";
            strncpy(pw, password, strlen(password));
            printf("Return");
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return pw;
        } else if (step == SQLITE_DONE) {
            return "";
        } else {
            printf("SQL execution failed: %s", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return "";
        }
    }
}

bool userExist(char *username){

    char tempUsernames[usersLimit][usernameLen] = {'\0'};

    sqlite3 *db;
    int rc = sqlite3_open(databaseName, &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return false;
    }

    sqlite3_stmt * stmt;
    char *sql = "SELECT * FROM users";

    sqlite3_prepare(db, sql, -1 , &stmt, 0);
    for (int i = 0; ; i++) {
        int s = sqlite3_step(stmt);
        if (s == SQLITE_ROW) {
            const char *user = sqlite3_column_text(stmt, 0);
            strncpy(tempUsernames[i], user, strlen(user));
        } else if (s == SQLITE_DONE) {
            break;
        } else {
            printf("SQL Error: %s\n", sqlite3_errmsg(db));
            return false;
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    for (int i = 0; i < usersLimit; i++)
        if (strcmp(tempUsernames[i], username) == 0) return true;

    return false;
}


cmake_minimum_required(VERSION 3.19)
project(LS_System C)

set(CMAKE_C_STANDARD 99)

include_directories("lib")


add_executable(LS_System main.c database.c database.h lib/sqlite3.c scipher.h scipher.c main.h)
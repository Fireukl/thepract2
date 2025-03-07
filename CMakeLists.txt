cmake_minimum_required(VERSION 3.10)

project(thepract2 C)

set(CMAKE_C_STANDARD 99)

add_executable(thepract2 src/main.c src/users.c src/processes.c src/help.c src/file_utils.c)


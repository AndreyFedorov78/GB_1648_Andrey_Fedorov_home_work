#ifndef LIB_11_H
#define LIB_11_H
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

// задаем размер буфера для копирования
#define BUF_SIZE 1024
void file_copy(FILE *f1, FILE *f2); // функция копирования
void tree(const char *path); // внешняя функция вывода дерева каталогов
static void dir_tree(const char *path, uint16_t n); // рекурсивная функция вывода дерева каталогов
static void print_spases(uint16_t n);  //  функция вывода пробелов

#endif

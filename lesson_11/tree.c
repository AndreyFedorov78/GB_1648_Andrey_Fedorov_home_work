/*
Задание2:
Рекурсивный вывод файлов в директории.
Вывести информацию о файлах в директории(и из всех дочерних директорий), указанной пользователем либо через аргументы командной строки(argc,argv), либо через getcwd() либо через scanf()
Аналогия: команда ls -r
например:
./myls /home/user
*/


#include <stdio.h>
#include "lib_11.h"

int main(int argc, char **argv)
{
  for (int i=1; i<argc; ++i) tree(argv[i]);
  return 0;
}
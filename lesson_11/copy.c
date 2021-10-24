/*
Задание1:
Копирование файлов. Режим работы - двоичный.
Пользователь указывает имя файла для копирования, и имя файла целевого.
Происходит копирование(как утилита/команда cp)
например:
./mycp file1 file2
*/
#include <stdio.h>
#include "lib_11.h"

int main(int argc, char **argv)
{
  FILE *f1, *f2;
  if (argc != 3){
    printf("Введено неверное количество аргументов\nиспользуйте: 'my_copy file1 file2'\n");
    return 0;
    }
    printf("копирование файла %s в файл %s\n", argv[1], argv[2]);
    if (!(f1=fopen(argv[1], "rb"))){
      printf("Ошибка открытия файла %s\n", argv[1]);
      return 0;
    }
    if (!(f2=fopen(argv[2], "wb"))){
      printf("Ошибка открытия файла %s\n", argv[2]);
      return 0;
    }
   file_copy(f1,f2);
   fclose(f1);
   fclose(f2);
return 0;
}

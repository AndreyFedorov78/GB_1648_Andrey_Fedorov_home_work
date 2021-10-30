#include "temp_functions.h"
#include "main.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  extern char *optarg;
  extern int optind, opterr, optopt;
  char fileName[200] = "data.csv"; // имя файла
  uint8_t select_month = 12;
  struct temp_data *td;
  struct year_data result;
  char ret;
  int tmp = 13;  // небольшие костыли для правильного чтения месяца
  while ((ret = getopt(argc, argv, "f:m:h")) != -1)
  {
    switch (ret)
    {
    case 'h':
      printf(HELP_INFO, argv[0]);
      return 0;
      break;
    case 'f':
      sprintf(fileName, "%s", optarg);
      break;
    case 'm':
      if (sscanf(optarg, "%d", &tmp) == 1)
        tmp--;
      select_month = (tmp > 12 || tmp < 0) ? 12 : (uint8_t)tmp;
      break;
    }
  }
  td = read_file(fileName); // читаем все данные в список и получаем указатель на него
  sort_list(td);            // сортируем список по дате
  while (td != NULL)        // цикл по годам
  {
    printf("Анализ температуры за %d год\n", year_analyse(&td, &result)); // анализируем год и сразу освобождаем память
    print_analyse(&result, select_month);                                 // выводим результаты по году
  }

#ifdef DEBUG
  print_list(td); //  этой функцией я проверял сортировку,
                  //сейчас она ничего не выводит, тк к этому месту список уже стерт
#endif
  return 0;
}

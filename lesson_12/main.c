/*
Доработать программу из Домашнего задания(вашего) 10.
Опции командной строки теперь необходимо обрабатывать через getopt()
По возможности использовать динамическую аллокацию памяти для массивов вместо
статической(malloc/free)
пример
Опция -f <filename> - имя файла для генерации
Опция -n <count> - количество значений для генерации
Опция -v - подробный вывод. Если эта опция присутствует, программа должна генерировать отладочные сообщения, если программа собрана с -DDEBUG
*/

#include "main.h"  // все остальные инклуды там

extern char *optarg;
extern int optind, opterr, optopt;

int main(int argc, char **argv)     // всю работу с файлом буду делать в теле основной процедуры
{
  time_t now;      // дата от которой начнутся измерения
  temp_t temp;     // структура с температурой
  char str[17];    // буфер день(2)+месяц(2)+год(4)+3*';'+температура(4)+ \n + \0 в конце строки итого 17
  FILE *f;
  char *message;
  char fileName[200]; // имя файла
  sprintf(fileName,FILENAME);
  uint16_t numOfMes = NUM_OF_MES; // колчество записей
  bool v =false;
  srand(time(NULL));
  now=time(NULL)+ (rand()%1000-500) * DTS;  // назначаем случайную дату  (DTS - количество сек в дне)

  /*
  Задание 12 работа с getopt();
  */
  opterr = 0;
  char ret;
  while ((ret = getopt(argc, argv, ":f:n:v")) != -1) {
    switch(ret) {
      case 'f' :
        sprintf(fileName,"%s",optarg);
        break;
      case 'n' :
        sscanf(optarg,"%hu",&numOfMes);
        break;
      case 'v' :
        #ifdef DEBUG
          v = true;
        #else
          printf("данная сборка не поддерживает вывод промежуточной информации\n");
        #endif
        break;
      case 'h' :
        printf("%s -f 'имя выходного файла' -n 'количество измерений' ", argv[0] );
        #ifdef DEBUG
           printf(" -v (вывод отладочной информации) ");
        #endif
        printf("\n");
        return(0);
        break;
     }
    }
    // в 10 дз я не хранил массив в пямяти, а сразу записывал данные в файл
    // поэтому не знаю где применить malloc, вот решил использовать буфер для вывода сообщений
    #ifdef DEBUG
    if (v) {
      message = malloc(1000);
      char *nextMsg = message;
      sprintf(nextMsg,"Включен режим 'debug'\n");
      nextMsg += strlen(nextMsg);
      sprintf(nextMsg,"Имя выходного файла: '%s'\n",fileName);
      nextMsg += strlen(nextMsg);
      sprintf(nextMsg,"Количество измерений: %d\n", numOfMes);
      printf("%s",message );
      free(message);
    }
    #endif


    f=fopen(fileName, "a");  // открываем файл на добавление
    if (!f){
      printf("ошибка открытия фала");
      return 0;
    }
    for (uint16_t i=0; i < numOfMes; i++){ // будем записывать 10 измерений начиная со случайной даты
      t_push_date(&temp,now + i * DTS);  // заносим текущую дату
      t_fake_measure(&temp); // измеряем температуру
      t_print(str,temp); // формируем строку в буфере
      fprintf(f,"%s",str); // сохраняем её в файле
    }
    fclose(f);
    return 0;
  }

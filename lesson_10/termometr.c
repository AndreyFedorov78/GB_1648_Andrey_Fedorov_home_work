#include "termometr.h"


void t_push_date (struct temp_data *data, const time_t time)
{
  struct tm *u;
  u = localtime(&time);
  data->day = u->tm_mday;    // можно сделать (*data).day, но компилятор подсказал '->' и мне такой вид понравился
  data->month = u->tm_mon+1;  // tm_mon считает месяцы не с 1 а с 0
  data->year = u->tm_year+1900; // 'C' считает что до 1900 года мир не существовал
}


void t_fake_measure (struct temp_data *data)
{
  data->temp = rand()%80-40;
}


void t_print (char *str, const struct temp_data data)
{
   sprintf(str, "%d;%d;%d;%d\n", data.day, data.month, data.year, data.temp);
}

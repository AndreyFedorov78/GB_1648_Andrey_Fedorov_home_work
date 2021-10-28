#ifndef TRMOMETR_H
#define TRMOMETR_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct temp_data{
  int day, month, year, temp;
};

void t_push_date (struct temp_data *data,  const time_t time); // заносит время в структуру
void t_fake_measure (struct temp_data *data); // эмулирует измерение температуры
void t_print (char *str, const struct temp_data data); // переводит данные в строку

typedef struct temp_data temp_t;

#endif

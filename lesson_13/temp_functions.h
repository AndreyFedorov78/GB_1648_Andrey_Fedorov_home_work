#ifndef TEMP_FUNCTIONS_H
#define TEMP_FUNCTIONS_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#define BUFF_SIZE 25
#define PRINT_RESYLTS "макс: %3dС, мин: %3dС,  средняя: %3dС\n"
#define NO_RESYLTS "нет статистики за данный период\n"

struct temp_data
{
    struct temp_data *next_element; // следующая запись
    time_t date;                    // дата время измерения
    int8_t temp;                    // температура
};

struct common_data                  // вспомогательная структура с минимами и максимумами 
{
    int8_t t_max, t_min, t_average;  // результаты анализа месяца/года
    bool changed;                    // отметка о том, что по месяцу были данные 
};

struct year_data                     // структура с полными данными по году
{
    struct common_data year;         // год 
    struct common_data month[12];    // и 12 месяцев  
};

struct temp_data *create_element(struct temp_data *td);             // добавление элемента
struct temp_data *delete_element(struct temp_data *td);             // удаление элемента
struct temp_data *read_file(const char *filename);                  // чтение всего файла в структуру
void sort_list(struct temp_data *td);                               // будем сортировать банальным пузырьком
int get_month(struct temp_data *td);                                // опреденяет месяц текущего элемента
int get_year(struct temp_data *td);                                 // опреденяет год текущего элемента
uint16_t year_analyse(struct temp_data **td, struct year_data *ys); // анализ года
void print_analyse(struct year_data *ys, uint8_t month_choose);     // вывод результатов анализа

void read_string(FILE *f, char *buff, const uint8_t buf_size);   // чтение строки из файла
bool parse_string(const char *buff, struct temp_data *td); // проверка и парсинг строки

#ifdef DEBUG
void print_list(struct temp_data *st); // Вывод всего списка на экран
#endif

#endif
#include "temp_functions.h"

struct temp_data *create_element(struct temp_data *td)   
{
    struct temp_data *result = malloc(sizeof(struct temp_data)); // создали элемент
    result->next_element = td;                                   // сделали ссылку на предыдущий
    return result;                                               // вернули новый
}

struct temp_data *delete_element(struct temp_data *td)
{
    struct temp_data *result = td->next_element; // возвражаем ссылку на уменьшенный список
    free(td);                                    // удаляем крайний элемент
    return result;
}

struct temp_data *read_file(const char *filename)
{
    struct temp_data *td = NULL;                  // последний элемент списка должен быть инициализирован NULL
    FILE *f;
    char buff[BUFF_SIZE];                         
    int line_cnt = 1;                             // счетчик срок для выдачи ошибок
    f = fopen(filename, "r");
    if (!f)
    {
        fprintf(stderr, "Ошибка открытия фала\n");
        return NULL;
    }
    td = create_element(td);                      // создаем пустой элемент
    while (1)
    {
        read_string(f, buff, BUFF_SIZE);
        if (buff[0] == EOF)
            break;
        if (parse_string(buff, td))               // если данные считанны создаем элемент для следующей итерации
            td = create_element(td);
        else
            fprintf(stderr, "Ошибка в строке %d: '%s'\n", line_cnt, buff);
        line_cnt++;
    }
    fclose(f);
    td = delete_element(td);                     // в начале списка у нас остался пустой элемент, удаляем его
    return td;
}

bool parse_string(const char *buff, struct temp_data *td)
{
    int temp;
    struct tm date;
    if (sscanf(buff, "%d;%d;%d;%d;%d;%d", &(date.tm_mday), &(date.tm_mon), &(date.tm_year), &(date.tm_hour), &(date.tm_min), &temp) != 6)
        return false; // данные не считались
    date.tm_mon--;  // месяцы нумеруются с 0
    date.tm_year -= 1900;  // возможно для маков и линукса это разные цифры 
    if ((td->date = mktime(&date)) == -1)
        return false; // ошибка формата даты
    if (temp > -100 && temp < 100)
        td->temp = temp;
    else
        return false; // ошибка условия по температуре (-99 < t < 99)
    return true;
}

void read_string(FILE *f, char *buff,const uint8_t buf_size)
{
    char c;
    uint8_t n = 0;
    while (((c = fgetc(f)) != '\n')  )  // читаем строку и контролируем переполнение
    {                                                       
        *buff = c;
        buff +=(n < buf_size - 1)? 1 : 0; // если строка длиннее buf_size она точно ошибочная
        if (c == EOF)
            break;
    }
    *buff = 0;
    return;
}

void sort_list(struct temp_data *td)
{
    struct temp_data *pointer = td;
    struct temp_data tmp;
    bool replaced = true;

    while (replaced)
    {
        replaced = false;
        while (pointer->next_element != NULL)
        {
            if ((pointer->date) < (pointer->next_element->date))
            {
                tmp.temp = pointer->temp; // делаем перестановку данных не трогая указатели
                tmp.date = pointer->date;
                pointer->temp = pointer->next_element->temp;
                pointer->date = pointer->next_element->date;
                pointer->next_element->temp = tmp.temp;
                pointer->next_element->date = tmp.date;
                replaced = true;
            }
            pointer = pointer->next_element;
        }
    }
}

int get_month(struct temp_data *td)
{
    return localtime(&(td->date))->tm_mon;
}

int get_year(struct temp_data *td)
{
    return localtime(&(td->date))->tm_year + 1900;
}

uint16_t year_analyse(struct temp_data **td, struct year_data *ys)
{
    if (td == NULL)
        return 0; // не должно такого случиться но вдруг!
    uint16_t result;
    result = get_year(*td);
    int y_counter = 0, m_counter = 0;
    uint8_t y_max, y_min, m_max, m_min;
    long long int m_average = 0, y_average = 0;
    // инициализация переменных
    ys->year.t_max = (*td)->temp;
    ys->year.t_min = (*td)->temp;
    ys->year.changed = true;
    for (uint8_t i = 0; i < 12; i++)
        ys->month[i].changed = false;
    ys->month[get_month(*td)].changed = true;
    ys->month[get_month(*td)].t_min = (*td)->temp;
    ys->month[get_month(*td)].t_max = (*td)->temp;

    while (get_year(*td) == result)  // обрабатываем только один год
    {
        y_counter++;
        m_counter++;
        if (ys->month[get_month(*td)].t_min > (*td)->temp)
            ys->month[get_month(*td)].t_min = (*td)->temp;
        if (ys->month[get_month(*td)].t_max < (*td)->temp)
            ys->month[get_month(*td)].t_max = (*td)->temp;
        if (ys->year.t_min > (*td)->temp)
            ys->year.t_min = (*td)->temp;
        if (ys->year.t_max < (*td)->temp)
            ys->year.t_max = (*td)->temp;
        y_average += (*td)->temp;
        m_average += (*td)->temp;
        /*
        в условии определения конца месяца, пержде чем обращяться к следующиму элементу нужно убедиться что он существует
        поэтому вначале делаем проверку на NULL
        */
        if (((*td)->next_element == NULL) ? 1 : get_month(*td) != get_month((*td)->next_element))  // последний элемент месяца
        {
            ys->month[get_month(*td)].t_average = m_average / m_counter;  // считаем среднее
            m_counter = 0;                                                // и все сбрасываем
            m_average = 0;
            if ((*td)->next_element != NULL)  // если следующий месяц настенет то инициализируем минимумы и максимумы
            {
                ys->month[get_month((*td)->next_element)].changed = true;
                ys->month[get_month((*td)->next_element)].t_min = (*td)->next_element->temp;
                ys->month[get_month((*td)->next_element)].t_max = (*td)->next_element->temp;
            }
        }
        *td = delete_element(*td); // удаляем элемент
        if (*td == NULL)
            break;
    }
    ys->year.t_average = y_average / y_counter; // среднее по году
    return result;
}

void print_analyse(struct year_data *ys, uint8_t month_choose) // номера месяцев 0-11, 12 - вывод всех месяцев
{
    static char *name[] = {"Январь  ", "Февраль ", "Март    ", "Апрель  ","Май     ","Июнь    ","Июль    ","Август  ","Сентябрь","Октябрь ","Ноябрь  ","Декабрь "};
    printf(PRINT_RESYLTS, ys->year.t_max, ys->year.t_min, ys->year.t_average); // вывод данных по году
    printf("\n");
    for (uint8_t i = 0; i < 12; i++)
    {
        if (month_choose != 12)  // если надо вывести только один месяц меняем i 
            i = month_choose;  
        printf("за месяц %s: ", name[i]);
        if (ys->month[i].changed)
            printf(PRINT_RESYLTS, ys->month[i].t_max, ys->month[i].t_min, ys->month[i].t_average); // вывод данных по месяцу
        else
            printf(NO_RESYLTS);  // если данных нет
        if (month_choose != 12)  // если выводим только один месяц то прерываем цикл на первой итерации
            break;
    }
    printf("\n\n");
    return;
}

#ifdef DEBUG
void print_list(struct temp_data *st) 
{
    while (st != NULL)
    {
        printf("%2d/%2d/%2d t=%3dC\n", localtime(&(st->date))->tm_mday, localtime(&(st->date))->tm_mon, localtime(&(st->date))->tm_year, st->temp);
        st = st->next_element;
    }
}
#endif
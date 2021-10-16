/*
Пользователь вводит строку вида 12345+5678-1235/2567*12356
Программа должна выполнить все операции по порядку. То есть сначала 12345+5678
Потом -1235
потом /2567
и так далее.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define STRING_SIZE 1000 // длина строки в символах
#define IS_NUMBER(ch) (ch >= '0' && ch <= '9')
#define ISNOT_ERROR(ch) (IS_NUMBER(ch) || ch == '+' || ch == '*' || ch == '-' || ch == '/')


void get_string(char *str, const uint16_t max); // чтение строки с клавиатуры
int calculate(char *str); // расчет выражения
int get_number(char **str); // чтение одного числа
bool check_string(char *str); // проверка строки


int main(int argc, char const *argv[]) {
  char str[STRING_SIZE+1] = {0};
  while (!(str[0] =='0' && str[1] =='\0')){
    printf("Введите математическое выражение из целых чисел или 0 для выхода \n");
    get_string(str,STRING_SIZE);
    if (check_string(str)) printf("результат: %d\n", calculate(str));
    else printf("ошибка в выражении\n");
  }
  return 0;
}


int calculate(char *str)
{
  int result=get_number(&str);
  while (*str != '\0'){
    switch (*str) {
      case '+':
        str++;
        result=result+get_number(&str);
        break;
      case '-':
        str++;
        result=result-get_number(&str);
        break;
      case '*':
        str++;
        result=result*get_number(&str);
        break;
      case '/':
        str++;
        result=result/get_number(&str);
        break;
    }
  }
  return result;
}


int get_number(char **str)
{
  int result = 0;
  while (IS_NUMBER(**str)){
    result= result *10 + **str - '0';
    (*str)++;
  }
  return result;
}


void get_string(char *str, const uint16_t max)
{
  char *pointer = str;
  while (((*pointer++ = getchar()) != '\n') && (pointer - str < max)){}
  *(--pointer)='\0';
}


bool check_string(char *str)
{
  /*
  два оператора подряд не будут считаться ошибкой
  выражение 1+-2*+1 = 1+0-2*0-1
  деление на 0 не проверяется
  */

  while (ISNOT_ERROR(*str)) str++;
  return *(str) == '\0';
}

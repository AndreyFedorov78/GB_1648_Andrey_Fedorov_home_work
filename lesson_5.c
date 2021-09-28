#include <stdio.h>
#include <stdbool.h>
/*
Распечатать первые n простых чисел (простое число X - это такое число X >= 2 и делится только на 1 и на себя).
Пример:
Пользователь вводит 5 - значит надо вывести первые 5 простых чисел
2 3 5 7 11
На пункт "домашние задания" в методичке не обращаем внимания
*/

int get_int_from_prompt(void);  // функция запроса числа, возвращает -1 при ошибочном вводе
int is_prime(int x);  //  проверка является ли число простым
void print_primes(int n); // вывод n простых чисел
void divide_primes(int x);  // простите не сдержался, дописал функцию нахождения множетелей

int main(void)
{
  int input;
  printf("Введите количество простых чисел, которое Вы хотите получить: ");
  do {
    input = get_int_from_prompt();
  } while (input <1);
  printf("Вот список  из %d простых чисел: ", input);
  print_primes(input);

 //было не остановиться
 printf("\nВведите число для разложения на множители: ");
 do {
   input = get_int_from_prompt();
 } while (input <1);
 divide_primes(input);


}


int get_int_from_prompt(void)
{
  int result = 0;
  if (!scanf("%d", &result)){
    printf("ошибка в веденных данных\n");
    while ((getchar()) != '\n');  // это место списано с Дмитрия Прядко
    return -1;
  }
  return result;
}


int is_prime(int x)
{
  if (x<4) {  //  2,3 - простые числа // а вот 1 оказывается не является простым :((((
    return true;
  }
  for (int i=2; i<x; i++){
    if (!(x%i)) {     // почти никогда не писал на С,
      return false;   // поэтому просто прихожу в восторг от таких конструкций
    }
  }
  return true;
}

void print_primes(int n)
{
  int count = 0;
  int i = 2;
  while (count<n){
    if (is_prime(i)){
     printf("%d ",i);
     count++;
   }
   i++;
  }
  printf("\n");
}

void divide_primes(int x)
{
  int count = 0;
  int i = 2;
  printf("%d = ", x);
  while (i<=x){
    if (is_prime(i)&&(!(x%i))){

     printf((count) ? " X %d" : "%d",i);
     x=x/i;
     count++;
   } else {
   i++; }
  }
  printf("\nнайдено %d множителей\n", count);
}

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/*
Домашнее задание:
Программа "стрельба в мишень"
Пользователь вводит с клавиатуры 3 числа типа float(X, Y, Radius)
Первая функция вида
bool get_user_input(float *X, float *Y, float *R)
считывает с клавиатуры значения координат X,Y и радиуса, и проводит валидацию входных значений.(количество успешных преобразований от функции scanf, неотрицательный и ненулевой радиус и так далее)
Если происходит ошибка - функция возвращает false. В этом случае программа с ошибкой завершается.
Вторая функция вида
bool is_target_hit(float X, float Y, float R)
проверяет, попал ли пользователь в мишень. Формула X*X + Y*Y < R*R
Результат выводится на экран(printf)
*/

#define GOAL_TRUE "Поздравляем! Вы попали в мишень!\n"
#define GOAL_FALSE "Вы не попали в мишень.\n"


bool get_user_input (float *X, float *Y, float *R);
bool is_target_hit (float X, float Y, float R);

int main(void)
{
  float x, y, radius = 0;
  bool finish = false;
  while (!finish) {
    if (get_user_input (&x, &y, &radius)){
      finish = is_target_hit (x, y, radius);
      printf((finish)? GOAL_TRUE : GOAL_FALSE );
    } else {
      printf("Ошибка ввода данных.\nBye!\n");
      return 0;
    }
  }
  return 0;
}


bool get_user_input (float *X, float *Y, float *R)
{
  static unsigned int count;
  bool result;
  if (!*R){
    count=1;
    printf("Попытка №1,  введите координаты точки (x,y), и не нулевой диаметр мишени: ");
    result = (scanf("%f%f%f", X, Y, R) == 3);
  } else {
    count++;
    printf("Попытка №%d,  введите координаты точки (x,y): ", count);
    result = (scanf("%f%f", X, Y) == 2);
  }
  return result;
}


bool is_target_hit (float X, float Y, float R)
{
  return (X*X+Y*Y)<(R*R);
}

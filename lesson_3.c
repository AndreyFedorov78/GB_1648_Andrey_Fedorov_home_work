#include <stdio.h>
#include <math.h>

/* Домашнее задание к уроку 3 :

Пользователь вводит радиус через scanf.
Нужно вычислить для указанного радиуса R:

Длину окружности. Формула 2 * Pi * R
Площадь круга. Формула Pi * R * R
Объем шара. Формула 4/3 * Pi * R * R * R
Pi можно принять за 3.1415 либо использовать константу M_PI подключив #include <math.h>
Результаты вывести в консоль через printf */

int main(void){
   float r, l, s, v; // определяем общие переменные для всех задач
   printf ("Введите радиус:");
   scanf("%f", &r);
   l = 2 * r * M_PI;
   s = l/2 * r;
   v = 4.0f / 3 * s;
   printf("Радиус: %0.2f,\nДлинна окружности: %0.2f;\nПлощадь круга: %0.2f;\nОбъем шара: %0.2f;\n", r, l, s, v);
}

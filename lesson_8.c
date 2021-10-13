/*
Реализовать алгоритм сортировки массива(любой на ваше усмотрение)
https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D1%81%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B8
И продемонстрировать его работу.
Исходные данные для массива либо вводятся вручную, либо берутся случайные значения через rand()
github:
https://github.com/008agent/c_basics_1648/blob/master/lesson8/main.c
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

/*
несколько раз собирался отправить дз и находил сбои алгоритма
устал писать и стирать отладочные выводы информации,
поэтому добавил режим компиляции "DEBUG"
*/

//#define DEBUG
#define DEBUG_PRINT printf("\n%d\n", ref);print_array(arr,n,true);print_array(arr,l+1,false);print_array(&arr[r],n-r,true);

// массивы на которых получались ошибки
#define EXAMPLE_1 {1,2,10,20,10,15,33,1,2,0}
#define EXAMPLE_2 {1,4,4,4,4,4,4,4,4,4}
#define EXAMPLE_3 { 28,-33,  8,-92, 62,-75, -9, 44,-62, 70}
#define EXAMPLE_4 { 58, 94, 62, 98,-24, 97, 14,-94, 60,-90}
#define EXAMPLE_5 { 40, 97,-55, 27,-13, 41, 65,  9,-24,  1}

void print_array(int arr[], int8_t n, bool cr_lf ); //  функция вывода массива
void qsort_array(int arr[], int8_t n);              //  сортировка quicksort
void fill_array(int arr[], int8_t n);               //  случайными числами
void show_sort(int arr[], int8_t n);                // вывод массива, сортировка, повторный вывод
void replace_elements (int arr[], int8_t x, int8_t y); // перестановка элементов в массиве


int main(void)
{
  srand(time(NULL));
  int a[10] = EXAMPLE_1;  // сортируем один заданный массив
  show_sort(a,10);
  for (int8_t i=0; i<10; i++){ // и 10 случайных
    fill_array(a,10);
    show_sort(a,10);
  }
  return 0;
}


void qsort_array(int arr[], int8_t n)
{
  int8_t r=0, l=n-1; // индексы начала правого и конца левого множеств
  int ref = arr[n/2]; // опорный элемент
  while (r<=l) {
    while (arr[l] > ref)  l--;
    while (arr[r] < ref ) r++;
    if (r <= l) replace_elements (arr, r++, l--);
  }
  #ifdef DEBUG
  DEBUG_PRINT
  #endif
  if (l > 0 ) qsort_array(arr,l+1);       // левый блок
  if (r < n ) qsort_array(&arr[r],n-r);   // правый блок
}


void print_array(int arr[], int8_t n, bool cr_lf)
{
  printf("{");
  for (int8_t i=0; i<n; i++){
    printf((i<n-1)?"%3d,":"%3d", arr[i] );
  }
  printf((cr_lf)?"}\n":"}");
}


void replace_elements (int arr[], int8_t x, int8_t y)
{
  int tmp = arr[x];
  arr[x] = arr[y];
  arr[y] = tmp;
}


void fill_array(int arr[], int8_t n){
  for (int8_t i=0; i<n; i++){
    arr[i]=rand()%198-99;
  }
}


void show_sort(int arr[], int8_t n){
  print_array(arr,n, false);
  printf(" => ");
  qsort_array(arr,n);
  print_array(arr,n, true);
}

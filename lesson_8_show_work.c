/*
Демонтстрация работы алгоритма QuickSort
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


// массивы на которых получались ошибки
#define EXAMPLE_1 {1,2,10,20,10,15,33,1,2,0}
#define EXAMPLE_2 {1,4,4,4,4,4,4,4,4,4}
#define EXAMPLE_3 { 10,1, 1, 1, 1, 10, 9, 20,20, 10}
#define EXAMPLE_4 { 58, 94, 62, 98,-24, 97, 14,-94, 60,-90}
#define EXAMPLE_5 { 40, 97,-55, 27,-13, 41, 65,  9,-24,  1}
// кол-во элементов массива
#define N 10

void print_array(int arr[], int8_t n, bool cr_lf ); //  функция вывода массива
void qsort_array(int arr[], int8_t n);              //  сортировка quicksort
void fill_array(int arr[], int8_t n);               //  случайными числами
void show_sort(int arr[], int8_t n);                // вывод массива, сортировка, повторный вывод
void replace_elements (int arr[], int8_t x, int8_t y); // перестановка элементов в массиве

int a[N] = EXAMPLE_3;  // сортируем один заданный массив

int main(void)
{
    show_sort(a,10);
  return 0;
}


void qsort_array(int arr[], int8_t n)
{
  int8_t r=0, l=n-1; // индексы начала правого и конца левого множеств
  int ref = arr[n/2]; // опорный элемент
  while (r<=l) {
    while (arr[l] > ref)  {l--; };
    while (arr[r] < ref ) r++;
    if (r <= l)
    {
      print_array(a,N,false);
      printf(" // ");
      print_array(arr,n,false);
      printf(" /// %d [%d] <=> %d [%d] ref(%d) \n", arr[r],r, arr[l],l,ref );
    replace_elements (arr, r++, l--);
  }


  }

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
  qsort_array(arr,n);
  print_array(arr,n, true);
}

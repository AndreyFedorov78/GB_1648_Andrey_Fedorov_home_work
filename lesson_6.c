#include <stdio.h>
#include <stdbool.h>

#define buff_0_9 (buff >= '0' && buff <= '9')
#define buff_a_z (buff >= 'a' && buff <= 'z')
#define buff_A_Z (buff >= 'A' && buff <= 'Z')
#define buff_space (buff == ' ')
#define buff_A_F (buff >= 'A' && buff <= 'F')
#define buff_a_f (buff >= 'a' && buff <= 'f')
#define buff_hex (buff_A_F || buff_a_f)
#define buff_1_9 (buff >= '1' && buff <= '9')
#define buff_dot (buff == ',' || buff == '.')


void char_calculate(void);  // считаем виды символов
double get_double_from_char(void);  // читаем  double из буфера

int main(void)
{
  char_calculate();
   printf("Введите  вещественное число (возможно использование префиксов 0x или 0b) :");
  printf("результат %f\n",get_double_from_char());
}


void char_calculate(void)
{
   printf("Введите любую строку, будем её анализировать:");
  char buff;
  int count = 0, count_a_z = 0, count_A_Z = 0, count_dig = 0, count_space = 0;
  float  perc_a_z, perc_A_Z, perc_dig, perc_space;
  while ( (buff = getchar()) != '\n'){
   count ++;
   count_a_z += buff_a_z? 1 : 0;
   count_A_Z += buff_A_Z? 1 : 0;
   count_dig += buff_0_9? 1 : 0;
   count_space += buff_space? 1 : 0;
  }
   perc_a_z = 100.0f * count_a_z / count ;
   perc_A_Z = 100.0f * count_A_Z / count ;
   perc_dig = 100.0f * count_dig / count ;
   perc_space = 100.0f * count_space /count ;
   printf("в строке %d (%0.1f%%) пробелов, ", count_space, perc_space );
   printf("%d (%0.1f%%)  цифр, ", count_dig, perc_dig );
   printf("%d (%0.1f%%) английских букв верхнего регистра, ", count_A_Z, perc_A_Z );
   printf("%d (%0.1f%%) английских букв нижнего регистра\n", count_a_z, perc_a_z );
}


double get_double_from_char(void)
{
  // отнесемся к пользователю с пониманием
  // и будем игнорировать любые неверные символы
  // разделитель десятичной части будем принимать как '.' так и ','
  double result=0;  // результат
  int8_t token = 1; // знак
  int8_t base  = 10 ; //  система счисления
  int devider = 1 ;
  bool start = false; // флаг начала обработки численной части
  bool dot = false; // флаг обработки дробной части
  char buff = ' ';  // буфер
  while ( buff != '\n'){
    buff = getchar();
    if (!start) {         // обработка строки до начала цифр
      if (buff == '-') {   // отрицательное число
        token = -1;
      } else if (buff == '0') {  // возможна смена системы счисления
        buff = getchar();
        switch (buff) {
          case 'x':     // 0x
          base = 16;
          break;
          case 'b':  // 0b
          base = 2;
          break;
        }
      }         // нет else, так как мы могли считать символ после нуля
      if ( buff_1_9 || buff_hex || buff_dot){  // если цифра, то переходим в режим чтения числа
        start = true;
      }
    }
    if (start){
      if buff_dot {   //  если точка то переключаем режим расчета
        dot = true;
      } else if (buff_0_9 || buff_hex) {  // если цифра то вычесляем её
        int figure = 0;
        if buff_0_9 {
          figure = buff - '0';
        } else if buff_hex {
          figure = 10 + (buff_A_F? buff - 'A' : buff - 'a') ;
        }
        if (figure < base) {   //  избегаем варианта 0b01201A001
          if (dot){        // расчет дробной части
            devider *= base;
            result = result + 1.0f * figure / devider;
          } else {  // расчет целой части
            result = result * base + figure;
          }
        }
      }
    }

  }
  return token * result;
};

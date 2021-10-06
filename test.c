#include <stdio.h>
#include <stdint.h>
uint16_t x, y, z;
int main(void)
{
  printf("Проверка поведения программы при переполнении переменной \n x++, z=x+3 \n\n");
  x = 0xFFFA;
  for (y=0;y<10;++y){
    x++; z=x+3;
    printf("x=%5d z=%5d;\n",x,z);
  }
  return 0;
}

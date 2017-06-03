#include "timer.h"
#include "i2c.h"
#include "VL6180X.h"
#include "printf.h"
#include "uart.h"
 
int  main() {
  int count = 10;
printf_init();  
uart_init();
  i2c_init();
  vl6180x_init();
  printf("I am = %x \n", vl6180x_get_whoami());
  timer_init();
  while(count<50){
    short x,y;
   vl6180x_read_tof_sensor(&x, &y);
   printf("sensor measurements: x is%d and y is %y\n",x,y);
   count++;
  }

return 0;
}

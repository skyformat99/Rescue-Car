#include "gpio.h"
#include "motor.h"
#include "timer.h"
#include "printf.h"
#include "tof.h"

void main() {
  timer_init();
  gpio_init();
  printf_init();
  /*while(1){
    reverse_motion();
    }*/
  tof_init();
  //printf("Hello, world!\n");
}

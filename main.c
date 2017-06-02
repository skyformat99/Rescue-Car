#include "gpio.h"
#include "motor.h"
#include "timer.h"

void main() {
  timer_init();
  gpio_init();
  motor_init();
  while(1){
    reverse_motion();
  }
  //printf("Hello, world!\n");
}

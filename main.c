//#include "timer.h"
#include "gpio.h"
//#include "gpioextra.h"
//#include "printf.h"
//#include "motor.h"
//#include "circular.h"

void main(void){
  gpio_set_output(GPIO_PIN23);
  gpio_set_output(GPIO_PIN22);
  gpio_set_output(GPIO_PIN5);
  gpio_set_output(GPIO_PIN6);
  gpio_write(GPIO_PIN23, 0);
  gpio_write(GPIO_PIN22, 1);
  gpio_write(GPIO_PIN5, 0);
  gpio_write(GPIO_PIN6, 1);
  while(1){}

  //  delay(500);
}

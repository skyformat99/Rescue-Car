#include "gpio.h"
#include "led_lights.h"
#include "timer.h"


#define ON 1
#define OFF 0

/*Initializes the LEDs*/
void led_light_init(unsigned int left, unsigned int right){
  left_pin = left;
  right_pin = right;
  gpio_set_output(left_pin);
  gpio_set_output(right_pin);
}

void left_signal(){
  gpio_write(left_pin, ON);
  delay_ms(1);
  gpio_write(left_pin, OFF);
}
void right_signal(){
  gpio_write(right_pin, ON);
  delay_ms(1);
  gpio_write(right_pin, OFF);
}
void dance_pattern(){
int counter = 0;
// gpio_set_output(GPIO_PIN0);
gpio_set_output(GPIO_PIN9);
gpio_set_output(GPIO_PIN10);
gpio_set_output(GPIO_PIN11);
int prev_pin = GPIO_PIN11;
while(1){
  int mode_of_num = counter%3;
  if(mode_of_num == 0){
    toggle_leds(GPIO_PIN1, prev_pin);
    prev_pin = GPIO_PIN1;
  }else if(mode_of_num == 1){
    toggle_leds(GPIO_PIN10, prev_pin);
    prev_pin = GPIO_PIN10;
  }else if(mode_of_num == 2){
    toggle_leds(GPIO_PIN11, prev_pin);
    prev_pin = GPIO_PIN11;
  }
  printf("Previus pin%d\n",prev_pin );
counter++;
}
}
void toggle_leds(unsigned int current_pin, unsigned int prev_pin){
  gpio_write(current_pin, ON);
  delay_ms(100);
  gpio_write(prev_pin, OFF);
}
void alarm_pattern(){
return;
}


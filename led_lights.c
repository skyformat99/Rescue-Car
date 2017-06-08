#include "gpio.h"
#include "led_lights.h"
#include "timer.h"

unsigned int left_pin, right_pin, back_pin;

/*Initializes the LEDs*/
void led_lights_init(unsigned int left, unsigned int right, unsigned int back){
  left_pin = left;
  right_pin = right;
  back_pin = back;
  gpio_set_output(left_pin);
  gpio_set_output(right_pin);
  gpio_set_output(back_pin);
}

void signal(unsigned int pin){
  gpio_write(pin, ON);
  delay_ms(1000); //change value
  gpio_write(pin, OFF);
  delay_ms(1000); //change value
}

void signal_left() {
  signal(left_pin);
}

void signal_right() {
  signal(right_pin);
}

void signal_back(int mode) {
  gpio_write(back_pin, mode);
}

void alarm_pattern() {
  gpio_write(left_pin, ON);
  gpio_write(right_pin, ON);
  gpio_write(back_pin, ON);
  delay_ms(1000); //change value
  gpio_write(left_pin, OFF);
  gpio_write(right_pin, OFF);
  gpio_write(back_pin, OFF);
  delay_ms(1000); //change value
}

//////////////////////////////////////////////////
/*void dance_pattern(){
int counter = 0;
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
}*
}
void toggle_leds(unsigned int current_pin, unsigned int prev_pin){
  gpio_write(current_pin, ON);
  delay_ms(100);
  gpio_write(prev_pin, OFF);
  }*/

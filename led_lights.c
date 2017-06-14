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
  gpio_write(left_pin, 0);
  gpio_write(right_pin, 0);
  gpio_write(back_pin, 0);
}

void signal(unsigned int pin){
  int c = 3;
  while (c > 0) {  
    gpio_write(pin, ON);
    delay_ms(500); //change value
    gpio_write(pin, OFF);
    delay_ms(500); //change value
    c--;
  }
}

void signal_left() {
  signal(left_pin);
}

void signal_right() {
  signal(right_pin);
}

void signal_back() {
  signal(back_pin);
}

void alarm_pattern() {
  int c = 3;
  while (c > 0) {
    gpio_write(left_pin, ON);
    gpio_write(right_pin, ON);
    gpio_write(back_pin, ON);
    delay_ms(500); //change value
    gpio_write(left_pin, OFF);
    gpio_write(right_pin, OFF);
    gpio_write(back_pin, OFF);
    delay_ms(500); //change value
    c--;
 }
}


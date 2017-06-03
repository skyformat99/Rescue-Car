
#include "timer.h"
#include "gpio.h"
#include "gpioextra.h"
#include "printf.h"
#include "motor.h"
#include "circular.h"


const unsigned trigger = GPIO_PIN3;
const unsigned echo = GPIO_PIN2;
cir_t *cir;

unsigned get_distance(void) {
  // write hi for 10usec
  gpio_write(trigger, 1);
  delay_us(10);
  gpio_write(trigger, 0);

  unsigned start = timer_get_time();
  delay_us(149); // wait til device settles: 148 = time to go one inch
  while(!gpio_read(echo))
    ;

  unsigned end;
  while(gpio_read(echo) == 1)
    ;
  end = timer_get_time();

  // ((340M/S / 2) * 39.37inch / meter) / 10^6 = inch/usec
  return (end - start) / 149;
}

void main(void) {
  printf_init();
  timer_init();
  gpio_init();
  motor_init();
  cir = cir_new(); // initialize circular buffer
  gpio_set_output(trigger);
  gpio_set_input(echo);
  gpio_set_pulldown(echo);
  delay_ms(40);
  forward_motion();

  while(1) {
    unsigned distance = get_distance();
    printf("distance = %d inches\n", distance);
    delay_ms(1000);
    if(distance<5){
      reverse_motion();
      delay_ms(2000);
      right_turn(2000);
      forward_motion();
    }
  }
  // stop at the very end
}


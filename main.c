#include "interrupts.h"
#include "timer.h"
#include "gpio.h"
#include "gpioextra.h"
#include "printf.h"
#include "motor.h"
#include "path.h"
#include "distance.h"
#include "led_lights.h"

extern void clock_init();
extern int top;
extern int stack[128];

const unsigned trigger = GPIO_PIN3;
const unsigned echo = GPIO_PIN2;

//ultrasonic sensor
unsigned get_distance(void) {
  // write hi for 10usec
  gpio_write(trigger, 1);
  delay_us(10);
  gpio_write(trigger, 0);

  unsigned start = timer_get_time();
  delay_us(149); // wait til device settles: 148 = time to go one inch
  while(!gpio_read(echo));

  unsigned end;
  while(gpio_read(echo) == 1);
  end = timer_get_time();

  // ((340M/S / 2) * 39.37inch / meter) / 10^6 = inch/usec
  return (end - start) / 149;
}

/* Initialize distance and clock at beginning of main and run
display_distance() in forever while loop.*/
void main(void) {
    system_enable_interrupts();
    motor_init();
    led_lights_init(GPIO_PIN6, GPIO_PIN7, GPIO_PIN8);
    clock_init();
    distance_init();
    while (1) {
        if (!isEmpty()) {
        for (int i = 0; i <= top; i++) printf("i: distance is %d %d \n", i, stack[i]);
        } 
    }
 
/*  gpio_set_output(trigger);
  gpio_set_input(echo);
  gpio_set_pulldown(echo);
  delay_ms(40);
  forward_motion();

  while(1) {
    unsigned distance = get_distance();
    printf("distance = %d inches\n", distance);
    delay_ms(1000);
    unsigned left_distance;
    unsigned right_distance;
    if(distance<5){
      reverse_motion();
      delay_ms(2000);
      right_turn(2000);
      right_distance = get_distance();
      left_turn(2000);
      left_turn(2000);
      left_distance = get_distance();
      if (left_distance < right_distance){
	turn_right();
	turn_right();
      }
      forward_motion();
    }
  }
  // stop at the very end*/
}


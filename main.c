#include "clock.h"
#include "timer.h"
#include "gpio.h"
#include "motor.h"
#include "printf.h"
#include "sensor.h"
#include "distance.h"
#include "interrupts.h"

static int help = 0;
static const unsigned trigger = GPIO_PIN3;
static const unsigned echo = GPIO_PIN2;
static unsigned int audio_pin = GPIO_PIN2;
extern int sensor_flag;

void main(void){
//  gpio_init();
//  clock_init();
//  printf_init();
//  motor_init();
//  ultrasonic_init();
  audio_sensor_init();
//  system_enable_interrupts();
//  delay(3);
//  distance_init();
 // gpio_set_pullup(GPIO_PIN16);
   while (1) {
//    forward_motion();
//    display_distance();
 // if (audio_sensor_fetch() != 1)
    printf(" %d \n", audio_sensor_fetch());
/*    unsigned distance = get_distance();
    unsigned left_distance;
    unsigned right_distance;
    if (distance < 20) {
      reverse_motion();
      display_distance();
      right_turn(650);
      right_distance = get_distance();
      left_turn(650);
      display_distance();
      left_turn(650);
      left_distance = get_distance();
      display_distance();
      forward_motion();
      delay(1);
      stop();
      display_distance();
    }*/
  } 
}

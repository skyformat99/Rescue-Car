/* This file contains functions that implement the ultrasonic sensor. */

#include "interrupts.h"
#include "timer.h"
#include "gpio.h"
#include "gpioextra.h"
#include "gpioevent.h"
#include "printf.h"
#include "motor.h"
#include "path.h"
#include "distance.h"
#include "led_lights.h"
#include "sensor.h"

static int help = 0;
static const unsigned trigger = GPIO_PIN3;
static const unsigned echo = GPIO_PIN2;
static unsigned int audio_pin = GPIO_PIN5;
static int flag = 0; 

/* This getter function returns whether or not the program is currently in the function that calls the ultrasonic sensor. 
   @return the value of the flag of type int */
int get_flag() {
  return flag;
}

/* This getter function returns the value of the help flag, which indicates whether or not "HELP" should be flashed on the screen.
   @return the value of the help flag of type int */
int get_help() {
  return help;
}

/* This function clears the flag that toggles "warning" behavior (aka flashing "HELP" on the screen). */
void clear_help() {
  help = 0;
}

/*Adapted from Pat: This function uses the ultrasonic sensor to determine 
  the distance, in inches, of the obstacle from the user. */
unsigned get_distance(void) {
  // write high for 10usec
  flag = 1;
  gpio_write(trigger, 1);
  delay_us(10);
  gpio_write(trigger, 0);

  unsigned start = timer_get_time();
  delay_us(149); // wait til device settles: 148 = time to go one inch
  while(!gpio_read(echo));

  unsigned end;
  while(gpio_read(echo) == 1);
  end = timer_get_time();

  flag = 0;
  // ((340M/S / 2) * 39.37inch / meter) / 10^6 = inch/usec
  return (end - start) / 149;
}

/* This function initializes the audio sensor by setting up GPIO_PIN5 as an input pin that can enable interrupts. */
void audio_sensor_init() {
  gpio_set_function(GPIO_PIN5, GPIO_FUNC_INPUT);
  gpio_set_pullup(GPIO_PIN5);
  gpio_detect_falling_edge(GPIO_PIN5);
  interrupts_enable(INTERRUPTS_GPIO3); 
}

/* This function initializes the ultrasonic sensor to measure obstacle distances. */
void ultrasonic_init() {
  gpio_set_output(trigger);
  gpio_set_input(echo);
  gpio_set_pulldown(echo);
  delay_us(40);
}

/* Interrupt hanlder for the audio sensor, which triggers gpio interrupt that activates
   "warning" behavior.
void audio_sensor_vector(unsigned pc) {
  if (!gpio_check_and_clear_event(GPIO_PIN5)) return;
  help = 1; //check for this flag in main, and then flash LEDS/flash HELP on clock
}

 This function returns the value of the audio sensor's pin.
int audio_sensor_fetch() {
  return gpio_read(audio_pin);
}*/

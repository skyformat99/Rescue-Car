/*
 * This file contains functions that implement the perform computations of the distance the car has travelled.
 */

#include "odometer.h"
#include "gpio.h"
#include "timer.h"
#include "path.h"
#include "motor.h"
#include "armtimer.h"
#include "interrupts.h"
#include "printf.h"

#define TURN_SPEED 12.1 //get actual value
#define STRAIGHT_SPEED 14.5 //get actual value
#define DISTANCE_TIMER_INTERVAL 0x100 //set to 1 second = 10^6 us
#define DELAY_DISTANCE 24

// extern void displayNum(int d1, int d2, int d3, int d4, int c);

static unsigned int distance; 
static unsigned int total_time; //in us
static unsigned int mov_time; //in us
static unsigned int prev_mov;
static unsigned int prev_time;
static unsigned int count;
static int motor_flag = 0;

void distance_init() {
  distance = 0;
  mov_time = 0;
  total_time = 0;
  prev_time = timer_get_time()/1000000;
  prev_mov = FWD; //assume 1st move is forward
  count = 50000;
  armtimer_init(DISTANCE_TIMER_INTERVAL);
  armtimer_enable();
  armtimer_enable_interrupt();
  interrupts_enable_basic(INTERRUPTS_BASIC_ARM_TIMER_IRQ); 
}

unsigned int get_dist() {
  return distance;
}

void compute_distance() {
  if (!motor_flag) {
    gpio_write(GPIO_PIN19, 0);
    gpio_write(GPIO_PIN26, 0);
    motor_flag = 1;
  }
  else {
    gpio_write(GPIO_PIN19, 1);
    gpio_write(GPIO_PIN26, 1);
    motor_flag = 0;
  }
  //need to enable opposite of current power status to both motors; will flip rapidly
  if (get_flag()) return; //dont execute computations if in middle of ultrasound  
  if (count != 0) return;
  int cur_time = timer_get_time()/1000000;
  int cur_mov = get_dir();
  if ((cur_mov == FWD) || (cur_mov == REV)) {
    distance += (cur_time - prev_time)*STRAIGHT_SPEED;
  } else {
    distance += (cur_time - prev_time)*TURN_SPEED;
  }
  if (cur_mov != prev_mov) {
    push((total_time*10)+prev_mov);
    total_time = cur_time - prev_time;
  } else total_time += cur_time - prev_time;
  prev_time = cur_time;
  count = 50000;
  // printf("distance is %d \n", distance);
}

void distance_vector(unsigned pc) {
  if (armtimer_check_interrupt()) {
    count--;
    compute_distance();       
    armtimer_clear_interrupt();
  }
}

void display_distance() { 
  int d4 = distance % 10;
  int d3 = (distance/10) % 10;
  int d2 = (distance/100) % 10;
  int d1 = distance/1000;
  displayNum(d1, d2, d3, d4, 100);
}

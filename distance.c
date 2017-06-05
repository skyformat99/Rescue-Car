/*
 * This file contains functions that implement the clock.
 */

#include "clock.h"
#include "gpio.h"
#include "timer.h"
#include "path.h"
#include "motor.h"
#include "armtimer.h"
#include "printf.h"

//measure time to travel 50cm--> quotient is rate
#define TURN_SPEED 10; //get actual value
#define STRAIGHT_SPEED 20; //get actual value
#define DISTANCE_TIMER_INTERVAL 0x20 //1 second = 10^6 us

extern void displayNum(int d1, int d2, int d3, int d4, int c);

int distance;
unsigned int total_time; //in us
unsigned int mov_time; //in us
unsigned int prev_mov;

void distance_init() {
    distance = 0;
    mov_time = 0;
    total_time = 0;
    prev_mov = FWD; //assume 1st move is forward
    armtimer_init(DISTANCE_TIMER_INTERVAL);
    armtimer_enable();
    armtimer_enable_interrupt();
}

void compute_distance() {
    distance++;
    push(distance);
    printf ("in compute distance \n");
//  if ((get_dir() == FWD) || (get_dir() == REV)) distance += mov_time*STRAIGHT_SPEED
//  else if ((get_dir() == LEFT) || (get_dir() == RIGHT)) distance += mov_time*TURN_SPEED;
}

void distance_vector(unsigned pc) {
    if (armtimer_check_interrupt()) {
        compute_distance();       
        armtimer_clear_interrupt();
    }
}

//return time in move in milliseconds
/*static unsigned int time_in_move() {
  unsigned int time = timer_get_time();
  mov_time = 0;
  while (peek()%10 == prev_mov) mov_time = (timer_get_time() - time)/1000;
  prev_mov = peek();
  return (timer_get_time() - time)/1000;
}

void display_distance() { 
  gpio_write(GPIO_PIN27, 0); //for DP
  int prev_distance = 0;   
  while (prev_mov == peek()) displayNum(d1, d2, d3, d4, 1); //Display current distance repeatedly
  int prev_dist = compute_distance();
  if (prev_dist > 1000) {
    prev_dist -= 1000;  
  }
  d4 = prev_dist % 10;
  d3 = (prev_dist/10) % 10;
  d2 = (prev_dist/100) % 10;
  d1 = prev_dist/1000;
  displayTime(d1, d2, d3, d4, 1);
}*/

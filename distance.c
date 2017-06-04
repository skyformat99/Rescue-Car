/*
 * This file contains functions that implement the clock.
 */

#include "clock.h"
#include "gpio.h"
#include "timer.h"
#include "stack.h"

#define TURN_RATE = 10; //get actual value
#define STRAIGHT_RATE = 20; //get actual value

unsigned int d1, d2, d3, d4; 
int distance;
unsigned int mov_time; //in us
unsigned int prev_mov;

void distance_init() {
  d1 = d2 = d3 = d4 = 0; 
  distance = 0;
  mov_time = 0;
  prev_mov = 2; //assume 1st move is forward
}

//return time in milliseconds
unsigned int get_mov_time() {
  return mov_time/1000;
}

//return time in move in milliseconds
static unsigned int time_in_move() {
  unsigned int time = timer_get_time();
  mov_time = 0;
  while (peek() == prev_mov) mov_time = (timer_get_time() - time)/1000;
  prev_mov = peek();
  return (timer_get_time() - time)/1000;
}

void compute_distance() {
  if ((peek() % 10 == 2) || (peek() % 10 == 1)) distance += mov_time*STRAIGHT_RATE
  else if ((peek() % 10 == 0) || (peek() % 10 == 3)) distance += mov_time*TURN_RATE;
}

void display_distance() { 
  gpio_write(GPIO_PIN27, 0); //for DP
  int prev_distance = 0;   
  while (prev_mov == peek()) displayTime(d1, d2, d3, d4, 1); //Display current distance repeatedly
  int prev_dist = compute_distance();
  if (prev_dist > 1000) {
    prev_dist -= 1000;  
  }
  d4 = prev_dist % 10;
  d3 = (prev_dist/10) % 10;
  d2 = (prev_dist/100) % 10;
  d1 = prev_dist/1000;
  displayTime(d1, d2, d3, d4, 1);
}

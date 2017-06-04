
#include "clock.h"
#include "gpio.h"
#include "timer.h"
#include "stack.h"

unsigned int d1, d2, d3, d4; 
int distance;
unsigned int mov_time; //in us
unsigned int prev_mov;

void distance_init();

//return time in milliseconds
unsigned int get_mov_time();

//return time in move in milliseconds
static unsigned int time_in_move();

void compute_distance();

void display_distance(); 


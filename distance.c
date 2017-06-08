/*
 * This file contains functions that implement the clock.
 */

#include "clock.h"
#include "gpio.h"
#include "timer.h"
#include "path.h"
#include "motor.h"
#include "armtimer.h"
#include "interrupts.h"
#include "printf.h"

//measure time to travel 50cm--> quotient is rate
#define TURN_SPEED 7.854; //get actual value
#define STRAIGHT_SPEED 14.5; //get actual value
#define DISTANCE_TIMER_INTERVAL 0x100000 //set to 1 second = 10^6 us

//extern int stack[1024];
//extern int top;
//int c = 0;

extern void displayNum(int d1, int d2, int d3, int d4, int c);

static unsigned int distance;
static unsigned int total_time; //in us
static unsigned int mov_time; //in us
static unsigned int prev_mov;
static unsigned int prev_time;

void distance_init() {
    distance = 0;
    mov_time = 0;
    total_time = 0;
    prev_time = timer_get_time()/1000;
    prev_mov = FWD; //assume 1st move is forward
    armtimer_init(DISTANCE_TIMER_INTERVAL);
    armtimer_enable();
    armtimer_enable_interrupt();
    interrupts_enable_basic(INTERRUPTS_BASIC_ARM_TIMER_IRQ); 
}

unsigned int get_dist() {
    return distance;
}

void compute_distance() {
//    c++; printf("%d", c);
    int cur_time = timer_get_time()/1000;
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
}

void distance_vector(unsigned pc) {
    if (armtimer_check_interrupt()) {
        compute_distance();       
  //      top++; stack[top] = 1;
        armtimer_clear_interrupt();
    }
}

void display_distance() { 
    int d4 = distance % 10;
    int d3 = (distance/10) % 10;
    int d2 = (distance/100) % 10;
    int d1 = distance/1000;
    displayNum(d1, d2, d3, d4, 10);
}

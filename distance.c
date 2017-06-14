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

#define TURN_SPEED 6 
#define STRAIGHT_SPEED 7.25
#define DISTANCE_TIMER_INTERVAL 10000 
#define DELAY_DISTANCE 24 //not needed so can remove

static unsigned int distance; 
static unsigned int total_time; //in us
static unsigned int mov_time; //in us
static unsigned int prev_mov;
static unsigned int prev_time;
static unsigned int count;
static int motor_flag = 0;

/* This function initializes variables and enables armtimer interrupts. */
void distance_init() {
    distance = 0;
    mov_time = 0;
    total_time = 0;
    prev_time = timer_get_time()/1000000;
    prev_mov = FWD; //assume 1st move is forward
    armtimer_init(DISTANCE_TIMER_INTERVAL);
    armtimer_enable();
    armtimer_enable_interrupt();
    interrupts_enable_basic(INTERRUPTS_BASIC_ARM_TIMER_IRQ); 
}

/* This getter function returns the distance the car has travelled so far. 
   @return the distance of type unsigned int */
unsigned int get_dist() {
    return distance;
}

/* This function implements Pulse Width Modulation to decrease the speed of the car by one half. 
It also calculates the distance the car has travelled so far. */
void compute_distance() {
    if (motor_flag % 2) {
        gpio_write(GPIO_PIN19, 0);
        gpio_write(GPIO_PIN26, 0);
    } else {
        gpio_write(GPIO_PIN19, 1);
        gpio_write(GPIO_PIN26, 1);
    }
    motor_flag++;
    if (get_flag()) return; //don't execute computations if in middle of ultrasound  
    int cur_time = timer_get_time()/1000000;
    int cur_mov = get_dir();
    if ((cur_mov == FWD) || (cur_mov == REV)) {
        distance += (cur_time - prev_time)*STRAIGHT_SPEED;
    } else if ((cur_mov == LEFT) || (cur_mov == RIGHT)) {
        distance += (cur_time - prev_time)*TURN_SPEED;
    }
    if (cur_mov != prev_mov) {
        push((total_time*10)+prev_mov);
        total_time = cur_time - prev_time;
    } else total_time += cur_time - prev_time;
    prev_time = cur_time;
}

/* This function handles armtimer interrupts, executing PWM and calculating the distance the car has travelled. */
void distance_vector(unsigned pc) {
    if (armtimer_check_interrupt()) {
        compute_distance();       
        armtimer_clear_interrupt();
    }
}

/* This function displays the distance the car has travelled so far on the screen.*/
void display_distance() { 
    int d4 = distance % 10;
    int d3 = (distance/10) % 10;
    int d2 = (distance/100) % 10;
    int d1 = distance/1000;
    displayNum(d1, d2, d3, d4, 100);
}

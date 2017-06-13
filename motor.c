/* This file has functions that implement the motor. */

#include "gpio.h"
#include "timer.h"
#include "motor.h"
#include "distance.h"
#include "led_lights.h"

static int dir;

/* This getter function returns the direction the car is travelling. 
   @return the direction of the car */
int get_dir() {
    return dir;
}

/* This function intiializes the motor by configuring direction and enable pins. */
void motor_init() {
    gpio_init();
    timer_init();

    //1st motor
    gpio_set_output(GPIO_PIN20);
    gpio_set_output(GPIO_PIN21);

    //2nd motor
    gpio_set_output(GPIO_PIN5);
    gpio_set_output(GPIO_PIN6);

    //configure enable pins
    gpio_set_output(GPIO_PIN19);
    gpio_set_output(GPIO_PIN26);
    gpio_write(GPIO_PIN19, HIGH);
    gpio_write(GPIO_PIN26,HIGH);
}

/* This function enables pins to move the car forward. */
void forward_motion() {
    stop();
    dir = FWD;

    //direction pins
    gpio_write(GPIO_PIN21, HIGH);
    gpio_write(GPIO_PIN20, LOW);
    gpio_write(GPIO_PIN5, LOW);
    gpio_write(GPIO_PIN6, HIGH);
}

/* This function enables pins to move the car backward. */
void reverse_motion() {
    stop();
    signal_back();
    dir = REV;
    gpio_write(GPIO_PIN21, LOW);
    gpio_write(GPIO_PIN20, HIGH);
    gpio_write(GPIO_PIN6, LOW);
    gpio_write(GPIO_PIN5, HIGH);
}

/* This function enables pins to stop the car. */
void stop() {
    gpio_write(GPIO_PIN6, LOW);
    gpio_write(GPIO_PIN5, LOW);
    gpio_write(GPIO_PIN20, LOW);
    gpio_write(GPIO_PIN21, LOW);
}

/* This function enables pins to turn the car left. */
void left_turn(int time_turn) {
    stop();
    signal_left();
    dir = LEFT;
    gpio_write(GPIO_PIN21, HIGH);
    gpio_write(GPIO_PIN20, LOW);
    delay_ms(time_turn);
    gpio_write(GPIO_PIN21, LOW);
}

/* This function enables pins to turn the car right. */
void right_turn(int time_turn) {
    stop();
    signal_right();
    dir = RIGHT;
    gpio_write(GPIO_PIN6, HIGH);
    gpio_write(GPIO_PIN5, LOW);
    delay_ms(time_turn);
    gpio_write(GPIO_PIN6, LOW);
}

/* This function may be called to move the car in a particular direction for a 
particular length of time.
   @param i of type int is the direction of the car
   @param time of type int is the length of time that the car should move in that direction */
void move(int i, int time) {
    if (i == LEFT) {
        left_turn(time);
    } else if (i == REV) {
        reverse_motion();
        delay_ms(time);
    } else if (i == FWD) {
        forward_motion();
        delay_ms(time);
    } else if (i == RIGHT) {
        right_turn(time);
    } 
    return;
}

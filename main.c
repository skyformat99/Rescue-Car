#include "timer.h"
#include "gpio.h"
#include "gpioextra.h"
#include "printf.h"
#include "motor.h"

#define MAX_ELEM 100
#define LEFTTURN 0
#define REVERSE 1
#define FORWARD 2
#define RIGHTTURN 3

const unsigned trigger = GPIO_PIN3;
const unsigned echo = GPIO_PIN2;

static stack[MAX_ELEM];
static top = -1;
// data structure:

// https://www.tutorialspoint.com/javaexamples/data_stack.htm source referred
// http://www.sanfoundry.com/c-program-stack-implementation/

/* Should replace it with other things */


unsigned get_distance(void) {
    // write hi for 10usec
    gpio_write(trigger, 1);
    delay_us(10);
    gpio_write(trigger, 0);
    
    unsigned start = timer_get_time();
    delay_us(149); // wait til device settles: 148 = time to go one inch
    while(!gpio_read(echo))
        ;
    
    unsigned end;
    while(gpio_read(echo) == 1)
        ;
    end = timer_get_time();
    
    // ((340M/S / 2) * 39.37inch / meter) / 10^6 = inch/usec
    return (end - start) / 149;
}

int isEmpty(){
    return (top == -1);
}

int isFull(){
    return (top == MAX_ELEM-1);
}

int push(int i){
    stack[++top] = i;
}

int pop(){
    return stack[top--];
}

int peek(){
    return stack[top];
}

void main(void) {
    printf_init();
    timer_init();
    gpio_init();
    motor_init();
    
    gpio_set_output(trigger);
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
    int mod = FORWARD;
    int time = 10;
    int input = mod + time * 10;
    push(input);
    mod = REVERSE;
    time = 20;
    input = mod + time * 10;
    push(input);
    mod = LEFTTURN;
    time = 30;
    input = mod + time * 10;
    push(input);
    mod = RIGHTTURN;
    time = 40;
    input = mod + time * 10;
    push(input);
    while(!isEmpty()){
        int num = pop();
        int mod = num % 10;
        int time = num / 10;
        //stop();
        move(3-mod, time); // reverse direction so 3-mod
        printf("distance is : %d", num/10);
        printf("distance is : %d", num%10);
    }
    
    // stop at the very end
}

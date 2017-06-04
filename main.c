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



// https://www.tutorialspoint.com/javaexamples/data_stack.htm source referred
// http://www.sanfoundry.com/c-program-stack-implementation/

/* Should replace it with other things */

void move(int i, int time){
    if(i==0){
        left_turn(time);
    } else if(i==1){
        reverse_motion();
        delay_ms(time);
    } else if(i==2){
        forward_motion();
        delay_ms(time);
    } else if(i==3){
        right_turn(time);
    } else {
        // throw error, should never come here
    }
}

void main(void) {
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
}


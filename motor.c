#include "gpio.h"
#include "timer.h"
#include "motor.h"

static int dir;

int get_dir() {
  return dir;
}

void motor_init(){
  gpio_init();
  timer_init();
  // for A
  gpio_set_output(GPIO_PIN20);
  gpio_set_output(GPIO_PIN21);
  // for B
  gpio_set_output(GPIO_PIN5);
  gpio_set_output(GPIO_PIN6);
}

void forward_motion(){
  stop();
  dir = FWD;
  gpio_write(GPIO_PIN21, HIGH);
  gpio_write(GPIO_PIN20, LOW);
  gpio_write(GPIO_PIN5, LOW);
  gpio_write(GPIO_PIN6, HIGH);
}

void reverse_motion(){
  stop();
  dir = REV;
  gpio_write(GPIO_PIN21, LOW);
  gpio_write(GPIO_PIN20, HIGH);
  gpio_write(GPIO_PIN6, LOW);
  gpio_write(GPIO_PIN5, HIGH);
}

void stop(){
  gpio_write(GPIO_PIN6, LOW);
  gpio_write(GPIO_PIN5, LOW);
  gpio_write(GPIO_PIN20, LOW);
  gpio_write(GPIO_PIN21, LOW);
}

void left_turn(int time_turn){
  stop();
  dir = LEFT;
  gpio_write(GPIO_PIN21, 1);
  gpio_write(GPIO_PIN20, 0);
  delay_ms(time_turn);
}

void right_turn(int time_turn){
  stop();
  dir = RIGHT;
  gpio_write(GPIO_PIN6, 1);
  gpio_write(GPIO_PIN5, 0);
  delay_ms(time_turn);
}

void move(int i, int time){
  if(i == LEFT){
    left_turn(time);
  } else if(i == REV){
    reverse_motion();
    delay_ms(time);
  } else if(i == FWD){
    forward_motion();
    delay_ms(time);
  } else if(i == RIGHT){
    right_turn(time);
  } else {
    // throw error, should never come here
  }
}

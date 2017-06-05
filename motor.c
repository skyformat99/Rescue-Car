
#include "gpio.h"
#include "timer.h"
#include "motor.h"
#include "led_lights.h"

//static int speed;
static int dir;

int get_dir() {
    return dir;
}

void motor_init(){
  // for A
  gpio_set_output(GPIO_PIN16);
  gpio_set_output(GPIO_PIN20);
  gpio_set_output(GPIO_PIN21);
  // for B
  gpio_set_output(GPIO_PIN13);
  gpio_set_output(GPIO_PIN19);
  gpio_set_output(GPIO_PIN26);
}

void forward_motion(){
  stop();
  signal_back(OFF);
  dir = FWD;
  gpio_write(GPIO_PIN20, HIGH);
  gpio_write(GPIO_PIN21, LOW);
  gpio_write(GPIO_PIN19, LOW);
  gpio_write(GPIO_PIN26, HIGH);
  gpio_write(GPIO_PIN13, HIGH);
  gpio_write(GPIO_PIN16, HIGH);
}

void reverse_motion(){
  stop();
  signal_back(ON);
  dir = REV;
  gpio_write(GPIO_PIN20, LOW);
  gpio_write(GPIO_PIN21, HIGH);
  gpio_write(GPIO_PIN19, HIGH);
  gpio_write(GPIO_PIN26, LOW);
  gpio_write(GPIO_PIN13, HIGH);
  gpio_write(GPIO_PIN16, HIGH);
}

void stop(){
  signal_back(OFF);
  gpio_write(GPIO_PIN20, LOW);
  gpio_write(GPIO_PIN21, LOW);
  gpio_write(GPIO_PIN19, LOW);
  gpio_write(GPIO_PIN26, LOW);
  gpio_write(GPIO_PIN13, LOW);
  gpio_write(GPIO_PIN16, LOW);
}

void left_turn(int time_turn){
    stop();
    signal_back(OFF);
    dir = LEFT;
    int start_time = timer_get_time();
  while(timer_get_time()-start_time<time_turn){
    signal_left();
    gpio_write(GPIO_PIN16, 1);
    gpio_write(GPIO_PIN13, 0);
    delay_ms(TURN_FIRST_DELAY);
    gpio_write(GPIO_PIN16, 0);
    gpio_write(GPIO_PIN13, 1);
    delay_ms(TURN_SECOND_DELAY);
  }
}

void right_turn(int time_turn){
    stop();
    signal_back(OFF);
    dir = RIGHT;
    int start_time = timer_get_time();
  while(timer_get_time()-start_time<time_turn){
    signal_right();
    gpio_write(GPIO_PIN16, 0);
    gpio_write(GPIO_PIN13, 1);
    delay_ms(TURN_FIRST_DELAY);
    gpio_write(GPIO_PIN16, 1);
    gpio_write(GPIO_PIN13, 0);
    delay_ms(TURN_SECOND_DELAY);
  }
}

void move(int i, int time){
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
  } else {
    // throw error, should never come here                                  
  }
}


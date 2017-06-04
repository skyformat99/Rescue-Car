// set all the pins to be outputs
// pin for motor A dir1, dir2, speed, motor B dir1, dir2, speed

// GPIO 16 SPEED 20 DIR1 21 DIR2 A
// GPIO 13 SPEED 19 DIR1 26 DIR2 B
/*#define HIGH 1
#define LOW 0
#define TIME_TURN 10000000
#define TURN_FIRST_DELAY 100
#define TURN_SECOND_DELAY 10*/

#include "gpio.h"
#include "timer.h"
#include "motor.h"

static int speed;
static int dir;

void motor_init(){
  // init speed, time, dir
  //gpio_init();
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
  gpio_write(GPIO_PIN20, HIGH);
  gpio_write(GPIO_PIN21, LOW);
  gpio_write(GPIO_PIN19, LOW);
  gpio_write(GPIO_PIN26, HIGH);
  gpio_write(GPIO_PIN13, HIGH);
  gpio_write(GPIO_PIN16, HIGH);
}

void reverse_motion(){
  stop();
  gpio_write(GPIO_PIN20, LOW);
  gpio_write(GPIO_PIN21, HIGH);
  gpio_write(GPIO_PIN19, HIGH);
  gpio_write(GPIO_PIN26, LOW);
  gpio_write(GPIO_PIN13, HIGH);
  gpio_write(GPIO_PIN16, HIGH);
}

void stop(){
  gpio_write(GPIO_PIN20, LOW);
  gpio_write(GPIO_PIN21, LOW);
  gpio_write(GPIO_PIN19, LOW);
  gpio_write(GPIO_PIN26, LOW);
  gpio_write(GPIO_PIN13, LOW);
  gpio_write(GPIO_PIN16, LOW);
}

void left_turn(int time_turn){
  stop();
  int start_time = timer_get_time();
  while(timer_get_time()-start_time<time_turn){
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
  int start_time = timer_get_time();
  while(timer_get_time()-start_time<time_turn){
    gpio_write(GPIO_PIN16, 0);
    gpio_write(GPIO_PIN13, 1);
    delay_ms(TURN_FIRST_DELAY);
    gpio_write(GPIO_PIN16, 1);
    gpio_write(GPIO_PIN13, 0);
    delay_ms(TURN_SECOND_DELAY);
  }
}

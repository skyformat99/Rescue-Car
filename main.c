#include "clock.h"
#include "timer.h"
#include "gpio.h"
//#include "gpioextra.h"
//#include "printf.h"
#include "motor.h"
#include "printf.h"
#include "sensor.h"
#include "distance.h"
#include "interrupts.h"
//#include "circular.h"
//#include "ultrasonic.h"
//#include "sensor.h"
//extern void ultrasonic_init();
//extern unsigned get_distance();

extern void flashHelp();
static int help = 0;
static const unsigned trigger = GPIO_PIN3;
static const unsigned echo = GPIO_PIN2;
static unsigned int audio_pin = GPIO_PIN5;

void main(void){
  gpio_init();
  clock_init();
  printf_init();
  motor_init();
  ultrasonic_init();
  distance_init();
  //system_enable_interrupt();
  //  flashHelp();
  printf("flashed");
  delay(3);
  forward_motion();
   while (1) {
    //    printf("distance = %d", distance);
    printf("get distance");
    unsigned distance = get_distance();
    printf("%s\n", "outside dist");
    printf("distance = %d inches\n", distance);
    // dela;
    unsigned left_distance;
    unsigned right_distance;
    display_distance();
    if (distance < 20) {
      reverse_motion();
      display_distance();
      // delay_ms(2000);
      right_turn(650);
      display_distance();
      right_distance = get_distance();
      display_distance();
      //      printf("right distance is (%d) and ", right_distance);
      left_turn(650);
      display_distance();
      left_turn(650);
      display_distance();
      left_distance = get_distance();
      // printf("left distance is (%d) \n", left_distance);
      // if (left_distance < right_distance){
    	// printf("turning right because there are less obstacles. \n");
	   // right_turn(10);//update time from test
	   // right_turn(10);//update time from test
      // }
      display_distance();
      forward_motion();
      delay(1);
      stop();
      // delay(1);
      // left_turn(650);
      // delay(1);
      // stop();
      // right_turn(650);
      // delay(1);
      // stop();
      // delay(2);

    }
    //    if (!isEmpty()) {
    //   for (int i = 0; i <= top; i++) printf("i: distance is %d %d \n", i, stack[i]);
    //  } 
    } 
  //reverse_motion();
//  while(1){}

  //  delay(500);
}


/*#include "timer.h"
#include "gpio.h"
#include "gpioextra.h"
#include "printf.h"
#include "motor.h"
#include "circular.h"


const unsigned trigger = GPIO_PIN3;
const unsigned echo = GPIO_PIN2;
cir_t *cir;

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

void main(void) {
  printf_init();
  timer_init();
  gpio_init();
  motor_init();
  cir = cir_new(); // initialize circular buffer
  gpio_set_output(trigger);
  gpio_set_input(echo);
  gpio_set_pulldown(echo);
  delay_ms(40);
  forward_motion();

  while(1) {
    unsigned distance = get_distance();
    printf("distance = %d inches\n", distance);
    delay_ms(1000);
    if(distance<5){
      reverse_motion();
      delay_ms(2000);
      right_turn(2000);
      forward_motion();
    }
  }
  // stop at the very end
}*/

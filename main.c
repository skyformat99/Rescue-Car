
#include "interrupts.h"
#include "timer.h"
#include "gpio.h"
#include "gpioextra.h"
#include "printf.h"
#include "motor.h"
#include "path.h"
#include "distance.h"
#include "led_lights.h"
#include "sensor.h"

extern void clock_init();
extern void flashHelp();
extern int top;
//ut(GPIO_PIN16);
//gpio_set_output(GPIO_PIN20);
extern int stack[128];

/* Initialize distance and clock at beginning of main and run
   display_distance() in forever while loop.*/
void main(void) {
  gpio_init();
  //system_enable_interrupts();
  //clock_init();
  //  motor_init();
  gpio_set_output(GPIO_PIN22);
  gpio_set_output(GPIO_PIN23);
  gpio_set_output(GPIO_PIN5);
  gpio_set_output(GPIO_PIN6);
  //gpio_set_output(GPIO_PIN6);
  //gpio_set_output(GPIO_PIN5);
  //printf_init();
  //distance_init();
  //audio_sensor_init();
  //ultrasonic_init();
  //led_lights_init(GPIO_PIN6, GPIO_PIN7, GPIO_PIN8);
  //forward_motion();
  //while(1){
    //printf("forward motion");
    //gpio_write(GPIO_PIN13, 1);                                                
    //gpio_write(GPIO_PIN16, 1);
    //gpio_write(GPIO_PIN13, 1);
    //gpio_write(GPIO_PIN5, 1);
    gpio_write(GPIO_PIN22, 1);
    //gpio_write(GPIO_PIN20, 1);
    //gpio_write(GPIO_PIN26, 1);
    //gpio_write(GPIO_PIN21, 1);
    gpio_write(GPIO_PIN23, 0);
    gpio_write(GPIO_PIN5, 0);
    gpio_write(GPIO_PIN6, 1);
    delay_ms(40000000);
    //printf("%b", gpio_read(GPIO_PIN13));
    //gpio_write(GPIO_PIN16, 1);
    //printf("%b", gpio_read(GPIO_PIN16));
    //forward_motion();
    //reverse_motion();
    //delay(300);
    //}
  /* while (1) {
    unsigned distance = get_distance();
    printf("distance = %d inches\n", distance);
    delay_us(1000);
    unsigned left_distance;
    unsigned right_distance;
    display_distance();
    if (distance < 5) {
      reverse_motion();
      delay_us(2000);
      right_turn(2000);
      right_distance = get_distance();
      left_turn(2000);
      left_turn(2000);
      left_distance = get_distance();
      if (left_distance < right_distance){
	right_turn(10);//update time from test
	right_turn(10);//update time from test
      }
      forward_motion();
    }
    //    if (!isEmpty()) {
    //   for (int i = 0; i <= top; i++) printf("i: distance is %d %d \n", i, stack[i]);
    //  } 
  } */
}

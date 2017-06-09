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
extern int stack[128];
//extern int c;

//extern int test[1024];
//extern int i;

/* Initialize distance and clock at beginning of main and run
display_distance() in forever while loop.*/
void main(void) {
    clock_init();
  //  motor_init();
    printf_init();
    distance_init();
    flashHelp();
//    system_enable_interrupts();
//    audio_sensor_init();
//    ultrasonic_init();
//    led_lights_init(GPIO_PIN6, GPIO_PIN7, GPIO_PIN8);
//    forward_motion();
/*    while (1) {
        unsigned distance = get_distance();
//        printf("distance = %d inches\n", distance);
        delay_ms(5000);
        unsigned left_distance;
        unsigned right_distance;
//        display_distance();
        if (distance < 10) {
            reverse_motion();
            delay_us(2000);
            right_turn(650);
            right_distance = get_distance();
            left_turn(650);
            left_turn(650);
            left_distance = get_distance();
            if (left_distance < right_distance){
                right_turn(650);
                right_turn(650);
            }
            forward_motion();
        }
    }*/
}


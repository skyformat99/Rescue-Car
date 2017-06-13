  #include "gpio.h"
  #include "timer.h"
  #include "motor.h"
  #include "printf.h"
  #include "sensor.h"
  #include "distance.h"
  #include "interrupts.h"
  #include "odometer.h"
  #define TURN_TIME 1000

  static int help = 0;
  static const unsigned trigger = GPIO_PIN3;
  static const unsigned echo = GPIO_PIN2;
  static unsigned int audio_pin = GPIO_PIN5;
  void main2(){
    gpio_init();
    gpio_set_input(GPIO_PIN26);
    while(gpio_read(GPIO_PIN26)){

    }
    printf("%s\n","done" );
  }

  void main(){
    gpio_init();
    timer_init();
    clock_init();
    printf_init();
    motor_init();
    ultrasonic_init();
    distance_init();
    system_enable_interrupts();
    delay(5);
    // flashHelp();
    //test remote control
    // gpio_set_input(GPIO_PIN21);
    //  unsigned int x;
    // while (1){
    //   x = gpio_read(GPIO_PIN21);
    //   if(x != 0){
    //     break;
    //   } 
    //   // printf("%d\n",x );
    //   // delay(0.2);
    // }
    
      //int count = 10;
    int sensitiviy_distance = 15;
    int count = 0;
    // int timer_get_time()
     while (1) {
      // if(count == 0){
      //   display_distance();
      //   count = 10;
      // }
      // count--;
      unsigned distance = get_distance();
      unsigned left_distance;
      unsigned right_distance;
      if (distance <= sensitiviy_distance) {
        reverse_motion();
        delay(1);
        stop();
        display_distance();
        right_turn( TURN_TIME);
        stop();
         display_distance();
        right_distance = get_distance();
        left_turn(2* TURN_TIME);//to account for two turns
        stop();
        // left_turn(650);
        display_distance();
        left_distance = get_distance();
        // display_distance();
        // display_distance();
        if (left_distance <= sensitiviy_distance && right_distance <= sensitiviy_distance){
          flashHelp();
          reverse_motion();
          delay(2);
        } else if (left_distance < right_distance){
          right_turn(2* TURN_TIME);
        }
        stop();
        display_distance();
        
        // delay(1);
        // stop ();
        // display_distance();
        // // delay(1);
        // left_turn(650);
        // delay(1);
        // stop();
        // right_turn(650);
        // delay(1);
        // stop();
        // delay(2);

      }
      forward_motion();
      } 
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

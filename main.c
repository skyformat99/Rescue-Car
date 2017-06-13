  #include "gpio.h"
  #include "timer.h"
  #include "motor.h"
  #include "printf.h"
  #include "sensor.h"
  #include "distance.h"
  #include "interrupts.h"
  #include "odometer.h"
  #include "led_lights.h"
  #define TURN_TIME 1000

  static int help = 0;
  static const unsigned trigger = GPIO_PIN3;
  static const unsigned echo = GPIO_PIN2;
  static unsigned int audio_pin = GPIO_PIN5;

 void main4(){
    led_lights_init(GPIO_PIN7, GPIO_PIN8, GPIO_PIN19);
  while(1) { 
   signal_left();
    delay(1);
    signal_right();
    delay(1);
    signal_back();
    delay(1);
    alarm_pattern();
    delay(1);
  }
 }

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
    led_lights_init(GPIO_PIN7, GPIO_PIN8, GPIO_PIN13);
    system_enable_interrupts();
    delay(5);
    int sensitiviy_distance = 15;
    int count = 0;
     while (1) {
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
        display_distance();

        left_distance = get_distance();
        if (left_distance <= sensitiviy_distance && right_distance <= sensitiviy_distance){
          flashHelp();
          reverse_motion();
          delay(2);
        } else if (left_distance < right_distance){
          right_turn(2* TURN_TIME);
        }
        stop();
      }
      forward_motion();
      } 
  }

        #include "gpio.h"
        #include "timer.h"
        #include "motor.h"
        #include "printf.h"
        #include "sensor.h"
        #include "distance.h"
        #include "interrupts.h"
        #include "odometer.h"
        #include "led_lights.h"
        #define TURN_TIME 900

        static int help = 0;
        static const unsigned trigger = GPIO_PIN3;
        static const unsigned echo = GPIO_PIN2;
        static unsigned int audio_pin = GPIO_PIN5;


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
          //for the remote
          gpio_set_input(GPIO_PIN16);
          while(gpio_read(GPIO_PIN16)){
          }
          int moving_forward = 1;
          int sensitiviy_distance = 15;
          int count = 0;
          while (1) {
              unsigned distance = get_distance();
              unsigned left_distance;
              unsigned right_distance;
              //check if the car is within the sensitivity distance of an obstacle
              if (distance <= sensitiviy_distance) {
                  reverse_motion();
                  delay(1);
                  stop();
                  display_distance();

                  right_turn(TURN_TIME);
                  stop();
                  display_distance();
                  right_distance = get_distance();

                  left_turn(2* TURN_TIME);//to account for two turns
                  stop();
                  display_distance();
                  left_distance = get_distance();

                  //flash the word help if blocked
                  if (left_distance <= sensitiviy_distance && right_distance <= sensitiviy_distance) {
                      flashHelp();
                      reverse_motion();
                      delay(2);
                  } else if (left_distance < right_distance) {
                      right_turn(2* TURN_TIME);
                  }
                  stop();
              }
              if (moving_forward){
                forward_motion();
              }
               if (!gpio_read(GPIO_PIN16)){
                stop();
                if (moving_forward){
                  moving_forward = 0;
                  stop();
                }else{
                  moving_forward = 1;
                  forward_motion();
                }
               }
          } 
      }

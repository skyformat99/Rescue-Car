#include "audio_sensor.h"
#include "gpio.h"
#include "printf.h"

int  main() {
  int voice_pin = GPIO_PIN24;
  audio_sensor_init(voice_pin);
  while (1){
    int num = audio_sensor_fetch();
    printf("The value in the %d\n", num);
  }
  }

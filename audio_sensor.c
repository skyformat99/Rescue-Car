#include "gpio.h"
#include "audio_sensor.h"


void audio_sensor_init(unsigned int pin){
  audio_pin = pin;
  gpio_set_input(pin);
}

int audio_sensor_fetch(){
  return gpio_read(audio_pin);
}

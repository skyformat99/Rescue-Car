
#include "gpio.h"
#include "led_lights.h"



void main(void) {
  // stop at the very end
led_light_init(GPIO_PIN5, GPIO_PIN6);
dance_pattern();
}

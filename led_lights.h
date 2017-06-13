#ifndef LED_LIGHTS_H
#define LED_LIGHTS_H

#define ON 1
#define OFF 0

void led_lights_init(unsigned int left, unsigned int right, unsigned int back);
void signal_left();
void signal_right();
void signal_back();
void toggle_leds(unsigned int current_pin, unsigned int prev_pin);
void dance_pattern();
void alarm_pattern();                   
#endif  

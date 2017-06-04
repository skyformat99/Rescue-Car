unsigned int left_pin;
unsigned int right_pin;

void led_light_init(unsigned int left, unsigned int right);
void left_signal();
void right_signal();
void toggle_leds(unsigned int current_pin, unsigned int prev_pin);
void dance_pattern();
void alarm_pattern();

// set all the pins to be outputs
// pin for motor A dir1, dir2, speed, motor B dir1, dir2, speed

// GPIO 16 SPEED 20 DIR1 21 DIR2 A
// GPIO 13 SPEED 19 DIR1 26 DIR2 B
void motor_init(){
  // init speed, time, dir
  gpio_init();
  // for A
  gpio_set_output(GPIO_PIN16);
  gpio_set_output(GPIO_PIN20);
  gpio_set_output(GPIO_PIN21);
  // for B
  gpio_set_output(GPIO_PIN13);
  gpio_set_output(GPIO_PIN19);
  gpio_set_output(GPIO_PIN26);
} 

void main(){

}

// gpio 4 : gpio pin 0
// gpio 17 : VDD

#include "gpio.h"
#include "i2c.h"
#include "timer.h"
#include "printf.h"

#define FSEL0  0x20200000
#define FSEL1  0x20200004
#define FSEL2  0x20200008
#define FSEL3  0x2020000C
//#define FSEL4  0x20200010
#define SET0   0x2020001C
#define CLR0   0x20200028
#define LEVEL0 0x20200034
#define LEVEL1 0x20200038

//#define SCL GPIO_PIN3;
#define SYSTEM_FRESH_OUT_OF_RESET 0x0016

void tof_init(){
    
    // 1) apply power
    gpio_set_output(GPIO_PIN4);
    //gpio_set_output(GPIO_PIN17);
    gpio_pullup(GPIO_PIN4);
    // 2) Set GPIO to '1' gpio_write
    gpio_write(GPIO_PIN4, 1);
    delay_ms(1);
    int val = *((volatile int *)(SYSTEM_FRESH_OUT_OF_RESET));
    printf("this is a value : %d", val);
    while(val!=1){
        gpio_set_function(GPIO_PIN4, 0);
        gpio_write(GPIO_PIN4, 0);
        delay_ms(1);
        gpio_write(GPIO_PIN4, 1);
        gpio_set_function(GPIO_PIN4, 1);
        delay_ms(1);
    }
    // what does it mean to apply ?
    //gpio_pullup(GPIO_PIN17);
}

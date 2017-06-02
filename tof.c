// gpio 4 : gpio pin 0
// gpio 17 : VDD

#include "gpio.h"
#include "i2c.h"
#include "timer.h"
#include "printf.h"
#include "gpioextra.h"
#include "gpioevent.h"

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
#define SYSTEM_INTERRUPT_CONFIG_GPIO 0x0014
#define SYSTEM_FRESH_OUT_OF_RESET 0x0016

void tof_init(){
    
    // 1) apply power
    i2c_init();
    gpio_set_input(GPIO_PIN4);
    //gpio_set_output(GPIO_PIN17);
    gpio_set_pullup(GPIO_PIN4);
    // 2) Set GPIO to '1' gpio_write
    //gpio_set_function(GPIO_PIN4, 1);
    gpio_write(GPIO_PIN4, 1);
    printf("the value of pin 4 is %d", gpio_read(GPIO_PIN4));
    delay_ms(2);
    unsigned int val = *((volatile unsigned int *)(SYSTEM_FRESH_OUT_OF_RESET));
    printf("this is a value : %d", val);
    while(val!=1){
        //gpio_set_function(GPIO_PIN4, 0);
        gpio_write(GPIO_PIN4, 0);
        delay_ms(2);
        gpio_write(GPIO_PIN4, 1);
        //gpio_set_function(GPIO_PIN4, 1);
        delay_ms(2);
	printf("this is a value : %d", val);
	val = *((volatile unsigned int *)(SYSTEM_FRESH_OUT_OF_RESET));
    }

    // the lines up there are def buggy

    tof_settings();
    



    // what does it mean to apply ?
    //gpio_pullup(GPIO_PIN17);
}

static void tof_settings(){
    // Mandatory : private registers
    WriteByte(0x0207, 0x01);
    WriteByte(0x0208, 0x01);
    WriteByte(0x0096, 0x00);
    WriteByte(0x0097, 0xfd);
    WriteByte(0x00e3, 0x00);
    WriteByte(0x00e4, 0x04);
    WriteByte(0x00e5, 0x02);
    WriteByte(0x00e6, 0x01);
    WriteByte(0x00e7, 0x03);
    WriteByte(0x00f5, 0x02);
    WriteByte(0x00d9, 0x05);
    WriteByte(0x00db, 0xce);
    WriteByte(0x00dc, 0x03);
    WriteByte(0x00dd, 0xf8);
    WriteByte(0x009f, 0x00);
    WriteByte(0x00a3, 0x3c);
    WriteByte(0x00b7, 0x00);
    WriteByte(0x00bb, 0x3c);
    WriteByte(0x00b2, 0x09);
    WriteByte(0x00ca, 0x09);
    WriteByte(0x0198, 0x01);
    WriteByte(0x01b0, 0x17);
    WriteByte(0x01ad, 0x00);
    WriteByte(0x00ff, 0x05);
    WriteByte(0x0100, 0x05);
    WriteByte(0x0199, 0x05);
    WriteByte(0x01a6, 0x1b);
    WriteByte(0x01ac, 0x3e);
    WriteByte(0x01a7, 0x1f);
    WriteByte(0x0030, 0x00);
    // Recommended : Public registers - See data sheet for more detail
    WriteByte(0x0011, 0x10); // Enables polling for ‘New Sample ready’
    // when measurement completes
    WriteByte(0x010a, 0x30); // Set the averaging sample period
    // (compromise between lower noise and
    // increased execution time)
    WriteByte(0x003f, 0x46); // Sets the light and dark gain (upper
    // nibble). Dark gain should not be
    // changed.
    WriteByte(0x0031, 0xFF); // sets the # of range measurements after
    // which auto calibration of system is
    // performed
    WriteByte(0x0040, 0x63); // Set ALS integration time to 100ms
    WriteByte(0x002e, 0x01); // perform a single temperature calibration
    // of the ranging sensor
    WriteByte(0x001b, 0x09); // Set default ranging inter-measurement
    // period to 100ms
    WriteByte(0x003e, 0x31); // Set default ALS inter-measurement period
    // to 500ms
    WriteByte(0x0014, 0x24); // Configures interrupt on ‘New Sample
    // Ready threshold event’
}

void WriteByte(int address, int value){
    // what should we do here?!?!?!??!?!?1?!??1?!??!?!?!?
    i2c_write(address, );
}

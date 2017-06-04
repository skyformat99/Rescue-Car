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

int measure_status = 0; //set to 1 if want to start continuous range measurement
#define SYSTEM_INTERRUPT_CONFIG_GPIO 0x0014
#define SYSTEM_FRESH_OUT_OF_RESET 0x0016
#define SYSRANGE_START 0x0018
#define RESULT_RANGE_STATUS 0x4D //OPTIONAL
#define RESULT_INTERRUPT_STATUS_GPIO 0x4F
#define RESULT_RANGE_VAL 0x62
#define SYSTEM_INTERRUPT_CLEAR 0x15

#define VL6180X 0x29


static void tof_settings();


unsigned tof_read_reg(unsigned char reg) {
    i2c_write(VL6180X, (void*) &reg, 1);
    unsigned char uc = 0;
    i2c_read(VL6180X, (void*) &uc, 1);
    return uc;
}

void WriteByte(unsigned char reg, unsigned char v) {
    char data[2] = {reg, v};
    i2c_write(VL6180X, data, 2);
}

void tof_init(){
    i2c_init();
    //gpio_set_input(GPIO_PIN17);
    gpio_set_output(GPIO_PIN17);
    gpio_set_pullup(GPIO_PIN17);
    gpio_set_pullup(GPIO_PIN2);
    gpio_set_pullup(GPIO_PIN3);
    gpio_write(GPIO_PIN17, 1);
    gpio_set_function(GPIO_PIN17, 1);
    delay_ms(2);
    unsigned char uc = tof_read_reg(0x16);
    printf("%c (%d)", uc);
    printf("done");
    tof_settings();
    printf("done");
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
    //x
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

//https://www.pololu.com/file/download/AN4545.pdf?file_id=0J962
/*static void cont_range() {
  while (measure_status) { //want to continuously measure until we toggle off
    char buf[1];
    i2c_read(RESULT_RANGE_STATUS, buf, 1);
    if ((buf[0] & 0x01) == 0) return; //error check, zeroth bit must be set
    buf[0] = 0x03;
    i2c_write(SYSRANGE_START, buf, 1);i

    //wait for range measurement to complete
    i2c_read(RESULTS_INTERRUPT_STATUS, buf, 1);
    while (((buf[0] >> 2) & 0x01) != 0) i2c_read(RESULTS_INTERRUPT_STATUS, buf, 1);

    //read range result, returned in milimeters
    char result[2];
    i2c_read(RESULT_RANGE_VAL, result, 1);
    if (result[0] == 0) //valid measurement {
    //do things with measured range (aka command motor appropriately), stored in result[1]
  //}
  }

    //now done with range measurement
    buf[0] = 0x07;
    i2c_write(SYSTEM_INTERRUPT_CLEAR, buf, 1); //clear interrupt
    buf[0] = 0x01;
    i2c_write(SYSRANGE_START, buf, 1); //stop measurement
}*/

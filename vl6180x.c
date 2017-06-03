#include "timer.h"
#include "printf.h"
#include "i2c.h"
#include "VL6180X.h"

void vl6180x_read_tof_sensor(short *x, short *z);
void _write_reg(unsigned char reg, unsigned char v);
unsigned vl6180x_read_reg(unsigned char reg);unsigned vl6180x_read_reg(unsigned char reg);
void vl6180x_init();
unsigned vl6180x_get_whoami();

const unsigned vl6180x_address = 0b0101001; //tof sensor address


void vl6180x_write_reg(unsigned char reg, unsigned char v) {
	char data[2] = {reg, v};
	i2c_write(vl6180x_address, data, 2);
}

unsigned vl6180x_read_reg(unsigned char reg) {
	i2c_write(vl6180x_address, (void*) &reg, 1);
	unsigned char uc = 0;
	i2c_read(vl6180x_address, (void*) &uc, 1);
	return uc;
}

void vl6180x_init() {
	vl6180x_write_reg(CTRL2_G, 0x80);   // 1600Hz (high perf mode)
	vl6180x_write_reg(CTRL1_XL, 0x80);  // 1600Hz (high perf mode)
}

unsigned vl6180x_get_whoami() {
    return vl6180x_read_reg(WHO_AM_I);
}


void vl6180x_read_tof_sensor(short *x, short *z) {
    *x =  vl6180x_read_reg(OUTX_L_G);
    *x |= vl6180x_read_reg(OUTX_H_G) << 8;
    *z =  vl6180x_read_reg(OUTZ_L_XL);
    *z |= vl6180x_read_reg(OUTZ_H_XL) << 8;
}

/*
 * This file contains functions to manipulate gpio pins, which includes setting
 * the value of the pins, changing among different modes, and reading these modifications.
*/

#include "gpio.h"

#define FSEL0 ((volatile unsigned int *)0x20200000) //addresses of FSEL registers 0-5
#define FSEL1 ((volatile unsigned int *)0x20200004)
#define FSEL2 ((volatile unsigned int *)0x20200008)
#define FSEL3 ((volatile unsigned int *)0x2020000C)
#define FSEL4 ((volatile unsigned int *)0x20200010)
#define FSEL5 ((volatile unsigned int *)0x20200014)

#define SET0  ((volatile unsigned int *)0x2020001C) //addresses of set, clear, and 
#define SET1  ((volatile unsigned int *)0x20200020) // level registers
#define CLR0  ((volatile unsigned int *)0x20200028)
#define CLR1  ((volatile unsigned int *)0x2020002C)
#define LEV0  ((volatile unsigned int *)0x20200034)
#define LEV1  ((volatile unsigned int *)0x20200038)

/*
 * initializes gpio
 */
void gpio_init(void) {
}

/*
 * Sets GPIO pin number `pin` to the GPIO function `function`. Does not affect
 * the other pins.
 * @param pin: the pin number to initialize
 * @param function: the GPIO function to set for the pin
 */
void gpio_set_function(unsigned int pin, unsigned int function) {
   volatile unsigned int *addr;
   unsigned int shiftVal, temp1, temp2;
   if ((pin >= GPIO_PIN0 && pin <= GPIO_PIN53) && (function >= GPIO_FUNC_INPUT && function <= GPIO_FUNC_ALT3)) {
	if (pin <= GPIO_PIN9) {
		addr = FSEL0;
		shiftVal = ((pin - GPIO_PIN0) * 3);
	} else if (pin <= GPIO_PIN19) {
		addr = FSEL1;
		shiftVal = ((pin - GPIO_PIN10) * 3);
	} else if (pin <= GPIO_PIN29) {
		addr = FSEL2;
		shiftVal = ((pin - GPIO_PIN20) * 3);
        } else if (pin <= GPIO_PIN39) {
		addr = FSEL3;
		shiftVal = ((pin - GPIO_PIN30) * 3);
        } else if (pin <= GPIO_PIN49) {
		addr = FSEL4;
		shiftVal = ((pin - GPIO_PIN40) * 3);
        } else {
		addr = FSEL5;
		shiftVal = ((pin - GPIO_PIN50) * 3);
	}
   	
	temp1 = *addr;
	
	if (function == GPIO_FUNC_ALT3) { //111
		temp2 = GPIO_FUNC_ALT3 << shiftVal; //shift
		*addr = temp1 | temp2; //bitwise OR to get back original value
	} else if (function == GPIO_FUNC_INPUT) { //000
		temp2 = ~(7 << shiftVal); //shift 000 into location
		*addr = temp1 & temp2; //force 0's into register
	} else {	
		temp2 = function << shiftVal; //shift
		*addr = temp1 | temp2; //copied 1's over
		temp1 = *addr;
		temp2 = ~((7-function) << shiftVal); //shift bit pattern into location
		*addr = temp1 & temp2; //force 0's into right location
	}
   }
}

/*
 * Sets gpio pin to input mode by calling appropriate function.
 * @param pin of type unsigned int is the pin whose mode is to be set to input
 */
void gpio_set_input (unsigned int pin) {
   gpio_set_function (pin, GPIO_FUNC_INPUT);
}

/*
 * Sets gpio pin to output mode by calling appropriate function.
 * @param pin of type unsigned int is the pin whose mode is to be set to output
 */
void gpio_set_output (unsigned int pin) {
   gpio_set_function (pin, GPIO_FUNC_OUTPUT);
}

/*
 * Gets the function for GPIO pin number `pin`. Does not affect any regieters.
 * @param pin: the pin number whose state should be returned
 * @return the state of the pin (0 or 1) 
 */
unsigned int gpio_get_function(unsigned int pin) {
   unsigned int function = 0;
   if ((pin >= GPIO_PIN0 && pin <= GPIO_PIN53) && (function >= GPIO_FUNC_INPUT && function <= GPIO_FUNC_ALT3)) {
        if (pin <= GPIO_PIN9) {
                function = (*FSEL0 >> ((pin - GPIO_PIN0) * 3)) & 7;
	} else if (pin <= GPIO_PIN19) {
                function = (*FSEL1 >> ((pin - GPIO_PIN10) * 3)) & 7;
        } else if (pin <= GPIO_PIN29) {
                function = (*FSEL2 >> ((pin - GPIO_PIN20) * 3)) & 7;
        } else if (pin <= GPIO_PIN39) {
                function = (*FSEL3 >> ((pin - GPIO_PIN30) * 3)) & 7;
        } else if (pin <= GPIO_PIN49) {
                function = (*FSEL4 >> ((pin - GPIO_PIN40) * 3)) & 7;
        } else {
                function = (*FSEL5 >> ((pin - GPIO_PIN50) * 3)) & 7;
        }
   }
   return function;
}
/* 
 * This static function appropriately shifts the bits in a register
 * (clock implementation uses set or clear registers) to set the value of the pin.
 * @param loc is the number of bits to be shifted
 * @param *addr is the address of the register where bits will be modified
 */
static void set_value (volatile unsigned int *addr, unsigned int loc) {
   unsigned int temp1, temp2;
   temp1 = *addr;
   temp2 = 1 << loc;
   *addr = temp1 | temp2;
}

/*
 * Sets GPIO pin number `pin` to the value `value`. The GPIO pin is set
 * to output mode before the appropriate set or clear register is modified.
 * @param pin is the pin number to set or clear
 * @param value is 1 if the pin should be set, 0 otherwise
 */
void gpio_write(unsigned int pin, unsigned int value) {
   unsigned int  shiftVal;
   if ((pin >= GPIO_PIN0 && pin <= GPIO_PIN53) && (value == 1 || value == 0)) {
	gpio_set_output(pin);
	if (pin <= GPIO_PIN31) {
		shiftVal = pin - GPIO_PIN0;
		if (value == 1) {
			set_value (SET0, shiftVal);
		} else {
			set_value (CLR0, shiftVal);
		}
        }
        else {
                shiftVal = pin - GPIO_PIN32;
		if (value == 1) {
                        set_value (SET1, shiftVal);
                } else {
                        set_value (CLR1, shiftVal);
                }
       }  
   }
}

/*
 * Read GPIO pin number `pin`. 
 * @param pin s the pin number to be read
 */
unsigned int gpio_read(unsigned int pin) {
   unsigned int value = 0;
   if (pin >= GPIO_PIN0 && pin <= GPIO_PIN53) {
        if (pin <= GPIO_PIN31) {
		return (*LEV0 >> (pin - GPIO_PIN0)) & 1;
        } else {
                return (*LEV1 >> (pin - GPIO_PIN32)) & 1;
        }
   }
   return value;
}

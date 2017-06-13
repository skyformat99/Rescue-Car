/*
 * This file contains functions that implement the odometer.
 */

#include "odometer.h"
#include "gpio.h"
#include "timer.h"

#define FSEL1 ((volatile unsigned int *)0x20200004) //Address of FSEL1 register
#define FSEL2 ((volatile unsigned int *)0x20200008) //Address of FSEL2 register
#define SET0  ((volatile unsigned int *)0x2020001C) //Address of SET register
#define CLR0  ((volatile unsigned int *)0x20200028) //Address of CLR0 register
#define LEV0  ((volatile unsigned int *)0x20200034) //Address of LEV0 register

char array[19]; //bit patterns for 0-9, A-F (b and d are lowercase)
void clearAll();
#define DELAY_TIME 2500

/* Performs initialization of the array containing bitwise pattern for digits and characters. */
void clock_init() {
    gpio_set_output(GPIO_PIN9);
    gpio_set_output(GPIO_PIN10);
    gpio_set_output(GPIO_PIN11);
    gpio_set_output(GPIO_PIN12);
    gpio_set_output(GPIO_PIN17);
    gpio_set_output(GPIO_PIN18);
    gpio_set_output(GPIO_PIN22);
    gpio_set_output(GPIO_PIN23);
    gpio_set_output(GPIO_PIN24);
    gpio_set_output(GPIO_PIN25);
    gpio_set_output(GPIO_PIN27);
    gpio_write(GPIO_PIN9, 0);
    gpio_write(GPIO_PIN10, 0);
    gpio_write(GPIO_PIN11, 0);
    gpio_write(GPIO_PIN12, 0);
    gpio_write(GPIO_PIN17, 0);
    gpio_write(GPIO_PIN18, 0);
    gpio_write(GPIO_PIN22, 0);
    gpio_write(GPIO_PIN23, 0);
    gpio_write(GPIO_PIN24, 0);
    gpio_write(GPIO_PIN25, 0);
    gpio_write(GPIO_PIN27, 0);
    array[0] = 0b00111111;
    array[1] = 0b00000110;
    array[2] = 0b01011011;
    array[3] =  0b01001111;
    array[4] = 0b01100110;
    array[5] =  0b01101101;
    array[6] = 0b01111101;
    array[7] = 0b00000111; 
    array[8] = 0b01111111;
    array[9] =  0b01101111; 
    array[10] = 0b01110111; //A
    array[11] = 0b01111100; //B
    array[12] = 0b00110011; //C
    array[13] = 0b01011110; //D
    array[14] = 0b01111001; //E
    array[15] = 0b01110001; //F
    array[16] = 0b01110110; //H
    array[17] = 0b00111000; //L
    array[18] = 0b01110011; //P
}

/*
 * This static function lights up the required segments to display a number on one of four digits.
 * @param num is the bitwise pattern of the digit to be displayed
 * @param pin is the pin (digit) on which the digit should be displayed
 */
void displayDigit (unsigned int num, unsigned int pin) {
  clearAll();
  unsigned int j = 0;
  gpio_write(pin, 1);
  while (j < 8) { //go through each bit
    if (num & 1) {
      switch (j) {
      case 0:      
	gpio_write(GPIO_PIN17, num & 1); //mask all but last bit
	break;
      case 1:      
	gpio_write(GPIO_PIN18, num & 1); //mask all but last bit
	break;
      case 2:      
	gpio_write(GPIO_PIN22, num & 1); //mask all but last bit
	break;
      case 3:      
	gpio_write(GPIO_PIN23, num & 1); //mask all but last bit
	break;
      case 4:      
	gpio_write(GPIO_PIN24, num & 1); //mask all but last bit
	break;
      case 5:      
	gpio_write(GPIO_PIN25, num & 1); //mask all but last bit
	break;
      case 6:      
	gpio_write(GPIO_PIN27, num & 1); //mask all but last bit
	break;
      }
    }
    num = num >> 1; //right shift by 1
    j++;
  }
}

/*
 * This static function sets all the pins controlling segments to input mode.
 */
void clearAll() {
    gpio_write(GPIO_PIN17, 0);
    gpio_write(GPIO_PIN18, 0);
    gpio_write(GPIO_PIN22, 0);
    gpio_write(GPIO_PIN23, 0);
    gpio_write(GPIO_PIN24, 0);
    gpio_write(GPIO_PIN25, 0);
    gpio_write(GPIO_PIN27, 0);
}

/*
 * This static function displays the time on the clock at a particular rate.
 * @param d1, d2, d3, d4 represent the bitwise patterns for each digit that should be displayed
 * @param delay_counter determines the length of time for which each four digit sequence is displayed
 */
void displayNum(unsigned int d1, unsigned int d2, unsigned int d3, unsigned int d4, unsigned int delay_counter) { 
    while (delay_counter > 0) {
        gpio_write(GPIO_PIN9, 0);
        gpio_write(GPIO_PIN10, 0);
        gpio_write(GPIO_PIN11, 0);
    
        displayDigit(array[d4], GPIO_PIN12);
        delay_us(DELAY_TIME);
        clearAll();

        gpio_write(GPIO_PIN12, 0);
        displayDigit(array[d3], GPIO_PIN11);
        delay_us(DELAY_TIME);
        clearAll();

        gpio_write(GPIO_PIN11, 0);
        displayDigit(array[d2], GPIO_PIN10);
        delay_us(DELAY_TIME);
        clearAll();

        gpio_write(GPIO_PIN10, 0);
        displayDigit(array[d1], GPIO_PIN9);
        delay_us(DELAY_TIME);
        clearAll();

        delay_counter--;
    }
}

/* This function flashes "HELP" on the display ten times. */
void flashHelp() {
    int c = 10;
    while (c > 0) {
        displayNum(16, 14, 17, 18, 40);
        clearAll();
        delay_us(120000);
        c--;
    }
}


/*
 * This file contains functions that implement the clock.
 */

#include "clock.h"
#include "gpio.h"
#include "timer.h"

#define FSEL1 ((volatile unsigned int *)0x20200004) //Address of FSEL1 register
#define FSEL2 ((volatile unsigned int *)0x20200008) //Address of FSEL2 register
#define SET0  ((volatile unsigned int *)0x2020001C) //Address of SET register
#define CLR0  ((volatile unsigned int *)0x20200028) //Address of CLR0 register
#define LEV0  ((volatile unsigned int *)0x20200034) //Address of LEV0 register

char array[16]; //bit patterns for 0-9, A-F (b and d are lowercase)

/* Performs initialization of the array containing bitwise pattern for digits and characters. */
void clock_init() {
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
static void displayDigit (unsigned int num, unsigned int pin) {
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
static void clearAll() {
   gpio_set_input(GPIO_PIN17);
   gpio_set_input(GPIO_PIN18);
   gpio_set_input(GPIO_PIN22);
   gpio_set_input(GPIO_PIN23);
   gpio_set_input(GPIO_PIN24);
   gpio_set_input(GPIO_PIN25);
   gpio_set_input(GPIO_PIN27);
}

/*
 * This static function displays the time on the clock at a particular rate.
 * @param d1, d2, d3, d4 represent the bitwise patterns for each digit that should be displayed
 * @param delay_counter determines the length of time for which each four digit sequence is displayed
 */
void displayNum(unsigned int d1, unsigned int d2, unsigned int d3, unsigned int d4, unsigned int delay_counter) { 
   while (delay_counter > 0) {
	gpio_set_input(GPIO_PIN9);
	gpio_set_input(GPIO_PIN10);
	gpio_set_input(GPIO_PIN11);
  
	displayDigit(array[d4], GPIO_PIN12);
	delay_us(2500);
	clearAll();

	gpio_set_input(GPIO_PIN12);
	displayDigit(array[d3], GPIO_PIN11);
	delay_us(2500);
	clearAll();

	gpio_set_input(GPIO_PIN11);
	displayDigit(array[d2], GPIO_PIN10);
	delay_us(2500);
	clearAll();

	gpio_set_input(GPIO_PIN10);
	displayDigit(array[d1], GPIO_PIN9);
	delay_us(2500);
	clearAll();

	delay_counter--;
   }
}

void flashHelp() {
    int c = 10;
    while (c > 0) {
        displayNum(16, 14, 17, 18, 40);
        clearAll();
        delay_us(120000);
        c--;
    }
}

/* This function runs the clock */
void clock_run() {
   while (1) { //forever loop that constantly runs the clock

	unsigned int d1, d2, d3, d4; 
	d1 = 0;
	d2 = 0;
	d3 = 0;
	d4 = 0;
	displayTime(d1, d2, d3, d4, 100); //Display 00:00 
   
	//Display 00:01 through 99:59
	while (1) {

	   //When the minute button (red) is pressed, the min digits can be reset to desired value.
	   while (gpio_read(GPIO_PIN3) == 0) {
		displayTime (d1, d2, d3, d4, 10);	
		d2++; //set d2
	        if (d2 == 10) {
	   	   d1++; //set d1
		   d2 = 0;
	        }
	        if (d1 == 10) {
                   d1 = 0; 
		   d2 = 0; 
	        }
	   }
       
           //When the second button is pressed, the sec digits can be reset to the desired value.
	   while (gpio_read(GPIO_PIN2) == 0) {
		displayTime (d1,d2,d3,d4, 10);	
	        if (d4 == 9) d4 = 0; //set d4
			else d4++;
		if (d4 == 0) d3++; //set d3
		if (d3 == 6) {
		   d3 = 0;
	        }
           }

	   // Handle all digits when not pressing button
	   if (d4 == 9) d4 = 0; //set d4
	   else d4++;
	   if (d4 == 0) d3++; //set d3
	   if (d3 == 6) {
		d3 = 0;
		d2++; //set d2
 	   }
 	   if (d2 == 10) {
		d1++; //set d1
	        d2 = 0;
	   }
	   if (d1 == 10) break; 
		displayNum(d1, d2, d3, d4, 100);
	}
   }
}

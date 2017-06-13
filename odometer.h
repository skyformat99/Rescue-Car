#ifndef ODOMETER_H
#define ODOMETER_H

void clock_init();
void displayDigit (unsigned int num, unsigned int pin);
void clearAll();
void displayNum(unsigned int d1, unsigned int d2, unsigned int d3, unsigned int d4, unsigned int delay_counter);
void flashHelp();

#endif

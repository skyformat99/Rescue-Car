/*
 * This file contains functions to implement a timer (details
 * explained above each function).
 */

#include "timer.h"
#define CLO ((volatile unsigned int *)0x20003004) //address for lower 32 bits of system timer

/*
 * initialize the timer
 */
void timer_init(void) {
}

/*
 * Returns the current system time in us.
 * @return system time in microseconds
 */
unsigned int timer_get_time(void) {
  return (unsigned int) *CLO;
}

/*
 * A simple busy loop that delays the program for `n` microseconds.
 * @param n the number of microseconds to busy loop for
 */
void delay_us(unsigned int n) {
  unsigned int start = timer_get_time();
  while (timer_get_time() - start < n) { /* spin */ }
}

/*
 * Delay for `n` seconds.
 * @param n the number of seconds to busy loop for
 */
void delay(unsigned int n) {
  unsigned int i;
  for (i = 0; i < n; i++) {
    delay_us(1000000);
  }
}

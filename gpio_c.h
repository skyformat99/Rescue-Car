enum {
    GPIO_PIN_FIRST = 0,
    GPIO_PIN0 = 0,
    GPIO_PIN1 = 1,
    GPIO_PIN2 = 2,
    GPIO_PIN3 = 3,
    GPIO_PIN4 = 4,
    GPIO_PIN5 = 5,
    GPIO_PIN6 = 6,
    GPIO_PIN7 = 7,
    GPIO_PIN8 = 8,
    GPIO_PIN9 = 9,
    GPIO_PIN10 = 10,
    GPIO_PIN11 = 11,
    GPIO_PIN12 = 12,
    GPIO_PIN13 = 13,
    GPIO_PIN14 = 14,
    GPIO_PIN15 = 15,
    GPIO_PIN16 = 16,
    GPIO_PIN17 = 17,
    GPIO_PIN18 = 18,
    GPIO_PIN19 = 19,
    GPIO_PIN20 = 20,
    GPIO_PIN21 = 21,
    GPIO_PIN22 = 22,
    GPIO_PIN23 = 23,
    GPIO_PIN24 = 24,
    GPIO_PIN25 = 25,
    GPIO_PIN26 = 26,
    GPIO_PIN27 = 27,
    GPIO_PIN28 = 28,
    GPIO_PIN29 = 29,
    GPIO_PIN30 = 30,
    GPIO_PIN31 = 31,
    GPIO_PIN32 = 32,
    GPIO_PIN33 = 33,
    GPIO_PIN34 = 34,
    GPIO_PIN35 = 35,
    GPIO_PIN36 = 36,
    GPIO_PIN37 = 37,
    GPIO_PIN38 = 38,
    GPIO_PIN39 = 39,
    GPIO_PIN40 = 40,
    GPIO_PIN41 = 41,
    GPIO_PIN42 = 42,
    GPIO_PIN43 = 43,
    GPIO_PIN44 = 44,
    GPIO_PIN45 = 45,
    GPIO_PIN46 = 46,
    GPIO_PIN47 = 47,
    GPIO_PIN48 = 48,
    GPIO_PIN49 = 49,
    GPIO_PIN50 = 50,
    GPIO_PIN51 = 51,
    GPIO_PIN52 = 52,
    GPIO_PIN53 = 53,
    GPIO_PIN_LAST =  53
};

void gpio_init(void);

enum {
    GPIO_FUNC_INPUT   = 0,
    GPIO_FUNC_OUTPUT  = 1,
    GPIO_FUNC_ALT0    = 4,
    GPIO_FUNC_ALT1    = 5,
    GPIO_FUNC_ALT2    = 6,
    GPIO_FUNC_ALT3    = 7,
    GPIO_FUNC_ALT4    = 3,
    GPIO_FUNC_ALT5    = 2,
    GPIO_FUNC_INVALID = 8 // Only returned for invalid pins
};

/*
 * initializes gpio
 */
void gpio_init_c(void);

/*
 * Sets GPIO pin number `pin` to the GPIO function `function`. Does not affect
 * the other pins.
 * @param pin: the pin number to initialize
 * @param function: the GPIO function to set for the pin
 */
void gpio_set_function_c(unsigned int pin, unsigned int function);

/*
 * Sets gpio pin to input mode by calling appropriate function.
 * @param pin of type unsigned int is the pin whose mode is to be set to input
 */
void gpio_set_input_c(unsigned int pin);

/*
 * Sets gpio pin to output mode by calling appropriate function.
 * @param pin of type unsigned int is the pin whose mode is to be set to output
 */
void gpio_set_output_c(unsigned int pin);

/*
 * Gets the function for GPIO pin number `pin`. Does not affect any regieters.
 * @param pin: the pin number whose state should be returned
 * @return the state of the pin (0 or 1) 
 */
unsigned int gpio_get_function_c(unsigned int pin);

/* 
 * This static function appropriately shifts the bits in a register
 * (clock implementation uses set or clear registers) to set the value of the pin.
 * @param loc is the number of bits to be shifted
 * @param *addr is the address of the register where bits will be modified
 */
static void set_value_c(volatile unsigned int *addr, unsigned int loc);

/*
 * Sets GPIO pin number `pin` to the value `value`. The GPIO pin is set
 * to output mode before the appropriate set or clear register is modified.
 * @param pin is the pin number to set or clear
 * @param value is 1 if the pin should be set, 0 otherwise
 */
void gpio_write_c(unsigned int pin, unsigned int value);

/*
 * Read GPIO pin number `pin`. 
 * @param pin s the pin number to be read
 */
unsigned int gpio_read_c(unsigned int pin);

// set all the pins to be outputs
// pin for motor A dir1, dir2, speed, motor B dir1, dir2, speed

// GPIO 16 SPEED 20 DIR1 21 DIR2 A
// GPIO 13 SPEED 19 DIR1 26 DIR2 B
//#define TIME_TURN 10000000
//#define TURN_FIRST_DELAY 100 //calculate with car
//#define TURN_SECOND_DELAY 10 //calculate with car

#define HIGH 1
#define LOW 0

#define LEFT 0
#define REV 1
#define FWD 2
#define RIGHT 3

int get_dir();

void motor_init();

void forward_motion();

void reverse_motion();

void stop();

void left_turn(int time_turn);

void right_turn(int time_turn);

void move(int i, int time);

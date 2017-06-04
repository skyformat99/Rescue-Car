#define HIGH 1
#define LOW 0
//#define TIME_TURN 10000000
#define TURN_FIRST_DELAY 100
#define TURN_SECOND_DELAY 10

void motor_init();
void forward_motion();
void reverse_motion();
void left_turn(int time_turn);
void right_turn(int time_turn);
void move(int i, int time);
void stop();

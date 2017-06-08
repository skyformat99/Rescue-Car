#ifndef SENSOR_H
#define SENSOR_H

void ultrasonic_init();
void audio_sensor_init(); //audio sensor
unsigned get_distance(void); //ultrasonic sensor
int audio_sensor_fetch(); //audio sensor

#endif

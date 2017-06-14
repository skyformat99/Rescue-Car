Presenting, JDK: The Autonmous Rescue Car

We have created an autonomous rescue car that moves on its own and avoids obstacles. Powered by two motors/motor driver mounted on a wooden chasis, the vehicle uses an ultrasonic sensor to determine the distance of obstacles. The rasberry pi and stepper motors are powered by separate batteries. An odometer is mounted on the back of the car and uses armtimer interrupts to calculate the distance the car has travelled so far. The motor's speed is reduced by one half through implementing software Pulse Width Modulation; armtimer interrupts, executed every 100 microseconds, turn the motors on/off continuously. LED's on the front right, front left, and back of the car flash as indicators when the car is about to move in the appropriate direction. If the car encounters an obstacle closer than the preset threshold, and the obstacles on both left and right sides are also closer than the threshold, the odometer flashes "HELP," and all the LED's flash.

In terms of its functionality as a resuce car, the car can avoid obstacles and drive to locations that may not be accessible by other vehicles that need to be driven manually by people. Once the target in need of help, who is boxed in on all sides, is reached, the car flashes "HELP," flashes its lights, and personnel onboard can adminster aid.

Our final code is in the branch titled "final-branch." 

All of us worked together on all parts of the project (hardware, software, debugging, testing). 
A general breakdown where we spent much of the time is as follows:

Ken - Remote On/Off, Motor/Motor Driver, Ultrasonic Sensor, much soldering :)
Durga - Armtimer Interrupts (PWM, Odometer calculations/display), LED Lights, Motor/Interfacing hardware & software components together
Jenny - Ultrasonic Sensor, Motor/Motor Driver, LED Lights


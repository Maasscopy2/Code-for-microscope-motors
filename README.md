You can use this code to control 28BYJ-48 motors using a USB controller. 

The Motor control.py is set up in order to work with Windows machines, if you want to make it work with Linux machines (e.g. RasberryPi) then you have to change the code.
line 11 from 'COM3' has to become '/dev/ttyACM0' .

A python IDE has to be used in order to run the code (ver. 3.7.3 and higher).

Use the scheme provided to wire the Arduino Nano Every, the motor drivers, and the motors together.

The gamepad_0.1.ino has to be uploaded to an Arduino Nano Every using the Arduino IDE (ver. 1.8.12 and higher)

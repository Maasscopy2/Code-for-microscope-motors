#include <Arduino.h>

// Define pin connections for each motor
const int motor1Pins[] = {13, 12, 11, 10}; // Motor 1
const int motor2Pins[] = {9, 8, 7, 6};     // Motor 2
const int motor3Pins[] = {5, 4, 3, 2};     // Motor 3

// Delay time between steps
const int stepDelay = 2; // Adjust this for speed

// Number of steps to move forward or backward
const int stepsToMove = 100; // Number of steps per command

// Function to initialize motor pins
void setupMotorPins(const int motorPins[]) {
  for (int i = 0; i < 4; i++) {
    pinMode(motorPins[i], OUTPUT);
  }
}

// Function to step the motor forward
void stepMotorForward(const int motorPins[], int steps) {
  for (int i = 0; i < steps; i++) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(motorPins[j], (j == i % 4) ? HIGH : LOW);
    }
    delay(stepDelay); // Adjust delay for motor speed
  }
}

// Function to step the motor backward
void stepMotorBackward(const int motorPins[], int steps) {
  for (int i = steps - 1; i >= 0; i--) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(motorPins[j], (j == (i % 4)) ? HIGH : LOW);
    }
    delay(stepDelay); // Adjust delay for motor speed
  }
}

void setup() {
  Serial.begin(9600); // Start serial communication
  setupMotorPins(motor1Pins);
  setupMotorPins(motor2Pins);
  setupMotorPins(motor3Pins);
  
  Serial.println("Ready to receive 6-digit binary codes.");
}

void loop() {
  // Check if there are at least 6 characters available in the Serial buffer
  if (Serial.available() >= 6) {
    // Read 6 characters directly into a String
    String input = Serial.readStringUntil('\n'); // Read until newline
    input.trim(); // Remove any whitespace

    // Ensure input length is 6
    if (input.length() == 6) {
      // Move Motor 1
      if (input[0] == '1') {
        Serial.println("Moving Motor 1 Forward");
        stepMotorForward(motor1Pins, stepsToMove);
      }
      if (input[1] == '1') {
        Serial.println("Moving Motor 1 Backward");
        stepMotorBackward(motor1Pins, stepsToMove);
      }

      // Move Motor 2
      if (input[2] == '1') {
        Serial.println("Moving Motor 2 Forward");
        stepMotorForward(motor2Pins, stepsToMove);
      }
      if (input[3] == '1') {
        Serial.println("Moving Motor 2 Backward");
        stepMotorBackward(motor2Pins, stepsToMove);
      }

      // Move Motor 3
      if (input[4] == '1') {
        Serial.println("Moving Motor 3 Forward");
        stepMotorForward(motor3Pins, stepsToMove);
      }
      if (input[5] == '1') {
        Serial.println("Moving Motor 3 Backward");
        stepMotorBackward(motor3Pins, stepsToMove);
      }
    } else {
      Serial.println("Invalid input! Please enter a 6-digit binary code.");
    }
  }
}

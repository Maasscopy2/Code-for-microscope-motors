import pygame
import serial
import time

# Initialize the NES controller
pygame.init()
pygame.joystick.init()

# Setup serial communication with Arduino
try:
    ser = serial.Serial('COM3', 9600)  # Change 'COM3' to the correct port for your Arduino
    print("Serial port opened successfully!")
    time.sleep(2)  # Wait for Arduino to initialize
except serial.SerialException as e:
    print("Error opening serial port: {}".format(e))
    exit()

# Check if a joystick is connected
if pygame.joystick.get_count() == 0:
    print("No joystick connected!")
    exit()
else:
    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    print("Joystick initialized!")

# Mapping of button indices for NES controller
button_a = 1  # Button A
button_b = 2  # Button B
# Assuming the D-pad is mapped as button presses (you may need to adjust these)
button_up = 5    # Example index for UP button
button_down = 4  # Example index for DOWN button
button_left = 3  # Example index for LEFT button
button_right = 0 # Example index for RIGHT button

# Function to read gamepad inputs
def read_gamepad():
    pygame.event.pump()  # Process event queue

    # Buttons (A and B)
    a_pressed = joystick.get_button(button_a)
    b_pressed = joystick.get_button(button_b)

    # D-pad inputs as button presses
    up_pressed = joystick.get_button(button_up)
    down_pressed = joystick.get_button(button_down)
    left_pressed = joystick.get_button(button_left)
    right_pressed = joystick.get_button(button_right)

    # Create a command string: "110101" (button_a, button_b, up, down, left, right)
    command = "{}{}{}{}{}{}".format(
        a_pressed, b_pressed, up_pressed, down_pressed, left_pressed, right_pressed
    )

    # Print the gamepad input to the console
    print("Gamepad Input -> A: {}, B: {}, UP: {}, DOWN: {}, LEFT: {}, RIGHT: {}".format(
        a_pressed, b_pressed, up_pressed, down_pressed, left_pressed, right_pressed
    ))

    return command  # Return the command string

# Main loop
while True:
    # Read the gamepad inputs
    gamepad_input = read_gamepad()  # Call the function to get input
    print(gamepad_input)
    # Send the command to Arduino
    ser.write((gamepad_input + "\n").encode('utf-8'))  # Send input as a string with newline

    # Wait for a short time to avoid flooding the serial port
    time.sleep(0.1)



# Pico_Independence_Day_Lightshow
# This project is designed to work with a Raspberry Pi Pico or other RP2040 architecture
# This project is designed to wire up to 9 differently colored LEDs and a single RBG LED with four connections including the anode
# The program written in C++ randomly toggles LEDs, expected to be a combination of red, white and blue to celebrate Independence Day
# Use the Bill of Materials and wire the LEDs to GPIO pins 10 through 18 with appropriate resistors to balance 3.3V and the LED capacity
# The RBG light should be wired to the PICO in the following way: red = gpio 1; green = gpio 2; blue = gpio 3
# The RBG will randomly change between red, white and blue itself when the program is successfully executed.
# I assume you have already used a raspberry pi pico and have the SDK installed. If not, you should read the getting started manual for the Pico here: https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf
# Also download the SDK book here and read after the one above: https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf
# I provide the necessary CMakeLists.txt file in this repository.

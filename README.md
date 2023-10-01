# PwFusion_I2C_Buttons

Are you looking for a way to take your project to the next level? Playing with Fusion's I2C Buttons board is the way to go! This device greatly simplifies connectivity to a microcontroller through the QWIIC system. The typical 6 wires required to use 5 push buttons with a microcontroller can be reduced to one QWIIC cable. You can even chain multiple QWIIC devices together for maximum wiring efficiency! If that isn't enough, Playing with Fusion provides Arduino libraries to make writing code for these boards as easy as possible! Weather you are a beginner looking for a simple introduction to the world of hobbiest electronics or an advanced user looking for a rapid prototyping tool, Playing with Fusion's I2C Joystick is right for you!

## I2C Addresses

ADR Jumper connected: 0x05
ADR Jumper disconnected: 0x06

Each Playing with Fusion I2C interface board comes with 2 available I2C addresses, which can be easily selected by disconnecting a jumper on the printed circuit board. This allows for 2 of the same boards (ex: 2 button boards) to be used on the same QWIIC chain. If you would like more than 2, see docs/Programming Instructions and flash a modified firmware with additional I2C address options.
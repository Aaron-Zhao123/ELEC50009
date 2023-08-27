Department of Electrical & Electronic Engineering

Imperial College London


# Lab 3 –  Integrate an accelerometer with a NIOS

## Objectives
By the end of this experiment, you should have achieved:

* Designed a NIOS II system that interfaces with the accelerometer on DE10-
lite board
* Understand the design process of a NIOSII system and the SPI interface
* Learn how to read the acceleration value provided by the accelerometer
* Design a low-pass FIR filter to process the readings
* Investigate the impact of using low arithmetic precision to the quality of the results and the performance of your system.

## Task 1: Interface an accelerometer to a NIOS II system

The first objective of the lab is to show you how you can interface the Nios 
processor with an accelerometer. 

The DE10-lite comes with a digital accelerometer sensor module (ADXL345), commonly known as G-sensor. This G-sensor is a small, thin, ultralow power assumption 3-axis accelerometer with high-resolution measurement.

Digitalized output is formatted as 16-bit in two’s complement and can be accessed through SPI (3- and 4-wire) and I2C digital interfaces. 

SPI stands for Serial Peripheral Interface and it is one of the most common interfaces between a microprocessor and a peripheral with low-bandwidth requirements, and this is what we will use to interface the accelerometer to NIOS. 

Please follow the steps below to design your system. The main difference with the previous system, is that you will add an extra IP, the Accelerometer SPI mode, which will interface your NIOS to an SPI peripheral. As you should have experience by now how to design a NIOSII system, the steps below are given at a high-level.

Steps:
1. Open the provided DE10_LITE_Golden_Top project and launch Platform 
Designer
2. Add the following IPs:
    * Nios II Processor (select Nios II/e and click Finish)
    * On Chip Memory (change the size to 65536 and uncheck Initialize memory content)
    * JTAG UART
    * PIO for LED (10 bits, output)
    * Interval Timer
    * Accelerometer SPI Mode
3. Rename and connect your IPs as follows, ensuring that led and spi export 
external connections.
4. Assign Base Addresses: System -> Assign Base Address
5. Set both the reset vector memory and exception vector memory of cpu to 
onchip_memory.s1
6. Save the file as nios_accelerometer.qsys
7. Generate the HDL. 
8. Go back to Quartus, add the generated file into your project
9. Copy the code in nios_accelerometer_inst.v and paste them in `DE10_LITE_Golden_Top.v`. Modify the top level file code as follows: 
10. Compile your design.
11. Launch Eclipse
12. New -> Nios II Application and BSP from Template.
13. Choose .sopcinfo and choose Hello World Small as template
14. Replace the existing code with the code form led_accelerometer_main.c
15. Build the project in Eclipse and program your device using the terminal 
commands. The LEDs should indicate the titling position of your board.


Note: 
1. You can find more information about the accelerometer in the DE10-Lite User Manual.
2. You can find more information about SPI here: 
https://www.analog.com/en/analog-dialogue/articles/introduction-to-spi-interface.html#
3. This part of the tutorial is based on: 
http://venividiwiki.ee.virginia.edu/mediawiki/index.php/Accelerometer_Controlled_LED
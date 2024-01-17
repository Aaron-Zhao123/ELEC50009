Department of Electrical & Electronic Engineering

Imperial College London

# Lab 4 –  Integrate an accelerometer with a NIOS

## Task 1: UART communication with a host PC

A design is provided (`lab4_task1.zip`) that allows a NIOSII to communicate with the host PC through a UART interface.
The main difference of this design from what you have developed so far is the addition of off-chip memory, extended the memory capacity of your system.

Please open the design files and have a look and the system.

The design is located in the jtag-uart-test directory. You will also notice that the system also includes a PLL (Phase-Locked Loop).

The PLL can generate a signal whose phase is related to an input signal.
As the signals to/from off-chip memory exhibit considerable delays, a shifted version of the clock (phase shift) that drives the off-chip memory related to NIOS needs to be used, in order to allow to the data a full clock cycle for registration.

Please note, that for establishing UART communication between the host PC and NIOS, you do not need to add off-chip memory.

This design serves just as an example in case you develop a system that requires more memory than is available on-chip.

There are two sides to the communication, the host side (`host.py`) and board side (`jtag-uart-test/software/task1/task1.c`).
The host program sends signals to the board, waits on a response and then processes the response.
The board side code polls the UART port for input. Board-Side Code (`jtag-uart-test/software/task1/task1.c`):

The board side code presented here is written in conjunction with the python host file. To see more interaction capabilities of the board, look at the DE_seven_segment_display.c file.

In this design, the NIOS processing is put into a slave mode, responding to commands sent out by the host.

To enable this to work, the `hello_world_time_limited.sof` can be directly used to program the DE10-Lite board and will directly work for the code described below.

The board-side code performs the following steps:

1. Starting at the main function, go straight to reading the characters being brought in.
2. The running variable is used to keep the process live and running indefinitely until the QUITLETTER
variable is sent along the JTAG/UART line.
3. Inside the while loop, `alt_getchar()` reads from the /dev/jtag_uart port by extracting a
single character. This also stalls the processing until a new character is encountered.
4. After the first character is received the text buffer gets filled with the input
a. The new character is checked if it is a quitting character and is added to the text
buffer (line 21), incrementing the text index pointer.
5. After all operations with the character are done, the next character si read in, until a new
line ‘\n’ character is encountered.
6. After reading in the input, the text is printed back out to the host terminal
    * A string is generated, being ended with the character 0x4. This character returns Ctrl+D up to the host to get the host terminal to terminate. This is important to ensure your host code can keep running.
    * The string is then printed to the host terminal.
    * The text buffer is finally emptied out so that it can be used for the next input. Most of the code for the rest of the course will be added inside the while loop between generate_text and  `print_text` function as this is best place to react to the produced string and provide a response that will be passed back to the host.
    * Host-Side Code (`host.py`): Familiarize yourselves with the python code. The code sends commands  to the NIOS processor and then reads a response which it can then operate on.

### Steps

> [!TIP]
> You may need to install Python first and ensure Python is available in your powershell.

1. Open the project `jtag-uart-test` in Quartus, and run the programmer to download `hello_world_time_limited.sof` to the DE10-Lite board.
2. Create a new software project using the `jtag-uart-test\qsys_system\cpu.sopcinfo`, hello_world BSP template, and the `task1.c` file provided in the `jtag-uart-test\software` directory. Compile the project to get the `.elf` file.
    * `jtag-uart-test\software` also contains a compiled `.elf` file.
3. Following the note in lab2, use Powershell to download the `.elf` file to the DE10-Lite board using the following command.
4. Try the command `nios2-terminal.exe <<< hello` in the terminal to see if the communication is working. You should see the following output.

    ```terminal
    $ nios2-terminal.exe <<< hello
    nios2-terminal: connected to hardware target using JTAG UART on cable
    nios2-terminal: "USB-Blaster [USB-0]", device 1, instance 0
    nios2-terminal: (Use the IDE stop button or Ctrl-C to terminate)
    <--> Detected 5 characters: hello <-->
    nios2-terminal: exiting due to ^D on remote
    ```

    The first time may not be successful. If 0 characters are detected, you may try `nios2-terminal.exe <<< hello` again.

Most of the processing for the coursework will use variations of the perform_computation that will be used to send and receive data to and from the NIOS processor.

## Task 2: Extend your Lab 3 system

Use the provided example, and integrate the provided infrastructure with your Lab 3 project (i.e. accelerometer). Modify the code so your system can operate between two modes depending on the command received by the host:

* Mode 0: no filtering of the accelerometer data
* Mode 1: filtering the accelerometer data should take place

Think how the processing of the commands and the rest of the code should be integrated. As you NIOS is polling the jtag, think about the frequency of polling and how this impacts the sampling of the accelerometer.

* Challenge 1: Add a command to update the coefficients

    The objective here is to add a new command that enables the host PC to update the coefficients of the FIR filter. As the UART only sees characters, you need to think how to convert a sequence of characters into a number. You may need to have a number of assumptions for your communication such as number of coefficients for transmission and number of digits per coefficient.

* Challenge 2: Add a command to plot accelerometer data in real-time

    The objective here is to add a new command that enables the host PC to plot the accelerometer data (processed or not) in real-time. The command should specify the duration (number of samples to be plotted) so after the execution of the command a new command can be issued.

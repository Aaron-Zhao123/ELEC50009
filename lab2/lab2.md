Department of Electrical & Electronic Engineering

Imperial College London

# Lab 2 – Design a NOIS2 System

## Objectives

By the end of this experiment, you should have achieved:

* Design a NIOS II system
* Understand the design process of a NIOSII system
* Program the Max 10 FPGA chip on the DE10-Lite board with your design
* Write code that runs on the processor NIOS to display a message on a terminal
* Explore and test the capabilities of your NIOS II system design

## Task 1: Design a NIOS II System

The objective of the lab is to show you how you can instantiate a soft processor on your FPGA, connect it to various peripherals of the board, familiarize yourselves with how you can interface with these peripherals from the processor, and establish a communication with the host-PC and display a “hello” message on a terminal.

Our target processor is a NIOS II, a soft-core processor that is provided by Intel and targets Intel FPGA devices.  The steps that you have to follow in order to complete this lab are described in the [*Hello_World_Lab_manual_DE10_Lite.pdf*](./Hello_World_Lab_Manual_DE10_Lite.pdf), and I will be referring to this document as **manual**.

### Steps

> [!TIP]
> Please note that the manual is using an older version of Quartus. As such, the process outlined may not be directly applicable to your case. Please follow the instructions below to complete the lab.

1. Follow the steps outlined in the manual starting from Section 2 (page 11).
2. In **page 11**, the manual refers to Qsys. In the new version of Quartus this has been changed to **Platform Designer** under the tool menu.
3. Once you have completed **page 26** before you assign the base addresses, add in a **System ID Peripheral Intel FPAG IP unit** and attach the clk and reset as expected. Furthermore connect the `control_slave` the `cpu.data_master`.
4. In **page 30**, the manual describes how to include the NIOS system that you have designed to a top-level module `DE10_LITE_Golden_Top.v`. The top level module provides the necessary code to connect a design to the specific components of the DE10-LITE board, this file is provided at [`lab2/src/Golden_Top/DE10_LITE_Golden_Top.v`](./src/Golden_Top/DE10_LITE_Golden_Top.v).
    * You can open the `nios_setup_v2_inst.v` in the directory where you generate QSys HDLs to see the code that describes your NIOS system. You need to copy the NIOS declaration from the `nios_setup_v2_inst.v` into `DE10_LITE_Golden_Top.v`, and make the following changes in order to connect your NIOS system to the ports of the high level module as shown in the figure below. It is also worth to note that this is instantiating the qsys componenet (NIOS2 CPU system), so the module name should aligh with your system name (in this case I named it `lab2`), and `system` is simply the instance name.

        <img src="./images/lab2_qsys.png" alt="drawing" width="720"/>

5. In page 30, please ignore step 2
6. In page 30, in step 4, add the nios_setup_v2.qsys file (rather the .qip file)

If you have followed the above instructions, then you should be able now to compile the NIOS system for your board. Well Done! Please try to understand what you are doing in each step (rather than just clicking and following the instructions), as this enhances your understanding of how a processor system is designed. The next task is to write the software for your system.

## Task 2: Program a NIOS II system

> [!TIP]
> Quartus 18.1 already has eclipse installed, but newer version requires manual installation of Quartus. If you are not using Quartus 18.1 and failed to launch *NIOS II Software Build Tools for Eclipse*, please refer to the Troubleshooting section at the end of this document.

Please follow the instructions of part 2 of the manual. Follow the manual and use the `hello_world_small` example.

Once you reach step 15 on page 44, you can stop following the instructions. At this point follow the instructions below:

1. Right click hello_world_sw_bsp then go to Nios II -> Generate BSP
2. Right click hello_world_sw then select Build Project
    * If the building of a project is successful, then you should have a `.elf` file created in your “software” directory of your project. This is the file that needs to be downloaded to NIOS and executed.
3. Right click hello_world_sw then Run As -> Run Configurations
    * Inside the window, go the Target Connections tab
    * If you do not see anything inside Processors window, ensure your  board is properly connected.
    * If there is a problem with the system ID, ensure that your qsys design is constructed properly, the system ID unit is correctly connected and  you have properly connected everything in your top level verilog file.
        * After this you can regenerate the BSP
        * If everything is properly connected, come back to this window and Refresh Connections and then Resolve Names.
    * If there is a problem with the timestamp, regenerate the BSP
4. Make sure you have your `hello_world_sw` and `hello_world_bsp` ready, and the `.elf` file has already been generated.
5. Click on the Target Connection tab, and click Refresh Connections, then Resolve Names.
    * The connection should indicate that Eclipse has connected to the USB-blaster.
    * Note that you might need to stretch the window wider to see the Refresh Connections button.
6. Once the connection is made to the USB-Blaster, you should observe something like the following:

    <img src="./images/run_cfg.png" alt="drawing" width="720"/>

7. Click on the Run button, and you should see "hello world" printed on the console tab at the bottom of the Eclipse window:

    <img src="./images/cmd_shell_win.png" alt="drawing" width="720"/>

> [!Important]
> **How to download the `.elf` file to the FPGA board using Terminal**
> In lab 4 you will be required to download the `.elf` file to the FPGA board and interact with the board using the terminal. The following steps show you how to do this:
>
> 1. Open a terminal window (PowerShell on Windows) and execute `Nios II Command Shell.bat` in Quartus installation directory. This will set up the environment for you to use the NIOS II tools.
>
>     ```powershell
>     & 'C:\intelFPGA_lite\23.1std\nios2eds\Nios II Command Shell.bat'
>     ```
>
> 2. Then navigate to the directory where your `.elf` file is located, and use `nios2-download` to download the file to the FPGA board.
>
>    ```powershell
>    cd <your_elf_file_directory>
>    nios2-download -g <your_elf_file_name>.elf
>    ```
>
> Now you should be able to see the output of your program on the terminal.

---

By now, you should have successfully run your C code on the NIOS processor. If you press button KEY0/KEY1 on the board, LED0/LED1 will be lit up as the processor is reading the status of the buttons and writing the status to the LEDs. However, unlike the lab described in the manual, LED2 is not driven by any hard-wired switch. You can modify your QSys and top Verilog code to achieve this. Have a try!

## Task 3: Extensions - Challenges

Having learned to program our system, let’s make something fun.
Change the `hello_world.c` code to light up the LEDs in a sequence.
For example, you can light up the LEDs from left to right in a specific pattern by controlling the time to light up LED x after having light up LED x-1. Use the two keys (push buttons) to produce two different patterns. Print any related information on the terminal. Think how to produce a delay in lighting up the LEDs.
You can also think how to use the slide switches and the six 7-segment display to provide more complicated set of patterns

## Troubleshooting

In Quartus, if clicking Tools > NIOS2 Software Biuld Tools has no effect (eg. no window pops up). This is likely because you have not installed NIOS2 Eclipse properly. The new version of Quartus requires a separate install of NIOS2, which you should follow the instructions at `"C:\intelFPGA_lite\<your_version_number>\nios2eds\bin\README"` to install Eclipse and plugins.

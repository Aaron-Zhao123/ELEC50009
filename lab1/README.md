Department of Electrical & Electronic Engineering

Imperial College London

# Lab 1 – Introduction to DE10-Lite and Setting up Quartus Prime Lite

## Objectives

By the end of this experiment, you should have achieved:

* Setting up the Quartus Prime Lite to run on your machine;
* Create a directory structure for this and subsequent Labs;
* Create a new project in Quartus and complete a basic 7-segment LED display decoder design using Quartus and Verilog from start to finish;
* Program the Max 10 FPGA chip on the DE10-Lite board with your design;
* Create another project to perform hexadecimal to BCD decoding;
* Explore and test your decoder design.

### Installing Quartus Prime Lite

> [!WARNING]
> It is highly recommend to install **Quartus Prime Lite 18.1**. Other versions may have missing IPs or require other dependencies.

You will be using Intel/Altera software known as Quartus Prime Lite. **The level 1 lab machines should have Quartus 18.1 installed**. If you prefer to develop on your own laptop:

1. You are using a Windows machine: you can download and install Quartus Prime Lite 18.1 from [the official webset](https://www.intel.com/content/www/us/en/software-kit/665990/intel-quartus-prime-lite-edition-design-software-version-18-1-for-windows.html).
    * If your USB-blaster driver is not installed properly by Quartus installer, check the Appendix at the end of this document.
2. You are using a Linux machine: you can download and install Quartus Prime Lite 18.1 from [the official webset](https://www.intel.com/content/www/us/en/software-kit/665988/intel-quartus-prime-lite-edition-design-software-version-18-1-for-linux.html). Note that depending on your linux version, you may need to install missing dependencies and [fixes USB-blaster driver](https://www.intel.com/content/www/us/en/support/programmable/support-resources/download/dri-usb-b-lnx.html).

Known issues with installations

- Only Quartus 18.1 and 20.1 have been tested and verfieid working. Quartus 20.1+ actually WILL NOT WORK!
- Quartus 20.1 would require a correct installation of Eclipse, please follow the pdf guide.
- Windows with 20.1 requires WSL1 (not WSL2).
- VM (Virtualbox) can be really slow if you do not have a powerful machine, and may encounter JTAG issues depending on the OS you are running (lab4).

Preferred setup (from high to low)

- Win11 + Quartus 18.1 (lab machine setup)
- Linux + Quartus 20.1/18.1 (laptop)
- Win11 + Quartus 18.1 (laptop)
- Win11 + WSL1 + Quartus 20.1 (laptop)

Official GTA support is only provided to lab machines, we do not have the bandwidth to accomondate different OS needs, since we realised many other factors (incorrect wsl install, quartus install) can affect a correct installation.

### The DE10-Lite FPGA Board

You have been loaned a DE10-Lite.  Connect the DE10 board to your machine using the USB cable provided.  You should see the board LED displays cycling through all digits, showing that the board is working properly.  The diagram below shows the features provided on this board.  Note that the FPGA chip is 10M50DAF484C7G.

<img src="./images/altera_max10.png" width="480"/>

## Task 0: Preparation

In task 1, you will use four slide switches on the right (SW3 to SW0) on the DE10 board as input, and display the 4-bit binary number as a hexadecimal digit on the right-most 7-segment display (HEX0). In task 0, you will check that everything is working properly by directly opening a pre-compiled `.sof` file.

<img src="./images/task0_overview.png" width="480"/>

### Step 1:  Creating a good directory structure

Before you start carrying out any design for this Lab, it would be very helpful if you first create a directory structure for the labs. A possible directory structure is shown below:

```bash
├── parent_dir
    ├── lab1
    │   ├── task1
    |   │   ├── task1_top.sv
    |   |   └── others.sv
    │   ├── task2
    │   ├── ...
    |   └── mylab
    ├── lab2
    ├── lab3
    └── lab4
```

If you are using a Windows 10 machine, create this in a convenient location such as `C:/E2_CAS/`. We will use `parent_dir` to represent this parent directory.

### Step 2:  See what you are aiming for

Go to the course webpage and download a copy of the solution for Exercise 1: “lab1task1_sol.sof” to your folder for Lab1 (or wherever that is), it should be in the form of `parent_dir/lab1/task0`.  Make sure that your DE10 board is plugged in and running.

### Step 3:  Setting up programming hardware

Run Quartus software on your computer.
Click command: Tools > Programmer.
In the popup window, click: Hardware Setup ….
You should see something like the diagram below.
Then select: USB Blaster. This is to tell Quartus software that you are using the DE10 interface to program (or blast) the FPGA.

If you do not see USB-Blaster under Hardware Setup although the DE10-Lite is plugged in properly, it is most likely that the Device Driver had not been installed or loaded properly. In which case, please see the instruction in the Appendix.

<img src="./images/usb_blast.png" width="270" />

### Step 4: Blasting the FPGA

Next click the AddFile button.

Navigate to the folder containing the `lab1task1_sol.sof` file.  Select this.  You should see a display like this:

<img src="./images/hardware_setup.png" width=200 />

Note that the device indicated here is the one on the DE10 board: **10M50DAF484**.

Click the Start button.

The `lab1task1_sol.sof` file contains the solution to Task 1.

It has the bit-stream to configure (or programme/blast) the FPGA Max10 chip. Once the bit-stream is successfully sent to the FPGA chip, the task1 design will take over the function of the chip.  You should be able to change the least significant four switches and see a hexadecimal number displayed on rightmost 7-segment display. Now you are ready to create this design from scratch.

## Task 1: The Design Flow – 7 Segment LED Display

### Step 5: Create the project “task1”

* Create in your home directory the folder `parent_dir/lab1/task1`.
* Click file>New Project Wizard, complete the form. Use `task1` as the project name and `task1_top` as top-level design name.
* Click Finish.

<img src="./images/project_wizard.png" width="480" />

### Step 6: Device Assignment

Click Assignments -> Device, and select the Max 10 chip used in DE10, which is:  10M50DAF484C7G.  (Interpretation of the device code: 10M is Max10 family. 50 is the size of the device of around 50,000 logic elements.  484 is the number of pins.  C7 is the speed grade.)

### Step 7: Creating the Verilog specification

* In Quartus, create a design file for the decoder module in Verilog HDL as hex_to_7seg.v using: File >  New ….  and select Verilog HDL from the list.
* Type the Verilog source file as shown here. Make sure that you pay attention to the syntax of Verilog. Save your file.
* At this stage, you check the syntax of your code by clicking:  Process > Analyze current file.  You should get into a habit of ALWAYS perform this step to make sure that the new Verilog module you have created is error free.  It will save you a lot of time later.
* Click:  Project > Add Current file to Project to include this module in your design.

<img src="./images/7seg_verilog.png" width="200" />

### Step 8:  Create Top-Level Specification in Verilog

* We need to create a top-level (at chip level) design that make sure of the decoder module. Create the file “task1_top.v” as shown here.  Specify that this is our top-level design with:
Project > Set as Top-level Entity ….
* Verify that everything works properly with:  Process > Start > Start analysis & elaboration. Make sure that there is no error.  (Warnings often capture potential errors.  However, the Quartus system generates many warnings, and nearly all of which are not important.  Once you have gain confidence in the system, you may start ignoring the warning, but never ignore any error.)

<img src="./images/top_verilog.png" width="300" />

**You will save a lot of time if you ALWAYS use these two steps: analyze, and analysis & elaboration, and ensure that ALL errors are dealt with (and warning understood).**

Note:  Every time you create a new entity or module as part of your design, you must include the file in the project. Click: Project > Add Current Files to Project ….,

### Step 9: Pin assignment – the hard way

You need to associate your design with the physical pins of the Max 10 FPGA on the DE10 board.  We will now only assign two of 11 pins used in our design.

* Click Assignment > Pin Planner   and a new window with the chip package diagram. You should also see the top-level input/output ports shown as a list.
* Click on the field shown and select the appropriate values for Location and I/O standard.
* Close the pin assignment window and click: File > open…  Enter *.* in the file name field and select: task1.qsf (qsf = Quartus Setting File).  Examine its contents.  You should see the effect of the manual pin assignment step as highlighted in RED.
* The first line defines the physical pin location of HEX0[6]  is PIN_C17.
* The second line defines the voltage standard used is 3.0V LVTTL.

![](./images/pin_hex.png)

<img src="./images/pin_loc.png" width="480">

<img src="./images/pin_loc2.png" width="480">

### Step 10: Pin Assignment – the easy way

* Manual pin assignment is tedious and prone to errors.  A much better way to perform pin assignment is to insert a text file with the necessary information directly into the `.qsf` file.
* Delete the four lines highlight above which was created through the manual pin assignment in Step 9.
* Download from the course webpage: `pin_assignment.txt` to the task1 folder.
* Click:  Edit > Insert File …   and insert pin_assignment.txt at the end of the file.
ALL the pins used on the DE10 are assigned here. However, unused pins are ignored.

### Step 11: Compile the design & Programming the FPGA

* Click Process > Start Compilation.  This will perform all the steps of compilation, placement, routing, fitting etc. and produce a bit-stream file (.sof) ready to blast onto the FPGA.
* Examine the Compilation Report and you should see a Flow Summary similar to the one shown here.

* This correctly shows that the design used 8 logic elements (out of nearly 50,000) and 11 pins.
* Programme the DE10 with YOUR design with the file: task1_top.sof. (See Task 0 if you have forgotten how to do this.)   Test you design.

**Congratulations! You have now completed your design from beginning to the end.**

**Put verified modules in mylib**

For the rest of this module, you will design and verify various Verilog modules which you will reuse.  You should copy `hex_to_7seg.v` (and others in the future) to the “mylib” folder and include them in your new design as necessary.

Note:  When you perform a compilation, there may be a popup window informing you that some “Chain_x.cdf” file has been modified, and ask if you wish to save it. Just click NO.

## Task 2: Explore Netlist Viewer and Timing Analyzer

### Step 1:   Viewing the design

Quartus Prime provides a graphical view of the synthesized design. Exploring this provides you with some insight into how the Verilog HDL code is turned into actual FPGA hardware.

* Click  Tools > Netlist Views > RTL Viewer
This should appear on your screen:

    ![](./images/rtl_view.png)

* Push down into this block and investigate what is being displayed and how it relates to the decode logic.
RTL Viewer only shows the abstract Boolean description of the design, not the physical implementation on the FPGA.
* Click  Tools > Netlist Views > Technology Map Viewer (post mapping)
Explain what you find and link this back to the Compilation Report.

### Step 2:  Timing Analyzer

Click  Tools > Timing Analyzer

A Timing Analyzer window will appear.

Now click Report datasheet.  The Timing Analyzer tool will provide datasheet type table showing the propagation delays of all the paths in your design

Study the results for worst-case delay at different temperature and explain what you found.

![](./images/netlist_view.png)

### Step 3:   Test yourself

Create your own design in task2 folder (top-level file is task2_top.v) to display all 10-bit sliding switches as hexadecimal on three of the 7 segment LED displays.

## Appendix

> [!TIP]
> **Installing USB-Blaster Device Drive under Windows 10/11**
>
> If you are installing Quartus directly to your PC running Windows 10/11, you may need to install the driver manually according to the following steps:
>
> 1. Plug the USB-Blaster into your PC.
> 2. Open the Device Manager
> 3. Under Unspecified, USB Blaster should be listed. Right mouse click on this and then select Properties.
> 4. Select the Hardware tab and select Properties.
> 5. A new window should pop up with the General tab already selected. Select Change Settings.
> 6. Again a new window should pop up with the General tab already selected. Select Update.
> 7. Select Browse my computer for driver software.
> 8. Select the folder `C:\intelFPGA_lite\18.1\quartus\drivers\usb-blaster`. Note that stop at the drivers folder, i.e., do NOT go deeper by opening a folder within the drivers folder
> 9. Select OK. Make sure the proper path was selected then select Next.
> 10. If the Windows security window pops up, check the Always trust software from “Altera Corporation” box and select Install.

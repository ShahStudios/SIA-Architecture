# SIA-Architecture
Custom Built Computer Architecture for Machine Code. <br />
This program uses C to make a custom machine code assembler and compiler. A test case is provided to be used with the assembler and virtual machine. The assembler takes user inputs from the test cases and turns into hex to be read by the virtual machine.
The VM will proceed to fetch, dispatch, execute, and store the data.

# Installation
Install is as simple as downloading and running with visual studios. <br />
Although a command terminal with GCC will be needed to read the hex data that is printed out.

# GCC installation guide
GCC installation for windows https://www.youtube.com/watch?v=sXW2VLrQ3Bs <br />
Macs can use "command line: od -x" for hex dump <br />
Technologies: Microsft Visual Studios 2019: C 

# Instruction Set Functionality
* add (opcode 1)<br/>
	Adds the values of 2 registers and places the answer in a third register. <br/>
	Example: add r1 r2 r3 ; r3  r1 + r2 <br/>
	Instruction format: 3R <br/>
  *

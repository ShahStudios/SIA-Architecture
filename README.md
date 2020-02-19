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
* addimmediate (opcode 9) <br/>
	Adds a signed 8 bit value to a register <br/>
	Example: addimediate r1 -127 ; adds -127 to r1 <br/>
* and (opcode 2)<br/>
	Preforms a bitwise and on 2 registers and stores the result in a third register <br/>
	Example: and r1 r2 r3 ; r3  r1 & r2 <br/>
* branchifequal (opcode 10) <br/>
Compares two registers – if they hold the same value, jump to an offset from the current program counter. The offset can be between -524,286 and 524,286. The offset is the number of words (2 bytes) forward or back. PC <= PC + (2 * offset). <br/>
Example: branchifequal r1 r2 1000 <br/>
* branchIfless (opcode 11) <br/>
Compares two registers – if the first is less than the second, jump to an offset from the current program counter. The offset can be between -524,286 and 524,286. The offset is the number of words (2 bytes) forward or back. PC <= PC + (2 * offset). <br/>
Example: branchifless r1 r2 1000 <br/>
* call (opcode 13) <br/>
Calls a “function” – pushes the PC of the next instruction onto the stack (R15), then jumps to the address specified by this instruction times 2 (0 – 1,073,741,824). <br/>
Example: call 444  <br/>
* divide (opcode 3) <br/>
Divides the value of the first register by the second and places the answer in a third register. This is integer math with the fractional portion discarded. <br/>
Example: divide r1 r2 r3 ; r3  r1 / r2 <br/>
* halt (opcode 0) <br/>
	Stops the CPU. <br/>
	Example: halt <br/>
* interrupt (opcode 8)<br/>
Interrupts the CPU using a particular interrupt number. This could be used to jump between kernel mode and user mode or to support devices. For the virtual machine, two interrupts are supported: 0 (print registers) and 1 (print out memory) <br/>
Example: interrupt 17 <br/>
* jump (opcode 12) <br/>
	Jumps to the location specified in the instruction times 2 (0 – 1,073,741,824) <br/>
	Example: jump 1000 <br/>
* load (opcode 14)<br/> 
Loads a register from the memory pointed to by another register plus 2 times the offset (0 to 30). Note that both the address in the register and the offset are in words (memory locations). <br/>
	Example: load r1 r2 10 ; loads r1 with the value pointed to by r2 plus 20 bytes <br/>
* multiply (opcode 4) <br/>
Multiplies the value of the first register times the second and places the answer in a third register. <br/>
	Example: multiply r1 r2 r3 ; r3  r1 * r2 <br/>
* or (opcode 6) <br/>
	Performs a bitwise OR on 2 registers and stores the result in a third register <br/>
	Example: or r1 r2 r3 ; r3  r1 | r2 <br/>
*













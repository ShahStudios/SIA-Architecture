#include <stdio.h>
#include <stdlib.h>
#define memorySize 25
#define regSize 16
char currentInstruction[4];
unsigned char memoryArray[memorySize];
int regArray[regSize];
unsigned char opcode;
unsigned char haltFlag = 0;
int pc = 0, op1 = 0, op2 = 0, op3 = 0, result = 0, r15 = 25, getReg1, getReg2, getReg3, getJmpOffset, getBrOffset, getAiNumber, getLsNumber, getIntNumber, getTwoBits, copyMemory;

void loadFile (char *textFile) 
{
	FILE *src;
	if ((src = fopen(textFile,"r")) == NULL) 
	{
		printf("Error! opening file");
		exit(1);
	} 
	fread (memoryArray, memorySize, 1, src);
	fclose (src); 
}

void fetch() 
{
	printf("\n<--------------------- Fetch Instruction ---------------------->\n");
	int counter = pc;
	for (int i = 0; i < 4; i++) 
	{
		currentInstruction[i] = memoryArray[counter];
		counter++;
	}
}

void dispatch()
{
    opcode = ((currentInstruction[0] & 0xF0) >> 4);
	getReg1 = (currentInstruction[0] & 0x0F);
	getReg2 = ((currentInstruction[1] & 0xF0) >> 4);
	getReg3 = (currentInstruction[1] & 0x0F);
    getAiNumber = (((int)currentInstruction[1]));
	getTwoBits = ((currentInstruction[1] & 0xF0) >> 4);
    getIntNumber = (((int)currentInstruction[0] & 0x0F) << 8) | ((int)currentInstruction[1]);
    getBrOffset = ((((currentInstruction[1] & 0x0F) << 16) | (((int)currentInstruction[2]) << 8) | (currentInstruction[3])));
	getJmpOffset = ((((int)currentInstruction[0] & 0x0F) << 24) | (((int)currentInstruction[1] & 0xFF) << 16) | (((int)currentInstruction[2] & 0xFF) << 8) | ((int)currentInstruction[3] & 0x0F));
    printf("              ->  The current opcode value is: %d  <-\n", opcode);
	printf("            ->  The current pc counter value is: %d  <-\n\n", pc);
	
	if (opcode > 0 && opcode <= 6) 
	{
		op1 = regArray[getReg1];
		op2 = regArray[getReg2];
        printf("   ->  The current register value for operator one is: %d  <-\n", op1);
        printf("   ->  The current register value for operator two is: %d  <-\n", op2);
	} 
    
	if (opcode == 7) 
	{
		op1 = regArray[getReg1];
		op2 = getTwoBits;
		printf("   ->  The current register value for operator one is: %d  <-\n", op1);
        printf("   ->  The current two bit value for operator two is: %d  <-\n", getTwoBits);
	}
    
	if (opcode == 9) 
	{
		op1 = regArray[getReg1];
		op2 = getAiNumber;
        printf("   ->  The current register value for operator one is: %d  <-\n", op1);
        printf("    ->  The current number value for operator two is: %d  <-\n", op2);
	} 

    if (opcode == 10 || opcode == 11)
	{
        op1 = regArray[getReg1];
        op2 = regArray[getReg2];
        printf("   ->  The current register value for operator one is: %d  <-\n", op1);
        printf("   ->  The current register value for operator two is: %d  <-\n", op2);
	}

	if (opcode == 12)
	{
		op1 = getJmpOffset;
		printf("   ->  The current offset value for operator one is: %d  <-\n", op1);
	}

	if (opcode == 10 || opcode == 11 || opcode == 12 || opcode == 13)
	{
		pc += 4; 
	}
	else
	{
		pc += 2;
	}
}

void execute()
{	
    printf("|------------------[ Executing Instruction ]-------------------|\n");
	printf("            ->  The current pc counter value is: %d  <-\n", pc);
	
	switch(opcode)
	{
		case 0:
		{
			haltFlag = 1;	
			break;
		}
		case 1:
		{
			result = op1 + op2;
			break;
		}
		case 2:
		{
			result = op1 & op2;
			break;
		}
		case 3:	
		{
			result = op1 / op2;
            break;
		}
		case 4:		
		{
			result = op1 * op2;
			break;
		}
		case 5:		
		{
			result = op1 - op2;
			break;
		}
		case 6:	
		{
			result = op1 | op2;
			break;
		}
		case 7:
		{
			copyMemory = (memoryArray[r15+3] + (memoryArray[r15+2] << 8) + (memoryArray[r15+1] << 16) + (memoryArray[r15] << 24));
			
			if (getTwoBits == 8)
			{
				result = (memoryArray[r15+3] + (memoryArray[r15+2] << 8) + (memoryArray[r15+1] << 16) + (memoryArray[r15] << 24));
				r15 += 4;
				break;
			} else if (getTwoBits == 4) 
			{
				r15 -= 4;
				break;
			} else if (getTwoBits == 0) 
			{
				result = (memoryArray[r15+3] + (memoryArray[r15+2] << 8) + (memoryArray[r15+1] << 16) + (memoryArray[r15] << 24));
				r15 += 4;
				pc = result;
				break;
			}
		}
        case 8: 
		{
			switch (getIntNumber)
			{
				case 0:
				{
					for (int i=0; i<regSize; i++) 
					{
						printf("			    R[%d] = %d\n", i, regArray[i]);
					}
					break;
				}
				case 1: 
				{
					for (int i=0; i<memorySize; i++) 
					{
						printf("                        Memory[%d] = %d\n", i, memoryArray[i]);
					}
					break;
				}
			}
		}
        case 9:	
		{
			result = op1 + op2;
			break;
		}
        case 10:	
		{
			if (op1 == op2)
			{
				pc += getBrOffset * 2;
            }
            break;
        }
        case 11:	
		{
			if (op1 < op2)
			{
				pc += getBrOffset * 2;
            }
            break;
        }
		case 12:
		{
			pc = op1 * 2;
		}
	}

    if (opcode == 0) 
    {
        printf("               ->  The program has come to a halt <-\n");
    } else if (opcode == 1) 
    {
        printf("    ->  The Add operation (op1 + op2) result value is:  %d  <-\n", result);
    } else if (opcode == 2) 
    {
        printf("    ->  The And operation (op1 & op2) result value is:  %d  <-\n", result);
    } else if (opcode == 3) 
    {
        printf("    ->  The Divide operation (op1 / op2) result value is:  %d  <-\n", result);
    } else if (opcode == 4) 
    {
        printf("    ->  The Multiply operation (op1 * op2) result value is:  %d  <-\n", result);
    } else if (opcode == 5) 
    {
        printf(" ->  The Subtract operation (op1 - op2) result value is:  %d  <-\n", result);
    } else if (opcode == 6) 
    {
    printf("    ->  The Or operation (op1 | op2) result value is:  %d  <-\n", result);
    } else if (opcode == 7 && getTwoBits == 8) 
	{
		printf("  ->  Popped value from Stack into op1 value successfully  <-\n");
	} else if (opcode == 7 && getTwoBits == 4) 
	{
		printf("  ->  Pushed value from op1 into Stack value successfully  <-\n");
	} else if (opcode == 7 && getTwoBits == 0) 
	{
		printf("    ->  ----------------Return-----------------  <-\n");
	} else if (opcode == 8) 
    {
        printf("              ->  The printed results are above <-\n");
    } else if (opcode == 9) 
    {
        printf("    ->  The Addi operation (op1 + op2) result value is:  %d  <-\n", result);
    } else if (opcode == 10) 
    {
        printf("  ->  The BR (op1 = op2) is valid go to offset: %d * 2 = %d <-\n", op1, pc);
    } else if (opcode == 11) 
    {
        printf("  ->  The BR (op1 < op2) is valid go to offset: %d * 2 = %d <-\n", op1, pc);
    } else if (opcode == 12) 
	{
		printf("  ->  The Jump operation is valid go to offset: %d * 2 = %d <-\n", op1, pc);
	}
}

void store() 
{
    printf("<----------------------- Fetch Complete ----------------------->\n\n");
    
	if (opcode > 0 && opcode <= 6) 
	{
		regArray[getReg3] = result;
	} 

	if (opcode == 7 && getTwoBits == 8) 
	{
		regArray[getReg1] = result;
	} else if (opcode == 7 && getTwoBits == 4) 
	{
		memoryArray[r15+3] = (regArray[getReg1] & 0xFF);
		memoryArray[r15+2] = ((regArray[getReg1] & 0xFF) >> 8); 
		memoryArray[r15+1] = ((regArray[getReg1] & 0xFF) >> 16); 
		memoryArray[r15] = (regArray[getReg1] >> 24); 
	}

    if (opcode == 9) 
	{
		regArray[getReg1] = result;
	} 
}

int main (int argc, char *argv[]) 
{
	loadFile (argv[1]);
	while (haltFlag != 1) 
	{
		fetch();
		dispatch();
		execute();
		store();
	}
	return 0;
} 
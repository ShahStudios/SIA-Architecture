#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *ltrim(char *s) {
	while (*s == ' ' || *s == '\t') s++;
	return s;
}

char getRegister(char *text) {
	if (*text == 'r' || *text=='R') text++;
	return atoi(text);
}

char getAddress(char *text) {
	return atoi(text);
}

// 3R
char get3R(char OPCODE, unsigned char *bytes) {
    
        long reg1 = getRegister(strtok(NULL," "));
		long reg2 = getRegister(strtok(NULL," "));
		long reg3 = getRegister(strtok(NULL," "));

        bytes[0] = OPCODE;
		bytes[0] |= reg1;
		bytes[1] = reg2 << 4 | reg3;
		
		return 2;
}

// JMP
char getJMP(char OPCODE, unsigned char *bytes) {
    
		long address = getAddress(strtok(NULL," "));

		bytes[0] = OPCODE;
		bytes[0] |= (0xF000000 & address >> 24);
        bytes[1] = (0x0FF0000 & address) >> 16;
        bytes[2] = (0x000FF00 & address) >> 8;
        bytes[3] = (0x00000FF & address);

		return 4;
}

// BR
char getBR(char OPCODE, unsigned char *bytes) {

        long reg1 = getRegister(strtok(NULL," "));
		long reg2 = getRegister(strtok(NULL," ")); 
		
		long address = getAddress(strtok(NULL," ")); 

		bytes[0] = OPCODE; 
		bytes[0] |= reg1; 

		bytes[1] = reg2 << 4;
		bytes[1] |= (0xF0000 & address) >> 16;

		bytes[2] = (0x0FF00 & address) >> 8;
		bytes[3] = (0x000FF & address); 

		return 4;
}

// LS
char getLS(char OPCODE, unsigned char *bytes) {
    
		long reg1 = getRegister(strtok(NULL," "));
		long reg2 = getRegister(strtok(NULL," "));

		long address = getAddress(strtok(NULL," "));
		
        bytes[0] = OPCODE;
		bytes[0] |= reg1;

		bytes[1] = reg2 << 4;
		bytes[1] |= address;

		return 2;
}

// INT
char getINT(char OPCODE, unsigned char *bytes) {
    
		long address = getAddress(strtok(NULL," "));
		
		bytes[0] = OPCODE;
		bytes[0] |= (0xF00 & address) >> 8;
		bytes[1] = (0x0FF & address);

		return 2;
}

// HALT
char getHALT(char OPCODE, unsigned char *bytes) {
    
		bytes[0] = OPCODE;
		bytes[1] = 0;
		
        return 2;
}

// STACK
char getSTACK(char OPCODE, char OPCODE1, unsigned char *bytes) {
    
		long reg = getRegister(strtok(NULL," "));
		
		bytes[0] = OPCODE;
		bytes[0] |= reg;
		bytes[1] = OPCODE1;

		return 2;
}

// AI
char getAI(char OPCODE, unsigned char *bytes) {
    
		long reg = getRegister(strtok(NULL," ")); 		
		long address = getAddress(strtok(NULL," ")); 

		bytes[0] = OPCODE; 
		bytes[0] |= reg; 

		bytes[1] = (0xFF & address);

		return 2;
}

int assembleLine(char *text, unsigned char* bytes) {
	text = ltrim(text);
	char *keyWord = strtok(text," ");

    if (strcmp("add", keyWord) == 0) {
        return get3R(0x10, bytes);
    } else if (strcmp("and", keyWord) == 0) {
        return get3R(0x20, bytes);
    } else if (strcmp("divide", keyWord) == 0) {
        return get3R(0x30, bytes);
    } else if (strcmp("multiply", keyWord) == 0) {
        return get3R(0x40, bytes);
    } else if (strcmp("subtract", keyWord) == 0) {
        return get3R(0x50, bytes);
    } else if (strcmp("or", keyWord) == 0) {
        return get3R(0x60, bytes);
    } else if (strcmp("addimmediate", keyWord) == 0) {
		return getAI(0x90, bytes);
    } else if (strcmp("store", keyWord) == 0) {
        return getLS(0xF0, bytes);
    } else if (strcmp("load", keyWord) == 0) {
        return getLS(0xE0, bytes);
    } else if (strcmp("pop", keyWord) == 0) {
        return getSTACK(0x70, 0x80, bytes);
    } else if (strcmp("push", keyWord) == 0) {
        return getSTACK(0x70, 0x40, bytes);
    } else if (strcmp("return", keyWord) == 0) {
        return getSTACK(0x70, 0x00, bytes);
    } else if (strcmp("call", keyWord) == 0) {
        return getJMP(0xD0, bytes);
    } else if (strcmp("jump", keyWord) == 0) {
        return getJMP(0xC0, bytes);
    } else if (strcmp("branchifequal", keyWord) == 0) {
        return getBR(0xA0, bytes);
    } else if (strcmp("branchifless", keyWord) == 0) {
        return getBR(0xB0, bytes);
    } else if (strcmp("interrupt", keyWord) == 0) {
        return getINT(0x80, bytes);
    } else if (strcmp("halt", keyWord) == 0) {
        return getHALT(0x00, bytes);
    } 
}

int main(int argc, char **argv) {
	FILE *src = fopen(argv[1],"r");
	FILE *dst = fopen(argv[2],"w");
	while (!feof(src)) {
		unsigned char bytes[4];
		char line[1000];
		if (NULL != fgets(line, 1000, src)) {
			printf ("read: %s\n",line);
			int byteCount = assembleLine(line,bytes);
			fwrite(bytes,byteCount,1,dst);
		}
	}
	fclose(src);
	fclose(dst);
	return 0;
}
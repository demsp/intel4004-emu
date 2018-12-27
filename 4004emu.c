// https://ok.ru/terralinux/topic/66357700466000
// https://www.openlearning.com/u/john.badger/4004Emulator
//  gcc -Wall -O2 4004emu.c -o 4004emu

    #include <stdlib.h>
    #include <stdio.h>
    #define PROCESSOR_SIZE 16
    #define FALSE 0
    #define TRUE  1
    #define HALTING_THRESHOLD 256
     
    typedef struct _mp {
    	unsigned char cell[PROCESSOR_SIZE]; //main memory
    	unsigned char ip; //instruction pointer register (system)
    	unsigned char is; //instruction store register (system)
    	unsigned char sw; //swap register register (system)
    	unsigned char r0; //register 0 for user
    	unsigned char r1; //register 1 for user
    } mp;
    void printState(mp processor, int extraData);
     
    int main (int argc, char *argv[]) {
    while(1) {
    	mp FOOF = {{0}, 0, 0, 0, 0, 0}; //FOOF stands for four oh oh four - 4004. 0 by default because this is the convention of the 4004 emulator given in COMP1917
        //manual input
    	char input[PROCESSOR_SIZE*2] = {0}; //by default
    	printf("Input your program here: (input must be in PAIRS of characters, so 7 is 07, 0 is 00, 12 is 12, 3 is 03 etc)\n");
    	scanf("%32s", input);
     
        int counter = 0;
    	while (counter < PROCESSOR_SIZE) {
    		if (input[counter*2] != 0 && input[counter*2 + 1] != 0) {
                FOOF.cell[counter] = (input[counter*2] - 48)*10 + (input[counter*2 + 1] - 48);
    		} else {
                FOOF.cell[counter] = 0;
    		}
    		counter++;
    	}
     
    	printf("Data converted to:\n");
        printState(FOOF, FALSE);
        printf("\n");
     
    	//check if legit input then map input to FOOF.cell[]
    	//remember subtract the ascii values (-32?) for real numbers
    	int halted = FALSE;
    	counter = 0;
    	while (halted == FALSE) {
    		FOOF.is = FOOF.cell[FOOF.ip];
            //printState(FOOF);
    		FOOF.ip++;
    		switch (FOOF.is) {
    			//one byte instruction set
    			case 0:
    				halted = TRUE;
    				printf("\nHalted.\n");
    				break;
    			case 1:
    				if (FOOF.r0 == 15) {
                        FOOF.r0 = 0;
    				} else {
    				    FOOF.r0++;
                    }
    				break;
    			case 2:
    			    if (FOOF.r0 != 0) {
                        FOOF.r0--;
    			    } else {
                        FOOF.r0 = 15;
    			    }
    				break;
    			case 3:
    				FOOF.r1++;
    				if (FOOF.r1 > 15) {
                        FOOF.r1 = (FOOF.r1 % PROCESSOR_SIZE);
    				}
    				break;
    			case 4:
    				if (FOOF.r1 != 0) {
                        FOOF.r1--;
    			    } else {
                        FOOF.r1 = 15;
    			    }
    				break;
    			case 5:
    				FOOF.r0 += FOOF.r1;
    				if (FOOF.r0 > 15) {
                        FOOF.r0 = (FOOF.r0 % PROCESSOR_SIZE);
    				}
    				break;
    			case 6:
    				FOOF.r0 += 16; //take care that r1 isn't > r0
    				FOOF.r0 -= FOOF.r1;
    				if (FOOF.r0 > 15) {
                        FOOF.r0 = (FOOF.r0 % PROCESSOR_SIZE);
    				}
    				break;
    			case 7:
    				printf("%d ", FOOF.r0);
    				break;
    			//two byte instruction set
    			case 8:
    				if (FOOF.r0 != 0) {
    					FOOF.ip = FOOF.cell[FOOF.ip];
    				} else {
                        FOOF.ip++; //move on
    				}
    				break;
    			case 9:
    				if (FOOF.r0 == 0) {
    					FOOF.ip = FOOF.cell[FOOF.ip];
    				} else {
                        FOOF.ip++;
    				}
    				break;
    			case 10:
    				FOOF.r0 = FOOF.cell[FOOF.ip];
    				FOOF.ip++;
    				break;
    			case 11:
    				FOOF.r1 = FOOF.cell[FOOF.ip];
    				FOOF.ip++;
    				break;
    			case 12:
    				FOOF.cell[FOOF.cell[FOOF.ip]] = FOOF.r0;
    				FOOF.ip++;
    				break;
    			case 13:
    				FOOF.cell[FOOF.cell[FOOF.ip]] = FOOF.r1;
    				FOOF.ip++;
    				break;
    			case 14: {
    				unsigned char tempR0 = FOOF.r0;
    				FOOF.r0 = FOOF.cell[FOOF.cell[FOOF.ip]];
    				FOOF.cell[FOOF.cell[FOOF.ip]] = tempR0;
    				FOOF.ip++;
    				break;
    			}
    			case 15: {
    				unsigned char tempR1 = FOOF.r1;
    				FOOF.r1 = FOOF.cell[FOOF.cell[FOOF.ip]];
    				FOOF.cell[FOOF.cell[FOOF.ip]] = tempR1;
    				FOOF.ip++;
    				break;
    			}
    		}
    		//repeat until halted naturally, or force terminate after halting threshold
    		counter++;
    		if (counter > HALTING_THRESHOLD) {
                halted = TRUE;
                printf("Forced termination.\n");
    		}
    		//printState(FOOF, TRUE);
    	}
    }
     
    	return EXIT_SUCCESS;
    }
     
    void printState(mp processor, int extraData) {
    	int counter = 0;
    	while (counter < PROCESSOR_SIZE) {
    		printf("%d ", processor.cell[counter]);
    		counter++;
    	}
    	if (extraData) {
            printf("\nIS: %d IP: %d SW: %d R0: %d R1: %d\n", processor.ip, processor.is, processor.sw, processor.r0, processor.r1);
    	}
    }

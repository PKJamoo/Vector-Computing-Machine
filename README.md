# Vector-Computing-Machine
Simple emulator for faux computer architecture with support 
for assembly vector drawing primitives.

install by cloning the github repo then calling make in terminal.
Running with ./VCM will input you directly into the shell.

CURRENT SHELL COMMANDS TO USE:
open [FILE_NAME] (runs binary files)
asm [FILE_NAME] (runs the assembler on a .PASM file, writes out the binary code)
quit (shuts down the VCM)

Specifications for Assembly Instruction Set

	HALT=0,	// op 0, end operation, 1 byte length OP-FN 0x00
	NOP,	// op 1, no operation, 1 byte length OP-FN. 0x10
	MOV,	// op 2, move values register to register, fn codes CONDFNC, 2 byte length OP-FN rA-rB 0x2fnAB
	LOAD,	// op 3, load immediate value or value from memory to register, 
			// fn codes MEMFNC 2 byte to 4 byte OP-FN rA-rB 0x3[01][rr] or 0x32[rr][valC]
	STORE,	// op 4, store value in a register to memory, same structure as LOAD
	BINOP,	// op 5, binary operations, fn codes BINFNC, 2 byte length OP-FN rA-rB
	JMP,	// op 6, jump operations, fn codes JMPFNC, 3 byte length OP-FN HIGH LOW
	CALL,	// op 7, call function commands, 3 byte length OP-FN DEST
	RET,	// op 8, return from function command, 1 byte length OP-FN.
	PUSH,	// op 9, push value in register onto stack increment RSP 2 byte OP-FN rA-rB
	POP,	// op A, pop top value of stack decrement RSP, 2 byte OP-FN rA-rB
	DRAW,	// op B, vector drawing primitives, fn codes DRAWFNC 2 byte OP-FN rA-rB
	PRINT	// op C, prints every register to the screen.

	
	RA=0,	//  ***
	RB,		//	RA - RD 
	RC,		//	general purpose registers
	RD,		// 	***
	RBP,	// 4 - register for array addresses
	RBI,	// 5 - register for array indexing
	RRET,	// 6 - register to store return values
	RSP,	// 7 - register for stack pointer
	RSI,	// 8 - register for stack indexing
	REG9,	// ***
	REG10,	//
	REG11,	// TBD
	REG12,	//
	REG13,	//
	REG14,	//
	REG15,	//	***
	REG16 // F - dummy register for unused registers in operations

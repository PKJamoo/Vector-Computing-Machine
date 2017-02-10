#ifndef HARDWARE_H_
#define HARDWARE_H_

/* Programming Architecture Constants and Structs */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
/* Constants for the CPU */

#define READ_SIZE 2		// in bytes
#define NUM_REGS 16	// number of registers for the system
#define NUM_FLAGS 3	// number of (condition codes) flags for the system
#define MEM_START 0x0F
#define NUM_OPS 16


// Typedefs
typedef struct struct_cpu cpu;
typedef struct struct_gpu gpu;

enum OPCODES 
{
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
};


// COND for jump and conditional move commands
enum CONDFN
{
	UNCOND,				// fn 0
	LESSTHAN,			// fn 1
	LESSTHANEQUALS,		// fn 2
	EQUALS,				// fn 3
	NOTEQUALS,			// fn 4
	GREATERTHANEQUALS,	// fn 5
	GREATERTHAN 		// fn 6
};
// MEM for load and store commands
enum MEMFN
{
	IMM=0,	// fn 0, immediate value load/store rB = register to load to, or address to store to
	MEM,	// fn 1 load/store from memory address
	IND		// fn 2, load/store from/to valC = memory address, ind = offset index (multiplied by 2 bytes)
};
// BIN for binary function commands
enum BINFN
{
	ADD=0,	// fn 0
	SUB,	// fn 1
	MULT,	// fn 2
	DIV,	// fn 3
	MOD,	// fn 4
	AND,	// fn 5
	XOR		// fn 6

};
// DRAW for drawing function commands
enum DRAWFN
{
	LINE=0,	// fn 0
	RECT,	// fn 1
	CIRCLE	// fn 2
};

// 15 registers plus dummy F register, rename for function
enum REGS
{
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
};


enum FLAGS
{
	ZEROFLAG,
	SIGNFLAG,
	INTERRUPTFLAG
};

/* Structs for the CPU */


struct struct_cpu {
	int running;

	uint16_t ip;
	int16_t regs[NUM_REGS];
	int16_t flags[NUM_FLAGS];

	int16_t return_address;
};

/* Function Prototypes for the CPU */

// CPU helpers
void reset_cpu(cpu* cpu);
void fill_op_table(cpu* cpu);

// CPU operations
void fetch( cpu* cpu );
void halt( cpu* cpu );
void move( cpu* cpu, unsigned char op_code, unsigned char regA, unsigned char regB);
void load(  cpu* cpu, unsigned char op_code, int regA, int regB, int16_t valC);
void store( cpu* cpu, unsigned char op_code, int regA, int regB, int16_t valC);
void binop( cpu* cpu, unsigned char op_code, unsigned char regA, unsigned char regB );
void jump( cpu* cpu, unsigned char op_code, int16_t destination );
void call( cpu* cpu, int16_t destination );
void ret( cpu* cpu );
void push( cpu* cpu, int from_reg) ;
void pop ( cpu* cpu, int to_reg  );
void draw(cpu* cpu, gpu* gpu);

/* Constants for the Memory and Mem Management */
# define MEM_SIZE 65536

unsigned char mainmem[MEM_SIZE];


/* Structs for Memory */


/* Function Prototypes for the Memory Manager  */


/* Constants for the GPU */

/* Structs for the GPU */
struct struct_gpu {

	int16_t draw_table[3];
	uint16_t video_mode;

};


/* Function Prototypes for the GPU */
void init_gpu(gpu* gpu);
void draw_line();
void draw_rect();
void draw_circle();

/* Global Variables */
cpu* processor;
gpu* graphics;


#endif // HARDWARE_H_
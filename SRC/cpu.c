#include <hardware.h>

/*  CPU   */


// global variables for CPU operations
unsigned char instruction_byte;
unsigned char register_byte;
unsigned char op_byte;
unsigned char func_byte;
int valC;
int from_reg;
int to_reg;

/*
set given cpu's registers, condition flags and instruction pointer back to default values
*/
void reset_cpu ( cpu* cpu ) 
{
	cpu->running = 0;

	cpu->ip = 0;
	int i;
	for (i = 0; i < NUM_REGS; i ++)
		cpu->regs[i] = 0;
	for (i = 0; i < NUM_FLAGS; i ++)
		cpu->flags[i] = 0;

}

void fetch( cpu* cpu )
{
	unsigned char instruction_byte = mainmem[cpu->ip];
	unsigned char register_byte;
	unsigned char op_byte = instruction_byte >> 4;
	unsigned char func_byte = instruction_byte & 0x0F;
	printf("instruction: %x\n", op_byte);
	printf("function: %x\n", func_byte);


	switch(op_byte)
	{
		case HALT:
			halt(cpu);
			break;
		case NOP:
			//printf("NOP\n");
			cpu->ip++;
			break;
		case MOV:
			register_byte = mainmem[cpu->ip + 1];
			from_reg = register_byte >> 4;
			to_reg = register_byte & 0x0F;
			move(cpu, func_byte, from_reg, to_reg);
			break;
		case LOAD:
			register_byte = mainmem[cpu->ip + 1];
			from_reg = register_byte >> 4;
			to_reg = register_byte & 0x0F;
			valC = mainmem[cpu->ip + 2] << 8 | mainmem[cpu->ip + 3];
			load(cpu, func_byte, from_reg, to_reg, valC);
			break;
		case STORE:
			register_byte = mainmem[cpu->ip + 1];
			from_reg = register_byte >> 4;
			to_reg = register_byte & 0x0F;
			store(cpu, func_byte, from_reg, to_reg, valC);
			break;
		case BINOP:
			register_byte = mainmem[cpu->ip + 1];
			from_reg = register_byte >> 4;
			to_reg = register_byte & 0x0F;
			binop(cpu, func_byte, from_reg, to_reg);
			break;
		case JMP:
			valC = mainmem[cpu->ip + 1] << 8 || mainmem[cpu->ip + 2];
			jump(cpu, func_byte, valC);
			break;
		case CALL:
			valC = mainmem[cpu->ip + 1] << 8 || mainmem[cpu->ip + 2];
			call(cpu, valC);
			break;
		case RET:
			ret(cpu);
			break;
		case PUSH:
			register_byte = mainmem[cpu->ip + 1];
			from_reg = register_byte >> 4;
			to_reg = register_byte & 0x0F;
			push(cpu, from_reg);
			break;
		case POP:
			register_byte = mainmem[cpu->ip + 1];
			from_reg = register_byte >> 4;
			to_reg = register_byte & 0x0F;
			pop(cpu, to_reg);
			break;
		case DRAW:
			// to be filled in later
		default:
			printf("ERROR: illegal operation\n");
			halt(cpu);
			break;
	}
}

void halt ( cpu* cpu )
{
	cpu->running = FALSE;
}
void move( cpu* cpu, unsigned char op_code, unsigned char regA, unsigned char regB)
{
	switch (op_code)
	{
		case UNCOND:
			cpu->regs[regB] = cpu->regs[regA];
			break;
		case LESSTHAN:
			if (cpu->flags[SIGNFLAG] < 0 && cpu->flags[ZEROFLAG] != 0)
				cpu->regs[regB] = cpu->regs[regA];
			break;
		case LESSTHANEQUALS:
			if (cpu->flags[SIGNFLAG] < 0 || cpu->flags[ZEROFLAG] == 0)
				cpu->regs[regB] = cpu->regs[regA];
			break;
		case EQUALS:
			if (cpu->flags[ZEROFLAG] == 0)
				cpu->regs[regB] = cpu->regs[regA];
			break;
		case NOTEQUALS:
			if (cpu->flags[ZEROFLAG] != 0)
				cpu->regs[regB] = cpu->regs[regA];
			break;
		case GREATERTHANEQUALS:
			if (cpu->flags[SIGNFLAG] > 0 || cpu->flags[ZEROFLAG] == 0 )
				cpu->regs[regB] = cpu->regs[regA];
			break;
		case GREATERTHAN:
			if (cpu->flags[SIGNFLAG] > 0 && cpu->flags[ZEROFLAG] != 0)
				cpu->regs[regB] = cpu->regs[regA];
			break;
		default:
			printf("ERROR: ILLEGAL MOVE COMMAND\n");
			break;
	}

	cpu->ip = cpu->ip + 2;


}
void load( cpu* cpu,  unsigned char op_code, int regA, int regB, int16_t valC)
{

	switch(op_code)
	{
		case IMM:
			cpu->regs[regB] = valC;
			cpu->ip = cpu->ip + 4;
			break;
		case MEM:
			cpu->regs[regB] = (mainmem[valC] << 8) | mainmem[valC + 1];
			cpu->ip = cpu->ip + 4;
			break;
		case IND:
			cpu->regs[regB] = (mainmem[valC + (2 * cpu->regs[regA]) ] << 8) | mainmem[valC + (2 * cpu->regs[regA]) + 1];
			cpu->ip = cpu->ip + 4;
			break;
		default:
			printf("ERROR: ILLEGAL LOAD COMMAND\n");
			break;
	}

	printf("valC: %x\n", valC);
}
void store( cpu* cpu, unsigned char op_code, int regA, int regB, int16_t valC)
{

	switch(op_code)
	{
		case MEM:
			mainmem[valC] = cpu->regs[regB] >> 8;
			mainmem[valC + 1] = cpu->regs[regB] & 0x00FF;
			cpu->ip = cpu->ip + 4;
			break;
		case IND:
			mainmem[valC + (2 * cpu->regs[regA])] = cpu->regs[regB] >> 8;
			mainmem[valC + (2 * cpu->regs[regA] + 1)] = cpu->regs[regB] & 0x00FF;
			cpu->ip = cpu->ip + 4;
			break;
		default:
			printf("ERROR: ILLEGAL STORE COMMAND\n");
			break;

	}

}
void binop( cpu* cpu, unsigned char op_code, unsigned char regA, unsigned char regB)
{
	switch (op_code)
	{
		case ADD:
			cpu->regs[regB] = cpu->regs[regB] + cpu->regs[regA];
			break;
		case SUB:
			cpu->regs[regB] = cpu->regs[regB] - cpu->regs[regA];
			break;
		case MULT:
			cpu->regs[regB] = cpu->regs[regB] * cpu->regs[regA];
			break;
		case DIV:
			if (cpu->regs[regA] == 0 ){
				printf("ERROR: DIVIDE BY ZERO\n");
				halt(cpu);
			}
			cpu->regs[regB] = cpu->regs[regB] / cpu->regs[regA];
			break;
		case MOD:
			cpu->regs[regB] = cpu->regs[regB] % cpu->regs[regA];
			break;
		case AND:
			cpu->regs[regB] = cpu->regs[regB] & cpu->regs[regA];
			break;
		case XOR:
			cpu->regs[regB] = cpu->regs[regB] ^ cpu->regs[regA];
			break;
		default:
			printf("ERROR: ILLEGAL BINARY OPERATION \n");
			break;

	}

			if (cpu->regs[regB] == 0)
				cpu->flags[ZEROFLAG] = 1;
			if (cpu->regs[regB] < 0)
				cpu->flags[SIGNFLAG] = 1;

			printf("OPERANDS %x = %x %x\n", cpu->regs[regB], cpu->regs[regB], cpu->regs[regA]);
			cpu->ip = cpu->ip + 2;


}
void jump( cpu* cpu, unsigned char op_code, int16_t valC)
{
		switch (op_code)
	{
		case UNCOND:
			cpu->ip = valC;
			//printf("valC: %x\n", valC);
			break;
		case LESSTHAN:
			if (cpu->flags[SIGNFLAG] < 0 && cpu->flags[ZEROFLAG] != 0)
				cpu->ip = valC;
			break;
		case LESSTHANEQUALS:
			if (cpu->flags[SIGNFLAG] < 0 || cpu->flags[ZEROFLAG] == 0)
				cpu->ip = valC;
			break;
		case EQUALS:
			if (cpu->flags[ZEROFLAG] == 0)
				cpu->ip = valC;
			break;
		case NOTEQUALS:
			if (cpu->flags[ZEROFLAG] != 0)
				cpu->ip = valC;
			break;
		case GREATERTHANEQUALS:
			if (cpu->flags[SIGNFLAG] > 0 || cpu->flags[ZEROFLAG] == 0 )
				cpu->ip = valC;
			break;
		case GREATERTHAN:
			if (cpu->flags[SIGNFLAG] > 0 && cpu->flags[ZEROFLAG] != 0)
				cpu->ip = valC;
			break;
		default:
			printf("ERROR: ILLEGAL JUMP COMMAND\n");
			break;

	}


}
void call( cpu* cpu, int16_t valC)
{
	// maybe push all register values

	cpu->return_address = ++cpu->ip;
	cpu->ip = valC;

}
void ret( cpu* cpu )
{
	// maybe pop all register values
	
	cpu->ip = cpu->return_address;


}
void push(cpu* cpu, int from_reg)
{
	// value of RSP always on first occupied spot of stack
	cpu->regs[RSP] = cpu->regs[RSP] - 2;
	unsigned char lo_byte = cpu->regs[from_reg] >> 8;
	unsigned char hi_byte = cpu->regs[from_reg] & 0X0F; 
	mainmem[cpu->regs[RSP]] = hi_byte;
	mainmem[cpu->regs[RSP] + 1] = lo_byte;

	


}
void pop (cpu* cpu, int to_reg)
{	
	unsigned char lo_byte = mainmem[cpu->regs[RSP]];
	unsigned char hi_byte = mainmem[cpu->regs[RSP] + 1];
	cpu->regs[to_reg] = lo_byte | hi_byte;
	cpu->regs[RSP] = cpu->regs[RSP] + 2;


}


void draw (cpu* cpu, gpu* gpu)
{


	
}
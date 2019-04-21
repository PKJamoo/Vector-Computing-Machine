#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

/* Assembler Architecture Constants and Structs */

#define ASSEMBLER_BUFF_SIZE 512
#define ASSEMBLER_PARAMS_SIZE 20


typedef struct struct_label	label;
typedef struct struct_instr instr;
typedef struct struct_ast ast;
typedef struct struct_jump jmp_instr;

struct struct_label {

	char* label;
	int address;
	label * next;
};

struct struct_instr {

	char opcode[5];
	char fncode[5];
	char arg0[16];
	char arg1[16];
	uint16_t address;
	instr * next;

};

struct struct_jmp {
	char opcode[5];
	char fncode[3];
	char*	label;
	instr * next_instr;

};

struct struct_ast {
	label * labels;
	instr * instrs;
};



// Assembler Helpers

FILE* assembler_open_file(char* file_name);

label* find_labels(FILE* file);
void replace_labels(ast* ast);

char* 	assembler_read_line(FILE* file, int* end);
char**	assembler_split_line(char* line);



// Functions for the Assembler
void assembler_parse(FILE* file, ast* ast);
void assembler_optimize(ast* ast);
void assembler_create_bin(ast* ast);
void assembler(char* file_name);




#endif // ASSEMBLER_H_
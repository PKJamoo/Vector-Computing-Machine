#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

/* Assembler Architecture Constants and Structs */


typedef struct struct_label	label;
typedef struct struct_instr instr;
typedef struct struct_ast ast;

struct struct_label {

	char* label;
	int address;
	void* next;
};

struct struct_instr {

	int opcode;
	int fncode;
	int arg0;
	int arg1;
	void* next_instr;

};

struct struct_ast {
	label* labels;
	instr* instrs;
};



// Assembler Helpers

FILE* assembler_open_file(char* file_name);

label* find_labels(FILE* file);
void replace_labels(instr* instrs, label* labels);



// Functions for the Assembler
void assembler_parse(FILE* file, ast* ast);
void assembler_optimize(ast* ast);
void assembler(char* file_name);




#endif // ASSEMBLER_H_
#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

/* Assembler Architecture Constants and Structs */


typedef struct struct_label	label;
typedef struct struct_instr instr;

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



// Assembler Helpers

FILE* assembler_open_file(char* file_name);

label* find_labels(FILE* file);
void replace_labels(instr* instrs, label* labels);



// Functions for the Assembler
void assembler_parse();
void assembler_optimize();




#endif // ASSEMBLER_H_
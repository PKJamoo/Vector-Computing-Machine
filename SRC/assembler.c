#include <hardware.h>
#include <assembler.h>



FILE* assembler_open_file(char* file_name)
{

	FILE* file;
	// create String filepath
	char* file_path = "TESTASM/";

	
	char* full_path = malloc(strlen(file_path) + strlen(file_name) + 1);
	strcpy(full_path, file_path);
	strcat(full_path, file_name);
	// open file
	file = fopen(full_path, "r");
	return file;


}

// read a single line from the file and process the results
char* assembler_read_line(FILE* file, int* end) 
{
	//printf("entered readline\n");
	int buffer_size = ASSEMBLER_BUFF_SIZE;
	char* buffer = malloc(sizeof(char) * ASSEMBLER_BUFF_SIZE);
	int pos = 0;
	char new_char;

		if(!buffer){
		perror("asm: memory allocation error.\n");
	}

	while(1){
		// read the next character
		new_char = getc(file);

		if (new_char == EOF || new_char == '\n' || new_char == '\r') {
			if (new_char == EOF) {
				*end = 1;
			}
			buffer[pos] = '\0';
			// test print statement
			printf("asm code: %s\n", buffer);
			return buffer;
		}
		else {
			buffer[pos] = new_char;
		}
		pos++;

		// re-allocate buffer
		if (pos >= buffer_size) {
	      buffer_size += ASSEMBLER_BUFF_SIZE;
	      buffer = realloc(buffer, buffer_size);
	      if (!buffer) {
			perror("asm: memory allocation error.\n");
	      	}
	  	}
	}
}

// split a single line of code from the file into its parts
char** assembler_split_line(char* line) 
{
	//printf("entered splitline\n");
	printf("line: %s\n", line);
	int pos = 0;
	int params_size = ASSEMBLER_PARAMS_SIZE;
	char* token;
	char** args = malloc(params_size * sizeof(char*));
	// find first command
	token = strtok(line, " ");

	while (token != NULL){

		printf("token: %s\n", token);
		args[pos] = token;
		pos++;

		// re-allocate buffer
		if (pos >= params_size) {
	      params_size += ASSEMBLER_PARAMS_SIZE;
	      args = realloc(args, params_size);
	      //printf("am I reallocating?\n");
	      if (!args) {
			perror("sh: memory allocation error.\n");
	      	}
	  	}
		token = strtok(NULL, " ");

	}
		args[pos] = NULL;


		// test prints
		/*
		printf("asm args:");
		for (int i = 0; i < pos; i++){
		printf(" %s", args[i]);
		}
		printf("\n");
		*/
		return args;
}

// parse a single line of code into an instr for the ast
void assembler_parse_instr(char** args, int argc, instr* instr)
{
	// big if/else tree based on type of instruction
	if (strcmp(args[0], "HALT") == 0){
		strcpy(instr->opcode, "HALT");

	}
	else if (strcmp(args[0], "NOP") == 0){
		strcpy(instr->opcode, "NOP");
	}

	else if (strcmp(args[0], "MOV") == 0){
		strcpy(instr->opcode, "MOV");
		strcpy(instr->arg0, args[1]);
		strcpy(instr->arg1, args[2]);
	}
	else if (strcmp(args[0], "LOAD") == 0){
		strcpy(instr->opcode, "LOAD");
		strcpy(instr->fncode, "");
		strcpy(instr->arg0, args[1]);
		strcpy(instr->arg1, args[2]);
	}
	else if (strcmp(args[0], "STORE") == 0){
		strcpy(instr->opcode, "STORE");
	}

	else if (strcmp(args[0], "ADD") == 0){
		strcpy(instr->opcode, "BIN");
	}
	else if (strcmp(args[0], "SUB") == 0){
		strcpy(instr->opcode, "BIN");
	}
	else if (strcmp(args[0], "MULT") == 0){
		strcpy(instr->opcode, "BIN");
	}

	else if (strcmp(args[0], "DIV") == 0){
		strcpy(instr->opcode, "BIN");
	}
	else if (strcmp(args[0], "MOD") == 0){
		strcpy(instr->opcode, "BIN");
	}
	else if (strcmp(args[0], "AND") == 0){
		strcpy(instr->opcode, "BIN");
	}

	else if (strcmp(args[0], "XOR") == 0){
		strcpy(instr->opcode, "XOR");
	}
	else if (strcmp(args[0], "JMP") == 0){
		strcpy(instr->opcode, "JMP");
	}
	else if (strcmp(args[0], "JGE") == 0){

	}
	else if (strcmp(args[0], "JGT") == 0){
		strcpy(instr->opcode, "JMP");
	}
	else if (strcmp(args[0], "JEQ") == 0){
		strcpy(instr->opcode, "JMP");
	}
	else if (strcmp(args[0], "JNE") == 0){
		strcpy(instr->opcode, "JMP");
	}
	else if (strcmp(args[0], "JLT") == 0){
		strcpy(instr->opcode, "JMP");
	}
	else if (strcmp(args[0], "JLE") == 0){
		strcpy(instr->opcode, "JMP");
	}
	else if (strcmp(args[0], "CALL") == 0){
		strcpy(instr->opcode, "CALL");
	}
	else if (strcmp(args[0], "RET") == 0){
		strcpy(instr->opcode, "RET");
	}
	else if (strcmp(args[0], "PUSH") == 0){
		strcpy(instr->opcode, "PUSH");
	}
	else if (strcmp(args[0], "POP") == 0){
		strcpy(instr->opcode, "POP");
	}
	else if (strcmp(args[0], "DRAWR") == 0){
		strcpy(instr->opcode, "DRAW");
	}
	else if (strcmp(args[0], "DRAWC") == 0){
		strcpy(instr->opcode, "DRAW");
	}
	else if (strcmp(args[0], "DRAWL") == 0){
		strcpy(instr->opcode, "DRAW");
	}
	else if (strcmp(args[0], "PRINT") == 0){
		strcpy(instr->opcode, "PRINT");
	}
	else {
		printf("Illegal Command Error: %s is not a valid operation", args[0]);
	}



}


// helper function to be used in the parsing stage
//TBD
label* find_labels(FILE* file)
{
	return NULL;
}

// helper function to be used in the optimization stage
// TBD
void replace_labels(ast* ast)
{


}


//--------------------

// parse assembler code into AST
void assembler_parse(FILE* file, ast* ast)
{
	// get pointer to first instr in ast
	//printf("getting instrs\n");
	instr* current_instr = ast->instrs;
	//printf("got instrs\n");


	int end;
	end = 0;
	// check to see if file ended
	while (!end){
		char** args = assembler_split_line(	 // find separate pieces of assembler instr
			assembler_read_line(file, &end)); // read a single line, determine if file is ended
			if (end) break;					// check if we're on the last line and leave the loop


		//printf("read line, split line\n");
		int arg_count = 0;
		while (args[arg_count]){
			//printf("args %s\n", args[arg_count]);
			arg_count++;
		}
		printf("parsing instr\n");
		assembler_parse_instr(args, arg_count, current_instr); // parse the arguments into an ast instr_node
		if (!end){
			printf("hello: %s\n", current_instr->opcode);
			ast->instrs->next = malloc(sizeof(instr));
			current_instr = ast->instrs->next;
		}
	}

	// find all labels in file
	ast->labels = find_labels(file);


	
}

// perform small optimizations on Assembler AST
void assembler_optimize(ast* ast)
{


}


void assembler_create_bin(ast* ast)
{

}


// entry point for users to access the assembler
void assembler(char* file_name)
{
	// open .pasm file for parsing
	FILE* file = assembler_open_file(file_name);
	printf("opened file\n");

	// allocate memory for instruction ast
	ast* ast = malloc(sizeof(ast));
	if (!ast) {
		perror("asm: memory allocation error.\n");
	}
	ast->instrs = malloc(sizeof(instr));
	if (!ast->instrs) {
		perror("asm: memory allocation error.\n");
	}
	ast->labels = malloc(sizeof(label));
	if (!ast->instrs) {
		perror("asm: memory allocation error.\n");
	}

	// call parse function to create ast
	assembler_parse(file, ast);
	printf("parsed\n");


	// optimize code
	assembler_optimize(ast);


	// create binary file
	assembler_create_bin(ast);

	// close file after use
	fclose(file);

	// free AST after use


}







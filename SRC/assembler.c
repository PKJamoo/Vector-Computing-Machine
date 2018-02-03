#include <hardware.h>
#include <assembler.h>
#include <stdio.h>


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
	int pos = 0;
	int params_size = ASSEMBLER_PARAMS_SIZE;
	char* token;
	char** args = malloc(params_size * sizeof(char*));
	// find first command
	token = strtok(line, " ");

	while (token != NULL){

		args[pos] = token;
		pos++;

		// re-allocate buffer
		if (pos >= params_size) {
	      params_size += ASSEMBLER_PARAMS_SIZE;
	      args = realloc(args, params_size);
	      if (!args) {
			perror("sh: memory allocation error.\n");
	      	}
	  	}

		token = strtok(NULL, " ");

	}
		args[pos] = NULL;

		free(line);

		return args;
}

// parse a single line of code into an instr for the ast
void	assembler_parse_instr(char** args, int argc, void* instr)
{
	// big switch statements based on type of instruction

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
	instr* instr = ast->instrs;


	int end;
	end = 0;
	// check to see if file ended
	while (~(end)){

		char** args = assembler_split_line(	 // find separate pieces of assembler instr
			assembler_read_line(file, &end)); // read a soingle line, determine if file is ended

		int arg_count = 0;
		while (args[arg_count]){
			arg_count++;
		}

		assembler_parse_instr(args, arg_count, instr); // parse the arguments into an ast instr_node
		instr = ast->instrs->next;
	}

	// find all labels in file
	ast->labels = find_labels(file);


	
}

// perform small optimizations on Assembler AST
void assembler_optimize(ast* ast)
{


}




// entry point for users to access the assembler
void assembler(char* file_name)
{
	FILE* file = assembler_open_file(file_name);

	ast* ast = malloc(sizeof(ast));

	// call parse function to create ast
	assembler_parse(file, ast);


	// optimize code
	assembler_optimize(ast);


	// close file after use
	fclose(file);

	// free AST after use


}







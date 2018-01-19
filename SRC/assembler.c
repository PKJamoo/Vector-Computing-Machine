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


// parse assembler code into AST
void assembler_parse(FILE* file, ast* ast)
{
	// if file is empty
	fseek(file, 0, SEEK_END);
	if (ftell(file) == 0)
	{
		printf("FILE EMPTY\n");
		return;
	}

	


	
}

// perform small optimizations on Assembler AST
void assembler_optimize(ast* ast)
{


}




// entry point for users to access the assembler
void assembler(char* file_name)
{
	FILE* file = assembler_open_file(file_name);

	ast ast;

	// call parse function to create ast
	assembler_parse(file, &ast);


	// optimize code
	assembler_optimize(&ast);


	// free file pointer after use
	free(file);

	// free AST after use


}







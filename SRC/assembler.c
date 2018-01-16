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



void assembler_parse(FILE* file)
{


	
	free(file);
}


void assembler_optimize()
{


}



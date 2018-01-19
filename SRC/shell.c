#include <shell.h>
#include <hardware.h>
#include <assembler.h>

// global file pointer for opening files
FILE* file;

// shell helper function for opening files
void run_file()
{
	processor->running = TRUE;
	while(processor->running){
		fetch(processor);

	}
}

// include path variable for shell command type.
void load_file (char* file_name)
{
	// create String filepath
	char* file_path = "TESTBIN/";

	
	char* full_path = malloc(strlen(file_path) + strlen(file_name) + 1);
	strcpy(full_path, file_path);
	strcat(full_path, file_name);
	// open file
	file = fopen(full_path, "rb");
	// find file size
	int file_size;
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	rewind(file);
	// read file into mainmem
	fread(mainmem, sizeof(unsigned char), file_size, file);
	// close file and free path string
	fclose(file);
	free(full_path);
}

// read a line from stdin to get commands for the shell.
char* shell_read_line() 
{
	char *line = malloc(sizeof(char) * SHELL_BUFF_SIZE);
	int buffer_size = SHELL_BUFF_SIZE;
	int pos = 0;
	char new_char;

	if(!line){
		perror("sh: memory allocation error.\n");
	}

	while(1){
		// read the next character
		new_char = getchar();

		if (new_char == EOF || new_char == '\n') {
			line[pos] = '\0';
			return line;
		}
		else {
			line[pos] = new_char;
		}
		pos++;

		// re-allocate buffer
		if (pos >= buffer_size) {
	      buffer_size += SHELL_BUFF_SIZE;
	      line = realloc(line, buffer_size);
	      if (!line) {
			perror("sh: memory allocation error.\n");
	      	}
	  	}
	}
}


char** shell_split_line(char* line) 
{
	int pos = 0;
	int params_size = SHELL_PARAMS_SIZE;
	char* token;
	char** args = malloc(params_size * sizeof(char*));
	// find first command
	token = strtok(line, " ");

	while (token != NULL){

		args[pos] = token;
		pos++;

		// re-allocate buffer
		if (pos >= params_size) {
	      params_size += SHELL_PARAMS_SIZE;
	      args = realloc(args, params_size);
	      if (!args) {
			perror("sh: memory allocation error.\n");
	      	}
	  	}

		token = strtok(NULL, " ");

	}
		args[pos] = NULL;

		return args;


}


int	    shell_execute_command(int argc, char** args)
{
		if (strcmp(args[0], "open") == 0){
			if (argc != 2) {
				printf("MUST INCLUDE FILENAME TO RUN\n");
				return 0;
			}
			load_file(args[1]);
			run_file();
			return 0;

		}

		if (strcmp(args[0], "asm") == 0) {
			if (argc != 2) {
				printf("MUST INCLUDE FILENAME TO ASSEMBLE\n");
				return 0;
			}
			assembler(args[1]);

		}
		printf("%s IS NOT A VALID COMMAND\n", args[0]);
		return 0;
}

int 	shell()
{
	// status is ok!
	int status = 1;
	char* line;
	char** args;
	while (status >= 0) {
		printf(">");
		// read and parse shell commands
		line = shell_read_line();
		args = shell_split_line(line);

		// find number of arguments
		int count = 0;
		while (args[count]){
			count++;
		}
		// execute command and return error code if necessary
		status = shell_execute_command(count, args);
		free(line);
		free(args);
	}
	printf("sh: exiting shell\n");
	return 0;


}
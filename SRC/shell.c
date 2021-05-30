#include "shell.h"
#include "hardware.h"


FILE* file;
// shell helper function for opening files
void run_file()
{
	processor->running = TRUE;
	while(processor->running){
		printf("Fetch\n");
		fetch(processor);

	}
}

void load_file (char* file_name)
{
	char* file_path = "C:\\Users\\Liam\\Desktop\\VCM\\Vector-Computing-Machine\\TESTBIN\\";
	char* full_path = malloc(strlen(file_path) + strlen(file_name) + 1);
	strcpy(full_path, file_path);
	strcat(full_path, file_name);
	file = fopen(full_path, "rb");
	int file_size;
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	rewind(file);
	fread(mainmem, sizeof(unsigned char), file_size, file);
	free(full_path);
}

// read a line from stdin to get commands for the shell.
char* shell_read_line() 
{
	char *line = malloc(sizeof(char) * SHELL_BUFF_SIZE);
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

	// deal with buffer size issues in the future maybe?
	}
}


char** shell_split_line(char* line) 
{
	int position = 0;
	char* token;
	char** args = malloc(SHELL_BUFF_SIZE * sizeof(char*));
	// find first command
	token = strtok(line, " ");

	while (token != NULL){

		args[position] = token;
		position++;

		token = strtok(NULL, " ");

	}
		args[position] = NULL;

		return args;


}


int	    shell_execute_command(int argc, char** args)
{
		if (strcmp(args[0], "open") == 0){
			if (argc != 2) {
				printf("MUST INCLUDE FILENAME\n");
				return 0;
			}
			load_file(args[1]);
			run_file();
			return 0;

		}
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
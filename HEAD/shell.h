#ifndef SHELL_H_
#define SHELL_H_

// constants for use by the shell
#define SHELL_BUFF_SIZE 1024
#define SHELL_PARAMS_SIZE 10


// helpers for shell
void run_file();
void load_file(char* file_name);

// functions for the shell
char* 	shell_read_line();
char**	shell_split_line(char* line);
int	    shell_execute_command(int argc, char** args);
int 	shell();



#endif // SHELL_H_
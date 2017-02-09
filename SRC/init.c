#include <hardware.h>
#include <stdlib.h>
#include <stdio.h>

FILE* file;

void load_file (char* file_name)
{
	char* file_path = "TESTBIN/";
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



int main (int argc, char* argv[])
{
	if (argc != 2) {
		printf("PLEASE INPUT A FILE NAME TO BE LOADED AND NOTHING ELSE\n");
		return -1;
	}
	// initialize hardware
	unsigned char mainmem[MEM_SIZE];
	cpu* processor = malloc(sizeof(cpu));
	gpu* graphics = malloc(sizeof(gpu));

	load_file(argv[1]);


	processor->running = TRUE;
	while(processor->running) {
		fetch(processor);

	}

	printf("halt: processor stopped\n");

}

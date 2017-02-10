#include <hardware.h>
#include <stdlib.h>
#include <stdio.h>
#include <shell.h>


int main (int argc, char* argv[])
{
	/*
	if (argc != 2) {
		printf("PLEASE INPUT A FILE NAME TO BE LOADED AND NOTHING ELSE\n");
		return -1;
	}
	*/
	// initialize hardware
	unsigned char mainmem[MEM_SIZE];
	processor = malloc(sizeof(cpu));
	graphics = malloc(sizeof(gpu));

	
	shell();

	printf("halt: processor stopped\n");

}

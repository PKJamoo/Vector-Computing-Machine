#include <hardware.h>
#include <assembler.h>



FILE* assembler_open_file(char* file_name)
{

	FILE* file;
	// create String filepath
	char* file_path = "C:\\Users\\Liam\\Desktop\\VCM\\Vector-Computing-Machine\\test\\";

	
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
			//printf("asm code: %s\n", buffer);
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
	//printf("line: %s\n", line);
	int pos = 0;
	int params_size = ASSEMBLER_PARAMS_SIZE;
	char* token;
	char** args = malloc(params_size * sizeof(char*));
	// find first command
	token = strtok(line, " ");

	while (token != NULL){

		//printf("token: %s\n", token);
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
		if (pos > 1) {
			args[1][strlen(args[1])] = '\0';
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
void assembler_parse_instr(char** args, int argc, instr* instr, uint16_t *address)
{
	// big if/else tree based on type of instruction
	if (strcmp(args[0], "HALT") == 0){
		strcpy(instr->opcode, "HALT");
		instr->address = (*address)++;

	}
	else if (strcmp(args[0], "NOP") == 0){
		strcpy(instr->opcode, "NOP");
		instr->address = (*address)++;
	}

	else if (strcmp(args[0], "MOV") == 0){
		strcpy(instr->opcode, "MOV");
		strcpy(instr->arg0, args[1]);
		strcpy(instr->arg1, args[2]);
		instr->address = *address;
		*address += 2;
	}
	else if (strcmp(args[0], "LOAD") == 0){
		// TODO differentiate the types of lds and stores
		strcpy(instr->opcode, "LOAD");
		strcpy(instr->arg0, args[1]);
		strcpy(instr->arg1, args[2]);
		instr->address = *address;
		*address += 4;
	}
	else if (strcmp(args[0], "STORE") == 0){
		// TODO differentiate the types of lds and stores
		strcpy(instr->opcode, "STORE");
		strcpy(instr->arg0, args[1]);
		strcpy(instr->arg1, args[2]);
		instr->address = *address;
		*address += 4;
	}

	else if (strcmp(args[0], "ADD") == 0){
		strcpy(instr->opcode, "BIN");
		strcpy(instr->fncode, "ADD");
		strcpy(instr->arg0, args[1]);
		strcpy(instr->arg1, args[2]);
		instr->address = *address;
		*address += 2;
	}
	else if (strcmp(args[0], "SUB") == 0){
		strcpy(instr->opcode, "BIN");
		strcpy(instr->fncode, "SUB");
		strcpy(instr->arg0, args[1]);
		strcpy(instr->arg1, args[2]);
		instr->address = *address;
		*address += 2;
	}
	else if (strcmp(args[0], "MULT") == 0){
		strcpy(instr->opcode, "BIN");
		strcpy(instr->fncode, "MULT");
		strcpy(instr->arg0, args[1]);
		strcpy(instr->arg1, args[2]);
		instr->address = *address;
		*address += 2;
	}

	else if (strcmp(args[0], "DIV") == 0){
		strcpy(instr->opcode, "BIN");
		strcpy(instr->fncode, "DIV");
		strcpy(instr->arg0, args[1]);
		strcpy(instr->arg1, args[2]);
		instr->address = *address;
		*address += 2;
	}
	else if (strcmp(args[0], "MOD") == 0){
		strcpy(instr->opcode, "BIN");
		strcpy(instr->fncode, "MOD");
		strcpy(instr->arg0, args[1]);
		strcpy(instr->arg1, args[2]);
		instr->address = *address;
		*address += 2;
	}
	else if (strcmp(args[0], "AND") == 0){
		strcpy(instr->opcode, "BIN");
		strcpy(instr->fncode, "AND");
		strcpy(instr->arg0, args[1]);
		strcpy(instr->arg1, args[2]);
		instr->address = *address;
		*address += 2;
	}

	else if (strcmp(args[0], "XOR") == 0){
		strcpy(instr->opcode, "XOR");
		strcpy(instr->fncode, "XOR");
		strcpy(instr->arg0, args[1]);
		strcpy(instr->arg1, args[2]);
		instr->address = *address;
		*address += 2;
	}
	else if (strcmp(args[0], "JMP") == 0){
		strcpy(instr->opcode, "JMP");
		strcpy(instr->fncode, "UCN");
		strcpy(instr->arg0, args[1]);
		instr->address = *address;
		*address += 3;
	}
	else if (strcmp(args[0], "JGE") == 0){
		strcpy(instr->opcode, "JMP");
		strcpy(instr->fncode, "GE");
		strcpy(instr->arg0, args[1]);
		instr->address = *address;
		*address += 3;


	}
	else if (strcmp(args[0], "JGT") == 0){
		strcpy(instr->opcode, "JMP");
		strcpy(instr->fncode, "GT");
		strcpy(instr->arg0, args[1]);
		instr->address = *address;
		*address += 3;

	}
	else if (strcmp(args[0], "JEQ") == 0){
		strcpy(instr->opcode, "JMP");
		strcpy(instr->fncode, "EQ");
		strcpy(instr->arg0, args[1]);
		instr->address = *address;
		*address += 3;

	}
	else if (strcmp(args[0], "JNE") == 0){
		strcpy(instr->opcode, "JMP");
		strcpy(instr->fncode, "NE");
		strcpy(instr->arg0, args[1]);
		instr->address = *address;
		*address += 3;

	}
	else if (strcmp(args[0], "JLT") == 0){
		strcpy(instr->opcode, "JMP");
		strcpy(instr->fncode, "LT");
		strcpy(instr->arg0, args[1]);
		instr->address = *address;
		*address += 3;

	}
	else if (strcmp(args[0], "JLE") == 0){
		strcpy(instr->opcode, "JMP");
		strcpy(instr->fncode, "LE");
		strcpy(instr->arg0, args[1]);
		instr->address = *address;
		*address += 3;

	}
	else if (strcmp(args[0], "CALL") == 0){
		strcpy(instr->opcode, "CALL");
		instr->address = *address;
		*address += 3;
	}
	else if (strcmp(args[0], "RET") == 0){
		strcpy(instr->opcode, "RET");
		instr->address = *address;
		*address += 3;
	}
	else if (strcmp(args[0], "PUSH") == 0){
		strcpy(instr->opcode, "PUSH");
		instr->address = *address;
		*address += 1;
	}
	else if (strcmp(args[0], "POP") == 0){
		strcpy(instr->opcode, "POP");
		instr->address = *address;
		*address += 1;
	}
	else if (strcmp(args[0], "DRAWR") == 0){
		strcpy(instr->opcode, "DRAW");
		strcpy(instr->opcode, "REC");
	}
	else if (strcmp(args[0], "DRAWC") == 0){
		strcpy(instr->opcode, "DRAW");
		strcpy(instr->opcode, "CIR");
	}
	else if (strcmp(args[0], "DRAWL") == 0){
		strcpy(instr->opcode, "DRAW");
		strcpy(instr->opcode, "LIN");
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
	// TODO: FIX BUG, LOST INSTRUCTION IF EOF IS ON SAME LINE AS LAST INSTR
	// get pointer to first instr in ast
	instr* current_instr = ast->instrs;
	label* current_label = ast->labels;
	// set up current address
	uint16_t address = 0;


	int end;
	end = 0;
	// check to see if file ended
	while (!end){
		char** args = assembler_split_line(	 // find separate pieces of assembler instr
			assembler_read_line(file, &end)); // read a single line, determine if file is ended
			if (end) break;					// check if we're on the last line and leave the loop

		int arg_count = 0;
		while (args[arg_count]){
			arg_count++;
		}
		// logic to deal with labels
		
		if (strcmp(&args[0][strlen(args[0]) - 1], ":") == 0){ 	// if :, it means it is a label.
			// if the label is on it's own line, move on.
			args[0][strlen(args[0]) - 1] = '\0';
			strcpy(current_label->name, args[0]);
			current_label->address = address;
			//printf("label name: %s %d\n", current_label->name, current_label->address);

			current_label->next = malloc(sizeof(label));
			current_label = current_label->next;

			if (arg_count == 1) {continue;}
			else {
				// if the label is on the same line as an instruction.
				char* old_arg = args[0];
				// delete the label instruction.
				args = &args[1];
				arg_count--;
				// free the memory
				//free(old_arg);
				old_arg = NULL;
			}
		}
		assembler_parse_instr(args, arg_count, current_instr, &address); // parse the arguments into an ast instr_node
		current_instr->next = malloc(sizeof(instr));
		current_instr = current_instr->next;
	} 
}

void print_ast(ast* ast)
{
	instr* current_instr;
	current_instr = ast->instrs;

	label* current_label;
	current_label = ast->labels;

	printf("\nINSTRUCTIONS\n");
	while (current_instr->next != NULL)
	{
		printf("ADDR: %d | INSTR: %s %s %s %s \n", current_instr->address, current_instr->opcode, current_instr->fncode, current_instr->arg0, current_instr->arg1);
		current_instr = current_instr->next;
	}

	printf("\nLABELS\n");
	while (current_label->next != NULL)
	{
		printf("NAME: %s | ADDR: %d\n", current_label->name, current_label->address);
		current_label = current_label->next;

	}
}

// perform small optimizations on Assembler AST
void assembler_optimize(ast* ast)
{


}

void assembler_bin_instr(unsigned char* binary, instr* instr, int *place)
{


	if (strcmp(instr->opcode, "HALT") == 0){
		binary[(*place)++] = 0x00;
	}
	else if (strcmp(instr->opcode, "NOP") == 0){
		binary[(*place)++] = 0x10;
	}

	else if (strcmp(instr->opcode, "MOV") == 0){
		binary[(*place)++] = 0x20;
		unsigned char regs_args = 0x00;
		regs_args = ((instr->arg0[0] % 65) + 1) << 4;
		regs_args += ((instr->arg1[0] % 65) + 1);
		binary[(*place)++] = regs_args;
	}
	else if (strcmp(instr->opcode, "LOAD") == 0){
		// TODO differentiate the types of lds and stores
		binary[(*place)++] = 0x30;
		unsigned char regs_args = 0x00;
		regs_args += ((instr->arg1[0] % 65) + 1);
		binary[(*place)++] = regs_args;
		uint16_t addr = (uint16_t) strtol(&instr->arg0[1], NULL, 16);
		binary[(*place)++] = (unsigned char) (addr >> 8);
		binary[(*place)++] = addr;

	}
	else if (strcmp(instr->opcode, "STORE") == 0){
		// TODO differentiate the types of lds and stores
		binary[(*place)++] = 0x40;
		unsigned char regs_args = 0x00;
		regs_args += ((instr->arg1[0] % 65) + 1);
		binary[(*place)++] = regs_args;
		uint16_t addr = (uint16_t) strtol(&instr->arg0[1], NULL, 16);
		binary[(*place)++] = (unsigned char) (addr >> 8);
		binary[(*place)++] = addr;

	}

	else if (strcmp(instr->fncode, "ADD") == 0){
		binary[(*place)++] = 0x50;
		unsigned char regs_args = 0x00;
		regs_args = ((instr->arg0[0] % 65) + 1) << 4;
		regs_args += ((instr->arg1[0] % 65) + 1);
		binary[(*place)++] = regs_args;
	}
	else if (strcmp(instr->fncode, "SUB") == 0){
		binary[(*place)++] = 0x51;
		unsigned char regs_args = 0x00;
		regs_args = ((instr->arg0[0] % 65) + 1) << 4;
		regs_args += ((instr->arg1[0] % 65) + 1);
		binary[(*place)++] = regs_args;

	}
	else if (strcmp(instr->fncode, "MULT") == 0){
		binary[(*place)++] = 0x52;
		unsigned char regs_args = 0x00;
		regs_args = ((instr->arg0[0] % 65) + 1) << 4;
		regs_args += ((instr->arg1[0] % 65) + 1);
		binary[(*place)++] = regs_args;

	}

	else if (strcmp(instr->fncode, "DIV") == 0){
		binary[(*place)++] = 0x53;
		unsigned char regs_args = 0x00;
		regs_args = ((instr->arg0[0] % 65) + 1) << 4;
		regs_args += ((instr->arg1[0] % 65) + 1);
		binary[(*place)++] = regs_args;
	}
	else if (strcmp(instr->fncode, "MOD") == 0){
		binary[(*place)++] = 0x54;
		unsigned char regs_args = 0x00;
		regs_args = ((instr->arg0[0] % 65) + 1) << 4;
		regs_args += ((instr->arg1[0] % 65) + 1);
		binary[(*place)++] = regs_args;
	}
	else if (strcmp(instr->fncode, "AND") == 0){
		binary[(*place)++] = 0x55;
		unsigned char regs_args = 0x00;
		regs_args = ((instr->arg0[0] % 65) + 1) << 4;
		regs_args += ((instr->arg1[0] % 65) + 1);
		binary[(*place)++] = regs_args;
	}

	else if (strcmp(instr->fncode, "XOR") == 0){
		binary[(*place)++] = 0x56;
		unsigned char regs_args = 0x00;
		regs_args = ((instr->arg0[0] % 65) + 1) << 4;
		regs_args += ((instr->arg1[0] % 65) + 1);
		binary[(*place)++] = regs_args;
	}
	else if (strcmp(instr->fncode, "UCN") == 0){
		binary[(*place)++] = 0x60;
		uint16_t addr = (uint16_t) strtol(instr->arg0, NULL, 16);
		binary[(*place)++] = (unsigned char) (addr >> 8);
		binary[(*place)++] = addr;
	}
	else if (strcmp(instr->fncode, "JGE") == 0){
		binary[(*place)++] = 0x61;
		uint16_t addr = (uint16_t) strtol(instr->arg0, NULL, 16);
		binary[(*place)++] = (unsigned char) (addr >> 8);
		binary[(*place)++] = addr;
	}
	else if (strcmp(instr->fncode, "JGT") == 0){
		binary[(*place)++] = 0x62;
		uint16_t addr = (uint16_t) strtol(instr->arg0, NULL, 16);
		binary[(*place)++] = (unsigned char) (addr >> 8);
		binary[(*place)++] = addr;
	}
	else if (strcmp(instr->fncode, "JEQ") == 0){
		binary[(*place)++] = 0x63;
		uint16_t addr = (uint16_t) strtol(instr->arg0, NULL, 16);
		binary[(*place)++] = (unsigned char) (addr >> 8);
		binary[(*place)++] = addr;

	}
	else if (strcmp(instr->fncode, "JNE") == 0){
		binary[(*place)++] = 0x64;
		uint16_t addr = (uint16_t) strtol(instr->arg0, NULL, 16);
		binary[(*place)++] = (unsigned char) (addr >> 8);
		binary[(*place)++] = addr;
	}
	else if (strcmp(instr->fncode, "JLT") == 0){
		binary[(*place)++] = 0x65;
		uint16_t addr = (uint16_t) strtol(instr->arg0, NULL, 16);
		binary[(*place)++] = (unsigned char) (addr >> 8);
		binary[(*place)++] = addr;

	}
	else if (strcmp(instr->fncode, "JLE") == 0){
		binary[(*place)++] = 0x66;
		uint16_t addr = (uint16_t) strtol(instr->arg0, NULL, 16);
		binary[(*place)++] = (unsigned char) (addr >> 8);
		binary[(*place)++] = (unsigned char) addr;

	}
	else if (strcmp(instr->opcode, "CALL") == 0){
		binary[(*place)++] = 0x70;

	}
	else if (strcmp(instr->opcode, "RET") == 0){
		binary[(*place)++] = 0x80;
	}
	else if (strcmp(instr->opcode, "PUSH") == 0){
		binary[(*place)++] = 0x90;
	}
	else if (strcmp(instr->opcode, "POP") == 0){
		binary[(*place)++] = 0xA0;
	}
	else if (strcmp(instr->fncode, "REC") == 0){
		binary[(*place)++] = 0xB0;
	}
	else if (strcmp(instr->fncode, "CIR") == 0){
		binary[(*place)++] = 0xB1;

	}
	else if (strcmp(instr->fncode, "LIN") == 0){
		binary[(*place)++] = 0xB2;

	}
	else if (strcmp(instr->opcode, "PRINT") == 0){
		binary[(*place)++] = 0xC0;

	}
	

}


void assembler_create_bin(ast* ast)
{
	// TODO: calculate number of bytes needed from ast
	unsigned char* binary = malloc(sizeof(unsigned char) * 1000);
	int place = 0;
	int i = 0;
	instr* current_instr = ast->instrs;
	while (current_instr->next) {
	assembler_bin_instr(binary, current_instr, &place);
	current_instr = current_instr->next;
	i++;
	}


	for(int i = 0; i < place; i++){
		printf("%02x ", binary[i]);
	}
		printf("\n");
}


// entry point for users to access the assembler
void assembler(char* file_name)
{
	// open .pasm file for parsing
	FILE* file = assembler_open_file(file_name);
	if (!file) {
		printf("asm: No such file or directory exists\n");
		return;
	}
	//printf("opened file\n");

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
	//printf("parsed\n");
	print_ast(ast);

	// optimize code
	//assembler_optimize(ast);
	// create binary file
	//assembler_create_bin(ast);

	// close file after use
	fclose(file);

	// free AST after use
	/*
	instr* temp_instr;
	while (ast->instrs != NULL){
		temp_instr = ast->instrs;
		ast->instrs = ast->instrs->next;
		free(temp_instr);
	}
	ast->instrs = NULL;
	label* temp_label;
	while (ast->labels != NULL){
		temp_label = ast->labels;
		ast->labels = ast->labels->next;
		free(temp_label);
	}
	ast->labels = NULL;

	free(ast);
	*/

}







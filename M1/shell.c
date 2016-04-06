
// This file should be compiled and assembled with lib.asm not kernel.asm

int parse(char*);
void execute(char*, char*);
void copy(char*, char*, int);

void main(){
	//I don't think you need an infinite loop here since the
	//infinite loop should be in the kernel loading this program
	//endlessly.

	// Also, to parse any command, you don't need to read more than the
	// first two characters to know which command is it.
	
	char cmd[19]; //bottleneck is at copy: 4+1+6+1+6+\0
	char buffer[13312];
	interrupt(0x21, 0, "$ \0", 0, 0);
	interrupt(0x21, 1, cmd, 0, 0);
	execute(cmd, buffer);
}

/*returns a number specifying which command should be executed
The number is returned according to the description ordering of
the shell commands. It also returns -1 indicating an error*/

int parse(char* cmd){
	if(cmd[0] == 'v')
		return 1;
	if(cmd[0] == 'e')
		return 2;
	if(cmd[0] == 'd')
		if(cmd[1] == 'e')
			return 3;
		return 5;
	if(cmd[0] == 'c')
		if(cmd[1] == 'o')
			return 4;
		return 6;
	return -1;
}

void execute(char* cmd, char* buffer){
	char arg1[6];
	char arg2[6];
	int proc = parse(cmd);
	if(proc == 1){
		copy(cmd, arg1, 5);
		interrupt(0x21, 3, arg1, buffer, 0);
		interrupt(0x21, 0, buffer, 0, 0);
	}
}


void copy(char* cmd, char* arg, int j){
	for(int i = j; i<6; i++)
		arg[i] = cmd[i];
}
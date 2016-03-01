

void printString(char*);
void readString(char*);

void main()
{
	
	// putInMemory(0xB000, 0x8000, 'H');
	// putInMemory(0xB000, 0x8001, 0x7); // white
	// putInMemory(0xB000, 0x8002, 'e');
	// putInMemory(0xB000, 0x8003, 0x7);
	// putInMemory(0xB000, 0x8004, 'l');
	// putInMemory(0xB000, 0x8005, 0x7);
	// putInMemory(0xB000, 0x8006, 'l');
	// putInMemory(0xB000, 0x8007, 0x7);
	// putInMemory(0xB000, 0x8008, 'o');
	// putInMemory(0xB000, 0x8009, 0x7);
	// putInMemory(0xB000, 0x800A, ',');
	// putInMemory(0xB000, 0x800B, 0x7);
	// putInMemory(0xB000, 0x800C, ' ');
	// putInMemory(0xB000, 0x800D, 0x7);
	// putInMemory(0xB000, 0x800E, 'w');
	// putInMemory(0xB000, 0x800F, 0x7);
	// putInMemory(0xB000, 0x8010, 'o');
	// putInMemory(0xB000, 0x8011, 0x7);
	// putInMemory(0xB000, 0x8012, 'r');
	// putInMemory(0xB000, 0x8013, 0x7);
	// putInMemory(0xB000, 0x8014, 'l');
	// putInMemory(0xB000, 0x8015, 0x7);
	// putInMemory(0xB000, 0x8016, 'd');
	// putInMemory(0xB000, 0x8017, 0x7);
	// putInMemory(0xB000, 0x8018, '!');
	// putInMemory(0xB000, 0x8019, 0x7);
	// while(1);
	char line[80];
	printString("Hello, world!!!!\n\0");
	readString(line);
	printString("\n\0");
	printString(line);
	while(1);
}


void printString(char* in){
	while(*in != '\0'){
		interrupt(0x10, (0xE*256) + (*in), 0, 0, 0);
		in++;
	}
}


void readString(char* buffer){
	char in = interrupt(0x16, 0, 0, 0, 0);
	int i = 0;
	while(in != 0xd){
		if(in != 0x8){
		*buffer = in;
		buffer++;
		i++;
	}else{
		buffer = i>0 ? buffer-- : buffer;
		i = i>0 ? i-- : i;
		*buffer = '\0';
	}
		interrupt(0x10, 0xE*256 + (in), 0, 0, 0);
		in = interrupt(0x16, 0, 0, 0, 0);
	} 
	buffer++; *buffer = 0xa;
	buffer++; *buffer = 0x0;
}


void printString(char*);
void readString(char*);
int DIV(int,int);
int MOD(int,int);
void readSector(char*,int);
void handleInterrupt21 (int,int,int,int);

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
	//--------------------
	//test of task 1& 2
	// 	char line[80];
  // printString("Hello, world!!!!\n\0");
  // readString(line);
  // printString("\n\0");
  // printString(line);
	//-----------------------
	//test of task 3
	//char buffer[512];
	//readSector(buffer, 30);
	//printString(buffer);
	//-----------------------
	// test task 4,5
	char* line[100];
    makeInterrupt21(); 
    interrupt(0x21,1,line,0,0);
    interrupt(0x21,0,line,0,0);
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
		if(i>0){
			i--;
			buffer--;
		}
		*buffer = '\0';
	}
		interrupt(0x10, 0xE*256 + (in), 0, 0, 0);
		in = interrupt(0x16, 0, 0, 0, 0);
	}
	buffer++; *buffer = 0xa;
	buffer++; *buffer = 0x0;
}
int DIV(int a, int b){
	int x=0;
	if(!b) return 0; //it will make error
	for(;a>=b;x++){ a-=b;}
	return x;
}
int MOD(int a , int b){
	if(!b) return 0; //it will make error
	for(;a>=b;){ a-=b;}
	return a;
}

void readSector(char* buffer, int sector){
	int cl = MOD(sector,18)+1;
	int dh =  MOD(DIV(sector,18),2);
	int ch = DIV(sector,36);
	interrupt(0x13,(2*256)+1,buffer,(ch*256)+cl,dh*256);

}

void handleInterrupt21 (int ax, int bx, int cx, int dx){
	if(ax == 0){
   printString(bx);
	}
	if(ax == 1){
   readString(bx);
	}
	if(ax == 2){
    readSector(bx,cx);
	}
	if(ax >= 3){
    printString("ERROR !!!!! \n\0");  
	}  
}

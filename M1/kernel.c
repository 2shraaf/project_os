
void main()
{

	putInMemory(0xB000, 0x8000, 'H');
	putInMemory(0xB000, 0x8001, 0x7); // white
	putInMemory(0xB000, 0x8002, 'e');
	putInMemory(0xB000, 0x8003, 0x7);
	putInMemory(0xB000, 0x8004, 'l');
	putInMemory(0xB000, 0x8005, 0x7);
	putInMemory(0xB000, 0x8006, 'l');
	putInMemory(0xB000, 0x8007, 0x7);
	putInMemory(0xB000, 0x8008, 'o');
	putInMemory(0xB000, 0x8009, 0x7);
	putInMemory(0xB000, 0x800A, ',');
	putInMemory(0xB000, 0x800B, 0x7);
	putInMemory(0xB000, 0x800C, ' ');
	putInMemory(0xB000, 0x800D, 0x7);
	putInMemory(0xB000, 0x800E, 'w');
	putInMemory(0xB000, 0x800F, 0x7);
	putInMemory(0xB000, 0x8010, 'o');
	putInMemory(0xB000, 0x8011, 0x7);
	putInMemory(0xB000, 0x8012, 'r');
	putInMemory(0xB000, 0x8013, 0x7);
	putInMemory(0xB000, 0x8014, 'l');
	putInMemory(0xB000, 0x8015, 0x7);
	putInMemory(0xB000, 0x8016, 'd');
	putInMemory(0xB000, 0x8017, 0x7);
	putInMemory(0xB000, 0x8018, '!');
	putInMemory(0xB000, 0x8019, 0x7);
	while(1);
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
	interrupt(0x10, buffer, 0, 0, 0);

}

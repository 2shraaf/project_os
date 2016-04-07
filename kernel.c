
void printString(char*);
void readString(char*);
void readSector(char*,int);
void readFile(char*, char* );
void writeSector(char*,int);
void writeFile(char*,char*, int );
void handleInterrupt21 (int,int,int,int);
void printChar(char );
void prtInt(int );
//M3 T1
int my_strcmp(char*, char*);
int DIV(int,int);
int MOD(int,int);
void deleteFile(char*);
void executeProgram(char*, int);
void terminateProgram();

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
	// 	char line[80];x
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
	// char* line[100];
 	// makeInterrupt21();
 	// interrupt(0x21,1,line,0,0);
 	// interrupt(0x21,0,line,0,0);
 	//----------------------------------------------------------------
 	/**
 	 * test loadfile
 	 */
    char buffer[13312]; /*this is the maximum size of a file*/
 	 char buffer1[13312];
	// makeInterrupt21();
	// interrupt(0x21, 3, "messag\0", buffer, 0); //read the file into buffer
	// interrupt(0x21, 0, buffer, 0, 0); /*print out the file*/
	// ---------------------------------------------------------------
  /**
   * test writeFile
   */
  // int i=0;
  // char buffer1[13312];
  // char buffer2[13312];
  // buffer2[0]='h'; buffer2[1]='e'; buffer2[2]='l';
  // buffer2[4]='o'; //will not prented cuz buffer2[3] =0x00
  // for(i=5; i<13312; i++) buffer2[i]=0x0;
  // makeInterrupt21();
  // interrupt(0x21,8, "testW\0", buffer2, 1); //write file testW
  // interrupt(0x21,3, "testW\0", buffer1, 0); //read file testW
  // interrupt(0x21,0, buffer1, 0, 0); // print out contents of testW
  // printChar(buffer1[4]);

  /*** Testing deleteFile ****/
  
// makeInterrupt21();
// interrupt(0x21, 7, "messag\0", 0, 0); //delete messag
// interrupt(0x21, 3, "messag\0", buffer1, 0); // try to read messag
// interrupt(0x21, 0, buffer1, 0, 0); //print out the contents of buffer

/* Test for executeProgram */
// makeInterrupt21();
// interrupt(0x21, 4,"tstprg\0", 0x2000, 0);

/* Test for terminateProgram */
makeInterrupt21();
interrupt(0x21, 4,"tstpr2\0", 0x2000, 0);
   /* you should load the shell program here using loadProgram or 
   whatever its name was*/
   // interrupt(0x21, 0, "hello\0", 0, 0);
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
int MOD(int a, int b){
    while(a >= b){
        a = a - b;
    }
    return a;
}

int DIV(int a, int b){
    int q = 0;
    while(q*b <=a){
        q = q+1;
    }
    return q-1;

}

void readSector(char* buffer, int sector){
	int cl = MOD(sector,18)+1;
	int dh =  MOD(DIV(sector,18),2);
	int ch = DIV(sector,36);
	interrupt(0x13,(2*256)+1,buffer,(ch*256)+cl,dh*256);

}
/**
*	Write a buffer in a certain sector
*buffer size 512
* Ah = 3
*/

void writeSector(char* buffer, int sector){
  int cl = MOD(sector,18)+1;
  int dh =  MOD(DIV(sector,18),2);
  int ch = DIV(sector,36);
  interrupt(0x13,(3*256)+1,buffer,(ch*256)+cl,dh*256);
}

/**
*	Write a file in a certain sectors
*
*/

void writeFile(char* name, char* buffer, int secNum){
    int indx = -1;
    int i = 0;
    int bff =0;
    int j = 0;
    int sec = -1;
    char diskMap[512];
    char directoryMap[512];
    char giveToSector[512];
    if(secNum>26)secNum =26;
    readSector(directoryMap,2);
    readSector(diskMap,1);

    // pass by 16 line of 32 bytes
    for( i = 0 ;i<512;i+=0x20 ){
      if(directoryMap[i]=='\0'){
        indx = i;
        break;
      }
    }
    if(indx==-1){
      printString("No Free space for Directory \n\0");
        return;
    }
    for( i = 0;i<6;i++,indx++){
      if(name[i] == '\0'){ //If name lenth < 6
        directoryMap[indx]=0x00;
    }else{
        directoryMap[indx]=name[i];
      }
    }
    for( j = 0 ;j<secNum;j++,indx++){
      sec = -1;
      for( i = 3;i<512;i++){
        if(diskMap[i]!=0x00){ //search for free sector
          sec=i;
          diskMap[i]=0xFF; //use it
          break;
        }
      }
      if(sec==-1){
          printString("No Free space for sector \n\0");
          return;
      }
      directoryMap[indx]= sec;

      for( i=0;i<512;i++){
          giveToSector[i]=buffer[bff];
          bff++;
      }
      writeSector(giveToSector,sec);
    }
    for(i = secNum;i< 26;i++,indx++){
      directoryMap[indx] = 0x00;
    }
    writeSector(diskMap,1);
    writeSector(directoryMap,2);
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
	if(ax == 3){
    readFile(bx,cx);
	}
  if(ax == 4){
    executeProgram(bx,cx);
  }
  if(ax == 5){
    terminateProgram();
  }
  if(ax== 6){
  writeSector(bx,cx);
  }
  if(ax == 7){
  deleteFile(bx);
  }
  if(ax ==8){
  writeFile(bx,cx,dx);
    }
}
	/**
	*	Reads a file into a certain buffer, it will alert the user if the
	*	file is not found.
	*/
void readFile(char* file_name, char* buff){
		char dir[512];
    char cm [8];
    int i = 0, j , k = 0 , f = 0 ,z;
		readSector(dir, 2);
		for( i = 0; i<16; i++){
      for(f = 0 ; f<6 ;f++)
        cm[f] = dir[k+f];
    	cm[6] = "\n";
    	cm[7] = "\0";
			if(my_strcmp(cm, file_name)==1){
				k += 6;
				for ( j = 0; j < 26 &&  dir[k]!= 0x0; j++){
					readSector(buff,dir[k]);
					k  = k +  1;
					buff += 512;
				}
				return;
			}
			k += 32;
		}
		printString("The file \0");
    printString(file_name);
		printString("does not exist\n\0");
	}
	// It only checks if the first 6 bytes of a are equal to b unlike the
	// std strcmp.
	int my_strcmp(char* a, char* b){
		int i;
		for(i = 0; i<6; i++){
			if(a[i] != b[i]){
        return 0;

      }
		}
		return 1;
	}

void deleteFile(char* name){
	int i, j, k, f;
	char dir[512];
	char map[512];
	char cm[8];
	readSector(dir, 2);
	readSector(map, 1);

	for(i = 0; i<16; i++){
		for(f = 0 ; f<6 ;f++)
        	cm[f] = dir[k+f];
    	cm[6] = "\n";
    	cm[7] = "\0";
    	if(my_strcmp(cm, name)==1){
    		dir[k] = 0x0;
    		k+=6;
    		for ( j = 0; j < 26 &&  dir[k]!= 0x0; j++){
    			map[((int)dir[k]) + 1] = 0x00;
    			k = k + 1;
    		}
    		writeSector(map,1);
    		writeSector(dir,2);
    		return;
    	}
    	k+=32;
	}

	printString("The file \0");
    printString(name);
	printString("does not exist\n\0");

}
//Task 2 M3.
void executeProgram(char* name, int segment){
  int i;
  char buff[512]; 
  readFile(name, buff); 
    for(i = 0; i<512; i++){
       putInMemory(segment, 0x0000 + i, buff[i]);
    }
  launchProgram(segment);
}
//Task 3 M3.
void terminateProgram(){
  while(1);
}
  /**
   * For test
   *
   */
  void printChar(char ch){
  	char* chars[2];
  	chars[0] = ch;
  	chars[1] = '\0';
  	printString(chars);
  }
  void prtInt(int i){
  	int* chars[2];
  	chars[0] ='0'+i;
  	chars[1] = '\0';
  	printString(chars);

  }

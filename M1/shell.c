
// This file should be compiled and assembled with lib.asm not kernel.asm

void execute(char*, char*);
int my_strcmp(char* , char* );
int my_strcmp1(char* , char* );
void getword(char* ,char*);
int check(char*);
int copy(char* , char* , int );
int DIV(int,int);
int MOD(int,int);


void main(){
	//I don't think you need an infinite loop here since the
	//infinite loop should be in the kernel loading this program
	//endlessly.

	// Also, to parse any command, you don't need to read more than the
	// first two characters to know which command is it.
	int i ;
	while(1){
		char cmd[100]; //bottleneck is at copy: 4+1+6+1+6+\0
		char buffer[13312];
		for( i = 0 ; i<13312;i++)
			buffer[i]=0x00;
		for( i = 0 ; i<100;i++)
			cmd[i]=0x00;
		interrupt(0x21, 0, "$ \0", 0, 0);
		interrupt(0x21, 1, cmd, 0, 0);
		execute(cmd, buffer);
	}
}

/*returns a number specifying which command should be executed
The number is returned according to the description ordering of
the shell commands. It also returns -1 indicating an error*/

int check(char* word){
	if(my_strcmp(word,"view\0\0"))
		return 1;
	if(my_strcmp(word,"execut"))
		return 2;
	if(my_strcmp(word,"delete"))
		return 3;
	if(my_strcmp(word,"copy\0\0"))
		return 4;
	if(my_strcmp(word,"dir\0\0\0"))
		return 5;
	if(my_strcmp(word,"create\0"))
		return 6;
	return -1;

}
void getword(char* cmd,char* word){
	int i = 0;
	int j = 0;
	int k = 0;
	int c = 0;
	int tr = 0;
	for( i = 0 ; i<6 ;i++){
		if(cmd[i] == 0x20 || cmd[i]==0x00)
			break;
		word[i]=cmd[i];
	}
	for(c = i;c<6;c++)
		word[c]=0x00;
	tr = (i==6);
	while(cmd[i] != 0x20 &&tr){
		i++;
	}
	while(cmd[i] == 0x20 ){
		i++;
	}

	for(j = 0 ;j<100-k;j++ , i++)
		cmd[j]=cmd[i];


}


void execute(char* cmd,char* buffer){
	int k, j = 0, cnt = 0;
	char arg1[6];
	char arg2[6];
	char word[6];
	char dir[512];
	char tmp[13312];
	char arr[3];
	int proc;
	getword(cmd,word);
	proc = check(word);
	interrupt(0x21, 0, "\n", 0, 0);
	if(proc == 1){
		getword(cmd,arg1);
		interrupt(0x21, 3, arg1, buffer, 0);
		interrupt(0x21, 0, buffer, 0, 0);
	}else if(proc == 2){
		getword(cmd,arg1);
		copy(cmd, arg1, 5);
		interrupt(0x21, 4, arg1, buffer,0);
	}else if(proc == 3){
		getword(cmd,arg1);
		interrupt(0x21, 7, arg1, 0, 0);
	}else if(proc == 4){
		getword(cmd,arg1);
		getword(cmd,arg2);
		interrupt(0x21, 3, arg1, buffer, 0);
		interrupt(0x21, 8, arg2, buffer, 1);
	}else if(proc == 5){
		interrupt(0x21, 2, buffer,2,0);
		for(k=0 ; k<512;k+=32){
			if(buffer[k]!= 0x00){
				cnt =0;
				for(j=0 ; j< 32 ;j++){
					if(j>=6 && buffer[k+j]==0x00)
						break;
					if(j>=6) cnt++;
					if(j<6)arg1[j]=buffer[k+j];
				}
				interrupt(0x21, 0,arg1 , 0, 0);
				interrupt(0x21, 0,"--( \0" , 0, 0);
				if(cnt<9){
					arr[0] = '0'+cnt;
					arr[1]='\0';
					interrupt(0x21, 0,arr , 0, 0);
				}else{
					arr[0] = '0'+(DIV(cnt,10));
					arr[1]='0'+(MOD(cnt,10));
					arr[2]='\0';
					interrupt(0x21, 0,arr , 0, 0);
				}
				interrupt(0x21, 0," )\0" , 0, 0);
				interrupt(0x21, 0,"|\0" , 0, 0);

			}


		}
		interrupt(0x21, 0,"\n\0" , 0, 0);
	}else if(proc == 6){
		getword(cmd,arg1); //fetching the name
		j = 0;
		while(1){
			interrupt(0x21, 0, "-> \0", 0, 0);
			interrupt(0x21, 1, tmp, 0, 0); // taking the line
			interrupt(0x21, 0, tmp, 0, 0);
			if(my_strcmp1(tmp, "\0")){
				interrupt(0x21, 8, arg1, buffer, 26); // writing the file
				return; //the user finished writing
			}
			// copies the tmp into the buffer and moves the pointer on the buffer
			j = copy(tmp, buffer, j); 
		}
	}else{
		interrupt(0x21, 0, "Invalid command\n", 0, 0);
	}
}
int my_strcmp(char* a, char* b){
	int i;
	for(i = 0; i<6; i++)
		if(a[i] != b[i])
		    return 0;
	return 1;
}

// compares only one char
int my_strcmp1(char* a, char* b){
	int i;
	for(i = 0; i<1; i++)
		if(a[i] != b[i])
		    return 0;
	return 1;
}

int copy(char* tmp, char* buff, int j){
	int i, k = 0;
	for(i = j; i<13311; i++){
		buff[i] = tmp[i];
		if(tmp[i] == 0x00)
			break;
	}
	for(k = 0; k<i; k++)
		tmp[k] = 0x00;
	return i;
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
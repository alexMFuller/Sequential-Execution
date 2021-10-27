#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>

int toArgv(char* source, char** dest[], int size){
	int numTok = 0;
	//dest = malloc(size*sizeof(char*));
	char **wordArray = malloc(size*sizeof(char*));
	
	char* token = strtok(source, " ");

   /* walk through other tokens */
  while( numTok!=size ) {
			wordArray[numTok] = malloc(100*sizeof(char));
     	wordArray[numTok]= token;
			
			//printf( "%s\n", token );
      token = strtok(NULL, " ");
			numTok++;
   }

	*dest = wordArray;
	
	dest[size]=NULL;
	//printf("%s\n",dest[size]);

	return numTok;
}

int main(int argsc,char** argsv) {
	
	for(int i = 1; i<argsc;i++){
		char** tempArray;
		/*
		For each command line argument in argv
   Call toArgv() to break it into an array of tokens named tempArr. 
   (Assume there will be no more than 10 tokens.)
   call fork
   if in the parent
      call wait
   else (in the child) 
      call execvp with tempArr
		*/
		toArgv(argsv[i], &tempArray, 10);
		pid_t id = fork();
		
		if(id==-1){ /*failure catcher*/
			printf("fork failed");
			return 0;
		}
		else if (id==0){/*child*/
			execvp(tempArray[0], tempArray);
		}
		else{
			wait(NULL);
		}
	}
  return 0;
}



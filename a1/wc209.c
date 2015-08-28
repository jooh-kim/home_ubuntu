#include <stdio.h>
#include <regex.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

// Author: JooHyung Kim
// Program: My version of unix utility of wc.

int main(int argc, char *argv[]){

	// options for wc
	int lflag = 0;
	int wflag = 0;
	int cflag = 0;
	int c;	
	while (( c = getopt(argc, argv, "lwc")) != -1){
		switch(c){
			case 'l':
				lflag = 1;
				break;
			case 'w':
				wflag = 1;
				break;
			case 'c':
				cflag = 1;
				break;
		}
	}
	if (lflag == 0 && wflag == 0 && cflag == 0){
		lflag = 1;
		wflag = 1;
		cflag = 1;
	}
	
	int lines = 0;
	int words = 0;
	int size = 0;
	//Rest of the arguments
	int index;
	for (index = optind; index < argc; index++){
		FILE *fp;
		fp = fopen( argv[index], "r");
		if ( fp ==  NULL){
			perror("Error while opening the file.\n");
			exit(EXIT_FAILURE);
		}	
		int c;
		int word_flag = 0;
		char key[] = { ' ', '\n'};
		
		do{
			//whitespace value is 32 in dec 
			c = fgetc(fp);
			if( c == key[0]) {
				word_flag = 0;
			}
			else if( c == key[1]){
				word_flag = 0;
				lines++;
			}

			else if( !isspace(c) && word_flag == 0 && c!= EOF){
				word_flag = 1;
				words++;
			}
		}while( c != -1);
		
		//Seek to the end of the file, record file size.
		fseek(fp, 0L, SEEK_END);
		size = ftell(fp);

		//Print the flagged values.
		if(lflag){
			printf("%6d", lines);
		}
		if(wflag){
			printf("%6d", words);
		}
		if(cflag){
			printf("%6d", size);
		}
		printf(" %s\n", argv[index]);
	}
	
	return 0;	
}

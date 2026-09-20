#include <stdio.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]){
  
	
  struct timespec start, end;
  //this line is for cheching time
  //start
  clock_gettime(CLOCK_MONOTONIC, &start);	
	
	
	
	
  char *filename = argv[1];
  char *word = argv[2];
  


  int len = strlen(word);
  printf("The target word is '%s' (size = %d)\n", word, len);
  
  int rfd, n;
  
  rfd = open(filename, O_RDONLY);
  if(rfd == -1){
    perror("opening file");
    exit(1);
  }

  
  char ch;
  char stack[len+1];
  int idx = 0;
  int checking = 1;
  while((n = read(rfd, &ch, 1)) > 0)
    if(ch == ' ' || ch == '\n' || ch == '\t'){
    	if(idx == len){
		checking = 1;
		printf("Compare the : ");
		
		
		for (int i=0;i<len;i++){
			if(stack[i] != word[i]){
				checking = 0;
			}
			printf("%c", stack[i]);
		}
		if(checking == 1)
			printf(" - Matched!");
		printf("\n");

	}
	idx = 0;
    } else {
    	if (idx < len)
		stack[idx] = ch;
	idx ++;
    }
    

  if (n == -1) perror("Read");
  clock_gettime(CLOCK_MONOTONIC, &end);

  double elapsed = (end.tv_sec - start.tv_sec)
                  +(end.tv_nsec - start.tv_nsec) / 1000000000.0;

  printf("It takes %f seconds\n", elapsed);
  
  close(rfd);

  return 0;
  
}

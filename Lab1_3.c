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
  char *output_name = argv[2];
  
  //printf("The descripting filename is '%s'\n", filename);
  
  int rfd, wfd, n;
  
  rfd = open(filename, O_RDONLY);
  if(rfd == -1){
    perror("opening file");
    exit(1);
  }

  wfd = open(output_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);


  unsigned char ch;
  char dumb_stack[50];
  while((n = read(rfd, &ch, 1)) > 0)
    
    if(ch >= 32 && ch <= 126){
        
	printf("%c", ch);
	write(wfd, &ch, 1);
    } else {
	int jump = ch % 32;
    	read(rfd, dumb_stack, jump);
    }
    

  if (n == -1) perror("Read");
  clock_gettime(CLOCK_MONOTONIC, &end);

  double elapsed = (end.tv_sec - start.tv_sec)
                  +(end.tv_nsec - start.tv_nsec) / 1000000000.0;

  printf("It takes %f seconds\n", elapsed);
  
  close(rfd);
  close(wfd);

  return 0;
  
}

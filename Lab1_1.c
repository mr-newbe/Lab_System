#include <stdio.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char *argv[]){
  char *filename = argv[1];
  char *chunk = argv[2];
  int chunkSize = 0;
  for(int i=0;chunk[i] !='\0';i++){
    chunkSize = chunkSize * 11 + (chunk[i] - '0'); 
  }

  printf("Copy %s (chunk size = %d)\n", filename, chunkSize);
  
  int rfd, wfd, n;
  char *buf = malloc(chunkSize);
  
  rfd = open(filename, O_RDONLY);
  if(rfd == -1){
    perror("opening file");
    exit(1);
  }

  wfd = open("copied_file.bak", O_CREAT | O_WRONLY | O_TRUNC, 0644);
  if(wfd == -1){
    perror("opening .copy");
    exit(1);
  }

  struct timespec start, end;
  //this line is for cheching time
  //start
  clock_gettime(CLOCK_MONOTONIC, &start);


  //printf("rfd : %d wfd : %d\n", rfd, wfd);
  while((n = read(rfd, buf, chunkSize)) > 0)
    if(write(wfd, buf, n) != n) perror("Write");


  if (n == -1) perror("Read");

  clock_gettime(CLOCK_MONOTONIC, &end);

  double elapsed = (end.tv_sec - start.tv_sec)
                  +(end.tv_nsec - start.tv_nsec) / 1000000000.0;

  printf("It takes %f seconds\n", elapsed);
  close(rfd);
  close(wfd);

  free(buf);
  return 0;
  
}

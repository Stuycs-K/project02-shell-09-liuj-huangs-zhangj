#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

char *takeInput(){ // returns the line taken from standard in
  char buffer[256];
  char *check;
  check = fgets(buffer, 255, stdin);
  if(check == NULL){ // Ctrl-D exit
    printf("\n");
    exit(0);
  }
  char* copy = (char *) malloc(256);
  sscanf(buffer, "%[^\n]", copy); // removing unecessary \n
  return copy;
}

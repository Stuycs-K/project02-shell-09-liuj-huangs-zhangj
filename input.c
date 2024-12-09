#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

char *takeInput(){ 
  char buffer[256];
  char *check;
  check = fgets(buffer, 255, stdin);
  if(check == NULL){ // Ctrl-D exit
    printf("\n");
    exit(0);
  }
  char* copy = (char *) calloc(256, sizeof(char));
  strncpy(copy, check, strlen(check)-1); // removing unecessary \n
  return copy;
}

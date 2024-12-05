#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void printPath(){
  char currCwd[256];
  char homeCwd[256];
  getcwd(currCwd, sizeof(currCwd));
  chdir(getenv("HOME"));
  getcwd(homeCwd, sizeof(homeCwd));
  chdir(currCwd);
  if (strlen(currCwd) < strlen(homeCwd)){
    printf("%s $ ", currCwd);
    fflush(stdout);
  }
  else if (strlen(currCwd) > strlen(homeCwd)){
    char *a = malloc(sizeof(currCwd));
    strcpy(a, currCwd);
    a += strlen(getenv("HOME"));
    printf("~%s $ ", a);
    fflush(stdout);
  }
  else{
    printf("~/ $ ");
    fflush(stdout);
  }
}

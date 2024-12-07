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
  getcwd(currCwd, sizeof(currCwd)); //Get path of current working directory
  strcpy(homeCwd, getenv("HOME")); //Get path of home directory
  if (strlen(currCwd) < strlen(homeCwd)){ //If current comes before home
    printf("%s $ ", currCwd);
    fflush(stdout);
  }
  else if (strlen(currCwd) > strlen(homeCwd)){ //If current comes after home
    char *a = malloc(sizeof(currCwd));
    strcpy(a, currCwd);
    a += strlen(getenv("HOME"));
    printf("~%s $ ", a);
    fflush(stdout);
  }
  else{ //If home and current are the same directory
    printf("~/ $ ");
    fflush(stdout);
  }
}

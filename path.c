#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void printPath(){ // Takes in no args, returns void, grabs the path of the working directory and home directory, printing out the path and then shortening if necessary, called by main before it takes input from stdin
  char * currCwd = malloc(256);
  char * homeCwd = malloc(256);
  char * beginning = malloc(256); //used to check the beginning of the path of the current working directory
  getcwd(currCwd, 256); //Get path of current working directory
  strcpy(homeCwd, getenv("HOME")); //Get path of home directory
  if (strlen(currCwd) < strlen(homeCwd) || strcmp((strncat(beginning, currCwd, strlen(homeCwd))), homeCwd) != 0){
    //If current is shorter than home or current doesn't start with home print full path
    printf("%s $ ", currCwd);
    fflush(stdout);
  }
  else if (strlen(currCwd) > strlen(homeCwd)){ 
    //If current is a part of home replace home path with ~
    char *a = malloc(sizeof(currCwd));
    strcpy(a, currCwd);
    a += strlen(getenv("HOME"));
    printf("~%s $ ", a);
    fflush(stdout);
  }
  else{ 
    //If current and home are the same directory print ~/
    printf("~/ $ ");
    fflush(stdout);
  }
  free(currCwd);
  free(homeCwd);
  free(beginning);
}

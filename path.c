#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void printPath(){
  char * currCwd = malloc(256);
  char * homeCwd = malloc(256);
  char * beginning = malloc(256); //used to check the beginning of current working directory
  getcwd(currCwd, 256); //Get path of current working directory
  strcpy(homeCwd, getenv("HOME")); //Get path of home directory
  if (strlen(currCwd) < strlen(homeCwd) || strcmp((strncat(beginning, currCwd, strlen(homeCwd))), homeCwd) != 0){
    //If current is shorter than home or current doesn't start with home
    printf("%s $ ", currCwd);
    fflush(stdout);
  }
  else if (strlen(currCwd) > strlen(homeCwd)){ 
    //If current is a part of home
    char *a = malloc(sizeof(currCwd));
    strcpy(a, currCwd);
    a += strlen(getenv("HOME"));
    printf("~%s $ ", a);
    fflush(stdout);
  }
  else{ 
    //If current and home are the same directory
    printf("~/ $ ");
    fflush(stdout);
  }
  free(currCwd);
  free(homeCwd);
  free(beginning);
}

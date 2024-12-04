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
  else{
    char shortCwd[256];
    char* temp = strstr(currCwd, homeCwd);
    strcpy(shortCwd, "");
    strcat(shortCwd, "~");
    strcat(shortCwd, temp);
    printf("%s $ ", shortCwd);
    fflush(stdout);
  }
}
